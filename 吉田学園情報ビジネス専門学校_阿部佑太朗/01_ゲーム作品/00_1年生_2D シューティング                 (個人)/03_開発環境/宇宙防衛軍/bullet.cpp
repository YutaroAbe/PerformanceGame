//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================

//*****************************************************************************
//	インクルードファイル
//*****************************************************************************
#include "bullet.h"		//	弾
#include "main.h"		//	メイン
#include "player.h"		//	プレイヤー
#include "input.h"		//	入力
#include "explosion.h"	//	爆発
#include "enemy.h"		//	敵
#include "sideenemy.h"	//	サイド側の敵
#include "tbossenemy.h"	//	ボス
#include "effect.h"		//	エフェクト

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET		(10000)								//	弾の最大数
#define POS_X			(5)									//	ポジション_X
#define POS_Y			(5)									//	ポジション_Y2
#define BULLET_TEXTURENAMRE "data/TEXTURE/bullet000.png"	//	テクスチャの名前

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//	位置
	D3DXVECTOR3 move;   //	移動量
	BULLETTYPE type;	//	弾の種類
	bool bUse;          //	使用しているかどうか
	int nLife;			//	寿命

}Bullet;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//	テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//	頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//	弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	弾の確保分回す
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	位置
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	動き
		g_aBullet[nCntBullet].bUse = false;								//	使用しているかしないか
		g_aBullet[nCntBullet].nLife = 0;								//	寿命
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAMRE, &g_pTextureBullet);

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

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	弾の確保分回す
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);	//	左上
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);	//	右上
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);	//	左上
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);	//	右下
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//	左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//	右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//	左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//	右下

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
	{//	テクスチャが使用されていた場合
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{//	頂点バッファが使用されていた場合
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;	//	頂点情報のポインタ

	//	頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	弾の確保分回す
		if (g_aBullet[nCntBullet].bUse == true)
		{//	弾が使用されているか
			//弾を移動させる
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);

			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			if (g_aBullet[nCntBullet].pos.y <= 0|| g_aBullet[nCntBullet].pos.y >= 780 || g_aBullet[nCntBullet].pos.x <= 0 || g_aBullet[nCntBullet].pos.x >= 1280)
			{//	画面外に出た場合
				g_aBullet[nCntBullet].bUse = false;	//	弾を消す
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//	プレイヤーの弾
				//	一定時間経過
				g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//	弾のライフ設定
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
				if (g_aBullet[nCntBullet].nLife >= 0)
				{//	エフェクトの処理
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 10.0f, 10);
					g_aBullet[nCntBullet].bUse = true;
				}

				//	敵ポインタ
				Enemy *pEnemy;
				pEnemy = GetEnemy();

				//	中ボスエネミーポインタ
				TBossEnemy *pTBossEnemy;
				pTBossEnemy = GetTBossEnemy();

				//	サイドエネミーポインタ
				SideEnemy *pSideEnemy;
				pSideEnemy = GetSideEnemy();

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//	敵の確保分回す
					if (pEnemy->bUse == true)
					{//敵が使用されている
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{//	敵の通常状態
							//[敵との当たり判定]
							if (pEnemy->pos.x - ENEMY_SIZEMAX < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + ENEMY_SIZEMAX > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - ENEMY_SIZEMAX < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + ENEMY_SIZEMAX > g_aBullet[nCntBullet].pos.y)
							{
								HitEnemy(nCntEnemy, 1);
								g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
							}
						}
					}
				}
				for (int nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++, pTBossEnemy++)
				{//中ボスエネミー
					if (pTBossEnemy->bUse == true) //敵が使用されている
					{
						//[敵との当たり判定]
						if (pTBossEnemy->pos.x - 50 - 50 < g_aBullet[nCntBullet].pos.x && pTBossEnemy->pos.x + 50 + 50 > g_aBullet[nCntBullet].pos.x  &&
							pTBossEnemy->pos.y - 50 - 50 < g_aBullet[nCntBullet].pos.y && pTBossEnemy->pos.y + 50 + 50 > g_aBullet[nCntBullet].pos.y)
						{
							HitTBossEnemy(nCntTBossEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
						}
					}
				}
				for (int nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++, pSideEnemy++)
				{//大砲エネミー
					if (pSideEnemy->bUse == false) //敵が使用されている
					{
						//[敵との当たり判定]
						if (pSideEnemy->pos.x - 15 - 15 < g_aBullet[nCntBullet].pos.x && pSideEnemy->pos.x + 15 + 15 > g_aBullet[nCntBullet].pos.x  &&
							pSideEnemy->pos.y - 15 - 15 < g_aBullet[nCntBullet].pos.y && pSideEnemy->pos.y + 15 + 15 > g_aBullet[nCntBullet].pos.y)
						{
							HitSideEnemy(nCntSideEnemy, 1);
						}
					}
				}
			}
			else  if (g_aBullet[nCntBullet].type == BULLTETYPE_ENEMY)	//敵の弾
			{//プレイヤー

				if (g_aBullet[nCntBullet].nLife >= 0)
				{//エフェクトの処理
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 10.0f, 5);
					g_aBullet[nCntBullet].bUse = true;
				}
				Player*pPlayer;
				pPlayer = GetPlayer();
				//カラー
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				//プレイヤー
				pPlayer = GetPlayer();
				if (pPlayer->bDisp == true)
				{
					//[プレイヤーとの当たり判定]
					if (pPlayer->pos.x - 10 - 10 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 10 + 10 > g_aBullet[nCntBullet].pos.x  &&
						pPlayer->pos.y - 10 - 10 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 10 + 10 > g_aBullet[nCntBullet].pos.y)
					{//	プレイヤーの範囲内に入った場合
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
					}
				}
			}

		}
		pVtx += 4;		//	該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBullet->Unlock();

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
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntBullet ,2);
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
			g_aBullet[nCntBullet].pos = pos;		//	位置
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			g_aBullet[nCntBullet].nLife = 35;		//	寿命
			g_aBullet[nCntBullet].move = move;		//	動き
			g_aBullet[nCntBullet].type = type;		//	種類
			g_aBullet[nCntBullet].bUse = true;		//	弾が使用されている
			break;
		}
		pVtx += 4;			//	該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBullet->Unlock();
}

