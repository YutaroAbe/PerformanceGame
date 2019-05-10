//=========================================================================================================================
//
// �|�[�Y���[������ [rulebook.h]
// Author :
//
//=========================================================================================================================
#ifndef _RULEPAUSE_H_
#define _RULEPAUSE_H_

#include "main.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_RULEPAUSE	(128)	// ���j���[�ő吔

//*************************************************************************************************************************
// �\����
//*************************************************************************************************************************
typedef enum
{
	RULESTATE_NORMAL = 0,	// �ʏ���
	RULESTATE_SELECT,		// �I�����
	RULESTATE_MAX
}RULEPAUSESTATE;

//���j���[���
typedef enum
{
	RULEPAUSETYPE_BG = 0,
	RULEPAUSETYPE_FLOW,
	RULEPAUSETYPE_KEYBORD,
	RULEPAUSETYPE_CONTROLLER,
	RULEPAUSETYPE_ROLE,
	RULEPAUSETYPE_CHARA,				// �p���`->�p���`
	RULEPAUSETYPE_BACK,		// �p���`->�p���`->�p���`
	RULEPAUSETYPE_MAX
}RULEPAUSETYPE;

typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXCOLOR col;		// �J���[
	float SelectColor;	// �I���J���[
	int nCntState;		// ��Ԃ̃J�E���^
	int	SelectNum;		// �I��ԍ�
	bool bUse;			// �g�p���Ă��邩
	bool bMenu;			// ���j���[�g�p���Ă���
	float fWidth;		// ����
	float fHeight;		// �c��
	bool  bRule;
	int nType;			// ���
	RULEPAUSESTATE state;
} RULEPAUSEMENU;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitRulePause(void);						//���[���u�b�N����������
void UninitRulePause(void);						//���[���u�b�N�I������
void UpdateRulePause(void);						//���[���u�b�N�X�V����
void DrawRulePause(void);						//���[���u�b�N�`�揈��
void SetRulePause(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight);
bool GetbMenu(void);
#endif
