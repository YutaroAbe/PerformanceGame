//=============================================================================
//
// ���͏��� [input.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "game.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hinstance, HWND hwnd); 
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);//�{�^���̈ړ��̓v���X
bool GetKeyboardTrigger(int nKey);//�{�^���̔��˂̓g���K�[

#endif