//=============================================================================
//
// アクションゲーム3処理 [game3.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME3_H_			//	2重インクルード防止のマクロ定義
#define _GAME3_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	GAME3STATE_NONE = 0,//何もしていない
	GAME3STATE0_NORMAL,//通常状態
	GAME3STATE_END,//終了状態
	GAME3STATE_CLEAR,//クリア状態
}GAME3STATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame3(void);		//初期化処理タイトル
void UninitGame3(void);		//終了処理タイトル
void UpdateGame3(void);		//更新処理タイトル
void DrawGame3(void);		//描画処理タイトル
void SetGemeState3(GAME3STATE state);
GAME3STATE GetGAME3State(void);
//void PaauseGame3(void);
void SetGAME3(void);
#endif // !