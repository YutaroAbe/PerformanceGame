//=============================================================================
//
// �J�������� [camera.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_POSV_Y			(140.0f)	// �J�����̏������_[����]
#define CAMERA_POSV_Z			(-300.0f)	// �J�����̏������_[���s]
#define CAMERA_POSR_Y			(50.0f)		// �J�����̏��������_[����]
#define CAMERA_SPEED			(2.0f)		// �J�����̕��s�ړ����x
#define CAMERA_ROT_SPEED		(0.025f)		// �J�����̉�]���x
#define CAMERA_ZOOMIN_MAX		(50.0f)		// �J�����̍ő�g�勗��
#define CAMERA_ZOOMOUT_MAX		(500.0f)	// �J�����̍ő�k������
#define CAMERA_PLAYER_MIN		(20.0f)		// �����_�ƃv���C���[�̍Œ዗��
#define CAMERA_PLAYER_ADD		(10.0f)		// �ړ��ʂɂ����Z����鋗��
#define CAMERA_FOLLOW_MIN_R		(0.05f)		// �����_�̍Œ�ǐՑ��x
#define CAMERA_FOLLOW_MIN_V		(0.04f)		// ���_�̍Œ�ǐՑ��x
#define CAMERA_FOLLOW_ADD		(0.01f)		// �ړ��ʂɂ����Z�����ǐՑ��x
#define CAMERA_AROUND_TIME		(60 * 2)	// ��荞�݂��J�n����܂ł̎���
#define CAMERA_AROUND_SPEED		(0.02f)		// �J�����̉�荞�ݑ��x
#define CAMERA_MOVIE_SPEED		(0.005f)	// �Љ�f���ł̉�]���x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_aCamera[2];	// �J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{

	g_aCamera[0].Viewport.X = 0;
	g_aCamera[0].Viewport.Y = 0;
	g_aCamera[0].Viewport.Width = SCREEN_WIDTH;
	g_aCamera[0].Viewport.Height = SCREEN_HEIGHT;
	g_aCamera[0].Viewport.MinZ = 0.0f;
	g_aCamera[0].Viewport.MaxZ = 1.0f;


	g_aCamera[0].posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -750.0f);
	g_aCamera[0].posR = D3DXVECTOR3(0.0f, CAMERA_POSR_Y, -450.0f);

	g_aCamera[0].posVDest = g_aCamera[0].posV;
	g_aCamera[0].posRDest = g_aCamera[0].posR;
	g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aCamera[0].rot = D3DXVECTOR3(0.0f, atan2f((g_aCamera[0].posV.x - g_aCamera[0].posR.x),
		(g_aCamera[0].posV.z - g_aCamera[0].posR.z)), 0.0f);
	g_aCamera[0].rotDest = g_aCamera[0].rot;
	g_aCamera[0].fLength = sqrtf((g_aCamera[0].posV.x - g_aCamera[0].posR.x) * (g_aCamera[0].posV.x - g_aCamera[0].posR.x) +
		(g_aCamera[0].posV.z - g_aCamera[0].posR.z) * (g_aCamera[0].posV.z - g_aCamera[0].posR.z));
	g_aCamera[0].nCntStop = 0;
	g_aCamera[0].bOperation = false;

	g_aCamera[1].Viewport.X = 928;
	g_aCamera[1].Viewport.Y = 10;
	g_aCamera[1].Viewport.Width = 205;
	g_aCamera[1].Viewport.Height = 162;
	g_aCamera[1].Viewport.MinZ = 0.0f;
	g_aCamera[1].Viewport.MaxZ = 1.0f;

	g_aCamera[1].posV = D3DXVECTOR3(0.0f, 50.0f, 70.0f);
	g_aCamera[1].posR = D3DXVECTOR3(0.0f, -5.0f, 5.0f);
	g_aCamera[1].vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_aCamera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

		if (GetKeyboardPress(DIK_UP) == true)
		{// �J�����O���ړ�
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - D3DX_PI) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - D3DX_PI) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// �J��������ړ�
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{// �J�������ړ�
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - (-D3DX_PI * 0.5f)) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - (-D3DX_PI * 0.5f)) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// �J�����E�ړ�
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_Q) == true)
		{// �����_������
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_E) == true)
		{// �����_�E����
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_Z) == true)
		{// ���_������
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}

			g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
			g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
		}
		else if (GetKeyboardPress(DIK_C) == true)
		{// ���_�E����
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}

			g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
			g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
		}
		else if (GetKeyboardPress(DIK_Y) == true)
		{// ���_�㏸
			g_aCamera[0].posV.y += CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_N) == true)
		{// ���_���~
			g_aCamera[0].posV.y -= CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_T) == true)
		{// �����_�㏸
			g_aCamera[0].posR.y += CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_B) == true)
		{// �����_���~
			g_aCamera[0].posR.y -= CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_U) == true)
		{// ���_�g��
			if (g_aCamera[0].fLength >= CAMERA_ZOOMIN_MAX)
			{// �������ő�g�勗���ȏ�̏ꍇ
				g_aCamera[0].fLength -= CAMERA_SPEED;
				g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
				g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
			}
		}
		else if (GetKeyboardPress(DIK_M) == true)
		{// ���_�k��
			if (g_aCamera[0].fLength <= CAMERA_ZOOMOUT_MAX)
			{// �������ő�k�������ȉ��̏ꍇ
				g_aCamera[0].fLength += CAMERA_SPEED;
				g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
				g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
			}
		}


		Player *pPlayer = GetPlayer();
		D3DXVECTOR3 move = pPlayer->move;

		// �ړ��ʂ����̏ꍇ���ɒ���
		if (move.x < 0.0f)
		{
			move.x *= -1;
		}
		if (move.y < 0.0f)
		{
			move.y *= -1;
		}
		if (move.z < 0.0f)
		{
			move.z *= -1;
		}

		if (pPlayer->move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{// �v���C���[���ړ����Ă��Ȃ��ꍇ
			g_aCamera[0].nCntStop++;
		}
		else
		{// �v���C���[���ړ����Ă���ꍇ
			g_aCamera[0].nCntStop = 0;
		}

		//// �v���C���[�̔w��ɉ�荞��
		//if (g_aCamera[0].nCntStop >= CAMERA_AROUND_TIME)
		//{
		//	g_aCamera[0].rotDest.y = pPlayer->rot.y - g_aCamera[0].rot.y;
		//	if (g_aCamera[0].rotDest.y < -D3DX_PI)
		//	{
		//		g_aCamera[0].rotDest.y += D3DX_PI * 2.0f;
		//	}
		//	else if (g_aCamera[0].rotDest.y > D3DX_PI)
		//	{
		//		g_aCamera[0].rotDest.y -= D3DX_PI * 2.0f;
		//	}

		//	g_aCamera[0].rot.y += g_aCamera[0].rotDest.y * CAMERA_AROUND_SPEED;
		//	if (g_aCamera[0].rot.y < -D3DX_PI)
		//	{
		//		g_aCamera[0].rot.y += D3DX_PI * 2.0f;
		//	}
		//	else if (g_aCamera[0].rot.y > D3DX_PI)
		//	{
		//		g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
		//	}
		//}

		if (GetKeyboardPress(DIK_LEFT) == true)
		{// ���_�E����
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}
			g_aCamera[0].nCntStop = 0;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// ���_������
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}
			g_aCamera[0].nCntStop = 0;
		}

		// �ړI�̒����_�Ǝ��_��ݒ�
		g_aCamera[0].posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y - D3DX_PI) * (CAMERA_PLAYER_MIN + move.x * CAMERA_PLAYER_ADD);
		g_aCamera[0].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y - D3DX_PI) * (CAMERA_PLAYER_MIN + move.z * CAMERA_PLAYER_ADD);
		g_aCamera[0].posRDest.y = pPlayer->pos.y + CAMERA_POSR_Y;
		g_aCamera[0].posVDest.x = g_aCamera[0].posRDest.x + sinf(g_aCamera[0].rot.y) * (g_aCamera[0].fLength + move.x * CAMERA_PLAYER_ADD);
		g_aCamera[0].posVDest.z = g_aCamera[0].posRDest.z + cosf(g_aCamera[0].rot.y) * (g_aCamera[0].fLength + move.z * CAMERA_PLAYER_ADD);
		g_aCamera[0].posVDest.y = g_aCamera[0].posRDest.y + (CAMERA_POSV_Y - CAMERA_POSR_Y);

		// �J�������v���C���[�ɍ��킹��
		g_aCamera[0].posR.x += (g_aCamera[0].posRDest.x - g_aCamera[0].posR.x) * (CAMERA_FOLLOW_MIN_R + move.x * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posR.z += (g_aCamera[0].posRDest.z - g_aCamera[0].posR.z) * (CAMERA_FOLLOW_MIN_R + move.z * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posR.y += (g_aCamera[0].posRDest.y - g_aCamera[0].posR.y) * CAMERA_FOLLOW_MIN_R;
		g_aCamera[0].posV.x += (g_aCamera[0].posVDest.x - g_aCamera[0].posV.x) * (CAMERA_FOLLOW_MIN_V + move.x * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posV.z += (g_aCamera[0].posVDest.z - g_aCamera[0].posV.z) * (CAMERA_FOLLOW_MIN_V + move.z * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posV.y += (g_aCamera[0].posVDest.y - g_aCamera[0].posV.y) * CAMERA_FOLLOW_MIN_V;

}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(int IdxViewport)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												//�@�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_aCamera[IdxViewport].Viewport);

												// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[IdxViewport].mtxProjection);

	if (IdxViewport == 0)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_aCamera[IdxViewport].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[IdxViewport].Viewport.Width / (float)g_aCamera[IdxViewport].Viewport.Height,
			10.0f,
			6000.0f);
	}
	if (IdxViewport == 1)
	{
		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_aCamera[IdxViewport].mtxProjection,
			D3DXToRadian(30.0f),
			(float)g_aCamera[IdxViewport].Viewport.Width / (float)g_aCamera[IdxViewport].Viewport.Height,
			10.0f,
			6000.0f);
	}
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[IdxViewport].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aCamera[IdxViewport].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_aCamera[IdxViewport].mtxView
		, &g_aCamera[IdxViewport].posV
		, &g_aCamera[IdxViewport].posR
		, &g_aCamera[IdxViewport].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[IdxViewport].mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}
