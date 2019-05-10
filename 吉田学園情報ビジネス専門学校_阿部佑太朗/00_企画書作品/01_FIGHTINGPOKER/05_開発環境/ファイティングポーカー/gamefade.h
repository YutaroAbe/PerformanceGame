//=============================================================================
//
// ゲームフェード処理 [gamefade.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _GAMEFADE_H_
#define _GAMEFADE_H_

#include "game.h"
#include "cardModel.h"
//*************************************
// フェードの状態
//*************************************
typedef enum
{
	GAMEFADE_NONE = 0,		// 何もしていない状態
	GAMEFADE_IN,			// フェードイン状態
	GAMEFADE_OUT,			// フェードアウト状態
	GAMEFADE_MAX
} GAMEFADE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGameFade(GAMEMODE mode);
void UninitGameFade(void);
void UpdateGameFade(void);
void DrawGameFade(void);
void SetGameFade(GAMEMODE modeNext);
void SetPokerFade(CARDSIDE sideNext);
GAMEFADE GetGameFade(void);
#endif
