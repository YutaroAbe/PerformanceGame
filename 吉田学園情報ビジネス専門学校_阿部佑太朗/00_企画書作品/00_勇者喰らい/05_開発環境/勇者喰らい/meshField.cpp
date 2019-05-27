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
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		TEXTURE_EFFECT		"data/TEXTURE/1021_brick_s.jpg"
#define		SPLIT_FIELD			(100)		//�e�N�X�`���ׂ̍���
#define		MAX_CNTVERTEX		(800)
#define		MAX_CLS_F			(50)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct
{//���ڎ��@�Z�[�u�̎�
	int		nCross;
	int		nVertical;
	float	fLengthX;
	float	fLengthZ;

}Field;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//float					g_fDistortion;						//�c�݂̗�
//float					g_fPercent;							//�c�݂̎g�p��

D3DXVECTOR3 vertex[MAX_CNTVERTEX];		//����p�̃��f����͂钸�_
Field	collision[MAX_CLS_F];	//���蕪���
int			g_nCntCLS_F;

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(char *aMapName)
{
	FILE *pFile;			//���[�h
	int nCntSave;
	g_nCntCLS_F = 0;

	if (aMapName != NULL)
	{
		char aMapfllName[48];
		strcpy(&aMapfllName[0], &aMapName[0]);
		//strcat(&aMapfllName[0], "F.bin");


		pFile = fopen(&aMapfllName[0], "rb");

		if (pFile != NULL)
		{//Save�@����
			fread(&g_nCntCLS_F, sizeof(int), 1, pFile);
			fread(&collision[0], sizeof(Field), g_nCntCLS_F, pFile);
			fread(&nCntSave, sizeof(int), 1, pFile);
			fread(&vertex[0], sizeof(D3DXVECTOR3), nCntSave, pFile);

			fclose(pFile);
		}
		else
		{//���s
			MessageBox(0, "", "�Z�[�u�Ɏ��s���܂���", MB_OK);
		}
	}
}

//=============================================================================
// ����������
//=============================================================================
void BreakMeshField(void)
{
	g_nCntCLS_F = 0;
}

//=============================================================================
// �n�ʂ̂����蔻��
//=============================================================================
int CollisionMeshField(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float *fPos, bool bJump, MODEL_SETTING *set)
{
	int	nField = 0;
	//float	fRotCross;										//�ʂ̊p�xX
	//float	fRotVertical;									//�ʂ̊p�xZ
	float	fPercentX;
	float	fPercentZ;
	int		nCntCross;
	int		nCntVertical;
	int		nCntVtx;
	int		nCntVtxP = 0;
	D3DXVECTOR3	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (nCntVtx = 0; nCntVtx < g_nCntCLS_F; nCntVtx++)
	{
		if (pos[0].x < vertex[nCntVtxP].x && pos[0].x > vertex[nCntVtxP + collision[nCntVtx].nCross].x &&
			pos[0].z > vertex[nCntVtxP].z && pos[0].z < vertex[nCntVtxP + collision[nCntVtx].nVertical * (collision[nCntVtx].nCross + 1)].z)
		{//Field�̍��[����E�[�A��O���牜�Ŕ���
			nCntCross = (int)((vertex[nCntVtxP].x - pos[0].x) / collision[nCntVtx].fLengthX);		//���̒��_�̗���Z�o
			nCntVertical = (int)((pos[0].z - vertex[nCntVtxP].z) / collision[nCntVtx].fLengthZ);	//�c�̒��_�̗���Z�o

			length.x = vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross].x - pos[0].x;	//�Z�H����X�̒������Z�o
			length.z = pos[0].z - vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross].z;	//�Z�H����Z�̒������Z�o
			fPercentZ = length.z / collision[nCntVtx].fLengthZ;											//�^�l�p�|���S������Z�̐Z�H�����Z�o
			if (collision[nCntVtx].fLengthX * (1.0f - fPercentZ) > length.x)
			{//�O�p�`�敪�ō��㑤
				fPercentX = length.x / collision[nCntVtx].fLengthX;
				fPercentZ = length.z / collision[nCntVtx].fLengthZ;

				length.x = fPercentX * (vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross + 1].y - vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross].y);
				length.z = fPercentZ * (vertex[nCntVtxP + (nCntVertical + 1) * (collision[nCntVtx].nCross + 1) + nCntCross].y - vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross].y);
				length.y = vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross].y + length.x + length.z;

				//MessageBox(0, "", "", MB_OK);
			}
			else
			{//�O�p�`�敪�ŉE����
			 //�o���p�x�ƒ��������Ƃ�Y�����Z�o
				length.x = collision[nCntVtx].fLengthX - length.x;	//�Z�H����X�̒������Z�o
				length.z = collision[nCntVtx].fLengthZ - length.z;	//�Z�H����Z�̒������Z�o
				fPercentX = length.x / collision[nCntVtx].fLengthX;
				fPercentZ = length.z / collision[nCntVtx].fLengthZ;

				length.x = fPercentX * (vertex[nCntVtxP + (nCntVertical + 1) * (collision[nCntVtx].nCross + 1) + nCntCross].y - vertex[nCntVtxP + (nCntVertical + 1) * (collision[nCntVtx].nCross + 1) + nCntCross + 1].y);
				length.z = fPercentZ * (vertex[nCntVtxP + nCntVertical * (collision[nCntVtx].nCross + 1) + nCntCross + 1].y - vertex[nCntVtxP + (nCntVertical + 1) * (collision[nCntVtx].nCross + 1) + nCntCross + 1].y);
				length.y = vertex[nCntVtxP + (nCntVertical + 1) * (collision[nCntVtx].nCross + 1) + nCntCross + 1].y + length.x + length.z;
			}
			//wsprintf(&aStr[0], "CROSS %d : VERTICAL %d", nCntCross, nCntVertical);
			//ChangeFont(true, &aStr[0], 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			//�ʂ̊p�x�ɂ���ď���
			if (bJump == true && pos[0].y - length.y < 50.0f &&  pos[0].y - length.y > -50.0f)
			{//�n�ʂɂ���
				fPos[0] = length.y;
				nField = 1;
			}
			else if (bJump == false)
			{//��
				if (posold[0].y + 60 >= length.y && pos[0].y <= length.y)
				{//���n
					pos[0].y = length.y;
					fPos[0] = pos[0].y;
					nField = 2;
				}
				//�ӂ��������ڂȂ�ђʑΏ�
			}
		}
		nCntVtxP += (collision[nCntVtx].nVertical + 1) * (collision[nCntVtx].nCross + 1);
	}
	if (nField != 0) { move[0].y = 0.0f; }

	return nField;
}
