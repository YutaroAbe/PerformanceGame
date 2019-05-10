//=============================================================================
//
// ���f������ [model.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//=============================================================================
//�R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	m_pMesh = NULL;					//	���b�V�����ւ̃|�C���^
	m_pBuffMat = NULL;				//	�}�e���A�����ւ̃|�C���^
	m_pTexture= NULL;				//	�e�N�X�`���ւ̃|�C���^
	m_nNumMat = 0;					//	�}�e���A�����̐�
	m_pParent = NULL;				//	�e���f���ւ̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// ��������
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel = {};

	if (pModel == NULL)
	{//	���f�����g���Ă��Ȃ������ꍇ
		pModel = new CModel;	//	�������̊m��
		if (pModel != NULL)
		{//	������������
			pModel->m_pos = pos;	//	�ʒu
			pModel->m_rot = rot;	//	����
			pModel->Init();			//	������
		}
	}
	//	�l��Ԃ�
	return pModel;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	//�|�C���^��NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{
			//�|�C���^���̃|�C���^��NULL�`�F�b�N
			if (m_pTexture[nCnt] != NULL)
			{
				//�e�N�X�`���j��
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
		//���������J��
		delete[] m_pTexture;
		//NULL������
		m_pTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	//	���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���_�@���̎������K��		�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{//�e�̃}�g���b�N�X���擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{	//Draw�ŌĂ΂ꂽ�Ƃ��ŐV��mtx��pDevice����擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e�̏�������	�|�����킹�Ă���
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		if (pMat != NULL)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`��������ꍇ
				pDevice->SetTexture(0, m_pTexture[nCntMat]);
			}
			else
			{	// �e�N�X�`�����g���Ă��Ȃ�
				pDevice->SetTexture(0, NULL);
			}
		}
		//�I�u�W�F�N�g(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
	// ���_�@���̎������K��		�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//	���C�g��߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// �}�e���A�����蓖�ď���
//=============================================================================
void CModel::BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	m_pBuffMat = Buff;
	m_nNumMat = nNumMat;
	m_pMesh = Mesh;
	//�}�e���A����񂩂�e�N�X�`���̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//�e�N�X�`�����}�e���A���̐������I�m��
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];
	//�}�e���A���̐���
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat; nCntMatTex++)
	{
		//NULL������ ���g�����
		m_pTexture[nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐ݒ�
			D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
				pMat[nCntMatTex].pTextureFilename,		// �t�@�C���̖��O
				&m_pTexture[nCntMatTex]);				// �e�N�X�`���ւ̃|�C���^
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̎擾����
//=============================================================================
D3DXMATRIX &CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̐ݒ菈��
//=============================================================================
void CModel::SetMtxWorld(D3DXMATRIX MtxWorld)
{
	m_mtxWorld = MtxWorld;
}

