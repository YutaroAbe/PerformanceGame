//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �Q�[���̏��� [battle.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "battle.h"
#include "camera.h"
#include "gamepad.h"
#include "light.h"
#include "input.h"
#include "shadow.h"
#include "meshSphere.h"
#include "meshBattleField.h"
#include "meshDome.h"
#include "player.h"
#include "pause.h"
#include "pausemenu.h"
#include "fade.h"
#include "game.h"
#include "gamefade.h"
#include "hpGage.h"
#include "spGage.h"
#include "message.h"
#include "timer.h"
#include "effect.h"
#include "textureanim.h"
#include "particle.h"
#include "rulePause.h"
#include "sound.h"
#include "gameobject.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ��錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
BATTLESTATE g_battleState = BATTLESTATE_NONE;		// �Q�[���̏��
BATTLESTATE g_battleStateOld = g_battleState;		// �Q�[���̑O����
BATTLELEVEL g_battleLevel;						// �Q�[���̓�Փx
int g_nCounterBattleState;					// ��ԊǗ��̃J�E���^�[
bool g_bPause;								// �|�[�Y�����ǂ���
bool g_bRulePause;							// ���[���|�[�Y�����ǂ���
bool g_bPauseView;							// �|�[�Y��ʕ\���I���I�t
bool g_bPbutton;

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitBattle(void)
{
	g_battleState = BATTLESTATE_START;		// �ʏ��Ԃɐݒ�
	g_nCounterBattleState = 0;
	g_bPause = false;
	g_bRulePause = false;
	g_bPauseView = true;
	g_bPbutton = true;

	// �|�[�Y�̏�����
	InitPause();

	// �|�[�Y���j���[�̏�����
	InitPausemenu();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏���������
	InitShadow();

	// ���b�V���t�B�[���h�̏���������
	InitMeshBattleField();

	// ���b�V���h�[���̏���������
	InitMeshDome();

	// �v���C���[�̏�����
	InitPlayer();

	// �Q�[���I�u�W�F�N�g�̏�����
	InitGameObject();

	// HP�Q�[�W�̏���������
	InitHpGage();

	// SP�Q�[�W�̏���������
	InitSpGage();

	// ���b�Z�[�W�̏���������
	InitMessage();

	// �^�C�}�[�̏���������
	InitTimer();
	// �^�C�}�[��OFF�ɂ���
	SetTimerSwitch(false);

	// �G�t�F�N�g�̏�����
	InitEffect();

	// �e�N�X�`���[�A�j���[�V�����̏�����
	InitTextureAnim();

	// �p�[�e�B�N���̏�����
	InitParticle();

	// �e�탍�[�h
	LoadPlayerStatus();
	// �v���C���[�̗͂ƃX�L���|�C���g�ۑ�����
	PlayerLoadHpSkill();

	// ���[���|�[�Y�̏���������
	InitRulePause();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitBattle(void)
{
	// �|�[�Y�̏I������
	UninitPause();

	// �|�[�Y���j���[�̏I������
	UninitPausemenu();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �e�̏I������
	UninitShadow();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshBattleField();

	// ���b�V���h�[���̏I������
	UninitMeshDome();

	// �v���C���[�̏I������
	UninitPlayer();

	// �Q�[���I�u�W�F�N�g�̏I������
	UninitGameObject();

	// HP�Q�[�W�̏I������
	UninitHpGage();

	// SP�Q�[�W�̏I������
	UninitSpGage();

	// ���b�Z�[�W�̏I������
	UninitMessage();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �G�t�F�N�g�̏I��
	UninitEffect();

	// �e�N�X�`���[�A�j���[�V�����̏I��
	UninitTextureAnim();

	// �p�[�e�B�N���̏I��
	UninitParticle();

	// ���[���|�[�Y�̏I������
	UninitRulePause();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateBattle(void)
{
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	// �O��̃o�g����Ԃ��擾
	g_battleStateOld = g_battleState;

	//�f�o�b�O�p
	//if (GetKeyboardTrigger(DIK_T) == true)
	//{ // ���Ԑ؂�̕ς��
	//	if (pGameFade == GAMEFADE_NONE)
	//	{
	//		// �v���C���[�̗͂ƃX�L���|�C���g�ۑ�����
	//		PlayerSaveHpSkill();

	//		SetGameFade(GAMEMODE_POKER);

	//		// ROUND����i�߂�
	//		AddRoundCounter();
	//	}
	//}

	if (g_bPbutton == true)
	{
		if (GetKeyboardTrigger(DIK_P) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START) == true && g_bRulePause == false)
		{ // �|�[�YON/OFF
			InitPauseSelect();
			g_bPause = g_bPause ? false : true;
			if (g_bPause == true)
			{
				PlaySound(SOUND_LABEL_SE_PAUSE);
			}
			else
			{
				PlaySound(SOUND_LABEL_SE_CANCEL);
			}
		}
	}

	if (g_bPause == false && g_bRulePause == false)
	{
		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();

		if (g_battleState != BATTLESTATE_SKILL)
		{
			// �e�̍X�V����
			UpdateShadow();

			// �v���C���[�̍X�V
			UpdatePlayer();

			// �Q�[���I�u�W�F�N�g�̍X�V
			UpdateGameObject();

			// HP�Q�[�W�̍X�V
			UpdateHpGage();

			// SP�Q�[�W�̍X�V
			UpdateSpGage();

			// ���b�V���X�t�B�A�̍X�V����
			UpdateMeshSphere();

			// ���b�V���t�B�[���h�̍X�V����
			UpdateMeshBattleField();

			// ���b�V���h�[���̍X�V����
			UpdateMeshDome();

			// ���b�Z�[�W�̍X�V����
			UpdateMessage();

			// �^�C�}�[�̍X�V
			UpdateTimer();

			// �G�t�F�N�g�̍X�V
			UpdateEffect();

			// �e�N�X�`���[�A�j���[�V�����̍X�V
			UpdateTextureAnim();

			// �p�[�e�B�N���̍X�V
			UpdateParticle();
		}

		switch (g_battleState)
		{
		case BATTLESTATE_NORMAL:
			break;
		case BATTLESTATE_START:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= MESSAGE_FIGHT_FRAME + MESSAGE_APPEAR_FRAME + MESSAGE_WAIT_FRAME)
			{
				g_battleState = BATTLESTATE_NORMAL;

				// �^�C�}�[�̃X�^�[�g
				SetTimerSwitch(true);

				Player *pPlayer = GetPlayer();

				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					AddPlayerLife(nCntPlayer, pPlayer[nCntPlayer].nRecovery);
					// HP�Q�[�W�̕ύX
					SetHpGageDestLife(pPlayer[nCntPlayer].nLife, (PLAYER_CONTROL)nCntPlayer);
				}
			}
			break;
		case BATTLESTATE_END:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_STARTTIME)
			{
				g_battleState = BATTLESTATE_NONE;

				// �t�F�[�h�ݒ�
				SetGameFade(GAMEMODE_POKER);
			}
			break;
		case BATTLESTATE_SKILL:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_SKILLTIME)
			{
				g_battleState = BATTLESTATE_NORMAL;

			}
			break;
		case BATTLESTATE_CLEAR:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= 300)
			{
				g_battleState = BATTLESTATE_NONE;

				// �t�F�[�h�ݒ�
				SetGameFade(GAMEMODE_RESULT);
			}
			break;
		case BATTLESTATE_TIMEOVER:
			g_nCounterBattleState++;
			if (g_nCounterBattleState >= BATTLE_TIMEOVER_FADETIME)
			{
				g_battleState = BATTLESTATE_NONE;

				// �v���C���[�̗͂ƃX�L���|�C���g�ۑ�����
				PlayerSaveHpSkill();

				// ROUND����i�߂�
				AddRoundCounter();

				// �t�F�[�h�ݒ�
				SetGameFade(GAMEMODE_POKER);
			}
		}
	}
	else if (g_bPause == true && g_bRulePause == false)
	{
		g_bPbutton = true;

		// �|�[�Y�̍X�V����
		UpdatePause();

		// �|�[�Y���j���[�̍X�V����
		UpdatePausemenu();

		// �|�[�Y�r���[�f�o�b�O�p
#if 0
		if (GetKeyboardTrigger(DIK_V) == true)
		{ // �|�[�Y�r���[�f�o�b�O�p
			g_bPauseView = g_bPauseView ? false : true;
		}
#endif
		if (g_bPauseView == false)
		{
			// �J�����̍X�V����
			UpdateCamera();
		}
	}

	else if (g_bPause == false && g_bRulePause == true)
	{
		g_bPbutton = false;
		// ���[���|�[�Y�̍X�V
		UpdateRulePause();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawBattle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewportDef;
	// �r���[�|�[�g�̏�Ԃ��擾
	pDevice->GetViewport(&viewportDef);

	// �J�����̐ݒ�
	SetCamera(0);

	// �r���[�|�[�g���N���A����
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// ���b�V���h�[���̕`�揈��
	DrawMeshDome();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshBattleField();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �}�b�v�̕`�揈��
	DrawGameObject();

	// �e�̕`�揈��
	DrawShadow();

	// ���b�V���X�t�B�A�̕`�揈��
	DrawMeshSphere();

	// ���b�Z�[�W�̕`�揈��
	DrawMessage();

	// �^�C�}�[�̕`��
	DrawTimer();

	// �p�[�e�B�N���̕`��
	DrawParticle();

	// �e�N�X�`���[�A�j���[�V�����̕`��
	DrawTextureAnim();

	// �G�t�F�N�g�̕`��
	DrawEffect();

	// HP�Q�[�W�̕`�揈��
	DrawHpGage();

	// SP�Q�[�W�̕`�揈��
	DrawSpGage();

	// �r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewportDef);

	if (g_bPause == true)
	{
		if (g_bPauseView == true)
		{
			// �|�[�Y�̕`�揈��
			DrawPause();

			// �|�[�Y���j���[�̕`�揈��
			DrawPausemenu();

		}
	}
	if (g_bRulePause == true)
	{
		DrawRulePause();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���̏�Ԑݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetBattleState(BATTLESTATE state)
{
	g_battleState = state;
	g_nCounterBattleState = 0;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���̓�Փx�ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetBattleLevel(BATTLELEVEL level)
{
	g_battleLevel = level;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���̏�Ԃ̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLESTATE GetBattleState(void)
{
	return g_battleState;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���̑O���Ԃ̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLESTATE GetBattleStateOld(void)
{
	return g_battleStateOld;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���̓�Փx�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BATTLELEVEL GetBattleLevel(void)
{
	return g_battleLevel;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�̏��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y���[���̏��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetRulePauseState(bool bRulePause)
{
	g_bRulePause = bRulePause;
}

