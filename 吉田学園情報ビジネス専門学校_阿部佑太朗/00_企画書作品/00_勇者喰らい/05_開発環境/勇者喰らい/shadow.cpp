//=============================================================================
//
// �|���S������ [Shadow.cpp]
// Author : ���{��
//
//=============================================================================
#include "game.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		MAX_SHADOW		(128)
#define		MAX_TEXSHADOW	(3)
#define		TEXTURE_EFFECT	"data/TEXTURE/shadow000.jpg"
#define		TEXTURE_EFFECT1	"data/TEXTURE/shadow001.jpg"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureShadow[MAX_TEXSHADOW] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Shadow g_Shadow[MAX_SHADOW];

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTextureShadow[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT1, &g_pTextureShadow[1]);

	// ���_���̍쐬
	MakeVertexShadow(pDevice);


}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	BreakShadow(-1);

	for (int nCntTex = 0; nCntTex < MAX_TEXSHADOW; nCntTex++)
	{// �e�N�X�`���̊J��
		if (g_pTextureShadow[nCntTex] != NULL)
		{
			g_pTextureShadow[nCntTex]->Release();
			g_pTextureShadow[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��;
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//�S�e�����
		if (g_Shadow[nCntShadow].bUse == true)
		{
			CollisionObjectS(&g_Shadow[nCntShadow].pos);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	int nCntShadow;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			pVtx[nCntShadow * 4].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].fLengthX, 0.1f, g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].fLengthX, 0.1f, g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].fLengthX, 0.1f, -g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].fLengthX, 0.1f, -g_Shadow[nCntShadow].fLengthZ);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorldShadow);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow, &g_Shadow[nCntShadow].mtxWorldShadow, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow, &g_Shadow[nCntShadow].mtxWorldShadow, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorldShadow);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow[g_Shadow[nCntShadow].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();

	pDevice->SetTexture(0, NULL);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntShadow;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//�@���̐ݒ�
		pVtx[nCntShadow * 4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[nCntShadow * 4].tex = D3DXVECTOR2(0.05f, 0.05f);
		pVtx[nCntShadow * 4 + 1].tex = D3DXVECTOR2(0.95f, 0.05f);
		pVtx[nCntShadow * 4 + 2].tex = D3DXVECTOR2(0.05f, 0.95f);
		pVtx[nCntShadow * 4 + 3].tex = D3DXVECTOR2(0.95f, 0.95f);

		//���_�J���[�̐ݒ�
		pVtx[nCntShadow * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

																		   //g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
																		   //g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;

	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}
//=============================================================================
// �e�̍쐬
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLengthX, float fLengthZ, float fHeight, int nShadow)
{
	int nCntShadow;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{//�e�̏���ݒ肵�Ă��̔ԍ���Ԃ�

			g_Shadow[nCntShadow].bUse = true;
			g_Shadow[nCntShadow].fLengthZ = fLengthZ;
			g_Shadow[nCntShadow].nType = nShadow;
			g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			if (nShadow == 0)
			{
				g_Shadow[nCntShadow].pos = pos;
				g_Shadow[nCntShadow].rot.y = rot.y;
				g_Shadow[nCntShadow].fLengthX = fLengthX;
			}
			else
			{
				g_Shadow[nCntShadow].pos = pos + D3DXVECTOR3(fHeight * -0.3f, 0.0f, 0.0f);
				g_Shadow[nCntShadow].fLengthX = fLengthX + fHeight * 0.3f;
			}

			if (nShadow == 2) { g_Shadow[nCntShadow].fLengthX = 0; g_Shadow[nCntShadow].fLengthZ = 0; }
			SettingShadow(g_Shadow[nCntShadow].pos, g_Shadow[nCntShadow].rot, g_Shadow[nCntShadow].fLengthX, g_Shadow[nCntShadow].fLengthZ, nCntShadow);

			pVtx[nCntShadow * 4].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].fLengthX, 0.1f, g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].fLengthX, 0.1f, g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].fLengthX, 0.1f, -g_Shadow[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].fLengthX, 0.1f, -g_Shadow[nCntShadow].fLengthZ);
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;
}
//=============================================================================
// �e�̔��f
//=============================================================================
void SettingShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLengthX, float fLengthZ, int nNumber)
{
	g_Shadow[nNumber].pos = pos;
	g_Shadow[nNumber].rot.y = rot.y;
	g_Shadow[nNumber].fLengthX = fLengthX;
	g_Shadow[nNumber].fLengthZ = fLengthZ;
}
//=============================================================================
// �e�̍폜
//=============================================================================
void BreakShadow(int nNumber)
{
	if (nNumber > -1) { g_Shadow[nNumber].bUse = false; }
	else if(nNumber == -1)
	{
		for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
		{
			g_Shadow[nCount].bUse = false;
		}
	}
	else
	{//�v���C���[�̂ݍ폜���Ȃ�
		MODEL_INFO *pModel = GetModel_Info();
		for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
		{
			if (pModel[0].nCntShadow != nCount)
			{
				g_Shadow[nCount].bUse = false;
			}
		}
	}

}