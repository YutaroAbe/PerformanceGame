//=============================================================================
//
// ���f������ [model.cpp]
// Author : ���{��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall�˔j
#include <stdio.h>						//�C���N���h�t�@�C��
#include <math.h>
#include "model.h"						//���f��
#include "camera.h"						//�J����
//#include "input.h"						//�L�[�{�[�h
#include "meshField.h"
#include "game.h"
#include "object.h"
#include "fade.h"
#include "joypad.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MODEL_TYPE		(MODEL_TYPE_EMPTY)	//���f���̎��
#define	MAX_MODEL_TEX		(15)	//���f���̎��

#define	MAX_MODEL_INFO		(100)	//���f���̐�
#define	MAX_MODEL_CHAR		(8)		//���[�V�����̐�
#define	MAX_MODEL_PARE		(16)	//���f���̐�
#define	MAX_ENEMY_DATA		(16)	//���f���̐�
#define	HIT_HIGHT			(20.0f)	//���f���̐�

#define	MODEL_PMOVE			(0.00005f)//�v���C���[�̈ړ����x �{��
#define	MODEL_SMOVE			(25)//�v���C���[��	�X�^�~�i �{��
#define	MODEL_PMOVE0		(0.75f)	//�v���C���[�̈ړ����x �����l
#define	MODEL_RUN_MOVE		(2.25f)	//�v���C���[�̈ړ����x �����l
#define	INIT_EXP			(50000.0f)	//�����o���l
#define	EXP_UP				(1.1f)	//���̌o���l�̔{��

#define	MOTION_LAND			(3)		//���n���[�V����
#define	MOTION_LANDING		(4)		//�W�����v���[�V����
#define	MOTION_AIR			(5)		//�󒆃��[�V����
#define	MOTION_STEP			(6)		//�X�e�b�v���[�V����
#define	MOTION_STEPS		(7)		//�X�e�b�v���[�V����
#define	MOTION_GUARD		(8)		//�K�[�h���[�V���� �������K�[�h���߂̃L�[�ɖ߂�
#define	MOTION_SHRINK		(9)		//����
#define	MOTION_DOWN			(10)	//�_�E��
#define	MOTION_GETUP		(11)	//���A

#define	MAX_Gifted			(51)		//�˔\�̐U�蕝

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
MODEL_DRAW		g_model_Draw[MAX_MODEL_TYPE];
LPDIRECT3DTEXTURE9	pTextureModel[MAX_MODEL_TEX] = {};	//�e�N�X�`��

MODEL_INFO		g_model_Info[MAX_MODEL_INFO];
MODEL_MOTION	g_model_motion[MAX_MODEL_CHAR][MAX_MODEL_MOTION];

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	FILE *pFile;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char aStr[10][256];		//���f���̖��O�擾�p
	int				nNumMotion;

	BreakModel(0);

	//���[�V�����f�[�^�̏�����
	for (int nCountData = 0; nCountData < MAX_MODEL_MOTION; nCountData++)
	{
		g_model_motion[0][nCountData].nKey = 2;
		g_model_motion[0][nCountData].fFastFrame = 0.0f;
		g_model_motion[0][nCountData].nBranch[0] = 0;
		g_model_motion[0][nCountData].nBranch[1] = 0;
		g_model_motion[0][nCountData].nBranch[2] = 0;
		g_model_motion[0][nCountData].nBranch[3] = MOTION_LAND;
		g_model_motion[0][nCountData].nCancel[0] = 0;
		g_model_motion[0][nCountData].nCancel[1] = 0;
		g_model_motion[0][nCountData].fEndFreame = 0.0f;
		g_model_motion[0][nCountData].fCancelFreame = 0.0f;
		for (int nCountData0 = 0; nCountData0 < MAX_KEY; nCountData0++)
		{
			g_model_motion[0][nCountData].key[nCountData0].nMuse = 1;
			g_model_motion[0][nCountData].key[nCountData0].nAtkFrame[0] = 0;
			g_model_motion[0][nCountData].key[nCountData0].nAtkFrame[1] = 10;
			g_model_motion[0][nCountData].key[nCountData0].nInvincible = 10;
			g_model_motion[0][nCountData].key[nCountData0].nFloating = 0;
			g_model_motion[0][nCountData].key[nCountData0].nAtkEffect = -1;
			g_model_motion[0][nCountData].key[nCountData0].nShowEffect = -1;
			g_model_motion[0][nCountData].key[nCountData0].fAtkplus = 1.0f;
			g_model_motion[0][nCountData].key[nCountData0].blown = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			g_model_motion[0][nCountData].key[nCountData0].fFrame = 40.0f;
			g_model_motion[0][nCountData].key[nCountData0].fRange = 5.0f;
			g_model_motion[0][nCountData].key[nCountData0].fSlip = 1.0f;
			g_model_motion[0][nCountData].key[nCountData0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_model_motion[0][nCountData].key[nCountData0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			for (int nCountData1 = 0; nCountData1 < MAX_PARTS; nCountData1++)
			{
				g_model_motion[0][nCountData].key[nCountData0].rot[MAX_PARTS] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	pFile = fopen("data/model.txt", "r");

	if (pFile != NULL)//Load
	{//����
		for (int nCountData = 0; nCountData < MODEL_TYPE_EMPTY; nCountData++)
		{// X�t�@�C���̓ǂݍ���
			fscanf(pFile, "%s\n", &g_model_Draw[nCountData].aText[0]);//�t�@�C����
			fscanf(pFile, "%d\n", &g_model_Draw[nCountData].nTexture);//�摜�ԍ�
			fscanf(pFile, "%f %f %f", &g_model_Draw[nCountData].addpos.x, &g_model_Draw[nCountData].addpos.y, &g_model_Draw[nCountData].addpos.z);//�ꏊ
			fscanf(pFile, "%f %f %f\n", &g_model_Draw[nCountData].addrot.x, &g_model_Draw[nCountData].addrot.y, &g_model_Draw[nCountData].addrot.z);//�p�x
		}
		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "", "", MB_OK);
	}

	for (int nCountData = 0; nCountData < MAX_MODEL_INFO; nCountData++)
	{//���f����񏉊���
		g_model_Info[nCountData].bUse = false;
		g_model_Info[nCountData].set.nCntChar = -1;
	}

	//���[�V�����̓ǂݍ���----------------------------------------------------------
	int nCntMotion[3];
	int nCountData[3];

	pFile = fopen("data/motion.txt", "r");

	if (pFile != NULL)//Load
	{//����
		fscanf(pFile, "%d", &nCntMotion[0]);//�t�@�C����
		for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
		{
			fscanf(pFile, "%s", &aStr[nCntChar][0]);//�t�@�C����
		}

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "���[�V����", "motion.txt�����I", MB_OK);
	}

	for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
	{
		pFile = fopen(&aStr[nCntChar][0], "r");
		if (pFile != NULL)//Load
		{//���[�V�����t�@�C��Load
			fscanf(pFile, "%d %d\n", &nNumMotion, &nCntMotion[2]);//���[�V������ �p�[�c��
			for (nCountData[0] = 0; nCountData[0] < nNumMotion; nCountData[0]++)
			{//���[�V��������]
				fscanf(pFile, "%d %d %d %d %d %d %d\n", &g_model_motion[nCntChar][nCountData[0]].nKey,
					&g_model_motion[nCntChar][nCountData[0]].nCancel[0],
					&g_model_motion[nCntChar][nCountData[0]].nCancel[1],
					&g_model_motion[nCntChar][nCountData[0]].nBranch[0],
					&g_model_motion[nCntChar][nCountData[0]].nBranch[1],
					&g_model_motion[nCntChar][nCountData[0]].nBranch[2],
					&g_model_motion[nCntChar][nCountData[0]].nBranch[3]);
				fscanf(pFile, "%f %f %f\n\n", &g_model_motion[nCntChar][nCountData[0]].fFastFrame,
					&g_model_motion[nCntChar][nCountData[0]].fEndFreame,
					&g_model_motion[nCntChar][nCountData[0]].fCancelFreame);

				for (nCountData[1] = 0; nCountData[1] < g_model_motion[nCntChar][nCountData[0]].nKey; nCountData[1]++)
				{//�L�[����]
					fscanf(pFile, "%d %d %d %d %d %d %d %d\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nMuse,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nAtkFrame[0],
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nAtkFrame[1],
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nParts,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nInvincible,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nFloating,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nAtkEffect,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].nShowEffect);//���[�V������ �p�[�c��
					fscanf(pFile, "%f %f %f %f\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].fFrame,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].fRange,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].fAtkplus,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].fSlip);
					fscanf(pFile, "%f %f %f\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].blown.x,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].blown.y,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].blown.z);
					fscanf(pFile, "%f %f %f\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].move.x,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].move.y,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].move.z);
					fscanf(pFile, "%f %f %f\n\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].pos.x,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].pos.y,
						&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].pos.z);

					for (nCountData[2] = 0; nCountData[2] < nCntMotion[2]; nCountData[2]++)
					{//�p�[�c����]
						fscanf(pFile, "%f %f %f\n", &g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].rot[nCountData[2]].x,
							&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].rot[nCountData[2]].y,
							&g_model_motion[nCntChar][nCountData[0]].key[nCountData[1]].rot[nCountData[2]].z);
					}
					fscanf(pFile, "\n");
				}

			}
			fclose(pFile);
		}
		else
		{//���s
			MessageBox(0, "���[�V�����f�[�^", "������!?", MB_OK);
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{

	BreakModel(0);

	for (int nCount = 0; nCount < MODEL_TYPE_EMPTY; nCount++)
	{
		// ���b�V���̊J��
		if (g_model_Draw[nCount].MeshModel != NULL)
		{
			g_model_Draw[nCount].MeshModel->Release();
			g_model_Draw[nCount].MeshModel = NULL;
		}

		// �}�e���A���̊J��
		if (g_model_Draw[nCount].pBuffMatModel != NULL)
		{
			g_model_Draw[nCount].pBuffMatModel->Release();
			g_model_Draw[nCount].pBuffMatModel = NULL;
		}
	}

	for (int nCount = 0; nCount < MAX_MODEL_TEX; nCount++)
	{
		// �e�N�X�`���̊J��
		if (pTextureModel[nCount] != NULL)
		{
			pTextureModel[nCount]->Release();
			pTextureModel[nCount] = NULL;
		}
	}
}
//=============================================================================
// ���f�����[�h����
//=============================================================================
void LoadModel(int type)
{
	int nLength = (int)strlen(&g_model_Draw[type].aText[0]);		//�������m�F

	if (nLength > 4)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXLoadMeshFromX(&g_model_Draw[type].aText[0],
			D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_model_Draw[type].pBuffMatModel, NULL, &g_model_Draw[type].nNumMatModel, &g_model_Draw[type].MeshModel);
		strcpy(&g_model_Draw[type].aText[0], "");

		//�e�N�X�`���m�F
		if (pTextureModel[g_model_Draw[type].nTexture] == NULL)
		{//�ǂݍ��܂�Ă��Ȃ�
			D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

			pMat = (D3DXMATERIAL*)g_model_Draw[type].pBuffMatModel->GetBufferPointer();
			D3DXCreateTextureFromFile(pDevice, pMat[0].pTextureFilename, &pTextureModel[g_model_Draw[type].nTexture]);
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	Camera *pCamera = GetCamera();

	D3DXCOLOR col;
	D3DXVECTOR3 SavePos[2];
	ENEMY *pEnemy = GetEnemy();
	int nCount;
	static int nMotion = 0;
	static bool bEnter = false;
	int nField;
	int nMField;
	int nRand;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_model_Info[nCount].bUse == true)
		{
			if (pCamera[0].ViewS != SCENE_VIEW_STOP)
			{
				//�X�L�����Ԍo��
				g_model_Info[nCount].set.nSkillTime[0]--;
				g_model_Info[nCount].set.nSkillTime[1]--;

				//�n�ʂ̂����蔻��̌떂����
				if (g_model_Info[nCount].set.bJump == true)
				{
					g_model_Info[nCount].set.pos.y += (g_model_Info[nCount].set.fPos - g_model_Info[nCount].set.pos.y) * 0.8f;
				}

				g_model_Info[nCount].set.posold = g_model_Info[nCount].set.pos;
				if (g_model_Info[nCount].use == MODEL_USE_PLAYER && pCamera[0].state == CAMERA_STATE_GAME)
				{//�g�p�� && �v���C���[�Ȃ�
					UpdatePlayer(nCount);
				}
				else if (g_model_Info[nCount].use == MODEL_USE_Title)
				{//Title�̃��f��
					g_model_Info[nCount].set.move.y = -10.0f;
					g_model_Info[nCount].set.move.x = -3.0f;
					g_model_Info[nCount].set.pos.z = 0.0f;
					//g_model_Info[nCount].set.rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);
					g_model_Info[nCount].set.nNumMotion[2] = -99;
					if (g_model_Info[nCount].set.pos.y < 0) { g_model_Info[nCount].set.pos.y = 0; }
					if (g_model_Info[nCount].set.pos.x < -225)
					{
						nRand = rand() % 3;
						if (nRand == 0) { g_model_Info[nCount].set.parent[15].type = MODEL_TYPE_RUN_Sword0; }
						else if (nRand == 1) { g_model_Info[nCount].set.parent[15].type = MODEL_TYPE_RUN_Sword1; }
						else { g_model_Info[nCount].set.parent[15].type = MODEL_TYPE_RUN_Sword2; }
						g_model_Info[nCount].set.pos.x = 225;
					}

				}

				//���[�V�����ɂ���ăX�^�~�i����
				g_model_Info[nCount].data.nTimeStamina--;
				if ((g_model_Info[nCount].set.nNumMotion[1] <= 1 && g_model_Info[nCount].data.nTimeStamina < 0) || g_model_Info[nCount].set.nNumMotion[1] == MOTION_DOWN)
				{
					g_model_Info[nCount].data.nStamina += g_model_Info[nCount].data.nMaxStamina / 45;
				}
				else if (g_model_Info[nCount].set.nNumMotion[1] == 2)
				{
					g_model_Info[nCount].data.nStamina--;
					if (g_model_Info[nCount].data.nStamina < -1) { g_model_Info[nCount].data.nStamina = -30; }
				}
				if (g_model_Info[nCount].set.nNumMotion[1] > 1) { g_model_Info[nCount].data.nTimeStamina = 20; }
				if (g_model_Info[nCount].data.nStamina > g_model_Info[nCount].data.nMaxStamina) { g_model_Info[nCount].data.nStamina = g_model_Info[nCount].data.nMaxStamina; }
				if (g_model_Info[nCount].data.nStamina < -30) { g_model_Info[nCount].data.nStamina = -30; }

				g_model_Info[nCount].set.nCntHeel++;
				if (g_model_Info[nCount].set.nCntHeel > 120 && g_model_Info[nCount].data.nLifePoint > 0)
				{//��
					g_model_Info[nCount].set.nCntHeel = 0;
					g_model_Info[nCount].data.nLifePoint += g_model_Info[nCount].data.nLifePoint / 100;
					g_model_Info[nCount].data.nSkillPoint += g_model_Info[nCount].data.nSkillPoint / 30;
					if (g_model_Info[nCount].data.nLifePoint > (int)g_model_Info[nCount].data.status.fLifePoint)
					{
						g_model_Info[nCount].data.nLifePoint = (int)g_model_Info[nCount].data.status.fLifePoint;
					}
					if (g_model_Info[nCount].data.nSkillPoint > (int)g_model_Info[nCount].data.status.fSkillPoint)
					{
						g_model_Info[nCount].data.nSkillPoint = (int)g_model_Info[nCount].data.status.fSkillPoint;
					}
				}

				UpdateMotion(nCount);

				//�X�e�[�^�X�㏸�̃J�E���g
				if (g_model_Info[nCount].data.plus[0].fAttack > 0.0f)
				{//�㏸���Ȃ� �U��
					g_model_Info[nCount].data.plus[0].fAttack--;
					if (g_model_Info[nCount].data.plus[0].fAttack == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fAttack = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fDefense > 0.0f)
				{//�㏸���Ȃ�@�h��
					g_model_Info[nCount].data.plus[0].fDefense--;
					if (g_model_Info[nCount].data.plus[0].fDefense == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fDefense = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fInt > 0.0f)
				{//�㏸���Ȃ�@����
					g_model_Info[nCount].data.plus[0].fInt--;
					if (g_model_Info[nCount].data.plus[0].fInt == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fInt = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fRes > 0.0f)
				{//�㏸���Ȃ�@���h
					g_model_Info[nCount].data.plus[0].fRes--;
					if (g_model_Info[nCount].data.plus[0].fRes == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fRes = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fSpeed > 0.0f)
				{//�㏸���Ȃ�@�X�s�[�h
					g_model_Info[nCount].data.plus[0].fSpeed--;
					if (g_model_Info[nCount].data.plus[0].fSpeed == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fSpeed = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fLucky > 0.0f)
				{//�㏸���Ȃ�@�^
					g_model_Info[nCount].data.plus[0].fLucky--;
					if (g_model_Info[nCount].data.plus[0].fLucky == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fLucky = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
					}
				}
				if (g_model_Info[nCount].data.plus[0].fLifePoint > 0.0f)
				{//�㏸���Ȃ�@HP
					g_model_Info[nCount].data.plus[0].fLifePoint--;
					if (g_model_Info[nCount].data.plus[0].fLifePoint == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fLifePoint = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
						if ((int)g_model_Info[nCount].data.status.fLifePoint < g_model_Info[nCount].data.nLifePoint)
						{
							g_model_Info[nCount].data.nLifePoint = (int)g_model_Info[nCount].data.status.fLifePoint;
						}
					}
				}
				if (g_model_Info[nCount].data.plus[0].fSkillPoint > 0.0f)
				{//�㏸���Ȃ�@SP
					g_model_Info[nCount].data.plus[0].fSkillPoint--;
					if (g_model_Info[nCount].data.plus[0].fSkillPoint == 0.0f)
					{
						g_model_Info[nCount].data.plus[1].fSkillPoint = 0.0f;
						GetStatus(&g_model_Info[nCount].data, true);
						if ((int)g_model_Info[nCount].data.status.fSkillPoint < g_model_Info[nCount].data.nSkillPoint)
						{
							g_model_Info[nCount].data.nSkillPoint = (int)g_model_Info[nCount].data.status.fSkillPoint;
						}
					}
				}



				if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].nFloating == 1)
				{//���V����Ȃ�
					g_model_Info[nCount].set.move.y = 0.0f;
				}
				else { g_model_Info[nCount].set.move.y -= 0.25f; }	//���V�Ȃ��Ȃ�
				g_model_Info[nCount].set.pos += g_model_Info[nCount].set.move;
				g_model_Info[nCount].set.fPos += g_model_Info[nCount].set.move.y;
				//SadnessError(nCount);

				//�ʏ�
				//CollisionMeshWall(&g_model_Info[nCount].set.pos, &g_model_Info[nCount].set.posold, &g_model_Info[nCount].set.move, 20.0f);

				//SavePos[0] = g_model_Info[nCount].set.pos;
				//g_model_Info[nCount].set.pos = g_model_Info[nCount].set.posold;
				//g_model_Info[nCount].set.pos += (SavePos[0] - g_model_Info[nCount].set.posold) * 0.5f;
				//SavePos[1] = g_model_Info[nCount].set.pos;
				////�����ōĊm�F
				//CollisionMeshWall(&g_model_Info[nCount].set.pos, &g_model_Info[nCount].set.posold, &g_model_Info[nCount].set.move, 20.0f);
				//if (g_model_Info[nCount].set.pos == SavePos[1]) { g_model_Info[nCount].set.pos = SavePos[0]; }
				//else { MessageBox(0, "", "�ђʂ��Ă��", MB_OK); }

				//CollisionModel(nCount);
				//CollisionMeshWall(&g_model_Info[nCount].set.pos, &g_model_Info[nCount].set.posold, &g_model_Info[nCount].set.move, 20.0f);
				//nField = CollisionMeshField(&g_model_Info[nCount].set.pos, &g_model_Info[nCount].set.posold, &g_model_Info[nCount].set.move, &g_model_Info[nCount].set.fPos, g_model_Info[nCount].set.bJump, &g_model_Info[nCount].set);

				//�I�u�W�F�̕�

				nField = CollisionObject(nCount);
				nMField = CollisionMeshField(&g_model_Info[nCount].set.pos, &g_model_Info[nCount].set.posold, &g_model_Info[nCount].set.move, &g_model_Info[nCount].set.fPos, g_model_Info[nCount].set.bJump, &g_model_Info[nCount].set);
				if (nMField != 0)
				{//���b�V���t�B�[���h�ɂ���
					nField = nMField;
				}

				CollisionModel(nCount);
				CollisionObject(nCount);

				if (nField > 1)
				{//���n����
					if (g_model_Info[nCount].data.nLifePoint > 0)
					{
						if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].nFloating == 0)
						{
							g_model_Info[nCount].set.bJump = true;
							g_model_Info[nCount].set.bStep = true;
							g_model_Info[nCount].set.nNumMotion[3] = -2;
							if (g_model_Info[nCount].set.nNumMotion[1] != MOTION_SHRINK)
							{//�ʏ펞
								g_model_Info[nCount].set.nNumMotion[1] =
									g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[3];
								if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_LAND) { g_model_Info[nCount].set.state = MODEL_STATE_NONE; }	//�j���[�g�����Ȃ�
							}
							else
							{//���݂̏ꍇ
								g_model_Info[nCount].set.nNumMotion[1] = MOTION_DOWN;
								g_model_Info[nCount].set.nAirTime = 300;
								g_model_Info[nCount].set.nCntState = 30;
								if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
								{//�G�̏ꍇ
									if (pEnemy[g_model_Info[nCount].set.nCntChar].nDying == 1)
									{//�m���̏ꍇ//�m���̃��[�V������
										g_model_Info[nCount].set.nNumMotion[1] = MOTION_DOWN + 2;
										g_model_Info[nCount].set.nAirTime = 15;
										g_model_Info[nCount].set.nCntState = 0;
									}
								}
							}
						}
					}
					else
					{//����ł���
						g_model_Info[nCount].set.state = MODEL_STATE_DIE;
						g_model_Info[nCount].set.nCntState = 60;
						g_model_Info[nCount].set.nNumMotion[1] = MOTION_DOWN; g_model_Info[nCount].set.nAirTime = 300;
						g_model_Info[nCount].set.bJump = true;
						if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
						{
							ChangeZWindow(
								pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[0], g_model_Info[nCount].data.status.fLifePoint,
								g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos, false);
							ChangeZWindow(
								pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[1], g_model_Info[nCount].data.status.fLifePoint,
								g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos, false);
							ChangeZWindow(
								pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[2], g_model_Info[nCount].data.status.fLifePoint,
								g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos, false);
						}
						BreakShadow(g_model_Info[nCount].nCntShadow);
						BreakObject(g_model_Info[nCount].nCntObject);
					}
				}
				else if (nField == 0)
				{
					if (g_model_Info[nCount].set.nNumMotion[1] < 3)
					{//�j���[�g�����̏ꍇ
						g_model_Info[nCount].set.nNumMotion[3] = -2;
						g_model_Info[nCount].set.nNumMotion[1] = 5;
					}
					g_model_Info[nCount].set.bJump = false;
				}

				if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
				{//�G��HP�Q�[�W�̈ړ�
					ChangeZWindow(
						pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[0], g_model_Info[nCount].data.status.fLifePoint,
						g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos
						+ D3DXVECTOR3(sinf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f, 95.0f, cosf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f), true);
					ChangeZWindow(
						pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[1], g_model_Info[nCount].data.status.fLifePoint,
						g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos
						+ D3DXVECTOR3(sinf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f, 95.0f, cosf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f), true);
					ChangeZWindow(
						pEnemy[g_model_Info[nCount].set.nCntChar].nCntHPGage[2], g_model_Info[nCount].data.status.fLifePoint,
						g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].set.pos
						+ D3DXVECTOR3(sinf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f, 95.0f, cosf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f), true);
				}

				//�e�z�u
				SettingShadow(g_model_Info[nCount].set.pos, g_model_Info[nCount].set.rot, g_model_Info[nCount].set.fSlength, g_model_Info[nCount].set.fSlength, g_model_Info[nCount].nCntShadow);
				SettingObject(g_model_Info[nCount].set.pos, g_model_Info[nCount].set.rot, g_model_Info[nCount].nCntObject);
			}
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel_P(void)
{
	for (int nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_model_Info[nCount].bUse == true && g_model_Info[nCount].use == MODEL_USE_Pause)
		{
			UpdateMotion(nCount);
		}
	}
}
//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void UpdatePlayer(int nCount)
{
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	char aStr[48];
	int nLength;

	if (g_model_Info[nCount].data.nLifePoint > 0)
	{//�����Ă���
	 //�}�b�v�؂�ւ��m�F
		MAP_CHANGE	*pMap_Change = GetMap_Change();
		LOAD_MAP	*pLoad_Map = GetLoad_Map();
		for (int nCntMap = 0; nCntMap < MAX_MAP_CHANGE; nCntMap++)
		{
			if (pMap_Change[nCntMap].bUse == true)
			{//�؂�ւ�������Ȃ�
				if (pMap_Change[nCntMap].Entrance.x + pMap_Change[nCntMap].nLengthX > g_model_Info[nCount].set.pos.x &&
					pMap_Change[nCntMap].Entrance.x - pMap_Change[nCntMap].nLengthX < g_model_Info[nCount].set.pos.x &&
					pMap_Change[nCntMap].Entrance.z + pMap_Change[nCntMap].nLengthZ > g_model_Info[nCount].set.pos.z &&
					pMap_Change[nCntMap].Entrance.z - pMap_Change[nCntMap].nLengthZ < g_model_Info[nCount].set.pos.z)
				{//�؂�ւ��͈͂��͈͓�
					int *pTime = GetTime();
					pTime[0] = 0;	//���ꂩ��Â��Ȃ�
					g_model_Info[nCount].set.state = MODEL_STATE_MAP;//�U��������Ȃ��Ȃ�
					g_model_Info[nCount].set.move = D3DXVECTOR3(0.0f, g_model_Info[nCount].set.move.y, 0.0f);
					SetLoad_Map(pMap_Change[nCntMap].Export, pMap_Change[nCntMap].MapNumber);
					//��ʈÂ��Ȃ�
					SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.0f,0.0f,0.0f, 0.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEIN, WINDOWUSE_NORMAL);
					pMap_Change[nCntMap].bUse = false;
					break;
				}
			}
		}

		//�G�̏o���n�m�F
		ENEMY_APPEAR *pEnemy_Appear = GetEnemy_Appear();
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_APPEAR; nCntEnemy++)
		{
			if (pEnemy_Appear[nCntEnemy].bUse == true)
			{//�؂�ւ�������Ȃ�
				if (pEnemy_Appear[nCntEnemy].Entrance.x + pEnemy_Appear[nCntEnemy].nLengthX > g_model_Info[nCount].set.pos.x &&
					pEnemy_Appear[nCntEnemy].Entrance.x - pEnemy_Appear[nCntEnemy].nLengthX < g_model_Info[nCount].set.pos.x &&
					pEnemy_Appear[nCntEnemy].Entrance.z + pEnemy_Appear[nCntEnemy].nLengthZ > g_model_Info[nCount].set.pos.z &&
					pEnemy_Appear[nCntEnemy].Entrance.z - pEnemy_Appear[nCntEnemy].nLengthZ < g_model_Info[nCount].set.pos.z)
				{//�؂�ւ��͈͂��͈͓�
					Enemy_Appear(pEnemy_Appear[nCntEnemy].Entrance, pEnemy_Appear[nCntEnemy].nNumber);
					pEnemy_Appear[nCntEnemy].bUse = false;
					break;
				}
			}
		}

		//��b�X�V
		UpdateSpeech();

		float fRot = g_model_Info[nCount].set.angle.y;

		if (pLoad_Map[0].nMapNumber != MAP_TYPE_EMPTY) { UpdateMap_Change(nCount, 0); }
		else if (g_model_Info[nCount].set.state != MODEL_STATE_MAP)
		{
			float	fRotX = 0.0f;
			float	fRotZ = 0.0f;
			bool	bMove = false;
			int nLock = 5;
			XINPUT_STATE state;
			XInputGetState(0, &state);

			//�h���b�v�g
			switch (pPlayer[0].SDstate)
			{
			case SDROP_STATE_NONE:		//�\������
				if (pPlayer[0].nDSkill[0] != -1)
				{//�X�L���������Ă���
				 //�E�B���h�E�\���Ǝ��ԁA�X�L���\��
					pPlayer[0].nCntDWindow[0] = SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 100, 40, 23, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADEIN, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
					pPlayer[0].nCntDWindow[1] = SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 100, 40, 24, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADEIN, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
					pPlayer[0].nCntDWindow[2] = SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.825f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 100, 40, 25, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADEIN, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
					SetFont(RECT{ 1000 , 297, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "10.0�b", 8, 0, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
					wsprintf(&aStr[0], "");
					ReturnSkillName(&aStr[0], pPlayer[0].nDSkill[0]);
					nLength = (int)strlen(&aStr[0]);
					wsprintf(&aStr[nLength], "\n%d SP\n", MotionSkill(g_model_motion[g_model_Info[0].set.nNumMotion[0]][pPlayer[0].nDSkill[0]].key[0].nAtkEffect));

					SetFont(RECT{ 800 , 342, 1300, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 9, 0, DT_CENTER, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
					pPlayer[0].SDstate = SDROP_STATE_SELECT;
					pPlayer[0].nCntSDstate = 600;
				}
				break;
			case SDROP_STATE_SELECT:	//�I��
				pPlayer[0].nCntSDstate--;
				wsprintf(&aStr[0], "%d.%d�b", pPlayer[0].nCntSDstate / 60, (pPlayer[0].nCntSDstate / 6) % 10);
				ChangeFont(true, &aStr[0], 8, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				//�t�H���g�̕ω�
				if (pPlayer[0].bButton[BUTTON_LEFT] == true)
				{//Skill1����ւ�
					SwapSkill(0, nCount);
					g_model_Info[nCount].set.nSkillTime[0] = 0;
					pPlayer[0].SDstate = SDROP_STATE_END;
					pPlayer[0].nCntSDstate = 61;
					//�I��window�̕ω�
					ChangeWindow(pPlayer[0].nCntDWindow[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT_B);
					ChangeWindow(pPlayer[0].nCntDWindow[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
					ChangeWindow(pPlayer[0].nCntDWindow[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
				}
				else if (pPlayer[0].bButton[BUTTON_RIGHT] == true)
				{//Skill2����ւ�
					SwapSkill(1, nCount);
					g_model_Info[nCount].set.nSkillTime[1] = 0;
					pPlayer[0].SDstate = SDROP_STATE_END;
					pPlayer[0].nCntSDstate = 61;
					//�I��window�̕ω�
					ChangeWindow(pPlayer[0].nCntDWindow[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
					ChangeWindow(pPlayer[0].nCntDWindow[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT_B);
					ChangeWindow(pPlayer[0].nCntDWindow[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
				}
				else if (pPlayer[0].bButton[BUTTON_DOWN] == true || pPlayer[0].nCntSDstate == 0)
				{//�L�����Z��
					SwapSkill(-1, nCount);
					pPlayer[0].SDstate = SDROP_STATE_END;
					pPlayer[0].nCntSDstate = 61;
					//�I��window�̕ω�
					ChangeWindow(pPlayer[0].nCntDWindow[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
					ChangeWindow(pPlayer[0].nCntDWindow[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
					ChangeWindow(pPlayer[0].nCntDWindow[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT_B);
				}
				break;
			case SDROP_STATE_END:		//����
				pPlayer[0].nCntSDstate--;
				if (pPlayer[0].nCntSDstate == 0) { pPlayer[0].SDstate = SDROP_STATE_NONE; }
				else if (pPlayer[0].nCntSDstate == 60)
				{//�߂�
				 //window�ƃt�H���g�̍폜
					ChangeFont(false, &aStr[0], 8, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					ChangeFont(false, &aStr[0], 9, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				}
				break;
			}

			//�X�s�[�h
			if (g_model_Info[nCount].set.nNumMotion[1] < MOTION_STEP || g_model_Info[nCount].set.nMotionFrame == 0)
			{
				if (g_model_Info[nCount].set.nNumMotion[1] < MOTION_LANDING)
				{
					if (pPlayer[0].bButton[BUTTON_LSHIFT] == true)
					{
						//g_model_Info[nCount].data.nLifePoint -= 100.0f;
						if (g_model_Info[nCount].data.nStamina > 0)
						{
							g_model_Info[nCount].set.fSpeed = (MODEL_PMOVE0 + g_model_Info[nCount].data.status.fSpeed * MODEL_PMOVE) * MODEL_RUN_MOVE;
						}
						else { g_model_Info[nCount].set.fSpeed = (MODEL_PMOVE0 + g_model_Info[nCount].data.status.fSpeed * MODEL_PMOVE); }
						g_model_Info[nCount].set.bRun = true;
					}
					else
					{
						g_model_Info[nCount].set.fSpeed = (MODEL_PMOVE0 + g_model_Info[nCount].data.status.fSpeed * MODEL_PMOVE);
						g_model_Info[nCount].set.bRun = false;
					}
				}//���n�����SPEED�Ȃ�
				else if (g_model_Info[nCount].set.nNumMotion[1] > MOTION_LANDING) { g_model_Info[nCount].set.fSpeed = 0.0f; }
				else { g_model_Info[nCount].set.fSpeed = (MODEL_PMOVE0 + g_model_Info[nCount].data.status.fSpeed * MODEL_PMOVE); }
			}
			else { g_model_Info[nCount].set.fSpeed = 0.0f; }
			if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_AIR) { g_model_Info[nCount].set.fSpeed = (1.0f + g_model_Info[nCount].data.status.fSpeed * 0.0001f); }
			if (g_model_Info[nCount].data.nStamina < 0) { g_model_Info[nCount].set.fSpeed *= 0.5f; }

			if (g_model_Info[nCount].set.nNumMotion[1] != MOTION_DOWN)
			{//���݂̃��[�V�������_�E���łȂ��Ȃ�
				if (pPlayer[0].bButton[BUTTON_Q] == true)
				{
					if (g_model_Info[nCount].data.nSkillPoint > MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[0][0]].key[0].nAtkEffect && g_model_Info[nCount].data.nSkill[0][0] > 0))
					{
						if (pPlayer[0].bButton[BUTTON_J] == true) { g_model_Info[nCount].set.nNumMotion[2] = -3; g_model_Info[nCount].set.nPlayTime = 30; }
					}//�X�L����
					if (g_model_Info[nCount].data.nSkillPoint > MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[1][0]].key[0].nAtkEffect && g_model_Info[nCount].data.nSkill[1][0] > 0))
					{
						if (pPlayer[0].bButton[BUTTON_I] == true) { g_model_Info[nCount].set.nNumMotion[2] = -4; g_model_Info[nCount].set.nPlayTime = 30; }
					}//�X�L����
				}
				else
				{

					if (pPlayer[0].bButton[BUTTON_J] == true) { g_model_Info[nCount].set.nNumMotion[2] = -1; g_model_Info[nCount].set.nPlayTime = 30; }	//�U����
					if (pPlayer[0].bButton[BUTTON_I] == true) { g_model_Info[nCount].set.nNumMotion[2] = -2; g_model_Info[nCount].set.nPlayTime = 30; }	//�U����
				}

				if (pPlayer[0].bButton[BUTTON_K] == true) { g_model_Info[nCount].set.nNumMotion[2] = MOTION_GUARD; }	//�K�[�h
				if (pPlayer[0].bButton[BUTTON_L] == true) { g_model_Info[nCount].set.nNumMotion[2] = MOTION_STEP; g_model_Info[nCount].set.nPlayTime = 30; }	//�X�e�b�v

				if (pPlayer[0].bButton[BUTTON_SPACE] == true && g_model_Info[nCount].set.bJump == true) { g_model_Info[nCount].set.nNumMotion[2] = MOTION_LANDING; g_model_Info[nCount].set.nPlayTime = 30; }	//�W�����v
																																																				//if (GetKeyboardTrigger(DIK_Y) == true) { g_model_Info[nCount].set.nNumMotion[2] = MOTION_SHRINK; g_model_Info[nCount].set.nPlayTime = 30; }	//��_��
			}
			else if (g_model_Info[nCount].set.nCntState < 1)
			{//�_�E�����Ă��� && �N���オ���Ă����Ȃ�
				if (pPlayer[0].bButton[BUTTON_J] == true) { g_model_Info[nCount].set.nNumMotion[1] = MOTION_GETUP; g_model_Info[nCount].set.nNumMotion[3] = -1; }	//�U����
				if (pPlayer[0].bButton[BUTTON_I] == true) { g_model_Info[nCount].set.nNumMotion[1] = MOTION_GETUP; g_model_Info[nCount].set.nNumMotion[3] = -1; }	//�U����
				if (pPlayer[0].bButton[BUTTON_K] == true) { g_model_Info[nCount].set.nNumMotion[1] = MOTION_GETUP; g_model_Info[nCount].set.nNumMotion[3] = -1; }	//�K�[�h
				if (pPlayer[0].bButton[BUTTON_L] == true) { g_model_Info[nCount].set.nNumMotion[1] = MOTION_GETUP; g_model_Info[nCount].set.nNumMotion[3] = -1; }	//�X�e�b�v																															//K���b�N�I��
				if (pPlayer[0].bButton[BUTTON_SPACE] == true) { g_model_Info[nCount].set.nNumMotion[1] = MOTION_GETUP; g_model_Info[nCount].set.nNumMotion[3] = -1; }	//�W�����v
			}

			//�ړ�
			bMove = false;
			if (pPlayer[0].bButton[BUTTON_W] == true) { bMove = true; fRotZ = 1.0f; }
			else if (pPlayer[0].bButton[BUTTON_S] == true) { bMove = true; fRotZ = -1.0f; }
			if (pPlayer[0].bButton[BUTTON_A] == true) { bMove = true; fRotX = -1.0f; }
			else if (pPlayer[0].bButton[BUTTON_D] == true) { bMove = true; fRotX = 1.0f; }
			//�W���C�p�b�h�␳
			if (pPlayer[0].bButton[BUTTON_WS] == true) { fRotZ = state.Gamepad.sThumbLY; }
			if (pPlayer[0].bButton[BUTTON_SS] == true) { fRotZ = state.Gamepad.sThumbLY; }
			if (pPlayer[0].bButton[BUTTON_AS] == true) { fRotX = state.Gamepad.sThumbLX; }
			if (pPlayer[0].bButton[BUTTON_DS] == true) { fRotX = state.Gamepad.sThumbLX; }


			fRot = atan2f(fRotX, fRotZ) + pCamera[0].rot.y;
			if (bMove == true)
			{
				g_model_Info[nCount].set.angle.y = fRot;
				g_model_Info[nCount].set.move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -g_model_Info[nCount].set.fSpeed;
			}

			if (g_model_Info[nCount].set.nLockChar > -1) { nLock = 0; }

			if (g_model_Info[nCount].set.nNumMotion[1] < MOTION_STEP || g_model_Info[nCount].set.nMotionFrame < nLock)
			{//���݂̃��[�V�������U�����Ă��Ȃ��ꍇ
				if (g_model_Info[nCount].set.move.x > 0.1f || g_model_Info[nCount].set.move.x < -0.1f || g_model_Info[nCount].set.move.z > 0.1f || g_model_Info[nCount].set.move.z < -0.1f)
				{//�ړ��� �J�����̊p�x�Ɏ��@�̊p�x�����킹��
					float fRotPoor = g_model_Info[nCount].set.angle.y - g_model_Info[nCount].set.rot.y;
					if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
					else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
					g_model_Info[nCount].set.rot.y += fRotPoor * 0.15f;
				}
				if (g_model_Info[nCount].set.rot.y > D3DX_PI) { g_model_Info[nCount].set.rot.y -= D3DX_PI * 2; }
				if (g_model_Info[nCount].set.rot.y < -D3DX_PI) { g_model_Info[nCount].set.rot.y += D3DX_PI * 2; }
			}

		}
		if (g_model_Info[nCount].set.nPlayTime > 0)
		{
			g_model_Info[nCount].set.nPlayTime--;
			if (g_model_Info[nCount].set.nPlayTime == 0) { g_model_Info[nCount].set.nNumMotion[2] = 0; }
		}

		//D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//D3DXVECTOR3 pos = pCamera[0].posV;
		//pCamera[0].targetpos += (g_model_Info[nCount].set.pos + (g_model_Info[nCount].set.pos - g_model_Info[nCount].set.posold) * 20.0f - pCamera[0].targetpos) * 0.08f;
		//if (pCamera[0].targetpos.y - g_model_Info[nCount].set.pos.y < -50) { pCamera[0].targetpos.y = g_model_Info[nCount].set.pos.y - 50; }
		//if (pCamera[0].targetpos.y - g_model_Info[nCount].set.pos.y > 50) { pCamera[0].targetpos.y = g_model_Info[nCount].set.pos.y + 50; }

		//CollisionMeshWall(&pos, &g_model_Info[nCount].set.pos, &move, 10.0f);
		//pCamera[0].posV += (pos - pCamera[0].posV) * 0.1f;

		LockOn_MODEL(nCount);
	}//�������Ă���Ȃ�

	if (pPlayer[0].bGame == true)
	{//�ق��̍X�V����
		if (g_model_Info[nCount].data.nLifePoint > 0)
		{
			if (pCamera[0].state == CAMERA_STATE_MOVIE) { ChangeWindow(pPlayer[0].nCntSkillWindow[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), WINDOWSTATE_MAX); }
			else if (g_model_Info[nCount].set.nSkillTime[0] < 1 && g_model_Info[nCount].data.nSkillPoint > MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[0][0]].key[0].nAtkEffect))
			{
				ChangeWindow(pPlayer[0].nCntSkillWindow[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX);
			}
			else { ChangeWindow(pPlayer[0].nCntSkillWindow[0], D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), WINDOWSTATE_MAX); }
			if (pCamera[0].state == CAMERA_STATE_MOVIE) { ChangeWindow(pPlayer[0].nCntSkillWindow[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), WINDOWSTATE_MAX); }
			else if (g_model_Info[nCount].set.nSkillTime[1] < 1 && g_model_Info[nCount].data.nSkillPoint > MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[1][0]].key[0].nAtkEffect))
			{
				ChangeWindow(pPlayer[0].nCntSkillWindow[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX);
			}
			else { ChangeWindow(pPlayer[0].nCntSkillWindow[1], D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), WINDOWSTATE_MAX); }
			ChangeZWindow(pPlayer[0].nCntStamina[0], g_model_Info[nCount].data.nMaxStamina * 1.0f, g_model_Info[nCount].data.nStamina * 1.0f
				, g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f, 95.0f, cosf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f), true);
			ChangeZWindow(pPlayer[0].nCntStamina[1], g_model_Info[nCount].data.nMaxStamina * 1.0f, g_model_Info[nCount].data.nStamina * 1.0f
				, g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f, 95.0f, cosf(pCamera[0].rot.y - D3DX_PI * 0.25f) * -28.0f), true);
			CheckEXP(g_model_Info[nCount].data.nExperience * 1.0f, g_model_Info[nCount].data.nNextLevel * 1.0f, pPlayer[0].nCntEXPGage[1]);
		}
		CheckGage(g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].data.status.fLifePoint, pPlayer[0].nCntHPGage[1]);
		CheckGage(g_model_Info[nCount].data.nLifePoint * 1.0f, g_model_Info[nCount].data.status.fLifePoint, pPlayer[0].nCntHPGage[2]);
		CheckGage(g_model_Info[nCount].data.nSkillPoint * 1.0f, g_model_Info[nCount].data.status.fSkillPoint, pPlayer[0].nCntMPGage[1]);
		CheckGage(g_model_Info[nCount].data.nSkillPoint * 1.0f, g_model_Info[nCount].data.status.fSkillPoint, pPlayer[0].nCntMPGage[2]);
		pPlayer[0].nTime[1]++;
		if (pPlayer[0].nTime[1] == 6)
		{
			pPlayer[0].nTime[1] = 0;
			pPlayer[0].nTime[0]--;
		}

		//�X�e�[�^�X�㏸�m�F
		if (g_model_Info[nCount].data.plus[1].fLifePoint > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[0], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fSkillPoint > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[1], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fAttack > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[2], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[2], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fDefense > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[3], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[3], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fInt > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[4], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[4], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fRes > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[5], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[5], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fSpeed > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[6], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[6], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }
		if (g_model_Info[nCount].data.plus[1].fLucky > 0.0f) { ChangeWindow(pPlayer[0].nCntIcon[7], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_MAX); }
		else { ChangeWindow(pPlayer[0].nCntIcon[7], D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), WINDOWSTATE_MAX); }

		if (g_model_Info[nCount].data.nSkill[0][0] < 0) { g_model_Info[nCount].set.nSkillTime[0] = 9999; }
		if (g_model_Info[nCount].data.nSkill[1][0] < 0) { g_model_Info[nCount].set.nSkillTime[1] = 9999; }

		if (pPlayer[0].bButton[BUTTON_UP] == true)
		{
			pCamera[3].nCntState = (pCamera[3].nCntState + 1) % 3;
		}
		SettingObject(g_model_Info[nCount].set.pos, g_model_Info[nCount].set.rot, pPlayer[0].nCntModel_M);
		SettingPolygon(g_model_Info[nCount].set.pos);
	}
}

//=============================================================================
// ��b�X�V����
//=============================================================================
void UpdateSpeech(void)
{
	PLAYER *pPlayer = GetPlayer();

	if (pPlayer[0].nScnSpeech > -1)
	{
		switch (pPlayer[0].nScnSpeech)
		{
		case 0:
			Speech_Tutorial();
			break;
		}
	}
}
//=============================================================================
// ��b�X�V���� �`���[�g���A����
//=============================================================================
void Speech_Tutorial(void)
{
	PLAYER *pPlayer = GetPlayer();
	char aStr[84];

	switch (pPlayer[0].nNumSpeech)
	{
	case 0:
		pPlayer[0].nCntSTime = 0;
		pPlayer[0].nNumSpeech++;
		pPlayer[0].nCntSpeech = SetWindow(D3DXVECTOR3(255, SCREEN_HEIGHT * 0.65f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 0.0f }, 250, 70, 7, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADEIN, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
		strcpy(&aStr[0], "��{�I�ȑ�����@���������S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		SetFont(RECT{ 150 , 422, 1280, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 24, 7, DT_LEFT, 60, true, FONTSTATE_NONE, WINDOW_DRAW_1);
		ChangeFont(true, &aStr[0], 24, 0, 0, 60, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case 1:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[L�X�e�B�b�N][WASD]�ňړ��A\n[R1][L_SHIFT]�������Ȃ��炾��\n�����S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;

	case 2:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "���F�}�b�v�؂�ւ��@���F�L�����Z��\n���F�X�L��L2���̂Ă�\n���F�X�L��R2���̂Ă�");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 3:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[L1][K]�ŃK�[�h\n[�X�^�[�g�{�^��][P]�Ń|�[�Y");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 4:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[X�{�^��][J]�Ŏ�U��\n[Y�{�^��][I]��\n�ߐH/�ߐH�U�����ł���]");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 5:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[B�{�^��][SPACE]�ŃW�����v\n[A�{�^��][L]��\n�u�[�X�g�ł���S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 6:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[L2 + X][Q + J]�ŃX�L���P\n[L2 + Y][Q + I]�ŃX�L���Q�𔭓����I");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 7:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[B�{�^��][SPACE]�ŃW�����v\n[A�{�^��][L]�Ńu�[�X�g�ł���S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 8:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[R�X�e�B�b�N]�ŃJ��������\n[Y/H]���㉺\n[U/O]�ō��E���S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 9:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "[R2][E]�Ń��b�N�I�����S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	case 10:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nCntSTime = 0; pPlayer[0].nNumSpeech++;
		strcpy(&aStr[0], "����ő�����@�̐����͏I���S�u");
		pPlayer[0].nCntSStop = (strlen(&aStr[0]) / 2) * SPEECH_FLOW + SPEECH_STOP;
		ChangeFont(true, &aStr[0], 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;

	case 11:if (pPlayer[0].nCntSTime == pPlayer[0].nCntSStop) {
		pPlayer[0].nScnSpeech = -1;
		ChangeWindow(pPlayer[0].nCntSpeech, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), WINDOWSTATE_FADEOUT);
		ChangeFont(false, NULL, 24, 0, 0, 3, FONTSTATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}break;
	}
	pPlayer[0].nCntSTime++;
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	Camera *pCamera = GetCamera();

	if (pCamera[0].state == CAMERA_STATE_GAME)
	{
		switch (use)
		{
		case MODEL_USE_ENEMY_B://�S�J
			UpdateBEnemy(&set[0], &data[0], use, nMode);
			break;

		case MODEL_USE_ENEMY_Z://�߂Â��ĉ��邾�� ����
			UpdateZEnemy(&set[0], &data[0], use, nMode);
			break;

		case MODEL_USE_ENEMY_ZE://�߂Â��ĉ��邾���@����
			UpdateZEnemyE(&set[0], &data[0], use, nMode);
			break;

		case MODEL_USE_ENEMY_S://�߂Â��ĉ����� �҂����Ԋ�{����
			UpdateSEnemy(&set[0], &data[0], use, nMode);
			break;

		case MODEL_USE_ENEMY_T://�X�e�b�v���
			UpdateSEnemy(&set[0], &data[0], use, nMode);
			break;
		}
	}
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateSubEnemy(MODEL_SETTING *set, CHAR_DATA *data, float fRot, bool bMove)
{
	if (set[0].nNumMotion[1] < MOTION_STEP || set[0].nMotionFrame == 0)
	{
		if (set[0].nNumMotion[1] < MOTION_LANDING)
		{
			if (set[0].bRun == true)
			{
				//g_model_Info[nCount].data.nLifePoint -= 100.0f;
				if (data[0].nStamina > 0)
				{
					set[0].fSpeed = (MODEL_PMOVE0 + data[0].status.fSpeed * MODEL_PMOVE) * MODEL_RUN_MOVE;
				}
				else { set[0].fSpeed = (MODEL_PMOVE0 + data[0].status.fSpeed * MODEL_PMOVE); }
			}
			else
			{
				set[0].fSpeed = (MODEL_PMOVE0 + data[0].status.fSpeed * MODEL_PMOVE);
				set[0].bRun = false;
			}
		}//���n�����SPEED�Ȃ�
		else if (set[0].nNumMotion[1] > MOTION_LANDING) { set[0].fSpeed = 0.0f; }
		else { set[0].fSpeed = (MODEL_PMOVE0 + data[0].status.fSpeed * MODEL_PMOVE); }
	}
	else { set[0].fSpeed = 0.0f; }

	if (bMove == true)
	{
		if (data[0].nStamina < 50) { set[0].bRun = false; }
		set[0].angle.y = fRot;
		set[0].move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -set[0].fSpeed;
	}

	if (set[0].nNumMotion[1] < MOTION_STEP || set[0].nMotionFrame < 1)
	{//���݂̃��[�V�������U�����Ă��Ȃ��ꍇ
		if (set[0].move.x > 0.1f || set[0].move.x < -0.1f || set[0].move.z > 0.1f || set[0].move.z < -0.1f)
		{//�ړ��� �J�����̊p�x�Ɏ��@�̊p�x�����킹��
			float fRotPoor = set[0].angle.y - set[0].rot.y;
			if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
			else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
			set[0].rot.y += fRotPoor * 0.15f;
		}
		if (set[0].rot.y > D3DX_PI) { set[0].rot.y -= D3DX_PI * 2; }
		if (set[0].rot.y < -D3DX_PI) { set[0].rot.y += D3DX_PI * 2; }
	}

}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateBEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	if (set[0].nPlayTime > 0) { set[0].nPlayTime = -1; }
	ENEMY *pEnemy = GetEnemy();
	float fDistance;
	float fDistanceX;
	float fDistanceZ;
	//float fDistanceY;
	float fTarget = ReturnAngle(&set[0]);
	float fRot = fTarget;
	int nDistance;
	bool bMove = true;

	//�����v�Zposold��
	fDistanceX = set[0].posold.x - g_model_Info[0].set.posold.x;
	fDistanceZ = set[0].posold.z - g_model_Info[0].set.posold.z;
	//fDistanceY = set[0].posold.y - g_model_Info[0].set.posold.y;
	//fDistance = 0;
	//if (fDistanceY < 0) { fDistanceY *= -1; }
	fDistance = fDistanceX * fDistanceX + fDistanceZ * fDistanceZ;

	if (fDistance < 150.0f * 150.0f) { nDistance = 0; }
	else if (fDistance < 250.0f * 250.0f) { nDistance = 1; }
	else if (fDistance < 500.0f * 500.0f) { nDistance = 2; }
	else { nDistance = 3; }
	if (nDistance != pEnemy[set[0].nCntChar].nDistance)
	{//�������ς����
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
		pEnemy[set[0].nCntChar].nDistance = nDistance;
		set[0].bRun = false;
	}

	pEnemy[set[0].nCntChar].nCntTime++;
	switch (set[0].state)
	{
		//�U�����ē�����Ȃ�����
	case MODEL_STATE_ATK:
		//������Ɉȍ~
		if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
		else { set[0].nNumMotion[2] = -1; }
		break;

	case MODEL_STATE_ATKHIT:	//�U�����������Ă���
								//�G�̖��G���Ԃ����ȉ�
		if ((g_model_Info[0].set.nAirTime < 5 && g_model_Info[0].set.state != MODEL_STATE_GUARD) || nMode != 0)
		{
			if (set[0].nNumMotion[1] == MOTION_STEP || set[0].nNumMotion[1] == MOTION_STEPS)
			{//�X�e�b�v���Ă���Ȃ�@�X�L���ɂȂ���@nPlayTime = ...;
				if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
				{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
					set[0].nNumMotion[2] = -1; set[0].nPlayTime = 50;
					if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
					{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
						set[0].nPlayTime = 65;
					}
				}
				else if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
				{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
					set[0].nNumMotion[2] = -1; set[0].nPlayTime = 40;
				}
				else if (set[0].nSkillTime[0] > 0)
				{//�R���{���Ɏ�U�����g�p���Ă���Ȃ�
					set[0].nNumMotion[2] = -2;
				}
				else
				{//MP���Ȃ��Ȃ�
					set[0].nNumMotion[2] = -1;
				}
			}
			else
			{//���݂��X�e�b�v�łȂ�
				if (nMode != 0)
				{//�O���X�e�b�v������
					if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
					{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
						set[0].nNumMotion[2] = -3;
					}
					else if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
					{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
						set[0].nNumMotion[2] = -4;
					}
				}
				else
				{//�R���{��
					if (set[0].nNumMotion[2] != -1)
					{//��U������]
						set[0].nNumMotion[2] = -1;	//��U���Ɉȍ~
					}
					else
					{//���[�V�������؂�ւ���Ă��Ȃ�
						if (data[0].nStamina > 30) { set[0].nNumMotion[2] = MOTION_STEP; }//�X�e�b�v�g�p�\�Ȃ�@�X�^�~�i�����S��													   
						else if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
						{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
							set[0].nNumMotion[2] = -3;
						}
						else if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
						{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
							set[0].nNumMotion[2] = -4;
						}
					}
				}
			}
		}
		else if (g_model_Info[0].set.nAirTime < 3)
		{//���������
			if (data[0].nStamina > 30)
			{
				set[0].nNumMotion[2] = MOTION_STEP;
				fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
			}
			else
			{
				if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
				else { set[0].nNumMotion[2] = -1; }//���[�V�������؂�ւ���Ă��Ȃ�

			}
		}
		break;

	case MODEL_STATE_GUARD:		//�K�[�h����
		if (data[0].nStamina > 30)
		{
			set[0].nNumMotion[2] = MOTION_STEP;
			fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
		}
		break;

	case MODEL_STATE_NONE:	//�ʏ펞
		if (fDistance < 1000.0f * 1000.0f) { set[0].nLockChar = 0; }
		else if (use != MODEL_USE_ENEMY_B) { set[0].nLockChar = -1; }

		if (set[0].nLockChar != -1)
		{//�v���C���[�𔭌����Ă���
			if (g_model_Info[0].set.nAirTime > 0)
			{//�v���C���[���G
				if (nDistance < 2)
				{//�����������������h�ŃX�e�b�v or �_�b�V�� or ����
					PointEnemy(&set[0], 2);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = MOTION_STEPS; }
					if (data[0].nStamina > 100) { set[0].bRun = true; }
					fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
				}
				else
				{//������ �V���Q�_��
					set[0].bRun = false;
					if (pEnemy[set[0].nCntChar].nCntTime % 4 < 2) { fRot = fTarget + D3DX_PI * 0.49f; }
					else { fRot = fTarget - D3DX_PI * 0.49f; }
				}
			}
			else
			{//���G�łȂ�
				if (nDistance == 0)
				{//�ߋ����Ȃ�@��U�� or �K�[�h or ���
					if (set[0].nNumMotion[1] == MOTION_STEP || set[0].nNumMotion[1] == MOTION_STEPS)
					{//�X�e�b�v��
						if (rand() % 2 == 0)
						{
							set[0].nNumMotion[2] = -1;
							if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
							{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
								set[0].nPlayTime = 50;
								if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
								{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
									set[0].nPlayTime = 60;
								}
							}
						}
						else { set[0].nNumMotion[2] = -2; }
					}
					else
					{//�X�e�b�v���Ă��Ȃ�
						PointEnemy(&set[0], 4);

						fRot = fTarget;
						if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = -1; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 1) { set[0].nNumMotion[2] = -2; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 2) { set[0].nNumMotion[2] = MOTION_GUARD; }
						else
						{//����
							if (data[0].nStamina > 30)
							{
								set[0].nNumMotion[2] = MOTION_STEP;
							}
							fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
						}
					}
				}
				else if (nDistance == 1)
				{//�������Ȃ�@���U�� or �l�߂�(�X�e�b�v or �_�b�V��) or �l�q��(�X�e�b�v or �W�����v or �_�b�V�� or ����) 
					if (set[0].nNumMotion[1] == MOTION_STEP || set[0].nNumMotion[1] == MOTION_STEPS)
					{//�X�e�b�v��
						if (rand() % 2 == 0)
						{
							set[0].nNumMotion[2] = -1;
							if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
							{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
								set[0].nPlayTime = 45;
								if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[1][0]].key[0].nAtkEffect) && set[0].nSkillTime[1] < 1)
								{//���X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
									set[0].nPlayTime = 55;
								}
							}
						}
						else { set[0].nNumMotion[2] = -2; }
					}
					else
					{//�X�e�b�v���Ă��Ȃ�
						PointEnemy(&set[0], 3);

						if (pEnemy[set[0].nCntChar].nAction[0] == 0 && data[0].nStamina > 100)
						{//�l�߂�
							if (rand() % 2 == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200; }
							else { set[0].nNumMotion[2] = MOTION_LANDING; pEnemy[set[0].nCntChar].nCntTime += 200; }
							fRot = fTarget - D3DX_PI * 0.4f + (D3DX_PI * 0.8f) * (rand() % 2);

						}
						else if (pEnemy[set[0].nCntChar].nAction[0] == 2)
						{//���U��
							pEnemy[set[0].nCntChar].nCntTime += 10000;
							set[0].nNumMotion[2] = -2;
						}
						else if (pEnemy[set[0].nCntChar].nAction[0] == 3)
						{
							if (pEnemy[set[0].nCntChar].nCntTime % 4 < 2) { fRot = fTarget + D3DX_PI * 0.49f; }
							else { fRot = fTarget - D3DX_PI * 0.49f; }
							if (data[0].nStamina > 30) { pEnemy[set[0].nCntChar].nAction[0] = 1; }
						}
						else
						{//����
							if (data[0].nStamina > 30)
							{//�X�^�~�i������ꍇ
								set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200;
								fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
							}
							else
							{//�X�^�~�i���Ȃ�
								if (rand() % 2 == 0)
								{//�K�[�h
									set[0].nNumMotion[2] = MOTION_GUARD; pEnemy[set[0].nCntChar].nCntTime += 200;
								}
								else
								{//�V���Q�_����
									pEnemy[set[0].nCntChar].nMaxTime = 120;
									pEnemy[set[0].nCntChar].nAction[0] = 3;
									set[0].bRun = false;
								}
							}
						}
					}
				}
				else if (nDistance == 2)
				{//���������@�l�߂�(�X�e�b�v or �_�b�V��) �l�q��(�����@�_�b�V��)
					PointEnemy(&set[0], 3);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 120;

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200; }

						if (data[0].nStamina > 200) { set[0].bRun = true; }
						else if (data[0].nStamina < 150) { set[0].bRun = false; }

						fRot = fTarget;
					}
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1)
					{//�l�q��
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						if (pEnemy[set[0].nCntChar].nAction[2] < 0) { pEnemy[set[0].nCntChar].nAction[2] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 80;

						if (pEnemy[set[0].nCntChar].nAction[2] == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 100; }
						if (data[0].nStamina > 300) { set[0].bRun = true; }
						else if (data[0].nStamina < 250) { set[0].bRun = false; }

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { fRot = fTarget + D3DX_PI * 0.4f; }
						else { fRot = fTarget - D3DX_PI * 0.4f; }
					}
					else
					{//�V���Q�_��
						pEnemy[set[0].nCntChar].nMaxTime = 30;
						set[0].bRun = false;
						if (pEnemy[set[0].nCntChar].nCntTime % 4 < 2) { fRot = fTarget + D3DX_PI * 0.49f; }
						else { fRot = fTarget - D3DX_PI * 0.49f; }
					}
				}
				else
				{//�������@�����@�߂Â�
					if (data[0].nStamina > 300) { set[0].bRun = true; }
					else if (data[0].nStamina < 250) { set[0].bRun = false; }

					fRot = fTarget;
				}
			}
		}
		break;
	}
	UpdateSubEnemy(&set[0], &data[0], fRot, bMove);
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateTEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	if (set[0].nPlayTime > 0) { set[0].nPlayTime = -1; }
	ENEMY *pEnemy = GetEnemy();
	float fDistance;
	float fDistanceX;
	float fDistanceZ;
	float fTarget = ReturnAngle(&set[0]);
	float fRot = fTarget;
	int nDistance;
	bool bMove = true;

	//�����v�Zposold��
	fDistanceX = set[0].posold.x - g_model_Info[0].set.posold.x;
	fDistanceZ = set[0].posold.z - g_model_Info[0].set.posold.z;
	fDistance = fDistanceX * fDistanceX + fDistanceZ * fDistanceZ;

	if (fDistance < 150.0f * 150.0f) { nDistance = 0; }
	else if (fDistance < 250.0f * 250.0f) { nDistance = 1; }
	else if (fDistance < 500.0f * 500.0f) { nDistance = 2; }
	else { nDistance = 3; }
	if (nDistance != pEnemy[set[0].nCntChar].nDistance)
	{//�������ς����
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
		pEnemy[set[0].nCntChar].nDistance = nDistance;
		set[0].bRun = false;
	}

	pEnemy[set[0].nCntChar].nCntTime++;
	switch (set[0].state)
	{
		//�U�����ē�����Ȃ�����
	case MODEL_STATE_ATK:
		//������Ɉȍ~
		if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
		else { set[0].nNumMotion[2] = -1; }
		break;

	case MODEL_STATE_ATKHIT:	//�U�����������Ă���
		if (g_model_Info[0].set.nAirTime < 3)
		{//�G�̖��G���Ԃ����ȉ�
			set[0].nNumMotion[2] = -1;//����
		}
		break;

	case MODEL_STATE_NONE:	//�ʏ펞
		if (fDistance < 1000.0f * 1000.0f) { set[0].nLockChar = 0; }
		else if (use != MODEL_USE_ENEMY_B) { set[0].nLockChar = -1; }

		if (set[0].nLockChar != -1)
		{//�v���C���[�𔭌����Ă���
			if (g_model_Info[0].set.nAirTime > 0)
			{//�v���C���[���G
				if (nDistance < 2)
				{//�����������������h�ŃX�e�b�v or �_�b�V�� or ����
					PointEnemy(&set[0], 2);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = MOTION_STEPS; }
					if (data[0].nStamina > 100) { set[0].bRun = true; }
					fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
				}
				else
				{//������ �������Ȃ�
					set[0].bRun = false;
					bMove = false;
				}
			}
			else
			{//���G�łȂ�
				if (nDistance == 0)
				{//�ߋ����Ȃ�@��U�� or �K�[�h or ���
					if (set[0].nNumMotion[1] == MOTION_STEP || set[0].nNumMotion[1] == MOTION_STEPS)
					{//�X�e�b�v��
						if (rand() % 2 == 0) { set[0].nNumMotion[2] = -1; set[0].nPlayTime = 60; }
						else { set[0].nNumMotion[2] = -2; }
					}
					else
					{//�X�e�b�v���Ă��Ȃ�
						PointEnemy(&set[0], 4);

						fRot = fTarget;
						if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = -1; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 1) { set[0].nNumMotion[2] = -2; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 2) { set[0].nNumMotion[2] = MOTION_GUARD; }
						else
						{//����
							if (data[0].nStamina > 30)
							{
								set[0].nNumMotion[2] = MOTION_STEP;
							}
							fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
						}
					}
				}
				else if (nDistance == 1)
				{//�������Ȃ�@���U�� or �l�߂�(�X�e�b�v or �_�b�V��) or �l�q��(�X�e�b�v or �W�����v or �_�b�V�� or ����) 
					if (set[0].nNumMotion[1] == MOTION_STEP || set[0].nNumMotion[1] == MOTION_STEPS)
					{//�X�e�b�v��
						if (rand() % 2 == 0) { set[0].nNumMotion[2] = -1; set[0].nPlayTime = 60; }
						else { set[0].nNumMotion[2] = -2; }
					}
					else
					{//�X�e�b�v���Ă��Ȃ�
						PointEnemy(&set[0], 10);

						if (pEnemy[set[0].nCntChar].nAction[0] < 3 && data[0].nStamina > 100)
						{//�l�߂�
							if (rand() % 2 == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200; }
							else { set[0].nNumMotion[2] = MOTION_LANDING; pEnemy[set[0].nCntChar].nCntTime += 200; }
							fRot = fTarget - D3DX_PI * 0.4f + (D3DX_PI * 0.8f) * (rand() % 2);

						}
						else if (pEnemy[set[0].nCntChar].nAction[0] < 3)
						{//���U��
							pEnemy[set[0].nCntChar].nCntTime += 10000;
							set[0].nNumMotion[2] = -2;
						}
						else if (pEnemy[set[0].nCntChar].nAction[0] < 6)
						{
							set[0].bRun = false;
							bMove = false;
							if (data[0].nStamina > 30) { pEnemy[set[0].nCntChar].nAction[0] = 1; }
						}
						else if (pEnemy[set[0].nCntChar].nAction[0] < 9)
						{//����
							if (data[0].nStamina > 30)
							{//�X�^�~�i������ꍇ
								set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200;
								fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
							}
							else
							{//�X�^�~�i���Ȃ�
								if (rand() % 2 == 0)
								{//�K�[�h
									set[0].nNumMotion[2] = MOTION_GUARD; pEnemy[set[0].nCntChar].nCntTime += 200;
								}
								else
								{//�ʏ��
									pEnemy[set[0].nCntChar].nMaxTime = 120;
									pEnemy[set[0].nCntChar].nAction[0] = 3;
									set[0].bRun = false;
								}
							}
						}
						else
						{
							pEnemy[set[0].nCntChar].nCntTime += 10000;
							if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
							{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
								set[0].nNumMotion[2] = -3;
							}
						}
					}
				}
				else if (nDistance == 2)
				{//���������@�l�߂�(�X�e�b�v or �_�b�V��) �l�q��(�����@�_�b�V��)
					PointEnemy(&set[0], 3);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 120;

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 200; }

						if (data[0].nStamina > 200) { set[0].bRun = true; }
						else if (data[0].nStamina < 150) { set[0].bRun = false; }

						fRot = fTarget;
					}
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1)
					{//�l�q��
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						if (pEnemy[set[0].nCntChar].nAction[2] < 0) { pEnemy[set[0].nCntChar].nAction[2] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 80;

						if (pEnemy[set[0].nCntChar].nAction[2] == 0) { set[0].nNumMotion[2] = MOTION_STEP; pEnemy[set[0].nCntChar].nCntTime += 100; }
						if (data[0].nStamina > 300) { set[0].bRun = true; }
						else if (data[0].nStamina < 250) { set[0].bRun = false; }

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { fRot = fTarget + D3DX_PI * 0.4f; }
						else { fRot = fTarget - D3DX_PI * 0.4f; }
					}
					else
					{//�ʏ�
						pEnemy[set[0].nCntChar].nMaxTime = 30;
						set[0].bRun = false;
						bMove = false;
					}
				}
				else
				{//�������@�����@�߂Â�
					if (data[0].nStamina > 300) { set[0].bRun = true; }
					else if (data[0].nStamina < 250) { set[0].bRun = false; }

					fRot = fTarget;
				}
			}
		}
		else { bMove = false; }
		break;
	}

	UpdateSubEnemy(&set[0], &data[0], fRot, bMove);
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateSEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	if (set[0].nPlayTime > 0) { set[0].nPlayTime = -1; }
	ENEMY *pEnemy = GetEnemy();
	float fDistance;
	float fDistanceX;
	float fDistanceZ;
	float fTarget = ReturnAngle(&set[0]);
	float fRot = fTarget;
	int nDistance;
	bool bMove = true;

	//�����v�Zposold��
	fDistanceX = set[0].posold.x - g_model_Info[0].set.posold.x;
	fDistanceZ = set[0].posold.z - g_model_Info[0].set.posold.z;
	fDistance = fDistanceX * fDistanceX + fDistanceZ * fDistanceZ;

	if (fDistance < 150.0f * 150.0f) { nDistance = 0; }
	else if (fDistance < 250.0f * 250.0f) { nDistance = 1; }
	else if (fDistance < 500.0f * 500.0f) { nDistance = 2; }
	else { nDistance = 3; }
	if (nDistance != pEnemy[set[0].nCntChar].nDistance)
	{//�������ς����
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
		pEnemy[set[0].nCntChar].nDistance = nDistance;
		set[0].bRun = false;
	}

	pEnemy[set[0].nCntChar].nCntTime++;
	switch (set[0].state)
	{
		//�U�����ē�����Ȃ�����
	case MODEL_STATE_ATK:
		//������Ɉȍ~
		if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
		else { set[0].nNumMotion[2] = -1; }
		break;

	case MODEL_STATE_ATKHIT:	//�U�����������Ă���
		if (g_model_Info[0].set.nAirTime < 3)
		{//�G�̖��G���Ԃ����ȉ�
			set[0].nNumMotion[2] = -1;//����
		}
		break;

	case MODEL_STATE_NONE:	//�ʏ펞
		if (fDistance < 1000.0f * 1000.0f) { set[0].nLockChar = 0; }
		else if (use != MODEL_USE_ENEMY_B) { set[0].nLockChar = -1; }

		if (set[0].nLockChar != -1)
		{//�v���C���[�𔭌����Ă���
			if (g_model_Info[0].set.nAirTime > 0)
			{//�v���C���[���G
				if (nDistance < 2)
				{//�����������������h�ŃX�e�b�v or �_�b�V�� or ����
					if (data[0].nStamina > 100) { set[0].bRun = true; }
					fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
				}
				else
				{//������ �������Ȃ�
					set[0].bRun = false;
					bMove = false;
				}
			}
			else
			{//���G�łȂ�
				if (nDistance == 0)
				{//�ߋ����Ȃ�@��U�� or �K�[�h or ���
					PointEnemy(&set[0], 2);

					fRot = fTarget;
					if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = -1; }
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1) { set[0].nNumMotion[2] = -2; }
				}
				else if (nDistance == 1)
				{//�������Ȃ�@���U�� or �l�߂�(�X�e�b�v or �_�b�V��) or �l�q��(�X�e�b�v or �W�����v or �_�b�V�� or ����) 
					PointEnemy(&set[0], 7);

					if (pEnemy[set[0].nCntChar].nAction[0] < 3 && data[0].nStamina > 100)
					{//�l�߂�
						set[0].nNumMotion[2] = MOTION_LANDING; pEnemy[set[0].nCntChar].nCntTime += 200;
						set[0].bRun = true;
						fRot = fTarget - D3DX_PI * 0.4f + (D3DX_PI * 0.8f) * (rand() % 2);

					}
					else if (pEnemy[set[0].nCntChar].nAction[0] < 6)
					{//���U��
						pEnemy[set[0].nCntChar].nCntTime += 10000;
						set[0].nNumMotion[2] = -2;
					}
					else
					{
						pEnemy[set[0].nCntChar].nCntTime += 10000;
						if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
						{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
							set[0].nNumMotion[2] = -3;
						}
					}
				}
				else if (nDistance == 2)
				{//���������@�l�߂�(�X�e�b�v or �_�b�V��) �l�q��(�����@�_�b�V��)
					PointEnemy(&set[0], 3);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						pEnemy[set[0].nCntChar].nMaxTime = 120;

						if (data[0].nStamina > 200) { set[0].bRun = true; }
						else if (data[0].nStamina < 150) { set[0].bRun = false; }

						fRot = fTarget;
					}
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1)
					{//�l�q��
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 80;

						if (data[0].nStamina > 300) { set[0].bRun = true; }
						else if (data[0].nStamina < 250) { set[0].bRun = false; }

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { fRot = fTarget + D3DX_PI * 0.4f; }
						else { fRot = fTarget - D3DX_PI * 0.4f; }
					}
					else
					{//�ʏ�
						pEnemy[set[0].nCntChar].nMaxTime = 30;
						set[0].bRun = false;
						bMove = false;
					}
				}
				else
				{//�������@�����@�߂Â�
					if (data[0].nStamina > 300) { set[0].bRun = true; }
					else if (data[0].nStamina < 250) { set[0].bRun = false; }

					fRot = fTarget;
				}
			}
		}
		else { bMove = false; }
		break;
	}

	UpdateSubEnemy(&set[0], &data[0], fRot, bMove);
}

//=============================================================================
// �G�̍X�V���� �������^
//=============================================================================
void UpdateZEnemyE(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	if (set[0].nPlayTime > 0) { set[0].nPlayTime = -1; }
	ENEMY *pEnemy = GetEnemy();
	float fDistance;
	float fDistanceX;
	float fDistanceZ;
	float fTarget = ReturnAngle(&set[0]);
	float fRot = fTarget;
	int nDistance;
	bool bMove = true;

	//�����v�Zposold��
	fDistanceX = set[0].posold.x - g_model_Info[0].set.posold.x;
	fDistanceZ = set[0].posold.z - g_model_Info[0].set.posold.z;
	fDistance = fDistanceX * fDistanceX + fDistanceZ * fDistanceZ;

	if (fDistance < 350.0f * 350.0f) { nDistance = 0; }
	else if (fDistance < 450.0f * 450.0f) { nDistance = 1; }
	else if (fDistance < 600.0f * 600.0f) { nDistance = 2; }
	else { nDistance = 3; }
	if (nDistance != pEnemy[set[0].nCntChar].nDistance)
	{//�������ς����
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
		pEnemy[set[0].nCntChar].nDistance = nDistance;
		set[0].bRun = false;
	}

	pEnemy[set[0].nCntChar].nCntTime++;
	switch (set[0].state)
	{
		//�U�����ē�����Ȃ�����
	case MODEL_STATE_ATK:
		//������Ɉȍ~
		if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
		else { set[0].nNumMotion[2] = -1; }
		break;

	case MODEL_STATE_ATKHIT:	//�U�����������Ă���
		if (g_model_Info[0].set.nAirTime < 3)
		{//�G�̖��G���Ԃ����ȉ�
			set[0].nNumMotion[2] = -1;//����
		}
		break;

	case MODEL_STATE_NONE:	//�ʏ펞
		if (fDistance < 1000.0f * 1000.0f) { set[0].nLockChar = 0; }
		else if (use != MODEL_USE_ENEMY_B) { set[0].nLockChar = -1; }

		if (set[0].nLockChar != -1)
		{//�v���C���[�𔭌����Ă���
			if (g_model_Info[0].set.nAirTime > 0)
			{//�v���C���[���G
				if (nDistance < 2)
				{//�����������������h�ŃX�e�b�v or �_�b�V�� or ����
					fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
				}
				else
				{//������ �������Ȃ�
					bMove = false;
				}
			}
			else
			{//���G�łȂ�
				if (nDistance == 0)
				{//�ߋ����Ȃ�@��U�� or �K�[�h or ���
					PointEnemy(&set[0], 2);

					fRot = fTarget;
					if (rand() % ENEMY_ATIME == 0)
					{
						if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = -1; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 1) { set[0].nNumMotion[2] = -2; }
					}
				}
				else if (nDistance == 1)
				{//�������Ȃ�@���U�� or �l�߂�(�X�e�b�v or �_�b�V��) or �l�q��(�X�e�b�v or �W�����v or �_�b�V�� or ����) 
					PointEnemy(&set[0], 7);

					if (pEnemy[set[0].nCntChar].nAction[0] < 3 && data[0].nStamina > 100)
					{//�����
						pEnemy[set[0].nCntChar].nCntTime += 200;
						fRot = fTarget - D3DX_PI * 0.4f + (D3DX_PI * 0.8f) * (rand() % 2) + D3DX_PI * 0.5f;

					}
					else if (pEnemy[set[0].nCntChar].nAction[0] < 6)
					{//���U��
						if (rand() % ENEMY_ATIME == 0)
						{
							pEnemy[set[0].nCntChar].nCntTime += 10000;
							set[0].nNumMotion[2] = -2;
						}
					}
					else
					{
						pEnemy[set[0].nCntChar].nCntTime += 10000;
						if (data[0].nSkillPoint > MotionSkill(g_model_motion[set[0].nNumMotion[0]][data[0].nSkill[0][0]].key[0].nAtkEffect) && set[0].nSkillTime[0] < 1)
						{//��X�L���g�p�\�Ȃ�	MP������Ă���&&�g�p����
							set[0].nNumMotion[2] = -3;
						}
					}
				}
				else if (nDistance == 2)
				{//���������@�l�߂�(�X�e�b�v or �_�b�V��) �l�q��(�����@�_�b�V��)
					PointEnemy(&set[0], 3);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						pEnemy[set[0].nCntChar].nMaxTime = 120;

						fRot = fTarget;
					}
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1)
					{//�l�q��
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 80;

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { fRot = fTarget + D3DX_PI * 0.4f; }
						else { fRot = fTarget - D3DX_PI * 0.4f; }
					}
					else
					{//�ʏ�
						pEnemy[set[0].nCntChar].nMaxTime = 30;
						bMove = false;
					}
				}
				else
				{//�������@�����@�߂Â�
					fRot = fTarget;
				}
			}
		}
		else { bMove = false; }
		break;
	}

	set[0].bRun = false;
	UpdateSubEnemy(&set[0], &data[0], fRot, bMove);
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateZEnemy(MODEL_SETTING *set, CHAR_DATA *data, MODEL_USE use, int nMode)
{
	if (set[0].nPlayTime > 0) { set[0].nPlayTime = -1; }
	ENEMY *pEnemy = GetEnemy();
	float fDistance;
	float fDistanceX;
	float fDistanceZ;
	float fTarget = ReturnAngle(&set[0]);
	float fRot = fTarget;
	int nDistance;
	bool bMove = true;

	//�����v�Zposold��
	fDistanceX = set[0].posold.x - g_model_Info[0].set.posold.x;
	fDistanceZ = set[0].posold.z - g_model_Info[0].set.posold.z;
	fDistance = fDistanceX * fDistanceX + fDistanceZ * fDistanceZ;

	if (fDistance < 120.0f * 120.0f) { nDistance = 0; }
	else if (fDistance < 250.0f * 250.0f) { nDistance = 1; }
	else if (fDistance < 500.0f * 500.0f) { nDistance = 2; }
	else { nDistance = 3; }
	if (nDistance != pEnemy[set[0].nCntChar].nDistance)
	{//�������ς����
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
		pEnemy[set[0].nCntChar].nDistance = nDistance;
		set[0].bRun = false;
	}

	pEnemy[set[0].nCntChar].nCntTime++;
	switch (set[0].state)
	{
		//�U�����ē�����Ȃ�����
	case MODEL_STATE_ATK:
		//������Ɉȍ~
		if (set[0].nNumMotion[2] != -2) { set[0].nNumMotion[2] = -2; }
		else { set[0].nNumMotion[2] = -1; }
		break;

	case MODEL_STATE_ATKHIT:	//�U�����������Ă���
		if (g_model_Info[0].set.nAirTime < 3)
		{//�G�̖��G���Ԃ����ȉ�
			set[0].nNumMotion[2] = -1;//����
		}
		break;

	case MODEL_STATE_NONE:	//�ʏ펞
		if (fDistance < 1000.0f * 1000.0f) { set[0].nLockChar = 0; }
		else if (use != MODEL_USE_ENEMY_B) { set[0].nLockChar = -1; }

		if (set[0].nLockChar != -1)
		{//�v���C���[�𔭌����Ă���
			if (g_model_Info[0].set.nAirTime > 0)
			{//�v���C���[���G
				if (nDistance < 2)
				{//�����������������h�ŃX�e�b�v or �_�b�V�� or ����
					fRot = fTarget - D3DX_PI * 0.75f - (D3DX_PI * 0.25f) * (rand() % 3);
				}
				else
				{//������ �������Ȃ�
					bMove = false;
				}
			}
			else
			{//���G�łȂ�
				if (nDistance == 0)
				{//�ߋ����Ȃ�@��U�� or �K�[�h or ���
					PointEnemy(&set[0], 2);
					bMove = false;

					fRot = fTarget;
					if (rand() % ENEMY_ATIME == 0)
					{
						if (pEnemy[set[0].nCntChar].nAction[0] == 0) { set[0].nNumMotion[2] = -1; }
						else if (pEnemy[set[0].nCntChar].nAction[0] == 1) { set[0].nNumMotion[2] = -2; }
					}
				}
				else if (nDistance == 1)
				{//�������Ȃ�@���U�� or �l�߂�(�X�e�b�v or �_�b�V��) or �l�q��(�X�e�b�v or �W�����v or �_�b�V�� or ����) 
					PointEnemy(&set[0], 2);

					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						pEnemy[set[0].nCntChar].nCntTime += 200;
						fRot = fTarget - D3DX_PI * 0.4f + (D3DX_PI * 0.8f) * (rand() % 2);
					}
					else
					{//���U��
						if (rand() % ENEMY_ATIME == 0)
						{
							pEnemy[set[0].nCntChar].nCntTime += 10000;
							set[0].nNumMotion[2] = -2;
						}
					}
				}
				else if (nDistance == 2)
				{//���������@�l�߂�(�X�e�b�v or �_�b�V��) �l�q��(�����@�_�b�V��)
					PointEnemy(&set[0], 3);
					if (pEnemy[set[0].nCntChar].nAction[0] == 0)
					{//�l�߂�
						pEnemy[set[0].nCntChar].nMaxTime = 120;
						fRot = fTarget;
					}
					else if (pEnemy[set[0].nCntChar].nAction[0] == 1)
					{//�l�q��
						if (pEnemy[set[0].nCntChar].nAction[1] < 0) { pEnemy[set[0].nCntChar].nAction[1] = rand() % 2; }
						pEnemy[set[0].nCntChar].nMaxTime = 80;

						if (pEnemy[set[0].nCntChar].nAction[1] == 0) { fRot = fTarget + D3DX_PI * 0.4f; }
						else { fRot = fTarget - D3DX_PI * 0.4f; }
					}
					else
					{//�ʏ�
						pEnemy[set[0].nCntChar].nMaxTime = 30;
						bMove = false;
					}
				}
				else
				{//�������@�����@�߂Â�
					fRot = fTarget;
				}
			}
		}
		else { bMove = false; }
		break;
	}

	set[0].bRun = false;
	UpdateSubEnemy(&set[0], &data[0], fRot, bMove);
}
//=============================================================================
// �G�̍X�V����
//=============================================================================
void PointEnemy(MODEL_SETTING *set, int nRand)
{
	ENEMY *pEnemy = GetEnemy();

	if (pEnemy[set[0].nCntChar].nCntTime > pEnemy[set[0].nCntChar].nMaxTime)
	{//�v�l�؂�ւ�
		pEnemy[set[0].nCntChar].nAction[0] = rand() % nRand;
		pEnemy[set[0].nCntChar].nAction[1] = -1;
		pEnemy[set[0].nCntChar].nAction[2] = -1;
		pEnemy[set[0].nCntChar].nCntTime = 0;
		pEnemy[set[0].nCntChar].nMaxTime = 0;
	}
}
//=============================================================================
// ���b�N�I������
//=============================================================================
void LockOn_MODEL(int nCount)
{
	int nCntModel;
	int nLockModel = -1;
	float fRot;
	int nLockChange = 0;
	D3DXVECTOR3 pos;
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();

	if (g_model_Info[nCount].set.nLockChar > -1)
	{//lock���̃L����������
		if (g_model_Info[g_model_Info[nCount].set.nLockChar].bUse == true && g_model_Info[g_model_Info[nCount].set.nLockChar].set.state != MODEL_STATE_DIE)
		{//���b�N�I���}�[�J�[�\���@�J�����␳
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (g_model_Info[g_model_Info[nCount].set.nLockChar].set.nAirTime > 5) { col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f); }
			SetZWindow(D3DXVECTOR3(g_model_Info[g_model_Info[nCount].set.nLockChar].set.pos.x
				, g_model_Info[g_model_Info[nCount].set.nLockChar].set.pos.y + 55.0f
				, g_model_Info[g_model_Info[nCount].set.nLockChar].set.pos.z)
				, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, 30, 30, 2, 0, WINDOWSTATE_Delete0, 0.0f);

			if (pPlayer[0].bButton[BUTTON_U] == false && pPlayer[0].bButton[BUTTON_O] == false)
			{//����{�^���������Ă��Ȃ��Ȃ�
			 //�p�x�v�Z
				pos = (g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 200.0f, 0.0f)) - g_model_Info[g_model_Info[nCount].set.nLockChar].set.pos;
				fRot = atan2f(pos.x, pos.z);
				fRot -= pCamera[0].rot.y;

				if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
				else if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2.0f; }
				pCamera[0].rot.y += fRot * 0.1f;//���������ŋl�߂�
				if (pCamera[0].rot.y > D3DX_PI) { pCamera[0].rot.y -= D3DX_PI * 2.0f; }
				else if (pCamera[0].rot.y < -D3DX_PI) { pCamera[0].rot.y += D3DX_PI * 2.0f; }

				fRot = atan2f(powf(pos.y, 2), powf(pos.x, 2) + powf(pos.z, 2));
				fRot -= pCamera[0].rot.x;

				if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
				else if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2.0f; }
				pCamera[0].rot.x += fRot * 0.1f;//���������ŋl�߂�
				if (pCamera[0].rot.x > 0.3f) { pCamera[0].rot.x = 0.3f; }
				else if (pCamera[0].rot.x < -0.3f) { pCamera[0].rot.x = -0.3f; }
			}

			if (pPlayer[0].bButton[BUTTON_E] == true)
			{
				g_model_Info[nCount].set.nLockChar = -1;
				PlaySound(SOUND_LABEL_LOCKOFF);
			}
			else if (pPlayer[0].bButton[BUTTON_X] == true) { nLockChange = -1; }
			else if (pPlayer[0].bButton[BUTTON_C] == true) { nLockChange = 1; }

			if (nLockChange != 0)
			{//�^�[�Q�b�g�ύX
				nCntModel = g_model_Info[nCount].set.nLockChar;
				while (1)
				{
					nCntModel += nLockChange;

					if (nCntModel < 0) { nCntModel = MAX_MODEL_INFO - 1; }
					if (nCntModel >= MAX_MODEL_INFO) { nCntModel = 0; }

					if (g_model_Info[nCntModel].bUse == true && nCntModel != nCount && g_model_Info[nCntModel].data.nLifePoint > 0 && g_model_Info[nCntModel].use != MODEL_USE_Pause)
					{//true�Ȃ�
						g_model_Info[nCount].set.nLockChar = nCntModel;
						PlaySound(SOUND_LABEL_LOCKOFF);

						break;
					}

				}
			}
		}
		else { g_model_Info[nCount].set.nLockChar = -1; }
	}
	else
	{//���b�N�I���ł�����̕\��
	 //�����̏ꏊ���玩���̌����ɒe����
		pos = g_model_Info[nCount].set.pos;
		pos -= D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * -100.0f;
		for (int nCntMove = 0; nCntMove < 3; nCntMove++)
		{
			pos += D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * -200.0f;
			for (nCntModel = 0; nCntModel < MAX_MODEL_INFO; nCntModel++)
			{//�S���f������]
				if (g_model_Info[nCntModel].bUse == true && nCntModel != nCount && g_model_Info[nCntModel].data.nLifePoint > 0 && g_model_Info[nCntModel].use != MODEL_USE_Pause)
				{//true�Ȃ�
					if (g_model_Info[nCntModel].set.pos.x + 200.0f > pos.x && g_model_Info[nCntModel].set.pos.x - 200.0f < pos.x &&
						g_model_Info[nCntModel].set.pos.z + 200.0f > pos.z && g_model_Info[nCntModel].set.pos.z - 200.0f < pos.z)
					{
						nLockModel = nCntModel;
						nCntMove = 3;
						break;
					}
				}//���݊m�F
			}//for����
		}
		if (nLockModel > -1)
		{//�������Ă���Ȃ�@�\�� and ���b�N�I��
			if (pPlayer[0].bButton[BUTTON_E] == true)
			{
				g_model_Info[nCount].set.nLockChar = nLockModel;
				PlaySound(SOUND_LABEL_LOCKON);
			}
			SetZWindow(D3DXVECTOR3(g_model_Info[nLockModel].set.pos.x, g_model_Info[nLockModel].set.pos.y + 55.0f, g_model_Info[nLockModel].set.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 1, 0, WINDOWSTATE_Delete0, 0.0f);
		}
	}
}
//=============================================================================
// ���b�N�I���@�U�����̏���
//=============================================================================
float ReturnAngle(MODEL_SETTING *set)
{//�ړI�ւ̊p�x��Ԃ�
	float fRot = set[0].rot.y;

	if (set[0].nLockChar > -1)
	{//���b�N�I�����Ă����
		MODEL_INFO *model = GetModel_Info();
		D3DXVECTOR3 pos = set[0].pos - model[set[0].nLockChar].set.pos;
		fRot = atan2f(pos.x, pos.z);
	}

	return fRot;
}
//=============================================================================
// �L�������m�̂����蔻��
//=============================================================================
void CollisionModel(int nCount)
{
	D3DXVECTOR3 Extent;		//�͈͌v�Z�p
	float		fLength;	//�ړI�܂ł̋���
	float		fExtent;	//�����ƖړI�̓�����͈�
	float		fRot;		//�p�x�v�Z�p

	for (int nCntModel = 0; nCntModel < MAX_MODEL_INFO; nCntModel++)
	{
		if (g_model_Info[nCntModel].bUse == true && nCntModel != nCount && g_model_Info[nCntModel].use != MODEL_USE_Pause)
		{//�g���Ă��郂�f���Ȃ�
		 //Y���͈͓�
			if (g_model_Info[nCntModel].set.pos.y < g_model_Info[nCount].set.pos.y + g_model_Info[nCount].set.fHeight &&
				g_model_Info[nCntModel].set.pos.y > g_model_Info[nCount].set.pos.y - g_model_Info[nCntModel].set.fHeight)
			{
				//�����̉~���ɓ����Ă�����o��
				Extent = g_model_Info[nCntModel].set.pos - g_model_Info[nCount].set.pos;
				fLength = powf(Extent.x, 2) + powf(Extent.z, 2);
				fExtent = powf(g_model_Info[nCntModel].set.fSlength + g_model_Info[nCount].set.fSlength, 2);
				if (fLength < fExtent)
				{//�͈͓�
				 //�����ƖړI�̊p�x�v�Z
					fRot = atan2f(Extent.x, Extent.z);
					//move�̔{���ቺ
					g_model_Info[nCount].set.move.x *= 0.5f;
					g_model_Info[nCount].set.move.z *= 0.5f;

					if (g_model_Info[nCntModel].set.pos.y + g_model_Info[nCntModel].set.fHeight < g_model_Info[nCount].set.pos.y + (g_model_Info[nCntModel].set.fHeight / 2))
					{//��̂ق��Ȃ�move����
						g_model_Info[nCntModel].set.move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * ((fExtent - fLength) * 0.01f);
					}
					else
					{//�p�x�ɉ����ďꏊ�̈ړ�
						g_model_Info[nCount].set.pos =
							D3DXVECTOR3(g_model_Info[nCntModel].set.pos.x, g_model_Info[nCount].set.pos.y, g_model_Info[nCntModel].set.pos.z)
							+ D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -g_model_Info[nCntModel].set.fSlength	//�ړI�͈͕̔�
							+ D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -g_model_Info[nCount].set.fSlength;	//�����͈͕̔�
					}
				}
			}
		}
	}
}
//=============================================================================
// �߂��݂̃G���[�Ώ��p
//=============================================================================
void SadnessError(int nCount)
{
	if (g_model_Info[nCount].set.pos.y < -1000)
	{
		g_model_Info[nCount].set.pos = g_model_Info[nCount].set.Initpos;
		g_model_Info[nCount].set.posold = g_model_Info[nCount].set.Initpos;
		g_model_Info[nCount].set.bJump = false;
	}
}
//=============================================================================
// ���[�V�����̍X�V
//=============================================================================
void UpdateMotion(int nCount)
{
	int nCntModel;
	D3DXVECTOR3 Move;
	float fFastPlus = 0.0;
	float fCancelPlus = 0.0f;
	float fEndPlus = 0.0f;

	if (g_model_Info[nCount].set.nNumMotion[0] >= 0)
	{//MOTION�����L
		if (g_model_Info[nCount].set.nCntState > 0)
		{//�X�e�[�g�Ǘ�
			g_model_Info[nCount].set.nCntState--;
			if (g_model_Info[nCount].set.nCntState == 0 && g_model_Info[nCount].set.state == MODEL_STATE_DAMAGE && g_model_Info[nCount].set.bJump == true && g_model_Info[nCount].set.nNumMotion[1] == MOTION_SHRINK)
			{
				g_model_Info[nCount].set.state = MODEL_STATE_NONE; g_model_Info[nCount].set.nNumMotion[1] = 0; g_model_Info[nCount].set.nNumMotion[3] = -1;
			}
		}
		if (g_model_Info[nCount].set.state == MODEL_STATE_NONE)
		{//�X�L���̎g�p�m�F
			g_model_Info[nCount].data.nSkill[0][4] = -1;
			g_model_Info[nCount].data.nSkill[1][4] = -1;
		}
		if (g_model_Info[nCount].set.nAirTime > 0) { g_model_Info[nCount].set.nAirTime--; }

		if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
		{
			g_model_Info[nCount].set.nPlayTime--;
			if (g_model_Info[nCount].set.nPlayTime == 0) { UpdateEnemy(&g_model_Info[nCount].set, &g_model_Info[nCount].data, g_model_Info[nCount].use, 1); }
		}//�G�̎v�l

		if (g_model_Info[nCount].set.nNumMotion[2] == -3)
		{//�X�L���㕪��
			if (g_model_Info[nCount].set.nNumMotion[1] != MOTION_SHRINK && g_model_Info[nCount].set.nNumMotion[1] != MOTION_DOWN)
			{//����, �_�E���łȂ��Ȃ�
				if (g_model_Info[nCount].set.nSkillTime[0] < 0 && g_model_Info[nCount].data.nSkillPoint >= MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[0][0]].key[0].nAtkEffect))
				{//���Ԍo�ߍς݂Ȃ�
					g_model_Info[nCount].set.nNumMotion[1] = g_model_Info[nCount].data.nSkill[0][0]; g_model_Info[nCount].set.nNumMotion[3] = -11;
					g_model_Info[nCount].data.nSkill[0][4] = 1;
					if (g_model_Info[nCount].set.state != MODEL_STATE_ATKHIT) { g_model_Info[nCount].set.state = MODEL_STATE_ATK; }	//��x�q�b�g���Ă���Ες��Ȃ�
					g_model_Info[nCount].set.rot.y = ReturnAngle(&g_model_Info[nCount].set);//���b�N�I�����Ă���Ίp�x�����킹��
					g_model_Info[nCount].set.angle.y = g_model_Info[nCount].set.rot.y;
				}
				else { g_model_Info[nCount].set.nNumMotion[2] = 0; }//���s��
			}
			else { g_model_Info[nCount].set.nNumMotion[2] = 0; }
		}

		if (g_model_Info[nCount].set.nNumMotion[2] == -4)
		{//�X�L��������
			if (g_model_Info[nCount].set.nNumMotion[1] != MOTION_SHRINK && g_model_Info[nCount].set.nNumMotion[1] != MOTION_DOWN)
			{//����, �_�E���łȂ��Ȃ�
				if (g_model_Info[nCount].set.nSkillTime[1] < 0 && g_model_Info[nCount].data.nSkillPoint >= MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[1][0]].key[0].nAtkEffect))
				{//���Ԍo�ߍς݂Ȃ�
					g_model_Info[nCount].set.nNumMotion[1] = g_model_Info[nCount].data.nSkill[1][0]; g_model_Info[nCount].set.nNumMotion[3] = -12;
					g_model_Info[nCount].data.nSkill[1][4] = 1;
					if (g_model_Info[nCount].set.state != MODEL_STATE_ATKHIT) { g_model_Info[nCount].set.state = MODEL_STATE_ATK; }	//��x�q�b�g���Ă���Ες��Ȃ�
					g_model_Info[nCount].set.rot.y = ReturnAngle(&g_model_Info[nCount].set);//���b�N�I�����Ă���Ίp�x�����킹��
					g_model_Info[nCount].set.angle.y = g_model_Info[nCount].set.rot.y;
				}
				else { g_model_Info[nCount].set.nNumMotion[2] = 0; }//���s��
			}
			else { g_model_Info[nCount].set.nNumMotion[2] = 0; }
		}

		if (g_model_Info[nCount].set.nMotionFrame > g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nCancel[0] &&
			g_model_Info[nCount].set.nMotionFrame <= g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nCancel[1] &&
			g_model_Info[nCount].set.nNumMotion[3] >= 0 && g_model_Info[nCount].set.state != MODEL_STATE_POISED)
		{//�\�t���[�� && �L�����Z���\�񖳂�

		 //	�G�̍s��
			if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z) { UpdateEnemy(&g_model_Info[nCount].set, &g_model_Info[nCount].data, g_model_Info[nCount].use, 0); }//�G�̎v�l

			if (g_model_Info[nCount].set.nNumMotion[2] != 0 && g_model_Info[nCount].set.nNumMotion[2] != -99 && g_model_Info[nCount].set.nNumMotion[2] != g_model_Info[nCount].set.nNumMotion[1])
			{//�o�^���[�V�������j���[�g�����łȂ� && �o�^���[�V���������݂Ɠ����łȂ�
				if (g_model_Info[nCount].set.nNumMotion[2] == -1)
				{//��U������
					if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[1] != -1)
					{//�L�����Z���g������� 
						if (g_model_Info[nCount].set.state == MODEL_STATE_GUARD)
						{//�K�[�h�������󒆂ƒn��ŕ�����
							if (g_model_Info[nCount].set.bJump == true) { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][0].nBranch[1]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
							else { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][MOTION_AIR].nBranch[1]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
						}
						else { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[1]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
						if (g_model_Info[nCount].set.state != MODEL_STATE_ATKHIT) { g_model_Info[nCount].set.state = MODEL_STATE_ATK; }	//��x�q�b�g���Ă���Ες��Ȃ�
						g_model_Info[nCount].set.rot.y = ReturnAngle(&g_model_Info[nCount].set);//���b�N�I�����Ă���Ίp�x�����킹��
						g_model_Info[nCount].set.angle.y = g_model_Info[nCount].set.rot.y;
					}
				}
				else if (g_model_Info[nCount].set.nNumMotion[2] == -2)
				{
					if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[2] != -1)
					{//�L�����Z���g������� 
						if (g_model_Info[nCount].set.state == MODEL_STATE_GUARD)
						{//�K�[�h�������󒆂ƒn��ŕ�����
							if (g_model_Info[nCount].set.bJump == true) { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][0].nBranch[2]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
							else { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][MOTION_AIR].nBranch[2]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
						}
						else { g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[2]; g_model_Info[nCount].set.nNumMotion[3] = -1; }
						if (g_model_Info[nCount].set.state != MODEL_STATE_ATKHIT) { g_model_Info[nCount].set.state = MODEL_STATE_ATK; }	//��x�q�b�g���Ă���Ες��Ȃ�
						g_model_Info[nCount].set.rot.y = ReturnAngle(&g_model_Info[nCount].set);//���b�N�I�����Ă���Ίp�x�����킹��
						g_model_Info[nCount].set.angle.y = g_model_Info[nCount].set.rot.y;
					}
				}//���U������
				else
				{//�X�L��, �K�[�h, �X�e�b�v����
					if (g_model_Info[nCount].set.nNumMotion[2] == MOTION_LANDING)
					{//�W�����v����
						if (g_model_Info[nCount].set.state != MODEL_STATE_ATK && (g_model_Info[nCount].set.state != MODEL_STATE_ATKHIT || g_model_Info[nCount].set.nNumMotion[1] == MOTION_STEP))
						{//�U�����̓_���@�q�b�g���X�e�b�v���Ȃ炨��
							if (g_model_Info[nCount].set.bJump == true)
							{
								g_model_Info[nCount].set.nNumMotion[1] = MOTION_LANDING; g_model_Info[nCount].set.nNumMotion[3] = -1; g_model_Info[nCount].data.nStamina -= 30;
								if (g_model_Info[nCount].data.nStamina < -1) { g_model_Info[nCount].data.nStamina = -20; }
							}
						}
					}
					else if (g_model_Info[nCount].set.nNumMotion[2] == MOTION_STEP)
					{//�X�e�b�v����
						if (g_model_Info[nCount].set.state != MODEL_STATE_ATK && g_model_Info[nCount].data.nStamina > -1)
						{//�U�����̓_���@�q�b�g���͂�낵��
							if (g_model_Info[nCount].set.bJump == false && g_model_Info[nCount].set.bStep == true)
							{
								g_model_Info[nCount].set.nNumMotion[1] = MOTION_STEPS; g_model_Info[nCount].set.nNumMotion[3] = -1; g_model_Info[nCount].set.bStep = false; g_model_Info[nCount].set.nLeg = 2;
								g_model_Info[nCount].data.nStamina -= 30; if (g_model_Info[nCount].data.nStamina < -1) { g_model_Info[nCount].data.nStamina = -30; }
							}
							else if (g_model_Info[nCount].set.bJump == true)
							{
								g_model_Info[nCount].set.nNumMotion[1] = MOTION_STEP; g_model_Info[nCount].set.nNumMotion[3] = -1; g_model_Info[nCount].set.nLeg = 2;
								g_model_Info[nCount].data.nStamina -= 30; if (g_model_Info[nCount].data.nStamina < -1) { g_model_Info[nCount].data.nStamina = -30; }
							}

						}
					}
					else if (g_model_Info[nCount].set.nNumMotion[2] == MOTION_GUARD)
					{//�K�[�h����
						if (g_model_Info[nCount].set.state != MODEL_STATE_ATK)
						{//�U�����̓_���@�q�b�g���͂�낵��
							g_model_Info[nCount].set.nNumMotion[1] = MOTION_GUARD; g_model_Info[nCount].set.nNumMotion[3] = -1;
							g_model_Info[nCount].set.state = MODEL_STATE_POISED; g_model_Info[nCount].set.nCntState = 35;
							PlaySound(SOUND_LABEL_GUARD000);
						}
					}//����ȊO
					else
					{
						g_model_Info[nCount].set.nNumMotion[1] = g_model_Info[nCount].set.nNumMotion[2]; g_model_Info[nCount].set.nNumMotion[3] = -1;
					}
				}
			}
			else if (g_model_Info[nCount].set.nNumMotion[1] <= MOTION_LAND)
			{//�j���[�g����, ����, ����, ���n�Ȃ� move�œ���ւ�

				if (g_model_Info[nCount].set.move.x * g_model_Info[nCount].set.move.x + g_model_Info[nCount].set.move.z * g_model_Info[nCount].set.move.z >= 0.3f)
				{
					if ((g_model_Info[nCount].set.nNumMotion[4] == 0) || g_model_Info[nCount].set.nNumMotion[1] == 0)
					{
						if ((g_model_Info[nCount].set.bRun == true && g_model_Info[nCount].set.nNumMotion[1] != 2) || g_model_Info[nCount].set.nNumMotion[2] == -99) { g_model_Info[nCount].set.nLeg = g_model_Info[nCount].set.nNumMotion[3]; g_model_Info[nCount].set.nNumMotion[1] = 2; g_model_Info[nCount].set.nNumMotion[3] = -1; }//����
						else if (g_model_Info[nCount].set.bRun == false && g_model_Info[nCount].set.nNumMotion[1] != 1) { g_model_Info[nCount].set.nLeg = g_model_Info[nCount].set.nNumMotion[3]; g_model_Info[nCount].set.nNumMotion[1] = 1; g_model_Info[nCount].set.nNumMotion[3] = -1; }//����
					}
				}
				else if (g_model_Info[nCount].set.move.x * g_model_Info[nCount].set.move.x + g_model_Info[nCount].set.move.z * g_model_Info[nCount].set.move.z < 0.3f && g_model_Info[nCount].set.nNumMotion[1] != MOTION_LAND && g_model_Info[nCount].set.nNumMotion[1] != 0)
				{//�j���[�g���� && ���n���[�V��������Ȃ�
					if (g_model_Info[nCount].set.nNumMotion[1] == 1 || g_model_Info[nCount].set.nNumMotion[1] == 2)
					{//����������Ȃ�
						if (g_model_Info[nCount].set.nNumMotion[4] < 2)
						{
							g_model_Info[nCount].set.nLeg = g_model_Info[nCount].set.nNumMotion[3];
							g_model_Info[nCount].set.nNumMotion[1] = 0; g_model_Info[nCount].set.nNumMotion[3] = -1;
						}
					}
					//else { set[0].nNumMotion[1] = 0; set[0].nNumMotion[3] = -1; }
				}//���n�łȂ��Ȃ�~�܂�
			}
		}

		if (g_model_Info[nCount].set.nNumMotion[3] < 0)
		{//�L�����Z�����ꂽ�Ȃ�
			g_model_Info[nCount].set.nNumMotion[2] = 0;	//���̎����j���[�g������
			g_model_Info[nCount].set.nNumMotion[4] = -1;
			if (g_model_Info[nCount].set.nNumMotion[1] != 0) { fCancelPlus = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[5]].fCancelFreame; }
			g_model_Info[nCount].set.nNumMotion[4] -= (int)fCancelPlus;	//�t���[���̏����� +�Ȃ�x��-�Ȃ瑁���Ȃ�
			g_model_Info[nCount].set.nMotionFrame = 0;	//�S�t���[���̏�����
			if (g_model_Info[nCount].set.nNumMotion[3] < -10)
			{//�X�L���Ȃ�
				g_model_Info[nCount].set.nNumMotion[4] = -1;
				PlaySound(SOUND_LABEL_SKILL);
				SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 250, 10, 1, 5, 1, 1, ANIMATION_NORMAL);
				if (g_model_Info[nCount].set.nNumMotion[3] == -11)
				{
					g_model_Info[nCount].data.nSkillPoint -= MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[0][0]].key[0].nAtkEffect);
					g_model_Info[nCount].set.nSkillTime[0] = 200;
				}
				else
				{
					g_model_Info[nCount].data.nSkillPoint -= MotionSkill(g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].data.nSkill[1][0]].key[0].nAtkEffect);
					g_model_Info[nCount].set.nSkillTime[1] = 200;
				}

				if (g_model_Info[nCount].set.state == MODEL_STATE_ATKHIT) { g_model_Info[nCount].set.nNumMotion[3] = 1; g_model_Info[nCount].set.nNumMotion[4] = 9999; }
				g_model_Info[nCount].set.nNumMotion[3] = 0;	//�L�[�̏�����	
			}
			else { g_model_Info[nCount].set.nNumMotion[3] = 0; }	//�L�[�̏�����	

			if (g_model_Info[nCount].set.nNumMotion[1] == 1 || g_model_Info[nCount].set.nNumMotion[1] == 2) { g_model_Info[nCount].set.nNumMotion[3] = g_model_Info[nCount].set.nLeg; } //�����Ƒ���̏ꍇ
			if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame < 0) { g_model_Info[nCount].set.nNumMotion[4] -= (int)g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame; }
			g_model_Info[nCount].set.addPosmove = (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].pos - g_model_Info[nCount].set.addpos)
				/ (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fFrame
					+ g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame
					+ fCancelPlus);
			for (nCntModel = 0; nCntModel < g_model_Info[nCount].set.nMaxModel; nCntModel++)
			{//move���v�Z���đ��
				g_model_Info[nCount].set.parent[nCntModel].addRotmove = (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].rot[nCntModel] - g_model_Info[nCount].set.parent[nCntModel].addrot);

				//�p�x�m�F
				if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.x > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.x -= D3DX_PI * 2; }
				else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.x < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.x += D3DX_PI * 2; }
				if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.y > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.y -= D3DX_PI * 2; }
				else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.y < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.y += D3DX_PI * 2; }
				if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.z > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.z -= D3DX_PI * 2; }
				else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.z < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.z += D3DX_PI * 2; }

				g_model_Info[nCount].set.parent[nCntModel].addRotmove /= (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fFrame
					+ g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame
					+ fCancelPlus);
			}
			MotionEffect_S(-1, nCount);
			g_model_Info[nCount].set.nNumMotion[5] = g_model_Info[nCount].set.nNumMotion[1]; //���̃��[�V�����Ɍ��݂̃��[�V����������
			if (g_model_Info[nCount].set.nNumMotion[1] < 3) { g_model_Info[nCount].set.state = MODEL_STATE_NONE; }	//�j���[�g�����Ȃ�
			if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 50; }	//�N���オ��Ȃ�
			if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_STEP || g_model_Info[nCount].set.nNumMotion[1] == MOTION_STEPS)
			{//�X�e�b�v�Ȃ�@�p�x���킹 ���ɂ���ă��[�V�����؂�ւ��H
				g_model_Info[nCount].set.rot = g_model_Info[nCount].set.angle;
			}

		}

		g_model_Info[nCount].set.nNumMotion[4] += 1;	//�t���[���̐i�s

		while (1)
		{
			if (g_model_Info[nCount].set.nNumMotion[4] < g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fFrame)
			{//�t���[�����͈͓��Ȃ�
				if (g_model_Info[nCount].set.nNumMotion[4] > 0) { g_model_Info[nCount].set.nMotionFrame++; }//���[�V�����S�̃t���[���̐i�s
				g_model_Info[nCount].set.move.x -= g_model_Info[nCount].set.move.x * (0.3f * g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fSlip);
				g_model_Info[nCount].set.move.z -= g_model_Info[nCount].set.move.z * (0.3f * g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fSlip);
				MotionEffect_S(g_model_Info[nCount].set.nMotionFrame, nCount);

				//�ړ��l���Z�L���t���[���Ȃ�
				if (g_model_Info[nCount].set.nNumMotion[4] < g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].nMuse)
				{
					float fRot = g_model_Info[nCount].set.rot.y;
					if (g_model_Info[nCount].set.nNumMotion[1] != MOTION_STEP && g_model_Info[nCount].set.nNumMotion[1] != MOTION_STEPS)
					{
						fRot = ReturnAngle(&g_model_Info[nCount].set);
					}//���b�N�I�����Ă���Ίp�x�����킹��
					Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					Move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].move.z;
					Move += D3DXVECTOR3(sinf(fRot + D3DX_PI * 0.5f), 0.0f, cosf(fRot + D3DX_PI * 0.5f)) * -g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].move.x;
					Move.y += g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].move.y;
					if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].move.y > 0.0f)
					{
						g_model_Info[nCount].set.bJump = false;
					}
					if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_STEP || g_model_Info[nCount].set.nNumMotion[1] == MOTION_STEPS)
					{
						Move.x *= (1.0f + g_model_Info[nCount].data.status.fSpeed * 0.00003f);
						Move.z *= (1.0f + g_model_Info[nCount].data.status.fSpeed * 0.00003f);
					}
					if (g_model_Info[nCount].data.nStamina < 0) { Move *= 0.5f; }
					g_model_Info[nCount].set.move += Move;
				}

				g_model_Info[nCount].set.addpos += g_model_Info[nCount].set.addPosmove;		//�{�̂̈ړ�
				for (nCntModel = 0; nCntModel < g_model_Info[nCount].set.nMaxModel; nCntModel++)
				{//�ۑ����ꂽmove��������
				 //rot�̈ړ��l���Z
					g_model_Info[nCount].set.parent[nCntModel].addrot += g_model_Info[nCount].set.parent[nCntModel].addRotmove;
					//���b�g�m�F
					if (g_model_Info[nCount].set.parent[nCntModel].addrot.x > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.x -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addrot.x < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.x += D3DX_PI * 2; }
					if (g_model_Info[nCount].set.parent[nCntModel].addrot.y > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.y -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addrot.y < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.y += D3DX_PI * 2; }
					if (g_model_Info[nCount].set.parent[nCntModel].addrot.z > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.z -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addrot.z < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addrot.z += D3DX_PI * 2; }
				}
				break;
			}
			else
			{//�L�[�̏I��
				g_model_Info[nCount].set.nNumMotion[4] = 0;	//�t���[���̏�����
				g_model_Info[nCount].set.nNumMotion[3]++;		//�L�[�̐i��

				if (g_model_Info[nCount].set.nNumMotion[3] >= g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nKey)
				{//���̃��[�V�������I��
					g_model_Info[nCount].set.angle = g_model_Info[nCount].set.rot;
					g_model_Info[nCount].set.nMotionFrame = 0;						//�S�t���[���̏�����
					if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[0] > -1)
					{
						g_model_Info[nCount].set.nNumMotion[3] = 0;						//�L�[�̏�����
						if (g_model_Info[nCount].set.nNumMotion[1] != g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[0])
						{//���[�v����Ȃ����
							fEndPlus = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fEndFreame;
							g_model_Info[nCount].set.nNumMotion[4] = (int)fEndPlus;
							g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[0];	//���̃��[�V�����̕t�^
							if (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame < 0) { g_model_Info[nCount].set.nNumMotion[4] -= (int)g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame; }
							fFastPlus = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].fFastFrame;
							if (g_model_Info[nCount].set.nNumMotion[1] == 0) { g_model_Info[nCount].set.state = MODEL_STATE_NONE; }	//�j���[�g�����Ȃ�
							if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 90; }	//�N���オ��Ȃ�
						}
						else
						{
							g_model_Info[nCount].set.nNumMotion[1] = g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].nBranch[0];
							if (g_model_Info[nCount].set.nNumMotion[1] == 0 || g_model_Info[nCount].set.nNumMotion[1] == MOTION_AIR)
							{
								g_model_Info[nCount].set.state = MODEL_STATE_NONE;
							}	//�j���[�g�����Ȃ�
						}	//���̃��[�V�����̕t�^}
						g_model_Info[nCount].set.nNumMotion[5] = g_model_Info[nCount].set.nNumMotion[1]; //���̃��[�V�����Ɍ��݂̃��[�V����������
					}
					else
					{//���̃L�[�ݒ肪����Ă��Ȃ��Ȃ炻�̂܂ܕ��u
						g_model_Info[nCount].set.nNumMotion[3]--;						//�L�[�̏�����
						g_model_Info[nCount].set.nNumMotion[4] = 0;
					}
				}
				MotionEffect_S(-1, nCount);

				g_model_Info[nCount].set.addPosmove = (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].pos - g_model_Info[nCount].set.addpos)
					/ (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fFrame
						+ fFastPlus
						- fEndPlus);
				for (nCntModel = 0; nCntModel < g_model_Info[nCount].set.nMaxModel; nCntModel++)
				{//move���v�Z���đ��
					g_model_Info[nCount].set.parent[nCntModel].addRotmove = (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].rot[nCntModel] - g_model_Info[nCount].set.parent[nCntModel].addrot);

					//�p�x�m�F
					if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.x > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.x -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.x < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.x += D3DX_PI * 2; }
					if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.y > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.y -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.y < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.y += D3DX_PI * 2; }
					if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.z > D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.z -= D3DX_PI * 2; }
					else if (g_model_Info[nCount].set.parent[nCntModel].addRotmove.z < -D3DX_PI) { g_model_Info[nCount].set.parent[nCntModel].addRotmove.z += D3DX_PI * 2; }

					g_model_Info[nCount].set.parent[nCntModel].addRotmove /= g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].fFrame
						+ fFastPlus - fEndPlus;
				}
			}//�L�[�I��
		}//�X�Vwhile
	}//���[�V�����g�p�m�F
}
//=============================================================================
// ���[�V������Reset
//=============================================================================
void ResetMotion(MODEL_SETTING *set)
{
	set[0].nNumMotion[1] = 0;
	set[0].nNumMotion[2] = 0;
	set[0].nNumMotion[3] = -1;
	set[0].nNumMotion[4] = 0;
	set[0].nNumMotion[5] = 0;

	set[0].addpos = g_model_motion[set[0].nNumMotion[0]][0].key[1].pos;
	for (int nCntModel = 0; nCntModel < set[0].nMaxModel; nCntModel++)
	{//move���v�Z���đ��
		set[0].parent[nCntModel].addrot = g_model_motion[set[0].nNumMotion[0]][0].key[1].rot[nCntModel];
	}
}
//=============================================================================
// ���[�V�����̌��� �U����
//=============================================================================
int MotionSkill(int nCntMotion)
{
	switch (nCntMotion)
	{
	case -2:
		return 920;
	case -3:
		return 680;
	case -4:
		return 800;
	case -5:
		return 2850;
	case -6:
		return 2550;
	case -7:
		return 2150;

	case -24:
		return 3000;
	case -25:
		return 9500;
	case -26:
		return 3000;
	case -27:
		return 6000;
	case -28:
		return 8000;
	case -29:
		return 10000;
	case -31://���e�I
		return 11500;
	case -32://����
		return 8000;
	case -33://����
		return 6000;
	case -34://����
		return 7000;
	case -35:
		return 0;
	case -36:
		return 8000;
	case -37:
		return 11000;
	case -38:
		return 12000;
	}
	return 0;
}

//=============================================================================
// ���[�V�����̌��� �U����
//=============================================================================
void MotionEffect_A(int nCount, int nEnemy, float fAtk, float *fHeel, float *fPredator)
{
	Camera *pCamera = GetCamera();

	switch (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].nAtkEffect)
	{//���[�V�������Ƃ̌���
	case 0://
		SetAnimation(g_model_Info[nEnemy].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), 300, 300, 5, 2, 5, 4, 1, ANIMATION_NORMAL);
		break;
	case 1://
		SetAnimation(g_model_Info[nEnemy].set.pos + D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 2, 10, 3, 5, 1, ANIMATION_NORMAL);
		PlaySound(SOUND_LABEL_ATTACK002);
		break;
	case 9:	//�ߐH
		fPredator[0] = 1000.0f;
		break;
	case 24:	//�ߐH
		fPredator[0] = 100000.0f;
		break;

	case 200:	//�U���^
		SetZWindow(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 250, 4, 2, WINDOWSTATE_FADE_Z, 0.02f);
		break;
	}
}

//=============================================================================
// ���[�V�����̌��� �T�E���h, ������
//=============================================================================
void MotionEffect_S(int nMode, int nCount)
{
	Camera *pCamera = GetCamera();
	float fState;

	switch (g_model_motion[g_model_Info[nCount].set.nNumMotion[0]][g_model_Info[nCount].set.nNumMotion[1]].key[g_model_Info[nCount].set.nNumMotion[3]].nShowEffect)
	{//���[�V�������Ƃ̌���
	case 0:	//����
			//PlaySound(SOUND_LABEL_ATTACK000);
		break;
	case 1:	//����
			//PlaySound(SOUND_LABEL_ATTACK000);
		break;
	case 2:	//�U�����ʉ�
		if (nMode == -1) { PlaySound(SOUND_LABEL_ATTACK000); }

		break;
	case 3:	//�W�����v
		if (nMode == -1) { PlaySound(SOUND_LABEL_DASH000); }
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.93f, 0.1f), 200, 200, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		break;
	case 4:	//�u�[�X�g
		if (nMode == -1) { PlaySound(SOUND_LABEL_DASH000); }
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.98f, 0.0f, 0.1f), 200, 200, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		break;
	case 5:	//���؂���ʉ�
		if (nMode == -1) { PlaySound(SOUND_LABEL_TitleSE000); }
		break;
	case 6:	//����
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_ATTACK001);
			SetAnimation(D3DXVECTOR3(g_model_Info[nCount].set.parent[2].mtxWorldModel._41, g_model_Info[nCount].set.parent[2].mtxWorldModel._42, g_model_Info[nCount].set.parent[2].mtxWorldModel._43), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 250, 250, 8, 1, 2, 6, 1, ANIMATION_UP);
		}//SetAnimation(D3DXVECTOR3(set[0].parent[2].mtxWorldModel._41, set[0].parent[2].mtxWorldModel._42, set[0].parent[2].mtxWorldModel._43), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 100, 100, 8, 1, 2, 6, ANIMATION_UP);
		break;
	case 7:	//�W�����v
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.93f, 0.1f), 200, 200, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		break;
	case 8:	//�u�[�X�g
		if (nMode % 2 == 0)
		{
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.98f, 0.0f, 0.1f), 200, 200, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
		}
		break;
	case 9:	//�ߐH
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_SKILL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 150, 150, 10, 1, 3, 1, 1, ANIMATION_NORMAL);
		}
		break;
	case 10:	//�ǉ�����
		if (nMode == -1)
		{
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }
		}
		break;
	case 30:	//�W�����v
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_ATTACK400);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 6, 6, 1, ANIMATION_NORMAL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130, 8, 1, 1, 6, 1, ANIMATION_UP);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 6, 9, 10, ANIMATION_NORMAL);
		}
		break;
	case 40://���e�I�H
	{
		if (nMode == -1)
		{
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }

			SetBullet(g_model_Info[nCount].set.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 12.5f, 30.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 9.15f, 90.0f, 1.0f, 90, 0, 99999, 40, 40, -1, nCount);
		}
	}
	break;
	case 42:	//����
		if (nMode == -1)
		{
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }

			fState = g_model_Info[nCount].set.rot.y - D3DX_PI * 0.3f;
			for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
			{
				fState += D3DX_PI * 0.15f;
				SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(fState) * -100.0f, 50.0f, (cosf(fState) * -100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * -0.5f, fState, 0.0f),
					D3DXVECTOR3(0.0f, 4.5f, 50.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 3.55f, 80.0f, 1.0f, 60, 6, 99999, 42, 42, -1, nCount);
			}
		}
		break;
	case 43:	//����
		if (nMode == -1)
		{
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }

			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * 50.0f, 50.0f, cosf(g_model_Info[nCount].set.rot.y) * 50.0f), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -8.0f, 0.0f, cosf(g_model_Info[nCount].set.rot.y) * -8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 8.8f, 25.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 6.45f, 150.0f, 0.0f, 60, 4, 99999, 43, 43, -1, nCount);
		}
		break;
	case 44:	//����
		if (nMode == -1)
		{
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }

			PlaySound(SOUND_LABEL_ATTACK400);
			fState = g_model_Info[nCount].set.rot.y;
			for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
			{
				fState += D3DX_PI * 0.5f;
				SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(fState) * -100.0f, 50.0f, (cosf(fState) * -100.0f)), D3DXCOLOR(1.0f, 0.12f, 0.05f, 1.0f), 100, 100, 5, 5, 2, 8, 1, ANIMATION_NORMAL);
				SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(fState) * -100.0f, 50.0f, (cosf(fState) * -100.0f)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 4, 6, 1, ANIMATION_NORMAL);
				SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(fState) * -100.0f, 50.0f, (cosf(fState) * -100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 7.5f, 80.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 9.15f, 80.0f, 1.0f, 31, 1, 99999, 400, 400, -1, nCount);
			}
		}
		break;
	case 45:	//����
		if (nMode == -1)
		{//������HP1��, NORMAL�^�� ���͂̓G��HP1
			if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
			if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }

			SetBullet(g_model_Info[nCount].set.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 16.0f, 0.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.0f, 9999.9f, 1.0f, 2, 1, 99999, 45, 45, -1, nCount);

			SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEOUT, WINDOWUSE_NORMAL);

			g_model_Info[nCount].data.nLifePoint = 1;
			g_model_Info[nCount].data.nSkillPoint = 0;

			//NORMAL�^
			Set_P_NOR(&g_model_Info[nCount].set);
			//���[�V������Reset
			ResetMotion(&g_model_Info[nCount].set);
			CollisionObject_Plus(&g_model_Info[nCount].set);

			char aStr[48];
			int nLength;
			MODEL_MOTION *pMotion = GetModel_Motion();

			wsprintf(&aStr[0], "%d SP\n", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[0][0]].key[0].nAtkEffect));
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[0][0]);
			ChangeFont(true, &aStr[0], 5, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			wsprintf(&aStr[0], "");
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[1][0]);
			nLength = (int)strlen(&aStr[0]);
			wsprintf(&aStr[nLength], "\n%d SP", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[1][0]].key[0].nAtkEffect));
			ChangeFont(true, &aStr[0], 6, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	case 46:	//�ϐg
		if (nMode == -1)
		{
			SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEOUT, WINDOWUSE_NORMAL);
			g_model_Info[nCount].data.nSkill[0][0] = -1;
			g_model_Info[nCount].data.nSkill[1][0] = -1;
			//�X�e�[�^�X�ŕ���
			int nEvolve = rand() % 8;
			switch (nEvolve)
			{
			case 0:
				Set_P_NOR(&g_model_Info[nCount].set);
				break;
			case 1:
				Set_P_ATK(&g_model_Info[nCount].set);
				break;
			case 2:
				Set_P_INT(&g_model_Info[nCount].set);
				break;
			case 3:
				Set_P_SPD(&g_model_Info[nCount].set);
				break;
			case 4:
				Set_E_KING(&g_model_Info[nCount].set);
				break;
			case 5:
				Set_E_WARRIOR(&g_model_Info[nCount].set);
				break;
			case 6:
				Set_E_NINJA(&g_model_Info[nCount].set);
				break;
			case 7:
				Set_E_WIZARD(&g_model_Info[nCount].set);
				break;
			}

			//���[�V������Reset
			ResetMotion(&g_model_Info[nCount].set);
			CollisionObject_Plus(&g_model_Info[nCount].set);

			char aStr[48];
			int nLength;
			MODEL_MOTION *pMotion = GetModel_Motion();

			wsprintf(&aStr[0], "%d SP\n", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[0][0]].key[0].nAtkEffect));
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[0][0]);
			ChangeFont(true, &aStr[0], 5, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			wsprintf(&aStr[0], "");
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[1][0]);
			nLength = (int)strlen(&aStr[0]);
			wsprintf(&aStr[nLength], "\n%d SP", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[1][0]].key[0].nAtkEffect));
			ChangeFont(true, &aStr[0], 6, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	case 50:	//�q�[��
		if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
		if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }
		g_model_Info[0].data.nLifePoint += 30000;
		if (g_model_Info[0].data.nLifePoint > (int)g_model_Info[0].data.status.fLifePoint)
		{
			g_model_Info[0].data.nLifePoint = (int)g_model_Info[0].data.status.fLifePoint;
		}
		break;
	case 51:	//���K�q�[��
		if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
		if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }
		g_model_Info[0].data.nLifePoint += 60000;
		if (g_model_Info[0].data.nLifePoint > (int)g_model_Info[0].data.status.fLifePoint)
		{
			g_model_Info[0].data.nLifePoint = (int)g_model_Info[0].data.status.fLifePoint;
		}
		break;
	case 52:	//�M�K�q�[��
		if (g_model_Info[nCount].data.nSkill[0][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[0][0], nCount); }
		if (g_model_Info[nCount].data.nSkill[1][4] > 0) { SkillEffect_S(&g_model_Info[nCount].data.nSkill[1][0], nCount); }
		g_model_Info[0].data.nLifePoint += 100000;
		if (g_model_Info[0].data.nLifePoint > (int)g_model_Info[0].data.status.fLifePoint)
		{
			g_model_Info[0].data.nLifePoint = (int)g_model_Info[0].data.status.fLifePoint;
		}
		break;

	case 99:	//�i�� �S��ʃG�t�F�N�g
		if (nMode == -1)
		{
			SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2, 2, 8, 3, 5, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, D3DX_PI * 0.0f, 1);
		}
		break;
	case 100:	//�i���@�ύX
		if (nMode == -1)
		{
			SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEOUT, WINDOWUSE_NORMAL);

			//�X�e�[�^�X�ŕ���
			int nEvolve = 2;
			if (g_model_Info[nCount].data.status.fAttack > g_model_Info[nCount].data.status.fInt
				&& g_model_Info[nCount].data.status.fAttack > g_model_Info[nCount].data.status.fSpeed * 1.5f) {
				nEvolve = 0;
			}
			else if (g_model_Info[nCount].data.status.fInt > g_model_Info[nCount].data.status.fAttack
				&& g_model_Info[nCount].data.status.fInt > g_model_Info[nCount].data.status.fSpeed * 1.5f) {
				nEvolve = 1;
			}
			else { nEvolve = 2; }


			switch (nEvolve)
			{
			case 0:
				Set_P_ATK(&g_model_Info[nCount].set);
				g_model_Info[nCount].data.gifted.fLifePoint += 1000.0f;
				g_model_Info[nCount].data.gifted.fAttack += 60.0f;
				g_model_Info[nCount].data.gifted.fDefense += 20.0f;
				g_model_Info[nCount].data.gifted.fSpeed += 20.0f;
				break;
			case 1:
				Set_P_INT(&g_model_Info[nCount].set);
				g_model_Info[nCount].data.gifted.fLifePoint += 600.0f;
				g_model_Info[nCount].data.gifted.fInt += 90.0f;
				g_model_Info[nCount].data.gifted.fRes += 20.0f;
				g_model_Info[nCount].data.gifted.fSpeed += 20.0f;
				break;
			case 2:
				Set_P_SPD(&g_model_Info[nCount].set);
				g_model_Info[nCount].data.gifted.fLifePoint += 800.0f;
				g_model_Info[nCount].data.gifted.fAttack += 40.0f;
				g_model_Info[nCount].data.gifted.fInt += 40.0f;
				g_model_Info[nCount].data.gifted.fRes += 40.0f;
				g_model_Info[nCount].data.gifted.fSpeed += 90.0f;
				break;
			}

			//���[�V������Reset
			ResetMotion(&g_model_Info[nCount].set);
			CollisionObject_Plus(&g_model_Info[nCount].set);

			char aStr[48];
			int nLength;
			MODEL_MOTION *pMotion = GetModel_Motion();

			wsprintf(&aStr[0], "%d SP\n", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[0][0]].key[0].nAtkEffect));
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[0][0]);
			ChangeFont(true, &aStr[0], 5, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			wsprintf(&aStr[0], "");
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[1][0]);
			nLength = (int)strlen(&aStr[0]);
			wsprintf(&aStr[nLength], "\n%d SP", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[1][0]].key[0].nAtkEffect));
			ChangeFont(true, &aStr[0], 6, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;

	case 200:	//�U���^
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_ATTACK001);
			SetAnimation(g_model_Info[nCount].set.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 300, 300, 8, 1, 2, 6, 1, ANIMATION_UP);
		}
		break;

	case 400:
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_ATTACK400);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXCOLOR(1.0f, 0.12f, 0.05f, 1.0f), 150, 150, 5, 5, 2, 8, 1, ANIMATION_NORMAL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 4, 6, 1, ANIMATION_NORMAL);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 7.5f, 80.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 9.15f, 120.0f, 1.0f, 30, 1, 99999, 400, 400, -1, nCount);
		}
		break;
	case 401:
		if (nMode == -1)
		{
			PlaySound(SOUND_LABEL_ATTACK001);
			SetBullet(g_model_Info[nCount].set.pos, D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 8.8f, 45.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 11.45f, 150.0f, 1.0f, 20, 1, 99999, 401, 401, -1, nCount);
			SetAnimation(g_model_Info[nCount].set.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 300, 300, 8, 1, 2, 6, 1, ANIMATION_UP);
		}
		break;
	case 402:
		if (nMode == -1)
		{
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -40.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -40.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -10.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -10.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 10.5f, 10.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 7.35f, 80.0f, 0.0f, 21, 3, 99999, 402, 402, -1, nCount);
		}
		break;
	case 403:
		if (nMode % 10 == 2)
		{
			if (nMode < 30)
			{
				PlaySound(SOUND_LABEL_ATTACK403);
				SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -40.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -40.0f)), D3DXCOLOR(0.96f, 1.0f, 0.12f, 0.5f), 60, 60, 5, 2, 1, 4, 1, ANIMATION_NORMAL);
				SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -40.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -40.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f - (g_model_Info[nCount].set.move.x * 3.0f), (3 - (nMode / 10)) * -5.0f - 10.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f - (g_model_Info[nCount].set.move.z * 3.0f))), D3DXVECTOR3(1.57f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 2.5f, 3.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.95f, 20.0f, 0.0f, 21, 2, 5, 403, 403, -1, nCount);
			}
			else
			{
				PlaySound(SOUND_LABEL_ATTACK404);
				SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -40.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -40.0f)), D3DXCOLOR(0.96f, 1.0f, 0.12f, 0.5f), 200, 200, 5, 2, 3, 4, 1, ANIMATION_NORMAL);
				SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -40.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -40.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f - (g_model_Info[nCount].set.move.x * 3.0f), (3 - (nMode / 10)) * -5.0f - 10.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f - (g_model_Info[nCount].set.move.z * 3.0f))), D3DXVECTOR3(1.57f, 0.0f, 0.0f),
					D3DXVECTOR3(0.0f, 6.5f, 10.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 1.95f, 40.0f, 0.0f, 21, 2, 5, 404, 404, -1, nCount);
			}
		}
		break;
	case 404:
		if (nMode == -1)
		{
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y + D3DX_PI * 0.5f) * -20.0f, 80.0f, (cosf(g_model_Info[nCount].set.rot.y + D3DX_PI * 0.5f) * -20.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 14.5f, 0.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.35f, 80.0f, 0.0f, 41, 3, 1, 405, 405, -1, nCount);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y + D3DX_PI * 0.5f) * -40.0f, 60.0f, (cosf(g_model_Info[nCount].set.rot.y + D3DX_PI * 0.5f) * -40.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 14.5f, 0.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.35f, 80.0f, 0.0f, 41, 3, 1, 405, 405, -1, nCount);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y - D3DX_PI * 0.5f) * -20.0f, 80.0f, (cosf(g_model_Info[nCount].set.rot.y - D3DX_PI * 0.5f) * -20.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 14.5f, 0.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.35f, 80.0f, 0.0f, 41, 3, 1, 405, 405, -1, nCount);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y - D3DX_PI * 0.5f) * -40.0f, 60.0f, (cosf(g_model_Info[nCount].set.rot.y - D3DX_PI * 0.5f) * -40.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -30.0f, 0.0f, (cosf(g_model_Info[nCount].set.rot.y) * -30.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 14.5f, 0.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.35f, 80.0f, 0.0f, 41, 3, 1, 405, 405, -1, nCount);
		}
	case 405:
		if (nMode == -1)
		{
			//if (set[0].nLockChar > 0)
			//{
			//	SetBullet(g_model_Info[set[0].nLockChar].set.pos, D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
			//		D3DXVECTOR3(0.0f, -50.0f, 0.0f), use, data[0].status.fInt, 25.5f, 150.0f, 0.0f, 10, 4, 999999, 405, 405, 25);
			//}

		}
	case 500:
		if (nMode == -1)
		{//���@�g���@���@1
			PlaySound(SOUND_LABEL_ATTACK403);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -100.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -100.0f)), D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y), 0.0f, cosf(g_model_Info[nCount].set.rot.y)) * -15.0f, D3DXVECTOR3(D3DX_PI * -0.5f, g_model_Info[nCount].set.rot.y, 0.0f),
				D3DXVECTOR3(0.0f, 4.5f, 15.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 0.55f, 40.0f, 1.0f, 90, 1, 99999, 500, 500, -1, nCount);
		}
		break;
	case 501:
		if (nMode == -1)
		{//���@�g���@���@1			
			PlaySound(SOUND_LABEL_ATTACK400);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXCOLOR(1.0f, 0.12f, 0.05f, 1.0f), 150, 150, 5, 5, 2, 8, 1, ANIMATION_NORMAL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 4, 6, 1, ANIMATION_NORMAL);
			SetBullet(g_model_Info[nCount].set.pos + D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * -80.0f, 50.0f, (cosf(g_model_Info[nCount].set.rot.y) * -80.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 7.5f, 80.0f), g_model_Info[nCount].use, g_model_Info[nCount].data.status.fInt, 2.75f, 120.0f, 1.0f, 30, 1, 99999, 400, 400, -1, nCount);

		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3			pos, rot;
	ENEMY *pEnemy = GetEnemy();

	int nCount;
	float fCola = 1.0f;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_model_Info[nCount].bUse == true && g_model_Info[nCount].use != MODEL_USE_Pause)
		{//�g�p���Ȃ�
			if (g_model_Info[nCount].set.state == MODEL_STATE_DIE)
			{
				fCola = ((0.5f / 60) * g_model_Info[nCount].set.nCntState);
				if (g_model_Info[nCount].set.nCntState == 0)
				{
					if (g_model_Info[nCount].use == MODEL_USE_ENEMY_B)
					{//�{�X��|����
						GAME_PLAY *pGame_Play = GetGame_Play();
						pGame_Play[0].bUse = true;
						pGame_Play[0].nResults = 17;
						SetGameState(GAMESTATE_END, MODE_ENDSTORY, 200);
					}
					else if (g_model_Info[nCount].use == MODEL_USE_PLAYER)
					{//�v���C���[�Ȃ�I���
						GAME_PLAY *pGame_Play = GetGame_Play();
						pGame_Play[0].bUse = true;
						pGame_Play[0].nResults = 16;
						SetGameState(GAMESTATE_END, MODE_GAMEOVER, 200);
					}
					g_model_Info[nCount].bUse = false;
					if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
					{//�G�Ȃ�
						pEnemy[g_model_Info[nCount].set.nCntChar].bUse = false;
					}
				}
			}
			else if (g_model_Info[nCount].set.nAirTime > 0 && g_model_Info[nCount].set.nAirTime < 11 && g_model_Info[nCount].set.nNumMotion[1] != MOTION_SHRINK) { fCola = 1.0f - (g_model_Info[nCount].set.nAirTime * 0.1f); }
			else if (g_model_Info[nCount].set.nAirTime > 0) { fCola = 0.5f; }
			else { fCola = 1.0f; }
			for (int nCntModel = 0; nCntModel < g_model_Info[nCount].set.nMaxModel; nCntModel++)
			{//�p�[�c��������]

			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel);

				if (g_model_Info[nCount].set.parent[nCntModel].nParent >= 0)
				{//�q���Ȃ���Z�����
					pos = g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos;
					rot = g_model_Info[nCount].set.parent[nCntModel].addrot;
				}
				else
				{//�e�Ȃ��Ȃ猴�_����
					pos = g_model_Info[nCount].set.pos + g_model_Info[nCount].set.addpos;
					pos += D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.z
						, g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.y
						, cosf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.z);
					//pos += D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.x
					//	, 0.0f
					//	, cosf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.x);
					rot = g_model_Info[nCount].set.parent[nCntModel].addrot + g_model_Info[nCount].set.rot;
				}

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
				D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
				D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &mtxTrans);

				if (g_model_Info[nCount].set.parent[nCntModel].nParent >= 0)
				{//�e�̈ʒu�Ɗp�x���v���X
					D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[g_model_Info[nCount].set.parent[nCntModel].nParent].mtxWorldModel);
				}

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].pBuffMatModel->GetBufferPointer();
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pTextureModel[g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].nTexture]);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				for (int nCountData = 0; nCountData < (int)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].nNumMatModel; nCountData++)
				{
					// �}�e���A���̐ݒ�
					pMat = (D3DXMATERIAL*)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].pBuffMatModel->GetBufferPointer();
					pMat[nCountData].MatD3D.Diffuse.a = fCola; //�����x�ݒ�

					pDevice->SetMaterial(&pMat[nCountData].MatD3D);

					// ���f��(�p�[�c)�̕`��
					g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].MeshModel->DrawSubset(nCountData);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
				pDevice->SetTexture(0, NULL);

			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel_P(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3			pos, rot;

	int nCount;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_model_Info[nCount].bUse == true && g_model_Info[nCount].use == MODEL_USE_Pause)
		{//�g�p���Ȃ�
			for (int nCntModel = 0; nCntModel < g_model_Info[nCount].set.nMaxModel; nCntModel++)
			{//�p�[�c��������]

			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel);

				if (g_model_Info[nCount].set.parent[nCntModel].nParent >= 0)
				{//�q���Ȃ���Z�����
					pos = g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos;
					rot = g_model_Info[nCount].set.parent[nCntModel].addrot;
				}
				else
				{//�e�Ȃ��Ȃ猴�_����
					pos = g_model_Info[nCount].set.pos + g_model_Info[nCount].set.addpos;
					pos += D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.z
						, g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.y
						, cosf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.z);
					//pos += D3DXVECTOR3(sinf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.x
					//	, 0.0f
					//	, cosf(g_model_Info[nCount].set.rot.y) * g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].addpos.x);
					rot = g_model_Info[nCount].set.parent[nCntModel].addrot + g_model_Info[nCount].set.rot;
				}

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
				D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
				D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &mtxTrans);

				if (g_model_Info[nCount].set.parent[nCntModel].nParent >= 0)
				{//�e�̈ʒu�Ɗp�x���v���X
					D3DXMatrixMultiply(&g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel, &g_model_Info[nCount].set.parent[g_model_Info[nCount].set.parent[nCntModel].nParent].mtxWorldModel);
				}

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_model_Info[nCount].set.parent[nCntModel].mtxWorldModel);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);
				pMat = (D3DXMATERIAL*)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].pBuffMatModel->GetBufferPointer();
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pTextureModel[g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].nTexture]);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				for (int nCountData = 0; nCountData < (int)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].nNumMatModel; nCountData++)
				{
					// �}�e���A���̐ݒ�
					pMat = (D3DXMATERIAL*)g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].pBuffMatModel->GetBufferPointer();

					pDevice->SetMaterial(&pMat[nCountData].MatD3D);

					// ���f��(�p�[�c)�̕`��
					g_model_Draw[g_model_Info[nCount].set.parent[nCntModel].type].MeshModel->DrawSubset(nCountData);
				}

				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
				pDevice->SetTexture(0, NULL);

			}
		}
	}
}
//=============================================================================
// * �U�� �����蔻��
//=============================================================================
void Attackjudge(void)
{
	LPDIRECT3DDEVICE9	pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX	mtxParts;			//���蕔�ʂ̕ۑ��p

	for (int nCntModel = 0; nCntModel < MAX_MODEL_INFO; nCntModel++)
	{
		if (g_model_Info[nCntModel].bUse == true && g_model_Info[nCntModel].use != MODEL_USE_Pause)
		{
			if (g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].nAtkFrame[0] < g_model_Info[nCntModel].set.nNumMotion[4] &&
				g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].nAtkFrame[1] > g_model_Info[nCntModel].set.nNumMotion[4])
			{//�U���t���[�����Ȃ�

			 //g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].fRange;
			 // ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxParts);
				mtxParts = g_model_Info[nCntModel].set.parent[g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].nParts / 100].mtxWorldModel;

				Hitjudge(nCntModel, 0
					, g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].nParts % 100
					, g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].nInvincible
					, g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].fRange
					, g_model_Info[nCntModel].data.status.fAttack
					, g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].fAtkplus
					, g_model_motion[g_model_Info[nCntModel].set.nNumMotion[0]][g_model_Info[nCntModel].set.nNumMotion[1]].key[g_model_Info[nCntModel].set.nNumMotion[3]].blown
					, mtxParts, 0);
			}//�U������
		}
	}//for��
}

//=============================================================================
// * �U�� �����蔻��
//=============================================================================
void Hitjudge(int nCntModel, int nCntBullet, int nCntAtk, int nInvincible, float fRange, float fAtk, float fAtkplus, D3DXVECTOR3 blown, D3DXMATRIX	mtxParts, int nMode)
{
	Camera *pCamera = GetCamera();
	D3DXMATRIX	mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxSave = mtxParts;
	float		fRange0;
	float		fDef, fLuk;	//�X�e�[�^�X�v�Z�p
	float		fDamage;			//�_���[�W�v�Z�p
	float		fPredator;			//0.0f�ߐH����, �{���ɉ����ăX�L���h���b�v
	float		fHeel;				//�z���̔{��
	float		fMoveY;
	bool		bSkill;
	float	fLengthOneself;
	int		nBattle[2];
	if (g_model_Info[nCntModel].use == MODEL_USE_PLAYER) { nBattle[0] = 0; }
	else { nBattle[0] = 1; }
	fRange0 = fRange;

	for (int nCntChar = 0; nCntChar < MAX_MODEL_INFO; nCntChar++)
	{//�S���f������]
		if (g_model_Info[nCntChar].bUse == true && nCntModel != nCntChar && g_model_Info[nCntChar].set.nAirTime == 0 && g_model_Info[nCntChar].set.state != MODEL_STATE_MAP && g_model_Info[nCntChar].use != MODEL_USE_Pause)
		{//�g���Ă��� && �����ƒ��Ԃ���Ȃ�
			if (g_model_Info[nCntChar].use == MODEL_USE_PLAYER) { nBattle[1] = 0; }
			else { nBattle[1] = 1; }
			if (nBattle[0] != nBattle[1])
			{
				//fRange = powf(fRange, 2) + powf(fRange, 2);
				fLengthOneself = powf(fRange0 + 15.0f, 2);		//�ڕW�̂�XZ�͈̔�

				for (int nCntLength = 0; nCntLength < nCntAtk; nCntLength++)
				{//����������
					if ((mtxParts._42 - fRange0 <= g_model_Info[nCntChar].set.pos.y + g_model_Info[nCntChar].set.fHeight && mtxParts._42 + fRange0 >= g_model_Info[nCntChar].set.pos.y))
					{//Y���͈͓��Ȃ�
						float fLengthX = g_model_Info[nCntChar].set.pos.x - mtxParts._41;	//X�̍�
						float fLengthZ = g_model_Info[nCntChar].set.pos.z - mtxParts._43;	//Z�̍�
						float fLengthTotal = powf(fLengthX, 2) + powf(fLengthZ, 2);
						if (fLengthOneself >= fLengthTotal)
						{//XZ�͈͓��Ȃ�
							fHeel = 0.0f; fPredator = 0.0f; bSkill = false;

							if ((g_model_Info[nCntChar].set.state == MODEL_STATE_POISED && g_model_Info[nCntChar].set.nCntState > 0) || g_model_Info[nCntChar].set.state == MODEL_STATE_GUARD)
							{
								//���[�V�����̕ω�
								g_model_Info[nCntChar].set.nNumMotion[3] = -1;
								g_model_Info[nCntChar].set.nNumMotion[1] = MOTION_GUARD;
								g_model_Info[nCntChar].set.state = MODEL_STATE_GUARD;
								g_model_Info[nCntChar].set.nAirTime = nInvincible;
								if (g_model_Info[nCntChar].set.nAirTime > 5) { g_model_Info[nCntChar].set.nAirTime = 5; }
								fMoveY = 0.0f;
								PlaySound(SOUND_LABEL_LOCKON);
								SetAnimation(g_model_Info[nCntChar].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
							}
							else
							{
								//�_���[�W
								fAtk = (fAtk * (rand() % 31 + 95)) * 0.01f;
								if (nMode == 0) { fDef = (g_model_Info[nCntChar].data.status.fDefense * (rand() % 21 + 45)) * 0.01f; }
								else { fDef = (g_model_Info[nCntChar].data.status.fRes * (rand() % 21 + 45)) * 0.01f; }
								//�q�b�g������
								if (nMode == 0) { MotionEffect_A(nCntModel, nCntChar, fAtk, &fHeel, &fPredator); }
								else { UpdateABullet(nCntBullet, nCntChar, fAtk); }

								//�����Ă���X�L���m�F
								if (g_model_Info[nCntModel].data.nSkill[0][4] > 0)
								{//�X�L���Ȃ�ǉ����ʊm�F
									bSkill = true;
									SkillEffect_A(&g_model_Info[nCntModel].data.nSkill[0][0], nCntModel, nCntChar, &fAtk, &fHeel, &fPredator);
								}
								else if (g_model_Info[nCntModel].data.nSkill[1][4] > 0)
								{//�X�L���Ȃ�ǉ����ʊm�F
									bSkill = true;
									SkillEffect_A(&g_model_Info[nCntModel].data.nSkill[1][0], nCntModel, nCntChar, &fAtk, &fHeel, &fPredator);
								}


								fLuk = (g_model_Info[nCntModel].data.status.fLucky - g_model_Info[nCntChar].data.status.fLucky) / 50;
								if (fLuk < 5.0f) { fLuk = 5.0f; }				//�Ⴗ�������̏����@�Œ�5��
								else if (fLuk > 90.0f) { fLuk = 90.0f; }		//���������ꍇ�@�ő�90��
								if (rand() % 100 < (int)fLuk)
								{//��S
								 //��S��//�{���ɉ�����
									fDamage = 1.35f;
									fAtk *= 1.25f;
									//�G�t�F�N�g
									PlaySound(SOUND_LABEL_Damage002);
									SetAnimation(g_model_Info[nCntChar].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 5, 2, 3, 2, 1, ANIMATION_NORMAL);
								}
								else
								{//�ʏ퉹
								 //�{���ɉ�����
									fDamage = 1.0f;
									SetAnimation(g_model_Info[nCntChar].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 0.8f), 150, 150, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
									SetAnimation(g_model_Info[nCntChar].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 50, 50, 5, 1, 5, 0, 1, ANIMATION_NORMAL);
								}
								//�U���{�����܂߂ă_���[�W�v�Z
								fDamage = (fAtk - fDef) * fDamage;
								if (fDamage < fAtk * 0.5f) { fDamage = fAtk * 0.5f; }
								fDamage *= fAtkplus;
								g_model_Info[nCntChar].data.nLifePoint -= (int)fDamage;

								//�����Ă���X�L���łȂ���Ή�
								g_model_Info[nCntModel].data.nSkillPoint += (int)(fDamage * 0.015f);

								//�z���������Ă���Ȃ�
								if (fHeel > 0.0f) { g_model_Info[nCntModel].data.nLifePoint += (int)(fDamage * fHeel); }

								if (fPredator > 0.0f)
								{//�ߐH ��
									g_model_Info[nCntModel].data.nLifePoint += (int)(fDamage * 0.25f);
									g_model_Info[nCntModel].data.nSkillPoint += (int)(fDamage * 0.08f);
									SetZWindow(g_model_Info[nCntModel].set.pos + D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * 3.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 500, 4, 2, WINDOWSTATE_FADE_Z, 0.02f);
									SetAnimation(g_model_Info[nCntModel].set.pos + D3DXVECTOR3((rand() % 2000) * 0.1f - 100.0f, (rand() % 1000) * 0.1f, (rand() % 2000) * 0.1f - 100.0f), D3DXCOLOR(0.4f, 1.0f, 1.0f, 0.8f), 250, 250, 10, 1, 5, 1, 2, ANIMATION_NORMAL);
									SetAnimation(g_model_Info[nCntModel].set.pos + D3DXVECTOR3((rand() % 2000) * 0.1f - 100.0f, (rand() % 1000) * 0.1f, (rand() % 2000) * 0.1f - 100.0f), D3DXCOLOR(0.4f, 1.0f, 1.0f, 0.7f), 350, 450, 10, 1, 6, 1, 2, ANIMATION_NORMAL);
									SetAnimation(g_model_Info[nCntModel].set.pos + D3DXVECTOR3((rand() % 2000) * 0.1f - 100.0f, (rand() % 1000) * 0.1f, (rand() % 2000) * 0.1f - 100.0f), D3DXCOLOR(0.4f, 1.0f, 1.0f, 0.6f), 450, 450, 10, 1, 7, 1, 2, ANIMATION_NORMAL);
								}

								if (g_model_Info[nCntModel].data.nSkillPoint > (int)g_model_Info[nCntModel].data.status.fSkillPoint) { g_model_Info[nCntModel].data.nSkillPoint = (int)g_model_Info[nCntModel].data.status.fSkillPoint; }
								if (g_model_Info[nCntModel].data.nLifePoint > (int)g_model_Info[nCntModel].data.status.fLifePoint) { g_model_Info[nCntModel].data.nLifePoint = (int)g_model_Info[nCntModel].data.status.fLifePoint; }

								//���݂Ɩ��G
								g_model_Info[nCntChar].set.state = MODEL_STATE_DAMAGE;
								g_model_Info[nCntChar].set.nCntState = (int)(fAtkplus * 30.0f);
								//���[�V�����̕ω�
								g_model_Info[nCntChar].set.nAirTime = nInvincible;
								g_model_Info[nCntChar].set.nNumMotion[3] = -1;
								g_model_Info[nCntChar].set.nNumMotion[1] = MOTION_SHRINK;

								fMoveY = blown.y;
							}
							//�������
							g_model_Info[nCntChar].set.move = D3DXVECTOR3(sinf(g_model_Info[nCntModel].set.angle.y), 0.0f, cosf(g_model_Info[nCntModel].set.angle.y))
								* -blown.z;
							g_model_Info[nCntChar].set.move.y = fMoveY;
							if (g_model_Info[nCntChar].set.move.y > 0.0f) { g_model_Info[nCntChar].set.bJump = false; }

							//�U���q�b�g��Ԃ�
							g_model_Info[nCntModel].set.state = MODEL_STATE_ATKHIT;


							if (g_model_Info[nCntChar].data.nLifePoint < 0)
							{//���񂾏ꍇ
								g_model_Info[nCntChar].data.nLifePoint = 0;
								if (g_model_Info[nCntChar].set.bJump == true)
								{//�����Ă��Ȃ�
									g_model_Info[nCntChar].set.move.y = 5.0f;
									g_model_Info[nCntChar].set.bJump = false;
								}
								g_model_Info[nCntChar].set.nAirTime = 9999;

								if (g_model_Info[nCntChar].use == MODEL_USE_PLAYER)
								{//�v���C���[�Ȃ�I���
									StopSound();
									PlaySound(SOUND_LABEL_DEAD_END);
								}
								else
								{//�G�Ȃ�o���l���, ���x���オ��
									ENEMY *pEnemy = GetEnemy();

									if (pEnemy[g_model_Info[nCntChar].set.nCntChar].nDying == 2)
									{//�ʏ�Ȃ�@ //�m���ɂȂ���HP1
										pEnemy[g_model_Info[nCntChar].set.nCntChar].nDying = 1;
										g_model_Info[nCntChar].data.nLifePoint = 1;
										g_model_Info[nCntChar].set.move.x *= 0.1f;
										g_model_Info[nCntChar].set.move.z *= 0.1f;
										PlaySound(SOUND_LABEL_TitleSE001);
									}
									else
									{//�m���Ȃ�or�m�������Ȃ�
										pEnemy[g_model_Info[nCntChar].set.nCntChar].nDying = 0;
										PLAYER *pPlayer = GetPlayer();
										CHAR_DATA	dataold = g_model_Info[nCntModel].data;
										char aStr[48];
										int nPlus = (g_model_Info[nCntChar].data.nStrength / 500);
										bool bPredator = false;

										pPlayer[0].nTime[0] += nPlus;
										wsprintf(&aStr[0], "+%d.%d", nPlus / 10, nPlus % 10);
										SetFont(RECT{ 540 , 35, 1200, 720 }, D3DXCOLOR{ 1.0f, 0.95f, 0.08f , 1.0f }, &aStr[0], 10, 3, DT_LEFT, -1, true, FONTSTATE_DELETE, WINDOW_DRAW_0);

										if (fPredator > 0.0f)
										{//�ߐH�Ȃ�o���l�Ȃ�
											switch (g_model_Info[nCntChar].set.parent[0].type)
											{
											case MODEL_TYPE_EWarrior_bodyD:	//�U���͏㏸
												bPredator = true;
												g_model_Info[nCntModel].data.gifted.fAttack += g_model_Info[nCntChar].data.gifted.fAttack * 0.25f;
												break;
											case MODEL_TYPE_EWizard_bodyD:	//���͏㏸
												bPredator = true;
												g_model_Info[nCntModel].data.gifted.fInt += g_model_Info[nCntChar].data.gifted.fInt * 0.25f;
												break;
											case MODEL_TYPE_ENinja_bodyD:	//�X�s�[�h�㏸
												bPredator = true;
												g_model_Info[nCntModel].data.gifted.fSpeed += g_model_Info[nCntChar].data.gifted.fSpeed * 0.25f;
												break;
											}
											if (bPredator == true)
											{
												GetStatus(&g_model_Info[nCntModel].data, true);
												ShowStatus(dataold, g_model_Info[nCntModel].data);

												if (rand() % pEnemy[g_model_Info[nCntChar].set.nCntChar].nDropS < (int)(fPredator * (1.0f + g_model_Info[nCntModel].data.status.fLucky * 0.001f)))
												{//�X�L���h���b�v
													DropSkill(pEnemy[g_model_Info[nCntChar].set.nCntChar].nDSkill[rand() % 2]);
												}
											}
										}
										if (bPredator == false)
										{//�ߐH����
											CHAR_DATA	data;
											float		fLife, fSkill;
											g_model_Info[nCntModel].data.nExperience += g_model_Info[nCntChar].data.nStrength;
											while (1)
											{
												if (g_model_Info[nCntModel].data.nExperience > g_model_Info[nCntModel].data.nNextLevel)
												{//���x���A�b�v
													SetAnimation(g_model_Info[nCntChar].set.pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 50, 1, 7, 5, 3, 1, ANIMATION_NORMAL);
													g_model_Info[nCntModel].data.nExperience -= g_model_Info[nCntModel].data.nNextLevel;
													g_model_Info[nCntModel].data.nNextLevel = (int)(INIT_EXP * powf(EXP_UP, g_model_Info[nCntModel].data.nLevel * 1.0f));
													g_model_Info[nCntModel].data.nLevel++;
													//��
													data = g_model_Info[nCntModel].data;
													GetStatus(&data, true);
													fLife = data.status.fLifePoint - g_model_Info[nCntModel].data.status.fLifePoint;
													fSkill = data.status.fSkillPoint - g_model_Info[nCntModel].data.status.fSkillPoint;
													g_model_Info[nCntModel].data = data;
													g_model_Info[nCntModel].data.nLifePoint += (int)(fLife + g_model_Info[nCntModel].data.status.fLifePoint * 0.3f);
													g_model_Info[nCntModel].data.nSkillPoint += (int)(fSkill + g_model_Info[nCntModel].data.status.fSkillPoint * 0.5f);
													if (g_model_Info[nCntModel].data.nLifePoint > (int)g_model_Info[nCntModel].data.status.fLifePoint) { g_model_Info[nCntModel].data.nLifePoint = (int)g_model_Info[nCntModel].data.status.fLifePoint; }
													if (g_model_Info[nCntModel].data.nSkillPoint > (int)g_model_Info[nCntModel].data.status.fSkillPoint) { g_model_Info[nCntModel].data.nSkillPoint = (int)g_model_Info[nCntModel].data.status.fSkillPoint; }
												}
												else
												{
													if (dataold.nLevel < g_model_Info[nCntModel].data.nLevel)
													{
														ShowStatus(dataold, g_model_Info[nCntModel].data);
													}
													break;
												}
											}
										}//���jelse
										if (rand() % pEnemy[g_model_Info[nCntChar].set.nCntChar].nDropI < (int)(350.0f + g_model_Info[nCntModel].data.status.fLucky * 0.1f))
										{//�A�C�e���h���b�v

										}

										if (g_model_Info[nCntChar].use == MODEL_USE_ENEMY_B)
										{//�Q�[���N���A��
											StopSound();
											PlaySound(SOUND_LABEL_BOSS_D);
										}
										if (g_model_Info[nCntChar].use == MODEL_USE_ENEMY_T)
										{//�����ł���
											PlaySound(SOUND_LABEL_BOSS_D);
											DropSkill(25);
											SetMap_Change(D3DXVECTOR3(0.0f, 0.0f, -8850.0f), D3DXVECTOR3(0.0f, 0.0f, 2700.0f), 1000, 80, MAP_TYPE_301_CASTLE);
										}
										else { PlaySound(SOUND_LABEL_TitleSE001); }
									}
								}//	�_���[�W��
							}
							else { PlaySound(SOUND_LABEL_Damage000); }
							break;
						}//XZ�͈�
					}//Y�͈�
					 //�c�q����
					 // �ړ��𔽉f
					D3DXMatrixTranslation(&mtxTrans, 0.0f, fRange0, 0.0f);
					D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &mtxParts);
					mtxParts = mtxTrans;
				}//for��
				mtxParts = mtxSave;
			}//���� �G����
		}//���� �Ώێ�
	}//for�󂯑�
}
//=============================================================================
// �X�L���h���b�v����
//=============================================================================
void DropSkill(int nSkill)
{
	if (nSkill > 0)
	{//�����Ă��Ȃ�Skill
		PLAYER *pPlayer = GetPlayer();

		for (int nCntSkill = 0; nCntSkill < 3; nCntSkill++)
		{
			if (pPlayer[0].nDSkill[nCntSkill] == nSkill)
			{//�������̂��h���b�v
				break;
			}
			else if (pPlayer[0].nDSkill[nCntSkill] == -1)
			{//���g����
				pPlayer[0].nDSkill[nCntSkill] = nSkill;
				break;
			}
		}
	}
}
//=============================================================================
// �X�L����������
//=============================================================================
void SwapSkill(int nNumber, int nCount)
{
	PLAYER *pPlayer = GetPlayer();
	int nLength;

	if (nNumber > -1)
	{//�X�L������ւ�
		MODEL_MOTION *pMotion = GetModel_Motion();
		char aStr[48];

		g_model_Info[0].data.nSkill[nNumber][0] = pPlayer[0].nDSkill[0];
		PlusSkill(&g_model_Info[0].data.nSkill[nNumber][0], nCount); //�����_���ɃX�L��+
		if (nNumber == 0)
		{
			wsprintf(&aStr[0], "%d SP\n", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[nNumber][0]].key[0].nAtkEffect));
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[nNumber][0]);
		}
		else
		{
			wsprintf(&aStr[0], "", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[nNumber][0]].key[0].nAtkEffect));
			ReturnSkillName(&aStr[0], g_model_Info[0].data.nSkill[nNumber][0]);
			nLength = (int)strlen(&aStr[0]);
			wsprintf(&aStr[nLength], "\n%d SP\n", MotionSkill(pMotion[g_model_Info[0].set.nNumMotion[0] * MAX_MODEL_MOTION + g_model_Info[0].data.nSkill[nNumber][0]].key[0].nAtkEffect));
		}
		ChangeFont(true, &aStr[0], 5 + nNumber, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	for (int nCntSkill = 0; nCntSkill < 2; nCntSkill++)
	{
		pPlayer[0].nDSkill[nCntSkill] = pPlayer[0].nDSkill[nCntSkill + 1];
	}
	pPlayer[0].nDSkill[2] = -1;
}
//=============================================================================
// �X�L���ǉ�����
//=============================================================================
void PlusSkill(int *nSkill, int nCount)
{
	int nRand;
	int nRandL;

	int nSave[3] = { -1, -1, -1 };
	int nMap = 0;
	PLAYER  *pPlayer = GetPlayer();

	switch (pPlayer[0].maptype)
	{
	case MAP_TYPE_100_YEUNG:
		nMap = 1; break;
	case MAP_TYPE_200_CITY:
		nMap = 1; break;
	case MAP_TYPE_300_CASTLE:
		nMap = 2; break;
	case MAP_TYPE_301_CASTLE:
		nMap = 3; break;
	}
	for (int nCntSkill = 1; nCntSkill < 4; nCntSkill++)
	{//��ɂ���
		nSkill[nCntSkill] = -1;
	}

	for (int nCntSkill = 1; nCntSkill < 4; nCntSkill++)
	{//�X�L��3�܂� 0�̓X�L���ԍ�
		if (rand() % (4000 * nCntSkill) < (int)(5000.0f * (1.0f + g_model_Info[nCount].data.status.fLucky * 0.0002f)))
		{//�ǉ�
			nRand = rand() % 2; //�U�������펞��
			if (nSkill[0] > 30) { nRand = 0; }

			nRandL = rand() % 10000 - (int)(g_model_Info[nCount].data.status.fLucky * 0.08f);
			if (nRandL < 500 * nCntSkill + 500) { nRandL = 2; }	//��5
			else if (nRandL < 2500 * nCntSkill + 2500) { nRandL = 1; }	//��4
			else { nRandL = 0; }	//��3


			if (nRand == 0)
			{//�������X�L��
				if (rand() % 8 == 0) { nRand = 100 + nRandL; }	//100�ƃ����N+
				else { nRand = (rand() % 7) * 10 + (rand() % 2) * 3 + nRandL; }	//0�`70��2���+�����N
			}
			else
			{//Hit���X�L��
				nRand = 1000 + (rand() % 3) * 10 + nRandL;
			}

			//����Ă�����j��
			if (nRand / 10 == nSave[0] / 10 || nRand / 10 == nSave[1] / 10) { break; }
			nSkill[nCntSkill] = nRand;
			nSave[nCntSkill - 1] = nSkill[nCntSkill];
		}
		else
		{
			break;
		}
	}
}
//=============================================================================
// Skill�̒ǉ����ʎ��s����
//=============================================================================
void SkillEffect_S(int *nSkill, int nCount)
{
	for (int nCntSkill = 1; nCntSkill < 4; nCntSkill++)
	{//�X�L��3�܂� 0�̓X�L���ԍ�
		switch (nSkill[nCntSkill])
		{
		case 0:	//HP���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLifePoint = 8000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)8000.0f;
			break;
		case 1:	//HP���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLifePoint = 2000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)2000.0f;
			break;
		case 2:	//HP��@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLifePoint = 50000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)50000.0f;
			break;
		case 3:	//HP���@�㏸
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLifePoint = 8000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)8000.0f;
			break;
		case 4:	//HP���@�㏸
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLifePoint = 20000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)20000.0f;
			break;
		case 5:	//HP��@�㏸
			g_model_Info[nCount].data.plus[0].fLifePoint = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLifePoint = 80000.0f;
			GetStatus(&g_model_Info[nCount].data, true);
			g_model_Info[nCount].data.nLifePoint += (int)50000.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 10:	//�U�����@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 0.3f;
			break;
		case 11:	//�U�����㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 0.6f;
			break;
		case 12:	//�U����@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 1.0f;
			break;
		case 13:	//�U�����@�㏸
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 0.3f;
			break;
		case 14:	//�U�����@�㏸
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 0.6f;
			break;
		case 15:	//�U����@�㏸
			g_model_Info[nCount].data.plus[0].fAttack = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fAttack = (g_model_Info[nCount].data.status.fAttack - g_model_Info[nCount].data.plus[1].fAttack) * 1.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 20:	//�h�䏬�@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 0.3f;
			break;
		case 21:	//�h�䒆�@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 0.6f;
			break;
		case 22:	//�h���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 1.0f;
			break;
		case 23:	//�h�䏬�@�㏸
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 0.3f;
			break;
		case 24:	//�h�䒆�@�㏸
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 0.6f;
			break;
		case 25:	//�h���@�㏸
			g_model_Info[nCount].data.plus[0].fDefense = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fDefense = (g_model_Info[nCount].data.status.fDefense - g_model_Info[nCount].data.plus[1].fDefense) * 1.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 30:	//���U���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt) * 0.3f;
			break;
		case 31:	//���U���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt)  * 0.6f;
			break;
		case 32:	//���U��@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt)  * 1.0f;
			break;
		case 33:	//���U���@�㏸
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt)  * 0.3f;
			break;
		case 34:	//���U���@�㏸
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt)  * 0.6f;
			break;
		case 35:	//���U��@�㏸
			g_model_Info[nCount].data.plus[0].fInt = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fInt = (g_model_Info[nCount].data.status.fInt - g_model_Info[nCount].data.plus[1].fInt)  * 1.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 40:	//���h���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 0.3f;
		case 41:	//���h���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 0.6f;
			break;
		case 42:	//���h��@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 1.0f;
			break;
		case 43:	//���h���@�㏸
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 0.3f;
			break;
		case 44:	//���h���@�㏸
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 0.6f;
			break;
		case 45:	//���h��@�㏸
			g_model_Info[nCount].data.plus[0].fRes = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fRes = (g_model_Info[nCount].data.status.fRes - g_model_Info[nCount].data.plus[1].fRes) * 1.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 50:	//���x���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 0.3f;
			break;
		case 51:	//���x���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 0.6f;
			break;
		case 52:	//���x��@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 1.0f;
			break;
		case 53:	//���x���@�㏸
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 0.3f;
			break;
		case 54:	//���x���@�㏸
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 0.6f;
			break;
		case 55:	//���x��@�㏸
			g_model_Info[nCount].data.plus[0].fSpeed = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fSpeed = (g_model_Info[nCount].data.status.fSpeed - g_model_Info[nCount].data.plus[1].fSpeed) * 1.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 60:	//���x���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 0.5f;
			break;
		case 61:	//���x���@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 1.0f;
			break;
		case 62:	//���x��@�㏸�@�Z����
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 2.0f;
			break;
		case 63:	//���x���@�㏸
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 0.5f;
			break;
		case 64:	//���x���@�㏸
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 1.0f;
			break;
		case 65:	//���x��@�㏸
			g_model_Info[nCount].data.plus[0].fLucky = SKILL_TIME * 2;
			g_model_Info[nCount].data.plus[1].fLucky = (g_model_Info[nCount].data.status.fLucky - g_model_Info[nCount].data.plus[1].fLucky) * 2.0f;
			break;
			//--------------------------------------------------------------------------------------------
		case 100:	//HP���@��
			g_model_Info[nCount].data.nLifePoint += (int)(10000 * (1.0f + g_model_Info[nCount].data.status.fRes * 0.0001f));
			break;
		case 101:	//HP���@��
			g_model_Info[nCount].data.nLifePoint += (int)(30000 * (1.0f + g_model_Info[nCount].data.status.fRes * 0.0001f));
			break;
		case 102:	//HP��@��
			g_model_Info[nCount].data.nLifePoint += (int)(65000 * (1.0f + g_model_Info[nCount].data.status.fRes * 0.0001f));
			break;
		}

		if (nSkill[nCntSkill] < 100 && nSkill[nCntSkill] > 0)
		{//�X�e�㏸
			PlaySound(SOUND_LABEL_UP);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 150, 150, 5, 2, 4, 12, 1, ANIMATION_NORMAL);
		}
		else if (nSkill[nCntSkill] < 1000 && nSkill[nCntSkill] > 0)
		{//��
			PlaySound(SOUND_LABEL_HELL);
			SetAnimation(g_model_Info[nCount].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 150, 150, 4, 2, 4, 11, 1, ANIMATION_NORMAL);
		}
	}

	GetStatus(&g_model_Info[nCount].data, true);
	if (g_model_Info[nCount].data.nLifePoint > (int)g_model_Info[nCount].data.status.fLifePoint)
	{//HP�m�F
		g_model_Info[nCount].data.nLifePoint = (int)g_model_Info[nCount].data.status.fLifePoint;
	}

}//=============================================================================
 // Skill�̒ǉ����ʎ��s���� �U���q�b�g��
 //=============================================================================
void SkillEffect_A(int *nSkill, int nCount, int nEnemy, float *fAtk, float *fHeel, float *fPredator)
{
	for (int nCntSkill = 1; nCntSkill < 4; nCntSkill++)
	{//�X�L��3�܂� 0�̓X�L���ԍ�
		switch (nSkill[nCntSkill])
		{
		case 1000:	//�X�L���U����UP�@��
			fAtk[0] *= 1.2f;
			break;
		case 1001:	//�X�L���U����UP�@��
			fAtk[0] *= 1.5f;
			break;
		case 1002:	//�X�L���U����UP�@��
			fAtk[0] *= 1.8f;
			break;
			//--------------------------------------------------------------------------------------------
		case 1010:	//�񕜁@��
			fHeel[0] += 0.1f;
			break;
		case 1011:	//�񕜁@��
			fHeel[0] += 0.2f;
			break;
		case 1012:	//�񕜁@��
			fHeel[0] += 0.35f;
			break;
			//--------------------------------------------------------------------------------------------
		case 1020:	//�ߐH�@��
			fPredator[0] += 0.1f;
			break;
		case 1021:	//�ߐH�@��
			fPredator[0] += 0.5f;
			break;
		case 1022:	//�ߐH�@��
			fPredator[0] += 1.0f;
			break;
		}
	}
}
//=============================================================================
// �ǉ��X�L���l�[���ԐM����
//=============================================================================
void ReturnSkillName_P(char *aName, int *nSkill)
{
	//��ɂ���
	strcpy(&aName[0], "");

	for (int nCntSkill = 1; nCntSkill < 4; nCntSkill++)
	{//�X�L��3�܂� 0�̓X�L���ԍ�
		switch (nSkill[nCntSkill])
		{
		case 0:
			strcat(&aName[0], "+ �Z����HP�㏸(��)\n");
			break;
		case 1:
			strcat(&aName[0], "+ �Z����HP�㏸(��)\n");
			break;
		case 2:
			strcat(&aName[0], "+ �Z����HP�㏸(��)\n");
			break;
		case 3:
			strcat(&aName[0], "+ ��莞��HP�㏸(��)\n");
			break;
		case 4:
			strcat(&aName[0], "+ ��莞��HP�㏸(��)\n");
			break;
		case 5:
			strcat(&aName[0], "+ ��莞��HP�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 10:
			strcat(&aName[0], "+ �Z����ATK�㏸(��)\n");
			break;
		case 11:
			strcat(&aName[0], "+ �Z����ATK�㏸(��)\n");
			break;
		case 12:
			strcat(&aName[0], "+ �Z����ATK�㏸(��)\n");
			break;
		case 13:
			strcat(&aName[0], "+ ��莞��ATK�㏸(��)\n");
			break;
		case 14:
			strcat(&aName[0], "+ ��莞��ATK�㏸(��)\n");
			break;
		case 15:
			strcat(&aName[0], "+ ��莞��ATK�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 20:
			strcat(&aName[0], "+ �Z����DEF�㏸(��)\n");
			break;
		case 21:
			strcat(&aName[0], "+ �Z����DEF�㏸(��)\n");
			break;
		case 22:
			strcat(&aName[0], "+ �Z����DEF�㏸(��)\n");
			break;
		case 23:
			strcat(&aName[0], "+ ��莞��DEF�㏸(��)\n");
			break;
		case 24:
			strcat(&aName[0], "+ ��莞��DEF�㏸(��)\n");
			break;
		case 25:
			strcat(&aName[0], "+ ��莞��DEF�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 30:
			strcat(&aName[0], "+ �Z����INT�㏸(��)\n");
			break;
		case 31:
			strcat(&aName[0], "+ �Z����INT�㏸(��)\n");
			break;
		case 32:
			strcat(&aName[0], "+ �Z����INT�㏸(��)\n");
			break;
		case 33:
			strcat(&aName[0], "+ ��莞��INT�㏸(��)\n");
			break;
		case 34:
			strcat(&aName[0], "+ ��莞��INT�㏸(��)\n");
			break;
		case 35:
			strcat(&aName[0], "+ ��莞��INT�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 40:
			strcat(&aName[0], "+ �Z����RES�㏸(��)\n");
			break;
		case 41:
			strcat(&aName[0], "+ �Z����RES�㏸(��)\n");
			break;
		case 42:
			strcat(&aName[0], "+ �Z����RES�㏸(��)\n");
			break;
		case 43:
			strcat(&aName[0], "+ ��莞��RES�㏸(��)\n");
			break;
		case 44:
			strcat(&aName[0], "+ ��莞��RES�㏸(��)\n");
			break;
		case 45:
			strcat(&aName[0], "+ ��莞��RES�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 50:
			strcat(&aName[0], "+ �Z����SPD�㏸(��)\n");
			break;
		case 51:
			strcat(&aName[0], "+ �Z����SPD�㏸(��)\n");
			break;
		case 52:
			strcat(&aName[0], "+ �Z����SPD�㏸(��)\n");
			break;
		case 53:
			strcat(&aName[0], "+ ��莞��SPD�㏸(��)\n");
			break;
		case 54:
			strcat(&aName[0], "+ ��莞��SPD�㏸(��)\n");
			break;
		case 55:
			strcat(&aName[0], "+ ��莞��SPD�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 60:
			strcat(&aName[0], "+ �Z����LUK�㏸(��)\n");
			break;
		case 61:
			strcat(&aName[0], "+ �Z����LUK�㏸(��)\n");
			break;
		case 62:
			strcat(&aName[0], "+ �Z����LUK�㏸(��)\n");
			break;
		case 63:
			strcat(&aName[0], "+ ��莞��LUK�㏸(��)\n");
			break;
		case 64:
			strcat(&aName[0], "+ ��莞��LUK�㏸(��)\n");
			break;
		case 65:
			strcat(&aName[0], "+ ��莞��LUK�㏸(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 100:
			strcat(&aName[0], "+ HP��(��)\n");
			break;
		case 101:
			strcat(&aName[0], "+ HP��(��)\n");
			break;
		case 102:
			strcat(&aName[0], "+ HP��(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
			//--------------------------------------------------------------------------------------------
		case 1000:
			strcat(&aName[0], "+ �X�L���U����UP(��)\n");
			break;
		case 1001:
			strcat(&aName[0], "+ �X�L���U����UP(��)\n");
			break;
		case 1002:
			strcat(&aName[0], "+ �X�L���U����UP(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 1010:
			strcat(&aName[0], "+ �z��(��)\n");
			break;
		case 1011:
			strcat(&aName[0], "+ �z��(��)\n");
			break;
		case 1012:
			strcat(&aName[0], "+ �z��(��)\n");
			break;
			//--------------------------------------------------------------------------------------------
		case 1020:
			strcat(&aName[0], "+ �ߐH(��)\n");
			break;
		case 1021:
			strcat(&aName[0], "+ �ߐH(��)\n");
			break;
		case 1022:
			strcat(&aName[0], "+ �ߐH(��)\n");
			break;
		}
	}
}
//=============================================================================
// �X�L���l�[���ԐM����
//=============================================================================
void ReturnSkillName(char *aName, int nSkill)
{
	int nLength = (int)strlen(&aName[0]);

	strcpy(&aName[nLength], "���ݒ�");

	switch (nSkill)
	{
	case -1:
		strcpy(&aName[nLength], "");
		break;
	case 10:
		strcpy(&aName[nLength], "�_�E��");
		break;
	case 24:
		strcpy(&aName[nLength], "���ߐH");
		break;
	case 25:
		switch (g_model_Info[0].set.parent[0].type)
		{
		case MODEL_TYPE_PNOR_hip:	strcpy(&aName[nLength], "�i��");	break;
		case MODEL_TYPE_PATK_hip:	strcpy(&aName[nLength], "�ҍU");	break;
		case MODEL_TYPE_PINT_body3: strcpy(&aName[nLength], "����");	break;
		case MODEL_TYPE_PSPD_hip:	strcpy(&aName[nLength], "�A��");	break;
		}
		break;
	case 26:
		strcpy(&aName[nLength], "�͂���");
		break;
	case 27:
		strcpy(&aName[nLength], "�ːi");
		break;
	case 28:
		strcpy(&aName[nLength], "�W�����v");
		break;
	case 29:
		strcpy(&aName[nLength], "�������Ƃ�");
		break;
	case 31:
		strcpy(&aName[nLength], "���e�I");
		break;
	case 32:
		strcpy(&aName[nLength], "����");
		break;
	case 33:
		strcpy(&aName[nLength], "����");
		break;
	case 34:
		strcpy(&aName[nLength], "����");
		break;
	case 35:
		strcpy(&aName[nLength], "����");
		break;
	case 36:
		strcpy(&aName[nLength], "�q�[��");
		break;
	case 37:
		strcpy(&aName[nLength], "���K�q�[��");
		break;
	case 38:
		strcpy(&aName[nLength], "�M�K�q�[��");
		break;
	}
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
int SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_USE use, MODEL_SETTING *pSet, CHAR_DATA *data, float fSlength, float fHeight)
{
	int nCount;

	for (nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
	{//�p�ӂ������f���g�����
		if (g_model_Info[nCount].bUse == false)
		{//�g�p���Ă��Ȃ��Ȃ�
			g_model_Info[nCount].data = data[0];
			g_model_Info[nCount].data.nSkill[0][4] = -1;
			g_model_Info[nCount].data.nSkill[1][4] = -1;
			g_model_Info[nCount].data.plus[0] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
			g_model_Info[nCount].data.plus[1] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

			g_model_Info[nCount].set = pSet[0];
			g_model_Info[nCount].set.nNumMotion[1] = 0;	//�j���[�g�����ɐݒ�
			g_model_Info[nCount].set.nNumMotion[2] = 0;	//���̃L�[���j���[�g������
			g_model_Info[nCount].set.nNumMotion[3] = -1;	//���݂̃L�[��0��
			g_model_Info[nCount].set.nNumMotion[4] = 0;	//���݂̃t���[����0��
			g_model_Info[nCount].set.nNumMotion[5] = 0;	//�O�̃��[�V������0��
			g_model_Info[nCount].set.nMotionFrame = 0;	//MOTION�̏��߂�0F�I
			g_model_Info[nCount].set.nLeg = 0;			//���߂͉E���I
			g_model_Info[nCount].set.fSpeed = 0.0f;		//����

			g_model_Info[nCount].set.state = MODEL_STATE_NONE;
			g_model_Info[nCount].set.nCntState = 0;
			g_model_Info[nCount].set.nCntHeel = 0;			//�񕜎��ԃ��Z�b�g
			g_model_Info[nCount].set.nLockChar = -1;		//lock���Ă���L��������
			g_model_Info[nCount].set.nPlayTime = 0;		//�w���̑҂����ԏ�����
			g_model_Info[nCount].set.nAirTime = 0;		//���G����
			g_model_Info[nCount].set.nSkillTime[0] = 0;		//�X�L���҂�����
			g_model_Info[nCount].set.nSkillTime[1] = 0;		//�X�L���҂�����
			g_model_Info[nCount].use = use;
			g_model_Info[nCount].set.Initpos = pos;
			g_model_Info[nCount].set.pos = pos;
			g_model_Info[nCount].set.posold = pos;
			g_model_Info[nCount].set.fPos = pos.y;
			g_model_Info[nCount].set.move = D3DXVECTOR3(0.0f, -25.0f, 0.0f);
			g_model_Info[nCount].set.rot = rot;
			g_model_Info[nCount].set.angle = rot;
			g_model_Info[nCount].set.fSlength = fSlength;
			g_model_Info[nCount].set.fHeight = fHeight;
			g_model_Info[nCount].set.bJump = false;
			g_model_Info[nCount].set.bStep = false;
			g_model_Info[nCount].bUse = true;

			if (use != MODEL_USE_Pause)
			{//�����ŉe�̐ݒ� �I�u�W�F�N�g����
				g_model_Info[nCount].nCntShadow = SetShadow(pos, rot, g_model_Info[nCount].set.fSlength, g_model_Info[nCount].set.fSlength, 0.0f, 0);
				if (use == MODEL_USE_PLAYER) { g_model_Info[nCount].nCntObject = SetObject(pos, rot, OBJECT_TYPE_999_PARROWS, OBJECT_USE_MAP, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2); }
				else { g_model_Info[nCount].nCntObject = SetObject(pos, rot, OBJECT_TYPE_999_EARROWS, OBJECT_USE_MAP, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2); }
			}

			g_model_Info[nCount].set.addPosmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ResetMotion(&g_model_Info[nCount].set);

			if (g_model_Info[nCount].use == MODEL_USE_PLAYER)
			{
				Camera *pCamera = GetCamera();
				pCamera[0].targetpos = g_model_Info[nCount].set.pos;
			}
			else if (g_model_Info[nCount].use >= MODEL_USE_ENEMY_Z)
			{
				//�}�b�v�ɂ���đ��

				g_model_Info[nCount].set.nCntChar = SetEnemy(&g_model_Info[nCount].data, g_model_Info[nCount].set.pos, g_model_Info[nCount].set.parent[0].type);
			}
			break;
		}
	}

	return nCount;
}
//=============================================================================
// ���[�V�����̍X�V
//=============================================================================
void BreakModel(int nUse)
{
	ENEMY *pEnemy = GetEnemy();

	if (nUse == 0)
	{//�S����
		for (int nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
		{//�p�ӂ������f���g�����
			g_model_Info[nCount].bUse = false;
			BreakShadow(g_model_Info[nCount].nCntShadow);
		}
	}
	else if (nUse == 1)
	{//PLAYER�ȊO����
		for (int nCount = 0; nCount < MAX_MODEL_INFO; nCount++)
		{//�p�ӂ������f���g�����
			if (g_model_Info[nCount].use != MODEL_USE_PLAYER && g_model_Info[nCount].bUse == true && g_model_Info[nCount].use != MODEL_USE_Pause)
			{
				g_model_Info[nCount].bUse = false;
				BreakShadow(g_model_Info[nCount].nCntShadow);
			}
		}
	}
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
int SetEnemy(CHAR_DATA *data, D3DXVECTOR3 pos, MODEL_TYPE type)
{
	ENEMY	*pEnemy = GetEnemy();
	int		nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�S�G��]
		if (pEnemy[nCntEnemy].bUse == false)
		{//HP�ԍ��擾
			pEnemy[nCntEnemy].nCntHPGage[0] = SetZWindow(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 50, 2.5f, 0, 0, WINDOWSTATE_MAXLIFEGAGE, 0.0f);
			pEnemy[nCntEnemy].nCntHPGage[1] = SetZWindow(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.51f, 1.0f, 0.0f, 1.0f), 50, 2.5f, 0, 0, WINDOWSTATE_AUTOLIFEGAGE, 0.0f);
			pEnemy[nCntEnemy].nCntHPGage[2] = SetZWindow(pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.51f, 1.0f, 0.0f, 1.0f), 50, 2.5f, 0, 0, WINDOWSTATE_LIFEGAGE, 0.0f);
			pEnemy[nCntEnemy].bUse = true;

			pEnemy[nCntEnemy].nDying = 3;

			data[0].nSkill[0][0] = 27;
			data[0].nSkill[1][0] = 28;
			pEnemy[nCntEnemy].nDSkill[0] = -1;
			pEnemy[nCntEnemy].nDSkill[1] = -1;
			pEnemy[nCntEnemy].nItem = -1;
			pEnemy[nCntEnemy].nDropS = 10000;
			pEnemy[nCntEnemy].nDropI = 10000;

			SetEnemySkill(&data[0], type, nCntEnemy);

			switch (type)
			{
			case MODEL_TYPE_EWarrior_bodyD:	//�m������
			case MODEL_TYPE_EWizard_bodyD:	//�m������
			case MODEL_TYPE_ENinja_bodyD:	//�m������
				pEnemy[nCntEnemy].nDying = 2;
				break;
			}
			break;
		}
	}

	return nCntEnemy;
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
void SetEnemySkill(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();

	switch (pPlayer[0].maptype)
	{
	case MAP_TYPE_100_YEUNG:
		SetEnemySkill_100(&data[0], type, nCntEnemy);
		break;
	case MAP_TYPE_200_CITY:
		SetEnemySkill_200(&data[0], type, nCntEnemy);
		break;
	case MAP_TYPE_300_CASTLE:
		SetEnemySkill_300(&data[0], type, nCntEnemy);
		break;
	case MAP_TYPE_301_CASTLE:
		SetEnemySkill_301(&data[0], type, nCntEnemy);
		break;
	case MAP_TYPE_400_THRONE:
		data[0].nSkill[0][0] = 27;
		data[0].nSkill[1][0] = 28;
		break;
	}
}
//=============================================================================
// * �X Skill�ݒ菈��
//=============================================================================
void SetEnemySkill_100(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy)
{
	ENEMY	*pEnemy = GetEnemy();

	switch (type)
	{
	case MODEL_TYPE_EWarrior_bodyD:	//��m
		data[0].nSkill[0][0] = 29;
		data[0].nSkill[1][0] = 29;
		pEnemy[nCntEnemy].nDSkill[0] = 26;
		pEnemy[nCntEnemy].nDSkill[1] = 27;
		break;
	case MODEL_TYPE_EWizard_bodyD:	//���@�g��
		data[0].nSkill[0][0] = 10;
		data[0].nSkill[1][0] = 10;
		pEnemy[nCntEnemy].nDSkill[0] = 10;
		pEnemy[nCntEnemy].nDSkill[1] = 10;
		break;
	case MODEL_TYPE_ENinja_bodyD:	//�E��
		data[0].nSkill[0][0] = 10;
		data[0].nSkill[1][0] = 10;
		pEnemy[nCntEnemy].nDSkill[0] = 10;
		pEnemy[nCntEnemy].nDSkill[1] = 10;
		break;
	}
}
//=============================================================================
// * �鉺�� Skill�ݒ菈��
//=============================================================================
void SetEnemySkill_200(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy)
{
	ENEMY	*pEnemy = GetEnemy();
	pEnemy[nCntEnemy].nDropS = 1000;

	switch (type)
	{
	case MODEL_TYPE_EWarrior_bodyD:	//��m
		data[0].nSkill[0][0] = 30;
		data[0].nSkill[1][0] = 30;
		pEnemy[nCntEnemy].nDSkill[0] = 26;
		pEnemy[nCntEnemy].nDSkill[1] = 27;
		break;
	case MODEL_TYPE_EWizard_bodyD:	//���@�g��
		data[0].nSkill[0][0] = 31;
		data[0].nSkill[1][0] = 31;
		pEnemy[nCntEnemy].nDSkill[0] = 32;
		pEnemy[nCntEnemy].nDSkill[1] = 36;
		break;
	case MODEL_TYPE_ENinja_bodyD:	//�E��
		data[0].nSkill[0][0] = 28;
		data[0].nSkill[1][0] = 28;
		pEnemy[nCntEnemy].nDSkill[0] = 28;
		pEnemy[nCntEnemy].nDSkill[1] = 33;
		break;
	}
}
//=============================================================================
// * ��1F Skill�ݒ菈��
//=============================================================================
void SetEnemySkill_300(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy)
{
	ENEMY	*pEnemy = GetEnemy();

	pEnemy[nCntEnemy].nDropS = 5000;

	switch (type)
	{
	case MODEL_TYPE_EWarrior_bodyD:	//��m
		data[0].nSkill[0][0] = 31;
		data[0].nSkill[1][0] = 31;
		pEnemy[nCntEnemy].nDSkill[0] = 26;
		pEnemy[nCntEnemy].nDSkill[1] = 27;
		break;
	case MODEL_TYPE_EWizard_bodyD:	//���@�g��
		data[0].nSkill[0][0] = 30;
		data[0].nSkill[1][0] = 30;
		pEnemy[nCntEnemy].nDSkill[0] = 34;
		pEnemy[nCntEnemy].nDSkill[1] = 37;
		break;
	case MODEL_TYPE_ENinja_bodyD:	//�E��
		data[0].nSkill[0][0] = 30;
		data[0].nSkill[1][0] = 30;
		pEnemy[nCntEnemy].nDSkill[0] = 28;
		pEnemy[nCntEnemy].nDSkill[1] = 33;
		break;
	}
}
//=============================================================================
// * ��2F Skill�ݒ菈��
//=============================================================================
void SetEnemySkill_301(CHAR_DATA *data, MODEL_TYPE type, int nCntEnemy)
{
	ENEMY	*pEnemy = GetEnemy();

	pEnemy[nCntEnemy].nDropS = 5000;

	switch (type)
	{
	case MODEL_TYPE_EWarrior_bodyD:	//��m
		data[0].nSkill[0][0] = 32;
		data[0].nSkill[1][0] = 32;
		pEnemy[nCntEnemy].nDSkill[0] = 29;
		pEnemy[nCntEnemy].nDSkill[1] = 27;
		break;
	case MODEL_TYPE_EWizard_bodyD:	//���@�g��
		data[0].nSkill[0][0] = 32;
		data[0].nSkill[1][0] = 32;
		pEnemy[nCntEnemy].nDSkill[0] = 31;
		pEnemy[nCntEnemy].nDSkill[1] = 38;
		break;
	case MODEL_TYPE_ENinja_bodyD:	//�E��
		data[0].nSkill[0][0] = 28;
		data[0].nSkill[1][0] = 28;
		pEnemy[nCntEnemy].nDSkill[0] = 28;
		pEnemy[nCntEnemy].nDSkill[1] = 33;
		break;
	}
}
//=============================================================================
// * ���f���Z�b�g����
//=============================================================================
void BreakEnemy(void)
{
	ENEMY	*pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�S�G��]
		pEnemy[nCntEnemy].bUse = false;
	}
}
//=============================================================================
// * �X�e�[�^�X�쐬����
//=============================================================================
CHAR_DATA GetGifted(char *Name)
{
	CHAR_DATA data;
	strcpy(&data.aName[0], &Name[0]);
	data.nExperience = 0;
	data.nLevel = 1;
	data.nNextLevel = (int)(INIT_EXP * powf(EXP_UP, 1));

	int nLength;	//���O�̒���
	int nValue;	//�l �{��
	float fConvert;	//�l �{��
	float fValue = 0;

	nLength = (int)strlen(&Name[0]);
	for (int nCntName = 0; nCntName < nLength; nCntName++)
	{
		nValue = (int)Name[nCntName];		//�A�X�L�[�R�[�h�ŕϊ�
		if (nValue < 0) { nValue *= -1; }	//�v���X�̒l������荞�܂Ȃ�
		fConvert = nValue * (nCntName * 0.39f + 1.0f);

		fValue += fConvert;		//�l�̍��v
	}
	for (int nCntSkill = 0; nCntSkill < 2; nCntSkill++)
	{
		for (int nCntName = 0; nCntName < 4; nCntName++)
		{
			data.nSkill[nCntSkill][nCntName] = -1;
		}
	}

	data.nCareer = (int)(fValue + nLength * nLength) % 14;
	data.gifted.fAttack = INIT_ATK * ((int)(fValue * powf(1.37f, 4)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fInt = INIT_INT * ((int)(fValue * powf(2.41f, 2)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fDefense = INIT_DFF * ((int)(fValue * powf(1.82f, 3)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fRes = INIT_RES * ((int)(fValue * powf(3.12f, 1)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fSpeed = INIT_SPD *  ((int)(fValue + nLength * powf(2.41f, 4)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fLucky = INIT_LUK *  ((int)(nLength + fValue * powf(1.09f, 3)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fLifePoint = INIT_HP * ((int)((fValue + nLength) * powf(1.43f, 5)) % MAX_Gifted + 100) * 0.01f;
	data.gifted.fSkillPoint = INIT_SP * ((int)((fValue + nLength) * powf(1.27f, 5)) % MAX_Gifted + 100) * 0.01f;
	if (strcmp(&Name[0], "�x���Z���[�W��") == 0)
	{
		data.nCareer = 99;
	}
	if (strcmp(&Name[0], "�A�[�T�[��") == 0)
	{
		data.nCareer = 100;
	}
	data.plus[0] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	data.plus[1] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	return data;
}
//=============================================================================
// * �X�e�[�^�X�擾����
//=============================================================================
void GetStatus(CHAR_DATA *data, bool bInit)
{
	char aStr[48];
	CHAR_STATUS status = GetCareer(data[0].nCareer, &aStr[0]);
	data[0].status.fAttack = (data[0].gifted.fAttack * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fAttack + data[0].plus[1].fAttack;
	data[0].status.fInt = (data[0].gifted.fInt * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fInt + data[0].plus[1].fInt;
	data[0].status.fDefense = (data[0].gifted.fDefense * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fDefense + data[0].plus[1].fDefense;
	data[0].status.fRes = (data[0].gifted.fRes * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fRes + data[0].plus[1].fRes;
	data[0].status.fSpeed = (data[0].gifted.fSpeed * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fSpeed + data[0].plus[1].fSpeed;
	data[0].status.fLucky = (data[0].gifted.fLucky * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fLucky + 1000.0f + data[0].plus[1].fLucky;
	data[0].status.fLifePoint = (data[0].gifted.fLifePoint * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f) * status.fLifePoint + 10000.0f) + data[0].plus[1].fLifePoint;
	data[0].status.fSkillPoint = (data[0].gifted.fSkillPoint * (data[0].nLevel + 15) * powf(1.02f, data[0].nLevel * 1.0f)) * status.fSkillPoint + 1000.0f + data[0].plus[1].fSkillPoint;
	data[0].status.fSkillPoint += data[0].status.fInt * 0.65f;

	data[0].nMaxStamina = 300 + ((int)data[0].status.fSpeed / MODEL_SMOVE);
	if (bInit == false)
	{//�X�^�~�i�̏�����
		data[0].nLifePoint = (int)data[0].status.fLifePoint;
		data[0].nSkillPoint = (int)data[0].status.fSkillPoint;
		data[0].nStamina = data[0].nMaxStamina;
		data[0].nTimeStamina = 0;
	}

	data[0].nStrength = (int)(
		((data[0].status.fAttack - data[0].plus[1].fAttack) * 1.2f) +
		((data[0].status.fDefense - data[0].plus[1].fDefense) * 1.05f) +
		((data[0].status.fInt - data[0].plus[1].fInt) * 1.1f) +
		((data[0].status.fRes - data[0].plus[1].fRes) * 1.05f) +
		((data[0].status.fSpeed - data[0].plus[1].fSpeed) * 1.15f) +
		((data[0].status.fLucky - data[0].plus[1].fLucky) * 1.0f) +
		((data[0].status.fLifePoint - data[0].plus[1].fLifePoint) * 1.1f) +
		((data[0].status.fSkillPoint - data[0].plus[1].fSkillPoint) * 1.05f));

}
//=============================================================================
// * Status�\������
//=============================================================================
void ShowStatus0(CHAR_DATA data, char *aStr)
{
	wsprintf(&aStr[0], "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d"
		, data.nLevel
		, (int)(data.status.fLifePoint - data.plus[1].fLifePoint)
		, (int)(data.status.fSkillPoint - data.plus[1].fSkillPoint)
		, (int)(data.status.fAttack - data.plus[1].fAttack)
		, (int)(data.status.fDefense - data.plus[1].fDefense)
		, (int)(data.status.fInt - data.plus[1].fInt)
		, (int)(data.status.fRes - data.plus[1].fRes)
		, (int)(data.status.fSpeed - data.plus[1].fSpeed)
		, (int)(data.status.fLucky - data.plus[1].fLucky)
		, data.nStrength);
}
//=============================================================================
// * ���x���A�b�v��Status�\������
//=============================================================================
void ShowStatus(CHAR_DATA data, CHAR_DATA data0)
{
	char aStr[256];

	wsprintf(&aStr[0], "LV\nHP\nSP\nATk\nDEF\nINT\nRES\nSPD\nLUK\n�퓬��");
	SetFont(RECT{ -395 , 3, 800, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 0.0f }, &aStr[0], 11, 1, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_1);

	ShowStatus0(data, &aStr[0]);
	SetFont(RECT{ -285 , 3, 800, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 0.0f }, &aStr[0], 12, 1, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_1);

	//wsprintf(&aStr[0], ">>\n>>\n>>\n>>\n>>\n>>\n>>\n>>\n>>\n>>");
	wsprintf(&aStr[0], "+%d\n+%d\n+%d\n+%d\n+%d\n+%d\n+%d\n+%d\n+%d\n+%d"
		, data0.nLevel - data.nLevel
		, (int)(data0.status.fLifePoint - data.status.fLifePoint)
		, (int)(data0.status.fSkillPoint - data.status.fSkillPoint)
		, (int)(data0.status.fAttack - data.status.fAttack)
		, (int)(data0.status.fDefense - data.status.fDefense)
		, (int)(data0.status.fInt - data.status.fInt)
		, (int)(data0.status.fRes - data.status.fRes)
		, (int)(data0.status.fSpeed - data.status.fSpeed)
		, (int)(data0.status.fLucky - data.status.fLucky)
		, data.nStrength - data.nStrength
	);
	SetFont(RECT{ -185 , 3, 800, 720 }, D3DXCOLOR{ 1.0f, 0.95f, 0.08f , 0.0f }, &aStr[0], 13, 1, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_1);

	ShowStatus0(data0, &aStr[0]);
	SetFont(RECT{ -85 , 3, 800, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0f , 0.0f }, &aStr[0], 14, 1, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_1);
}
//=============================================================================
// * �E�Ɛݒ菈��
//=============================================================================
CHAR_STATUS GetCareer(int nCareer, char *aCareer)
{
	CHAR_STATUS status;

	switch (nCareer)
	{
		//�o�����X�^
	case 0:	//�E��
		strcpy(&aCareer[0], "����");
		status.fLifePoint = 1.5f;
		status.fSkillPoint = 1.25f;
		status.fAttack = 1.4f;
		status.fDefense = 1.4f;
		status.fInt = 1.4f;
		status.fRes = 1.4f;
		status.fSpeed = 1.25f;
		status.fLucky = 1.2f;
		break;
	case 1:	//���m
		strcpy(&aCareer[0], "�A���f�b�h");
		status.fLifePoint = 1.55f;
		status.fSkillPoint = 1.0f;
		status.fAttack = 1.25f;
		status.fDefense = 1.2f;
		status.fInt = 1.2f;
		status.fRes = 1.2f;
		status.fSpeed = 0.95f;
		status.fLucky = 1.0f;
		break;
	case 2:	//���m
		strcpy(&aCareer[0], "�S�[�X�g");
		status.fLifePoint = 0.95f;
		status.fSkillPoint = 1.8f;
		status.fAttack = 0.8f;
		status.fDefense = 1.15f;
		status.fInt = 1.7f;
		status.fRes = 1.75f;
		status.fSpeed = 0.85f;
		status.fLucky = 0.95f;
		break;
	case 3:	//�O���f�B�G�[�^�[
		strcpy(&aCareer[0], "���@���p�C�A");
		status.fLifePoint = 1.45f;
		status.fSkillPoint = 1.45f;
		status.fAttack = 1.85f;
		status.fDefense = 1.25f;
		status.fInt = 0.6f;
		status.fRes = 0.6f;
		status.fSpeed = 1.7f;
		status.fLucky = 1.15f;
		break;
	case 4:	//�o�g���}�X�^�[
		strcpy(&aCareer[0], "�S�[����");
		status.fLifePoint = 1.85f;
		status.fSkillPoint = 0.75f;
		status.fAttack = 1.3f;
		status.fDefense = 1.95f;
		status.fInt = 0.8f;
		status.fRes = 1.25f;
		status.fSpeed = 0.6f;
		status.fLucky = 1.0f;
		break;

		//�U���^
	case 5:	//�_�[�N�i�C�g
		strcpy(&aCareer[0], "�E���t");
		status.fLifePoint = 1.15f;
		status.fSkillPoint = 1.15f;
		status.fAttack = 1.65f;
		status.fDefense = 0.95f;
		status.fInt = 0.95f;
		status.fRes = 0.95f;
		status.fSpeed = 2.0f;
		status.fLucky = 1.8f;
		break;
	case 6:	//�o�[�T�[�J�[
		strcpy(&aCareer[0], "���C�o�[��");
		status.fLifePoint = 1.95f;
		status.fSkillPoint = 1.15f;
		status.fAttack = 1.65f;
		status.fDefense = 1.15f;
		status.fInt = 1.75f;
		status.fRes = 0.85f;
		status.fSpeed = 1.35f;
		status.fLucky = 0.85f;
		break;
	case 7:	//�\�[�h�}�X�^�[
		strcpy(&aCareer[0], "�f�[����");
		status.fLifePoint = 1.55f;
		status.fSkillPoint = 0.65f;
		status.fAttack = 1.75f;
		status.fDefense = 1.15f;
		status.fInt = 1.7f;
		status.fRes = 0.65f;
		status.fSpeed = 1.4f;
		status.fLucky = 0.45f;
		break;
	case 8:	//��
		strcpy(&aCareer[0], "�T�L���o�X");
		status.fLifePoint = 0.85f;
		status.fSkillPoint = 1.95f;
		status.fAttack = 1.25f;
		status.fDefense = 0.95f;
		status.fInt = 1.65f;
		status.fRes = 1.15f;
		status.fSpeed = 1.35f;
		status.fLucky = 1.55f;
		break;

		//�h��^
	case 9:	//�d����m
		strcpy(&aCareer[0], "�f�r��");
		status.fLifePoint = 1.35f;
		status.fSkillPoint = 0.95f;
		status.fAttack = 1.35f;
		status.fDefense = 1.35f;
		status.fInt = 1.8f;
		status.fRes = 0.65f;
		status.fSpeed = 1.25f;
		status.fLucky = 0.95f;
		break;
	case 10:	//�p���f�B��
		strcpy(&aCareer[0], "�X���C��");
		status.fLifePoint = 0.5f;
		status.fSkillPoint = 1.0f;
		status.fAttack = 1.0f;
		status.fDefense = 1.0f;
		status.fInt = 1.95f;
		status.fRes = 1.95f;
		status.fSpeed = 1.0f;
		status.fLucky = 2.95f;
		break;
	case 11:	//�R�m
		strcpy(&aCareer[0], "�l�N���}���T�[");
		status.fLifePoint = 1.8f;
		status.fSkillPoint = 1.0f;
		status.fAttack = 1.25f;
		status.fDefense = 1.55f;
		status.fInt = 1.0f;
		status.fRes = 1.3f;
		status.fSpeed = 0.9f;
		status.fLucky = 1.05f;
		break;
	case 12:	//�b��
		strcpy(&aCareer[0], "�\�E���C�[�^�[");
		status.fLifePoint = 1.75f;
		status.fSkillPoint = 0.9f;
		status.fAttack = 1.95f;
		status.fDefense = 0.45f;
		status.fInt = 0.45f;
		status.fRes = 0.35f;
		status.fSpeed = 1.75f;
		status.fLucky = 1.95f;
		break;
	case 13:	//�b��
		strcpy(&aCareer[0], "�X�P���g��");
		status.fLifePoint = 0.75f;
		status.fSkillPoint = 0.95f;
		status.fAttack = 1.35f;
		status.fDefense = 1.35f;
		status.fInt = 1.0f;
		status.fRes = 1.4f;
		status.fSpeed = 0.95f;
		status.fLucky = 1.45f;
		break;

	case 99:	//���l
		strcpy(&aCareer[0], "����");
		status.fLifePoint = 1.2f;
		status.fSkillPoint = 1.0f;
		status.fAttack = 1.4f;
		status.fDefense = 1.0f;
		status.fInt = 1.0f;
		status.fRes = 1.0f;
		status.fSpeed = 1.0f;
		status.fLucky = 1.0f;
		break;

	case 100:	//����
		strcpy(&aCareer[0], "����");
		status.fLifePoint = 3.0f;
		status.fSkillPoint = 1.0f;
		status.fAttack = 1.8f;
		status.fDefense = 0.5f;
		status.fInt = 1.4f;
		status.fRes = 1.4f;
		status.fSpeed = 0.7f;
		status.fLucky = 1.2f;
		break;
	}

	return status;
}
//=============================================================================
// * �����j���O�}���r�o����
//=============================================================================
void SetRunningman(MODEL_SETTING *set, MODEL_TYPE type)
{
	set[0].nMaxModel = 16;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_RUN_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_RUN_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_RUN_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_RUN_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_RUN_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_RUN_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_RUN_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_RUN_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_RUN_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_RUN_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_RUN_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_RUN_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_RUN_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_RUN_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_RUN_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ type, 5 };
	set[0].nNumMotion[0] = 4;

	for (int nCount = MODEL_TYPE_RUN_bodyD; nCount <= MODEL_TYPE_RUN_footL; nCount++) { LoadModel(nCount); }
	LoadModel(MODEL_TYPE_RUN_Sword0);
	LoadModel(MODEL_TYPE_RUN_Sword1);
	LoadModel(MODEL_TYPE_RUN_Sword2);
}
//=============================================================================
// * �m�[�}���^�r�o����
//=============================================================================
void Set_P_NOR(MODEL_SETTING *set)
{
	set[0].nMaxModel = 15;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_PNOR_hip, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_PNOR_chest, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_PNOR_neck, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_PNOR_head, 2 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_PNOR_chin, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_PNOR_Rhand, 1 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_PNOR_Lhand, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_PNOR_Rleg, 0 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_PNOR_Rknee, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_PNOR_Rfoot, 8 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_PNOR_Lleg, 0 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_PNOR_Lknee, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_PNOR_Lfoot, 11 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_PNOR_tail1, 0 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_PNOR_tail2, 13 };

	for (int nCount = MODEL_TYPE_PNOR_hip; nCount <= MODEL_TYPE_PNOR_tail2; nCount++) { LoadModel(nCount); }

	set[0].nNumMotion[0] = 0;
	set[0].fSlength = 20.0f;
}
//=============================================================================
// * �U���^�r�o����
//=============================================================================
void Set_P_ATK(MODEL_SETTING *set)
{
	set[0].nMaxModel = 20;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_PATK_hip, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_PATK_body, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_PATK_chest, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_PATK_neck, 2 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_PATK_head, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_PATK_chin, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_PATK_legR, 0 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_PATK_kneeR, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_PATK_footR, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_PATK_legL, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_PATK_kneeL, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_PATK_footL, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_PATK_shoulderR, 2 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_PATK_armR, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_PATK_handR, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_PATK_shoulderL, 2 };
	set[0].parent[16] = MODEL_PARENT{ MODEL_TYPE_PATK_armL, 15 };
	set[0].parent[17] = MODEL_PARENT{ MODEL_TYPE_PATK_handL, 16 };
	set[0].parent[18] = MODEL_PARENT{ MODEL_TYPE_PATK_tail1, 0 };
	set[0].parent[19] = MODEL_PARENT{ MODEL_TYPE_PATK_tail2, 18 };

	for (int nCount = MODEL_TYPE_PATK_hip; nCount <= MODEL_TYPE_PATK_tail2; nCount++) { LoadModel(nCount); }

	set[0].nNumMotion[0] = 1;
	set[0].fSlength = 40.0f;
}
//=============================================================================
// * ���@�^�r�o����
//=============================================================================
void Set_P_INT(MODEL_SETTING *set)
{
	set[0].nMaxModel = 24;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_PINT_body3, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_PINT_body2, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_PINT_body1, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_PINT_body0, 2 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_PINT_neck, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_PINT_head, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_PINT_chin, 5 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_PINT_tail0, 0 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_PINT_tail1, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_PINT_wingS, 3 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_PINT_wingL, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_PINT_wingR, 9 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_PINT_armLU, 3 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_PINT_armLD, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_PINT_handL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_PINT_armRU, 3 };
	set[0].parent[16] = MODEL_PARENT{ MODEL_TYPE_PINT_armRD, 15 };
	set[0].parent[17] = MODEL_PARENT{ MODEL_TYPE_PINT_handR, 16 };
	set[0].parent[18] = MODEL_PARENT{ MODEL_TYPE_PINT_legLU, 0 };
	set[0].parent[19] = MODEL_PARENT{ MODEL_TYPE_PINT_legLD, 18 };
	set[0].parent[20] = MODEL_PARENT{ MODEL_TYPE_PINT_footL, 19 };
	set[0].parent[21] = MODEL_PARENT{ MODEL_TYPE_PINT_legRU, 0 };
	set[0].parent[22] = MODEL_PARENT{ MODEL_TYPE_PINT_legRD, 21 };
	set[0].parent[23] = MODEL_PARENT{ MODEL_TYPE_PINT_footR, 22 };

	for (int nCount = MODEL_TYPE_PINT_body3; nCount <= MODEL_TYPE_PINT_footR; nCount++) { LoadModel(nCount); }

	set[0].nNumMotion[0] = 2;
	set[0].fSlength = 40.0f;
}
//=============================================================================
// * �U���^�r�o����
//=============================================================================
void Set_P_SPD(MODEL_SETTING *set)
{
	set[0].nMaxModel = 20;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_PSPD_hip, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_PSPD_third_body, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_PSPD_second_body, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_PSPD_chest, 2 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_PSPD_head, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_PSPD_chin, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rleg, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rknee, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rfoot, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_PSPD_Lleg, 1 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_PSPD_Lknee, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_PSPD_Lfoot, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rshoulder, 3 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rarm, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_PSPD_Rhand, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_PSPD_Lshoulder, 3 };
	set[0].parent[16] = MODEL_PARENT{ MODEL_TYPE_PSPD_Larm, 15 };
	set[0].parent[17] = MODEL_PARENT{ MODEL_TYPE_PSPD_Lhand, 16 };
	set[0].parent[18] = MODEL_PARENT{ MODEL_TYPE_PSPD_tail1, 0 };
	set[0].parent[19] = MODEL_PARENT{ MODEL_TYPE_PSPD_tail2, 0 };

	for (int nCount = MODEL_TYPE_PSPD_hip; nCount <= MODEL_TYPE_PSPD_tail2; nCount++) { LoadModel(nCount); }

	set[0].nNumMotion[0] = 3;
	set[0].fSlength = 40.0f;
}
//=============================================================================
// * �����r�o����
//=============================================================================
void Set_E_KING(MODEL_SETTING *set)
{
	set[0].nMaxModel = 16;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_EKING_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_EKING_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_EKING_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_EKING_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_EKING_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_EKING_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_EKING_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_EKING_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_EKING_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_EKING_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_EKING_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_EKING_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_EKING_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_EKING_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_EKING_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_EKING_Sword, 5 };
	set[0].nNumMotion[0] = 4;
	set[0].fSlength = 20.0f;

	for (int nCount = MODEL_TYPE_EKING_bodyD; nCount <= MODEL_TYPE_EKING_Sword; nCount++) { LoadModel(nCount); }
}
//=============================================================================
// * ��m�r�o����
//=============================================================================
void Set_E_WARRIOR(MODEL_SETTING *set)
{
	set[0].nMaxModel = 16;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_EWarrior_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_EWarrior_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_EWarrior_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_EWarrior_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_EWarrior_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_EWarrior_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_EWarrior_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_EWarrior_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_EWarrior_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_EWarrior_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_EWarrior_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_EWarrior_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_EWarrior_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_EWarrior_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_EWarrior_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_EWarrior_Sword, 5 };
	set[0].nNumMotion[0] = 5;
	set[0].fSlength = 20.0f;

	for (int nCount = MODEL_TYPE_EWarrior_bodyD; nCount <= MODEL_TYPE_EWarrior_Sword; nCount++) { LoadModel(nCount); }
}
//=============================================================================
// * �E�Ҕr�o����
//=============================================================================
void Set_E_NINJA(MODEL_SETTING *set)
{
	set[0].nMaxModel = 17;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_ENinja_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_ENinja_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_ENinja_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_ENinja_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_ENinja_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_ENinja_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_ENinja_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_ENinja_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_ENinja_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_ENinja_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_ENinja_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_ENinja_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_ENinja_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_ENinja_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_ENinja_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_ENinja_Sword1, 5 };
	set[0].parent[16] = MODEL_PARENT{ MODEL_TYPE_ENinja_Sword2, 8 };
	set[0].nNumMotion[0] = 6;
	set[0].fSlength = 20.0f;

	for (int nCount = MODEL_TYPE_ENinja_bodyD; nCount <= MODEL_TYPE_ENinja_Sword2; nCount++) { LoadModel(nCount); }
}
//=============================================================================
// * ���@�g���r�o����
//=============================================================================
void Set_E_WIZARD(MODEL_SETTING *set)
{
	set[0].nMaxModel = 16;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_EWizard_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_EWizard_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_EWizard_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_EWizard_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_EWizard_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_EWizard_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_EWizard_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_EWizard_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_EWizard_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_EWizard_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_EWizard_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_EWizard_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_EWizard_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_EWizard_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_EWizard_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_EWizard_Sword, 5 };
	set[0].nNumMotion[0] = 7;
	set[0].fSlength = 20.0f;

	for (int nCount = MODEL_TYPE_EWizard_bodyD; nCount <= MODEL_TYPE_EWizard_Sword; nCount++) { LoadModel(nCount); }
}
//=============================================================================
// * ��m�r�o����
//=============================================================================
void Set_E_SOLDIERS(MODEL_SETTING *set)
{
	set[0].nMaxModel = 16;
	set[0].parent[0] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_bodyD, -1 };
	set[0].parent[1] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_bodyU, 0 };
	set[0].parent[2] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_head, 1 };
	set[0].parent[3] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_armUR, 1 };
	set[0].parent[4] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_armDR, 3 };
	set[0].parent[5] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_handR, 4 };
	set[0].parent[6] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_armUL, 1 };
	set[0].parent[7] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_armDL, 6 };
	set[0].parent[8] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_handL, 7 };
	set[0].parent[9] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_legUR, 0 };
	set[0].parent[10] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_legDR, 9 };
	set[0].parent[11] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_footR, 10 };
	set[0].parent[12] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_legUL, 0 };
	set[0].parent[13] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_legDL, 12 };
	set[0].parent[14] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_footL, 13 };
	set[0].parent[15] = MODEL_PARENT{ MODEL_TYPE_ESoldiers_Sword, 5 };
	set[0].nNumMotion[0] = 5;
	set[0].fSlength = 20.0f;

	for (int nCount = MODEL_TYPE_ESoldiers_bodyD; nCount <= MODEL_TYPE_ESoldiers_Sword; nCount++) { LoadModel(nCount); }
}
//=============================================================================
// * ���f�����擾����
//=============================================================================
MODEL_INFO *GetModel_Info(void)
{
	return &g_model_Info[0];
}
//=============================================================================
// * ���[�V�������擾����
//=============================================================================
MODEL_MOTION *GetModel_Motion(void)
{
	return &g_model_motion[0][0];
}
//=============================================================================
// * �v���C���[���擾����
//=============================================================================
PLAYER *GetPlayer(void)
{
	static PLAYER Player;

	return &Player;
}
//=============================================================================
// * �G���擾����
//=============================================================================
ENEMY *GetEnemy(void)
{
	static ENEMY Enemy[MAX_ENEMY];

	return &Enemy[0];
}
//=============================================================================
// * �G�f�[�^�擾����
//=============================================================================
CHAR_DATA *GetChar_Data(void)
{
	static CHAR_DATA g_Enemy_Data[MAX_ENEMY_DATA];

	return &g_Enemy_Data[0];
}
//=============================================================================
// * �G�f�[�^����������
//=============================================================================
void InitChar_Data(int nLevel)
{
	CHAR_DATA *data = GetChar_Data();

	char aName[MAX_ENEMY_DATA][25];
	strcpy(&aName[0][0], "�Γc�O��");
	strcpy(&aName[1][0], "����ƍN");
	strcpy(&aName[2][0], "�^�c�K��");
	strcpy(&aName[3][0], "�ɒB���@");
	strcpy(&aName[4][0], "���c�M��");
	strcpy(&aName[5][0], "�L�b�G�g");
	strcpy(&aName[6][0], "�D�c�M��");
	strcpy(&aName[7][0], "�Бq���\�Y");
	strcpy(&aName[8][0], "�㐙�i��");
	strcpy(&aName[9][0], "��������");
	strcpy(&aName[10][0], "���q���G");
	strcpy(&aName[11][0], "���򍲏�");
	strcpy(&aName[12][0], "���c����");
	strcpy(&aName[13][0], "��������");
	strcpy(&aName[14][0], "�c����");
	strcpy(&aName[15][0], "�A�[�T�[��");

	for (int nCntData = 0; nCntData < MAX_ENEMY_DATA; nCntData++)
	{
		data[nCntData] = GetGifted(&aName[nCntData][0]);
		data[nCntData].nLevel = nLevel;
		GetStatus(&data[nCntData], false);
		nLevel++;
	}

	//LoadChar_Data(&data[0]);
	SaveChar_Data(data[0]);
}
//=============================================================================
// * �G�f�[�^���[�h����
//=============================================================================
void LoadChar_Data(CHAR_DATA *data)
{
	FILE *pFile;

	pFile = fopen("data/Enemy.bin", "rb");

	if (pFile != NULL)
	{//Save�@����
		fread(&data[0], sizeof(CHAR_DATA), MAX_ENEMY_DATA, pFile);

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "�G�f�[�^", "���[�h�Ɏ��s���܂���", MB_OK);
	}
}
//=============================================================================
// * �G�f�[�^�Z�[�u����
//=============================================================================
void SaveChar_Data(CHAR_DATA Pdata)
{
	//InitChar_Data();	//���݂̃L�����f�[�^�擾

	CHAR_DATA *data = GetChar_Data();
	//for (int nCntData = 0; nCntData < MAX_ENEMY_DATA - 1; nCntData++)
	//{
	//	data[nCntData] = data[nCntData + 1];
	//}
	//data[MAX_ENEMY_DATA - 1] = Pdata;

	FILE *pFile;
	pFile = fopen("data/Enemy.bin", "wb");

	if (pFile != NULL)
	{//Save�@����
		fwrite(&data[0], sizeof(CHAR_DATA), MAX_ENEMY_DATA, pFile);

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "�G�f�[�^", "�Z�[�u�Ɏ��s���܂���", MB_OK);
	}
}
//=============================================================================
// * �G�X�e�[�^�X�␳����
//=============================================================================
void CorrectionChar_Data(void)
{
	CHAR_DATA *data = GetChar_Data();

	for (int nCntdata = 0; nCntdata < MAX_ENEMY_DATA; nCntdata++)
	{
		if (nCntdata + 1 == MAX_ENEMY_DATA)
		{//�{�X�␳
			data[nCntdata].status.fLifePoint = (int)data[nCntdata].status.fLifePoint * 2.0f;
			data[nCntdata].status.fAttack = data[nCntdata].status.fAttack * 0.25f;
		}
		else
		{
			data[nCntdata].status.fLifePoint = data[nCntdata].status.fLifePoint * (nCntdata * 0.085f + 0.15f);
			data[nCntdata].status.fAttack = data[nCntdata].status.fAttack * (nCntdata * 0.015f + 0.35f);
		}
		data[nCntdata].status.fDefense = data[nCntdata].status.fDefense * (nCntdata * 0.05f + 0.15f);
		data[nCntdata].status.fSpeed = data[nCntdata].status.fSpeed * (nCntdata * 0.05f + 0.35f);
		data[nCntdata].status.fLucky = data[nCntdata].status.fLucky * (nCntdata * 0.05f + 0.45f);
		data[nCntdata].nStrength *= (int)powf(1.1f, nCntdata * 1.0f);

		data[nCntdata].nLifePoint = (int)data[nCntdata].status.fLifePoint;
		data[nCntdata].nSkillPoint = (int)data[nCntdata].status.fSkillPoint;
	}
}
