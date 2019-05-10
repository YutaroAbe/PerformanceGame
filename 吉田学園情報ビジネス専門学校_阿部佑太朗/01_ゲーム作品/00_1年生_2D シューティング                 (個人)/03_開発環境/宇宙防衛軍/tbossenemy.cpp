//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "tbossenemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_TBOSSENEMY		(4)								// 敵の種類
#define TBOSSENEMY_01 "data/TEXTURE/enemy002.png"
#define TBOSSENEMY_02 "data/TEXTURE/enemy004.png"
#define TBOSSENEMY_03 "data/TEXTURE/enemy002.png"
#define TBOSSENEMY_04 "data/TEXTURE/enemy003.png"


//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureTBossEnemy[MAX_TYPE_TBOSSENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTBossEnemy = NULL;					// 頂点バッファへのポインタ
TBossEnemy g_aTBossEnemy[MAX_TBOSSENEMY];										//敵の情報
int g_nNumTBossEnemy;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTBossEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		g_aTBossEnemy[nCntTBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aTBossEnemy[nCntTBossEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTBossEnemy[nCntTBossEnemy].nType = 0;
		g_aTBossEnemy[nCntTBossEnemy].bUse = false;
		g_aTBossEnemy[nCntTBossEnemy].nLife = 50;
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 0;
		g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;
		g_nNumTBossEnemy = 0;
		g_aTBossEnemy[nCntTBossEnemy].nCounterBullet = 0;
	}

	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_01, &g_apTextureTBossEnemy[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_02, &g_apTextureTBossEnemy[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_03, &g_apTextureTBossEnemy[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_04, &g_apTextureTBossEnemy[3]);



	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TBOSSENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTBossEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//左上
		pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//右上
		pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//左上
		pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//右下
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTBossEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTBossEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_TBOSSENEMY; nCntTex++)
	{
		if (g_apTextureTBossEnemy[nCntTex] != NULL)
		{
			g_apTextureTBossEnemy[nCntTex]->Release();
			g_apTextureTBossEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTBossEnemy != NULL)
	{
		g_pVtxBuffTBossEnemy->Release();
		g_pVtxBuffTBossEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTBossEnemy(void)
{

	int nCntTBossEnemy;


	for (nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		g_aTBossEnemy[nCntTBossEnemy].nCounterBullet++;
		Player*pPlayer;
		pPlayer = GetPlayer();
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //敵が使用されている
		{//敵に当たったらプレイヤーがデス状態
			if (pPlayer->bDisp == true)
			{//
				if (pPlayer->pos.x - BOSSENEMY_SIZEMAX < g_aTBossEnemy[nCntTBossEnemy].pos.x && pPlayer->pos.x + BOSSENEMY_SIZEMAX > g_aTBossEnemy[nCntTBossEnemy].pos.x  &&
					pPlayer->pos.y - BOSSENEMY_SIZEMAX < g_aTBossEnemy[nCntTBossEnemy].pos.y && pPlayer->pos.y + BOSSENEMY_SIZEMAX > g_aTBossEnemy[nCntTBossEnemy].pos.y)
				{
					HitPlayer(pPlayer->nLife);

				}
			}
		}
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //敵が使用されている
		{
			if (rand() % 8 == 0)
			{//攻撃速
				float fBullet;

				fBullet = 0.05f * ((g_aTBossEnemy[nCntTBossEnemy].nCounterBullet) % 3600);

				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(fBullet)*10.0f, cosf(fBullet)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//弾
				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(3.14f - fBullet)*10.0f, cosf(3.14f - fBullet)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//弾

			}
			else if (rand() % 100 == 0)
			{

				float fDiffAngle;				//差分
				float fDestAngle;				//目的の角度
				float fMoveAngle;				//現在の角度
				fDestAngle = D3DX_PI;
				fDestAngle = atan2f(pPlayer->pos.x - g_aTBossEnemy[nCntTBossEnemy].pos.x, pPlayer->pos.y - g_aTBossEnemy[nCntTBossEnemy].pos.y);
				fMoveAngle = (0.0f, 0.0f, 0.0f);

				fDiffAngle = fDestAngle - fMoveAngle;
				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				if (fDiffAngle < -D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				fMoveAngle += fDiffAngle * 0.1f;
				if (fMoveAngle > D3DX_PI)
				{
					fMoveAngle -= D3DX_PI * 2.0f;
				}
				if (fMoveAngle < -D3DX_PI)
				{
					fMoveAngle += D3DX_PI * 2.0f;
				}
				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(fDiffAngle)*10.0f, cosf(fDiffAngle)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//弾

			}
		}

		switch (g_aTBossEnemy[nCntTBossEnemy].state)
		{
		case TBOSSENEMYSTATE_NOMAL:
			//	カウントダウン
			g_aTBossEnemy[nCntTBossEnemy].nCounterState--;
			if (g_aTBossEnemy[nCntTBossEnemy].bUse == true)
			{//	敵が使用されていたら
				g_aTBossEnemy[nCntTBossEnemy].pos.x += g_aTBossEnemy[nCntTBossEnemy].move.x;
				g_aTBossEnemy[nCntTBossEnemy].pos.y += g_aTBossEnemy[nCntTBossEnemy].move.y;
				//	頂点情報の作成
				VERTEX_2D *pVtx;
				//	頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);
				//	ポジション
				pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//左上
				pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//右上
				pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//左上
				pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//右下
				// 頂点バッファをアンロックする
				g_pVtxBuffTBossEnemy->Unlock();
				//	移動の設定
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.x = 0;

					if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 1;

						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.y = 0;

							if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
							{
								g_aTBossEnemy[nCntTBossEnemy].move.x = -1;
							}
						}
					}
				}
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.x = 0;
					if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = -1;
						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.y = 0;
						}
						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.x = 1;
						}
					}

				}
				else
				{
					break;
				}

		case TBOSSENEMYSTATE_DAMAGE:
			g_aTBossEnemy[nCntTBossEnemy].pos.x += g_aTBossEnemy[nCntTBossEnemy].move.x;
			g_aTBossEnemy[nCntTBossEnemy].pos.y += g_aTBossEnemy[nCntTBossEnemy].move.y;

			// 頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

			//	ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//左上
			pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//右上
			pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//左上
			pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//右下

			// 頂点バッファをアンロックする
			g_pVtxBuffTBossEnemy->Unlock();

			//移動の設定｛
			if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
			{
				g_aTBossEnemy[nCntTBossEnemy].move.x = 0;

				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.y = 1;

					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 0;

						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.x = -1;
						}
					}
				}
			}
			if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
			{
				g_aTBossEnemy[nCntTBossEnemy].move.x = 0;
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.y = -1;
					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 0;
					}
					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.x = 1;
					}
				}

			}

			g_aTBossEnemy[nCntTBossEnemy].nCounterState--; //カウントダウン
			if (g_aTBossEnemy[nCntTBossEnemy].nCounterState <= 0)
			{
				g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;

				VERTEX_2D*pVtx;								//頂点情報のポインタ
				// 頂点バッファをロックし、頂点データへのポインタ
				g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntTBossEnemy * 4);//頂点ポインタを4つ進める

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//頂点バッファアンロックする
				g_pVtxBuffTBossEnemy->Unlock();

			}
			break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffTBossEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureTBossEnemy[g_aTBossEnemy[nCntTBossEnemy].nType]);
			//ポリゴンの描画
			if (g_aTBossEnemy[nCntTBossEnemy].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntTBossEnemy * 4,
					2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetTBossEnemy(D3DXVECTOR3 pos,int nType)
{
	int nCntTBossEnemy;
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == false)	//敵が使用されていない
		{
			g_aTBossEnemy[nCntTBossEnemy].pos = D3DXVECTOR3(1400, 300, 0.0f);
			g_aTBossEnemy[nCntTBossEnemy].move = D3DXVECTOR3(-1, 0, 0);
			//g_aTBossEnemy[nCntTBossEnemy].pos = pos;
			g_aTBossEnemy[nCntTBossEnemy].nType = nType;
			g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;
			g_aTBossEnemy[nCntTBossEnemy].nCounterState = 0;
			g_aTBossEnemy[nCntTBossEnemy].nLife = 50;//敵のライフ設定
			g_aTBossEnemy[nCntTBossEnemy].bUse = true;//敵が使用されている

			//ポジション
			pVtx[nCntTBossEnemy * 4].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);

			g_nNumTBossEnemy++;
			break;
		}
	}
	//頂点バッファアンロックする
	g_pVtxBuffTBossEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
TBossEnemy *GetTBossEnemy(void)
{
	return &g_aTBossEnemy[0];
}
//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitTBossEnemy(int nCntTBossEnemy, int nDamage)
{
	g_aTBossEnemy[nCntTBossEnemy].nLife -= nDamage;


	if (g_aTBossEnemy[nCntTBossEnemy].nLife <= 0)
	{//ライフが0になった場合
   		SetExplosion(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//SetGemeState(GAMESTATE_END);								//リザルト画面へ
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 90;			//ダメージ状態時間
		SetGemeState(GAMESTATE_CLEAR);								//リザルト画面へ
		g_aTBossEnemy[nCntTBossEnemy].bUse = false;
			AddScore(10000);

	}
	else
	{
		g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_DAMAGE;
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 10;		//ダメージ状態時間

		VERTEX_2D*pVtx;								//頂点情報のポインタ
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[nCntTBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファアンロックする
		g_pVtxBuffTBossEnemy->Unlock();
	}

	//攻撃したENMYが蟹になる
	//
	/*if ((g_aEnemy[nCntEnemy].nLife <= 0) || (g_aEnemy[nCntEnemy].nType = 0))
	{
		AddScore(g_aEnemy[nCntEnemy].nType + 1);
	}*/
}
