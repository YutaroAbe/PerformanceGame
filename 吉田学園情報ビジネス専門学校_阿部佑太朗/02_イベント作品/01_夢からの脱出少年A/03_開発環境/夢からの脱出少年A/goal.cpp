//=============================================================================
//
// ���f������ [goal.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "goal.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GOAL_FILENAME "data/MODEL/goal.x"
#define GOAL_MOVE_SPEED (0.7f)
#define GOAL_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_GOAL (1)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshGoal[MAX_NUM_GOAL] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatGoal[MAX_NUM_GOAL] = {};//�}�e���A�����ւ̃|�C���^

GOAL g_Goal[MAX_NUM_GOAL];
//=============================================================================
// ����������
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(GOAL_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatGoal[nCntGoal],
			NULL,
			&g_Goal[nCntGoal].NumMatGoal,
			&g_pMeshGoal[nCntGoal]);

		/*�����蔻��̐ݒ�*/
		SetGoalVertex(nCntGoal);
		//���_���̎擾

		// �ʒu�E�����̏����ݒ�
		g_Goal[nCntGoal].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Goal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړ��ʁE��]�ʂ̏�����
		g_Goal[nCntGoal].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Goal[nCntGoal].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Goal[nCntGoal].bUse = true;

	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitGoal(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_GOAL; nCntMesh++)
	{
		// ���b�V���̉��
		if (g_pMeshGoal[nCntMesh] != NULL)
		{
			g_pMeshGoal[nCntMesh]->Release();
			g_pMeshGoal[nCntMesh] = NULL;
		}
		/*�e�N�X�`���̉��*/
		//�}�e���A���̉��
		if (g_pBuffMatGoal[nCntMesh] != NULL)
		{
			g_pBuffMatGoal[nCntMesh]->Release();
			g_pBuffMatGoal[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGoal(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Goal[nCntGoal].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Goal[nCntGoal].rot.y,
			g_Goal[nCntGoal].rot.x,
			g_Goal[nCntGoal].rot.z);

		D3DXMatrixMultiply(&g_Goal[nCntGoal].mtxWorld,
			&g_Goal[nCntGoal].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_Goal[nCntGoal].pos.x,
			g_Goal[nCntGoal].pos.y,
			g_Goal[nCntGoal].pos.z);

		D3DXMatrixMultiply(&g_Goal[nCntGoal].mtxWorld,
			&g_Goal[nCntGoal].mtxWorld,
			&mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Goal[nCntGoal].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatGoal[nCntGoal]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Goal[nCntGoal].NumMatGoal; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*�e�N�X�`���̐ݒ�*/
			pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

			// ���f��(�p�[�c)�̕`��
			g_pMeshGoal[nCntGoal]->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void SetGoal(D3DXVECTOR3 pos)
{
	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = pos;
	}

}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionGoal(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bEnter = false;

	for (int nCntData = 0; nCntData < MAX_NUM_GOAL; nCntData++)
	{
		if (g_Goal[nCntData].bUse == true)
		{
			if (g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//������E
					bEnter = true;

				}
				if (g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//�E���獶
					bEnter = true;

				}
			}

			if (g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//��O���牜
					bEnter = true;

				}
				if (g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//�������O
					bEnter = true;
				}
			}
		}
	}
	return bEnter;

}
//=============================================================================
// �ő�E�ŏ��̒��_���W���擾
//=============================================================================
void SetGoalVertex(int nCntGoal)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Goal[nCntGoal].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Goal[nCntGoal].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshGoal[nCntGoal]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshGoal[nCntGoal]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshGoal[nCntGoal]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Goal[nCntGoal].VtxMin.x > vtx.x)
		{
			g_Goal[nCntGoal].VtxMin.x = vtx.x;
		}
		if (g_Goal[nCntGoal].VtxMax.x < vtx.x)
		{
			g_Goal[nCntGoal].VtxMax.x = vtx.x;
		}

		//y
		if (g_Goal[nCntGoal].VtxMin.y > vtx.y)
		{
			g_Goal[nCntGoal].VtxMin.y = vtx.y;
		}
		if (g_Goal[nCntGoal].VtxMax.y < vtx.y)
		{
			g_Goal[nCntGoal].VtxMax.y = vtx.y;
		}

		//z
		if (g_Goal[nCntGoal].VtxMin.z > vtx.z)
		{
			g_Goal[nCntGoal].VtxMin.z = vtx.z;
		}
		if (g_Goal[nCntGoal].VtxMax.z < vtx.z)
		{
			g_Goal[nCntGoal].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshGoal[nCntGoal]->UnlockVertexBuffer();

}