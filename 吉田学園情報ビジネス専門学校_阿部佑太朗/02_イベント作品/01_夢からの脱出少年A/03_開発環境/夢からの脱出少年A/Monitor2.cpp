//=============================================================================
// 
// ���j�^�[�̏��� [Monitor.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Monitor2.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MONITOR2_TEXTURENAME		"data\\TEXTURE\\timerframe.png"	//�e�N�X�`���̃t�@�C����
#define MONITOR2_X				(930)							//������WX
#define MONITOR2_Y				(500)							//������WY	
#define MONITOR2_WIDTH			(1230)				//�����`�̉������W
#define MONITOR2_HEIGHT			(700)				//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMonitor2 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMonitor2 = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//*****************************************************************************
// ������
//*****************************************************************************
void InitMonitor2(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MONITOR2_TEXTURENAME,
		&g_pTextureMonitor2);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMonitor2,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMonitor2->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(MONITOR2_X, MONITOR2_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MONITOR2_WIDTH, MONITOR2_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MONITOR2_X, MONITOR2_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MONITOR2_WIDTH, MONITOR2_HEIGHT, 0.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMonitor2->Unlock();

}
//=============================================================================
// �I������
//=============================================================================
void UninitMonitor2(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMonitor2 != NULL)
	{
		g_pTextureMonitor2->Release();
		g_pTextureMonitor2 = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffMonitor2 != NULL)
	{
		g_pVtxBuffMonitor2->Release();
		g_pVtxBuffMonitor2 = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonitor2(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonitor2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMonitor2, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMonitor2);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}