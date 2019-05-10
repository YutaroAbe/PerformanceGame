//=============================================================================
//
// プレイヤーの処理 [Player.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "bullet.h"
#include "fade.h"
#include "effect.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define NCUT_ANIM_TIME (15)							//カウントアニメーション時間
#define NPAR_ANIM_TAIM (10)							//アニメーションパターン
#define POS_X (40)									//ポジション_X
#define POS_Y (70)									//ポジション_X
#define POLYGON_TEXTURENAMRE "data/TEXTURE/player000.png"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //頂点バッファのポイント

Player g_Player;
float g_Spin;
int g_nPosState;
int g_nTexAnimState;
int nBulletType;
//=============================================================================
//初期化処理プレイヤー
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	g_Player.nCounterAnim = 0;
	g_nTexAnimState = 0;
	g_Player.nPatternAnim = 0;
	//各ｇ_変数初期化
	g_Player.pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	//g_Player.bUse = true;
	g_Player.nCounterState = 0;
	g_Player.nLife = 10;
	g_Player.bDisp = true;
	g_Player.state = PLAYERSTATE_NOMAL;
	g_nPosState = 1;
	nBulletType = 0;

	//テクスチャ読み込み右
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAMRE, &g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx,0);

	//ポリゴン位置、移動
	g_Player.pos = D3DXVECTOR3(200, 365, 0.0f);
	g_Player.move = D3DXVECTOR3(0,0,0.0f);

	//頂点座標設定
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//右下
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);			  //左上
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);			  //右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);			  //左下
	pVtx[3].tex = D3DXVECTOR2(0.125f, 0.5f);			  //右下
	//頂点バッファアンロックする
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//終了処理更新処理プレイヤー
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=============================================================================
//更新処理プレイヤー
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx = 0;								//頂点情報のポインタ

	if (GetKeyboardTrigger(DIK_W) == true)
	{//上移動遅くす

		g_nPosState -= 1;
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{//下移動遅くする
		g_nPosState += 1;
	}
	switch (g_nPosState)
	{
	case 0:
		g_Player.pos.y = 260;
		break;
	case 1:
		g_Player.pos.y = 450;
		break;
	case 2:
		g_Player.pos.y = 640;
		break;
	}

	if (g_nPosState >= 2)
	{
		g_nPosState = 2;
	}
	else if (g_nPosState <= 0)
	{
		g_nPosState = 0;
	}


	if (GetKeyboardTrigger(DIK_I) == true)
	{//スペース押した場合の処理

		g_nTexAnimState = 1;
	}
	else if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_nTexAnimState = 2;
	}
	else
	{
		nBulletType = 0;
	}
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	switch (g_nTexAnimState)
	{
	case 0:
		break;
	case 1:
		g_Player.nCounterAnim++;
		if ((g_Player.nCounterAnim % 2) == 0)
		{
			//パターンNo,更新
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 6;//パターンを初期化に戻す

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((1.0f/6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.0f);				 //右上
			pVtx[1].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.0f);				 //右上
			pVtx[2].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.5f);				 //右上
			pVtx[3].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.5f);				//右上
			if (g_Player.nPatternAnim <= 0)
			{
				g_nTexAnimState = 0;

			}
			else if (g_Player.nPatternAnim <= 3)
			{
				nBulletType = 1;
			}
		}
		break;
	case 2:
		g_Player.nCounterAnim++;
		if ((g_Player.nCounterAnim % 2) == 0)
		{
			//パターンNo,更新
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 6;//パターンを初期化に戻す

																	//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.5f);				 //右上
			pVtx[1].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.5f);				 //右上
			pVtx[2].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 1.0f);				 //右上
			pVtx[3].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 1.0f);				//右上
			if (g_Player.nPatternAnim <= 0)
			{
				g_nTexAnimState = 0;

			}
			else if (g_Player.nPatternAnim <= 3)
			{
				nBulletType = 2;
			}
		}
		break;
	}
	//頂点バッファアンロックする
	g_pVtxBuffPlayer->Unlock();

	switch (nBulletType)
	{
	case 0 :
		break;
	case 1:
		SetBullet(g_Player.pos + D3DXVECTOR3(30, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_000);			//弾横
		break;
	case 2:
		SetBullet(g_Player.pos + D3DXVECTOR3(30, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_001);			//弾横
		break;
	}

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//右下

	//頂点バッファアンロックする
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//描画処理プレイヤー
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスへのポインタ

		//デバイス取得
		pDevice = GetDevice();
		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
		//頂点フォーマット設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);
		if (g_Player.bDisp == true)
		{
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}

}
//=============================================================================
// プレイヤーの設定
//=============================================================================
void SetPlayer(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Player.bDisp == false)			//プレイヤーが使用されていない
	{
		g_Player.pos = pos;					//位置
		g_Player.state = PLAYERSTATE_NOMAL;
		g_Player.nType = nType;				//タイプ
		g_Player.nCounterState = 0;			//プレイヤーのライフ設定
		g_Player.nLife = 10;				//体力
		g_Player.bDisp = true;				//プレイヤーが使用されている
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//左上
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//右上
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//左下
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//右下

	}
	//頂点バッファアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	//int nCount;
	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//プレイヤーの体力が0以下になったとき

			//SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_Player.state = PLAYERSTATE_DEATH;
			g_Player.nCounterState = 60;				//ダメージ状態時間
			g_Player.bDisp = false;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 15;				//ダメージ状態時間

		VERTEX_2D*pVtx;								//頂点情報のポインタ
		// 頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}
//=============================================================================
//
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

