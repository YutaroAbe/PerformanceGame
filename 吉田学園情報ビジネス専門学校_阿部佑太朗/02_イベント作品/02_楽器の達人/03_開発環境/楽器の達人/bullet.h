//=============================================================================
//
// 弾の処理 [bullet.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{//弾の種類
	BULLETTYPE_000 = 0,	//弾の種類[0]
	BULLETTYPE_001,		//弾の種類[1]
	BULLETTYPE_MAX
}BULLETTYPE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);


#endif
