//=============================================================================
//
// ���C������ [main.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "sideenemy.h"
#include "score.h"
#include "tbossenemy.h"
#include "effect.h"
#include "fade.h"
#include "time.h"
#include "life.h"
#include "nlife.h"
#include "Pause.h"
#include "ranking.h"
#include "score.h"

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;	//�Q�[�����
int g_nCounterGameState;	//��ԊǗ��J�E���^�[
bool g_bPause;		//�|�[�Y
int g_aCounterGame;

//=============================================================================
// ����������
//=============================================================================
void InitGAME(void)
{
	//�����������|�[�Y
	InitPause();
	//�����������o�b�N�O���E���h
	InitBG();
	//�����������o���b�g
	InitBullet();
	//�����������G�N�X�v���[�W����
	InitExplosion();
	//�����������G�t�F�N�g
	InitEffect();
	//�����������G�l�~�[
	InitEnemy();
	//�����������T�C�h�G�l�~�[
	InitSideEnemy();
	//�������������{�X�G�l�~�[
	InitTBossEnemy();
	//�����������X�R�A
	InitScore();
	//�����������^�C��
	InitTime();
	//�������������C�t�O�t������
	InitNlife();
	//�������������C�t
	InitLife();
	//�����������v���C���[
	InitPlayer();

	//��C
	SetSideEnemy(D3DXVECTOR3(105, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(305, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(505, 693, 0.0f),0);
	SetSideEnemy(D3DXVECTOR3(705, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(905, 693, 0.0f), 0);
	SetSideEnemy(D3DXVECTOR3(1105, 693, 0.0f), 0);

	g_GameState = GAMESTATE0_NORMAL;	//	�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;			//	�J�E���^�[�X�e�[�g�̏�����
	g_aCounterGame = 0;					//	�Q�[���̃J�E���g�̏�����
	Enemy *pEnemy;
	pEnemy = GetEnemy();				//	�G�̎擾
	pEnemy->state = ENEMYSTATE_NOMAL;	//	�ʏ�̃X�e�[�^�X
	g_bPause = false;					//	�|�[�Y���ĂȂ�

}

//=============================================================================
// �I������
//=============================================================================
void UninitGAME(void)
{
	//�I�������|�[�Y
	UninitPause();
	// �I�������o�b�N�O���E���h
	UninitBG();
	//�I�������o���b�g
	UninitBullet();
	// �I�������G�N�X�v���[�W����
	UninitExplosion();
	//�I�������G�t�F�N�g
	UninitEffect();
	// �I�������G�l�~�[
	UninitEnemy();
	// �I�������T�C�h�G�l�~�[
	UninitSideEnemy();
	//�I���������{�X�G�l�~�[
	UninitTBossEnemy();
	// �I�������X�R�A
	UninitScore();
	//�I�������^�C��
	UninitTime();
	//�I���������C�t�O�t������
	UninitNlife();
	//�I���������C�t
	UninitLife();
	// �I�������v���C���[
	UninitPlayer();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGAME(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�̐ݒ�{�^���uP�v
		PaauseGame();
	}
	if (g_bPause == false)
	{
		// �X�V�����o�b�N�O���E���h
		UpdateBG();
		// �X�V�����o���b�g
		UpdateBullet();
		// �X�V�����G�N�X�v���[�W����
		UpdateExplosion();
		//�X�V�����G�t�F�N�g
		UpdateEffect();
		// �X�V�����G�l�~�[
		UpdateEnemy();
		// �X�V�����T�C�h�G�l�~�[
		UpdateSideEnemy();
		//�X�V�������{�X�G�l�~�[
		UpdateTBossEnemy();
		// �X�V�����X�R�A
		UpdateScore();
		//�X�V�����^�C��
		UpdateTime();
		//�X�V�������C�t�O�t������
		UpdateNlife();
		//�X�V�������C�t
		UpdateLife();
		// �X�V�����v���C���[
		UpdatePlayer();

		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//	�Q�[���ʏ펞
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);
			g_aCounterGame++;	//	�G�l�~�[���o�Ă���J�E���^�[
			SetEnemyGame();		//	�G�l�~�[�Z�b�g

			break;
		case GAMESTATE_END:					//	�Q�[���I����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20)
			{//	���񂾂Ƃ��̗]�C
				g_GameState = GAMESTATE_NONE;
				SetRankScore(GetScore());
				//	���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		case GAMESTATE_CLEAR:				//	�N���A���
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20)
			{//���񂾂Ƃ��̗]�C
				g_GameState = GAMESTATE_NONE;
				SetRankScore(GetScore());
				//���(���[�h)�̐ݒ�
				SetFade(MODE_CLEAR);
			}
		}
	}
	else
	{
		//�I�������|�[�Y
		UpdatePause();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGAME(void)
{
		//�`�揈���o�b�N�O���E���h
		DrawBG();
		//�`�揈���o���b�g
		DrawBullet();
		// �`�揈���G�N�X�v���[�W����
		DrawExplosion();
		//�`�揈���G�t�F�N�g
		DrawEffect();
		// �`�揈���G�l�~�[
		DrawEnemy();
		// �`�揈���T�C�h�G�l�~�[
		DrawSideEnemy();
		//�`�揈�����{�X�G�l�~�[
		DrawTBossEnemy();
		// �`�揈���X�R�A
		DrawScore();
		//�`�揈���^�C��
		DrawTime();
		//�`�揈�����C�t�O�t������
		DrawNlife();
		//�`�揈�����C�t
		DrawLife();
		//�`�揈���v���C���[
		DrawPlayer();
		if (g_bPause == true)
		{
			//�`�揈���|�[�Y
			DrawPause();

		}
}
void SetGemeState(GAMESTATE state)
{
	g_GameState = state;
	g_nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_GameState;
}
//=============================================================================
//�G�l�~�[�Z�b�g�i�Q�[���̗���j
//=============================================================================
void SetEnemyGame(void)
{
	Enemy *pEnemy;
	pEnemy = GetEnemy();

	if (g_aCounterGame == 100)
	{
		SetEnemy(1, D3DXVECTOR3(1300, 600, 0.0f), D3DXVECTOR3(-3, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 500, 0.0f), D3DXVECTOR3(-2, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 200, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 150)
	{
		SetEnemy(1, D3DXVECTOR3(1300, 300, 0.0f), D3DXVECTOR3(-3, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 550, 0.0f), D3DXVECTOR3(-2, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1300, 280, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 300)
	{
		SetEnemy(1, D3DXVECTOR3(1400, 600, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1400, 700, 0.0f), D3DXVECTOR3(-1, 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 500)
	{
		SetEnemy(1, D3DXVECTOR3(700, 0, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 550)
	{
		SetEnemy(3, D3DXVECTOR3(700, 0, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 650)
	{
		SetEnemy(3, D3DXVECTOR3(1280, 0, 0.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1290, 0, 0.0f), D3DXVECTOR3(-1.2f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1300, 0, 0.0f), D3DXVECTOR3(-1.6f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(3, D3DXVECTOR3(1310, 0, 0.0f), D3DXVECTOR3(-1.8f, 1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 780)
	{
		SetEnemy(2, D3DXVECTOR3(1280, 780, 0.0f), D3DXVECTOR3(-1.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1290, 780, 0.0f), D3DXVECTOR3(-1.2f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1300, 780, 0.0f), D3DXVECTOR3(-1.6f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(2, D3DXVECTOR3(1310, 780, 0.0f), D3DXVECTOR3(-1.8f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 800)
	{
		SetEnemy(1, D3DXVECTOR3(800, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(900, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3(1000, 780, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 950)
	{
		SetEnemy(0, D3DXVECTOR3(1500, 430, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1450, 415, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1400, 400, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1350, 375, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3(1300, 350, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3(1350, 325, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1400, 300, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1450, 275, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3(1500, 250, 0.0f), D3DXVECTOR3(-1, 0, 0.0f), ENEMYSTATE_NOMAL);
	}
	if (g_aCounterGame == 1300)
	{
		SetTBossEnemy(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1);		//���{�X
	}
}
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}