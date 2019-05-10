//=============================================================================
//
// ���f������ [model.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "model.h"
#include "camera.h"


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshModel[BLOCKCOLOR_MAX][MAX_NUM_MODEL] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel[BLOCKCOLOR_MAX][MAX_NUM_MODEL] = {};//�}�e���A�����ւ̃|�C���^

MODEL g_Model[BLOCKCOLOR_MAX][MAX_NUM_MODEL];
//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPCSTR FileName[BLOCKCOLOR_MAX] = { MODEL_FILENAME0,
										MODEL_FILENAME1,
										MODEL_FILENAME2,
										MODEL_FILENAME3,
										MODEL_FILENAME4,
										MODEL_FILENAME5 };

	
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(FileName[nCntCol],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatModel[nCntCol][nCntModel],
				NULL,
				&g_Model[nCntCol][nCntModel].NumMatModel,
				&g_pMeshModel[nCntCol][nCntModel]);

			/*�����蔻��̐ݒ�*/
			SetModelVertex(nCntModel, nCntCol);
			//���_���̎擾

			// �ʒu�E�����̏����ݒ�
			g_Model[nCntCol][nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model[nCntCol][nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʁE��]�ʂ̏�����
			g_Model[nCntCol][nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model[nCntCol][nCntModel].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model[nCntCol][nCntModel].bUse = false;

		}
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntMesh = 0; nCntMesh < MAX_NUM_MODEL; nCntMesh++)
		{
			// ���b�V���̉��
			if (g_pMeshModel[nCntCol][nCntMesh] != NULL)
			{
				g_pMeshModel[nCntCol][nCntMesh]->Release();
				g_pMeshModel[nCntCol][nCntMesh] = NULL;
			}
			/*�e�N�X�`���̉��*/
			//�}�e���A���̉��
			if (g_pBuffMatModel[nCntCol][nCntMesh] != NULL)
			{
				g_pBuffMatModel[nCntCol][nCntMesh]->Release();
				g_pBuffMatModel[nCntCol][nCntMesh] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
		{
			if (g_Model[nCntCol][nCntModel].bUse == true)
			{

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Model[nCntCol][nCntModel].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Model[nCntCol][nCntModel].rot.y,
					g_Model[nCntCol][nCntModel].rot.x,
					g_Model[nCntCol][nCntModel].rot.z);

				D3DXMatrixMultiply(&g_Model[nCntCol][nCntModel].mtxWorld,
					&g_Model[nCntCol][nCntModel].mtxWorld,
					&mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans,
					g_Model[nCntCol][nCntModel].pos.x,
					g_Model[nCntCol][nCntModel].pos.y,
					g_Model[nCntCol][nCntModel].pos.z);

				D3DXMatrixMultiply(&g_Model[nCntCol][nCntModel].mtxWorld,
					&g_Model[nCntCol][nCntModel].mtxWorld,
					&mtxTrans);
				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntCol][nCntModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntCol][nCntModel]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Model[nCntCol][nCntModel].NumMatModel; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*�e�N�X�`���̐ݒ�*/
					pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

					// ���f��(�p�[�c)�̕`��
					g_pMeshModel[nCntCol][nCntModel]->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}

		}
	}
}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax, 
	MODEL		**pModel)
{
	//�ϐ��錾
	bool bLand = false;
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
		{
			if (g_Model[nCntCol][nCntData].bUse == true)
			{
				if (g_Model[nCntCol][nCntData].VtxMin.z + g_Model[nCntCol][nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Model[nCntCol][nCntData].VtxMax.z + g_Model[nCntCol][nCntData].pos.z >= pPos->z + pVtxMin->z)
				{
					if (g_Model[nCntCol][nCntData].VtxMin.x + g_Model[nCntCol][nCntData].pos.x <= pPos->x + pVtxMax->x&&
						g_Model[nCntCol][nCntData].VtxMax.x + g_Model[nCntCol][nCntData].pos.x >= pPos->x + pVtxMin->x)
					{
						if (g_Model[nCntCol][nCntData].VtxMin.y + g_Model[nCntCol][nCntData].pos.y <= pPos->y + pVtxMin->y &&
							g_Model[nCntCol][nCntData].VtxMax.y + g_Model[nCntCol][nCntData].pos.y >= pOldPos->y + pVtxMin->y)
						{
							bLand = true;

							pMove->y = 0.0f;
							pPos->y = g_Model[nCntCol][nCntData].VtxMax.y + g_Model[nCntCol][nCntData].pos.y;
							*pModel = &g_Model[nCntCol][nCntData];

						}
					}
				}

			}
		}
	}
	return bLand;

}
//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetModelVertex(int nCntModel, int ColNum)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Model[ColNum][nCntModel].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Model[ColNum][nCntModel].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshModel[ColNum][nCntModel]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[ColNum][nCntModel]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshModel[ColNum][nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Model[ColNum][nCntModel].VtxMin.x > vtx.x)
		{
			g_Model[ColNum][nCntModel].VtxMin.x = vtx.x;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.x < vtx.x)
		{
			g_Model[ColNum][nCntModel].VtxMax.x = vtx.x;
		}

		//y
		if (g_Model[ColNum][nCntModel].VtxMin.y > vtx.y)
		{
			g_Model[ColNum][nCntModel].VtxMin.y = vtx.y;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.y < vtx.y)
		{
			g_Model[ColNum][nCntModel].VtxMax.y = vtx.y;
		}

		//z
		if (g_Model[ColNum][nCntModel].VtxMin.z > vtx.z)
		{
			g_Model[ColNum][nCntModel].VtxMin.z = vtx.z;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.z < vtx.z)
		{
			g_Model[ColNum][nCntModel].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshModel[ColNum][nCntModel]->UnlockVertexBuffer();

}

//=============================================================================
// ���f���̈ʒu�ݒ�
//=============================================================================
void SetModel(D3DXVECTOR3 pos, BLOCKCOLOR col)
{
	for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
	{
		if (g_Model[col][nCntData].bUse == false)
		{
			g_Model[col][nCntData].pos = pos;
			g_Model[col][nCntData].col = col;
			g_Model[col][nCntData].bUse = true;
			break;
		}
	}
}