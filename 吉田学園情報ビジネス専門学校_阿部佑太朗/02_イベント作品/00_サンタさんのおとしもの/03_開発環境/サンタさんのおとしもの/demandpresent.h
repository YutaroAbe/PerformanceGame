//=============================================================================
//
// ほしいプレゼント表示の処理 [demandpresent.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _DEMANDPRESENT_H_
#define _DEMANDPRESENT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define    MAX_DEMANDPRESENT  (20)             // 欲しいプレゼントを表示できる最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;    // 現在の位置
	int nIdxHuman;      // 人間の番号
	bool bDisp;         // 表示するかしないか
}DemandPresent;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDemandPresent(void);
void UninitDemandPresent(void);
void UpdateDemandPresent(void);
void DrawDemandPresent(void);
void SetDemandPresent(D3DXVECTOR3 pos, int nIdxHuman, int nNumTex);
void DeleteDemandPresent(int nIdxHuman);

#endif