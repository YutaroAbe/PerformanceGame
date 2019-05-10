//=============================================================================
//
// スコア表示処理 [getscore.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _GETSCORE_H_
#define _GETSCORE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DRAW_SCORE        (10)                          // 一度に表示できるスコアの数

//*****************************
// スコアの構造体
//*****************************
typedef struct
{
	D3DXVECTOR3 pos;    // 位置
	D3DXVECTOR3 move;   // 移動量
	float fWidth;       // 幅
	float fHeight;      // 高さ
	D3DXCOLOR col;      // 色
	bool bUse;          // 使用しているかどうか
	int GetScore;       // 入手したスコア
	int nCounterDraw;   // 描画する時間
}GETSCORE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGetScore(void);
void UninitGetScore(void);
void UpdateGetScore(void);
void DrawGetScore(void);
void SetScore(D3DXVECTOR3 pPos, float width, float height, int score);
GETSCORE *GetGetScore(void);

#endif