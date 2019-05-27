//=============================================================================
//
// セレクト画面処理 [select2D.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _SELECT2D_H_
#define _SELECT2D_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
typedef enum
{
	SELECT_CURSOR = 0,
	SELECT_BATTLE,
	SELECT_RULE,
	SELECT_CREDIT,
	SELECT_RETURN,
	SELECT_OPERATION,
	SELECT_GUIDE,
	SELECT_MAX
}SELECTTYPE;
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//カラ－
	float fWidth;
	float fHeight;
	bool bUse;
	bool bSelect;
	SELECTTYPE type;
}SELECT2D;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitSelect2D(void);
void UninitSelect2D(void);
void UpdateSelect2D(void);
void DrawSelect2D(void);
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);
void SetSelect2D(D3DXVECTOR3 pos, float fWidth, float fHeight, SELECTTYPE type);
SELECTTYPE  GetSelectType(void);
#endif