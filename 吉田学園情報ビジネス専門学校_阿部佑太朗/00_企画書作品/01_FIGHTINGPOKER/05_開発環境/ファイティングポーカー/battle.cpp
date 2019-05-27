//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ゲームの処理 [battle.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "battle.h"
#include "camera.h"
#include "gamepad.h"
#include "light.h"
#include "input.h"
#include "shadow.h"
#include "meshSphere.h"
#include "meshBattleField.h"
#include "meshDome.h"
#include "player.h"
#include "pause.h"
#include "pausemenu.h"
#include "fade.h"
#include "game.h"
#include "gamefade.h"
#include "hpGage.h"
#include "spGage.h"
#include "message.h"
#include "timer.h"
#include "effect.h"
#include "textureanim.h"
#include "particle.h"
#include "rulePause.h"
#include "sound.h"
#include "gameobject.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
BATTLESTATE g_battleState = BATTLESTATE_NONE;		// ゲームの状態
BATTLESTATE g_battleStateOld = g_battleState;		// ゲームの前回状態
BATTLELEVEL g_battleLevel;						// ゲームの難易度
int g_nCounterBattleState;					// 状態管理のカウンター
bool g_bPause;								// ポーズ中かどうか
bool g_bRulePause;							// ルールポーズ中かどうか
bool g_bPauseView;							// ポーズ画面表示オンオフ
bool g_bPbutton;

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitBattle(void)
{
	g_battleState = BATTLESTATE_START;		// 通常状態に設定
	g_nCounterBattleState = 0;
	g_bPause = false;
	g_bRulePause = false;
	g_bPauseView = true;
	g_bPbutton = true;

	// ポーズの初期化
	InitPause();

	// ポーズメニューの初期化
	InitPausemenu();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	// 影の初期化処理
	InitShadow();

	// メッシュフィールドの初期化処理
	InitMeshBattleField();

	// メッシュドームの初期化処理
	InitMeshDome();

	// プレイヤーの初期化
	InitPlayer();

	// ゲームオブジェクトの初期化
	InitGameObject();

	// HPゲージの初期化処理
	InitHpGage();

	// SPゲージの初期化処理
	InitSpGage();

	// メッセージの初期化処理
	InitMessage();

	// タイマーの初期化処理
	InitTimer();
	// タイマーをOFFにする
	SetTimerSwitch(false);

	// エフェクトの初期化
	InitEffect();

	// テクスチャーアニメーションの初期化
	InitTextureAnim();

	// パーティクルの初期化
	InitParticle();

	// 各種ロード
	LoadPlayerStatus();
	// プレイヤー体力とスキルポイント保存処理
	PlayerLoadHpSkill();

	// ルールポーズの初期化処理
	InitRulePause();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitBattle(void)
{
	// ポーズの終了処理
	UninitPause();

	// ポーズメニューの終了処理
	UninitPausemenu();

	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	// 影の終了処理
	UninitShadow();

	// メッシュフィールドの終了処理
	UninitMeshBattleField();

	// メッシュドームの終了処理
	UninitMeshDome();

	// プレイヤーの終了処理
	UninitPlayer();

	// ゲームオブジェクトの終了処理
	UninitGameObject();

	// HPゲージの終了処理
	UninitHpGage();

	// SPゲージの終了処理
	UninitSpGage();

	// メッセージの終了処理
	UninitMessage();

	// タイマーの終了処理
	UninitTimer();

	// エフェクトの終了
	UninitEffect();

	// テクスチャーアニメーションの終了
	UninitTextureAnim();

	// パーティクルの終了
	UninitParticle();

	// ルールポーズの終了処理
	UninitRulePause();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateBattle(void)
{
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	// 前回のバトル状態を取得
	g_battleStateOld = g_battleState;

	//デバッグ用
	//if (GetKeyboardTrigger(DIK_T) == true)
	//{ // 時間切れの変わり
	//	if (pGameFade == GAMEFADE_NONE)
	//	{
	//		// プレイヤー体力とスキルポイント保存処理
	//		PlayerSaveHpSkill();

	//		SetGameFade(GAMEMODE_POKER);

	//		// ROUND数を進める
	//		AddRoundCounter();
	//	}
	//}

	if (g_bPbutton == true)
	{
		if (GetKeyboardTrigger(DIK_P) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START) == true && g_bRulePause == false)
		{ // ポーズON/OFF
			InitPauseSelect();
			g_bPause = g_bPause ? false : true;
			if (g_bPause == true)
			{
				PlaySound(SOUND_LABEL_SE_PAUSE);
			}
			else
			{
				PlaySound(SOUND_LABEL_SE_CANCEL);
			}
		}
	}

	if (g_bPause == false && g_bRulePause == false)
	{
		// カメラの更新処理
		UpdateCamera();

		// ライトの更新処理
		UpdateLight();

		if (g_battleState != BATTLESTATE_SKILL)
		{
			// 影の更新処理
			UpdateShadow();

			// プレイヤーの更新
			UpdatePlayer();

			// ゲームオブジェクトの更新
			UpdateGameObject();

			// HPゲージの更新
			UpdateHpGage();

			// SPゲージの更新
			UpdateSpGage();

			// メッシュスフィアの更新処理
			UpdateMeshSphere();

			// メッシュフィールドの更新処理
			UpdateMeshBattleField();

			// メッシュドームの更新処理
			UpdateMeshDome();

			// メッセージの更新処理
			UpdateMessage();

			// タイマーの更新
			UpdateTimer();

			// エフェクトの更新
			UpdateEffect();

			// テクスチャーアニメーションの更新
			UpdateTextureAnim();

			// パーティクルの更新
			UpdateParticle();
		}

		switch (g_battleState)
		{
		case BATTLESTATE_NORMAL:
			break;
		case BATTLESTATE_START:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= MESSAGE_FIGHT_FRAME + MESSAGE_APPEAR_FRAME + MESSAGE_WAIT_FRAME)
			{
				g_battleState = BATTLESTATE_NORMAL;

				// タイマーのスタート
				SetTimerSwitch(true);

				Player *pPlayer = GetPlayer();

				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					AddPlayerLife(nCntPlayer, pPlayer[nCntPlayer].nRecovery);
					// HPゲージの変更
					SetHpGageDestLife(pPlayer[nCntPlayer].nLife, (PLAYER_CONTROL)nCntPlayer);
				}
			}
			break;
		case BATTLESTATE_END:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_STARTTIME)
			{
				g_battleState = BATTLESTATE_NONE;

				// フェード設定
				SetGameFade(GAMEMODE_POKER);
			}
			break;
		case BATTLESTATE_SKILL:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_SKILLTIME)
			{
				g_battleState = BATTLESTATE_NORMAL;

			}
			break;
		case BATTLESTATE_CLEAR:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= 300)
			{
				g_battleState = BATTLESTATE_NONE;

				// フェード設定
				SetGameFade(GAMEMODE_RESULT);
			}
			break;
		case BATTLESTATE_TIMEOVER:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_TIMEOVER_FADETIME)
			{
				g_battleState = BATTLESTATE_NONE;

				// プレイヤー体力とスキルポイント保存処理
				PlayerSaveHpSkill();

				// ROUND数を進める
				AddRoundCounter();

				// フェード設定
				SetGameFade(GAMEMODE_POKER);
			}
		}
	}
	else if (g_bPause == true && g_bRulePause == false)
	{
		g_bPbutton = true;

		// ポーズの更新処理
		UpdatePause();

		// ポーズメニューの更新処理
		UpdatePausemenu();

		// ポーズビューデバッグ用
#if 0
		if (GetKeyboardTrigger(DIK_V) == true)
		{ // ポーズビューデバッグ用
			g_bPauseView = g_bPauseView ? false : true;
		}
#endif
		if (g_bPauseView == false)
		{
			// カメラの更新処理
			UpdateCamera();
		}
	}

	else if (g_bPause == false && g_bRulePause == true)
	{
		g_bPbutton = false;
		// ルールポーズの更新
		UpdateRulePause();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawBattle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;
	// ビューポートの状態を取得
	pDevice->GetViewport(&viewportDef);

	// カメラの設定
	SetCamera(0);

	// ビューポートをクリアする
	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// メッシュドームの描画処理
	DrawMeshDome();

	// メッシュフィールドの描画処理
	DrawMeshBattleField();

	// プレイヤーの描画処理
	DrawPlayer();

	// マップの描画処理
	DrawGameObject();

	// 影の描画処理
	DrawShadow();

	// メッシュスフィアの描画処理
	DrawMeshSphere();

	// メッセージの描画処理
	DrawMessage();

	// タイマーの描画
	DrawTimer();

	// パーティクルの描画
	DrawParticle();

	// テクスチャーアニメーションの描画
	DrawTextureAnim();

	// エフェクトの描画
	DrawEffect();

	// HPゲージの描画処理
	DrawHpGage();

	// SPゲージの描画処理
	DrawSpGage();

	// ビューポートを元に戻す
	pDevice->SetViewport(&viewportDef);

	if (g_bPause == true)
	{
		if (g_bPauseView == true)
		{
			// ポーズの描画処理
			DrawPause();

			// ポーズメニューの描画処理
			DrawPausemenu();

		}
	}
	if (g_bRulePause == true)
	{
		DrawRulePause();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームの状態設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetBattleState(BATTLESTATE state)
{
	g_battleState = state;
	g_nCounterBattleState = 0;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームの難易度設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetBattleLevel(BATTLELEVEL level)
{
	g_battleLevel = level;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームの状態の取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLESTATE GetBattleState(void)
{
	return g_battleState;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームの前回状態の取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLESTATE GetBattleStateOld(void)
{
	return g_battleStateOld;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームの難易度の取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLELEVEL GetBattleLevel(void)
{
	return g_battleLevel;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズの状態
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズルールの状態
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetRulePauseState(bool bRulePause)
{
	g_bRulePause = bRulePause;
}

