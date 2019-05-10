//=============================================================================
//
// DirectX雛型処理 [main.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "input.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "Selectmode.h"
#include "fade.h"
#include "sound.h"
#include "game2.h"
#include "game3.h"
#include "arasuji.h"
#include "clia.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME		"私はモンスターだが人間に勝ちたい"	// ウインドウの名前(キャプション名)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;					//Direct3Dオブジェクトのポイント
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//DirectXデバイスのポインタ
MODE g_Mode = MODE_TITLE;					//画面スタート時モード
SELECTSTATE g_aSelSTE;

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

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	srand((unsigned int)time(0));	//ラウンド

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

	// ウィンドウの生成
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

	// 初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd,FALSE)))//TRUEをFALSEにするとフルスクリーン
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
		break;
	}
	g_aSelSTE = GetSelstate();
	if (g_aSelSTE == SELECT_QUIT)
	{
		PostQuitMessage(0);
		DestroyWindow(hWnd);
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
	d3dpp.BackBufferWidth			 = 1280;				// ゲーム画面サイズ(幅)1280
	d3dpp.BackBufferHeight			 = 720;			    // ゲーム画面サイズ(高さ)720
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファの形式
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
    d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;					    // ウィンドウモード
	//d3dpp.Windowed					= false;					    // ウィンドウモード
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
	SetMode(g_Mode);

	//フェードの設定
	InitFade(g_Mode);

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
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 更新処理インプット
	UpdateKeyboard();
	switch (g_Mode)
	{
	case MODE_TITLE:   //タイトル
		UpdateTitle();
		break;
	case MODE_SELECT: //セレクト
		UpdateSelectmode();
		break;
	case MODE_ARASU:
		UpdateArasuji();
		break;
	case MODE_GAME:
		UpdateGame();  //ゲーム
		break;
	case MODE_GAME2:
		UpdateGame2();  //ゲーム
		break;
	case MODE_GAME3:
		UpdateGame3();  //ゲーム
		break;
	case MODE_TUTO:
		UpdateTutorial();  //チュートリアル
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_CLIA:
		UpdateCLIA();
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
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_Mode)
		{
		case MODE_TITLE: //タイトル
			DrawTitle();
			break;
		case MODE_SELECT:
			DrawSelectmode();
			break;
		case MODE_ARASU:
			DrawArasuji();
			break;
		case MODE_GAME:  //ゲーム
			DrawGame();
			break;
		case MODE_GAME2:  //ゲーム
			DrawGame2();
			break;
		case MODE_GAME3:  //ゲーム
			DrawGame3();
			break;
		case MODE_TUTO:
			DrawTutorial(); //津y-トリアル
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_CLIA:
			DrawCLIA();
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
	switch (g_Mode)
	{
	case MODE_TITLE:
		StopSound(SOUND_LABEL_BGM010);
		UninitTitle();
		break;
	case MODE_SELECT:
		StopSound(SOUND_LABEL_BGM008);
		UninitSelectmode();
		break;
	case MODE_ARASU:
		StopSound(SOUND_LABEL_BGM013);
		UninitArasuji();
		break;
	case MODE_GAME:
		StopSound(SOUND_LABEL_BGM011);
		UninitGame();
		break;
	case MODE_GAME2:
		StopSound(SOUND_LABEL_BGM011);
		UninitGame2();
		break;
	case MODE_GAME3:
		StopSound(SOUND_LABEL_BGM014);
		UninitGame3();
		break;
	case MODE_TUTO:
		StopSound(SOUND_LABEL_BGM015);
		UninitTutorial();
		break;
	case MODE_RESULT:
		StopSound(SOUND_LABEL_BGM012);
		UninitResult();
		break;
	case MODE_CLIA:
		StopSound(SOUND_LABEL_BGM014);
		UninitCLIA();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		PlaySound(SOUND_LABEL_BGM010);
		InitTitle();
		break;
	case MODE_SELECT:
		PlaySound(SOUND_LABEL_BGM008);
		InitSelectmode();
		break;
	case MODE_ARASU:
		PlaySound(SOUND_LABEL_BGM013);
		InitArasuji();
		break;
	case MODE_GAME:
		PlaySound(SOUND_LABEL_BGM011);
		InitGame();
		break;
	case MODE_GAME2:
		PlaySound(SOUND_LABEL_BGM011);
		InitGame2();
		break;
	case MODE_GAME3:
		PlaySound(SOUND_LABEL_BGM014);
		InitGame3();
		break;
	case MODE_TUTO:
		PlaySound(SOUND_LABEL_BGM015);
		InitTutorial();
		break;
	case MODE_RESULT:
		PlaySound(SOUND_LABEL_BGM012);
		InitResult();
		break;
	case MODE_CLIA:
		PlaySound(SOUND_LABEL_BGM014);
		InitCLIA();
		break;
	}
	g_Mode = mode;
}
MODE GetMode(void)
{
	return g_Mode;
}
