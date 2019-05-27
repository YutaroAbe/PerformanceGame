//=============================================================================
//
// ���f������ [model.cpp]
// Author : �ړc�@��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "time.h"

#include "input.h"
#include "camera.h"
#include "poker.h"
#include "cardModel.h"
#include "timer.h"
#include "3DUi.h"
#include "PlayerShow.h"
#include "ui.h"
#include "gamefade.h"
#include "sound.h"
#include "gamepad.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_CARD		"data/MODEL/card.x"			// �J�[�h�̃��f��
#define TEX_BRAVE		"data/TEXTURE/breve.png"	// �E�҃}�[�N�̃e�N�X�`��
#define TEX_KING		"data/TEXTURE/king.png"		// ���l�}�[�N�̃e�N�X�`��
#define TEX_DEVIL		"data/TEXTURE/devil.png"	// �����}�[�N�̃e�N�X�`��
#define TEX_HEART		"data/TEXTURE/heart.png"	// �n�[�g�}�[�N�̃e�N�X�`��
#define TEX_JOKER		"data/TEXTURE/joker.png"	// �W���[�J�[�}�[�N�̃e�N�X�`��
#define PRESS_CNT				(30)		// �v���X�̃J�E���g
#define POS_1P_XFIRST			(-400.0f)	// ����X�ʒu
#define POS_1P_Z_1				(-100.0f)	// Z�ʒu
#define POS_1P_XSPACE_1			(-150.0f)	// X�̃X�y�[�X
#define POS_LEFT_1P_1			D3DXVECTOR3(POS_1P_XFIRST,0.0f,POS_1P_Z_1)								// 1P ���̈ʒu
#define POS_CENTERLEFT_1P_1		D3DXVECTOR3((POS_1P_XFIRST - POS_1P_XSPACE_1), 0.0f, POS_1P_Z_1)		// 1P �Z���^�[���̈ʒu
#define POS_CENTER_1P_1			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 2)), 0.0f, POS_1P_Z_1)	// 1P �Z���^�[�̈ʒu
#define POS_RIGHTCENTER_1P_1	D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 3)), 0.0f, POS_1P_Z_1)	// 1P �Z���^�[�E�̈ʒu
#define POS_RIGHT_1P_1			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 4)), 0.0f, POS_1P_Z_1)	// 1P �E�̈ʒu

#define POS_1P_XSPACE_2			(-75.0f)	// X�̃X�y�[�X
#define POS_1P_Z_2				(-200.0f)	// Z�ʒu
#define POS_LEFT_1P_2			D3DXVECTOR3(POS_1P_XFIRST,0.0f,POS_1P_Z_2)								// 1P ���̈ʒu
#define POS_CENTERLEFT_1P_2		D3DXVECTOR3((POS_1P_XFIRST - POS_1P_XSPACE_2), 0.0f, POS_1P_Z_2)		// 1P �Z���^�[���̈ʒu
#define POS_CENTER_1P_2			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 2)), 0.0f, POS_1P_Z_2)	// 1P �Z���^�[�̈ʒu
#define POS_RIGHTCENTER_1P_2	D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 3)), 0.0f, POS_1P_Z_2)	// 1P �Z���^�[�E�̈ʒu
#define POS_RIGHT_1P_2			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 4)), 0.0f, POS_1P_Z_2)	// 1P �E�̈ʒu

#define POS_2P_XFIRST_1			(-400.0f)	// ����X�ʒu
#define POS_2P_Z_1				(150.0f)	// Z�ʒu
#define POS_2P_XSPACE_1			(-150.0f)	// X�̃X�y�[�X
#define POS_LEFT_2P_1			D3DXVECTOR3(POS_2P_XFIRST_1,0.0f,POS_2P_Z_1)								// 2P ���̈ʒu
#define POS_CENTERLEFT_2P_1		D3DXVECTOR3((POS_2P_XFIRST_1 - POS_2P_XSPACE_1), 0.0f, POS_2P_Z_1)			// 2P �Z���^�[���̈ʒu
#define POS_CENTER_2P_1			D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 2)), 0.0f, POS_2P_Z_1)	// 2P �Z���^�[�̈ʒu
#define POS_RIGHTCENTER_2P_1	D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 3)), 0.0f, POS_2P_Z_1)	// 2P �Z���^�[�E�̈ʒu
#define POS_RIGHT_2P_1			D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 4)), 0.0f, POS_2P_Z_1)	// 2P �E�̈ʒu

#define POS_2P_XFIRST_2			(95.0f)		// ����X�ʒu
#define POS_2P_XSPACE_2			(-75.0f)	// X�̃X�y�[�X
#define POS_2P_Z_2				(-200.0f)	// Z�ʒu
#define POS_LEFT_2P_2			D3DXVECTOR3(POS_2P_XFIRST_2,0.0f,POS_2P_Z_2)								// 2P ���̈ʒu
#define POS_CENTERLEFT_2P_2		D3DXVECTOR3((POS_2P_XFIRST_2 - POS_2P_XSPACE_2), 0.0f, POS_2P_Z_2)			// 2P �Z���^�[���̈ʒu
#define POS_CENTER_2P_2			D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 2)), 0.0f, POS_2P_Z_2)	// 2P �Z���^�[�̈ʒu
#define POS_RIGHTCENTER_2P_2	D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 3)), 0.0f, POS_2P_Z_2)	// 2P �Z���^�[�E�̈ʒu
#define POS_RIGHT_2P_2			D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 4)), 0.0f, POS_2P_Z_2)	// 2P �E�̈ʒu

#define DECK_POS_Z				(POS_1P_Z_1 + POS_2P_Z_1 / 2) - (POS_1P_Z_1 / 2)							// �R�D�̈ʒu(Z)
#define DECK_POS				D3DXVECTOR3(POS_1P_XFIRST - (POS_1P_XSPACE_1 * 2), 0.0f, DECK_POS_Z)		// �R�D�̈ʒu
#define SELECT_POS				(30.0f)		// �I�������J�[�h���ǂ��܂ňړ����邩
#define ROT_SPEED				(0.1f)		// ��]���鑬��
#define WIDTH					(5.0f)		// �ʒu����̕�
#define MAX_SET_CARD			(5)			// �z�z�J�[�h�̍ő�
#define MAX_MODEL				(1)			// �ǂݍ��ރ��f���̍ő吔
#define MAX_BRAVE				(13)		// �E�҃J�[�h�̖���
#define MAX_ROUND				(5)			// �ő僉�E���h��
#define MAX_KING				(13)		// ���l�J�[�h�̖���
#define MAX_DEVIL				(13)		// �����J�[�h�̖���
#define MAX_HEART				(13)		// �񕜃J�[�h�̖���
#define MAX_JOKER				(2)			// �W���[�J�[�̖���
#define MAX_CARD				(MAX_BRAVE + MAX_KING + MAX_DEVIL + MAX_HEART+ MAX_JOKER)	// �S�J�[�h�̖���
#define MAX_STATUS				(PARAMETER_MAX)	// �U���́@�h���
#define AUTO_FADE_TIME			(120)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_nStatus1P[STATUS_MAX]; // 1P�̃X�e�[�^�X�Ǘ�
int g_nStatus2P[STATUS_MAX]; // 2P�̃X�e�[�^�X�Ǘ�
int g_nNowPlayer;
int g_nSelectCard;			// ��������J�[�h�̔ԍ�
int g_nTwoRandType;			// �c�[�y�A���ɂǂ��炩�̃^�C�v�Ɋ��蓖�Ă�
int g_nData[MAX_PLAYER];	// �𔻒�p�̐������i�[����
int g_nPressCnt;			// �v���X�̃J�E���^�[
int g_nSetCnt;				// �J�[�h��z�z����J�E���g
int g_nNumBrave1P;			// �E�҂̖���
int g_nNumKing1P;			// ���l�̖���
int g_nNumDevil1P;			// �����̖���
int g_nNumCommoner1P;		// �񕜂̖���
int g_nNumJoker1P;			// �W���[�J�[�̖���
int g_nNumBrave2P;			// �E�҂̖���
int g_nNumKing2P;			// ���l�̖���
int g_nNumDevil2P;			// �����̖���
int g_nNumCommoner2P;		// �񕜂̖���
int g_nNumJoker2P;			// �W���[�J�[�̖���
int g_nFadeCnt;				// �v���C���[�`�F���W�܂ł̃J�E���g
bool g_bTwoPair1P;			// �ǂ̃^�C�v���m�Ńc�[�y�A�ɂȂ��Ă��邩
bool g_bTwoPair2P;			// �ǂ̃^�C�v���m�Ńc�[�y�A�ɂȂ��Ă��邩
bool g_bSet;				// �z�z�ς݂��ǂ���
bool g_bChangePlayer;		// �v���C���[����コ�ꂽ��
bool g_bRotFin;				// ��]���I��������
bool g_bFinish;				// �|�[�J�[���I��������
CARDSIDE g_PokerState;		// �Q�[���̏�Ԕ��f
CARDTYPE g_aType[MAX_PLAYER];				// ���݂̃^�C�v��ۑ�����
D3DXVECTOR3	g_ChangePos;					// �R�D�̈ʒu
CardModel	g_aCardModel1P[MAX_SET_CARD];	// 1P�̏��
CardModel	g_aCardModel2P[MAX_SET_CARD];	// 2P�̏��
CardModel	g_CardDeck;						// �R�D�̏��
											// �ǂݍ��ރI�u�W�F�N�g���̐ݒ�
CardData		g_apCardModel[TYPE_MAX] = {};
D3DXVECTOR3		g_aDestCard1P[CARD_POS_MAX] =
{// 1P�̈ʒu�ݒ�
	POS_LEFT_1P_1,				// 1P ��
	POS_CENTERLEFT_1P_1,		// 1P �Z���^�[��
	POS_CENTER_1P_1,			// 1P �Z���^�[
	POS_RIGHTCENTER_1P_1,		// 1P �Z���^�[�E
	POS_RIGHT_1P_1,				// 1P �E
};
D3DXVECTOR3		g_aDestCard2P[CARD_POS_MAX] =
{// 2P�̈ʒu�ݒ�
	POS_RIGHT_2P_1,				// 2P ��
	POS_RIGHTCENTER_2P_1,		// 2P �Z���^�[��
	POS_CENTER_2P_1,			// 2P �Z���^�[
	POS_CENTERLEFT_2P_1,		// 2P �Z���^�[�E
	POS_LEFT_2P_1,				// 2P �E
};
D3DXVECTOR3		g_aShowCard1P[CARD_POS_MAX] =
{// 1P�̈ʒu�ݒ�
	POS_LEFT_1P_2,				// 1P ��
	POS_CENTERLEFT_1P_2,		// 1P �Z���^�[��
	POS_CENTER_1P_2,			// 1P �Z���^�[
	POS_RIGHTCENTER_1P_2,		// 1P �Z���^�[�E
	POS_RIGHT_1P_2,				// 1P �E
};
D3DXVECTOR3		g_aShowCard2P[CARD_POS_MAX] =
{// 2P�̈ʒu�ݒ�
	POS_RIGHT_2P_2,				// 2P ��
	POS_RIGHTCENTER_2P_2,		// 2P �Z���^�[��
	POS_CENTER_2P_2,			// 2P �Z���^�[
	POS_CENTERLEFT_2P_2,		// 2P �Z���^�[�E
	POS_LEFT_2P_2,				// 2P �E
};
//=============================================================================
// ����������
//=============================================================================
void InitCardModel(void)
{
	srand((unsigned int)time(0));	// �N�����鎞�ԂŒl��ς���
									//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���f���̓ǂݍ���
	LoadModel(pDevice);

	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{// 1P�̏�񏉊���
		g_aCardModel1P[nCntModel].type = TYPE_BRAVE;							// ���
		g_aCardModel1P[nCntModel].ModelType = 0;								// �`��p
		g_aCardModel1P[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
		g_aCardModel1P[nCntModel].rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);			// ����
		g_aCardModel1P[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
		g_aCardModel1P[nCntModel].bUse = false;									// �g�p���Ă��邩
		g_aCardModel1P[nCntModel].distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		g_aCardModel1P[nCntModel].bMove = false;								// �ړ����Ă��邩
		g_aCardModel1P[nCntModel].bSelect = false;								// �I������Ă��邩
		g_aCardModel1P[nCntModel].bChange = false;								// �`�F���W���Ă��邩
	}
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{// 2P�̏�񏉊���
		g_aCardModel2P[nCntModel].type = TYPE_BRAVE;									// ���
		g_aCardModel2P[nCntModel].ModelType = 0;										// �`��p
		g_aCardModel2P[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
		g_aCardModel2P[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
		g_aCardModel2P[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ���
		g_aCardModel2P[nCntModel].bUse = false;											// �g�p���Ă��邩
		g_aCardModel2P[nCntModel].distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
		g_aCardModel2P[nCntModel].bMove = false;										// �ړ����Ă��邩
		g_aCardModel2P[nCntModel].bSelect = false;										// �I������Ă��邩
		g_aCardModel2P[nCntModel].bChange = false;										// �`�F���W���Ă��邩
	}
	// �R�D�̏�񏉊���
	g_CardDeck.pos = DECK_POS;	// �ʒu
	g_ChangePos = DECK_POS;		// �R�D�̈ʒu
	g_CardDeck.bUse = false;	// �g�p���Ă��邩
								// �c�[�y�A���f�p
	g_bTwoPair1P = false;	// �ǂ̃^�C�v���m�Ńc�[�y�A�ɂȂ��Ă��邩
	g_bTwoPair2P = false;	// �ǂ̃^�C�v���m�Ńc�[�y�A�ɂȂ��Ă��邩
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_nData[nCntPlayer] = 0;			// �𔻒�p
		g_aType[nCntPlayer] = TYPE_BRAVE;	// ���݂̃^�C�v��ۑ�����
	}
	g_bSet = false;					// �J�[�h���Z�b�g����Ă��邩
	g_bChangePlayer = false;		// �v���C���[����コ�ꂽ��
	g_bRotFin = false;				// ��]���I�������
	g_PokerState = CARD_SIDE_1P;	// �|�[�J�[�̏��
	g_nFadeCnt = 0;					// �����Ńt�F�[�h����J�E���g
	g_nSelectCard = 0;				// ���Ԃ̃J�[�h���I�΂�Ă��邩
	g_nTwoRandType = 0;				// �c�[�y�A���ɂǂ��炩�����_���Ŋ���U��
	g_nPressCnt = 0;				// �J�[�h�I���̃v���X�J�E���g
	g_nSetCnt = 0;					// �J�[�h��z��J�E���g
	g_nNumBrave1P = 0;				// �E�҂̐�
	g_nNumKing1P = 0;				// ���l�̐�
	g_nNumDevil1P = 0;				// �����̐�
	g_nNumCommoner1P = 0;			// �����̐�
	g_nNumJoker1P = 0;				// �P�̐�
	g_nNumBrave2P = 0;				// �E�҂̐�
	g_nNumKing2P = 0;				// ���l�̐�
	g_nNumDevil2P = 0;				// �����̐�
	g_nNumCommoner2P = 0;			// �����̐�
	g_nNumJoker2P = 0;				// �P�̐�
	g_nNowPlayer = 1;
}
//=============================================================================
// �I������
//=============================================================================
void UninitCardModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// ���b�V���̊J��
		if (g_apCardModel[nCntModel].pMesh != NULL)
		{
			g_apCardModel[nCntModel].pMesh->Release();
			g_apCardModel[nCntModel].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_apCardModel[nCntModel].pBuffMat != NULL)
		{
			g_apCardModel[nCntModel].pBuffMat->Release();
			g_apCardModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateCardModel(void)
{
	bool bReady = GetReady();
	GAMEMODE GameMode = GetGameMode();
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();
	Timer *pTimer = GetTimer();

	if (GameMode == GAMEMODE_POKER)
	{
		g_CardDeck.bUse = true;
		SetCard();	// �J�[�h�Z�b�g
		for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
		{
			if (g_aCardModel1P[nCntModel].pos.x > g_aCardModel1P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel1P[nCntModel].pos.x < g_aCardModel1P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel1P[nCntModel].pos.z > g_aCardModel1P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel1P[nCntModel].pos.z < g_aCardModel1P[nCntModel].DestPos.z + WIDTH)
			{// �J�[�h�̔���
				g_aCardModel1P[nCntModel].bMove = false;
			}
			if (g_aCardModel2P[nCntModel].pos.x > g_aCardModel2P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel2P[nCntModel].pos.x < g_aCardModel2P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel2P[nCntModel].pos.z > g_aCardModel2P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel2P[nCntModel].pos.z < g_aCardModel2P[nCntModel].DestPos.z + WIDTH)
			{// �J�[�h�̔���
				g_aCardModel2P[nCntModel].bMove = false;
			}
			// �ʒu�X�V
			if (g_aCardModel1P[nCntModel].bMove == true)
			{
				g_aCardModel1P[nCntModel].pos += g_aCardModel1P[nCntModel].move;
			}
			if (g_aCardModel2P[nCntModel].bMove == true)
			{
				g_aCardModel2P[nCntModel].pos += g_aCardModel2P[nCntModel].move;
			}
		}
		if (bReady == true)
		{
			MoveCursor();	// �J�[�\���ړ�
		}
		if (pTimer->bFinish == false)
		{
			//=============== [ 1P���� ] ===============//
			if (g_PokerState == CARD_SIDE_1P)
			{
				g_nNowPlayer = 0;
				for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
				{
					if (bReady == true)
					{
						if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP))
						{// ��������J�[�h��I��
							SelectCard1P((CARDPOS)g_nSelectCard);
							PlaySound(SOUND_LABEL_SE_CARD_SET);
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P)
						{// �����̃J�[�h�͑S�ĕ\�ɂ���
							g_aCardModel1P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel1P[nCntModel].rot.z >= D3DX_PI)
							{
								g_aCardModel1P[nCntModel].rot.z = D3DX_PI;
								g_bRotFin = true;
							}
						}
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P && g_aCardModel2P[nCntModel].PosType == CARD_POS_RIGHT)
						{// ����J�[�h�̉E�[��\�ɂ���
							g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel2P[nCntModel].rot.z >= D3DX_PI)
							{
								g_aCardModel2P[nCntModel].rot.z = D3DX_PI;
								g_bRotFin = true;
							}
						}
					}
					if (g_bRotFin == true)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P,ELECOM_A))
						{// �J�[�h���R�D�ɖ߂�(����)
							PlaySound(SOUND_LABEL_SE_CARD_SELECT);
							ChangeCard1P();
							pTimer->nTime = 0;
						}
					}
				}
				if (bReady == false)
				{
					SetReady(false);
				}
			}
			//=============== [ 2P���� ] ===============//
			if (g_PokerState == CARD_SIDE_2P)
			{
				g_nNowPlayer = 1;
				for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
				{
					if (bReady == true)
					{
						if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP))
						{// ��������J�[�h��I��
							SelectCard2P((CARDPOS)g_nSelectCard);
							PlaySound(SOUND_LABEL_SE_CARD_SET);
						}
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P)
						{// �����̃J�[�h�͑S�ĕ\�ɂ���
							g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel2P[nCntModel].rot.z >= -D3DX_PI)
							{
								g_aCardModel2P[nCntModel].rot.z = -D3DX_PI;
								g_bRotFin = true;
							}
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType == CARD_POS_RIGHT)
						{// ����J�[�h�̉E�[�ȊO�𗠂ɂ���
							g_aCardModel1P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel1P[nCntModel].rot.z >= -D3DX_PI)
							{
								g_aCardModel1P[nCntModel].rot.z = -D3DX_PI;
								g_bRotFin = true;
							}
						}
					}
					if (bReady == false)
					{
						SetReady(false);
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P)
						{// �����̃J�[�h�͑S�ĕ\�ɂ���
							g_aCardModel2P[nCntModel].rot.z = -D3DX_PI * 2;
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType == CARD_POS_RIGHT)
						{// ����J�[�h�̉E�[�ȊO�𗠂ɂ���
							g_aCardModel1P[nCntModel].rot.z = -D3DX_PI * 2;
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType != CARD_POS_RIGHT)
						{// ����J�[�h�̉E�[�ȊO�𗠂ɂ���
							g_aCardModel1P[nCntModel].rot.z = D3DX_PI * 2;
						}
					}
					if (g_bRotFin == true)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A))
						{// �J�[�h���R�D�ɖ߂�(����)
							PlaySound(SOUND_LABEL_SE_CARD_SELECT);
							ChangeCard2P();
							pTimer->nTime = 0;
						}
					}
				}
			}
		}
		if (pTimer->nTime == 0)
		{// �������ԂɂȂ�����
			g_nFadeCnt++;
			if (pTimer->bFinish == false)
			{
				if (g_PokerState == CARD_SIDE_1P)
				{
					ChangeCard1P();					// �J�[�h���R�D�ɖ߂�
					ExchangeCard1P();				// �J�[�h����
					CheckHand1P();					// ���m�F
					CheckType1P();					// �^�C�v�m�F
					WriteText1P();					// �^�C�v�ۑ�
				}
				else if (g_PokerState == CARD_SIDE_2P)
				{
					ChangeCard2P();					// �J�[�h���R�D�ɖ߂�
					ExchangeCard2P();				// �J�[�h����
					CheckHand2P();					// ���m�F
					CheckType2P();					// �^�C�v�m�F
					WriteText2P();					// �^�C�v�ۑ�
				}
				pTimer->bFinish = true;
			}
			g_nSelectCard = 0;
			if (g_nFadeCnt >= AUTO_FADE_TIME)
			{
				switch (g_PokerState)
				{
				case CARD_SIDE_1P:
					if (pGameFade == GAMEFADE_NONE)
					{
						SetPokerFade(CARD_SIDE_2P);
					}
					break;
				case CARD_SIDE_2P:
					if (pGameFade == GAMEFADE_IN)
					{
						SetReady(false);
						pTimer->nTime = MAX_TIME;
						pTimer->bFinish = false;
						g_bRotFin = false;
						g_nFadeCnt = 0;
					}
					if (pGameFade == GAMEFADE_NONE)
					{// �v���C���[�\����ʂ֑J��
						SetGameFade(GAMEMODE_PLAYERSHOW);
					}
					break;
				}
			}
		}
	}
	if (GameMode == GAMEMODE_PLAYERSHOW)
	{
		for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
		{
			if (g_aCardModel1P[nCntModel].pos.x > g_aCardModel1P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel1P[nCntModel].pos.x < g_aCardModel1P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel1P[nCntModel].pos.z > g_aCardModel1P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel1P[nCntModel].pos.z < g_aCardModel1P[nCntModel].DestPos.z + WIDTH)
			{// �J�[�h�̔���
				g_aCardModel1P[nCntModel].bMove = false;
			}
			if (g_aCardModel2P[nCntModel].pos.x > g_aCardModel2P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel2P[nCntModel].pos.x < g_aCardModel2P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel2P[nCntModel].pos.z > g_aCardModel2P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel2P[nCntModel].pos.z < g_aCardModel2P[nCntModel].DestPos.z + WIDTH)
			{// �J�[�h�̔���
				g_aCardModel2P[nCntModel].bMove = false;
			}
			// �ʒu�X�V
			if (g_aCardModel1P[nCntModel].bMove == true)
			{
				g_aCardModel1P[nCntModel].pos += g_aCardModel1P[nCntModel].move;
			}
			if (g_aCardModel2P[nCntModel].bMove == true)
			{
				g_aCardModel2P[nCntModel].pos += g_aCardModel2P[nCntModel].move;
			}
			g_aCardModel1P[nCntModel].rot.z = D3DX_PI;
			g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
			if (g_aCardModel2P[nCntModel].rot.z >= -D3DX_PI)
			{
				g_aCardModel2P[nCntModel].rot.z = -D3DX_PI;
			}
		}
		g_CardDeck.bUse = false;
		PlayerShowSetCard1P();
		PlayerShowSetCard2P();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawCardModel(void)
{
	MODE Mode = GetMode();
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

											/* �J�[�h�{�̂̕`�� */
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aCardModel1P[nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCardModel1P[nCntModel].rot.y, g_aCardModel1P[nCntModel].rot.x, g_aCardModel1P[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aCardModel1P[nCntModel].mtxWorld, &g_aCardModel1P[nCntModel].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aCardModel1P[nCntModel].pos.x, g_aCardModel1P[nCntModel].pos.y, g_aCardModel1P[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aCardModel1P[nCntModel].mtxWorld, &g_aCardModel1P[nCntModel].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aCardModel1P[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_apCardModel[g_aCardModel1P[nCntModel].ModelType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_aCardModel1P[nCntModel].ModelType].nNumMat; nCntMat++)
			{
				if (g_aCardModel1P[nCntModel].bUse == true)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̕`��
					pDevice->SetTexture(0, g_apCardModel[g_aCardModel1P[nCntModel].type].pTextureModel[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_apCardModel[g_aCardModel1P[nCntModel].ModelType].pMesh->DrawSubset(nCntMat);
				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aCardModel2P[nCntModel].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCardModel2P[nCntModel].rot.y, g_aCardModel2P[nCntModel].rot.x, g_aCardModel2P[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aCardModel2P[nCntModel].mtxWorld, &g_aCardModel2P[nCntModel].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aCardModel2P[nCntModel].pos.x, g_aCardModel2P[nCntModel].pos.y, g_aCardModel2P[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aCardModel2P[nCntModel].mtxWorld, &g_aCardModel2P[nCntModel].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aCardModel2P[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_apCardModel[g_aCardModel2P[nCntModel].ModelType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_aCardModel2P[nCntModel].ModelType].nNumMat; nCntMat++)
			{
				if (g_aCardModel2P[nCntModel].bUse == true)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̕`��
					pDevice->SetTexture(0, g_apCardModel[g_aCardModel2P[nCntModel].type].pTextureModel[nCntMat]);

					// ���f��(�p�[�c)�̕`��
					g_apCardModel[g_aCardModel2P[nCntModel].ModelType].pMesh->DrawSubset(nCntMat);

				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

	/* �R�D�̕`�� */
	if (g_CardDeck.bUse == true)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_CardDeck.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_CardDeck.rot.y, g_CardDeck.rot.x, g_CardDeck.rot.z);
		D3DXMatrixMultiply(&g_CardDeck.mtxWorld, &g_CardDeck.mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_CardDeck.pos.x, g_CardDeck.pos.y, g_CardDeck.pos.z);
		D3DXMatrixMultiply(&g_CardDeck.mtxWorld, &g_CardDeck.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_CardDeck.mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_apCardModel[g_CardDeck.ModelType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_CardDeck.ModelType].nNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̕`��
			pDevice->SetTexture(0, g_apCardModel[g_CardDeck.ModelType].pTextureModel[nCntMat]);

			// ���f��(�p�[�c)�̕`��
			g_apCardModel[g_CardDeck.ModelType].pMesh->DrawSubset(nCntMat);
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// 1P2P�؂�ւ�
//=============================================================================
void SetSide(CARDSIDE side)
{
	g_PokerState = side;
}
//=============================================================================
// �J�[�h�Z�b�g
//=============================================================================
void SetCardModel1P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side)
{
	GAMEMODE GameMode = GetGameMode();
	int nRandType = 0;
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bUse == false)
		{
			g_aCardModel1P[nCntModel].pos = pos;				// �|�W�V����
			if (GameMode == GAMEMODE_POKER)
			{
				g_aCardModel1P[nCntModel].PosType = CardPos;		// �J�[�h�̃|�W�V����
				g_aCardModel1P[nCntModel].DestPos = g_aDestCard1P[g_aCardModel1P[nCntModel].PosType]; //�ړI
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel1P[nCntModel].PosType = CardPos;		// �J�[�h�̃|�W�V����
				g_aCardModel1P[nCntModel].DestPos = g_aShowCard1P[g_aCardModel1P[nCntModel].PosType]; //�ړI
			}
			g_aCardModel1P[nCntModel].side = side;
			//�@����������
			g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;

			g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
			g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;

			g_aCardModel1P[nCntModel].bUse = true;
			g_aCardModel1P[nCntModel].bMove = true;
			if (GameMode == GAMEMODE_POKER)
			{
#if 1
				nRandType = rand() % MAX_CARD;	// �����_��
				if (nRandType == 0)
				{
					nRandType = 1;
				}
				if (nRandType >= 1 && nRandType <= 13)
				{
					g_aCardModel1P[nCntModel].type = TYPE_BRAVE;
					g_nNumBrave1P++;
				}
				else if (nRandType >= 14 && nRandType <= 26)
				{
					g_aCardModel1P[nCntModel].type = TYPE_KING;
					g_nNumKing1P++;
				}
				else if (nRandType >= 27 && nRandType <= 39)
				{
					g_aCardModel1P[nCntModel].type = TYPE_DEVIL;
					g_nNumDevil1P++;
				}
				else if (nRandType >= 40 && nRandType <= 52)
				{
					g_aCardModel1P[nCntModel].type = TYPE_COMMONER;
					g_nNumCommoner1P++;
				}
				else if (nRandType == 53 || nRandType == 54)
				{
					g_aCardModel1P[nCntModel].type = TYPE_JOKER;
					g_nNumJoker1P++;
				}
#endif
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel1P[nCntModel].type = g_aCardModel1P[nCntModel].type;
			}
			break;
		}
	}
}
//=============================================================================
// �J�[�h�Z�b�g
//=============================================================================
void SetCardModel2P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side, D3DXVECTOR3 rot)
{
	GAMEMODE GameMode = GetGameMode();
	int nRandType = 0;
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bUse == false)
		{
			g_aCardModel2P[nCntModel].pos = pos;				// �|�W�V����
			if (GameMode == GAMEMODE_POKER)
			{
				g_aCardModel2P[nCntModel].PosType = CardPos;		// �J�[�h�̃|�W�V����
				g_aCardModel2P[nCntModel].DestPos = g_aDestCard2P[g_aCardModel2P[nCntModel].PosType]; //�ړI
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel2P[nCntModel].PosType = CardPos;		// �J�[�h�̃|�W�V����
				g_aCardModel2P[nCntModel].DestPos = g_aShowCard2P[g_aCardModel2P[nCntModel].PosType]; //�ړI
			}
			g_aCardModel2P[nCntModel].side = side;
			g_aCardModel2P[nCntModel].rot = rot;
			//�@����������
			g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;

			g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
			g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;

			g_aCardModel2P[nCntModel].bUse = true;
			g_aCardModel2P[nCntModel].bMove = true;
			if (GameMode == GAMEMODE_POKER)
			{
#if 1
				nRandType = rand() % MAX_CARD;	// �����_��
				if (nRandType == 0)
				{
					nRandType = 1;
				}
				if (nRandType >= 1 && nRandType <= 13)
				{
					g_aCardModel2P[nCntModel].type = TYPE_BRAVE;
					g_nNumBrave2P++;
				}
				else if (nRandType >= 14 && nRandType <= 26)
				{
					g_aCardModel2P[nCntModel].type = TYPE_KING;
					g_nNumKing2P++;
				}
				else if (nRandType >= 27 && nRandType <= 39)
				{
					g_aCardModel2P[nCntModel].type = TYPE_DEVIL;
					g_nNumDevil2P++;
				}
				else if (nRandType >= 40 && nRandType <= 52)
				{
					g_aCardModel2P[nCntModel].type = TYPE_COMMONER;
					g_nNumCommoner2P++;
				}
				else if (nRandType == 53 || nRandType == 54)
				{
					g_aCardModel2P[nCntModel].type = TYPE_JOKER;
					g_nNumJoker2P++;
				}
#endif
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel2P[nCntModel].type = g_aCardModel2P[nCntModel].type;
			}
			break;
		}
	}
}
//=============================================================================
// �J�[�h�̔z�u
//=============================================================================
void SetCard(void)
{
	if (g_bSet == false)
	{
		g_nSetCnt++;
		if (g_nSetCnt == 1)
		{
			SetDeckCard(DECK_POS);
		}
		if (g_nSetCnt == 60)
		{
			SetCardModel1P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 120)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 180)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 240)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 300)
		{
			SetCardModel1P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 360)
		{
			g_bSet = true;
			g_nSetCnt = 0;
		}
	}
}
//=============================================================================
// �v���C���[�\�����̃J�[�h�̃Z�b�g (1P)
//=============================================================================
void PlayerShowSetCard1P(void)
{
	LoadText1P();
	SetCardModel1P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_1P);
}
//=============================================================================
// �v���C���[�\�����̃J�[�h�̃Z�b�g (2P)
//=============================================================================
void PlayerShowSetCard2P(void)
{
	LoadText2P();
	SetCardModel2P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
}
//=============================================================================
// �R�D�Z�b�g
//=============================================================================
void SetDeckCard(D3DXVECTOR3 pos)
{
	g_CardDeck.pos = pos;		// �|�W�V����
	g_CardDeck.bUse = true;
}
//=============================================================================
// �J�[�h�I������(1P)
//=============================================================================
void SelectCard1P(CARDPOS CardPos)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_bSet == true)
		{
			if (g_aCardModel1P[nCntModel].PosType == CardPos)
			{
				g_aCardModel1P[nCntModel].bMove = true;
				if (g_aCardModel1P[nCntModel].bSelect == false && g_aCardModel1P[nCntModel].bChange == false)
				{// �J�[�h���I������Ă��Ȃ� && �`�F���W���Ă��Ȃ�
				 // �ړ�������
					g_aCardModel1P[nCntModel].bSelect = true;
					g_aCardModel1P[nCntModel].DestPos.z += SELECT_POS;
				}
				else if (g_aCardModel1P[nCntModel].bSelect == true)
				{// �J�[�h���I������Ă���
				 // ���̏ꏊ�ɖ߂�
					g_aCardModel1P[nCntModel].bSelect = false;
					g_aCardModel1P[nCntModel].DestPos.z -= SELECT_POS;
				}
				// �������o��
				g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;
				// �J�[�h���ړ�������
				g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
				g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;
			}
		}
	}
}
//=============================================================================
// �J�[�h�I������(2P)
//=============================================================================
void SelectCard2P(CARDPOS CardPos)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_bSet == true)
		{
			if (g_aCardModel2P[nCntModel].PosType == CardPos)
			{
				g_aCardModel2P[nCntModel].bMove = true;
				if (g_aCardModel2P[nCntModel].bSelect == false && g_aCardModel2P[nCntModel].bChange == false)
				{// �J�[�h���I������Ă��Ȃ� && �`�F���W���Ă��Ȃ�
				 // �ړ�������
					g_aCardModel2P[nCntModel].bSelect = true;
					g_aCardModel2P[nCntModel].DestPos.z -= SELECT_POS;
				}
				else if (g_aCardModel2P[nCntModel].bSelect == true)
				{// �J�[�h���I������Ă���
				 // ���̏ꏊ�ɖ߂�
					g_aCardModel2P[nCntModel].bSelect = false;
					g_aCardModel2P[nCntModel].DestPos.z += SELECT_POS;
				}
				// �������o��
				g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;
				// �J�[�h���ړ�������
				g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
				g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;
			}
		}
	}
}
//=============================================================================
// �J�[�h���`�F���W���鏈�� (1P)
//=============================================================================
void ChangeCard1P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bSelect == true)
		{//�J�[�h���I�΂�Ă���Ƃ�
		 // �ړI�̏ꏊ(���S)
			g_aCardModel1P[nCntModel].DestPos = g_ChangePos;
			// ����������
			g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;
			// �J�[�h���ړ�������
			g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
			g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;

			g_aCardModel1P[nCntModel].bMove = true;
			g_aCardModel1P[nCntModel].bChange = true;
			g_aCardModel1P[nCntModel].bSelect = false;
			g_aCardModel1P[nCntModel].bUse = false;
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_BRAVE)
			{
				g_nNumBrave1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_KING)
			{
				g_nNumKing1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_DEVIL)
			{
				g_nNumDevil1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_COMMONER)
			{
				g_nNumCommoner1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_JOKER)
			{
				g_nNumJoker1P--;
			}
		}
	}
}
//=============================================================================
// �J�[�h���`�F���W���鏈�� (2P)
//=============================================================================
void ChangeCard2P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bSelect == true)
		{//�J�[�h���I�΂�Ă���Ƃ�
		 // �ړI�̏ꏊ(���S)
			g_aCardModel2P[nCntModel].DestPos = g_ChangePos;
			// ����������
			g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;
			// �J�[�h���ړ�������
			g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
			g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;

			g_aCardModel2P[nCntModel].bMove = true;
			g_aCardModel2P[nCntModel].bChange = true;
			g_aCardModel2P[nCntModel].bSelect = false;
			g_aCardModel2P[nCntModel].bUse = false;
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_BRAVE)
			{
				g_nNumBrave2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_KING)
			{
				g_nNumKing2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_DEVIL)
			{
				g_nNumDevil2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_COMMONER)
			{
				g_nNumCommoner2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_JOKER)
			{
				g_nNumJoker2P--;
			}
		}
	}
}
//=============================================================================
// �e�L�X�g�������ݏ��� (1P)
//=============================================================================
void WriteText1P(void)
{
	// �t�@�C���̃|�C���^�擾
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_1P, "w");
	if (pFile != NULL)
	{// �e�L�X�g���J������
		fprintf(pFile, "�L���� ");
		switch (g_aType[0])
		{
		case TYPE_BRAVE:
			fprintf(pFile, "0\n");
			break;
		case TYPE_DEVIL:
			fprintf(pFile, "1\n");
			break;
		case TYPE_KING:
			fprintf(pFile, "2\n");
			break;
		case TYPE_COMMONER:
			fprintf(pFile, "3\n");
			break;
		case TYPE_GOD:
			fprintf(pFile, "4\n");
			break;
		}
		switch (g_nData[0])
		{
		case 100:
			fprintf(pFile, "�� [ STRONG ZERO ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 10:
			fprintf(pFile, "�� [ �t���n�E�X ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 5:
			fprintf(pFile, "�� [ �t���b�V�� ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 4:
			fprintf(pFile, "�� [ �t�H�[�J�[�h ]\n");
			g_nStatus1P[STATUS_ATTACK] = 2;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 3:
			fprintf(pFile, "�� [ �X���[�J�[�h ]\n");
			g_nStatus1P[STATUS_ATTACK] = 2;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 2:
			fprintf(pFile, "�� [ �c�[�y�A ]\n");
			g_nStatus1P[STATUS_ATTACK] = 1;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 1:
			fprintf(pFile, "�� [ �����y�A ]\n");
			g_nStatus1P[STATUS_ATTACK] = 1;
			g_nStatus1P[STATUS_DEFENSE] = 1;
			break;
		}
		fprintf(pFile, "�U���� %d \n", g_nStatus1P[STATUS_ATTACK]);
		fprintf(pFile, "�h��� %d \n", g_nStatus1P[STATUS_DEFENSE]);
		fprintf(pFile, "�񕜗� %d \n", g_nNumCommoner1P);
		for (int nCnt = 0; nCnt < MAX_SET_CARD; nCnt++)
		{
			switch (g_aCardModel1P[nCnt].type)
			{
			case TYPE_BRAVE:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_KING:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_DEVIL:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_COMMONER:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_JOKER:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			}
		}
		fprintf(pFile, "END_SCRIPT\n");
		fclose(pFile);
	}
	else
	{// �e�L�X�g���J���Ȃ�������

	}
}
//=============================================================================
// �e�L�X�g�������ݏ��� (2P)
//=============================================================================
void WriteText2P(void)
{
	// �t�@�C���̃|�C���^�擾
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_2P, "w");
	if (pFile != NULL)
	{// �e�L�X�g���J������
		fprintf(pFile, "�L���� ");
		switch (g_aType[1])
		{
		case TYPE_BRAVE:
			fprintf(pFile, "0\n");
			break;
		case TYPE_DEVIL:
			fprintf(pFile, "1\n");
			break;
		case TYPE_KING:
			fprintf(pFile, "2\n");
			break;
		case TYPE_COMMONER:
			fprintf(pFile, "3\n");
			break;
		case TYPE_GOD:
			fprintf(pFile, "4\n");
			break;
		}
		switch (g_nData[1])
		{
		case 100:
			fprintf(pFile, "�� [ STRONG ZERO ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 10:
			fprintf(pFile, "�� [ �t���n�E�X ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 5:
			fprintf(pFile, "�� [ �t���b�V�� ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 4:
			fprintf(pFile, "�� [ �t�H�[�J�[�h ]\n");
			g_nStatus2P[STATUS_ATTACK] = 2;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 3:
			fprintf(pFile, "�� [ �X���[�J�[�h ]\n");
			g_nStatus2P[STATUS_ATTACK] = 2;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 2:
			fprintf(pFile, "�� [ �c�[�y�A ]\n");
			g_nStatus2P[STATUS_ATTACK] = 1;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 1:
			fprintf(pFile, "�� [ �����y�A ]\n");
			g_nStatus2P[STATUS_ATTACK] = 1;
			g_nStatus2P[STATUS_DEFENSE] = 1;
			break;
		}
		fprintf(pFile, "�U���� %d \n", g_nStatus2P[STATUS_ATTACK]);
		fprintf(pFile, "�h��� %d \n", g_nStatus2P[STATUS_DEFENSE]);
		fprintf(pFile, "�񕜗� %d \n", g_nNumCommoner2P);
		for (int nCnt = 0; nCnt < MAX_SET_CARD; nCnt++)
		{
			switch (g_aCardModel2P[nCnt].type)
			{
			case TYPE_BRAVE:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_KING:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_DEVIL:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_COMMONER:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_JOKER:
				fprintf(pFile, "%d���� %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			}
		}
		fprintf(pFile, "END_SCRIPT\n");
		fclose(pFile);
	}
	else
	{// �e�L�X�g���J���Ȃ�������

	}
}
//=============================================================================
// �e�L�X�g�ǂݍ��ݏ��� (1P)
//=============================================================================
void LoadText1P(void)
{
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���

								// �t�@�C���̃|�C���^�擾
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_1P, "r");
	if (pFile != NULL)
	{
		while (strcmp(HeadText, "END_SCRIPT") != 0)
		{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
			{
				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "1����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[0].type);
				}
				else if (strcmp(HeadText, "2����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[1].type);
				}
				else if (strcmp(HeadText, "3����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[2].type);
				}
				else if (strcmp(HeadText, "4����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[3].type);
				}
				else if (strcmp(HeadText, "5����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[4].type);
				}
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// �e�L�X�g�ǂݍ��ݏ��� (2P)
//=============================================================================
void LoadText2P(void)
{
	char ReadText[256];			// �ǂݍ��񂾕���������Ă���
	char HeadText[256];			// ��r�p
	char DustBox[256];			// �g�p���Ȃ����̂����Ă���

								// �t�@�C���̃|�C���^�擾
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_2P, "r");
	if (pFile != NULL)
	{
		while (strcmp(HeadText, "END_SCRIPT") != 0)
		{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
			{
				if (strcmp(HeadText, "\n") == 0)
				{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "1����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[0].type);
				}
				else if (strcmp(HeadText, "2����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[1].type);
				}
				else if (strcmp(HeadText, "3����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[2].type);
				}
				else if (strcmp(HeadText, "4����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[3].type);
				}
				else if (strcmp(HeadText, "5����") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[4].type);
				}
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// ���m�F	(1P)
//=============================================================================
void CheckHand1P(void)
{
	if (g_nNumBrave1P == 1 && g_nNumKing1P == 1 && g_nNumDevil1P == 1 && g_nNumCommoner1P == 1 && g_nNumJoker1P == 1)
	{// STRONG�@ZERO
		g_nData[0] = 100;
	}
	else if (g_nNumBrave1P == 5 || g_nNumKing1P == 5 || g_nNumDevil1P == 5 || g_nNumCommoner1P == 5)
	{// �t���b�V��
		g_nData[0] = 5;
	}
	else if (g_nNumBrave1P == 4 || g_nNumKing1P == 4 || g_nNumDevil1P == 4 || g_nNumCommoner1P == 4)
	{// �t�H�[�J�[�h
		g_nData[0] = 4;
	}
	else if (g_nNumBrave1P == 3 || g_nNumKing1P == 3 || g_nNumDevil1P == 3 || g_nNumCommoner1P == 3)
	{// �X���[�J�[�h
		g_nData[0] = 3;
		if (g_nNumBrave1P == 2 || g_nNumKing1P == 2 || g_nNumDevil1P == 2 || g_nNumCommoner1P == 2)
		{// �t���n�E�X
			g_nData[0] = 10;
		}
	}
	else if (g_nNumBrave1P == 2 || g_nNumKing1P == 2 || g_nNumDevil1P == 2 || g_nNumCommoner1P == 2 || g_nNumJoker1P == 2)
	{// �����y�A
		g_nData[0] = 1;
		if (g_nNumBrave1P == 3 || g_nNumKing1P == 3 || g_nNumDevil1P == 3 || g_nNumCommoner1P == 3)
		{// �t���n�E�X
			g_nData[0] = 10;
		}
	}
	// �c�[�y�A����
	if (g_nNumBrave1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_BRAVE;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_KING;
		g_bTwoPair1P = true;
	}
	if (g_nNumDevil1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// �����_��
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_BRAVE;
		}
		if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_DEVIL;
		}
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false
		|| g_nNumKing1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// �����_��
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_KING;
		}
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false
		|| g_nNumJoker1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_BRAVE;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false
		|| g_nNumJoker1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_KING;
		g_bTwoPair1P = true;
	}
	if (g_nNumJoker1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// �����_��
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_KING;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_DEVIL;
		}
		g_bTwoPair1P = true;
	}
	if (g_bTwoPair1P == true)
	{
		g_nData[0] = 2;
	}
}
//=============================================================================
// ���m�F	(2P)
//=============================================================================
void CheckHand2P(void)
{
	if (g_nNumBrave2P == 1 && g_nNumKing2P == 1 && g_nNumDevil2P == 1 && g_nNumCommoner2P == 1 && g_nNumJoker2P == 1)
	{// STRONG�@ZERO
		g_nData[1] = 100;
	}
	if (g_nNumBrave2P == 5 || g_nNumKing2P == 5 || g_nNumDevil2P == 5 || g_nNumCommoner2P == 5)
	{// �t���b�V��
		g_nData[1] = 5;
	}
	if (g_nNumBrave2P == 4 || g_nNumKing2P == 4 || g_nNumDevil2P == 4 || g_nNumCommoner2P == 4)
	{// �t�H�[�J�[�h
		g_nData[1] = 4;
	}
	if (g_nNumBrave2P == 3 || g_nNumKing2P == 3 || g_nNumDevil2P == 3 || g_nNumCommoner2P == 3)
	{// �X���[�J�[�h
		g_nData[1] = 3;
		if (g_nNumBrave2P == 2 || g_nNumKing2P == 2 || g_nNumDevil2P == 2 || g_nNumCommoner2P == 2)
		{// �t���n�E�X
			g_nData[1] = 10;
		}
	}
	if (g_nNumBrave2P == 2 || g_nNumKing2P == 2 || g_nNumDevil2P == 2 || g_nNumCommoner2P == 2)
	{// �����y�A
		g_nData[1] = 1;
		if (g_nNumBrave2P == 3 || g_nNumKing2P == 3 || g_nNumDevil2P == 3 || g_nNumCommoner2P == 3)
		{// �t���n�E�X
			g_nData[1] = 10;
		}
	}
	// �c�[�y�A����
	if (g_nNumBrave2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_BRAVE;
		g_bTwoPair2P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_KING;
		g_bTwoPair2P = true;
	}
	if (g_nNumDevil2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_DEVIL;
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumDevil2P == 2)
	{
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_DEVIL;
		}
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumKing2P == 2)
	{
		g_nTwoRandType = rand() % 2;	// �����_��
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_KING;
		}
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_BRAVE;
		g_bTwoPair2P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_KING;
		g_bTwoPair2P = true;
	}
	if (g_nNumDevil2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumDevil2P == 2)
	{
		g_nTwoRandType = rand() % 2;	// �����_��
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_KING;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_DEVIL;
		}
		g_bTwoPair2P = true;
	}
	if (g_bTwoPair2P == true)
	{
		g_nData[1] = 2;
	}
}
//=============================================================================
// �^�C�v�m�F	(1P)
//=============================================================================
void CheckType1P(void)
{
	if (g_bTwoPair1P == false)
	{
		if (g_nData[0] == 10)
		{
			if (g_nNumCommoner1P == 3)
			{
				if (g_nNumBrave1P == 2)
				{
					g_aType[0] = TYPE_BRAVE;
				}
				if (g_nNumKing1P == 2)
				{
					g_aType[0] = TYPE_KING;
				}
				if (g_nNumDevil1P == 2)
				{
					g_aType[0] = TYPE_DEVIL;
				}
			}
			else
			{
				if (g_nNumBrave1P >= g_nNumKing1P && g_nNumBrave1P >= g_nNumDevil1P && g_nNumBrave1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_BRAVE;
				}
				if (g_nNumKing1P >= g_nNumBrave1P && g_nNumKing1P >= g_nNumDevil1P && g_nNumKing1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_KING;
				}
				if (g_nNumDevil1P >= g_nNumBrave1P && g_nNumDevil1P >= g_nNumKing1P && g_nNumDevil1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_DEVIL;
				}
			}
		}
		if (g_nData[0] != 10)
		{
			if (g_nNumBrave1P >= g_nNumKing1P && g_nNumBrave1P >= g_nNumDevil1P && g_nNumBrave1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_BRAVE;
			}
			if (g_nNumKing1P >= g_nNumBrave1P && g_nNumKing1P >= g_nNumDevil1P && g_nNumKing1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_KING;
			}
			if (g_nNumDevil1P >= g_nNumBrave1P && g_nNumDevil1P >= g_nNumKing1P && g_nNumDevil1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_DEVIL;
			}
			if (g_nNumCommoner1P >= g_nNumBrave1P && g_nNumCommoner1P >= g_nNumKing1P && g_nNumCommoner1P >= g_nNumDevil1P)
			{
				g_aType[0] = TYPE_COMMONER;
			}
			if (g_nNumBrave1P == 1 && g_nNumKing1P == 1 && g_nNumDevil1P == 1 && g_nNumCommoner1P == 1 && g_nNumJoker1P == 1)
			{
				g_aType[0] = TYPE_GOD;
			}
		}
	}
}
//=============================================================================
// �^�C�v�m�F	(2P)
//=============================================================================
void CheckType2P(void)
{
	if (g_bTwoPair2P == false)
	{
		if (g_nData[1] == 10)
		{
			if (g_nNumCommoner2P == 3)
			{
				if (g_nNumBrave2P == 2)
				{
					g_aType[1] = TYPE_BRAVE;
				}
				if (g_nNumKing2P == 2)
				{
					g_aType[1] = TYPE_KING;
				}
				if (g_nNumDevil2P == 2)
				{
					g_aType[1] = TYPE_DEVIL;
				}
			}
			else
			{
				if (g_nNumBrave2P >= g_nNumKing2P && g_nNumBrave2P >= g_nNumDevil2P && g_nNumBrave2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_BRAVE;
				}
				if (g_nNumKing2P >= g_nNumBrave2P && g_nNumKing2P >= g_nNumDevil2P && g_nNumKing2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_KING;
				}
				if (g_nNumDevil2P >= g_nNumBrave2P && g_nNumDevil2P >= g_nNumKing2P && g_nNumDevil2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_DEVIL;
				}
			}
		}
		if (g_nData[1] != 10)
		{
			if (g_nNumBrave2P >= g_nNumKing2P && g_nNumBrave2P >= g_nNumDevil2P && g_nNumBrave2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_BRAVE;
			}
			if (g_nNumKing2P >= g_nNumBrave2P && g_nNumKing2P >= g_nNumDevil2P && g_nNumKing2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_KING;
			}
			if (g_nNumDevil2P >= g_nNumBrave2P && g_nNumDevil2P >= g_nNumKing2P && g_nNumDevil2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_DEVIL;
			}
			if (g_nNumCommoner2P >= g_nNumBrave2P && g_nNumCommoner2P >= g_nNumKing2P && g_nNumCommoner2P >= g_nNumDevil2P)
			{
				g_aType[1] = TYPE_COMMONER;
			}
			if (g_nNumBrave2P == 1 && g_nNumKing2P == 1 && g_nNumDevil2P == 1 && g_nNumCommoner2P == 1 && g_nNumJoker2P == 1)
			{
				g_aType[1] = TYPE_GOD;
			}
		}
	}
}
//=============================================================================
// �J�[�h���� (1P)
//=============================================================================
void ExchangeCard1P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bChange == true)
		{
			g_aCardModel1P[nCntModel].bMove = true;
			g_aCardModel1P[nCntModel].bChange = false;
			g_aCardModel1P[nCntModel].bSelect = false;
			g_aCardModel1P[nCntModel].bUse = false;
			SetCardModel1P(DECK_POS, CARDPOS(nCntModel), CARD_SIDE_1P);
		}
	}
}
//=============================================================================
// �J�[�h���� (2P)
//=============================================================================
void ExchangeCard2P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bChange == true)
		{
			g_aCardModel2P[nCntModel].bMove = true;
			g_aCardModel2P[nCntModel].bChange = false;
			g_aCardModel2P[nCntModel].bSelect = false;
			g_aCardModel2P[nCntModel].bUse = false;
			SetCardModel2P(DECK_POS, CARDPOS(nCntModel), CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
		}
	}
}
//=============================================================================
// �J�[�\���ړ�
//=============================================================================
void MoveCursor(void)
{
	if (g_bSet == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true || GetGamePadPovPress(g_nNowPlayer,POV_RIGHT) || GetGamePadStickPress(g_nNowPlayer,STICK_RIGHT))
		{
			g_nPressCnt++;
			if (g_nPressCnt % PRESS_CNT == 0)
			{
				g_nSelectCard = (g_nSelectCard + 1) % (CARD_POS_MAX - 1);
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetGamePadPovPress(g_nNowPlayer, POV_LEFT) || GetGamePadStickPress(g_nNowPlayer, STICK_LEFT))
		{
			g_nPressCnt++;
			if (g_nPressCnt % PRESS_CNT == 0)
			{
				g_nSelectCard = (g_nSelectCard + 3) % (CARD_POS_MAX - 1);
			}
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true || GetGamePadPovTrigger(g_nNowPlayer, POV_RIGHT) || GetGamePadStickTrigger(g_nNowPlayer, STICK_RIGHT))
		{
			g_nSelectCard = (g_nSelectCard + 1) % (CARD_POS_MAX - 1);
		}
		else if (GetKeyboardTrigger(DIK_LEFT) == true || GetGamePadPovTrigger(g_nNowPlayer, POV_LEFT) || GetGamePadStickTrigger(g_nNowPlayer, STICK_LEFT))
		{
			g_nSelectCard = (g_nSelectCard + 3) % (CARD_POS_MAX - 1);
		}
		if (GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true
			|| GetGamePadPovRelease(g_nNowPlayer, POV_RIGHT) || GetGamePadPovRelease(g_nNowPlayer, POV_LEFT)
			|| GetGamePadStickRelease(g_nNowPlayer,STICK_RIGHT) ||  GetGamePadStickRelease(g_nNowPlayer, STICK_LEFT))
		{
			g_nPressCnt = 0;
		}
	}
}
//=============================================================================
// ���f���ǂݍ���
//=============================================================================
void LoadModel(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXLoadMeshFromX(MODEL_CARD,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_apCardModel[0].pBuffMat,
		NULL,
		&g_apCardModel[0].nNumMat,
		&g_apCardModel[0].pMesh);

	D3DXCreateTextureFromFile(pDevice, TEX_BRAVE, g_apCardModel[TYPE_BRAVE].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_KING, g_apCardModel[TYPE_KING].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_DEVIL, g_apCardModel[TYPE_DEVIL].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_JOKER, g_apCardModel[TYPE_JOKER].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_HEART, g_apCardModel[TYPE_COMMONER].pTextureModel);
}
//=============================================================================
// �K�C�h�\���Ɏg������
//=============================================================================
int GetNum(void)
{// �I�΂�Ă���J�[�h�̔ԍ�
	return g_nSelectCard;
}
int GetHandNum(int nNowPlayer)
{// �𔻒�Ŏg���l
	return g_nData[nNowPlayer];
}
CARDTYPE GetType(int nNowPlayer)
{// �^�C�v�m�F
	return g_aType[nNowPlayer];
}
CARDTYPE Get1PHand(int nIndex)
{// 5���̒��g
	return g_aCardModel1P[nIndex].type;
}
CARDTYPE Get2PHand(int nIndex)
{// 5���̒��g
	return g_aCardModel2P[nIndex].type;
}
bool GetSet(void)
{// �J�[�h���z�u���ꂽ��
	return g_bSet;
}
/* �J�[�\���̈ʒu���J�[�h�ɍ��킹�� */
D3DXVECTOR3 GetCardPos1P(int nSelectNum)
{// 1P
	return g_aCardModel1P[nSelectNum].pos;
}
D3DXVECTOR3 GetCardPos2P(int nSelectNum)
{// 2P
	return g_aCardModel2P[nSelectNum].pos;
}
CARDSIDE GetPokerState(void)
{// �|�[�J�[�̏�
	return g_PokerState;
}
D3DXVECTOR3 GetLockPos1P(int nNumber)
{// 1P �E�̃J�[�h��Ƀ��b�N�}�[�N������
	return g_aDestCard1P[nNumber];
}
D3DXVECTOR3 GetLockPos2P(int nNumber)
{// 2P ���̃J�[�h��Ƀ��b�N�}�[�N������
	return g_aDestCard2P[nNumber];
}
int GetNowPlayer(void)
{
	return g_nNowPlayer;
}