//=============================================================================
//
// プレイヤー表示処理 [playershow.h]
// Author : EbinaRiku
//
//=============================================================================
#ifndef _PLAYERSHOW_H_
#define _PLAYERSHOW_H_

#include "main.h"
#include "player.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayerShow(void);
void UninitPlayerShow(void);
void UpdatePlayerShow(void);
void DrawPlayerShow(void);
void PlayBackVoice(PLAYER_TYPE type);
#endif
