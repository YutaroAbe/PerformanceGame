//=============================================================================
//
// メイン処理 [main.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "title.h"//タイトル
#include "game.h"//ゲーム
#include "result.h"//リザルト
#include "tutorial.h"//チュートリアル
#include "main.h"//メインｈ
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "score.h"
#include "serect.h"
#include "clear.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME		"楽器の達人"		// ウインドウの名前(キャプション名)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
void Uninit(void);
void Update(void);
void Draw(void);

void DrawTX(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;					//Direct3Dオブジェクトのポイント
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//DirectXデバイスのポインタ
MODE g_mode = MODE_TITLE;					//画面スタート時モード

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;//ウィンドウハンドル（識別子）
	MSG msg; //メッセージを格納する変数

	DWORD dwCurrentTime; //	現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻

	timeBeginPeriod(1);//分解能

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	srand((unsigned int)time(0));	//ラウンド

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							//SCREEN_WIDTH,
							//SCREEN_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd, FALSE)))//TRUEをFALSEにするとフルスクリーン
	{
		return -1;
	}

	//分解能
	timeBeginPeriod(1);

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"メッセージが送られてきたらループを抜ける
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
		{// DirectXの処理
			dwCurrentTime = timeGetTime();	//現在時刻を取得
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の１秒経過
				dwExecLastTime = dwCurrentTime;	//処理した時刻を保存

			}
			// 更新処理
			Update();
			// 描画処理
			Draw();

		}
	}
	// 終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);


	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{

	case WM_DESTROY:
		// "WM_QUIT"メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			// ウィンドウを破棄する("WM_DESTROY"メッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;									//プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
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
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferWidth =SCREEN_WIDTH;				// ゲーム画面サイズ(幅)1280
		d3dpp.BackBufferHeight =SCREEN_HEIGHT;			    // ゲーム画面サイズ(高さ)720
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファの形式
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
    d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;					    // ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート(現在の速度に合わせる)	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)

	// Direct3Dデバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// デバイスタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャーステージステート
	/*g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);*/

	//初期化処理インプット
	InitKeyboard(hInstance, hWnd);
	//サウンドの設定
	InitSound(hWnd);
	//モードの設定
	SetMode(g_mode);
	////初期化タイトル
	//InitTitle();
	////初期化セレクトモード
	//InitSelectmode();
	////初期化チュートリアル
	//InitTUTORIAL();
	////初期化ゲーム
	//InitGAME();
	////初期化ランキング
	//InitRanking();
	////初期化リザルト
	//InitRESULT();
	////初期化クリア
	//InitCLEAR();
	//フェードの設定
	InitFade(g_mode);

	// 情報表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 33, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "monospace", &g_pFont);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// 終了処理インプット
	UninitKeyboard();
	//サウンド
	UninitSound();
	////終了処理タイトル
	//UninitTitle();
	////終了処理セレクトモード
	//UninitSelectmode();
	////終了処理チュートリアル
	//UninitTUTORIAL();
	////終了処理ゲーム
	//UninitGAME();
	////終了処理ランキング
	//UninitRanking();
	////終了処理リザルト
	//UninitRESULT();
	////終了処理クリア
	//UninitCLEAR();
	//終了処理フェイド
	UninitFade();

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice -> Release();
		g_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{// デバッグ表示用フォントの開放
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 更新処理インプット
	UpdateKeyboard();
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_SELECTMODE:
		UpdateSerect();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_GAME:
		UpdateGAME();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;
	case MODE_RESULT:
		UpdateRESULT();
		break;
	case MODE_CLEAR:
		UpdateCLEAR();
		break;
	}
	//フェードの更新処理
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
		// バックバッファ＆Ｚバッファのクリア
		g_pD3DDevice->Clear(0,
			NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);//画面色設定(0,0,0,0,)は黒

		//描画の開始
		if (SUCCEEDED(g_pD3DDevice->BeginScene()))
		{
			switch (g_mode)
			{
			case MODE_TITLE:
				DrawTitle();
				break;
			case MODE_SELECTMODE:
				DrawSerect();
				break;
			case MODE_TUTORIAL:
				DrawTutorial();
				break;
			case MODE_GAME:
				DrawGAME();
				DrawTX();
				break;
			case MODE_RANKING:
				DrawRanking();
				break;
			case MODE_RESULT:
				DrawRESULT();
				break;
			case MODE_CLEAR:
				DrawCLEAR();
				break;
			}
			//フェードの描画処理
			DrawFade();
			// 描画の終了
			g_pD3DDevice->EndScene();

		}

		// バックバッファとフロントバッファの入れ替え
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//=============================================================================
//デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		StopSound(SOUND_LABEL_BGM003);
		UninitTitle();
		break;
	case MODE_SELECTMODE:
		StopSound(SOUND_LABEL_BGM004);
		UninitSerect();
		break;
	case MODE_TUTORIAL:
		StopSound(SOUND_LABEL_BGM003);
		UninitTutorial();
		break;
	case MODE_GAME:
		StopSound(SOUND_LABEL_BGM005);
		UninitGAME();
		break;
	case MODE_RANKING:
		StopSound(SOUND_LABEL_BGM007);
		UninitRanking();
		break;
	case MODE_RESULT:
		StopSound(SOUND_LABEL_BGM008);
		UninitRESULT();
		break;
	case MODE_CLEAR:
		StopSound(SOUND_LABEL_BGM009);
		UninitCLEAR();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		PlaySound(SOUND_LABEL_BGM003);
		InitTitle();
		break;
	case MODE_SELECTMODE:
		PlaySound(SOUND_LABEL_BGM004);
		InitSerect();
		break;
	case MODE_TUTORIAL:
		PlaySound(SOUND_LABEL_BGM003);
		InitTutorial();
		break;
	case MODE_GAME:
		PlaySound(SOUND_LABEL_BGM005);
		InitGAME();
		break;
	case MODE_RANKING:
		PlaySound(SOUND_LABEL_BGM007);
		InitRanking();
		break;
	case MODE_RESULT:
		PlaySound(SOUND_LABEL_BGM008);
		InitRESULT();
		break;
	case MODE_CLEAR:
		PlaySound(SOUND_LABEL_BGM009);
		InitCLEAR();
		break;
	}
	g_mode = mode;

}
MODE GetMode(void)
{
	return g_mode;
}
void DrawTX(void)
{
	//RECT rect = { 0, 15, SCREEN_WIDTH, SCREEN_HEIGHT };
	//char str[256];
	//int nNumNumber = GetGameCounter();


	//wsprintf(str, "%d",nNumNumber);

	//g_pFont->DrawText(NULL, &str[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/);


}