//=============================================================================
//
// �A�C�e���̏��� [item.h]
// Author :�@���R���
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM			(128)	// �A�C�e���̍ő吔

//*****************************************************************************
// �A�C�e���̎��
//*****************************************************************************
typedef enum
{
	ITEMTYPE_COIN = 0,	// �R�C��
	ITEMTYPE_MIKIYA,	// �R�C��
	ITEMTYPE_MAX
} ITEMTYPE;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	//D3DXCOLOR col;				// �F
	ITEMTYPE itemtype;				// �A�C�e���̎��
	float fItemWidth;
	float fItemHeight;
	int nCounterAnim;				// �A�j���[�V�����J�E���^�[
	int nPatternAnim;				// �A�j���[�V�����p�^�[��
	bool bUse;						// �g�p���Ă��邩�ǂ���
} Item;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEMTYPE itemtype);
Item *GetItem(void);
bool CollisionItem(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **nItem);

#endif