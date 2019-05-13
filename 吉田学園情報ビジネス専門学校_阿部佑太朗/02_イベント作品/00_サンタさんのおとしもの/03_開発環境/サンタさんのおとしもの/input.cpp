//=============================================================================
//
// ���͏��� [input.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX	     (256)	 // �L�[�̍ő吔
#define DI_JOY_I_INPUT   (1000)  // �X�e�B�b�N�̕������͎�t���s���͈�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;              // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;  // ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevJoypad = NULL;    // ���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];               // �L�[�{�[�h�̓��͏��(�v���X���)
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];        // �L�[�{�[�h�̓��͏��(�g���K�[���)
BYTE g_aKeyStateRelease[NUM_KEY_MAX];        // �L�[�{�[�h�̓��͏��(�����[�X���)
BYTE g_aJoyState[DIJS_BUTTON_MAX];           // �W���C�p�b�h�̓��͏��(�v���X���)
BYTE g_aJoyStateTrigger[DIJS_BUTTON_MAX];    // �W���C�p�b�h�̓��͏��(�g���K�[���)
BYTE g_aJoyStateRelease[DIJS_BUTTON_MAX];    // �W���C�p�b�h�̓��͏��(�����[�X���)
int  Pad;                                    // �ڑ�����Ă���W���C�p�b�h�̐�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//======================================
	// �L�[�{�[�h����������
	//======================================
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	//======================================
	// �W���C�p�b�h����������
	//======================================
	// ���̓f�o�C�X(�W���C�p�b�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_Joystick, &g_pDevJoypad, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevJoypad->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_BACKGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevJoypad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (g_pDevJoypad != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		g_pDevJoypad->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitInput(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�W���C�p�b�h)�̊J��
	if (g_pDevJoypad != NULL)
	{
		g_pDevJoypad->Unacquire();   // �W���C�p�b�h�ւ̃A�N�Z�X�������
		g_pDevJoypad->Release();
		g_pDevJoypad = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateInput(void)
{
	//======================================
	// �L�[�{�[�h�X�V����
	//======================================
	BYTE aKeyState[NUM_KEY_MAX]; // �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X(�L�[�{�[�h)����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];   // �L�[�{�[�h�̓��͏��(�g���K�[���)�ۑ�
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey]; // �L�[�{�[�h�̓��͏��(�����[�X���)�ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  // �L�[�{�[�h�̓��͏��(�v���X���)�ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

	//======================================
	// �W���C�p�b�h�X�V����
	//======================================
	if (g_pDevJoypad != NULL)
	{// �����ł���
		DIJOYSTATE dijs;   // �W���C�p�b�h�̓��͏��
		BYTE aJoyState[DIJS_BUTTON_MAX]; // �L�[�{�[�h�̓��͏��

		// ���̓f�o�C�X(�W���C�p�b�h)����f�[�^���擾
		g_pDevJoypad->Poll();
		if (SUCCEEDED(g_pDevJoypad->GetDeviceState(sizeof(DIJOYSTATE), &dijs)))
		{
			//-----------------------------
			// ���A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lY <= -100)
			{// ���A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_10] = 0x80;
			}
			if (dijs.lY >= 100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_11] = 0x80;
			}
			if (dijs.lX <= -100)
			{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_13] = 0x80;
			}
			if (dijs.lX >= 100)
			{// ���A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_12] = 0x80;
			}

			//-----------------------------	
			// �E�A�i���O�X�e�B�b�N
			//-----------------------------
			if (dijs.lRz <= -100)
			{// �E�A�i���O�X�e�B�b�N����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_14] = 0x80;
			}
			if (dijs.lRz >= 100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_15] = 0x80;
			}
			if (dijs.lZ <= -100)
			{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_17] = 0x80;
			}
			if (dijs.lZ >= 100)
			{// �E�A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
				dijs.rgbButtons[DIJS_BUTTON_16] = 0x80;
			}

			//-----------------------------
			// �\���L�[
			//-----------------------------
			if (dijs.rgdwPOV[0] / 100 == 0)
			{// �\���L�[�̏オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 45)
			{// �\���L�[�̉E�オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 90)
			{// �\���L�[�̉��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 135)
			{// �\���L�[�̉E���������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_20] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 180)
			{// �\���L�[�̉E�������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 225)
			{// �\���L�[�̍����������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_19] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 270)
			{// �\���L�[�̍��������ꂽ
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}
			if (dijs.rgdwPOV[0] / 100 == 315)
			{// �\���L�[�̍��オ�����ꂽ
				dijs.rgbButtons[DIJS_BUTTON_18] = 0x80;
				dijs.rgbButtons[DIJS_BUTTON_21] = 0x80;
			}

			for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
			{// �W���C�p�b�h�̃{�^���̐������J��Ԃ�
				g_aJoyStateTrigger[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & dijs.rgbButtons[nCntJoyButton];  // �W���C�p�b�h�̓��͏��(�g���K�[���)�ۑ�
				g_aJoyStateRelease[nCntJoyButton] = (g_aJoyState[nCntJoyButton] ^ dijs.rgbButtons[nCntJoyButton]) & g_aJoyState[nCntJoyButton];      // �W���C�p�b�h�̓��͏��(�����[�X���)�ۑ�
				g_aJoyState[nCntJoyButton] = dijs.rgbButtons[nCntJoyButton];   // �W���C�p�b�h�̓��͏��(�v���X���)�ۑ�
				aJoyState[nCntJoyButton] = false;
			}
		}
		else
		{
			g_pDevJoypad->Acquire(); // �W���C�p�b�h�ւ̃A�N�Z�X�����l��
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetJoyPadPress(int nButton)
{
	return (g_aJoyState[nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetJoyPadTrigger(int nButton)
{
	return (g_aJoyStateTrigger[nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetJoyPadRelease(int nButton)
{
	return (g_aJoyStateRelease[nButton] & 0x80) ? true : false;
}