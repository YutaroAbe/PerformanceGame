//=============================================================================
//
// �Q�[������ [main.cpp]
// Author :
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "game.h"
#include "life.h"
#include "time.h"
#include "fade.h"
#include "block.h"
#include "item.h"
#include "pause.h"
#include "input.h"
#include "missionmessage.h"
#include "enemycount.h"

//=============================================================================
//�ÓI�����o�ϐ�������
//=============================================================================
CGame::GAMESTATE CGame::m_GameState = GAMESTATE_NONE;
CGame::SETSTEGEMODE CGame::m_SetStageMode = SETSTEGEMODE_001;
CPlayer *CGame::m_pPlayer = NULL;							//	�v���C���[�̏�����
bool CGame::m_bPause = false;								//	�|�[�Y�̏�Ԃ̏�����
int CGame::m_nEnemyCount = NULL;							//	�G�̐��̏�����
D3DXVECTOR3 CGame::m_EnemyPos[EMEMY_NUM_MAX] = {};			//	�G�̃|�W�V�����̏�����
int CGame::m_nEnemyType[EMEMY_NUM_MAX] = {};				//	�G�̎�ނ̏�����
int CGame::m_nEnemyLife[EMEMY_NUM_MAX] = {};				//	�G�̎�ނ̏�����
int CGame::m_nItemCount = NULL;								//	�A�C�e���̏�����
D3DXVECTOR3 CGame::m_ItemPos[ITEM_NUM_MAX] = {};			//	�A�C�e���̃|�W�V�����̏�����
int CGame::m_nItemType[ITEM_NUM_MAX] = {};					//	�A�C�e���̎�ނ̏�����
int CGame::m_nBlockCount = NULL;							//	�u���b�N�̏�����
D3DXVECTOR3 CGame::m_BlockPos[ITEM_NUM_MAX] = {};			//	�u���b�N�̃|�W�V�����̏�����
int CGame::m_nBlockType[ITEM_NUM_MAX] = {};					//	�u���b�N�̎�ނ̏�����
float CGame::m_fBlockfWindth[BLOCK_NUM_MAX] = {};			//	�u���b�N�̕�
float CGame::m_fBlockfHeight[BLOCK_NUM_MAX] = {};			//	�u���b�N�̍���
float CGame::m_fBlockTexSplitX[BLOCK_NUM_MAX] = {};			//	�u���b�N�̃e�N�X�`���̕�����X��
float CGame::m_fBlockTexSplitY[BLOCK_NUM_MAX] = {};			//	�u���b�N�̃e�N�X�`���̕�����Y��

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_nCounterState = NULL;
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	switch (m_SetStageMode)
	{
	case SETSTEGEMODE_000:
		LoadSetTutorial();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;
	case SETSTEGEMODE_001:
		LoadSetGame();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_STAGE1);
		break;
	case SETSTEGEMODE_002:
		LoadSetGameStage2();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_STAGE2);
		break;
	}
	//�@�G�t�F�N�g�̃e�N�X�`���̊J��
	CEffect::Laod();
	//	�t�F�C�h�̃e�N�X�`���̓ǂݍ���
	CFade::Laod();
	//	�����̃e�N�X�`���̓ǂݍ���
	CNumber::Laod();
	//	�u���b�N�̃e�N�X�`���ǂݍ���
	CBlock::Laod();
	//	�e�̃e�N�X�`���̓ǂݍ���
	CBullet::Laod();
	//	�����̃e�N�X�`���̓ǂݍ���
	CExplosion::Laod();
	//	�G�̃e�N�X�`���̓ǂݍ���
	CEnemy::Laod();
	//	�v���C���[�̃e�N�X�`���̓ǂݍ���
	CPlayer::Laod();
	//	�w�i�̃e�N�X�`���ǂݍ���
	CBg::Laod();
	//�@�̗͂̃e�N�X�`���ǂݍ���
	CLife::Laod();
	//	�A�C�e���̃e�N�X�`���ǂݍ���
	CItem::Laod();
	//	�|�[�Y�̃e�N�X�`���̓ǂݍ���
	CPause::Load();
	//�@�w�i�̐���
	CBg::Create();
	//	�X�R�A�̐���
	CScore::Create();

	//	�^�C�}�[�̐���
	CTime::Create();
	//	�v���C���[�̐���
	m_pPlayer->Create(D3DXVECTOR3(600.0f, 500.0f, 0.0f));
	//	���C�t�̐ݒ�
	CLife::Create(D3DXVECTOR3(90.0f, 44.0f, 0.0f), D3DXVECTOR3(11.8f, 13.8f, 0.0f));
	//	�G�l�~�[�̑���
	CEnemycount::Create();
	//	�G�̐���
	for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
	{
		CEnemy::Create(D3DXVECTOR3(m_EnemyPos[nCount].x, m_EnemyPos[nCount].y, m_EnemyPos[nCount].z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nEnemyLife[nCount], m_nEnemyType[nCount]);
	}

	//�A�C�e���̐���
	for (int nCount = 0; nCount < m_nItemCount; nCount++)
	{
		CItem::Create(D3DXVECTOR3(m_ItemPos[nCount].x, m_ItemPos[nCount].y, m_ItemPos[nCount].z), m_nItemType[nCount]);
	}
	//	�u���b�N�̐���
	for (int nCount = 0; nCount < m_nBlockCount; nCount++)
	{
		CBlock::Create(D3DXVECTOR3(m_BlockPos[nCount].x, m_BlockPos[nCount].y, m_BlockPos[nCount].z),
		m_fBlockfWindth[nCount], m_fBlockfHeight[nCount], m_nBlockType[nCount], m_fBlockTexSplitX[nCount], m_fBlockTexSplitY[nCount]);	//�ʒu/����/��/����/���/�e�N�X�`������X/�e�N�X�`������Y
	}
	//	PAUSE�̐���
	CPause::Create();

	//�|�[�Y�̏�Ԃ̏�����
	m_bPause = false;

	m_GameState = GAMESTATE0_NORMAL;
	m_nCounterState = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//	�v���C���[�̃e�N�X�`���̊J��
	CPlayer::UnLoad();
	//	�G�̃e�N�X�`���J��
	CEnemy::UnLoad();
	//	�����̃e�N�X�`���̊J��
	CExplosion::UnLoad();
	//	�e�̃e�N�X�`���̊J��
	CBullet::UnLoad();
	//�@�����̃e�N�X�`���J��
	CNumber::UnLoad();
	//	�w�i�̃e�N�X�`���̊J��
	CBg::UnLoad();
	//�@�G�t�F�N�g�̃e�N�X�`���̊J��
	CEffect::UnLoad();
	//�@�̗͂̃e�N�X�`���J��
	CLife::UnLoad();
	//	�u���b�N�̊J��
	CBlock::UnLoad();
	//	�A�C�e���̊J��
	CItem::UnLoad();
	//	�|�[�Y�̊J��
	CPause::UnLoad();
	//���ׂẴ|���S���̊J��
	CScene::ReleaseAll();

	CSound::StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_STAGE1);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_STAGE2);
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetGamePadTrigger(BUTTON_START)==true)
	{// �|�[�Y�� true false �؂�ւ���
		CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
		m_bPause = m_bPause ? false : true;
	}


	switch (m_GameState)
	{
	case GAMESTATE0_NORMAL:
		break;
	case GAMESTATE_END:
		m_nCounterState++;
		if (m_nCounterState >= 20)
		{
			m_GameState = GAMESTATE_NONE;
		}
		break;
	case GAMESTATE_CLEAR:
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{
			if (pFade->m_fade == pFade->FADE_NONE && m_SetStageMode != SETSTEGEMODE_000)
			{
				pFade->SetFade(CManager::MODE_RESULT);
			}
		}
		break;
	}

		int nNumEnemy = CEnemy::GetNUMENEMY();
		if (nNumEnemy <= 0)
		{//	�G�l�~�[�𑍐����|������Q�[���N���A
			m_GameState = GAMESTATE_CLEAR;
		}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_GameState;
}

//=============================================================================
//	�|�[�Y�̏�Ԃ̎擾
//=============================================================================
bool CGame::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
//	�|�[�Y�̏�Ԃ̐ݒ�
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;
}
//=============================================================================
//	�Q�[���̃I�u�W�F�N�g�̐ݒu
//=============================================================================
void CGame::LoadSetTutorial(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage0.txt", "r");

	if (pFile != NULL)
	{//	�t�@�C�����J�����ꍇ

	 //	���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// �G�l�~�[�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �A�C�e���̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �u���b�N�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	������@/�@���@/�@������
		}

		//	�G�l�~�[�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	�G�l�~�[�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�G�l�~�[�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�G�l�~�[�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	�G�l�~�[�̗̑͂̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	�A�C�e���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	�A�C�e���̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�A�C�e���̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�A�C�e���̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	�u���b�N�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	�u���b�N�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�u���b�N�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�u���b�N�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "�e�L�X�g�ɖ�肪����܂�", "�x��", MB_OK);
	}
}
//=============================================================================
//	�Q�[���̃I�u�W�F�N�g�̐ݒu
//=============================================================================
void CGame::LoadSetGame(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage1.txt", "r");

	if (pFile != NULL)
	{//	�t�@�C�����J�����ꍇ

		//	���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// �G�l�~�[�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �A�C�e���̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �u���b�N�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	������@/�@���@/�@������
		}

		//	�G�l�~�[�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++){fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); }}
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	�G�l�~�[�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�G�l�~�[�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�G�l�~�[�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	�G�l�~�[�̗̑͂̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	�A�C�e���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	�A�C�e���̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�A�C�e���̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�A�C�e���̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	�u���b�N�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	�u���b�N�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�u���b�N�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�u���b�N�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "�e�L�X�g�ɖ�肪����܂�", "�x��", MB_OK);
	}
}
//=============================================================================
//	�Q�[���̃I�u�W�F�N�g�̐ݒu
//=============================================================================
void CGame::LoadSetGameStage2(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage2.txt", "r");

	if (pFile != NULL)
	{//	�t�@�C�����J�����ꍇ

	 //	���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// �G�l�~�[�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �A�C�e���̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	������@/�@���@/�@������
		}
		// �u���b�N�̐��̐ݒ�
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	������@/�@���@/�@������
		}

		//	�G�l�~�[�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	�G�l�~�[�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�G�l�~�[�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�G�l�~�[�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	�G�l�~�[�̗̑͂̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	�A�C�e���̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	�A�C�e���̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�A�C�e���̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�A�C�e���̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	�u���b�N�̐ݒ�̃e�L�X�g��R�����g�A�E�g
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	�u���b�N�̐ݒ�
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	�u���b�N�̈ʒu�̐ݒ�
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	�u���b�N�̎�ނ̐ݒ�
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "�e�L�X�g�ɖ�肪����܂�", "�x��", MB_OK);
	}
}
//=============================================================================
//	�X�e�[�W�̑I��
//=============================================================================
void CGame::SetStage(SETSTEGEMODE SetStageMode)
{
	m_SetStageMode = SetStageMode;
}

//=============================================================================
//�X�e�[�W�̎擾
//=============================================================================
CGame::SETSTEGEMODE CGame::GetStageState(void)
{
	return m_SetStageMode;
}