//=============================================================================
//
// �Q�[���^�O���� [Tagu.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "tagu.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/tagu.png" //�ǂݍ��ރe�N�X�`��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTagu = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTagu = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Tagu;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitTagu(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

		g_Tagu = D3DXVECTOR2(0, 0);
	
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureTagu);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTagu,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^

	g_pVtxBuffTagu->Lock(0, 0, (void**)&pVtx,0);


		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Tagu.x - 0, g_Tagu.y -0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Tagu.x + 1280.0f, g_Tagu.y -0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Tagu.x - 0, g_Tagu.y + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Tagu.x + 1280.0f, g_Tagu.y + 70.0f, 0.0f);
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
	g_pVtxBuffTagu->Unlock();
	
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitTagu(void)
{
		//�e�N�X�`���̔j��
		if (g_pTextureTagu != NULL)
		{
			g_pTextureTagu->Release();
			g_pTextureTagu = NULL;
		}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTagu != NULL)
	{
		g_pVtxBuffTagu->Release();
		g_pVtxBuffTagu = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateTagu(void)
{
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawTagu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTagu,0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);	

	
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTagu);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}
