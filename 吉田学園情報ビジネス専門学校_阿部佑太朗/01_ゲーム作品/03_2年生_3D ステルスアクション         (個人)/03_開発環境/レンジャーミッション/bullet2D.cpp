//=============================================================================
//
// �e2D���� [bullet2D.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"		// �V�[��3D
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����
#include "camera.h"			// �J����
#include "item.h"			// �A�C�e��
#include "effect.h"			// �G�t�F�N�g
#include "bullet2D.h"		// �e2D
#include "floor.h"			// ��
#include "scene.h"			// �V�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet2D::m_pTexture[BULT2D_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet2D::CBullet2D() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_BULLET2D)
{
	m_nLife = 0;					//	�����̏�����
	m_BulletState = BULLET_NONE;	//	�e�̃X�e�[�^�X�̏�����
	m_pShadow = NULL;
	m_nDispCounter = 0;				//	������܂ł̃J�E���g
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ߋ��̈ʒu�̕ۑ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet2D::~CBullet2D()
{

}

//=============================================================================
//	�A�C�e���̐���
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nLife, TYPEBULT BultType)
{
	CBullet2D *pBullet2D = {};

	if (pBullet2D == NULL)
	{//	�A�C�e���̐���
		pBullet2D = new CBullet2D;
		if (pBullet2D != NULL)
		{//�A�C�e���̏�����
			pBullet2D->Init(pos, move, size, col, TexUV, nLife,BultType);
		}
	}
	return pBullet2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nLife, TYPEBULT BultType)
{
	//	�V�[��3D�̏�����
	CScene3D::SetInitAll(pos, D3DXVECTOR3(0.0f,0.0f,0.0f), size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	//	�e�N�X�`���̊��蓖��
	CScene3D::BindTexture(m_pTexture[(int)BultType]);
	m_nLife = nLife;		//	������������
	m_move = move;			//	�����̑��
	//	�e�̐���
	if (m_pShadow == NULL)
	{//	�e���g���Ă��Ȃ�������
		m_pShadow = CShadow::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, 0.0f, size.y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet2D::Uninit(void)
{

	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet2D::Update(void)
{

	D3DXVECTOR3 pos = CScene3D::Getpos();					//	�傫���̎擾
	D3DXVECTOR3 size = CScene3D::Getsize();					//	�傫���̎擾
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// ���݁@
	CScene *pSceneNext = NULL;								// ��
	m_posOld = pos;											//�ʒu�̕ۑ�
	switch (m_BulletState)
	{
		//--------------------------------------------------
		//	�ʏ�
		//--------------------------------------------------
	case BULLET_NONE:
		m_nLife--;			//	�����̌���
		pos += m_move;		//	�����̉��Z
		if (m_pShadow != NULL)
		{//	�e���g�p���ꂽ�������΂�
		 //	�e�̈ʒu�̐ݒ�
			CManager::m_CDebugProcRight->Print("\n�e�ʒu  ( %.1f : %.1f  : %.1f)", pos.x, pos.y, pos.z);
			m_pShadow->Setpos(D3DXVECTOR3(pos.x, 10.0f, pos.z));
		}
		CScene3D::Setpos(pos);					//	�ʒu�̐ݒ�
		CScene3D::Update();
		while (pScene != NULL)
		{// NULL�ȊO�̏ꍇ
		 // ���I�u�W�F�N�g����ۑ�
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
			{//	���������ꍇ
				CFloor *pFloor = (CFloor*)pScene;						//	���ɃL���X�g
				if (pFloor->Collision(&pos, &m_posOld, &m_move, size, size) == true)// �����蔻��
				{
					m_BulletState = BULLET_HIT;		//	�e��������
				}
			}
			// ���̃I�u�W�F�N�g�ɐݒ�
			pScene = pSceneNext;
		}

		if (m_nLife <= 0)
		{//	�������w��̒l�𒴂����ꍇ
			m_BulletState = BULLET_HIT;		//	�e��������
		}
		break;
		//--------------------------------------------------
		//	�e����������
		//--------------------------------------------------
	case BULLET_HIT:
		m_nDispCounter++;
		if (m_nDispCounter < 10)
		{//	�J�E���g���w��̒l�ȏ�ɂȂ����ꍇ
			size.x += 0.95f;
			size.y += 0.95f;
		}
		else
		{
			m_BulletState = BULLET_DISP;	//	�e��������
		}

		CScene3D::Setsize(size);					//	�ʒu�̐ݒ�
		CScene3D::Update();
		break;
		//--------------------------------------------------
		//	�e��������
		//--------------------------------------------------
	case BULLET_DISP:
		//	�e������
		m_pShadow->Uninit();
		//	�I������
		Uninit();
		break;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet2D::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BULLET\\bullet2D_000.png", &m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CBullet2D::Unload(void)
{
	for (int nCount = 0; nCount < BULT2D_TYPE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==============================================================================================================================
// �A�C�e���̂����蔻��̍쐬
//==============================================================================================================================
bool  CBullet2D::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;
	D3DXVECTOR3 pos = CScene3D::Getpos();				//	�e�̈ʒu
	D3DXVECTOR3 size = CScene3D::Getsize();				//	�e�̑傫��
	//	�v���C���[�Ƃ̊p�x
	float fAngle = atan2f(pPos->x - pos.x, pPos->z - pos.z);
	// ��������̂̋���
	float fPosX = (pos.x - pPos->x);
	float fPosY = (pos.y + size.y) - (pPos->y+ sizeMax.y);
	float fPosZ = (pos.z - pPos->z);

	float fRadiusA = fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ;
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x/2 + size.x)* (sizeMax.z/2 + size.x);

	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{
		//	�e������
		m_pShadow->Uninit();
		bHit = true;
	}

	return bHit;
}