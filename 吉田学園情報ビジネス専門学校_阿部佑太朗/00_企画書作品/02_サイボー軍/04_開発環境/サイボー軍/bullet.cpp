//=============================================================================
//
//	�e�̏��� [bullet.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_Texture[MAX_BULLET] = {};					//	�e�N�X�`���̏�����

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CBullet::CBullet() : CScene2D(4)
{
	m_BulletType = BULLET_NONE;											//	�e�̏�����
	 m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	�����̏�����
	 m_nLife = 0;														//	�����̏�����
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CBullet::~CBullet()
{
}

//==============================================================================
//	����������
//==================================    ============================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_BULLET);

	m_move = move;

	if (m_nType == 0)
	{
		m_nLife = 35;
	}
	else if (m_nType == 1)
	{
		m_nLife = 35;
	}
	else if (m_nType == 2)
	{
		m_nLife = 35;
	}
	else if (m_nType == 3)
	{
		m_nLife = 35;
	}
	else if (m_nType == 4)
	{//	�G�l�~�[�̒e
		m_nLife = 160;
	}

	SetPosition(pos, BULLET_POLIGON_X, BULLET_POLIGON_Y);

	m_BulletType = BulletType;

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();											//	�e�̈ʒu�̎擾
	D3DXVECTOR3 move = GetMoveing();
	D3DXVECTOR3 playermove = CPlayer::GetMove();								//	�v���C���[�̓����̎擾
	move += m_move;

	if (playermove.x >= 0.0f)
	{
		move.x -= playermove.x;
	}
	else if (playermove.x <= 0.0f)
	{
		move.x += -playermove.x;
	}
	pos.x += move.x;															//	�e�̓����̍X�VX���W
	pos.y += move.y;															//	�e�̓����̍X�VY���W

	SetPosition(pos, BULLET_POLIGON_X, BULLET_POLIGON_Y);						//	�e�̈ʒu�Ƒ傫���ݒ�



	m_nLife--;																	//	�e�̎���

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			//	�G�l�~�[�̔���--------------------------------------------------------------------------------------
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();

				if (objtype == CScene::OBJECT_ENEMY &&m_BulletType == BULLET_ENEMY)
				{
					CEffect::Create(pos, 80, BULLET_POLIGON_X, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
				}
				else if (objtype == CScene::OBJECT_PLAYER &&m_BulletType == BULLET_PLAYER)
				{
					CEffect::Create(pos, 80, BULLET_POLIGON_X, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}

				if (objtype == CScene::OBJECT_ENEMY &&	m_BulletType == BULLET_PLAYER)
				{//	�I�u�W�F�N�g���G��������
					D3DXVECTOR3 enemy_pos = pScene->GetPosition();
					CEnemy * pEnemy = (CEnemy*)pScene;
					if (enemy_pos.x - 25 < pos.x &&	enemy_pos.x + 25 > pos.x &&
						enemy_pos.y - 25 * 2 < pos.y && enemy_pos.y > pos.y)
					{//�G�͈̔͐ݒ�
						m_nLife = 0;
						pEnemy->Hit(1);
					}
				}
				else if (objtype == CScene::OBJECT_PLAYER &&m_BulletType == BULLET_ENEMY)
				{//	�I�u�W�F�N�g���v���C���[��������
					D3DXVECTOR3 player_pos = pScene->GetPosition();
					if (player_pos.x - 25 < pos.x &&	player_pos.x + 25 > pos.x &&
						player_pos.y - 25 * 2 < pos.y && player_pos.y > pos.y)
					{//�v���C���[�͈̔͐ݒ�
						m_nLife = 0;
						pScene->HitDamage(1);
					}
				}
				else if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();		//	�u���b�N�̈ʒu
					float block_fWindth = pScene->GetfWindth();			//	�u���b�N�̕�
					float block_fHeight = pScene->GetfHeight();			//	�u���b�N�̍���

					if (pos.x + (BULLET_POLIGON_X / 2) >= block_pos.x  &&
						pos.x - (BULLET_POLIGON_X / 2) <= block_pos.x + block_fWindth &&
						pos.y >= block_pos.y &&
						pos.y - BULLET_POLIGON_Y <= block_pos.y + block_fHeight)
					{//	 YX���͈͓�
						m_nLife = 0;
						CExplosion::Create(pos + D3DXVECTOR3(2.0f, 2.0f, 0.0f));		//	�����̐���
					}
				}
			}
		}
	}
	if (m_nLife <= 0)
	{
		Uninit();																//	�I������
	}
}
//==============================================================================
//	�`�揈��
//==============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType)
{
	CBullet *pBullet = {};

	if (pBullet == NULL)
	{
		pBullet = new CBullet;									//	�e�̃������̊m��

		if (pBullet != NULL)
		{
			// �|���S���̏���������
			pBullet->Init(pos, move,  m_nType, BulletType);
			//	�e�̃e�N�X�`���̊��蓖��
			pBullet->BindTexture(m_Texture[m_nType]);
		}
		else
		{
		}
	}
	return pBullet;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CBullet::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_3, &m_Texture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_4, &m_Texture[4]);
	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CBullet::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}