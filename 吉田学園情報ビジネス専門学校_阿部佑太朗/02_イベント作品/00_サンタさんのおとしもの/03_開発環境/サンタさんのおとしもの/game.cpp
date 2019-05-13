//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "input.h"
#include "pause.h"
#include "pauseselect.h"
#include "pauselogo.h"
#include "rankingscore.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include "explosion.h"
#include "bullet.h"
#include "item.h"
#include "human.h"
#include "demandpresent.h"
#include "frame.h"
#include "score.h"
#include "timer.h"
#include "bg2.h"
#include "getscore.h"
#include "bg3.h"
#include "crow.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	ITEMTYPE itemtype;
}ItemInfo;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void GameScene(void);

//=============================================================================
// グローバル変数宣言
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // ゲームの状態
int       g_nCounterGameState;            // ゲームの状態管理カウンター
bool      g_bPuase;                       // ポーズ中かどうか
int       g_GameCounter;                  // ゲームの進行管理カウンター

ItemInfo g_ItemInfo[] =
{// アイテムの配置情報
	{ D3DXVECTOR3(250.0f,200.0f,0.0f),ITEMTYPE_COIN},
	{ D3DXVECTOR3(1050.0f,200.0f,0.0f),ITEMTYPE_MIKIYA}
};

//=============================================================================
// ゲーム画面初期化処理
//=============================================================================
void InitGame(void)
{

	//初期化処理背景
	InitBG2();

	//初期化処理背景
	InitBG3();

	// プレイヤーの初期化処理
	InitPlayer();

	// 人間の初期化処理
	InitHuman();

	//カラスの初期化処理
	InitCrow();

	// 弾の初期化処理
	InitBullet();

	//アイテムの初期化処理
	InitItem();

	// 爆発の初期化処理
	InitExplosion();

	// 欲しいプレゼント表示の初期化処理
	InitDemandPresent();

	// エフェクトの初期化処理
	InitEffect();

	// フレームの初期化処理
	InitFrame();

	// タイマーの初期化処理
	InitTimer();

	// スコアの初期化処理
	InitScore();

	// ゲットスコアの初期化処理
	InitGetScore();

	// ポーズ初期化処理
	InitPause();

	// ポーズロゴ初期化処理
	InitPauseLogo();

	// ポーズ項目初期化処理
	InitPauseSelect();

	for (int nCntItem = 0; nCntItem < sizeof g_ItemInfo / sizeof(ItemInfo); nCntItem++)
	{// 配置するアイテムの数だけ繰り返し
		SetItem(g_ItemInfo[nCntItem].pos, g_ItemInfo[nCntItem].itemtype);
	}

	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
	g_GameCounter = 0;
}
//=============================================================================
// ゲーム画面終了処理
//=============================================================================
void UninitGame(void)
{
	//終了処理背景
	UninitBG2();

	//終了処理背景
	UninitBG3();

	// プレイヤーの終了処理
	UninitPlayer();

	// 人間の終了処理
	UninitHuman();

	//カラスの終了処理
	UninitCrow();

	// 弾の終了処理
	UninitBullet();

	// アイテムの終了処理
	UninitItem();

	// 爆発の終了処理
	UninitExplosion();

	// 欲しいプレゼント表示の終了処理
	UninitDemandPresent();

	// エフェクトの終了処理
	UninitEffect();

	// フレームの終了処理
	UninitFrame();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	// ゲットスコアの終了処理
	UninitGetScore();

	// ポーズ終了処理
	UninitPause();

	// ポーズロゴ終了処理
	UninitPauseLogo();

	// ポーズ項目終了処理
	UninitPauseSelect();
}
//=============================================================================
// ゲーム画面更新処理
//=============================================================================
void UpdateGame(void)
{
	FADE fade;
	fade = *GetFade();

	if (GetJoyPadTrigger(DIJS_BUTTON_9) == TRUE && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL || GetKeyboardTrigger(DIK_P) == true && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL)
	{// ポーズON/OFF
		g_bPuase = g_bPuase ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSEOPEN);
	}

	if (g_bPuase == false)
	{// ポーズOFF
		g_GameCounter++;

		//更新処理背景
		UpdateBG2();

		//終了処理背景
		UpdateBG3();

		// プレイヤーの更新処理
		UpdatePlayer();

		// 弾の更新処理
		UpdateBullet();

		// アイテムの更新処理
		UpdateItem();

		// 人間の更新処理
		UpdateHuman();

		//カラスの更新処理
		UpdateCrow();

		// 爆発の更新処理
		UpdateExplosion();

		// 欲しいプレゼント表示の更新処理
		UpdateDemandPresent();

		// エフェクトの更新処理
		UpdateEffect();

		// フレームの更新処理
		UpdateFrame();

		// タイマーの更新処理
		UpdateTimer();

		// スコアの更新処理
		UpdateScore();

		// ゲットスコアの更新処理
		UpdateGetScore();

		// 人間の配置
		GameScene();

#ifdef _DEBUG
		//if (GetKeyboardTrigger(DIK_RETURN) && g_GameState == GAMESTATE_NORMAL)
		//{// デバック用
		//	g_GameState = GAMESTATE_END;
		//}
#endif

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // 通常状態
			break;

		case GAMESTATE_RETRY:   // やり直し状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// 一定時間たったら

				g_GameState = GAMESTATE_NONE_RETRY;
				SetFade(MODE_GAME);

			}
			break;

		case GAMESTATE_END:     //終了状態
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// 一定時間たったら
				g_GameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);

			}
			break;
		}
	}
	else
	{
		// ポーズ更新処理
		UpdatePause();

		// ポーズロゴ更新処理
		UpdatePauseLogo();

		// ポーズ項目更新処理
		UpdatePauseSelect();

		if (GetJoyPadTrigger(DIJS_BUTTON_2) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// 決定ボタンが押された
			RESTART restart;
			restart = GetRestart();
			FADE fade;
			fade = *GetFade();

			if (fade == FADE_NONE)
			{// フェード状態でない
				switch (restart)
				{
				case RESTART_CONTINUE:  // ゲーム再開
					break;
				case RESTART_RETRY:     // ゲームやり直し
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_GAME);
					return; // これ以上ゲームはUpdateしない
					break;
				case RESTART_QUIT:      // タイトル遷移
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_TITLE);
					return; // これ以上ゲームはUpdateしない
					break;
				}
				g_bPuase = g_bPuase ? false : true; // ポーズは解除
			}
		}
	}
}
//=============================================================================
// ゲーム画面描画処理
//=============================================================================
void DrawGame(void)
{
	//描画処理背景
	DrawBG3();

	//描画処理背景
	DrawBG2();

	// アイテムの描画処理
	DrawItem();

	// 爆発の描画処理
	DrawExplosion();

	// プレイヤーの描画処理
	DrawPlayer();

	// 人間の描画処理
	DrawHuman();

	//カラスの描画処理
	DrawCrow();

	// 欲しいプレゼントの描画処理
	DrawDemandPresent();

	// 弾の描画処理
	DrawBullet();

	// エフェクトの描画処理
	DrawEffect();

	// フレームの描画処理
	DrawFrame();

	// タイマーの描画処理
	DrawTimer();

	// スコアの描画処理
	DrawScore();

	// ゲットスコアの描画処理
	DrawGetScore();

	if (g_bPuase == true)
	{// ポーズ中なら
		// ポーズ描画処理
		DrawPause();

		// ポーズロゴ描画処理
		DrawPauseLogo();

		// ポーズ項目描画処理
		DrawPauseSelect();
	}
}
//=============================================================================
// ゲーム画面設定処理
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// ゲーム画面取得処理
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// 人間の配置処理
//=============================================================================
void GameScene(void)
{
	if (g_GameCounter % 150 == 0)
	{
		// 人間の配置
		SetHuman();
	}
}