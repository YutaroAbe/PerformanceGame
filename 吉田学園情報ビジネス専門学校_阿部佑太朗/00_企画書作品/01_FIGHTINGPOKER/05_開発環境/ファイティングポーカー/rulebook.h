//=========================================================================================================================
//
// メニュー処理 [rulebook.h]
// Author :
//
//=========================================================================================================================
#ifndef _RULEBOOK_H_
#define _RULEBOOK_H_

#include "main.h"

//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef enum
{
	BOOKTYPE_BG = 0,
	BOOKTYPE_FLOW,
	BOOKTYPE_KEYBORD,
	BOOKTYPE_CONTROLLER,
	BOOKTYPE_ROLE,
	BOOKTYPE_CHARA,				// パンチ->パンチ
	BOOKTYPE_BACK,		// パンチ->パンチ->パンチ
	PAUSETYPE_MAX
}RULEBOOKTYPE;
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 Initpos;// 初期位置
	D3DXCOLOR col;		// 色
	D3DXVECTOR3 move;	// 移動
	int nType;			// 種類
	int nCounterAnim;	// カウンター
	int nPatternAnim;	// パターン
	float fWidth;		// 幅
	float fHeight;		// 高さ
	bool bUse;			// 使用しているかどうか
} RULEBOOK;
//******************************************************************************************************************************
// プロトタイプ宣言
//******************************************************************************************************************************
void InitRulebook(void);
void UninitRulebook(void);
void UpdateRulebook(void);
void DrawRulebook(void);
void SetRulebook(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
#endif // !_PAUSE_H_

