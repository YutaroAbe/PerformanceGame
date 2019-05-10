//=============================================================================
//
// サウンド処理 [sound.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	//SOUND_LABEL_BGM001,			// BGM1
//	SOUND_LABEL_BGM002,			// BGM2
	//SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	//SOUND_LABEL_BGM005,			// BGM5
	//SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM6
	SOUND_LABEL_BGM008,			// BGM6
	SOUND_LABEL_BGM009,			// BGM9
	SOUND_LABEL_BGM010,			// BGM10
	SOUND_LABEL_BGM011,			// BGM11
	SOUND_LABEL_BGM012,			// BGM12
	SOUND_LABEL_BGM013,			// BGM13
	SOUND_LABEL_BGM014,			// BGM14
	SOUND_LABEL_BGM015,			// BGM15
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT000,		// ヒット音0
	SOUND_LABEL_SE_HIT001,		// ヒット音1
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_COIN000,		// コイン
	SOUND_LABEL_SE_COIN001,		// コイン
	SOUND_LABEL_SE_COIN002,		// コイン
	SOUND_LABEL_SE_COIN003,		// コイン
	SOUND_LABEL_SE_BLOCK000,	// ブロック
	SOUND_LABEL_SE_SWITCH,		// SWITCH
	//SOUND_LABEL_SE_UMA,		// 馬足音
	SOUND_LABEL_SE_BAKEHATU,	// 馬足音
	SOUND_LABEL_SE_TRAP0,	
	SOUND_LABEL_SE_ENEMY0,	
	SOUND_LABEL_SE_ENEMY1,
	SOUND_LABEL_SE_BANE,
	SOUND_LABEL_SE_HATENA,
	SOUND_LABEL_SE_KAIHUKU,
	SOUND_LABEL_SE_DOA,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

