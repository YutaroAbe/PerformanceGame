//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �e���� [shadow.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "shadow.h"
#include "meshBattleField.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_SHADOW		(128)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	SHADOW_TEX_000 = 0,	// �e�e�N�X�`��000
	SHADOW_TEX_MAX,		// ����
}ShadowTexName;

typedef struct
{
	char *pFilename;	// �t�@�C����
} ShadowTexInfo;
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffShadow = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_apTextureShadow[SHADOW_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
Shadow	g_aShadow[MAX_SHADOW];								// �e�̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
ShadowTexInfo g_apTextureShadowInfo[SHADOW_TEX_MAX] =
{
	{ "data//TEXTURE//shadow000.jpg" },		// �e�N�X�`��0
};
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	for (int nCntShadowTex = 0; nCntShadowTex < SHADOW_TEX_MAX; nCntShadowTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureShadowInfo[nCntShadowTex].pFilename,
			&g_apTextureShadow[nCntShadowTex]);
	}

	// ���_���̍쐬
	MakeVertexShadow(pDevice);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitShadow(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < SHADOW_TEX_MAX; nCntTex++)
	{
		if (g_apTextureShadow[nCntTex] != NULL)
		{
			g_apTextureShadow[nCntTex]->Release();
			g_apTextureShadow[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateShadow(void)
{

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot,mtxTrans;					// �v�Z�p�}�g���b�N�X����

	// �A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g���J�n����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ��l(REF)�����߂�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ����(FUNC)�����߂�,D3DCMP_GREATER,��r(CMP),GREATER(�Z�Z���傫��)

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// ��]�𔽉f	Y,X,Z�̏��Ԃ����
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureShadow[0]);

			// �e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g���I������
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		// ���_���̐ݒ�	���W�̒��ڎw��͂����ł͊�{�I�ɂ͂��Ȃ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���̐ݒ�@�@���́u1�v�ɂ��Ȃ��Ă͂Ȃ�Ȃ��H�u1.0�v�ȉ��ɂ��Ȃ���΂Ȃ�Ȃ��H
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �e�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth)
{
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{ // �e���g�p����Ă��Ȃ��ꍇ
			// �ʒu�̐ݒ�
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].pos.y = 2.0f;
			// �����̐ݒ�
			g_aShadow[nCntShadow].rot = rot;

			// �傫���̐ݒ�
			g_aShadow[nCntShadow].fWidth = fWidth;
			g_aShadow[nCntShadow].fDepth = fDepth;

			g_aShadow[nCntShadow].bUse = true; // �g�p���Ă����Ԃɂ���

			pVtx[0].pos = D3DXVECTOR3(- g_aShadow[nCntShadow].fWidth / 2, 0.0f, g_aShadow[nCntShadow].fDepth / 2);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2, 0.0f, g_aShadow[nCntShadow].fDepth / 2);
			pVtx[2].pos = D3DXVECTOR3( -g_aShadow[nCntShadow].fWidth / 2, 0.0f, - g_aShadow[nCntShadow].fDepth / 2);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2, 0.0f, - g_aShadow[nCntShadow].fDepth / 2);

			break;	// ����break�͂��Ȃ���
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �e�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPositionShadow(int nIdyShadow, D3DXVECTOR3 pos)
{
	if (g_aShadow[nIdyShadow].bUse == true)
	{
		g_aShadow[nIdyShadow].pos = pos;
		g_aShadow[nIdyShadow].pos.y = -1000000.0f;

		MeshBattleField *pMeshBattleField = GetMeshBattleField();
		for (int nCntField = 0; nCntField < MAX_MESHBATTLEFIELD; nCntField++)
		{

			if (pos.y >= pMeshBattleField[nCntField].pos.y && g_aShadow[nIdyShadow].pos.y < pMeshBattleField[nCntField].pos.y
				&& pos.x > pMeshBattleField[nCntField].pos.x - (pMeshBattleField[nCntField].fWidth * pMeshBattleField[nCntField].nXBlock)/2.0f && pos.x < pMeshBattleField[nCntField].pos.x + (pMeshBattleField[nCntField].fWidth * pMeshBattleField[nCntField].nXBlock) / 2.0f
				&& pos.z > pMeshBattleField[nCntField].pos.z - (pMeshBattleField[nCntField].fDepth * pMeshBattleField[nCntField].nZBlock) / 2.0f && pos.z < pMeshBattleField[nCntField].pos.z + (pMeshBattleField[nCntField].fDepth * pMeshBattleField[nCntField].nZBlock) / 2.0f)
			{ // �e�̎�������Ⴂ�ʒu�ɂ���A���̔�r�������̂�荂���ʒu�ɂ���ꍇ
				g_aShadow[nIdyShadow].pos.y = pMeshBattleField[nCntField].pos.y;
			}

		}

		g_aShadow[nIdyShadow].pos.y += 1.0f;

		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nIdyShadow;

		// �e�̍������25.0f
		float fRadius = 0.0f;

		fRadius += (pos.y - g_aShadow[nIdyShadow].pos.y) / 100.0f;

		if (fRadius >= 1.0f)
		{
			fRadius = 0.0f;
		}

		if (pos.y - g_aShadow[nIdyShadow].pos.y > 100.0f)
		{
			fRadius = 0.0f;
		}
		float fAlpha = 1.0f;

		fAlpha -= (pos.y - g_aShadow[nIdyShadow].pos.y) / 100.0f;

		if (fAlpha <= 0)
		{
			fAlpha = 0.0f;
		}

		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f,(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, (g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, -(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, -(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �e�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Shadow *GetShadow(void)
{
	return &g_aShadow[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �e�̏���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DeletShadow(int nIdyShadow)
{
	g_aShadow[nIdyShadow].bUse = false;
}