//=============================================================================
//
// 矢印処理 [yajirusi.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _YAJIRUSI_H_
#define _YAJIRUSI_H_

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
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo
	int nNumYajirusi;
}Yajirusi;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitYajirusi(void);
void UninitYajirusi(void);
void UpdateYajirusi(void);
void DrawYajirusi(void);
void SetYajirusi(int nType,D3DXVECTOR3 pos);
Yajirusi *GetYajirusi(void);


#endif
