//=============================================================================
//
//  [rule.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _RULE_H_
#define _RULE_H_

#include "main.h"
//=============================================================================
// �񋓌^��`
//=============================================================================
typedef enum
{
	RULE_FLOW = 0,
	RULE_KEYBORD,		  // �L�[�{�[�h����
	RULE_CONTROLLER,  // �R���g���[����
	RULE_ROLE,			  // ���@
	RULE_CHARA,			  // �L����
	RULE_PRESSBUTTON,	  // �v���X�G���^�[
	RULE_MAX
}RULETYPE;
//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fWidth;
	float fHeight;
	RULETYPE type;
	bool bUse;
}RULE;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitRule(void);
void UninitRule(void);
void UpdateRule(void);
void DrawRule(void);
void SetRule(D3DXVECTOR3 pos, float fWidth, float fHeight, RULETYPE type);
void MakeVertexRule(LPDIRECT3DDEVICE9 pDevice);
RULE *GetRule(void);
#endif
