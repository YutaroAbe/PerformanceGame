//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	RANKINGTYPE_SCORE = 0,	// �����L���O
	RANKINGTYPE_RANK,	// ����
	RANKINGTYPE_BG,			// �w�i
	RANKINGTYPE_ROGO,		// ���S
}RANKINGTYPE;

//
typedef enum
{
	OFF = 0,
	ON ,
	ALL
}FLASH;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SortRanking(int nScore);

#endif
