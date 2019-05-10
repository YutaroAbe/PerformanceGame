//=============================================================================
//
// �J�������� [camera.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef enum
{// �J�����̎��
	CAMERATYPE_MAIN = 0,	// ���C��
	CAMERATYPE_EVENT,		// �C�x���g�p
	CAMERATYPE_MAX			// ��ނ̑���
} CAMERATYPE;

typedef struct
{
	D3DXVECTOR3	posV;			// ���݂̎��_
	D3DXVECTOR3	posR;			// ���݂̒����_
	D3DXVECTOR3	posVDest;		// �ړI�̎��_
	D3DXVECTOR3	posRDest;		// �ړI�̒����_
	D3DXVECTOR3	vecU;			// ������x�N�g��
	D3DXMATRIX	mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	mtxView;		// �r���[�}�g���b�N�X
	D3DXVECTOR3	rot;			// ���݂̌���
	D3DXVECTOR3	rotDest;		// �ړI�̌���
	float		fLength;		// �����_�Ǝ��_�̋���
	int			nCntStop;		// ��~����
	bool		bOperation;		// ����\���ǂ���
	D3DVIEWPORT9 Viewport;		//�r���[�|�[�g
} Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int IdxViewport);
Camera *GetCamera(void);

#endif
