//=========================================================================================================================
//
// ���j���[���� [rulebook.h]
// Author :
//
//=========================================================================================================================
#ifndef _RULEBOOK_H_
#define _RULEBOOK_H_

#include "main.h"

//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef enum
{
	BOOKTYPE_BG = 0,
	BOOKTYPE_FLOW,
	BOOKTYPE_KEYBORD,
	BOOKTYPE_CONTROLLER,
	BOOKTYPE_ROLE,
	BOOKTYPE_CHARA,				// �p���`->�p���`
	BOOKTYPE_BACK,		// �p���`->�p���`->�p���`
	PAUSETYPE_MAX
}RULEBOOKTYPE;
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 Initpos;// �����ʒu
	D3DXCOLOR col;		// �F
	D3DXVECTOR3 move;	// �ړ�
	int nType;			// ���
	int nCounterAnim;	// �J�E���^�[
	int nPatternAnim;	// �p�^�[��
	float fWidth;		// ��
	float fHeight;		// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
} RULEBOOK;
//******************************************************************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************************************************************
void InitRulebook(void);
void UninitRulebook(void);
void UpdateRulebook(void);
void DrawRulebook(void);
void SetRulebook(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
#endif // !_PAUSE_H_

