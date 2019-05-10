//=============================================================================
//
// �A�N�V�����Q�[������ [GAME2.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "game3.h"
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
}BlockInfo3;
//*****************************************************************************
//�O���[�o���ϐ�
//*****************************************************************************
GAME3STATE g_GAME3State = GAME3STATE_NONE; //�Q�[�����
bool g_bPause3;		//�|�[�Y
int g_CounterGAME3State;	//��ԊǗ��J�E���^�[
int g_nSwich3Counter;	//��ԊǗ��J�E���^�[
int g_nSwich3Counter3;	//��ԊǗ��J�E���^�[

BlockInfo3 g_aBlockInfo3[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//����������
//=============================================================================
void InitGame3(void)
{
	//�����������o�b�N�O���E���h
	InitBG();
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
	SetItem(2, D3DXVECTOR3(4100.0f, 160, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�Z�b�g�G�l�~�[
	SetEnemy(1, D3DXVECTOR3(3800.0f, 160.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
	SetEnemy(1, D3DXVECTOR3(3900.0f, 160.0f, 0), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 30, 60, 2);
	//�Z�b�g�Q�[��
	SetGAME3();
	g_GAME3State = GAME3STATE0_NORMAL;	//�ʏ��Ԃɐݒ�
	g_CounterGAME3State = 0;
	g_nSwich3Counter = 0;
	g_nSwich3Counter3 = 0;	//��ԊǗ��J�E���^�[
	 
	g_bPause3 = false;			//�|�[�Y���ĂȂ�
}
//=============================================================================
//�I������
//=============================================================================
void UninitGame3(void)
{
	//�I�������o�b�N�O���E���h
	UninitBG();
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
void UpdateGame3(void)
{
	Switch *pSwitch;
	pSwitch = GetSwitch();
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�Y�̐ݒ�{�^���uP�v
		
	}
	if (g_bPause3 == false)
	{
		//�X�V�����o�b�N�O���E���h
		UpdateBG();
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
		
		switch (g_GAME3State)
		{
		case  GAME3STATE0_NORMAL:			//�Q�[���ʏ펞
			g_CounterGAME3State--;
			AddTime(g_CounterGAME3State <= 60);

			break;
		case GAME3STATE_END:					//�Q�[���I����
			g_CounterGAME3State++;
			if (g_CounterGAME3State >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GAME3State = GAME3STATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		case GAME3STATE_CLEAR://�N���A���
			g_CounterGAME3State++;
			if (g_CounterGAME3State >= 20) //���񂾂Ƃ��̗]�C
			{
				g_GAME3State = GAME3STATE_NONE;
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
void DrawGame3(void)
{
	//�`�揈���o�b�N�O���E���h
	DrawBG();
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
	if (g_bPause3 == true)
	{
		//�`�揈���|�[�Y
		DrawPause();

	}
	//�`�揈���t�����gBG
	DrawFrontBG();
}
void SetGemeState3(GAME3STATE state)
{
	g_GAME3State = state;
	g_CounterGAME3State = 0;
}
GAME3STATE GetGAME3State(void)
{
	return g_GAME3State;
}
void SetGAME3(void)
{
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfo3 / sizeof(BlockInfo3); nCountBlock++)
	{
		//��
		SetBlock(D3DXVECTOR3(-100, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 600.0f, 300.0f, 0);
		//��
		SetBlock(D3DXVECTOR3(-100, 650.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5000.0f, 300.0f, 0);
	}
	//doa
	SetBlock(D3DXVECTOR3(430, 565.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 80.0f, 27);
	//�g�����|����
	SetBlock(D3DXVECTOR3(1900, 620, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80.0f, 40.0f, 7);
	SetBlock(D3DXVECTOR3(1400,70, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 530.0f, 16);
	//N�L�[���������ɏオ����
	SetBlock(D3DXVECTOR3(1405, 600, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 50.0f, 32);
	
	SetBlock(D3DXVECTOR3(2000, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 250.0f, 34);

	SetBlock(D3DXVECTOR3(2050, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 150.0f, 1);
	SetBlock(D3DXVECTOR3(2055, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 50.0f, 35);
	SetBlock(D3DXVECTOR3(2050, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 250.0f, 20.0f, 1);
	SetBlock(D3DXVECTOR3(2300, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 210.0f, 1);
}