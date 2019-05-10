//=============================================================================
//
// �Z���N�g��ʏ��� [select2D.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "select2D.h"
#include "fade.h"
#include "input.h"
#include "select.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RETURN_TEX				"data/TEXTURE/SELECT/return.png"
#define BATTLE_TEX				"data/TEXTURE/SELECT/battle.png"
#define RULE_TEX				"data/TEXTURE/SELECT/rule.png"
#define CREDIT_TEX				"data/TEXTURE/SELECT/credit.png"
#define GUIDE_TEX				"data/TEXTURE/SELECT/guide.png"
#define OPERATION_TEX			"data/TEXTURE/SELECT/operation.png"
#define MAX_TAG					(4)
#define MAX_TEXTURE				(SELECT_MAX)		//�g���e�N�X�`���̐�
//=============================================================================
// �Z���N�g�̏��
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	float fWidth;								//��
	float fHeight;								//����
	SELECTTYPE type;							//���
}SelectInfo;
//=============================================================================
// UI�̔z�u
//=============================================================================
SelectInfo g_aSelectInfo[] =
{
	{ D3DXVECTOR3(90.0f,90.0f,0.0f), 520.0f, 220.0f,SELECT_CURSOR },			// �g
	{ D3DXVECTOR3(100.0f,100.0f,0.0f), 500.0f, 200.0f,SELECT_BATTLE },			// �o�g��
	{ D3DXVECTOR3(700.0f,100.0f,0.0f), 500.0f, 200.0f,SELECT_RULE },			// ���[���u�b�N
	{ D3DXVECTOR3(100.0f,350.0f,0.0f), 500.0f, 200.0f,SELECT_CREDIT },			// �N���W�b�g
	{ D3DXVECTOR3(700.0f,350.0f,0.0f), 500.0f, 200.0f,SELECT_RETURN },			// �^�C�g���ɖ߂�
	{ D3DXVECTOR3(0.0f,600.0f,0.0f), SCREEN_WIDTH, 120.0f,SELECT_OPERATION },	// �e�����
	{ D3DXVECTOR3(0.0f,0.0f,0.0f), SCREEN_WIDTH, 80.0f,SELECT_GUIDE },			// �������
};

D3DXVECTOR3		g_aCursorPos[MAX_TAG] =
{// �J�[�\���ʒu�ݒ�
	D3DXVECTOR3(90.0f, 90.0f, 0.0f),
	D3DXVECTOR3(690.0f, 90.0f, 0.0f),
	D3DXVECTOR3(90.0f, 340.0f, 0.0f),
	D3DXVECTOR3(690.0f, 340.0f, 0.0f),
};
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelect2D[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect2D = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
SELECT2D g_aSelect2D[MAX_TEXTURE];								// �Z���N�g�̏��
SELECTTYPE g_SelectType;
int g_nNumber;
bool g_bLength;
//=============================================================================
// ����������
//=============================================================================
void InitSelect2D(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		g_aSelect2D[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect2D[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSelect2D[nCnt].fWidth = 0.0f;
		g_aSelect2D[nCnt].fHeight = 0.0f;
		g_aSelect2D[nCnt].bUse = false;
		g_aSelect2D[nCnt].bSelect = false;
	}
	g_nNumber = 0;
	g_bLength = false;
	g_SelectType = SELECT_BATTLE;
	MakeVertexSelect(pDevice);

	//�ʒu�@���@���@���@�����@���@���
	for (int nCntSelect = 0; nCntSelect < sizeof g_aSelectInfo / sizeof(SelectInfo); nCntSelect++)
	{
		SetSelect2D(g_aSelectInfo[nCntSelect].pos, g_aSelectInfo[nCntSelect].fWidth, g_aSelectInfo[nCntSelect].fHeight, g_aSelectInfo[nCntSelect].type);
	}
}
//=============================================================================
// �I������
//=============================================================================
void UninitSelect2D(void)
{
	for (int nCntCharSelect = 0; nCntCharSelect < MAX_TEXTURE; nCntCharSelect++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSelect2D[nCntCharSelect] != NULL)
		{
			g_pTextureSelect2D[nCntCharSelect]->Release();
			g_pTextureSelect2D[nCntCharSelect] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect2D != NULL)
	{
		g_pVtxBuffSelect2D->Release();
		g_pVtxBuffSelect2D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect2D(void)
{
	FADE pFade = GetFade();
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	g_pVtxBuffSelect2D->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	pVtx[0].col = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 1.0f, 0.0f, 1.0f);

	if (GetKeyboardTrigger(DIK_A) == true
		|| GetKeyboardTrigger(DIK_LEFT) == true
		|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_LEFT) == true 
		|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_LEFT) == true)
	{// �ړ�
		g_nNumber = (g_nNumber + 3) % 4;
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
	}
	else if (GetKeyboardTrigger(DIK_D) == true
		|| GetKeyboardTrigger(DIK_RIGHT) == true
		|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_RIGHT) == true
		|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_RIGHT) == true)
	{// �ړ�
		g_nNumber = (g_nNumber + 1) % 4;
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
	}
	if (GetKeyboardTrigger(DIK_W) == true
		|| GetKeyboardTrigger(DIK_UP) == true
		|| GetKeyboardTrigger(DIK_S) == true
		|| GetKeyboardTrigger(DIK_DOWN) == true
		|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true
		|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_DOWN) == true
		|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP) == true
		|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_DOWN) == true)
	{// �㉺�ړ�
		g_bLength = g_bLength ? false : true;
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
	}
	if (g_nNumber == 0)
	{
		g_aSelect2D[0].pos = g_aCursorPos[0];
		g_SelectType = SELECT_BATTLE;
		if (g_bLength == true)
		{
			g_nNumber = 2;
			g_aSelect2D[0].pos = g_aCursorPos[2];
			g_SelectType = SELECT_CREDIT;
			g_bLength = false;
		}
	}
	else if (g_nNumber == 1)
	{
		g_aSelect2D[0].pos = g_aCursorPos[1];
		g_SelectType = SELECT_RULE;
		if (g_bLength == true)
		{
			g_nNumber = 3;
			g_aSelect2D[0].pos = g_aCursorPos[3];
			g_SelectType = SELECT_RETURN;
			g_bLength = false;
		}
	}
	else if (g_nNumber == 2)
	{
		g_aSelect2D[0].pos = g_aCursorPos[2];
		g_SelectType = SELECT_CREDIT;
		if (g_bLength == true)
		{
			g_nNumber = 0;
			g_aSelect2D[0].pos = g_aCursorPos[0];
			g_SelectType = SELECT_BATTLE;
			g_bLength = false;
		}
	}
	else if (g_nNumber == 3)
	{
		g_aSelect2D[0].pos = g_aCursorPos[3];
		g_SelectType = SELECT_RETURN;
		if (g_bLength == true)
		{
			g_nNumber = 1;
			g_aSelect2D[0].pos = g_aCursorPos[1];
			g_SelectType = SELECT_RULE;
			g_bLength = false;
		}
	}
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aSelect2D[0].pos;
	pVtx[1].pos = D3DXVECTOR3(g_aSelect2D[0].fWidth, 0.0f, 0.0f) + g_aSelect2D[0].pos;
	pVtx[2].pos = D3DXVECTOR3(0.0f, g_aSelect2D[0].fHeight, 0.0f) + g_aSelect2D[0].pos;
	pVtx[3].pos = D3DXVECTOR3(g_aSelect2D[0].fWidth, g_aSelect2D[0].fHeight, 0.0f) + g_aSelect2D[0].pos;
	g_pVtxBuffSelect2D->Unlock();	// ���_�o�b�t�@���A�����b�N


	g_pVtxBuffSelect2D->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	pVtx += 4 * SELECT_OPERATION;
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_nNumber * 0.25f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_nNumber * 0.25f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_nNumber * 0.25f + 0.25f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_nNumber * 0.25f + 0.25f);

	g_pVtxBuffSelect2D->Unlock();	// ���_�o�b�t�@���A�����b�N

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect2D(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾����

												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect2D, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSelect = 0; nCntSelect < MAX_TEXTURE; nCntSelect++)
	{
		if (g_aSelect2D[nCntSelect].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSelect2D[g_aSelect2D[nCntSelect].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSelect * 4, 2);
		}
	}
}
//=============================================================================
// �Z���N�g�ݒ�
//=============================================================================
void SetSelect2D(D3DXVECTOR3 pos, float fWidth, float fHeight, SELECTTYPE type)
{
	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect2D->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++, pVtx += 4)
	{
		if (g_aSelect2D[nCnt].bUse == false)
		{
			g_aSelect2D[nCnt].pos = pos;			// �ʒu
			g_aSelect2D[nCnt].fWidth = fWidth;	// ����
			g_aSelect2D[nCnt].fHeight = fHeight;	// ��
			g_aSelect2D[nCnt].type = type;		// ���

			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aSelect2D[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aSelect2D[nCnt].fWidth, 0.0f, 0.0f) + g_aSelect2D[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(0.0f, g_aSelect2D[nCnt].fHeight, 0.0f) + g_aSelect2D[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aSelect2D[nCnt].fWidth, g_aSelect2D[nCnt].fHeight, 0.0f) + g_aSelect2D[nCnt].pos;
			g_aSelect2D[nCnt].bUse = true;
			break;
		}
	}
	g_pVtxBuffSelect2D->Unlock();	// ���_�o�b�t�@���A�����b�N
}
//=============================================================================
// ���_��񐶐�����
//=============================================================================
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect2D,
		NULL);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, RETURN_TEX, &g_pTextureSelect2D[SELECT_RETURN]);
	D3DXCreateTextureFromFile(pDevice, BATTLE_TEX, &g_pTextureSelect2D[SELECT_BATTLE]);
	D3DXCreateTextureFromFile(pDevice, RULE_TEX, &g_pTextureSelect2D[SELECT_RULE]);
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEX, &g_pTextureSelect2D[SELECT_CREDIT]);
	D3DXCreateTextureFromFile(pDevice, OPERATION_TEX, &g_pTextureSelect2D[SELECT_OPERATION]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEX, &g_pTextureSelect2D[SELECT_GUIDE]);

	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect2D->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++, pVtx += 4)
	{
		// �|���S���̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aSelect2D[nCnt].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aSelect2D[nCnt].fWidth, 0.0f, 0.0f) + g_aSelect2D[nCnt].pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f, g_aSelect2D[nCnt].fHeight, 0.0f) + g_aSelect2D[nCnt].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aSelect2D[nCnt].fWidth, g_aSelect2D[nCnt].fHeight, 0.0f) + g_aSelect2D[nCnt].pos;
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// �|���S���̐F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect2D->Unlock();
}
//=============================================================================
// �^�C�v�擾
//=============================================================================
SELECTTYPE GetSelectType(void)
{
	return g_SelectType;
}
