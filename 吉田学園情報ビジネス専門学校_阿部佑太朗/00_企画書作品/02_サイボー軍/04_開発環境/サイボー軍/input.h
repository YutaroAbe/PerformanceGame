//=============================================================================
//
// ���͏��� [input.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
//�L�[�{�[�h

#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔


//�p�b�h

#define GAMEPAD_DEADZONE		(3)
#define MAX_ZONE				(1000)
#define	GAMEPAD_NUM_KEY_MAX		(128)		// �L�[�̍ő吔

#define BUTTON_X	   (CInputGamePad::ELECOM_X)		// X�{�^���̔ԍ�
#define BUTTON_Y	   (CInputGamePad::ELECOM_Y)		// Y�{�^���̔ԍ�
#define BUTTON_A	   (CInputGamePad::ELECOM_A)		// A�{�^���̔ԍ�
#define BUTTON_B	   (CInputGamePad::ELECOM_B)		// B�{�^���̔ԍ�
#define BUTTON_L1	   (CInputGamePad::ELECOM_L1)		// L1�{�^���̔ԍ�
#define BUTTON_R1	   (CInputGamePad::ELECOM_R1)		// R1�{�^���̔ԍ�
#define BUTTON_L2	   (CInputGamePad::ELECOM_L2)		// L2�{�^���̔ԍ�
#define BUTTON_R2	   (CInputGamePad::ELECOM_R2)		// R2�{�^���̔ԍ�
#define BUTTON_L_STICK (CInputGamePad::ELECOM_L_STICK)	// L_STICK�{�^���̔ԍ�
#define BUTTON_R_STICK (CInputGamePad::ELECOM_R_STICK)	// R_STICK�{�^���̔ԍ�
#define BUTTON_BACK	   (CInputGamePad::ELECOM_BACK)		// BACK�{�^���̔ԍ�
#define BUTTON_START   (CInputGamePad::ELECOM_START)	// START�{�^���̔ԍ�
#define BUTTON_GUIDE   (CInputGamePad::ELECOM_GUIDE)	// GUIDE�{�^���̔ԍ�
#define BUTTON_MAX	   (CInputGamePad::ELECOM_MAX)		// �{�^���̍ő�

#define CROSSKEY_UP (CInputGamePad::POV_UP)
#define CROSSKEY_DOWN (CInputGamePad::POV_DOWN)
#define CROSSKEY_LEFT (CInputGamePad::POV_LEFT)
#define CROSSKEY_RIGHT (CInputGamePad::POV_RIGHT)

//=============================================================================
//	���͂̃N���X
//=============================================================================
class CInput
{
public:
	CInput();														//	�R���X�g���N�^
	~CInput();														//	�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	���͂̏���������
	virtual void Uninit(void);										//	���͂̏I������
	virtual void Update(void)= 0;									//	���͂̍X�V����
	//LPDIRECTINPUTDEVICE8 GetInput(void);

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevic;
};

//=============================================================================
// �L�[�{�[�h�̃N���X
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();												//	�R���X�g���N�^
	~CInputKeyboard();												//	�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	�L�[�{�[�h�̏���������
	void Uninit(void);										//	�L�[�{�[�h�̏I������
	void Update(void);										//	�L�[�{�[�h�̍X�V����
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];									// �L�[�{�[�h�ւ̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];							// �L�[�{�[�h�ւ̓��͏��(�g���K�[���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];							// �L�[�{�[�h�ւ̓��͏��(�����[�X���)
};


//=============================================================================
// �Q�[���p�b�h�̓��̓N���X
//=============================================================================
class CInputGamePad : public CInput
{
public:
	typedef enum
	{// �A�i���O�X�e�B�b�N�̕����̎��(4����)
		ANALOG_STICK_UP = 0,
		ANALOG_STICK_RIGHT,
		ANALOG_STICK_LEFT,
		ANALOG_STICK_DOWN,
		ANALOG_STICK_MAX
	}ANALOG_STICK;

	typedef enum
	{// �\���L�[�̕����̎��
		POV_UP = 0,
		POV_DOWN,
		POV_RIGHT,
		POV_LEFT,
		POV_MAX
	}POV;

	typedef enum
	{//�{�^���̎��
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
	//�֐�
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);	//�R�[���o�b�N�֐�
	static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);				//�R�[���o�b�N�֐�

																										//�ϐ�
	static LPDIRECTINPUTDEVICE8 m_pDevGamePad;															// ���̓f�o�C�X(k�R���g���[���[)�ւ̃|�C���^
	DIDEVCAPS m_GamepadCaps;																			// �Q�[���p�b�h�̋@�\���

	DIJOYSTATE2 m_aGamePad;																				// �R���g���[���[�̏��

	BYTE		m_aGamePadKeyState[GAMEPAD_NUM_KEY_MAX];												// �W���C�X�e�B�b�N�̃v���X���͏��
	BYTE		m_aGamePadKeyStateTrigger[GAMEPAD_NUM_KEY_MAX];											// �W���C�X�e�B�b�N�̃g���K�[���͏��
	BYTE		m_aGamePadKeyStateRelease[GAMEPAD_NUM_KEY_MAX];											// �W���C�X�e�B�b�N�̃����[�X���͏��
	BYTE		m_aLeftAnalogStick[ANALOG_STICK_MAX];													// ���A�i���O�X�e�B�b�N�̃v���X���
	BYTE		m_aLeftAnalogStickTrigger[ANALOG_STICK_MAX];												// ���A�i���O�X�e�B�b�N�̃g���K�[���
	BYTE		m_aPov[POV_MAX];																	// �\���L�[�̃v���X���
	BYTE		m_aPovTrigger[POV_MAX];
	// �\���L�[�̃g���K�[���
	LPDIRECTINPUT8  m_pGamePad = NULL;		// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	int		   	    m_JoyconAxesNumber;		// joystick�̋@�\�R�[���o�b�N�֐��Ŏg���W���C�R���̔ԍ�
};

#endif