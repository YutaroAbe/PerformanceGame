//=============================================================================
//
// ���b�V���I�[�r�b�g���� [orbit.cpp]
// Author :YUTARO ABE
//
//=============================================================================
#include "orbit.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
COrbit::COrbit() : CScene(CScene::PRIORITY_5, OBJECTE_ORBIT)
{
	m_pTexture = NULL;												//�@�e�N�X�`���ւ̃|�C���^�̏�����
	m_pVtxBuff = NULL;												//�@���_�o�b�t�@�ւ̃|�C�̏��������^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�@�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�@�����̏�����
	m_fWidth = NULL;												//	��
	m_fHeight = NULL;												//	����
	m_fOffSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fOffSet[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{
		m_aPosVerTex[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
COrbit::COrbit(int nPriority, CScene::OBJTYPE objType) : CScene(CScene::PRIORITY_3, OBJECTE_ORBIT)
{
	m_pTexture = NULL;												//�@�e�N�X�`���ւ̃|�C���^�̏�����
	m_pVtxBuff = NULL;												//�@���_�o�b�t�@�ւ̃|�C�̏��������^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�@�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�@�����̏�����
	m_fWidth = NULL;												//	��
	m_fHeight = NULL;												//	����
	m_fOffSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fOffSet[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{
		m_aPosVerTex[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
COrbit::~COrbit()
{

}

//=============================================================================
//�|���S���̐�������
//=============================================================================
COrbit *COrbit::Create(D3DXVECTOR3 offsetstate, D3DXVECTOR3 offsetend)
{
	COrbit *pOrbit = {};

	if (pOrbit == NULL)
	{//	3D�|���S���̐���
		pOrbit = new COrbit;
		if (pOrbit != NULL)
		{
			pOrbit->m_fOffSet[0] = offsetstate;
			pOrbit->m_fOffSet[1] = offsetend;
			// �|���S���̏���������
			pOrbit->Init();
		}
	}
	return pOrbit;
}

//=============================================================================
//	����������
//=============================================================================
HRESULT COrbit::Init(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gradation004.jpg", &m_pTexture);
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SIZE
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < MAX_XSIZE + 1; nCount++)
	{
		pVtx[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCount + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//	�@�����̌v�Z
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCount + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCount + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCount].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCount + 1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 1;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void COrbit::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{//	���_�o�b�t�@���g���Ă�����
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �V�[���J��
	CScene::SetDeath();
}

//=============================================================================
//	�X�V����
//=============================================================================
void COrbit::Update(void)
{
}

//=============================================================================
//	�X�V����
//=============================================================================
void COrbit::Draw(void)
{
	//	�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						// ���C�g�e���󂯂Ȃ�

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = MAX_SIZE - 1; nCount > 1; nCount--)
	{//
		m_aPosVerTex[nCount] = m_aPosVerTex[nCount - 2];
	}

	//	�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXVec3TransformCoord(&m_aPosVerTex[0], &m_fOffSet[0], m_pMtxParrentState);
	D3DXVec3TransformCoord(&m_aPosVerTex[1], &m_fOffSet[1], m_pMtxParrentState);

	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{//	����ւ����x�N�g���𒸓_���ɓ����
		pVtx[nCount].pos = m_aPosVerTex[nCount];
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	if (m_pMtxParrentState != NULL)
	{
		// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, MAX_PORIGON_ORBIT);
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					// Z�o�b�t�@�ւ̏�������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�g�e���󂯂Ȃ�

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
//	�}�g���b�N�X�̐ݒ�
//=============================================================================
void COrbit::SetMtxParent(D3DXMATRIX *pMtxstate)
{
	m_pMtxParrentState = pMtxstate;
}
