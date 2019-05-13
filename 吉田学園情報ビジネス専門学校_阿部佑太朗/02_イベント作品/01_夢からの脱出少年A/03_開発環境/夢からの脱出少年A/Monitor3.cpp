//=============================================================================
// 
// ���j�^�[�̏��� [Monitor.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Monitor3.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MONITOR3_TEXTURENAME		"data\\TEXTURE\\timerframe2.png"	//�e�N�X�`���̃t�@�C����
#define MONITOR3_X				(80)							//������WX
#define MONITOR3_Y				(000)							//������WY	
#define MONITOR3_WIDTH			(450)				//�����`�̉������W
#define MONITOR3_HEIGHT			(200)				//�����`�̏c�����W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMonitor3 = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMonitor3 = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//*****************************************************************************
// ������
//*****************************************************************************
void InitMonitor3(void)
{	//���[�J���ϐ�
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MONITOR3_TEXTURENAME,
		&g_pTextureMonitor3);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMonitor3,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMonitor3->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(MONITOR3_X, MONITOR3_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MONITOR3_WIDTH, MONITOR3_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MONITOR3_X, MONITOR3_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MONITOR3_WIDTH, MONITOR3_HEIGHT, 0.0f);
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
	g_pVtxBuffMonitor3->Unlock();

}
//=============================================================================
// �I������
//=============================================================================
void UninitMonitor3(void)
{	//�e�N�X�`���̔j��
	if (g_pTextureMonitor3 != NULL)
	{
		g_pTextureMonitor3->Release();
		g_pTextureMonitor3 = NULL;
	}
	//���_�o�b�t�@�̔j���̔j��
	if (g_pVtxBuffMonitor3 != NULL)
	{
		g_pVtxBuffMonitor3->Release();
		g_pVtxBuffMonitor3 = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMonitor3(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMonitor3(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMonitor3, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMonitor3);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}