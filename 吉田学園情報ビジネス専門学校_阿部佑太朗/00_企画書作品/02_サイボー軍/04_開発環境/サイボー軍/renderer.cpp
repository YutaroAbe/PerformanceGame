//=============================================================================
//
// メイン処理 [main.cpp]
// Author :
//
//=============================================================================
#include "renderer.h"
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "enemy.h"
#include "number.h"
#include "block.h"
#include "input.h"
#include "manager.h"
#include "fade.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;			// Direct3Dオブジェクト
	m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
	m_pFont = NULL;			// フォントへのポインタ
	m_pDebugFont = NULL;
	m_pManager = {};
}

//=============================================================================
//デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = TRUE;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

																	// デバイスの生成
																	// ディスプレイアダプタを表すためのデバイスを作成
																	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定

																			// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	int nMode = CManager::GetMode();


		// 情報表示用フォントの生成
		D3DXCreateFont(m_pD3DDevice, 33, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "monospace", &m_pFont);


	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pDebugFont);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// 情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	// デバッグ情報表示用フォントの破棄
	if (m_pDebugFont != NULL)
	{
		m_pDebugFont->Release();
		m_pDebugFont = NULL;
	}

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	CScene::UpdateAll();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// ポリゴンの描画処理
		CScene::DrawAll();

		CFade *pFade = CManager::GetFade();

		pFade->Draw();

		if (pFade->m_fade == pFade->FADE_IN || pFade->m_fade == pFade->FADE_NONE)
		{
			int nMode = CManager::GetMode();
			int nStageMode = CGame::GetStageState();

			if (nMode == CManager::MODE_SELECT)
			{
				DrawSelect();
			}
			if (nMode == CManager::MODE_GAME&& nStageMode == CGame::SETSTEGEMODE_000)
			{
				DrawGameTutorial();
			}
			if (nMode == CManager::MODE_STAGESELECT)
			{
				DrawStageSelect();
			}
		}
#ifdef _DEBUG
		// FPS表示
		DrawFPS();
		DrawPosition();

#endif
		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	nCountFPS = GetFPS();

	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_pDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawPosition(void)
{
	RECT rect = { 0, 15, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	D3DXVECTOR3 pos;										//	プレイヤーの現在の位置
	D3DXVECTOR3 move;										//	プレイヤーの現在の動き
	int nLife;												//	プレイヤーの体力
	int nNUW_TEX;											//	プレイヤーのテクスチャの番号
	int nNUMALL;											//	ポリゴンの数
	int nNUMENEMY;											//	敵の数
	int nNumNumber;											//	ナンバーのポリゴンの数
	int nNumBlock;											//	ブロックの数
	int nNuwMode;

	pos = CPlayer::GetPosition();							//	プレイヤーの現在の位置取得
	move = CPlayer::GetMove();								//	プレイヤーの現在の動き取得
	nLife = CPlayer::GetLife();								//	プレイヤーの体力取得
	nNUW_TEX = CPlayer::GetTexNumber();						//	プレイヤーのテクスチャの番号取得
	nNUMALL = CScene::GetNumALL();							//	ポリゴンの数取得
	nNUMENEMY = CEnemy::GetNUMENEMY();						//	敵の数取得
	nNumNumber = CNumber::GetNumNumber();					//	ナンバーのポリゴンの数取得
	nNumBlock = CBlock::GetNumBlock();						//	ブロックの数取得
	nNuwMode = CManager::GetMode();

	wsprintf(str, "現在のモード(%d) 0:タイトル 1：セレクト 2:ステージセレクト　3：ゲーム\n\n\n\nPOS:(%d,%d,%d)\nMOVE:(%d,%d,%d)\n現在のTEX(%d):0=右動く/1＝左動く\nLIFE:(%d)\nポリゴン総数(%d)\n敵の数(%d)\nブロックの数(%d)\n数字の数(%d)",
		(int)nNuwMode,(int)pos.x, (int)pos.y, (int)pos.z,(int)move.x, (int)move.y, (int)move.z, nNUW_TEX, nLife, nNumNumber+ nNUMALL, nNUMENEMY,nNumBlock, nNumNumber);

	// テキスト描画
	m_pDebugFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif

//=============================================================================
// セレクトの説明欄文字列
//=============================================================================
void CRenderer::DrawSelect(void)
{
	RECT rect = { 220, 510, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nSelectNum = CSelect::GetNumSelect();
	int nSelectCounter = CSelect::GetSelWordCounter();

	if (nSelectNum == 1)
	{//	ゲームモード
		if (nSelectCounter >= 10) { wsprintf(str, "本\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));}
		if (nSelectCounter >= 15) { wsprintf(str, "　 編\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));}
		if (nSelectCounter >= 20) { wsprintf(str, "　  　の\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 25) { wsprintf(str, "　  　　 ゲ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 30) { wsprintf(str, "　  　　 　 ー\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 35) { wsprintf(str, "　  　　 　 　 ム\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 40) { wsprintf(str, "　  　　 　 　 　 モ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 45) { wsprintf(str, "　  　　 　 　 　 　 ー\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 50) { wsprintf(str, "　  　　 　 　 　 　 　 ド\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　 　　  で\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 60) { wsprintf(str, "　  　　 　 　 　 　 　　  　 す\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 65) { wsprintf(str, "　  　　 　 　 　 　 　　  　  　！！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
	}
	else if (nSelectNum == 2)
	{//	クレジットモード
		if (nSelectCounter >= 10) { wsprintf(str, "著\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 15) { wsprintf(str, "　 作\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 20) { wsprintf(str, "　  　物\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 25) { wsprintf(str, "　  　　 の\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 30) { wsprintf(str, "　  　　 　 詳\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 35) { wsprintf(str, "　  　　 　 　 細\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 40) { wsprintf(str, "　  　　 　 　 　 が\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 45) { wsprintf(str, "　  　　 　 　 　 　 書\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 50) { wsprintf(str, "　  　　 　 　 　 　 　 か\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　 　　  れ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 60) { wsprintf(str, "　  　　 　 　 　 　 　　  　 て\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 65) { wsprintf(str, "　  　　 　 　 　 　 　　  　  　い\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 70) { wsprintf(str, "　  　　 　 　 　 　 　　  　  　　 ま\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 75) { wsprintf(str, "　  　　 　 　 　 　 　　  　  　　 　 す\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 80) { wsprintf(str, "　  　　 　 　 　 　 　　  　  　　 　  　！！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
	}
	else if (nSelectNum == 3)
	{//	ゲームの終了
		if (nSelectCounter >= 10) { wsprintf(str, "ゲ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 15) { wsprintf(str, "　 ー\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 20) { wsprintf(str, "　  　ム\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 25) { wsprintf(str, "　  　　 を\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 30) { wsprintf(str, "　  　　 　 終\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 35) { wsprintf(str, "　  　　 　 　 了\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 40) { wsprintf(str, "　  　　 　 　 　 し\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 45) { wsprintf(str, "　  　　 　 　 　 　 ま\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 50) { wsprintf(str, "　  　　 　 　 　 　 　 す\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nSelectCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　 　　  ！！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
	}


	rect = { 220, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
	wsprintf(str, "[W S]選択　 / [ENTER]　決定 \n[十字キー]選択　/　[Aボタン]　決定\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//=============================================================================
// ゲームのチュートリアルの説明欄文字列
//=============================================================================
void  CRenderer::DrawGameTutorial(void)
{
	RECT rect = { 180, 210, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nSelectNum = CMissionMessage::GetNumText();
	int nGameCounter = CMissionMessage::GetGameText();
	if (nSelectNum == 0)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "や\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 15) { wsprintf(str, "　 あ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 20) { wsprintf(str, "　  　！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 25) { wsprintf(str, "　  　　 ！\n\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 30) { wsprintf(str, "　  　　 　 は\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 35) { wsprintf(str, "　  　　 　 　 じ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 40) { wsprintf(str, "　  　　 　 　 　 め\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 45) { wsprintf(str, "　  　　 　 　 　 　 ま\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 50) { wsprintf(str, "　  　　 　 　 　 　 　 し\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　 　　 て"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 60) { wsprintf(str, "　  　　 　 　 　 　 　　	   ！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 75) { wsprintf(str, "\n\n                          [Mキー][Xボタン]...NEXT\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0, 0)); }
	}
	else if (nSelectNum == 1)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "私\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 15) { wsprintf(str, "　 は\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 20) { wsprintf(str, "　  　人\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 25) { wsprintf(str, "　  　　 間\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 30) { wsprintf(str, "　  　　 　 の\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 35) { wsprintf(str, "　  　　 　 　 体\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 40) { wsprintf(str, "　  　　 　 　 　 を\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 45) { wsprintf(str, "　  　　 　 　 　 　 監\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 50) { wsprintf(str, "　  　　 　 　 　 　 　 視\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　 　　  し"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 60) { wsprintf(str, "　  　　 　 　 　 　 　　	    て\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 65) { wsprintf(str, "　  　　 　 　 　 　 　　	       い\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 70) { wsprintf(str, "　  　　 　 　 　 　 　　	          る\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 75) { wsprintf(str, "　  　　 　 　 　 　 　　	             者\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 80) { wsprintf(str, "　  　　 　 　 　 　 　　	                だ！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 95) { wsprintf(str, "\n\n                          [Mキー][Xボタン]...NEXT\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0, 0)); }
	}
	else if (nSelectNum == 2)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "君\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 15) { wsprintf(str, "　 に\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 20) { wsprintf(str, "　  　は\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 25) { wsprintf(str, "　  　　 こ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 30) { wsprintf(str, "　  　　 　の\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 35) { wsprintf(str, "　  　　 　   体\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 40) { wsprintf(str, "　  　　 　 　   を\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 45) { wsprintf(str, "　  　　 　 　 　   守\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 50) { wsprintf(str, "　  　　 　 　 　      る\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　    　為\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 60) { wsprintf(str, "\n ウ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
		if (nGameCounter >= 65) { wsprintf(str, "\n    イ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
		if (nGameCounter >= 70) { wsprintf(str, "\n       ルス\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
		if (nGameCounter >= 75) { wsprintf(str, "\n              と\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 80) { wsprintf(str, "\n                 戦\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 85) { wsprintf(str, "\n                    って\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 90) { wsprintf(str, "\n                         も\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 95) { wsprintf(str, " \n                            ら\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 100) { wsprintf(str, "\n                               う！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 115) { wsprintf(str, "\n\n                          [Mキー][Xボタン]...NEXT\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0, 0)); }
	}
	else if (nSelectNum == 3)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "そ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 15) { wsprintf(str, "　 の\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 20) { wsprintf(str, "　  　為\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 25) { wsprintf(str, "　  　　 に\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 30) { wsprintf(str, "　  　　 　 い\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 35) { wsprintf(str, "　  　　 　    く\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 40) { wsprintf(str, "　  　　 　 　   つ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 45) { wsprintf(str, "　  　　 　 　 　   か\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 50) { wsprintf(str, "　  　　 　 　 　      戦 \n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 55) { wsprintf(str, "　  　　 　 　 　 　    　闘\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 60) { wsprintf(str, "　  　　 　 　 　 　   　    に\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 65) { wsprintf(str, "　  　　 　 　 　 　          　必\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 70) { wsprintf(str, "　  　　 　 　 　 　             　要\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 75) { wsprintf(str, "　  　　 　 　 　 　                　な\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 80) { wsprintf(str, "\n       操\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 0)); }
		if (nGameCounter >= 85) { wsprintf(str, "\n          作\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 0)); }
		if (nGameCounter >= 90) { wsprintf(str, "\n             方\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 0)); }
		if (nGameCounter >= 95) { wsprintf(str, "\n                法\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 0)); }
		if (nGameCounter >= 100) { wsprintf(str, "\n                   を\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 105) { wsprintf(str, "\n                      教\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 110) { wsprintf(str, "\n                         え\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 115) { wsprintf(str, " \n                            る\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 120) { wsprintf(str, "\n                               よ!\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
		if (nGameCounter >= 135) { wsprintf(str, "\n\n                          [Mキー][Xボタン]...NEXT\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0, 0)); }
	}
	else if (nSelectNum == 4)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "[Aボタン]　ジャンプ　：　[Bボタン]　攻撃\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
		if (nGameCounter >= 30) { wsprintf(str, "\n[十字キー]　移動　  :  [START]　ポーズ\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
		if (nGameCounter >= 35) { wsprintf(str, "\n\n                          [Mキー][Xボタン]...NEXT\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); }
	}
	else if (nSelectNum >= 5)
	{//	ゲームモード
		if (nGameCounter >= 10) { wsprintf(str, "準備次第[Nキー][Yボタン]ステージ選択\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0)); }
	}

}
//=============================================================================
// ステージセレクトの説明欄文字列
//=============================================================================
void CRenderer::DrawStageSelect(void)
{
	RECT rect = { 220, 510, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	int nSelectNum = CStageSelect::GetNumSelect();

	if (nSelectNum == 1)
	{
		wsprintf(str, "チュートリアルです！！\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
	else if (nSelectNum == 2)
	{
		wsprintf(str, "ステージ１へ移行します\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
	else if (nSelectNum == 3)
	{
		wsprintf(str, "ステージ２へ移行します\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
	else if (nSelectNum == 4)
	{
		wsprintf(str, "セレクト画面に移行します\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
	rect = { 220, 600, SCREEN_WIDTH, SCREEN_HEIGHT };
	wsprintf(str, "[A D]選択　/　[ENTER]　決定 \n[十字キー]選択　/　[Aボタン]　決定\n"); m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

