//=============================================================================
//
//	���C�t�ɐ��l�̏��� [LifeNUmber.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "bulletNumber.h"
#include "number.h"
#include "game.h"
#include "player.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
CNumber *CBulletNumber::m_apNumber[MAX_LIFENUMBER] = {};
int CBulletNumber::m_nNumber = NULL;

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CBulletNumber::CBulletNumber() :CScene(PRIORITY_UI, OBJTYPE_LIFENUMBER)
{

}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CBulletNumber::~CBulletNumber()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CBulletNumber::Init(void)
{
	m_nNumber = 0;
	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{//	�ԍ��̐���
		if (nCount == 0 || nCount == 1)
		{
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3((SCREEN_WIDTH - 130.0f) + (nCount * 35), (SCREEN_HEIGHT - 40.0f), 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f));
		}
	}

	AddNum(CGame::GetPlayer()->GetBltNum());				//	�����̃��C�t�̐��l�ݒ�
	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CBulletNumber::Uninit(void)
{
	if (m_apNumber != NULL)
	{
		for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
		{//�����̊J��
			m_apNumber[nCount]->Uninit();
		}
	}
	//�������g�̊J��
	CScene::SetDeath();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CBulletNumber::Update(void)
{
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CBulletNumber::Draw(void)
{
	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{//	�ԍ��̕`��
		m_apNumber[nCount]->Draw();
	}
}

//==============================================================================
//	�X�R�A�̐�������
//==============================================================================
CBulletNumber *CBulletNumber::Create(void)
{
	CBulletNumber *pBuletNum = {};

	if (pBuletNum == NULL)
	{//	�������m��
		pBuletNum = new CBulletNumber;

		if (pBuletNum != NULL)
		{//	�������m�ۏo������
			pBuletNum->Init();				//	�̏���������
		}
	}
	return pBuletNum;
}

//==============================================================================
//	�擾
//==============================================================================
int  CBulletNumber::GetLefeNum(void)
{
	return m_nNumber;
}

//==============================================================================
//	�ݒ�
//==============================================================================
void  CBulletNumber::AddNum(int nValue)
{
	int aNumber[MAX_LIFENUMBER];

	m_nNumber += nValue;

	aNumber[0] = m_nNumber % 100 / 10;
	aNumber[1] = m_nNumber % 10 / 1;


	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(aNumber[nCount]);
	}
}