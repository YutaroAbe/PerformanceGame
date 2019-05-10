//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "enemy.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "block.h"
#include "trap.h"
#include "sound.h"
#include "fade.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(5)								// 敵の種類
#define ENEMY_01 "data/TEXTURE/.png"
#define ENEMY_02 "data/TEXTURE/enemy001.png"
#define ENEMY_03 "data/TEXTURE/enemy002.png"
#define ENEMY_04 "data/TEXTURE/enemy003.png"
#define ENEMY_05 "data/TEXTURE/enemy004.png"

#define ENEMY_PMAX (25)											//敵の大きさ

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
		g_aEnemy[nCntEnemy].fHeight = 0;
		g_aEnemy[nCntEnemy].fWindth = 0;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterMove = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
	}
	g_nNumEnemy = 0;
	
	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_03, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_04, &g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_05, &g_apTextureEnemy[4]);
	

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
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
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

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
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
	
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//アニメーション
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//エネミーが使用されているか 
		{
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;		//前回の位置を保存
			g_aEnemy[nCntEnemy].pos.x -= pPlayer->move.x;
			g_aEnemy[nCntEnemy].nCounterAnim++;
			g_aEnemy[nCntEnemy].nCounterMove++;
			if (g_aEnemy[nCntEnemy].nType == 1)
			{//ナイト1
				if (g_aEnemy[nCntEnemy].nCounterMove % 60 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= -1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 2)
			{//ナイト2
				if (g_aEnemy[nCntEnemy].nCounterMove % 155 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 80 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -20.0f;
					g_aEnemy[nCntEnemy].move.x = -5.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 160 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= -1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 3)
			{//ナイト3
				if (g_aEnemy[nCntEnemy].nCounterMove % 190 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -5.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -5.0f;
					g_aEnemy[nCntEnemy].move.x = 6.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 90 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 150 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -15.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 4)
			{//ナイト3
				if (g_aEnemy[nCntEnemy].nCounterMove % 140 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -2.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 170 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -3.0f;
					g_aEnemy[nCntEnemy].move.x = 6.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 190 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -11.0f;
					g_aEnemy[nCntEnemy].move.x = -2.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 170 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
			}
			if ((g_aEnemy[nCntEnemy].nCounterAnim % 15) == 0)
			{
				//パターンNo,更新
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;//パターンを初期化に戻す 
			}

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.0f);					 //右上
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);				 //右上
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //右上

			if (g_aEnemy[nCntEnemy].move.x >= 0.5)
			{
					//テクスチャ座標
					pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.0f);					 //右上
					pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
					pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);				 //右上
					pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //右上
			}
			else if (g_aEnemy[nCntEnemy].move.x <= -0.5)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);					 //右上
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //右上
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 1.0f);				 //右上
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 1.0f);       //右上
			}

		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
	
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		
		if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用されている
		{
			g_aEnemy[nCntEnemy].move.y += 0.75;				//重力
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				g_aEnemy[nCntEnemy].nCounterState--; //カウントダ
				break;
			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEnemy].nCounterState--; //カウントダウン

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					// 頂点バッファをロックし、頂点情報へのポインタを取得
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);//頂点ポインタを4つ進める
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					// 頂点バッファをアンロックする
					g_pVtxBuffEnemy->Unlock();
					break;
				}
			}
		}
		
	}
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//CollisionTrap(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].fWindth, &g_aEnemy[nCntEnemy].fHeight); //ブロックとの判定処理

		if (g_aEnemy[nCntEnemy].bUse == true)//エネミーが使用されているか 
		{

			CollisionBlockEnemy(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].fWindth, &g_aEnemy[nCntEnemy].fHeight);

			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
		}
		pVtx += 4;
	}
	//頂点バッファアンロックする
	g_pVtxBuffEnemy->Unlock();
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
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight,int nLife )
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
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = nLife;//敵のライフ設定
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].fWindth = fWindth;
			g_aEnemy[nCntEnemy].bUse = true;//敵が使用されている
			g_aEnemy[nCntEnemy].nCounterAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			
			break;
			g_nNumEnemy++;
		}
		pVtx += 4;
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
		if (g_aEnemy[nCntEnemy].nType == 1)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
		}
		if (g_aEnemy[nCntEnemy].nType == 2)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

		}
		if (g_aEnemy[nCntEnemy].nType == 3)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);

		}
		g_aEnemy[nCntEnemy].nCounterState = 90;		//ダメージ状態時間
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		if (g_aEnemy[nCntEnemy].nType == 1 || g_aEnemy[nCntEnemy].nType == 2 || g_aEnemy[nCntEnemy].nType == 4)
		{
			AddScore(100);
		}
		if (g_aEnemy[nCntEnemy].nType == 3)
		{
			AddScore(500);
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

		pVtx += (nCntEnemy * 4);//頂点ポインタを4つ進める
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		//頂点バッファアンロックする
		g_pVtxBuffEnemy->Unlock();
		
	}
}
//=============================================================================
//プレイヤーとエネミーの判定処理
//=============================================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	for (int nCntEnemy = 0; nCntEnemy< MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth &&									//プレイヤーが右からめり込んでるとき
				pPos->x - (*fWindth / 2) <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth &&		//プレイヤーが左からめり込んでるとき
				pPos->y <= g_aEnemy[nCntEnemy].pos.y &&															//プレイヤーが上から下にめり込んでるとき
				pPos->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)					//プレイヤーが下から上にめり込んでるとき
			{//YXが範囲内
				if (pPosOld->y - *fHeight <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight &&
					pPos->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)
				{//敵上判定	
					PlaySound(SOUND_LABEL_SE_ENEMY0);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - (g_aEnemy[nCntEnemy].fHeight * 2);
					pMove->y = -8.0f;
					HitEnemy(nCntEnemy, 1);
				}
				else if (pPosOld->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight &&	//プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
					        pPos->y - *fHeight <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)				//現在の位置がめり込んでるとき
				{//	敵下判定
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y;
					HitPlayer(1);
				}
				else if (pPosOld->x + *fWindth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth &&	//昔の位置がブロックより右にあって現在の位置がめり込んでる場合
						    pPos->x - *fWindth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth)
				{//ブロック右判定
				 
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					HitPlayer(1);
					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth;
					pMove->x = 20.0f;
					pMove->y = -10.0f;
					
				}
				else if (pPosOld->x - *fWindth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth&&									//昔の位置がブロックより左にあって現在の位置がめり込んでる場合
					         pPos->x + *fWindth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth)
				{//ブロック左判定
				 //bLand = true;
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					HitPlayer(1);
					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth;
					pMove->x = -20.0f;
					pMove->y = - 10.0f;
				}
			}
		}
	}
}
