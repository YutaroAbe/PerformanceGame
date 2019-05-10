//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "game.h"			//	�Q�[��
#include "manager.h"		//	�}�l�[�W���[
#include "renderer.h"		//	�����_���[
#include "input.h"			//	����
#include "camera.h"			//	�J����
#include "fade.h"			//	�t�F�[�h
#include "player.h"			//	�v���C���[
#include "block.h"			//	�u���b�N
#include "item.h"			//	�A�C�e��
#include "time.h"			//	�^�C��
#include "effect.h"			//	�G�t�F�N�g
#include "item.h"			//	�A�C�e��
#include "3dobject.h"		//	3D�w�i�I�u�W�F�N�g
#include "floor.h"			//	��
#include "shadow.h"			//	�e
#include "UI.h"				//	Ui
#include "number.h"			//	�ԍ�
#include "score.h"			//	�X�R�A
#include "wall.h"			//	��
#include "bulletNumber.h"	//	���C�t�̐��l
#include "effect.h"			//	�G�t�F�N�g
#include "bullet3D.h"		//	�e3D
#include "enemy.h"			//	�G
#include "hpber3D.h"		//�@HP�o�[3D
#include "bullet2D.h"		//	�e��2D
#include "pause.h"			//	Pause
#include "sound.h"			//	��
#include <iostream>
#include <string>

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
CPlayer *CGame::m_pPlayer = NULL;
CFloor *CGame::m_pFloor[MAX_FLOOR] = {};
CEnemy *CGame::m_pEnemy = NULL;
CPause *CGame::m_pPause = NULL;
bool CGame::m_bPause = false;
CGame::STAGETYPE  CGame::m_StageType = STAGE_NONE;		//	�X�e�[�W���
CGame::GAMESTATE CGame::m_GameState = GAMESTATE_NONE;	//	�Q�[���̃X�e�[�^�X
int CGame::m_nOverNum = 0;								//	�Q�[���I�[�o�[�̑I������
bool CGame::m_bClear = false;							//	�N���A�������ǂ���
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_pPlayer = NULL;										//	�v���C���[
	for (int nCount = 0; nCount < MAX_FLOOR; nCount++)
	{//	��
		m_pFloor[nCount] = NULL;
	}

	for (int nCountb = 0; nCountb < OBJTYPE_MAX; nCountb++)
	{//	�e�L�X�g�̃I�u�W�F�N�g�̎��
		m_textState[nCountb].nCnter = NULL;
		for (int nCount = 0; nCount < OBJ_MAX; nCount++)
		{//	�e�L�X�g�̒��g�̏�����
			m_textState[nCountb].nType[nCount] = NULL;		//	���
			m_textState[nCountb].nColType[nCount] = NULL;	//	�����蔻��̎��
			m_textState[nCountb].pos[nCount] = {};			//	�ʒu
			m_textState[nCountb].rot[nCount] = {};			//	��]
			m_textState[nCountb].size[nCount] = {};			//	�傫��
			m_textState[nCountb].pVtxFloor[nCount] = {};	//	���̒��_�̍���
			m_textState[nCountb].col[nCount] = {};			//	�F
			m_textState[nCountb].uv[nCount] = {};			//	UV
			m_textState[nCountb].nColType[nCount] = {};		//	�����蔻��̎��
			m_textState[nCountb].nLife[nCount] = {};		//	���
			m_textState[nCountb].nAIType[nCount] = {};		//	AI�̎��
			m_textState[nCountb].nMoveLength[nCount] = {};	//	��������
			m_textState[nCountb].fNoneSpeed[nCount] = {};	//	�I�u�W�F�N�g�̒ʏ�̑���
			m_textState[nCountb].fFomSpeed[nCount] = {};	//	�I�u�W�F�N�g�̒Ǐ]����Ƃ��̑���
		}
	}
	m_GameState = GAMESTATE0_NORMAL;	//	�Q�[���̏��
	m_nCounterState = 0;				//	�J�E���^�[�̏�����
	m_StageType = STAGE_TUTORIAL;		//	�X�e�[�W�̐ݒ�
	m_bClear = false;					//	�N���A�������ǂ���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(STAGETYPE StageType, int nPlayerLife)
{
	//	�G�t�F�N�g�̃e�L�X�g�̖��O�̓ǂݍ���
	CEffect::LoadNameEffect();			//	�G�t�F�N�g�̃e�L�X�g�ǂݍ���
	CEffect::LoadDataEffect();			//	�G�t�F�N�g�̃f�[�^�ǂݍ���
	CEffect::Load();					//	�G�t�F�N�g�̓ǂݍ���
	CPlayer::Load();					//	�v���C���[�̓ǂݍ���
	CEnemy::Load();						//	�v���C���[�̓ǂݍ���
	CItem::Load();						//	�A�C�e����
	CBlock::Load();						//	�u���b�N�̓ǂݍ���
	C3Dobject::Load();					//	3D�I�u�W�F�N�g�̓ǂݍ���
	CFloor::Load();						//	���̓ǂݍ���
	CShadow::Load();					//	�e�̓ǂݍ���
	CNumber::Laod();					//	���̓ǂݍ���
	CWall::Load();						//	�ǂ̓ǂݍ���
	CBullet3D::Load();					//	�e3D�̓ǂݍ���
	CHpBer3D::Load();					//	HP�o�[�̓ǂݍ���
	CBullet2D::Load();					//	�e��2D�̓ǂݍ���
	m_StageType = StageType;
	switch (m_StageType)
	{
		//-----------------------------------------------------------
		//	�`���[�g���A���X�e�[�W
		//------------------------------------------------------------
	case STAGE_TUTORIAL:
		CUI::Load(CManager::MODE_GAMETUTO);				//  Ui�̓ǂݍ���
		ObjectLoad(STAGE_TUTORIAL);						//	�e�L�X�g�ǂݍ���
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -1650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300,80);
		CUI::CreateMode(CManager::MODE_GAMETUTO);		//UI�̐���
		break;
		//-----------------------------------------------------------
		//	�X�e�[�W	1
		//------------------------------------------------------------
	case STAGE_001:
		CUI::Load(CManager::MODE_GAMESTAGE000);			//  Ui�̓ǂݍ���
		ObjectLoad(STAGE_001);							//	�e�L�X�g�ǂݍ���
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE000);	//UI�̐���
		break;
		//-----------------------------------------------------------
		//	�X�e�[�W	2
		//------------------------------------------------------------
	case STAGE_002:
		CUI::Load(CManager::MODE_GAMESTAGE000);			//  Ui�̓ǂݍ���
		ObjectLoad(STAGE_002);							//	�e�L�X�g�ǂݍ���
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE000);	//UI�̐���
		break;
		//-----------------------------------------------------------
		//	�X�e�[�W	3
		//------------------------------------------------------------
	case STAGE_003:
		CUI::Load(CManager::MODE_GAMESTAGE002);			//  Ui�̓ǂݍ���
		ObjectLoad(STAGE_003);							//	�e�L�X�g�ǂݍ���
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE002);	//UI�̐���
		break;
	}
	//�e�̐���
	CBulletNumber::Create();

	for (int nCount = 0; nCount < m_textState[OBJTYPE_ENEMY].nCnter; nCount++)
	{//	�G�ݒ�	�ʒu�@��]�@�����@��ށ@�Ǐ]�͈́@�����͈� �I�u�W�F�N�g�̒ʏ�̑��� �I�u�W�F�N�g�̒Ǐ]����Ƃ��̑����@�G�̓����̎��
		m_pEnemy = CEnemy::Create
		(m_textState[OBJTYPE_ENEMY].pos[nCount], m_textState[OBJTYPE_ENEMY].rot[nCount], m_textState[OBJTYPE_ENEMY].nLife[nCount],
			m_textState[OBJTYPE_ENEMY].nType[nCount], m_textState[OBJTYPE_ENEMY].nMoveLength[nCount], m_textState[OBJTYPE_ENEMY].fNoneSpeed[nCount],
			m_textState[OBJTYPE_ENEMY].fFomSpeed[nCount],(CEnemy::ENEMY_AI)m_textState[OBJTYPE_ENEMY].nAIType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_ITEM].nCnter; nCount++)
	{//	�A�C�e���̐ݒ�	�ʒu�@��]�@�傫���@�F�@UV�@���
		CItem::Create
		(m_textState[OBJTYPE_ITEM].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[OBJTYPE_ITEM].size[nCount],
			m_textState[OBJTYPE_ITEM].col[nCount], m_textState[OBJTYPE_ITEM].uv[nCount], m_textState[OBJTYPE_ITEM].nType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_BLOCK].nCnter; nCount++)
	{//	�u���b�N�̐ݒ�@�ʒu�@��]�@�傫���@��ށ@�@�����蔻��̎��
		CBlock::Create
		(m_textState[OBJTYPE_BLOCK].pos[nCount],
			D3DXVECTOR3(m_textState[OBJTYPE_BLOCK].rot[nCount].x, D3DX_PI*m_textState[OBJTYPE_BLOCK].rot[nCount].y, m_textState[OBJTYPE_BLOCK].rot[nCount].z),
			m_textState[OBJTYPE_BLOCK].size[nCount], (CBlock::MODELTYPE)m_textState[OBJTYPE_BLOCK].nType[nCount], (CBlock::COLTYPE)m_textState[OBJTYPE_BLOCK].nColType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_3DPORI].nCnter; nCount++)
	{//	3D�|���S���̐ݒ�	�ʒu�@��]�@�傫���@�F�@UV�@���
		C3Dobject::Create
		(m_textState[OBJTYPE_3DPORI].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[OBJTYPE_3DPORI].size[nCount],
			m_textState[OBJTYPE_3DPORI].col[nCount], m_textState[OBJTYPE_3DPORI].uv[nCount], m_textState[OBJTYPE_3DPORI].nType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_FLOOR].nCnter; nCount++)
	{//	���ݒ�	�ʒu�@��]�@�傫���@���_�̍����@�F�@UV�@���
		CFloor::Create
		(m_textState[OBJTYPE_FLOOR].pos[nCount], D3DXVECTOR3(0.0f, 0.0f,0.0f), m_textState[OBJTYPE_FLOOR].size[nCount],
			m_textState[OBJTYPE_FLOOR].col[nCount], m_textState[OBJTYPE_FLOOR].uv[nCount], m_textState[OBJTYPE_FLOOR].nType[nCount], (CFloor::COLTYPE)m_textState[OBJTYPE_FLOOR].nColType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_WALL].nCnter; nCount++)
	{//	�ǐݒ�	�ʒu�@��]�@�傫���@�F�@UV�@���
		CWall::Create
		(m_textState[OBJTYPE_WALL].pos[nCount], D3DXVECTOR3(0.0f, D3DX_PI*m_textState[OBJTYPE_WALL].rot[nCount].y, 0.0f), m_textState[OBJTYPE_WALL].size[nCount],
			m_textState[OBJTYPE_WALL].col[nCount], m_textState[OBJTYPE_WALL].uv[nCount], m_textState[OBJTYPE_WALL].nType[nCount]);
	}

	m_bPause = false;
	m_nOverNum = 0;						//	�Q�[���I�[�o�[�̑I������
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	CEnemy::UnLoad();			//	�G�̊J��
	CItem::Unload();			//	�A�C�e���̊J��
	CBlock::Unload();			//	�u���b�N�̊J��
	C3Dobject::Unload();		//	3D�|���S���̊J��
	CFloor::Unload();			//	���̊J��
	CShadow::Unload();			//	�e�̊J��
	CUI::Unload();				//  Ui�̊J��
	CNumber::UnLoad();			//�@�����̃e�N�X�`���J��
	CWall::Unload();			//	�ǂ̔j��
	CBullet3D::Unload();		//	�e3D�̔j��
	CEffect::Unload();			//	�G�t�F�N�g�̊J��
	CPlayer::UnLoad();			//	�v���C���[�̊J��
	CHpBer3D::Unload();			//	Hp�o�[�[�̊J��
	CBullet2D::Unload();		//	�e��2D�̓ǂݍ���

	if (m_pPause != NULL)
	{//	�|�[�Y�̔j��
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	CScene::ReleaseMode();		// ���[�h�I��

}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CSound *pSound = CManager::GetSound();	//	�T�E���h�̎擾

	switch (m_GameState)
	{
	case GAMESTATE0_NORMAL:
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_START, 0) == true)
			{//�L�[�{�[�h�iP�j��������
				m_bPause = m_bPause ? false : true;		// �g�p�؂�ւ�
				if (m_bPause == true)
				{// �g�p����
					if (m_pPause == NULL)
					{// NULL�̏ꍇ
					 // �|�[�Y����
						m_pPause = new CPause;
						if (m_pPause != NULL)
						{
							m_pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
						}
					}
					if (m_pPause != NULL)
					{
						// �X�V�͈͂��|�[�Y����
						CScene::SetStartUp(CScene::PRIORITY_PAUSE);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);	//	SE�炷
					}
				}
				else
				{// ���̑�
					if (m_pPause != NULL)
					{// NULL�ȊO�̏ꍇ
						m_pPause->Uninit();		// �I������
						delete m_pPause;		// �������J��
						m_pPause = NULL;		// NULL��
					}
					CScene::SetStartUp(0);
				}
			}
			if (m_pPause != NULL && m_bPause == true)
			{// NULL�ȊO�̏ꍇ
				m_pPause->Update();		// �|�[�Y�X�V
			}
		}
		if (m_pPlayer->GetDisp() == true)
		{//	�v���C���[���S���Ȃ����ꍇ
			m_GameState = GAMESTATE_END;
		}

		break;
	case GAMESTATE_END:
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{//	�w��̒l�𒴂����ꍇ
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
				|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{	// W ���́@���L�[���������ꍇ
				m_nOverNum = (m_nOverNum + 1) % 2;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			}
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
				|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
			{	// S ���́@���L�[���������ꍇ
				m_nOverNum = (m_nOverNum + 1) % 2;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			}
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PRESS);	//	���艹
				if (m_nOverNum == 0)
				{//	��蒼��
					if (CFade::GetFade() == CFade::FADE_NONE)
					{//	�������Ă��Ȃ��t�F�C�h�������ꍇ
						if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
						{//	�`���[�g���A���������ꍇ
							CFade::Create(CManager::MODE_GAMETUTO, CFade::FADE_OUT,0);
						}
						else if (CGame::GetStage() == CGame::STAGE_001)
						{//	�X�e�[�W1�������ꍇ
							CFade::Create(CManager::MODE_GAMESTAGE000, CFade::FADE_OUT, 0);
						}
						else if (CGame::GetStage() == CGame::STAGE_002)
						{//	�X�e�[�W2�������ꍇ
							CFade::Create(CManager::MODE_GAMESTAGE001, CFade::FADE_OUT, 1);
						}
						else if (CGame::GetStage() == CGame::STAGE_003)
						{//	�X�e�[�W2�������ꍇ
							CFade::Create(CManager::MODE_GAMESTAGE002, CFade::FADE_OUT, 1);
						}
					}
				}
				else if (m_nOverNum == 1)
				{	//�@�^�C�g����ʂ�
					if (CFade::GetFade() == CFade::FADE_NONE)
					{//	�������Ă��Ȃ��t�F�C�h�������ꍇ
						CFade::Create(CManager::MODE_OVER, CFade::FADE_OUT, 0);
					}
				}
			}
		}
		break;
	case GAMESTATE_CLEAR:
		CScene::SetStartUp(CScene::PRIORITY_PAUSE);
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{//	�w��̒l�𒴂����ꍇ
			if (CFade::GetFade() == CFade::FADE_NONE)
			{// �t�F�[�h���Ă��Ȃ����
				if (m_StageType == STAGE_TUTORIAL)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE000, CFade::FADE_OUT, 0);
				}
				else if (m_StageType == STAGE_001)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE001, CFade::FADE_OUT, 1);
				}
				else if (m_StageType == STAGE_002)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE002, CFade::FADE_OUT, 1);
				}
				else if (m_StageType == STAGE_003)
				{
					m_bClear = true;	//	�Q�[���N���A����
					if (CUI::GetNumTxst() > 5)
					{//	�����̃e�L�X�g���l���i�񂾏ꍇ
						CScene::SetStartUp(0);
						CFade::Create(CManager::MODE_CLEAR, CFade::FADE_OUT, 1);
					}
				}
			}
		}
		break;
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	if (m_pPause != NULL)
	{// NULL�ȊO�̏ꍇ
		m_pPause->Draw();	// �|�[�Y�`��
	}
}

//=============================================================================
// �e�L�X�g�ǂݍ���
//=============================================================================
void CGame::ObjectLoad(STAGETYPE stage)
{
	FILE *pFile;
	char read[128];										//	�ǂݍ��ޕ�����
	char *txstName[STAGE_MAX][OBJTYPE_MAX][128] = {};	//	�ǂݍ��ރe�L�X�g�̃t�@�C��

	if (stage == STAGE_TUTORIAL)
	{//	�`���[�g���A��
		txstName[STAGE_TUTORIAL][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_TUTO/ItemSet.txt";		//	�X�e�[�W1�̃A�C�e��
		txstName[STAGE_TUTORIAL][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_TUTO/BlockSet.txt";	//	�X�e�[�W1�u���b�N
		txstName[STAGE_TUTORIAL][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_TUTO/3DPorSet.txt";	//	�X�e�[�W1D�|���S���r���{�[�h
		txstName[STAGE_TUTORIAL][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_TUTO/FloorSet.txt";	//	�X�e�[�W1D�|���S����
		txstName[STAGE_TUTORIAL][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_TUTO/WallSet.txt";		//	�X�e�[�W1D�|���S����
		txstName[STAGE_TUTORIAL][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_TUTO/EnemySet.txt";	//	�X�e�[�W1D�|���S���G
	}
	else if (stage == STAGE_001)
	{//	�X�e�[�W1
		txstName[STAGE_001][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_000/ItemSet.txt";		//	�X�e�[�W1�̃A�C�e��
		txstName[STAGE_001][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_000/BlockSet.txt";		//	�X�e�[�W1�u���b�N
		txstName[STAGE_001][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_000/3DPorSet.txt";		//	�X�e�[�W1D�|���S���r���{�[�h
		txstName[STAGE_001][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_000/FloorSet.txt";		//	�X�e�[�W1D�|���S����
		txstName[STAGE_001][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_000/WallSet.txt";		//	�X�e�[�W1D�|���S����
		txstName[STAGE_001][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_000/EnemySet.txt";		//	�X�e�[�W1D�|���S���G
	}
	else if (stage == STAGE_002)
	{//	�X�e�[�W2
		txstName[STAGE_002][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_001/ItemSet.txt";		//	�X�e�[�W2�̃A�C�e��
		txstName[STAGE_002][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_001/BlockSet.txt";		//	�X�e�[�W2�u���b�N
		txstName[STAGE_002][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_001/3DPorSet.txt";		//	�X�e�[�W2D�|���S���r���{�[�h
		txstName[STAGE_002][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_001/FloorSet.txt";		//	�X�e�[�W2D�|���S����
		txstName[STAGE_002][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_001/WallSet.txt";		//	�X�e�[�W2D�|���S����
		txstName[STAGE_002][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_001/EnemySet.txt";		//	�X�e�[�W2D�|���S���G
	}
	else if (stage == STAGE_003)
	{//	�X�e�[�W3
		txstName[STAGE_003][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_002/ItemSet.txt";		//	�X�e�[�W3�̃A�C�e��
		txstName[STAGE_003][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_002/BlockSet.txt";		//	�X�e�[�W3�u���b�N
		txstName[STAGE_003][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_002/3DPorSet.txt";		//	�X�e�[�W3D�|���S���r���{�[�h
		txstName[STAGE_003][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_002/FloorSet.txt";		//	�X�e�[�W3D�|���S����
		txstName[STAGE_003][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_002/WallSet.txt";		//	�X�e�[�W3D�|���S����
		txstName[STAGE_003][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_002/EnemySet.txt";		//	�X�e�[�W3D�|���S���G
	}

	//-------------------------------------�A�C�e��--------------------------------------------
	//	�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_ITEM][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "ITEM_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].y, &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	�傫���̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].y, &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].z);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_ITEM].nType[m_textState[OBJTYPE_ITEM].nCnter]);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].r, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].g, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].b, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_ITEM].uv[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].uv[m_textState[OBJTYPE_ITEM].nCnter].y);
				}
			} while (strcmp(&read[0], "ITEM_END") != 0);
			//	�ǂݍ��񂾃A�C�e���̐����Z
			m_textState[OBJTYPE_ITEM].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		//	�e�L�X�g���߂�
		fclose(pFile);
	}
	//-------------------------------------�u���b�N-------------------------------------------
	//	�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_BLOCK][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "BLOCK_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT") == 0)
				{//	��]�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	�傫���̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "MODELTYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_BLOCK].nType[m_textState[OBJTYPE_BLOCK].nCnter]);
				}
				else if (strcmp(&read[0], "COLTYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_BLOCK].nColType[m_textState[OBJTYPE_BLOCK].nCnter]);
				}
			} while (strcmp(&read[0], "BLOCK_END") != 0);
			//	�ǂݍ��񂾃��f���̐����Z
			m_textState[OBJTYPE_BLOCK].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------3D�|���S��-------------------------------------------
	//	�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_3DPORI][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "3DPORIGON_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].y, &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].y, &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].z);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_3DPORI].nType[m_textState[OBJTYPE_3DPORI].nCnter]);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].r, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].g, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].b, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_3DPORI].uv[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].uv[m_textState[OBJTYPE_3DPORI].nCnter].y);
				}
			} while (strcmp(&read[0], "3DPORIGON_END") != 0);
			//	�ǂݍ��񂾃��f���̐����Z
			m_textState[OBJTYPE_3DPORI].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------��-------------------------------------------
	//�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_FLOOR][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "FLOOR_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].y, &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	�傫���̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].y, &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].z);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].r, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].g, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].b, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].uv[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].uv[m_textState[OBJTYPE_FLOOR].nCnter].y);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_FLOOR].nType[m_textState[OBJTYPE_FLOOR].nCnter]);
				}
				else if (strcmp(&read[0], "COLTYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_FLOOR].nColType[m_textState[OBJTYPE_FLOOR].nCnter]);
				}
			} while (strcmp(&read[0], "FLOOR_END") != 0);
			//	�ǂݍ��񂾃��f���̐����Z
			m_textState[OBJTYPE_FLOOR].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------��-------------------------------------------
	//	�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_WALL][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "WALL_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].y, &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT_Y") == 0)
				{//	Y��]�̐ݒ�4
					fscanf(pFile, "%s%f",
						&read[0], &m_textState[OBJTYPE_WALL].rot[m_textState[OBJTYPE_WALL].nCnter].y);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	�傫���̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].y, &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].z);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].r, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].g, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].b, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	�傫���̐ݒ�4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].uv[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].uv[m_textState[OBJTYPE_WALL].nCnter].y);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_WALL].nType[m_textState[OBJTYPE_WALL].nCnter]);
				}


			} while (strcmp(&read[0], "WALL_END") != 0);
			//	�ǂݍ��񂾃��f���̐����Z
			m_textState[OBJTYPE_WALL].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}

	//-------------------------------------�G-------------------------------------------
	//	�ǂݍ��ރe�L�X�g
	pFile = fopen(txstName[stage][OBJTYPE_ENEMY][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "ENEMY_SET") == 0)
		{//	�����񂪓ǂݍ��܂�Ă����ꍇ
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	�ʒu�̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].x, &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].y, &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT") == 0)
				{//	�����̐ݒ�
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].x, &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].y, &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].z);
				}
				else if (strcmp(&read[0], "LIFE") == 0)
				{//	�̗͂̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nLife[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	��ނ̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nType[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "MOVELENGTH") == 0)
				{//	���������̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nMoveLength[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "NONESPEED") == 0)
				{//	�ʏ�̑���
					fscanf(pFile, "%s%3f",
						&read[0], &m_textState[OBJTYPE_ENEMY].fNoneSpeed[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "FOMSPEED") == 0)
				{//	�Ǐ]����Ƃ��̑���
					fscanf(pFile, "%s%3f",
						&read[0], &m_textState[OBJTYPE_ENEMY].fFomSpeed[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "AITYPE") == 0)
				{//	AI�̎�ނ̐ݒ�
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nAIType[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
			} while (strcmp(&read[0], "ENEMY_END") != 0);
			//	�ǂݍ��񂾃��f���̐����Z
			m_textState[OBJTYPE_ENEMY].nCnter++;
			//	���̕�����ǂݍ���
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
}
//=============================================================================
// �|�[�Y�ݒ�
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;		// �|�[�Y�؂�ւ�

	if (m_bPause == true)
	{// �g�p����
		if (m_pPause == NULL)
		{// NULL�̏ꍇ
		 // �|�[�Y����
			m_pPause = new CPause;	// �������m��
			m_pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
		// �X�V�͈͂��|�[�Y����
		CScene::SetStartUp(CScene::PRIORITY_PAUSE);
	}
	else if(m_bPause == false)
	{// ���̑�
		if (m_pPause != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pPause->Uninit();		// �I������
			delete m_pPause;		// �������J��
			m_pPause = NULL;		// NULL��
		}
		// �X�V�͈͂�߂�
		CScene::SetStartUp(0);
	}
}