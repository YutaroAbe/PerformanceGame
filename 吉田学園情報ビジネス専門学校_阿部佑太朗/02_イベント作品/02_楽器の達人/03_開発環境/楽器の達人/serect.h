//=============================================================================
//
// セレクトの処理 [score.h]
// Author :YUTARO ABE
//
//=============================================================================
#ifndef _SERECT_H_
#define _SERECT_H_
#include "main.h"
#define MAX_SERECT (128)


//=============================================================================
//構造体
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
// プロトタイプ宣言
//*****************************************************************************
void InitSerect(void);
void UninitSerect(void);
void UpdateSerect(void);
void DrawSerect(void);
STETAS *GetSel(void);


#endif

