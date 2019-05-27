//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "ui.h"
#include "fade.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "shadow.h"
#include "bg.h"
#include "sound.h"
#include "gamepad.h"
//=============================================================================
// グローバル変数宣言
//=============================================================================
int g_nPlayBackWinnerCnt = 0;
//=============================================================================
// リザルトの初期化処理
//=============================================================================
void InitResult(void)
{
	g_nPlayBackWinnerCnt = 0;
	// 背景の初期化処理
	InitBG();

	// カメラの初期化
	InitCamera();

	// UIの初期化処理
	InitUI();

	// 影の初期化処理
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	// プレイヤーのステータス情報読み込み
	LoadPlayerStatus();

	// プレイヤーのモーションをファイティングモーションに設定
	PlayerMotionTypeSet(0, PLAYER_MOTION_TYPE_FIGHTING_LEFT);
	PlayerMotionTypeSet(1, PLAYER_MOTION_TYPE_FIGHTING_RIGHT);
}
//=============================================================================
// リザルトの終了処理
//=============================================================================
void UninitResult(void)
{
	// 背景の終了処理
	UninitBG();

	// ライトの終了処理
	UninitLight();

	// UIの終了処理
	UninitUI();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();
}
//=============================================================================
// リザルトの更新処理
//=============================================================================
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();

	Player *pPlayer;
	pPlayer = GetPlayer();

	int nWinner = GetWinnerPlayer();
	
	g_nPlayBackWinnerCnt++;
	if (g_nPlayBackWinnerCnt == 30)
	{
		PlayBackWinnerVoice(pPlayer[nWinner - 1].type);
	}
	// 背景の更新処理
	UpdateBG();

	// ライトの更新処理
	UpdateLight();

	// UIの更新所処理
	UpdateUI();

	// 影の更新処理
	UpdateShadow();

	// プレイヤーの更新
	UpdatePlayer();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)

	{
		if (pFade == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetFade(MODE_TITLE);
		}
	}
	if (g_nPlayBackWinnerCnt >= 300)
	{
		if (pFade == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetFade(MODE_TITLE);
		}
	}
}
//=============================================================================
// リザルトの描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;
	// ビューポートの状態を取得
	pDevice->GetViewport(&viewportDef);

	// 背景用のビューポートカメラの設定
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Zバッファのみをクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 背景の描画
	DrawBG();

	// プレイヤー1のビューポートカメラの設定
	SetCamera(PLAYERSHOW_CAMERA_TYPE_PLAYER01);

	// Zバッファのみをクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// プレイヤーの描画処理
	DrawPlayer();

	// プレイヤー2のビューポートカメラの設定
	SetCamera(PLAYERSHOW_CAMERA_TYPE_PLAYER02);

	// Zバッファのみをクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// プレイヤーの描画処理
	DrawPlayer();

	// 3DUIのビューポートカメラの設定
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Zバッファのみをクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// UIの描画処理
	DrawUI();
}
//=============================================================================
// ボイス再生
//=============================================================================
void PlayBackWinnerVoice(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE_BRAVE:
		// 勇者のボイス再生
		PlaySound(SOUND_LABEL_SE_YUSHA_005_SE);
		break;
	case PLAYER_TYPE_DEVIL:
		// 魔王のボイス再生
		PlaySound(SOUND_LABEL_SE_MAOU_005_SE);
		break;
	case PLAYER_TYPE_KING:
		// 王様のボイス再生
		PlaySound(SOUND_LABEL_SE_OU_005_SE);
		break;
	case PLAYER_TYPE_PEOPLE:
		// 平民のボイス再生
		PlaySound(SOUND_LABEL_HEIMIN_005_SE);
		break;
	case PLAYER_TYPE_GOD:
		// 神のボイス再生
		PlaySound(SOUND_LABEL_GOD_005_SE);
		break;
	}
}