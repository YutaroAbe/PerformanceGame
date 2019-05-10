//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "tutorial.h"
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
#include "explosion.h"
#include "life.h"
#include "nlife.h"
#include "tagu.h"

//*****************************************************************************
//�u���b�N�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
}BlockInfoTUTO;
//*****************************************************************************
//�O���[�o���ϐ�
//*****************************************************************************
TUTOSTATE g_TutorialState = TUTOSTATE_NONE; //�Q�[�����
bool g_tPause;		//�|�[�Y
int g_nCounterTutorialState;	//��ԊǗ��J�E���^�[
BlockInfoTUTO g_aBlockInfoTUTO[] =
{
	{D3DXVECTOR3(0, 0, 0), 0, 0, 0 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 16 },
	{D3DXVECTOR3(0, 0, 0), 0, 0, 17 }
};

//=============================================================================
//����������
//=============================================================================
void InitTutorial(void)
{
	//�����������o�b�N�O���E���h
	InitBG();
	//�����������|�[�Y
	//InitPause();
	//�����������^�O
	//InitTagu();
	//�������^�C��
	//InitTime();
	//�������X�R�A
	//InitScore();
	//����������
	InitExplosion();
	//���������C�t
	//InitLife();
	//�������A�C�e��
	InitItem();
	//�����������X�C�b�`
	InitSwitch();
	//�����������v���C���[
	InitPlayer();
	//�����������G�l�~�[
	//InitEnemy();
	//�����������u���b�N
	InitBlock();

	//�Z�b�g�Q�[��
	SetTutorial();
	
	g_TutorialState = TUTOSTATE_NONE;	//�ʏ��Ԃɐݒ�
	g_nCounterTutorialState = 0;

	g_tPause = false;			//�|�[�Y���ĂȂ�
}
//=============================================================================
//�I������
//=============================================================================
void UninitTutorial(void)
{
		//�I�������o�b�N�O���E���h
		UninitBG();
		//�I�������|�[�Y
	//	UninitPause();
		//�I�������^�O
		//UninitTagu();
		//�I�������^�C��
		//UninitTime();
		//�I�������X�R�A
		//UninitScore();
		//�I����������
		UninitExplosion();
		//�I�������A�C�e��
		UninitItem();
		//�I�������X�C�b�`
		UninitSwitch();
		//�I�������v���C���[
		UninitPlayer();
		//�I�������G�l�~�[
		//UninitEnemy();
		//�I�������u���b�N
		UninitBlock();
}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateTutorial(void)
{
		//�X�V�����o�b�N�O���E���h
		UpdateBG();
		//�X�V�����^�O
		//UpdateTagu();
		//�X�V�����^�C��
		//UpdateTime();
		//�X�V�����X�R�A
		//UpdateScore();
		//�X�V��������
		UpdateExplosion();
		//�X�V�������C�t
		//UpdateLife();
		//�X�V�����X�C�b�`
		UpdateSwitch();
		//�X�V�����A�C�e��
		UpdateItem();
		//�X�V�����G�l�~�[
		//UpdateEnemy();
		//�X�V�����v���C���[
		UpdatePlayer();
		//�X�V�����u���b�N
		UpdateBlock();
		switch (g_TutorialState)
		{
		case TUTOSTATE_NORMAL:			//�Q�[���ʏ펞
			g_nCounterTutorialState--;
			AddTime(g_nCounterTutorialState <= 60);

			break;
		case TUTOSTATE_END:					//�Q�[���I����
			g_nCounterTutorialState++;
			if (g_nCounterTutorialState >= 20) //���񂾂Ƃ��̗]�C
			{
				g_TutorialState = TUTOSTATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_TUTO);
			}
			break;
		case TUTOSTATE_CLEAR://�N���A���
			g_nCounterTutorialState++;
			if (g_nCounterTutorialState >= 20) //���񂾂Ƃ��̗]�C
			{
				g_TutorialState = TUTOSTATE_NONE;
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
		}
}
//=============================================================================
//�`�揈��
//=============================================================================
void DrawTutorial(void)
{
	//�`�揈���o�b�N�O���E���h
	DrawBG();
	//�`�揈���^�O
	//DrawTagu();
	//�`�揈���^�C��
	//DrawTime();
	//�`�揈���X�R�A
	//DrawScore();
	//�`�揈������
	DrawExplosion();
	//�`�揈�����C�t
	//DrawLife();
	//�`�揈���A�C�e��
	DrawItem();
	//�`�揈���v���C���[
	DrawPlayer();
	//�`�揈���X�C�b�`
	DrawSwitch();
	//�`�揈���G�l�~�[
	//DrawEnemy();
	//�`�揈���u���b�N
	DrawBlock();
}
void SetTutoState(TUTOSTATE state)
{
	g_TutorialState = state;
	g_nCounterTutorialState = 0;
}
TUTOSTATE GetTutoState(void)
{
	return g_TutorialState;
}
void SetTutorial(void)
{
	
	//�E�֐i�݂��������\��
	SetBlock(D3DXVECTOR3(0, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 605.0f, 18);
	//WASD�Ŕ�
	SetBlock(D3DXVECTOR3(800, -100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 19);
	//SPACE�Ŕ�
	SetBlock(D3DXVECTOR3(1200, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 20);
	//�X�C�b�`�Ŕ�
	SetBlock(D3DXVECTOR3(1600, -100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 350.0f, 400.0f, 21);
	//SWITCH
	SetSwitch(D3DXVECTOR3(1800, 620.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 25.0f, 25.0f, 7);
	//N�L�[��UP
	SetBlock(D3DXVECTOR3(2505, 570.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 45.0f, 80.0f, 11);
	//�X�C�b�`�Ŕ�
	SetBlock(D3DXVECTOR3(2000, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 22);
	//�|�[�Y�Ŕ�
	SetBlock(D3DXVECTOR3(650, 300, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f, 23);
	//�G����
	SetBlock(D3DXVECTOR3(2605, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 28);
	//���C�t����
	SetBlock(D3DXVECTOR3(2755, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 300.0f, 29);
	for (int nCountBlock = 0; nCountBlock < sizeof g_aBlockInfoTUTO / sizeof(BlockInfoTUTO); nCountBlock++)
	{
		//��
		SetBlock(D3DXVECTOR3(500, 100, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 1);
		SetBlock(D3DXVECTOR3(500, 400, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 300.0f, 1);		
		SetBlock(D3DXVECTOR3(-100, 680.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3000.0f, 300.0f, 0);
		SetBlock(D3DXVECTOR3(2500, 0.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 580.0f, 1);
		SetBlock(D3DXVECTOR3(2550, 560, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200, 20.0f, 1);
		SetBlock(D3DXVECTOR3(2750, 560, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 120.0f, 1);
		SetBlock(D3DXVECTOR3(2700, 600, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 80.0f, 14);
	}
	
	//�Z���N�g��ʂ�---------------------------------------------------------------------------
	SetBlock(D3DXVECTOR3(4150, 100.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 60.0f, 14);
	
}