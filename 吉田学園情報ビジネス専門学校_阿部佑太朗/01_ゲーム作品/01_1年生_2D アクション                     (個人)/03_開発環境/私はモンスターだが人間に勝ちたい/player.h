//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _PLAYER_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

#include "main.h"
#include "block.h"

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{
	//PLAYERSTATE_APPEAR=0,		//�o����ԁi���G�j
	PLAYERSTATE_NOMAL = 0,		//�ʏ�_���[�W
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_END,
	PLAYERSTATE_MAX
}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	PLAYERSTATE state;
	int nLife;			//�̗�
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	bool bDisp;			//�\�����邩���Ȃ����b������treu
	int nType;			//���
	int nCounterAnim;
	int nPatternAnim;
	float fWindth;		//��
	float fHeight;		//����
	int DirectMove;
	bool bJump;
	//Block *pBlock;

}PLAYER;
//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);		//�����������|���S��
void UninitPlayer(void);	//�I�������|���S��
void UpdatePlayer(void);	//�X�V�����|���S��
void DrawPlayer(void);		//�`�揈���|���S��
void SetPlayer(D3DXVECTOR3 pos, int nType);
void HitPlayer(int nDamage);
PLAYER *GetPlayer(void);
#endif // !

