//=============================================================================
//
// �w�i(�o�b�N�O���E���h)���� [FRONTBG.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"


//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define FRONTBG_TEXTURENAMRE "data/TEXTURE/bg002.png" //�ǂݍ��ރe�N�X�`��
#define FRONTBG_POS_X  (0)�@�@�@//�w�i�̍���X���W
#define FRONTBG_POS_Y  (0)�@�@�@//�w�i�̍���Y���W
#define FRONTBG_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define FRONTBG_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define MAX_TEX (1)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureFRONTBG = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFRONTBG = NULL;  //���_�o�b�t�@�̃|�C���g

//=============================================================================
//�����������w�i
//=============================================================================
void InitFRONTBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
													//�f�o�C�X�擾
	pDevice = GetDevice();


	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FRONTBG_TEXTURENAMRE, &g_pTextureFRONTBG);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFRONTBG,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^

	g_pVtxBuffFRONTBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//���_���W�ݒ�
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //�E��
		pVtx[1].pos = D3DXVECTOR3(FRONTBG_WIDTH, 0, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(0, FRONTBG_HEIGHT, 0.0f);				 //����
		pVtx[3].pos = D3DXVECTOR3(FRONTBG_WIDTH, FRONTBG_HEIGHT, 0.0f);		 //����
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //�E��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffFRONTBG->Unlock();

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitFRONTBG(void)
{
		//�e�N�X�`���̔j��
		if (g_pTextureFRONTBG != NULL)
		{
			g_pTextureFRONTBG->Release();
			g_pTextureFRONTBG = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFRONTBG != NULL)
	{
		g_pVtxBuffFRONTBG->Release();
		g_pVtxBuffFRONTBG = NULL;
	}
}
//=============================================================================
//�X�V�����w�i
//=============================================================================
void UpdateFRONTBG(void)
{
}
//=============================================================================
//�`�揈���w�i
//=============================================================================
void DrawFRONTBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
									//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFRONTBG, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFRONTBG);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 3);
	}
}
