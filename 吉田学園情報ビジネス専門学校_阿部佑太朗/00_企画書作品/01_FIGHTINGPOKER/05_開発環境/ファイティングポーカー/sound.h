//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// サウンド処理 [sound.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_TITLE_BGM = 0,			// タイトルBGM
	SOUND_LABEL_SELECT_BGM,				// セレクトBGM
	SOUND_LABEL_GAME_R1R2R3R4_BGM,		// バトル1Rから5RBGM
	SOUND_LABEL_GAME_R5_BGM,			// バトル５ラウンドBGM
	SOUND_LABEL_POKERTURN_BGM,			// ポーカーフェイズBGM
	SOUND_LABEL_RESULT_BGM,				// リザルトBGM
	SOUND_LABEL_RULEBOOK_BGM,			// ルールブックBGM
	SOUND_LABEL_CHARACTER_BGM,			// キャラクターBGM
	SOUND_LABEL_CREDIT_BGM,				// クレジットBGM

	SOUND_LABEL_SE_DECISION_SE,			// 決定音SE
	SOUND_LABEL_SE_SELECTITEM_SE,		// セレクト音SE
	SOUND_LABEL_SE_DAMAGE_SE,			// ダメージ音SE
	SOUND_LABEL_SE_PAUSE,				// ポーズSE
	SOUND_LABEL_SE_CANCEL,				// キャンセルSE

	SOUND_LABEL_HIT_000,				// 攻撃弱
	SOUND_LABEL_HIT_001,				// 攻撃強
	SOUND_LABEL_GUARD_000,				// ガード

	SOUND_LABEL_SKILL_GOD_SE,			// 神スキル
	SOUND_LABEL_SKILL_HEIMIN_SE,		// 平民スキル
	SOUND_LABEL_SKILL_MAOU_SE,			// 魔王スキル
	SOUND_LABEL_SKILL_OU_SE,			// 王スキル
	SOUND_LABEL_SKILL_YUSHA_SE,			// 勇者スキル

	SOUND_LABEL_SE_MAOU_000_SE,			// 魔王[攻撃弱]
	SOUND_LABEL_SE_MAOU_001_SE,			// 魔王[攻撃強]
	SOUND_LABEL_SE_MAOU_002_SE,			// 魔王[ダメージ]
	SOUND_LABEL_SE_MAOU_003_SE,			// 魔王[ぶっ飛び]
	SOUND_LABEL_SE_MAOU_004_SE,			// 魔王[スキル]
	SOUND_LABEL_SE_MAOU_005_SE,			// 魔王[勝利]
	SOUND_LABEL_SE_MAOU_006_SE,			// 魔王[キャラクター画面]

	SOUND_LABEL_SE_YUSHA_000_SE,		// 勇者[攻撃弱]
	SOUND_LABEL_SE_YUSHA_001_SE,		// 勇者[攻撃強]
	SOUND_LABEL_SE_YUSHA_002_SE,		// 勇者[ダメージ]
	SOUND_LABEL_SE_YUSHA_003_SE,		// 勇者[ぶっ飛び]
	SOUND_LABEL_SE_YUSHA_004_SE,		// 勇者[スキル]
	SOUND_LABEL_SE_YUSHA_005_SE,		// 勇者[勝利]
	SOUND_LABEL_SE_YUSHA_006_SE,		// 勇者[キャラクター画面]

	SOUND_LABEL_SE_OU_000_SE,			// 王[攻撃弱]
	SOUND_LABEL_SE_OU_001_SE,			// 王[攻撃強]
	SOUND_LABEL_SE_OU_002_SE,			// 王[ダメージ]
	SOUND_LABEL_SE_OU_003_SE,			// 王[ぶっ飛び]
	SOUND_LABEL_SE_OU_004_SE,			// 王[スキル]
	SOUND_LABEL_SE_OU_005_SE,			// 王[勝利]
	SOUND_LABEL_SE_OU_006_SE,			// 王[キャラクター画面]

	SOUND_LABEL_HEIMIN_000_SE,			// 平民[攻撃弱]
	SOUND_LABEL_HEIMIN_001_SE,			// 平民[攻撃強]
	SOUND_LABEL_HEIMIN_002_SE,			// 平民[ダメージ]
	SOUND_LABEL_HEIMIN_003_SE,			// 平民[ぶっ飛び]
	SOUND_LABEL_HEIMIN_004_SE,			// 平民[スキル]
	SOUND_LABEL_HEIMIN_005_SE,			// 平民[勝利]
	SOUND_LABEL_HEIMIN_006_SE,			// 平民[キャラクター画面]

	SOUND_LABEL_GOD_000_SE,				// 神[攻撃弱]
	SOUND_LABEL_GOD_001_SE,				// 神[攻撃強]
	SOUND_LABEL_GOD_002_SE,				// 神[ダメージ]
	SOUND_LABEL_GOD_003_SE,				// 神[ぶっ飛び]
	SOUND_LABEL_GOD_004_SE,				// 神[スキル]
	SOUND_LABEL_GOD_005_SE,				// 神[勝利]
	SOUND_LABEL_GOD_006_SE,				// 神[キャラクター画面]

	SOUND_LABEL_R1_SE,					// ラウンド1
	SOUND_LABEL_R2_SE,					// ラウンド2
	SOUND_LABEL_R3_SE,					// ラウンド3
	SOUND_LABEL_R4_SE,					// ラウンド4
	SOUND_LABEL_R5_SE,					// ラウンド5
	SOUND_LABEL_KO_SE,					// KO
	SOUND_LABEL_FIGHT_SE,				// ファイト
	SOUND_LABEL_TIMEOVER_SE,			// タイムオーバー

	SOUND_LABEL_SE_CARD_SET,			// カード配布音
	SOUND_LABEL_SE_CARD_SELECT,			// カードセレクト音
	SOUND_LABEL_SE_CARD_OPEN,			// カードめくり音

	SOUND_LABEL_SE_ANNOUNCE,			// アナウンス音

	SOUND_LABEL_SE_SPECIAL,				//

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
HRESULT InitSound(HWND hWnd);			// main.cppに使う
void UninitSound(void);					// main.cppに使う
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SelectVolume(SOUND_LABEL label, float fVolume);	// 音量調整

#endif
