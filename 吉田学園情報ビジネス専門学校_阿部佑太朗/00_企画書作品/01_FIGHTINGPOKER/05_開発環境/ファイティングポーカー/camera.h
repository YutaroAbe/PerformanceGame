//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �J�������� [camera.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_CAMERA	(3)		// �J�����̍ő吔

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �J�����̍\����
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posVDest;		// �ړI�̎��_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 posRDest;		// �ړI�̒����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X�i�e���r�̂悤�ȕ�
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X�i�J�����}���̂悤�ȕ�
	D3DXVECTOR3 rot;			// �p�x
	D3DXVECTOR3 rotDest;		// �ړI�̊p�x
	float fLength;				// ����
	float fHeight;				// ����
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
}Camera;

typedef enum
{ // �o�g�����[�h�̃J�����̗񋓑�
	BATTLE_CAMERA_TYPE_MAIN = 0,	// ���C���J����
	BATTLE_CAMERA_TYPE_MAX,			// ����
}BATTLE_CAMERA_TYPE;

typedef enum
{ // �v���C���[�V���E���[�h�̃J�����̗񋓑�
	PLAYERSHOW_CAMERA_TYPE_PLAYER01 = 0,	// 1P�r���[�|�[�g�J����
	PLAYERSHOW_CAMERA_TYPE_PLAYER02,		// 2P�r���[�|�[�g�J����
	PLAYERSHOW_CAMERA_TYPE_3DUI,			// 3DUI�r���[�|�[�g�J����
	PLAYERSHOW_CAMERA_TYPE_MAX,		// ����
}PLAYERSHOW_CAMERA_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdyCamera);
Camera *GetCamera(void);
#endif
