//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�V���V�h�[������ [meshDome.cpp]
// Author : ���a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "meshDome.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_MESHDOME	(2)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX	mtxWorld;				// ���[���h�}�g���b�N�X
	float fRadius;						// ���a
	int nHBlock;						// X�����̃u���b�N��
	int nVBlock;						// Y�����̃u���b�N��
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
	int nTexType;						// �e�N�X�`���[���
	bool bInside;						// �������ǂ���
	bool bUp;							// ��������ǂ���
	bool bUse;							// �g�p���Ă��邩�ǂ���
}MeshDome;

typedef enum
{
	POLYGON_TEX_000 = 0,	// �|���S���e�N�X�`��000
	POLYGON_TEX_MAX,		// ����
}MeshDomeTexName;

typedef struct
{
	char *pFilename;	// �t�@�C����
} MeshDomeTexInfo;
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMeshDome(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexMeshDome(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9			g_apTextureMeshDome[POLYGON_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^

MeshDome g_aMeshDome[MAX_MESHDOME];				// ���b�V���h�[���̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
MeshDomeTexInfo g_apTextureMeshDomeInfo[POLYGON_TEX_MAX] =
{
	{ "data//TEXTURE//sky000.jpg" },		// �e�N�X�`��0
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMeshDome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	for (int nCntMeshDomeTex = 0; nCntMeshDomeTex < POLYGON_TEX_MAX; nCntMeshDomeTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMeshDomeInfo[nCntMeshDomeTex].pFilename,
			&g_apTextureMeshDome[nCntMeshDomeTex]);
	}

	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		g_aMeshDome[nCntMeshDome].pVtxBuff = NULL;
		g_aMeshDome[nCntMeshDome].pIdxBuff = NULL;
		g_aMeshDome[nCntMeshDome].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntMeshDome].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshDome[nCntMeshDome].nHBlock = 0;
		g_aMeshDome[nCntMeshDome].nVBlock = 0;
		g_aMeshDome[nCntMeshDome].fRadius = 0.0f;
		g_aMeshDome[nCntMeshDome].nNumVertex = 0;
		g_aMeshDome[nCntMeshDome].nNumIndex = 0;
		g_aMeshDome[nCntMeshDome].nNumPolygon = 0;
		g_aMeshDome[nCntMeshDome].nTexType = 0;
		g_aMeshDome[nCntMeshDome].bInside = false;
		g_aMeshDome[nCntMeshDome].bUp = false;
	}
	// �z�u���b�V���̏��
	g_aMeshDome[0].pos = D3DXVECTOR3(0.0f, -200.0f, 0.0f);
	g_aMeshDome[0].nHBlock = 64;
	g_aMeshDome[0].nVBlock = 16;
	g_aMeshDome[0].fRadius = 3600.0f;
	g_aMeshDome[0].bInside = false;
	g_aMeshDome[0].bUp = true;

	g_aMeshDome[1].pos = D3DXVECTOR3(0.0f, -200.0f, 0.0f);
	g_aMeshDome[1].nHBlock = 64;
	g_aMeshDome[1].nVBlock = 16;
	g_aMeshDome[1].fRadius = 3600.0f;
	g_aMeshDome[1].bInside = false;
	g_aMeshDome[1].bUp = false;

	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		// �C���f�b�N�X���v�Z
		g_aMeshDome[nCntMeshDome].nNumIndex = 2 + g_aMeshDome[nCntMeshDome].nHBlock * 2;
		g_aMeshDome[nCntMeshDome].nNumIndex += (g_aMeshDome[nCntMeshDome].nNumIndex + 2) * (g_aMeshDome[nCntMeshDome].nVBlock - 1);

		// �|���S�����v�Z
		g_aMeshDome[nCntMeshDome].nNumPolygon = (g_aMeshDome[nCntMeshDome].nHBlock * g_aMeshDome[nCntMeshDome].nVBlock) * 2 + 4 * (g_aMeshDome[nCntMeshDome].nVBlock - 1);

		// ���_���v�Z
		g_aMeshDome[nCntMeshDome].nNumVertex = (g_aMeshDome[nCntMeshDome].nHBlock + 1)*(g_aMeshDome[nCntMeshDome].nVBlock + 1);
	}

	// ���_���̍쐬
	MakeVertexMeshDome(pDevice);

	// �C���f�b�N�X���̍쐬
	MakeIndexMeshDome(pDevice);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMeshDome(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < POLYGON_TEX_MAX; nCntTex++)
	{
		if (g_apTextureMeshDome[nCntTex] != NULL)
		{
			g_apTextureMeshDome[nCntTex]->Release();
			g_apTextureMeshDome[nCntTex] = NULL;
		}
	}

	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_aMeshDome[nCntMeshDome].pVtxBuff != NULL)
		{
			g_aMeshDome[nCntMeshDome].pVtxBuff->Release();
			g_aMeshDome[nCntMeshDome].pVtxBuff = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_aMeshDome[nCntMeshDome].pIdxBuff != NULL)
		{
			g_aMeshDome[nCntMeshDome].pIdxBuff->Release();
			g_aMeshDome[nCntMeshDome].pIdxBuff = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMeshDome(void)
{
	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		g_aMeshDome[nCntMeshDome].rot.y += 0.001f;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMeshDome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot,mtxTrans;					// �v�Z�p�}�g���b�N�X����

	// ���C�g�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aMeshDome[nCntMeshDome].mtxWorld);

		// ��]�𔽉f	Y,X,Z�̏��Ԃ����
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshDome[nCntMeshDome].rot.y, g_aMeshDome[nCntMeshDome].rot.x, g_aMeshDome[nCntMeshDome].rot.z);
		D3DXMatrixMultiply(&g_aMeshDome[nCntMeshDome].mtxWorld, &g_aMeshDome[nCntMeshDome].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aMeshDome[nCntMeshDome].pos.x, g_aMeshDome[nCntMeshDome].pos.y, g_aMeshDome[nCntMeshDome].pos.z);
		D3DXMatrixMultiply(&g_aMeshDome[nCntMeshDome].mtxWorld, &g_aMeshDome[nCntMeshDome].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshDome[nCntMeshDome].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_aMeshDome[nCntMeshDome].pVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_aMeshDome[nCntMeshDome].pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureMeshDome[0]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshDome[nCntMeshDome].nNumVertex, 0, g_aMeshDome[nCntMeshDome].nNumPolygon);
	}
	// ���C�g�I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMeshDome(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		// ���_�o�b�t�@�𐶐�
		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshDome[nCntMeshDome].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aMeshDome[nCntMeshDome].pVtxBuff,
			NULL);

		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_aMeshDome[nCntMeshDome].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		// ���_���̐ݒ�	���W�̒��ڎw��͂����ł͊�{�I�ɂ͂��Ȃ�(g_pos~~���𑫂������͂��Ȃ�D3DXMatrixTranslation�ł���Ă�
		for (int nCntPos = 0; nCntPos < g_aMeshDome[nCntMeshDome].nNumVertex; nCntPos++)
		{
			int nInside = 1;
			if (g_aMeshDome[nCntMeshDome].bInside == true)
			{
				nInside *= -1;
			}
			if (g_aMeshDome[nCntMeshDome].bUp == true)
			{ // ��������ǂ���
				pVtx[nCntPos].pos =
					D3DXVECTOR3(float(sin(D3DX_PI * nInside - ((D3DX_PI * 2.0f * nInside) / g_aMeshDome[nCntMeshDome].nHBlock) * (nCntPos % (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * (cos(-D3DX_PI + ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius)),
						float(sin(D3DX_PI - ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius),
						float(cos(float(D3DX_PI * nInside - ((D3DX_PI * 2.0f * nInside) / g_aMeshDome[nCntMeshDome].nHBlock) * float(nCntPos % (g_aMeshDome[nCntMeshDome].nHBlock + 1)))) * (cos(-D3DX_PI + ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius)));
			}
			else
			{
				pVtx[nCntPos].pos =
					D3DXVECTOR3(float(sin(D3DX_PI * nInside - ((D3DX_PI * 2.0f * nInside) / g_aMeshDome[nCntMeshDome].nHBlock) * (nCntPos % (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * (cos(-D3DX_PI + ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius)) * -1,
						float(sin(D3DX_PI - ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius),
						float(cos(float(D3DX_PI * nInside - ((D3DX_PI * 2.0f * nInside) / g_aMeshDome[nCntMeshDome].nHBlock) * float(nCntPos % (g_aMeshDome[nCntMeshDome].nHBlock + 1)))) * (cos(-D3DX_PI + ((D3DX_PI / 2.0f) / g_aMeshDome[nCntMeshDome].nVBlock) * (nCntPos / (g_aMeshDome[nCntMeshDome].nHBlock + 1))) * g_aMeshDome[nCntMeshDome].fRadius))) * -1;
			}
		}

		// �@���̐ݒ�@�@���́u1�v�ɂ��Ȃ��Ă͂Ȃ�Ȃ��H�u1.0�v�ȉ��ɂ��Ȃ���΂Ȃ�Ȃ��H
		for (int nCntNor = 0; nCntNor < g_aMeshDome[nCntMeshDome].nNumVertex; nCntNor++)
		{
			D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].pos);		// ���K������
		}

		// ���_�J���[�̐ݒ�
		for (int nCntCol = 0; nCntCol < g_aMeshDome[nCntMeshDome].nNumVertex; nCntCol++)
		{
			pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �e�N�X�`���̐ݒ�
		for (int nCntTex = 0; nCntTex < g_aMeshDome[nCntMeshDome].nNumVertex; nCntTex++)
		{
			pVtx[nCntTex].tex = D3DXVECTOR2(1.0f / 2.0f / g_aMeshDome[nCntMeshDome].nHBlock * (nCntTex % (g_aMeshDome[nCntMeshDome].nHBlock + 1))*2, // �Ō��*2�͂��̏ꂵ�̂�
				1.0f / 2.0f / g_aMeshDome[nCntMeshDome].nVBlock * (nCntTex / (g_aMeshDome[nCntMeshDome].nHBlock + 1)));
		}


		// ���_�o�b�t�@���A�����b�N����
		g_aMeshDome[nCntMeshDome].pVtxBuff->Unlock();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �C���f�b�N�X���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeIndexMeshDome(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshDome = 0; nCntMeshDome < MAX_MESHDOME; nCntMeshDome++)
	{
		// �C���f�b�N�X�o�b�t�@�𐶐�
		// �C���f�b�N�X���̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshDome[nCntMeshDome].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,			// ��̐�����2�o�C�g�����g��Ȃ�
			D3DPOOL_MANAGED,
			&g_aMeshDome[nCntMeshDome].pIdxBuff,
			NULL);

		WORD *pIdx;				// �C���f�b�N�X�f�[�^�ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		g_aMeshDome[nCntMeshDome].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �C���f�b�N�X�̐ݒ�
		for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshDome[nCntMeshDome].nNumIndex; nCntIdx += 2)
		{
			if ((nCntIdx / 2) % (g_aMeshDome[nCntMeshDome].nHBlock + 2) == g_aMeshDome[nCntMeshDome].nHBlock + 1)
			{
				pIdx[nCntIdx] = nCntPos - 1;
				pIdx[nCntIdx + 1] = nCntPos + g_aMeshDome[nCntMeshDome].nHBlock + 1;
			}
			else
			{
				pIdx[nCntIdx] = nCntPos + g_aMeshDome[nCntMeshDome].nHBlock + 1;
				pIdx[nCntIdx + 1] = nCntPos;

				nCntPos++;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_aMeshDome[nCntMeshDome].pIdxBuff->Unlock();
	}
}
