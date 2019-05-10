//=============================================================================
//
// �J���X�̏��� [crow.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "crow.h"
#include "bullet.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CROW		"data/TEXTURE/crow.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCrow = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCrow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Crow					g_Crow;		            // �J���X�̏��
float                   g_Tex;                  // �e�N�X�`��U���W��؂�ւ���

//=============================================================================
// ����������
//=============================================================================
void InitCrow(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_Crow.pos = D3DXVECTOR3(100.0f, 400.0f, 0.0f);   // �ʒu�̏�����
	g_Crow.move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);      // �ړ��ʂ�������
	g_Crow.nCounterAnim = 0;                          // �A�j���[�V�����J�E���^�[��������
	g_Crow.nPatternAnim = 0;                          // �p�^�[��No.��������
	g_Crow.itemtype = 0;                              // �A�C�e���̃^�C�v��������
	g_Crow.fWidth = 35.0f;                            // ����������
	g_Crow.fHeight = 35.0f;                           // ������������
	g_Tex = 0.5f;
	

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CROW, &g_pTextureCrow);

	// ���_���̍쐬
	MakeVertexCrow(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitCrow(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureCrow != NULL)
	{
		g_pTextureCrow->Release();
		g_pTextureCrow = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCrow != NULL)
	{
		g_pVtxBuffCrow->Release();
		g_pVtxBuffCrow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCrow(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCrow->Lock(0, 0, (void**)&pVtx, 0);

	g_Crow.pos += g_Crow.move;  // �ʒu�X�V

	if (g_Crow.pos.x + g_Crow.fWidth >= SCREEN_WIDTH)
	{
		g_Crow.move.x *= -1;   // �ړ��������]
		g_Tex = 0.0f;          // U���W�ړ�
	}
	if (g_Crow.pos.x - g_Crow.fWidth <= 0.0f)
	{
		g_Crow.move.x *= -1;   // �ړ��������]
		g_Tex = 0.5f;          // U���W�ړ�
	}

	if (CollisionBullet2(&g_Crow.pos, g_Crow.fWidth, g_Crow.fHeight,&g_Crow.nIdxBullet) == true)
	{
		DeleteBullet(*g_Crow.nIdxBullet);
		PlaySound(SOUND_LABEL_SE_KARASU);
	}

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(-g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[1].pos = D3DXVECTOR3(g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[2].pos = D3DXVECTOR3(-g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[3].pos = D3DXVECTOR3(g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;

	pVtx[0].tex = D3DXVECTOR2(g_Tex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_Tex + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_Tex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_Tex + 0.5f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCrow->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCrow, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCrow);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexCrow(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCrow,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCrow->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[1].pos = D3DXVECTOR3(g_Crow.fWidth, -g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[2].pos = D3DXVECTOR3(-g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;
	pVtx[3].pos = D3DXVECTOR3(g_Crow.fWidth, g_Crow.fHeight, 0.0f) + g_Crow.pos;

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    // ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCrow->Unlock();
}
