//=============================================================================
//
// item�̏��� [item.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DCOLOR col;		//���_�J���[
	float fAngle;
	float fLength;
	float fWindth;		//��
	float fHeight;		//����
	int nType;			//���
	bool bUse;			//�g�p����Ă��邩�ǂ���
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No
	int nNumItem;
}Item;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move);
Item *Getitem(void);
void CollisionItem(D3DXVECTOR3 *pPos, float *fWindth, float *fHeight); //�u���b�N�Ƃ̔��菈��


#endif
