//=============================================================================
//
// ���f������ [model.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
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
	DWORD NumMatGoal;	//�}�e���A�����̐�
}GOAL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);

bool CollisionGoal(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);

void SetGoal(D3DXVECTOR3 pos);
void SetGoalVertex(int nCntGoal);

#endif
