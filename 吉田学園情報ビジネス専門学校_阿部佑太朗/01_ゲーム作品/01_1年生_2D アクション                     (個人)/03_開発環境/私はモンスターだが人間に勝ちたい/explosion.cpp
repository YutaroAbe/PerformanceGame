//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLOSION_TEXTURENAMRE "data/TEXTURE/explosion000.png"
#define EXPLOSION_TEXTURENAMRE1 "data/TEXTURE/explosion001.png"
#define EXPLOSION_TEXTURENAMRE2 "data/TEXTURE/explosion003.png"
#define EXPLOSION_TEXTURENAMRE3 "data/TEXTURE/explosion004.png"
#define EXPLOSION_TEXTURENAMRE4 "data/TEXTURE/explosion005.png"
#define	MAX_EXPLOSION (126)					            //爆発の最大数
#define POS_X         (25)								//ポジション_X
#define POS_Y         (25)								//ポジション_Y
#define MAX_EXP (5)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;      //カラー
	int nType;
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo
	bool bUse;          //使用しているかどうか

}Explosion;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion[MAX_EXP] = {};	    // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	    // 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];				    //爆発のの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();
	int nCntExplosion;

	// 爆発の情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col= D3DXCOLOR(255, 255, 255, 0);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nType = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE, &g_pTextureExplosion[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE1, &g_pTextureExplosion[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE2, &g_pTextureExplosion[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE3, &g_pTextureExplosion[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE4, &g_pTextureExplosion[4]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標設定
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y + 25, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y + 25, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);			//右下
		
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < MAX_EXP; nCntTex++)
	{
		if (g_pTextureExplosion[nCntTex] != NULL)
		{
			g_pTextureExplosion[nCntTex]->Release();
			g_pTextureExplosion[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=============================================================================
// 更新処理 
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	
	VERTEX_2D*pVtx;//頂点情報のポインタ
	 //頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//弾が使用されているか 
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
			{
				//パターンNo,更新
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;//パターンを初期化に戻す 

			//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.0f, 0.0f);				 //右上
				pVtx[1].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 0.0f);       //右上
				pVtx[2].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8 + 0.0f), 1.0f);				 //右上
				pVtx[3].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 1.0f);       //右上

				if (g_aExplosion[nCntExplosion].nPatternAnim <= 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
				}
			}
			pVtx += 4;
		}
	}
		//頂点バッファアンロックする
		g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//弾が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion[g_aExplosion[nCntExplosion].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntExplosion,2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col,int nType)
{
	int nCntExplosion;

	VERTEX_2D*pVtx;								//頂点情報のポインタ

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//弾が使用されていない
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nType = nType;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//弾が使用されている
			//頂点情報(頂点座標の更新)
			pVtx[0].pos = D3DXVECTOR3(-25, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
			pVtx[1].pos = D3DXVECTOR3(25, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
			pVtx[2].pos = D3DXVECTOR3(-25, 0, 0.0f) + g_aExplosion[nCntExplosion].pos;
			pVtx[3].pos = D3DXVECTOR3(25, 0, 0.0f) + g_aExplosion[nCntExplosion].pos;
			if (g_aExplosion[nCntExplosion].nType == 3)
			{
				//頂点情報(頂点座標の更新)
				pVtx[0].pos = D3DXVECTOR3(-20, -100, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[1].pos = D3DXVECTOR3(20, -100, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[2].pos = D3DXVECTOR3(-20, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[3].pos = D3DXVECTOR3(20, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
			}
			if (g_aExplosion[nCntExplosion].nType == 4)
			{
				//頂点情報(頂点座標の更新)
				pVtx[0].pos = D3DXVECTOR3(-25, -150, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[1].pos = D3DXVECTOR3(25, -150, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[2].pos = D3DXVECTOR3(-25, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
				pVtx[3].pos = D3DXVECTOR3(25, -50, 0.0f) + g_aExplosion[nCntExplosion].pos;
			}

			////テクスチャ座標
			//pVtx[0].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.0f, 0.0f);				 //右上
			//pVtx[1].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 0.0f);       //右上
			//pVtx[2].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8 + 0.0f), 1.0f);				 //右上
			//pVtx[3].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 1.0f);       //右上
			break; //使用していない状態にする
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

