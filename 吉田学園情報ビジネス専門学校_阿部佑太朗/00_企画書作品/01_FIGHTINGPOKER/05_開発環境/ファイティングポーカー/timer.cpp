//=============================================================================
//
// �^�C������ [timer.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "timer.h"
#include "input.h"
#include "cardModel.h"
#include "poker.h"
#include "ui.h"
#include "game.h"
#include "gamefade.h"
#include "fade.h"
#include "battle.h"
#include "message.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define INFINIT_TEX			"data/TEXTURE/infinite.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	FRAME_TEXTURE		"data/TEXTURE/frame_timer.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
/* �|�[�J�[�� */
#define POKER_TIME_WIDTH		(510.0f)			// X���W
#define POKER_TIME_WIDTH2		(570.0f)			// X���W
#define POKER_TIME_HEIGHT		(20.0f)				// Y���W
#define POKER_TIME_HEIGHT2		(80.0f)				// Y���W
#define POKER_FRAME_WIDTH		(380.0f)			// X���W
#define POKER_FRAME_WIDTH2		(630.0f)			// X���W
#define POKER_FRAME_HEIGHT		(0.0f)				// Y���W
#define POKER_FRAME_HEIGHT2		(100.0f)			// Y���W
/* �o�g���� */
#define BATTLE_TIME_WIDTH		(SCREEN_WIDTH /2 + 5.0f)			// X���W
#define BATTLE_TIME_WIDTH2		(SCREEN_WIDTH /2 + 55.0f)			// X���W
#define BATTLE_TIME_HEIGHT		(0.0f)				// Y���W
#define BATTLE_TIME_HEIGHT2		(100.0f)				// Y���W

#define TIMER_SPACE			(40)				// �����̃X�y�[�X
#define TIME_COUNT			(2)					// �X�R�A�̌���
#define FPM					(60)				// 60�b�J�E���g����
#define MAX_TEXTURE			(TIMERTYPE_MAX)		// �ǂݍ��ރe�N�X�`���̍ő吔
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer[MAX_TEXTURE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Timer					g_Time;								//�^�C�}�[�̏��
bool					g_bSwitch = true;
//=============================================================================
// ����������
//=============================================================================
void InitTimer(void)
{
	GAMEMODE GameMode = GetGameMode();
	int nRound = GetRoundCounter();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �^�C�}�[�̏�����
	if (GameMode == GAMEMODE_POKER)
	{
		g_Time.nTime = MAX_TIME;
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TIME, &g_pTextureTimer[TIMERTYPE_COUNT]);
		D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE, &g_pTextureTimer[TIMERTYPE_FRAME]);
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		g_Time.nTime = BATTLE_TIME;
		if (nRound <= 4)
		{
			g_Time.nTime = BATTLE_TIME;
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, TEXTURE_TIME, &g_pTextureTimer[TIMERTYPE_COUNT]);
		}
		if (nRound == 5)
		{
			D3DXCreateTextureFromFile(pDevice, INFINIT_TEX, &g_pTextureTimer[TIMERTYPE_COUNT]);
		}

		g_bSwitch = false;
	}
	g_Time.bUseTime = false;
	g_Time.bFinish = false;

	// ���_���̍쐬
	MakeVertexTimer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureTimer[nCnt] != NULL)
		{
			g_pTextureTimer[nCnt]->Release();
			g_pTextureTimer[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	int nCntTime;
	int nPlus[TIME_COUNT];
	static int nCntFrame = 0;
	int nRound = GetRoundCounter();
	GAMEMODE GameMode = GetGameMode();

	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	BATTLESTATE batleState = GetBattleState();

	bool bReady = GetReady();		// �v���C���[�̏������������Ă��邩

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

#if _DEBUG
	if (GetKeyboardTrigger(DIK_T) == true)
	{
		g_bSwitch = g_bSwitch ? false : true;
	}
#endif
	switch (GameMode)
	{
	case GAMEMODE_POKER:
		if (bReady == true)
		{
			//�t���[�����̉��Z
			nCntFrame++;
			if (nCntFrame % FPM == 0)
			{
				g_Time.nTime--;
				if (g_Time.nTime <= 0)
				{// �J�E���g��0�ɂȂ�����
					g_Time.nTime = 0;
				}
			}
		}
		break;
	case GAMEMODE_BATTLE:
		//�t���[�����̉��Z
		if (g_bSwitch == true)
		{
			if (nRound <= 4)
			{
				nCntFrame++;
				if (nCntFrame % FPM == 0)
				{
					g_Time.nTime--;
					if (g_Time.nTime <= 0)
					{// �J�E���g��0�ɂȂ�����
						g_Time.nTime = 0;
						if (batleState != BATTLESTATE_TIMEOVER && batleState != BATTLESTATE_NONE && batleState != BATTLESTATE_CLEAR)
						{// �o�g���X�e�[�g�����Ԑ؂�ɕύX
							SetBattleState(BATTLESTATE_TIMEOVER);

							// �^�C���I�[�o�[��\��
							SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_TIMEOVER);
							SelectVolume(SOUND_LABEL_TIMEOVER_SE, 0.8f);
						}
					}
				}
			}
		}
		break;
	}
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	if (GameMode == GAMEMODE_POKER)
	{
		for (nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
		{
			int nTimeData = 1;
			for (int nCnt_Ftime = nCntTime; nCnt_Ftime != 0; nCnt_Ftime--)
			{
				nTimeData *= 10;
			}
			nPlus[nCntTime] = g_Time.nTime % (nTimeData * 10) / nTimeData;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 1.0f);
		}
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		if (nRound <= 4)
		{
			for (nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
			{
				int nTimeData = 1;
				for (int nCnt_Ftime = nCntTime; nCnt_Ftime != 0; nCnt_Ftime--)
				{
					nTimeData *= 10;
				}
				nPlus[nCntTime] = g_Time.nTime % (nTimeData * 10) / nTimeData;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 1.0f);
			}
		}
		if (nRound == 5)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	GAMEMODE GameMode = GetGameMode();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer[TIMERTYPE_FRAME]);
	if (GameMode == GAMEMODE_POKER)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 + 8,	// �`����J�n���钸�_�C���f�b�N�X
			2);
	}
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer[TIMERTYPE_COUNT]);
	// �|���S���̕`��
	for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntTime * 4,// �`����J�n���钸�_�C���f�b�N�X
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	GAMEMODE GameMode = GetGameMode();
	int nRound = GetRoundCounter();

	// ���_����ݒ�
	VERTEX_2D * pVtx;

	if (GameMode == GAMEMODE_POKER)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_COUNT * MAX_TEXTURE,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTimer,
			NULL);
	}

	if (GameMode == GAMEMODE_BATTLE)
	{
		if (nRound <= 4)
		{
			// ���_�o�b�t�@�𐶐�
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_COUNT,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_pVtxBuffTimer,
				NULL);
		}
		if (nRound == 5)
		{
			// ���_�o�b�t�@�𐶐�
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_pVtxBuffTimer,
				NULL);
		}
	}

	if (GameMode == GAMEMODE_POKER)
	{
		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
		/* ���� */
		for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
		{
			// �|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(POKER_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POKER_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POKER_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POKER_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT2, 0.0f);
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			// �|���S���̐F
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			// �e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		pVtx += 4;	// ���_����4�i�߂�
					/* �t���[�� */
					// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(POKER_FRAME_WIDTH, POKER_FRAME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POKER_FRAME_WIDTH2, POKER_FRAME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(POKER_FRAME_WIDTH, POKER_FRAME_HEIGHT2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POKER_FRAME_WIDTH2, POKER_FRAME_HEIGHT2, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimer->Unlock();
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
		/* ���� */
		if (nRound <= 4)
		{
			for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
			{
				// �|���S���̍��W�ݒ�
				pVtx[0].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT2, 0.0f);
				// rhw�̐ݒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;
				// �|���S���̐F
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				// �e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
			}
		}
		if (nRound == 5)
		{
			// �|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(550.0f, POKER_FRAME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(720.0f, POKER_FRAME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550.0f, POKER_FRAME_HEIGHT2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(720.0f, POKER_FRAME_HEIGHT2, 0.0f);
			// rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			// �|���S���̐F
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			// �e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTimer->Unlock();
	}
}



//=============================================================================
// �^�C�}�[�̎擾
//=============================================================================
Timer *GetTimer(void)
{
	return &g_Time;
}

//=============================================================================
// �^�C�}�[��ON/OFF
//=============================================================================
void SetTimerSwitch(bool bSwitch)
{
	g_bSwitch = bSwitch;
}