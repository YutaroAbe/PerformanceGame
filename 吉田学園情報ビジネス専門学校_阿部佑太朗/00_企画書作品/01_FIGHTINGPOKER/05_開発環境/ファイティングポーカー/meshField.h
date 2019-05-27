//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.h]
// Author : Ebina Riku
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	FIELD_POKER,
	FIELD_PLAYERSHOW,
	FIELD_RESULT,
	FIELD_MAX
}FIELDTYPE;
typedef struct
{
	D3DXVECTOR3 pos;								// �ʒu
	D3DXVECTOR3 move;								// �ړ�
	D3DXVECTOR3 rot;								// ����
	D3DXMATRIX	mtxWorldField;						// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;			// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 pIdxBuffField;			// �C���f�b�N�X�o�b�t�@�̃|�C���^
	float fWidth;									// ��
	float fDepth;									// ����
	int nDivision_X;								// X�̕�����
	int nDivision_Z;								// Z�̕�����
	int MaxVertex;									// ���_�̍ő吔
	int MaxIndex;									// �C���f�b�N�X�̍ő吔
	int MaxPolygon;									// �|���S���̍ő吔
	bool bUse;										// �g�p��
	FIELDTYPE type;
}FIELD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif
