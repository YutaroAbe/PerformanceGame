//=============================================================================
//
// �A�N�V�����Q�[��3���� [game3.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME3_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _GAME3_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	GAME3STATE_NONE = 0,//�������Ă��Ȃ�
	GAME3STATE0_NORMAL,//�ʏ���
	GAME3STATE_END,//�I�����
	GAME3STATE_CLEAR,//�N���A���
}GAME3STATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame3(void);		//�����������^�C�g��
void UninitGame3(void);		//�I�������^�C�g��
void UpdateGame3(void);		//�X�V�����^�C�g��
void DrawGame3(void);		//�`�揈���^�C�g��
void SetGemeState3(GAME3STATE state);
GAME3STATE GetGAME3State(void);
//void PaauseGame3(void);
void SetGAME3(void);
#endif // !