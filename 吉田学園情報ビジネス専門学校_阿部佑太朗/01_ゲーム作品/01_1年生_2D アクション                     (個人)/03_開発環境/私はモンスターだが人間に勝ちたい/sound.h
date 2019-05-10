//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ABE YUUTAROU
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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	//SOUND_LABEL_BGM001,			// BGM1
//	SOUND_LABEL_BGM002,			// BGM2
	//SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	//SOUND_LABEL_BGM005,			// BGM5
	//SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM6
	SOUND_LABEL_BGM008,			// BGM6
	SOUND_LABEL_BGM009,			// BGM9
	SOUND_LABEL_BGM010,			// BGM10
	SOUND_LABEL_BGM011,			// BGM11
	SOUND_LABEL_BGM012,			// BGM12
	SOUND_LABEL_BGM013,			// BGM13
	SOUND_LABEL_BGM014,			// BGM14
	SOUND_LABEL_BGM015,			// BGM15
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT000,		// �q�b�g��0
	SOUND_LABEL_SE_HIT001,		// �q�b�g��1
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_COIN000,		// �R�C��
	SOUND_LABEL_SE_COIN001,		// �R�C��
	SOUND_LABEL_SE_COIN002,		// �R�C��
	SOUND_LABEL_SE_COIN003,		// �R�C��
	SOUND_LABEL_SE_BLOCK000,	// �u���b�N
	SOUND_LABEL_SE_SWITCH,		// SWITCH
	//SOUND_LABEL_SE_UMA,		// �n����
	SOUND_LABEL_SE_BAKEHATU,	// �n����
	SOUND_LABEL_SE_TRAP0,	
	SOUND_LABEL_SE_ENEMY0,	
	SOUND_LABEL_SE_ENEMY1,
	SOUND_LABEL_SE_BANE,
	SOUND_LABEL_SE_HATENA,
	SOUND_LABEL_SE_KAIHUKU,
	SOUND_LABEL_SE_DOA,
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

