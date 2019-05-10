//========================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : YUTARO ABE
//
//========================================================================
#ifndef _PARTICL_H_
#define _PARTICL_H_

//************************************************************************
// �C���N���[�h�t�@�C��
//************************************************************************
#include "main.h"

//************************************************************************
// �\���̒�`
//************************************************************************
typedef enum
{
	PARTICLETYPE_NONE = 0,
	PARTICLETYPE_DARKMATTER,
	PARTICLETYPE_STONE,
	PARTICLETYPE_MAX
}PARTICLETYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//	�ʒu
	D3DXVECTOR3 nor;			//	�@���x�N�g��
	D3DXVECTOR3 move;			//	�ړ��l
	D3DXCOLOR col;				//	�F
	PARTICLETYPE Type;			//	���
	D3DXVECTOR3 rot;			//	�@���x�N�g��
	D3DXMATRIX mtxWorld;		//	���_�J���[
	float fRadius;				//	���a(�傫��)
	float fLength;				//	����
	int nTypeTx;
	int nLife;					//	�\������(����)
	bool bUse;					//	�g�p���Ă��邩�ǂ���
	int nSetMax;				//	�p�[�e�B�N���̃|���S�����̐ݒ�
} PARTICLE;

//************************************************************************
// �v���g�^�C�v�錾
//************************************************************************
void InitParticle(void);			// �G�t�F�N�g����������
void UninitParticle(void);			// �G�t�F�N�g�I������
void UpdateParticle(void);			// �G�t�F�N�g�X�V����
void DrawParticle(void);			// �G�t�F�N�g�`�揈��
void SetParticle(D3DXVECTOR3 pos,PARTICLETYPE Type);		// �p�[�e�B�N���̐ݒ�

#endif