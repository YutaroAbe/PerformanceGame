//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{// �e�̏��
	ITEMKIND_NONE = 0,	// �A�C�e���������Ă��Ȃ�
	ITEMKIND_MIKIYA0,	// �A�C�e��0
	ITEMKIND_MIKIYA1,   // �A�C�e��1
	ITEMKIND_MAX	    // �A�C�e������
} ITEMKIND;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �O��̈ʒu
	D3DXVECTOR3 move;	// �ړ���
	float fPlayerWidth;		// ��
	float fPlayerHeight;	// ����
	int nCounterItem;	// �A�C�e���Ǘ��̃J�E���^�[
	int nDirection;			// �E������
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��
	ITEMKIND kind;		// �A�C�e���̎��
	bool bDis;			// �\�����邩���Ȃ���
	ITEMTYPE *nItem;    // �A�C�e���̎��
} Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
ITEMKIND *GetItemKind(void);

#endif