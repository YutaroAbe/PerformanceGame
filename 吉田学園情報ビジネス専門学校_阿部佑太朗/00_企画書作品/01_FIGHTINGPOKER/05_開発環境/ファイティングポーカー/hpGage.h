//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// HPゲージ処理 [hpGage.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _HPGAGE_H_
#define _HPGAGE_H_

#include "main.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	HPGAGE_TYPE_1P_FRAME = 0,	// 1P枠
	HPGAGE_TYPE_1P_HPBLACK,		// 1PHP黒
	HPGAGE_TYPE_1P_HPRED,		// 1PHP赤
	HPGAGE_TYPE_1P_HP,			// 1PHP
	HPGAGE_TYPE_2P_FRAME,		// 2P枠
	HPGAGE_TYPE_2P_HPBLACK,		// 2PHP黒
	HPGAGE_TYPE_2P_HPRED,		// 2PHP赤
	HPGAGE_TYPE_2P_HP,			// 2PHP
	HPGAGE_TYPE_MAX				// 総数
}HPGAGE_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitHpGage(void);
void UninitHpGage(void);
void UpdateHpGage(void);
void DrawHpGage(void);
void SetHpGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, HPGAGE_TYPE type);
void SetHpAsset(D3DXVECTOR3 pos, PLAYER_CONTROL playerID);
void SetHpGageDestLife(int nLife, PLAYER_CONTROL playerID);
void SetHpGageLife(int nLife, PLAYER_CONTROL playerID);
#endif
