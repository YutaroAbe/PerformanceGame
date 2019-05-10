//=============================================================================
//
// �Z���N�g�̏��� [score.h]
// Author :YUTARO ABE
//
//=============================================================================
#ifndef _SERECT_H_
#define _SERECT_H_
#include "main.h"
#define MAX_SERECT (128)


//=============================================================================
//�\����
//=============================================================================
typedef enum
{
	NORMAL = 0,
	END,
	MAX
}STETAS;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR cor;
	float SerectCor;
	int nCounrtState;
	int nSerect;
	STETAS State;
}SERECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitSerect(void);
void UninitSerect(void);
void UpdateSerect(void);
void DrawSerect(void);
STETAS *GetSel(void);


#endif

