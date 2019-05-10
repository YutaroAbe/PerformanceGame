//=============================================================================
//
// メイン処理 [main.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "title.h"
#include "Selectmode.h"
#include "fade.h"
#include "gameover.h"
#include "sound.h"
#include "clear.h"
#include "tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"										// ウインドウのクラス名
#define WINDOW_NAME		"夢からの脱出少年A"							// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
void Uninit(void);
void Update(void);
void Draw(void);
void DrawSelTXIT(void);						//セレクト画面の文字

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// デバイスオブジェクト(描画に必要)
MODE g_Mode = MODE_TITLE;					//画面スタート時モード
SELECTSTATE g_aSelSTE;						//セレクトの状態
int g_aSelectMenuMain;						//セレクトのメニュー
int g_aSelCounter;							//セレクトの会話出すカウンター
int g_aStoryMenuMain;						//ストーリーのメニュー
int g_aEndStoryMenuMain;					//エンドストーリーのメニュー

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
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
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
	if(FAILED(Init(hInstance, hWnd, FALSE)))
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
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
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

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
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
	switch(uMsg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
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
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
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

	//// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
																			//フォントオブジェクトの作成
	D3DXCreateFont(g_pD3DDevice, 38/*文字の高さ*/, 16/*文字の幅*/, 0/*フォントの太さ*/, 0/*ミップマップレベル数*/, FALSE, SHIFTJIS_CHARSET,//HANGEUL_CHARSET韓国語//SHIFTJIS_CHARSET日本語
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("monospace")/* フォント名*/, &g_pFont);

	srand((unsigned int)time(0));

	//初期化処理インプット
	InitInput(hInstance, hWnd);
	// サウンドの初期化処理
	InitSound(hWnd);
	//モード設定
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

	if (g_pFont != NULL)
	{// デバッグ表示用フォントの開放
		g_pFont->Release();
		g_pFont = NULL;
	}
	// サウンドの終了処理
	UninitSound();
	// 終了処理インプット
	UninitInput();
	//終了処理フェイド
	UninitFade();

	if(g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if(g_pD3D != NULL)
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
	// 更新処理インプット
	UpdateInput();


	switch (g_Mode)
	{
	case MODE_TITLE:			//タイトルの更新処理
		UpdateTitle();
		break;
	case MODE_SELCT:
		UpdateSelectmode();		//セレクトの更新処理
		break;
	case MODE_GAME:				//ゲームの更新処理
		UpdateGame();
		break;
	case MODO_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_CLEAR:
		UpdateClear();			//ゲームクリア
		break;
	case MODE_GAMEOVER:			//ゲームオーバーの更新処理
		UpdateGameOver();
		break;
	case MODE_RANKING:			//ランキング更新処理

		break;
	}
	//終了処理フェイド
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_Mode)
		{
		case MODE_TITLE:
			DrawTitle();					//タイトルの描画処理

			break;
		case MODE_SELCT:
			DrawSelectmode();
			if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_11, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_10, 0) == true){ g_aSelCounter=0;}
			else{
				DrawSelTXIT();				//セレクト文字出力
				g_aSelCounter++;			//セレクトの文字列カウンター++
				}

			break;
		case MODE_GAME:
			DrawGame();						//ゲームの描画処理
			break;
		case MODO_TUTORIAL:
			DrawTutorial();
			break;
		case MODE_CLEAR:
			DrawClear();					//ゲームクリア
			break;
		case MODE_GAMEOVER :				//ゲームオーバーの描画処理
			DrawGameOver();
			break;
		case MODE_RANKING:			//ランキング更新処理

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
// デバイスの取得
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
		StopSound(SOUND_LABEL_BGM000);
		UninitTitle();				//タイトルの終了処理
		break;
	case MODE_SELCT:
		StopSound(SOUND_LABEL_BGM001);
		UninitSelectmode();			//セレクトの終了処理
		break;
	case MODE_GAME:
		StopSound(SOUND_LABEL_BGM002);
		UninitGame();				//ゲームの終了処理
		break;
	case MODO_TUTORIAL:
		StopSound(SOUND_LABEL_BGM003);
		UninitTutorial();
		break;
	case MODE_CLEAR:
		StopSound(SOUND_LABEL_BGM004);
		UninitClear();
		break;
	case MODE_GAMEOVER:				//ゲームオーバーの終了処理
		StopSound(SOUND_LABEL_BGM005);
		UninitGameOver();
		break;
	case MODE_RANKING:			//ランキング更新処理
		StopSound(SOUND_LABEL_BGM006);
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		PlaySound(SOUND_LABEL_BGM000);
		InitTitle();				//タイトルの初期化処理
		break;
	case MODE_SELCT:
		PlaySound(SOUND_LABEL_BGM001);
		InitSelectmode();			//セレクトの初期化処理
		g_aSelCounter = 0;			//セレクトの文字列カウンター
		break;
	case MODE_GAME:
		PlaySound(SOUND_LABEL_BGM002);
		InitGame();					//ゲームの初期化処理
		break;
	case MODO_TUTORIAL:
		PlaySound(SOUND_LABEL_BGM003);
		InitTutorial();
		break;
	case MODE_CLEAR:
		PlaySound(SOUND_LABEL_BGM004);
		InitClear();
		break;
	case MODE_GAMEOVER:				//ゲームオーバーの初期化処理
		PlaySound(SOUND_LABEL_BGM005);
		InitGameOver();
		break;
	case MODE_RANKING:			//ランキング更新処理
		PlaySound(SOUND_LABEL_BGM006);
		break;
	}
	g_Mode = mode;
}
//=============================================================================
//
//=============================================================================
MODE GetMode(void)
{
	return g_Mode;
}
//=============================================================================
// セレクト画面の文字
//=============================================================================
void DrawSelTXIT(void)
{
	RECT rect = { 220, 480, SCREEN_WIDTH, SCREEN_HEIGHT };// 左上のx座標// 左上のy座標// 右下のx座標// 右下のy座標
	char aTX[256];
	g_aSelectMenuMain = GetSelMenu();

	// 文字列を代入//一文字につきスペース3つ
	if (g_aSelectMenuMain == 0)
	{
		if (g_aSelCounter >= 20)  { wsprintf(&aTX[0], "こ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/);}
		if (g_aSelCounter >= 25)  { wsprintf(&aTX[0], "   れ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/);}
		if (g_aSelCounter >= 30)  { wsprintf(&aTX[0], "      は\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/);}
		if (g_aSelCounter >= 35)  { wsprintf(&aTX[0], "         チ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*色*/); }
		if (g_aSelCounter >= 40)  { wsprintf(&aTX[0], "            ュー\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*色*/); }
		if (g_aSelCounter >= 45)  { wsprintf(&aTX[0], "                  ト\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*色*/); }
		if (g_aSelCounter >= 50)  { wsprintf(&aTX[0], "                     リ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*色*/); }
		if (g_aSelCounter >= 55)  { wsprintf(&aTX[0], "                        ア\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*色*/); }
		if (g_aSelCounter >= 60)  { wsprintf(&aTX[0], "                           ル\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 65)  { wsprintf(&aTX[0], "                              です。\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 70)  { wsprintf(&aTX[0], "\nゲ", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 75)  { wsprintf(&aTX[0], "\n   ーム", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 80)  { wsprintf(&aTX[0], "\n         内容", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 85)  { wsprintf(&aTX[0], "\n               を", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 90)  { wsprintf(&aTX[0], "\n                  説", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 95)  { wsprintf(&aTX[0], "\n                     明", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 100) { wsprintf(&aTX[0], "\n                        して", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 105) { wsprintf(&aTX[0], "\n                              いき", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 110) { wsprintf(&aTX[0], "\n                                    ます", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 115) { wsprintf(&aTX[0], "\n                                          !!", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }

	}
	else if (g_aSelectMenuMain == 1)
	{
		if (g_aSelCounter >= 20)  { wsprintf(&aTX[0], "こ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 25)  { wsprintf(&aTX[0], "   れ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 30)  { wsprintf(&aTX[0], "      は\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 35)  { wsprintf(&aTX[0], "         ゲ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(200, 100, 200)/*色*/); }
		if (g_aSelCounter >= 40)  { wsprintf(&aTX[0], "            ーム\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*色*/); }
		if (g_aSelCounter >= 45)  { wsprintf(&aTX[0], "                  モー\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*色*/); }
		if (g_aSelCounter >= 50)  { wsprintf(&aTX[0], "                        ド\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*色*/); }
		if (g_aSelCounter >= 55)  { wsprintf(&aTX[0], "                           で\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 60)  { wsprintf(&aTX[0], "                              す!!\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }

	}
	else if (g_aSelectMenuMain == 2)
	{
		if (g_aSelCounter >= 20) { wsprintf(&aTX[0], "こ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 25) { wsprintf(&aTX[0], "   れ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 30) { wsprintf(&aTX[0], "      は\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 35) { wsprintf(&aTX[0], "         ゲ\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 40) { wsprintf(&aTX[0], "            ーム\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 45) { wsprintf(&aTX[0], "                  を\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 50) { wsprintf(&aTX[0], "                     終\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 55) { wsprintf(&aTX[0], "                        了\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 60) { wsprintf(&aTX[0], "                           し\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 65) { wsprintf(&aTX[0], "                              ま\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }
		if (g_aSelCounter >= 70) { wsprintf(&aTX[0], "                                 す!!\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*文字列へのポインタ*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*色*/); }

	}

}
