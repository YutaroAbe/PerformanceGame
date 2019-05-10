//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	FADE_NONE = 0,		// �������Ă��Ȃ����
	FADE_IN,			// �t�F�[�h�C�����
	FADE_OUT,			// �t�F�[�h�A�E�g���
	FADE_MAX
} FADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFade(MODE modeNext);	//���ɏo�����
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);	//���ɏo�����
FADE *GetFade(void);

#endif