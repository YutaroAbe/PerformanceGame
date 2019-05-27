//=============================================================================
//
// �|���S������ [MeshField.cpp]
// Author : ���{��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�C���N���h�t�@�C�� �Z�[�u���[�h�̂���
#include "input.h"
#include "main.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		TEXTURE_EFFECT		"data/TEXTURE/1207_stone_s.jpg"
#define		BACK_WALL			(100.0f)
#define		Distance			(230.0f)
#define		SPLIT				(8)
#define		MAX_CNTVERTEXW		(8000)
//#define		XZ_LENGTH			(15.0f)
#define		XZ_LENGTH1			(1.0f)
#define		XZ_LENGTH2			(4)
#define		XZ_Range			(800.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
//typedef struct
//{//���ڎ��@�Z�[�u�̎�
//	int		nCross;
//	int		nVertical;
//
//}GWall;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int						g_nMaxWall;
int						g_nPlus;		//�v���X�̕�
WallInfo				wallinfo[100];
D3DXVECTOR3				vtxwall[MAX_CNTVERTEXW];

//=============================================================================
// ����������
//=============================================================================
void InitMeshBack(char *aMapName, int nPlus)
{
	FILE *pFile;			//���[�h
	int nCntSave = 1;
	char aMapfllName[48];
	strcpy(&aMapfllName[0], &aMapName[0]);
	strcat(&aMapfllName[0], "W.bin");
	g_nPlus = nPlus;

	pFile = fopen(&aMapfllName[0], "rb");

	if (pFile != NULL)
	{//Save�@����
		fread(&g_nMaxWall, sizeof(int), 1, pFile);
		fread(&wallinfo[0], sizeof(WallInfo), g_nMaxWall, pFile);
		fread(&nCntSave, sizeof(int), 1, pFile);
		fread(&vtxwall[0], sizeof(D3DXVECTOR3), nCntSave, pFile);

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "", "�Z�[�u�Ɏ��s���܂���", MB_OK);
	}
}
//=============================================================================
// ����������
//=============================================================================
void BreakMeshWall(void)
{//�ǂ��Ȃ���
	g_nMaxWall = 0;
}
//=============================================================================
// �ǂ̂����蔻��
//=============================================================================
void CollisionMeshWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float nLength)
{
	if (g_nPlus == 0)
	{
		D3DXVECTOR3 clsPos[5];
		D3DXVECTOR3	length;		//���݂̏ꏊ��������l
								//WallInfo *wallinfo = GetWallInfo();
								//D3DXVECTOR3 *vtxwall = GetVtxWall();

		int		nCntVtx;
		int		nCntWall;
		int		nCntCross;
		int		nCntVertical;
		int		nFlip = 0;
		//vtxwall[0] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//clsPos[0] = vtxwall[2];
		//if (clsPos[0].x == 0.0f) { MessageBox(0, "", "", MB_OK); }

		for (nCntVtx = 0, nCntWall = 0; nCntVtx < g_nMaxWall; nCntVtx++)
		{
			for (nCntVertical = 0; nCntVertical < wallinfo[nCntVtx].nVertical; nCntVertical++)
			{//�c��
				for (nCntCross = 0; nCntCross < wallinfo[nCntVtx].nCross; nCntCross++)
				{//����
				 //Z��
					//if (vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nCntWall].x >= vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + 1 + nCntWall].x)
					//{
					//	nFlip = 0;
					//}//0�Ԃ̂ق����l���傫���ꍇ
					//else { nFlip = 1; }		//1�Ԃ̂ق����l���傫���ꍇ
					clsPos[0 + nFlip] = vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nFlip + nCntWall];
					clsPos[1 - nFlip] = vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + 1 - nFlip + nCntWall];
					clsPos[3 + nFlip] = vtxwall[(nCntVertical + 1) * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nFlip + nCntWall];
					clsPos[4 - nFlip] = vtxwall[(nCntVertical + 1) * (wallinfo[nCntVtx].nCross + 1) + nCntCross + 1 - nFlip + nCntWall];

					//if (move[0].x * move[0].x - move[0].z * move[0].z < 0.2f)
					//{
					//	CollisionVertical(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall);
					//	CollisionCross(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall);
					//}
					if (move[0].x * move[0].x > move[0].z * move[0].z)
					{
						CollisionCross(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall, nLength);
						CollisionVertical(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall, nLength);
					}
					else
					{
						CollisionVertical(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall, nLength);
						CollisionCross(&clsPos[0], &pos[0], &posold[0], &move[0], nCntVertical, nCntCross, nCntVtx, nCntWall, nLength);
					}
				}
			}

			nCntWall += (1 + wallinfo[nCntVtx].nCross) * (1 + wallinfo[nCntVtx].nVertical);
		}
	}
	else
	{
		float fPosX = pos[0].x * pos[0].x;
		float fPosZ = pos[0].z * pos[0].z;
		if (XZ_Range * XZ_Range < fPosX + fPosZ)
		{
			float fRot = atan2f(pos[0].x, pos[0].z);
			pos[0] = D3DXVECTOR3(sinf(fRot) * XZ_Range, pos[0].y, cosf(fRot) * XZ_Range);
		}
	}
}
//=============================================================================
// X�̕ǔ���
//=============================================================================
void CollisionCross(D3DXVECTOR3 *clsPos, D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, int nCntVertical, int nCntCross, int nCntVtx, int nCntWall, float nLength)
{
	float	fPercentX;
	float	fPercentY;
	float	fWidthPos[2];

	if (clsPos[0].z > clsPos[1].z) { fWidthPos[0] = clsPos[0].z; fWidthPos[1] = clsPos[1].z; }
	else { fWidthPos[0] = clsPos[1].z; fWidthPos[1] = clsPos[0].z; }

	if (fWidthPos[0] >= pos[0].z - (nLength / XZ_LENGTH2) && fWidthPos[1] <= pos[0].z + (nLength / XZ_LENGTH2))
	{//X���� Z�����͈͓�
		fPercentX = clsPos[0].z - pos[0].z;						//�Z�H����X�̒������Z�o
		fPercentX = fPercentX / (clsPos[1].z - clsPos[0].z);	//�^�l�p�|���S������X�̐Z�H�����Z�o

		clsPos[2].x = fPercentX * (clsPos[0].x - clsPos[1].x);	//Z���̊p�x�ɉ�����X���̒l���l��

		if (clsPos[0].y - ((clsPos[1].y - clsPos[0].y) * fPercentX) >= pos[0].y - move[0].y && clsPos[3].y - ((clsPos[1].y - clsPos[0].y) * fPercentX) <= pos[0].y - move[0].y + 5.0f)
		{//Y�����͈͓�
			if (clsPos[0].y - clsPos[3].y == 0.0f) { clsPos[2].y = 0.0f; }
			else
			{//����ƍ�����Y�����d�Ȃ��Ă��Ȃ��Ȃ�@Y���ω���Z�v�Z
				if (clsPos[0].y < clsPos[1].y) { clsPos[0] = clsPos[1]; }
				fPercentY = clsPos[0].y - (pos[0].y - move[0].y);	//�Z�H����Y�̒������Z�o
				fPercentY = fPercentY / (clsPos[0].y - clsPos[3].y);	//�^�l�p�|���S������Z�̐Z�H�����Z�o
				clsPos[2].y = fPercentY * (vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nCntWall].x - vtxwall[(nCntVertical + 1) * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nCntWall].x);	//Y���̊p�x�ɉ�����Z���̒l���l��
			}

			//if (vtxwall[nCntCross + 1 + nCntWall].x > vtxwall[nCntCross + nCntWall].x) { fWall = vtxwall[nCntCross + nCntWall].x; }
			//else { fWall = vtxwall[nCntCross + 1 + nCntWall].x; }

			if (posold[0].x > clsPos[0].x + clsPos[2].x - clsPos[2].y)
			{//�O���Z�������̏ꍇ
				if (pos[0].x - nLength - XZ_LENGTH1 <= clsPos[0].x + clsPos[2].x - clsPos[2].y)
				{//���݂̈ʒu���O�ɂȂ��Ă���ꍇ
					pos[0].x = (clsPos[0].x + clsPos[2].x - clsPos[2].y + nLength);
					move[0].x = 0.0f;
				}
			}
			else
			{//�O���Z�����O�̏ꍇ
				if (pos[0].x + nLength - XZ_LENGTH1 >= clsPos[0].x + clsPos[2].x - clsPos[2].y)
				{//���݂̈ʒu���O�ɂȂ��Ă���ꍇ
					pos[0].x = (clsPos[0].x + clsPos[2].x - clsPos[2].y - nLength);
					move[0].x = 0.0f;

				}
			}
		}//Y�͈�
	}//X����
}
//=============================================================================
// Z�̕ǔ���
//=============================================================================
void CollisionVertical(D3DXVECTOR3 *clsPos, D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, int nCntVertical, int nCntCross, int nCntVtx, int nCntWall, float nLength)
{
	float	fPercentY;
	float	fPercentZ;

	if (clsPos[0].x + (nLength / XZ_LENGTH2) >= pos[0].x && clsPos[1].x <= pos[0].x - (nLength / XZ_LENGTH2))
	{//Z���� X�����͈͓�
		fPercentZ = clsPos[0].x - pos[0].x;						//�Z�H����X�̒������Z�o
		fPercentZ = fPercentZ / (clsPos[1].x - clsPos[0].x);	//�^�l�p�|���S������Z�̐Z�H�����Z�o

		clsPos[2].z = fPercentZ * (clsPos[0].z - clsPos[1].z);	//X���̊p�x�ɉ�����Z���̒l���l��

		if (clsPos[0].y - ((clsPos[1].y - clsPos[0].y) * fPercentZ) >= pos[0].y - move[0].y && clsPos[3].y - ((clsPos[1].y - clsPos[0].y) * fPercentZ) <= pos[0].y - move[0].y + 5.0f)
		{//Y�����͈͓�
			if (clsPos[0].y - clsPos[3].y == 0.0f) { clsPos[2].y = 0.0f; }
			else
			{//����ƍ�����Y�����d�Ȃ��Ă��Ȃ��Ȃ�@Y���ω���Z�v�Z
				if (clsPos[0].y < clsPos[1].y) { clsPos[0] = clsPos[1]; }
				fPercentY = clsPos[0].y - pos[0].y;	//�Z�H����Y�̒������Z�o
				fPercentY = fPercentY / (clsPos[0].y - clsPos[3].y);	//�^�l�p�|���S������Z�̐Z�H�����Z�o
				clsPos[2].y = fPercentY * (vtxwall[nCntVertical * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nCntWall].z - vtxwall[(nCntVertical + 1) * (wallinfo[nCntVtx].nCross + 1) + nCntCross + nCntWall].z);	//Y���̊p�x�ɉ�����Z���̒l���l��
			}

			//if (vtxwall[nCntCross + 1 + nCntWall].z > vtxwall[nCntCross + nCntWall].z) { fWall = vtxwall[nCntCross + nCntWall].z; }
			//else { fWall = vtxwall[nCntCross + 1 + nCntWall].z; }

			if (posold[0].z > clsPos[0].z + clsPos[2].z - clsPos[2].y)
			{//�O���Z�������̏ꍇ
				if (pos[0].z - nLength - XZ_LENGTH1 <= clsPos[0].z + clsPos[2].z - clsPos[2].y)
				{//���݂̈ʒu���O�ɂȂ��Ă���ꍇ
					pos[0].z = (clsPos[0].z + clsPos[2].z - clsPos[2].y + nLength);
					move[0].z = 0.0f;

				}
			}
			else
			{//�O���Z�����O�̏ꍇ
				if (pos[0].z + nLength - XZ_LENGTH1 >= clsPos[0].z + clsPos[2].z - clsPos[2].y)
				{//���݂̈ʒu���O�ɂȂ��Ă���ꍇ
					pos[0].z = (clsPos[0].z + clsPos[2].z - clsPos[2].y - nLength);
					move[0].z = 0.0f;

				}
			}
		}//Y�͈�
	}//Z����
}
