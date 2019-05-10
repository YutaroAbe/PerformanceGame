//=============================================================================
//
// �A�N�V�����Q�[������ [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,//�������Ă��Ȃ�
	GAMESTATE0_NORMAL,//�ʏ���
	GAMESTATE_END,//�I�����
	GAMESTATE_CLEAR,//�N���A���
}GAMESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);		//�����������^�C�g��
void UninitGame(void);		//�I�������^�C�g��
void UpdateGame(void);		//�X�V�����^�C�g��
void DrawGame(void);		//�`�揈���^�C�g��
void SetGemeState(GAMESTATE state);
GAMESTATE GetGameState(void);
void PaauseGame(void);
void SetGame(void);
#endif // !