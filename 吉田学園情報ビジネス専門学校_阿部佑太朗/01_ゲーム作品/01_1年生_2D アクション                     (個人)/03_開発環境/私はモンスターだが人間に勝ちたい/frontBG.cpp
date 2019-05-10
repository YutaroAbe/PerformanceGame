//=============================================================================
//
// フロントBG処理 [FrontBG.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "frontBG.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_FrontBG		(4)								// 敵の種類FrontBG
#define FrontBG_01 "data/TEXTURE/front000.png"
#define FrontBG_02 "data/TEXTURE/front001.png"
#define FrontBG_03 "data/TEXTURE/.png"
#define FrontBG_04 "data/TEXTURE/.png"
#define FrontBG_PMAX (15)											//敵の大きさ
#define FrontBG_PMAY (35)											//敵の大きさ
#define	MAX_FrontBG	(128)	// 敵の最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFrontBG[MAX_TYPE_FrontBG] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrontBG = NULL;					// 頂点バッファへのポインタ
FrontBG g_aFrontBG[MAX_FrontBG];										//敵の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitFrontBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFrontBG;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		g_aFrontBG[nCntFrontBG].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aFrontBG[nCntFrontBG].nType = 0;
		g_aFrontBG[nCntFrontBG].fHeight = 0;
		g_aFrontBG[nCntFrontBG].fWindth = 0;
		g_aFrontBG[nCntFrontBG].bUse = false;
		g_aFrontBG[nCntFrontBG].nCounterState = 0;
	}
	
	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, FrontBG_01, &g_apTextureFrontBG[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, FrontBG_02, &g_apTextureFrontBG[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, FrontBG_03, &g_apTextureFrontBG[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, FrontBG_04, &g_apTextureFrontBG[3]);
	
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FrontBG,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFrontBG,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		//ポジション
		pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		
		//RHW
		pVtx[nCntFrontBG * 4].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 1].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 2].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 3].rhw = 1.0f;
		//カラー
		pVtx[nCntFrontBG * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[nCntFrontBG * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[nCntFrontBG * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[nCntFrontBG * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[nCntFrontBG * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffFrontBG->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFrontBG(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_FrontBG; nCntTex++)
	{
		if (g_apTextureFrontBG[nCntTex] != NULL)
		{
			g_apTextureFrontBG[nCntTex]->Release();
			g_apTextureFrontBG[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFrontBG != NULL)
	{
		g_pVtxBuffFrontBG->Release();
		g_pVtxBuffFrontBG = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFrontBG(void)
{
	VERTEX_2D*pVtx = NULL;	

	PLAYER *pPlyer;
	pPlyer = GetPlayer();
		
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
			g_aFrontBG[nCntFrontBG].pos.x -= pPlyer->move.x;
		
			if (g_aFrontBG[nCntFrontBG].bUse == true)//エネミーが使用されているか 
			{//ポジション
				pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);

			}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffFrontBG->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFrontBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffFrontBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		if (g_aFrontBG[nCntFrontBG].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureFrontBG[g_aFrontBG[nCntFrontBG].nType]);
			//ポリゴンの描画
			if (g_aFrontBG[nCntFrontBG].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntFrontBG * 4,2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetFrontBG(int nType,D3DXVECTOR3 pos ,float fHeight, float fWindth)
{
	int nCntFrontBG;
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		if (g_aFrontBG[nCntFrontBG].bUse == false)		//敵が使用されていない
		{
			g_aFrontBG[nCntFrontBG].pos = pos;
			g_aFrontBG[nCntFrontBG].nType = nType;
			g_aFrontBG[nCntFrontBG].fHeight = fHeight;
			g_aFrontBG[nCntFrontBG].fWindth = fWindth;
			g_aFrontBG[nCntFrontBG].bUse = true;			//敵が使用されている

			//ポジション
			pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);

			break;
		}

	}
	//頂点バッファアンロックする
	g_pVtxBuffFrontBG->Unlock();
}
//=============================================================================
// 敵の取得
//=============================================================================
FrontBG *GetFrontBG(void)
{
	return &g_aFrontBG[0];
}