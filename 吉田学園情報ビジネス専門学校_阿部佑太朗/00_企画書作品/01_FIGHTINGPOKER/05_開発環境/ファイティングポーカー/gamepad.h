//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
// コントローラー入力処理 [gamepad.h]
// Author : Toshiharu Ueno
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**

#define POV_UP				(0)		// 上
#define POV_RIGHT_UP		(4500)	// 右上
#define POV_RIGHT			(9000)	// 右
#define POV_RIGHT_DOWN		(13500)
#define POV_DOWN			(18000)
#define POV_LEFT_UP			(31500)
#define POV_LEFT			(27000)
#define POV_LEFT_DOWN		(22500)

#define GAMEPAD_DEADZONE	(3)
#define MAX_ZONE			(100)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	STICK_NEUTRAL = 0,
	STICK_UP,
	STICK_RIGHT_UP,
	STICK_RIGHT,
	STICK_RIGHT_DOWN,
	STICK_DOWN,
	STICK_LEFT_UP,
	STICK_LEFT,
	STICK_LEFT_DOWN,
	STICK_MAX
}STICK_POV;

typedef enum
{
	ELECOM_X = 0,
	ELECOM_Y,
	ELECOM_A,
	ELECOM_B,
	ELECOM_LB,
	ELECOM_RB,
	ELECOM_LT,
	ELECOM_RT,
	ELECOM_LS,
	ELECOM_RS,
	ELECOM_BACK,
	ELECOM_START,
	ELECOM_MAX
}ELECOM_CTRL;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd);
void UninitGamePad(void);
void UpdateGamePad(void);

bool GetGamePadPress(int nPadID, int nKey);
bool GetGamePadTrigger(int nPadID, int nKey);
bool GetGamePadRelease(int nPadID, int nKey);

bool GetGamePadPovPress(int nPadID, int nKey);
bool GetGamePadPovTrigger(int nPadID, int nKey);
bool GetGamePadPovRelease(int nPadID, int nKey);

bool GetGamePadStickPress(int nPadID, STICK_POV stick);
bool GetGamePadStickTrigger(int nPadID, STICK_POV stick);
bool GetGamePadStickRelease(int nPadID, STICK_POV stick);

DIJOYSTATE2 *GetgamePadStick(int nPadID);
#endif
