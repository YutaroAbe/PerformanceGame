//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"		// �}�l�[�W���[
#include "input.h"			// ����
#include "camera.h"			// �J����
#include "light.h"			// ���C�g
#include "renderer.h"		// �����_���[
#include "fade.h"			// �t�F�[�h
#include "title.h"			// �^�C�g��
#include "game.h"			// �Q�[��
#include "result.h"			// ���U���g
#include "scene.h"			// �V�[��
#include "debugproc.h"		// �f�o�b�O���O
#include "selectmode.h"		// �Z���N�g���[�h
#include "sound.h"			// �T�E���h
#include "player.h"			//	�v���C���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STATE_MODE (MODE_TITLE)		//	�n�܂郂�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CManager::MODE		CManager::m_mode			= CManager::MODE_GAMETUTO;	// ���[�h
CInputKeyboard		*CManager::m_pInputKeyboard = NULL;					// �L�[�{�[�h
CInputDIPad			*CManager::m_pInputDIPad	= NULL;					// DI�p�b�h
CInputXPad			*CManager::m_pInputXPad		= NULL;					// X�p�b�h
CRenderer			*CManager::m_pRenderer		= NULL;					// �����_���[
CCamera				*CManager::m_pCamara		= NULL;					// �J����
CLight				*CManager::m_pLight			= NULL;					// ���C�g
CTitle				*CManager::m_pTitle			= NULL;					// �^�C�g��
CSelectMode			*CManager::m_pSelectMode	= NULL;					// �Z���N�g���[�h
CGame				*CManager::m_pGame			= NULL;					// �Q�[��
CResult				*CManager::m_pResult		= NULL;					// ���U���g
CDebugProcLEFT *CManager::m_CDebugProcLeft		= NULL;					// �f�o�b�O�p�̍��p������
CDebugProcRIGHT *CManager::m_CDebugProcRight	= NULL;					// �f�o�b�O�p�̉E�p������
CSound				*CManager::m_pSound			= NULL;					// �T�E���h
int					CManager::m_nPlayerLife = 0;						//	�v���C���[��HP
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_nPlayerLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �L�[�{�[�h
		if (m_pInputKeyboard == NULL)
		{// NULL�̏ꍇ//// �L�[�{�[�h�������m��
			m_pInputKeyboard = new CInputKeyboard;
			if (m_pInputKeyboard != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �L�[�{�[�h����������
				if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
				{
					return -1;
				}
			}
			else
			{// NULL�̏ꍇ
				MessageBox(0, "InputKeyboard��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "InputKeyboard��NULL�łȂ�", "�x��", MB_OK);
		}
	// DI�p�b�h
		if (m_pInputDIPad == NULL)
		{// NULL�̏ꍇ// DI�p�b�h�������m��
			m_pInputDIPad = new CInputDIPad;
			if (m_pInputDIPad != NULL)
			{// NULL�ȊO�̏ꍇ
			 // DI�p�b�h����������
				if (FAILED(m_pInputDIPad->Init(hInstance, hWnd)))
				{
					return -1;
				}
			}
			else
			{// NULL�̏ꍇ
				MessageBox(0, " InputDIPad��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "InputDIPad��NULL�łȂ�", "�x��", MB_OK);
		}
	// DI�p�b�h
		if (m_pInputXPad == NULL)
		{// NULL�̏ꍇ// DI�p�b�h�������m��
			m_pInputXPad = new CInputXPad;
			if (m_pInputXPad != NULL)
			{// NULL�ȊO�̏ꍇ
			 // DI�p�b�h����������
				if (FAILED(m_pInputXPad->Init(hInstance, hWnd)))
				{
					return -1;
				}
			}
			else
			{// NULL�̏ꍇ
				MessageBox(0, "InputXPad��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, " InputXPad��NULL�łȂ�", "�x��", MB_OK);
		}
		// �����_���[
		if (m_pRenderer == NULL)
		{// NULL�̏ꍇ// �����_���[�������m��
			m_pRenderer = new CRenderer;
			if (m_pRenderer != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �����_���[����������
				if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
				{
					return -1;
				}
			}
			else
			{// NULL�̏ꍇ,
				MessageBox(0, "Renderer��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, "Renderer��NULL�łȂ�", "�x��", MB_OK);
		}
		if (m_pSound == NULL)
		{//	�T�E���h���g�p����Ă��Ȃ������ꍇ
			m_pSound = new CSound;
			if (m_pSound != NULL)
			{//	�T�E���h�̐���
				m_pSound->InitSound(hWnd);
			}
			else
			{// NULL�̏ꍇ
				MessageBox(0, " �T�E���h��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, " �T�E���h��NULL�łȂ�", "�x��", MB_OK);
		}

		// ���C�g
		if (m_pLight == NULL)
		{// NULL�̏ꍇ// ���C�g�������m��
			m_pLight = new CLight;
			if (m_pLight != NULL)
			{// NULL�ȊO�̏ꍇ
			 // ���C�g����������
				if (FAILED(m_pLight->Init()))
				{
					return -1;
				}
			}
			else
			{// NULL�̏ꍇ
				MessageBox(0, " Light��NULL", "�x��", MB_OK);
			}
		}
		else
		{// NULL�ȊO�̏ꍇ
			MessageBox(0, " Light��NULL�łȂ�", "�x��", MB_OK);
		}
		if (m_CDebugProcLeft == NULL)
		{//	��������̐���
			m_CDebugProcLeft = new CDebugProcLEFT;
			if (m_CDebugProcLeft != NULL)
			{//	�������񂪐�������Ă���
				m_CDebugProcLeft->Init();
			}
		}
		if (m_CDebugProcRight == NULL)
		{//	�E������̐���
			m_CDebugProcRight = new CDebugProcRIGHT;
			if (m_CDebugProcRight != NULL)
			{//	�E�����񂪐�������Ă���
				m_CDebugProcRight->Init();
			}
		}
	//	�t�F�C�h�̓ǂݍ���
	CFade::Load();
	SetMode(STATE_MODE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{

	switch (m_mode)
	{// ���[�h
	 // �^�C�g��----------------------------
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{// �I������
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
		// �Z���N�g���[�h----------------------------
	case CManager::MODE_SELECTMODE:
		if (m_pSelectMode != NULL)
		{// �I������
			m_pSelectMode->Uninit();
			delete m_pSelectMode;
			m_pSelectMode = NULL;
		}
		break;
		// �Q�[���`���[�g���A��----------------------------
	case CManager::MODE_GAMETUTO:
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���X�e�[�W1----------------------------
	case CManager::MODE_GAMESTAGE000:
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���X�e�[�W2----------------------------
	case CManager::MODE_GAMESTAGE001:
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���X�e�[�W3----------------------------
	case CManager::MODE_GAMESTAGE002:
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���I�[�o�[----------------------------
	case CManager::MODE_OVER:
		if (m_pResult != NULL)
		{// �I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
		// �N���A----------------------------
	case CManager::MODE_CLEAR:
		if (m_pResult != NULL)
		{// �I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}
	//	�t�F�C�h�̊J��
	CFade::Unload();

	if (m_pInputKeyboard != NULL)
	{// NULL�ȊO�̏ꍇ
		// �I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;	// �L�[�{�[�h�������J��
		m_pInputKeyboard = NULL;	// NULL
	}

	if (m_pInputDIPad != NULL)
	{// NULL�ȊO�̏ꍇ
		// �I������
		m_pInputDIPad->Uninit();
		delete m_pInputDIPad;	// DI�p�b�h�������J��
		m_pInputDIPad = NULL;	// NULL
	}
	if (m_pInputXPad != NULL)
	{// NULL�ȊO�̏ꍇ
	 // �I������
		m_pInputXPad->Uninit();
		delete m_pInputXPad;	// X�p�b�h�������J��
		m_pInputXPad = NULL;	// NULL
	}

	// �����_���[
	if (m_pRenderer != NULL)
	{// NULL�ȊO�̏ꍇ
		// �I������
		m_pRenderer->Uninit();
		delete m_pRenderer;	// �����_���[�������J��
		m_pRenderer = NULL;	// NULL
	}

	// �J����
	if (m_pCamara != NULL)
	{// NULL�ȊO�̏ꍇ
		// �I������
		m_pCamara->Uninit();
		delete m_pCamara;	// �J�����������J��
		m_pCamara = NULL;	// NULL
	}
	if (m_pSound != NULL)
	{// NULL�ȊO�̏ꍇ
		//�I������
		m_pSound->UninitSound();
		delete m_pSound;	//	�T�E���h�̊J��
		m_pSound = NULL;	//	NULL
	}
	// ���C�g
	if (m_pLight != NULL)
	{// NULL�ȊO�̏ꍇ
		// �I������
		m_pLight->Uninit();

		delete m_pLight;	// ���C�g�������J��
		m_pLight = NULL;	// NULL
	}

	if (m_CDebugProcLeft != NULL)
	{
		//	�f�o�b�O�p�����t�H���g�̏I������
		m_CDebugProcLeft->Uninit();
		//�������̊J��
		delete m_CDebugProcLeft;
		//��ɂ���
		m_CDebugProcLeft = NULL;
	}
	if (m_CDebugProcRight != NULL)
	{
		//	�f�o�b�O�p�����t�H���g�̏I������
		m_CDebugProcRight->Uninit();
		//�������̊J��
		delete m_CDebugProcRight;
		//��ɂ���
		m_CDebugProcRight = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	switch (m_mode)
	{// ���[�h
	 // �^�C�g��----------------------------
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{// �X�V����
			m_pTitle->Update();
		}
		break;
		// �Z���N�g------------------------------
	case CManager::MODE_SELECTMODE:
		if (m_pSelectMode != NULL)
		{// �X�V����
			m_pSelectMode->Update();
		}
		break;
		// �`���[�g���A��------------------------------
	case CManager::MODE_GAMETUTO:
		if (m_pGame != NULL)
		{// �X�V����
			m_pGame->Update();
		}
		break;
		// �X�e�[�W1------------------------------
	case CManager::MODE_GAMESTAGE000:
		if (m_pGame != NULL)
		{// �X�V����
			m_pGame->Update();
		}
		break;
		// �X�e�[�W1------------------------------
	case CManager::MODE_GAMESTAGE001:
		if (m_pGame != NULL)
		{// �X�V����
			m_pGame->Update();
		}
		break;
		// �X�e�[�W2------------------------------
	case CManager::MODE_GAMESTAGE002:
		if (m_pGame != NULL)
		{// �X�V����
			m_pGame->Update();
		}
		break;
		// g�Q�[���I�[�o�[----------------------------
	case CManager::MODE_OVER:
		if (m_pResult != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pResult->Update();
		}
		break;
		// �N���A----------------------------
	case CManager::MODE_CLEAR:
		if (m_pResult != NULL)
		{	// NULL�ȊO�̏ꍇ
			m_pResult->Update();
		}
		break;
	}
	if (m_pInputKeyboard != NULL)
	{// NULL�ȊO�̏ꍇ
		// �L�[�{�[�h�X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputDIPad != NULL)
	{// NULL�ȊO�̏ꍇ
		// DI�p�b�h�X�V����
		m_pInputDIPad->Update();
	}

	if (m_pInputXPad != NULL)
	{// NULL�ȊO�̏ꍇ
		// X�p�b�h�X�V����
		m_pInputXPad->Update();
	}


	if (m_pRenderer != NULL)
	{// NULL�ȊO�̏ꍇ
		// �����_���[�X�V����
		m_pRenderer->Update();
	}

	if (m_pCamara != NULL)
	{// NULL�ȊO�̏ꍇ
		// �J�����X�V����
		m_pCamara->Update();
	}

	if (m_pLight != NULL)
	{// NULL�ȊO�̏ꍇ
		// ���C�g�X�V����
		m_pLight->Update();
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamara != NULL)
	{// NULL�ȊO�̏ꍇ
	 // �J�����`�揈��
		m_pCamara->SetCamera();
	}
	if (m_pRenderer != NULL)
	{// NULL�ȊO�̏ꍇ
	 // �����_���[�`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h�ݒ菈��
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	/*if (CGame::GetPlayer() != NULL)
	{
		m_nPlayerLife = CGame::GetPlayer()->GetLife();
	}*/
	switch (m_mode)
	{// ���[�h�i���݁j
	 // �^�C�g��----------------------------
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{// �I������
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);	//	BGM�~�߂�

		// �J����
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pCamara->Uninit();
			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}
		break;
		// �Z���N�g------------------------------
	case CManager::MODE_SELECTMODE:
		if (m_pSelectMode != NULL)
		{// �I������
			m_pSelectMode->Uninit();
			delete m_pSelectMode;
			m_pSelectMode = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_SELECT);	//	BGM�~�߂�

		break;
		// �`���[�g���A��---------------------------
	case CManager::MODE_GAMETUTO:
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		// �J����
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pCamara->Uninit();
			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}

		break;
		// �X�e�[�W1---------------------------
	case CManager::MODE_GAMESTAGE000:
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		// �J����
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pCamara->Uninit();
			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}


		break;
		// �X�e�[�W1---------------------------
	case CManager::MODE_GAMESTAGE001:
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGE2);
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		// �J����
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pCamara->Uninit();
			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}
		break;
		// �X�e�[�W3----------------------------
	case CManager::MODE_GAMESTAGE002:
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGE3);
		if (m_pGame != NULL)
		{// �I������
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		// �J����
		if (m_pCamara != NULL)
		{// NULL�ȊO�̏ꍇ
		 // �I������
			m_pCamara->Uninit();
			delete m_pCamara;	// �J�����������J��
			m_pCamara = NULL;	// NULL
		}
		break;
		// g�Q�[���I�[�o�[----------------------------
	case CManager::MODE_OVER:
		if (m_pResult != NULL)
		{// �I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
		// �N���A----------------------------
	case CManager::MODE_CLEAR:
		if (m_pResult != NULL)
		{// �I������
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}


	// ���[�h�ύX
	m_mode = mode;

	switch (mode)
	{// ���[�h
	 // �^�C�g��----------------------------
	case CManager::MODE_TITLE:
		if (m_pTitle == NULL)
		{// NULL�̏ꍇ
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{// ����������
				m_pTitle->Init();
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);	//	BGM�炷
		if (m_pCamara == NULL)
		{// NULL�̏ꍇ// �J�����������m��
			m_pCamara = new CCamera;
			if (m_pCamara != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �J��������������
				m_pCamara->Init(CCamera::CAMERATYPE_TITLE);
			}
		}
		break;
		// �Z���N�g���[�h------------------------------
	case CManager::MODE_SELECTMODE:
		if (m_pSelectMode == NULL)
		{// NULL�̏ꍇ
			m_pSelectMode = new CSelectMode;
			if (m_pSelectMode != NULL)
			{// ����������
				m_pSelectMode->Init();
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
		break;
		// �`���[�g���A��----------------------------
	case CManager::MODE_GAMETUTO:
		// �J����
		if (m_pGame == NULL)
		{// NULL�̏ꍇ
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{// ����������
				m_pGame->Init(CGame::STAGE_TUTORIAL, m_nPlayerLife);
			}
		}
		if (m_pCamara == NULL)
		{// NULL�̏ꍇ// �J�����������m��
			m_pCamara = new CCamera;
			if (m_pCamara != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �J��������������
				m_pCamara->Init(CCamera::CAMERATYPE_GAME);
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;
		// �X�e�[�W1----------------------------
	case CManager::MODE_GAMESTAGE000:
		// �J����
		if (m_pGame == NULL)
		{// NULL�̏ꍇ
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{// ����������
				m_pGame->Init(CGame::STAGE_001, m_nPlayerLife);
			}
		}
		if (m_pCamara == NULL)
		{// NULL�̏ꍇ// �J�����������m��
			m_pCamara = new CCamera;
			if (m_pCamara != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �J��������������
				m_pCamara->Init(CCamera::CAMERATYPE_GAME);
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;
		// �X�e�[�W2----------------------------
	case CManager::MODE_GAMESTAGE001:
		// �J����
		if (m_pGame == NULL)
		{// NULL�̏ꍇ
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{// ����������
				m_pGame->Init(CGame::STAGE_002, m_nPlayerLife);
			}
		}

		if (m_pCamara == NULL)
		{// NULL�̏ꍇ// �J�����������m��
			m_pCamara = new CCamera;
			if (m_pCamara != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �J��������������
				m_pCamara->Init(CCamera::CAMERATYPE_GAME);
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_STAGE2);
		break;
		// �X�e�[�W3----------------------------
	case MODE_GAMESTAGE002:
		// �J����
		if (m_pGame == NULL)
		{// NULL�̏ꍇ
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{// ����������
				m_pGame->Init(CGame::STAGE_003, m_nPlayerLife);
			}
		}

		if (m_pCamara == NULL)
		{// NULL�̏ꍇ// �J�����������m��
			m_pCamara = new CCamera;
			if (m_pCamara != NULL)
			{// NULL�ȊO�̏ꍇ
			 // �J��������������
				m_pCamara->Init(CCamera::CAMERATYPE_GAME);
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_STAGE3);
		break;
		// �I�[�o�[----------------------------
	case CManager::MODE_OVER:
		if (m_pResult == NULL)
		{	// NULL�̏ꍇ
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{// ����������
				m_pResult->Init(CResult::GAMESTATE_OVER);
			}
		}
		break;
		// �N���A----------------------------
	case CManager::MODE_CLEAR:
			if (m_pResult == NULL)
			{	// NULL�̏ꍇ
				m_pResult = new CResult;
				if (m_pResult != NULL)
				{// ����������
					m_pResult->Init(CResult::GAMESTATE_CLEAR);
				}
			}
		break;
	}

}
