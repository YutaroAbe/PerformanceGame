//=============================================================================
//
// �~�����v���[���g�\���̏��� [demandpresent.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "demandpresent.h"
#include "human.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEAMND_TEXTURE_NAME0       "data/TEXTURE/DemandPresent001.png"    // �ǂݍ��ރe�N�X�`���t�@�C����
#define DEAMND_TEXTURE_NAME1       "data/TEXTURE/DemandPresent000.png"    // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexDemandPresent(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDemandPresent[2] = {};	  // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDemandPresent = NULL;	      // ���_�o�b�t�@�ւ̃|�C���^
DemandPresent           g_aDemandPresent[MAX_DEMANDPRESENT];  // �\���̏��

//=============================================================================
// ����������
//=============================================================================
void InitDemandPresent(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// �\���ł���~�����v���[���g�̐������J��Ԃ�
		g_aDemandPresent[nCntDemand].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �ʒu��������
		g_aDemandPresent[nCntDemand].bDisp = false;                        // �\�����Ȃ���Ԃɂ���
	}

	// ���_���̐ݒ�
	MakeVertexDemandPresent(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitDemandPresent(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureDemandPresent[nCntTex] != NULL)
		{
			g_pTextureDemandPresent[nCntTex]->Release();
			g_pTextureDemandPresent[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDemandPresent != NULL)
	{
		g_pVtxBuffDemandPresent->Release();
		g_pVtxBuffDemandPresent = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateDemandPresent(void)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	Human *pHuman;
	pHuman = GetHuman();

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++,pHuman++)
	{// �\���ł���~�����v���[���g�̐������J��Ԃ�
		if (g_aDemandPresent[nCntDemand].bDisp == true)
		{// �\�������Ԃ�������
			
			// �ʒu�X�V
			g_aDemandPresent[nCntDemand].pos = D3DXVECTOR3(pHuman->pos.x + pHuman->fWidth + 10.0f, pHuman->pos.y - pHuman->fHeight - 30.0f, 0.0f);

			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);

			// ��ʒ[�ɍs���������
			if (pHuman == false)
			{// �E�[�ɓ��B����
				g_aDemandPresent[nCntDemand].bDisp = false;
			}
			if (pHuman->bUse == false)
			{// ���[�ɓ��B����
				g_aDemandPresent[nCntDemand].bDisp = false;
			}
		}

		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawDemandPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffDemandPresent, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// �\���ł���~�����v���[���g�̐������J��Ԃ�
		if (g_aDemandPresent[nCntDemand].bDisp == true)
		{// �\�������Ԃ�������
		 // �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureDemandPresent[g_aDemandPresent[nCntDemand].nIdxHuman]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDemand * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexDemandPresent(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		DEAMND_TEXTURE_NAME0,
		&g_pTextureDemandPresent[0]);
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		DEAMND_TEXTURE_NAME1,
		&g_pTextureDemandPresent[1]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DEMANDPRESENT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDemandPresent,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// �\���ł���~�����v���[���g�̐������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);

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

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetDemandPresent(D3DXVECTOR3 pos, int nIdxHuman,int nNumTex)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nIdxHuman;  // �|�C���^��l�Ԃ̔ԍ����i�߂�

	if (g_aDemandPresent[nIdxHuman].bDisp == false)
	{// �\�����Ȃ���Ԃ�������
		g_aDemandPresent[nIdxHuman].pos = pos;     // �ʒu��ݒ�
		g_aDemandPresent[nIdxHuman].bDisp = true;  // �g�p���Ă����Ԃɂ���
		g_aDemandPresent[nIdxHuman].nIdxHuman = nNumTex;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x - 35, g_aDemandPresent[nIdxHuman].pos.y - 35, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x + 35, g_aDemandPresent[nIdxHuman].pos.y - 35, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x - 35, g_aDemandPresent[nIdxHuman].pos.y + 35, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x + 35, g_aDemandPresent[nIdxHuman].pos.y + 35, 0.0f);

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void DeleteDemandPresent(int nIdxHuman)
{
	g_aDemandPresent[nIdxHuman].bDisp = false;  // �g�p���Ă��Ȃ���Ԃɂ���
}