//=============================================================================
//
// スコア処理 [score.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue,D3DXVECTOR3 pPos);
int GetScore(void);

#endif
