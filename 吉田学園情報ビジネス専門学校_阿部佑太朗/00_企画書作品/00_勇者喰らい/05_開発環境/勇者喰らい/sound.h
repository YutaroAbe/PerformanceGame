//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_TITLE000 = 0,	// taitol
	SOUND_LABEL_SELECT_000,	// �L�����N�^�[�쐬
	SOUND_LABEL_STORY_000,	// �L�����N�^�[�쐬
	SOUND_LABEL_ENDSTORY,		// BOSSBGM
	SOUND_LABEL_ENDROLL,		// BOSSBGM
	SOUND_LABEL_CREDIT,		// BOSSBGM
	SOUND_LABEL_GAMEOVER,		// BOSSBGM
	SOUND_LABEL_CHAR_MAKE000,	// �L�����N�^�[�쐬
	SOUND_LABEL_FBGM000,		// FIELDBGM0
	SOUND_LABEL_BBGM001,		// BOSSBGM
	

	SOUND_LABEL_CLEAR,			//�{�X���O�o���Ƃ���
	SOUND_LABEL_OVER,			//�{�X���O�o���Ƃ���

	SOUND_LABEL_BOTTON000,		//���艹
	SOUND_LABEL_BOTTON001,		//�L�����Z����
	SOUND_LABEL_LOCKON,			//lock-on
	SOUND_LABEL_LOCKOFF,			//lock-off

	SOUND_LABEL_TitleSE000,		//���ʉ�0
	SOUND_LABEL_TitleSE001,		//���ʉ�1//���S��

	SOUND_LABEL_BOTTON002,		//�J�[�\���ړ���
	SOUND_LABEL_BOTTON003,		//�X�R�A�J�E���^�[
	SOUND_LABEL_ATTACK000,		//�U����
	SOUND_LABEL_ATTACK001,		//�U������
	SOUND_LABEL_ATTACK002,		//�U���Ή�

	SOUND_LABEL_ATTACK400,		//�U������
	SOUND_LABEL_ATTACK402,		//�U������
	SOUND_LABEL_ATTACK403,		//�U����
	SOUND_LABEL_ATTACK404,		//�U����


	SOUND_LABEL_Damage000,		//��_��
	SOUND_LABEL_Damage001,		//��_��
	SOUND_LABEL_Damage002,		//��_��
	SOUND_LABEL_GUARD000,		//�K�[�h
	SOUND_LABEL_JUMP000,		//�W�����v		
	SOUND_LABEL_DASH000,		//�u�[�X�g
	SOUND_LABEL_DEAD_END,		//�J�[�\���ړ���
	SOUND_LABEL_BOSS_D,			//�{�X���j
	SOUND_LABEL_BOSS_N,			//�{�X���O�o���Ƃ���
	SOUND_LABEL_SKILL,			//�{�X���O�o���Ƃ���
	SOUND_LABEL_STORY_SE,			//�{�X���O�o���Ƃ���
	SOUND_LABEL_ENTER,			//�{�X���O�o���Ƃ���
	SOUND_LABEL_SELECTMOVE,			//�{�X���O�o���Ƃ���

	SOUND_LABEL_HELL,			//��
	SOUND_LABEL_UP,				//�X�e�A�b�v
	SOUND_LABEL_Right,			//��


	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
