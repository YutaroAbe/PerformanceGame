//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "tutorial.h"
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
#include "explosion.h"
#include "life.h"
#include "nlife.h"
#include "tagu.h"

//*****************************************************************************
//ブロックの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfoTUTO;
//*****************************************************************************
//グローバル変数
//*****************************************************************************
TUTOSTATE g_TutorialState = TUTOSTATE_NONE; //ゲーム状態
bool g_tPause;		//ポーズ
int g_nCounterTutorialState;	//状態管理カウンター
BlockInfoTUTO g_aBlockInfoTUTO[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//初期化処理
//=============================================================================
void InitTutorial(void)
{
	//初期化処理バックグラウンド
	InitBG();
	//初期化処理ポーズ
	//InitPause();
	//初期化処理タグ
	//InitTagu();
	//初期化タイム
	//InitTime();
	//初期化スコア
	//InitScore();
	//初期化爆発
	InitExplosion();
	//初期化ライフ
	//InitLife();
	//初期化アイテム
	InitItem();
	//初期化処理スイッチ
	InitSwitch();
	//初期化処理プレイヤー
	InitPlayer();
	//初期化処理エネミー
	//InitEnemy();
	//初期化処理ブロック
	InitBlock();

	//セットゲーム
	SetTutorial();
	
	g_TutorialState = TUTOSTATE_NONE;	//通常状態に設定
	g_nCounterTutorialState = 0;

	g_tPause = false;			//ポーズしてない
}
//=============================================================================
//終了処理
//=============================================================================
void UninitTutorial(void)
{
		//終了処理バックグラウンド
		UninitBG();
		//終了処理ポーズ
	//	UninitPause();
		//終了処理タグ
		//UninitTagu();
		//終了処理タイム
		//UninitTime();
		//終了処理スコア
		//UninitScore();
		//終了処理爆発
		UninitExplosion();
		//終了処理アイテム
		UninitItem();
		//終了処理スイッチ
		UninitSwitch();
		//終了処理プレイヤー
		UninitPlayer();
		//終了処理エネミー
		//UninitEnemy();
		//終了処理ブロック
		UninitBlock();
}
//=============================================================================
//更新処理
//=============================================================================
void UpdateTutorial(void)
{
		//更新処理バックグラウンド
		UpdateBG();
		//更新処理タグ
		//UpdateTagu();
		//更新処理タイム
		//UpdateTime();
		//更新処理スコア
		//UpdateScore();
		//更新処理爆発
		UpdateExplosion();
		//更新処理ライフ
		//UpdateLife();
		//更新処理スイッチ
		UpdateSwitch();
		//更新処理アイテム
		UpdateItem();
		//更新処理エネミー
		//UpdateEnemy();
		//更新処理プレイヤー
		UpdatePlayer();
		//更新処理ブロック
		UpdateBlock();
		switch (g_TutorialState)
		{
		case TUTOSTATE_NORMAL:			//ゲーム通常時
			g_nCounterTutorialState--;
			AddTime(g_nCounterTutorialState <= 60);

			break;
		case TUTOSTATE_END:					//ゲーム終了時
			g_nCounterTutorialState++;
			if (g_nCounterTutorialState >= 20) //死んだときの余韻
			{
				g_TutorialState = TUTOSTATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_TUTO);
			}
			break;
		case TUTOSTATE_CLEAR://クリア状態
			g_nCounterTutorialState++;
			if (g_nCounterTutorialState >= 20) //死んだときの余韻
			{
				g_TutorialState = TUTOSTATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
		}
}
//=============================================================================
//描画処理
//=============================================================================
void DrawTutorial(void)
{
	//描画処理バックグラウンド
	DrawBG();
	//描画処理タグ
	//DrawTagu();
	//描画処理タイム
	//DrawTime();
	//描画処理スコア
	//DrawScore();
	//描画処理爆発
	DrawExplosion();
	//描画処理ライフ
	//DrawLife();
	//描画処理アイテム
	DrawItem();
	//描画処理プレイヤー
	DrawPlayer();
	//描画処理スイッチ
	DrawSwitch();
	//描画処理エネミー
	//DrawEnemy();
	//描画処理ブロック
	DrawBlock();
}
void SetTutoState(TUTOSTATE state)
{
	g_TutorialState = state;
	g_nCounterTutorialState = 0;
}
TUTOSTATE GetTutoState(void)
{
	return g_TutorialState;
}
void SetTutorial(void)
{
	
	//右へ進みください表示
	SetBlock(D3DXVECTOR3(0, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 605.0f, 18);
	//WASD看板
	SetBlock(D3DXVECTOR3(800, -100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 19);
	//SPACE看板
	SetBlock(D3DXVECTOR3(1200, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 20);
	//スイッチ看板
	SetBlock(D3DXVECTOR3(1600, -100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 21);
	//SWITCH
	SetSwitch(D3DXVECTOR3(1800, 620.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 7);
	//NキーでUP
	SetBlock(D3DXVECTOR3(2505, 570.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 45.0f, 80.0f, 11);
	//スイッチ看板
	SetBlock(D3DXVECTOR3(2000, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 22);
	//ポーズ看板
	SetBlock(D3DXVECTOR3(650, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, 23);
	//敵説明
	SetBlock(D3DXVECTOR3(2605, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 28);
	//ライフ説明
	SetBlock(D3DXVECTOR3(2755, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 29);
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfoTUTO / sizeof(BlockInfoTUTO); nCountBlock++)
	{
		//壁
		SetBlock(D3DXVECTOR3(500, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 1);
		SetBlock(D3DXVECTOR3(500, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 1);		
		SetBlock(D3DXVECTOR3(-100, 680.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2500, 0.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 580.0f, 1);
		SetBlock(D3DXVECTOR3(2550, 560, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 20.0f, 1);
		SetBlock(D3DXVECTOR3(2750, 560, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 120.0f, 1);
		SetBlock(D3DXVECTOR3(2700, 600, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 80.0f, 14);
	}
	
	//セレクト画面へ---------------------------------------------------------------------------
	SetBlock(D3DXVECTOR3(4150, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 60.0f, 14);
	
}