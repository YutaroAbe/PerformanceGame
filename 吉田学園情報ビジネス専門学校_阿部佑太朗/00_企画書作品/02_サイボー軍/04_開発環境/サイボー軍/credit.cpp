//=============================================================================
//
//	�N���W�b�g���� [credit.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
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
#include "credit.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
LPDIRECT3DTEXTURE9 CCredit::m_pTexture[MAX_CREDIT_UI] = {};	// �e�N�X�`��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCredit::CCredit()
{
	for (int nCount = 0; nCount < MAX_CREDIT_UI; nCount++)
	{//	�N���W�b�g�̍ő吔����
		if (m_apScene2D[nCount] != NULL)
		{//	�N���W�b�g���g���Ă����ꍇ
			m_apScene2D[nCount] = NULL;
		}
	}
	m_nCounterAnim = 0;			//	�J�E���^�[�A�j���[�V�����̏�����
	m_nPatternAnim = 0;			//	�p�^�[���A�j���[�V�����̏�����
	m_bPressState = false;		//	�����Ă��邩�ǂ����̏�����

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCredit::~CCredit()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCredit::Init(void)
{
	m_nCounterAnim = 0;			//	�J�E���^�[�A�j���[�V�����̏�����
	m_nPatternAnim = 0;			//	�p�^�[���A�j���[�V�����̏�����
	m_bPressState = false;		//	�����Ă��邩�ǂ����̏�����
	//	�N���W�b�g�̓ǂݍ���
	CCredit::Load();

	for (int nCount = 0; nCount < MAX_CREDIT_UI; nCount++)
	{//	�N���W�b�g�̍ő吔����
		if (m_apScene2D[nCount] == NULL)
		{//	�N���W�b�g���g�p����Ă��Ȃ������ꍇ
			//	�������̊m��
			m_apScene2D[nCount] = new CScene2D;
			if (m_apScene2D[nCount] != NULL)
			{//	�N���W�b�g���g���Ă����ꍇ
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
void CCredit::Uninit(void)
{
	//	�e�N�X�`���̔j��
	CCredit::UnLoad();

	// CScene2D���J������
	for (int nCntPause = 0; nCntPause < MAX_CREDIT_UI; nCntPause++)
	{//	�N���W�b�g�̍ő吔������
		if (m_apScene2D[nCntPause] != NULL)
		{//	�N���W�b�g�������Ă����ꍇ
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
void CCredit::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//�Q�[���p�b�h�̏���
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	�t�F�C�h���I�������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
		{//	�G���^�[���������ʑJ��
			m_bPressState = true;					//	�{�^����������
			pFade->SetFade(CManager::MODE_SELECT);	//	�t�F�C�h�̏���
		}
	}
	//	�N���W�b�g�w�i
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f/2, 0.0f), 1280.0f / 2, 720.0f / 2);
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//	PRESS A BUTTON
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 2, 650.0f, 0.0f), 180, 50);
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_nCounterAnim++;
	if (m_bPressState == false)
	{//	�{�^���������Ă��Ȃ������ꍇ
		if ((m_nCounterAnim % 30) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}
	}
	 if (m_bPressState == true)
	{//	�{�^�����������ꍇ
		if ((m_nCounterAnim % 5) == 0)
		{//	PRESSENTER���A�j���[�V�������鎞�ԊԊu
			m_nPatternAnim += 1;
			//	PRESSENTER�̃A�j���[�V����
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCredit::Draw(void)
{
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CCredit::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CREDIT/bg.png", &m_pTexture[0]);			//	�N���W�b�g�w�i
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CREDIT/pressabutton.png", &m_pTexture[1]);	//	press a button

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����J��
//=============================================================================
void CCredit::UnLoad(void)
{
	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_CREDIT_UI; nCntTex++)
	{//	�N���W�b�g�̍ő吔����
		if (m_pTexture[nCntTex] != NULL)
		{//	�N���W�b�g�������Ă����ꍇ
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}