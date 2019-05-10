//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �Q�[���I�u�W�F�N�g���� [gameobject.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "gameobject.h"
#include "game.h"



//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_GAMEOBJECT_MODEL		(40)		// �ǂݍ��߂�Q�[���I�u�W�F�N�g���f���̍ő吔
#define GAMEOBJECT_LOADTXT_NAME			"data//TEXT//model_game.txt"			// �I�u�W�F�N�g�z�u�̃e�L�X�g�t�@�C����
#define MAX_LOAD_LINE				(256)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffGameObject = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
GameObject	g_aGameObject[MAX_GAMEOBJECT];						// �Q�[���I�u�W�F�N�g�̏��
GameObjectModelData g_apGameObject[MAX_GAMEOBJECT_MODEL] = {};	// �Q�[���I�u�W�F�N�g�ւ̃|�C���^
int g_nGameObjectLoadNum = 0;

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitGameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		g_aGameObject[nCntGameObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].posOld = g_aGameObject[nCntGameObject].pos;
		g_aGameObject[nCntGameObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGameObject[nCntGameObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].ModelType = 0;
		g_aGameObject[nCntGameObject].bUse = false;
		g_aGameObject[nCntGameObject].bDisp = true;
	}

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT_MODEL; nCntGameObject++)
	{
		g_apGameObject[nCntGameObject].pFilename = NULL;
		g_apGameObject[nCntGameObject].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_apGameObject[nCntGameObject].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	}
	LoadModelGameObject();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitGameObject(void)
{
	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT_MODEL; nCntGameObject++)
	{
		// �e�N�X�`���̊J��
		for (int nCntTex = 0; nCntTex < MAX_GAMEOBJECT_TEX; nCntTex++)
		{
			if (g_apGameObject[nCntGameObject].pTexture[nCntTex] != NULL)
			{
				g_apGameObject[nCntGameObject].pTexture[nCntTex]->Release();
				g_apGameObject[nCntGameObject].pTexture[nCntTex] = NULL;
			}
		}

		// ���b�V���̊J��
		if (g_apGameObject[nCntGameObject].pMesh != NULL)
		{
			g_apGameObject[nCntGameObject].pMesh->Release();
			g_apGameObject[nCntGameObject].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_apGameObject[nCntGameObject].pBuffMat != NULL)
		{
			g_apGameObject[nCntGameObject].pBuffMat->Release();
			g_apGameObject[nCntGameObject].pBuffMat = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffGameObject != NULL)
	{
		g_pVtxBuffGameObject->Release();
		g_pVtxBuffGameObject = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateGameObject(void)
{

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawGameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		if (g_aGameObject[nCntGameObject].bUse == true && g_aGameObject[nCntGameObject].bDisp == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aGameObject[nCntGameObject].mtxWorldGameObject);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGameObject[nCntGameObject].rot.y, g_aGameObject[nCntGameObject].rot.x, g_aGameObject[nCntGameObject].rot.z);
			D3DXMatrixMultiply(&g_aGameObject[nCntGameObject].mtxWorldGameObject, &g_aGameObject[nCntGameObject].mtxWorldGameObject, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aGameObject[nCntGameObject].pos.x, g_aGameObject[nCntGameObject].pos.y, g_aGameObject[nCntGameObject].pos.z);
			D3DXMatrixMultiply(&g_aGameObject[nCntGameObject].mtxWorldGameObject, &g_aGameObject[nCntGameObject].mtxWorldGameObject, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aGameObject[nCntGameObject].mtxWorldGameObject);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pBuffMat->GetBufferPointer();

			//pMat->pTextureFilename[0]
				//g_pTextureGameObject
			for (int nCntMat = 0; nCntMat < (int)g_apGameObject[g_aGameObject[nCntGameObject].ModelType].nNumMat; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pTexture[nCntMat]);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �Q�[���I�u�W�F�N�g(�p�[�c)�̕`��
				g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pMesh->DrawSubset(nCntMat);

			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���I�u�W�F�N�g�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetGameObject(D3DXVECTOR3 pos, int ModelType)
{
	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		if (g_aGameObject[nCntGameObject].bUse == false)
		{
			g_aGameObject[nCntGameObject].pos = pos;
			g_aGameObject[nCntGameObject].ModelType = ModelType;
			g_aGameObject[nCntGameObject].bUse = true;

			break;
		}
	}
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���I�u�W�F�N�g�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
GameObject *GetGameObject(void)
{
	return &g_aGameObject[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���I�u�W�F�N�g���f���̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
GameObjectModelData *GetGameObjectModel(void)
{
	return &g_apGameObject[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���I�u�W�F�N�gtxt�f�[�^�̓ǂݍ���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadModelGameObject(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1�s�̈ꎞ�I�ǂݍ���
	char cData[MAX_LOAD_LINE];			// �ꎞ�I�ǂݍ���

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	int nCntModel = 0;
	char cTexName[MAX_LOAD_LINE] = {};

	pFile = fopen(GAMEOBJECT_LOADTXT_NAME, "r"); // �t�@�C�����J��

	if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
	{ // �t�@�C�����J�����ۂ̏���ss
		while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
		{
			sscanf(cLine, "%s", cData);
			if (strcmp(cData, "NUM_MODEL") == 0)
			{
				int nNumModel;
				sscanf(cLine, "%s %s %d", cData, cData, &nNumModel);
			}
			else if (strcmp(cData, "MODEL_FILENAME") == 0)
			{
				sscanf(cLine, "%s %s %s", cData, cData, cData);

				D3DXLoadMeshFromX(cData,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_apGameObject[nCntModel].pBuffMat,
					NULL,
					&g_apGameObject[nCntModel].nNumMat,
					&g_apGameObject[nCntModel].pMesh);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_apGameObject[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_apGameObject[nCntModel].nNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_apGameObject[nCntModel].pTexture[nCntMat]);
					}
				}

				int nNumVtx;			// ���_��
				DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
				BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

				// ���_�����擾
				nNumVtx = g_apGameObject[nCntModel].pMesh->GetNumVertices();

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				sizeFVF = D3DXGetFVFVertexSize(g_apGameObject[nCntModel].pMesh->GetFVF());

				// ���_�o�b�t�@�����b�N
				g_apGameObject[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// ���_���W�̑��

					// �S�Ă̒��_�����r���ă��f���̍ŏ��l�ő�l�𔲂��o��
					if (vtx.x < g_apGameObject[nCntModel].vtxMin.x)
					{
						g_apGameObject[nCntModel].vtxMin.x = vtx.x;
					}
					if (vtx.y < g_apGameObject[nCntModel].vtxMin.y)
					{
						g_apGameObject[nCntModel].vtxMin.y = vtx.y;
					}
					if (vtx.z < g_apGameObject[nCntModel].vtxMin.z)
					{
						g_apGameObject[nCntModel].vtxMin.z = vtx.z;
					}

					if (vtx.x > g_apGameObject[nCntModel].vtxMax.x)
					{
						g_apGameObject[nCntModel].vtxMax.x = vtx.x;
					}
					if (vtx.y > g_apGameObject[nCntModel].vtxMax.y)
					{
						g_apGameObject[nCntModel].vtxMax.y = vtx.y;
					}
					if (vtx.z > g_apGameObject[nCntModel].vtxMax.z)
					{
						g_apGameObject[nCntModel].vtxMax.z = vtx.z;
					}

					pVtxBuff += sizeFVF;		// �T�C�Y���|�C���^��i�߂�
				}

				// ���_�o�b�t�@���A�����b�N
				g_apGameObject[nCntModel].pMesh->UnlockVertexBuffer();

				nCntModel++;
			}
			else if (strcmp(cData, "MODELSET") == 0)
			{
				for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
				{
					if (g_aGameObject[nCntGameObject].bUse == false)
					{
						while (strcmp(cData, "END_MODELSET") != 0)
						{
							fgets(cLine, MAX_LOAD_LINE, pFile);

							sscanf(cLine, "%s", cData);

							if (strcmp(cData, "TYPE") == 0)
							{
								sscanf(cLine, "%s %s %d", cData, cData, &g_aGameObject[nCntGameObject].ModelType);
								g_aGameObject[nCntGameObject].bUse = true;
							}
							else if (strcmp(cData, "POS") == 0)
							{
								sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aGameObject[nCntGameObject].pos.x,
									&g_aGameObject[nCntGameObject].pos.y,
									&g_aGameObject[nCntGameObject].pos.z);
							}
							else if (strcmp(cData, "ROT") == 0)
							{
								sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aGameObject[nCntGameObject].rot.x,
									&g_aGameObject[nCntGameObject].rot.y,
									&g_aGameObject[nCntGameObject].rot.z);
							}
						}
						break;
					}
				}
			}
		}
		fclose(pFile); // �t�@�C�������
	}
	else
	{ // �t�@�C�����J���Ȃ������ۂ̏���

	}
}

