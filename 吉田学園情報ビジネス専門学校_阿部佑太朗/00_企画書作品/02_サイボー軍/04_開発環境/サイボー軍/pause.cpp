//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "pause.h"
#include "fade.h"
#include "renderer.h"

//=============================================================================
//  �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSE] = {};	// �e�N�X�`��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause() : CScene(7)
{
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_apScene2D[nCntPause] = NULL;
	}

	m_nNumSelect = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{

	// �w�i�̐���
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] == NULL)
		{
			m_apScene2D[nCntPause] = new CScene2D(7);

			if (m_apScene2D[nCntPause] != NULL)
			{
				// ����������
				m_apScene2D[nCntPause]->Init();

				// �e�N�X�`���̐ݒ�
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);
			}
		}
	}
	 //�w�i�̑傫����ݒ�
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 200);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 200, 50);
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f), 200, 50);
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 50);

	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_apScene2D[2]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[3]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	m_nNumSelect = 1;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	// ����������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	// ����
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nNumSelect = (m_nNumSelect + SELECT_MAX - 1) % SELECT_MAX;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = 3;
			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nNumSelect = (m_nNumSelect + 1) % SELECT_MAX;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = 3;

			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

	CFade *pFade = CManager::GetFade();
	// ���[�h�J��
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A)==true)
	{
		CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
		if (m_nNumSelect == 1)
		{//�@�I���P��
			CGame::SetPause(false);
		}
		else if (m_nNumSelect == 2)
		{//�@�I��2��
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
		else if (m_nNumSelect == 3)
		{//�@�I��3��
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_SELECT);
			}
		}
	}
	// �w�i�̑傫����ݒ�
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 200);

	//	�傫���J���[�̐ݒ�
	for (int nCount = 1; nCount < MAX_PAUSE; nCount++)
	{
		if (nCount != m_nNumSelect)
		{
			//�@�J���[�̐ݒ�
			m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f + (nCount * 100), 0.0f), 200, 50);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// PAUSE�̐�������
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = {};
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			// ������
			pPause->Init();
		}
		else
		{
		}
	}
	return  pPause;
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause100.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause000.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause002.png", &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����J��
//=============================================================================
void CPause::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_PAUSE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}
