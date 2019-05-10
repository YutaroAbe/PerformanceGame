//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "ui.h"
#include "fade.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "shadow.h"
#include "bg.h"
#include "sound.h"
#include "gamepad.h"
//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
int g_nPlayBackWinnerCnt = 0;
//=============================================================================
// ���U���g�̏���������
//=============================================================================
void InitResult(void)
{
	g_nPlayBackWinnerCnt = 0;
	// �w�i�̏���������
	InitBG();

	// �J�����̏�����
	InitCamera();

	// UI�̏���������
	InitUI();

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
// ���U���g�̏I������
//=============================================================================
void UninitResult(void)
{
	// �w�i�̏I������
	UninitBG();

	// ���C�g�̏I������
	UninitLight();

	// UI�̏I������
	UninitUI();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();
}
//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();

	Player *pPlayer;
	pPlayer = GetPlayer();

	int nWinner = GetWinnerPlayer();
	
	g_nPlayBackWinnerCnt++;
	if (g_nPlayBackWinnerCnt == 30)
	{
		PlayBackWinnerVoice(pPlayer[nWinner - 1].type);
	}
	// �w�i�̍X�V����
	UpdateBG();

	// ���C�g�̍X�V����
	UpdateLight();

	// UI�̍X�V������
	UpdateUI();

	// �e�̍X�V����
	UpdateShadow();

	// �v���C���[�̍X�V
	UpdatePlayer();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)

	{
		if (pFade == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetFade(MODE_TITLE);
		}
	}
	if (g_nPlayBackWinnerCnt >= 300)
	{
		if (pFade == FADE_NONE)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			SetFade(MODE_TITLE);
		}
	}
}
//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void DrawResult(void)
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

	// UI�̕`�揈��
	DrawUI();
}
//=============================================================================
// �{�C�X�Đ�
//=============================================================================
void PlayBackWinnerVoice(PLAYER_TYPE type)
{
	switch (type)
	{
	case PLAYER_TYPE_BRAVE:
		// �E�҂̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_YUSHA_005_SE);
		break;
	case PLAYER_TYPE_DEVIL:
		// �����̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_MAOU_005_SE);
		break;
	case PLAYER_TYPE_KING:
		// ���l�̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_SE_OU_005_SE);
		break;
	case PLAYER_TYPE_PEOPLE:
		// �����̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_HEIMIN_005_SE);
		break;
	case PLAYER_TYPE_GOD:
		// �_�̃{�C�X�Đ�
		PlaySound(SOUND_LABEL_GOD_005_SE);
		break;
	}
}