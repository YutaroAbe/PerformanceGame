//=============================================================================
//
// ���C������ [main.cpp]
// Author : �ړc ��
//
//=============================================================================
#include "main.h"
#include "poker.h"
#include "battle.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "cardModel.h"
#include "ui.h"
#include "camera.h"
#include "fade.h"
#include "light.h"
#include "PlayerShow.h"
#include "player.h"
#include "game.h"
#include "title.h"
#include "select.h"
#include "rule.h"
#include "rulebook.h"
#include "credit.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Fighting Poker"		// �E�C���h�E�̃L���v�V������
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)
MODE g_mode = MODE_TITLE;
LPD3DXFONT				g_pFont = NULL;		// �t�H���g�ւ̃|�C���^
void DrawGuide(void);
//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = TRUE;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�I�u�W�F�N�g�̐���
																// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

																			// �L�[�{�[�h�̏���������
	InitKeyboard(hInstance, hWnd);
	// �Q�[���p�b�h�̏���������
	InitGamePad(hInstance, hWnd);
	// �T�E���h�̏���������
	InitSound(hWnd);
	// �t�F�[�h�̐ݒ�
	InitFade(g_mode);
	// �J�����̏���������
	InitCamera();
	// ���C�g�̏���������
	InitLight();
	//���[�h�̐ݒ�
	SetMode(g_mode);

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//�L�[�{�[�h�̏I������
	UninitKeyboard();
	// �Q�[���p�b�h�̏I������
	UninitGamePad();
	// �T�E���h�̏I������
	UninitSound();
	//�t�F�[�h�̏I������
	UninitFade();
	// ���C�g�̏I������
	UninitLight();

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// �L�[�{�[�h�̍X�V����
	UpdateKeyboard();
	// �Q�[���p�b�h�̍X�V����
	UpdateGamePad();

	switch (g_mode)
	{
	case MODE_TITLE:		// �^�C�g�����[�h
		UpdateTitle();
		break;
	case MODE_SELECT:		// �Z���N�g���[�h
		UpdateSelect();
		break;
	case MODE_RULE:			// ���[���u�b�N���[�h
		UpdateRulebook();
		break;
	case MODE_CREDIT:		// �N���W�b�g���[�h
		UpdateCredit();
		break;
	case MODE_GAME:			// �Q�[�����[�h
		UpdateGame();
		break;
	}

	//�t�F�[�h�̍X�V
	UpdateFade();
	// �J�����̍X�V����
	UpdateCamera();
	// ���C�g�̍X�V����
	UpdateLight();
}
//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// �J�����̐ݒ�
		SetCamera(0);
		switch (g_mode)
		{
		case MODE_TITLE:		// �^�C�g�����[�h
			DrawTitle();
			break;
		case MODE_SELECT:		// �Z���N�g���[�h
			DrawSelect();
			break;
		case MODE_RULE:			// ���[���u�b�N���[�h
			DrawRulebook();
			break;
		case MODE_CREDIT:		// �N���W�b�g���[�h
			DrawCredit();
			break;
		case MODE_GAME:			// �Q�[�����[�h
			DrawGame();
			// �f�o�b�O�p�R�}���h
		//	DrawGuide();
			break;
		}

		// �t�F�[�h�̕`��
		DrawFade();

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//�Q�[�����[�h�̐ݒ�
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:		// �^�C�g�����[�h
		UninitTitle();
		StopSound(SOUND_LABEL_TITLE_BGM);
		break;
	case MODE_SELECT:		// �Z���N�g���[�h
		UninitSelect();
		StopSound(SOUND_LABEL_SELECT_BGM);
		break;
	case MODE_RULE:			// ���[���u�b�N���[�h
		UninitRulebook();
		break;
	case MODE_CREDIT:		// �N���W�b�g���[�h
		UninitCredit();
		StopSound(SOUND_LABEL_CREDIT_BGM);
	case MODE_GAME:
		UninitGame();		// �Q�[�����[�h
		break;
	}

	// ���[�h����
	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:		// �^�C�g�����[�h
		InitTitle();
		StopSound();
		PlaySound(SOUND_LABEL_TITLE_BGM);
		SelectVolume(SOUND_LABEL_TITLE_BGM, 0.2f);
		break;
	case MODE_SELECT:		// �Z���N�g���[�h
		InitSelect();
		PlaySound(SOUND_LABEL_SELECT_BGM);
		SelectVolume(SOUND_LABEL_SELECT_BGM, 0.2f);
		break;
	case MODE_RULE:			// ���[���u�b�N���[�h
		InitRulebook();
		break;
	case MODE_CREDIT:		// �N���W�b�g���[�h
		InitCredit();
		StopSound(SOUND_LABEL_SELECT_BGM);
		PlaySound(SOUND_LABEL_CREDIT_BGM);
		SelectVolume(SOUND_LABEL_CREDIT_BGM, 0.2f);
		break;
	case MODE_GAME:			// �Q�[�����[�h
		InitGame();
		StopSound(SOUND_LABEL_SELECT_BGM);
		break;
	}
}
//=============================================================================
//�Q�[�����[�h�̎擾
//============================================================================
MODE GetMode(void)
{
	return g_mode;
}
//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

////=============================================================================
//// �����\������
////=============================================================================
void DrawGuide(void)
{
	GAMEMODE GameMode = GetGameMode();
	FADE pFade;
	pFade = GetFade();

	Camera *pCamera = GetCamera();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[10000];
	int nLength = 0;

	CARDSIDE side = GetPokerState();

	int nNumHand1P = GetHandNum(0);
	int nNumHand2P = GetHandNum(1);

	CARDTYPE type1P = GetType(0);
	CARDTYPE type2P = GetType(1);

	CARDTYPE Hand1P[5];
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		Hand1P[nCnt] = Get1PHand(nCnt);
	}
	CARDTYPE Hand2P[5];
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		Hand2P[nCnt] = Get2PHand(nCnt);
	}

	if (GameMode == GAMEMODE_POKER)
	{
		switch (side)
		{
		case CARD_SIDE_1P:
			wsprintf(&aStr[nLength], "1P�̔�\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case CARD_SIDE_2P:
			wsprintf(&aStr[nLength], "2P�̔�\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case CARD_SIDE_ALL:
			wsprintf(&aStr[nLength], "�I��\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "================== 1P ===================\n");
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "\n���݂̖�\n");
		nLength = (int)strlen(&aStr[0]);
		switch (nNumHand1P)
		{
		case 0:
			wsprintf(&aStr[nLength], "�n�C�J�[�h [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 1:
			wsprintf(&aStr[nLength], "�����y�A [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 2:
			wsprintf(&aStr[nLength], "�c�[�y�A [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 3:
			wsprintf(&aStr[nLength], "�X���[�J�[�h [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 4:
			wsprintf(&aStr[nLength], "�t�H�[�J�[�h [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 5:
			wsprintf(&aStr[nLength], "�t���b�V�� [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 10:
			wsprintf(&aStr[nLength], "�t���n�E�X [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 100:
			wsprintf(&aStr[nLength], "STRONG�@ZERO [ %d ]\n", nNumHand1P);
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "\n���݂̎�D\n");
		nLength = (int)strlen(&aStr[0]);
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			wsprintf(&aStr[nLength], "%d����", nCnt + 1);
			nLength = (int)strlen(&aStr[0]);
			switch (Hand1P[nCnt])
			{
			case TYPE_BRAVE:
				wsprintf(&aStr[nLength], "[ �E�� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_KING:
				wsprintf(&aStr[nLength], "[ ���l ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_DEVIL:
				wsprintf(&aStr[nLength], "[ ���� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_COMMONER:
				wsprintf(&aStr[nLength], "[ ���� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_JOKER:
				wsprintf(&aStr[nLength], "[ �W���[�J�[ ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			}
		}
		wsprintf(&aStr[nLength], "\n���݂̃L�����N�^�[\n");
		nLength = (int)strlen(&aStr[0]);
		switch (type1P)
		{
		case TYPE_BRAVE:
			wsprintf(&aStr[nLength], "[ �E�� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_KING:
			wsprintf(&aStr[nLength], "[ ���l ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_DEVIL:
			wsprintf(&aStr[nLength], "[ ���� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_COMMONER:
			wsprintf(&aStr[nLength], "[ ���� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_GOD:
			wsprintf(&aStr[nLength], "[ ����(��) ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "================== 2P ===================\n");
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "\n���݂̖�\n");
		nLength = (int)strlen(&aStr[0]);
		switch (nNumHand2P)
		{
		case 0:
			wsprintf(&aStr[nLength], "�n�C�J�[�h [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 1:
			wsprintf(&aStr[nLength], "�����y�A [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 2:
			wsprintf(&aStr[nLength], "�c�[�y�A [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 3:
			wsprintf(&aStr[nLength], "�X���[�J�[�h [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 4:
			wsprintf(&aStr[nLength], "�t�H�[�J�[�h [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 5:
			wsprintf(&aStr[nLength], "�t���b�V�� [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 10:
			wsprintf(&aStr[nLength], "�t���n�E�X [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		case 100:
			wsprintf(&aStr[nLength], "STRONG�@ZERO [ %d ]\n", nNumHand2P);
			nLength = (int)strlen(&aStr[0]);
			break;
		}
		wsprintf(&aStr[nLength], "\n���݂̎�D\n");
		nLength = (int)strlen(&aStr[0]);
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			wsprintf(&aStr[nLength], "%d����", nCnt + 1);
			nLength = (int)strlen(&aStr[0]);
			switch (Hand2P[nCnt])
			{
			case TYPE_BRAVE:
				wsprintf(&aStr[nLength], "[ �E�� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_KING:
				wsprintf(&aStr[nLength], "[ ���l ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_DEVIL:
				wsprintf(&aStr[nLength], "[ ���� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_COMMONER:
				wsprintf(&aStr[nLength], "[ ���� ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			case TYPE_JOKER:
				wsprintf(&aStr[nLength], "[ �W���[�J�[ ]\n");
				nLength = (int)strlen(&aStr[0]);
				break;
			}
		}
		wsprintf(&aStr[nLength], "\n���݂̃L�����N�^�[\n");
		nLength = (int)strlen(&aStr[0]);
		switch (type2P)
		{
		case TYPE_BRAVE:
			wsprintf(&aStr[nLength], "[ �E�� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_KING:
			wsprintf(&aStr[nLength], "[ ���l ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_DEVIL:
			wsprintf(&aStr[nLength], "[ ���� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_COMMONER:
			wsprintf(&aStr[nLength], "[ ���� ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		case TYPE_GOD:
			wsprintf(&aStr[nLength], "[ ����(��) ]\n");
			nLength = (int)strlen(&aStr[0]);
			break;
		}
	}
	else if (GameMode == GAMEMODE_BATTLE)
	{
		// ���������(�J�����̎��_
		wsprintf(&aStr[0], "[�J�����̎��_       : (%d : %d : %d)]\n", (int)pCamera->posV.x, (int)pCamera->posV.y, (int)pCamera->posV.z);

		// ���������(�J�����̒����_
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "[�J�����̒����_     : (%d : %d : %d)]\n\n", (int)pCamera->posR.x, (int)pCamera->posR.y, (int)pCamera->posR.z);

		Player *pPlayer = GetPlayer();

		// Player1.HP�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_HP : %d\n", pPlayer[0].nLife);

		// Player1.�X�L���|�C���g�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_SKIL : %d\n", pPlayer[0].nSkillPoint);

		// Player1.�X�e�[�^�X�����N�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_ATK : %d\n", (int)pPlayer[0].atkRank);
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_DEF : %d\n", (int)pPlayer[0].defRank);

		// Player1.���[�V�����\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER01_���[�V���� : %d\n", (int)pPlayer[0].MotionType);

		// Player2.HP�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_HP : %d\n", pPlayer[1].nLife);

		// Player2.�X�L���|�C���g�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_SKIL : %d\n", pPlayer[1].nSkillPoint);

		// Player1.�X�e�[�^�X�����N�\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_ATK : %d\n", (int)pPlayer[1].atkRank);
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_DEF : %d\n", (int)pPlayer[1].defRank);

		// Player2.���[�V�����\�L
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "PLAYER02_���[�V���� : %d\n", (int)pPlayer[1].MotionType);

		// �ړ���������
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "�ړ��������� : %d\n", GetMoveRimit());

		// FPS
		/*nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "FPS : %d\n", g_nCountFPS);*/

		// ���������(���f������
		nLength = (int)strlen(&aStr[0]);
		wsprintf(&aStr[nLength], "*** �S���Z�b�g ***\nENTER\n");
	}
	else
	{
		wsprintf(&aStr[0], "�f�o�b�O�p�\�L�ł�");
	}

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0x0, 0xff));
}

