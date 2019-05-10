//=============================================================================
//
// 敵の処理 [sideenemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "sideenemy.h"
#include "explosion.h"
#include "bullet.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_SIDEENEMY		(4)								// 敵の種類
#define ENEMY_01 "data/TEXTURE/T0000.png"
#define ENEMY_02 "data/TEXTURE/T0001.png"
#define ENEMY_PMAX (30)											//敵の大きさ

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureSIDEEnemy[MAX_TYPE_SIDEENEMY] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSIDEEnemy = NULL;							// 頂点バッファへのポインタ
SideEnemy g_aSIDEEnemy[MAX_SIDEENEMY];										//敵の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitSideEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSIDEEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_SIDEENEMY; nCntEnemy++)
	{
		g_aSIDEEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aSIDEEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSIDEEnemy[nCntEnemy].nType = 0;
		g_aSIDEEnemy[nCntEnemy].bUse = false;
		//g_aSIDEEnemy[nCntEnemy].nLife = 1;
		g_aSIDEEnemy[nCntEnemy].nCounterState = 0;
		g_aSIDEEnemy[nCntEnemy].state = SIDEENEMYSTATE_NOMAL;
	}

	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureSIDEEnemy[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureSIDEEnemy[1]);

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SIDEENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffSIDEEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntSIDEEnemy = 0; nCntSIDEEnemy < MAX_SIDEENEMY; nCntSIDEEnemy++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//左上
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//右上
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//左上
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//右下
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSIDEEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSideEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_SIDEENEMY; nCntTex++)
	{
		if (g_apTextureSIDEEnemy[nCntTex] != NULL)
		{
			g_apTextureSIDEEnemy[nCntTex]->Release();
			g_apTextureSIDEEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffSIDEEnemy != NULL)
	{
		g_pVtxBuffSIDEEnemy->Release();
		g_pVtxBuffSIDEEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSideEnemy(void)
{
	int nCntSideEnemy;

	for (nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++)
	{
		if (g_aSIDEEnemy[nCntSideEnemy].bUse == true)	//敵が使用されている
		{
			switch (g_aSIDEEnemy[nCntSideEnemy].state)
			{
			case SIDEENEMYSTATE_NOMAL:

				g_aSIDEEnemy[nCntSideEnemy].nCounterState--; //カウントダウン

				if (g_aSIDEEnemy[nCntSideEnemy].bUse == true)
				{
					g_aSIDEEnemy[nCntSideEnemy].pos.x += g_aSIDEEnemy[nCntSideEnemy].move.x;
					g_aSIDEEnemy[nCntSideEnemy].pos.y += g_aSIDEEnemy[nCntSideEnemy].move.y;
					// 頂点情報の作成
					VERTEX_2D *pVtx;

					// 頂点バッファをロックし、頂点情報へのポインタを取得
					g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);
					//ポジション
					pVtx[nCntSideEnemy * 4].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 1].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 2].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 3].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
					// 頂点バッファをアンロックする
					g_pVtxBuffSIDEEnemy->Unlock();

					//g_aSIDEEnemy[nCntSideEnemy].pos.x + g_aSIDEEnemy[nCntSideEnemy].move.x;
					if (g_aSIDEEnemy[nCntSideEnemy].pos.x <= 0)
					{
						g_aSIDEEnemy[nCntSideEnemy].move.x = 1;
					}
					if (g_aSIDEEnemy[nCntSideEnemy].pos.x >= 1250)
					{
						g_aSIDEEnemy[nCntSideEnemy].move.x = -1;
					}


					if (rand() % 250 == 0)
					{//攻撃速度
						SetBullet(g_aSIDEEnemy[nCntSideEnemy].pos, D3DXVECTOR3(0.0f, -4.0f, 0.0f), BULLTETYPE_ENEMY);		//弾下
					}
					break;
				}
			case SIDEENEMYSTATE_DAMAGE:

				g_aSIDEEnemy[nCntSideEnemy].nCounterState--; //カウントダウン
				if (g_aSIDEEnemy[nCntSideEnemy].nCounterState <= 0)
				{
					g_aSIDEEnemy[nCntSideEnemy].state = SIDEENEMYSTATE_NOMAL;

					VERTEX_2D*pVtx;								//頂点情報のポインタ
					// 頂点バッファをロックし、頂点データへのポインタ
					g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

					pVtx += (nCntSideEnemy * 4);//頂点ポインタを4つ進める

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//頂点バッファアンロックする
					g_pVtxBuffSIDEEnemy->Unlock();
				}
				break;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSideEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffSIDEEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_SIDEENEMY; nCntEnemy++)
	{
		if (g_aSIDEEnemy[nCntEnemy].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureSIDEEnemy[g_aSIDEEnemy[nCntEnemy].nType]);
			//ポリゴンの描画
			if (g_aSIDEEnemy[nCntEnemy].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntEnemy * 4,
					2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetSideEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntSideEnemy;
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++)
	{
		if (g_aSIDEEnemy[nCntSideEnemy].bUse == false)	//敵が使用されていない
		{
			g_aSIDEEnemy[nCntSideEnemy].pos = pos;
			g_aSIDEEnemy[nCntSideEnemy].move = D3DXVECTOR3(-1, 0, 0);
			g_aSIDEEnemy[nCntSideEnemy].nType = nType;
			g_aSIDEEnemy[nCntSideEnemy].state = SIDEENEMYSTATE_NOMAL;
			g_aSIDEEnemy[nCntSideEnemy].nCounterState = 0;//敵のライフ設定
			//g_aSIDEEnemy[nCntSideEnemy].nLife = 100;
			g_aSIDEEnemy[nCntSideEnemy].bUse = true;//敵が使用されている

			//ポジション
			pVtx[nCntSideEnemy * 4].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 1].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 2].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 3].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);

			break;
		}
	}
	//頂点バッファアンロックする
	g_pVtxBuffSIDEEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
SideEnemy *GetSideEnemy(void)
{
	return &g_aSIDEEnemy[0];
}
//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitSideEnemy(int nCntEnemy, int nDamage)
{
		g_aSIDEEnemy[nCntEnemy].nCounterState = 90;		//ダメージ状態時間
		g_aSIDEEnemy[nCntEnemy].bUse = false;

}
