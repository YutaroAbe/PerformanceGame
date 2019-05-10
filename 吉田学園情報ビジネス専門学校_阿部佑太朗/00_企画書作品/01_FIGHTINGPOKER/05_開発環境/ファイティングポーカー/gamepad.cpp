//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �R���g���[���[���͏��� [gamepad.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "gamepad.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define	GAMEPAD_NUM_KEY_MAX			(128)	// �L�[�̍ő吔
#define	GAMEPAD_NUM_POV_KEY_MAX		(4)		// �\���L�[�̍ő吔
#define MAX_GAMEPAD					(2)		// �Q�[���p�b�h�̍ő吔

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECTINPUT8 g_pGamePad = NULL;						// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevGamePad[MAX_GAMEPAD] = {};		// ���̓f�o�C�X(k�R���g���[���[)�ւ̃|�C���^
DIDEVCAPS g_GamepadCaps;								// �Q�[���p�b�h�̋@�\���

DIJOYSTATE2 g_aGamePadKeyState[MAX_GAMEPAD];			// �L�[�{�[�h�̓��͏��(�v���X���)
DIJOYSTATE2 g_aGamePadKeyStateTrigger[MAX_GAMEPAD];		// �L�[�{�[�h�̓��͏��(�g���K�[���)
DIJOYSTATE2 g_aGamePadKeyStateRelease[MAX_GAMEPAD];		// �L�[�{�[�h�̓��͏��(�����[�X���)

STICK_POV g_StickPovType[MAX_GAMEPAD];
STICK_POV g_StickPovTypeOld[MAX_GAMEPAD];
int g_nPovOld[MAX_GAMEPAD];								// �O��̏\���L�[�̕���

int g_nGamePad;				// �Q�[���p�b�h�̃J�E���^�[
int g_nGamePadAccess;		// �Q�[���p�b�h�̃J�E���^�[�ijoystick�̋@�\�R�[���o�b�N�֐��Ŏg�p
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// �Q�[���p�b�h�̃J�E���^�[�̏�����
	g_nGamePad = 0;
	g_nGamePadAccess = 0;

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pGamePad, NULL)))
	{
		return FALSE;
	}

	// ���̓f�o�C�X(�R���g���[���[)�̐���
	if (FAILED(g_pGamePad->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))		// ��4���� (ATTACHEDONLY = ���ݐڑ�����Ă���W���C�X�e�B�b�N�̂݌��o����)
	{
		return FALSE;
	}



	for (int nCnt = 0; nCnt < g_nGamePad; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{// �R���g���[���[���q�����Ă��Ȃ��Ƃ��������Ȃ�
		// �f�o�C�X�Ƀf�[�^�t�H�[�}�b�g��ݒ�
			if (FAILED(hr = g_pDevGamePad[nCnt]->SetDataFormat(&c_dfDIJoystick2)))
			{
				return FALSE;
			}

			// �������[�h��ݒ�
			if (FAILED(hr = g_pDevGamePad[nCnt]->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
			{
				return FALSE;
			}

			// �Q�[���p�b�h�̋@�\�̏������W
			g_GamepadCaps.dwSize = sizeof(DIDEVCAPS);

			if (FAILED(hr = g_pDevGamePad[nCnt]->GetCapabilities(&g_GamepadCaps)))
			{
				g_pDevGamePad[nCnt]->Release();
				return FALSE;
			}

			// �e���̃��[�h�ݒ�
			if (FAILED(hr = g_pDevGamePad[nCnt]->EnumObjects(EnumAxesCallback, (void*)g_pDevGamePad[nCnt], DIDFT_AXIS)))
			{
				return FALSE;
			}
			// �X�e�B�b�N��XY���̐�����[EnumAxesCallback]���Ă΂��̂ł����ŃJ�E���^�[��i�߂�
			g_nGamePadAccess++;

			// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
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
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{// �R���g���[���[���q�����Ă��Ȃ��Ƃ��������Ȃ�
		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
			if (g_pDevGamePad[nCnt] != NULL)
			{
				g_pDevGamePad[nCnt]->Unacquire();
				g_pDevGamePad[nCnt]->Release();
				g_pDevGamePad[nCnt] = NULL;
			}
		}
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pGamePad != NULL)
	{
		g_pGamePad->Release();
		g_pGamePad = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateGamePad(void)
{
	for (int nCnt = 0; nCnt < MAX_GAMEPAD; nCnt++)
	{
		if (g_pDevGamePad[nCnt] != NULL)
		{
			DIJOYSTATE2 aGamePadKeyState;		// �R���g���[���[�̓��͏��
			HRESULT hr;

			// �O��̏\���L�[�̏����L�^
			g_nPovOld[nCnt] = g_aGamePadKeyState[nCnt].rgdwPOV[0];
			// �O��̃X�e�B�b�N�̊p�x�̏����L�^
			g_StickPovTypeOld[nCnt] = g_StickPovType[nCnt];

			hr = g_pDevGamePad[nCnt]->Poll();

			// ���̓f�o�C�X����f�[�^���擾
			if (SUCCEEDED(hr = g_pDevGamePad[nCnt]->GetDeviceState(sizeof(DIJOYSTATE2), &aGamePadKeyState)))
			{
				// �{�^��
				for (int nCntKey = 0; nCntKey < GAMEPAD_NUM_KEY_MAX; nCntKey++)
				{
					// �R���g���[���[�̓��͏��̕ۑ�(�g���K�[)
					g_aGamePadKeyStateTrigger[nCnt].rgbButtons[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ g_aGamePadKeyState[nCnt].rgbButtons[nCntKey]) & aGamePadKeyState.rgbButtons[nCntKey];
					// �R���g���[���[�̓��͏��̕ۑ�(�����[�X)
					g_aGamePadKeyStateRelease[nCnt].rgbButtons[nCntKey] = (aGamePadKeyState.rgbButtons[nCntKey] ^ g_aGamePadKeyState[nCnt].rgbButtons[nCntKey]) & g_aGamePadKeyState[nCnt].rgbButtons[nCntKey];
					// �R���g���[���[�̓��͏��̕ۑ�(�v���X)
					g_aGamePadKeyState[nCnt].rgbButtons[nCntKey] = aGamePadKeyState.rgbButtons[nCntKey];
				}

				// �\���{�^��
				// �R���g���[���[�̓��͏��̕ۑ�(�g���K�[)
				g_aGamePadKeyStateTrigger[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];;
				// �R���g���[���[�̓��͏��̕ۑ�(�����[�X)
				g_aGamePadKeyStateRelease[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];;
				// �R���g���[���[�̓��͏��̕ۑ�(�v���X)
				g_aGamePadKeyState[nCnt].rgdwPOV[0] = aGamePadKeyState.rgdwPOV[0];

				// �X�e�B�b�N�̓��͏��
				g_aGamePadKeyState[nCnt] = aGamePadKeyState;

				// �\�������̃X�e�B�b�N�̓��͏��
				if (g_aGamePadKeyState[nCnt].lX < -GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lX > GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lY < -GAMEPAD_DEADZONE || g_aGamePadKeyState[nCnt].lY> GAMEPAD_DEADZONE)
				{
					float fGamePagStickAngle = atan2f(float(-g_aGamePadKeyState[nCnt].lX), float(g_aGamePadKeyState[nCnt].lY));

					if (fGamePagStickAngle > (D3DX_PI / 8) * 7 || fGamePagStickAngle < (-D3DX_PI / 8) * 7)
					{// ��
						g_StickPovType[nCnt] = STICK_UP;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 7 && fGamePagStickAngle > (D3DX_PI / 8) * 5)
					{ // ����
						g_StickPovType[nCnt] = STICK_LEFT_UP;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 5 && fGamePagStickAngle >(D3DX_PI / 8) * 3)
					{ // ��
						g_StickPovType[nCnt] = STICK_LEFT;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 3 && fGamePagStickAngle >(D3DX_PI / 8) * 1)
					{ // ����
						g_StickPovType[nCnt] = STICK_LEFT_DOWN;
					}
					else if (fGamePagStickAngle <(D3DX_PI / 8) * 1 && fGamePagStickAngle >(-D3DX_PI / 8) * 1)
					{// ��
						g_StickPovType[nCnt] = STICK_DOWN;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 1 && fGamePagStickAngle >(-D3DX_PI / 8) * 3)
					{ // �E��
						g_StickPovType[nCnt] = STICK_RIGHT_DOWN;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 3 && fGamePagStickAngle >(-D3DX_PI / 8) * 5)
					{// �E
						g_StickPovType[nCnt] = STICK_RIGHT;
					}
					else if (fGamePagStickAngle <(-D3DX_PI / 8) * 5 && fGamePagStickAngle >(-D3DX_PI / 8) * 7)
					{// �E��
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
				g_pDevGamePad[nCnt]->Acquire();		// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���p�b�h�̓��͏��(�X�e�B�b�N)���擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
DIJOYSTATE2 *GetgamePadStick(int nPadID)
{
	return(&g_aGamePadKeyState[nPadID]);
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�e�B�b�N�̏\�������̓��͏��(�v���X���)���擾
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
// �X�e�B�b�N�̏\�������̓��͏��(�g���K�[���)���擾
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
// �X�e�B�b�N�̏\�������̓��͏��(�����[�X���)���擾
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
// �Q�[���p�b�h�̏\���L�[���͏��(�v���X���)���擾
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
// �Q�[���p�b�h�̏\���L�[���͏��(�g���K�[���)���擾
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
// �Q�[���p�b�h�̏\���L�[���͏��(�����[�X���)���擾
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
// �Q�[���p�b�h�̓��͏��(�v���X���)���擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadPress(int nPadID, int nKey)
{
	return(g_aGamePadKeyState[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���p�b�h�̓��͏��(�g���K�[���)���擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadTrigger(int nPadID, int nKey)
{
	return(g_aGamePadKeyStateTrigger[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �Q�[���p�b�h�̓��͏��(�����[�X���)���擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetGamePadRelease(int nPadID, int nKey)
{
	return(g_aGamePadKeyStateRelease[nPadID].rgbButtons[nKey] & 0x80) ? true : false;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// joystick�p�R�[���o�b�N�֐�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidinstance, VOID* pContext)
{
	HRESULT hr;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾
	hr = g_pGamePad->CreateDevice(pdidinstance->guidInstance, &g_pDevGamePad[g_nGamePad], NULL);

	// �f�o�C�X�����o�o���Ȃ������ꍇ
	if (FAILED(hr))
	{
		return DIENUM_CONTINUE;
	}

	// �J�E���^�[��i�߂�
	g_nGamePad++;

	return DIENUM_CONTINUE;
	//return DIENUM_STOP;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// joystick�̋@�\�R�[���o�b�N�֐�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HRESULT hr;
	DIPROPRANGE diprg;

	diprg.diph.dwSize		= sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow		= DIPH_BYID;
	diprg.diph.dwObj		= pdidoi->dwType;
	diprg.lMin				= -(GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE);				// �\���L�[�̍ŏ��l [��] [��]
	diprg.lMax				= GAMEPAD_DEADZONE / GAMEPAD_DEADZONE * MAX_ZONE;					// �\���L�[�̍ő�l [��] [�E]

	// �f�o�C�X�ɐݒ�
	hr = g_pDevGamePad[g_nGamePadAccess]->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}