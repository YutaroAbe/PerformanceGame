//=============================================================================
//
// カラスの処理 [crow.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "crow.h"
#include "bullet.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_CROW		"data/TEXTURE/crow.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexCrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCrow = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCrow = NULL;	// 頂点バッファへのポインタ
Crow					g_Crow;		            // カラスの情報
float                   g_Tex;                  // テクスチャU座標を切り替える

//=============================================================================
// 初期化処理
//=============================================================================
void InitCrow(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_Crow.pos = D3DXVECTOR3(100.0f, 400.0f, 0.0f);   // 位置の初期化
	g_Crow.move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);      // 移動量を初期化
	g_Crow.nCounterAnim = 0;                          // アニメーションカウンターを初期化
	g_Crow.nPatternAnim = 0;                          // パターンNo.を初期化
	g_Crow.itemtype = 0;                              // アイテムのタイプを初期化
	g_Crow.fWidth = 35.0f;                            // 幅を初期化
	g_Crow.fHeight = 35.0f;                           // 高さを初期化
	g_Tex = 0.5f;
	

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CROW, &g_pTextureCrow);

	// 頂点情報の作成
	MakeVertexCrow(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCrow(void)
{
	// テクスチャの開放
	if (g_pTextureCrow != NULL)
	{
		g_pTextureCrow->Release();
		g_pTextureCrow = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffCrow != NULL)
	{
		g_pVtxBuffCrow->Release();
		g_pVtxBuffCrow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCrow(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCrow->Lock(0, 0, (void**)&pVtx, 0);

	g_Crow.pos += g_Crow.move;  // 位置更新

	if (g_Crow.pos.x + g_Crow.fWidth >= SCREEN_WIDTH)
	{
		g_Crow.move.x *= -1;   // 移動方向反転
		g_Tex = 0.0f;          // U座標移動
	}
	if (g_Crow.pos.x - g_Crow.fWidth <= 0.0f)
	{
		g_Crow.move.x *= -1;   // 移動方向反転
		g_Tex = 0.5f;          // U座標移動
	}

	if (CollisionBullet2(&g_Crow.pos, g_Crow.fWidth, g_Crow.fHeight,&g_Crow.nIdxBullet) == true)
	{
		DeleteBullet(*g_Crow.nIdxBullet);
		PlaySound(SOUND_LABEL_SE_KARASU);
	}

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(-g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[1].pos = D3DXVECTOR3(g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[2].pos = D3DXVECTOR3(-g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[3].pos = D3DXVECTOR3(g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;

	pVtx[0].tex = D3DXVECTOR2(g_Tex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_Tex + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_Tex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_Tex + 0.5f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffCrow->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCrow, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCrow);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexCrow(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCrow,
		NULL);

	// 頂点バッファの情報を設定
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCrow->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[1].pos = D3DXVECTOR3(g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[2].pos = D3DXVECTOR3(-g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[3].pos = D3DXVECTOR3(g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    // 頂点バッファをアンロック
	g_pVtxBuffCrow->Unlock();
}
