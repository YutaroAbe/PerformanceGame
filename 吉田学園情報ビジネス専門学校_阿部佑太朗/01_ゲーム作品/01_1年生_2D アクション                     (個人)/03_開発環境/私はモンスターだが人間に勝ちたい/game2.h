//=============================================================================
//
// �A�N�V�����Q�[������ [game22.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME2_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _GAME2_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	GAME2STATE_NONE = 0,//�������Ă��Ȃ�
	GAME2STATE0_NORMAL,//�ʏ���
	GAME2STATE_END,//�I�����
	GAME2STATE_CLEAR,//�N���A���
}GAME2STATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame2(void);		//�����������^�C�g��
void UninitGame2(void);		//�I�������^�C�g��
void UpdateGame2(void);		//�X�V�����^�C�g��
void DrawGame2(void);		//�`�揈���^�C�g��
void SetGemeState2(GAME2STATE state);
GAME2STATE GetGAME2State(void);
void PaauseGame2(void);
void SetGAME2(void);
#endif // !