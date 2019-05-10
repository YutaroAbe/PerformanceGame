//=============================================================================
//
// スイッチ処理 [switch.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置
	D3DXVECTOR3 move;	//位置
	int nType;			//種類
	float fWindth;		//幅
	float fHeight;		//高さ
	bool bUse;          //使用しているかどうか
}Switch;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSwitch(void);
void UninitSwitch(void);
void UpdateSwitch(void);
void DrawSwitch(void);
void SetSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
void CollisionSwitch(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //ブロックとの判定処理
Switch *GetSwitch(void);
//bool GetKeyboardPress(int nKey);

#endif

