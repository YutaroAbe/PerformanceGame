//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �J�������� [camera.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "camera.h"
#include "player.h"
#include "main.h"
#include "battle.h"
#include "cardModel.h"
#include "fade.h"
#include "game.h"
#include "gamefade.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define POS_V_1P	D3DXVECTOR3(0.0f, 750.0f, -100.0f)		// 1P���̎��_
#define POS_R_1P	D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// 1P���̒����_
#define POS_V_2P	D3DXVECTOR3(-200.0f, 750.0f, 150.0f)	// 2P���̎��_
#define POS_R_2P	D3DXVECTOR3(-200.0f, 0.0f, 50.0f)		// 2P���̒����_
#define POS_V_ALL	D3DXVECTOR3(0.0f,650.0f,-100.0f)		// �I�����̎��_
#define POS_R_ALL	D3DXVECTOR3(0.0f,0.0f,0.0f)				// �I�����̒����_

#define CAMERA_V_CHASE		(0.1f)		// ���_�̒ǐՊ���
#define CAMERA_R_CHASE		(0.5f)		// �����_�̒ǐՊ���
#define CAMERA_VR_LENGTH	(10.0f)		// �J�����̋���

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXVECTOR3 rot;			// �p�x
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
}CameraInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
Camera g_aCamera[MAX_CAMERA];	// �J�����̏��

// �o�g�����[�h�̃J�������
CameraInfo g_aInfoBattleCamera[BATTLE_CAMERA_TYPE_MAX] =
{
	// ���C���J����
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 100.0f, -270.0f) ,	D3DXVECTOR3(0.0f, 100.0f, 0.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x�ʒu,			y�ʒu,					��,					����,			���sMin,	���sMax
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f) ,		{0,						0,						SCREEN_WIDTH,		SCREEN_HEIGHT,	0.0f,		1.0f } },
};

// �v���C���[�V���E���[�h�̃J�������
CameraInfo g_aInfoPlayerShowCamera[PLAYERSHOW_CAMERA_TYPE_MAX] =
{
	// 1P�r���[�|�[�g�J����
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f) ,	D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x�ʒu,			y�ʒu,					��,					����,			���sMin,	���sMax
	D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f) ,		{ 0,					0,						SCREEN_WIDTH / 2,	700,			0.0f,		1.0f } },

	// 2P�r���[�|�[�g�J����
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f) ,	D3DXVECTOR3(0.0f, 0.0f, -50.0f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x�ʒu,			y�ʒu,					��,					����,			���sMin,	���sMax
	D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f),		{ SCREEN_WIDTH / 2,		0,						SCREEN_WIDTH / 2,	700,			0.0f,		1.0f } },

	// 3DUI�r���[�|�[�g�J����
	// posV,								posR,							vecU,
	{ POS_V_ALL ,							POS_R_ALL,						D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x�ʒu,			y�ʒu,					��,					����,			���sMin,	���sMax
	D3DXVECTOR3(0.0f, 0.0f, 0.0f) ,			{ 0,					0,						SCREEN_WIDTH,		SCREEN_HEIGHT,	0.0f,		1.0f } },
};
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �J�����̏���������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitCamera(void)
{
	MODE Mode = GetMode();

	CARDSIDE side = GetPokerState();
	GAMEMODE GameMode = GetGameMode();
	FADE pFade;
	pFade = GetFade();

	if (Mode != MODE_GAME)
	{ // ���[�h�Q�[���ȊO
	  /* �|�[�J�[�̎� */
		g_aCamera[0].posV = POS_V_1P;										// ���_
		g_aCamera[0].posR = POS_R_1P;										// �����_
		g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// ������x�N�g��
		g_aCamera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]
		g_aCamera[0].fLength = g_aCamera[0].posR.z - g_aCamera[0].posV.z;	// Z�̋���
																			//======== [ �r���[�|�[�g ] ===========//
		g_aCamera[0].viewport.X = 0;										// �ʒu
		g_aCamera[0].viewport.Y = 0;										// �ʒu
		g_aCamera[0].viewport.Width = SCREEN_WIDTH;							// ��
		g_aCamera[0].viewport.Height = SCREEN_HEIGHT;						// ����
		g_aCamera[0].viewport.MinZ = 0.0f;									// ���s��
		g_aCamera[0].viewport.MaxZ = 1.0f;									// ���s��
	}
	else
	{
		switch (GameMode)
		{
		case GAMEMODE_POKER:	// �|�[�J�[���[�h�̏ꍇ
			/* �|�[�J�[�̎� */
			g_aCamera[0].posV = POS_V_1P;										// ���_
			g_aCamera[0].posR = POS_R_1P;										// �����_
			g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// ������x�N�g��
			g_aCamera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]
			g_aCamera[0].fLength = g_aCamera[0].posR.z - g_aCamera[0].posV.z;	// Z�̋���
			//======== [ �r���[�|�[�g ] ===========//
			g_aCamera[0].viewport.X = 0;										// �ʒu
			g_aCamera[0].viewport.Y = 0;										// �ʒu
			g_aCamera[0].viewport.Width = SCREEN_WIDTH;							// ��
			g_aCamera[0].viewport.Height = SCREEN_HEIGHT;						// ����
			g_aCamera[0].viewport.MinZ = 0.0f;									// ���s��
			g_aCamera[0].viewport.MaxZ = 1.0f;									// ���s��
			break;
		case GAMEMODE_PLAYERSHOW:	//
			for (int nCntCamera = 0; nCntCamera < PLAYERSHOW_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoPlayerShowCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoPlayerShowCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoPlayerShowCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoPlayerShowCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoPlayerShowCamera[nCntCamera].viewport;
			}
			break;
		case GAMEMODE_BATTLE:	// �o�g�����[�h�̏ꍇ
			for (int nCntCamera = 0; nCntCamera < BATTLE_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoBattleCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoBattleCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoBattleCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoBattleCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoBattleCamera[nCntCamera].viewport;
			}
			break;
		case GAMEMODE_RESULT:	//
			for (int nCntCamera = 0; nCntCamera < PLAYERSHOW_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoPlayerShowCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoPlayerShowCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoPlayerShowCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoPlayerShowCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoPlayerShowCamera[nCntCamera].viewport;
			}
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �J�����̏I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitCamera(void)
{
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �J�����̍X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();
	pPlayer = GetPlayer();

	CARDSIDE side = GetPokerState();
	GAMEMODE GameMode = GetGameMode();
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	switch (GameMode)
	{
	case GAMEMODE_POKER:	// �|�[�J�[���[�h�̏ꍇ
		if (pGameFade == FADE_IN)
		{
			if (side == CARD_SIDE_1P)
			{// 1P���쎞�̃J����
				g_aCamera[0].posV = POS_V_1P;	// ���_
				g_aCamera[0].posR = POS_R_1P;	// �����_
			}
			else if (side == CARD_SIDE_2P)
			{// 2P���쎞�̃J����
				g_aCamera[0].posV = POS_V_2P;	// ���_
				g_aCamera[0].posR = POS_R_2P;	// �����_
			}
		}
		break;
	case GAMEMODE_PLAYERSHOW:	// �v���C���[�V���E�̏ꍇ
		// 1P�r���[�|�[�g�J����
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x - sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z - cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 250.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x + sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z + cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 250.0f;

		// 2P�r���[�|�[�g�J����
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x - sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z - cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 250.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x + sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z + cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 250.0f;
		break;
	case GAMEMODE_BATTLE:	// �o�g�����[�h
		if (pPlayer->bUse == true)
		{
			Player *pPlayer = GetPlayer();
			BATTLESTATE BattleState = GetBattleState();

			float fWidth = pPlayer[0].pos.x - pPlayer[1].pos.x;
			float fHeight = pPlayer[0].pos.y - pPlayer[1].pos.y;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x = pPlayer[0].pos.x - fWidth / 2;
			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.y = pPlayer[0].pos.y - fHeight / 2 + 50.0f;
			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 5.0f;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.x = g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x + sinf(g_aCamera[BATTLE_CAMERA_TYPE_MAIN].rot.y) * g_aCamera[BATTLE_CAMERA_TYPE_MAIN].fLength;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.y = pPlayer[0].pos.y - fHeight / 2 + 50.0f;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.z = g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.z + cosf(g_aCamera[BATTLE_CAMERA_TYPE_MAIN].rot.y) * g_aCamera[BATTLE_CAMERA_TYPE_MAIN].fLength;

			if (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x >= PLAYER_MOVE_LIMIT_LEFT + float(PLAYER_MOVE_RIMIT) / 2.0f
				&& g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x <= PLAYER_MOVE_LIMIT_RIGHT - float(PLAYER_MOVE_RIMIT) / 2.0)
			{
				// ���݂̈ʒu�ɍ����̉���������
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR) * CAMERA_R_CHASE;
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV) * CAMERA_V_CHASE;
			}
			else
			{// Y�����͏�ɍs��
				// ���݂̈ʒu�ɍ����̉���������
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR.y += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.y - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR.y) * CAMERA_R_CHASE;
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV.y += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.y - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV.y) * CAMERA_V_CHASE;
			}

		}
		break;
	case GAMEMODE_RESULT:	// ���U���g�̏ꍇ
		// 1P�r���[�|�[�g�J����
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x - sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z - cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 200.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x + sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z + cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 200.0f;

		// 2P�r���[�|�[�g�J����
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x - sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z - cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 200.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x + sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z + cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 200.0f;
		break;
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �J�����̐ݒ菈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCamera(int nIdyCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nIdyCamera].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdyCamera].mtxProjection,
								D3DXToRadian(45.0f),	// ��p�A����p
								(float)g_aCamera[nIdyCamera].viewport.Width / (float)g_aCamera[nIdyCamera].viewport.Height,
								10.0f,					// 10.0f~
								7000.0f);				// 1000.f�̊Ԃ̃|���S��������`��

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nIdyCamera].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[nIdyCamera].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_aCamera[nIdyCamera].mtxView,
						&g_aCamera[nIdyCamera].posV,
						&g_aCamera[nIdyCamera].posR,
						&g_aCamera[nIdyCamera].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nIdyCamera].mtxView);

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_aCamera[nIdyCamera].viewport);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �J�����̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}
