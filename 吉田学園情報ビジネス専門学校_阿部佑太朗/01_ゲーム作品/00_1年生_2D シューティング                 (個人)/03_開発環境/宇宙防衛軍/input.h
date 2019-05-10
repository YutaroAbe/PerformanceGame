//=============================================================================
//
// 入力処理 [input.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "game.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hinstance, HWND hwnd); 
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);//ボタンの移動はプレス
bool GetKeyboardTrigger(int nKey);//ボタンの発射はトリガー

#endif