//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �|�[�Y���j���[���� [pausemenu.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "pausemenu.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "battle.h"
#include "game.h"
#include "gamefade.h"
#include "sound.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define ANIM_CUT				(1)										// �A�j���[�V�����̕�����
#define ANIM_CUT_WIDTH			(1.0f)									// �A�j���[�V�����̉��̕�����
#define ANIM_CUT_HEIGHT			(1.0f)									// �A�j���[�V�����̏c�̕�����
#define ANIM_PATTERN_WIDTH		float(1 / ANIM_CUT_WIDTH)				// �A�j���[�V�����̉��p�^�[���̉��Z��
#define ANIM_PATTERN_HEIGHT		float(1 / ANIM_CUT_HEIGHT)				// �A�j���[�V�����̏c�p�^�[���̉��Z��
#define PAUSEMENU_MAX			(4)										// �\������I�u�W�F�N�g�̐�
#define PAUSEMENU_SELECT_WIDTH	(350)									// �I�����̉���
#define PAUSEMENU_SELECT_HEIGHT	(100)									// �I�����̏c��
#define PAUSEMENU_WIDTH			(400)									// ���j���[�̉���
#define PAUSEMENU_HEIGHT		(400)									// ���j���[�̏c��

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	PAUSEMENU_TEX_BG = 0,		// ���j���[�w�i
	PAUSEMENU_TEX_CONTINUE,		// �R���e�j���[
	PAUSEMENU_TEX_RULEBOOK,		// ���g���C
	PAUSEMENU_TEX_QUIT,			// �N�C�b�g
	PAUSEMENU_TEX_MAX,			// ����
}PauseMenuTexName;

typedef struct
{
	char *pFilename;	// �t�@�C����
} PauseMenuTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexPausemenu(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ��錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTexturePausemenu[PAUSEMENU_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPausemenu = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Pausemenu				g_aPausemenu[PAUSEMENU_MAX];				// �|�[�Y���j���[�̏��
int						g_nSelectCounter;							// �I�����̃J�E���^�[
int						g_nPuressCounter;							// �v���X�̃J�E���^�[

// �ǂݍ��ރe�N�X�`�����̐ݒ�
PauseMenuTexInfo g_apTexturePausemenuInfo[PAUSEMENU_TEX_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },		// ���j���[�w�i
	{ "data//TEXTURE//pause000.png" },		// �R���e�j���[
	{ "data//TEXTURE//pause001.png" },		// ���g���C
	{ "data//TEXTURE//pause002.png" },		// �N�C�b�g
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPausemenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|�[�Y�̏��̏�����
	for(int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		g_aPausemenu[nCntPausemenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPausemenu[nCntPausemenu].nTexType = PAUSEMENU_TEX_BG;
		g_aPausemenu[nCntPausemenu].fWidth = 0.0f;
		g_aPausemenu[nCntPausemenu].fHeight = 0.0f;
		g_aPausemenu[nCntPausemenu].bUse = false;
		g_aPausemenu[nCntPausemenu].bSelect = false;
	}

	g_nSelectCounter = 0;
	g_nPuressCounter = 0;

	// �e�N�X�`���̓ǂݍ���
	for (int nCntPausemenuTex = 0; nCntPausemenuTex < PAUSEMENU_TEX_MAX; nCntPausemenuTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePausemenuInfo[nCntPausemenuTex].pFilename,
			&g_pTexturePausemenu[nCntPausemenuTex]);
	}


	// ���_���̍쐬
	MakeVertexPausemenu(pDevice);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2), 0.0f), PAUSEMENU_TEX_BG,
		PAUSEMENU_WIDTH, PAUSEMENU_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2 - 100.0f), 0.0f), PAUSEMENU_TEX_CONTINUE,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2), 0.0f), PAUSEMENU_TEX_RULEBOOK,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2 + 100.0f), 0.0f), PAUSEMENU_TEX_QUIT,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPausemenu(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PAUSEMENU_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTexturePausemenu[nCntTex] != NULL)
		{
			g_pTexturePausemenu[nCntTex]->Release();
			g_pTexturePausemenu[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPausemenu != NULL)
	{
		g_pVtxBuffPausemenu->Release();
		g_pVtxBuffPausemenu = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePausemenu()
{
	int nRound = GetRoundCounter();
	// �P�������̏���
	if (GetKeyboardTrigger(DIK_S) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
	{
		g_nSelectCounter = (g_nSelectCounter + 1) % MAX_MENU;
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);


	}
	else if (GetKeyboardTrigger(DIK_W) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		g_nSelectCounter = (g_nSelectCounter + MAX_MENU - 1) % MAX_MENU;
	}

	// �������̏���
	if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
	{
		g_nPuressCounter++;
		if (g_nPuressCounter > 30)
		{
			if (g_nPuressCounter % 5 == 0)
			{
				g_nSelectCounter = (g_nSelectCounter + 1) % MAX_MENU;
			}
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
	{
		g_nPuressCounter++;
		if (g_nPuressCounter > 30)
		{
			if (g_nPuressCounter % 5 == 0)
			{
				g_nSelectCounter = (g_nSelectCounter + MAX_MENU - 1) % MAX_MENU;
			}
		}
	}

	// �|�[�Y�J�E���^�[�̏�����
	if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
	{
		g_nPuressCounter = 0;
	}
	else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
	{
		g_nPuressCounter = 0;
	}

	for (int nCntPausemenu = 1; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		if (g_nSelectCounter == nCntPausemenu - 1)
		{
			g_aPausemenu[nCntPausemenu].bSelect = true;
		}
		else
		{
			g_aPausemenu[nCntPausemenu].bSelect = false;
		}
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
	{
		if (g_aPausemenu[nCntPausemenu].nTexType == PAUSEMENU_TEX_BG)
		{ // �I�������I������Ă���
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (g_aPausemenu[nCntPausemenu].bSelect == true)
		{ // �I�������I������Ă���
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		}
		pVtx[0].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[1].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[2].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[3].col = g_aPausemenu[nCntPausemenu].col;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPausemenu->Unlock();


	FADE pFade;
	// �t�F�[�h���[�h�̎擾
	pFade = GetFade();
	// �t�F�[�h���ʏ��Ԃ�
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		if (pFade == FADE_NONE)
		{
			if (g_nSelectCounter == MENU_CONTINUE)
			{
				//�L�����Z��
				PlaySound(SOUND_LABEL_SE_CANCEL);
				SetPauseState(false);
				SetRulePauseState(false);
				g_nPuressCounter = 0;
			}
			else if (g_nSelectCounter == MENU_RULEBOOK)
			{
				//�L�����Z��
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetPauseState(false);
				SetRulePauseState(true);
			}
			else if (g_nSelectCounter == MENU_QUIT)
			{
				// �Q�[���^�C�g��
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				if (nRound < 5)
				{
					StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
				}
				else
				{
					StopSound(SOUND_LABEL_GAME_R5_BGM);
				}
				SetFade(MODE_TITLE);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPausemenu(void)
{
	int nCntPausemenu;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffPausemenu, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePausemenu[g_aPausemenu[nCntPausemenu].nTexType]);
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPausemenu * 4, 2);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexPausemenu(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSEMENU_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPausemenu,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ANIM_PATTERN_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ANIM_PATTERN_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(ANIM_PATTERN_WIDTH, ANIM_PATTERN_HEIGHT);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPausemenu->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y���j���[�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseMenu(D3DXVECTOR3 pos, int Textype, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
	{
		if (g_aPausemenu[nCntPausemenu].bUse == false)
		{ // �^�C�g�����g�p����Ă��Ȃ��ꍇ
		  // ���_�ʒu�̐ݒ�
			g_aPausemenu[nCntPausemenu].pos = pos;
			g_aPausemenu[nCntPausemenu].fWidth = fWidth;
			g_aPausemenu[nCntPausemenu].fHeight = fHeight;

			// �|�[�Y���j���[�̎�ނ̐ݒ�
			g_aPausemenu[nCntPausemenu].nTexType = Textype;

			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x - g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y - g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x + g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y - g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x - g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y + g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x + g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y + g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);

			g_aPausemenu[nCntPausemenu].bUse = true;	// �g�p�����Ԃɂ���
			break;	// ����break�͂��Ȃ���
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPausemenu->Unlock();
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetPauseSelect(void)
{
	return g_nSelectCounter;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�I�����̏�����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPauseSelect(void)
{
	g_nSelectCounter = MENU_CONTINUE;
}
