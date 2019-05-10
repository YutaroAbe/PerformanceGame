//=============================================================================
//
//	�����̏��� [number.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_Texture = NULL;
int CNumber::m_NumNumber = NULL;

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CNumber::~CNumber()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_Length = Length;

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CNumber::Uninit(void)
{
	m_NumNumber--;
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
//	�X�V����
//==============================================================================
void CNumber::Update(void)
{

}

//==============================================================================
//	�`�揈��
//==============================================================================
void CNumber::Draw(void)
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

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================================
//	�X�R�A�̐�������
//==============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	CNumber *pNumber = {};
	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		if (pNumber != NULL)
		{
			m_NumNumber++;
			pNumber->Init(pos, Length);
			pNumber->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pNumber;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CNumber::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_NUMBER_0, &m_Texture);

	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CNumber::UnLoad(void)
{
	//	�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}
//==============================================================================
//	�X�R�A�̎擾
//==============================================================================
void CNumber::SetNumber(int nNumber)
{
	int aNumber = nNumber;

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	 //�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber * 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	���ʃe�N�X�`�������蓖�Ă鏈��
//=============================================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_Texture = pTexture;
}

//=============================================================================
//	����Ă���ԍ��̐��̎擾
//=============================================================================
int  CNumber::GetNumNumber(void)
{
	return m_NumNumber;
}