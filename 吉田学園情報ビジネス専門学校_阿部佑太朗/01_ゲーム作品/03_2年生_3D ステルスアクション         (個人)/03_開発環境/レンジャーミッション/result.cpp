//**************************************************************
//
//		���U���g�̏���[result.cpp]
//		Auther : YUTARO ABE
//
//**************************************************************
#include "scene2d.h"		// �V�[��2D
#include "result.h"			// ���U���g
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "fade.h"			// �t�F�[�h
#include "input.h"			// ����
#include "scene.h"			// �V�[��
#include "UI.h"				// UI
#include "sound.h"			// �T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
//		�R���X�g���N�^
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
//		�f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
//		����������
//=============================================================================
HRESULT CResult::Init(GAMESTATE GameState)
{
	if (GAMESTATE_OVER == GameState)
	{//	�Q�[���I�[�o�[�������ꍇ
		m_rGameState = GAMESTATE_OVER;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_OVER);
		//  Ui�̓ǂݍ���
		CUI::Load(CManager::MODE_OVER);
		//	UI�̐���
		CUI::CreateMode(CManager::MODE_OVER);
	}
	else if (GAMESTATE_CLEAR == GameState )
	{//	�Q�[���N���A�������ꍇ
		m_rGameState = GAMESTATE_CLEAR;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_CLEAR);
		//  Ui�̓ǂݍ���
		CUI::Load(CManager::MODE_CLEAR);
		//	UI�̐���
		CUI::CreateMode(CManager::MODE_CLEAR);
	}


	return S_OK;
}

//=============================================================================
//		�I������
//=============================================================================
void CResult::Uninit(void)
{
	CUI::Unload();			//   Ui�̊J��

	CScene::ReleaseMode();	// ���[�h�I��

	//	�����~�߂�
	CSound::StopSound(CSound::SOUND_LABEL_BGM_CLEAR);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_OVER);
}

//=============================================================================
//		�X�V����
//=============================================================================
void CResult::Update(void)
{

	if (m_rGameState == GAMESTATE_CLEAR)
	{//	�Q�[���N���A�������ꍇ
#ifdef _DEBUG
	CManager::m_CDebugProcLeft->Print("\n���݂̃��[�h�y�@�N���A�@�z");
#endif // _DEBUG
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT,1);
			}
		}
	}
	else if (m_rGameState == GAMESTATE_OVER)
	{
#ifdef _DEBUG
		CManager::m_CDebugProcLeft->Print("\n���݂̃��[�h�y�@�I�[�o�[�@�z");
#endif // _DEBUG

		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				CFade::Create(CManager::MODE_SELECTMODE, CFade::FADE_OUT, 0);
			}
		}
	}

}

//=============================================================================
//		�`�揈��
//=============================================================================
void CResult::Draw(void)
{

}