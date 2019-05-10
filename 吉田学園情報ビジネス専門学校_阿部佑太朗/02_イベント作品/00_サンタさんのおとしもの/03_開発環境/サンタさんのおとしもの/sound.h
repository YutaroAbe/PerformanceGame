//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Niwa Hodaka
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
	SOUND_LABEL_BGM001_GAME,
	SOUND_LABEL_BGM002_TITLE,
	SOUND_LABEL_BGM003_MODESELECT,
	SOUND_LABEL_BGM004_RANKING,
	SOUND_LABEL_BGM005_TUTORIAL,
	SOUND_LABEL_BGM006_RESULT,
	SOUND_LABEL_SE_DICIDE,
	SOUND_LABEL_SE_PAUSEOPEN,
	SOUND_LABEL_SE_PAUSESELECT,
	SOUND_LABEL_SE_PAUSEDECIDE,
	SOUND_LABEL_SE_WARNING,
	SOUND_LABEL_SE_FALL,
	SOUND_LABEL_SE_GET,
	SOUND_LABEL_SE_HIT,
	SOUND_LABEL_SE_KARASU,
	SOUND_LABEL_SE_WANT,
	SOUND_LABEL_MAX
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
