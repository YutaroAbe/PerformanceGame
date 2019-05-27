//=============================================================================
//
// �X�g�[���[�̏��� [story.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _STORY_H_
#define _STORY_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	STORY_000 = 0,		//�ʏ�
	STORY_001,				//END
	STORY_002,
	STORY_003,
	STORY_004,
	STORY_005,
	STORY_006,
	STORY_007,
	STORY_008,
	STORY_009,
	STORY_010,
	STORY_011,
	STORY_012,
	STORY_013,
	STORY_014,
	STORY_015,
	STORY_016,
	STORY_017,
	STORY_MAX
}STORYSTATE;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void InitStory(void);		//�����������X�g�[���[
void UninitStory(void);		//�I�������X�g�[���[
void UpdateStory(void);		//�X�V�����^�C�g��
void DrawStory(void);		//�`�揈���^�C�g��
STORYSTATE GetStstate(void);//
int GetStoryMenu(void);
#endif

