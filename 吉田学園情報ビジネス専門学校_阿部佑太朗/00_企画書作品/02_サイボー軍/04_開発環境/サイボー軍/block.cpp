//=============================================================================
//
//	�u���b�N�̏��� [block.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "scene.h"
#include "block.h"
//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CBlock::m_Texture[MAX_BLOCK] = {};	//	�u���b�N�̋��ʃe�N�X�`���̃|�C���^������
int CBlock::m_NumBlock = NULL;							//	�u���b�N�̐�������
int CBlock::m_nType = NULL;								//	��ނ̏�����

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CBlock::CBlock() : CScene2D(3)
{
	m_NumBlock++;			//	�u���b�N�̐��̉��Z
	m_fWindth = NULL;		//	���̏�����
	m_fHeight = NULL;		//	�c�̏�����
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CBlock::~CBlock()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_BLOCK);

	//	����������
	CScene2D::Init();
	m_fWindth = fWindth;	//	���̑��
	m_fHeight = fHeight;	//	�c�̑��
	m_nType = nType;		//	��ނ̑��

	//	�|���S���̈ʒu
	D3DXVECTOR3 pPos[4];

	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, m_fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(m_fWindth, m_fHeight, 0.0f);

	//	UV
	D3DXVECTOR2 tex[4];

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f*fTexSplitX, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f*fTexSplitY);
	tex[3] = D3DXVECTOR2(1.0f*fTexSplitX, 1.0f*fTexSplitY);

	SetVtxPosition(&pPos[0], pos);				//	�ʒu�̐ݒ�
	SetTexture(&tex[0]);						//	UV�ݒ�
	SetType(m_nType);							//	��ނ̐ݒ�
	SetWindthHeigth(m_fWindth, m_fHeight);		//	���ƍ����̐ݒ�

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CBlock::Uninit(void)
{
	//	�I������
	CScene2D::Uninit();
	m_NumBlock--;								//	�u���b�N�̐��̌��Z
}

//==============================================================================
//	�X�V����
//==============================================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();				//	�ʒu
	D3DXVECTOR3 move = GetMoveing();				//	����
	 float fWindth = GetfWindth();					//	��
	 float fHeight = GetfHeight();					//	����
	fWindth = m_fWindth;							//	���̑��
	fHeight = m_fHeight;							//	�����̑��
	D3DXVECTOR3 PlayerMove = CPlayer::GetMove();	//	�v���C���[�̓����̎擾

	if (PlayerMove.x >= 0.1f)
	{//	�v���C���[��X���W��0.1�ȏゾ�����ꍇ
	 //	�u���b�N���v���C���[�̈ړ��̃x�N�g���Ƃ͔��΂ɓ�����
		move.x -= PlayerMove.x;
	}
	else if (PlayerMove.x <= -0.1f)
	{//	�v���C���[��X���W��0.1�C�J�������ꍇ
	//	�u���b�N���v���C���[�̈ړ��̃x�N�g���Ƃ͔��΂ɓ�����
		move.x += -PlayerMove.x;
	}

	//	�������ʒu�ɉ��Z
	pos.x += move.x;
	pos.y += move.y;

	//	���_���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, fHeight, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CBlock::Draw(void)
{
	//	�V�[��2D�̕`��
	CScene2D::Draw();
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, float fWindth, float fHeight,int nType, float fTexSplitX, float fTexSplitY)
{
	CBlock *pBlock = {};		//	�u���b�N�̕ϐ�

	if (pBlock == NULL)
	{//	�u���b�N���g���Ă��Ȃ��������ꍇ
		if (nType != TYPE_FALL)
		{//	�u���b�N�̃������̊m��
			pBlock = new CBlock;
		}
		else if (nType == TYPE_FALL)
		{//	������u���b�N�̃������̊m��
			pBlock = new CBlockDrop;
		}
		if (pBlock != NULL)
		{//�u���b�N�̃��������m�ۂ��ꂽ��
			// �w�i�̏���������
			pBlock->Init(pos, fWindth, fHeight, nType, fTexSplitX, fTexSplitY);
			//	�w�i�̃e�N�X�`���̊��蓖��
			pBlock->BindTexture(m_Texture[nType]);
		}
	}
	//	�l��Ԃ�
	return pBlock;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CBlock::Laod(void)
{
	//	�f�o�C�X�̐ݒ�
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_000, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_001, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_002, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_003, &m_Texture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_004, &m_Texture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_005, &m_Texture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_006, &m_Texture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_007, &m_Texture[7]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_008, &m_Texture[8]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_009, &m_Texture[9]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_010, &m_Texture[10]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_011, &m_Texture[11]);

	//	�l��Ԃ�
	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CBlock::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
	{//	�u���b�N�̃e�N�X�`���̍ő吔��
		//	�e�N�X�`���̔j��
		if (m_Texture[nCount] != NULL)
		{//	�e�N�X�`�����g�p����Ă����ꍇ
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}

//==============================================================================
//	�G�̐��̎擾
//==============================================================================
int  CBlock::GetNumBlock(void)
{
	return m_NumBlock;
}

//==============================================================================
//	�G�̎�ނ̎擾
//==============================================================================
int CBlock::GetTypeBlock(void)
{
	return m_nType;
}
//-------------------------------------------------------------------------------------------------------------------------------
//������u���b�N
//-------------------------------------------------------------------------------------------------------------------------------
//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBlockDrop::CBlockDrop()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBlockDrop::~CBlockDrop()
{
}

//==============================================================================
//	�u���b�N�̏���������
//==============================================================================
HRESULT CBlockDrop::Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY)
{
	CBlock::Init(pos, fWindth, fHeight, nType, fTexSplitX, fTexSplitY);
	return S_OK;
}

//==============================================================================
//	�u���b�N�̏I������
//==============================================================================
void CBlockDrop::Uninit(void)
{
	CBlock::Uninit();
}
//==============================================================================
//	�u���b�N�̍X�V����
//==============================================================================
void CBlockDrop::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();				//	�ʒu�擾
	D3DXVECTOR3 move = GetMoveing();				//	�����擾
	float fWindth = GetfWindth();					//	���擾
	float fHeight = GetfHeight();					//	�����̑��
	fWindth = m_fWindth;							//	���̑��
	fHeight = m_fHeight;							//	�����̑��
	D3DXVECTOR3 PlayerMove = CPlayer::GetMove();	//	�v���C���[�̓����̎擾
	bool bLand = CPlayer::GetLand();				//	�v���C���[���u���b�N�ɏ���Ă��邩�ǂ���

	if (PlayerMove.x >= 0.1f)
	{//	�v���C���[��X���W��0.1�ȏゾ�����ꍇ
	 //	�u���b�N���v���C���[�̈ړ��̃x�N�g���Ƃ͔��΂ɓ�����
		move.x -= PlayerMove.x;
	}
	else if (PlayerMove.x <= -0.1f)
	{//	�v���C���[��X���W��0.1�C�J�������ꍇ
	 //	�u���b�N���v���C���[�̈ړ��̃x�N�g���Ƃ͔��΂ɓ�����
		move.x += -PlayerMove.x;
	}
	if (bLand == true)
	{//	�v���C���[���u���b�N�ɏ���Ă����ꍇ
		move.y += 0.55f;	//	�u���b�N���Ƃ�
	}
	//	�������ʒu�ɉ��Z
	pos.x += move.x;
	pos.y += move.y;

	//	���_���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, fHeight, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);
}

//==============================================================================
//	�u���b�N�̕`�揈��
//==============================================================================
void CBlockDrop::Draw(void)
{
	CBlock::Draw();
}