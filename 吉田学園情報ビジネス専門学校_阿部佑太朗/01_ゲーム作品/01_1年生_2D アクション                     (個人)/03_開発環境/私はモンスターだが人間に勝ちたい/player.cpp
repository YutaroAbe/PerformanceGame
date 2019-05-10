//=============================================================================
//
// DirectX雛型処理 [player.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "switch.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "enemy.h"
#include "tutorial.h"
#include "trap.h"
#include "explosion.h"
#include "game2.h"
//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAMRE "data/TEXTURE/PPP.png" //読み込むテクスチャ
#define POS_X (25)								//ポジション_X
#define POS_Y (50)								//ポジション_Y

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //頂点バッファのポイント
D3DXVECTOR3 g_posPlayer;							//ポリゴンの位置
D3DXVECTOR3 g_movePlayer;							//ポリゴンの移動量
PLAYER g_aPlayer;
int g_posCounter;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	g_posCounter = 0;
	g_aPlayer.nCounterAnim = 0;
	g_aPlayer.nPatternAnim = 0;
	g_aPlayer.nCounterState = 0;
	g_aPlayer.fHeight = POS_Y;
	g_aPlayer.fWindth = POS_X;
	g_aPlayer.state = PLAYERSTATE_NOMAL;
	g_aPlayer.nLife = 10;
	g_aPlayer.bDisp = true;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAMRE, &g_pTexturePlayer);

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
	g_aPlayer.pos = D3DXVECTOR3(600, 600, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0, 0, 0.0f);

	//頂点座標設定
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//左上
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//右下
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
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);			//左上
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);			//右下
	//頂点バッファアンロックする
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//終了処理更新処理ポリゴン
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
//更新処理ポリゴン
//=============================================================================
void UpdatePlayer(void)
{
	if (g_aPlayer.bDisp == false)
	{
		g_aPlayer.move.x = 0;
		g_aPlayer.move.y = 0;
	}
	g_aPlayer.posOld = g_aPlayer.pos;		//前回の位置を保存
	Block *g_aBlock;
	g_aBlock = Getblock();

	VERTEX_2D*pVtx;

	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NOMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		PlaySound(SOUND_LABEL_SE_ENEMY0);
		g_aPlayer.nCounterState--;	//カウントダウン
		if (g_aPlayer.nCounterState <= 0)
		{
			g_aPlayer.state = PLAYERSTATE_NOMAL;

			VERTEX_2D*pVtx;								//頂点情報のポインタ

			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_aPlayer.nCounterState--;	//カウントダウン
		if (g_aPlayer.nCounterState <= 0)
		{
			SetGemeState(GAMESTATE_END);
			SetGemeState2(GAME2STATE_END);
			SetTutoState(TUTOSTATE_END);
			g_aPlayer.state = PLAYERSTATE_END;
		}
		return;
		break;

	case PLAYERSTATE_END:
		break;
	}

	if (g_aPlayer.bDisp == true)
	{
		if (g_aPlayer.pos.x = 600)
		{
			g_aPlayer.pos.x = 600;
		}
		if (g_aPlayer.pos.y <= 70)
		{
			HitPlayer(10);
		}
		if (g_aPlayer.pos.y >= 800)
		{
			HitPlayer(10);
		}
		//任意のキー(Aキー)が押されたかどうか :左移動
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aPlayer.move.x += sinf(-D3DX_PI * 0.5) *2.25f;

		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//任意のキー(Dキー)が押されたかどうか　：右移動
			g_aPlayer.move.x += sinf(D3DX_PI * 0.5) *2.25f;
		}
		else
		{
			g_aPlayer.nPatternAnim = 0;
		}

		if (g_aPlayer.move.x <= -0.01f)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.DirectMove = 1;
			if (g_aPlayer.move.y <= -0.01f)
			{//右ジャンプ時
				g_aPlayer.DirectMove = 4;

			}
		}
		else if (g_aPlayer.move.x >= 0.01f)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.DirectMove = 0;
			if (g_aPlayer.move.y <= -0.01f)
			{//左ジャンプ時
				g_aPlayer.DirectMove = 3;
			}
		}
		switch (g_aPlayer.DirectMove)	//プレイヤーテクスチャ切り替え
		{
		case 0:			//左向いて歩いている
			g_aPlayer.nCounterAnim++;
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			if ((g_aPlayer.nCounterAnim % 5) == 0)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.0f);					//左上
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.0f);			//右上
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.5f);					//左上
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.5f);			//右下
			}
			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
			break;
		case 1:			//右向いて歩いている
			g_aPlayer.nCounterAnim++;
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			if ((g_aPlayer.nCounterAnim % 5) == 0)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.5f);					//左上
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.5f);			//右上
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 1.0f);					//左上
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 1.0f);			//右下
			}
			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
			break;
		case 3:			//左向
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);			//左上
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);			//右上
			pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);			//左上
			pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);			//右下
			g_aPlayer.DirectMove = 0;
			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
			break;
		case 4:			//右向
				// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);			//左上
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);			//右上
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);			//左上
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);			//右下
			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
			g_aPlayer.DirectMove = 1;
			break;
		}
		g_aPlayer.move.y += 0.75;				//重力

		g_aPlayer.pos.x += g_aPlayer.move.x;	//横移動
		g_aPlayer.pos.y += g_aPlayer.move.y;	//落下

		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*0.425f;
		//g_aPlayer.move.y += (0.0f - g_aPlayer.move.y)*0.625f;

		if (CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight) == true)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				g_aPlayer.move.y -= 15;			 //ジャンプ力
			}
		}

		CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionItem(&g_aPlayer.pos, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionSwitch(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionTrap(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight); //ブロックとの判定処理


		// 頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//左上
		pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//右上
		pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//左上
		pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//右下
		//頂点バッファアンロックする
		g_pVtxBuffPlayer->Unlock();
	}

}
//=============================================================================
//描画処理ポリゴン
//=============================================================================pp
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer,0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テェクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);
	if (g_aPlayer.bDisp == true)
	{
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=============================================================================
//プレイヤー設定
//=============================================================================
void SetPlayer(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.bDisp == false)				//プレイヤーが使用されていない
	{
		g_aPlayer.pos = pos;					//位置
		g_aPlayer.state = PLAYERSTATE_NOMAL;
		g_aPlayer.nType = nType;				//タイプ
		g_aPlayer.nCounterState = 0;			//プレイヤーのライフ設定
		g_aPlayer.nLife = 10;					//体力
		g_aPlayer.bDisp = true;					//プレイヤーが使用されている

		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//左上
		pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//右上
		pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//左上
		pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//右下

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
	g_aPlayer.nLife -= nDamage;

	if (g_aPlayer.nLife <= 0)
	{//プレイヤーの体力が0以下になったとき
		SetExplosion(g_aPlayer.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		g_aPlayer.state = PLAYERSTATE_DEATH;
		g_aPlayer.nCounterState = 60;				//ダメージ状態時間
		g_aPlayer.bDisp = false;
	}
	else
	{
		g_aPlayer.state = PLAYERSTATE_DAMAGE;
		g_aPlayer.nCounterState = 15;				//ダメージ状態時間

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
PLAYER *GetPlayer(void)
{
	return &g_aPlayer;
}



