//=============================================================================
//
// フロントBG処理 [frontBG.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _FRONTBG_H_
#define _FRONTBG_H_

#include "main.h"
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DCOLOR col;		//頂点カラー
	float fAngle;
	float fLength;
	float fWindth;		//幅
	float fHeight;		//高さ
	int nType;			//種類
	bool bUse;			//使用されているかどうか
	int nCounterState;  //状態管理のカウンター
	int nNumYajirusi;
}FrontBG;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitFrontBG(void);
void UninitFrontBG(void);
void UpdateFrontBG(void);
void DrawFrontBG(void);
void SetFrontBG(int nType,D3DXVECTOR3 pos, float fHeight, float fWindth);
FrontBG *GetFrontBG(void);

#endif
