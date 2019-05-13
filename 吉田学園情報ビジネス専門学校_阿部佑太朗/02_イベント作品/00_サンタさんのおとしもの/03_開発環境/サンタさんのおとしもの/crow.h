//=============================================================================
//
// カラスの処理 [crow.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _CROW_H_
#define _CROW_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;      // 現在の位置
	D3DXVECTOR3 move;     // 移動量
	float fWidth;         // 幅
	float fHeight;        // 高さ
	int nCounterAnim;     // アニメーションカウンター
	int nPatternAnim;     // パターンNo.
	ITEMTYPE *itemtype;   // アイテムの種類
	int *nIdxBullet;      // 消す弾の番号
}Crow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCrow(void);
void UninitCrow(void);
void UpdateCrow(void);
void DrawCrow(void);

#endif