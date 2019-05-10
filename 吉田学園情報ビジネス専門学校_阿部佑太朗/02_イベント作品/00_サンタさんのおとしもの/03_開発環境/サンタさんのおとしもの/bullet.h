//=============================================================================
//
// 弾処理 [bullet.h]
// Author :　長山拓実
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEMTYPE *itemtype);
bool CollisionBullet(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **itemtype);
bool CollisionBullet2(D3DXVECTOR3 *pPos, float fHeight, float fWidth, int **nIdxBullet);
void DeleteBullet(int nIdxBullet);

#endif
