//=============================================================================
//
// ブロック設置の処理 [blockeffect.cpp]
// Author :長山拓実
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BLOCKEFFECT				(128)													// 弾の最大数
#define BLOCKEFFECT_TEXTURE_NAME	"data\\TEXTURE\\explosion000.png"						// 読み込むテクスチャ名
#define BLOCKEFFECT_ANIM_X			((0.2f * g_aBlockEffect[nCntBlockEffect].nPatternAnim))	// 読み込むテクスチャのパターン
#define BLOCKEFFECT_ANIM_Y			((0.5f * g_aBlockEffect[nCntBlockEffect].nPatternAnim))	// 読み込むテクスチャのパターン
#define BLOCKEFFECT_SIZE			(40)													// 読み込むテクスチャの大きさ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXCOLOR col;					// 色
	D3DXVECTOR3 move;				// 移動量
	int nCounterAnim;				// アニメーションカウンター
	int nPatternAnim;				// アニメーションパターン
	bool bUse;						// 使用しているかどうか
} BlockEffect;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlockEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlockEffect = NULL;	// 頂点バッファへのポインタ
BlockEffect g_aBlockEffect[MAX_BLOCKEFFECT];			// 使用しているかどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlockEffect;

	// デバイスの取得
	pDevice = GetDevice();

	// 爆発の初期化
	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		g_aBlockEffect[nCntBlockEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlockEffect[nCntBlockEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBlockEffect[nCntBlockEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlockEffect[nCntBlockEffect].nCounterAnim = 0;
		g_aBlockEffect[nCntBlockEffect].nPatternAnim = 0;
		g_aBlockEffect[nCntBlockEffect].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BLOCKEFFECT_TEXTURE_NAME, &g_pTextureBlockEffect);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCKEFFECT,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlockEffect,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

		// rhwの設定
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
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBlockEffect->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureBlockEffect != NULL)
	{
		g_pTextureBlockEffect->Release();
		g_pTextureBlockEffect = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBlockEffect != NULL)
	{
		g_pVtxBuffBlockEffect->Release();
		g_pVtxBuffBlockEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntBlockEffect;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		g_aBlockEffect[nCntBlockEffect].nCounterAnim++;

		if ((g_aBlockEffect[nCntBlockEffect].nCounterAnim % 5) == 0)
		{
			if (g_aBlockEffect[nCntBlockEffect].bUse == true)	// 弾が使用されている
			{
				// パターンNo.を更新
				g_aBlockEffect[nCntBlockEffect].nPatternAnim = (g_aBlockEffect[nCntBlockEffect].nPatternAnim + 1) % 10;

				// テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
				pVtx[1].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
				pVtx[2].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);
				pVtx[3].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);

				if (g_aBlockEffect[nCntBlockEffect].nPatternAnim == 0)
				{
					g_aBlockEffect[nCntBlockEffect].bUse = false;	// 使用していない状態にする
				}
			}
		}

		g_aBlockEffect[nCntBlockEffect].pos.y += g_aBlockEffect[nCntBlockEffect].move.y;

		// 頂点座標の更新
		pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

		pVtx += 4;	// 該当の位置まで進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBlockEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlockEffect;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlockEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlockEffect);

	// ポリゴンの描画
	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		if (g_aBlockEffect[nCntBlockEffect].bUse == true)	// 弾が使用されている
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBlockEffect,
				2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntBlockEffect;

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		if (g_aBlockEffect[nCntBlockEffect].bUse == false)
		{
			VERTEX_2D *pVtx;	// 頂点情報へのポインタ

			// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBlockEffect * 4);	// 該当の位置まで進める

			g_aBlockEffect[nCntBlockEffect].pos = pos;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

			g_aBlockEffect[nCntBlockEffect].col = col;

			// 頂点カラー
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aBlockEffect[nCntBlockEffect].nPatternAnim = 0;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
			pVtx[1].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
			pVtx[2].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);
			pVtx[3].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);

			// 頂点バッファをアンロック
			g_pVtxBuffBlockEffect->Unlock();

			g_aBlockEffect[nCntBlockEffect].nCounterAnim = 0;
			g_aBlockEffect[nCntBlockEffect].bUse = true;	// 使用している状態
			break;
		}
	}
}