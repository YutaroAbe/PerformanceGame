//=============================================================================
//
// ���f������ [model.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILENAME0 "data/MODEL/fieldStart.x"
#define MODEL_FILENAME1 "data/MODEL/fieldRed.x"
#define MODEL_FILENAME2 "data/MODEL/fieldGreen.x"
#define MODEL_FILENAME3 "data/MODEL/fieldBlue.x"
#define MODEL_FILENAME4 "data/MODEL/fieldPurple.x"
#define MODEL_FILENAME5 "data/MODEL/fieldYellow.x"
#define MODEL_MOVE_SPEED (0.7f)
#define MODEL_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_MODEL (200)

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	BLOCKCOLOR_START = 0,
	BLOCKCOLOR_RED,
	BLOCKCOLOR_GREEN,
	BLOCKCOLOR_BLUE,
	BLOCKCOLOR_PURPLE,
	BLOCKCOLOR_YELLOW,
	BLOCKCOLOR_MAX,
}BLOCKCOLOR;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 difPos;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	int nIdxShadow;
	bool bUse;
	D3DXVECTOR3 VtxMin;	//���f���̓����蔻��̍ŏ�
	D3DXVECTOR3 VtxMax;	//���f���̓����蔻��̍ő�
	DWORD NumMatModel;	//�}�e���A�����̐�
	BLOCKCOLOR col;		//���f���̐F
}MODEL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

bool CollisionModel(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax,
	MODEL		**pModel);

void SetModel(D3DXVECTOR3 pos,BLOCKCOLOR col);
void SetModelVertex(int nCntModel,int ColNum);

#endif
