//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "fade.h"
#include "result.h"
#include "input.h"
#include "pause.h"
#include "pauseselect.h"
#include "pauselogo.h"
#include "rankingscore.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include "explosion.h"
#include "bullet.h"
#include "item.h"
#include "human.h"
#include "demandpresent.h"
#include "frame.h"
#include "score.h"
#include "timer.h"
#include "bg2.h"
#include "getscore.h"
#include "bg3.h"
#include "crow.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	ITEMTYPE itemtype;
}ItemInfo;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void GameScene(void);

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;   // �Q�[���̏��
int       g_nCounterGameState;            // �Q�[���̏�ԊǗ��J�E���^�[
bool      g_bPuase;                       // �|�[�Y�����ǂ���
int       g_GameCounter;                  // �Q�[���̐i�s�Ǘ��J�E���^�[

ItemInfo g_ItemInfo[] =
{// �A�C�e���̔z�u���
	{ D3DXVECTOR3(250.0f,200.0f,0.0f),ITEMTYPE_COIN},
	{ D3DXVECTOR3(1050.0f,200.0f,0.0f),ITEMTYPE_MIKIYA}
};

//=============================================================================
// �Q�[����ʏ���������
//=============================================================================
void InitGame(void)
{

	//�����������w�i
	InitBG2();

	//�����������w�i
	InitBG3();

	// �v���C���[�̏���������
	InitPlayer();

	// �l�Ԃ̏���������
	InitHuman();

	//�J���X�̏���������
	InitCrow();

	// �e�̏���������
	InitBullet();

	//�A�C�e���̏���������
	InitItem();

	// �����̏���������
	InitExplosion();

	// �~�����v���[���g�\���̏���������
	InitDemandPresent();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// �t���[���̏���������
	InitFrame();

	// �^�C�}�[�̏���������
	InitTimer();

	// �X�R�A�̏���������
	InitScore();

	// �Q�b�g�X�R�A�̏���������
	InitGetScore();

	// �|�[�Y����������
	InitPause();

	// �|�[�Y���S����������
	InitPauseLogo();

	// �|�[�Y���ڏ���������
	InitPauseSelect();

	for (int nCntItem = 0; nCntItem < sizeof g_ItemInfo / sizeof(ItemInfo); nCntItem++)
	{// �z�u����A�C�e���̐������J��Ԃ�
		SetItem(g_ItemInfo[nCntItem].pos, g_ItemInfo[nCntItem].itemtype);
	}

	g_GameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_bPuase = false;
	g_GameCounter = 0;
}
//=============================================================================
// �Q�[����ʏI������
//=============================================================================
void UninitGame(void)
{
	//�I�������w�i
	UninitBG2();

	//�I�������w�i
	UninitBG3();

	// �v���C���[�̏I������
	UninitPlayer();

	// �l�Ԃ̏I������
	UninitHuman();

	//�J���X�̏I������
	UninitCrow();

	// �e�̏I������
	UninitBullet();

	// �A�C�e���̏I������
	UninitItem();

	// �����̏I������
	UninitExplosion();

	// �~�����v���[���g�\���̏I������
	UninitDemandPresent();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �t���[���̏I������
	UninitFrame();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	// �Q�b�g�X�R�A�̏I������
	UninitGetScore();

	// �|�[�Y�I������
	UninitPause();

	// �|�[�Y���S�I������
	UninitPauseLogo();

	// �|�[�Y���ڏI������
	UninitPauseSelect();
}
//=============================================================================
// �Q�[����ʍX�V����
//=============================================================================
void UpdateGame(void)
{
	FADE fade;
	fade = *GetFade();

	if (GetJoyPadTrigger(DIJS_BUTTON_9) == TRUE && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL || GetKeyboardTrigger(DIK_P) == true && fade == FADE_NONE && g_GameState == GAMESTATE_NORMAL)
	{// �|�[�YON/OFF
		g_bPuase = g_bPuase ? false : true;
		PlaySound(SOUND_LABEL_SE_PAUSEOPEN);
	}

	if (g_bPuase == false)
	{// �|�[�YOFF
		g_GameCounter++;

		//�X�V�����w�i
		UpdateBG2();

		//�I�������w�i
		UpdateBG3();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �e�̍X�V����
		UpdateBullet();

		// �A�C�e���̍X�V����
		UpdateItem();

		// �l�Ԃ̍X�V����
		UpdateHuman();

		//�J���X�̍X�V����
		UpdateCrow();

		// �����̍X�V����
		UpdateExplosion();

		// �~�����v���[���g�\���̍X�V����
		UpdateDemandPresent();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �t���[���̍X�V����
		UpdateFrame();

		// �^�C�}�[�̍X�V����
		UpdateTimer();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �Q�b�g�X�R�A�̍X�V����
		UpdateGetScore();

		// �l�Ԃ̔z�u
		GameScene();

#ifdef _DEBUG
		//if (GetKeyboardTrigger(DIK_RETURN) && g_GameState == GAMESTATE_NORMAL)
		//{// �f�o�b�N�p
		//	g_GameState = GAMESTATE_END;
		//}
#endif

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:  // �ʏ���
			break;

		case GAMESTATE_RETRY:   // ��蒼�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// ��莞�Ԃ�������

				g_GameState = GAMESTATE_NONE_RETRY;
				SetFade(MODE_GAME);

			}
			break;

		case GAMESTATE_END:     //�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 120)
			{// ��莞�Ԃ�������
				g_GameState = GAMESTATE_NONE;
				SetRankingScore(GetScore());
				SetFade(MODE_RESULT);

			}
			break;
		}
	}
	else
	{
		// �|�[�Y�X�V����
		UpdatePause();

		// �|�[�Y���S�X�V����
		UpdatePauseLogo();

		// �|�[�Y���ڍX�V����
		UpdatePauseSelect();

		if (GetJoyPadTrigger(DIJS_BUTTON_2) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ����{�^���������ꂽ
			RESTART restart;
			restart = GetRestart();
			FADE fade;
			fade = *GetFade();

			if (fade == FADE_NONE)
			{// �t�F�[�h��ԂłȂ�
				switch (restart)
				{
				case RESTART_CONTINUE:  // �Q�[���ĊJ
					break;
				case RESTART_RETRY:     // �Q�[����蒼��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_GAME);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				case RESTART_QUIT:      // �^�C�g���J��
					g_GameState = GAMESTATE_NONE;
					SetFade(MODE_TITLE);
					return; // ����ȏ�Q�[����Update���Ȃ�
					break;
				}
				g_bPuase = g_bPuase ? false : true; // �|�[�Y�͉���
			}
		}
	}
}
//=============================================================================
// �Q�[����ʕ`�揈��
//=============================================================================
void DrawGame(void)
{
	//�`�揈���w�i
	DrawBG3();

	//�`�揈���w�i
	DrawBG2();

	// �A�C�e���̕`�揈��
	DrawItem();

	// �����̕`�揈��
	DrawExplosion();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �l�Ԃ̕`�揈��
	DrawHuman();

	//�J���X�̕`�揈��
	DrawCrow();

	// �~�����v���[���g�̕`�揈��
	DrawDemandPresent();

	// �e�̕`�揈��
	DrawBullet();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �t���[���̕`�揈��
	DrawFrame();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �Q�b�g�X�R�A�̕`�揈��
	DrawGetScore();

	if (g_bPuase == true)
	{// �|�[�Y���Ȃ�
		// �|�[�Y�`�揈��
		DrawPause();

		// �|�[�Y���S�`�揈��
		DrawPauseLogo();

		// �|�[�Y���ڕ`�揈��
		DrawPauseSelect();
	}
}
//=============================================================================
// �Q�[����ʐݒ菈��
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
//=============================================================================
// �Q�[����ʎ擾����
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
// �l�Ԃ̔z�u����
//=============================================================================
void GameScene(void)
{
	if (g_GameCounter % 150 == 0)
	{
		// �l�Ԃ̔z�u
		SetHuman();
	}
}