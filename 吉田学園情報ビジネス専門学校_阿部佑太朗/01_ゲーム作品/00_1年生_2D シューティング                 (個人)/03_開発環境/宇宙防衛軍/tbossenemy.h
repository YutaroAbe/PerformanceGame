//=============================================================================
//
// ���{�X�G�̏��� [tbossenemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _TBOSSENEMY_H_
#define _TBOSSENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TBOSSENEMY	(4)				//  �G�̍ő吔
#define BOSSENEMY_SIZEMAX (100)			// 	�G�̑傫��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�G�̏�Ԃ̎��

	TBOSSENEMYSTATE_NOMAL = 0, // �ʏ�_���[�W
	TBOSSENEMYSTATE_DAMAGE,//�_���[�W���
	//ENEMYSTATE_DEATH,//���S���
	TBOSSENEMYSTATE_MAX

}TBOSSENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//����
	D3DCOLOR col;		//���_�J���[
	int nType;			//���
	bool bUse;			//�g�p����Ă��邩�ǂ���
	int nCounterBullet;
	//bool bDisp;
	TBOSSENEMYSTATE state;	//�G�̏��
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	int nLife;			//�̗�
}TBossEnemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTBossEnemy(void);
void UninitTBossEnemy(void);
void UpdateTBossEnemy(void);
void DrawTBossEnemy(void);
void SetTBossEnemy(D3DXVECTOR3 pos,int nType);
TBossEnemy *GetTBossEnemy(void);
void HitTBossEnemy(int nCntTBossEnemy, int nDamage);


#endif
