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
#include "sideenemy.h"
#include "tbossenemy.h"
#include "effect.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define NCUT_ANIM_TIME (15)							//カウントアニメーション時間
#define NPAR_ANIM_TAIM (10)							//アニメーションパターン
#define POS_X (20)									//ポジション_X
#define POS_Y (20)									//ポジション_X
#define POLYGON_TEXTURENAMRE "data/TEXTURE/player000.png"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //頂点バッファのポイント
int g_nCounterAnim;									//アニメーションカウンター
int g_nPatternAnim;									//アニメーションパターンNo、
Player g_Player;
float g_Spin;

//=============================================================================
//初期化処理プレイヤー
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

	//各ｇ_変数初期化
	g_nCounterAnim= 0;							    //	カウンターを初期化する
	g_nPatternAnim = 0;							    //	パターン初期化する
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	位置
	g_Player.nCounterState = 0;						//	状態のカウンター
	g_Player.nLife = 10;							//	寿命
	g_Player.bDisp = true;							//	死亡状態
	g_Player.state = PLAYERSTATE_NOMAL;

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
	g_Player.pos = D3DXVECTOR3(35, 365, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			  //右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			  //左下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			  //右下
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
	//プレイヤーの画面の当たり判定
	if (g_Player.pos.y <= 25)
	{//画面上の当たり判定の設定
		g_Player.move.y = 1;
	}
	if (g_Player.pos.y >= 695)
	{//画面下の当たり判定の設定
		g_Player.move.y = -1;
	}
	if (g_Player.pos.x <= 25)
	{//画面下の当たり判定の設定
		g_Player.move.x = 1;
	}
	if (g_Player.pos.x >= 1245)
	{//画面右の当たり判定の設定
		g_Player.move.x = -1;
	}

	if (g_Player.bDisp == true)
	{
		MODE pMode;
		pMode = GetMode();
		if (pMode == MODE_GAME)
		{
			SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f), 13.0f, 10);
		}
	}
		//プレイヤーの状態による設定
		switch (g_Player.state)
		{
		case PLAYERSTATE_NOMAL:
			break;

		case PLAYERSTATE_DAMAGE:

			g_Player.nCounterState--;	//カウントダウン
			if (g_Player.nCounterState <= 0)
			{//	状態カウンターが0以下になった場合
				g_Player.state = PLAYERSTATE_NOMAL;			//	状態を通常状態

				VERTEX_2D*pVtx;								//頂点情報のポインタ

				// 頂点バッファをロックし、頂点データへのポインタ
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//	頂点バッファアンロックする
				g_pVtxBuffPlayer->Unlock();
			}
			break;

		case PLAYERSTATE_DEATH:
			//	カウントダウン
			g_Player.nCounterState--;
			if (g_Player.nCounterState <= 0)
			{//	状態カウンターが0以下になった場合
				SetGemeState(GAMESTATE_END);		//	リザルト画面に行く
				g_Player.state = PLAYERSTATE_END;
			}
			break;
		case PLAYERSTATE_END:

			break;
		}
		//	カウンター加算
		g_nCounterAnim++;

		if ((g_nCounterAnim %NCUT_ANIM_TIME) == 0)
		{
			g_nPatternAnim++;						//パターンNo,更新
			g_nPatternAnim = (g_nPatternAnim) % NPAR_ANIM_TAIM;//パターンを初期化に戻す
		}

		VERTEX_2D*pVtx;								//頂点情報のポインタ

		//移動設定=================================================================
		if (GetKeyboardPress(DIK_A) == true)
		{//任意のキー(Aキー)が押されたかどうか :左移動
			if (GetKeyboardPress(DIK_W) == true)
			{//左上移動
				g_Player.move.x += sinf(-D3DX_PI * 0.75f) *1.05f;
				g_Player.move.y += cosf(-D3DX_PI * 0.75f) *1.05f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左下移動
				g_Player.move.x += sinf(-D3DX_PI * 0.25f) *1.05f;
				g_Player.move.y += cosf(-D3DX_PI * 0.25f) *1.05f;
			}
			else
			{//左移動
				g_Player.move.x += sinf(-D3DX_PI * 0.5f) *1.05f;
			}
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//任意のキー(Dキー)が押されたかどうか　：右移動

			if (GetKeyboardPress(DIK_W) == true)
			{//右上移動
				g_Player.move.x += sinf(D3DX_PI * 0.75f) *1.05f;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) *1.05f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右下移動
				g_Player.move.x += sinf(D3DX_PI * 0.25f) *1.05f;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) *1.05f;
			}
			else
			{//右移動
				g_Player.move.x += sinf(D3DX_PI * 0.5f) *1.05f;
			}

			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//任意のキー(Wキー)が押されたかどうか
			g_Player.move.y -= 1.05f;						//プレイヤーの位置を上に移動

			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//	任意のキー(Sキー)が押されたかどうか
			g_Player.move.y += 1.05f;					  //プレイヤーの位置を下に移動

			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}

		//シフト+移動＝遅く移動する
		if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_D) == true)
		{//右遅くする

			if (GetKeyboardPress(DIK_W) == true)
			{//右上移動遅くする
				g_Player.move.x -= sinf(D3DX_PI * 0.75f) *0.5f;
				g_Player.move.y -= cosf(D3DX_PI * 0.75f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//右下移動遅くする
				g_Player.move.x -= sinf(D3DX_PI * 0.25f) *0.5f;
				g_Player.move.y -= cosf(D3DX_PI * 0.25f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//	プレイヤーの位置をに移動
				g_Player.move.x += 0.5f;
			}
			else
			{//	プレイヤーの位置を上に移動
				g_Player.move.x -= 0.5f;
			}
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_A) == true)
		{//左遅くする

			if (GetKeyboardPress(DIK_W) == true)
			{//左上移動遅くする
				g_Player.move.x -= sinf(-D3DX_PI * 0.75f) * 0.5f;
				g_Player.move.y -= cosf(-D3DX_PI * 0.75f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//左下移動遅くする
				g_Player.move.x -= sinf(-D3DX_PI * 0.25f) *0.5f;
				g_Player.move.y -= cosf(-D3DX_PI * 0.25f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				g_Player.move.x -= 0.5f;					//プレイヤーの位置をに移動
			}
			else
			{
				g_Player.move.x += 0.5f;					//プレイヤーの位置をに移動
			}
			// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_W) == true)
		{//上移動遅くする
			g_Player.move.y += 0.5f;						//プレイヤーの位置を上に移動

															// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_S) == true)
		{//下移動遅くする
			g_Player.move.y -= 0.5f;						//プレイヤーの位置を上に移動

															// 頂点バッファをロックし、頂点データへのポインタ
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点バッファアンロックする
			g_pVtxBuffPlayer->Unlock();
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		g_Player.move.x += (0.0f - g_Player.move.x)*0.075f;
		g_Player.move.y += (0.0f - g_Player.move.y)*0.075f;

		//	弾の設定===================================================================
		if (g_Player.bDisp == true)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//スペース押した場合の処理
				//(1)
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);			//	弾横
				SetBullet(g_Player.pos, D3DXVECTOR3(-8.0f, -0.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾左
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -2.0f, 0.0f), BULLETTYPE_PLAYER);			//	弾右上
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 2.0f, 0.0f), BULLETTYPE_PLAYER);			//	弾右下
			}

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//スペース押した場合の処理
				if (g_Player.nLife <= 2)
				{
					//(1)
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾横
					SetBullet(g_Player.pos, D3DXVECTOR3(-8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾右
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -2.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾上
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 2.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾右
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -4.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾左
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 4.0f, 0.0f), BULLETTYPE_PLAYER);		//	弾右
				}
			}
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//	スペース押した場合の処理
				PlaySound(SOUND_LABEL_SE_GUN);
			}
		}
		//	頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//	左上
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//	右上
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//	左下
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//	右下

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
			g_Player.nLife = 10;					//体力
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

			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

