//=============================================================================
//
// �e�̏��� [bullet.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{//�e�̎��
	BULLETTYPE_000 = 0,	//�e�̎��[0]
	BULLETTYPE_001,		//�e�̎��[1]
	BULLETTYPE_MAX
}BULLETTYPE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);


#endif
