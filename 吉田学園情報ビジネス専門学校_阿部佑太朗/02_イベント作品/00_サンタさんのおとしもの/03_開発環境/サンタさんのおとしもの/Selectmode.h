//=============================================================================
//
// �Z���N�g��ʏ��� [Selectmode.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _SELECTMODE_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _SELECTMODE_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	SELECT_NOMAL = 0,		//�ʏ�_���[�W
	SELECT_END,
	SELECT_QUIT,
	SELECT_MAX
}SELECTSTATE;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void InitSelectmode(void);		//�������������C�t�O�t��
void UninitSelectmode(void);	//�I���������C�t�O�t��
void UpdateSelectmode(void);	//�X�V�������C�t�O�t��
void DrawSelectmode(void);		//�`�揈�����C�t�O�t��
SELECTSTATE GetSelstate(void);

#endif // !
