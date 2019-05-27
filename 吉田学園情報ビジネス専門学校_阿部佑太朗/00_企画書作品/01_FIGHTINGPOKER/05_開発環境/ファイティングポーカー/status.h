//=============================================================================
//
// �X�e�[�^�X [status.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _STATUS_H_
#define _STATUS_H_

#include "main.h"

//=============================================================================
// �񋓌^��`
//=============================================================================
typedef enum
{
	STATUSINFO_ATTACK = 0,
	STATUSINFO_DEFENSE,
	STATUSINFO_FRAME,
	STATUSINFO_MAX,
}STATUSINFO;
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
	bool bUse;
	STATUSINFO type;
}STATUS;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitStatus(void);
void UninitStatus(void);
void UpdateStatus(void);
void DrawStatus(void);
void SetStatus(D3DXVECTOR3 pos, float fWidth, float fHeight, STATUSINFO type);
void MakeVertexStatus(LPDIRECT3DDEVICE9 pDevice);
void SetStatusUp(void);
#endif
