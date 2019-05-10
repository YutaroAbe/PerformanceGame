//=============================================================================
//
// トラップ処理 [trap.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _TRAP_H_
#define _TRAP_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置
	D3DXVECTOR3 move;   //移動量
	int nCounterrMove;  //移動量
	int nType;			//種類
	float fWindth;		//幅
	float fHeight;		//高さ
	bool bUse;          //使用しているかどうか
}TRAP;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTrap(void);
void UninitTrap(void);
void UpdateTrap(void);
void DrawTrap(void);
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
void CollisionTrap(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //ブロックとの判定処理
void CollisionTrapEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight);
TRAP *GetTrap(void);
//bool GetKeyboardPress(int nKey);

#endif

