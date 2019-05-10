//=========================================================================================================================
//
// ポーズルール処理 [rulebook.h]
// Author :
//
//=========================================================================================================================
#ifndef _RULEPAUSE_H_
#define _RULEPAUSE_H_

#include "main.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_RULEPAUSE	(128)	// メニュー最大数

//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************
typedef enum
{
	RULESTATE_NORMAL = 0,	// 通常状態
	RULESTATE_SELECT,		// 選択状態
	RULESTATE_MAX
}RULEPAUSESTATE;

//メニュー状態
typedef enum
{
	RULEPAUSETYPE_BG = 0,
	RULEPAUSETYPE_FLOW,
	RULEPAUSETYPE_KEYBORD,
	RULEPAUSETYPE_CONTROLLER,
	RULEPAUSETYPE_ROLE,
	RULEPAUSETYPE_CHARA,				// パンチ->パンチ
	RULEPAUSETYPE_BACK,		// パンチ->パンチ->パンチ
	RULEPAUSETYPE_MAX
}RULEPAUSETYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXCOLOR col;		// カラー
	float SelectColor;	// 選択カラー
	int nCntState;		// 状態のカウンタ
	int	SelectNum;		// 選択番号
	bool bUse;			// 使用しているか
	bool bMenu;			// メニュー使用している
	float fWidth;		// 横幅
	float fHeight;		// 縦幅
	bool  bRule;
	int nType;			// 種類
	RULEPAUSESTATE state;
} RULEPAUSEMENU;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitRulePause(void);						//ルールブック初期化処理
void UninitRulePause(void);						//ルールブック終了処理
void UpdateRulePause(void);						//ルールブック更新処理
void DrawRulePause(void);						//ルールブック描画処理
void SetRulePause(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
bool GetbMenu(void);
#endif
