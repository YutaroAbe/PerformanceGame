//=============================================================================
//
//	ゲージの処理 [gauge.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	float g_fGauge;												// ゲージの値
	float g_fGaugeColR;											// ゲージの色(赤)
	float g_fGaugeColG;											// ゲージの色(緑)
	float g_fGaugeColB;											// ゲージの色(青)
	int nChargeGauge;											// ゲージ(充電中かどうか)
} GAUGE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
GAUGE *GetGauge(void);

#endif
