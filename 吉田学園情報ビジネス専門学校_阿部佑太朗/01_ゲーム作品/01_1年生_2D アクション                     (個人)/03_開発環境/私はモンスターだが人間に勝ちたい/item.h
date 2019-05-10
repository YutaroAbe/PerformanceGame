//=============================================================================
//
// itemの処理 [item.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	D3DCOLOR col;		//頂点カラー
	float fAngle;
	float fLength;
	float fWindth;		//幅
	float fHeight;		//高さ
	int nType;			//種類
	bool bUse;			//使用されているかどうか
	int nCounterState;  //状態管理のカウンター
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo
	int nNumItem;
}Item;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move);
Item *Getitem(void);
void CollisionItem(D3DXVECTOR3 *pPos, float *fWindth, float *fHeight); //ブロックとの判定処理


#endif
