//=============================================================================
//
//	�Q�[�W�̏��� [gauge.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	float g_fGauge;												// �Q�[�W�̒l
	float g_fGaugeColR;											// �Q�[�W�̐F(��)
	float g_fGaugeColG;											// �Q�[�W�̐F(��)
	float g_fGaugeColB;											// �Q�[�W�̐F(��)
	int nChargeGauge;											// �Q�[�W(�[�d�����ǂ���)
} GAUGE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
GAUGE *GetGauge(void);

#endif
