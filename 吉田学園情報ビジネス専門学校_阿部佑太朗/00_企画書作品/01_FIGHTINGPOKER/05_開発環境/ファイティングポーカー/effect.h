//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author :
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �G�t�F�N�g�̎��
	EFFECTTYPE_GUARD = 0,	// �K�[�h
	EFFECTTYPE_HIT_000,		// �q�b�g��
	EFFECTTYPE_HIT_001,		// �q�b�g��
	EFFECTTYPE_SMOKE_001,	// ��[�W�����v��]
	EFFECTTYPE_SMOKE_002,	// ��[���n��]
	EFFECTTYPE_MAX			// ��ނ̑���
} EFFECTTYPE;

typedef enum
{// �G�t�F�N�g�̃T�C�Y�ω��̎��
	EFFECTSIZE_NONE = 0,	// �ς��Ȃ�
	EFFECTSIZE_UP,			// �g��
	EFFECTSIZE_DOWN,		// �k��
	EFFECTSIZE_MAX			// ��ނ̑���
} EFFECTSIZE;

typedef struct
{
	D3DXMATRIX	mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR	col;		// �F
	float		fRadius_X;	// ���a(�傫��)
	float		fRadius_Y;	// ���a(�傫��)
	float		fClear;		// ����
	int			nLife;		// �\������(����)
	EFFECTTYPE	type;		// ���
	EFFECTSIZE	size;		// �T�C�Y�ω��̎��
	bool		bUse;		// �g�p���Ă��邩�ǂ���
} EFFECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, EFFECTTYPE type);

#endif
