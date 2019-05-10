//=============================================================================
//
//	�G�t�F�N�g�̏��� [effect.cpp]
//	 Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_Texture = NULL;	//	�e�N�X�`���̏�����

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEffect::CEffect() : CScene2D(3)
{
	m_nLife = NULL;								//	�G�t�F�N�g�̎����̏�����
	m_fRadius = NULL;							//	���a�̏�����
	m_pVtxBuff = NULL;							//	���_���̏�����
	m_Color = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);	//	�F�̐ݒ�
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEffect::~CEffect()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col)
{
	CScene2D::Init();							//	2D�|���S���̏���������
	SetPosition(pos, fRadius, fRadius);			//	�|�W�V�����Ƒ傫���̐ݒ�
	m_nLife = nLife;							//	�G�t�F�N�g�̎����̐ݒ�
	m_fRadius = fRadius;						//	���a�̐ݒ�
	m_Color = Col;								//	�J���[�̐ݒ�

	D3DXCOLOR col[4];
	//	�F�̐ݒ�
	col[0] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[1] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[2] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[3] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	//	�F�̔��f
	CScene2D::SetColor(&col[0]);

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CEffect::Uninit(void)
{
	//	�V�[��2D�̔j��
	CScene2D::Uninit();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();							//	�ʒu�̎擾
	//	�ʒu�̂��Ă�
	SetPosition(pos, EFFECT_POLIGON_X, EFFECT_POLIGON_Y);

	m_nLife--;		//	�����̌��Z
	m_fRadius--;	//	���a�̌��Y��

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//	���_���̎擾
	m_pVtxBuff = CScene2D::GetBuff();

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (m_nLife <= 0 || m_fRadius <= 0)
	{//������0�����܂��͔��a��0�����ɂȂ����ꍇ
		Uninit();
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	�V�[��2D�̕`��
	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col)
{
	CEffect *pEffect = {};	//	�G�t�F�N�g�̃|�C���^

	if (pEffect == NULL)
	{//	�G�t�F�N�g���g�p����Ă��Ȃ������ꍇ
		pEffect = new CEffect;		//	�������̊m��

		if (pEffect != NULL)
		{//	�G�t�F�N�g���g�p����Ă����ꍇ
			// �|���S���̏���������
			pEffect->Init(pos,nLife, fRadius, Col);
			//�e�̃e�N�X�`���̊��蓖��
			pEffect->BindTexture(m_Texture);
		}
	}
	//	�l��Ԃ�
	return pEffect;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CEffect::Laod(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EFFECT, &m_Texture);

	//	�l��Ԃ�
	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CEffect::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{//	�e�N�X�`�����g�p����Ă����ꍇ
		m_Texture->Release();
		m_Texture = NULL;
	}
}

