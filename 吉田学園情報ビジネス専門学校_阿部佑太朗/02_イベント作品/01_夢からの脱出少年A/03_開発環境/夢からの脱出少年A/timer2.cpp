//=============================================================================
//
// �^�C�}�[���� [timer2.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "timer2.h"
//#include "dice.h"
//#include "game.h"
//#include "meter.h"
#include "ColorBall.h"
//=============================================================================
//	�v���g�^�C�v�錾
//=============================================================================
void MakeTimer2Font(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer2 = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimer2 = NULL;						//�e�N�X�`���ւ̃|�C���^

LPD3DXFONT	pTimer2Font = NULL;	// �t�H���g�I�u�W�F�N�g
D3DXCOLOR g_Timer2FontColor;		//�t�H���g�̐F
char g_Timer2Text[256];	//�t�H���g�̕���[256�ŌŒ�]

RECT g_Timer2Rect = {	//�t�H���g��u���͈�
	1000,		// �����x���W
	500,			// �����y���W
	1600,		// �E����x���W
	670			// �E����y���W
};

int g_nCountTimer2;		//�^�C�}�[�J�E���g�p
int g_nDiceTime2;		//�T�C�R���̃^�C�}�[

bool g_bSetTimer2Flag;		//�^�C�}�[�̃J�E���g����

//=============================================================================
//	����������
//=============================================================================
void InitTimer2(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_nCountTimer2 = 0;
	g_nDiceTime2 = -1;
	g_Timer2FontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);
	g_bSetTimer2Flag = true;
	//�t�H���g�̍쐬
	MakeTimer2Font(pDevice);

}

//=============================================================================
//	�I������
//=============================================================================
void UninitTimer2(void)
{
	//�t�H���g�̉��
	if (pTimer2Font != NULL)
	{
		pTimer2Font->Release();
		pTimer2Font = NULL;
	}

}

//=============================================================================
//	�X�V����
//=============================================================================
void UpdateTimer2(void)
{
	COLORBALL *pColBall;
	pColBall = GetColorBall();

	if (g_bSetTimer2Flag == true && g_nDiceTime2 != -1 && pColBall->state == COLORBALLSTATE_STOP)
	{
		g_nCountTimer2++;
		if (g_nCountTimer2 == 60)
		{
			//DeleteDice(2);
		}
		//�^�C�}�[�̃J�E���g�_�E��
		if (g_nCountTimer2 % TIMER_INTERVAL == 0)
		{
			g_nDiceTime2--;

		}

		//�t�H���g�̐F�̒���
		if (g_nDiceTime2 > 4)
		{
			g_Timer2FontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);

		}
		else
		{
			g_Timer2FontColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		}
		/*if (GetMeterSize() <= 0)
		{
			g_bSetTimer2Flag = false;
			g_nDiceTime2 = -1;
			SetGameState(GAMESTATE_OVER);
		}*/

		//if (GetKeyboardTrigger(DIK_L) == true)		//DEBUG
		//{
		//	g_nDiceTime2 = -1;
		//	SetDice(2);

		//}
		if (g_nDiceTime2 == 0 && g_nCountTimer2 % TIMER_INTERVAL == 59)
		{
			g_nDiceTime2 = 10;
			//SetDice(2);
			//SetTurnState(TURNSTATE_END);
			g_Timer2FontColor = D3DXCOLOR(0.4f, 1.0f, 1.0f, 1.0f);
		}

		//�o�͂��镶�����ݒ�
		wsprintf(g_Timer2Text, "%d.%d", g_nDiceTime2, 60 - (g_nCountTimer2 % TIMER_INTERVAL));
	}

}

//=============================================================================
//	�`�揈��
//=============================================================================
void DrawTimer2(void)
{
	if (g_nDiceTime2 != -1)
	{//�v���C���͕\��
	 //�t�H���g�̕`��
		pTimer2Font->DrawText(
			NULL,								// NULL
			g_Timer2Text,						// �`�悷��e�L�X�g
			-1,									// �`�悷�镶����(-1�ŏ�̃e�L�X�g�̕��������擾���Ă����)
			&g_Timer2Rect,						// �`��͈�(��Œ�`����RECT�^�̕ϐ��̃|�C���^������)
			DT_VCENTER | DT_LEFT,				// �`��I�v�V����
			g_Timer2FontColor					// �F�w��
		);
	}

}

//=============================================================================
//	�^�C�}�[�Z�b�g
//=============================================================================
void SetTimer2(int nTime)
{
	//�擾�����o�ڂɉ����Ď��Ԃ����߁A�J�E���g���J�n����
	g_nDiceTime2 = nTime /** TIMER_COUNT_COEFFICIENT*/ - 1;
	g_nCountTimer2 = 0;

	//�o�͂��镶�����ݒ�
	wsprintf(g_Timer2Text, "%d.%d", g_nDiceTime2, 60 - (g_nCountTimer2 % TIMER_INTERVAL));

}

//=============================================================================
//	�t�H���g�̍쐬
//=============================================================================
void MakeTimer2Font(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// �f�o�C�X�̃|�C���^
		80,							// ����
		40,							// ��
		FW_BLACK,					// �t�H���g�̑���
		NULL,						// ����
		FALSE,						// �Α�(TRUE��on,FALSE��off)
		SHIFTJIS_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x(OUT_DEFAULT_PRECIS�ŌŒ�)
		PROOF_QUALITY,				// �����̕i��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~���̃C���f�b�N�X
		TEXT("Meiryo UI"),			// �t�H���g��(�󔒁A�啶�����܂߂Đ��m�ɓ��͂��邱��)
		&pTimer2Font);				// �t�H���g�̃|�C���^

}

//=============================================================================
//	�^�C�}�[�̎擾
//=============================================================================
int GetTimer2(void)
{
	return g_nDiceTime2;
}

//=============================================================================
//	�^�C�}�[�̃J�E���g�t���O�̏�Ԃ��擾
//=============================================================================
bool GetSetTimer2Flag(void)
{
	return g_bSetTimer2Flag;
}
