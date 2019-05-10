//=============================================================================
//
// アクションゲーム処理 [game22.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME2_H_			//	2重インクルード防止のマクロ定義
#define _GAME2_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	GAME2STATE_NONE = 0,//何もしていない
	GAME2STATE0_NORMAL,//通常状態
	GAME2STATE_END,//終了状態
	GAME2STATE_CLEAR,//クリア状態
}GAME2STATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame2(void);		//初期化処理タイトル
void UninitGame2(void);		//終了処理タイトル
void UpdateGame2(void);		//更新処理タイトル
void DrawGame2(void);		//描画処理タイトル
void SetGemeState2(GAME2STATE state);
GAME2STATE GetGAME2State(void);
void PaauseGame2(void);
void SetGAME2(void);
#endif // !