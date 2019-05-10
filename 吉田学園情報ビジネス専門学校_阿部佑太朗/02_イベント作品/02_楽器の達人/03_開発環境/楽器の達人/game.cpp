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
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "time.h"
#include "Pause.h"
#include "ranking.h"
#include "score.h"
#include "door.h"
#include "fade.h"
#include "frontbg.h"

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
GAMESTATE g_GameState = GAMESTATE_NONE;	//�Q�[�����
int g_nCounterGameState;	//��ԊǗ��J�E���^�[
int g_nGameCounter;
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
	//InitEffect();
	//�����������G�l�~�[
	InitEnemy();
	InitDoor();
	//�����������X�R�A
	InitScore();
	//�����������^�C��
	InitTime();
	//�����������v���C���[
	InitPlayer();
	//
	InitFRONTBG();

	SetDoor(D3DXVECTOR3(100.0f, 270.0f, 0.0f),0);
	SetDoor(D3DXVECTOR3(100.0f, 467.0f, 0.0f), 1);
	SetDoor(D3DXVECTOR3(100.0f, 670.0f, 0.0f), 2);

	g_GameState = GAMESTATE0_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_aCounterGame = 0;

	Enemy *pEnemy;
	pEnemy = GetEnemy();

	pEnemy->state = ENEMYSTATE_NOMAL;
	g_nGameCounter = 0;
	g_bPause = false;			//�|�[�Y���ĂȂ�

}

//=============================================================================
// �I������
//=============================================================================
void UninitGAME(void)
{
	//	//�I�������|�[�Y
	UninitPause();
	//	// �I�������o�b�N�O���E���h
	UninitBG();
	//	//�I�������o���b�g
	UninitBullet();
	//	// �I�������G�N�X�v���[�W����
	UninitExplosion();
	//	//�I�������G�t�F�N�g
	//	UninitEffect();
	//	// �I�������G�l�~�[
	UninitEnemy();
	//	// �I�������X�R�A
	UninitScore();
	UninitDoor();
	//	//�I�������^�C��
	UninitTime();
	//	// �I�������v���C���[
	UninitPlayer();
	UninitFRONTBG();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGAME(void)
{

	//�G���^�[�Ń��[�h�G���^�[�Ɉڍs
	FADE pFade = *GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�̐ݒ�{�^���uP�v
		PaauseGame();
	}
	if (g_bPause == false)
	{
		//// �X�V�����o�b�N�O���E���h
		UpdateBG();
		//// �X�V�����o���b�g
		UpdateBullet();
		//// �X�V�����G�N�X�v���[�W����
		UpdateExplosion();
		////�X�V�����G�t�F�N�g
		//UpdateEffect();
		//// �X�V�����G�l�~�[
		UpdateEnemy();
		//// �X�V�����X�R�A
		UpdateScore();
		UpdateDoor();
		////�X�V�����^�C��
		UpdateTime();
		// �X�V�����v���C���[
		UpdatePlayer();
		UpdateFRONTBG();


		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//�Q�[���ʏ펞
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);
			g_aCounterGame++;	//�G�l�~�[���o�Ă���J�E���^�[
			SetEnemyGame();		//�G�l�~�[�Z�b�g

			break;
		case GAMESTATE_END:					//�Q�[���I����
			g_nGameCounter++;
			if (g_nGameCounter >= 60) //���񂾂Ƃ��̗]�C
			{
				g_GameState = GAMESTATE_NONE;
				//SetRankScore(GetScore());
				if (pFade == FADE_NONE)
				{
					//���(���[�h)�̐ݒ�
					SetFade(MODE_RANKING);
				}
			}
			break;
		case GAMESTATE_CLEAR://�N���A���
			g_nGameCounter++;
			if (g_nGameCounter >= 60) //���񂾂Ƃ��̗]�C
			{
				g_GameState = GAMESTATE_NONE;
				//SetRankScore(GetScore());
				//���(���[�h)�̐ݒ�
				//SetFade(MODE_RANKING);
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
		////�`�揈���o�b�N�O���E���h
		DrawBG();
		////�`�揈���o���b�g
		DrawBullet();
		//// �`�揈���G�N�X�v���[�W����
		DrawExplosion();
		////�`�揈���G�t�F�N�g
		//DrawEffect();
		//// �`�揈���G�l�~�[
		DrawEnemy();
		//// �`�揈���X�R�A
		DrawScore();
		DrawDoor();
		////�`�揈���^�C��
		DrawTime();
		//�`�揈���v���C���[
		DrawPlayer();
		DrawFRONTBG();

		if (g_bPause == true)
		{
			//�`�揈���|�[�Y
			DrawPause();

		}
}
void SetGemeState(GAMESTATE state)
{
	g_GameState = state;
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

	if ((g_aCounterGame % (rand() % 180 + (rand() % 30 + 60))) == 0)
	{
		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);

		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(0, D3DXVECTOR3((float)(rand() % 100 + 1300), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 180 + (rand() % 25 + 60))) == 0)
	{
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
		SetEnemy(1, D3DXVECTOR3((float)(rand() % 100 + 1300), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}

	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	���[��[1]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 280, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	���[��[2]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 470, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
	if ((g_aCounterGame % (rand() % 200 + 600)) == 0)
	{	//	���[��[3]
		SetEnemy(2, D3DXVECTOR3((float)(rand() % 100 + 1400), 660, 0.0f), D3DXVECTOR3(-(float)(rand() % 2 + 2), 0.0f, 0.0f), ENEMYSTATE_NOMAL);
	}
}
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}
int GetGameCounter(void)
{
	return g_nCounterGameState;
}