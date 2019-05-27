//=============================================================================
//
//	�~�b�V�������b�Z�[�W���� [credit.cpp]
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
#include"missionmessage.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CMissionMessage::m_pTexture[MAX_MISSONMESSAGE_UI] = {};	// �e�N�X�`��
int CMissionMessage::m_nGameTextCounter = NULL;
int CMissionMessage::m_nNumText = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CMissionMessage::CMissionMessage()
{
	for (int nCount = 0; nCount < MAX_MISSONMESSAGE_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_bPressState = false;

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CMissionMessage::~CMissionMessage()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMissionMessage::Init(void)
{
	m_bPressState = false;
	m_nGameTextCounter = 0;
	m_nNumText = 0;

	CMissionMessage::Load();
	for (int nCount = 0; nCount < MAX_MISSONMESSAGE_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	�������̊m��
			m_apScene2D[nCount] = new CScene2D;

			if (m_apScene2D[nCount] != NULL)
			{
				// ����������
				m_apScene2D[nCount]->Init();
				m_apScene2D[nCount]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
void CMissionMessage::Uninit(void)
{
	CMissionMessage::UnLoad();

	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_MISSONMESSAGE_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	//	���ׂẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMissionMessage::Update(void)
{
	m_nGameTextCounter++;
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	�t�F�C�h���I�������
		if ((pInputKeyboard->GetTrigger(DIK_M) == true || pInputGamepad->GetGamePadTrigger(BUTTON_X) == true ) &&m_nGameTextCounter > 120)
		{//	�G���^�[���������ʑJ��
			m_nGameTextCounter = 0;
			m_nNumText += 1;
			CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTO);
		}
	}

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	�t�F�C�h���I�������
		if (m_nNumText > 4)
		{
			if (pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_Y) == true)
			{//	�G���^�[���������ʑJ��
				pFade->SetFade(CManager::MODE_STAGESELECT);
			}
		}
	}
	//	�w�i
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(400.0f, 240.0f, 0.0f),400.0f,90.0f);
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMissionMessage::Draw(void)
{
}


//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CMissionMessage::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/MISSIONMESSAGE/bossmesssage.png", &m_pTexture[0]);			//	�N���W�b�g�w�i

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����J��
//=============================================================================
void CMissionMessage::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_MISSONMESSAGE_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//�Q�[���̕����̃e�L�X�g���o�͂���J�E���^�[
//=============================================================================
int CMissionMessage::GetGameText(void)
{
	return m_nGameTextCounter;
}
//=============================================================================
//�Q�[���̕����̃e�L�X�g���o�͂���J�E���^�[
//=============================================================================
int CMissionMessage::GetNumText(void)
{
	return m_nNumText;
}