//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// プレイヤーの構造体
//*****************************************************************************
typedef enum
{// 弾の状態
	ITEMKIND_NONE = 0,	// アイテムを持っていない
	ITEMKIND_MIKIYA0,	// アイテム0
	ITEMKIND_MIKIYA1,   // アイテム1
	ITEMKIND_MAX	    // アイテム総数
} ITEMKIND;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 posOld;	// 前回の位置
	D3DXVECTOR3 move;	// 移動量
	float fPlayerWidth;		// 幅
	float fPlayerHeight;	// 高さ
	int nCounterItem;	// アイテム管理のカウンター
	int nDirection;			// 右か左か
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターン
	ITEMKIND kind;		// アイテムの種類
	bool bDis;			// 表示するかしないか
	ITEMTYPE *nItem;    // アイテムの種類
} Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
ITEMKIND *GetItemKind(void);

#endif