//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	RANKINGTYPE_SCORE = 0,	// ランキング
	RANKINGTYPE_RANK,	// 順位
	RANKINGTYPE_BG,			// 背景
	RANKINGTYPE_ROGO,		// ロゴ
}RANKINGTYPE;

//
typedef enum
{
	OFF = 0,
	ON ,
	ALL
}FLASH;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SortRanking(int nScore);

#endif
