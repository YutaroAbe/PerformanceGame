//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �T�E���h���� [sound.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_TITLE_BGM = 0,			// �^�C�g��BGM
	SOUND_LABEL_SELECT_BGM,				// �Z���N�gBGM
	SOUND_LABEL_GAME_R1R2R3R4_BGM,		// �o�g��1R����5RBGM
	SOUND_LABEL_GAME_R5_BGM,			// �o�g���T���E���hBGM
	SOUND_LABEL_POKERTURN_BGM,			// �|�[�J�[�t�F�C�YBGM
	SOUND_LABEL_RESULT_BGM,				// ���U���gBGM
	SOUND_LABEL_RULEBOOK_BGM,			// ���[���u�b�NBGM
	SOUND_LABEL_CHARACTER_BGM,			// �L�����N�^�[BGM
	SOUND_LABEL_CREDIT_BGM,				// �N���W�b�gBGM

	SOUND_LABEL_SE_DECISION_SE,			// ���艹SE
	SOUND_LABEL_SE_SELECTITEM_SE,		// �Z���N�g��SE
	SOUND_LABEL_SE_DAMAGE_SE,			// �_���[�W��SE
	SOUND_LABEL_SE_PAUSE,				// �|�[�YSE
	SOUND_LABEL_SE_CANCEL,				// �L�����Z��SE

	SOUND_LABEL_HIT_000,				// �U����
	SOUND_LABEL_HIT_001,				// �U����
	SOUND_LABEL_GUARD_000,				// �K�[�h

	SOUND_LABEL_SKILL_GOD_SE,			// �_�X�L��
	SOUND_LABEL_SKILL_HEIMIN_SE,		// �����X�L��
	SOUND_LABEL_SKILL_MAOU_SE,			// �����X�L��
	SOUND_LABEL_SKILL_OU_SE,			// ���X�L��
	SOUND_LABEL_SKILL_YUSHA_SE,			// �E�҃X�L��

	SOUND_LABEL_SE_MAOU_000_SE,			// ����[�U����]
	SOUND_LABEL_SE_MAOU_001_SE,			// ����[�U����]
	SOUND_LABEL_SE_MAOU_002_SE,			// ����[�_���[�W]
	SOUND_LABEL_SE_MAOU_003_SE,			// ����[�Ԃ����]
	SOUND_LABEL_SE_MAOU_004_SE,			// ����[�X�L��]
	SOUND_LABEL_SE_MAOU_005_SE,			// ����[����]
	SOUND_LABEL_SE_MAOU_006_SE,			// ����[�L�����N�^�[���]

	SOUND_LABEL_SE_YUSHA_000_SE,		// �E��[�U����]
	SOUND_LABEL_SE_YUSHA_001_SE,		// �E��[�U����]
	SOUND_LABEL_SE_YUSHA_002_SE,		// �E��[�_���[�W]
	SOUND_LABEL_SE_YUSHA_003_SE,		// �E��[�Ԃ����]
	SOUND_LABEL_SE_YUSHA_004_SE,		// �E��[�X�L��]
	SOUND_LABEL_SE_YUSHA_005_SE,		// �E��[����]
	SOUND_LABEL_SE_YUSHA_006_SE,		// �E��[�L�����N�^�[���]

	SOUND_LABEL_SE_OU_000_SE,			// ��[�U����]
	SOUND_LABEL_SE_OU_001_SE,			// ��[�U����]
	SOUND_LABEL_SE_OU_002_SE,			// ��[�_���[�W]
	SOUND_LABEL_SE_OU_003_SE,			// ��[�Ԃ����]
	SOUND_LABEL_SE_OU_004_SE,			// ��[�X�L��]
	SOUND_LABEL_SE_OU_005_SE,			// ��[����]
	SOUND_LABEL_SE_OU_006_SE,			// ��[�L�����N�^�[���]

	SOUND_LABEL_HEIMIN_000_SE,			// ����[�U����]
	SOUND_LABEL_HEIMIN_001_SE,			// ����[�U����]
	SOUND_LABEL_HEIMIN_002_SE,			// ����[�_���[�W]
	SOUND_LABEL_HEIMIN_003_SE,			// ����[�Ԃ����]
	SOUND_LABEL_HEIMIN_004_SE,			// ����[�X�L��]
	SOUND_LABEL_HEIMIN_005_SE,			// ����[����]
	SOUND_LABEL_HEIMIN_006_SE,			// ����[�L�����N�^�[���]

	SOUND_LABEL_GOD_000_SE,				// �_[�U����]
	SOUND_LABEL_GOD_001_SE,				// �_[�U����]
	SOUND_LABEL_GOD_002_SE,				// �_[�_���[�W]
	SOUND_LABEL_GOD_003_SE,				// �_[�Ԃ����]
	SOUND_LABEL_GOD_004_SE,				// �_[�X�L��]
	SOUND_LABEL_GOD_005_SE,				// �_[����]
	SOUND_LABEL_GOD_006_SE,				// �_[�L�����N�^�[���]

	SOUND_LABEL_R1_SE,					// ���E���h1
	SOUND_LABEL_R2_SE,					// ���E���h2
	SOUND_LABEL_R3_SE,					// ���E���h3
	SOUND_LABEL_R4_SE,					// ���E���h4
	SOUND_LABEL_R5_SE,					// ���E���h5
	SOUND_LABEL_KO_SE,					// KO
	SOUND_LABEL_FIGHT_SE,				// �t�@�C�g
	SOUND_LABEL_TIMEOVER_SE,			// �^�C���I�[�o�[

	SOUND_LABEL_SE_CARD_SET,			// �J�[�h�z�z��
	SOUND_LABEL_SE_CARD_SELECT,			// �J�[�h�Z���N�g��
	SOUND_LABEL_SE_CARD_OPEN,			// �J�[�h�߂��艹

	SOUND_LABEL_SE_ANNOUNCE,			// �A�i�E���X��

	SOUND_LABEL_SE_SPECIAL,				//

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
HRESULT InitSound(HWND hWnd);			// main.cpp�Ɏg��
void UninitSound(void);					// main.cpp�Ɏg��
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SelectVolume(SOUND_LABEL label, float fVolume);	// ���ʒ���

#endif
