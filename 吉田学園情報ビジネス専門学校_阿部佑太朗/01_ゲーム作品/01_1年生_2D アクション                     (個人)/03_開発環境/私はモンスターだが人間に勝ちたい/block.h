//=============================================================================
//
// ブロック処理 [block.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

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
}Block;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //ブロックとの判定処理
void CollisionBlockEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight);
Block *Getblock(void);
//bool GetKeyboardPress(int nKey);

#endif

