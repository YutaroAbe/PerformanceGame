//=============================================================================
//
// アクションゲーム処理 [GAME2.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game3.h"
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
}BlockInfo3;
//*****************************************************************************
//グローバル変数
//*****************************************************************************
GAME3STATE g_GAME3State = GAME3STATE_NONE; //ゲーム状態
bool g_bPause3;		//ポーズ
int g_CounterGAME3State;	//状態管理カウンター
int g_nSwich3Counter;	//状態管理カウンター
int g_nSwich3Counter3;	//状態管理カウンター

BlockInfo3 g_aBlockInfo3[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//初期化処理
//=============================================================================
void InitGame3(void)
{
	//初期化処理バックグラウンド
	InitBG();
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
	SetItem(2, D3DXVECTOR3(4100.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//セットエネミー
	SetEnemy(1, D3DXVECTOR3(3800.0f, 160.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3900.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);
	//セットゲーム
	SetGAME3();
	g_GAME3State = GAME3STATE0_NORMAL;	//通常状態に設定
	g_CounterGAME3State = 0;
	g_nSwich3Counter = 0;
	g_nSwich3Counter3 = 0;	//状態管理カウンター
	 
	g_bPause3 = false;			//ポーズしてない
}
//=============================================================================
//終了処理
//=============================================================================
void UninitGame3(void)
{
	//終了処理バックグラウンド
	UninitBG();
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
void UpdateGame3(void)
{
	Switch *pSwitch;
	pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズの設定ボタン「P」
		
	}
	if (g_bPause3 == false)
	{
		//更新処理バックグラウンド
		UpdateBG();
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
		
		switch (g_GAME3State)
		{
		case  GAME3STATE0_NORMAL:			//ゲーム通常時
			g_CounterGAME3State--;
			AddTime(g_CounterGAME3State <= 60);

			break;
		case GAME3STATE_END:					//ゲーム終了時
			g_CounterGAME3State++;
			if (g_CounterGAME3State >= 20) //死んだときの余韻
			{
				g_GAME3State = GAME3STATE_NONE;
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		case GAME3STATE_CLEAR://クリア状態
			g_CounterGAME3State++;
			if (g_CounterGAME3State >= 20) //死んだときの余韻
			{
				g_GAME3State = GAME3STATE_NONE;
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
void DrawGame3(void)
{
	//描画処理バックグラウンド
	DrawBG();
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
	if (g_bPause3 == true)
	{
		//描画処理ポーズ
		DrawPause();

	}
	//描画処理フロントBG
	DrawFrontBG();
}
void SetGemeState3(GAME3STATE state)
{
	g_GAME3State = state;
	g_CounterGAME3State = 0;
}
GAME3STATE GetGAME3State(void)
{
	return g_GAME3State;
}
void SetGAME3(void)
{
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo3 / sizeof(BlockInfo3); nCountBlock++)
	{
		//壁
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		//床
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5000.0f, 300.0f, 0);
	}
	//doa
	SetBlock(D3DXVECTOR3(430, 565.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 80.0f, 27);
	//トランポリン
	SetBlock(D3DXVECTOR3(1900, 620, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, 7);
	SetBlock(D3DXVECTOR3(1400,70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 530.0f, 16);
	//Nキー押したら上に上がるやつ
	SetBlock(D3DXVECTOR3(1405, 600, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 32);
	
	SetBlock(D3DXVECTOR3(2000, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 250.0f, 34);

	SetBlock(D3DXVECTOR3(2050, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 150.0f, 1);
	SetBlock(D3DXVECTOR3(2055, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 50.0f, 35);
	SetBlock(D3DXVECTOR3(2050, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, 20.0f, 1);
	SetBlock(D3DXVECTOR3(2300, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 210.0f, 1);
}