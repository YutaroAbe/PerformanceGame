//=============================================================================
//
//	�w�i�̏��� [bg.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "bg.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// =============================================================================
LPDIRECT3DTEXTURE9 CBg::m_Texture[MAX_TEXTURE] = {};

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CBg::CBg() :CScene(0)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	�e�N�X�`���̐�������
		m_apScene2D[nCount] = NULL;
	}
	//	�o�b�t�@�̏�����
	m_pVtxBuff = NULL;
	//	�����̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CBg::Init(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	�e�N�X�`������
		if (m_apScene2D[nCount] == NULL)
		{//	�V�[��2D���g���Ă��Ȃ������ꍇ
			//	�w�i�P���ڂ̐���
			m_apScene2D[nCount] = new CScene2D;						//	�������̊m��
			if (m_apScene2D[nCount] != NULL)
			{
				m_apScene2D[nCount]->Init();							//	����������
				m_pVtxBuff = m_apScene2D[nCount]->GetBuff();

				//���_���ւ̃|�C���^
				VERTEX_2D*pVtx;

				//�o�b�t�@�����b�N
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//	�ʒu�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

				//���_�o�b�t�@���A�����b�N����
				m_pVtxBuff->Unlock();
				//	�e�N�X�`�����蓖��
				m_apScene2D[nCount]->BindTexture(m_Texture[nCount]);
			}
		}
	}
	//	�l��Ԃ�
	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CBg::Uninit(void)
{
	//	�w�i�̊J��
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	�e�N�X�`���̐�������
		if (m_apScene2D[nCount] != NULL)
		{//	�V�[��2D���g���Ă����ꍇ
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}
	//	�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{//	�o�b�t�@���g���Ă����ꍇ
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//	�I�u�W�F�N�g�̔j��
	Release();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CBg::Update(void)
{
	D3DXVECTOR3 move[4];										//	�w�i�̓���

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	�w�i�̖�������
		D3DXVECTOR3 pos = m_apScene2D[nCount]->GetPosition();	//	�|�W�V�����̎擾

		move[nCount] = m_apScene2D[nCount]->GetMoveing();		//	�����̎擾

			move[0].x -= 0.0005f;								//	�w�i1���ڂ̓���
			move[1].x -= 0.001f;								//	�w�i2���ڂ̓���
			move[2].x -= 0.002f;								//	�w�i3���ڂ̓���

		m_apScene2D[nCount]->BGMove(move[nCount]);
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CBg::Draw(void)
{
	//	�V�[���̔h��������Draw�͉��������Ȃ�
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg = {};		//	�w�i�̃|�C���^

	if (pBg == NULL)
	{//	�w�i���g���Ă��Ȃ������ꍇ
		pBg = new CBg;					//	�������̊m��
		if (pBg != NULL)
		{//	�������̊m�ۏo������
			pBg->Init();				//	����������
		}
	}
	//	�l��Ԃ�
	return pBg;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CBg::Laod(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_3, &m_Texture[3]);
	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	�w�i�̖�������
		//	�e�N�X�`���̔j��
		if (m_Texture[nCount] != NULL)
		{//	�e�N�X�`�����g�p����Ă�����
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}
