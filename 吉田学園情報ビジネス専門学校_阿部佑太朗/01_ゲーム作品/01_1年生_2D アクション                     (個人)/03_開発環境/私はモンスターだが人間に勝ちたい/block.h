//=============================================================================
//
// �u���b�N���� [block.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

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
}Block;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //�u���b�N�Ƃ̔��菈��
void CollisionBlockEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight);
Block *Getblock(void);
//bool GetKeyboardPress(int nKey);

#endif

