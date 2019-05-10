//=============================================================================
//
//	�e3D�̏���[bullet.cpp]
//	Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"	//	�}�l�[�W���[
#include "renderer.h"	//	�����_���[
#include "bullet3D.h"	//	�e3D
#include "block.h"		//	�u���b�N
#include "wall.h"		//	��
#include "floor.h"		//	��
#include "effect.h"		//	�G�t�F�N�g
#include "enemy.h"		//	�G
#include "sound.h"		//	��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME_BOOM	"data\\MODEL\\Object\\boom.x"		// �ʏ�u���b�N

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		*CBullet3D::m_pTexture[BULLET3D_MAX] = {};			// �e�N�X�`�����ւ̃|�C���^
LPD3DXMESH				CBullet3D::m_pMesh[BULLET3D_MAX] = {};				// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER			CBullet3D::m_pBuffMat[BULLET3D_MAX] = {};			// �}�e���A�����ւ̃|�C���^
DWORD					CBullet3D::m_nNumMat[BULLET3D_MAX] = {};			// �}�e���A�����̐�

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CBullet3D::CBullet3D() :CSceneX(CScene::PRIORITY_3,CScene::OBJTYPE_BULLET3D)
{
	m_Bullet3DType = BULLET3D_TYPE_BOOM;		//	�e�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�����̏�����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�O��̈ʒu�̏�����
	m_nDispCounter = 0;							//	�e��������܂ł̃J�E���g
	m_BulletState = BULLET_NONE;				//	�e�̏��
	m_bExplColl = false;						//
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet3D::~CBullet3D()
{

}

//=============================================================================
//	���f���̃e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet3D::Load(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	���f���̖��O���i�[�̂���ϐ�
	char cModelName[256];

	for (int nCntIndex = 0; nCntIndex < BULLET3D_MAX; nCntIndex++)
	{//	���f�����ő吔����
		switch (nCntIndex)
		{
		case BULLET3D_TYPE_BOOM:	//	�e���[�@�{���@]
			wsprintf(cModelName, MODEL_NAME_BOOM);
			break;
		}
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(cModelName,
			D3DXMESH_SYSTEMMEM,
			pDevice, NULL,
			&m_pBuffMat[nCntIndex],
			NULL,
			&m_nNumMat[nCntIndex],
			&m_pMesh[nCntIndex]);

		D3DXMATERIAL *pmat;									// �}�e���A���f�[�^�ւ̃|�C���^
		D3DMATERIAL9 *matDef;								// ���݂̃}�e���A���ۑ��p

		pmat = (D3DXMATERIAL*)m_pBuffMat[nCntIndex]->GetBufferPointer();
		matDef = new D3DMATERIAL9[m_nNumMat[nCntIndex]];						//	�}�e���A���̃������̊m��
		m_pTexture[nCntIndex] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntIndex]];	//	�e�N�X�`���̃������̊m��

		for (DWORD tex = 0; tex < m_nNumMat[nCntIndex]; tex++)
		{// �J�E���g
			matDef[tex] = pmat[tex].MatD3D;					//�@�}�e���A���̃v���p�e�B���L�q���� D3DMATERIAL9 �\����
			matDef[tex].Ambient = matDef[tex].Diffuse;		//�@���̒��ړ����镔���̐F�����𓖂���Ȃ������Ɠ���������
			m_pTexture[nCntIndex][tex] = NULL;				//	�e�N�X�`��������ɂ���
			if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
			{// �e�N�X�`�����g�p���Ă��� & ������̒�����0�ȏゾ������

				if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTexture[nCntIndex][tex])))
				{
					//MessageBox(NULL, "���f���̃e�N�X�`��/�}�e���A���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
		//	�}�e���A���̊J��
		delete[] matDef;
		matDef = NULL;
	}
	return S_OK;
}

//=============================================================================
//	���f���̃e�N�X�`���̊J��
//=============================================================================
void CBullet3D::Unload(void)
{
	for (int nCntIndex = 0; nCntIndex < BULLET3D_MAX; nCntIndex++)
	{//	���f���̍ő吔����
	 // �e�N�X�`���̔j��
		for (DWORD tex = 0; tex < m_nNumMat[nCntIndex]; tex++)
		{// �J�E���g
			if (m_pTexture[nCntIndex][tex] != NULL)
			{// NULL�ȊO�̏ꍇ
				m_pTexture[nCntIndex][tex]->Release();		// �������̉��
				m_pTexture[nCntIndex][tex] = NULL;			// NULL��
			}
		}
		//	�e�N�X�`���̊J��
		delete[] m_pTexture[nCntIndex];
		m_pTexture[nCntIndex] = NULL;

		// �}�e���A���̊J��
		if (m_pBuffMat[nCntIndex] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pBuffMat[nCntIndex]->Release();				// �������̉��
			m_pBuffMat[nCntIndex] = NULL;					// NULL��
		}

		// �}�e���A���̊J��
		if (m_pMesh[nCntIndex] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pMesh[nCntIndex]->Release();					// �������̉��
			m_pMesh[nCntIndex] = NULL;						// NULL��
		}
		// �}�e���A���̏�����
		m_nNumMat[nCntIndex] = 0;
	}
}

//=============================================================================
// ��������
//=============================================================================
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType)
{
	CBullet3D *pBullet3D = {};	//	�e3D�̃|�C���^�^�ϐ�

	if (pBullet3D == NULL)
	{//	�e���g���Ă��Ȃ������ꍇ
		pBullet3D = new CBullet3D;	//	�e3D�̃������m��
		if (pBullet3D != NULL)
		{//	�������̊J�����o�����ꍇ
			pBullet3D->Init(pos, rot, scale, move,BulletType);	//	����������
		}
	}
	return pBullet3D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move ,BULLET3DTYPE BulletType)
{
	//	�ϐ��̐ݒ�̏�����
	CSceneX::SetInitAll(m_pTexture[BulletType], m_pMesh[BulletType], m_pBuffMat[BulletType], m_nNumMat[BulletType], pos, rot, scale);
	CSceneX::Init();			//	����������
	CSceneX::Setpos(pos);		//	�ʒu�̐ݒ�
	CSceneX::Setrot(rot);		//	��]�̏���
	CSceneX::SetScale(scale);	//	�g��k��

	//	�e�̎�ނ̐ݒ�
	m_Bullet3DType = BulletType;
	//	�����̐ݒ�
	m_move = move;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet3D::Uninit(void)
{
	//	�I������
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet3D::Update(void)
{
	D3DXVECTOR3 vtxMax = CSceneX::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 vtxMix = CSceneX::Getsize(1);		//	�傫���̍ŏ��l
	CSound *pSound = CManager::GetSound();			//	�T�E���h�̎擾
	D3DXVECTOR3 pos = CSceneX::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 rot = CSceneX::Getrot();			//	��]�̎擾
	D3DXVECTOR3 scale = CSceneX::GetScale();		//	�g��k���̎擾

	// �V�[��
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// ���݁@
	CScene *pSceneNext = NULL;								// ��

	//	�ʒu�̕ۑ�
	m_posOld = pos;

	switch (m_BulletState)
	{
	case BULLET_NONE:

		//	�d�͗�
		m_move.y -= 0.75f;
		//	�ʒu�̓��������Z����
		pos += m_move;

		while (pScene != NULL)
		{// NULL�ȊO�̏ꍇ
		 // ���I�u�W�F�N�g����ۑ�
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
			{//	���������ꍇ
				CFloor *pFloor = (CFloor*)pScene;				//	���ɃL���X�g
				pFloor->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		// �����蔻��]
				bool bHit = pFloor->GetHit();
				if (bHit == true)
				{
					m_BulletState = BULLET_HIT;		//	�e����������
				}
			}
			// ���̃I�u�W�F�N�g�ɐݒ�
			pScene = pSceneNext;
		}
		pScene = CScene::GetScene(CScene::PRIORITY_3);	// ���݁@
		pSceneNext = NULL;								// ��

		while (pScene != NULL)
		{// NULL�ȊO�̏ꍇ
		 // ���I�u�W�F�N�g����ۑ�
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
			{// �I�u�W�F�N�g�^�C�v���u���b�N��������
				CBlock *pBlock = (CBlock*)pScene;									// �u���b�N�ɃL���X�g
				pBlock->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		// �����蔻��
				bool *bLand = pBlock->GetHit();
				if (bLand[0] == true)
				{// �㔻��
					m_BulletState = BULLET_HIT;		//	�e����������
				}
			}
			else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
			{//	�ǂ������ꍇ
				CWall *pWall = (CWall*)pScene;										//	�ǂɃL���X�g
				pWall->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);			//  �����蔻��
			}
			else if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{//	�G�������ꍇ
				CEnemy *pEnemy = (CEnemy*)pScene;									//	�G�ɃL���X�g
				pEnemy->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		//  �����蔻��
				bool bHit = pEnemy->GetHit();
				if (bHit == true)
				{//	�I�u�W�F�N�g�Ƃ�������
					m_BulletState = BULLET_HIT;		//	�e����������
				}

			}
			// ���̃I�u�W�F�N�g�ɐݒ�
			pScene = pSceneNext;
		}
		CSceneX::Setpos(pos);								//	�ʒu�̐ݒ�
		CSceneX::Setrot(rot);								//	��]�̐ݒ�
		CSceneX::SetScale(scale);							//	�傫���̐ݒ�
		break;
	case BULLET_HIT:
		//	�������~�߂�
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//	�J�E���g���Z
		m_nDispCounter++;
		if ((m_nDispCounter % 2) == 0)
		{//	6�t���[����0.1�b���傫�����Ă���
			scale *= 1.075f;

		}
		if (m_nDispCounter >= BULLET_USE_VALSE)
		{//	�e��������܂ł̃J�E���g��60�t���[���ȏソ�������{
			m_BulletState = BULLET_DISP;				//	���������
		}
		CSceneX::Setpos(pos);							//	�ʒu�̐ݒ�
		CSceneX::Setrot(rot);							//	��]�̐ݒ�
		CSceneX::SetScale(scale);						//	�傫���̐ݒ�
		break;
	case BULLET_DISP:
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);	//	������
		CEffect::Create(pos, 0, 1);								//	���̉��̃G�t�F�N�g
		CEffect::Create(pos, 0, 0);								//	���̃G�t�F�N�g
		Uninit();
		break;
	}

}
//=============================================================================
//�`�揈��
//=============================================================================
void CBullet3D::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//	���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���_�@���̎������K��		�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// �`�揈��
	CSceneX::Draw();

	// ���_�@���̎������K��		�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//	���C�g��߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
