//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 舘田 翼
//
//=============================================================================
#include "main.h"
#include "poker.h"
#include "battle.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "cardModel.h"
#include "ui.h"
#include "camera.h"
#include "fade.h"
#include "light.h"
#include "PlayerShow.h"
#include "player.h"
#include "game.h"
#include "title.h"
#include "select.h"
#include "rule.h"
#include "rulebook.h"
#include "credit.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"Fighting Poker"		// ウインドウのキャプション名
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// デバイスオブジェクト(描画に必要)
MODE g_mode = MODE_TITLE;
LPD3DXFONT				g_pFont = NULL;		// フォントへのポインタ
void DrawGuide(void);
//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = TRUE;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

																// デバイスオブジェクトの生成
																// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

																			// キーボードの初期化処理
	InitKeyboard(hInstance, hWnd);
	// ゲームパッドの初期化処理
	InitGamePad(hInstance, hWnd);
	// サウンドの初期化処理
	InitSound(hWnd);
	// フェードの設定
	InitFade(g_mode);
	// カメラの初期化処理
	InitCamera();
	// ライトの初期化処理
	InitLight();
	//モードの設定
	SetMode(g_mode);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// デバッグ情報表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//キーボードの終了処理
	UninitKeyboard();
	// ゲームパッドの終了処理
	UninitGamePad();
	// サウンドの終了処理
	UninitSound();
	//フェードの終了処理
	UninitFade();
	// ライトの終了処理
	UninitLight();

	if (g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// キーボードの更新処理
	UpdateKeyboard();
	// ゲームパッドの更新処理
	UpdateGamePad();

	switch (g_mode)
	{
	case MODE_TITLE:		// タイトルモード
		UpdateTitle();
		break;
	case MODE_SELECT:		// セレクトモード
		UpdateSelect();
		break;
	case MODE_RULE:			// ルールブックモード
		UpdateRulebook();
		break;
	case MODE_CREDIT:		// クレジットモード
		UpdateCredit();
		break;
	case MODE_GAME:			// ゲームモード
		UpdateGame();
		break;
	}

	//フェードの更新
	UpdateFade();
	// カメラの更新処理
	UpdateCamera();
	// ライトの更新処理
	UpdateLight();
}
//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// カメラの設定
		SetCamera(0);
		switch (g_mode)
		{
		case MODE_TITLE:		// タイトルモード
			DrawTitle();
			break;
		case MODE_SELECT:		// セレクトモード
			DrawSelect();
			break;
		case MODE_RULE:			// ルールブックモード
			DrawRulebook();
			break;
		case MODE_CREDIT:		// クレジットモード
			DrawCredit();
			break;
		case MODE_GAME:			// ゲームモード
			DrawGame();
			// デバッグ用コマンド
		//	DrawGuide();
			break;
		}

		// フェードの描画
		DrawFade();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//ゲームモードの設定
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:		// タイトルモード
		UninitTitle();
		StopSound(SOUND_LABEL_TITLE_BGM);
		break;
	case MODE_SELECT:		// セレクトモード
		UninitSelect();
		StopSound(SOUND_LABEL_SELECT_BGM);
		break;
	case MODE_RULE:			// ルールブックモード
		UninitRulebook();
		break;
	case MODE_CREDIT:		// クレジットモード
		UninitCredit();
		StopSound(SOUND_LABEL_CREDIT_BGM);
	case MODE_GAME:
		UninitGame();		// ゲームモード
		break;
	}

	// モードを代入
	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:		// タイトルモード
		InitTitle();
		StopSound();
		PlaySound(SOUND_LABEL_TITLE_BGM);
		SelectVolume(SOUND_LABEL_TITLE_BGM, 0.2f);
		break;
	case MODE_SELECT:		// セレクトモード
		InitSelect();
		PlaySound(SOUND_LABEL_SELECT_BGM);
		SelectVolume(SOUND_LABEL_SELECT_BGM, 0.2f);
		break;
	case MODE_RULE:			// ルールブックモード
		InitRulebook();
		break;
	case MODE_CREDIT:		// クレジットモード
		InitCredit();
		StopSound(SOUND_LABEL_SELECT_BGM);
		PlaySound(SOUND_LABEL_CREDIT_BGM);
		SelectVolume(SOUND_LABEL_CREDIT_BGM, 0.2f);
		break;
	case MODE_GAME:			// ゲームモード
		InitGame();
		StopSound(SOUND_LABEL_SELECT_BGM);
		break;
	}
}
//=============================================================================
//ゲームモードの取得
//============================================================================
MODE GetMode(void)
{
	return g_mode;
}
//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

////=============================================================================
//// 文字表示処理
////=============================================================================
void DrawGuide(void)
{
	GAMEMODE GameMode = GetGameMode();
	FADE pFade;
	pFade = GetFade();

	Camera *pCamera = GetCamera();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[10000];
	int nLength = 0;

	CARDSIDE side = GetPokerState();

	int nNumHand1P = GetHandNum(0);
	int nNumHand2P = GetHandNum(1);

	CARDTYPE type1P = GetType(0);
	CARDTYPE type2P = GetType(1);

	CARDTYPE Hand1P[5];
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		Hand1P[nCnt] = Get1PHand(nCnt);
	}
	CARDTYPE Hand2P[5];
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		Hand2P[nCnt] = Get2PHand(nCnt);
	}

	if (GameMode == GAMEMODE_POKER)
	{
		switch (side)
		{
		case CARD_SIDE_1P:
			wsprintf(&aStr[nLength], "1Pの番\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case CARD_SIDE_2P:
			wsprintf(&aStr[nLength], "2Pの番\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case CARD_SIDE_ALL:
			wsprintf(&aStr[nLength], "終了\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "================== 1P ===================\n");
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "\n現在の役\n");
		nLength = (int)strlen(&aStr[0]);
		switch (nNumHand1P)
		{
		case 0:
			wsprintf(&aStr[nLength], "ハイカード [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 1:
			wsprintf(&aStr[nLength], "ワンペア [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 2:
			wsprintf(&aStr[nLength], "ツーペア [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 3:
			wsprintf(&aStr[nLength], "スリーカード [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 4:
			wsprintf(&aStr[nLength], "フォーカード [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 5:
			wsprintf(&aStr[nLength], "フラッシュ [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 10:
			wsprintf(&aStr[nLength], "フルハウス [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 100:
			wsprintf(&aStr[nLength], "STRONG　ZERO [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "\n現在の手札\n");
		nLength = (int)strlen(&aStr[0]);
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			wsprintf(&aStr[nLength], "%d枚目", nCnt + 1);
			nLength = (int)strlen(&aStr[0]);
			switch (Hand1P[nCnt])
			{
			case TYPE_BRAVE:
				wsprintf(&aStr[nLength], "[ 勇者 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_KING:
				wsprintf(&aStr[nLength], "[ 王様 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_DEVIL:
				wsprintf(&aStr[nLength], "[ 魔王 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_COMMONER:
				wsprintf(&aStr[nLength], "[ 平民 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_JOKER:
				wsprintf(&aStr[nLength], "[ ジョーカー ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			}
		}
		wsprintf(&aStr[nLength], "\n現在のキャラクター\n");
		nLength = (int)strlen(&aStr[0]);
		switch (type1P)
		{
		case TYPE_BRAVE:
			wsprintf(&aStr[nLength], "[ 勇者 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_KING:
			wsprintf(&aStr[nLength], "[ 王様 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_DEVIL:
			wsprintf(&aStr[nLength], "[ 魔王 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_COMMONER:
			wsprintf(&aStr[nLength], "[ 平民 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_GOD:
			wsprintf(&aStr[nLength], "[ 平民(強) ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "================== 2P ===================\n");
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "\n現在の役\n");
		nLength = (int)strlen(&aStr[0]);
		switch (nNumHand2P)
		{
		case 0:
			wsprintf(&aStr[nLength], "ハイカード [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 1:
			wsprintf(&aStr[nLength], "ワンペア [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 2:
			wsprintf(&aStr[nLength], "ツーペア [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 3:
			wsprintf(&aStr[nLength], "スリーカード [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 4:
			wsprintf(&aStr[nLength], "フォーカード [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 5:
			wsprintf(&aStr[nLength], "フラッシュ [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 10:
			wsprintf(&aStr[nLength], "フルハウス [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 100:
			wsprintf(&aStr[nLength], "STRONG　ZERO [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "\n現在の手札\n");
		nLength = (int)strlen(&aStr[0]);
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			wsprintf(&aStr[nLength], "%d枚目", nCnt + 1);
			nLength = (int)strlen(&aStr[0]);
			switch (Hand2P[nCnt])
			{
			case TYPE_BRAVE:
				wsprintf(&aStr[nLength], "[ 勇者 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_KING:
				wsprintf(&aStr[nLength], "[ 王様 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_DEVIL:
				wsprintf(&aStr[nLength], "[ 魔王 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_COMMONER:
				wsprintf(&aStr[nLength], "[ 平民 ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_JOKER:
				wsprintf(&aStr[nLength], "[ ジョーカー ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			}
		}
		wsprintf(&aStr[nLength], "\n現在のキャラクター\n");
		nLength = (int)strlen(&aStr[0]);
		switch (type2P)
		{
		case TYPE_BRAVE:
			wsprintf(&aStr[nLength], "[ 勇者 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_KING:
			wsprintf(&aStr[nLength], "[ 王様 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_DEVIL:
			wsprintf(&aStr[nLength], "[ 魔王 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_COMMONER:
			wsprintf(&aStr[nLength], "[ 平民 ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_GOD:
			wsprintf(&aStr[nLength], "[ 平民(強) ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
	}
	else if (GameMode == GAMEMODE_BATTLE)
	{
		// 文字列を代入(カメラの視点
		wsprintf(&aStr[0], "[カメラの視点       : (%d : %d : %d)]\n", (int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z);

		// 文字列を代入(カメラの注視点
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "[カメラの注視点     : (%d : %d : %d)]\n\n", (int)pCamera->posR.x, (int)pCamera->posR.y, (int)pCamera->posR.z);

		Player *pPlayer = GetPlayer();

		// Player1.HP表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_HP : %d\n", pPlayer[0].nLife);

		// Player1.スキルポイント表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_SKIL : %d\n", pPlayer[0].nSkillPoint);

		// Player1.ステータスランク表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_ATK : %d\n", (int)pPlayer[0].atkRank);
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_DEF : %d\n", (int)pPlayer[0].defRank);

		// Player1.モーション表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_モーション : %d\n", (int)pPlayer[0].MotionType);

		// Player2.HP表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_HP : %d\n", pPlayer[1].nLife);

		// Player2.スキルポイント表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_SKIL : %d\n", pPlayer[1].nSkillPoint);

		// Player1.ステータスランク表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_ATK : %d\n", (int)pPlayer[1].atkRank);
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_DEF : %d\n", (int)pPlayer[1].defRank);

		// Player2.モーション表記
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_モーション : %d\n", (int)pPlayer[1].MotionType);

		// 移動制限距離
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "移動制限距離 : %d\n", GetMoveRimit());

		// FPS
		/*nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "FPS : %d\n", g_nCountFPS);*/

		// 文字列を代入(モデル操作
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "*** 全リセット ***\nENTER\n");
	}
	else
	{
		wsprintf(&aStr[0], "デバッグ用表記です");
	}

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0x0, 0xff));
}

