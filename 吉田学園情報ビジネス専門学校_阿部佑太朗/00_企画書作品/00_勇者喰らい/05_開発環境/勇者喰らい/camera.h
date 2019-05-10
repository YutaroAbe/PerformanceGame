//=============================================================================
//
// �J�������� [camera.h]
// Author : ���{�@��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//���f���̎��
	CAMERA_STATE_NONE = 0,	//�������Ȃ�
	CAMERA_STATE_GAME,		//�Q�[��
	CAMERA_STATE_MOVIE,		//���[�r�[

}CAMERA_STATE;
typedef enum
{//���f���̎��
	CAMERA_VIEW_IGNORE = 0,	//���ɂ��ւ��Ȃ�
	CAMERA_VIEW_FOLLOW,		//�Ǐ]
	CAMERA_VIEW_WATCH,		//�ǂ킸�Ɍ��邾��

}CAMERA_VIEW;
typedef enum
{//���f���̎��
	SCENE_VIEW_NORMAL = 0,	//�ʏ�ʂ蓮��
	SCENE_VIEW_STOP,		//���f���̂ݎ~�܂�

}SCENE_VIEW;
typedef enum
{//���f���̎��
	SCENE_TYPE_NO = 0,	//�߂�@�ԈႦ�悤�̑Ώ�
	SCENE_TYPE_TBOSS,	//���{�X�O�̃V�[��
	SCENE_TYPE_BOSS,	//�{�X�O�̃V�[��

}SCENE_TYPE;

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 vecU;			//������̃x�N�g��

	D3DXVECTOR3 goal;			//�������ʒu
	D3DXVECTOR3 targetpos;		//�Ǐ]����ꏊ
	D3DXVECTOR3 rot;			//�p�x
	D3DXVECTOR3 addpos;			//�J�����̐����ړ���
	float		fDistance;		//�J�����ƒ����_�̋���
	float		fGMagnification;	//�ړI�ɂ����܂ł̔{��

	CAMERA_STATE	state;		//���
	CAMERA_VIEW		ViewC;		//������ �J����
	SCENE_VIEW		ViewS;		//������ �J�����ȊO(���f����)
	SCENE_TYPE		scene;			//���̃V�[����
	int				nCntState;		//���[�r�[�̐i�s�x
	int				nCntModel;		//���̃L������Ǐ]���邩
	int				nCntTime;		//�V�[���̃t���[�����L�^

	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;		//�J�����ݒ�p


}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void ResetCamera(void);
void SetCamera(int nCount);
void SetScene(SCENE_TYPE type);
void UpdateScene(void);
void Scene_TBOSS(void);
void Scene_BOSS(void);
Camera *GetCamera(void);

#endif
