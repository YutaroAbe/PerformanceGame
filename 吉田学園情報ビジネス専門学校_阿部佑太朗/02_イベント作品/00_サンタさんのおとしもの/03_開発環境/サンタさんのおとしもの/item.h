//=============================================================================
//
// アイテムの処理 [item.h]
// Author :　長山拓実
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM			(128)	// アイテムの最大数

//*****************************************************************************
// アイテムの種類
//*****************************************************************************
typedef enum
{
	ITEMTYPE_COIN = 0,	// コイン
	ITEMTYPE_MIKIYA,	// コイン
	ITEMTYPE_MAX
} ITEMTYPE;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	//D3DXCOLOR col;				// 色
	ITEMTYPE itemtype;				// アイテムの種類
	float fItemWidth;
	float fItemHeight;
	int nCounterAnim;				// アニメーションカウンター
	int nPatternAnim;				// アニメーションパターン
	bool bUse;						// 使用しているかどうか
} Item;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEMTYPE itemtype);
Item *GetItem(void);
bool CollisionItem(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **nItem);

#endif