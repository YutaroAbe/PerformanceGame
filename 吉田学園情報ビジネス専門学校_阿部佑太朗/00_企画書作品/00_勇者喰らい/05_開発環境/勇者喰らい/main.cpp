//=============================================================================
//
// ���C������ [main.cpp]
// Author : ���{��
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "billboord.h"
#include "bullet.h"
#include "Title.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"

#include "goburin.h"
#include "Selectmode.h"
#include "endstory.h"
#include "endroll.h"
#include "gameover.h"
#include "story.h"
#include "credit.h"

#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�E�ҋ�炢"		// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPD3DXFONT			g_pFont = NULL;			// �t�H���g�ւ̃|�C���^
void Uninit(void);
void Update(void);
void Draw(void);

void DrawSelTXIT(void);						//�Z���N�g��ʂ̕���
void DrawStoryTXIT(void);					//�X�g�[���[��ʕ���
void DrawEndStoryTXIT(void);				//�G���h�X�g�[���[��ʕ���
void DrawEndrollTXIT(void);					//�G���h���[����ʕ���
void DrawSELECTTXIT(void);					//�Z���N�g��ʕ���

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)

SELECTSTATE g_aSelSTE;						//�Z���N�g�̏��
int g_aSelectMenuMain;						//�Z���N�g�̃��j���[
int g_aSelCounter;							//�Z���N�g�̉�b�o���J�E���^�[

int g_aStoryMenuMain;						//�X�g�[���[�̃��j���[
int g_aStoryCounter;						//�X�g�[���[�̉�b�o���J�E���^�[

int g_aEndStoryMenuMain;					//�G���h�X�g�[���[�̃��j���[
int g_aEndStoryCounter;						//�X�g�[���[�̉�b�o���J�E���^�[

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
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	//int nTime;

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
	if(FAILED(Init(hInstance, hWnd, FALSE)))
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
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
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

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��

				//dwCurrentTime = ���݂̎���
				//dwExecLastTime = �Ō�ɒʂ�������

				//nTime = (dwCurrentTime - dwExecLastTime);
				//nTime = (1000 / 60);

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwExecLastTime = dwCurrentTime;
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
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	g_aSelSTE = GetSelstate();
	if (g_aSelSTE == SELECT_QUIT)
	{
		PostQuitMessage(0);
		DestroyWindow(hWnd);
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
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed					 = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
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
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	D3DXCreateFont(g_pD3DDevice, 38/*�����̍���*/, 16/*�����̕�*/, 0/*�t�H���g�̑���*/, 0/*�~�b�v�}�b�v���x����*/, FALSE, SHIFTJIS_CHARSET,//HANGEUL_CHARSET�؍���//SHIFTJIS_CHARSET���{��
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("monospace")/* �t�H���g��*/, &g_pFont);



	// �e��I�u�W�F�N�g�̏���������
	InitKeyboard(hInstance, hWnd);

	MODE *Mode;	//���݂̃��[�h�m�F�̂���
	GAME_PLAY *game_play = GetGame_Play();
	game_play[0].bUse = true;

	Mode = GetMode();	//���݂̃��[�h�����炤
	srand((unsigned int)time(0));	//�����h�̂���

	InitJoystick();
	InitSound(hWnd);
	InitFade(Mode[0]);
	InitWindow();
	InitFadeWindow();
	InitAnimation();
	InitExplosion();
	InitFont();
	StopSound();


	switch (Mode[0])
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	case MODE_SELCT:
		InitSelectmode();			//�Z���N�g�̏���������
		break;

	case MODE_GAME:
		InitGame(0);
		break;

	case MODE_START:
		InitStart();
		break;

	case MODE_STORY:
		InitStory();				//�X�g�[���[�̏���������
		break;

	case MODE_CREDIT:				//�N���W�b�g��
		InitCredit();
		break;

	case MODE_ENDSTORY:
		InitEndStory();				//�G���h�X�g�[���[�̏���������
		break;

	case MODE_ENDROLL:				//�G���h���[���̏���������
		InitEndRoll();
		break;

	case MODE_GAMEOVER:				//�Q�[���I�[�o�[�̏���������
		InitGameOver();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}


	HWND *hwnd;
	hwnd = GethWnd();
	hwnd[0] = hWnd;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	MODE *Mode;	//���݂̃��[�h�m�F�̂���

	Mode = GetMode();	//���݂̃��[�h�����炤

	StopSound();
	//�e��I�u�W�F�N�g�̏I������
	UninitKeyboard();

	// �e��I�u�W�F�N�g�̍X�V����
	UninitKeyboard();

	switch (Mode[0])
	{
	case MODE_TITLE:

		UninitTitle();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;

	case MODE_SELCT:
		UninitSelectmode();

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_START:
		UninitStart();
		break;

	case MODE_STORY:
		UninitStory();
		break;

	case MODE_CREDIT:
		UninitCredit();
		break;

	case MODE_ENDSTORY:
		UninitEndStory();
		break;

	case MODE_ENDROLL:
		UninitEndRoll();
		break;

	case MODE_GAMEOVER:
		UninitGameOver();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}
	UninitWindow();
	UninitFade();
	UninitFadeWindow();
	UninitFont();
	UninitSound();
	UninitAnimation();
	UninitExplosion();

	if (g_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		g_pFont->Release();
		g_pFont = NULL;
	}

	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
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
	MODE *Mode;	//���݂̃��[�h�m�F�̂���

	Mode = GetMode();	//���݂̃��[�h�����炤

	// �e��I�u�W�F�N�g�̍X�V����
	ConnectJoystick();
	Trigger();

	UpdateKeyboard();
	ButtonKeybord();
	ButtonJoypad();
	GetKeyboardCount();

	switch (Mode[0])
	{
	case MODE_TITLE:
		UpdateTitle();			//�^�C�g���̍X�V����
		break;

	case MODE_RANKING:			//�����L���O�̍X�V����
		UpdateRanking();
		break;

	case MODE_SELCT:
		UpdateSelectmode();		//�Z���N�g�̍X�V����
		UpdateGOBURIN();		//�S�u�����̍X�V����
		break;

	case MODE_GAME:
		UpdateGame();			//�Q�[���̍X�V����
		break;

	case MODE_START:
		UpdateStart();			//�L�������C�N�̍X�V����
		break;

	case MODE_STORY:
		UpdateStory();			//�X�g�[���[�̍X�V����
		UpdateGOBURIN();		//�S�u�����̍X�V����
		break;

	case MODE_CREDIT:			//�N���W�b�g�̍X�V����
		UpdateCredit();
		break;

	case MODE_ENDSTORY:
		UpdateEndStory();		//�G���h�X�g�[���[�̍X�V����
		UpdateGOBURIN();		//�S�u�����̍X�V����
		break;

	case MODE_ENDROLL:			//�G���h���[���̍X�V����
		UpdateEndRoll();
		break;

	case MODE_GAMEOVER:			//�Q�[���I�[�o�[�̍X�V����
		UpdateGameOver();
		break;

	case MODE_RESULT:			//���U���g�̍X�V����
		UpdateResult();
		break;

	}
	UpdateWindow(WINDOW_UPDATE_SELECT);
	UpdateFade();
	UpdateFadeWindow();
	UpdateAnimation();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{

	PLAYER *pPlayer = GetPlayer();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(20, 20, 20, 255), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		D3DVIEWPORT9 ViewportDef[3];
		MODE *Mode;	//���݂̃��[�h�m�F�̂���

		Mode = GetMode();	//���݂̃��[�h�����炤

		switch (Mode[0])
		{
		case MODE_TITLE:					//�^�C�g���̕`�揈��DrawRanking(void)
			DrawTitle();
			break;

		case MODE_RANKING:					//�^�C�g���̕`�揈��
			DrawRanking();
			break;

		case MODE_SELCT:
			//�r���[�|�[�g�̎擾����
			g_pD3DDevice->GetViewport(&ViewportDef[0]);
			DrawSelectmode();
			// �J�����̐ݒ�
			SetCamera(4);					//�J�����̐ݒ�[1]
											// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
			g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
			//�@���f���̕`�揈��
			DrawGOBURIN();					//�S�u�����̕`�揈��
											//�r���[�|�[�g�̐ݒ肷��
			g_pD3DDevice->SetViewport(&ViewportDef[0]);

			if ( pPlayer[0].bButton[BUTTON_S] == true || pPlayer[0].bButton[BUTTON_W] == true)
			{
				g_aSelCounter = 0;
			}
			else
			{
				DrawSelTXIT();				//�Z���N�g�����o��
				g_aSelCounter++;			//�Z���N�g�̕�����J�E���^�[++
			}
			DrawSELECTTXIT();

			break;

		case MODE_STORY:
			//�r���[�|�[�g�̎擾����
			g_pD3DDevice->GetViewport(&ViewportDef[1]);

			// �J�����̐ݒ�
			SetCamera(5);					//�J�����̐ݒ�[2]
											// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
			g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
			//�@���f���̕`�揈��
			DrawGOBURIN();					//�S�u�����̕`�揈��
			DrawStory();					//�X�g�[���[�̕`�揈��
											//�r���[�|�[�g�̐ݒ肷��
			g_pD3DDevice->SetViewport(&ViewportDef[1]);

			if (pPlayer[0].bButton[BUTTON_ENTER] == true && g_aStoryCounter >= 120)
			{//�G���^�[��������

					g_aStoryCounter = 0;

			}
			else
			{
				DrawStoryTXIT();			//�X�g�[���[�̕�����
				g_aStoryCounter++;			//�Z���N�g�̕�����J�E���^�[++
			}

			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_CREDIT:					//�N���W�b�g�̕`�揈��
			DrawCredit();
			break;

		case MODE_START:
			DrawStart();
			break;

		case MODE_ENDSTORY:
			//�r���[�|�[�g�̎擾����
			g_pD3DDevice->GetViewport(&ViewportDef[2]);
			// �J�����̐ݒ�
			SetCamera(5);					//�J�����̐ݒ�[2]
			// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
			g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
			//�@���f���̕`�揈��
			DrawGOBURIN();					//�S�u�����̕`�揈��
			DrawEndStory();					//�G���h�X�g�[���[�̕`�揈��

			if ( pPlayer[0].bButton[BUTTON_ENTER] == true && g_aEndStoryCounter >= 120)
			{//�G���^�[��������

					g_aEndStoryCounter = 0;
			}
			else
			{
				DrawEndStoryTXIT();					//�G���h�X�g�[���[�̕�����
				g_aEndStoryCounter++;			//�Z���N�g�̕�����J�E���^�[++
			}
			break;

		case MODE_ENDROLL:						//�G���h���[���̕`�揈��
			DrawEndRoll();
			DrawEndrollTXIT();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		case MODE_GAMEOVER:					//�Q�[���I�[�o�[�̕`�揈��
			DrawGameOver();
			break;
		}

		// �J�����̐ݒ��߂�
		SetCamera(0);

		DrawFont(WINDOW_DRAW_TIME);
		DrawFade();
		DrawFadeWindow();

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================================//
// �f�o�C�X�̎擾
//=========================================================================================================//
void SetMode(MODE mode, int nFade)
{
	MODE *Mode;	//���݂̃��[�h�m�F�̂���

	Mode = GetMode();	//���݂̃��[�h�����炤


	switch (Mode[0])
	{//���݂̏������I������
	case MODE_TITLE:
		StopSound();
		UninitTitle();
		break;

	case MODE_RANKING:
		StopSound();
		UninitRanking();
		break;

	case MODE_SELCT:
		StopSound();
		UninitSelectmode();			//�Z���N�g�̏I������
		UninitGOBURIN();			//�S�u�����̏I������

		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_START:
		UninitStart();
		break;

	case MODE_STORY:
		StopSound();
		UninitStory();				//�X�g�[���[�̏I������
		UninitGOBURIN();			//�S�u�����̏I������
		break;

	case MODE_CREDIT:				//�N���W�b�g�̏I������
		StopSound();
		UninitCredit();
		break;

	case MODE_ENDSTORY:
		StopSound();
		UninitEndStory();			//�G���h�X�g�[���[�̏I������
		UninitGOBURIN();			//�S�u�����̏I������
		break;

	case MODE_ENDROLL:				//�G���h���[���̏I������
		StopSound();
		UninitEndRoll();
		break;

	case MODE_GAMEOVER:				//�Q�[���I�[�o�[�̏I������
		StopSound();
		UninitGameOver();
		break;

	case MODE_RESULT:
	//	StopSound();
		UninitResult();
		break;


	}//switch����




	switch (mode)
	{//���ɍs�������̏�����
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_RANKING:
		StopSound();
		PlaySound(SOUND_LABEL_CREDIT);
		InitRanking();
		break;
	case MODE_SELCT:

		InitSelectmode();			//�Z���N�g�̏���������
		InitGOBURIN();				//�S�u�����̏���������
		StopSound();
		PlaySound(SOUND_LABEL_SELECT_000);
		g_aSelCounter = 0;			//�Z���N�g�̕�����J�E���^�[�̏���������
		break;

	case MODE_GAME:
		InitGame(nFade);
		break;

	case MODE_START:
		InitStart();
		break;

	case MODE_STORY:
		InitStory();				//�X�g�[���[�̏���������
		InitGOBURIN();				//�S�u�����̏���������
		StopSound();

		g_aStoryCounter = 0;		//�X�g�[���[�̕�����J�E���^�[�̏���������
		PlaySound(SOUND_LABEL_STORY_000);
		break;

	case MODE_CREDIT:				//�N���W�b�g��
		StopSound();

		PlaySound(SOUND_LABEL_CREDIT);
		InitCredit();
		break;

	case MODE_ENDSTORY:

		InitEndStory();				//�G���h�X�g�[���[�̏���������
		InitGOBURIN();				//�S�u�����̏���������
		g_aEndStoryCounter = 0;		//�X�g�[���[�̕�����J�E���^�[�̏���������
		StopSound();

		PlaySound(SOUND_LABEL_ENDSTORY);
		break;

	case MODE_ENDROLL:				//�G���h���[���̏���������

		InitEndRoll();
		StopSound();

		PlaySound(SOUND_LABEL_ENDROLL);
		break;

	case MODE_GAMEOVER:				//�Q�[���I�[�o�[�̏���������

		InitGameOver();
		StopSound();

		PlaySound(SOUND_LABEL_GAMEOVER);
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}//switch����
	Mode[0] = mode;
}

//=========================================================================================================//
// ���[�h�̎擾
//=========================================================================================================//
int *GetTime(void)
{
	static int nTime = 0;

	return &nTime;
}
//=========================================================================================================//
// ���[�h�̎擾
//=========================================================================================================//
int *GetStoryTXT(void)
{
	return &g_aStoryCounter;
}
//=========================================================================================================//
// ���[�h�̎擾
//=========================================================================================================//
int *GetENDStoryTXT(void)
{
	return &g_aEndStoryCounter;
}

//=========================================================================================================//
// ���[�h�̎擾
//=========================================================================================================//
MODE *GetMode(void)
{
	static MODE Mode = MODE_TITLE;

	return &Mode;
}
//=========================================================================================================//
// window�̎擾
//=========================================================================================================//
HWND *GethWnd(void)
{
	static HWND hWnd;

	return &hWnd;
}
//==========================================================================================================================================================
// �f�o�C�X�̎擾
//==========================================================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//==========================================================================================================================================================
// �f�o�C�X�̎擾
//==========================================================================================================================================================
GAME_PLAY *GetGame_Play(void)
{
	static GAME_PLAY g_Game_Play;

	return &g_Game_Play;
}
//==========================================================================================================================================================
// �Z���N�g��ʂ̕���
//==========================================================================================================================================================
void DrawSelTXIT(void)
{
	RECT rect = { 220, 510, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
	char aTX[256];
	g_aSelectMenuMain = GetSelMenu();

	// ���������//�ꕶ���ɂ��X�y�[�X3��
	if (g_aSelectMenuMain == 0)
	{
		if (g_aSelCounter >= 20) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 25) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 30) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 35) { wsprintf(&aTX[0], "         �X\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aSelCounter >= 40) { wsprintf(&aTX[0], "            �g�[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aSelCounter >= 45) { wsprintf(&aTX[0], "                 ���[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aSelCounter >= 50) { wsprintf(&aTX[0], "                       ���[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aSelCounter >= 55) { wsprintf(&aTX[0], "                             �h\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aSelCounter >= 60) { wsprintf(&aTX[0], "                               �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 65) { wsprintf(&aTX[0], "                                  �u�b�B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 70) { wsprintf(&aTX[0], "                                   \n�Q", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 75) { wsprintf(&aTX[0], "                                  �@ \n   -��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 80) { wsprintf(&aTX[0], "                                  �@ \n        ���e", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 85) { wsprintf(&aTX[0], "                                  �@ \n              ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 90) { wsprintf(&aTX[0], "                                  �@ \n       �@�@      ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 95) { wsprintf(&aTX[0], "                                  �@ \n       �@�@         ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 100) { wsprintf(&aTX[0], "                                   �@\n       �@�@            ����", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 105) { wsprintf(&aTX[0], "                                  �@ \n       �@�@                  ����", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 110) { wsprintf(&aTX[0], "                                  �@ \n       �@�@                       �S�u�b", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 115) { wsprintf(&aTX[0], "                                  �@ \n       �@�@                       �@�@�@�@!!", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	else if (g_aSelectMenuMain == 1)
	{
		if (g_aSelCounter >= 20) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 25) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 30) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 35) { wsprintf(&aTX[0], "         �Q\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(200, 100, 200)/*�F*/); }
		if (g_aSelCounter >= 40) { wsprintf(&aTX[0], "            �[��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*�F*/); }
		if (g_aSelCounter >= 45) { wsprintf(&aTX[0], "                  ���[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*�F*/); }
		if (g_aSelCounter >= 50) { wsprintf(&aTX[0], "                       �h\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 200)/*�F*/); }
		if (g_aSelCounter >= 55) { wsprintf(&aTX[0], "                          �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 60) { wsprintf(&aTX[0], "                             �u�b�B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 65) { wsprintf(&aTX[0], " \n�@�@�@�@�X�g", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 70) { wsprintf(&aTX[0], " \n    �@�@�@�@ �[��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 85) { wsprintf(&aTX[0], " \n      �@�@�@�@     �[��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 90) { wsprintf(&aTX[0], " \n       �@�@�@�@          ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 95) { wsprintf(&aTX[0], " \n       �@�@�@�@             ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 100) { wsprintf(&aTX[0], " \n        �@�@�@�@               �S", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 105) { wsprintf(&aTX[0], " \n         �@�@�@�@                 �u�b", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 110) { wsprintf(&aTX[0], " \n         �@�@�@�@                      �H�H", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	else if (g_aSelectMenuMain == 2)
	{
		if (g_aSelCounter >= 20) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 25) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 30) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 35) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 40) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 45) { wsprintf(&aTX[0], "               �X\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 50) { wsprintf(&aTX[0], "                  �^\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 55) { wsprintf(&aTX[0], "                     �b\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 60) { wsprintf(&aTX[0], "                        �t\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 65) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 70) { wsprintf(&aTX[0], "                              \n��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 75) { wsprintf(&aTX[0], "                              \n   ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 80) { wsprintf(&aTX[0], "                              \n      ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 85) { wsprintf(&aTX[0], "                              \n         ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 90) { wsprintf(&aTX[0], "                              \n            ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 95) { wsprintf(&aTX[0], "                              \n               ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 100) { wsprintf(&aTX[0], "                              \n                  ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 105) { wsprintf(&aTX[0], "                              \n                     ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 110) { wsprintf(&aTX[0], "                              \n                         ����", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 115) { wsprintf(&aTX[0], "                              \n                              ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 120) { wsprintf(&aTX[0], "                              \n                                 ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 125) { wsprintf(&aTX[0], "                              \n                                    �S�u�b", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	else if (g_aSelectMenuMain == 3)
	{
		if (g_aSelCounter >= 20) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 25) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 30) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 35) { wsprintf(&aTX[0], "         �Q\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 40) { wsprintf(&aTX[0], "            �[��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 45) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 50) { wsprintf(&aTX[0], "                     �I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 55) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 60) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 65) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aSelCounter >= 70) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
}
//==========================================================================================================================================================
// �X�g�[���[��ʂ̕���
//==========================================================================================================================================================
void DrawStoryTXIT(void)
{
	RECT rect = { 220, 520, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
	char aTX[256];
	g_aStoryMenuMain = GetStoryMenu();


	if (g_aStoryMenuMain == 0)
	{
		RECT rect = { SCREEN_WIDTH / 2 - 380, SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
																									 // ���������
		wsprintf(&aTX[0], "����͐l�ԊE�Ɩ��E�̌����̑�������n�܂���...\n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/);
	}
	if (g_aStoryMenuMain == 1)
	{
		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 210) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aStoryMenuMain == 2)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         �l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 3)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  �b\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        �N\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "                                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "                                                   �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "                                                      �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "                                                        �I�I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aStoryMenuMain == 4)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     �l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "                                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "                                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "                                                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "                                                         �I�I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 5)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     �X\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ���B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 6)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 7)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "             �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                            �n\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                              �B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "\n��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "\n   ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "\n      ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "\n         ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 110) { wsprintf(&aTX[0], "\n              ...", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 8)
	{

		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              �B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "\n�l", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "\n   ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "\n      �E", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "\n         ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "\n            ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "\n               ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "\n                  �u��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 100, 100)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "\n                       ���v", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(55, 50, 198)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "\n                            ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 110) { wsprintf(&aTX[0], "\n                               ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 115) { wsprintf(&aTX[0], "\n                                  ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 120) { wsprintf(&aTX[0], "\n                                     �āB", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 9)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      �B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  �c\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ���B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 10)
	{

		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                       �q\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                          �v\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "                                               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "                                                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "                                                     ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aStoryMenuMain == 11)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  �Z\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        �[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           �W��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                                �I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                   �I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aStoryMenuMain == 12)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   �Q\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                   �l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                         �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                           ��B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "\n��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "\n   ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "\n      ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "\n         �|", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "\n            ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 110) { wsprintf(&aTX[0], "\n               ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 115) { wsprintf(&aTX[0], "\n                  ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 120) { wsprintf(&aTX[0], "\n                     ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 125) { wsprintf(&aTX[0], "\n                        ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 130) { wsprintf(&aTX[0], "\n                           ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 135) { wsprintf(&aTX[0], "\n                              ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 140) { wsprintf(&aTX[0], "\n                                 ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 145) { wsprintf(&aTX[0], "\n                                    ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 150) { wsprintf(&aTX[0], "\n                                       ...", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aStoryMenuMain == 13)
	{

		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                             �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "                                               ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aStoryMenuMain == 14)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         �Q\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            �[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 45) { wsprintf(&aTX[0], "                     �[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 50) { wsprintf(&aTX[0], "                        �h\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 60) { wsprintf(&aTX[0], "                              �i\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 90) { wsprintf(&aTX[0], "                                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 95) { wsprintf(&aTX[0], "                                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "                                                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 105) { wsprintf(&aTX[0], "                                                         �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 110) { wsprintf(&aTX[0], "                                                            �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 115) { wsprintf(&aTX[0], "                                                               ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aStoryMenuMain == 15)
	{
		if (g_aStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 15) { wsprintf(&aTX[0], "   �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 150)/*�F*/); }
		if (g_aStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aStoryCounter >= 40) { wsprintf(&aTX[0], "                  ........\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aStoryMenuMain == 16)
	{
		// ���������
		wsprintf(&aTX[0], "......................\n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/);
	}
	if (g_aStoryMenuMain != 0)
	{
		rect = { 0, 670, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		wsprintf(&aTX[0], "START/P:SKIP\n", aTX);
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(80, 80, 80)/*�F*/);
	}

		 rect = { 0, 470, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		//char aTX[256];

		wsprintf(&aTX[0], "[B]BUTTON/ENTRE�FNEXT \n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(80, 80, 80)/*�F*/);



}
//==========================================================================================================================================================
// �G���h�X�g�[���[��ʂ̕���
//==========================================================================================================================================================
void DrawEndStoryTXIT(void)
{
	RECT rect = { 220, 520, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
	char aTX[256];
	g_aEndStoryMenuMain = GetEndStoryMenu();

	if (g_aEndStoryMenuMain == 0)
	{
		RECT rect = { SCREEN_WIDTH / 2 - 230 , SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
																									  // ���������
		wsprintf(&aTX[0], "�u�����v��|���Ă��炻�̌�...\n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/);
	}
	if (g_aEndStoryMenuMain == 1)
	{
		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 210) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aEndStoryMenuMain == 2)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      �v\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                        ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
	}
	if (g_aEndStoryMenuMain == 3)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               �b\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           �ˁB\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 4)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     �l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 50,50)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "                                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 95) { wsprintf(&aTX[0], "                                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "                                                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 105) { wsprintf(&aTX[0], "                                                         ���I�I\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

	}
	if (g_aEndStoryMenuMain == 5)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "�u��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "     ���v\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 150, 150)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "                   �Z\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                         �[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                            �W\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                              �|\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "                                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "                                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 95) { wsprintf(&aTX[0], "                                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "                                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 105) { wsprintf(&aTX[0], "                                                             ��...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 6)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "�s\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         �m\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ���B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "\n��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "\n   ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "\n      �Z", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "\n         ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "\n            �[", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "\n               �W", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "\n                  ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "\n                     ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 95) { wsprintf(&aTX[0], "\n                        �l", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "\n                           ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 105) { wsprintf(&aTX[0], "\n                              �E", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 110) { wsprintf(&aTX[0], "\n                                 ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 115) { wsprintf(&aTX[0], "\n                                    �j", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 80, 80)/*�F*/); }
		if (g_aEndStoryCounter >= 120) { wsprintf(&aTX[0], "\n                                       ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 80, 80)/*�F*/); }
		if (g_aEndStoryCounter >= 125) { wsprintf(&aTX[0], "\n                                          ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 130) { wsprintf(&aTX[0], "\n                                            ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 135) { wsprintf(&aTX[0], "\n                                               ��", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 135) { wsprintf(&aTX[0], "\n                                                  ���B", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 7)
	{

		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "�l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   �X\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         �N\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 8)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               �Z\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     �[\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        �W\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(150, 150, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "                                             ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "                                                .....\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 9)//�X�g�[���[���[�h
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "                                             �b\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "                                                ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 95) { wsprintf(&aTX[0], "                                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "                                                      ���B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 10)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  �N\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                       ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 11)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "�V\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  �S\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(88, 166, 31)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     �u\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(88, 166, 31)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(88, 166, 31)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(88, 166, 31)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              �E\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(88, 166, 31)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                                       �l\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                                             !!!!\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }



	}
	if (g_aEndStoryMenuMain == 12)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  �́B\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 13)
	{
		if (g_aEndStoryCounter >= 10) { wsprintf(&aTX[0], "��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 15) { wsprintf(&aTX[0], "   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 20) { wsprintf(&aTX[0], "      �A\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 25) { wsprintf(&aTX[0], "         ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 30) { wsprintf(&aTX[0], "            ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 35) { wsprintf(&aTX[0], "               ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 40) { wsprintf(&aTX[0], "                  ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 45) { wsprintf(&aTX[0], "                     ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 50) { wsprintf(&aTX[0], "                        ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 55) { wsprintf(&aTX[0], "                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 60) { wsprintf(&aTX[0], "                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 65) { wsprintf(&aTX[0], "                                 ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 70) { wsprintf(&aTX[0], "                                   ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 75) { wsprintf(&aTX[0], "                     �@�@�@�@�@�@    ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 80) { wsprintf(&aTX[0], "                      �@�@�@�@          ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 85) { wsprintf(&aTX[0], "                                           ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 90) { wsprintf(&aTX[0], "                                              ��\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }
		if (g_aEndStoryCounter >= 95) { wsprintf(&aTX[0], "                                                  ...\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }

		RECT rect = { 950, 650, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
		if (g_aEndStoryCounter >= 100) { wsprintf(&aTX[0], "NEXT\n", aTX); g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/); }


	}
	if (g_aEndStoryMenuMain == 14)
	{
		// ���������
		wsprintf(&aTX[0], "......................\n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255)/*�F*/);
	}

		rect = { 0, 470, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
													   //char aTX[256];

		wsprintf(&aTX[0], "[B]BUTTON/ENTRE�FNEXT \n", aTX);
		// �`��
		g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(80, 80, 80)/*�F*/);

}
//=============================================================================
// �G���h���[����ʂ̕���
//=============================================================================
void DrawEndrollTXIT(void)
{
	RECT rect = { 0, 680, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
	char aTX[256];

	wsprintf(&aTX[0], "START/P�E�E�E������\n", aTX);
	// �`��
	g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(80, 80, 80)/*�F*/);

}
//=============================================================================
// �Z���N�g��ʂ̕���
//=============================================================================
void DrawSELECTTXIT(void)
{
	RECT rect = { 240, 660, SCREEN_WIDTH, SCREEN_HEIGHT };// �����x���W// �����y���W// �E����x���W// �E����y���W
	char aTX[256];

	wsprintf(&aTX[0], "[ �\���L�[�F�I�� :�uB�vBUTTON�F���� ]\n", aTX);
	// �`��
	g_pFont->DrawText(NULL, &aTX[0]/*������ւ̃|�C���^*/, -1, &rect, DT_LEFT, D3DCOLOR_XRGB(80, 80, 80)/*�F*/);

}
