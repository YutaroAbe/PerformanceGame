//=============================================================================
//
// �A�C�e������ [item.cpp]
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
#include "fade.h"
#include "sound.h"			//	�T�E���h

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
LPDIRECT3DTEXTURE9 CItem::m_pTexture[ITEM_MAXTYPE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_ITEM)
{
	m_ItemType = {};
	m_pPlayer = NULL;	//	�v���C���[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
//	�A�C�e���̐���
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CItem *pItem = {};

	if (pItem == NULL)
	{//	�A�C�e���̐���
		pItem = new CItem;
		if (pItem != NULL)
		{//�A�C�e���̏�����
			pItem->Init(pos, rot, size, col, TexUV, itemType);
		}
	}
	return pItem;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CScene3D::SetInitAll(pos, rot, size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	CScene3D::BindTexture(m_pTexture[itemType]);
	m_ItemType = (ITEMTYPE)itemType;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CItem::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\boom.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\HP000.png", &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �A�����[�h����
//=============================================================================
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < ITEM_MAXTYPE; nCount++)
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
bool  CItem::CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;							//	�����������ǂ���
	D3DXVECTOR3 pos = CScene3D::Getpos();		//	�ʒu�̎擾
	D3DXVECTOR3 size = CScene3D::Getsize();		//	�傫���̎擾
	CSound *pSound = CManager::GetSound();		//	���̎擾

	if (pos.x + (size.x / 2) >= pPos->x + sizeMin.x &&		// ��
		pos.x - (size.x / 2) <= pPos->x + sizeMax.x &&		// ��
		pos.z + (size.z / 2) >= pPos->z + sizeMin.z &&		// �E
		pos.z - (size.z / 2) <= pPos->z + sizeMax.z &&		// ��
		pos.y + (size.y/ 2) >= pPos->y + sizeMin.y &&		// ��O
		pos.y - (size.y/2) <= pPos->y + sizeMax.y)			// ��
	{// �A�C�e���ɂԂ������ꍇ
		if (m_ItemType == TYPE_BULLETADD)
		{//	�X�s�[�h�A�C�e����������
			bHit = true;										//	��������
			Uninit();											//	�J��
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEM000);	//	�A�C�e���擾���̉�
		}
		else if (m_ItemType == TYPE_LIFEUP)
		{//	�񕜃A�C�e����������
			bHit = true;										//	��������
			Uninit();											//	�J��
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEM001);	//	�A�C�e���擾���̉�

		}
	}

	return bHit;
}