//=============================================================================
//
// �v���C���[�̏��� [Player.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _PLAYER_H_			//	2�d�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

//*****************************************************************************
//�\����
//*****************************************************************************
typedef enum
{//	�v���C���[�̏��
	PLAYERSTATE_NOMAL = 0,		//	�ʏ�_���[�W
	PLAYERSTATE_DAMAGE,			//	�_���[�W���
	PLAYERSTATE_DEATH,			//	���S���
	PLAYERSTATE_END,			//
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//	�ʒu
	D3DXVECTOR3 move;	//	����
	PLAYERSTATE state;	//	���
	int nCounterState;  //	��ԊǗ��̃J�E���^�[
	int nLife;			//	�̗�
	bool bDisp;			//	�\�����邩���Ȃ����b������treu
	int nType;			//	���
}Player;


//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);		//�����������|���S��
void UninitPlayer(void);		//�I�������|���S��
void UpdatePlayer(void);	//�X�V�����|���S��
void DrawPlayer(void);		//�`�揈���|���S��
void HitPlayer(int nDamage);
void SetPlayer(D3DXVECTOR3 pos, int nType);
Player *GetPlayer(void);

#endif // !

