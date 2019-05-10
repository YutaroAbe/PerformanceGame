//=============================================================================
//
// �u���b�N�ݒu�̏��� [blockeffect.cpp]
// Author :���R���
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BLOCKEFFECT				(128)													// �e�̍ő吔
#define BLOCKEFFECT_TEXTURE_NAME	"data\\TEXTURE\\explosion000.png"						// �ǂݍ��ރe�N�X�`����
#define BLOCKEFFECT_ANIM_X			((0.2f * g_aBlockEffect[nCntBlockEffect].nPatternAnim))	// �ǂݍ��ރe�N�X�`���̃p�^�[��
#define BLOCKEFFECT_ANIM_Y			((0.5f * g_aBlockEffect[nCntBlockEffect].nPatternAnim))	// �ǂݍ��ރe�N�X�`���̃p�^�[��
#define BLOCKEFFECT_SIZE			(40)													// �ǂݍ��ރe�N�X�`���̑傫��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXCOLOR col;					// �F
	D3DXVECTOR3 move;				// �ړ���
	int nCounterAnim;				// �A�j���[�V�����J�E���^�[
	int nPatternAnim;				// �A�j���[�V�����p�^�[��
	bool bUse;						// �g�p���Ă��邩�ǂ���
} BlockEffect;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlockEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlockEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
BlockEffect g_aBlockEffect[MAX_BLOCKEFFECT];			// �g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlockEffect;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �����̏�����
	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		g_aBlockEffect[nCntBlockEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlockEffect[nCntBlockEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBlockEffect[nCntBlockEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlockEffect[nCntBlockEffect].nCounterAnim = 0;
		g_aBlockEffect[nCntBlockEffect].nPatternAnim = 0;
		g_aBlockEffect[nCntBlockEffect].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCKEFFECT_TEXTURE_NAME, &g_pTextureBlockEffect);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCKEFFECT,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlockEffect,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlockEffect->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBlockEffect != NULL)
	{
		g_pTextureBlockEffect->Release();
		g_pTextureBlockEffect = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlockEffect != NULL)
	{
		g_pVtxBuffBlockEffect->Release();
		g_pVtxBuffBlockEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntBlockEffect;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		g_aBlockEffect[nCntBlockEffect].nCounterAnim++;

		if ((g_aBlockEffect[nCntBlockEffect].nCounterAnim % 5) == 0)
		{
			if (g_aBlockEffect[nCntBlockEffect].bUse == true)	// �e���g�p����Ă���
			{
				// �p�^�[��No.���X�V
				g_aBlockEffect[nCntBlockEffect].nPatternAnim = (g_aBlockEffect[nCntBlockEffect].nPatternAnim + 1) % 10;

				// �e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
				pVtx[1].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
				pVtx[2].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);
				pVtx[3].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);

				if (g_aBlockEffect[nCntBlockEffect].nPatternAnim == 0)
				{
					g_aBlockEffect[nCntBlockEffect].bUse = false;	// �g�p���Ă��Ȃ���Ԃɂ���
				}
			}
		}

		g_aBlockEffect[nCntBlockEffect].pos.y += g_aBlockEffect[nCntBlockEffect].move.y;

		// ���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

		pVtx += 4;	// �Y���̈ʒu�܂Ői�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlockEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlockEffect;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlockEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlockEffect);

	// �|���S���̕`��
	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		if (g_aBlockEffect[nCntBlockEffect].bUse == true)	// �e���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBlockEffect,
				2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntBlockEffect;

	for (nCntBlockEffect = 0; nCntBlockEffect < MAX_BLOCKEFFECT; nCntBlockEffect++)
	{
		if (g_aBlockEffect[nCntBlockEffect].bUse == false)
		{
			VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBlockEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBlockEffect * 4);	// �Y���̈ʒu�܂Ői�߂�

			g_aBlockEffect[nCntBlockEffect].pos = pos;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y - BLOCKEFFECT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x - BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlockEffect[nCntBlockEffect].pos.x + BLOCKEFFECT_SIZE, g_aBlockEffect[nCntBlockEffect].pos.y + BLOCKEFFECT_SIZE, 0.0f);

			g_aBlockEffect[nCntBlockEffect].col = col;

			// ���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aBlockEffect[nCntBlockEffect].nPatternAnim = 0;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
			pVtx[1].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.0f + BLOCKEFFECT_ANIM_Y);
			pVtx[2].tex = D3DXVECTOR2(0.0f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);
			pVtx[3].tex = D3DXVECTOR2(0.2f + BLOCKEFFECT_ANIM_X, 0.5f + BLOCKEFFECT_ANIM_Y);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffBlockEffect->Unlock();

			g_aBlockEffect[nCntBlockEffect].nCounterAnim = 0;
			g_aBlockEffect[nCntBlockEffect].bUse = true;	// �g�p���Ă�����
			break;
		}
	}
}