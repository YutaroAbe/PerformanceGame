//=============================================================================
//
// ゲーム処理 [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,//何もしていない
	GAMESTATE_NORMAL,//通常状態
	GAMESTATE_END,//終了状態
	GAMESTATE_CLEAR,//クリア状態
}GAMESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);	//初期化処理
void UninitGame(void);//終了処理
void UpdateGame(void);//更新処理
void DrawGame(void);//更新処理
void SetGame(void);	//設定処理
void SetGemeState(GAMESTATE state);
GAMESTATE GetGameState(void);
void PaauseGame(void);
void PauseModeChange(void);

#endif
