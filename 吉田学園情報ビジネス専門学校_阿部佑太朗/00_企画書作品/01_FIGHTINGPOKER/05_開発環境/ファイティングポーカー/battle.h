//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ゲームの処理 [battle.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _BATTLE_H_
#define _BATTLE_H_

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define BATTLE_TIMEOVER_FADETIME			(240)	// タイムオーバー時のフェード時間
#define BATTLE_KO_FADETIME					(240)	// KO時のフェード時間
#define BATTLE_STARTTIME					(240)	// バトルスタートまでの時間
#define BATTLE_SKILLTIME					(30)	// スキル使用時の暗転時間
#define MAX_LOAD_LINE						(256)	// 読み込みテキストの1行の最大文字数
#define BATTLE_TIME							(30)	// 1ROUNDの時間
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	BATTLESTATE_NONE = 0,		// 何もしていない状態
	BATTLESTATE_START,			// 開始状態
	BATTLESTATE_NORMAL,			// 通常状態
	BATTLESTATE_SKILL,			// スキル使用状態
	BATTLESTATE_CLEAR,			// クリア状態
	BATTLESTATE_END,			// 終了状態
	BATTLESTATE_TIMEOVER,		// 時間超過状態
	BATTLESTATE_MAX				// 総数
}BATTLESTATE;

typedef enum
{
	BATTLELEVEL_EASY = 0,		// イージー
	BATTLELEVEL_HARD,			// ハード
	BATTLELEVEL_MAX			// 総数
}BATTLELEVEL;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitBattle(void);
void UninitBattle(void);
void UpdateBattle(void);
void DrawBattle(void);
void SetBattleState(BATTLESTATE state);
void SetBattleLevel(BATTLELEVEL level);
BATTLESTATE GetBattleState(void);
BATTLESTATE GetBattleStateOld(void);
BATTLELEVEL GetBattleLevel(void);
void SetPauseState(bool bPause);
void SetRulePauseState(bool bRulePause);

#endif
