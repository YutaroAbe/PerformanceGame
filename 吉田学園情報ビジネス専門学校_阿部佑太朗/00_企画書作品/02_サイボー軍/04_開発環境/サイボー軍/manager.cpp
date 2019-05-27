//=============================================================================
//
// ���C������ [main.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
CSound *CManager::m_pSound = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CFade *CManager::m_pFade = NULL;
CSelect *CManager::m_pSelect = NULL;
CStageSelect *CManager::m_pStageSelect = NULL;
CInputGamePad *CManager::m_pInputGamepad = NULL;
CCredit *CManager::m_pCredit = NULL;
CMissionMessage *CManager::m_pMissionMessage = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL )
		{
			// �����_�[�̏���������
			if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
			{//�t���X�N���[��
				return -1;
			}
		}
		else
		{
			MessageBox(0, "�������Ń������̊m�ۂ��ł��Ă��܂���", "�x��", MB_OK);
		}
	}
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;

		if ( m_pInputKeyboard != NULL)
		{
			//	���͂̂̏���������
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{
			MessageBox(0, "�������Ń������̊m�ۂ��ł��Ă��܂���", "�x��", MB_OK);
		}
	}
	if (m_pInputGamepad == NULL)
	{
		m_pInputGamepad = new CInputGamePad;

		if (m_pInputGamepad != NULL)
		{
			//	���͂̂̏���������
			if (FAILED(m_pInputGamepad->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{
			MessageBox(0, "�������Ń������̊m�ۂ��ł��Ă��܂���", "�x��", MB_OK);
		}
	}
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{//	�T�E���h�̐���
			m_pSound->InitSound(hWnd);
		}
	}
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		if (m_pFade != NULL)
		{
			m_pFade->Init(m_mode);
		}
	}
	//���[�h�̐ݒ�
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_�[�̏I������
		m_pRenderer->Uninit();

		//�������̊J��
		delete m_pRenderer;

		//NULL�ɂ���
		m_pRenderer = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{
		//���͂̏I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}
	if (m_pInputGamepad != NULL)
	{
		//���͂̏I������
		m_pInputGamepad->Uninit();

		delete m_pInputGamepad;

		m_pInputGamepad = NULL;
	}
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I������
		m_pSound->UninitSound();

		delete m_pSound;

		m_pSound = NULL;
	}
	if (m_pFade != NULL)
	{
		//�t�@�C�h�̏I������
		m_pFade->Uninit();

		delete m_pFade;

		m_pFade = NULL;
	}

	//�S�Ă̏I������
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	int nStageMode = CGame::GetStageState();
	if (m_pRenderer != NULL)
	{
		// �����_�[�X�V����
		m_pRenderer->Update();

		//���͂̍X�V����
		m_pInputKeyboard->Update();

		m_pInputGamepad->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Update();
		}
		break;
	case MODE_GAME:
		if (nStageMode == CGame::SETSTEGEMODE_000)
		{//	�`���[�g���A���݂̂ɏo�͂���
			if (m_pMissionMessage != NULL)
			{//	�~�b�V�������b�Z�[�W
				m_pMissionMessage->Update();
			}
		}
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Update();
		}
		break;
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	int nStageMode = CGame::GetStageState();
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{

			m_pSelect->Draw();
		}
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Draw();
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			m_pGame->Draw();
		}

		if (nStageMode == CGame::SETSTEGEMODE_000)
		{//	�`���[�g���A���݂̂ɏo�͂���
			if (m_pMissionMessage != NULL)
			{//	�~�b�V�������b�Z�[�W
				m_pMissionMessage->Draw();
			}
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Draw();
		}
		break;
	}
}

//=============================================================================
//�����_�[�̎擾
//=============================================================================
CRenderer *CManager ::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//���͂̎擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//���͂̎擾
//=============================================================================
CInputGamePad *CManager::GetInputGamepad(void)
{
	return m_pInputGamepad;
}

//=============================================================================
//	���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{//�I������
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//	�������Ƀf�[�^����������
			m_pTitle->Uninit();					//	�^�C�g���̏I������
			delete m_pTitle;
			m_pTitle = NULL;					//	����������ɂ���
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();					//	�^�C�g���̏I������
			delete m_pSelect;
			m_pSelect = NULL;					//	����������ɂ���
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			delete m_pStageSelect;
			m_pStageSelect = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		break;
	case MODE_GAME:
		if (m_pMissionMessage != NULL)
		{//	�~�b�V�������b�Z�[�W
			m_pMissionMessage->Uninit();
			delete m_pMissionMessage;
			m_pMissionMessage = NULL;
		}
		if (m_pGame != NULL)
		{//	�������Ƀf�[�^����������
			m_pGame->Uninit();					//	�^�C�g���̏I������
			delete m_pGame;
			m_pGame = NULL;						//	����������ɂ���
		}

		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Uninit();
			delete m_pCredit;
			m_pCredit = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_CREDIT);
		break;
	}

	switch (mode)
	{//����������
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//�^�C�g���ɉ����Ȃ�������
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{//	���������m�ۏo������
				m_pTitle->Init();				//�^�C�g���̏���������
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case MODE_SELECT:
		if (m_pSelect == NULL)
		{
			m_pSelect = new CSelect;
			if (m_pSelect != NULL)
			{//	�������̊m�ۂ��o������
				m_pSelect->Init();				//	�Z���N�g�̏I������
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect == NULL)
		{
			m_pStageSelect = new CStageSelect;
			if (m_pStageSelect != NULL)
			{
				m_pStageSelect->Init();
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//�^�C�g���ɉ����Ȃ�������
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{//	���������m�ۏo������
				m_pGame->Init();				//�Q�[���̏���������
			}
		}
		if (m_pMissionMessage == NULL)
		{
			m_pMissionMessage = new CMissionMessage;
			if (m_pMissionMessage != NULL)
			{
				m_pMissionMessage->Init();
			}
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//�^�C�g���ɉ����Ȃ�������
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				m_pResult->Init();
			}
		}


		break;
	case MODE_CREDIT:
		if (m_pCredit == NULL)
		{
			m_pCredit = new CCredit;
			if (m_pCredit != NULL)
			{
				m_pCredit->Init();

			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_CREDIT);

		break;
	}

	m_mode = mode;
 }

//=============================================================================
//	���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}