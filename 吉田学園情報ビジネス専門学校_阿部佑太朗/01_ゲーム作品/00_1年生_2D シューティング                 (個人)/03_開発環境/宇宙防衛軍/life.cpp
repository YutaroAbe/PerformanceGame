//=========================================================================================================================
//
// ���C�t�̏��� [life.cpp]
// Author :
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "life.h"//�^�C��
#include "input.h"//�L�[�{�[�h
#include "player.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_LIFE_NUMBER (10)
#define TEXTURE_LIFE "data/TEXTURE/HP102.png"// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_PLIFE (30)							//���C�t�̑傫��

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posLife;

//=========================================================================================================================
// �X�R�A����������
//=========================================================================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //�f�o�C�X�|�C���^
	float  nCntLife;			//�X�R�A�J�E���g
	float nLifePos;				//�X�R�A�ʒu


	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (nCntLife = 0; nCntLife < MAX_LIFE_NUMBER; nCntLife++)
	{
		//�ʒu
		g_posLife = D3DXVECTOR3(90, 52, 0.0f);
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_LIFE, &g_pTextureLife);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0, nLifePos = 10;  nCntLife < MAX_LIFE_NUMBER; nCntLife++, g_posLife.x += 20)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posLife.x - 11.8f, g_posLife.y - 13.8f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife.x + 11.8f, g_posLife.y - 13.8f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife.x - 11.8f, g_posLife.y + 13.8f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife.x + 11.8f, g_posLife.y + 13.8f, 0.0f);
		//RHW
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 65, 200);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 65, 200);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 65, 200);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 65, 200);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffLife->Unlock();

}

//=========================================================================================================================
// �X�R�A�I������
//=========================================================================================================================
void UninitLife(void)
{
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUMBER; nCntLife++)
	{
		//�e�N�X�`���[�̔j��
		if (g_pTextureLife != NULL)
		{
			g_pTextureLife->Release();
			g_pTextureLife = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=========================================================================================================================
// �X�R�A�X�V����
//=========================================================================================================================
void UpdateLife(void)
{
}

//=========================================================================================================================
// �X�R�A�`�揈��
//=========================================================================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	int nCntLife;//�X�R�A�J�E���g

				  //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(0,g_pVtxBuffLife,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureLife);
		Player*pPlayer;
		pPlayer = GetPlayer();

		if (pPlayer->nLife == 10)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 10; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 9)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 9; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 8)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 8; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 7)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 7; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 6)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 6; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 5)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 5; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 4)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 4; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 3)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 3; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 2)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 2; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 1)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 1; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 0)
		{
			//�X�R�A�̕`��
			for (nCntLife = 0; nCntLife < 0
				; nCntLife++)
			{//�X�R�A�J�E���g
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
}

