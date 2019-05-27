#pragma once
//=============================================================================
//
// �G���h�X�g�[���[�̏��� [endstory.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _ENDSTORY_H_
#define _ENDSTORY_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	ENDSTORY_000 = 0,		//�ʏ�
	ENDSTORY_001,				//END
	ENDSTORY_002,
	ENDSTORY_003,
	ENDSTORY_004,
	ENDSTORY_005,
	ENDSTORY_006,
	ENDSTORY_007,
	ENDSTORY_008,
	ENDSTORY_009,
	ENDSTORY_010,
	ENDSTORY_011,
	ENDSTORY_012,
	ENDSTORY_013,
	ENDSTORY_014,
	ENDSTORY_015,
	ENDSTORY_016,
	ENDSTORY_MAX
}ENDSTORYSTATE;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void InitEndStory(void);		//�����������X�g�[���[
void UninitEndStory(void);		//�I�������X�g�[���[
void UpdateEndStory(void);		//�X�V�����^�C�g��
void DrawEndStory(void);		//�`�揈���^�C�g��
ENDSTORYSTATE GetEndStstate(void);//
int GetEndStoryMenu(void);
#endif

