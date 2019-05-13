//=============================================================================
//
// �w�i(�o�b�N�O���E���h)���� [bg.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "bg2.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/��BG.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE2 "data/TEXTURE/��BG.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE3 "data/TEXTURE/��BG.png" //�ǂݍ��ރe�N�X�`��
#define BG_POS_X  (0)�@�@�@//�w�i�̍���X���W
#define BG_POS_Y  (0)�@�@�@//�w�i�̍���Y���W
#define BG_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define BG_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define MAX_TEX (2)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureBG2[2] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_BG2[3];

//=============================================================================
//�����������w�i
//=============================================================================
void InitBG2(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

	for (int nCount = 0; nCount < 2; nCount++)
	{
		g_BG2[0] = D3DXVECTOR2(0.0f, 0.0f);
		g_BG2[1] = D3DXVECTOR2(0.0f, 0.0f);
		g_BG2[2] = D3DXVECTOR2(0.0f, 0.0f);
	}
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, & g_pTextureBG2[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, & g_pTextureBG2[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, & g_pTextureBG2[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG2,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^

	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx,0);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_���W�ݒ�
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //�E��
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);				 //����
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);		 //����
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				    //�E��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBG2->Unlock();
	
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitBG2(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���̔j��
		if ( g_pTextureBG2[nCount] != NULL)
		{
			 g_pTextureBG2[nCount]->Release();
			 g_pTextureBG2[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG2 != NULL)
	{
		g_pVtxBuffBG2->Release();
		g_pVtxBuffBG2 = NULL;
	}
}
//=============================================================================
//�X�V�����w�i
//=============================================================================
void UpdateBG2(void)
{
	VERTEX_2D*pVtx;

	g_BG2[0].y += 0.003f;
	g_BG2[1].y += 0.002f;
//_BG2[2].y += 0.001f;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx, 0);
	
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[0].y);						//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[0].y);					//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[0].y - 1.0f);						//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[0].y -1.0f);					//����
		
	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[1].y);						//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[1].y);					//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[1].y - 1.0f);						//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[1].y - 1.0f);					//����

	//pVtx += 4;

	//pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[2].y);						//�E��
	//pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[2].y );					//�E��
	//pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[2].y - 1.0f);						//����
	//pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[2].y - 1.0f);					//����
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG2->Unlock();
}
//=============================================================================
//�`�揈���w�i
//=============================================================================
void DrawBG2(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG2,0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);	

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0,  g_pTextureBG2[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 3);
	}
}
