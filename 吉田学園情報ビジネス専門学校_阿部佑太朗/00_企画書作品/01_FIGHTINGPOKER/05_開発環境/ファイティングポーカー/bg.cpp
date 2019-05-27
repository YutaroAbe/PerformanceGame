//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEX_1			"data/TEXTURE/bg.jpg"
#define BG_TEX_2			"data/TEXTURE/bg2.jpg"
#define BG_WIDTH			(SCREEN_WIDTH)				//�w�i�̕�
#define BG_HEIGHT			(SCREEN_HEIGHT)				//�w�i�̍���
#define BG_POS_X			(0)							//�w�i�̍���X���W
#define BG_POS_Y			(0)							//�w�i�̍���Y���W
#define MAX_BG				(1)							//�w�i�̍ő吔
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//���_�o�b�t�@�̃|�C���^
BG g_BG;												//�\����
//=============================================================================
// ����������
//=============================================================================
void InitBG(void)
{
	MODE mode = GetMode();
	GAMEMODE GameMode = GetGameMode();

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�e�평����
	g_BG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̓ǂݍ���
	if (mode == MODE_SELECT || GameMode == GAMEMODE_PLAYERSHOW)
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEX_1, &g_pTextureBG);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEX_2, &g_pTextureBG);
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// �I�������@
//=============================================================================
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// �X�V�����@
//=============================================================================
void UpdateBG(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �w�i�̎擾
//=============================================================================
BG *GetBG(void)
{
	return &g_BG;
}
