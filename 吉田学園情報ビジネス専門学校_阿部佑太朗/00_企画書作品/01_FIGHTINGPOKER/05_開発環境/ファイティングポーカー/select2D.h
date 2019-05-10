//=============================================================================
//
// �Z���N�g��ʏ��� [select2D.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _SELECT2D_H_
#define _SELECT2D_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************
typedef enum
{
	SELECT_CURSOR = 0,
	SELECT_BATTLE,
	SELECT_RULE,
	SELECT_CREDIT,
	SELECT_RETURN,
	SELECT_OPERATION,
	SELECT_GUIDE,
	SELECT_MAX
}SELECTTYPE;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�J���|
	float fWidth;
	float fHeight;
	bool bUse;
	bool bSelect;
	SELECTTYPE type;
}SELECT2D;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitSelect2D(void);
void UninitSelect2D(void);
void UpdateSelect2D(void);
void DrawSelect2D(void);
void MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);
void SetSelect2D(D3DXVECTOR3 pos, float fWidth, float fHeight, SELECTTYPE type);
SELECTTYPE  GetSelectType(void);
#endif