//=============================================================================
//
// 背景(バックグラウンド)処理 [bg.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _BG_H_			//	2重インクルード防止のマクロ定義
#define _BG_H_

#include "main.h"

//=============================================================================
//構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;			//使用されているか
	int nCounterAnim; //アニメーションカウンター
	int nType;			//種類
}BG;
//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void InitBG(void);		//初期化処理バックグラウンド
void UninitBG(void);	//終了処理バックグラウンド
void UpdateBG(void);	//更新処理バックグラウンド
void DrawBG(void);		//描画処理バックグラウンド

void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);


void InitRankingBG(void);
void UninitRankingBG(void);
void UpdateRankingBG(void);
void DrawRankingBG(void);

#endif // !
