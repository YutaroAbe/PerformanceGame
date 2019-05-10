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
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLTETYPE_ENEMY,//敵の弾
	BULLTETYPE_SIDEENEMY,
	BULLTETYPW_TBOSSENEMY,
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
bool GetKeyboardPress(int nKey);

#endif
