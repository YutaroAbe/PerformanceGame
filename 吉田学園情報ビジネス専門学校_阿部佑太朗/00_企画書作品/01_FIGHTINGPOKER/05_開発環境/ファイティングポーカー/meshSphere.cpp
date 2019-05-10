//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�V���X�t�B�A���� [meshSphere.cpp]
// Author : ���a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "meshSphere.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESHSPHERE_SMALL_BLOCK_NUM	(32)
#define MESHSPHERE_LARGE_BLOCK_NUM	(64)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXCOLOR col;						// �F
	D3DXMATRIX	mtxWorld;				// ���[���h�}�g���b�N�X
	float fRadius;						// ���a
	int nVBlock;						// X�����̃u���b�N��
	int nHBlock;						// Y�����̃u���b�N��
	int nNumVertex;						// ���_��
	int nNumIndex;						// �C���f�b�N�X��
	int nNumPolygon;					// �|���S����
	int nTexType;						// �e�N�X�`���[���
	bool bInside;						// �������ǂ���
	bool bUp;							// ��������ǂ���
	bool bUse;							// �g�p���Ă��邩�ǂ���
	bool bDisp;							// �\�����邩�ǂ���
	MESHSPHERE_TYPE type;				// ���
}MeshSphere;

typedef enum
{
	POLYGON_TEX_000 = 0,	// �|���S���e�N�X�`��000
	POLYGON_TEX_MAX,		// ����
}MeshSphereTexName;

typedef struct
{
	char *pFilename;	// �t�@�C����
} MeshSphereTexInfo;
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexMeshSphere(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9			g_apTextureMeshSphere[POLYGON_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^

MeshSphere g_aMeshSphere[MAX_MESHSPHERE];				// ���b�V���h�[���̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
MeshSphereTexInfo g_apTextureMeshSphereInfo[POLYGON_TEX_MAX] =
{
	{ "data//TEXTURE//.png" },		// �e�N�X�`��0
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	for (int nCntMeshSphereTex = 0; nCntMeshSphereTex < POLYGON_TEX_MAX; nCntMeshSphereTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMeshSphereInfo[nCntMeshSphereTex].pFilename,
			&g_apTextureMeshSphere[nCntMeshSphereTex]);
	}

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		g_aMeshSphere[nCntMeshSphere].pVtxBuff = NULL;
		g_aMeshSphere[nCntMeshSphere].pIdxBuff = NULL;
		g_aMeshSphere[nCntMeshSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshSphere[nCntMeshSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aMeshSphere[nCntMeshSphere].nVBlock = 0;
		g_aMeshSphere[nCntMeshSphere].nHBlock = 0;
		g_aMeshSphere[nCntMeshSphere].fRadius = 0.0f;
		g_aMeshSphere[nCntMeshSphere].nNumVertex = 0;
		g_aMeshSphere[nCntMeshSphere].nNumIndex = 0;
		g_aMeshSphere[nCntMeshSphere].nNumPolygon = 0;
		g_aMeshSphere[nCntMeshSphere].nTexType = 0;
		g_aMeshSphere[nCntMeshSphere].bInside = false;
		g_aMeshSphere[nCntMeshSphere].bUp = false;
		g_aMeshSphere[nCntMeshSphere].bUse = false;
		g_aMeshSphere[nCntMeshSphere].bDisp = false;
		g_aMeshSphere[nCntMeshSphere].type = MESHSPHERE_TYPE_ATTACK;
	}
	// �z�u���b�V���̏��
	/*g_aMeshSphere[0].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_aMeshSphere[0].nVBlock = 64;
	g_aMeshSphere[0].nHBlock = 64;
	g_aMeshSphere[0].fRadius = 10.0f;
	g_aMeshSphere[0].bInside = true;
	g_aMeshSphere[0].bUse = true;
	g_aMeshSphere[0].bDisp = true;

	g_aMeshSphere[1].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
	g_aMeshSphere[1].nVBlock = 64;
	g_aMeshSphere[1].nHBlock = 64;
	g_aMeshSphere[1].fRadius = 10.0f;
	g_aMeshSphere[1].bInside = true;
	g_aMeshSphere[1].bUse = true;
	g_aMeshSphere[1].bDisp = true;*/


	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		// �C���f�b�N�X���v�Z
		g_aMeshSphere[nCntMeshSphere].nNumIndex = 2 + g_aMeshSphere[nCntMeshSphere].nVBlock * 2;
		g_aMeshSphere[nCntMeshSphere].nNumIndex += (g_aMeshSphere[nCntMeshSphere].nNumIndex + 2) * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

		// �|���S�����v�Z
		g_aMeshSphere[nCntMeshSphere].nNumPolygon = (g_aMeshSphere[nCntMeshSphere].nVBlock * g_aMeshSphere[nCntMeshSphere].nHBlock) * 2 + 4 * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

		// ���_���v�Z
		g_aMeshSphere[nCntMeshSphere].nNumVertex = (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)*(g_aMeshSphere[nCntMeshSphere].nHBlock + 1);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMeshSphere(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < POLYGON_TEX_MAX; nCntTex++)
	{
		if (g_apTextureMeshSphere[nCntTex] != NULL)
		{
			g_apTextureMeshSphere[nCntTex]->Release();
			g_apTextureMeshSphere[nCntTex] = NULL;
		}
	}

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_aMeshSphere[nCntMeshSphere].pVtxBuff != NULL)
		{
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Release();
			g_aMeshSphere[nCntMeshSphere].pVtxBuff = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_aMeshSphere[nCntMeshSphere].pIdxBuff != NULL)
		{
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Release();
			g_aMeshSphere[nCntMeshSphere].pIdxBuff = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMeshSphere(void)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse == true)
		{
			VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�J���[�̐ݒ�
			for (int nCntCol = 0; nCntCol < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntCol++)
			{
				pVtx[nCntCol].col = g_aMeshSphere[nCntMeshSphere].col;
			}

			// ���_�o�b�t�@���A�����b�N����
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Unlock();

		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot,mtxTrans;					// �v�Z�p�}�g���b�N�X����

	// ���C�g�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse && g_aMeshSphere[nCntMeshSphere].bDisp)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshSphere[nCntMeshSphere].mtxWorld);

			// ��]�𔽉f	Y,X,Z�̏��Ԃ����
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshSphere[nCntMeshSphere].rot.y, g_aMeshSphere[nCntMeshSphere].rot.x, g_aMeshSphere[nCntMeshSphere].rot.z);
			D3DXMatrixMultiply(&g_aMeshSphere[nCntMeshSphere].mtxWorld, &g_aMeshSphere[nCntMeshSphere].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshSphere[nCntMeshSphere].pos.x, g_aMeshSphere[nCntMeshSphere].pos.y, g_aMeshSphere[nCntMeshSphere].pos.z);
			D3DXMatrixMultiply(&g_aMeshSphere[nCntMeshSphere].mtxWorld, &g_aMeshSphere[nCntMeshSphere].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshSphere[nCntMeshSphere].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aMeshSphere[nCntMeshSphere].pVtxBuff, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aMeshSphere[nCntMeshSphere].pIdxBuff);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureMeshSphere[0]);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshSphere[nCntMeshSphere].nNumVertex, 0, g_aMeshSphere[nCntMeshSphere].nNumPolygon);
		}
	}
	// ���C�g�I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���b�V���X�t�B�A�̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_���̍쐬
	MakeVertexMeshSphere(pDevice);

	// �C���f�b�N�X���̍쐬
	MakeIndexMeshSphere(pDevice);
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse)
		{
			// ���_�o�b�t�@�𐶐�
			// ���_���̍쐬
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshSphere[nCntMeshSphere].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_aMeshSphere[nCntMeshSphere].pVtxBuff,
				NULL);

			VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


			// ���_���̐ݒ�	���W�̒��ڎw��͂����ł͊�{�I�ɂ͂��Ȃ�(g_pos~~���𑫂������͂��Ȃ�D3DXMatrixTranslation�ł���Ă�
			for (int nCntPos = 0; nCntPos < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntPos++)
			{
				int nInside = 1;
				if (g_aMeshSphere[nCntMeshSphere].bInside == true)
				{
					nInside *= -1;
				}

				int nTest = (g_aMeshSphere[nCntMeshSphere].nNumVertex / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)) - (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1));


				//if (nCntPos < g_aMeshSphere[nCntMeshSphere].nNumVertex / 2)
				{
					pVtx[nCntPos].pos =
						D3DXVECTOR3(sinf(-(D3DX_PI*nInside) / 2.0f - ((-(D3DX_PI*nInside) * 2.0f) / g_aMeshSphere[nCntMeshSphere].nVBlock) * (nCntPos % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * (sinf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius),
							cosf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius,
							cosf(-(D3DX_PI*nInside) / 2.0f - ((-(D3DX_PI*nInside) * 2.0f) / g_aMeshSphere[nCntMeshSphere].nVBlock) * float(nCntPos % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * (sinf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius));
				}
			}

			// �@���̐ݒ�@�@���́u1�v�ɂ��Ȃ��Ă͂Ȃ�Ȃ��H�u1.0�v�ȉ��ɂ��Ȃ���΂Ȃ�Ȃ��H
			for (int nCntNor = 0; nCntNor < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntNor++)
			{
				D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].pos);		// ���K������
			}

			// ���_�J���[�̐ݒ�
			for (int nCntCol = 0; nCntCol < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntCol++)
			{
				pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// �e�N�X�`���̐ݒ�
			for (int nCntTex = 0; nCntTex < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntTex++)
			{
				pVtx[nCntTex].tex = D3DXVECTOR2(1.0f / 2.0f / g_aMeshSphere[nCntMeshSphere].nVBlock * (nCntTex % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)) * 2, // �Ō��*2�͂��̏ꂵ�̂�
					1.0f / 2.0f / g_aMeshSphere[nCntMeshSphere].nHBlock * (nCntTex / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)));
			}


			// ���_�o�b�t�@���A�����b�N����
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Unlock();
		}
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �C���f�b�N�X���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeIndexMeshSphere(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse)
		{
			// �C���f�b�N�X�o�b�t�@�𐶐�
			// �C���f�b�N�X���̍쐬
			pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshSphere[nCntMeshSphere].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,			// ��̐�����2�o�C�g�����g��Ȃ�
				D3DPOOL_MANAGED,
				&g_aMeshSphere[nCntMeshSphere].pIdxBuff,
				NULL);

			WORD *pIdx;				// �C���f�b�N�X�f�[�^�ւ̃|�C���^

			// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

			// �C���f�b�N�X�̐ݒ�
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshSphere[nCntMeshSphere].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aMeshSphere[nCntMeshSphere].nVBlock + 2) == g_aMeshSphere[nCntMeshSphere].nVBlock + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aMeshSphere[nCntMeshSphere].nVBlock + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aMeshSphere[nCntMeshSphere].nVBlock + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}

			// ���_�o�b�t�@���A�����b�N����
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Unlock();
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�t�B�A�̐ݒ菈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int SetSphere(D3DXVECTOR3 const pos, float const fRadius, MESHSPHERE_TYPE const type, bool const bInside)
{
	int nCntMeshSphere;

	for (nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (!g_aMeshSphere[nCntMeshSphere].bUse)
		{// �g�p���Ă��Ȃ��ꍇ
			g_aMeshSphere[nCntMeshSphere].pos = pos;
			g_aMeshSphere[nCntMeshSphere].fRadius = fRadius;
			g_aMeshSphere[nCntMeshSphere].type = type;
			g_aMeshSphere[nCntMeshSphere].bInside = bInside;
			if (fRadius < 1000)
			{ // ���̑傫�����Ȃ�|���S���������Ȃ�����
				g_aMeshSphere[nCntMeshSphere].nVBlock = MESHSPHERE_SMALL_BLOCK_NUM;
				g_aMeshSphere[nCntMeshSphere].nHBlock = MESHSPHERE_SMALL_BLOCK_NUM;
			}
			else
			{
				g_aMeshSphere[nCntMeshSphere].nVBlock = MESHSPHERE_LARGE_BLOCK_NUM;
				g_aMeshSphere[nCntMeshSphere].nHBlock = MESHSPHERE_LARGE_BLOCK_NUM;
			}
			g_aMeshSphere[nCntMeshSphere].bUse = true;

			// �C���f�b�N�X���v�Z
			g_aMeshSphere[nCntMeshSphere].nNumIndex = 2 + g_aMeshSphere[nCntMeshSphere].nVBlock * 2;
			g_aMeshSphere[nCntMeshSphere].nNumIndex += (g_aMeshSphere[nCntMeshSphere].nNumIndex + 2) * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

			// �|���S�����v�Z
			g_aMeshSphere[nCntMeshSphere].nNumPolygon = (g_aMeshSphere[nCntMeshSphere].nVBlock * g_aMeshSphere[nCntMeshSphere].nHBlock) * 2 + 4 * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

			// ���_���v�Z
			g_aMeshSphere[nCntMeshSphere].nNumVertex = (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)*(g_aMeshSphere[nCntMeshSphere].nHBlock + 1);

			switch (g_aMeshSphere[nCntMeshSphere].type)
			{
			case MESHSPHERE_TYPE_ATTACK:
				g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
				break;
			case MESHSPHERE_TYPE_DEFENSE:
				g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
				g_aMeshSphere[nCntMeshSphere].bDisp = true;
				break;
			}
			break;
		}
	}
	return nCntMeshSphere;
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�t�B�A�̈ړ�����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPositionSphere(int const nIDSphere, D3DXVECTOR3 const pos)
{
	if (g_aMeshSphere[nIDSphere].bUse == true)
	{
		g_aMeshSphere[nIDSphere].pos = pos;

		//g_aMeshSphere[nIDSphere].pos.z = -10.0f;
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�t�B�A�̕\���ؑ֏���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetDispSphere(int const nIDSphere, bool bDisp)
{
	if (g_aMeshSphere[nIDSphere].bUse == true)
	{
		g_aMeshSphere[nIDSphere].bDisp = bDisp;
	}
}