//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// コントローラー入力処理 [gamepad.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "gamepad.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define	GAMEPAD_NUM_KEY_MAX			(128)	// キーの最大数
#define	GAMEPAD_NUM_POV_KEY_MAX		(4)		// 十字キーの最大数
#define MAX_GAMEPAD					(2)		// ゲームパッドの最大数

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECTINPUT8 g_pGamePad = NULL;						// DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevGamePad[MAX_GAMEPAD] = {};		// 入力デバイス(kコントローラー)へのポインタ
DIDEVCAPS g_GamepadCaps;								// ゲームパッドの機能情報

DIJOYSTATE2 g_aGamePadKeyState[MAX_GAMEPAD];			// キーボードの入力情報(プレス情報)
DIJOYSTATE2 g_aGamePadKeyStateTrigger[MAX_GAMEPAD];		// キーボードの入力情報(トリガー情報)
DIJOYSTATE2 g_aGamePadKeyStateRelease[MAX_GAMEPAD];		// キーボードの入力情報(リリース情報)

STICK_POV g_StickPovType[MAX_GAMEPAD];
STICK_POV g_StickPovTypeOld[MAX_GAMEPAD];
int g_nPovOld[MAX_GAMEPAD];								// 前回の十字キーの方向

int g_nGamePad;				// ゲームパッドのカウンター
int g_nGamePadAccess;		// ゲームパッドのカウンター（joystickの機能コールバック関数で使用
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// ゲームパッドのカウンターの初期化
	g_nGamePad = 0;
	g_nGamePadAccess = 0;

	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pGamePad, NULL)))
	{
		return FALSE;
	}

	// 入力デバイス(コントローラー)の生成
	if (FAILED(g_pGamePad->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// 第4引数 (ATTACHEDONLY = 現在接続されているジョイスティックのみ検出する)
	{
		return FALSE;
	}



	for (int nCnt = 0; nCnt < g_nGamePad; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{// コントローラーが繋がっていないとき処理しない
		// デバイスにデータフォーマットを設定
			if (FAILED(hr = g_pDevGamePad[nCnt]->SetDataFormat(&c_dfDIJoystick2)))
			{
				return FALSE;
			}

			// 協調モードを設定
			if (FAILED(hr = g_pDevGamePad[nCnt]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
			{
				return FALSE;
			}

			// ゲームパッドの機能の情報を収集
			g_GamepadCaps.dwSize = sizeof(DIDEVCAPS);

			if (FAILED(hr = g_pDevGamePad[nCnt]->GetCapabilities(&g_GamepadCaps)))
			{
				g_pDevGamePad[nCnt]->Release();
				return FALSE;
			}

			// 各軸のモード設定
			if (FAILED(hr = g_pDevGamePad[nCnt]->EnumObjects(EnumAxesCallback, (void*)g_pDevGamePad[nCnt], DIDFT_AXIS)))
			{
				return FALSE;
			}
			// スティックのXY軸の数だけ[EnumAxesCallback]が呼ばれるのでここでカウンターを進める
			g_nGamePadAccess++;

			// ゲームパッドへのアクセス権を獲得(入力制御開始)
			hr = g_pDevGamePad[nCnt]->Poll();

			if (FAILED(hr))
			{
				hr = g_pDevGamePad[nCnt]->Acquire();

				while (hr == DIERR_INPUTLOST)
				{
					hr = g_pDevGamePad[nCnt]->Acquire();
				}
			}
		}
	}

	return S_OK;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{// コントローラーが繋がっていないとき処理しない
		// 入力デバイス(キーボード)の開放
			if (g_pDevGamePad[nCnt] != NULL)
			{
				g_pDevGamePad[nCnt]->Unacquire();
				g_pDevGamePad[nCnt]->Release();
				g_pDevGamePad[nCnt] = NULL;
			}
		}
	}

	// DirectInputオブジェクトの開放
	if (g_pGamePad != NULL)
	{
		g_pGamePad->Release();
		g_pGamePad = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{
			DIJOYSTATE2 aGamePadKeyState;		// コントローラーの入力情報
			HRESULT hr;

			// 前回の十字キーの情報を記録
			g_nPovOld[nCnt] = g_aGamePadKeyState[nCnt].rgdwPOV[0];
			// 前回のスティックの角度の情報を記録
			g_StickPovTypeOld[nCnt] = g_StickPovType[nCnt];

			hr = g_pDevGamePad[nCnt]->Poll();

			// 入力デバイスからデータを取得
			if (SUCCEEDED(hr = g_pDevGamePad[nCnt]->GetDeviceState(sizeof(DIJOYSTATE2), &aGamePadKeyState)))
			{
				// ボタン
				for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
				{
					// コントローラーの入力情報の保存(トリガー)
					g_aGamePadKeyStateTrigger[nCnt].rgbButtons[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ g_aGamePadKeyState[nCnt].rgbButtons[nCntKey]) & aGamePadKeyState.rgbButtons[nCntKey];
					// コントローラーの入力情報の保存(リリース)
					g_aGamePadKeyStateRelease[nCnt].rgbButtons[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ g_aGamePadKeyState[nCnt].rgbButtons[nCntKey]) & g_aGamePadKeyState[nCnt].rgbButtons[nCntKey];
					// コントローラーの入力情報の保存(プレス)
					g_aGamePadKeyState[nCnt].rgbButtons[nCntKey] = aGamePadKeyState.rgbButtons[nCntKey];
				}

				// 十字ボタン
				// コントローラーの入力情報の保存(トリガー)
				g_aGamePadKeyStateTrigger[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];;
				// コントローラーの入力情報の保存(リリース)
				g_aGamePadKeyStateRelease[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];;
				// コントローラーの入力情報の保存(プレス)
				g_aGamePadKeyState[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];

				// スティックの入力情報
				g_aGamePadKeyState[nCnt] = aGamePadKeyState;

				// 十字方向のスティックの入力情報
				if (g_aGamePadKeyState[nCnt].lX < -GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lX > GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lY < -GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lY> GAMEPAD_DEADZONE)
				{
					float fGamePagStickAngle = atan2f(float(-g_aGamePadKeyState[nCnt].lX), float(g_aGamePadKeyState[nCnt].lY));

					if (fGamePagStickAngle > (D3DX_PI / 8) * 7 || fGamePagStickAngle < (-D3DX_PI / 8) * 7)
					{// 上
						g_StickPovType[nCnt] = STICK_UP;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 7 && fGamePagStickAngle > (D3DX_PI / 8) * 5)
					{ // 左上
						g_StickPovType[nCnt] = STICK_LEFT_UP;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 5 && fGamePagStickAngle >(D3DX_PI / 8) * 3)
					{ // 左
						g_StickPovType[nCnt] = STICK_LEFT;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 3 && fGamePagStickAngle >(D3DX_PI / 8) * 1)
					{ // 左下
						g_StickPovType[nCnt] = STICK_LEFT_DOWN;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 1 && fGamePagStickAngle >(-D3DX_PI / 8) * 1)
					{// 下
						g_StickPovType[nCnt] = STICK_DOWN;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 1 && fGamePagStickAngle >(-D3DX_PI / 8) * 3)
					{ // 右下
						g_StickPovType[nCnt] = STICK_RIGHT_DOWN;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 3 && fGamePagStickAngle >(-D3DX_PI / 8) * 5)
					{// 右
						g_StickPovType[nCnt] = STICK_RIGHT;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 5 && fGamePagStickAngle >(-D3DX_PI / 8) * 7)
					{// 右上
						g_StickPovType[nCnt] = STICK_RIGHT_UP;
					}
				}
				else
				{
					g_StickPovType[nCnt] = STICK_NEUTRAL;
				}

			}
			else
			{
				g_pDevGamePad[nCnt]->Acquire();		// ゲームパッドへのアクセス権を獲得
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの入力情報(スティック)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
DIJOYSTATE2 *GetgamePadStick(int nPadID)
{
	return(&g_aGamePadKeyState[nPadID]);
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スティックの十字方向の入力情報(プレス情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadStickPress(int nPadID, STICK_POV stick)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_StickPovType[nPadID] == stick) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スティックの十字方向の入力情報(トリガー情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadStickTrigger(int nPadID, STICK_POV stick)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_StickPovType[nPadID] != g_StickPovTypeOld[nPadID]
			&& g_StickPovType[nPadID] == stick) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スティックの十字方向の入力情報(リリース情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadStickRelease(int nPadID, STICK_POV stick)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_StickPovType[nPadID] != g_StickPovTypeOld[nPadID]
			&& g_StickPovTypeOld[nPadID] == stick) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの十字キー入力情報(プレス情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadPovPress(int nPadID, int nPov)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_aGamePadKeyState[nPadID].rgdwPOV[0] == nPov) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの十字キー入力情報(トリガー情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadPovTrigger(int nPadID, int nPov)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_aGamePadKeyStateTrigger[nPadID].rgdwPOV[0] != g_nPovOld[nPadID]
			&& g_aGamePadKeyStateTrigger[nPadID].rgdwPOV[0] == nPov) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの十字キー入力情報(リリース情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadPovRelease(int nPadID, int nPov)
{
	if (g_pDevGamePad[nPadID] != NULL)
	{
		return(g_aGamePadKeyStateRelease[nPadID].rgdwPOV[0] != g_nPovOld[nPadID]
			&& g_nPovOld[nPadID] == nPov) ? true : false;
	}
	else
	{
		return false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの入力情報(プレス情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadPress(int nPadID, int nKey)
{
	return(g_aGamePadKeyState[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの入力情報(トリガー情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadTrigger(int nPadID, int nKey)
{
	return(g_aGamePadKeyStateTrigger[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームパッドの入力情報(リリース情報)を取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadRelease(int nPadID, int nKey)
{
	return(g_aGamePadKeyStateRelease[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// joystick用コールバック関数
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを取得
	hr = g_pGamePad->CreateDevice(pdidinstance->guidInstance, &g_pDevGamePad[g_nGamePad], NULL);

	// デバイスを検出出来なかった場合
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	// カウンターを進める
	g_nGamePad++;

	return DIENUM_CONTINUE;
	//return DIENUM_STOP;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// joystickの機能コールバック関数
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize		= sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow		= DIPH_BYID;
	diprg.diph.dwObj		= pdidoi->dwType;
	diprg.lMin				= -(GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE);				// 十字キーの最小値 [上] [左]
	diprg.lMax				= GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE;					// 十字キーの最大値 [下] [右]

	// デバイスに設定
	hr = g_pDevGamePad[g_nGamePadAccess]->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}