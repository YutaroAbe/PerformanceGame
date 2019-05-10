//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "result.h"
#include "poker.h"
#include "battle.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "cardModel.h"
#include "ui.h"
#include "camera.h"
#include "gamefade.h"
#include "fade.h"
#include "light.h"
#include "PlayerShow.h"
#include "player.h"
#include "meshSphere.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"Fighting Poker"			// ウインドウのキャプション名
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
GAMEMODE g_GameMode = GAMEMODE_POKER;
int	g_nRoundCounter;	// ラウンド数のカウンター
//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	GAMEMODE g_GameMode = GAMEMODE_POKER;

	// ラウンド数の初期化
	g_nRoundCounter = 1;

	// フェードの設定
	InitGameFade(g_GameMode);
	// カメラの初期化処理
	InitCamera();
	// ライトの初期化処理
	InitLight();
	// メッシュスフィアの初期化処理
	InitMeshSphere();

	// プレイヤータイプデータの初期化
	InitPlayerTypeData();

	// モデル等読み込み
	LoadMotion();

	// メッシュキューブの生成
	MakeMeshSphere();

	// 初期HPSKILLのテキスト作成
	PlayerSaveHpSkillInit();

	//モードの設定
	SetGameMode(g_GameMode);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	//フェードの終了処理
	UninitGameFade();
	// ライトの終了処理
	UninitLight();
	// メッシュスフィアの終了処理
	UninitMeshSphere();

	// プレイヤータイプデータの終了処理
	UninitPlayerTypeData();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// ポーカーモード
		UpdatePoker();
		break;
	case GAMEMODE_PLAYERSHOW:	// プレイヤー表示モード
		UpdatePlayerShow();
		break;
	case GAMEMODE_BATTLE:		// バトルモード
		UpdateBattle();
		break;
	case GAMEMODE_RESULT:		// リザルトモード
		UpdateResult();
		break;
	}
	//フェードの更新
	UpdateGameFade();
	// カメラの更新処理
	UpdateCamera();
	// ライトの更新処理
	UpdateLight();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// ポーカーモード
		DrawPoker();
		break;
	case GAMEMODE_PLAYERSHOW:	// プレイヤー表示モード
		DrawPlayerShow();
		break;
	case GAMEMODE_BATTLE:		// バトルモード
		DrawBattle();
		break;
	case GAMEMODE_RESULT:		// リザルトモード
		DrawResult();
		break;
	}
	// フェードの描画
	DrawGameFade();
}
//=============================================================================
//ゲームモードの設定
//=============================================================================
void SetGameMode(GAMEMODE mode)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// ポーカーモード
		UninitPoker();
		StopSound(SOUND_LABEL_POKERTURN_BGM);
		break;
	case GAMEMODE_PLAYERSHOW:	// プレイヤー表示モード
		UninitPlayerShow();
		StopSound(SOUND_LABEL_CHARACTER_BGM);
		break;
	case GAMEMODE_BATTLE:		// バトルモード
		UninitBattle();
		if (g_nRoundCounter < 5)
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
		}
		else
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			StopSound(SOUND_LABEL_GAME_R5_BGM);
		}
		break;
	case GAMEMODE_RESULT:		// リザルトモード
		UninitResult();
		StopSound(SOUND_LABEL_RESULT_BGM);
		break;
	}

	// モードを代入
	g_GameMode = mode;

	switch (mode)
	{
	case GAMEMODE_POKER:		// ポーカーモード
		InitPoker();
		PlaySound(SOUND_LABEL_POKERTURN_BGM);
		SelectVolume(SOUND_LABEL_POKERTURN_BGM, 0.2f);
		break;
	case GAMEMODE_PLAYERSHOW:	// プレイヤー表示モード
		InitPlayerShow();
		PlaySound(SOUND_LABEL_CHARACTER_BGM);
		SelectVolume(SOUND_LABEL_CHARACTER_BGM, 0.2f);
		break;
	case GAMEMODE_BATTLE:		// バトルモード
		InitBattle();
		if (g_nRoundCounter < 5)
		{
			PlaySound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			SelectVolume(SOUND_LABEL_GAME_R1R2R3R4_BGM, 0.2f);
		}
		else
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			PlaySound(SOUND_LABEL_GAME_R5_BGM);
			SelectVolume(SOUND_LABEL_GAME_R5_BGM, 0.2f);
		}
		break;
	case GAMEMODE_RESULT:		// リザルトモード
		InitResult();
		PlaySound(SOUND_LABEL_RESULT_BGM);
		SelectVolume(SOUND_LABEL_RESULT_BGM, 0.2f);
		break;
	}
}
//=============================================================================
//ゲームモードの取得
//============================================================================
GAMEMODE GetGameMode(void)
{
	return g_GameMode;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ラウンド数増加処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddRoundCounter(void)
{
	// ラウンド数を一つ進める
	g_nRoundCounter++;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ラウンド数取得処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetRoundCounter(void)
{
	return g_nRoundCounter;
}