//=============================================================================
//
// �t���[������ [frame.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FRAME_TEXTURE_NAME000  "data/TEXTURE/score_frame.png"    // �ǂݍ��ރe�N�X�`���t�@�C����(�X�R�A)
#define FRAME_TEXTURE_NAME001  "data/TEXTURE/score_logo.png"     // �ǂݍ��ރe�N�X�`���t�@�C����(�X�R�A���S)
#define FRAME_TEXTURE_NAME002  "data/TEXTURE/timer_frame.png"    // �ǂݍ��ރe�N�X�`���t�@�C����(�^�C�}�[)
#define FRAME_TEXTURE_NAME003  "data/TEXTURE/timer_logo.png"     // �ǂݍ��ރe�N�X�`���t�@�C����(�^�C�}�[���S)
//#define FRAME_TEXTURE_NAME002  "data/TEXTURE/frame_coin.png"     // �ǂݍ��ރe�N�X�`���t�@�C����(�v���[���g)
#define MAX_FRAME              (4)                               // �K�v�ȃt���[����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureFrame[MAX_FRAME] = {};       // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;   // ���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	// �X�R�A�t���[��
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME000,
		&g_pTextureFrame[0]);

	// �X�R�A���S
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME001,
		&g_pTextureFrame[1]);

	// �^�C�}�[�t���[��
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME002,
		&g_pTextureFrame[2]);

	// �^�C�}�[���S
	D3DXCreateTextureFromFile(pDevice,
		FRAME_TEXTURE_NAME003,
		&g_pTextureFrame[3]);

	//// �v���[���g�t���[��
	//D3DXCreateTextureFromFile(pDevice,
	//	FRAME_TEXTURE_NAME002,
	//	&g_pTextureFrame[2]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	//----------------
	// �X�R�A�t���[��
	//----------------

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(800, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1270, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(800, 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1270, 150, 0.0f);

	// ���_�e�N�X�`��
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// �X�R�A���S
	//----------------

	pVtx += 4; // �|�C���^�����炷

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(900, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1000, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900, 60, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1000, 60, 0.0f);

	// ���_�e�N�X�`��
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// �^�C�}�[�t���[��
	//----------------

	pVtx += 4; // �|�C���^�����炷

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(530, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(530, 150, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740, 150, 0.0f);

	// ���_�e�N�X�`��
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//----------------
	// �^�C�}�[���S
	//----------------

	pVtx += 4; // �|�C���^�����炷

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(593, 16, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(673, 16, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(593, 76, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(673, 76, 0.0f);

	// ���_�e�N�X�`��
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////----------------
	//// �v���[���g�t���[��
	////----------------

	//pVtx += 4; // �|�C���^�����炷

    //// ���_���W
	//pVtx[0].pos = D3DXVECTOR3(240, 0, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(370, 0, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(240, 120, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(370, 120, 0.0f);

	//// ���_�e�N�X�`��
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// ���_�J���[
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

	//// �e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitFrame(void)
{
	// �e�N�X�`���̔j��
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{// �\������t���[���������J��Ԃ�
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateFrame(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{// �\������t���[���������J��Ԃ�
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFrame[nCntFrame]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntFrame * 4,
			2);
	}
}