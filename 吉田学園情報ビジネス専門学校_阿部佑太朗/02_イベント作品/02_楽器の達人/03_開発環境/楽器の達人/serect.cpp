//=============================================================================
//
// �Z���N�g�̏��� [score.cpp]
// Author :�@YUTARO�@ABE
//
//=============================================================================
#include "serect.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "ranking.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SERECT_TEXTURE_NAME "data/TEXTURE/selecttitle1.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define SERECT_TEXTURE_NAME1 "data/TEXTURE/tutorial.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define SERECT_TEXTURE_NAME2 "data/TEXTURE/game111.jpg"		    // �ǂݍ��ރe�N�X�`���t�@�C����
#define SERECT_TEXTURE_NAME3 "data/TEXTURE/ranking.jpg" 		// �ǂݍ��ރe�N�X�`���t�@�C����

#define TUTORIAL_POS_X        (0)                               // �w�i�̍���w���W
#define TUTORIAL_POS_Y        (0)                               // �w�i�̍���x���W
#define TUTORIAL_WIDTH        (SCREEN_WIDTH)                    // �w�i�̕�
#define TUTORIAL_HEIGHT       (SCREEN_HEIGHT)                   // �w�i�̍���
#define MAX_TEX					(4)								// �I��
#define SERECT_POS_X			(0)								// �Z���N�g��X���W(����)
#define SERECT_POS_Y			(0)								// �Z���N�g��Y���W(�E��)
#define SERECT_WIDTH		    (SCREEN_WIDTH)					// �E�C���h�E�̉�
#define SERECT_HEIGHT			(SCREEN_HEIGHT)					// �E�C���h�E�̍���

#define SERECT_TEXTURE_U		(1.0f)
#define SERECT_TEXTURE_V		(1.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureSERECT[MAX_TEX] = {};			   // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSERECT = NULL;               // ���_�o�b�t�@�ւ̃|�C���^
SERECT g_Serect;											   // �|�X�̏��
STETAS g_Stetas;							                   // �X�e�[�^�X

															   //=============================================================================
															   // ����������
															   //=============================================================================
void InitSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Serect.pos = D3DXVECTOR3((SERECT_POS_X + SERECT_WIDTH) / 2, (SERECT_POS_Y + SERECT_HEIGHT) / 2, 0.0f);
	g_Serect.nCounrtState = 0;
	g_Serect.SerectCor = 1.0f;
	g_Stetas = NORMAL;

	float posSerect = (SERECT_HEIGHT / 2 - 271.0f);						//�Z���N�g�̍�

																		// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME,
		&g_pTextureSERECT[0]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME1,
		&g_pTextureSERECT[1]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME2,
		&g_pTextureSERECT[2]);

	D3DXCreateTextureFromFile(pDevice,
		SERECT_TEXTURE_NAME3,
		&g_pTextureSERECT[3]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSERECT,
		NULL);

	VERTEX_2D *pVtxSERECT;   // ���_���ւ̃|�C���^

							 // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	pVtxSERECT[0].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_POS_Y, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_POS_Y, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_HEIGHT, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_HEIGHT, 0.0f);

	// ���_�e�N�X�`��
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// ���_�J���[
	pVtxSERECT[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSERECT->Unlock();

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	pVtxSERECT += 4;

	//
	//	�`���[�g���A��
	//
	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// ���_�e�N�X�`��
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// ���_�J���[
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSERECT->Unlock();

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	//
	//	�Q�[��
	//
	pVtxSERECT += 8;
	posSerect += 155;

	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// ���_�e�N�X�`��
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// ���_�J���[
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSERECT->Unlock();


	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	//
	//	�����L���O
	//
	pVtxSERECT += 12;
	posSerect += 155;

	pVtxSERECT[0].pos = D3DXVECTOR3(100, posSerect, 0.0f);
	pVtxSERECT[1].pos = D3DXVECTOR3(600, posSerect, 0.0f);
	pVtxSERECT[2].pos = D3DXVECTOR3(100, posSerect + 150, 0.0f);
	pVtxSERECT[3].pos = D3DXVECTOR3(600, posSerect + 150, 0.0f);

	// ���_�e�N�X�`��
	pVtxSERECT[0].rhw = 1.0f;
	pVtxSERECT[1].rhw = 1.0f;
	pVtxSERECT[2].rhw = 1.0f;
	pVtxSERECT[3].rhw = 1.0f;

	// ���_�J���[
	pVtxSERECT[0].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[1].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[2].col = D3DCOLOR_RGBA(130, 130, 130, 255);
	pVtxSERECT[3].col = D3DCOLOR_RGBA(130, 130, 130, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtxSERECT[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxSERECT[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxSERECT[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxSERECT[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSERECT->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitSerect(void)
{
	for (int nCnt = 0; nCnt<4; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureSERECT[nCnt] != NULL)
		{

			g_pTextureSERECT[nCnt]->Release();
			g_pTextureSERECT[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffSERECT != NULL)
	{
		g_pVtxBuffSERECT->Release();
		g_pVtxBuffSERECT = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateSerect(void)
{
	VERTEX_2D *pVtxSERECT;				    // ���_���ւ̃|�C���^

	FADE p_fade = *GetFade();				// �t�F�[�h���
											// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSERECT->Lock(0, 0, (void**)&pVtxSERECT, 0);

	if (GetKeyboardTrigger(DIK_W) == true)
	{

		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 3) % 3;
		g_Serect.SerectCor = 1.0f;
	}

	if (GetKeyboardTrigger(DIK_S) == true)
	{
		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 1) % 3;
		g_Serect.SerectCor = 1.0f;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.nCounrtState = (g_Serect.nCounrtState + 2) % 3;
		g_Serect.SerectCor = 1.0f;
	}
	//���_�J���[�ݒ�
	pVtxSERECT[g_Serect.nCounrtState * 4 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 1 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 2 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);
	pVtxSERECT[g_Serect.nCounrtState * 4 + 3 + 4].col = D3DXCOLOR(g_Serect.SerectCor, g_Serect.SerectCor, g_Serect.SerectCor, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSERECT->Unlock();
	if (p_fade != FADE_OUT)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Serect.nCounrtState == 0)
			{
				SetFade(MODE_TUTORIAL);
			}
			if (g_Serect.nCounrtState == 1)
			{
				SetFade(MODE_GAME);
			}
			if (g_Serect.nCounrtState == 2)
			{
				SetFade(MODE_RANKING);
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSERECT, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//	{// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSERECT[0]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[2]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4,
		2);

	pDevice->SetTexture(0, g_pTextureSERECT[3]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 3 * 4,
		2);
}
//====================================
//�Z���N�g�̎擾
//====================================
STETAS *GetSel(void)
{
	return &g_Stetas;
}