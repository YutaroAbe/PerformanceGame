//=============================================================================
//
// �g���b�v���� [trap.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _TRAP_H_
#define _TRAP_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu
	D3DXVECTOR3 move;   //�ړ���
	int nCounterrMove;  //�ړ���
	int nType;			//���
	float fWindth;		//��
	float fHeight;		//����
	bool bUse;          //�g�p���Ă��邩�ǂ���
}TRAP;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTrap(void);
void UninitTrap(void);
void UpdateTrap(void);
void DrawTrap(void);
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
void CollisionTrap(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //�u���b�N�Ƃ̔��菈��
void CollisionTrapEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight);
TRAP *GetTrap(void);
//bool GetKeyboardPress(int nKey);

#endif

