//=============================================================================
//
// 入力処理 [input.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX	     (256)	 // キーの最大数
#define DI_JOY_I_INPUT   (1000)  // スティックの方向入力受付を行う範囲

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;              // DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;  // 入力デバイス(キーボード)へのポインタ
LPDIRECTINPUTDEVICE8 g_pDevJoypad = NULL;    // 入力デバイス(ジョイパッド)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];               // キーボードの入力情報(プレス情報)
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];        // キーボードの入力情報(トリガー情報)
BYTE g_aKeyStateRelease[NUM_KEY_MAX];        // キーボードの入力情報(リリース情報)
BYTE g_aJoyState[DIJS_BUTTON_MAX];           // ジョイパッドの入力情報(プレス情報)
BYTE g_aJoyStateTrigger[DIJS_BUTTON_MAX];    // ジョイパッドの入力情報(トリガー情報)
BYTE g_aJoyStateRelease[DIJS_BUTTON_MAX];    // ジョイパッドの入力情報(リリース情報)
int  Pad;                                    // 接続されているジョイパッドの数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//======================================
	// キーボード初期化処理
	//======================================
	// 入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	//======================================
	// ジョイパッド初期化処理
	//======================================
	// 入力デバイス(ジョイパッド)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_Joystick, &g_pDevJoypad, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevJoypad->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (g_pDevJoypad != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイパッドへのアクセス権を獲得(入力制御開始)
		g_pDevJoypad->Acquire();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitInput(void)
{
	// 入力デバイス(キーボード)の開放
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); // キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力デバイス(ジョイパッド)の開放
	if (g_pDevJoypad != NULL)
	{
		g_pDevJoypad->Unacquire();   // ジョイパッドへのアクセス権を放棄
		g_pDevJoypad->Release();
		g_pDevJoypad = NULL;
	}

	// DirectInputオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateInput(void)
{
	//======================================
	// キーボード更新処理
	//======================================
	BYTE aKeyState[NUM_KEY_MAX]; // キーボードの入力情報
	int nCntKey;

	// 入力デバイス(キーボード)からデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];   // キーボードの入力情報(トリガー情報)保存
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey]; // キーボードの入力情報(リリース情報)保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  // キーボードの入力情報(プレス情報)保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); // キーボードへのアクセス権を獲得
	}

	//======================================
	// ジョイパッド更新処理
	//======================================
	if (g_pDevJoypad != NULL)
	{// 生成できた
		DIJOYSTATE dijs;   // ジョイパッドの入力情報
		BYTE aJoyState[DIJS_BUTTON_MAX]; // キーボードの入力情報

		// 入力デバイス(ジョイパッド)からデータを取得
		g_pDevJoypad->Poll();
		if (SUCCEEDED(g_pDevJoypad->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			//-----------------------------
			// 左アナログスティック
			//-----------------------------
			if (dijs.lY <= -100)
			{// 左アナログスティックが上に倒された
				dijs.rgbButtons[DIJS_BUTTON_10] = 0x80;
			}
			if (dijs.lY >= 100)
			{// 左アナログスティックが下に倒された
				dijs.rgbButtons[DIJS_BUTTON_11] = 0x80;
			}
			if (dijs.lX <= -100)
			{// 左アナログスティックが左に倒された
				dijs.rgbButtons[DIJS_BUTTON_13] = 0x80;
			}
			if (dijs.lX >= 100)
			{// 左アナログスティックが右に倒された
				dijs.rgbButtons[DIJS_BUTTON_12] = 0x80;
			}

			//-----------------------------	
			// 右アナログスティック
			//-----------------------------
			if (dijs.lRz <= -100)
			{// 右アナログスティックが上に倒された
				dijs.rgbButtons[DIJS_BUTTON_14] = 0x80;
			}
			if (dijs.lRz >= 100)
			{// 右アナログスティックが下に倒された
				dijs.rgbButtons[DIJS_BUTTON_15] = 0x80;
			}
			if (dijs.lZ <= -100)
			{// 右アナログスティックが左に倒された
				dijs.rgbButtons[DIJS_BUTTON_17] = 0x80;
			}
			if (dijs.lZ >= 100)
			{// 右アナログスティックが右に倒された
				dijs.rgbButtons[DIJS_BUTTON_16] = 0x80;
			}

			//-----------------------------
			// 十字キー
			//-----------------------------
			if (dijs.rgdwPOV[0] / 100 == 0)
			{// 十字キーの上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 45)
			{// 十字キーの右上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 90)
			{// 十字キーの下が押された
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 135)
			{// 十字キーの右下が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 180)
			{// 十字キーの右が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 225)
			{// 十字キーの左下が押された
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 270)
			{// 十字キーの左が押された
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 315)
			{// 十字キーの左上が押された
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}

			for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
			{// ジョイパッドのボタンの数だけ繰り返し
				g_aJoyStateTrigger[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & dijs.rgbButtons[nCntJoyButton];  // ジョイパッドの入力情報(トリガー情報)保存
				g_aJoyStateRelease[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & g_aJoyState[nCntJoyButton];      // ジョイパッドの入力情報(リリース情報)保存
				g_aJoyState[nCntJoyButton] = dijs.rgbButtons[nCntJoyButton];   // ジョイパッドの入力情報(プレス情報)保存
				aJoyState[nCntJoyButton] = false;
			}
		}
		else
		{
			g_pDevJoypad->Acquire(); // ジョイパッドへのアクセス権を獲得
		}
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// キーボードの入力情報(リリース情報)を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=============================================================================
// ジョイパッドの入力情報(プレス情報)を取得
//=============================================================================
bool GetJoyPadPress(int nButton)
{
	return (g_aJoyState[nButton] & 0x80) ? true : false;
}
//=============================================================================
// ジョイパッドの入力情報(トリガー情報)を取得
//=============================================================================
bool GetJoyPadTrigger(int nButton)
{
	return (g_aJoyStateTrigger[nButton] & 0x80) ? true : false;
}
//=============================================================================
// ジョイパッドの入力情報(リリース情報)を取得
//=============================================================================
bool GetJoyPadRelease(int nButton)
{
	return (g_aJoyStateRelease[nButton] & 0x80) ? true : false;
}