//=============================================================================
//
// セレクトの処理 [score.cpp]
// Author :　YUTARO　ABE
//
//=============================================================================
#include "serect.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "ranking.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SERECT_TEXTURE_NAME "data/TEXTURE/selecttitle1.jpg"			// 読み込むテクスチャファイル名
#define SERECT_TEXTURE_NAME1 "data/TEXTURE/tutorial.jpg"		// 読み込むテクスチャファイル名
#define SERECT_TEXTURE_NAME2 "data/TEXTURE/game111.jpg"		    // 読み込むテクスチャファイル名
#define SERECT_TEXTURE_NAME3 "data/TEXTURE/ranking.jpg" 		// 読み込むテクスチャファイル名

#define TUTORIAL_POS_X        (0)                               // 背景の左上Ｘ座標
#define TUTORIAL_POS_Y        (0)                               // 背景の左上Ｙ座標
#define TUTORIAL_WIDTH        (SCREEN_WIDTH)                    // 背景の幅
#define TUTORIAL_HEIGHT       (SCREEN_HEIGHT)                   // 背景の高さ
#define MAX_TEX					(4)								// 選択数
#define SERECT_POS_X			(0)								// セレクトのX座標(左上)
#define SERECT_POS_Y			(0)								// セレクトのY座標(右上)
#define SERECT_WIDTH		    (SCREEN_WIDTH)					// ウインドウの横
#define SERECT_HEIGHT			(SCREEN_HEIGHT)					// ウインドウの高さ

#define SERECT_TEXTURE_U		(1.0f)
#define SERECT_TEXTURE_V		(1.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureSERECT[MAX_TEX] = {};			   // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSERECT = NULL;               // 頂点バッファへのポインタ
SERECT g_Serect;											   // ポスの情報
STETAS g_Stetas;							                   // ステータス

															   //=============================================================================
															   // 初期化処理
															   //=============================================================================
void InitSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_Serect.pos = D3DXVECTOR3((SERECT_POS_X + SERECT_WIDTH) / 2, (SERECT_POS_Y + SERECT_HEIGHT) / 2, 0.0f);
	g_Serect.nCounrtState = 0;
	g_Serect.SerectCor = 1.0f;
	g_Stetas = NORMAL;

	float posSerect = (SERECT_HEIGHT / 2 - 271.0f);						//セレクトの座

																		// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME,
		&g_pTextureSERECT[0]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME1,
		&g_pTextureSERECT[1]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME2,
		&g_pTextureSERECT[2]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME3,
		&g_pTextureSERECT[3]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSERECT,
		NULL);

	VERTEX_2D *pVtxSERECT;   // 頂点情報へのポインタ

							 // 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	pVtxSERECT[0].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_POS_Y, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_POS_Y, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_HEIGHT, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_HEIGHT, 0.0f);

	// 頂点テクスチャ
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// 頂点カラー
	pVtxSERECT[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSERECT->Unlock();

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	pVtxSERECT += 4;

	//
	//	チュートリアル
	//
	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// 頂点テクスチャ
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// 頂点カラー
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// テクスチャ座標の設定
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSERECT->Unlock();

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	//
	//	ゲーム
	//
	pVtxSERECT += 8;
	posSerect += 155;

	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// 頂点テクスチャ
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// 頂点カラー
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// テクスチャ座標の設定
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSERECT->Unlock();


	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	//
	//	ランキング
	//
	pVtxSERECT += 12;
	posSerect += 155;

	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// 頂点テクスチャ
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// 頂点カラー
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// テクスチャ座標の設定
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSERECT->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSerect(void)
{
	for (int nCnt = 0; nCnt<4; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTextureSERECT[nCnt] != NULL)
		{

			g_pTextureSERECT[nCnt]->Release();
			g_pTextureSERECT[nCnt] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffSERECT != NULL)
	{
		g_pVtxBuffSERECT->Release();
		g_pVtxBuffSERECT = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateSerect(void)
{
	VERTEX_2D *pVtxSERECT;				    // 頂点情報へのポインタ

	FADE p_fade = *GetFade();				// フェード状態
											// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	if (GetKeyboardTrigger(DIK_W) == true)
	{

		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 3) % 3;
		g_Serect.SerectCor = 1.0f;
	}

	if (GetKeyboardTrigger(DIK_S) == true)
	{
		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 1) % 3;
		g_Serect.SerectCor = 1.0f;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 2) % 3;
		g_Serect.SerectCor = 1.0f;
	}
	//頂点カラー設定
	pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffSERECT->Unlock();
	if (p_fade != FADE_OUT)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Serect.nCounrtState == 0)
			{
				SetFade(MODE_TUTORIAL);
			}
			if (g_Serect.nCounrtState == 1)
			{
				SetFade(MODE_GAME);
			}
			if (g_Serect.nCounrtState == 2)
			{
				SetFade(MODE_RANKING);
			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSERECT, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//	{// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSERECT[0]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[2]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[3]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 3 * 4,
		2);
}
//====================================
//セレクトの取得
//====================================
STETAS *GetSel(void)
{
	return &g_Stetas;
}