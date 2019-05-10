//=============================================================================
//
// セレクト画面処理 [select.h]
// Author :
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "select.h"
#include "select2D.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//=============================================================================
// セレクト画面の初期化処理
//=============================================================================
void InitSelect(void)
{
	// 背景の初期化処理
	InitBG();
	// セレクトの初期化処理
	InitSelect2D();
}

//=============================================================================
// セレクト画面の終了処理
//=============================================================================
void UninitSelect(void)
{
	// 背景の終了処理
	UninitBG();
	// セレクトの終了処理
	UninitSelect2D();
}

//=============================================================================
// セレクト画面の更新処理
//=============================================================================
void UpdateSelect(void)
{
	// 背景の更新
	UpdateBG();

	// セレクトの更新
	UpdateSelect2D();

	FADE fade;
	fade = GetFade();

	SELECTTYPE SelectType;
	SelectType = GetSelectType();
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
	{
		if (fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			switch (SelectType)
			{
			case SELECT_BATTLE:
				//モード設定
				SetFade(MODE_GAME);
				break;
			case SELECT_RULE:
				//モード設定
				SetFade(MODE_RULE);
				break;
			case SELECT_CREDIT:
				//モード設定
				SetFade(MODE_CREDIT);
				break;
			case SELECT_RETURN:
				//モード設定
				StopSound(SOUND_LABEL_SELECT_BGM);
				SetFade(MODE_TITLE);
				break;
			}
		}
	}
}

//=============================================================================
// セレクト画面の描画処理
//=============================================================================
void DrawSelect(void)
{
	// 背景の描画処理
	DrawBG();
	// セレクトの描画処理
	DrawSelect2D();
}
