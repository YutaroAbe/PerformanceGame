//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���{��
//
//=============================================================================
#include "camera.h"
#include "sound.h"
#include "model.h"
#include "input.h"
#include "goburin.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		DISTANCE		(200)			//�����_�Ǝ��_�̋���
#define		CAMERA_MOVE		(2.8f)			//�J�����̈ړ����x
#define		ROTPOOR_RY		(30)			//�����_�㉺ +��, -��
#define		ROTPOOR_VY		(50)				//�J�����{�� +��, -��
#define		MAX_CAMERA		(6)				//�J�����{�� +��, -��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera[MAX_CAMERA];		//�J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		g_camera[nCount].nCntTime = 0;
		g_camera[nCount].nCntState = 0;
		g_camera[nCount].scene = SCENE_TYPE_NO;
		g_camera[nCount].state = CAMERA_STATE_GAME;
		g_camera[nCount].ViewC = CAMERA_VIEW_FOLLOW;
		g_camera[nCount].ViewS = SCENE_VIEW_NORMAL;


		g_camera[nCount].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//���_
		g_camera[nCount].posR = D3DXVECTOR3(0.0f, 0.0f - ROTPOOR_RY, 0.0f);		//�����_
		g_camera[nCount].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�i�j�R��(��)
		g_camera[nCount].goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړI
		g_camera[nCount].rot = D3DXVECTOR3(0.3f, 0.0f, 0.0f);					//�p�x
		g_camera[nCount].addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);			//�J�����Ɨ��ړ�
		g_camera[nCount].targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�Ǐ]����J�����̏ꏊ
		g_camera[nCount].fDistance = DISTANCE;									//���_�ƒ����_�̋���
		g_camera[nCount].fGMagnification = 0.25f;
		g_camera[nCount].nCntModel = -1;

		switch (nCount)
		{
		case 0:
			g_camera[nCount].viewport.X = 0;
			g_camera[nCount].viewport.Y = 0;
			g_camera[nCount].viewport.Width = SCREEN_WIDTH;
			g_camera[nCount].viewport.Height = SCREEN_HEIGHT;
			break;
		case 1:
			g_camera[nCount].viewport.X = 0;
			g_camera[nCount].viewport.Y = SCREEN_HEIGHT / 10;
			g_camera[nCount].viewport.Width = SCREEN_WIDTH;
			g_camera[nCount].viewport.Height = (SCREEN_HEIGHT / 10) * 8;
			break;
		case 2:
			g_camera[nCount].viewport.X = SCREEN_WIDTH / 4;
			g_camera[nCount].viewport.Y = SCREEN_HEIGHT / 8;
			g_camera[nCount].viewport.Width = SCREEN_WIDTH / 2;
			g_camera[nCount].viewport.Height = (SCREEN_HEIGHT / 8) * 6;
			break;
		case 3:
			g_camera[nCount].viewport.X = 1015;
			g_camera[nCount].viewport.Y = 15;
			g_camera[nCount].viewport.Width = 250;
			g_camera[nCount].viewport.Height = 250;
			break;
		case 4:	//�X�g�[���[�S�u�����J����
			g_camera[nCount].viewport.X = SCREEN_WIDTH / 2;
			g_camera[nCount].viewport.Y = 150;
			g_camera[nCount].viewport.Width = SCREEN_WIDTH / 2;					//��
			g_camera[nCount].viewport.Height = 570;								//����
			g_camera[nCount].viewport.MinZ = 0.0f;
			g_camera[nCount].viewport.MaxZ = 1.0f;
			break;
		case 5:	//�Z���N�g�S�u�����J����
			g_camera[nCount].viewport.X = (SCREEN_WIDTH / 2) / 2;
			g_camera[nCount].viewport.Y = 100;
			g_camera[nCount].viewport.Width = SCREEN_WIDTH / 2 + 100;				//��
			g_camera[nCount].viewport.Height = SCREEN_HEIGHT;						//����
			g_camera[nCount].viewport.MinZ = 0.0f;
			g_camera[nCount].viewport.MaxZ = 1.0f;
			break;
		}
		g_camera[nCount].viewport.MinZ = 0.0f;
		g_camera[nCount].viewport.MaxZ = 1.0f;
	}

}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	MODEL_INFO *model = GetModel_Info();
	PLAYER *pPlayer = GetPlayer();
	XINPUT_STATE state;
	XInputGetState(0, &state);
	//static bool bCol = false;

	////���s�ړ�
	//if (GetKeyboardPress(DIK_NUMPAD8) == true) { g_camera.addpos += D3DXVECTOR3(sinf(g_camera.rot.y) * -CAMERA_MOVE, 0.0f, cosf(g_camera.rot.y) * -CAMERA_MOVE); }
	//if (GetKeyboardPress(DIK_NUMPAD5) == true) { g_camera.addpos += D3DXVECTOR3(sinf(g_camera.rot.y) * CAMERA_MOVE, 0.0f, cosf(g_camera.rot.y) * CAMERA_MOVE);	}
	//if (GetKeyboardPress(DIK_NUMPAD6) == true) { g_camera.addpos += D3DXVECTOR3(sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * -CAMERA_MOVE, 0.0f, cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * -CAMERA_MOVE);	}
	//if (GetKeyboardPress(DIK_NUMPAD4) == true) { g_camera.addpos += D3DXVECTOR3(sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE, 0.0f, cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE); }

	//if (GetKeyboardPress(DIK_NUMPAD7) == true) { g_camera.addpos.y += CAMERA_MOVE; }
	//if (GetKeyboardPress(DIK_NUMPAD9) == true) { g_camera.addpos.y += -CAMERA_MOVE; }
	//if (GetKeyboardTrigger(DIK_NUMPAD1) == true)
	//{ 
	//	if (g_camera.nCntModel > -1) { g_camera.nCntModel = -1; }
	//	else { g_camera.nCntModel = 0; }
	//}
	//if (GetKeyboardTrigger(DIK_NUMPAD2) == true) 
	//{ 
	//	if (bCol == false) { bCol = true; }
	//	else { bCol = false; }
	//}
	//if (GetKeyboardTrigger(DIK_NUMPAD3) == true)
	//{ 
	//	if(g_camera.state == CAMERA_STATE_GAME){ g_camera.state = CAMERA_STATE_MOVIE; }
	//	else { g_camera.state = CAMERA_STATE_GAME; }
	//}
	//if(bCol == true){ ColPlayerWindow(1.0f); }
	//else { ColPlayerWindow(0.0f); }


	if (g_camera[0].state == CAMERA_STATE_GAME)
	{
		float fPercentX = 1.0f;
		float fPercentY = 1.0f;

		if (pPlayer[0].bButton[BUTTON_US] == true || pPlayer[0].bButton[BUTTON_OS] == true)
		{ fPercentX = state.Gamepad.sThumbRX * 0.000035f; }
		if (fPercentX < 0.0f) { fPercentX *= -1; }

		if (pPlayer[0].bButton[BUTTON_YS] == true || pPlayer[0].bButton[BUTTON_HS] == true)
		{ fPercentY = state.Gamepad.sThumbRY * 0.000035f; }
		if (fPercentY < 0.0f) { fPercentY *= -1; }

		//���_����
		if (pPlayer[0].bButton[BUTTON_U] == true) { g_camera[0].rot.y += 0.045f * fPercentX; }
		if (pPlayer[0].bButton[BUTTON_O] == true) { g_camera[0].rot.y -= 0.045f * fPercentX; }
		if (pPlayer[0].bButton[BUTTON_Y] == true && g_camera[0].rot.x < D3DX_PI * 0.3f) { g_camera[0].rot.x += 0.03f * fPercentY; }
		if (pPlayer[0].bButton[BUTTON_H] == true && g_camera[0].rot.x > D3DX_PI * -0.3f) { g_camera[0].rot.x -= 0.03f * fPercentY; }
	}
	else { UpdateScene(); }

	if (g_camera[0].rot.y > D3DX_PI) { g_camera[0].rot.y -= D3DX_PI * 2; }
	if (g_camera[0].rot.y < -D3DX_PI) { g_camera[0].rot.y += D3DX_PI * 2; }

	if (g_camera[0].nCntModel > -1)
	{//�Ǐ]�̏ꏊ�̍X�V
		g_camera[0].targetpos += (model[g_camera[0].nCntModel].set.pos + (model[g_camera[0].nCntModel].set.pos - model[g_camera[0].nCntModel].set.posold) * 10.0f - g_camera[0].targetpos) * 0.08f;
		if (g_camera[0].targetpos.y - model[g_camera[0].nCntModel].set.pos.y < -50) { g_camera[0].targetpos.y = model[g_camera[0].nCntModel].set.pos.y - 50; }
		if (g_camera[0].targetpos.y - model[g_camera[0].nCntModel].set.pos.y > 50) { g_camera[0].targetpos.y = model[g_camera[0].nCntModel].set.pos.y + 50; }
	}
	g_camera[0].posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + g_camera[0].targetpos + g_camera[0].addpos;	//����ꏊ + �����ړ���
	//���_�@���� + (�p�x * ����) + �����ړ���
	g_camera[0].goal = D3DXVECTOR3(
		g_camera[0].targetpos.x + (sinf(g_camera[0].rot.y) * g_camera[0].fDistance) * cosf(g_camera[0].rot.x),							//X��
		g_camera[0].targetpos.y + sinf(g_camera[0].rot.x) * g_camera[0].fDistance + ROTPOOR_VY,											//Y��
		g_camera[0].targetpos.z + (cosf(g_camera[0].rot.y) * g_camera[0].fDistance) * cosf(g_camera[0].rot.x)) + g_camera[0].addpos;	//Z��

	g_camera[0].posV += (g_camera[0].goal - g_camera[0].posV) * g_camera[0].fGMagnification;

	//�~�j�}�b�v 0:������, 1:�ߋ���, 2:����
	g_camera[3].posR = model[0].set.pos;
	if(g_camera[3].nCntState == 0 || g_camera[3].nCntState == 2){ g_camera[3].posV = model[0].set.pos + D3DXVECTOR3(sinf(g_camera[0].rot.y) * 10.0f, 5000.0f, cosf(g_camera[0].rot.y) * 10.0f); }
	else{ g_camera[3].posV = model[0].set.pos + D3DXVECTOR3(sinf(g_camera[0].rot.y) * 10.0f, 2000.0f, cosf(g_camera[0].rot.y) * 10.0f); }
	

	GOBURIN *pGoburin;
	pGoburin = GetGOBURIN();
	//���݂̈ʒu
	g_camera[4].posR.x = pGoburin->pos.x;
	g_camera[4].posR.z = pGoburin->pos.z;
	g_camera[4].posR.y = pGoburin->pos.y + 90;

	g_camera[4].posV.x = pGoburin->pos.x - sinf(g_camera[4].rot.y) *  g_camera[4].fDistance;
	g_camera[4].posV.z = pGoburin->pos.z - cosf(g_camera[4].rot.y) *  g_camera[4].fDistance ;
	g_camera[4].posV.y = pGoburin->pos.y + 100;

	//���݂̈ʒu
	g_camera[5].posR.x = pGoburin->pos.x;
	g_camera[5].posR.z = pGoburin->pos.z;
	g_camera[5].posR.y = pGoburin->pos.y + 90;

	g_camera[5].posV.x = pGoburin->pos.x - sinf(g_camera[5].rot.y) *  g_camera[5].fDistance;
	g_camera[5].posV.z = pGoburin->pos.z - cosf(g_camera[5].rot.y) *  g_camera[5].fDistance ;
	g_camera[5].posV.y = pGoburin->pos.y + 100;
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void ResetCamera(void)
{
	if (g_camera[0].nCntModel > -1)
	{//�Ǐ]�̏ꏊ�̍X�V
		MODEL_INFO *model = GetModel_Info();
		g_camera[0].targetpos += (model[g_camera[0].nCntModel].set.pos + (model[g_camera[0].nCntModel].set.pos - model[g_camera[0].nCntModel].set.posold) * 1.0f - g_camera[0].targetpos);
		if (g_camera[0].targetpos.y - model[g_camera[0].nCntModel].set.pos.y < -50) { g_camera[0].targetpos.y = model[g_camera[0].nCntModel].set.pos.y - 50; }
		if (g_camera[0].targetpos.y - model[g_camera[0].nCntModel].set.pos.y > 50) { g_camera[0].targetpos.y = model[g_camera[0].nCntModel].set.pos.y + 50; }
	}
	g_camera[0].goal = D3DXVECTOR3(
		g_camera[0].targetpos.x + (sinf(g_camera[0].rot.y) * g_camera[0].fDistance) * cosf(g_camera[0].rot.x),						//X��
		g_camera[0].targetpos.y + sinf(g_camera[0].rot.x) * g_camera[0].fDistance + ROTPOOR_VY,									//Y��
		g_camera[0].targetpos.z + (cosf(g_camera[0].rot.y) * g_camera[0].fDistance) * cosf(g_camera[0].rot.x)) + g_camera[0].addpos;	//Z��

	g_camera[0].posV += (g_camera[0].goal - g_camera[0].posV) * 1.0f;
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(int nCount)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	
	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera[nCount].viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCount].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera[nCount].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_camera[nCount].viewport.Width / (float)g_camera[nCount].viewport.Height,					//��ʔ䗦,
		10.0f,
		8000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCount].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCount].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera[nCount].mtxView, &g_camera[nCount].posV, &g_camera[nCount].posR, &g_camera[nCount].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCount].mtxView);
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void SetScene(SCENE_TYPE type)
{
	g_camera[0].nCntState = 0;
	g_camera[0].nCntTime = 0;
	g_camera[0].state = CAMERA_STATE_MOVIE;
	g_camera[0].scene = type;
}
//=============================================================================
// �V�[���Đ�����
//=============================================================================
void UpdateScene(void)
{
	if (g_camera[0].state == CAMERA_STATE_MOVIE)
	{//�V�[���Đ�
		switch (g_camera[0].scene)
		{
		case SCENE_TYPE_NO:	//�G���[�����p
			InitCamera();
			g_camera[0].nCntModel = 0;
			break;

		case SCENE_TYPE_TBOSS:	//�{�X�O
			Scene_TBOSS();
			break;

		case SCENE_TYPE_BOSS:	//�{�X�O
			Scene_BOSS();
			break;
		}
	}
}
//=============================================================================
// �{�X�V�[���Đ�����
//=============================================================================
void Scene_TBOSS(void)
{
	CHAR_DATA *data = GetChar_Data();
	MODEL_SETTING set;
	MODEL_INFO *model = GetModel_Info();
	static int nCntEffect;		//���[�r�[���̃G�t�F�N�g

	g_camera[0].nCntTime++;
	switch (g_camera[0].nCntState)
	{
	case 0://������
		SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.0f,0.0f,0.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADEOUT, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
		g_camera[0].fDistance = 40.0f;
		g_camera[0].fGMagnification = 0.01f;
		g_camera[0].addpos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
		g_camera[0].rot = D3DXVECTOR3(-0.32f, 0.0f, 0.0f);
		Set_E_WARRIOR(&set);
		g_camera[0].nCntModel = SetModel(D3DXVECTOR3(0.0f, 300.0f, -7550.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_T, &set, &data[9], 20.0f, 85.0f);
		g_camera[0].nCntState++;
		g_camera[0].nCntTime = 0;
		ColPlayerWindow(0.0f);
		nCntEffect = SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, 3, 4, ANIMATION_LOOP, EXPLOSIONSTATE_FADE, D3DX_PI, 0);
		break;

	case 1:
		if (g_camera[0].nCntTime == 300)
		{
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].ViewS = SCENE_VIEW_STOP;
		}
		break;

	case 2:
		if (g_camera[0].nCntTime == 60)
		{
			SetAnimation(model[g_camera[0].nCntModel].set.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 300, 300, 8, 1, 2, 6, 1, ANIMATION_UP);
			PlaySound(SOUND_LABEL_ATTACK001);
		}
		if (g_camera[0].nCntTime > 120)
		{
			if (g_camera[0].nCntTime % 15 == 0)
			{
				SetZWindow(model[g_camera[0].nCntModel].set.pos + D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXVECTOR3(sinf(g_camera[0].rot.y), 0.0f, cosf(g_camera[0].rot.y)) * 3.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 300, 4, 1, WINDOWSTATE_FADE_Z, 0.02f);
				PlaySound(SOUND_LABEL_ATTACK001);
			}
		}
		if (g_camera[0].nCntTime == 300)
		{
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.0f,0.0f,0.0f, 0.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FADE_ALL, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].ViewS = SCENE_VIEW_STOP;
		}
		break;

	case 3:
		if (g_camera[0].nCntTime == 60) { g_camera[0].nCntState++; g_camera[0].nCntTime = 0; }
		break;

	case 4:
		g_camera[0].ViewS = SCENE_VIEW_NORMAL;
		g_camera[0].rot.y = 0.0f;
		g_camera[0].rot.x = 0.2f;
		g_camera[0].fGMagnification = 0.2f;
		g_camera[0].nCntModel = 0;
		ResetCamera();
		g_camera[0].state = CAMERA_STATE_GAME;
		ChangeExplosion(nCntEffect, EXPLOSIONSTATE_DELETE);
		ColPlayerWindow(1.0f);
		g_camera[0].fDistance = 200.0f;
		g_camera[0].addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);
		break;
	}
}


//=============================================================================
// �{�X�V�[���Đ�����
//=============================================================================
void Scene_BOSS(void)
{
	CHAR_DATA *data = GetChar_Data();
	MODEL_SETTING set;
	MODEL_INFO *model = GetModel_Info();
	static int nCntEffect;		//���[�r�[���̃G�t�F�N�g

	g_camera[0].nCntTime++;
	switch (g_camera[0].nCntState)
	{
	case 0://������
		StopSound();
		g_camera[0].fDistance = 200.0f;
		g_camera[0].fGMagnification = 1.0f;
		g_camera[0].targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[0].rot = D3DXVECTOR3(0.3f, D3DX_PI * -0.5f, 0.0f);
		Set_E_KING(&set);
		g_camera[0].nCntModel = SetModel(D3DXVECTOR3(0.0f, 800.0f, -1000.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_USE_ENEMY_B, &set, &data[15], 15, 85);
		model[g_camera[0].nCntModel].set.nNumMotion[1] = 0;
		model[g_camera[0].nCntModel].set.move.y = 0.0f;
		g_camera[0].nCntState++;
		g_camera[0].nCntTime = 0;
		ResetCamera();
		ColPlayerWindow(0.0f);
		nCntEffect = SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, 3, 4, ANIMATION_LOOP, EXPLOSIONSTATE_FADE, D3DX_PI, 0);
		break;

	case 1:
		g_camera[0].fDistance += 2.5f;
		if (g_camera[0].nCntTime < 145) { g_camera[0].rot.y -= D3DX_PI * 0.008f; }
		else { g_camera[0].rot.y -= D3DX_PI * 0.0035f; }
		if (g_camera[0].nCntTime == 5) { model[g_camera[0].nCntModel].set.nNumMotion[2] = 7; }
		if (g_camera[0].nCntTime == 55) { model[g_camera[0].nCntModel].set.nNumMotion[2] = 26; }
		if (g_camera[0].nCntTime == 195)
		{
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].fGMagnification = 0.1f;
			g_camera[0].fDistance = 100.0f;
			g_camera[0].addpos.y = 50.0f;
		}
		break;

	case 2:
		g_camera[0].rot.y -= D3DX_PI * 0.0035f;
		g_camera[0].rot.x -= D3DX_PI * 0.0035f;
		g_camera[0].fDistance++;
		if (g_camera[0].nCntTime == 65)
		{
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].ViewS = SCENE_VIEW_STOP;
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH - 850, SCREEN_HEIGHT - 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 450, 150, 21, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_FLOW, WINDOWUSE_NORMAL, WINDOWTYPE_CENTER, WINDOW_DRAW_2);

			MODEL_INFO *model = GetModel_Info();
			char aStr[48];
			GetCareer(model[g_camera[0].nCntModel].data.nCareer, &aStr[0]);

			PlaySound(SOUND_LABEL_BOSS_N);
			PlaySound(SOUND_LABEL_BBGM001);
			SetFont(RECT{ 200 , SCREEN_HEIGHT - 200, 1200, 720 }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), &model[g_camera[0].nCntModel].data.aName[0], 17, 4, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_0);
			SetFont(RECT{ 200 , SCREEN_HEIGHT - 250, 1200, 720 }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), &aStr[0], 26, 3, DT_LEFT, -1, true, FONTSTATE_FLOW, WINDOW_DRAW_0);
		}
		break;

	case 3:
		if (g_camera[0].nCntTime == 60)
		{
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].ViewS = SCENE_VIEW_NORMAL;
			g_camera[0].rot.y = D3DX_PI * 0.0f;
			g_camera[0].addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (g_camera[0].nCntTime == 1) { g_camera[0].fDistance = 10.0f; }
			g_camera[0].rot.x = 0.0f;
			g_camera[0].fGMagnification = 1.0f;
		}
		break;

	case 4:
		g_camera[0].fDistance += 8.0f;
		if (g_camera[0].nCntTime == 100)
		{
			g_camera[0].nCntState++; g_camera[0].nCntTime = 0;
			g_camera[0].fDistance = 300.0f;
			g_camera[0].addpos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
			g_camera[0].fGMagnification = 0.1f;
			g_camera[0].rot.y = 0.0f;
			g_camera[0].nCntModel = 0;
		}
		break;

	case 5:
		g_camera[0].rot.x += D3DX_PI * 0.0015f;

		if (g_camera[0].nCntTime == 60) { g_camera[0].nCntState++; g_camera[0].nCntTime = 0; }
		break;

	case 6:
		g_camera[0].state = CAMERA_STATE_GAME;
		ChangeExplosion(nCntEffect, EXPLOSIONSTATE_DELETE);
		ColPlayerWindow(1.0f);
		break;
	}
}//=============================================================================
// �J�������擾����
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera[0];
}
