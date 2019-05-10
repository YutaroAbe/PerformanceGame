//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _TUTORIAL_H_			//	2重インクルード防止のマクロ定義
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{
	TUTOSTATE_NONE = 0,//何もしていない
	TUTOSTATE_NORMAL,//通常状態
	TUTOSTATE_END,//終了状態
	TUTOSTATE_CLEAR,//クリア状態
}TUTOSTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTutorial(void);		//初期化処理タイトル
void UninitTutorial(void);		//終了処理タイトル
void UpdateTutorial(void);		//更新処理タイトル
void DrawTutorial(void);		//描画処理タイトル
void SetTutoState(TUTOSTATE state);
TUTOSTATE GetTutoState(void);
void PaauseTutorial(void);
void SetTutorial(void);
#endif // !