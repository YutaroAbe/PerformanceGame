//=============================================================================
//
// ���f������ [ColorBall.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "ColorBall.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLORFIELD_NAME000		 "data\\MODEL\\BallRed.x"		//�e�N�X�`���̃t�@�C����
#define COLORFIELD_NAME001		 "data\\MODEL\\BallGreen.x"		//�e�N�X�`���̃t�@�C����
#define COLORFIELD_NAME002		 "data\\MODEL\\BallBlue.x"		//�e�N�X�`���̃t�@�C����
#define COLORFIELD_NAME003		 "data\\MODEL\\BallPurple.x"		//�e�N�X�`���̃t�@�C����
#define COLORFIELD_NAME004		 "data\\MODEL\\BallYellow.x"		//�e�N�X�`���̃t�@�C����

#define MOVE_MODEL			(2.0f)							//���f���ړ���
#define MOVE_SIN_COS_TOP	(0.75f)							//�|���S���ړ���
#define MOVE_SIN_COS_BOT	(0.25f)							//�|���S���ړ���
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(1)								//���f���z�u�̍ő吔
#define MAX_COLORFIELD_TYPE	(5)								//���f����ނ̍ő吔
#define CHANGE_TIMER		(240)							//�ω����̎���(�t���[����)
#define MOVE_OK_TIMER		(600)							//�ړ��\����(�t���[����)
#define CHANGE_FRAME		(5)								//�ω��̃X�s�[�h(�t���[����)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshColorBall[MAX_COLORFIELD_TYPE];						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatColorBall[MAX_COLORFIELD_TYPE];				//�}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9	g_pTextureColorBall[MAX_COLORFIELD_TYPE];			//�e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatColorBall[MAX_COLORFIELD_TYPE] = {};					//�}�e���A�����̐�
COLORBALL g_aColorBall[MAX_MODEL];
//=============================================================================
// ����������
//=============================================================================
void InitColorBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(COLORFIELD_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[0],
		NULL,
		&g_nNumMatColorBall[0],
		&g_pMeshColorBall[0]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(COLORFIELD_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[1],
		NULL,
		&g_nNumMatColorBall[1],
		&g_pMeshColorBall[1]);
	
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(COLORFIELD_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[2],
		NULL,
		&g_nNumMatColorBall[2],
		&g_pMeshColorBall[2]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(COLORFIELD_NAME003,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[3],
		NULL,
		&g_nNumMatColorBall[3],
		&g_pMeshColorBall[3]);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(COLORFIELD_NAME004,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[4],
		NULL,
		&g_nNumMatColorBall[4],
		&g_pMeshColorBall[4]);



	D3DXVECTOR3 vtx[MAX_MODEL];
	
	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{//���f���̏�����
		g_aColorBall[nCntColorBall].nType = 0;
		g_aColorBall[nCntColorBall].bUse = false;
		g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
		g_aColorBall[nCntColorBall].CntState = COUNTERSTATE_CHANGE;
		g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;
		g_aColorBall[nCntColorBall].nStateCounter = 0;
		g_aColorBall[nCntColorBall].nFrameCounter = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[2]);
}

//=============================================================================
// �I������
//=============================================================================
void UninitColorBall(void)
{
	for (int nCntColorBall = 0; nCntColorBall < MAX_COLORFIELD_TYPE; nCntColorBall++)
	{
		// ���b�V���̊J��
		if (g_pMeshColorBall[nCntColorBall] != NULL)
		{
			g_pMeshColorBall[nCntColorBall]->Release();
			g_pMeshColorBall[nCntColorBall] = NULL;
		}
		// �}�e���A���̊J��
		if (g_pBuffMatColorBall[nCntColorBall] != NULL)
		{
			g_pBuffMatColorBall[nCntColorBall]->Release();
			g_pBuffMatColorBall[nCntColorBall] = NULL;
		}
		//�e�N�X�`���̔j��
		if (g_pTextureColorBall[nCntColorBall] != NULL)
		{
			g_pTextureColorBall[nCntColorBall]->Release();
			g_pTextureColorBall[nCntColorBall] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateColorBall(void)
{
	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == true)	//���f�����g�p����Ă���
		{
			if (g_aColorBall[nCntColorBall].state == COLORBALLSTATE_STOP)
			{
				g_aColorBall[nCntColorBall].nStateCounter++;
			}

			if (g_aColorBall[nCntColorBall].nStateCounter > MOVE_OK_TIMER)
			{
				g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
			}

			if (g_aColorBall[nCntColorBall].nTimerChange < 0)
			{	//��莞�Ԍo�ߌ�Ƀ����_���ŐF������
				g_aColorBall[nCntColorBall].nType = rand() % MAX_COLORFIELD_TYPE;
				g_aColorBall[nCntColorBall].state = COLORBALLSTATE_STOP;
				g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;
				g_aColorBall[nCntColorBall].nStateCounter = 0;
			}
			
			if (g_aColorBall[nCntColorBall].state == COLORBALLSTATE_CHANGE)
			{	//�����ς���
				//�t���[���̃J�E���^�[
				g_aColorBall[nCntColorBall].nFrameCounter++;
				//�~�߂邽�߂̃J�E���^�[
				g_aColorBall[nCntColorBall].nTimerChange--;
				if(g_aColorBall[nCntColorBall].nFrameCounter > CHANGE_FRAME)
				{	//10�t���[���Ɉ��ς���
					g_aColorBall[nCntColorBall].nFrameCounter = 0;
					g_aColorBall[nCntColorBall].nType++;
					PlaySound(SOUND_LABEL_SE004);
					if (g_aColorBall[nCntColorBall].nType > MAX_COLORFIELD_TYPE - 1)
					{	//��������0�ɖ߂�
						g_aColorBall[nCntColorBall].nType = 0;
					}
				}				
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawColorBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == true)	//���f�����g�p����Ă���
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aColorBall[nCntColorBall].mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aColorBall[nCntColorBall].rot.y, g_aColorBall[nCntColorBall].rot.x, g_aColorBall[nCntColorBall].rot.z);
			D3DXMatrixMultiply(&g_aColorBall[nCntColorBall].mtxWorld, &g_aColorBall[nCntColorBall].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aColorBall[nCntColorBall].pos.x, g_aColorBall[nCntColorBall].pos.y, g_aColorBall[nCntColorBall].pos.z);
			D3DXMatrixMultiply(&g_aColorBall[nCntColorBall].mtxWorld, &g_aColorBall[nCntColorBall].mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aColorBall[nCntColorBall].mtxWorld);
			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatColorBall[g_aColorBall[nCntColorBall].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatColorBall[g_aColorBall[nCntColorBall].nType]; nCntMat++)
			{	// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`��
				pDevice->SetTexture(0, g_pTextureColorBall[0]);
				// ���f��(�p�[�c)�̕`��
				g_pMeshColorBall[g_aColorBall[nCntColorBall].nType]->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
COLORBALL *GetColorBall(void)
{
	return &g_aColorBall[0];
}

//=============================================================================
// �J���[�t�B���h�̐ݒ菈��
//=============================================================================
void SetColorBall(D3DXVECTOR3 pos, int nType)
{

	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			g_aColorBall[nCntColorBall].pos = pos;
			g_aColorBall[nCntColorBall].rot = D3DXVECTOR3(0, 0, 0);
			g_aColorBall[nCntColorBall].nType = nType;
			g_aColorBall[nCntColorBall].bUse = true;
			g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
			g_aColorBall[nCntColorBall].CntState = COUNTERSTATE_CHANGE;
			g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;	
			g_aColorBall[nCntColorBall].nStateCounter = 0;
			g_aColorBall[nCntColorBall].nFrameCounter = 0;
			break;
		}
	}
}