//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�V���o�g���t�B�[���h���� [meshBattleField.cpp]
// Author : ���a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "meshBattleField.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	POLYGON_TEX_000 = 0,	// �|���S���e�N�X�`��000
	POLYGON_TEX_MAX,		// ����
}MeshBattleFieldTexName;

typedef struct
{
	char *pFilename;	// �t�@�C����
} MeshBattleFieldTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	float fWidth;			// ��
	float fDepth;			// ��
	int nXBlock;			// X�����̃u���b�N��
	int nZBlock;			// Y�����̃u���b�N��
}MeshBattleFieldInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMeshBattleField(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexMeshBattleField(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9			g_apTextureMeshBattleField[POLYGON_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^

MeshBattleField g_aMeshBattleField[MAX_MESHBATTLEFIELD];				// ���b�V���t�B�[���h�̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
MeshBattleFieldTexInfo g_apTextureMeshBattleFieldInfo[POLYGON_TEX_MAX] =
{
	{ "data//TEXTURE//Floor001.jpg" },		// �e�N�X�`��0
};

MeshBattleFieldInfo g_aMeshBattleFieldInfo[] =
{	//	�ʒu,								����,									��,			��,			X��		Z��
	{ D3DXVECTOR3(0.0f, 0.0f, 600.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		12,		20 },
	/*{ D3DXVECTOR3(0.0f, 0.0f, 400.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		2,		4 },
	{ D3DXVECTOR3(0.0f, 0.0f, 600.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		4,		4 },*/
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMeshBattleField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	for (int nCntMeshBattleFieldTex = 0; nCntMeshBattleFieldTex < POLYGON_TEX_MAX; nCntMeshBattleFieldTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMeshBattleFieldInfo[nCntMeshBattleFieldTex].pFilename,
			&g_apTextureMeshBattleField[nCntMeshBattleFieldTex]);
	}

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshBattleField[nCntMeshBattleField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshBattleField[nCntMeshBattleField].nXBlock = 0;
		g_aMeshBattleField[nCntMeshBattleField].nZBlock = 0;
		g_aMeshBattleField[nCntMeshBattleField].fWidth = 0.0f;
		g_aMeshBattleField[nCntMeshBattleField].fDepth = 0.0f;
		g_aMeshBattleField[nCntMeshBattleField].nNumVertex = 0;
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex = 0;
		g_aMeshBattleField[nCntMeshBattleField].nNumPolygon = 0;
		g_aMeshBattleField[nCntMeshBattleField].nTexType = 0;
	}

	// INFO
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < sizeof g_aMeshBattleFieldInfo / sizeof(MeshBattleFieldInfo); nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].pos = g_aMeshBattleFieldInfo[nCntMeshBattleField].pos;
		g_aMeshBattleField[nCntMeshBattleField].rot = g_aMeshBattleFieldInfo[nCntMeshBattleField].rot;
		g_aMeshBattleField[nCntMeshBattleField].fDepth = g_aMeshBattleFieldInfo[nCntMeshBattleField].fDepth;
		g_aMeshBattleField[nCntMeshBattleField].fWidth = g_aMeshBattleFieldInfo[nCntMeshBattleField].fWidth;
		g_aMeshBattleField[nCntMeshBattleField].nXBlock = g_aMeshBattleFieldInfo[nCntMeshBattleField].nXBlock;
		g_aMeshBattleField[nCntMeshBattleField].nZBlock = g_aMeshBattleFieldInfo[nCntMeshBattleField].nZBlock;
	}

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// �C���f�b�N�X���v�Z
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex = 2 + g_aMeshBattleField[nCntMeshBattleField].nXBlock * 2;
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex += (g_aMeshBattleField[nCntMeshBattleField].nNumIndex + 2) * (g_aMeshBattleField[nCntMeshBattleField].nZBlock - 1);

		// �|���S�����v�Z
		g_aMeshBattleField[nCntMeshBattleField].nNumPolygon = (g_aMeshBattleField[nCntMeshBattleField].nXBlock * g_aMeshBattleField[nCntMeshBattleField].nZBlock) * 2 + 4 * (g_aMeshBattleField[nCntMeshBattleField].nZBlock - 1);

		// ���_���v�Z
		g_aMeshBattleField[nCntMeshBattleField].nNumVertex = (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)*(g_aMeshBattleField[nCntMeshBattleField].nZBlock + 1);
	}

	// ���_���̍쐬
	MakeVertexMeshBattleField(pDevice);

	// �C���f�b�N�X���̍쐬
	MakeIndexMeshBattleField(pDevice);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMeshBattleField(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < POLYGON_TEX_MAX; nCntTex++)
	{
		if (g_apTextureMeshBattleField[nCntTex] != NULL)
		{
			g_apTextureMeshBattleField[nCntTex]->Release();
			g_apTextureMeshBattleField[nCntTex] = NULL;
		}
	}
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_aMeshBattleField[nCntMeshBattleField].pVtxBuff != NULL)
		{
			g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Release();
			g_aMeshBattleField[nCntMeshBattleField].pVtxBuff = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_aMeshBattleField[nCntMeshBattleField].pIdxBuff != NULL)
		{
			g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Release();
			g_aMeshBattleField[nCntMeshBattleField].pIdxBuff = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMeshBattleField(void)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].posOld = g_aMeshBattleField[nCntMeshBattleField].pos;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMeshBattleField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot,mtxTrans;					// �v�Z�p�}�g���b�N�X����

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld);

		// ��]�𔽉f	Y,X,Z�̏��Ԃ����
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshBattleField[nCntMeshBattleField].rot.y, g_aMeshBattleField[nCntMeshBattleField].rot.x, g_aMeshBattleField[nCntMeshBattleField].rot.z);
		D3DXMatrixMultiply(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aMeshBattleField[nCntMeshBattleField].pos.x, g_aMeshBattleField[nCntMeshBattleField].pos.y, g_aMeshBattleField[nCntMeshBattleField].pos.z);
		D3DXMatrixMultiply(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_aMeshBattleField[nCntMeshBattleField].pVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_aMeshBattleField[nCntMeshBattleField].pIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureMeshBattleField[0]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshBattleField[nCntMeshBattleField].nNumVertex, 0, g_aMeshBattleField[nCntMeshBattleField].nNumPolygon);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMeshBattleField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// ���_�o�b�t�@�𐶐�
		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshBattleField[nCntMeshBattleField].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aMeshBattleField[nCntMeshBattleField].pVtxBuff,
			NULL);

		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		// ���_���̐ݒ�	���W�̒��ڎw��͂����ł͊�{�I�ɂ͂��Ȃ�(g_pos~~���𑫂������͂��Ȃ�D3DXMatrixTranslation�ł���Ă�
		for (int nCntPos = 0; nCntPos < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntPos++)
		{
			pVtx[nCntPos].pos = D3DXVECTOR3(float(-((g_aMeshBattleField[nCntMeshBattleField].nXBlock * g_aMeshBattleField[nCntMeshBattleField].fWidth) / 2) + g_aMeshBattleField[nCntMeshBattleField].fWidth * (nCntPos % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1))),
				0.0f,
				float((g_aMeshBattleField[nCntMeshBattleField].nZBlock * g_aMeshBattleField[nCntMeshBattleField].fDepth) / 2 - g_aMeshBattleField[nCntMeshBattleField].fDepth * (nCntPos / (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1))));
		}

		// �@���̐ݒ�@�@���́u1�v�ɂ��Ȃ��Ă͂Ȃ�Ȃ��H�u1.0�v�ȉ��ɂ��Ȃ���΂Ȃ�Ȃ��H
		for (int nCntNor = 0; nCntNor < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntNor++)
		{
			pVtx[nCntNor].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		// ���_�J���[�̐ݒ�
		for (int nCntCol = 0; nCntCol < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntCol++)
		{
			pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �e�N�X�`���̐ݒ�
		for (int nCntTex = 0; nCntTex < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntTex++)
		{
			pVtx[nCntTex].tex = D3DXVECTOR2(1.0f * (nCntTex % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)),
				1.0f * (nCntTex / (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)));
		}


		// ���_�o�b�t�@���A�����b�N����
		g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Unlock();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �C���f�b�N�X���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeIndexMeshBattleField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{


		// �C���f�b�N�X�o�b�t�@�𐶐�
		// �C���f�b�N�X���̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshBattleField[nCntMeshBattleField].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,			// ��̐�����2�o�C�g�����g��Ȃ�
			D3DPOOL_MANAGED,
			&g_aMeshBattleField[nCntMeshBattleField].pIdxBuff,
			NULL);

		WORD *pIdx;				// �C���f�b�N�X�f�[�^�ւ̃|�C���^

		// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// �C���f�b�N�X�̐ݒ�
		for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshBattleField[nCntMeshBattleField].nNumIndex; nCntIdx += 2)
		{
			if ((nCntIdx / 2) % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 2) == g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)
			{
				pIdx[nCntIdx] = nCntPos - 1;
				pIdx[nCntIdx + 1] = nCntPos + g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1;
			}
			else
			{
				pIdx[nCntIdx] = nCntPos + g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1;
				pIdx[nCntIdx + 1] = nCntPos;

				nCntPos++;
			}
		}


		// ���_�o�b�t�@���A�����b�N����
		g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Unlock();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���b�V���t�B�[���h�̓����蔻��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionMeshBattleField(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fRadius)
{
	bool bLand = false;

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{

			// �����蔻��
		if (pPos->x + fRadius > g_aMeshBattleField[nCntMeshBattleField].pos.x - (g_aMeshBattleField[nCntMeshBattleField].fWidth * g_aMeshBattleField[nCntMeshBattleField].nXBlock) / 2
			&& pPos->x - fRadius < g_aMeshBattleField[nCntMeshBattleField].pos.x + (g_aMeshBattleField[nCntMeshBattleField].fWidth * g_aMeshBattleField[nCntMeshBattleField].nXBlock) / 2
			&& pPos->z + fRadius > g_aMeshBattleField[nCntMeshBattleField].pos.z - (g_aMeshBattleField[nCntMeshBattleField].fDepth * g_aMeshBattleField[nCntMeshBattleField].nZBlock) / 2
			&& pPos->z - fRadius < g_aMeshBattleField[nCntMeshBattleField].pos.z + (g_aMeshBattleField[nCntMeshBattleField].fDepth * g_aMeshBattleField[nCntMeshBattleField].nZBlock) / 2)
		{ // XZ���͈͓�
			if (pPos->y < g_aMeshBattleField[nCntMeshBattleField].pos.y
				&& pPosOld->y >= g_aMeshBattleField[nCntMeshBattleField].posOld.y)
			{ // Y+����
				pPos->y = g_aMeshBattleField[nCntMeshBattleField].pos.y;
				pMove->y = 0;
				bLand = true;
			}
		}

	}

	return bLand;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���b�V���t�B�[���h�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
MeshBattleField *GetMeshBattleField(void)
{
	return &g_aMeshBattleField[0];
}