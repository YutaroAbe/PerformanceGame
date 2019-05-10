//=============================================================================
//
// ���f������ [model.cpp]
// Author : ���{��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall�˔j
#include <stdio.h>						//�C���N���h�t�@�C��
#include "object.h"						//���f��
#include "camera.h"						//�J����
#include "input.h"						//�L�[�{�[�h
#include "shadow.h"
#include "bullet.h"
#include "meshField.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MODEL_TYPE		(OBJECT_TYPE_MAX)		//���f���̎��
#define	MAX_MODEL_INFO		(257)		//���f���̐�
#define	MAX_MODEL_PARE		(16)		//���f���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJECT_DRAW		g_Object_Draw[MAX_MODEL_TYPE];		//���f���̎��
OBJECT_INFO		g_Object_Info[MAX_MODEL_INFO];		//���f�����
int				g_nMax_Object;						//���f���̐��擾�p
MAP_CHANGE		g_Map_Change[MAX_MAP_CHANGE];		//�}�b�v�؂�ւ��̏o�����
LOAD_MAP		g_Load_Map;							//�}�b�v�؂�ւ��Ǘ�
													//=============================================================================
													// ����������
													//=============================================================================
void InitObject(void)
{
	FILE *pFile;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pFile = fopen("data/Object.txt", "r");

	if (pFile != NULL)//Load
	{//����
		fscanf(pFile, "%d", &g_nMax_Object);//�t�@�C����
		for (int nCountData = 0; nCountData < OBJECT_TYPE_MAX; nCountData++)
		{// X�t�@�C���̓ǂݍ���
			fscanf(pFile, "%s", &g_Object_Draw[nCountData].aText[0]);//�t�@�C����
			fscanf(pFile, "%f %f", &g_Object_Draw[nCountData].SlengthX, &g_Object_Draw[nCountData].SlengthZ);//�t�@�C����
		}
		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "", "", MB_OK);
	}

	int nCountData;

	for (nCountData = 0; nCountData < MAX_MODEL_INFO; nCountData++)
	{//���f����񏉊���
		g_Object_Info[nCountData].bUse = false;
	}

	g_Load_Map.nMapNumber = MAP_TYPE_EMPTY;	//�}�b�v�؂�ւ�����
	g_Load_Map.Export = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (nCountData = 0; nCountData < MAX_MAP_CHANGE; nCountData++)
	{//���f����񏉊���
		g_Map_Change[nCountData].bUse = false;
	}

	//SetModel(D3DXVECTOR3(-20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_TYPE_CAR002, 0, MODEL_USE_OBJECT);
	//SetModel(D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_TYPE_CAR000, 0, MODEL_USE_PLAYER);
	//SetModel(D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_TYPE_AIRPORT000, 0, MODEL_USE_OBJECT);

}

//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	BreakObject(-2);

	for (int nCount = 0; nCount < g_nMax_Object; nCount++)
	{
		// ���b�V���̊J��
		if (g_Object_Draw[nCount].MeshObject != NULL)
		{
			g_Object_Draw[nCount].MeshObject->Release();
			g_Object_Draw[nCount].MeshObject = NULL;
		}

		// �}�e���A���̊J��
		if (g_Object_Draw[nCount].pBuffMatObject != NULL)
		{
			g_Object_Draw[nCount].pBuffMatObject->Release();
			g_Object_Draw[nCount].pBuffMatObject = NULL;
		}

		// �e�N�X�`���̊J��
		if (g_Object_Draw[nCount].pTextureObject != NULL)
		{
			g_Object_Draw[nCount].pTextureObject->Release();
			g_Object_Draw[nCount].pTextureObject = NULL;
		}
	}
}

//=============================================================================
// ���f�����[�h����
//=============================================================================
void LoadObject(int type)
{
	int nLength = (int)strlen(&g_Object_Draw[type].aText[0]);		//�������m�F

	if (nLength > 4)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

		D3DXLoadMeshFromX(&g_Object_Draw[type].aText[0],
			D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Object_Draw[type].pBuffMatObject, NULL, &g_Object_Draw[type].nNumMatObject, &g_Object_Draw[type].MeshObject);

		pMat = (D3DXMATERIAL*)g_Object_Draw[type].pBuffMatObject->GetBufferPointer();
		D3DXCreateTextureFromFile(pDevice, pMat[0].pTextureFilename, &g_Object_Draw[type].pTextureObject);

		strcpy(&g_Object_Draw[type].aText[0], "");
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{
	int nCount;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_Object_Info[nCount].bUse == true && g_Object_Info[nCount].state != OBJECT_STATE_NONE)
		{
			g_Object_Info[nCount].nCntState--;
			if (g_Object_Info[nCount].nCntState < 0)
			{
				g_Object_Info[nCount].nCntState = 0;
				switch (g_Object_Info[nCount].state)
				{
				case OBJECT_STATE_SWAYING:
					g_Object_Info[nCount].pos = g_Object_Info[nCount].InitPos;
					break;
				case OBJECT_STATE_SPIN:
					g_Object_Info[nCount].nCntState = 99999;
					break;
				}
			}

			if (g_Object_Info[nCount].nCntState != 0)
			{
				switch (g_Object_Info[nCount].state)
				{
				case OBJECT_STATE_SWAYING:
					g_Object_Info[nCount].pos.x = g_Object_Info[nCount].InitPos.x
						+ (g_Object_Info[nCount].nCntState % 2) * 20.0f - 10.0f;
					break;
				case OBJECT_STATE_SPIN:
					g_Object_Info[nCount].rot.y += D3DX_PI * 0.01f;
					SettingShadow(g_Object_Info[nCount].pos, g_Object_Info[nCount].rot, g_Object_Info[nCount].length.x, g_Object_Info[nCount].length.z, g_Object_Info[nCount].nCntShadow);
					break;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	int nCount;

	//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ𖳌��ɂ���)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);//REF = Reference:�Q��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_Object_Info[nCount].bUse == true)
		{//�g�p���Ȃ�
			if (g_Object_Info[nCount].use != OBJECT_USE_NO && g_Object_Info[nCount].use != OBJECT_USE_MAP)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Object_Info[nCount].mtxWorldObject);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object_Info[nCount].rot.y, g_Object_Info[nCount].rot.x, g_Object_Info[nCount].rot.z);
				D3DXMatrixMultiply(&g_Object_Info[nCount].mtxWorldObject, &g_Object_Info[nCount].mtxWorldObject, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Object_Info[nCount].pos.x, g_Object_Info[nCount].pos.y, g_Object_Info[nCount].pos.z);
				D3DXMatrixMultiply(&g_Object_Info[nCount].mtxWorldObject, &g_Object_Info[nCount].mtxWorldObject, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Object_Info[nCount].mtxWorldObject);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_Object_Draw[g_Object_Info[nCount].type].pBuffMatObject->GetBufferPointer();

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Object_Draw[g_Object_Info[nCount].type].pTextureObject);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				for (int nCountData = 0; nCountData < (int)g_Object_Draw[g_Object_Info[nCount].type].nNumMatObject; nCountData++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCountData].MatD3D);

					// ���f��(�p�[�c)�̕`��
					g_Object_Draw[g_Object_Info[nCount].type].MeshObject->DrawSubset(nCountData);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}
		}
	}
	//�؂����߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject_MAP(int nMode)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	int nCount;
	OBJECT_TYPE type0 = OBJECT_TYPE_MAX, type1 = OBJECT_TYPE_MAX;
	if (nMode == 0) { type0 = OBJECT_TYPE_999_PARROW; }
	else
	{
		type0 = OBJECT_TYPE_999_PARROWS;
		type1 = OBJECT_TYPE_999_EARROWS;
	}

	//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ𖳌��ɂ���)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);//REF = Reference:�Q��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_Object_Info[nCount].bUse == true)
		{//�g�p���Ȃ�
			if (g_Object_Info[nCount].use != OBJECT_USE_NO && g_Object_Info[nCount].type != type0 && g_Object_Info[nCount].type != type1)
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Object_Info[nCount].mtxWorldObject);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object_Info[nCount].rot.y, g_Object_Info[nCount].rot.x, g_Object_Info[nCount].rot.z);
				D3DXMatrixMultiply(&g_Object_Info[nCount].mtxWorldObject, &g_Object_Info[nCount].mtxWorldObject, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Object_Info[nCount].pos.x, g_Object_Info[nCount].pos.y, g_Object_Info[nCount].pos.z);
				D3DXMatrixMultiply(&g_Object_Info[nCount].mtxWorldObject, &g_Object_Info[nCount].mtxWorldObject, &mtxTrans);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Object_Info[nCount].mtxWorldObject);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_Object_Draw[g_Object_Info[nCount].type].pBuffMatObject->GetBufferPointer();

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Object_Draw[g_Object_Info[nCount].type].pTextureObject);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				for (int nCountData = 0; nCountData < (int)g_Object_Draw[g_Object_Info[nCount].type].nNumMatObject; nCountData++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCountData].MatD3D);

					// ���f��(�p�[�c)�̕`��
					g_Object_Draw[g_Object_Info[nCount].type].MeshObject->DrawSubset(nCountData);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}
		}
	}
	//�؂����߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
int SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type, OBJECT_USE use, D3DXVECTOR3 length, int nShadow)
{
	int nCount;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_Object_Info[nCount].bUse == false)
		{//�g�p���Ă��Ȃ��Ȃ�
			g_Object_Info[nCount].bUse = true;
			g_Object_Info[nCount].pos = pos;
			g_Object_Info[nCount].rot = rot;
			g_Object_Info[nCount].type = type;
			g_Object_Info[nCount].use = use;
			g_Object_Info[nCount].length = length;
			g_Object_Info[nCount].state = OBJECT_STATE_NONE;

			g_Object_Info[nCount].nCntShadow = SetShadow(pos, rot, length.x, length.z, length.y, nShadow);
			LoadObject(type);

			if (use > OBJECT_USE_ITEM)
			{//�A�C�e���̏ꍇ
				g_Object_Info[nCount].state = OBJECT_STATE_SPIN;
			}

			break;
		}
	}
	return nCount;
}
//=============================================================================
// * �}�b�v�o������Z�b�g����
//=============================================================================
void SettingObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumber)
{
	g_Object_Info[nNumber].pos = pos;
	g_Object_Info[nNumber].rot = rot;
}
//=============================================================================
// * ���f���j�󏈗�
//=============================================================================
void BreakObject(int nMode)
{
	if (nMode > -1)
	{
		g_Object_Info[nMode].bUse = false;
	}
	else if (nMode == -1)
	{
		for (int nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
		{//�p�ӂ������f���g�����
			if (g_Object_Info[nCount].use != OBJECT_USE_MAP)
			{
				g_Object_Info[nCount].bUse = false;
			}
		}
	}
	else
	{
		for (int nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
		{//�p�ӂ������f���g�����
			g_Object_Info[nCount].bUse = false;
		}
	}

}
//=============================================================================
// * �G�o���n�Z�b�g����
//=============================================================================
void SetEnemy_Appear(D3DXVECTOR3 Entrance, int nLengthX, int nLengthZ, int nNumber)
{
	ENEMY_APPEAR *g_Enemy_Appear = GetEnemy_Appear();
	for (int nCntAppear = 0; nCntAppear < MAX_ENEMY_APPEAR; nCntAppear++)
	{
		if (g_Enemy_Appear[nCntAppear].bUse == false)
		{
			g_Enemy_Appear[nCntAppear].Entrance = Entrance;
			g_Enemy_Appear[nCntAppear].nLengthX = nLengthX;
			g_Enemy_Appear[nCntAppear].nLengthZ = nLengthZ;
			g_Enemy_Appear[nCntAppear].nNumber = nNumber;
			g_Enemy_Appear[nCntAppear].bUse = true;
			break;
		}
	}
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
void BreakAppear(void)
{
	ENEMY_APPEAR *g_Enemy_Appear = GetEnemy_Appear();

	for (int nCount = 0; nCount < MAX_ENEMY_APPEAR; nCount++)
	{//�p�ӂ������f���g�����
		g_Enemy_Appear[nCount].bUse = false;
	}
}
//=============================================================================
// * �G�o���n�Z�b�g����
//=============================================================================
void Enemy_Appear(D3DXVECTOR3 Entrance, int nNumber)
{
	PLAYER *pPlayer = GetPlayer();
	CHAR_DATA *data = GetChar_Data();
	MODEL_SETTING set;
	switch (nNumber)
	{
	case 0:
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		//SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);

		break;

	case 1:
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;

	case 2:
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		break;
	case 3:
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(200.0f, 500.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(-200.0f, 500.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		break;
	case 4:
		Set_E_KING(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[4], 20.0f, 85.0f);
		break;
	case 5: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		break;
	case 6:
		SetRunningman(&set, MODEL_TYPE_RUN_Sword0);
		SetModel(Entrance + D3DXVECTOR3(0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_B, &set, &data[6], 20.0f, 85.0f);
		break;

	case 100: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		break;
	case 101: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;

	case 200: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		break;
	case 201: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		break;
	case 202: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[3], 20.0f, 85.0f);
		break;
	case 203: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(600.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-600.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[2], 20.0f, 85.0f);
		break;
	case 204: Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[5], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[6], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[5], 20.0f, 85.0f);
		break;

	case 310:
		Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(600.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-600.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);

		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(600.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-600.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		BreakMap_Change();	//�}�b�v�o������폜
		BreakPolygon(-2);
		pPlayer[0].bTarget = false;
		SetScene(SCENE_TYPE_TBOSS);
		break;

	case 300:Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(-500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[4], 20.0f, 85.0f);
		break;

	case 301:Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(-500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_S, &set, &data[4], 20.0f, 85.0f);
		break;
	case 302:Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(-500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_S, &set, &data[4], 20.0f, 85.0f);
		break;
	case 303:Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;
	case 304:Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[1], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(-600.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[4], 20.0f, 85.0f);
		Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(-1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(1500.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(3300.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;
	case 305:Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[1], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;
	case 306:Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[1], 20.0f, 85.0f);
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[1], 20.0f, 85.0f);
		break;

	case 350: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_S, &set, &data[5], 20.0f, 85.0f);
		break;
	case 351: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_S, &set, &data[5], 20.0f, 85.0f);
		break;
	case 352: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[0], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[5], 20.0f, 85.0f);
		break;
	case 353: Set_E_WARRIOR(&set);
		SetModel(Entrance + D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_S, &set, &data[6], 20.0f, 85.0f);
		Set_E_WIZARD(&set);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_ZE, &set, &data[6], 20.0f, 85.0f);
		Set_E_NINJA(&set);
		SetModel(Entrance + D3DXVECTOR3(-300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[5], 20.0f, 85.0f);
		break;
	case 354: Set_E_SOLDIERS(&set);
		SetModel(Entrance + D3DXVECTOR3(500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-500.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(250.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(-250.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		SetModel(Entrance + D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_Z, &set, &data[3], 20.0f, 85.0f);
		break;
	}
}
//=============================================================================
// * �}�b�v�o������Z�b�g����
//=============================================================================
void SetMap_Change(D3DXVECTOR3 Entrance, D3DXVECTOR3 Export, int nLengthX, int nLengthZ, MAP_TYPE MapNumber)
{
	for (int nCntMap = 0; nCntMap < MAX_MAP_CHANGE; nCntMap++)
	{
		if (g_Map_Change[nCntMap].bUse == false)
		{
			PLAYER *pPlayer = GetPlayer();

			g_Map_Change[nCntMap].Entrance = Entrance;
			g_Map_Change[nCntMap].Export = Export;
			g_Map_Change[nCntMap].nLengthX = nLengthX;
			g_Map_Change[nCntMap].nLengthZ = nLengthZ;
			g_Map_Change[nCntMap].MapNumber = MapNumber;
			g_Map_Change[nCntMap].bUse = true;

			//�ڕW�̏ꏊ��ݒ�
			pPlayer[0].bTarget = true;
			pPlayer[0].target = Entrance;
			//�ڈ��ݒ�
			SetPolygon(Entrance, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR{ 1.0f, 0.1f, 0.0f , 1.0f }, nLengthX * 1.0f, nLengthZ * 1.0f, 0);
			break;
		}
	}
}
//=============================================================================
// * �}�b�v�o������Z�b�g����
//=============================================================================
void BreakMap_Change(void)
{
	for (int nCntMap = 0; nCntMap < MAX_MAP_CHANGE; nCntMap++)
	{
		g_Map_Change[nCntMap].bUse = false;
	}
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
void UpdateMap_Change(int nCntModel, int nMode)
{
	int *pTime = GetTime();

	if (g_Load_Map.nMapNumber != MAP_TYPE_EMPTY)
	{//�}�b�v�؂�ւ����
		pTime[0]++;
		if (pTime[0] > 20 || nMode != 0)
		{//��ʂ��Â��Ȃ���
			Camera *pCamera = GetCamera();
			MODEL_INFO *pModel_Info = GetModel_Info();
			PLAYER *pPlayer = GetPlayer();
			float fRot = 0.0f;
			int nCntObj;

			BreakModel(1);		//�G�S�폜
			BreakObject(-1);		//�}�b�v���S�폜
			BreakMap_Change();	//�}�b�v�o������폜
			BreakMeshField();
			BreakMeshWall();
			BreakAppear();
			BreakZWindow();
			BreakEnemy();
			BreakBGWindow();
			BreakShadow(-2);
			BreakPolygon(-2);
			pPlayer[0].bTarget = false;

			if (nCntModel > -1)
			{//�Q�[�����Ȃ� ��ʂ𖾂邭����
			 //�v���C���[��ʏ��Ԃ�
				pModel_Info[nCntModel].set.state = MODEL_STATE_NONE;
				pModel_Info[nCntModel].set.Initpos = g_Load_Map.Export;
				pModel_Info[nCntModel].set.pos = g_Load_Map.Export;
				pModel_Info[nCntModel].set.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pModel_Info[nCntModel].set.posold = g_Load_Map.Export;
				pModel_Info[nCntModel].set.posold.y += 100.0f;
				pModel_Info[nCntModel].set.fPos = g_Load_Map.Export.y;
				pModel_Info[nCntModel].set.bJump = true;
				pModel_Info[nCntModel].set.nNumMotion[3] = -1;
				pModel_Info[nCntModel].set.nNumMotion[2] = 0;
				pModel_Info[nCntModel].set.nNumMotion[1] = 0;
				BreakFadeWindow();
				SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.0f,0.0f,0.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEOUT, WINDOWUSE_NORMAL);
				//�X�^�~�i�Q�[�W
				pPlayer[0].nCntStamina[0] = SetZWindow(D3DXVECTOR3(9999.9f, 9999.9f, 9999.9f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 50.0f, 1.0f, 0, 0, WINDOWSTATE_MAXSTAMINAGAGE, 0.0f);
				pPlayer[0].nCntStamina[1] = SetZWindow(D3DXVECTOR3(9999.9f, 9999.9f, 9999.9f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50.0f, 1.0f, 0, 0, WINDOWSTATE_STAMINAGAGE, 0.0f);
				pPlayer[0].nTime[0] += 1200;
			}
			ResetCamera();

			//�}�b�v������
			pPlayer[0].maptype = g_Load_Map.nMapNumber;
			switch (g_Load_Map.nMapNumber)
			{//�ԍ��ɉ������}�b�v�؂�ւ�
			case MAP_TYPE_000_CHAR_MAKE:
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_000_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(2000.0f, 1.0f, 2000.0f), 2);
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_000_FLOOR, OBJECT_USE_NO, D3DXVECTOR3(1000.0f, 10000.0f, 1.0f), 2);
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_000_FLOOR, OBJECT_USE_NO, D3DXVECTOR3(1000.0f, 10000.0f, 1.0f), 2);
				SetObject(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_000_FLOOR, OBJECT_USE_NO, D3DXVECTOR3(1.0f, 10000.0f, 1000.0f), 2);
				SetObject(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_000_FLOOR, OBJECT_USE_NO, D3DXVECTOR3(1.0f, 10000.0f, 1000.0f), 2);

				InitMeshField(NULL);
				break;

			case MAP_TYPE_100_YEUNG:	//�X
				InitMeshField(NULL);
				InitChar_Data(1);
				CorrectionChar_Data();

				SetObject(D3DXVECTOR3(1000.0f, -200.0f, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_CROSS, OBJECT_USE_BLOCK, D3DXVECTOR3(40.0f, 300.0f, 2100.0f), 2);
				SetObject(D3DXVECTOR3(-1000.0f, -200.0f, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), OBJECT_TYPE_100_CROSS, OBJECT_USE_BLOCK, D3DXVECTOR3(40.0f, 300.0f, 2100.0f), 2);
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), OBJECT_TYPE_100_FLOOR_L, OBJECT_USE_BLOCK, D3DXVECTOR3(1000.0f, 1000.0f, 900.0f), 2);
				for (nCntObj = 0; nCntObj < 10; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(580.0f, 0.0f, 3000.0f - (500 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);
					SetObject(D3DXVECTOR3(780.0f, 0.0f, 2800.0f - (500 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);
					SetObject(D3DXVECTOR3(-580.0f, 0.0f, 3000.0f - (500 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);
					SetObject(D3DXVECTOR3(-780.0f, 0.0f, 2800.0f - (500 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);
				}
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -2200.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_GATE, OBJECT_USE_BLOCK, D3DXVECTOR3(1000.0f, 300.0f, 100.0f), 2);
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(1000.0f, 1.0f, 2200.0f), 2);
				SetObject(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_FENCE, OBJECT_USE_BLOCK, D3DXVECTOR3(40.0f, 300.0f, 2100.0f), 2);
				SetObject(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_100_FENCE, OBJECT_USE_BLOCK, D3DXVECTOR3(40.0f, 300.0f, 2100.0f), 2);
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 3450.0f), D3DXVECTOR3(D3DX_PI*-0.4f, D3DX_PI, 0.0f), OBJECT_TYPE_100_BACK, OBJECT_USE_BLOCK, D3DXVECTOR3(1000.0f, 300.0f, 100.0f), 2);

				//�G
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, 500.0f), 1000, 1000, 100);
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, -1200.0f), 1000, 1000, 101);

				//�A�C�e��
				SetObject(D3DXVECTOR3(0.0f, 30.0f, -1800.0f), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword0, OBJECT_USE_ITEM_GIFT0, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);

				//�}�b�v�؂�ւ�
				SetMap_Change(D3DXVECTOR3(0.0f, 0.0f, -2200.0f), D3DXVECTOR3(0.0f, 0.0f, 2200.0f), 300, 150, MAP_TYPE_200_CITY);
				break;

			case MAP_TYPE_200_CITY:	//�鉺��
				InitMeshField(NULL);
				InitChar_Data(4);
				CorrectionChar_Data();

				SetObject(D3DXVECTOR3(0.0f, 0.0f, 2800.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), OBJECT_TYPE_200_GATE, OBJECT_USE_BLOCK, D3DXVECTOR3(8000.0f, 2000.0f, 80.0f), 2);//��
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_HUNSUI, OBJECT_USE_BLOCK, D3DXVECTOR3(250.0f, 2000.0f, 250.0f), 2);//����
				for (nCntObj = 0; nCntObj < 20; nCntObj++)//��
				{
					for (int nCntObjY = 0; nCntObjY < 5; nCntObjY++)
					{
						SetObject(D3DXVECTOR3(-1300.0f - (250 * nCntObjY), 0.0f, 1600.0f - (nCntObj * 150)), D3DXVECTOR3(0.0f, D3DX_PI + (nCntObj * 2), 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 300.0f, 80.0f), 2);//�؁�

					}
				}
#if 1//����@��
				for (nCntObj = 0; nCntObj < 6; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, 2600.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 6; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, 2300.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 6; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, 2000.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 4; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, 1700.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 4; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, 1400.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 3; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, -300.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 3; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, -600.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 6; nCntObj++)//��
				{
					for (int nC = 0; nC < 3; nC++)//��
					{
						SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, (-900.0f - (nC * 300)) - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
					}
				}
				for (nCntObj = 0; nCntObj < 4; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, -1800.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 3; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, -2100.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 3; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3100.0f - (400.0f*nCntObj), 0.0f, -2400.0f - (150.0f*nCntObj)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
#endif
				for (nCntObj = 0; nCntObj < 8; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3100.0f + (300.0f*nCntObj), 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 8; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(-3300.0f + (300.0f*nCntObj), 0.0f, -2650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}

				for (nCntObj = 0; nCntObj < 14; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(800.0f + (300.0f*nCntObj), 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 14; nCntObj++)//��
				{

					SetObject(D3DXVECTOR3(900.0f + (300.0f*nCntObj), 0.0f, -2650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_100_WOOD, OBJECT_USE_BLOCK, D3DXVECTOR3(100.0f, 2000.0f, 100.0f), 2);//��
				}

				SetObject(D3DXVECTOR3(-4950.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_200_CHURCH, OBJECT_USE_BLOCK, D3DXVECTOR3(1400.0f, 5000.0f, 250.0f), 2);//����
				SetObject(D3DXVECTOR3(-3300.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_200_IDO, OBJECT_USE_BLOCK, D3DXVECTOR3(180.0f, 300.0f, 80.0f), 2);//��ˁ�
																																											  //����
				SetObject(D3DXVECTOR3(3000.0f, 0.0f, 1200.0f), D3DXVECTOR3(0.0f, -D3DX_PI / -2, 0.0f), OBJECT_TYPE_200_HOME1, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 5000.0f, 400.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(3800.0f, 0.0f, 1200.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), OBJECT_TYPE_200_HOME1, OBJECT_USE_BLOCK, D3DXVECTOR3(400.0f, 5000.0f, 250.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(3000.0f, 0.0f, -750.0f), D3DXVECTOR3(0.0f, -D3DX_PI / -2, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 5000.0f, 400.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(3800.0f, 0.0f, -750.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), OBJECT_TYPE_200_HOME1, OBJECT_USE_BLOCK, D3DXVECTOR3(400.0f, 5000.0f, 250.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(1400.0f, 0.0f, 1300.0f), D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(400.0f, 5000.0f, 250.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(1700.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), OBJECT_TYPE_200_HOME1, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 5000.0f, 400.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 5000.0f, 400.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(1100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / -2, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(250.0f, 5000.0f, 400.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(3400.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(400.0f, 5000.0f, 250.0f), 2);//�ƂP
				SetObject(D3DXVECTOR3(3400.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_200_HOME2, OBJECT_USE_BLOCK, D3DXVECTOR3(400.0f, 5000.0f, 250.0f), 2);//�ƂP


				SetObject(D3DXVECTOR3(3050.0f, 0.0f, -2350.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_100_FENCE, OBJECT_USE_BLOCK, D3DXVECTOR3(2300.0f, 5000.0f, 40.0f), 2);//��
				SetObject(D3DXVECTOR3(-3050.0f, 0.0f, -2350.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_100_FENCE, OBJECT_USE_BLOCK, D3DXVECTOR3(2300.0f, 5000.0f, 40.0f), 2);//��
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), OBJECT_TYPE_200_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(4000.0f, 1.0f, 7600.0f), 2);//���i�t�B�[���h�j
				SetObject(D3DXVECTOR3(6500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 2, 0.0f), OBJECT_TYPE_200_SIDE_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(2800.0f, 5000.0f, 4000.0f), 2);//���i�t�B�[���h�j
				SetObject(D3DXVECTOR3(-6500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_SIDE_FLOOR2, OBJECT_USE_BLOCK, D3DXVECTOR3(2800.0f, 5000.0f, 4000.0f), 2);//���i�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, -239.0f, -5050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_200_BRIDGE, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//��
				SetObject(D3DXVECTOR3(1050.0f, -20.0f, -5250.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_CHAIN, OBJECT_USE_BLOCK, D3DXVECTOR3(60.0f, 2000.0f, 2600.0f), 2);//����
				SetObject(D3DXVECTOR3(-1050.0f, -20.0f, -5250.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_CHAIN, OBJECT_USE_BLOCK, D3DXVECTOR3(60.0f, 2000.0f, 2600.0f), 2);//����

				SetObject(D3DXVECTOR3(0.0f, -85.0f, -7500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_200_BABYLON, OBJECT_USE_BLOCK, D3DXVECTOR3(5000.0f, 1781.0f, 450.0f), 2);//��
				SetObject(D3DXVECTOR3(0.0f, -400.0f, -2800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_200_GAKE, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//��
				SetObject(D3DXVECTOR3(0.0f, -385.0f, -7000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_GAKE, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�R
				SetObject(D3DXVECTOR3(0.0f, 15.0f, -7400.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f), OBJECT_TYPE_200_GAKE, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�R
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_200_DOUZOU, OBJECT_USE_BLOCK, D3DXVECTOR3(200.0f, 200.0f, 250.0f), 2);//�R

																																											   //�G																																						   //�G																																									//�G
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, 1400.0f), 1000, 1000, 200);
				SetEnemy_Appear(D3DXVECTOR3(2500.0f, 300.0f, 600.0f), 1000, 1000, 201);
				SetEnemy_Appear(D3DXVECTOR3(-3000.0f, 300.0f, 0.0f), 1000, 1000, 202);
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, -2000.0f), 1000, 1000, 203);
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, -5000.0f), 1000, 1000, 204);

				//�A�C�e�� 
				SetObject(D3DXVECTOR3(0.0f, 200.0f, 600.0f), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword0, OBJECT_USE_ITEM_GIFT0, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);
				SetObject(D3DXVECTOR3(-2850.0f, 30.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword1, OBJECT_USE_ITEM_GIFT1, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);
				SetObject(D3DXVECTOR3(3350.0f, 30.0f, 800.0), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword2, OBJECT_USE_ITEM_GIFT2, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);

				//�}�b�v�؂�ւ�
				SetMap_Change(D3DXVECTOR3(0.0f, 0.0f, -7000.0f), D3DXVECTOR3(0.0f, 0.0f, 3800.0f), 750, 150, MAP_TYPE_300_CASTLE);

				break;

			case MAP_TYPE_300_CASTLE:		//��1F
				InitMeshField(NULL);
				InitChar_Data(10);
				CorrectionChar_Data();

				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_STAGE, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 1.0f, 14100.0f), 2);//���i�t�B�[���h�j

				SetObject(D3DXVECTOR3(4000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 2000.0f, 14100.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-4000.0f, 0.0f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 2000.0f, 14100.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -13800.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL02, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-400.0f, 0.0f, -12300.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL03, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 2000.0f, 2000.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(400.0f, 0.0f, -12300.0f), D3DXVECTOR3(0.0f, 0.0F, 0.0f), OBJECT_TYPE_300_WALL03, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 2000.0f, 2000.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 8700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL04, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(1700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(3700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(1700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(3700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j

				SetObject(D3DXVECTOR3(-1700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-3700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-1700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-3700.0f, 0.0f, -10700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL05, OBJECT_USE_BLOCK, D3DXVECTOR3(750.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j

				SetObject(D3DXVECTOR3(0.0f, 500.0f, -10700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL04, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 500.0f, -10700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL04, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 2200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_TENJOU, OBJECT_USE_BACK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�V��i�t�B�[���h�j

				SetObject(D3DXVECTOR3(0.0f, 0.0f, -9850.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_KAIDAN, OBJECT_USE_BLOCK, D3DXVECTOR3(1050.0f, 2000.0f, 1000.0f), 2);//�K�i��
				for (nCntObj = 0; nCntObj < 9; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(2300.0f, 0.0f, 5300.0f - (1700 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_HASIRA, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				}
				for (nCntObj = 0; nCntObj < 9; nCntObj++)//��
				{
					SetObject(D3DXVECTOR3(-1700.0f, 0.0f, 5300.0f - (1700 * nCntObj)), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_HASIRA, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				}
				SetObject(D3DXVECTOR3(2900.0f, 0.0f, -12000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_TABLE, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 65.0f, 100.0f), 2);//��
				SetObject(D3DXVECTOR3(2900.0f, 0.0f, -12160.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_CHAIR, OBJECT_USE_BLOCK, D3DXVECTOR3(60.0f, 35.0f, 80.0f), 2);//��
				SetObject(D3DXVECTOR3(2200.0f, 0.0f, -13770.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_BOOK, OBJECT_USE_BLOCK, D3DXVECTOR3(120.0f, 150.0f, 100.0f), 2);//��
				SetObject(D3DXVECTOR3(2000.0f, 0.0f, -13770.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_BOOK, OBJECT_USE_BLOCK, D3DXVECTOR3(120.0f, 150.0f, 100.0f), 2);//��
				SetObject(D3DXVECTOR3(2400.0f, 0.0f, -13770.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_BOOK, OBJECT_USE_BLOCK, D3DXVECTOR3(120.0f, 150.0f, 100.0f), 2);//��
				//�G																																									
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 300.0f, -8050.0f), 10000, 4000, 310);

				SetEnemy_Appear(D3DXVECTOR3(200.0f, 300.0f, 2000.0f), 10000, 1000, 300);
				SetEnemy_Appear(D3DXVECTOR3(200.0f, 300.0f, 500.0f), 10000, 1000, 301);
				SetEnemy_Appear(D3DXVECTOR3(200.0f, 300.0f, -1000.0f), 10000, 1000, 303);
				SetEnemy_Appear(D3DXVECTOR3(200.0f, 300.0f, -3000.0f), 10000, 1000, 304);

				SetEnemy_Appear(D3DXVECTOR3(2500.0f, 300.0f, -11350.0f), 10000, 4000, 305);
				SetEnemy_Appear(D3DXVECTOR3(-2500.0f, 300.0f, -11350.0f), 10000, 4000, 306);
				SetObject(D3DXVECTOR3(3000.0f, 30.0f, -11850.0f), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword0, OBJECT_USE_ITEM_GIFT0, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);
				SetObject(D3DXVECTOR3(-3000.0f, 30.0f, -11850.0f), D3DXVECTOR3(D3DX_PI * 0.15f, 0.0f, 0.0f), OBJECT_TYPE_999_Sword0, OBJECT_USE_ITEM_GIFT0, D3DXVECTOR3(15.0f, 85.0f, 15.0f), 0);

				//�}�b�v�؂�ւ�
				//SetMap_Change(D3DXVECTOR3(0.0f, 0.0f, -8850.0f), D3DXVECTOR3(0.0f, 0.0f, 500.0f), 1000, 80, MAP_TYPE_400_THRONE);
				SetMap_Change(D3DXVECTOR3(0.0f, 0.0f, -8850.0f), D3DXVECTOR3(0.0f, 0.0f, 2700.0f), 1000, 80, MAP_TYPE_301_CASTLE);

				break;

			case MAP_TYPE_301_CASTLE:		//��2F
				InitMeshField("data/MAP/Field.bin");
				InitChar_Data(20);
				CorrectionChar_Data();

				SetObject(D3DXVECTOR3(-5000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_300_WALL06, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 2000.0f, 3500.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(5000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_300_WALL06, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 2000.0f, 3500.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_301_WALL03, OBJECT_USE_BLOCK, D3DXVECTOR3(5000.0f, 2000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j

				SetObject(D3DXVECTOR3(0.0f, 0.0f, -9000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIDAN, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�K�i
				SetObject(D3DXVECTOR3(0.0f, 350.0f, -10175.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIDAN, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�K�i
				SetObject(D3DXVECTOR3(0.0f, 700.0f, -11350.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIDAN, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�K�i
				SetObject(D3DXVECTOR3(0.0f, 850.0f, -11350.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_DOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(999.9f, 99999.0f, 10.0f), 2);//�h�A
				SetMap_Change(D3DXVECTOR3(0.0f, 850.0f, -11350.0f), D3DXVECTOR3(0.0f, 0.0f, 1000.0f), 1000, 150, MAP_TYPE_400_THRONE);

				SetObject(D3DXVECTOR3(-620.0f, 700.0f, -10175.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIDAN, OBJECT_USE_NO, D3DXVECTOR3(160.0f, 99999.0f, 1835.0f), 2);//�K�i
				SetObject(D3DXVECTOR3(620.0f, 700.0f, -10175.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIDAN, OBJECT_USE_NO, D3DXVECTOR3(160.0f, 99999.0f, 1835.0f), 2);//�K�i

				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(5100.0f, 1.0f, 12000.0f), 2);//��
				SetObject(D3DXVECTOR3(-2200.0f, 0.0f, 1420.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL, OBJECT_USE_BLOCK, D3DXVECTOR3(1600.0f, 2000.0f, 900.0f), 2);//��
				SetObject(D3DXVECTOR3(2200.0f, 0.0f, 1420.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL, OBJECT_USE_BLOCK, D3DXVECTOR3(1600.0f, 2000.0f, 900.0f), 2);//��
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL02, OBJECT_USE_BLOCK, D3DXVECTOR3(3800.0f, 2000.0f, 1000.0f), 2);//��
				SetObject(D3DXVECTOR3(-620.0f, 0.0f, -10500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL_K, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 2000.0f, 7000.0f), 2);//��
				SetObject(D3DXVECTOR3(620.0f, 0.0f, -10500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_WALL_K, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 2000.0f, 7000.0f), 2);//��
				SetObject(D3DXVECTOR3(2840.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL_K02, OBJECT_USE_BLOCK, D3DXVECTOR3(2160.0f, 2000.0f, 8.0f), 2);//��
				SetObject(D3DXVECTOR3(-2780.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_301_WALL_K02, OBJECT_USE_BLOCK, D3DXVECTOR3(2160.0f, 2000.0f, 8.0f), 2);//��
				SetObject(D3DXVECTOR3(4990.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_301_KAIGA, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-4990.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_301_KAIGA02, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�G��
				SetObject(D3DXVECTOR3(0.0f, 200.0f, -400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_KAIGA_KENOU, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�G��
																																												 //�b�h
				SetObject(D3DXVECTOR3(600.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-600.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(4920.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(4920.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-4920.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-4920.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(700.0f, 0.0f, -3400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-700.0f, 0.0f, -3400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				for (nCntObj = 0; nCntObj < 6; nCntObj++)
				{
					SetObject(D3DXVECTOR3(550.0f, 0.0f, -3700.0f - (nCntObj * 750)), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
					SetObject(D3DXVECTOR3(-550.0f, 0.0f, -3700.0f - (nCntObj * 750)), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				}
				SetObject(D3DXVECTOR3(0.0f, 3200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_TENJOU, OBJECT_USE_BLOCK, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);//�ǁi�t�B�[���h�j

				SetEnemy_Appear(D3DXVECTOR3(0.0f, 0.0f, 1200.0f), 1000, 1000, 350);
				SetEnemy_Appear(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), 1000, 1000, 351);
				SetEnemy_Appear(D3DXVECTOR3(-3000.0f, 0.0f, 0.0f), 1000, 1000, 352);
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 0.0f, -5000.0f), 1000, 1000, 353);
				SetEnemy_Appear(D3DXVECTOR3(0.0f, 0.0f, -8000.0f), 1000, 1000, 354);
				SetEnemy_Appear(D3DXVECTOR3(3000.0f, 0.0f, -2900.0f), 1000, 1000, 350);
				SetEnemy_Appear(D3DXVECTOR3(-3000.0f, 0.0f, -2900.0f), 1000, 1000, 350);
				SetEnemy_Appear(D3DXVECTOR3(-4300.0f, 0.0f, 2600.0f), 1000, 1000, 351);
				SetEnemy_Appear(D3DXVECTOR3(4300.0f, 0.0f, 2600.0f), 1000, 1000, 352);

				break;

			case MAP_TYPE_400_THRONE:	//�ʍ�
				InitMeshField(NULL);
				InitChar_Data(25);
				CorrectionChar_Data();
				SetScene(SCENE_TYPE_BOSS);

				SetObject(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_FLOOR, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 1.0f, 3600.0f), 2);//���i�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), OBJECT_TYPE_300_WALL04, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 5000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_300_WALL02, OBJECT_USE_BLOCK, D3DXVECTOR3(4100.0f, 5000.0f, 8.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(-4000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), OBJECT_TYPE_300_WALL06, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 5000.0f, 4000.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(4000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), OBJECT_TYPE_300_WALL06, OBJECT_USE_BLOCK, D3DXVECTOR3(8.0f, 5000.0f, 4000.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), MAP_TYPE_400_DAIZA, OBJECT_USE_BLOCK, D3DXVECTOR3(1920.0f, 5000.0f, 1205.0f), 2);//�ǁi�t�B�[���h�j
				SetObject(D3DXVECTOR3(0.0f, 330.0f, -3000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_GYOKUZA, OBJECT_USE_BLOCK, D3DXVECTOR3(300.0f, 5000.0f, 300.0f), 2);//�ǁi�t�B�[���h�j

				SetObject(D3DXVECTOR3(2400.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				SetObject(D3DXVECTOR3(2400.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				SetObject(D3DXVECTOR3(-2400.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				SetObject(D3DXVECTOR3(-2400.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				SetObject(D3DXVECTOR3(-2400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��
				SetObject(D3DXVECTOR3(2400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MAP_TYPE_400_HASIRA02, OBJECT_USE_BLOCK, D3DXVECTOR3(270.0f, 2000.0f, 270.0f), 2);//��

				SetObject(D3DXVECTOR3(450.0f, 350.0f, -3400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				SetObject(D3DXVECTOR3(-450.0f, 350.0f, -3400.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), OBJECT_TYPE_301_YOROI, OBJECT_USE_BLOCK, D3DXVECTOR3(80.0f, 200.0f, 80.0f), 2);//�G��
				break;
			}

			if (nCntModel > -1)
			{
				pModel_Info[nCntModel].set.rot.y = fRot;
				pCamera[0].rot.y = fRot;
			}
			g_Load_Map.nMapNumber = MAP_TYPE_EMPTY;
		}
	}
}
//=============================================================================
// * �����蔻��
//=============================================================================
int CollisionObject(int nCntModel)
{//�I�u�W�F�̓����蔻��

	int nLand = 0;
	MODEL_INFO *pModel = GetModel_Info();
	D3DXVECTOR3 pos = pModel[nCntModel].set.pos;
	float		fMove = pModel[nCntModel].set.move.y;
	bool		bCollision = false;

	for (int nCntObject = 0; nCntObject < MAX_MODEL_INFO; nCntObject++)
	{//�S�I�u�W�F����]
		if (g_Object_Info[nCntObject].bUse == true && g_Object_Info[nCntObject].use != OBJECT_USE_BACK && g_Object_Info[nCntObject].use != OBJECT_USE_BACK0 && g_Object_Info[nCntObject].use != OBJECT_USE_MAP)
		{//�I�u�W�F������
			if (pModel[nCntModel].set.pos.y < g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y)
			{//Y����
				if (pModel[nCntModel].set.posold.y + 10.0f >= g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y)
				{//�O����
					if (pModel[nCntModel].set.pos.x - pModel[nCntModel].set.fSlength <= g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
						pModel[nCntModel].set.pos.x + pModel[nCntModel].set.fSlength >= g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x &&
						pModel[nCntModel].set.pos.z - pModel[nCntModel].set.fSlength <= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
						pModel[nCntModel].set.pos.z + pModel[nCntModel].set.fSlength >= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
					{//XZ�͈͓��Ȃ�
						pos.y = g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y;   //�n�ʔ���
						fMove = 0.0f;
						bCollision = true;
						if (pModel[nCntModel].set.bJump == false) { nLand = 2; }
						else { nLand = 1; }
					}
				}
				else
				{
					if (pModel[nCntModel].set.pos.z - pModel[nCntModel].set.fSlength <= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
						pModel[nCntModel].set.pos.z + pModel[nCntModel].set.fSlength >= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
					{//X���� Z���͈͓�
						if (pModel[nCntModel].set.posold.x + pModel[nCntModel].set.fSlength <= g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x &&
							pModel[nCntModel].set.pos.x + pModel[nCntModel].set.fSlength > g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x)
						{//X���������Ă���Ȃ�
							bCollision = true;
							pos.x = g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x - pModel[nCntModel].set.fSlength;//POS��߂�
						}
						else if (pModel[nCntModel].set.posold.x - pModel[nCntModel].set.fSlength >= g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
							pModel[nCntModel].set.pos.x - pModel[nCntModel].set.fSlength < g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x)
						{//X�E�������Ă���Ȃ�
							bCollision = true;
							pos.x = g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x + pModel[nCntModel].set.fSlength;//POS��߂�
						}
					}
					if (pModel[nCntModel].set.pos.x - pModel[nCntModel].set.fSlength < g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
						pModel[nCntModel].set.pos.x + pModel[nCntModel].set.fSlength > g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x)
					{//Z���� X���͈͓�
						if (pModel[nCntModel].set.posold.z - pModel[nCntModel].set.fSlength >= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
							pModel[nCntModel].set.pos.z - pModel[nCntModel].set.fSlength < g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z)
						{//Z�O�������Ă���Ȃ�
							bCollision = true;
							pos.z = g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z + pModel[nCntModel].set.fSlength;//POS��߂�
						}
						else if (pModel[nCntModel].set.posold.z + pModel[nCntModel].set.fSlength <= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z &&
							pModel[nCntModel].set.pos.z + pModel[nCntModel].set.fSlength > g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
						{//Z��낪�����Ă���Ȃ�
							bCollision = true;
							pos.z = g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z - pModel[nCntModel].set.fSlength;//POS��߂�
						}
					}
				}
			}//Y����

			if (bCollision == true)
			{//��������
				bCollision = false;
				if (g_Object_Info[nCntObject].use > OBJECT_USE_ITEM && pModel[nCntModel].use == MODEL_USE_PLAYER)
				{
					pos = pModel[nCntModel].set.pos;
					fMove = pModel[nCntModel].set.move.y;
					HitItem(nCntModel, nCntObject);
				}
				else
				{
					pModel[nCntModel].set.pos = pos;
					pModel[nCntModel].set.fPos = pos.y;
					pModel[nCntModel].set.move.y = fMove;
				}
			}
		}//�I�u�W�F���݊m�F
	}//for����

	return nLand;
}

//=============================================================================
// * ����ɕύX�����������̉����o���p
//=============================================================================
int CollisionObject_Plus(MODEL_SETTING *set)
{//�ђʂ�h���I

	int nLand = 0;
	D3DXVECTOR3 pos = set[0].pos;
	float		fMove = set[0].move.y;
	bool		bCollision = false;

	for (int nCntObject = 0; nCntObject < MAX_MODEL_INFO; nCntObject++)
	{//�S�I�u�W�F����]
		if (g_Object_Info[nCntObject].bUse == true && g_Object_Info[nCntObject].use != OBJECT_USE_BACK && g_Object_Info[nCntObject].use != OBJECT_USE_BACK0 && g_Object_Info[nCntObject].use != OBJECT_USE_MAP)
		{//�I�u�W�F������
			if (set[0].pos.y < g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y)
			{//Y����
				if (set[0].posold.y + 10.0f >= g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y)
				{//�O����
					if (set[0].pos.x - set[0].fSlength <= g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
						set[0].pos.x + set[0].fSlength >= g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x &&
						set[0].pos.z - set[0].fSlength <= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
						set[0].pos.z + set[0].fSlength >= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
					{//XZ�͈͓��Ȃ�
						pos.y = g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y;   //�n�ʔ���
						fMove = 0.0f;
						bCollision = true;
						if (set[0].bJump == false) { nLand = 2; }
						//else { nLand = 1; }
					}
				}
				else
				{
					if (set[0].pos.z - set[0].fSlength <= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
						set[0].pos.z + set[0].fSlength >= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
					{//X���� Z���͈͓�
						if (set[0].posold.x <= g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x &&
							set[0].pos.x + set[0].fSlength > g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x)
						{//X���������Ă���Ȃ�
							bCollision = true;
							pos.x = g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x - set[0].fSlength;//POS��߂�
						}
						else if (set[0].posold.x >= g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
							set[0].pos.x - set[0].fSlength < g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x)
						{//X�E�������Ă���Ȃ�
							bCollision = true;
							pos.x = g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x + set[0].fSlength;//POS��߂�
						}
					}
					if (set[0].pos.x - set[0].fSlength < g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
						set[0].pos.x + set[0].fSlength > g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x)
					{//Z���� X���͈͓�
						if (set[0].posold.z >= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
							set[0].pos.z - set[0].fSlength < g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z)
						{//Z�O�������Ă���Ȃ�
							bCollision = true;
							pos.z = g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z + set[0].fSlength;//POS��߂�
						}
						else if (set[0].posold.z <= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z &&
							set[0].pos.z + set[0].fSlength > g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
						{//Z��낪�����Ă���Ȃ�
							bCollision = true;
							pos.z = g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z - set[0].fSlength;//POS��߂�
						}
					}
				}
			}//Y����

			if (bCollision == true)
			{//��������
				bCollision = false;
				set[0].pos = pos;
				set[0].move.y = fMove;
			}
		}//�I�u�W�F���݊m�F
	}//for����

	return nLand;
}
//=============================================================================
// * �����蔻��
//=============================================================================
void HitItem(int nCntModel, int nCntObject)
{
	MODEL_INFO *pModel = GetModel_Info();
	CHAR_DATA	dataold = pModel[nCntModel].data;

	if (pModel[nCntModel].use == MODEL_USE_PLAYER)
	{//�v���C���[�������Ȃ�
		PLAYER *pPlayer = GetPlayer();
		float fHeel;

		switch (g_Object_Info[nCntObject].use)
		{
		case OBJECT_USE_ITEM_HEEL0:
			g_Object_Info[nCntObject].bUse = false;
			BreakShadow(g_Object_Info[nCntObject].nCntShadow);
			DropSkill(10);
			pModel[nCntModel].data.plus[0].fLifePoint = 600;
			fHeel = pModel[nCntModel].data.status.fLifePoint * 2.0f;
			pModel[nCntModel].data.plus[1].fLifePoint = pModel[nCntModel].data.status.fLifePoint * 2.0f;
			GetStatus(&pModel[nCntModel].data, true);
			pModel[nCntModel].data.nLifePoint += (int)fHeel;
			SetAnimation(pModel[nCntModel].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 8, 1, 4, 7, 1, ANIMATION_NORMAL);
			break;

		case OBJECT_USE_ITEM_GIFT0:
			PlaySound(SOUND_LABEL_TitleSE001);
			g_Object_Info[nCntObject].bUse = false;
			BreakShadow(g_Object_Info[nCntObject].nCntShadow);

			pModel[nCntModel].data.gifted.fAttack *= 1.1f;
			pModel[nCntModel].data.gifted.fLucky *= 1.1f;
			GetStatus(&pModel[nCntModel].data, true); ShowStatus(dataold, pModel[nCntModel].data);
			break;
		case OBJECT_USE_ITEM_GIFT1:
			PlaySound(SOUND_LABEL_TitleSE001);
			g_Object_Info[nCntObject].bUse = false;
			BreakShadow(g_Object_Info[nCntObject].nCntShadow);

			pModel[nCntModel].data.gifted.fSpeed *= 1.1f;
			pModel[nCntModel].data.gifted.fRes *= 1.1f;
			GetStatus(&pModel[nCntModel].data, true); ShowStatus(dataold, pModel[nCntModel].data);
			break;
		case OBJECT_USE_ITEM_GIFT2:
			PlaySound(SOUND_LABEL_TitleSE001);
			g_Object_Info[nCntObject].bUse = false;
			pModel[nCntModel].data.gifted.fInt *= 1.1f;
			pModel[nCntModel].data.gifted.fDefense *= 1.1f;
			GetStatus(&pModel[nCntModel].data, true); ShowStatus(dataold, pModel[nCntModel].data);
			break;
		}
	}
}

//=============================================================================
// * �e�̓����蔻��
//=============================================================================
void CollisionObjectS(D3DXVECTOR3 *pos)
{//�I�u�W�F�̓����蔻��

	pos[0].y = -9999.9f;

	for (int nCntObject = 0; nCntObject < MAX_MODEL_INFO; nCntObject++)
	{//�S�I�u�W�F����]
		if (g_Object_Info[nCntObject].bUse == true && g_Object_Info[nCntObject].use != OBJECT_USE_BACK  && g_Object_Info[nCntObject].use != OBJECT_USE_MAP
			&& g_Object_Info[nCntObject].use != OBJECT_USE_BACK0 && g_Object_Info[nCntObject].use < OBJECT_USE_ITEM)
		{//�I�u�W�F������
			if (pos[0].y < g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y)
			{//Y����
				if (pos[0].x <= g_Object_Info[nCntObject].pos.x + g_Object_Info[nCntObject].length.x &&
					pos[0].x >= g_Object_Info[nCntObject].pos.x - g_Object_Info[nCntObject].length.x &&
					pos[0].z <= g_Object_Info[nCntObject].pos.z + g_Object_Info[nCntObject].length.z &&
					pos[0].z >= g_Object_Info[nCntObject].pos.z - g_Object_Info[nCntObject].length.z)
				{//XZ�͈͓��Ȃ�
					pos[0].y = g_Object_Info[nCntObject].pos.y + g_Object_Info[nCntObject].length.y;   //�n�ʔ���
				}
			}
		}
	}
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
void SetLoad_Map(D3DXVECTOR3 Export, MAP_TYPE nMapNumber)
{
	g_Load_Map.Export = Export;
	g_Load_Map.nMapNumber = nMapNumber;
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
ENEMY_APPEAR *GetEnemy_Appear(void)
{
	static ENEMY_APPEAR	g_Enemy_Appear[MAX_ENEMY_APPEAR];	//�G�o���Ǘ�

	return &g_Enemy_Appear[0];
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
MAP_CHANGE *GetMap_Change(void)
{
	return &g_Map_Change[0];
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
LOAD_MAP *GetLoad_Map(void)
{
	return &g_Load_Map;
}
//=============================================================================
// * �}�b�v�؂�ւ�����
//=============================================================================
OBJECT_INFO *GetObject(void)
{
	return &g_Object_Info[0];
}
