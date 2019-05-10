//=============================================================================
//
// 下にいる人の処理 [human.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define    MAX_HUMAN  (20)              // 下にいる人の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	HUMANSTATE_NORMAL = 0,     // 通常の状態
	HUMANSTATE_STOP,           // 止まっている状態
	HUMANSTATE_GIVEME_PRESENT, // プレゼントを欲しがっている状態
	HUMANSTATE_HAVEPRESENT,    // プレゼントをもらった状態
	HUMANSTATE_MAX
}HUMANSTATE;

typedef struct
{
	D3DXVECTOR3 pos;      // 現在の位置
	D3DXVECTOR3 posold;   // 前回の位置
	D3DXVECTOR3 move;     // 移動量
	HUMANSTATE state;     // 状態
	float fWidth;         // 幅
	float fHeight;        // 高さ
	bool bUse;            // 使用しているかどうか
	int nPresentCounter;  // ほしいプレゼントを出すまでの時間
	int nNumtex;          // テクスチャ番号
	int nCounterAnim;     // アニメーションカウンター
	int nPatternAnim;     // パターンNo.
	int nStopConter;      // 止めて置く時間
	ITEMTYPE *itemtype;   // アイテムの種類
}Human;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitHuman(void);
void UninitHuman(void);
void UpdateHuman(void);
void DrawHuman(void);
void SetHuman(void);
Human *GetHuman(void);

#endif