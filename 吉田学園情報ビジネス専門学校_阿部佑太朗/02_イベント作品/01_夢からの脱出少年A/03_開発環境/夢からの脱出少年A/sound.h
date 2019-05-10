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
	SOUND_LABEL_BGM000 = 0,	//タイトル
	SOUND_LABEL_BGM001,		//モードセレクト
	SOUND_LABEL_BGM002,		//ゲーム画面
	SOUND_LABEL_BGM003,		//チュートリアル画面
	SOUND_LABEL_BGM004,		//リザルト画面
	SOUND_LABEL_BGM005,		//リザルト画面
	SOUND_LABEL_BGM006,		//ランキング画面
	SOUND_LABEL_SE000,		//決定
	SOUND_LABEL_SE002,		//選択上
	SOUND_LABEL_SE004,		//サイコロ
	SOUND_LABEL_SE008,		//ジャンプ
	SOUND_LABEL_SE012,		//起動音
	SOUND_LABEL_SE014,		//キック
	SOUND_LABEL_SE015,		//ダメージ
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
