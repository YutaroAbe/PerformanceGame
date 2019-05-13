//=============================================================================
//
// �ق����v���[���g�\���̏��� [demandpresent.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _DEMANDPRESENT_H_
#define _DEMANDPRESENT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define    MAX_DEMANDPRESENT  (20)             // �~�����v���[���g��\���ł���ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;    // ���݂̈ʒu
	int nIdxHuman;      // �l�Ԃ̔ԍ�
	bool bDisp;         // �\�����邩���Ȃ���
}DemandPresent;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDemandPresent(void);
void UninitDemandPresent(void);
void UpdateDemandPresent(void);
void DrawDemandPresent(void);
void SetDemandPresent(D3DXVECTOR3 pos, int nIdxHuman, int nNumTex);
void DeleteDemandPresent(int nIdxHuman);

#endif