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
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "time.h"
#include "Pause.h"
#include "ranking.h"
#include "score.h"
#include "door.h"
#include "fade.h"
#include "frontbg.h"

//=============================================================================
//グローバル変数
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;	//ゲーム状態
int g_nCounterGameState;	//状態管理カウンター
int g_nGameCounter;
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
	//InitEffect();
	//初期化処理エネミー
	InitEnemy();
	InitDoor();
	//初期化処理スコア
	InitScore();
	//初期化処理タイム
	InitTime();
	//初期化処理プレイヤー
	InitPlayer();
	//
	InitFRONTBG();

	SetDoor(D3DXVECTOR3(100.0f, 270.0f, 0.0f),0);
	SetDoor(D3DXVECTOR3(100.0f, 467.0f, 0.0f), 1);
	SetDoor(D3DXVECTOR3(100.0f, 670.0f, 0.0f), 2);

	g_GameState = GAMESTATE0_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_aCounterGame = 0;

	Enemy *pEnemy;
	pEnemy = GetEnemy();

	pEnemy->state = ENEMYSTATE_NOMAL;
	g_nGameCounter = 0;
	g_bPause = false;			//ポーズしてない

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGAME(void)
{
	//	//終了処理ポーズ
	UninitPause();
	//	// 終了処理バックグラウンド
	UninitBG();
	//	//終了処理バレット
	UninitBullet();
	//	// 終了処理エクスプロージョン
	UninitExplosion();
	//	//終了処理エフェクト
	//	UninitEffect();
	//	// 終了処理エネミー
	UninitEnemy();
	//	// 終了処理スコア
	UninitScore();
	UninitDoor();
	//	//終了処理タイム
	UninitTime();
	//	// 終了処理プレイヤー
	UninitPlayer();
	UninitFRONTBG();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGAME(void)
{

	//エンターでモードエンターに移行
	FADE pFade = *GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズの設定ボタン「P」
		PaauseGame();
	}
	if (g_bPause == false)
	{
		//// 更新処理バックグラウンド
		UpdateBG();
		//// 更新処理バレット
		UpdateBullet();
		//// 更新処理エクスプロージョン
		UpdateExplosion();
		////更新処理エフェクト
		//UpdateEffect();
		//// 更新処理エネミー
		UpdateEnemy();
		//// 更新処理スコア
		UpdateScore();
		UpdateDoor();
		////更新処理タイム
		UpdateTime();
		// 更新処理プレイヤー
		UpdatePlayer();
		UpdateFRONTBG();


		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//ゲーム通常時
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);
			g_aCounterGame++;	//エネミーが出てくるカウンター
			SetEnemyGame();		//エネミーセット

			break;
		case GAMESTATE_END:					//ゲーム終了時
			g_nGameCounter++;
			if (g_nGameCounter >= 60) //死んだときの余韻
			{
				g_GameState = GAMESTATE_NONE;
				//SetRankScore(GetScore());
				if (pFade == FADE_NONE)
				{
					//画面(モード)の設定
					SetFade(MODE_RANKING);
				}
			}
			break;
		case GAMESTATE_CLEAR://クリア状態
			g_nGameCounter++;
			if (g_nGameCounter >= 60) //死んだときの余韻
			{
				g_GameState = GAMESTATE_NONE;
				//SetRankScore(GetScore());
				//画面(モード)の設定
				//SetFade(MODE_RANKING);
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
		////描画処理バックグラウンド
		DrawBG();
		////描画処理バレット
		DrawBullet();
		//// 描画処理エクスプロージョン
		DrawExplosion();
		////描画処理エフェクト
		//DrawEffect();
		//// 描画処理エネミー
		DrawEnemy();
		//// 描画処理スコア
		DrawScore();
		DrawDoor();
		////描画処理タイム
		DrawTime();
		//描画処理プレイヤー
		DrawPlayer();
		DrawFRONTBG();

		if (g_bPause == true)
		{
			//描画処理ポーズ
			DrawPause();

		}
}
void SetGemeState(GAMESTATE state)
{
	g_GameState = state;
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

	if ((g_aCounterGame % (rand() % 180 + (rand() % 30 + 60))) == 0)
	{
		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 180 + (rand() % 25 + 60))) == 0)
	{
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}

	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	レーン[1]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	レーン[2]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	レーン[3]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
}
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}
int GetGameCounter(void)
{
	return g_nCounterGameState;
}