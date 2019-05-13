//=============================================================================
//
// ブロック設置の処理 [blockeffect.h]
// Author :　長山拓実
//
//=============================================================================
#ifndef _BLOCKEFFECT_H_
#define _BLOCKEFFECT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif