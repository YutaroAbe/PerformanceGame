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
#include "title.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TITLE_UI] = {};	// �e�N�X�`��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_nCounterAnim[nCount] = NULL;
		m_nPatternAnim[nCount] = NULL;
	}
	 m_bPressState = false;

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_nCounterAnim[nCount] = 0;
		m_nPatternAnim[nCount] = 0;
	}
	m_bPressState = false;

	CTitle::Load();

	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
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
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f / 2, 720.0f / 2);	//	�^�C�g���w�i  �ʒu
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));										//	�^�C�g���w�i�@�F
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 2, 560.0f, 0.0f), 180, 50);						//	PRESSENTER	�ʒu
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));										//	PRESSENTER�@�F
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2.5, 0.0f), 500, 140);				//	�^�C�g�����S

	//�e�N�X�`���̐ݒ�
	D3DXVECTOR2 tex[4];
	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 4.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f));
	tex[3] = D3DXVECTOR2((1.0f / 4.0f), (1.0f / 2.0f));
	m_apScene2D[0]->SetTexture(&tex[0]);

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f));
	tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f));
	m_apScene2D[1]->SetTexture(&tex[0]);

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 7.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	tex[3] = D3DXVECTOR2((1.0f / 7.0f), 1.0f);
	m_apScene2D[2]->SetTexture(&tex[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	CTitle::UnLoad();

	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_TITLE_UI; nCntPause++)
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
void CTitle::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	�t�F�C�h���I�������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadRelease(BUTTON_A) == true)
		{//	�G���^�[���������ʑJ��
			pFade->SetFade(CManager::MODE_SELECT);
			m_bPressState = true;
		}
	}
	m_nCounterAnim[0]++;//	�^�C�g�����S���A�j���[�V�������鎞�Ԃ̉��Z
	m_nCounterAnim[1]++;//	PRESS ENTER���A�j���[�V�������鎞�Ԃ̉��Z
	m_nCounterAnim[2]++;//	�^�C�g���w�i���A�j���[�V�������鎞�Ԃ̉��Z
	if (m_bPressState == false)
	{
		if ((m_nCounterAnim[0] % 100) == 0)
		{//	�^�C�g���w�i���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim[0] += 1;
			//	�^�C�g���w�i�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + 0.0f, 0.0f);
			tex[1] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + (1.0f / 4.0f), 0.0f);
			tex[2] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4 + 0.0f), 0.5f);
			tex[3] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + (1.0f / 4.0f), 0.5f);
			m_apScene2D[0]->SetTexture(&tex[0]);
		}
		if ((m_nCounterAnim[2] % 30) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim[1] += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}

		if ((m_nCounterAnim[2] % 12) == 0 || m_nCounterAnim[2] >= 600)
		{//	�^�C�g�����S���A�j���[�V�������鎞�ԊԊu
			if (m_nCounterAnim[2] <= 600)
			{
				m_nPatternAnim[2] += 1;
			}
			else if (m_nCounterAnim[2] >= 600)
			{
				m_nPatternAnim[2] = 0;
				m_nCounterAnim[2] = 0;
			}

			if (m_nPatternAnim[2] <= 6)
			{
				//	�^�C�g�����S�̃A�j���[�V����
				D3DXVECTOR2 tex[4];
				tex[0] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + 0.0f, 0.0f);
				tex[1] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + (1.0f / 7.0f), 0.0f);
				tex[2] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7 + 0.0f), 1.0f);
				tex[3] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + (1.0f / 7.0f), 1.0f);
				m_apScene2D[2]->SetTexture(&tex[0]);

			}

		}
	}
	if (m_bPressState == true)
	{//	PRESSENTER�������ꂽ��
		if ((m_nCounterAnim[2] % 5) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim[1] += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/titlebg.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/pressabutton.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/titlelogo.png", &m_pTexture[2]);



	return S_OK;
}

//=============================================================================
// �e�N�X�`�����J��
//=============================================================================
void CTitle::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_TITLE_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}