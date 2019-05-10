//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)								// 敵の種類
#define ENEMY_01 "data/TEXTURE/enemy000.png"
#define ENEMY_02 "data/TEXTURE/enemy001.png"
#define ENEMY_03 "data/TEXTURE/enemy002.png"
#define ENEMY_04 "data/TEXTURE/enemy003.png"

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].CountLife = 0;
	}
	g_nNumEnemy = 0;

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_03, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_04, &g_apTextureEnemy[3]);


	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
		pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
		pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
		pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
		//RHW
		pVtx[nCntEnemy * 4].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 1].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 2].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 3].rhw = 1.0f;
		//カラー
		pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


		//テクスチャ座標
		pVtx[nCntEnemy * 4].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
		pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	VERTEX_2D*pVtx = NULL;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//VERTEX_2D*pVtx = NULL;//頂点情報のポインタ
		if (g_aEnemy[nCntEnemy].bUse == true)//エネミーが使用されているか
		{

			g_aEnemy[nCntEnemy].nCounterAnim++;
			if ((g_aEnemy[nCntEnemy].nCounterAnim % 15) == 0)
			{
				//パターンNo,更新
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 4;//パターンを初期化に戻す
			}
			if (g_aEnemy[nCntEnemy].nType == 2)
			{
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 120, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 120, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 120, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 120, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
			}
			else
			{
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
			}


			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.0f);					 //右上
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 1.0f);				 //右上
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 1.0f);       //右上
													   //カラー

		}
		pVtx += 4;

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
			if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用されている
			{
				g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
				g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NOMAL:

					g_aEnemy[nCntEnemy].nCounterState--; //カウントダウン

					if (rand() % 100 == 0)
					{

					}
						break;
				case ENEMYSTATE_DAMAGE:

					g_aEnemy[nCntEnemy].nCounterState--; //カウントダウン
					if (g_aEnemy[nCntEnemy].nCounterState <= 0)
					{
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;

						VERTEX_2D*pVtx;								//頂点情報のポインタ
						// 頂点バッファをロックし、頂点データへのポインタ
						g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

						pVtx += (nCntEnemy * 4);//頂点ポインタを4つ進める

						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

						//頂点バッファアンロックする
						g_pVtxBuffEnemy->Unlock();
						break;
					}

				}
			}
			if(g_aEnemy[nCntEnemy].pos.x <= 0)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//ポリゴンの描画
			if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEnemy * 4,2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYSTATE state)
{
	int nCntEnemy;
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//敵が使用されていない
		{
			g_aEnemy[nCntEnemy].pos = pos;

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].state = state;
			g_aEnemy[nCntEnemy].nCounterState = 0;//敵のライフ設定
			g_aEnemy[nCntEnemy].nCounterAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			g_aEnemy[nCntEnemy].bUse = true;//敵が使用されている

			if (g_aEnemy[nCntEnemy].nType == 2)
			{
				g_aEnemy[nCntEnemy].nLife = rand() % 2 + 3;
				//ポジション
				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 120, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 120, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 120, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 120, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
			}
			else
			{
				g_aEnemy[nCntEnemy].nLife = rand() % 1 + 1;
				//ポジション
				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX_X, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX_Y, 0.0f);
			}


			g_nNumEnemy++;
			break;
		}

	}
	//頂点バッファアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//ライフが0になった場合
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].nCounterState = 90;		//ダメージ状態時間
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		if (g_aEnemy[nCntEnemy].nType == 0)
		{
			AddScore(100);
			PlaySound(SOUND_LABEL_SE_TAIKO);
		}
		else if (g_aEnemy[nCntEnemy].nType == 1)
		{
			AddScore(200);
			PlaySound(SOUND_LABEL_SE_SINBARU);
		}
		else if (g_aEnemy[nCntEnemy].nType == 2)
		{
			AddScore(500);
			PlaySound(SOUND_LABEL_SE_MOKKIN);
		}


		g_nNumEnemy--;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 10;		//ダメージ状態時間

		VERTEX_2D*pVtx;								//頂点情報のポインタ
		// 頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy *4);//頂点ポインタを4つ進める

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファアンロックする
		g_pVtxBuffEnemy->Unlock();

	}

}