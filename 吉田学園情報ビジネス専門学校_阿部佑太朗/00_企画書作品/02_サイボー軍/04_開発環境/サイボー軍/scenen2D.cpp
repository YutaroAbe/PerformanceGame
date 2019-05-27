//=============================================================================
//
// ���C������ [main.cpp]
// Author :�@YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include <string>
#include <time.h>
#include "enemy.h"

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D() : CScene(3)
{
	m_pTexture = NULL;										//	�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;										//	���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//	�|���S���̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	�|���S���I����
	m_fWindth = NULL;										//	���̏�����
	m_fHeight = NULL;										//	�����̏�����
	m_nLife = NULL;											//	���C�t�̏�����
	m_nType = NULL;
}

//=============================================================================
//	�D�揇�ʂ̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriarity) : CScene(nPriarity)
{
	m_pTexture = NULL;										//	�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;										//	���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//	�|���S���̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	�|���S���I����
	m_fWindth = NULL;										//	���̏�����
	m_fHeight = NULL;										//	�����̏�����
	m_nLife = NULL;
	m_nType = NULL;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�������g�̔j��
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
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
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, MAX_POLIGON);

}

//=============================================================================
//	�v���C���[�̈ʒu�̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float PolygonSizeX, float PolygonSizeY)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	m_pos = pos;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-PolygonSizeX, -PolygonSizeY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(PolygonSizeX, -PolygonSizeY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-PolygonSizeX, PolygonSizeY, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(PolygonSizeX, PolygonSizeY, 0.0f) + m_pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�A�j���[�V�����̐ݒ�
//=============================================================================
void CScene2D::SetAnimation(int PatternAnim, float Split, int SplitAnim)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f/ Split) * (PatternAnim % SplitAnim) + 0.0f, 0.0f);				 //�E��
	pVtx[1].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim) + (1.0f / Split), 0.0f);				 //�E��
	pVtx[2].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim + 0.0f), 1.0f);				 //�E��
	pVtx[3].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim) + (1.0f / Split), 1.0f);				 //�E��

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�A�j���[�V�����̃e�N�X�`���̏�����
//=============================================================================
void CScene2D::InitAnimationTex(float Split)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
	pVtx[1].tex = D3DXVECTOR2((1.0f / Split), 0.0f);			//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[3].tex = D3DXVECTOR2((1.0f / Split), 1.0f);			//�E��

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	�w�i������
//=============================================================================
void CScene2D::BGMove(D3DXVECTOR3 move)
{
	m_move = move;
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_move.x, 0.0f);						//����
	pVtx[1].tex = D3DXVECTOR2(m_move.x - 1.0f, 0.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(m_move.x, 1.0f);						//����
	pVtx[3].tex = D3DXVECTOR2(m_move.x - 1.0f, 1.0f);				//�E��

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//	�J���[�ύX
//=============================================================================
void  CScene2D::ColorChange(D3DXCOLOR m_Col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	���_���̐ݒ�
//=============================================================================
void CScene2D::SetVtxPosition(D3DXVECTOR3 *pPos, D3DXVECTOR3 pos)
{
	m_pos = pos;

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].pos = pPos[0] + m_pos;
	pVtx[1].pos = pPos[1] + m_pos;
	pVtx[2].pos = pPos[2] + m_pos;
	pVtx[3].pos = pPos[3] + m_pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
//���ƍ����̐ݒ�
//=============================================================================
void CScene2D::SetWindthHeigth(float fWindth, float fHeight)
{
	m_fWindth = fWindth;
	m_fHeight = fHeight;
}

//=============================================================================
//	�J���[�̐ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR * color)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].col = color[0];
	pVtx[1].col = color[1];
	pVtx[2].col = color[2];
	pVtx[3].col = color[3];

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//	Texture�̐ݒ�
//=============================================================================
void CScene2D::SetTexture(D3DXVECTOR2 *pTex)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = pTex[0];
	pVtx[1].tex = pTex[1];
	pVtx[2].tex = pTex[2];
	pVtx[3].tex = pTex[3];

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//
//=============================================================================
void CScene2D::SetType(int nType)
{
	m_nType = nType;
}
//=============================================================================
//	���C�t�|�C���g�̐ݒ�
//=============================================================================
void CScene2D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
//	�o�b�t�@�̎擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetBuff(void)
{
	return m_pVtxBuff;
}

//=============================================================================
//	�v���C���[�̈ʒu�擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
//�v���C���[�̓����擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetMoveing(void)
{
	return m_move;
}
//=============================================================================
//	2D�|���S���̕��̎擾
//=============================================================================
float CScene2D::GetfWindth(void)
{
	return m_fWindth;
}
//=============================================================================
//	2D�|���S���̍����̎擾
//=============================================================================
float CScene2D::GetfHeight(void)
{
	return m_fHeight;
}
//==============================================================================
//�v���C���[�̃_���[�W�ݒ�
//==============================================================================
void CScene2D::HitDamage(int nDamage)
{
	CPlayer::HitDamage(nDamage);

}

//=============================================================================
//	���ʃe�N�X�`�������蓖�Ă鏈��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//�@HP�̎擾
//=============================================================================
int CScene2D::GetLife(void)
{
	return m_nLife;
}
//=============================================================================
//�@��ނ̎擾
//=============================================================================
int  CScene2D::GetType(void)
{
	return m_nType;
}