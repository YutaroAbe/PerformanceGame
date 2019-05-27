//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "result.h"
#include "poker.h"
#include "battle.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "cardModel.h"
#include "ui.h"
#include "camera.h"
#include "gamefade.h"
#include "fade.h"
#include "light.h"
#include "PlayerShow.h"
#include "player.h"
#include "meshSphere.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Fighting Poker"			// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
GAMEMODE g_GameMode = GAMEMODE_POKER;
int	g_nRoundCounter;	// ���E���h���̃J�E���^�[
//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	GAMEMODE g_GameMode = GAMEMODE_POKER;

	// ���E���h���̏�����
	g_nRoundCounter = 1;

	// �t�F�[�h�̐ݒ�
	InitGameFade(g_GameMode);
	// �J�����̏���������
	InitCamera();
	// ���C�g�̏���������
	InitLight();
	// ���b�V���X�t�B�A�̏���������
	InitMeshSphere();

	// �v���C���[�^�C�v�f�[�^�̏�����
	InitPlayerTypeData();

	// ���f�����ǂݍ���
	LoadMotion();

	// ���b�V���L���[�u�̐���
	MakeMeshSphere();

	// ����HPSKILL�̃e�L�X�g�쐬
	PlayerSaveHpSkillInit();

	//���[�h�̐ݒ�
	SetGameMode(g_GameMode);

}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	//�t�F�[�h�̏I������
	UninitGameFade();
	// ���C�g�̏I������
	UninitLight();
	// ���b�V���X�t�B�A�̏I������
	UninitMeshSphere();

	// �v���C���[�^�C�v�f�[�^�̏I������
	UninitPlayerTypeData();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// �|�[�J�[���[�h
		UpdatePoker();
		break;
	case GAMEMODE_PLAYERSHOW:	// �v���C���[�\�����[�h
		UpdatePlayerShow();
		break;
	case GAMEMODE_BATTLE:		// �o�g�����[�h
		UpdateBattle();
		break;
	case GAMEMODE_RESULT:		// ���U���g���[�h
		UpdateResult();
		break;
	}
	//�t�F�[�h�̍X�V
	UpdateGameFade();
	// �J�����̍X�V����
	UpdateCamera();
	// ���C�g�̍X�V����
	UpdateLight();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// �|�[�J�[���[�h
		DrawPoker();
		break;
	case GAMEMODE_PLAYERSHOW:	// �v���C���[�\�����[�h
		DrawPlayerShow();
		break;
	case GAMEMODE_BATTLE:		// �o�g�����[�h
		DrawBattle();
		break;
	case GAMEMODE_RESULT:		// ���U���g���[�h
		DrawResult();
		break;
	}
	// �t�F�[�h�̕`��
	DrawGameFade();
}
//=============================================================================
//�Q�[�����[�h�̐ݒ�
//=============================================================================
void SetGameMode(GAMEMODE mode)
{
	switch (g_GameMode)
	{
	case GAMEMODE_POKER:		// �|�[�J�[���[�h
		UninitPoker();
		StopSound(SOUND_LABEL_POKERTURN_BGM);
		break;
	case GAMEMODE_PLAYERSHOW:	// �v���C���[�\�����[�h
		UninitPlayerShow();
		StopSound(SOUND_LABEL_CHARACTER_BGM);
		break;
	case GAMEMODE_BATTLE:		// �o�g�����[�h
		UninitBattle();
		if (g_nRoundCounter < 5)
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
		}
		else
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			StopSound(SOUND_LABEL_GAME_R5_BGM);
		}
		break;
	case GAMEMODE_RESULT:		// ���U���g���[�h
		UninitResult();
		StopSound(SOUND_LABEL_RESULT_BGM);
		break;
	}

	// ���[�h����
	g_GameMode = mode;

	switch (mode)
	{
	case GAMEMODE_POKER:		// �|�[�J�[���[�h
		InitPoker();
		PlaySound(SOUND_LABEL_POKERTURN_BGM);
		SelectVolume(SOUND_LABEL_POKERTURN_BGM, 0.2f);
		break;
	case GAMEMODE_PLAYERSHOW:	// �v���C���[�\�����[�h
		InitPlayerShow();
		PlaySound(SOUND_LABEL_CHARACTER_BGM);
		SelectVolume(SOUND_LABEL_CHARACTER_BGM, 0.2f);
		break;
	case GAMEMODE_BATTLE:		// �o�g�����[�h
		InitBattle();
		if (g_nRoundCounter < 5)
		{
			PlaySound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			SelectVolume(SOUND_LABEL_GAME_R1R2R3R4_BGM, 0.2f);
		}
		else
		{
			StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
			PlaySound(SOUND_LABEL_GAME_R5_BGM);
			SelectVolume(SOUND_LABEL_GAME_R5_BGM, 0.2f);
		}
		break;
	case GAMEMODE_RESULT:		// ���U���g���[�h
		InitResult();
		PlaySound(SOUND_LABEL_RESULT_BGM);
		SelectVolume(SOUND_LABEL_RESULT_BGM, 0.2f);
		break;
	}
}
//=============================================================================
//�Q�[�����[�h�̎擾
//============================================================================
GAMEMODE GetGameMode(void)
{
	return g_GameMode;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���E���h����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddRoundCounter(void)
{
	// ���E���h������i�߂�
	g_nRoundCounter++;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���E���h���擾����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetRoundCounter(void)
{
	return g_nRoundCounter;
}