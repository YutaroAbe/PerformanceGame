//=============================================================================
//
// ���f������ [obstacle.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "obstacle.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBSTACLE_FILENAME0 "data/MODEL/mine1.x"
#define OBSTACLE_FILENAME1 "data/MODEL/object.x"
#define OBSTACLE_MOVE_SPEED (0.7f)
#define OBSTACLE_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_OBSTACLE (100)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshObstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE] = {};//�}�e���A�����ւ̃|�C���^

OBSTACLE g_Obstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE];
//=============================================================================
// ����������
//=============================================================================
void InitObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPCSTR ObsFileName[OBSTACLETYPE_MAX] = { OBSTACLE_FILENAME0,
											OBSTACLE_FILENAME1 };

	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{

		for (int nCntObstacle = 0; nCntObstacle < MAX_NUM_OBSTACLE; nCntObstacle++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(ObsFileName[nCntType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatObstacle[nCntType][nCntObstacle],
				NULL,
				&g_Obstacle[nCntType][nCntObstacle].NumMatObstacle,
				&g_pMeshObstacle[nCntType][nCntObstacle]);

			/*�����蔻��̐ݒ�*/
			SetObstacleVertex(nCntObstacle,nCntType);
			//���_���̎擾

			// �ʒu�E�����̏����ݒ�
			g_Obstacle[nCntType][nCntObstacle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Obstacle[nCntType][nCntObstacle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�ړ��ʁE��]�ʂ̏�����
			g_Obstacle[nCntType][nCntObstacle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Obstacle[nCntType][nCntObstacle].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Obstacle[nCntType][nCntObstacle].bUse = false;

		}
	}

}

//=============================================================================
// �I������
//=============================================================================
void UninitObstacle(void)
{
	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{
		for (int nCntMesh = 0; nCntMesh < MAX_NUM_OBSTACLE; nCntMesh++)
		{
			// ���b�V���̉��
			if (g_pMeshObstacle[nCntType][nCntMesh] != NULL)
			{
				g_pMeshObstacle[nCntType][nCntMesh]->Release();
				g_pMeshObstacle[nCntType][nCntMesh] = NULL;
			}
			/*�e�N�X�`���̉��*/
			//�}�e���A���̉��
			if (g_pBuffMatObstacle[nCntType][nCntMesh] != NULL)
			{
				g_pBuffMatObstacle[nCntType][nCntMesh]->Release();
				g_pBuffMatObstacle[nCntType][nCntMesh] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObstacle(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�̃|�C���^

	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{

		for (int nCntObstacle = 0; nCntObstacle < MAX_NUM_OBSTACLE; nCntObstacle++)
		{
			if (g_Obstacle[nCntType][nCntObstacle].bUse == true)
			{

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Obstacle[nCntType][nCntObstacle].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Obstacle[nCntType][nCntObstacle].rot.y,
					g_Obstacle[nCntType][nCntObstacle].rot.x,
					g_Obstacle[nCntType][nCntObstacle].rot.z);

				D3DXMatrixMultiply(&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans,
					g_Obstacle[nCntType][nCntObstacle].pos.x,
					g_Obstacle[nCntType][nCntObstacle].pos.y,
					g_Obstacle[nCntType][nCntObstacle].pos.z);

				D3DXMatrixMultiply(&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&mtxTrans);
				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Obstacle[nCntType][nCntObstacle].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType][nCntObstacle]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Obstacle[nCntType][nCntObstacle].NumMatObstacle; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*�e�N�X�`���̐ݒ�*/
					pDevice->SetTexture(0, NULL);//�e�N�X�`���̐ݒ�(�g��Ȃ����NULL������)

					// ���f��(�p�[�c)�̕`��
					g_pMeshObstacle[nCntType][nCntObstacle]->DrawSubset(nCntMat);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// ��Q���̐ݒu
//=============================================================================
void SetObstacle(D3DXVECTOR3 pos, OBS_TYPE type)
{
	for (int nCntData = 0; nCntData < MAX_NUM_OBSTACLE; nCntData++)
	{
		if (g_Obstacle[type][nCntData].bUse == false)
		{
			g_Obstacle[type][nCntData].pos = pos;

			g_Obstacle[type][nCntData].bUse = true;
			break;
		}

	}
}
//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CollisionObstacle(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//�ϐ��錾
	bool bLand = false;
	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{
		for (int nCntData = 0; nCntData < MAX_NUM_OBSTACLE; nCntData++)
		{
			if (g_Obstacle[nCntType][nCntData].bUse == true)
			{
				if (g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z <= pPos->z&&
					g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z >= pPos->z)
				{
					if (g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x <= pPos->x&&
						g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x >= pOldPos->x)
					{//������E
						pPos->x = g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x;
						pMove->x = 0.0f;
					}
					else if (g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x >= pPos->x &&
						g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x <= pOldPos->x)
					{//�E���獶
						pPos->x = g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x;
						pMove->x = 0.0f;
					}
				}

				if (g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x < pPos->x &&
					g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x > pPos->x)
				{
					if (g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z <= pPos->z&&
						g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z >= pOldPos->z)
					{//��O���牜
						pPos->z = g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z;
						pMove->z = 0.0f;
					}
					else if (g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z >= pPos->z&&
						g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z <= pOldPos->z)
					{//�������O
						pPos->z = g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z;
						pMove->z = 0.0f;
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
void SetObstacleVertex(int nCntObstacle,int nCntType)
{
	//�ϐ��錾
	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	g_Obstacle[nCntType][nCntObstacle].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Obstacle[nCntType][nCntObstacle].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//���_���̎擾
	nNumVtx = g_pMeshObstacle[nCntType][nCntObstacle]->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle[nCntType][nCntObstacle]->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshObstacle[nCntType][nCntObstacle]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

													//���_���r���ă��f���̍ŏ��E�ő�𔲂��o��
													//x
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.x > vtx.x)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.x = vtx.x;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.x < vtx.x)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.x = vtx.x;
		}

		//y
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.y > vtx.y)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.y = vtx.y;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.y < vtx.y)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.y = vtx.y;
		}

		//z
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.z > vtx.z)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.z = vtx.z;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.z < vtx.z)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}
	//�A�����b�N
	g_pMeshObstacle[nCntType][nCntObstacle]->UnlockVertexBuffer();

}