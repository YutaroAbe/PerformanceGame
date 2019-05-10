//=============================================================================
//
// アクションゲーム処理 [GAME2.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game2.h"
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
#include "frontBG.h"

//*****************************************************************************
//ブロックの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfo2;
//*****************************************************************************
//グローバル変数
//*****************************************************************************
GAME2STATE g_GAME2State = GAME2STATE_NONE; //ゲーム状態
bool g_bPause2;		//ポーズ
int g_CounterGAME2State;	//状態管理カウンター
int g_nSwich2Counter;	//状態管理カウンター
int g_nSwich2Counter2;	//状態管理カウンター

BlockInfo2 g_aBlockInfo2[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//初期化処理
//=============================================================================
void InitGame2(void)
{
	//初期化処理フロントBG
	InitFrontBG();
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
	
	SetItem(2, D3DXVECTOR3(3200.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetItem(2, D3DXVECTOR3(3600.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//セットエネミー
	SetEnemy(1, D3DXVECTOR3(3800.0f, 160.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3900.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);

	//セットゲーム
	SetGAME2();
	g_GAME2State = GAME2STATE0_NORMAL;	//通常状態に設定
	g_CounterGAME2State = 0;
	g_nSwich2Counter = 0;
	g_nSwich2Counter2 = 0;	//状態管理カウンター
	 
	g_bPause2 = false;			//ポーズしてない
}
//=============================================================================
//終了処理
//=============================================================================
void UninitGame2(void)
{
	//終了処理フロントBG
	UninitFrontBG();
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
void UpdateGame2(void)
{
	Switch *pSwitch;
	pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズの設定ボタン「P」
		PaauseGame2();
	}
	if (g_bPause2 == false)
	{
		//更新処理フロントBG
		UpdateFrontBG();
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
		
		switch (g_GAME2State)
		{
		case  GAME2STATE0_NORMAL:			//ゲーム通常時
			g_CounterGAME2State--;
			AddTime(g_CounterGAME2State <= 60);

			break;
		case GAME2STATE_END:					//ゲーム終了時
			g_CounterGAME2State++;
			if (g_CounterGAME2State >= 20) //死んだときの余韻
			{
				g_GAME2State = GAME2STATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		case GAME2STATE_CLEAR://クリア状態
			g_CounterGAME2State++;
			if (g_CounterGAME2State >= 20) //死んだときの余韻
			{
				g_GAME2State = GAME2STATE_NONE;
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
void DrawGame2(void)
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
	//描画処理フロントBG
	DrawFrontBG();
	if (g_bPause2 == true)
	{
		//描画処理ポーズ
		DrawPause();

	}
}
void SetGemeState2(GAME2STATE state)
{
	g_GAME2State = state;
	g_CounterGAME2State = 0;
}
GAME2STATE GetGAME2State(void)
{
	return g_GAME2State;
}
void PaauseGame2(void)
{
	g_bPause2 = g_bPause2 ^ 1;
}
void SetGAME2(void)
{
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo2 / sizeof(BlockInfo2); nCountBlock++)
	{
		//壁
		SetBlock(D3DXVECTOR3(-100, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(1100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20, 1);
		//床
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2950, 350.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1500.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6300.0f, 30.0f, 17);
		SetBlock(D3DXVECTOR3(1300, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 430.0f, 16);
		SetBlock(D3DXVECTOR3(1480, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 500.0f, 16);
	}
	for (int nCut = 0; nCut < 4; nCut++)
	{
		//草フロントBG
		SetFrontBG(1, D3DXVECTOR3(3300 + (nCut * 300.0f), 120, 0), 20, 80);
		SetFrontBG(0, D3DXVECTOR3(3100 + (nCut * 300.0f), 330.0f, 0), 20, 100);
	}
	for (int nCut = 0; nCut < 8; nCut++)
	{
		//針金
		SetTrap(D3DXVECTOR3(1350, 230.0f + (nCut * 50.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 50.0f, 0);
	}
	for (int nCut = 0; nCut < 8; nCut++)
	{
		//針金
		SetTrap(D3DXVECTOR3(1450, 100.0f + (nCut * 50.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 50.0f, 0);
	}
	for (int nCut = 0; nCut < 3; nCut++)
	{
		//上乗ったらfalse
		SetBlock(D3DXVECTOR3(1400, 250 + (nCut * 150.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 25.0f, 4);
	}
	for (int nCut = 0; nCut < 6; nCut++)
	{
		//ベルトコンベア
		SetBlock(D3DXVECTOR3(1600 + (nCut * 150.0f), 620, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 25.0f, 6);
	}
	//空中床
	SetBlock(D3DXVECTOR3(1550, 390, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1790, 250, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1690, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1980, 380, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	//針金
	SetTrap(D3DXVECTOR3(1710, 300, 0), D3DXVECTOR3(0.0f, 0.3f, 0.0f), 35.0f, 50.0f, 3);
	//トランポリン
	SetBlock(D3DXVECTOR3(1990, 340, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f,40.0f, 7);

	SetBlock(D3DXVECTOR3(1100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 40, 1);

	SetBlock(D3DXVECTOR3(2100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 40, 1);
	SetItem(2, D3DXVECTOR3(1630, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetYajirusi(0, D3DXVECTOR3(2250, 160, 0));
	SetSwitch(D3DXVECTOR3(2250, 180, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 13);
	SetSwitch(D3DXVECTOR3(1530, 160.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 15);

	SetBlock(D3DXVECTOR3(1000, 500, 0), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(1000, 300, 0), D3DXVECTOR3(0.0f, 0.6f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(1150, 350, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 40.0f, 3);
	for (int nCut = 0; nCut < 7; nCut++)
	{//階段
		SetBlock(D3DXVECTOR3(4450 + (nCut * 50.0f), 350.0f - (nCut * 30.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
	}
	SetBlock(D3DXVECTOR3(3100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 230.0f, 16);
	//Nキー押したら上に上がるやつ
	SetBlock(D3DXVECTOR3(3100, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 30);
	SetBlock(D3DXVECTOR3(4800, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20.0f, 1);
	SetBlock(D3DXVECTOR3(4950, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 80.0f, 1);
	SetItem(4, D3DXVECTOR3(4750.0f, 130, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBlock(D3DXVECTOR3(4900, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 80.0f, 27);
}