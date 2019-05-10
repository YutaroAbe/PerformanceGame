//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "ranking.h"
#include "bg.h"
#include "rankingscore.h"
#include "rankingrank.h"
#include "rankinglogo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
void InitRanking(void)
{
	// 背景初期化処理
	InitRankingBG();

	// 順位初期化処理
	InitRankingRank();

	// ロゴ初期化処理
	InitRankingLogo();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	// 背景終了処理
	UninitRankingBG();

	// 順位終了処理
	UninitRankingRank();

	// ロゴ終了処理
	UninitRankingLogo();
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	// 背景更新処理
	UpdateRankingBG();

	// 順位更新処理
	UpdateRankingRank();

	// ロゴ更新処理
	UpdateRankingLogo();

	// スコア更新処理
	UpdateRankingScore();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	// 背景描画処理
	DrawRankingBG();

	// 順位描画処理
	DrawRankingRank();

	// ロゴ描画処理
	DrawRankingLogo();

	// スコア描画処理
	DrawRankingScore();
}