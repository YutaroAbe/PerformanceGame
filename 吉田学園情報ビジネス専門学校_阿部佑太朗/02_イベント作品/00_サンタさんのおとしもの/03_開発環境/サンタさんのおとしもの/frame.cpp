//=============================================================================
//
// フレーム処理 [frame.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FRAME_TEXTURE_NAME000  "data/TEXTURE/score_frame.png"    // 読み込むテクスチャファイル名(スコア)
#define FRAME_TEXTURE_NAME001  "data/TEXTURE/score_logo.png"     // 読み込むテクスチャファイル名(スコアロゴ)
#define FRAME_TEXTURE_NAME002  "data/TEXTURE/timer_frame.png"    // 読み込むテクスチャファイル名(タイマー)
#define FRAME_TEXTURE_NAME003  "data/TEXTURE/timer_logo.png"     // 読み込むテクスチャファイル名(タイマーロゴ)
//#define FRAME_TEXTURE_NAME002  "data/TEXTURE/frame_coin.png"     // 読み込むテクスチャファイル名(プレゼント)
#define MAX_FRAME              (4)                               // 必要なフレーム数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureFrame[MAX_FRAME] = {};       // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;   // 頂点バッファへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	// テクスチャの読み込み
	// スコアフレーム
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME000,
		&g_pTextureFrame[0]);

	// スコアロゴ
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME001,
		&g_pTextureFrame[1]);

	// タイマーフレーム
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME002,
		&g_pTextureFrame[2]);

	// タイマーロゴ
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME003,
		&g_pTextureFrame[3]);

	//// プレゼントフレーム
	//D3DXCreateTextureFromFile(pDevice,
	//	FRAME_TEXTURE_NAME002,
	//	&g_pTextureFrame[2]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	//----------------
	// スコアフレーム
	//----------------

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(800, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1270, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(800, 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1270, 150, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// スコアロゴ
	//----------------

	pVtx += 4; // ポインタをずらす

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(900, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1000, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900, 60, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1000, 60, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// タイマーフレーム
	//----------------

	pVtx += 4; // ポインタをずらす

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(530, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(530, 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740, 150, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// タイマーロゴ
	//----------------

	pVtx += 4; // ポインタをずらす

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(593, 16, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(673, 16, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(593, 76, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(673, 76, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////----------------
	//// プレゼントフレーム
	////----------------

	//pVtx += 4; // ポインタをずらす

    //// 頂点座標
	//pVtx[0].pos = D3DXVECTOR3(240, 0, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(370, 0, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(240, 120, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(370, 120, 0.0f);

	//// 頂点テクスチャ
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// 頂点カラー
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

	//// テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffFrame->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitFrame(void)
{
	// テクスチャの破棄
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{// 表示するフレーム数だけ繰り返し
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateFrame(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{// 表示するフレーム数だけ繰り返し
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureFrame[nCntFrame]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntFrame * 4,
			2);
	}
}