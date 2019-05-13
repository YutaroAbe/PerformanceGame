//=============================================================================
//
// �Q�[������ [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,//�������Ă��Ȃ�
	GAMESTATE_NORMAL,//�ʏ���
	GAMESTATE_END,//�I�����
	GAMESTATE_CLEAR,//�N���A���
}GAMESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);	//����������
void UninitGame(void);//�I������
void UpdateGame(void);//�X�V����
void DrawGame(void);//�X�V����
void SetGame(void);	//�ݒ菈��
void SetGemeState(GAMESTATE state);
GAMESTATE GetGameState(void);
void PaauseGame(void);
void PauseModeChange(void);

#endif
