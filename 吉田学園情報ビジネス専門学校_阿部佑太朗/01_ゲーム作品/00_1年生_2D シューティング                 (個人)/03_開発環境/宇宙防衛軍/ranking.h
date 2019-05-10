//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : 
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
//void AddRanking(int nValue);
void SetRankScore(int nScore);

#endif
