//=============================================================================
// 
// ���j�^�[�̏��� [Monitor.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Monitor.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MONITOR_TEXTURENAME		"data\\TEXTURE\\Monitor.png"	//�e�N�X�`���̃t�@�C����
#define MONITOR_X				(880)							//������WX
#define MONITOR_Y				(0)							//������WY	
#define MONITOR_WIDTH			(1180)				//�����`�̉������W
#define MONITOR_HEIGHT			(200)				//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMonitor = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMonitor = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//*****************************************************************************
// ������
//*****************************************************************************
void InitMonitor(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MONITOR_TEXTURENAME,
		&g_pTextureMonitor);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMonitor,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMonitor->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(MONITOR_X, MONITOR_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MONITOR_WIDTH, MONITOR_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MONITOR_X, MONITOR_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MONITOR_WIDTH, MONITOR_HEIGHT, 0.0f);
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
	g_pVtxBuffMonitor->Unlock();

}
//=============================================================================
// �I������
//=============================================================================
void UninitMonitor(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMonitor != NULL)
	{
		g_pTextureMonitor->Release();
		g_pTextureMonitor = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffMonitor != NULL)
	{
		g_pVtxBuffMonitor->Release();
		g_pVtxBuffMonitor = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonitor(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonitor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMonitor, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMonitor);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}