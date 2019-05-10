//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author :�@YUUTAROU ABE
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include"player.h"
#include "bullet.h"
#include "input.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��̒�`
//=============================================================================
CScene *CScene::m_apScene[MAX_DROW][MAX_NUM] = {};			// �|���S���̏�����
int CScene::m_nNumAll = 0;									// �|���S�������̏�����
bool CScene::m_bPasue = false;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene::CScene()
{

}

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriarity)
{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{//	�|���S���̍ő吔��
			if (m_apScene[nPriarity][nCnt] == NULL)
			{//	�����Ȃ�������
			 //	������Ԃ�
				m_apScene[nPriarity][nCnt] = this;			//�@���������m�ۂ������������g�ɑ������
				m_nID = nCnt;//�@�ԍ��̑���w��
				m_nPriority = nPriarity;
				m_nNumAll++;								//�@���������Z
				m_object = OBJECT_NONE;
				break;
			}
		}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//  �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}

//=============================================================================
//  �I�u�W�F�N�g�̏I������
//=============================================================================
void CScene::Uninit(void)
{
}

//=============================================================================
//  �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
//  �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::Draw(void)
{
}

//=============================================================================
//	�S�Ă̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	m_bPasue = CGame::GetPause();

	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{//	�|���S���̍ő吔��
			if (m_bPasue == false)
			{
				if (nCntPriority != 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	�X�V����
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
			}
			else if (m_bPasue == true)
			{
				if (nCntPriority == 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	�X�V����
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
			}
		}
	}
}

//=============================================================================
//	�S�Ă̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	m_bPasue = CGame::GetPause();

	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{
			if (m_bPasue == false)
			{
				if (nCntPriority != 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	�`�揈��
						m_apScene[nCntPriority][nCnt]->Draw();
					}
				}
			}
			else if (m_bPasue == true)
			{
				if (m_apScene[nCntPriority][nCnt] != NULL)
				{
					//	�X�V����
					m_apScene[nCntPriority][nCnt]->Draw();
				}
			}
		}
	}
}

//=============================================================================
//	�S�Ă̏I������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++ )
		{
			//	�V�[���N���X�̔j��
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				// �I������
				m_apScene[nCntPriority][nCnt]->Uninit();
				//	�������̊J��
				delete m_apScene[nCntPriority][nCnt];
				//	NULL�ɂ���
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}
}

//=============================================================================
//	�I�u�V�F�N�g�̔j��
//=============================================================================
void CScene::Release(void)
{
	//	�V�[��2D�̔j��
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{//	�w�肵���ԍ����󂶂�Ȃ���������
		int nID;								//	�ۑ��悤�ϐ�
		int nPriority;
		nID = m_nID;							//	�������g�̔ԍ��̕ۑ�
		nPriority = m_nPriority;

		delete m_apScene[nPriority][nID];		//	�w�肵���ԍ��̃������̊J��//delete�������u��m_nID���s��ɂȂ�NULL�̑���ŃG���[���ł�

		m_apScene[nPriority][nID] = NULL;		//	�w�肵���ԍ�����ɂ���

		m_nNumAll--;							//	�w�肵���ԍ����̑��������炷
	}
}

//=============================================================================
//	�I�u�W�F�N�g�̎�ސݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE Objtype)
{
	m_object = Objtype;
}

//=============================================================================
//	�I�u�W�F�N�g�̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_object;
}

//=============================================================================
//	�I�u�W�F�N�g�̎擾
//=============================================================================
CScene * CScene::GetScene(int nPriarity, int nIndex)
{
	return m_apScene[nPriarity][nIndex];
}
//=============================================================================
//	�I�u�W�F�N�g�̎擾
//=============================================================================
int CScene::GetNumALL(void)
{
	return m_nNumAll;
}