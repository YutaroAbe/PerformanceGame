//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// SP�Q�[�W���� [spGage.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _SPGAGE_H_
#define _SPGAGE_H_

#include "main.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	SPGAGE_TYPE_1P_FRAME = 0,	// 1P�g
	SPGAGE_TYPE_1P_SPBLACK,		// 1PSP��
	SPGAGE_TYPE_1P_SPRED,		// 1PSP��
	SPGAGE_TYPE_1P_SP,			// 1PSP
	SPGAGE_TYPE_2P_FRAME,		// 2P�g
	SPGAGE_TYPE_2P_SPBLACK,		// 2PSP��
	SPGAGE_TYPE_2P_SPRED,		// 2PSP��
	SPGAGE_TYPE_2P_SP,			// 2PSP
	SPGAGE_TYPE_MAX				// ����
}SPGAGE_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitSpGage(void);
void UninitSpGage(void);
void UpdateSpGage(void);
void DrawSpGage(void);
void SetSpGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SPGAGE_TYPE type);
void SetSpAsset(D3DXVECTOR3 pos, PLAYER_CONTROL playerID);
void SetSpGageDestSkillPoint(int nSkillPoint, PLAYER_CONTROL playerID);
void SetSpGageSkillPoint(int nSkillPoint, PLAYER_CONTROL playerID);
#endif
