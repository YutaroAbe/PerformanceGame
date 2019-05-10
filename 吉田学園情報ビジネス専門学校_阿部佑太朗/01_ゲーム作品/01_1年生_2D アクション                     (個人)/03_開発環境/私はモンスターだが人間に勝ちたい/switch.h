//=============================================================================
//
// �X�C�b�`���� [switch.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ʒu
	D3DXVECTOR3 move;	//�ʒu
	int nType;			//���
	float fWindth;		//��
	float fHeight;		//����
	bool bUse;          //�g�p���Ă��邩�ǂ���
}Switch;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSwitch(void);
void UninitSwitch(void);
void UpdateSwitch(void);
void DrawSwitch(void);
void SetSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 move,float fWindth, float fHeight,int nType);
void CollisionSwitch(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight); //�u���b�N�Ƃ̔��菈��
Switch *GetSwitch(void);
//bool GetKeyboardPress(int nKey);

#endif

