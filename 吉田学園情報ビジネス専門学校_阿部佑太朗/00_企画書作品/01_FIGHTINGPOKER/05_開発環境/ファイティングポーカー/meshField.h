//=============================================================================
//
// メッシュフィールド処理 [meshField.h]
// Author : Ebina Riku
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	FIELD_POKER,
	FIELD_PLAYERSHOW,
	FIELD_RESULT,
	FIELD_MAX
}FIELDTYPE;
typedef struct
{
	D3DXVECTOR3 pos;								// 位置
	D3DXVECTOR3 move;								// 移動
	D3DXVECTOR3 rot;								// 向き
	D3DXMATRIX	mtxWorldField;						// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;			// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffField;			// インデックスバッファのポインタ
	float fWidth;									// 幅
	float fDepth;									// 高さ
	int nDivision_X;								// Xの分割数
	int nDivision_Z;								// Zの分割数
	int MaxVertex;									// 頂点の最大数
	int MaxIndex;									// インデックスの最大数
	int MaxPolygon;									// ポリゴンの最大数
	bool bUse;										// 使用状況
	FIELDTYPE type;
}FIELD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif
