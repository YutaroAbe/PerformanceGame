//=============================================================================
//
// �J���X�̏��� [crow.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _CROW_H_
#define _CROW_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;      // ���݂̈ʒu
	D3DXVECTOR3 move;     // �ړ���
	float fWidth;         // ��
	float fHeight;        // ����
	int nCounterAnim;     // �A�j���[�V�����J�E���^�[
	int nPatternAnim;     // �p�^�[��No.
	ITEMTYPE *itemtype;   // �A�C�e���̎��
	int *nIdxBullet;      // �����e�̔ԍ�
}Crow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCrow(void);
void UninitCrow(void);
void UpdateCrow(void);
void DrawCrow(void);

#endif