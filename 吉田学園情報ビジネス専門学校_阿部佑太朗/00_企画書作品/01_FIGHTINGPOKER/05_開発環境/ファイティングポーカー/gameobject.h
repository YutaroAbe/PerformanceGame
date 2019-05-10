//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �I�u�W�F�N�g���� [gameobject.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_GAMEOBJECT			(64)
#define MAX_GAMEOBJECT_TEX		(6)		// �I�u�W�F�N�g��ɑ΂���e�N�X�`���̍ő吔

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	GAMEOBJECTCATEGORY_00 = 0,		// �u���b�N
	GAMEOBJECTCATEGORY_01,			// �u���b�N
	GAMEOBJECTCATEGORY_02,			// �u���b�N
	GAMEOBJECTCATEGORY_03,			// �u���b�N
	GAMEOBJECTCATEGORY_04,			// �u���b�N
	GAMEOBJECTCATEGORY_05,			// �u���b�N
	GAMEOBJECTCATEGORY_06,			// �u���b�N
	GAMEOBJECTCATEGORY_07,			// �u���b�N
	GAMEOBJECTCATEGORY_08,			// �u���b�N
	GAMEOBJECTCATEGORY_09,			// �u���b�N
	GAMEOBJECTCATEGORY_10,			// �u���b�N
	GAMEOBJECTCATEGORY_MAX				// ����
}GAMEOBJECTCATEGORY;


typedef struct
{
	LPD3DXMESH pMesh;				// ���b�V���i���_�̏W�܂�j���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD nNumMat;					// �}�e���A�����̐�
	LPDIRECT3DTEXTURE9 pTexture[MAX_GAMEOBJECT_TEX];	// �I�u�W�F�N�g��̂ɑ΂���e�N�X�`��
	char *pFilename;				// �t�@�C����
	D3DXVECTOR3 vtxMin;				// ���_���W�̍ŏ��l
	D3DXVECTOR3	vtxMax;				// ���_���W�̍ő�l
}GameObjectModelData;

typedef struct
{
	D3DXVECTOR3	pos;				// �ʒu�i���S���W�j
	D3DXVECTOR3	posOld;				// �O��ʒu�i���S���W�j
	D3DXVECTOR3	move;				// �ړ���
	D3DXCOLOR col;					// �F
	D3DXVECTOR3	rot;				// ����
	D3DXMATRIX	mtxWorldGameObject;	// ���[���h�}�g���b�N�X
	int ModelType;					// �g�p���郂�f���̎��
	bool bUse;						// �g�p���Ă��邩�ǂ���
	bool bDisp;						// �\�����邩�ǂ���
}GameObject;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitGameObject(void);
void UninitGameObject(void);
void UpdateGameObject(void);
void DrawGameObject(void);
void SetGameObject(D3DXVECTOR3 pos, int ModelType);
GameObject *GetGameObject(void);
GameObjectModelData *GetGameObjectModel(void);
void LoadModelGameObject(void);
#endif
