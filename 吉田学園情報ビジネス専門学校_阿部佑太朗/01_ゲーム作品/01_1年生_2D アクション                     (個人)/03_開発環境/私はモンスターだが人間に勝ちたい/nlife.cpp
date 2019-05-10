//=============================================================================
//
// ���C�t�O�t������ [nlife.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "nlife.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/nHP001.png" //�ǂݍ��ރe�N�X�`��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureNlife = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNlife = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Nlife;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitNlife(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

		g_Nlife = D3DXVECTOR2(190, 45);
	
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureNlife);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNlife,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffNlife->Lock(0, 0, (void**)&pVtx,0);

		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Nlife.x - 135.0f, g_Nlife.y -40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Nlife.x + 135.0f, g_Nlife.y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Nlife.x - 135.0f, g_Nlife.y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Nlife.x + 135.0f, g_Nlife.y + 40.0f, 0.0f);
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

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffNlife->Unlock();
	
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitNlife(void)
{
		//�e�N�X�`���̔j��
	if (g_pTextureNlife != NULL)
	{
		g_pTextureNlife->Release();
		g_pTextureNlife = NULL;
	}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffNlife != NULL)
	{
		g_pVtxBuffNlife->Release();
		g_pVtxBuffNlife = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateNlife(void)
{
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawNlife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffNlife, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�F�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureNlife);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
