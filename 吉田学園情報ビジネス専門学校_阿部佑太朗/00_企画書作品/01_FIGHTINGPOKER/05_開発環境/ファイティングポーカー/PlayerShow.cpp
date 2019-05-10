//=============================================================================
//
// �v���C���[�\������ [playershow.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "PlayerShow.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "cardModel.h"
#include "timer.h"
#include "ui.h"
#include "3DUi.h"
#include "fade.h"
#include "input.h"
#include "fade.h"
#include "shadow.h"
#include "gamefade.h"
#include "bg.h"
#include "status.h"
#include "sound.h"
#include "gamepad.h"
//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
int g_nPlayBackCnt = 0;
//=============================================================================
// �v���C���[�\���̏���������
//=============================================================================
void InitPlayerShow(void)
{
	g_nPlayBackCnt = 0;
	// �X�e�[�^�X�̏�����
	InitStatus();

	// �w�i�̏�����
	InitBG();

	// �J�����̏�����
	InitCamera();

	// UI�̏���������
	InitUI();

	// �J�[�h���f���̏���������
	InitCardModel();

	// �e�̏���������
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	// �v���C���[�̃X�e�[�^�X���ǂݍ���
	LoadPlayerStatus();

	// �v���C���[�̃��[�V�������t�@�C�e�B���O���[�V�����ɐݒ�
	PlayerMotionTypeSet(0, PLAYER_MOTION_TYPE_FIGHTING_LEFT);
	PlayerMotionTypeSet(1, PLAYER_MOTION_TYPE_FIGHTING_RIGHT);
}
//=============================================================================
// �v���C���[�\���̏I������
//=============================================================================
void UninitPlayerShow(void)
{
	// �X�e�[�^�X�̏I������
	UninitStatus();

	// �w�i�̏I������
	UninitBG();

	// ���C�g�̏I������
	UninitLight();

	// ���f���̏I������
	UninitCardModel();

	// UI�̏I������
	UninitUI();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

}
//=============================================================================
// �v���C���[�\���̍X�V����
//=============================================================================
void UpdatePlayerShow(void)
{
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	Player *pPlayer;
	pPlayer = GetPlayer();

	g_nPlayBackCnt++;
	if (g_nPlayBackCnt == 30)
	{// 1�b�o�߂�����1P�̃{�C�X�Đ�
		PlayBackVoice(pPlayer[0].type);
	}
	if (g_nPlayBackCnt == 150)
	{// 3�b�o�߂�����2P�̃{�C�X�Đ�
		PlayBackVoice(pPlayer[1].type);
	}

	// �X�e�[�^�X�̍X�V����
	UpdateStatus();

	// �w�i�̍X�V����
	UpdateBG();

	// ���C�g�̍X�V����
	UpdateLight();

	// ���f���̍X�V����
	UpdateCardModel();

	// UI�̍X�V������
	UpdateUI();

	// �e�̍X�V����
	UpdateShadow();

	// �v���C���[�̍X�V
	UpdatePlayer();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		if (pGameFade == GAMEFADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetGameFade(GAMEMODE_BATTLE);
		}
	}
	if (g_nPlayBackCnt >= 300)
	{
		if (pGameFade == GAMEFADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetGameFade(GAMEMODE_BATTLE);
		}
	}
}
//=============================================================================
// �v���C���[�\���̕`�揈��
//=============================================================================
void DrawPlayerShow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;

	// �r���[�|�[�g�̏�Ԃ��擾
	pDevice->GetViewport(&viewportDef);

	// �w�i�p�̃r���[�|�[�g�J�����̐ݒ�
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Z�o�b�t�@�݂̂��N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �w�i�̕`��
	DrawBG();

	// �w�i�p�̃r���[�|�[�g�J�����̐ݒ�
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Z�o�b�t�@�݂̂��N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �X�e�[�^�X�̕`��
	DrawStatus();

	// �v���C���[1�̃r���[�|�[�g�J�����̐ݒ�
	SetCamera(PLAYERSHOW_CAMERA_TYPE_PLAYER01);

	// Z�o�b�t�@�݂̂��N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �v���C���[2�̃r���[�|�[�g�J�����̐ݒ�
	SetCamera(PLAYERSHOW_CAMERA_TYPE_PLAYER02);

	// Z�o�b�t�@�݂̂��N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// 3DUI�̃r���[�|�[�g�J�����̐ݒ�
	SetCamera(PLAYERSHOW_CAMERA_TYPE_3DUI);

	// Z�o�b�t�@�݂̂��N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �J�[�h���f���̕`�揈��
	DrawCardModel();

	// UI�̕`�揈��
	DrawUI();
}
//=============================================================================
// �{�C�X�Đ�
//=============================================================================
void PlayBackVoice(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE_BRAVE:
		// �E�҂̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_YUSHA_006_SE);
		break;
	case PLAYER_TYPE_DEVIL:
		// �����̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_MAOU_006_SE);
		break;
	case PLAYER_TYPE_KING:
		// ���l�̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_OU_006_SE);
		break;
	case PLAYER_TYPE_PEOPLE:
		// �����̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_HEIMIN_006_SE);
		break;
	case PLAYER_TYPE_GOD:
		// �_�̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_GOD_006_SE);
		break;
	}
}