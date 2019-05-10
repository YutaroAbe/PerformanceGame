//=============================================================================
//
// �Q�[���t�F�[�h���� [gamefade.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _GAMEFADE_H_
#define _GAMEFADE_H_

#include "game.h"
#include "cardModel.h"
//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	GAMEFADE_NONE = 0,		// �������Ă��Ȃ����
	GAMEFADE_IN,			// �t�F�[�h�C�����
	GAMEFADE_OUT,			// �t�F�[�h�A�E�g���
	GAMEFADE_MAX
} GAMEFADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGameFade(GAMEMODE mode);
void UninitGameFade(void);
void UpdateGameFade(void);
void DrawGameFade(void);
void SetGameFade(GAMEMODE modeNext);
void SetPokerFade(CARDSIDE sideNext);
GAMEFADE GetGameFade(void);
#endif
