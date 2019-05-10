//=============================================================================
//
// 入力処理 [input.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "input.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 CInputGamePad::m_pDevGamePad = NULL;

//=============================================================================
// 入力のコンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevic = NULL;
}

//=============================================================================
// 入力のデストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 入力の初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{//m_pInputが空だったら
	 // DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 入力の終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevic != NULL)
	{
		m_pDevic->Unacquire();	// キーボードへのアクセス権を放棄
		m_pDevic->Release();
		m_pDevic = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// 入力の更新処理
//=============================================================================
void CInput::Update(void)
{
}

//=============================================================================
// キーボードのコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//キーボード情報のクリア
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = {};
		m_aKeyStateRelease[nCount] = {};
		m_aKeyStateTrigger[nCount] = {};
	}
}

//=============================================================================
// キーボードのデストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力の初期化
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevic, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevic->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevic->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevic->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	//入力の終了処理
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// キーボードの入力情報
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevic->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// キーボードの入力情報保存
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevic->Acquire();	// キーボードへのアクセス権を獲得
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool  CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool  CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(リリース情報)を取得
//=============================================================================
bool  CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

////=============================================================================
////入力のデバイス取得
////=============================================================================
//LPDIRECTINPUTDEVICE8 CInput::GetInput(void)
//{
//	return m_pDevic;
//}

//=============================================================================
// コンストラクタ
//=============================================================================
CInputGamePad::CInputGamePad()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputGamePad::~CInputGamePad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//変数宣言
	HRESULT hr;
	//int				nCntBottun;
	//DIJOYSTATE2		GamePadState;	//ジョイパッドのボタン

									//初期化処理を呼び出す
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(コントローラー)の生成
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// 第4引数 (ATTACHEDONLY = 現在接続されているジョイスティックのみ検出する)
	{
		return FALSE;
	}
	if (m_pDevGamePad != NULL)
	{


		// デバイスにデータフォーマットを設定
		if (FAILED(hr = m_pDevGamePad->SetDataFormat(&c_dfDIJoystick2)))
		{
			return FALSE;
		}

		// 協調モードを設定
		if (FAILED(hr = m_pDevGamePad->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return FALSE;
		}

		// ゲームパッドの機能の情報を収集
		m_GamepadCaps.dwSize = sizeof(DIDEVCAPS);

		if (FAILED(hr = m_pDevGamePad->GetCapabilities(&m_GamepadCaps)))
		{
			m_pDevGamePad->Release();
			return FALSE;
		}

		// 各軸のモード設定
		hr = m_pDevGamePad->EnumObjects(EnumAxesCallback, (void*)m_pDevGamePad, DIDFT_AXIS);

		m_JoyconAxesNumber++;		// 番号を進める

									// ゲームパッドへのアクセス権を獲得(入力制御開始)
		hr = m_pDevGamePad->Poll();

		if (FAILED(hr))
		{
			hr = m_pDevGamePad->Acquire();

			while (hr == DIERR_INPUTLOST)
			{
				hr = m_pDevGamePad->Acquire();
			}
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInputGamePad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CInputGamePad::Update(void)
{
	if (m_pDevGamePad != NULL)
	{
		DIJOYSTATE2 aGamePadKeyState;								// コントローラーの入力情報
		BYTE aLeftAnalogStick[ANALOG_STICK_MAX] = { 0,0,0,0 };		// スティックの入力情報
		BYTE aPov[POV_MAX] = { 0,0,0,0 };							// 十字キーの入力情報

		HRESULT hr;
		hr = m_pDevGamePad->Poll();

		// 入力デバイスからデータを取得
		if (SUCCEEDED(hr = m_pDevGamePad->GetDeviceState(sizeof(DIJOYSTATE2), &aGamePadKeyState)))
		{
			// ボタン
			for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
			{
				// コントローラーの入力情報の保存(トリガー)
				m_aGamePadKeyStateTrigger[nCntKey] = (m_aGamePadKeyState[nCntKey] ^ aGamePadKeyState.rgbButtons[nCntKey]) & aGamePadKeyState.rgbButtons[nCntKey];
				// コントローラーの入力情報の保存(リリース)
				m_aGamePadKeyStateRelease[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ m_aGamePadKeyState[nCntKey]) & m_aGamePadKeyState[nCntKey];
				// コントローラーの入力情報の保存(プレス)
				m_aGamePadKeyState[nCntKey] = aGamePadKeyState.rgbButtons[nCntKey];
			}

			//--------------------------------------------------------
			// 左アナログスティックの入力情報の取得
			//--------------------------------------------------------
			if (aGamePadKeyState.lY < -GAMEPAD_DEADZONE)
			{// 左スティックを上に倒した
				aLeftAnalogStick[ANALOG_STICK_UP] = 128;			// 入力された
			}
			else if (aGamePadKeyState.lY > GAMEPAD_DEADZONE)
			{// 左スティックを下に倒した
				aLeftAnalogStick[ANALOG_STICK_DOWN] = 128;			// 入力された
			}
			else if (aGamePadKeyState.lX > GAMEPAD_DEADZONE)
			{// 左gスティックを右に倒した
				aLeftAnalogStick[ANALOG_STICK_RIGHT] = 128;			// 入力された
			}
			else if (aGamePadKeyState.lX < -GAMEPAD_DEADZONE)
			{// 左スティックを左に倒した
				aLeftAnalogStick[ANALOG_STICK_LEFT] = 128;			// 入力された
			}

			for (int nCntAnalogStick = 0; nCntAnalogStick < ANALOG_STICK_MAX; nCntAnalogStick++)
			{// 左アナログスティックの方向の種類分ループ
			 // 左スティックのトリガー情報
				m_aLeftAnalogStickTrigger[nCntAnalogStick] = (m_aLeftAnalogStick[nCntAnalogStick] ^ aLeftAnalogStick[nCntAnalogStick])&aLeftAnalogStick[nCntAnalogStick];		// 左アナログスティックのトリガー情報
				// 左スティックのプレス情報
				m_aLeftAnalogStick[nCntAnalogStick] = aLeftAnalogStick[nCntAnalogStick];																						// 左アナログスティックのプレス情報
			}

			//--------------------------------------------------------
			// 十字キーの入力情報の取得
			//--------------------------------------------------------
			if (aGamePadKeyState.rgdwPOV[0] == 0.0f)
			{// 十字キーの上を押した
				aPov[POV_UP] = 128;			// 入力された
			}
			if (aGamePadKeyState.rgdwPOV[0] == 18000.0f)
			{// 十字キーの下を押した
				aPov[POV_DOWN] = 128;			// 入力された
			}
			if (aGamePadKeyState.rgdwPOV[0] == 9000.0f)
			{// 十字キーの右を押した
				aPov[POV_RIGHT] = 128;			// 入力された
			}
			if (aGamePadKeyState.rgdwPOV[0] == 27000.0f)
			{// 十字キーの左を押した
				aPov[POV_LEFT] = 128;			// 入力された
			}

			for (int nCntPov = 0; nCntPov < POV_MAX; nCntPov++)
			{// 十字キーの方向の種類分ループ

				m_aPovTrigger[nCntPov] = (m_aPov[nCntPov] ^ aPov[nCntPov])&aPov[nCntPov];	// 十字キーのトリガー情報
				m_aPov[nCntPov] = aPov[nCntPov];											// 十字キーのプレス情報
			}
			m_aGamePad = aGamePadKeyState;			// 現在の状態を保存
		}
		else
		{
			m_pDevGamePad->Acquire();				// ゲームパッドへのアクセス権を獲得
		}
	}
}

//=============================================================================
// コールバック関数
//=============================================================================
BOOL CALLBACK CInputGamePad::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// 列挙されたジョイスティックへのインターフェイスを取得
	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &m_pDevGamePad, NULL);

	// デバイスを検出出来なかった場合
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// コールバック関数
//=============================================================================
BOOL CALLBACK CInputGamePad::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	//変数宣言
	HRESULT hr;
	DIPROPRANGE diprg;

	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -(GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE);				// 十字キーの最小値 [上] [左]
	diprg.lMax = GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE;				// 十字キーの最大 [上] [左]
	hr = m_pDevGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// プレス処理
//=============================================================================
bool CInputGamePad::GetGamePadPress(int nKey)
{
	return (m_aGamePadKeyState[nKey] & 0x80) ? true : false;
}

//========================================================================================
// 入力情報(トリガー情報)を取得
//========================================================================================
bool CInputGamePad::GetGamePadTrigger(int nKey)
{
	return (m_aGamePadKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================================================
// の入力情報(リリース情報)を取得
//========================================================================================
bool CInputGamePad::GetGamePadRelease(int nKey)
{
	return (m_aGamePadKeyStateRelease[nKey] & 0x80) ? true : false;
}

//===========================================================================
// ゲームパッドのスティック入力情報(プレス情報)を取得
//============================================================================
bool CInputGamePad::GetGamePadStickPress(int nKey)
{
	return (m_aLeftAnalogStick[nKey] & 0x80) ? true : false;
}

//============================================================================
// ゲームパッドのスティック入力情報(トリガー情報)を取得
//=============================================================================
bool CInputGamePad::GetGamePadStickTrigger(int nKey)
{
	return (m_aLeftAnalogStickTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// 十字キー入力情報(トリガー情報)を取得
//=============================================================================
bool CInputGamePad::GetPovTpress(int nAngle)
{
	return (m_aPov[nAngle] & 0x80) ? true : false;
}

//=============================================================================
// 十字キー入力情報(トリガー情報)を取得
//=============================================================================
bool CInputGamePad::GetPovTtigger(int nAngle)
{
	return (m_aPovTrigger[nAngle] & 0x80) ? true : false;
}