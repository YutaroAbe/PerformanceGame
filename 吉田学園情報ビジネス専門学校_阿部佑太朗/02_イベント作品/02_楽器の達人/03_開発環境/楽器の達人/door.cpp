//=============================================================================
//
// 弾の処理 [Door.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "door.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_DOOR		(10000)					// 弾の最大数
#define POS_X (55)								//ポジション_X
#define POS_Y (65)								//ポジション_Y2
#define Door__TEXTURENAMRE "data/TEXTURE/door.png"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;          //使用しているかどうか
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo
	int nLife;			//寿命
	int nType;
}DOOR;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDoor = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor = NULL;	// 頂点バッファへのポインタ
DOOR g_aDoor[MAX_DOOR];						//弾の情報
int nState;
//=============================================================================
// 初期化処理
//=============================================================================
void InitDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntDoor;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		g_aDoor[nCntDoor].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDoor[nCntDoor].bUse = false;
		g_aDoor[nCntDoor].nLife = 0;
		g_aDoor[nCntDoor].nCounterAnim = 0;
		g_aDoor[nCntDoor].nPatternAnim = 0;
		g_aDoor[nCntDoor].nType = 0;
	}
	nState = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Door__TEXTURENAMRE, &g_pTextureDoor);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DOOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDoor,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);//左上
		pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);//右上
		pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);//左上
		pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);//右下
																												  //RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffDoor->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDoor(void)
{
	// テクスチャの開放
	if (g_pTextureDoor != NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffDoor != NULL)
	{
		g_pVtxBuffDoor->Release();
		g_pVtxBuffDoor = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateDoor(void)
{
	VERTEX_2D*pVtx;//頂点情報のポインタ
				   //頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//弾が使用されているか
		{
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);



			Enemy *pEnemy;		//エネミーポインタ
			pEnemy = GetEnemy();
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{//エネミー
				if (pEnemy->bUse == true) //敵が使用されている
				{
					if (pEnemy->state == ENEMYSTATE_NOMAL)
					{
						//[敵との当たり判定]
						if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType ==  0)
						{
							nState = 1;
							pEnemy->bUse = false;

						}
						else	if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType == 1)
						{
							nState = 2;
							pEnemy->bUse = false;

						}
						else	if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType == 2)
						{
							nState = 3;
							pEnemy->bUse = false;

						}

					}
				}
			}

		}
		pVtx += 4;
	}
	//頂点バッファアンロックする
	g_pVtxBuffDoor->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//弾が使用されているか
		{
			switch (nState)
			{
			case 0:
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//	左上
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);			//	右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//	左上
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);			//	右下
				g_aDoor[nCntDoor].nPatternAnim = 0;
				g_aDoor[nCntDoor].nCounterAnim = 0;
				break;
			case 1:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//パターンNo,更新
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//パターンを初期化に戻す

																							  //テクスチャ座標
					pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //右上
					pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
					pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //右上
					pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //右上

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;
			case 2:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//パターンNo,更新
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//パターンを初期化に戻す

																							  //テクスチャ座標
					pVtx[4].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //右上
					pVtx[5].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
					pVtx[6].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //右上
					pVtx[7].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //右上

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;

			case 3:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//パターンNo,更新
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//パターンを初期化に戻す

																							  //テクスチャ座標
					pVtx[8].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //右上
					pVtx[9].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
					pVtx[10].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //右上
					pVtx[11].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //右上

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;
			}
		}

	}
	//頂点バッファアンロックする
	g_pVtxBuffDoor->Unlock();

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntDoor;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffDoor, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureDoor);

	// ポリゴンの描画
	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0 + (4 * nCntDoor),2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetDoor(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
												//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == false)	//弾が使用されていない
		{
			g_aDoor[nCntDoor].pos = pos;
			g_aDoor[nCntDoor].nCounterAnim = 0;
			g_aDoor[nCntDoor].nPatternAnim = 0;
			g_aDoor[nCntDoor].nType = nType;
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			//寿命

			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //右上
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //右上
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //右上

			g_aDoor[nCntDoor].bUse = true;//弾が使用されている


			break;
		}
		pVtx += 4;			//該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffDoor->Unlock();
}
