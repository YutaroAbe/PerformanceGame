//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _TUTORIAL_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	TUTOSTATE_NONE = 0,//�������Ă��Ȃ�
	TUTOSTATE_NORMAL,//�ʏ���
	TUTOSTATE_END,//�I�����
	TUTOSTATE_CLEAR,//�N���A���
}TUTOSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorial(void);		//�����������^�C�g��
void UninitTutorial(void);		//�I�������^�C�g��
void UpdateTutorial(void);		//�X�V�����^�C�g��
void DrawTutorial(void);		//�`�揈���^�C�g��
void SetTutoState(TUTOSTATE state);
TUTOSTATE GetTutoState(void);
void PaauseTutorial(void);
void SetTutorial(void);
#endif // !