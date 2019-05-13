//=============================================================================
//
// モデル処理 [ColorBall.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _COLORBALL_H_
#define _COLORBALL_H_

#include "main.h"
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	COLORBALLSTATE_STOP = 0,	//停止状態
	COLORBALLSTATE_CHANGE,		//変化状態
}COLORBALLSTATE;				//列挙型
typedef enum
{
	COUNTERSTATE_CHANGE = 0,//変化状態
	COUNTERSTATE_WAIT,		//待機状態
}COUNTERSTATE;				//列挙型

typedef struct
{
	DWORD nNumMat = 0;						//マテリアル情報の数
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX	mtxWorld;					//ワールドマトリックス
	float fShadow;							//影の大きさ
	int nIdxShadow;							//影のインデックス
	int nType;								//モデルの種類
	bool bUse;								//使用しているか
	COLORBALLSTATE state;
	COUNTERSTATE CntState;
	int nTimerChange;
	int nStateCounter;
	int nFrameCounter;
} COLORBALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitColorBall(void);
void UninitColorBall(void);
void UpdateColorBall(void);
void DrawColorBall(void);
COLORBALL *GetColorBall(void);
void SetColorBall(D3DXVECTOR3 pos,int nType);
#endif