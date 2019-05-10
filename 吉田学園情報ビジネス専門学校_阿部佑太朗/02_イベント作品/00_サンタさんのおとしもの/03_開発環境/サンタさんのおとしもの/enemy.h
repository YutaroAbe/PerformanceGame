//=============================================================================
//
// �G�̏��� [enemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(128)	// �G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{//�G�̏�Ԃ̎��

	ENEMYSTATE_NOMAL = 0, // �ʏ�_���[�W
	ENEMYSTATE_DAMAGE,//�_���[�W���
	//ENEMYSTATE_DEATH,//���S���
	ENEMYSTATE_MAX

}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DCOLOR col;		//���_�J���[
	int nType;			//���
	int CountLife;	//�o������
	bool bUse;			//�g�p����Ă��邩�ǂ���
	ENEMYSTATE state;	//�G�̏��
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	int nLife;			//�̗�
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No
	//D3DXVECTOR2 STG;	//�o������


}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYSTATE state);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);


#endif
