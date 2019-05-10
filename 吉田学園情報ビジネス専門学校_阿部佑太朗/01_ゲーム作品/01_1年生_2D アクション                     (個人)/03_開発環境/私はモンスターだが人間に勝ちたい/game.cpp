//=============================================================================
//
// �A�N�V�����Q�[������ [game.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "Pause.h"
#include "block.h"
#include "bg.h"
#include "item.h"
#include "score.h"
#include "time.h"
#include "switch.h"
#include "enemy.h"
#include "life.h"
#include "nlife.h"
#include "tagu.h"
#include "trap.h"
#include "yajirusi.h"
#include "explosion.h"

//*****************************************************************************
//�u���b�N�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfo;
//*****************************************************************************
//�O���[�o���ϐ�
//*****************************************************************************
GAMESTATE g_GameState = GAMESTATE_NONE; //�Q�[�����
bool g_bPause;		//�|�[�Y
int g_nCounterGameState;	//��ԊǗ��J�E���^�[
int g_nSwichCounter;	//��ԊǗ��J�E���^�[
int g_nSwichCounter2;	//��ԊǗ��J�E���^�[

BlockInfo g_aBlockInfo[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//����������
//=============================================================================
void InitGame(void)
{
	//�����������|�[�Y
	InitPause();
	//�����������^�O
	InitTagu();
	//�������^�C��
	InitTime();
	//�������X�R�A
	InitScore();
	//���������C�t
	InitLife();
	//����������
	InitExplosion();
	//�������g���b�v
	InitTrap();
	//�������A�C�e��
	InitItem();
	//�������₶�邵
	InitYajirusi();
	//�����������X�C�b�`
	InitSwitch();
	//�����������v���C���[
	InitPlayer();
	//�����������G�l�~�[
	InitEnemy();
	//�����������u���b�N
	InitBlock();

	
	SetYajirusi(0, D3DXVECTOR3(1090, 150.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(3030.0f, 290.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(4080, 250.0f, 0));
	SetYajirusi(0, D3DXVECTOR3(5850.0f, 360.0f, 0));

	SetSwitch(D3DXVECTOR3(1080, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 0);
	SetSwitch(D3DXVECTOR3(3030.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 2);
	SetSwitch(D3DXVECTOR3(4080, 260.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 9);
	SetSwitch(D3DXVECTOR3(5850.0f, 370.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 11);

	SetTrap(D3DXVECTOR3(1200, 500.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(1280, 240.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(1500, 150.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(900, 400.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);

	for(int nCountTrp = 0; nCountTrp < 9;nCountTrp++)
	{
		SetTrap(D3DXVECTOR3(5100.0f +(nCountTrp * 100), 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);

	}
	SetTrap(D3DXVECTOR3(4400, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4500, 190.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4600, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4700, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetTrap(D3DXVECTOR3(4800, 120.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 2);
	SetEnemy(1, D3DXVECTOR3(1000.0f, 160.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(1800.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(2600.0f, 100.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3800.0f, 480.0f, 0), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), 30, 60, 2);
	//�Z�b�g�Q�[��
	SetGame();

	g_GameState = GAMESTATE0_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_nSwichCounter = 0;
	g_nSwichCounter2 = 0;	//��ԊǗ��J�E���^�[
	 

	g_bPause = false;			//�|�[�Y���ĂȂ�
}
//=============================================================================
//�I������
//=============================================================================
void UninitGame(void)
{
	//�I�������|�[�Y
	UninitPause();
	//�I�������^�O
	UninitTagu();
	//�I�������^�C��
	UninitTime();
	//�I�������X�R�A
	UninitScore();
	//�I���������C�t
	UninitLife();
	//�I����������
	UninitExplosion();
	//�I�������g���b�v
	UninitTrap();
	//�I�������A�C�e��
	UninitItem();
	//�I�������₶�邵
	UninitYajirusi();
	//�I�������X�C�b�`
	UninitSwitch();
	//�I�������v���C���[
	UninitPlayer();
	//�I�������G�l�~�[
	UninitEnemy();
	//�I�������u���b�N
	UninitBlock();
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateGame(void)
{//Switch *pSwitch;
	//pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�̐ݒ�{�^���uP�v
		PaauseGame();
	}
	if (g_bPause == false)
	{
		//�X�V�����^�O
		UpdateTagu();
		//�X�V�����^�C��
		UpdateTime();
		//�X�V�����X�R�A
		UpdateScore();
		//�X�V�������C�t
		UpdateLife();
		//�X�V�����₶�邵
		UpdateYajirusi();
		//�X�V�����X�C�b�`
		UpdateSwitch();
		//�X�V��������
		UpdateExplosion();
		//�X�V�����g���b�v
		UpdateTrap();
		//�X�V�����A�C�e��
		UpdateItem();
		//�X�V�����G�l�~�[
		UpdateEnemy();
		//�X�V�����u���b�N
		UpdateBlock();
		//�X�V�����v���C���[
		UpdatePlayer();
		
		switch (g_GameState)
		{
		case  GAMESTATE0_NORMAL:			//�Q�[���ʏ펞
			g_nCounterGameState--;
			AddTime(g_nCounterGameState <= 60);

			break;
		case GAMESTATE_END:					//�Q�[���I����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GameState = GAMESTATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		case GAMESTATE_CLEAR://�N���A���
			g_nCounterGameState++;
			if (g_nCounterGameState >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GameState = GAMESTATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
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
//�`�揈��
//=============================================================================
void DrawGame(void)
{
	//�`�揈���^�O
	DrawTagu();
	//�`�揈���^�C��
	DrawTime();
	//�`�揈���X�R�A
	DrawScore();
	//�`�揈�����C�t
	DrawLife();
	//�`�揈���₶�邵
	DrawYajirusi();
	//�`�揈������
	DrawExplosion();
	//�`�揈���g���b�v
	DrawTrap();
	//�`�揈���A�C�e��
	DrawItem();
	//�`�揈���v���C���[
	DrawPlayer();
	//�`�揈���X�C�b�`
	DrawSwitch();
	//�`�揈���G�l�~�[
	DrawEnemy();
	//�`�揈���u���b�N
	DrawBlock();

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
void PaauseGame(void)
{
	g_bPause = g_bPause ^ 1;
}
void SetGame(void)
{

	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo / sizeof(BlockInfo); nCountBlock++)
	{
		//��
		SetBlock(D3DXVECTOR3(-100, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(500, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 580.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(3050.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 16);
		SetBlock(D3DXVECTOR3(6150.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 700.0f, 16);
		SetBlock(D3DXVECTOR3(5850.0f, 400.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300.0f, 700.0f, 16);
		//��
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1400.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(1950, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 400.0f, 16);
		SetBlock(D3DXVECTOR3(1900, 650, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 400.0f, 16);
		SetBlock(D3DXVECTOR3(2600, 610, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6300.0f, 30.0f, 17);
		SetBlock(D3DXVECTOR3(3900, 610, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(4900, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(5000, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 250.0f, 1);
	}
	for (int nCut = 0; nCut < 5; nCut++)
	{
		SetBlock(D3DXVECTOR3(800 + (nCut * 20.0f), 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1080 + (nCut * 40.0f), 250.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1200 + (nCut * 40.0f), 290.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
		SetBlock(D3DXVECTOR3(1380 + (nCut * 40.0f), 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
	}
	//�͂Ăȃu���b�N
	SetBlock(D3DXVECTOR3(900, 530.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 40.0f, 12);
	//�΂�
	SetBlock(D3DXVECTOR3(2650, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	//�΂�
	SetBlock(D3DXVECTOR3(1500, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	for (int nCut = 0; nCut < 2; nCut++)
	{
		//��
		SetTrap(D3DXVECTOR3(2000 + (nCut * 30.0f), 450.0f + (nCut * 5.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 0);
	}
	//�����鏰
	SetBlock(D3DXVECTOR3(2450, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 2);
	SetBlock(D3DXVECTOR3(2535, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 25.0f, 2);
	//�y�ǉ������
	SetBlock(D3DXVECTOR3(2400, 180, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 470.0f, 9);
	//�_���E
	SetBlock(D3DXVECTOR3(1350, 680, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 50.0f, 10);
	//��
	SetBlock(D3DXVECTOR3(2650, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(2750, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(3000, 350.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	for (int nCut = 0; nCut < 3; nCut++)
	{
		//�n��
		SetBlock(D3DXVECTOR3(2180, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2230, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2280, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 180, 1);
		SetBlock(D3DXVECTOR3(2330, 180.0f + (nCut * 120.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 180, 1);
	}
	for (int nCut = 0; nCut < 3; nCut++)
	{
		SetBlock(D3DXVECTOR3(2750.0f + (nCut * 100.0f), 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	}
	SetBlock(D3DXVECTOR3(2598.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	SetBlock(D3DXVECTOR3(2175.0f, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	SetBlock(D3DXVECTOR3(2632.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2.0f, 400.0f, 1);
	for (int nCut = 0; nCut < 4; nCut++)
	{
		SetBlock(D3DXVECTOR3(2600, 100.0f + (nCut * 100.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 100, 1);
	}
	SetBlock(D3DXVECTOR3(2750.0f, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	
	for (int nCut = 0; nCut < 2; nCut++)
	{
		//��ɏ������false
		SetBlock(D3DXVECTOR3(2800 + (nCut * 100.0f), 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 4);
	}
	SetBlock(D3DXVECTOR3(3800, 500.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(3900, 280.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(4050, 280.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 30.0f, 1);
	SetBlock(D3DXVECTOR3(4000, 480.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	
	SetBlock(D3DXVECTOR3(4050, 200.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 30.0f, 1);
	//�΂�
	SetBlock(D3DXVECTOR3(4150, 450, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 7);
	SetBlock(D3DXVECTOR3(4150, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 1);
	//��
	SetTrap(D3DXVECTOR3(4200, 320.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 0);
	//?�u���b�N�n�[�g
	SetBlock(D3DXVECTOR3(3950, 190, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 40.0f, 12);
	for (int nCut = 0; nCut < 20; nCut++)
	{
		//�j��
		SetTrap(D3DXVECTOR3(3900 + (nCut * 50.0f), 600.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 10.0f, 1);
	}
	//�j��
	SetTrap(D3DXVECTOR3(2900, 560.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 1);
	SetBlock(D3DXVECTOR3(4400, 400, 0), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(4600, 400, 0), D3DXVECTOR3(0.0f, 0.2f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(4800, 300, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 100.0f, 3);
	//N�L�[���������ɏオ����
	SetBlock(D3DXVECTOR3(5000, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 25);
	SetItem(4, D3DXVECTOR3(6050.0f, 130, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetItem(2, D3DXVECTOR3(3900.0f, 260, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X�e�[�W2��---------------------------------------------------------------------------
	SetBlock(D3DXVECTOR3(6100.0f, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 60.0f, 26);
	SetBlock(D3DXVECTOR3(6000.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 20, 1);
	
}