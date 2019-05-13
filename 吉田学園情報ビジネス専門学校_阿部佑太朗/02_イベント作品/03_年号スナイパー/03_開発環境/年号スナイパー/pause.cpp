//*****************************************************************************
//
//			�|�[�Y�̏���[pause.cpp]
//			Auther : YUTARO ABE
//
//*****************************************************************************

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"		// ����
#include "manager.h"	// �}�l�[�W���[
#include "renderer.h"	// �����_���[
#include "scene2D.h"	// �V�[��2D
#include "pause.h"		// �|�[�Y
#include "fade.h"		// �t�F�[�h
#include "game.h"		//	Pause
#include "sound.h"		//	��

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define TEXTURE_NAME000	"data/Texture/pause/continue.png"	// �ǂݍ��ރe�N�X�`��000
#define TEXTURE_NAME001	"data/Texture/pause/retry.png"		// �ǂݍ��ރe�N�X�`��001
#define TEXTURE_NAME002	"data/Texture/pause/Quit.png"		// �ǂݍ��ރe�N�X�`��002
#define COL_A			(0.009f)							// �����x�̕ω���
#define COL_A_MAX		(0.65f)								// �����x�̌��x��
#define POS_X_INTERVAL	(150.0f)							// X���W�̊Ԋu
#define PRESS_BUTTON_X	(50.0f)								// �{�^���̃T�C�Y(X��)
#define PRESS_BUTTON_Y	(50.0f)								// �{�^���̃T�C�Y(Y��)
#define PRESS_INTERVAL	(200.0f)							// ���j���[�Ƃ̋���

//*****************************************************************************
//				�ÓI�����o�ϐ�
//*****************************************************************************
int				CPause::m_nNum = false;

//*****************************************************************************
//				��������
//*****************************************************************************
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	CPause *pPause = {};

	// �V�[���̐���
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			pPause->Init(pos, size, col, UV);
		}
	}
	return pPause;
}
//*****************************************************************************
//				���[�h
//*****************************************************************************
HRESULT CPause::Load(void)
{

	return S_OK;
}
//*****************************************************************************
//				�A�����[�h
//*****************************************************************************
void CPause::Unload(void)
{

}
//*****************************************************************************
//				�R���X�g���N�^
//*****************************************************************************
CPause::CPause()
{

}
//*****************************************************************************
//				�f�X�g���N�^
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
//				����������
//*****************************************************************************
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	Load();		// �ǂݍ���

	//�@������
	m_nNum = 0;

	return S_OK;
}

//*****************************************************************************
//				�I������
//*****************************************************************************
void CPause::Uninit()
{

}

//*****************************************************************************
//				�X�V����
//*****************************************************************************
void CPause::Update()
{
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
	{	// W ���́@���L�[���������ꍇ
		m_nNum = (m_nNum + 2) % POLYGON_PAUSE;
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
	{	// S ���́@���L�[���������ꍇ
		m_nNum = (m_nNum + 1) % POLYGON_PAUSE;
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
	{
		if (m_nNum == 0)
		{	// �|�[�Y����
			CGame::SetPause(false);
		}
		else if (m_nNum == 1)
		{	// �Q�[����ʂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				if (CGame::GetStage() == CGame::STAGE_001)
				{//	�X�e�[�W1�������ꍇ
					CFade::Create(CManager::MODE_GAME001, CFade::FADE_OUT, 0);
				}
			}
		}
		else if (m_nNum == 2)
		{	//�@�^�C�g����ʂ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT,0);
			}
		}
	}
}

//*****************************************************************************
//				�`�揈��
//*****************************************************************************
void CPause::Draw()
{

}
