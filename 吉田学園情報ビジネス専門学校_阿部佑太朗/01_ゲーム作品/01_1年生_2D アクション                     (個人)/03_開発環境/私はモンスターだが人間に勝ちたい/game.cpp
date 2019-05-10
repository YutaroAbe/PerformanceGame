//=============================================================================
//
// アクションゲーム処理 [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "Pause.h"
#include "block.h"
#include "bg.h"
#include "item.h"
#include "score.h"
#include "time.h"
#include "switch.h"
#include "enemy.h"
#include "life.h"
#include "nlife.h"
#include "tagu.h"
#include "trap.h"
#include "yajirusi.h"
#include "explosion.h"

//*****************************************************************************
//ブロックの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfo;
//*****************************************************************************
//グローバル変数
//*****************************************************************************
GAMESTATE g_GameState = GAMESTATE_NONE; //ゲーム状態
bool g_bPause;		//ポーズ
int g_nCounterGameState;	//状態管理カウンター
int g_nSwichCounter;	//状態管理カウンター
int g_nSwichCounter2;	//状態管理カウンター

BlockInfo g_aBlockInfo[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//初期化処理
//=============================================================================
void InitGame(void)
{
	//初期化処理ポーズ
	InitPause();
	//初期化処理タグ
	InitTagu();
	//初期化タイム
	InitTime();
	//初期化スコア
	InitScore();
	//初期化ライフ
	InitLife();
	//初期化爆発
	InitExplosion();
	//初期化トラップ
	InitTrap();
	//初期化アイテム
	InitItem();
	//初期化やじるし
	InitYajirusi();
	//初期化処理スイッチ
	InitSwitch();
	//初期化処理プレイヤー
	InitPlayer();
	//初期化処理エネミー
	InitEnemy();
	//初期化処理ブロック
	InitBlock();

	
	SetYajirusi(0, D3DXVECTOR3(1090, 150.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(3030.0f, 290.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(4080, 250.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(5850.0f, 360.0f, 0));

	SetSwitch(D3DXVECTOR3(1080, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 0);
	SetSwitch(D3DXVECTOR3(3030.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 2);
	SetSwitch(D3DXVECTOR3(4080, 260.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 9);
	SetSwitch(D3DXVECTOR3(5850.0f, 370.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 11);

	SetTrap(D3DXVECTOR3(1200, 500.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(1280, 240.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(1500, 150.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(900, 400.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);

	for(int nCountTrp = 0; nCountTrp < 9;nCountTrp++)
	{
		SetTrap(D3DXVECTOR3(5100.0f +(nCountTrp * 100), 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);

	}
	SetTrap(D3DXVECTOR3(4400, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4500, 190.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4600, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4700, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4800, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetEnemy(1, D3DXVECTOR3(1000.0f, 160.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(1800.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(2600.0f, 100.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3800.0f, 480.0f, 0), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), 30, 60, 2);
	//セットゲーム
	SetGame();

	g_GameState = GAMESTATE0_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_nSwichCounter = 0;
	g_nSwichCounter2 = 0;	//状態管理カウンター
	 

	g_bPause = false;			//ポーズしてない
}
//=============================================================================
//終了処理
//=============================================================================
void UninitGame(void)
{
	//終了処理ポーズ
	UninitPause();
	//終了処理タグ
	UninitTagu();
	//終了処理タイム
	UninitTime();
	//終了処理スコア
	UninitScore();
	//終了処理ライフ
	UninitLife();
	//終了処理爆発
	UninitExplosion();
	//終了処理トラップ
	UninitTrap();
	//終了処理アイテム
	UninitItem();
	//終了処理やじるし
	UninitYajirusi();
	//終了処理スイッチ
	UninitSwitch();
	//終了処理プレイヤー
	UninitPlayer();
	//終了処理エネミー
	UninitEnemy();
	//終了処理ブロック
	UninitBlock();
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateGame(void)
{//Switch *pSwitch;
	//pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズの設定ボタン「P」
		PaauseGame();
	}
	if (g_bPause == false)
	{
		//更新処理タグ
		UpdateTagu();
		//更新処理タイム
		UpdateTime();
		//更新処理スコア
		UpdateScore();
		//更新処理ライフ
		UpdateLife();
		//更新処理やじるし
		UpdateYajirusi();
		//更新処理スイッチ
		UpdateSwitch();
		//更新処理爆発
		UpdateExplosion();
		//更新処理トラップ
		UpdateTrap();
		//更新処理アイテム
		UpdateItem();
		//更新処理エネミー
		UpdateEnemy();
		//更新処理ブロック
		UpdateBlock();
		//更新処理プレイヤー
		UpdatePlayer();
		
		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//ゲーム通常時
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);

			break;
		case GAMESTATE_END:					//ゲーム終了時
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20) //死んだときの余韻
			{
				g_GameState = GAMESTATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		case GAMESTATE_CLEAR://クリア状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20) //死んだときの余韻
			{
				g_GameState = GAMESTATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
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
//描画処理
//=============================================================================
void DrawGame(void)
{
	//描画処理タグ
	DrawTagu();
	//描画処理タイム
	DrawTime();
	//描画処理スコア
	DrawScore();
	//描画処理ライフ
	DrawLife();
	//描画処理やじるし
	DrawYajirusi();
	//描画処理爆発
	DrawExplosion();
	//描画処理トラップ
	DrawTrap();
	//描画処理アイテム
	DrawItem();
	//描画処理プレイヤー
	DrawPlayer();
	//描画処理スイッチ
	DrawSwitch();
	//描画処理エネミー
	DrawEnemy();
	//描画処理ブロック
	DrawBlock();

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
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}
void SetGame(void)
{

	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCountBlock++)
	{
		//壁
		SetBlock(D3DXVECTOR3(-100, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(500, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 580.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(3050.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 16);
		SetBlock(D3DXVECTOR3(6150.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 700.0f, 16);
		SetBlock(D3DXVECTOR3(5850.0f, 400.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 700.0f, 16);
		//床
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1400.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(1950, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 400.0f, 16);
		SetBlock(D3DXVECTOR3(1900, 650, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 400.0f, 16);
		SetBlock(D3DXVECTOR3(2600, 610, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6300.0f, 30.0f, 17);
		SetBlock(D3DXVECTOR3(3900, 610, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(4900, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(5000, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 250.0f, 1);
	}
	for (int nCut = 0; nCut < 5; nCut++)
	{
		SetBlock(D3DXVECTOR3(800 + (nCut * 20.0f), 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1080 + (nCut * 40.0f), 250.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1200 + (nCut * 40.0f), 290.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1380 + (nCut * 40.0f), 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
	}
	//はてなブロック
	SetBlock(D3DXVECTOR3(900, 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 40.0f, 12);
	//ばね
	SetBlock(D3DXVECTOR3(2650, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	//ばね
	SetBlock(D3DXVECTOR3(1500, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	for (int nCut = 0; nCut < 2; nCut++)
	{
		//棘
		SetTrap(D3DXVECTOR3(2000 + (nCut * 30.0f), 450.0f + (nCut * 5.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 0);
	}
	//落ちる床
	SetBlock(D3DXVECTOR3(2450, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 2);
	SetBlock(D3DXVECTOR3(2535, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 2);
	//土管横から上
	SetBlock(D3DXVECTOR3(2400, 180, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 470.0f, 9);
	//雲左右
	SetBlock(D3DXVECTOR3(1350, 680, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, 10);
	//床
	SetBlock(D3DXVECTOR3(2650, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(2750, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(3000, 350.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	for (int nCut = 0; nCut < 3; nCut++)
	{
		//地面
		SetBlock(D3DXVECTOR3(2180, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2230, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2280, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2330, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 180, 1);
	}
	for (int nCut = 0; nCut < 3; nCut++)
	{
		SetBlock(D3DXVECTOR3(2750.0f + (nCut * 100.0f), 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	}
	SetBlock(D3DXVECTOR3(2598.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	SetBlock(D3DXVECTOR3(2175.0f, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	SetBlock(D3DXVECTOR3(2632.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	for (int nCut = 0; nCut < 4; nCut++)
	{
		SetBlock(D3DXVECTOR3(2600, 100.0f + (nCut * 100.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 100, 1);
	}
	SetBlock(D3DXVECTOR3(2750.0f, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	
	for (int nCut = 0; nCut < 2; nCut++)
	{
		//上に乗ったらfalse
		SetBlock(D3DXVECTOR3(2800 + (nCut * 100.0f), 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 4);
	}
	SetBlock(D3DXVECTOR3(3800, 500.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(3900, 280.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(4050, 280.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(4000, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	
	SetBlock(D3DXVECTOR3(4050, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	//ばね
	SetBlock(D3DXVECTOR3(4150, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	SetBlock(D3DXVECTOR3(4150, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
	//棘
	SetTrap(D3DXVECTOR3(4200, 320.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 0);
	//?ブロックハート
	SetBlock(D3DXVECTOR3(3950, 190, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 12);
	for (int nCut = 0; nCut < 20; nCut++)
	{
		//針金
		SetTrap(D3DXVECTOR3(3900 + (nCut * 50.0f), 600.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 10.0f, 1);
	}
	//針金
	SetTrap(D3DXVECTOR3(2900, 560.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	SetBlock(D3DXVECTOR3(4400, 400, 0), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(4600, 400, 0), D3DXVECTOR3(0.0f, 0.2f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(4800, 300, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 100.0f, 3);
	//Nキー押したら上に上がるやつ
	SetBlock(D3DXVECTOR3(5000, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 25);
	SetItem(4, D3DXVECTOR3(6050.0f, 130, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetItem(2, D3DXVECTOR3(3900.0f, 260, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ステージ2へ---------------------------------------------------------------------------
	SetBlock(D3DXVECTOR3(6100.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 60.0f, 26);
	SetBlock(D3DXVECTOR3(6000.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 20, 1);
	
}