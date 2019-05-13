//=============================================================================
//
// �����L���O�w�i���� [rankingbg.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "bg.h"
#include "rankingscore.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKINGBG_TEXTURE_NAME  "data/TEXTURE/rankkingbg000.jpg" // �ǂݍ��ރe�N�X�`���t�@�C����
#define RANKINGBG_POS_X         (0)                           // �����L���O�w�i�̍���w���W
#define RANKINGBG_POS_Y         (0)                           // �����L���O�w�i�̍���x���W
#define RANKINGBG_WIDTH         (SCREEN_WIDTH)                // �����L���O�w�i�̕�
#define RANKINGBG_HEIGHT        (SCREEN_HEIGHT)               // �����L���O�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureRankingBG = NULL;   // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;   // ���_�o�b�t�@�ւ̃|�C���^
int                     g_nCounterRankingBG;          // �^�C�g����ʂɑJ�ڂ���^�C�~���O

//=============================================================================
// ����������
//=============================================================================
void InitRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_nCounterRankingBG = 0;  // �J�E���^�[��������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RANKINGBG_TEXTURE_NAME,
		&g_pTextureRankingBG);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingBG,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(RANKINGBG_POS_X, RANKINGBG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANKINGBG_WIDTH, RANKINGBG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANKINGBG_POS_X, RANKINGBG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANKINGBG_WIDTH, RANKINGBG_HEIGHT, 0.0f);


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
	g_pVtxBuffRankingBG->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitRankingBG(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureRankingBG != NULL)
	{
		g_pTextureRankingBG->Release();
		g_pTextureRankingBG = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingBG != NULL)
	{
		g_pVtxBuffRankingBG->Release();
		g_pVtxBuffRankingBG = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingBG(void)
{
	FADE *fade;
	fade = GetFade();

	g_nCounterRankingBG++;

	if (GetKeyboardTrigger(DIK_RETURN) && *fade == FADE_NONE || g_nCounterRankingBG % 600 == 0 && *fade == FADE_NONE)
	{// ENTER�L�[��������邩��莞�Ԃ��o�߂���
		SetFade(MODE_TITLE);
		// �����L���O�X�R�A�̎擾
		RANKINGSCORE *rankingscore;
		rankingscore = GetRankingScore();

		for (int nCntRankingScore = 0; nCntRankingScore < MAX_RANKINGSCORE; nCntRankingScore++, rankingscore++)
		{// �����L���O�X�R�A�̐������J��Ԃ�
			if (rankingscore->state == RANKINGSCORESTATE_UPDATE)
			{// �X�V��ԂɂȂ��Ă�����
				rankingscore->state = RANKINGSCORESTATE_NONE;
				rankingscore->col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingBG);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}