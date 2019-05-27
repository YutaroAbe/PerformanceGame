//=============================================================================
//
//	�t�F�C�h�̏��� [fade.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//
//
//
LPDIRECT3DTEXTURE9 CFade::m_Texture = NULL;
//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Texture = NULL;
	m_modenext = CManager::MODE_TITLE;
	m_fade = FADE_NONE;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CFade::~CFade()
{
}

//==============================================================================
//	����������
//==============================================================================
void CFade::Init(CManager::MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �l�̏�����
	m_fade = FADE_IN;	//�t�F�[�h�̏�Ԃ�
	m_modenext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�������(�s����)�ɂ��Ă���

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);				 //����
	pVtx[3].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);		 //����
	 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	m_pVtxBuff->Unlock();


}

//==============================================================================
//	�I������
//==============================================================================
void CFade::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
//	�X�V����
//==============================================================================
void CFade::Update(void)
{
	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)	//�t�F�[�h���
		{
			m_colorFade.a -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���
			m_colorFade.a -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;		//�������Ă��Ȃ����

			}
		}
		else if (m_fade == FADE_OUT)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
			m_colorFade.a += 1.0f / 60;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;	//�t�F�[�h��Ԃ�

				//���[�h�̐ݒ�
				CManager::SetMode(m_modenext);
			}
		}
		//�J���[
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//���_�o�b�t�@�A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CFade::Draw(void)
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
//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modenext = modeNext;

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�������(����)�ɂ��Ă���
}
////==============================================================================
////	�v���C���[�̐�������
////==============================================================================
//CFade *CFade::Create(CManager::MODE modenext)
//{
//	CFade *pFade = NULL;
//	if (m_fade == FADE_NONE)
//	{
//		if (pFade == NULL)
//		{
//			pFade = new CFade;						//	�������̊m��
//			if (pFade != NULL)
//			{										//	�������̊m�ۏo������
//				pFade->Init(modenext);						//	�������̏���������
//				m_fade = FADE_OUT;
//			}
//			else
//			{
//			}
//		}
//	}
//	return pFade;
//}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CFade::Laod(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FADE_0, &m_Texture);

	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CFade::UnLoad(void)
{
	//	�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}