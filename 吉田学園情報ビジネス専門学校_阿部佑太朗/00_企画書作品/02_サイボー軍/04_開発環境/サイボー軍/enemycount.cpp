//=============================================================================
//
//	�G�l�~�[���̃J�E���g�̏��� [time.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "enemycount.h"
#include "enemy.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
CNumber *CEnemycount::m_apNumber[MAX_ENEMYCOUNT] = {};		//	�G�l�~�[���̃J�E���g�̃|�C���^�^�ϐ�������
int CEnemycount::m_nEnemyCount = NULL;						//	�G�l�~�[���̃J�E���g�ϐ�������

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemycount::CEnemycount() :CScene(3)
{
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemycount::~CEnemycount()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemycount::Init(void)
{
	m_nEnemyCount = 0;
	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{//	�ԍ��̐���
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(400.0f + (nCount * 30), 47.0f, 0.0f), D3DXVECTOR3(17.0f, 17.0f, 0.0f));
	}



	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CEnemycount::Uninit(void)
{
	if (m_apNumber != NULL)
	{
		for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
		{//�����̊J��
			m_apNumber[nCount]->Uninit();
		}
	}
	//�������g�̊J��
	Release();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CEnemycount::Update(void)
{
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemycount::Draw(void)
{
	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{//	�ԍ��̕`��
		m_apNumber[nCount]->Draw();
	}
}

//==============================================================================
//	�^�C�}�[�̐�������
//==============================================================================
CEnemycount *CEnemycount::Create(void)
{
	CEnemycount *pEnemyCount = {};

	if (pEnemyCount == NULL)
	{
		pEnemyCount = new CEnemycount;

		if (pEnemyCount != NULL)
		{
			pEnemyCount->Init();
		}
		else
		{
		}
	}
	return pEnemyCount;
}

//==============================================================================
//	�^�C�}�[�̎擾
//==============================================================================
int  CEnemycount::GetTime(void)
{
	return m_nEnemyCount;
}

//==============================================================================
//	�^�C�}�[�̎擾
//==============================================================================
void  CEnemycount::AddEnemyCount(int nValue)
{
	int aNumber[MAX_ENEMYCOUNT];

	m_nEnemyCount += nValue;

	aNumber[0] = m_nEnemyCount % 1000 / 100;
	aNumber[1] = m_nEnemyCount % 100 / 10;
	aNumber[2] = m_nEnemyCount % 10 / 1;

	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{
		m_apNumber[nCount]->SetNumber(aNumber[nCount]);
	}
}