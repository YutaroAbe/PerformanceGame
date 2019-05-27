//=============================================================================
//
//	�����̏��� [bullet.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_Texture = NULL;

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CExplosion::CExplosion() : CScene2D(3)
{
	m_CounterAnim = 0;
	m_PatternAnim = 0;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CExplosion::~CExplosion()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init();

	//�e�N�X�`���̐ݒ�
	D3DXVECTOR2 tex[4];

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 5.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	tex[3] = D3DXVECTOR2((1.0f / 5.0f), 1.0f);

	CScene2D::SetTexture(&tex[0]);


	SetPosition(pos, EXPLOSION_POLIGON_X, EXPLOSION_POLIGON_Y);

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMoveing();							//	����

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

	SetPosition(pos, EXPLOSION_POLIGON_X, EXPLOSION_POLIGON_Y);

	m_CounterAnim++;

	if ((m_CounterAnim % 5) == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % 5;

		D3DXVECTOR2 tex[4];

		tex[0] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + 0.0f, 0.0f);
		tex[1] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + (1.0f / 5.0f), 0.0f);
		tex[2] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5 + 0.0f), 1.0f);
		tex[3] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + (1.0f / 5.0f), 1.0f);

		CScene2D::SetTexture(&tex[0]);

		if (m_PatternAnim <= 0)
		{
			Uninit();
		}
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = {};

	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;

		if (pExplosion != NULL)
		{
			// �|���S���̏���������
			pExplosion->Init(pos);
			//�e�̃e�N�X�`���̊��蓖��
			pExplosion->BindTexture(m_Texture);

		}
		else
		{

		}
	}
	return pExplosion;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CExplosion::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EXPLPSION, &m_Texture);

	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CExplosion::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

