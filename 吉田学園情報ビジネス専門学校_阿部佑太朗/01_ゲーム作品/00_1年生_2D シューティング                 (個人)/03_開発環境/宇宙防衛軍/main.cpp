//=============================================================================
//
// ���C������ [main.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "title.h"//�^�C�g��
#include "game.h"//�Q�[��
#include "result.h"//���U���g
#include "tutorial.h"//�`���[�g���A��
#include "main.h"//���C����
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "score.h"
#include"Selectmode.h"
#include "clear.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"WindowClass"			// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"�F���h�q�R"			// �E�C���h�E�̖��O(�L���v�V������)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;					//Direct3D�I�u�W�F�N�g�̃|�C���g
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//DirectX�f�o�C�X�̃|�C���^
MODE g_mode = MODE_TITLE;					//��ʃX�^�[�g�����[�h
SELECTSTATE g_aSelSTE;

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;//�E�B���h�E�n���h���i���ʎq�j
	MSG msg; //���b�Z�[�W���i�[����ϐ�

	DWORD dwCurrentTime; //	���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ�����������

	timeBeginPeriod(1);//����\

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	srand((unsigned int)time(0));	//���E���h

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							//SCREEN_WIDTH,
							//SCREEN_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);

	// ����������(�E�B���h�E�𐶐����Ă���s��)
	if (FAILED(Init(hInstance, hWnd, FALSE)))//TRUE��FALSE�ɂ���ƃt���X�N���[��
	{
		return -1;
	}

	//����\
	timeBeginPeriod(1);

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"���b�Z�[�W�������Ă����烋�[�v�𔲂���
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
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();	//���ݎ������擾
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60���̂P�b�o��
				dwExecLastTime = dwCurrentTime;	//��������������ۑ�

			}
			// �X�V����
			Update();
			// �`�揈��
			Draw();

		}
	}
	// �I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);


	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{

	case WM_DESTROY:
		// "WM_QUIT"���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			// �E�B���h�E��j������("WM_DESTROY"���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
	}
	g_aSelSTE = GetSelstate();
	if (g_aSelSTE == SELECT_QUIT)
	{
		PostQuitMessage(0);
		DestroyWindow(hWnd);
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ����̏�����Ԃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;									//�v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
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
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferWidth =SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)1280
		d3dpp.BackBufferHeight =SCREEN_HEIGHT;						 // �Q�[����ʃT�C�Y(����)720
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
    d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed					 = bWindow;					    // �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��(VSync��҂��ĕ`��)

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							// �f�o�C�X�^�C�v
									hWnd,									// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,									// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&g_pD3DDevice)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�����������C���v�b�g
	InitKeyboard(hInstance, hWnd);
	//�T�E���h�̐ݒ�
	InitSound(hWnd);
	//���[�h�̐ݒ�
	SetMode(g_mode);
	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//=============================================================================
//		�I������
//=============================================================================
void Uninit(void)
{
	// �I�������C���v�b�g
	UninitKeyboard();
	//�T�E���h
	UninitSound();
	//�I�������t�F�C�h
	UninitFade();

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice -> Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
//		�X�V����
//=============================================================================
void Update(void)
{
	// �X�V�����C���v�b�g
	UpdateKeyboard();
	switch (g_mode)
	{//	���[�h
	case MODE_TITLE:			//	�^�C�g�����[�h
		UpdateTITLE();			//	�^�C�g���̍X�V
		break;
	case MODE_SELECTMODE:		//	�Z���N�g���[�h
		UpdateSelectmode();		//	�Z���N�g�̍X�V
		break;
	case MODE_TUTORIAL:			//	�`���[�g���A�����[�h
		UpdateTUTORIAL();		//	�`���[�g���A���̍X�V
		break;
	case MODE_GAME:				//	�Q�[�����[�h
		UpdateGAME();			//	�Q�[���̍X�V
		break;
	case MODE_RANKING:			//	�����L���O���[�h
		UpdateRanking();		//	�����L���O�̍X�V
		break;
	case MODE_RESULT:			//	���U���g���[�h
		UpdateRESULT();			//	���U���g�̍X�V
		break;
	case MODE_CLEAR:			//	�N���A���[�h
		UpdateCLEAR();			//	�N���A�̍X�V
		break;
	}
	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//=============================================================================
//		�`�揈��
//=============================================================================
void Draw(void)
{
		// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
		g_pD3DDevice->Clear(0,
			NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);//��ʐF�ݒ�(0,0,0,0,)�͍�

		//�`��̊J�n
		if (SUCCEEDED(g_pD3DDevice->BeginScene()))
		{
			switch (g_mode)
			{
			case MODE_TITLE:		//	�^�C�g�����[�h
				DrawTITLE();		//	�^�C�g���̕`��
				break;
			case MODE_SELECTMODE:	//	�Z���N�g���[�h
				DrawSelectmode();	//	�Z���N�g�̕`��
				break;
			case MODE_TUTORIAL:		//	�`���[�g���A�����[�h
				DrawTUTORIAL();		//	�`���[�g���A���̕`��
				break;
			case MODE_GAME:			//	�Q�[�����[�h
				DrawGAME();			//	�Q�[���̕`��
				break;
			case MODE_RANKING:		//	�����L���O���[�h
				DrawRanking();		//	�����L���O�̕`��
				break;
			case MODE_RESULT:		//	���U���g���[�h
				DrawRESULT();		//	���U���g�̕`��
				break;
			case MODE_CLEAR:		//	�N���A���[�h
				DrawCLEAR();		//	�N���A�̕`��
				break;
			}
			//�t�F�[�h�̕`�揈��
			DrawFade();
			// �`��̏I��
			g_pD3DDevice->EndScene();

		}

		// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//=============================================================================
//		�f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//		���[�h�̐ݒ�
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:						//	�^�C�g�����[�h
		StopSound(SOUND_LABEL_BGM003);		//	�����~�߂�
		UninitTITLE();						//	�^�C�g���I������
		break;
	case MODE_SELECTMODE:					//	�Z���N�g���[�h
		StopSound(SOUND_LABEL_BGM004);		//	�����~�߂�
		UninitSelectmode();					//	�Z���N�g�̏I������
		break;
	case MODE_TUTORIAL:						//	�`���[�g���A�����[�h
		StopSound(SOUND_LABEL_BGM006);		//	�����~�߂�
		UninitTUTORIAL();					//	�`���[�g���A���I������
		break;
	case MODE_GAME:							//	�Q�[�����[�h
		StopSound(SOUND_LABEL_BGM005);		//	�����~�߂�
		UninitGAME();						//	�Q�[���̏I������
		break;
	case MODE_RANKING:						//	�����L���O���[�h
		StopSound(SOUND_LABEL_BGM007);		//	�����~�߂�
		UninitRanking();					//	�����L���O�̏I������
		break;
	case MODE_RESULT:						//	���U���g���[�h
		StopSound(SOUND_LABEL_BGM008);		//	�����~�߂�
		UninitRESULT();						//	���U���g�̏I������
		break;
	case MODE_CLEAR:						//	�N���A���[�h
		StopSound(SOUND_LABEL_BGM009);		//	�����~�߂�
		UninitCLEAR();						//	�N���A�̏I������
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:						//	�^�C�g�����[�h
		PlaySound(SOUND_LABEL_BGM003);		//	���̍Đ�
		InitTITLE();						//	�^�C�g���̏�����
		break;
	case MODE_SELECTMODE:					//	�Z���N�g���[�h
		PlaySound(SOUND_LABEL_BGM004);		//	���̍Đ�
		InitSelectmode();					//	�Z���N�g�̏�����
		break;
	case MODE_TUTORIAL:						//	�`���[�g���A�����[�h
		PlaySound(SOUND_LABEL_BGM006);		//	���̍Đ�
		InitTUTORIAL();						//	�`���[�g���A���̏�����
		break;
	case MODE_GAME:							//	�Q�[�����[�h
		PlaySound(SOUND_LABEL_BGM005);		//	���̍Đ�
		InitGAME();							//	�Q�[���̏�����
		break;
	case MODE_RANKING:						//	�����L���O���[�h
		PlaySound(SOUND_LABEL_BGM007);		//	���̍Đ�
		InitRanking();						//	�����L���O�̏�����
		break;
	case MODE_RESULT:						//	���U���g���[�h
		PlaySound(SOUND_LABEL_BGM008);		//	���̍Đ�
		InitRESULT();						//	���U���g�̏�����
		break;
	case MODE_CLEAR:						//	�N���A���[�h
		PlaySound(SOUND_LABEL_BGM009);		//	���̍Đ�
		InitCLEAR();						//	�N���A�̏�����
		break;
	}
	g_mode = mode;
}
//=============================================================================
//	���[�h�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}
