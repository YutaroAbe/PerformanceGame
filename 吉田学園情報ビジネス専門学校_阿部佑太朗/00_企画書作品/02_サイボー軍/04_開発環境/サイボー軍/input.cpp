//=============================================================================
//
// ���͏��� [input.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "input.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 CInputGamePad::m_pDevGamePad = NULL;

//=============================================================================
// ���͂̃R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevic = NULL;
}

//=============================================================================
// ���͂̃f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ���͂̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{//m_pInput���󂾂�����
	 // DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// ���͂̏I������
//=============================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevic != NULL)
	{
		m_pDevic->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevic->Release();
		m_pDevic = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// ���͂̍X�V����
//=============================================================================
void CInput::Update(void)
{
}

//=============================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//�L�[�{�[�h���̃N���A
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = {};
		m_aKeyStateRelease[nCount] = {};
		m_aKeyStateTrigger[nCount] = {};
	}
}

//=============================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���͂̏�����
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevic, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevic->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevic->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevic->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	//���͂̏I������
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevic->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̓��͏��ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevic->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool  CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool  CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool  CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

////=============================================================================
////���͂̃f�o�C�X�擾
////=============================================================================
//LPDIRECTINPUTDEVICE8 CInput::GetInput(void)
//{
//	return m_pDevic;
//}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputGamePad::CInputGamePad()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputGamePad::~CInputGamePad()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInputGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�ϐ��錾
	HRESULT hr;
	//int				nCntBottun;
	//DIJOYSTATE2		GamePadState;	//�W���C�p�b�h�̃{�^��

									//�������������Ăяo��
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�R���g���[���[)�̐���
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// ��4���� (ATTACHEDONLY = ���ݐڑ�����Ă���W���C�X�e�B�b�N�̂݌��o����)
	{
		return FALSE;
	}
	if (m_pDevGamePad != NULL)
	{


		// �f�o�C�X�Ƀf�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(hr = m_pDevGamePad->SetDataFormat(&c_dfDIJoystick2)))
		{
			return FALSE;
		}

		// �������[�h��ݒ�
		if (FAILED(hr = m_pDevGamePad->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return FALSE;
		}

		// �Q�[���p�b�h�̋@�\�̏������W
		m_GamepadCaps.dwSize = sizeof(DIDEVCAPS);

		if (FAILED(hr = m_pDevGamePad->GetCapabilities(&m_GamepadCaps)))
		{
			m_pDevGamePad->Release();
			return FALSE;
		}

		// �e���̃��[�h�ݒ�
		hr = m_pDevGamePad->EnumObjects(EnumAxesCallback, (void*)m_pDevGamePad, DIDFT_AXIS);

		m_JoyconAxesNumber++;		// �ԍ���i�߂�

									// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
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
// �I������
//=============================================================================
void CInputGamePad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputGamePad::Update(void)
{
	if (m_pDevGamePad != NULL)
	{
		DIJOYSTATE2 aGamePadKeyState;								// �R���g���[���[�̓��͏��
		BYTE aLeftAnalogStick[ANALOG_STICK_MAX] = { 0,0,0,0 };		// �X�e�B�b�N�̓��͏��
		BYTE aPov[POV_MAX] = { 0,0,0,0 };							// �\���L�[�̓��͏��

		HRESULT hr;
		hr = m_pDevGamePad->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(hr = m_pDevGamePad->GetDeviceState(sizeof(DIJOYSTATE2), &aGamePadKeyState)))
		{
			// �{�^��
			for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
			{
				// �R���g���[���[�̓��͏��̕ۑ�(�g���K�[)
				m_aGamePadKeyStateTrigger[nCntKey] = (m_aGamePadKeyState[nCntKey] ^ aGamePadKeyState.rgbButtons[nCntKey]) & aGamePadKeyState.rgbButtons[nCntKey];
				// �R���g���[���[�̓��͏��̕ۑ�(�����[�X)
				m_aGamePadKeyStateRelease[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ m_aGamePadKeyState[nCntKey]) & m_aGamePadKeyState[nCntKey];
				// �R���g���[���[�̓��͏��̕ۑ�(�v���X)
				m_aGamePadKeyState[nCntKey] = aGamePadKeyState.rgbButtons[nCntKey];
			}

			//--------------------------------------------------------
			// ���A�i���O�X�e�B�b�N�̓��͏��̎擾
			//--------------------------------------------------------
			if (aGamePadKeyState.lY < -GAMEPAD_DEADZONE)
			{// ���X�e�B�b�N����ɓ|����
				aLeftAnalogStick[ANALOG_STICK_UP] = 128;			// ���͂��ꂽ
			}
			else if (aGamePadKeyState.lY > GAMEPAD_DEADZONE)
			{// ���X�e�B�b�N�����ɓ|����
				aLeftAnalogStick[ANALOG_STICK_DOWN] = 128;			// ���͂��ꂽ
			}
			else if (aGamePadKeyState.lX > GAMEPAD_DEADZONE)
			{// ��g�X�e�B�b�N���E�ɓ|����
				aLeftAnalogStick[ANALOG_STICK_RIGHT] = 128;			// ���͂��ꂽ
			}
			else if (aGamePadKeyState.lX < -GAMEPAD_DEADZONE)
			{// ���X�e�B�b�N�����ɓ|����
				aLeftAnalogStick[ANALOG_STICK_LEFT] = 128;			// ���͂��ꂽ
			}

			for (int nCntAnalogStick = 0; nCntAnalogStick < ANALOG_STICK_MAX; nCntAnalogStick++)
			{// ���A�i���O�X�e�B�b�N�̕����̎�ޕ����[�v
			 // ���X�e�B�b�N�̃g���K�[���
				m_aLeftAnalogStickTrigger[nCntAnalogStick] = (m_aLeftAnalogStick[nCntAnalogStick] ^ aLeftAnalogStick[nCntAnalogStick])&aLeftAnalogStick[nCntAnalogStick];		// ���A�i���O�X�e�B�b�N�̃g���K�[���
				// ���X�e�B�b�N�̃v���X���
				m_aLeftAnalogStick[nCntAnalogStick] = aLeftAnalogStick[nCntAnalogStick];																						// ���A�i���O�X�e�B�b�N�̃v���X���
			}

			//--------------------------------------------------------
			// �\���L�[�̓��͏��̎擾
			//--------------------------------------------------------
			if (aGamePadKeyState.rgdwPOV[0] == 0.0f)
			{// �\���L�[�̏��������
				aPov[POV_UP] = 128;			// ���͂��ꂽ
			}
			if (aGamePadKeyState.rgdwPOV[0] == 18000.0f)
			{// �\���L�[�̉���������
				aPov[POV_DOWN] = 128;			// ���͂��ꂽ
			}
			if (aGamePadKeyState.rgdwPOV[0] == 9000.0f)
			{// �\���L�[�̉E��������
				aPov[POV_RIGHT] = 128;			// ���͂��ꂽ
			}
			if (aGamePadKeyState.rgdwPOV[0] == 27000.0f)
			{// �\���L�[�̍���������
				aPov[POV_LEFT] = 128;			// ���͂��ꂽ
			}

			for (int nCntPov = 0; nCntPov < POV_MAX; nCntPov++)
			{// �\���L�[�̕����̎�ޕ����[�v

				m_aPovTrigger[nCntPov] = (m_aPov[nCntPov] ^ aPov[nCntPov])&aPov[nCntPov];	// �\���L�[�̃g���K�[���
				m_aPov[nCntPov] = aPov[nCntPov];											// �\���L�[�̃v���X���
			}
			m_aGamePad = aGamePadKeyState;			// ���݂̏�Ԃ�ۑ�
		}
		else
		{
			m_pDevGamePad->Acquire();				// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��
		}
	}
}

//=============================================================================
// �R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputGamePad::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &m_pDevGamePad, NULL);

	// �f�o�C�X�����o�o���Ȃ������ꍇ
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// �R�[���o�b�N�֐�
//=============================================================================
BOOL CALLBACK CInputGamePad::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	//�ϐ��錾
	HRESULT hr;
	DIPROPRANGE diprg;

	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj = lpddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -(GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE);				// �\���L�[�̍ŏ��l [��] [��]
	diprg.lMax = GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE;				// �\���L�[�̍ő� [��] [��]
	hr = m_pDevGamePad->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

//=============================================================================
// �v���X����
//=============================================================================
bool CInputGamePad::GetGamePadPress(int nKey)
{
	return (m_aGamePadKeyState[nKey] & 0x80) ? true : false;
}

//========================================================================================
// ���͏��(�g���K�[���)���擾
//========================================================================================
bool CInputGamePad::GetGamePadTrigger(int nKey)
{
	return (m_aGamePadKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================================================
// �̓��͏��(�����[�X���)���擾
//========================================================================================
bool CInputGamePad::GetGamePadRelease(int nKey)
{
	return (m_aGamePadKeyStateRelease[nKey] & 0x80) ? true : false;
}

//===========================================================================
// �Q�[���p�b�h�̃X�e�B�b�N���͏��(�v���X���)���擾
//============================================================================
bool CInputGamePad::GetGamePadStickPress(int nKey)
{
	return (m_aLeftAnalogStick[nKey] & 0x80) ? true : false;
}

//============================================================================
// �Q�[���p�b�h�̃X�e�B�b�N���͏��(�g���K�[���)���擾
//=============================================================================
bool CInputGamePad::GetGamePadStickTrigger(int nKey)
{
	return (m_aLeftAnalogStickTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �\���L�[���͏��(�g���K�[���)���擾
//=============================================================================
bool CInputGamePad::GetPovTpress(int nAngle)
{
	return (m_aPov[nAngle] & 0x80) ? true : false;
}

//=============================================================================
// �\���L�[���͏��(�g���K�[���)���擾
//=============================================================================
bool CInputGamePad::GetPovTtigger(int nAngle)
{
	return (m_aPovTrigger[nAngle] & 0x80) ? true : false;
}