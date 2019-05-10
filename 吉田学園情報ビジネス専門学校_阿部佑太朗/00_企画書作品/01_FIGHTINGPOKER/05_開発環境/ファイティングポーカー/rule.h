//=============================================================================
//
//  [rule.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _RULE_H_
#define _RULE_H_

#include "main.h"
//=============================================================================
// 列挙型定義
//=============================================================================
typedef enum
{
	RULE_FLOW = 0,
	RULE_KEYBORD,		  // キーボード操作
	RULE_CONTROLLER,  // コントローラ操
	RULE_ROLE,			  // 役　
	RULE_CHARA,			  // キャラ
	RULE_PRESSBUTTON,	  // プレスエンター
	RULE_MAX
}RULETYPE;
//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fWidth;
	float fHeight;
	RULETYPE type;
	bool bUse;
}RULE;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitRule(void);
void UninitRule(void);
void UpdateRule(void);
void DrawRule(void);
void SetRule(D3DXVECTOR3 pos, float fWidth, float fHeight, RULETYPE type);
void MakeVertexRule(LPDIRECT3DDEVICE9 pDevice);
RULE *GetRule(void);
#endif
