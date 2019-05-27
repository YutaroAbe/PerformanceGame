//=========================================================================================================//
//
// �^�C�g���̏��� [Title.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�C���N���h�t�@�C�� �Z�[�u���[�h�̂���
#include "game.h"
#include "main.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//


//=========================================================================================================//
// * �Q�[���̏���������
//=========================================================================================================//
void InitRanking(void)
{
	int *pTime = GetTime();
	pTime[0] = 0;

	SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, 1, 2, ANIMATION_LOOP, EXPLOSIONSTATE_FADE, D3DX_PI * 0.0f, 1);
	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 450, 300, 15, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.07f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 180, 80, 14, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_1);

	//���[�h
	FILE *pFile;
	CHAR_DATA *pChar_Data = GetChar_Data();

	InitChar_Data(1);

	//������
	int nCountData[2];	//�J�E���g�p
	CHAR_DATA nData;

	for (nCountData[0] = 1; nCountData[0] < 16; nCountData[0]++)
	{//���ёւ�������
		for (nCountData[1] = 0; nCountData[1] < nCountData[0]; nCountData[1]++)
		{
			if (pChar_Data[nCountData[0]].nStrength > pChar_Data[nCountData[1]].nStrength)
			{//�傫�����ɑO�ց@(�召��r)
				nData = pChar_Data[nCountData[1]];	//�ۊ�(��)
				pChar_Data[nCountData[1]] = pChar_Data[nCountData[0]];	//����ւ�(��)
				pChar_Data[nCountData[0]] = nData;	//����ւ�(��)
			}
		}
	}

	pFile = fopen("data/Ranking.bin", "rb");

	if (pFile != NULL)
	{//���[�h�@����
	 //fread(&pChar_Data[0], sizeof(CHAR_DATA), 5, pFile);

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "", "���[�h�Ɏ��s���܂���", MB_OK);
	}

	GAME_PLAY *pGamePlay = GetGame_Play();
	int nStrong = -1;

	if (pGamePlay[0].bUse == true)
	{//����ւ�������Ȃ�
		int nCountData;	//�J�E���g�p
		CHAR_DATA Data;
		MODEL_INFO *pmodel = GetModel_Info();

		pChar_Data[5] = pmodel[0].data;
		nStrong = pChar_Data[5].nStrength;
		for (nCountData = 0; nCountData < 5; nCountData++)
		{
			if (pChar_Data[nCountData].nStrength < pChar_Data[5].nStrength)
			{//�傫�����ɑO�ց@(�召��r)
				Data = pChar_Data[5];	//�ۊ�(��)
				pChar_Data[5] = pChar_Data[nCountData];	//����ւ�(��)
				pChar_Data[nCountData] = Data;	//����ւ�(��)
			}
		}
	}

	pFile = fopen("data/Ranking.bin", "wb");

	if (pFile != NULL)
	{//Save�@����
		fwrite(&pChar_Data[0], sizeof(CHAR_DATA), 5, pFile);

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "", "�Z�[�u�Ɏ��s���܂���", MB_OK);
	}

	char aStr[48];
	int nLength;

	for (int nCount = 0; nCount < 5; nCount++)
	{
		strcpy(&aStr[0], &pChar_Data[nCount].aName[0]);
		nLength = (int)strlen(&aStr[0]);//�������m�F
		wsprintf(&aStr[nLength], "  %d", (int)pChar_Data[nCount].nStrength);
		if (nStrong == pChar_Data[nCount].nStrength)
		{
			SetFont(RECT{ 350 , nCount * 125 + 80, 1200, 720 }, D3DXCOLOR{ 1.0f, 0.95f, 0.08f , 1.0f }, &aStr[0], nCount * 2 + 1, 0, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
		}
		else
		{
			SetFont(RECT{ 350 , nCount * 125 + 80, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0f , 1.0f }, &aStr[0], nCount * 2 + 1, 3, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
		}
	}
}
//=========================================================================================================//
// * �Q�[���̏I������
//=========================================================================================================//
void UninitRanking(void)
{
	BreakFont();
	BreakExplosion();
	BreakWindow();
}
//=========================================================================================================//
// * �Q�[���̍X�V����
//=========================================================================================================//
void UpdateRanking(void)
{
	PLAYER *pPlayer = GetPlayer();
	int *pTime = GetTime();
	pTime[0]++;

	UpdateExplosion();
	UpdateFont();
	if (pPlayer[0].bButton[BUTTON_ENTER] == true || pTime[0] == 216)
	{
		SetFade(MODE_TITLE, 0, 0.0f, 0);
	}
}
//=========================================================================================================//
// * �Q�[���̕`�揈��
//=========================================================================================================//
void DrawRanking(void)
{
	DrawExplosion();
	DrawWindow(WINDOW_DRAW_1);
	DrawFont(WINDOW_DRAW_1);
	DrawWindow(WINDOW_DRAW_2);
	DrawFont(WINDOW_DRAW_0);
}
