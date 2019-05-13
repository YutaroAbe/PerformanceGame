//=============================================================================
//
// �S�u�������� [goburin.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _GOBURIN_H_
#define _GOBURIN_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{// �S�u�����̃��[�V�����̎��
	GOBURINMOTIONTYPE_NEUTRAL = 0,								// �j���[�g����
	GOBURINMOTIONTYPE_MOVE,										// �������[�V����
	GOBURINMOTIONTYPE_MAX										// ��ނ̑���
}GOBURINMOTIONTYPE;

typedef struct
{// �S�u�����̃��f���̏��
	LPD3DXMESH		pMesh = NULL;								// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMat = NULL;							// �}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	*pTex = NULL;							// �e�N�X�`�����ւ̃|�C���^
	D3DMATERIAL9	*pCol = NULL;								// ���݂̐F�ւ̃|�C���^
	D3DMATERIAL9	*pColDef = NULL;							// �f�t�H���g�̐F�ւ̃|�C���^
	DWORD			nNumMat = 0;								// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR3		posFarst;									// �����̈ʒu
	D3DXVECTOR3		pos;										// �ʒu
	D3DXVECTOR3		rot;										// ����
	int				nIdxModelParent;							// �e���f���̃C���f�b�N�X
	char			aName[128];									// �ǂݍ��ރ��f���̖��O
} GOBURINModel;

typedef struct
{// �S�u�����̃L�[�̏��
	D3DXVECTOR3	*aPos = NULL;									// �ʒu
	D3DXVECTOR3	*aRot = NULL;									// ����
	int			nNumFrame;										// �X�V����t���[����
} GOBURINKey;

typedef struct
{// �S�u�����̃��[�V�����̏��
	int			nLoop;											// ���[�v���邩�ǂ���[ ���Ȃ� = 0, ���� = 1 ]
	int			nNumKey;										// �L�[�̐�
	GOBURINKey	*aGOBURINKey = NULL;							// �L�[�̏��
	
} GOBURINMotion;

typedef struct
{// �S�u�����̏��
	D3DXMATRIX			mtxWorld;								// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;									// ���݂̈ʒu
	D3DXVECTOR3			rot;									// ����
	D3DXVECTOR3			rotDest;								// �ړI�̌���
	int					nNumModel;								// ���f����
	GOBURINModel		*aGOBURINModel = NULL;				// ���f���̏��ւ̃|�C���^
	GOBURINMotion		aGOBURINMotion[GOBURINMOTIONTYPE_MAX];	// ���[�V�����̏��
	GOBURINMOTIONTYPE	motionType;								// ���݂̃��[�V�����̎��
	int					nKey;									// ���݂̃L�[
	int					nCntFrame;								// �o�߃t���[��
	int					nMaxCntFrame;							// �����o�߃t���[��
	bool				bDisp;									// �o�����Ă邩�ǂ���
	bool				bMove;									// ���������ǂ���
} GOBURIN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGOBURIN(void);
void UninitGOBURIN(void);
void UpdateGOBURIN(void);
void DrawGOBURIN(void);
GOBURIN *GetGOBURIN(void);

#endif
