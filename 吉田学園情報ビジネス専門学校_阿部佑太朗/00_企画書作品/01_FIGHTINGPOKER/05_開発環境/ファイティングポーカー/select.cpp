//=============================================================================
//
// �Z���N�g��ʏ��� [select.h]
// Author :
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "select.h"
#include "select2D.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//=============================================================================
// �Z���N�g��ʂ̏���������
//=============================================================================
void InitSelect(void)
{
	// �w�i�̏���������
	InitBG();
	// �Z���N�g�̏���������
	InitSelect2D();
}

//=============================================================================
// �Z���N�g��ʂ̏I������
//=============================================================================
void UninitSelect(void)
{
	// �w�i�̏I������
	UninitBG();
	// �Z���N�g�̏I������
	UninitSelect2D();
}

//=============================================================================
// �Z���N�g��ʂ̍X�V����
//=============================================================================
void UpdateSelect(void)
{
	// �w�i�̍X�V
	UpdateBG();

	// �Z���N�g�̍X�V
	UpdateSelect2D();

	FADE fade;
	fade = GetFade();

	SELECTTYPE SelectType;
	SelectType = GetSelectType();
	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
	{
		if (fade != FADE_OUT)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			switch (SelectType)
			{
			case SELECT_BATTLE:
				//���[�h�ݒ�
				SetFade(MODE_GAME);
				break;
			case SELECT_RULE:
				//���[�h�ݒ�
				SetFade(MODE_RULE);
				break;
			case SELECT_CREDIT:
				//���[�h�ݒ�
				SetFade(MODE_CREDIT);
				break;
			case SELECT_RETURN:
				//���[�h�ݒ�
				StopSound(SOUND_LABEL_SELECT_BGM);
				SetFade(MODE_TITLE);
				break;
			}
		}
	}
}

//=============================================================================
// �Z���N�g��ʂ̕`�揈��
//=============================================================================
void DrawSelect(void)
{
	// �w�i�̕`�揈��
	DrawBG();
	// �Z���N�g�̕`�揈��
	DrawSelect2D();
}
