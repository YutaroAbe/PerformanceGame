//=============================================================================
//
// �Z���N�g���� [selsect.cpp]
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
#include "select.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CSelect::m_pTexture[MAX_SELECT_UI] = {};	// �e�N�X�`��
int CSelect::m_nNumSelect = 1;
int CSelect::m_nSelectWordCounter = NULL;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSelect::CSelect()
{
	//�ϐ��̏�����
	for (int nCount = 0; nCount < MAX_SELECT_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_nNextCounter = 0;
	m_bPress = false;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSelect::~CSelect()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSelect::Init(void)
{
	//�ϐ��̏�����
	m_nNumSelect = 1;
	m_nSelectWordCounter = 0;
	m_nNextCounter = 0;
	m_bPress = false;
	CSelect::Load();

	for (int nCount = 0; nCount < MAX_SELECT_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	�������̊m��
			m_apScene2D[nCount] = new CScene2D;
			if (m_apScene2D[nCount] != NULL)
			{
				// ����������
				m_apScene2D[nCount]->Init();

				// �e�N�X�`���̐ݒ�
				m_apScene2D[nCount]->BindTexture(m_pTexture[nCount]);

			}
		}
	}
	//	�Z���N�g�@�ʒu�̐ݒ�
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f / 2, 720.0f/2);	//	�Z���N�g�w�i
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(500, 205, 0.0f), 250, 130);								//�@�Q�[�����[�h
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(800, 310, 0.0f), 250, 130);								//	�N���W�b�g���[�h
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(500, 415, 0.0f), 250, 130);								//	�Q�[���I��
	m_apScene2D[4]->SetPosition(D3DXVECTOR3(1280.0f/2, 580, 0.0f), 450, 130);						//	���b�Z�[�W�E�B���h�E
	m_apScene2D[5]->SetPosition(D3DXVECTOR3(1280.0f / 2, 90, 0.0f), 350, 130);						//	�Z���N�g���S
	m_apScene2D[6]->SetPosition(D3DXVECTOR3(250 , 205, 0.0f), 100, 100);							//	���

	//�Z���N�g�J���[�̐ݒ�
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[2]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[3]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[4]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[5]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[6]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSelect::Uninit(void)
{

	CSelect::UnLoad();

	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_SELECT_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSelect::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();


	 if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_S) == true
		 || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
	{//	�Z���N�g�̐�����������̏�����
		 CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_nNextCounter = 0;

	}
	 m_nNextCounter++;
	 if (m_nNextCounter >= 600)
	 {
		 if (pFade->m_fade == pFade->FADE_NONE)
		 {
			 pFade->SetFade(CManager::MODE_TITLE);
		 }
	 }
	 if (m_bPress == false)
	 {
		 m_nSelectWordCounter++;
		 // ����
		 if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true)
		 {
			 m_nSelectWordCounter = 0;
			 m_nNumSelect = (m_nNumSelect + MAX_SELECT - 1) % MAX_SELECT;
			 if (m_nNumSelect == 0)
			 {
				 m_nNumSelect = MAX_SELECT;

			 }
			 m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		 }
		 else if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
		 {
			 m_nSelectWordCounter = 0;
			 m_nNumSelect = (m_nNumSelect + 1) % MAX_SELECT;
			 if (m_nNumSelect == 0)
			 {
				 m_nNumSelect = MAX_SELECT;
			 }
			 m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		 }
	 }
	// ���[�h�J��
	if (pInputKeyboard->GetRelease(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
	{
		m_bPress = true;
		if (m_nNumSelect == 1)
		{//�@�I���P��	[�Q�[�����[�h]
			if (pFade->m_fade == pFade->FADE_NONE)
			{

				pFade->SetFade(CManager::MODE_STAGESELECT);
			}
		}
		else if (m_nNumSelect == 2)
		{//�@�I��2��	[�N���W�b�g]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_CREDIT);
			}
		}
		else if (m_nNumSelect == 3)
		{//�@�I��3��	[�N���W�b�g]
			if (pFade->m_fade == pFade->FADE_NONE)
			{

				pFade->SetFade(CManager::MODE_TITLE);
			}
		}
	}

	//	���̐ݒ�
	if (m_nNumSelect == 1)
	{//�@�I���P��	[�Q�[�����[�h]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(250, 205, 0.0f), 100, 100);							//	���
	}
	else if (m_nNumSelect == 2)
	{//�@�I��2��	[�N���W�b�g]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(550, 310, 0.0f), 100, 100);							//	���
	}
	else if (m_nNumSelect == 3)
	{//�@�I��2��	[�N���W�b�g]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(250, 415, 0.0f), 100, 100);							//	���
	}
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	�傫���J���[�̐ݒ�
	for (int nCount = 1; nCount < MAX_SELECT_UI; nCount++)
	{
		if (nCount != m_nNumSelect)
		{
			//�@�J���[�̐ݒ�
			m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CSelect::Draw(void)
{

}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CSelect::Load(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//	�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/selectbg.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select000.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select002.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/Message.png", &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/selectLogo.png", &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/yajirusi.png", &m_pTexture[6]);
	return S_OK;
}

//=============================================================================
//	�e�N�X�`�����J��
//=============================================================================
void CSelect::UnLoad(void)
{
	//	�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_SELECT_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// �I������ԍ��̎擾
//=============================================================================
int CSelect::GetNumSelect(void)
{
	return m_nNumSelect;
}

//=============================================================================
//�@�Z���N�g�̕�����\���J�E���^�[�̎擾
//=============================================================================
int  CSelect::GetSelWordCounter(void)
{
	return m_nSelectWordCounter;
}
