//=============================================================================
//
// ���U���g���� [result.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "player.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void PlayBackWinnerVoice(PLAYER_TYPE type);
#endif