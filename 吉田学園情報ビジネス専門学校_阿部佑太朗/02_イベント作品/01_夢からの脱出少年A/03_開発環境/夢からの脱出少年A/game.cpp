//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "time.h"
#include "timer.h"
#include "ColorBall.h"
#include "gauge.h"
#include "obstacle.h"
#include "timer2.h"
#include "goal.h"
#include "pause.h"
#include "sky.h"
#include "Monitor.h"
#include "Monitor2.h"
#include "Monitor3.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_GameState = GAMESTATE_NORMAL;
int g_nCounterGameState;	//��ԊǗ��J�E���^�[
int g_nSwichCounter;	//��ԊǗ��J�E���^�[
int g_nSwichCounter2;	//��ԊǗ��J�E���^�[

bool g_bPause = false;				//�|�[�Y�����p  true = �|�[�Y��

//=============================================================================
// �Q�[���̏���������
//=============================================================================
void InitGame(void)
{
	InitPause();
	InitCamera();
	InitLight();
	InitPlayer();
	InitModel();
	InitObstacle();
	InitGoal();
	InitSky();
	InitTimer();
	InitTimer2();
	InitColorBall();
	InitGauge();
	InitMonitor();
	InitMonitor2();
	InitMonitor3();

	SetTimer(0);
	SetTimer2(10);
	g_bPause = false;

	int nData = 0;
	for (int nCntBlock = 0; nCntBlock < MAX_NUM_MODEL; nCntBlock++)
	{
		nData = rand() % (BLOCKCOLOR_MAX - 1) + 1;

		if (rand() % 100 >= 4)
		{

			SetModel(D3DXVECTOR3((nCntBlock % 5) * 100.0f,
				0.0f,
				(nCntBlock / 5) * 100.0f), (BLOCKCOLOR)nData);
		}


		if (nCntBlock / 5 >= 1 && rand() % 20 <= 1)
		{
			int nObs = rand() % 2;
			SetObstacle(D3DXVECTOR3((nCntBlock % 5) * 100.0f,
				20.0f,
				(nCntBlock / 5) * 100.0f),(OBS_TYPE)nObs);
		}
	}

	SetModel(D3DXVECTOR3(200.0f, 0.0f, -100.0f),BLOCKCOLOR_START);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 4000.0f), BLOCKCOLOR_START);

	SetGoal(D3DXVECTOR3(200.0f,0.0f,3950.0f));
	//���f���̃Z�b�g
	SetColorBall(D3DXVECTOR3(0.0f, 0.0f, 16.0f), 0);

}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void UninitGame(void)
{
	UninitPause();
	UninitCamera();
	UninitLight();
	UninitPlayer();
	UninitModel();
	UninitObstacle();
	UninitGoal();
	UninitSky();
	UninitTimer();
	UninitTimer2();
	UninitColorBall();
	UninitGauge();
	UninitMonitor();
	UninitMonitor2();
	UninitMonitor3();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void UpdateGame(void)
{
	//�|�[�Y�@ON/OFF
	if (GetKeyboardTrigger(DIK_P) == true || GetJoyPadTrigger(DIJS_BUTTON_9, 0) == true)
	{
		PauseModeChange();
		PlaySound(SOUND_LABEL_SE012);
		//SerectReset();
		//DispReset();
	}
	if (g_bPause == false || g_GameState == GAMESTATE_END || g_GameState == GAMESTATE_NONE)
	{

		UpdateCamera();
		UpdateLight();
		UpdatePlayer();
		UpdateModel();
		UpdateObstacle();
		UpdateGoal();
		UpdateSky();
		UpdateTimer();
		UpdateTimer2();
		UpdateColorBall();
		UpdateGauge();
		UpdateMonitor();
		UpdateMonitor2();
		UpdateMonitor3();
	}
	else if (g_bPause == true && g_GameState != GAMESTATE_END || g_GameState != GAMESTATE_NONE)
	{
		UpdatePause();//�|�[�Y����
	}

		switch (g_GameState)
		{
		case GAMESTATE_NORMAL:
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				SetFade(MODE_CLEAR);
				g_GameState = GAMESTATE_NONE;			//���[�h�ݒ�
			}
			break;
		}


}
//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DVIEWPORT9 ViewPortdef;
	//��ʂ̃N���A
	pDevice->GetViewport(&ViewPortdef);

		SetCamera(0);
		DrawPlayer();
		DrawModel();
		DrawObstacle();
		DrawGoal();
		DrawSky();
		DrawTimer();
		DrawTimer2();
		DrawGauge();
		DrawMonitor();
		DrawMonitor2();
		DrawMonitor3();
		SetCamera(1);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	DrawColorBall();

	SetCamera(0);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (g_bPause == true && g_GameState == GAMESTATE_NORMAL)
	{
		DrawPause();	//�|�[�Y���
	}

	//�r���[�|�[�g��߂�
	pDevice->SetViewport(&ViewPortdef);

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
//	�|�[�Y��Ԃ̐؂�ւ�
//=============================================================================
void PauseModeChange(void)
{
	g_bPause = g_bPause ? false : true;
}



