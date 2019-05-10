//=============================================================================
//
// �`���[�g���A���w�i���� [tutorialbg.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "bg.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "tutorialbg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIALBG_TEXTURE_NAME  "data/TEXTURE/tutorial.jpg" // �ǂݍ��ރe�N�X�`���t�@�C����
#define TUTORIALBG_TEXTURE_NAME2 "data/TEXTURE/PRESSENTER.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIALBG_POS_X         (0)                            // �w�i�̍���w���W
#define TUTORIALBG_POS_Y         (0)                            // �w�i�̍���x���W
#define TUTORIALBG_WIDTH         (SCREEN_WIDTH)                 // �w�i�̕�
#define TUTORIALBG_HEIGHT        (SCREEN_HEIGHT)                // �w�i�̍���
#define MAX_TUTO_TEX (2)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureTutorialBG[MAX_TUTO_TEX] = {};       // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;   // ���_�o�b�t�@�ւ̃|�C���^ 
D3DXVECTOR3 g_posEnter;
int g_PressTUTO;
TUTOSTATE  g_TSTATE;

//=============================================================================
// ����������
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();
	g_PressTUTO = 0;

	g_posEnter = D3DXVECTOR3(200, 100, 0);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG_TEXTURE_NAME,
		&g_pTextureTutorialBG[0]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG_TEXTURE_NAME2,
		&g_pTextureTutorialBG[1]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_TUTO_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(TUTORIALBG_POS_X, TUTORIALBG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIALBG_WIDTH, TUTORIALBG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIALBG_POS_X, TUTORIALBG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIALBG_WIDTH, TUTORIALBG_HEIGHT, 0.0f);


	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialBG->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;	//���_�|�C���^��8�i�߂�

				//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_posEnter.x - 200, g_posEnter.y - 50, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_posEnter.x + 200, g_posEnter.y - 50, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_posEnter.x - 200, g_posEnter.y + 50, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_posEnter.x + 200, g_posEnter.y + 50, 0.0f);		 //����
																							 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTutorialBG->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitTutorialBG(void)
{

	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < MAX_TUTO_TEX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureTutorialBG[nCount] != NULL)
		{
			g_pTextureTutorialBG[nCount]->Release();
			g_pTextureTutorialBG[nCount] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialBG(void)
{
	g_PressTUTO++;

	if (g_PressTUTO >= 60)
	{
		g_PressTUTO = 0;
	}
	//�L�[�{�[�h�ݒ�
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_TSTATE = TUTO_END;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_TUTO_TEX-1; nCount++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCount]);

		// �^�C�g����ʂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCount * 4,2);
	}
	switch (g_TSTATE)
	{
	case TUTO_NOMAL:
		if (g_PressTUTO >= 30 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTutorialBG[1]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		break;
	case TUTO_END:
		if (g_PressTUTO % 6 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTutorialBG[1]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		break;
	}
}