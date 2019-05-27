//=============================================================================
//
// ゲーム [game.h]
// Author : Ebina Riku
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H
//*****************************************************************************
// 列挙型定義
//*****************************************************************************
typedef enum
{
	GAMEMODE_POKER = 0,
	GAMEMODE_PLAYERSHOW,
	GAMEMODE_BATTLE,
	GAMEMODE_RESULT,
	GAMEMODE_MAX
}GAMEMODE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameMode(GAMEMODE mode);
GAMEMODE GetGameMode(void);
void AddRoundCounter(void);
int GetRoundCounter(void);
#endif