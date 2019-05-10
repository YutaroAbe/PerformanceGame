//=============================================================================
//
// �������Ԃ̏��� [gauge.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "gauge.h"
#include "game.h"
#include "ColorBall.h"
#include "model.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAUGE000		"data/TEXTURE/LifeFrame000.png"		// �ǂݍ��ރe�N�X�`���t�F�C����
#define MAX_GAUGE				(2)									// �Q�[�W�̍ő吔	
#define REDUCE_GAUGE			(0.20f)								// �Q�[�W�̌����(���t���[��)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGauge[MAX_GAUGE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
float g_fGauge;												// �Q�[�W�̒l
float g_fGaugeColR;											// �Q�[�W�̐F(��)
float g_fGaugeColG;											// �Q�[�W�̐F(��)
float g_fGaugeColB;											// �Q�[�W�̐F(��)
GAUGE g_aGauge;
//=============================================================================
// ����������
//=============================================================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �Q�[�W�̏�����
	g_fGauge = 340.0f;
	g_fGaugeColR = 0.0f;
	g_fGaugeColG = 1.0f;
	g_fGaugeColB = 0.0f;
	g_aGauge.nChargeGauge = 1;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE000, &g_pTextureGauge[1]);
	//D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE001, &g_pTextureGauge[1]);
	// ���_���̍쐬
	MakeVertexGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGauge(void)
{
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureGauge[nCntGauge] != NULL)
		{
			g_pTextureGauge[nCntGauge]->Release();
			g_pTextureGauge[nCntGauge] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGauge(void)
{
	//�Q�[���X�e�C�g�̎擾
	FADE *pFade;
	pFade = GetFade();
	COLORBALL *pColorBall;
	pColorBall = GetColorBall();
	Player *pPlayer;
	pPlayer = GetPlayer();

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	//�������F�ɏ���Ă��Ȃ��Ƃ��Q�[�W������
	if (pPlayer->pModel != NULL)
	{
		if (pColorBall->nType + 1 != pPlayer->pModel->col 
			&& pPlayer->pModel->col != BLOCKCOLOR_START
			&& pColorBall->state == COLORBALLSTATE_STOP)
		{
			g_fGauge += (REDUCE_GAUGE * g_aGauge.nChargeGauge);
			PlaySound(SOUND_LABEL_SE015);
		}
	}
	//�Q�[�W�̏����ʒu
	if (g_fGauge < 340.0f)
	{
		g_fGauge = 341.0f;
	}

	pVtx[0].pos = D3DXVECTOR3(100.0f, g_fGauge, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(150.0f, g_fGauge, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f, 580.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(150.0f, 580.0f, 0.0f);

	// �F�̕ω�(�Q�[�W)
	if (g_fGauge >= 320.0f && g_fGauge <= 381.9f)
	{
		// �Q�[�W(�ΐF)
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
	}
	else if (g_fGauge >= 381.9f && g_fGauge <= 484.9f)
	{
		// �Q�[�W(�I�����W�F)
		g_fGaugeColG += 0.004f;
		g_fGaugeColR += 0.004f;
		if (g_fGaugeColG >= 0.5f)
		{
			g_fGaugeColG = 0.5f;
		}
		if (g_fGaugeColR >= 1.0f)
		{
			g_fGaugeColR = 1.0f;
		}
		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
	}
	else if (g_fGauge >= 484.9f && g_fGauge <= 580.0f)
	{
		// �Q�[�W(�ԐF)
		g_fGaugeColG -= 0.004f;
		if (g_fGaugeColG <= 0.0f)
		{
			g_fGaugeColG = 0.0f;
		}
		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
	}
	//�Q�[�W���Ȃ��Ȃ�ƃQ�[���I�[�o�[
	if (g_fGauge >= 580.0f && *pFade != FADE_OUT)
	{	// �̗͂��Ȃ��Ȃ���(GAMEOVER)
		SetFade(MODE_GAMEOVER);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureGauge[nCntGauge]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	// ���_���̍쐬
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		if (nCntGauge == 0)
		{	//�Q�[�W
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(100.0f, g_fGauge, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(150.0f, g_fGauge, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(100.0f, 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(150.0f, 580.0f, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		}
		else if (nCntGauge == 1)
		{	//�̗͂̃t���[��
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(98.0f, 315.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(150.0f, 315.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(98.0f, 582.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(150.0f, 582.0f, 0.0f);

			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffGauge->Unlock();
}


//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
GAUGE *GetGauge(void)
{
	return &g_aGauge;
}
