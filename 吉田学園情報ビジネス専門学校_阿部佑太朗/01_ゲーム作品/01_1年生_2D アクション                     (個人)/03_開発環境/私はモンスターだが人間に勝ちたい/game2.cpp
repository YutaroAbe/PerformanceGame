//=============================================================================
//
// �A�N�V�����Q�[������ [GAME2.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game2.h"
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
#include "frontBG.h"

//*****************************************************************************
//�u���b�N�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfo2;
//*****************************************************************************
//�O���[�o���ϐ�
//*****************************************************************************
GAME2STATE g_GAME2State = GAME2STATE_NONE; //�Q�[�����
bool g_bPause2;		//�|�[�Y
int g_CounterGAME2State;	//��ԊǗ��J�E���^�[
int g_nSwich2Counter;	//��ԊǗ��J�E���^�[
int g_nSwich2Counter2;	//��ԊǗ��J�E���^�[

BlockInfo2 g_aBlockInfo2[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//����������
//=============================================================================
void InitGame2(void)
{
	//�����������t�����gBG
	InitFrontBG();
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
	
	SetItem(2, D3DXVECTOR3(3200.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetItem(2, D3DXVECTOR3(3600.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�Z�b�g�G�l�~�[
	SetEnemy(1, D3DXVECTOR3(3800.0f, 160.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3900.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);

	//�Z�b�g�Q�[��
	SetGAME2();
	g_GAME2State = GAME2STATE0_NORMAL;	//�ʏ��Ԃɐݒ�
	g_CounterGAME2State = 0;
	g_nSwich2Counter = 0;
	g_nSwich2Counter2 = 0;	//��ԊǗ��J�E���^�[
	 
	g_bPause2 = false;			//�|�[�Y���ĂȂ�
}
//=============================================================================
//�I������
//=============================================================================
void UninitGame2(void)
{
	//�I�������t�����gBG
	UninitFrontBG();
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
void UpdateGame2(void)
{
	Switch *pSwitch;
	pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�̐ݒ�{�^���uP�v
		PaauseGame2();
	}
	if (g_bPause2 == false)
	{
		//�X�V�����t�����gBG
		UpdateFrontBG();
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
		
		switch (g_GAME2State)
		{
		case  GAME2STATE0_NORMAL:			//�Q�[���ʏ펞
			g_CounterGAME2State--;
			AddTime(g_CounterGAME2State <= 60);

			break;
		case GAME2STATE_END:					//�Q�[���I����
			g_CounterGAME2State++;
			if (g_CounterGAME2State >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GAME2State = GAME2STATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		case GAME2STATE_CLEAR://�N���A���
			g_CounterGAME2State++;
			if (g_CounterGAME2State >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GAME2State = GAME2STATE_NONE;
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
void DrawGame2(void)
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
	//�`�揈���t�����gBG
	DrawFrontBG();
	if (g_bPause2 == true)
	{
		//�`�揈���|�[�Y
		DrawPause();

	}
}
void SetGemeState2(GAME2STATE state)
{
	g_GAME2State = state;
	g_CounterGAME2State = 0;
}
GAME2STATE GetGAME2State(void)
{
	return g_GAME2State;
}
void PaauseGame2(void)
{
	g_bPause2 = g_bPause2 ^ 1;
}
void SetGAME2(void)
{
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo2 / sizeof(BlockInfo2); nCountBlock++)
	{
		//��
		SetBlock(D3DXVECTOR3(-100, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(1100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20, 1);
		//��
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2950, 350.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1500.0f, 400.0f, 0);
		SetBlock(D3DXVECTOR3(-100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6300.0f, 30.0f, 17);
		SetBlock(D3DXVECTOR3(1300, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 430.0f, 16);
		SetBlock(D3DXVECTOR3(1480, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 500.0f, 16);
	}
	for (int nCut = 0; nCut < 4; nCut++)
	{
		//���t�����gBG
		SetFrontBG(1, D3DXVECTOR3(3300 + (nCut * 300.0f), 120, 0), 20, 80);
		SetFrontBG(0, D3DXVECTOR3(3100 + (nCut * 300.0f), 330.0f, 0), 20, 100);
	}
	for (int nCut = 0; nCut < 8; nCut++)
	{
		//�j��
		SetTrap(D3DXVECTOR3(1350, 230.0f + (nCut * 50.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 50.0f, 0);
	}
	for (int nCut = 0; nCut < 8; nCut++)
	{
		//�j��
		SetTrap(D3DXVECTOR3(1450, 100.0f + (nCut * 50.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 50.0f, 0);
	}
	for (int nCut = 0; nCut < 3; nCut++)
	{
		//��������false
		SetBlock(D3DXVECTOR3(1400, 250 + (nCut * 150.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 25.0f, 4);
	}
	for (int nCut = 0; nCut < 6; nCut++)
	{
		//�x���g�R���x�A
		SetBlock(D3DXVECTOR3(1600 + (nCut * 150.0f), 620, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 150.0f, 25.0f, 6);
	}
	//�󒆏�
	SetBlock(D3DXVECTOR3(1550, 390, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1790, 250, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1690, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	SetBlock(D3DXVECTOR3(1980, 380, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 40, 1);
	//�j��
	SetTrap(D3DXVECTOR3(1710, 300, 0), D3DXVECTOR3(0.0f, 0.3f, 0.0f), 35.0f, 50.0f, 3);
	//�g�����|����
	SetBlock(D3DXVECTOR3(1990, 340, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f,40.0f, 7);

	SetBlock(D3DXVECTOR3(1100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 40, 1);

	SetBlock(D3DXVECTOR3(2100, 220, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 40, 1);
	SetItem(2, D3DXVECTOR3(1630, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetYajirusi(0, D3DXVECTOR3(2250, 160, 0));
	SetSwitch(D3DXVECTOR3(2250, 180, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 13);
	SetSwitch(D3DXVECTOR3(1530, 160.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, 15);

	SetBlock(D3DXVECTOR3(1000, 500, 0), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(1000, 300, 0), D3DXVECTOR3(0.0f, 0.6f, 0.0f), 100.0f, 40.0f, 3);
	SetBlock(D3DXVECTOR3(1150, 350, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 40.0f, 3);
	for (int nCut = 0; nCut < 7; nCut++)
	{//�K�i
		SetBlock(D3DXVECTOR3(4450 + (nCut * 50.0f), 350.0f - (nCut * 30.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
	}
	SetBlock(D3DXVECTOR3(3100, 70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 230.0f, 16);
	//N�L�[���������ɏオ����
	SetBlock(D3DXVECTOR3(3100, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 30);
	SetBlock(D3DXVECTOR3(4800, 180.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 20.0f, 1);
	SetBlock(D3DXVECTOR3(4950, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 80.0f, 1);
	SetItem(4, D3DXVECTOR3(4750.0f, 130, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBlock(D3DXVECTOR3(4900, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 80.0f, 27);
}