//=============================================================================
//
// UI [ui.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"
//=============================================================================
// �񋓌^��`
//=============================================================================
typedef enum
{
	UI_READY = 0,
	UI_TYPELIST,
	UI_GUIDE,
	UI_1P,
	UI_2P,
	UI_VS,
	UI_RESULT,
	UI_MAX
}UITYPE;
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
	UITYPE type;
	bool bUse;
}UI;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, UITYPE type);
void MakeVertexUI(LPDIRECT3DDEVICE9 pDevice);
bool GetReady(void);
void SetReady(bool bSet);
void WhichWinner(void);
int GetWinnerPlayer(void);
#endif
