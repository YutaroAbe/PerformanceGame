//=============================================================================
//
// アイテムの処理 [item.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "item.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ITEM		(5)								// 敵の種類item
#define ITEM_01 "data/TEXTURE/coin000.png"
#define ITEM_02 "data/TEXTURE/HP101.png"
#define ITEM_03 "data/TEXTURE/HP101.png"
#define ITEM_04 "data/TEXTURE/item003.png"
#define ITEM_05 "data/TEXTURE/HP101.png"
#define ITEM_PMAX (25)											//敵の大きさ
#define	MAX_ITEM	(50)	// 敵の最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// 頂点バッファへのポインタ
Item g_aitem[MAX_ITEM];										//敵の情報
int g_CoinSe;
int g_NamTime;

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntitem;

	// デバイスの取得
	pDevice = GetDevice();

	//g_nCounterGAME++;

	// 敵の情報の初期化
	for(int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		g_aitem[nCntitem].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aitem[nCntitem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aitem[nCntitem].nType = 0;
		g_aitem[nCntitem].fHeight = 0;
		g_aitem[nCntitem].fWindth = 0;
		g_aitem[nCntitem].bUse = false;
		g_aitem[nCntitem].nCounterAnim = 0;
		g_aitem[nCntitem].nPatternAnim = 0;
		g_aitem[nCntitem].nCounterState = 0;
		g_aitem[nCntitem].nNumItem = 0;
		//g_aitem[nCntitem].CountLife = 0;

		g_CoinSe = 0;
	}
	g_NamTime = 0;

	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ITEM_01, &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_02, &g_apTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_03, &g_apTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_04, &g_apTextureItem[3]);
	D3DXCreateTextureFromFile(pDevice, ITEM_05, &g_apTextureItem[4]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffItem,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		//ポジション
		pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		/*pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, 0.0f);
*/
		//RHW
		pVtx[nCntitem * 4].rhw = 1.0f;
		pVtx[nCntitem * 4 + 1].rhw = 1.0f;
		pVtx[nCntitem * 4 + 2].rhw = 1.0f;
		pVtx[nCntitem * 4 + 3].rhw = 1.0f;
		//カラー
		pVtx[nCntitem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[nCntitem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[nCntitem * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[nCntitem * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[nCntitem * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

		//pVtx += 4;	//頂点ポインタを4つ進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{
		if (g_apTextureItem[nCntTex] != NULL)
		{
			g_apTextureItem[nCntTex]->Release();
			g_apTextureItem[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D*pVtx;

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		g_aitem[nCntitem].pos.x -= pPlyer->move.x;

		if (g_aitem[nCntitem].bUse == true)//エネミーが使用されているか
		{
			if (g_aitem[nCntitem].nType == 0)
			{
				g_aitem[nCntitem].nCounterAnim++;
				if ((g_aitem[nCntitem].nCounterAnim % 15) == 0)
				{
					//パターンNo,更新
					g_aitem[nCntitem].nPatternAnim = (g_aitem[nCntitem].nPatternAnim + 1) % 4;				//パターンを初期化に戻す
				}
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4), 0.0f);				 //右上
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4), 1.0f);				 //右上
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4) + 0.25f, 1.0f);       //右上
			}

			pVtx[0].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		if (g_aitem[nCntitem].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureItem[g_aitem[nCntitem].nType]);
			//ポリゴンの描画
			if (g_aitem[nCntitem].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntitem * 4,2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetItem(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntitem;
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		if (g_aitem[nCntitem].bUse == false)		//敵が使用されていない
		{
			g_aitem[nCntitem].pos = pos;
			g_aitem[nCntitem].nType = nType;
			g_aitem[nCntitem].move = move;
			g_aitem[nCntitem].fHeight = 0;
			g_aitem[nCntitem].fWindth = 0;
			g_aitem[nCntitem].bUse = true;			//敵が使用されている
			g_aitem[nCntitem].nCounterAnim = 0;
			g_aitem[nCntitem].nPatternAnim = 0;

			//ポジション
			pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			break;
		}

	}
	//頂点バッファアンロックする
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// 敵の取得
//=============================================================================
Item *Getitem(void)
{
	return &g_aitem[0];
}
//=============================================================================
//プレイヤーとアイテムの判定処理
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, float *fWindth, float *fHeight)
{
	for (int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++, g_NamTime++)
	{
		if (g_aitem[nCntitem].bUse == true)
		{
			g_NamTime--;
			if (pPos->x - *fWindth <= g_aitem[nCntitem].pos.x &&
				pPos->x + *fWindth  >= g_aitem[nCntitem].pos.x &&
				pPos->y - *fHeight <= g_aitem[nCntitem].pos.y &&
				pPos->y  >= g_aitem[nCntitem].pos.y)
			{//アイテムの判定

					g_aitem[nCntitem].bUse = false;					//プレイヤーがアイテムに当たったら消す
					if (g_aitem[nCntitem].bUse == false)
					{
						if (g_aitem[nCntitem].nType == 0)
						{

							switch (rand() % 4)
							{											//効果音
							case 0:
								PlaySound(SOUND_LABEL_SE_COIN000);
								break;
							case 1:
								PlaySound(SOUND_LABEL_SE_COIN001);
								break;
							case 2:
								PlaySound(SOUND_LABEL_SE_COIN002);
								break;
							case 3:
								PlaySound(SOUND_LABEL_SE_COIN003);
								break;
							}
							g_CoinSe += 1;
							if ((g_CoinSe >= 4))
							{
								g_CoinSe = 0;
							}
							//コインのポイント
							AddScore(100);								//スコア加算
						//	SetExplosion(g_aitem[nCntitem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
							if (g_NamTime <= 0)
							{
								AddScore(10000);								//スコア加算
							}
						}

						if (g_aitem[nCntitem].nType == 4)
						{
							PLAYER *pPlyer;
							pPlyer = GetPlayer();
							if (pPlyer->nLife <= 9)
							{
								PlaySound(SOUND_LABEL_SE_KAIHUKU);
								pPlyer->nLife = 10;
							}
						}
						if (g_aitem[nCntitem].nType == 2)
						{
							PLAYER *pPlyer;
							pPlyer = GetPlayer();
							if (pPlyer->nLife <= 9)
							{
								PlaySound(SOUND_LABEL_SE_KAIHUKU);
								pPlyer->nLife += 1;
							}
						}
				}
			}
		}
	}
}