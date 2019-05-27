//=============================================================================
//
//	�A�C�e���̏��� [item.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "item.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CItem::m_Texture[MAX_TEX_ITEM] = {};					//	�e�N�X�`���̏�����

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CItem::CItem() : CScene2D(3)
{
	 m_nType = NULL;																					//	���
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CItem::~CItem()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, int nType)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_BULLET);

	m_nType = nType;

	SetPosition(pos, ITEM_POLIGON_X, ITEM_POLIGON_Y);

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();															//	�e�̈ʒu
	D3DXVECTOR3 move = GetMoveing();															//	�e�̈ʒu

	D3DXVECTOR3 playermove = CPlayer::GetMove();

	if (playermove.x >= 0.1f)
	{
		move.x -= playermove.x;
	}
	else if (playermove.x <= -0.1f)
	{
		move.x += -playermove.x;
	}

	pos.x += move.x;
	pos.y += move.y;
	SetPosition(pos, ITEM_POLIGON_X, ITEM_POLIGON_Y);							//	�e�̈ʒu�Ƒ傫���ݒ�

	for (int nCnt= 0; nCnt < MAX_DROW; nCnt++)
	{//
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			//�v���C���[�̔���--------------------------------------------------------------------------------------
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_PLAYER)
				{//	�I�u�W�F�N�g���v���C���[��������
					D3DXVECTOR3 player_pos = pScene->GetPosition();

					if (player_pos.x - 40 < pos.x &&	player_pos.x + 40 > pos.x &&
						player_pos.y - 50 < pos.y &&	player_pos.y > pos.y)
					{//�v���C���[�͈̔͐ݒ�
						int player_life = pScene->GetLife();
						Uninit();
						if (m_nType == 0)
						{
							CPlayer::UpLife(15);

						}
						else if (m_nType == 1)
						{
							CPlayer::BulletChange(2);
						}
					}
				}
			}
		}
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, int m_nType)
{
	CItem *pItem = {};

	if (pItem == NULL)
	{
		pItem = new CItem;									//	�e�̃������̊m��

		if (pItem != NULL)
		{
			// �|���S���̏���������
			pItem->Init(pos, m_nType);
			//	�e�̃e�N�X�`���̊��蓖��
			pItem->BindTexture(m_Texture[m_nType]);
		}
		else
		{
		}
	}
	return pItem;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CItem::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_HP, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_001, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_002, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_003, &m_Texture[3]);

	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CItem::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEX_ITEM; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}