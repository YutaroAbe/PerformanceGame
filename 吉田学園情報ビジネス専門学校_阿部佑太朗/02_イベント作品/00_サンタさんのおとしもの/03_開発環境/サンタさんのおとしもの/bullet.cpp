//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author :長山拓実
//
//=============================================================================
#include "bullet.h"
//#include "explosion.h"
//#include "enemy.h"
#include "player.h"
//#include "effect.h"
#include "sound.h"
//#include "boss.h"
//#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BULLET			(2048)								// 弾の最大数
#define POLYGON_X			(1200)								// ポリゴンのX座標
#define POLYGON_Y			(350)								// ポリゴンのY座標
#define BULLET_TEXTURENAME	"data\\TEXTURE\\bullet000.png"		// テクスチャ名
#define BULLET_SIZE			(30)									// 弾の大きさ
#define BULLET_HIT			(25)								// 通常の敵の当たり判定
#define BULLET_HIT_BOSS		(100)								// ボスの当たり判定
#define PLAYER_HIT			(15)								// プレイヤーの当たり判定
#define MAX_TYPE_BULLET		(2)									// 読み込むテクスチャの数
#define ITEM0_TEXTURE_NAME	"data\\TEXTURE\\present_boy.png"				// 読み込むテクスチャ名
#define ITEM1_TEXTURE_NAME	"data\\TEXTURE\\present_girl.png"			// 読み込むテクスチャ名

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 弾の位置
	D3DXVECTOR3 move;		// 弾の移動
	D3DXCOLOR col;			// 弾の色
	ITEMTYPE itemtype;		// アイテムの種類
	float fBulletHeight;	// 高さ
	float fBulletWidth;		// 幅
	int nLife;				// 弾のライフ
	bool bUse;
} Bullet;

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBullet[MAX_TYPE_BULLET] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						// 使用しているかどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// ポリゴン座標の設定
	g_aBullet[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].itemtype = ITEMTYPE_COIN;
		g_aBullet[nCntBullet].fBulletHeight = BULLET_SIZE + 15.0f;
		g_aBullet[nCntBullet].fBulletWidth = BULLET_SIZE;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nLife = 200;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ITEM0_TEXTURE_NAME, &g_apTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM1_TEXTURE_NAME, &g_apTextureBullet[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,	// 確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						// 頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet,
								NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_BULLET; nCntTex++)
	{
		if (g_apTextureBullet[nCntTex] != NULL)
		{
			g_apTextureBullet[nCntTex]->Release();
			g_apTextureBullet[nCntTex] = NULL;
		}
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
	int nCntBullet;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	// 弾が使用されている
		{
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (4 * nCntBullet);	// 該当の位置まで進める

			// 頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

			// 頂点バッファをアンロック
			g_pVtxBuffBullet->Unlock();

			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;	// 使用していない状態にする
			}

			

			// 一定時間経過
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				// 爆発の設定
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT && g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH && g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			// エフェクトの設定
			//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0, 1.0f, 1.0f, 0.5f), 15.0f, 10);
			
			
			Player *pPlayer;

			// プレイヤーの取得
			pPlayer = GetPlayer();

			if (pPlayer->bDis == true)
			{// プレイヤーが使用されている
					

				// 一定時間経過
				g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{
					// 爆発の設定
					//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
			// エフェクトの設定
			//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0, 0.0f, 0.0f, 0.5f), 15.0f, 10);
			
		}
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

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	// 弾が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBullet[g_aBullet[nCntBullet].itemtype]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntBullet,
									2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEMTYPE *itemtype)
{
	int nCntBullet;
	//float fDiffAngle;	// 差分
	//float fDestAngle;	// 目的の角度
	//float fMoveAngle;	// 現在の角度
	Player *pPlayer;

	// プレイヤーの取得
	pPlayer = GetPlayer();
	// 敵の取得

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			
			g_aBullet[nCntBullet].pos = pos;

			VERTEX_2D *pVtx;	// 頂点情報へのポインタ

			// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBullet * 4);	// 該当の位置まで進める

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 頂点バッファをアンロック
			g_pVtxBuffBullet->Unlock();

			g_aBullet[nCntBullet].itemtype = *itemtype;   // アイテムの種類のアドレスを入れる

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;	// 使用している状態
			g_aBullet[nCntBullet].nLife = 300;	// 使用している状態
			break;
		}
	}
}

//=============================================================================
// 弾の当たり判定
//=============================================================================
bool CollisionBullet(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **itemtype)
{
	int nCntBullet;

	bool bBullet = false;

	// プレイヤーの取得
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (pPos->x + fWidth > g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth && pPos->y - fHeight < g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight
				&& pPos->x - fWidth < g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth && pPos->y > g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight)
			{
				//PlaySound(SOUND_LABEL_SE_COIN);
				//SetExplosion(g_aItem[nCntItem].pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				//AddScore(15000);				// スコア加算
				g_aBullet[nCntBullet].bUse = false;
				*itemtype = &g_aBullet[nCntBullet].itemtype;
				bBullet = true;
				//*nItem = &g_aItem[nCntItem].itemtype;   // アイテムの種類のアドレスを入れる
			}
		}
		/*if (g_aItem[nCntItem].bUse == false)
		{
		nItem++;

		if (nItem == MAX_ITEM)
		{
		GAMESTATE GameState;
		GameState = GetGameState();

		if (GameState != GAMESTATE_CLEAR && GameState != GAMESTATE_FAILD)
		{
		SetGameState(GAMESTATE_CLEAR);
		*TimeStop = true;
		}
		}
		}*/
	}
	return bBullet;
}
//=============================================================================
// 弾の当たり判定
//=============================================================================
bool CollisionBullet2(D3DXVECTOR3 *pPos, float fHeight, float fWidth ,int **nIdxBullet)
{
	int nCntBullet;

	bool bBullet = false;

	// プレイヤーの取得
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (pPos->x + fWidth > g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth && pPos->y - fHeight < g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight
				&& pPos->x - fWidth < g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth && pPos->y > g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight)
			{
				//PlaySound(SOUND_LABEL_SE_COIN);
				//SetExplosion(g_aItem[nCntItem].pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				//AddScore(15000);				// スコア加算
				g_aBullet[nCntBullet].bUse = false;
				*nIdxBullet = &nCntBullet;
				bBullet = true;
				//*nItem = &g_aItem[nCntItem].itemtype;   // アイテムの種類のアドレスを入れる
			}
		}
		/*if (g_aItem[nCntItem].bUse == false)
		{
		nItem++;

		if (nItem == MAX_ITEM)
		{
		GAMESTATE GameState;
		GameState = GetGameState();

		if (GameState != GAMESTATE_CLEAR && GameState != GAMESTATE_FAILD)
		{
		SetGameState(GAMESTATE_CLEAR);
		*TimeStop = true;
		}
		}
		}*/
	}
	return bBullet;
}
//=============================================================================
// 弾消去処理
//=============================================================================
void DeleteBullet(int nIdxBullet)
{
	g_aBullet[nIdxBullet].bUse = false;
}