//=============================================================================
//
// �G���̏��� [sideenemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _SIDEENEMY_H_
#define _SIDEENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_SIDEENEMY	(128)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�G�̏�Ԃ̎��

	SIDEENEMYSTATE_NOMAL = 0,
	SIDEENEMYSTATE_DAMAGE,
	SIDEENEMYSTATE_MAX

}SIDEENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DCOLOR col;		//���_�J���[
	int nType;			//���
	bool bUse;			//�g�p����Ă��邩�ǂ���
	SIDEENEMYSTATE state;	//�G�̏��
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	//int nLife;			//�̗�
}SideEnemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSideEnemy(void);
void UninitSideEnemy(void);
void UpdateSideEnemy(void);
void DrawSideEnemy(void);
void SetSideEnemy(D3DXVECTOR3 pos, int nType);
SideEnemy *GetSideEnemy(void);
void HitSideEnemy(int nCntSideEnemy, int nDamage);


#endif
