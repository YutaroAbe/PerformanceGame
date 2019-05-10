//=============================================================================
//
// アクションゲーム処理 [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME_H_			//	2重インクルード防止のマクロ定義
#define _GAME_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,//何もしていない
	GAMESTATE0_NORMAL,//通常状態
	GAMESTATE_END,//終了状態
	GAMESTATE_CLEAR,//クリア状態
}GAMESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);		//初期化処理タイトル
void UninitGame(void);		//終了処理タイトル
void UpdateGame(void);		//更新処理タイトル
void DrawGame(void);		//描画処理タイトル
void SetGemeState(GAMESTATE state);
GAMESTATE GetGameState(void);
void PaauseGame(void);
void SetGame(void);
#endif // !