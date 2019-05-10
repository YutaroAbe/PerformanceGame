//=========================================================================================================//
//
// �Q�[������ [game.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�C���N���h�t�@�C�� �Z�[�u���[�h�̂���
#include "game.h"
#include "fade.h"
#include "main.h"
#include "sound.h"

#include "camera.h"
#include "light.h"
#include "model.h"
#include "fade.h"
#include "object.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// * �}�N���錾 *
//*****************************************************************************
#define S_RANK		(2.25f)
#define AA_RANK		(2.0f)
#define A_RANK		(1.85f)
#define B_RANK		(1.45f)
#define C_RANK		(1.15f)
#define D_RANK		(0.8f)


//=========================================================================================================//
// * �Q�[���̏����������@RESET��
//=========================================================================================================//
void InitStart(void)
{
	int *pTime = GetTime();
	pTime[0] = 0;
	Camera *pCamera = GetCamera();
	GAME *pGame;	//���݂̏�Ԃ��|�C���^�Ŏ擾
	GAME_PLAY *pGame_Play = GetGame_Play();
	Result *pResult = GetResult();
	strcpy(&pResult[0].aStr[0], "");
	pResult[0].nHightFont = 0;
	pResult[0].nWideFont = 0;
	pGame = GetGameState();
	pGame[0].now = GAMESTATE_START;
	pGame_Play[0].bUse = true;

	// �J�����̏���������
	InitCamera();
	InitModel();
	InitObject();
	InitShadow();

	// �}�b�v������
	SetLoad_Map(D3DXVECTOR3(0.0f, 0.0f, 0.0f), MAP_TYPE_000_CHAR_MAKE);
	UpdateMap_Change(-1, -1);

	// ���C�g�̏���������
	InitLight();

	InitShadow();
	InitZWindow();
	pCamera[0].fDistance = 200;
	pCamera[0].addpos.x = 20;
	pCamera[0].addpos.y = 5;
	pCamera[0].nCntModel = 0;
	pCamera[0].state = CAMERA_STATE_GAME;

	// ���O���͉�ʂ̍쐬
	SetFont(RECT{ 470 , 120, 1200, 200 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 0, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
	SetWindow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, SCREEN_HEIGHT / 16, 12, 0, 1, 1, 2, WINDOW_UPDATE_SELECT, WINDOWSTATE_SELECTON, WINDOWUSE_FONT, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
	int *nSetFont = GetSetFont();
	nSetFont[0] = 1;
	InitChar_Data(1);

	MODEL_SETTING set;
	Set_P_NOR(&set);

	PLAYER *pPlayer = GetPlayer();
	pPlayer[0].state = JAYPAD_STATE_SELECT;
	pPlayer[0].bGame = false;
	pPlayer[0].SDstate = SDROP_STATE_NONE;
	pPlayer[0].nCntSDstate = 0;
	for (int nCount = 0; nCount < 3; nCount++) { pPlayer[0].nDSkill[nCount] = -1; }
	for (int nCount = 0; nCount < 3; nCount++) { pPlayer[0].nCntDWindow[nCount] = -1; }

	pPlayer[0].nScnSpeech = -1;
	pPlayer[0].nNumSpeech = 0;

	CHAR_DATA data;
	data = GetGifted("������");
	GetStatus(&data, false);
	data.nLifePoint = (int)data.status.fLifePoint;
	data.nSkillPoint = (int)data.status.fSkillPoint;
	data.nSkill[0][0] = 24;
	data.nSkill[1][0] = 27;

	BreakModel(0);
	SetModel(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_PLAYER, &set, &data, 15.0f, 85.0f);
	MODEL_INFO *model = GetModel_Info();
	model[0].set.state = MODEL_STATE_MAP;
	//UpdateCamera();
	//ResetCamera();
}

//=========================================================================================================//
// * �Q�[���̏I������
//=========================================================================================================//
void UninitStart(void)
{
	GAME *pGame;	//���݂̏�Ԃ��|�C���^�Ŏ擾
	pGame = GetGameState();
	pGame[0].now = GAMESTATE_NONE;

	BreakWindow();
	BreakFont();
	UninitCamera();
	UninitLight();

	UninitShadow();
	UninitModel();
	UninitObject();
	UninitZWindow();
}
//=========================================================================================================//
// * �Q�[���̍X�V����
//=========================================================================================================//
void UpdateStart(void)
{
	int *pTime = GetTime();
	GAME *pGame;	//���݂̏�Ԃ��|�C���^�Ŏ擾
	Result *pResult = GetResult();
	MODEL_INFO *model = GetModel_Info();
	PLAYER *pPlayer = GetPlayer();

	int *nSetFont = GetSetFont();
	bool bSound = true;

	static int nNumber;
	int nLength;
	//PLAYER *pPlayer = GetPlayer();

	pGame = GetGameState();
	//if (bStart == false)
	//{
	

	switch (pGame[0].now)
	{//�Q�[����Ԃɉ����������J�n
	case GAMESTATE_NONE:
		break;

	case GAMESTATE_START:
		if (pPlayer[0].bButton[BUTTON_ENTER] == true)
		{ 
			pGame[0].now = GAMESTATE_NORMAL;
			StopSound();
			PlaySound(SOUND_LABEL_CHAR_MAKE000);
		}
		break;

	case GAMESTATE_NORMAL:
		//���O���͏���
		model[0].set.state = MODEL_STATE_MAP;

		// �J�����̍X�V����
		UpdateCamera();

		// ���C�g�̍X�V����
		UpdateLight();
		UpdateFont();
		UpdateModel();
		UpdateExplosion();
		UpdateAnimation();
		if (pTime[0] > 10) { pTime[0]++; }
		else
		{
			if (pPlayer[0].bButton[BUTTON_W] == true)
			{//��ԏザ��Ȃ���� �I�������
				PlaySound(SOUND_LABEL_BOTTON002);
				if (pResult[0].nHightFont == 5)
				{//�I���, �����ɏo��Ƃ��@���ꂼ��^��ɍ��킹��
					if (pResult[0].nWideFont == 0) { pResult[0].nWideFont = 3; }
					else if (pResult[0].nWideFont == 1) { pResult[0].nWideFont = 5; }
					else if (pResult[0].nWideFont == 2) { pResult[0].nWideFont = 7; }
					else { pResult[0].nWideFont = 9; }
				}
				pResult[0].nHightFont--;
				if (pResult[0].nHightFont == -1)
				{
					if (pResult[0].nWideFont > 8) { pResult[0].nWideFont = 2; }	//�I���ɍ��킹��
					else if (pResult[0].nWideFont > 5) { pResult[0].nWideFont = 1; }	//�J�i�ɍ��킹��
					else { pResult[0].nWideFont = 0; }	//�Ђ�ɍ��킹��
					pResult[0].nHightFont = 5;
				}
			}
			if (pPlayer[0].bButton[BUTTON_S] == true)
			{//��ԉ�����Ȃ���� �I��������
				PlaySound(SOUND_LABEL_BOTTON002);
				if (pResult[0].nHightFont == 4)
				{//�I���, �����ɓ���Ƃ�
					if (pResult[0].nWideFont > 8) { pResult[0].nWideFont = 3; }	//�I���ɍ��킹��
					else if (pResult[0].nWideFont > 5) { pResult[0].nWideFont = 2; }	//�J�i�ɍ��킹��
					else if (pResult[0].nWideFont > 3) { pResult[0].nWideFont = 1; }	//�J�i�ɍ��킹��
					else { pResult[0].nWideFont = 0; }	//�Ђ�ɍ��킹��
				}
				pResult[0].nHightFont++;
				if (pResult[0].nHightFont == 6)
				{//�I���, �����ɏo��Ƃ��@���ꂼ��^��ɍ��킹��
					if (pResult[0].nWideFont == 0) { pResult[0].nWideFont = 3; }
					else if (pResult[0].nWideFont == 1) { pResult[0].nWideFont = 5; }
					else if (pResult[0].nWideFont == 2) { pResult[0].nWideFont = 7; }
					else { pResult[0].nWideFont = 9; }
					pResult[0].nHightFont = 0;
				}
			}
			if (pPlayer[0].bButton[BUTTON_A] == true)
			{//��ԍ�����Ȃ���� �I��������
				PlaySound(SOUND_LABEL_BOTTON002);
				pResult[0].nWideFont--;
				if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == -1) { pResult[0].nWideFont = 3; }
				else if (pResult[0].nWideFont == -1) { pResult[0].nWideFont = 10; }
			}
			if (pPlayer[0].bButton[BUTTON_D] == true)
			{//��ԉE����Ȃ���� �I�����E��
				PlaySound(SOUND_LABEL_BOTTON002);
				pResult[0].nWideFont++;
				if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == 4) { pResult[0].nWideFont = 0; }
				else if (pResult[0].nWideFont == 11) { pResult[0].nWideFont = 0; }
			}
			if (pPlayer[0].bButton[BUTTON_LCTRL] == true)
			{//�I���ɍ��킹��
				pResult[0].nWideFont = 3;
				pResult[0].nHightFont = 5;
			}
			//�g�̍X�V
			FontWindowMove(pResult[0].nWideFont, pResult[0].nHightFont);

			if (pPlayer[0].bButton[BUTTON_ENTER] == true)
			{//�I���ɉ���������
				if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == 3)
				{//�I��
					SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH, SCREEN_HEIGHT / 2, 2, 8, 3, 5, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, D3DX_PI * 0.0f, 1);
					pTime[0] = 11;
					PlaySound(SOUND_LABEL_TitleSE001);
					bSound = false;
				}
				else if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == 2)
				{
					nSetFont[0] = 2;
					//PlaySound(SOUND_LABEL_BOTTON001);
				}	//�J�^�J�i��
				else if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == 1)
				{
					nSetFont[0] = 1;
					//PlaySound(SOUND_LABEL_BOTTON001);
				}	//�Ђ炪�Ȃ�
				else if (pResult[0].nHightFont == 5 && pResult[0].nWideFont == 0)
				{
					nSetFont[0] = 3;
					//PlaySound(SOUND_LABEL_BOTTON001);
				}	//�p���
				else
				{
					nLength = (int)strlen(&pResult[0].aStr[0]);		//�������m�F
					if (nLength < 23) { InputName(nSetFont[0]); }	//���������]���Ă���Ȃ�
					else
					{//���������ő�
						if (nSetFont[0] != 3)
						{//���ƃJ�i�͑��_�ƁZ����
							if ((pResult[0].nHightFont == 1 && pResult[0].nWideFont == 3) || pResult[0].nHightFont == 3 && pResult[0].nWideFont == 3) { InputName(nSetFont[0]); }
						}	//�ϊ��Ȃ�
						if (pResult[0].nHightFont == 4 && pResult[0].nWideFont == 0) { InputName(nSetFont[0]); }	//�������ϊ��ϊ��Ȃ�
						else { PlaySound(SOUND_LABEL_BOTTON001); bSound = false; }//�G���[��
					}
				}
				if(bSound == true){ PlaySound(SOUND_LABEL_BOTTON000); }
			}
			if (pPlayer[0].bButton[BUTTON_BACKSPACE] == true)
			{//�ЂƂ���������
				//PlaySound(SOUND_LABEL_BOTTON003);
				nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F
				if (nLength > 1)
				{ //�����������Ă����
					strcpy(&pResult[0].aStr[nLength - 2], "\0");
					ChangeFont(true, &pResult[0].aStr[0], 0, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F
					if (nLength == 0)
					{
						ChangeFont(false, &pResult[0].aStr[0], 0, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						SetFont(RECT{ 470 , 120, 1200, 200 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, "", 0, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
					}

					PlaySound(SOUND_LABEL_BOTTON001);//�폜��
				}
				else { PlaySound(SOUND_LABEL_BOTTON002); }//�폜���s��
			}
			//�I����NORMAL1�� �X�e�\����
		}

		if (pTime[0] == 30)
		{
			SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, WINDOWSTATE_FADEOUT, WINDOWUSE_NORMAL);

			nSetFont[0] = 0;
			//int	nValue;
			char	aStr[252];
			char	aCareer[48];
			nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F
			if (nLength == 0) { strcat(&pResult[0].aStr[0], "�x���Z���[�W��"); }

			model[0].set.state = MODEL_STATE_NONE;
			strcpy(&model[0].data.aName[0], &pResult[0].aStr[0]);//���O�̑��
			model[0].data = GetGifted(&model[0].data.aName[0]);
			GetStatus(&model[0].data, false);
			model[0].data.nLifePoint = (int)model[0].data.status.fLifePoint;
			model[0].data.nSkillPoint = (int)model[0].data.status.fSkillPoint;
			model[0].data.nSkill[0][0] = 24;
			model[0].data.nSkill[1][0] = 27;

			BackWindow(1);
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 200, 360, 13, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_0);
			ChangeFont(false, "", 0, 0, -1, 0, FONTSTATE_NONE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetFont(RECT{ 50 , 20, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &pResult[0].aStr[0], 13, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 22, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &pResult[0].aStr[0], 0, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "�퓬�� %d", model[0].data.nStrength);
			SetFont(RECT{ 50 , 90, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 14, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 92, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 1, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "�푰 : ");
			nLength = (int)strlen(&aStr[0]);//�������m�F
			GetCareer(model[0].data.nCareer, &aCareer[0]);
			wsprintf(&aStr[nLength], &aCareer[0]);
			SetFont(RECT{ 50 , 140, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 15, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 142, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 2, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "HP %d", (int)model[0].data.status.fLifePoint);
			SetFont(RECT{ 50 , 185, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 16, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 187, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 3, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "MP %d", (int)model[0].data.status.fSkillPoint);
			SetFont(RECT{ 50 , 225, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 17, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 227, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 4, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "ATK %d", (int)model[0].data.status.fAttack);
			SetFont(RECT{ 50 , 265, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 18, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 267, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 5, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "DEF %d", (int)model[0].data.status.fDefense);
			SetFont(RECT{ 50 , 305, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 19, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 307, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 6, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "INT %d", (int)model[0].data.status.fInt);
			SetFont(RECT{ 50 , 345, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 20, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 347, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 7, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "RES %d", (int)model[0].data.status.fRes);
			SetFont(RECT{ 50 , 385, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 21, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 387, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 8, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "SPD %d", (int)model[0].data.status.fSpeed);
			SetFont(RECT{ 50 , 425, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 22, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 427, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 9, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			wsprintf(&aStr[0], "LUK %d", (int)model[0].data.status.fLucky);
			SetFont(RECT{ 50 , 465, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 23, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 467, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 10, 1, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);

			wsprintf(&aStr[0], "");
			nLength = (int)strlen(&aStr[0]);//�������m�F
											//�X�e�[�^�X�ʕ]�� HP
			if (model[0].data.status.fLifePoint - 10000.0f > (INIT_HP * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fLifePoint - 10000.0f >  (INIT_HP * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fLifePoint - 10000.0f >  (INIT_HP * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fLifePoint - 10000.0f >  (INIT_HP * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fLifePoint - 10000.0f >  (INIT_HP * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fLifePoint - 10000.0f >  (INIT_HP * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }
			//�X�e�[�^�X�ʕ]�� SP
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.status.fSkillPoint - 2000.0f > (INIT_SP * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fSkillPoint - 2000.0f  >  (INIT_SP * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fSkillPoint - 2000.0f >  (INIT_SP * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fSkillPoint - 2000.0f >  (INIT_SP * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fSkillPoint - 2000.0f >  (INIT_SP * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fSkillPoint - 2000.0f >  (INIT_SP * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }
			//�X�e�[�^�X�ʕ]�� �U��
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.status.fAttack > (INIT_ATK * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fAttack >  (INIT_ATK * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fAttack >  (INIT_ATK * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fAttack >  (INIT_ATK * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fAttack >  (INIT_ATK * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fAttack >  (INIT_ATK * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }
			//�X�e�[�^�X�ʕ]�� �h��
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.status.fDefense > (INIT_DFF * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fDefense >  (INIT_DFF * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fDefense >  (INIT_DFF * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fDefense >  (INIT_DFF * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fDefense >  (INIT_DFF * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fDefense >  (INIT_DFF * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }
			//�X�e�[�^�X�ʕ]�� ����
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.status.fSpeed > (INIT_SPD * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fSpeed >  (INIT_SPD * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fSpeed >  (INIT_SPD * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fSpeed >  (INIT_SPD * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fSpeed >  (INIT_SPD * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fSpeed >  (INIT_SPD * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }
			//�X�e�[�^�X�ʕ]�� �^
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.status.fLucky - 1000.0f > (INIT_LUK * 2 * 11) * S_RANK) { wsprintf(&aStr[nLength], "S\n"); }
			else if (model[0].data.status.fLucky - 1000.0f  >  (INIT_LUK * 2 * 11) * AA_RANK) { wsprintf(&aStr[nLength], "A+\n"); }
			else if (model[0].data.status.fLucky - 1000.0f  >  (INIT_LUK * 2 * 11) * A_RANK) { wsprintf(&aStr[nLength], "A\n"); }
			else if (model[0].data.status.fLucky - 1000.0f  >  (INIT_LUK * 2 * 11) * B_RANK) { wsprintf(&aStr[nLength], "B\n"); }
			else if (model[0].data.status.fLucky - 1000.0f  >  (INIT_LUK * 2 * 11) * C_RANK) { wsprintf(&aStr[nLength], "C\n"); }
			else if (model[0].data.status.fLucky - 1000.0f  >  (INIT_LUK * 2 * 11) * D_RANK) { wsprintf(&aStr[nLength], "D\n"); }
			else { wsprintf(&aStr[nLength], "E\n"); }

			//�����]��
			wsprintf(&aStr[0], "�]�� : ");
			nLength = (int)strlen(&aStr[0]);//�������m�F
			if (model[0].data.nStrength > 110000) { wsprintf(&aStr[nLength], "��   �_   ��"); }
			else if (model[0].data.nStrength > 1000000) { wsprintf(&aStr[nLength], "��  �V��  ��"); }
			else if (model[0].data.nStrength > 90000) { wsprintf(&aStr[nLength], "�� ���D�G ��"); }
			else if (model[0].data.nStrength > 80000) { wsprintf(&aStr[nLength], "��  �D�G  ��"); }
			else if (model[0].data.nStrength > 70000) { wsprintf(&aStr[nLength], "��  ���}  ��"); }
			else { wsprintf(&aStr[nLength], "�������ڂ�..."); }


			SetFont(RECT{ 50 , 625, 1200, 720 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 27, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);
			SetFont(RECT{ 52 , 627, 1200, 720 }, D3DXCOLOR{ 0.0f, 0.0f, 0.0 , 1.0f }, &aStr[0], 26, 0, DT_LEFT, -1, false, FONTSTATE_NONE, WINDOW_DRAW_1);

			pTime[0] = 0;
			pGame[0].now = GAMESTATE_NORMAL1;
			pPlayer[0].state = JAYPAD_STATE_GAME;

		}
		break;
	case GAMESTATE_NORMAL1:
		//�L�����X�e�[�^�X�m�F �p��or��蒼��
		pTime[0]++;

			// �J�����̍X�V����
			UpdateCamera();

			// ���C�g�̍X�V����
			UpdateLight();

			// �|���S���̍X�V����
			UpdateModel();
			UpdateFont();
			UpdateExplosion();
			UpdateZWindow();
			UpdateAnimation();
			if (pTime[0] == 60)
			{
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 150, 50, 0, 0, 1, 1, 0, WINDOW_UPDATE_SELECT, WINDOWSTATE_FLASH, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_2);
			}
			if (pTime[0] > 120 && pPlayer[0].bButton[BUTTON_ENTER] == true)
			{
				if (pPlayer[0].bButton[BUTTON_JENTER] == true) { SetFade(MODE_GAME, 2, 0.0f, 2); }
				else if (pPlayer[0].bButton[BUTTON_ENTER] == true) { SetFade(MODE_GAME, 2, 0.0f, 1); }
			}
		break;

	case GAMESTATE_END:	//�I���܂ł̃J�E���g�_�E��
		pGame[0].nCntGameState++;
		if (pGame[0].nCntGameState > 200)
		{
			pGame[0].now = GAMESTATE_NONE;
			SetFade(pGame[0].CHANGE, 0, 0.0f, 1);
		}
		break;
	}
	//}
}
//=========================================================================================================//
// * �Q�[���̕`�揈��
//=========================================================================================================//
void DrawStart(void)
{
	// �J�����̐ݒ�
	SetCamera(0);

	// �|���S���̕`�揈��
	DrawModel();
	DrawObject();
	DrawShadow();
	DrawZWindow();
	DrawWindow(WINDOW_DRAW_0);
	DrawFont(WINDOW_DRAW_1);
	DrawWindow(WINDOW_DRAW_1);
	DrawExplosion();
	DrawAnimation();

	DrawWindow(WINDOW_DRAW_2);
	DrawFont(WINDOW_DRAW_0);
}
//=========================================================================================================//
// * �Z�[�u���[�h�̂���
//=========================================================================================================//
Result *GetResult(void)
{
	static Result result;

	return &result;
}
//=========================================================================================================//
// * ���O���͂̑I���ɉ���������
//=========================================================================================================//
void InputName(int nMode)
{
	Result *pResult = GetResult();

	//PlaySound(SOUND_LABEL_BOTTON001);
	if (nMode == 1)
	{//�Ђ�
		if (pResult[0].nWideFont == 0)
		{//��s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�I"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�H"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { InputName3(); }
		}
		else if (pResult[0].nWideFont == 1)
		{//��s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�["); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�]"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�`"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 2)
		{//��s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 3)
		{//��s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { InputName1(); }
			if (pResult[0].nHightFont == 3) { InputName2(); }
		}
		else if (pResult[0].nWideFont == 4)
		{//�܍s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 5)
		{//�͍s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 6)
		{//�ȍs
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 7)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 8)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 9)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 10)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
	}
	else if (nMode == 2)//---------------------------------------------------------------------//
	{//�J�i
		if (pResult[0].nWideFont == 0)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�I"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�H"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { InputName3(); }
		}
		else if (pResult[0].nWideFont == 1)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�["); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�]"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�`"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 2)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 3)
		{//���s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 1) { InputName1(); }
			if (pResult[0].nHightFont == 3) { InputName2(); }
		}
		else if (pResult[0].nWideFont == 4)
		{//�}�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�}"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�~"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "��"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "��"); }
		}
		else if (pResult[0].nWideFont == 5)
		{//�n�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�n"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�q"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�t"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�w"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�z"); }
		}
		else if (pResult[0].nWideFont == 6)
		{//�i�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�i"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�j"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�k"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�l"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�m"); }
		}
		else if (pResult[0].nWideFont == 7)
		{//�^�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�^"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�`"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�c"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�e"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�g"); }
		}
		else if (pResult[0].nWideFont == 8)
		{//�T�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�T"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�V"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�X"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�Z"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�\"); }
		}
		else if (pResult[0].nWideFont == 9)
		{//�J�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�J"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�L"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�N"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�P"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�R"); }
		}
		else if (pResult[0].nWideFont == 10)
		{//�A�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�A"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�C"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�E"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�G"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�I"); }
		}
	}
	else if (nMode == 3)//---------------------------------------------------------------------//
	{//�p��
		if (pResult[0].nWideFont == 0)
		{//0�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�O"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�`"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�k"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�v"); }
			if (pResult[0].nHightFont == 4) { InputName3(); }
		}
		else if (pResult[0].nWideFont == 1)
		{//1�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�P"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�a"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�l"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�w"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 2)
		{//2�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�Q"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�b"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�m"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�x"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 3)
		{//3�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�R"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�c"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�n"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�y"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 4)
		{//4�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�S"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�d"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�o"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 5)
		{//5�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�T"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�e"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�p"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 6)
		{//6�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�U"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�f"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�q"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 7)
		{//7�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�V"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�g"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�r"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 8)
		{//8�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�W"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�h"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�s"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 9)
		{//9�s��
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�X"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�i"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�t"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
		else if (pResult[0].nWideFont == 10)
		{//10�s
			if (pResult[0].nHightFont == 0) { strcat(&pResult[0].aStr[0], "�D"); }
			if (pResult[0].nHightFont == 1) { strcat(&pResult[0].aStr[0], "�j"); }
			if (pResult[0].nHightFont == 2) { strcat(&pResult[0].aStr[0], "�u"); }
			if (pResult[0].nHightFont == 3) { strcat(&pResult[0].aStr[0], "�@"); }
			if (pResult[0].nHightFont == 4) { strcat(&pResult[0].aStr[0], "�@"); }
		}
	}

	//�������Z�b�g����
	ChangeFont(true, &pResult[0].aStr[0], 0, 0, -1, 0, FONTSTATE_NONE,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
//=========================================================================================================//
// * ���O���͂̑I���ɉ����������@�V�ϊ�
//=========================================================================================================//
void InputName1(void)
{
	Result *pResult = GetResult();
	int nLength;
	nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F

	if (nLength > 1)
	{//�V�ɕϊ�
		if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//���s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//���s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//���s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//�͍s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }

		//�J�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�E") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�J") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�K"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�L") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�M"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�N") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�O"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�P") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�Q"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�R") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�S"); }
		//�T�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�T") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�U"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�V") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�W"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�X") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�Y"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�Z") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�["); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�\") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�]"); }
		//�^�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�^") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�_"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�`") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�a"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�c") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�d"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�e") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�f"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�g") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�h"); }
		//�n�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�n") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�o"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�q") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�r"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�t") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�u"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�w") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�x"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�z") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�{"); }
		//�ύs
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//�p�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�p") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�o"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�s") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�r"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�v") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�u"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�y") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�x"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�|") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�{"); }
	}
	else {}//���s��
}
//=========================================================================================================//
// * ���O���͂̑I���ɉ����������@�K�ϊ�
//=========================================================================================================//
void InputName2(void)
{
	Result *pResult = GetResult();
	int nLength;
	nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F

	if (nLength > 1)
	{//�Z�ɕϊ�
	 //�͍s
		if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//�n�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�n") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�p"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�q") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�s"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�t") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�v"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�w") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�z") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�|"); }
		//��
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//�o�s
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�o") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�p"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�r") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�s"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�u") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�v"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�x") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�{") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�|"); }
	}
	else {}//���s��
}
//=========================================================================================================//
// * ���O���͂̑I���ɉ����������@�������ϊ�
//=========================================================================================================//
void InputName3(void)
{
	Result *pResult = GetResult();
	int nLength;
	nLength = (int)strlen(&pResult[0].aStr[0]);//�������m�F

	if (nLength > 1)
	{//�������ɕϊ�
		if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }

		//�J�^�J�i
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�A") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�@"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�C") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�B"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�E") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�D"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�G") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�F"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�I") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�H"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�c") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�b"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�J") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�P") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		
		//�p��
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�`") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�a") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�b") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�c") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�d") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�e") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�f") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�g") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�h") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�i") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�j") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�k") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�l") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�m") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�n") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�o") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�p") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�q") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�r") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�s") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�t") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�u") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�v") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�w") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�x") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "�y") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "��"); }
		//
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�`"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�a"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�b"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�c"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�d"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�e"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�f"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�g"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�h"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�i"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�j"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�k"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�l"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�m"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�n"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�o"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�p"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�q"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�r"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�s"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�t"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�u"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�v"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�w"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�x"); }
		else if (strcmp(&pResult[0].aStr[nLength - 2], "��") == 0) { strcpy(&pResult[0].aStr[nLength - 2], "�y"); }
	}
	else {}//���s��
}