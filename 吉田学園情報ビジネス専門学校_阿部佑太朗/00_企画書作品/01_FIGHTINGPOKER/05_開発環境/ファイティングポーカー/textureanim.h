//=============================================================================
//
// �e�N�X�`���A�j���[�V�������� [textureanim.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _TEXTUREANIM_H_
#define _TEXTUREANIM_H_

#include "main.h"

//*****************************************************************************
//	�\����
//*****************************************************************************
typedef enum
{
	TEXANIM_NONE = 0,
	TEXANIM_GRAVITY,		//	�O���r�e�B�o�C���h
	TEXANIM_FISSURES,		//	�n����
	TEXANIM_RAIZIN_R,		//	���C�W���E����
	TEXANIM_RAIZIN_L,		//	���C�W��������
	TEXANIM_GOD,			//	�_�̂�������
	TEXANIM_DARK,			//	�_�[�N�}�^�[
	TEXANIM_MAX				//	�e�N�X�`���A�j���[�V�����̍ő吔
}TEXANIMTYPA;

typedef struct
{
	TEXANIMTYPA type;		//	�e�N�X�`���A�j���[�V�����̎��
	D3DXVECTOR3 pos;		// �ʒu
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	float fRadius_X;		// ��
	float fRadius_Y;		// ����
	D3DXCOLOR col;			// �F
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��NO.
	int nLife;				// �|���S���̏o������
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int nSetMax;			// �|���S���̐�
} Explosion;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//		[	�O���r�e�B�o�C���h	]
#define GRAVITY_CNT_FPS					(6)											//	[	�O���r�e�B�o�C���h	]�X�V����t���[����
#define	GRAVITY_MAX_PATTERN				(2)											//	[	�O���r�e�B�o�C���h	]�p�^�[���̍ő吔
#define GRAVITY_TEX_WIDTH				(1.0f / GRAVITY_MAX_PATTERN)				//	[	�O���r�e�B�o�C���h	]�e�N�X�`���̕�
#define GRAVITY_COLOR					(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			//	[	�O���r�e�B�o�C���h	]�F
#define GRAVITY_RADIUS_X				(50.0f)										//�@[	�O���r�e�B�o�C���h	]�̔��a
#define GRAVITY_RADIUS_Y				(100.0f)										//	[	�O���r�e�B�o�C���h	]�̍���
#define GRAVITY_LIFE					(60)										//	[	�O���r�e�B�o�C���h	]�̎���
#define GRAVITY_MOVE_X					(4.5f)										//	[	�O���r�e�B�o�C���h	]�̉��ɓ����h����
#define GRAVITY_MOVE_Y					(4.5f)										//	[	�O���r�e�B�o�C���h	]�̏c�ɓ����h����
//	[	�n����	]
#define FISSURES_MAX_PATTERN			(6)											//	[	�n����	]�p�^�[���̍ő吔
#define FISSURES_CNT_FPS				(8)											//	[	�n����	]�X�V����t���[����
#define FISSURES_TEX_WIDTH				(1.0f / FISSURES_MAX_PATTERN)				//	[	�n����	]�e�N�X�`���̕�
#define FISSURES_COLOR					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	�n����	]�F
#define FISSURES_RADIUS_X				(100.0f)									//�@[	�n����	]�̔��a
#define FISSURES_RADIUS_Y				(150.0f)									//	[	�n����	]�̍���
//	[	���C�W��R����	]
#define RAIZIN_MAX_PATTERN_R			(10)										//	[	���C�W��R�@]�p�^�[���̍ő吔
#define	RAIZIN_CNT_FPS_R				(4)											//	[	���C�W��R�@]�X�V����t���[����
#define RAIZIN_TEX_WIDTH_R				(1.0f / RAIZIN_MAX_PATTERN_R)				//	[	���C�W��R�@]�e�N�X�`���̕�
#define RAIZIN_COLOR_R					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))			//	[	���C�W��R�@]�F
#define RAIZIN_RADIUS_X_R				(100.0f)									//�@[	���C�W��R�@]�̕�
#define RAIZIN_RADIUS_Y_R				(60.0f)										//	[	���C�W��R�@]�̍���
//	[	���C�W��L����	]
#define RAIZIN_MAX_PATTERN_L			(10)										//	[	���C�W��L�@]�p�^�[���̍ő吔
#define	RAIZIN_CNT_FPS_L				(4)											//	[	���C�W��L�@]�X�V����t���[����
#define RAIZIN_TEX_WIDTH_L				(1.0f / RAIZIN_MAX_PATTERN_L)				//	[	���C�W��L�@]�e�N�X�`���̕�
#define RAIZIN_COLOR_L					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))			//	[	���C�W��L�@]�F
#define RAIZIN_RADIUS_X_L				(100.0f)									//�@[	���C�W��L�@]�̕�
#define RAIZIN_RADIUS_Y_L				(60.0f)										//	[	���C�W��L�@]�̍���
//	[	�_�̂�������	]
#define GOD_MAX_PATTERN					(8)											//	[	�_�̂��������@]�p�^�[���̍ő吔
#define	GOD_CNT_FPS						(8)											//	[	�_�̂��������@]�X�V����t���[����
#define GOD_TEX_WIDTH					(1.0f / GOD_MAX_PATTERN)					//	[	�_�̂��������@]�e�N�X�`���̕�
#define GOD_COLOR						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	�_�̂��������@]�F
#define GOD_RADIUS_X					(120.0f)									//�@[	�_�̂��������@]�̔��a
#define GOD_RADIUS_Y					(270.0f)									//	[	�_�̂��������@]�̍���
//	[	�_�[�N�}�^�[	]
#define DARK_MAX_PATTERN				(10)										//	[	�_�[�N�}�^�[�@]�p�^�[���̍ő吔
#define DARK_CNT_FPS					(6)											//	[	�_�[�N�}�^�[�@]�X�V����t���[����
#define DARK_TEX_WIDTH					(1.0f / DARK_MAX_PATTERN)					//	[	�_�[�N�}�^�[�@]�e�N�X�`���̕�
#define DARK_COLOR						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	�_�[�N�}�^�[�@]�F
#define DARK_RADIUS_X					(60.0f)										//�@[	�_�[�N�}�^�[�@]�̔��a
#define DARK_RADIUS_Y					(60.0f)										//	[	�_�[�N�}�^�[�@]�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTextureAnim(void);
void UninitTextureAnim(void);
void UpdateTextureAnim(void);
void DrawTextureAnim(void);
void SetTextureAnim(D3DXVECTOR3 pos, TEXANIMTYPA type);

#endif
