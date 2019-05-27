//=============================================================================
//
// プレイヤー表示処理 [playershow.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "PlayerShow.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "cardModel.h"
#include "timer.h"
#include "ui.h"
#include "3DUi.h"
#include "fade.h"
#include "input.h"
#include "fade.h"
#include "shadow.h"
#include "gamefade.h"
#include "bg.h"
#include "status.h"
#include "sound.h"
#include "gamepad.h"
//=============================================================================
// グローバル変数宣言
//=============================================================================
int g_nPlayBackCnt = 0;
//=============================================================================
// プレイヤー表示の初期化処理
//=============================================================================
void InitPlayerShow(void)
{
	g_nPlayBackCnt = 0;
	// ステータスの初期化
	InitStatus();

	// 背景の初期化
	InitBG();

	// カメラの初期化
	InitCamera();

	// UIの初期化処理
	InitUI();

	// カードモデルの初期化処理
	InitCardModel();

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
// プレイヤー表示の終了処理
//=============================================================================
void UninitPlayerShow(void)
{
	// ステータスの終了処理
	UninitStatus();

	// 背景の終了処理
	UninitBG();

	// ライトの終了処理
	UninitLight();

	// モデルの終了処理
	UninitCardModel();

	// UIの終了処理
	UninitUI();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

}
//=============================================================================
// プレイヤー表示の更新処理
//=============================================================================
void UpdatePlayerShow(void)
{
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	Player *pPlayer;
	pPlayer = GetPlayer();

	g_nPlayBackCnt++;
	if (g_nPlayBackCnt == 30)
	{// 1秒経過したら1Pのボイス再生
		PlayBackVoice(pPlayer[0].type);
	}
	if (g_nPlayBackCnt == 150)
	{// 3秒経過したら2Pのボイス再生
		PlayBackVoice(pPlayer[1].type);
	}

	// ステータスの更新処理
	UpdateStatus();

	// 背景の更新処理
	UpdateBG();

	// ライトの更新処理
	UpdateLight();

	// モデルの更新処理
	UpdateCardModel();

	// UIの更新所処理
	UpdateUI();

	// 影の更新処理
	UpdateShadow();

	// プレイヤーの更新
	UpdatePlayer();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		if (pGameFade == GAMEFADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetGameFade(GAMEMODE_BATTLE);
		}
	}
	if (g_nPlayBackCnt >= 300)
	{
		if (pGameFade == GAMEFADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetGameFade(GAMEMODE_BATTLE);
		}
	}
}
//=============================================================================
// プレイヤー表示の描画処理
//=============================================================================
void DrawPlayerShow(void)
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

	// 背景用のビューポートカメラの設定
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Zバッファのみをクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// ステータスの描画
	DrawStatus();

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

	// カードモデルの描画処理
	DrawCardModel();

	// UIの描画処理
	DrawUI();
}
//=============================================================================
// ボイス再生
//=============================================================================
void PlayBackVoice(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE_BRAVE:
		// 勇者のボイス再生
		PlaySound(SOUND_LABEL_SE_YUSHA_006_SE);
		break;
	case PLAYER_TYPE_DEVIL:
		// 魔王のボイス再生
		PlaySound(SOUND_LABEL_SE_MAOU_006_SE);
		break;
	case PLAYER_TYPE_KING:
		// 王様のボイス再生
		PlaySound(SOUND_LABEL_SE_OU_006_SE);
		break;
	case PLAYER_TYPE_PEOPLE:
		// 平民のボイス再生
		PlaySound(SOUND_LABEL_HEIMIN_006_SE);
		break;
	case PLAYER_TYPE_GOD:
		// 神のボイス再生
		PlaySound(SOUND_LABEL_GOD_006_SE);
		break;
	}
}