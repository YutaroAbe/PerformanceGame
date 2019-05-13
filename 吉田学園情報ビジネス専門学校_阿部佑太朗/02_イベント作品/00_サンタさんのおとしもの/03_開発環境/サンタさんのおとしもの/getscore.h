//=============================================================================
//
// �X�R�A�\������ [getscore.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _GETSCORE_H_
#define _GETSCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DRAW_SCORE        (10)                          // ��x�ɕ\���ł���X�R�A�̐�

//*****************************
// �X�R�A�̍\����
//*****************************
typedef struct
{
	D3DXVECTOR3 pos;    // �ʒu
	D3DXVECTOR3 move;   // �ړ���
	float fWidth;       // ��
	float fHeight;      // ����
	D3DXCOLOR col;      // �F
	bool bUse;          // �g�p���Ă��邩�ǂ���
	int GetScore;       // ���肵���X�R�A
	int nCounterDraw;   // �`�悷�鎞��
}GETSCORE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGetScore(void);
void UninitGetScore(void);
void UpdateGetScore(void);
void DrawGetScore(void);
void SetScore(D3DXVECTOR3 pPos, float width, float height, int score);
GETSCORE *GetGetScore(void);

#endif