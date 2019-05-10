//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture[MAX_RESULT_UI] = {};	// �e�N�X�`��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	for (int nCount = 0; nCount < MAX_RESULT_UI; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount] = NULL;
		}
	}
	gamestate = GAMESTATE_NOMAL;

	m_fGameOverCounter = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bPressState = false;

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(void)
{
	m_fGameOverCounter = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bPressState = false;

	int GameState =  CGame::GetGameState();
	if (GameState == CGame::GAMESTATE_CLEAR)
	{//
		gamestate = GAMESTATE_CLEAR;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_CLEAR);
	}
	else
	{
		gamestate = GAMESTATE_OVER;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_OVER);

	}


	CResult::Load();

	for (int nCount = 0; nCount < MAX_RESULT_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	�������̊m��
			m_apScene2D[nCount] = new CScene2D;

			if (m_apScene2D[nCount] != NULL)
			{
				// ����������
				m_apScene2D[nCount]->Init();
				m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				// �e�N�X�`���̐ݒ�
				m_apScene2D[nCount]->BindTexture(m_pTexture[nCount]);
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	CResult::UnLoad();

	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_RESULT_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	//	���ׂẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	CSound::StopSound(CSound::SOUND_LABEL_BGM_CLEAR);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_OVER);
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();



	if (pFade->m_fade == pFade->FADE_NONE)
	{//	�t�F�C�h���I�������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
		{//	�G���^�[���������ʑJ��

			pFade->SetFade(CManager::MODE_SELECT);
			m_bPressState = true;
		}
	}

	m_fGameOverCounter += 0.0075f;					//	�Q�[���I�[�o�[�܂��̓Q�[���N���A���o�����鎞��
	m_nCounterAnim++;								//	press abbuttom���A�j���[�V��������Ԋu

	switch (gamestate)
	{
	case GAMESTATE_NOMAL:
		break;
	case GAMESTATE_OVER:
		//	�Q�[��
		m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 3, 300.0f, 0.0f), 350.0f,150.0f);
		m_apScene2D[0]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f+ m_fGameOverCounter));
		//	�I�[�o�[
		m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 1.5f, 450.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[1]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));

		break;
	case GAMESTATE_CLEAR:
		//	�X�e�[�W
		m_apScene2D[3]->SetPosition(D3DXVECTOR3(1280.0f / 3, 300.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[3]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));
		//	�N���A
		m_apScene2D[4]->SetPosition(D3DXVECTOR3(1280.0f / 1.5f, 450.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[4]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));

		break;
	}
	//	PRESS A BUTTON
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(1280.0f / 2, 560.0f, 0.0f), 180, 50);
	m_apScene2D[2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (m_bPressState == false)
	{
		if ((m_nCounterAnim % 30) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[2]->SetTexture(&tex[0]);
		}
	}
	else if (m_bPressState == true)
	{
		if ((m_nCounterAnim % 5) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[2]->SetTexture(&tex[0]);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CResult::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/game.png", &m_pTexture[0]);	//	�Q�[��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/over.png", &m_pTexture[1]);	//	�I�[�o�[
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/pressabutton.png", &m_pTexture[2]);	//	press a button
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/stage.png", &m_pTexture[3]);	//	�I�[�o�[
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/clear.png", &m_pTexture[4]);	//	press a button

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����J��
//=============================================================================
void CResult::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_RESULT_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}