//=============================================================================
//
// 入力処理 [input.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
//キーボード

#define	NUM_KEY_MAX			(256)	// キーの最大数


//パッド

#define GAMEPAD_DEADZONE		(3)
#define MAX_ZONE				(1000)
#define	GAMEPAD_NUM_KEY_MAX		(128)		// キーの最大数

#define BUTTON_X	   (CInputGamePad::ELECOM_X)		// Xボタンの番号
#define BUTTON_Y	   (CInputGamePad::ELECOM_Y)		// Yボタンの番号
#define BUTTON_A	   (CInputGamePad::ELECOM_A)		// Aボタンの番号
#define BUTTON_B	   (CInputGamePad::ELECOM_B)		// Bボタンの番号
#define BUTTON_L1	   (CInputGamePad::ELECOM_L1)		// L1ボタンの番号
#define BUTTON_R1	   (CInputGamePad::ELECOM_R1)		// R1ボタンの番号
#define BUTTON_L2	   (CInputGamePad::ELECOM_L2)		// L2ボタンの番号
#define BUTTON_R2	   (CInputGamePad::ELECOM_R2)		// R2ボタンの番号
#define BUTTON_L_STICK (CInputGamePad::ELECOM_L_STICK)	// L_STICKボタンの番号
#define BUTTON_R_STICK (CInputGamePad::ELECOM_R_STICK)	// R_STICKボタンの番号
#define BUTTON_BACK	   (CInputGamePad::ELECOM_BACK)		// BACKボタンの番号
#define BUTTON_START   (CInputGamePad::ELECOM_START)	// STARTボタンの番号
#define BUTTON_GUIDE   (CInputGamePad::ELECOM_GUIDE)	// GUIDEボタンの番号
#define BUTTON_MAX	   (CInputGamePad::ELECOM_MAX)		// ボタンの最大

#define CROSSKEY_UP (CInputGamePad::POV_UP)
#define CROSSKEY_DOWN (CInputGamePad::POV_DOWN)
#define CROSSKEY_LEFT (CInputGamePad::POV_LEFT)
#define CROSSKEY_RIGHT (CInputGamePad::POV_RIGHT)

//=============================================================================
//	入力のクラス
//=============================================================================
class CInput
{
public:
	CInput();														//	コンストラクタ
	~CInput();														//	デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	入力の初期化処理
	virtual void Uninit(void);										//	入力の終了処理
	virtual void Update(void)= 0;									//	入力の更新処理
	//LPDIRECTINPUTDEVICE8 GetInput(void);

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevic;
};

//=============================================================================
// キーボードのクラス
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();												//	コンストラクタ
	~CInputKeyboard();												//	デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	キーボードの初期化処理
	void Uninit(void);										//	キーボードの終了処理
	void Update(void);										//	キーボードの更新処理
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];									// キーボードへの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];							// キーボードへの入力情報(トリガー情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];							// キーボードへの入力情報(リリース情報)
};


//=============================================================================
// ゲームパッドの入力クラス
//=============================================================================
class CInputGamePad : public CInput
{
public:
	typedef enum
	{// アナログスティックの方向の種類(4方向)
		ANALOG_STICK_UP = 0,
		ANALOG_STICK_RIGHT,
		ANALOG_STICK_LEFT,
		ANALOG_STICK_DOWN,
		ANALOG_STICK_MAX
	}ANALOG_STICK;

	typedef enum
	{// 十字キーの方向の種類
		POV_UP = 0,
		POV_DOWN,
		POV_RIGHT,
		POV_LEFT,
		POV_MAX
	}POV;

	typedef enum
	{//ボタンの種類
		ELECOM_X = 0,
		ELECOM_Y,
		ELECOM_A,
		ELECOM_B,
		ELECOM_L1,
		ELECOM_R1,
		ELECOM_L2,
		ELECOM_R2,
		ELECOM_L_STICK,
		ELECOM_R_STICK,
		ELECOM_BACK,
		ELECOM_START,
		ELECOM_GUIDE,
		ELECOM_MAX
	}ELECOM_CTRL;

	CInputGamePad();
	~CInputGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetGamePadPress(int nKey);
	bool GetGamePadTrigger(int nKey);
	bool GetGamePadRelease(int nKey);
	bool GetGamePadStickPress(int nKey);
	bool GetGamePadStickTrigger(int nKey);
	bool GetPovTpress(int nAngle);
	bool GetPovTtigger(int nAngle);
	//LPDIRECTINPUTDEVICE8 *GetgamePadStick(void);

private:
	//関数
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);	//コールバック関数
	static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);				//コールバック関数

																										//変数
	static LPDIRECTINPUTDEVICE8 m_pDevGamePad;															// 入力デバイス(kコントローラー)へのポインタ
	DIDEVCAPS m_GamepadCaps;																			// ゲームパッドの機能情報

	DIJOYSTATE2 m_aGamePad;																				// コントローラーの情報

	BYTE		m_aGamePadKeyState[GAMEPAD_NUM_KEY_MAX];												// ジョイスティックのプレス入力情報
	BYTE		m_aGamePadKeyStateTrigger[GAMEPAD_NUM_KEY_MAX];											// ジョイスティックのトリガー入力情報
	BYTE		m_aGamePadKeyStateRelease[GAMEPAD_NUM_KEY_MAX];											// ジョイスティックのリリース入力情報
	BYTE		m_aLeftAnalogStick[ANALOG_STICK_MAX];													// 左アナログスティックのプレス情報
	BYTE		m_aLeftAnalogStickTrigger[ANALOG_STICK_MAX];												// 左アナログスティックのトリガー情報
	BYTE		m_aPov[POV_MAX];																	// 十字キーのプレス情報
	BYTE		m_aPovTrigger[POV_MAX];
	// 十字キーのトリガー情報
	LPDIRECTINPUT8  m_pGamePad = NULL;		// DirectInputオブジェクトへのポインタ
	int		   	    m_JoyconAxesNumber;		// joystickの機能コールバック関数で使うジョイコンの番号
};

#endif