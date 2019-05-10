//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "bullet.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(10000)						// 弾の最大数
#define POS_X (40)								//ポジション_X
#define POS_Y (30)								//ポジション_Y2
#define BULLET__TEXTURENAMRE "data/TEXTURE/.png"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;   //移動量
	BULLETTYPE type;	//弾の種類
	bool bUse;          //使用しているかどうか
	int nLife;			//寿命
}Bullet;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nLife = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET__TEXTURENAMRE, &g_pTextureBullet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);//左上
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);//右上
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);//左上
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);//右下
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
		{
			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
		{
			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されているか
		{
			//弾を移動させる
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}

			//一定時間経過
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//弾のライフ設定
				g_aBullet[nCntBullet].bUse = false;
			}

			Enemy *pEnemy;		//エネミーポインタ
			pEnemy = GetEnemy();

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)	//プレイヤーの弾
			{
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//エネミー

					if (pEnemy->bUse == true) //敵が使用されている
					{
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{
							//[敵との当たり判定]
							if (pEnemy->pos.x - 40 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 0 )	//プレイヤーの弾
								{
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
								}
							}
							if (pEnemy->pos.x - 40 * 3 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 * 3 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 2)	//プレイヤーの弾
								{
									AddScore(100);
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
								}
							}
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001 )	//プレイヤーの弾
			{
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//エネミー

					if (pEnemy->bUse == true) //敵が使用されている
					{
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{
							//[敵との当たり判定]
							if (pEnemy->pos.x - 40 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40> g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 1 )
								{
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
								}

							}
							if (pEnemy->pos.x - 40 *3 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 * 3 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 2)	//プレイヤーの弾
								{
									AddScore(100);
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
								}
							}
						}
					}
				}
			}
		}
		pVtx += 4;
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//弾が使用されている
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBullet) ,
				2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	 //頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)	//弾が使用されていない
		{
			g_aBullet[nCntBullet].pos = pos;

			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			//寿命
			g_aBullet[nCntBullet].nLife = 6;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;//弾が使用されている

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
			{
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}

			break;
		}
		pVtx += 4;			//該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBullet->Unlock();
}

