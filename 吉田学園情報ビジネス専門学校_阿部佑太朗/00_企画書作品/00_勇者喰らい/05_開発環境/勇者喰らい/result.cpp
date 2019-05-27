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
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//


//=========================================================================================================//
// * �Q�[���̏���������
//=========================================================================================================//
void InitResult(void)
{
	int *pTime = GetTime();
	pTime[0] = 0;
	GAME_PLAY *pGame_Play = GetGame_Play();
	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, pGame_Play[0].nResults, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
	if (pGame_Play[0].nResults == 17)
	{//�N���A��ʂȂ�
		//�L�����N�^�[�ۑ�
		//MODEL_INFO *model = GetModel_Info();
		//SaveChar_Data(model[0].data);
		PlaySound(SOUND_LABEL_CLEAR);
	}
	else{ PlaySound(SOUND_LABEL_OVER); }

	pGame_Play[0].nResults = 0;
	pGame_Play[0].nCntPoint = 0;
	pGame_Play[0].bUse = true;


	SetFont(RECT{ 702 , 14, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 1, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 62, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 3, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 111, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 5, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 159, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 7, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 208, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 9, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 256, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 11, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 305, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 13, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 353, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 15, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 402, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 17, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 450, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 19, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 499, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 21, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 547, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 23, 1, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetFont(RECT{ 702 , 632, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 25, 0, DT_LEFT, -1, true, FONTSTATE_NONE, WINDOW_DRAW_1);
}
//=========================================================================================================//
// * �Q�[���̏I������
//=========================================================================================================//
void UninitResult(void)
{
	BreakFont();
	BreakWindow();
}
//=========================================================================================================//
// * �Q�[���̍X�V����
//=========================================================================================================//
void UpdateResult(void)
{
	int *pTime = GetTime();
	GAME_PLAY *pGame_Play = GetGame_Play();
	PLAYER *pPlayer = GetPlayer();
	MODEL_INFO *model = GetModel_Info();
	int		nPoint;
	int		nFont[2];
	bool bEnter = false;

	if (pTime[0] < 140) { pTime[0]++; }
	//UpdateFont();
	if (pTime[0] == 60)
	{ SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 0.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 18, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_FADEIN, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_1); }
	if (pTime[0] == 140)
	{
		do
		{
			if (pPlayer[0].bButton[BUTTON_ENTER] == true) { bEnter = true; }
			switch (pGame_Play[0].nResults)
			{
			case 0:
				nPoint = model[0].data.nLevel; nFont[0] = 1; nFont[1] = 0; break;
			case 2:
				nPoint = (int)model[0].data.status.fLifePoint; nFont[0] = 5; nFont[1] = 4; break;
			case 3:
				nPoint = (int)model[0].data.status.fSkillPoint; nFont[0] = 7; nFont[1] = 6; break;
			case 4:
				nPoint = (int)model[0].data.status.fAttack; nFont[0] = 9; nFont[1] = 8; break;
			case 5:
				nPoint = (int)model[0].data.status.fDefense; nFont[0] = 11; nFont[1] = 10; break;
			case 6:
				nPoint = (int)model[0].data.status.fAttack; nFont[0] = 13; nFont[1] = 8; break;
			case 7:
				nPoint = (int)model[0].data.status.fDefense; nFont[0] = 15; nFont[1] = 10; break;
			case 8:
				nPoint = (int)model[0].data.status.fSpeed; nFont[0] = 17; nFont[1] = 12; break;
			case 9:
				nPoint = (int)model[0].data.status.fLucky; nFont[0] = 19; nFont[1] = 14; break;
			case 10:
				nPoint = model[0].data.nStrength; nFont[0] = 25; nFont[1] = 24; break;
			}

			if (pGame_Play[0].nResults == 1)
			{//�E�Ƃ̕\��
				char aStr[48];
				pGame_Play[0].nResults++;
				GetCareer(model[0].data.nCareer, &aStr[0]);
				ChangeFont(true, &aStr[0], 2, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				ChangeFont(true, &aStr[0], 3, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				PlaySound(SOUND_LABEL_BOTTON003);
			}
			else if (pGame_Play[0].nResults < 11)
			{
				if (nCntPoint(nFont[0], nFont[1], &pGame_Play[0].nCntPoint, nPoint, bEnter) == 1) { pGame_Play[0].nResults++; }
			}
			if (pGame_Play[0].nResults == 11)
			{
				pPlayer[0].bButton[BUTTON_ENTER] = false;
				break;
			}
		} while (bEnter == true);
	}
	if (pGame_Play[0].nResults == 11) { pGame_Play[0].nResults++; PlaySound(SOUND_LABEL_TitleSE001); }
	if (pGame_Play[0].nResults == 12)
	{
		pTime[0]++;
		if (pPlayer[0].bButton[BUTTON_ENTER] == true || pTime[0] == 600)
		{
			SetFade(MODE_RANKING, 0, 0.0f, 0);
		}
	}
}
//=========================================================================================================//
// * �Q�[���̕`�揈��
//=========================================================================================================//
void DrawResult(void)
{
	DrawWindow(WINDOW_DRAW_1);
	DrawFont(WINDOW_DRAW_1);
	DrawWindow(WINDOW_DRAW_2);
	DrawFont(WINDOW_DRAW_0);
}
//=========================================================================================================//
// * �Q�[���̍X�V����
//=========================================================================================================//
int nCntPoint(int nCntFont, int nShadowFont, int *nPoint, int nMaxPoint, bool bCnt)
{
	static int nCntTime = 0;
	nCntTime = (nCntTime + 1) % 7;
	if (nCntTime == 0 && bCnt == false) { PlaySound(SOUND_LABEL_BOTTON003); }
	int	nCntPoint = 1;
	char aStr[25];
	while (1)
	{
		if (nMaxPoint / nCntPoint > 0 && nMaxPoint % (nCntPoint * 10) / nCntPoint > nPoint[0] % (nCntPoint * 10) / nCntPoint)
		{//���̌�������
			nPoint[0] += nCntPoint;
			wsprintf(&aStr[0], "%d", nPoint[0]);
			ChangeFont(true, &aStr[0], nCntFont, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			return 0;
		}
		else if (nMaxPoint / nCntPoint == 0)
		{//���̌����Ȃ��ꍇ
			nPoint[0] = 0;
			return 1;
		}
		nCntPoint *= 10;
	}

	return 0;
}
