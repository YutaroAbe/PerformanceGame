//=============================================================================
//
// メイン処理 [main.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "sideenemy.h"
#include "score.h"
#include "tbossenemy.h"
#include "effect.h"
#include "fade.h"
#include "time.h"
#include "life.h"
#include "nlife.h"
#include "Pause.h"
#include "ranking.h"
#include "score.h"

//=============================================================================
//グローバル変数
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;	//ゲーム状態
int g_nCounterGameState;	//状態管理カウンター
bool g_bPause;		//ポーズ
int g_aCounterGame;

//=============================================================================
// 初期化処理
//=============================================================================
void InitGAME(void)
{
	//初期化処理ポーズ
	InitPause();
	//初期化処理バックグラウンド
	InitBG();
	//初期化処理バレット
	InitBullet();
	//初期化処理エクスプロージョン
	InitExplosion();
	//初期化処理エフェクト
	InitEffect();
	//初期化処理エネミー
	InitEnemy();
	//初期化処理サイドエネミー
	InitSideEnemy();
	//初期化処理中ボスエネミー
	InitTBossEnemy();
	//初期化処理スコア
	InitScore();
	//初期化処理タイム
	InitTime();
	//初期化処理ライフ外付け処理
	InitNlife();
	//初期化処理ライフ
	InitLife();
	//初期化処理プレイヤー
	InitPlayer();

	//大砲
	SetSideEnemy(D3DXVECTOR3(105, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(305, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(505, 693, 0.0f),0);
	SetSideEnemy(D3DXVECTOR3(705, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(905, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(1105, 693, 0.0f), 0);

	g_GameState = GAMESTATE0_NORMAL;	//	通常状態に設定
	g_nCounterGameState = 0;			//	カウンターステートの初期化
	g_aCounterGame = 0;					//	ゲームのカウントの初期化
	Enemy *pEnemy;
	pEnemy = GetEnemy();				//	敵の取得
	pEnemy->state = ENEMYSTATE_NOMAL;	//	通常のステータス
	g_bPause = false;					//	ポーズしてない

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGAME(void)
{
	//終了処理ポーズ
	UninitPause();
	// 終了処理バックグラウンド
	UninitBG();
	//終了処理バレット
	UninitBullet();
	// 終了処理エクスプロージョン
	UninitExplosion();
	//終了処理エフェクト
	UninitEffect();
	// 終了処理エネミー
	UninitEnemy();
	// 終了処理サイドエネミー
	UninitSideEnemy();
	//終了処理中ボスエネミー
	UninitTBossEnemy();
	// 終了処理スコア
	UninitScore();
	//終了処理タイム
	UninitTime();
	//終了処理ライフ外付け処理
	UninitNlife();
	//終了処理ライフ
	UninitLife();
	// 終了処理プレイヤー
	UninitPlayer();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGAME(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズの設定ボタン「P」
		PaauseGame();
	}
	if (g_bPause == false)
	{
		// 更新処理バックグラウンド
		UpdateBG();
		// 更新処理バレット
		UpdateBullet();
		// 更新処理エクスプロージョン
		UpdateExplosion();
		//更新処理エフェクト
		UpdateEffect();
		// 更新処理エネミー
		UpdateEnemy();
		// 更新処理サイドエネミー
		UpdateSideEnemy();
		//更新処理中ボスエネミー
		UpdateTBossEnemy();
		// 更新処理スコア
		UpdateScore();
		//更新処理タイム
		UpdateTime();
		//更新処理ライフ外付け処理
		UpdateNlife();
		//更新処理ライフ
		UpdateLife();
		// 更新処理プレイヤー
		UpdatePlayer();

		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//	ゲーム通常時
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);
			g_aCounterGame++;	//	エネミーが出てくるカウンター
			SetEnemyGame();		//	エネミーセット

			break;
		case GAMESTATE_END:					//	ゲーム終了時
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20)
			{//	死んだときの余韻
				g_GameState = GAMESTATE_NONE;
				SetRankScore(GetScore());
				//	画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		case GAMESTATE_CLEAR:				//	クリア状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20)
			{//死んだときの余韻
				g_GameState = GAMESTATE_NONE;
				SetRankScore(GetScore());
				//画面(モード)の設定
				SetFade(MODE_CLEAR);
			}
		}
	}
	else
	{
		//終了処理ポーズ
		UpdatePause();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGAME(void)
{
		//描画処理バックグラウンド
		DrawBG();
		//描画処理バレット
		DrawBullet();
		// 描画処理エクスプロージョン
		DrawExplosion();
		//描画処理エフェクト
		DrawEffect();
		// 描画処理エネミー
		DrawEnemy();
		// 描画処理サイドエネミー
		DrawSideEnemy();
		//描画処理中ボスエネミー
		DrawTBossEnemy();
		// 描画処理スコア
		DrawScore();
		//描画処理タイム
		DrawTime();
		//描画処理ライフ外付け処理
		DrawNlife();
		//描画処理ライフ
		DrawLife();
		//描画処理プレイヤー
		DrawPlayer();
		if (g_bPause == true)
		{
			//描画処理ポーズ
			DrawPause();

		}
}
void SetGemeState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
//エネミーセット（ゲームの流れ）
//=============================================================================
void SetEnemyGame(void)
{
	Enemy *pEnemy;
	pEnemy = GetEnemy();

	if (g_aCounterGame == 100)
	{
		SetEnemy(1, D3DXVECTOR3(1300, 600, 0.0f), D3DXVECTOR3(-3, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 500, 0.0f), D3DXVECTOR3(-2, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 200, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 150)
	{
		SetEnemy(1, D3DXVECTOR3(1300, 300, 0.0f), D3DXVECTOR3(-3, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 550, 0.0f), D3DXVECTOR3(-2, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 280, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 300)
	{
		SetEnemy(1, D3DXVECTOR3(1400, 600, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1400, 700, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 500)
	{
		SetEnemy(1, D3DXVECTOR3(700, 0, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 550)
	{
		SetEnemy(3, D3DXVECTOR3(700, 0, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 650)
	{
		SetEnemy(3, D3DXVECTOR3(1280, 0, 0.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1290, 0, 0.0f), D3DXVECTOR3(-1.2f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1300, 0, 0.0f), D3DXVECTOR3(-1.6f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1310, 0, 0.0f), D3DXVECTOR3(-1.8f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 780)
	{
		SetEnemy(2, D3DXVECTOR3(1280, 780, 0.0f), D3DXVECTOR3(-1.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1290, 780, 0.0f), D3DXVECTOR3(-1.2f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1300, 780, 0.0f), D3DXVECTOR3(-1.6f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1310, 780, 0.0f), D3DXVECTOR3(-1.8f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 800)
	{
		SetEnemy(1, D3DXVECTOR3(800, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(900, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1000, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 950)
	{
		SetEnemy(0, D3DXVECTOR3(1500, 430, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1450, 415, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1400, 400, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1350, 375, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3(1300, 350, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3(1350, 325, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1400, 300, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1450, 275, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1500, 250, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 1300)
	{
		SetTBossEnemy(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1);		//中ボス
	}
}
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}