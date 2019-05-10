//=============================================================================
//
//	�̗͂̏��� [number.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "life.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CLife::m_Texture = NULL;

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CLife::CLife() : CScene2D(3)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CLife::~CLife()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_Length = Length;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * m_nLife, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < m_nLife; nCount++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
		pVtx[1].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;
		pVtx[3].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`���̍��W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		m_pos += D3DXVECTOR3(m_Length.x, 0.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CLife::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CLife::Update(void)
{

}

//==============================================================================
//	�`�揈��
//==============================================================================
void CLife::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_Texture);

	int nLife = CPlayer::GetLife();

	for (int nCount = 0; nCount < nLife; nCount++)
	{//�@�v���C���[��HP�Ɠ���
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, MAX_POLIGON);
	}
}

//==============================================================================
//	�X�R�A�̐�������
//==============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	CLife *pLife = {};

	if (pLife == NULL)
	{
		pLife = new CLife;

		if (pLife != NULL)
		{
			pLife->Init(pos , Length);
			pLife->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pLife;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CLife::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFE, &m_Texture);


	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CLife::UnLoad(void)
{
	//	�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

//=============================================================================
//	���ʃe�N�X�`�������蓖�Ă鏈��
//=============================================================================
void CLife::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_Texture = pTexture;

}