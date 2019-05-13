//=============================================================================
//
// ���ɂ���l�̏��� [human.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define    MAX_HUMAN  (20)              // ���ɂ���l�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	HUMANSTATE_NORMAL = 0,     // �ʏ�̏��
	HUMANSTATE_STOP,           // �~�܂��Ă�����
	HUMANSTATE_GIVEME_PRESENT, // �v���[���g��~�������Ă�����
	HUMANSTATE_HAVEPRESENT,    // �v���[���g������������
	HUMANSTATE_MAX
}HUMANSTATE;

typedef struct
{
	D3DXVECTOR3 pos;      // ���݂̈ʒu
	D3DXVECTOR3 posold;   // �O��̈ʒu
	D3DXVECTOR3 move;     // �ړ���
	HUMANSTATE state;     // ���
	float fWidth;         // ��
	float fHeight;        // ����
	bool bUse;            // �g�p���Ă��邩�ǂ���
	int nPresentCounter;  // �ق����v���[���g���o���܂ł̎���
	int nNumtex;          // �e�N�X�`���ԍ�
	int nCounterAnim;     // �A�j���[�V�����J�E���^�[
	int nPatternAnim;     // �p�^�[��No.
	int nStopConter;      // �~�߂Ēu������
	ITEMTYPE *itemtype;   // �A�C�e���̎��
}Human;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitHuman(void);
void UninitHuman(void);
void UpdateHuman(void);
void DrawHuman(void);
void SetHuman(void);
Human *GetHuman(void);

#endif