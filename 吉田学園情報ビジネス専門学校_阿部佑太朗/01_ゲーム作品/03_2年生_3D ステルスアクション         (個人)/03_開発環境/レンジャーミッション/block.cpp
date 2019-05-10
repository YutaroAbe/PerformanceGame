//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "block.h"			// �u���b�N
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "game.h"			// �Q�[��
#include "input.h"			// ����
#include "camera.h"			// �J����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME_0	"data\\MODEL\\Object\\girisutu.x"		// �ʏ�u���b�N
#define MODEL_NAME_1	"data\\MODEL\\Object\\cylinder.x"		//�@�V�����_�[
#define MODEL_NAME_2	"data\\MODEL\\Object\\konntena000.x"	//�@�R���e�i000
#define MODEL_NAME_3	"data\\MODEL\\Object\\shipobj.x"		//�@�D
#define MODEL_NAME_4	"data\\MODEL\\Object\\grass.x"			//�@��
#define MODEL_NAME_5	"data\\MODEL\\Object\\kontena001.x"		//�@�R���e�i001
#define MODEL_NAME_6	"data\\MODEL\\Object\\kontena002.x"		//�@�R���e�i002
#define MODEL_NAME_7	"data\\MODEL\\Object\\shipon.x"			//�@�D�̏�̕���
#define MODEL_NAME_8	"data\\MODEL\\Object\\stageend.x"		//�@STAGE�̃S�[��
#define MODEL_NAME_9	"data\\MODEL\\Object\\door.x"			//�@�h�A
#define MODEL_NAME_10	"data\\MODEL\\Object\\billing000.x"		//�@�r��000
#define MODEL_NAME_11	"data\\MODEL\\Object\\Bronzestatue.x"	//�@����
#define MODEL_NAME_12	"data\\MODEL\\Object\\treewood.x"		//	�؂̉�����
#define MODEL_NAME_13	"data\\MODEL\\Object\\treegrass.x"		//	�؂̏�
#define MODEL_NAME_14	"data\\MODEL\\Object\\kontena003.x"		//�@�R���e�i003
#define MODEL_NAME_15	"data\\MODEL\\Object\\kontena004.x"		//�@�R���e�i004
#define MODEL_NAME_16	"data\\MODEL\\Object\\kontena005.x"		//�@�R���e�i005
#define MODEL_NAME_17	"data\\MODEL\\Object\\grassbig.x"		//�@�傫����
#define MODEL_NAME_18	"data\\MODEL\\Object\\billing001.x"		//�@�r��001
#define MODEL_NAME_19	"data\\MODEL\\Object\\billing002.x"		//�@�r��002
#define MODEL_NAME_20	"data\\MODEL\\Object\\billing003.x"		//�@�r��003
#define MODEL_NAME_21	"data\\MODEL\\Object\\billing004.x"		//�@�r��004
#define MODEL_NAME_22	"data\\MODEL\\Object\\billing005.x"		//�@�r��005

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		*CBlock::m_pTexture[m_MaxModel] = {};		// �e�N�X�`�����ւ̃|�C���^
LPD3DXMESH				CBlock::m_pMesh[m_MaxModel] = {};			// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER			CBlock::m_pBuffMat[m_MaxModel] = {};		// �}�e���A�����ւ̃|�C���^
DWORD					CBlock::m_nNumMat[m_MaxModel] = {};			// �}�e���A�����̐�
//bool					CBlock::m_bStealthIN = false;				// �X�e���X�I�u�W�F�N�g�ɓ������ꍇ
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBlock::CBlock() : CSceneX(CScene::PRIORITY_3, CScene::OBJTYPE_BLOCK)
{
	m_modelType = MODELTYPE_KONTENA000;								//�@���f���̎��
	m_colType = COLTYPE_NONE;										//	�����蔻��̎��
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//	�ߋ��̈ʒu

	for (int nCount = 0; nCount < 6; nCount++)
	{//	���������ꏊ�̐ݒ�
		m_bHit[nCount] = false;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// ���[�h����
//=============================================================================
HRESULT CBlock::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	���f���̖��O���i�[�̂���ϐ�
	char cModelName[256];

	for (int nCntIndex = 0; nCntIndex < m_MaxModel; nCntIndex++)
	{//	���f���̍ő吔����
		switch (nCntIndex)
		{//	�ǂݍ��ރ��f���̖��O
		case MODELTYPE_GIRISUTU:
			wsprintf(cModelName, MODEL_NAME_0);
			break;
		case MODELTYPE_CYLINDER:
			wsprintf(cModelName, MODEL_NAME_1);
			break;
		case MODELTYPE_KONTENA000:					//	�R���e�i000	�F
			wsprintf(cModelName, MODEL_NAME_2);
			break;
		case MODELTYPE_SHIPOBJ:
			wsprintf(cModelName, MODEL_NAME_3);
			break;
		case MODELTYPE_GRASS:
			wsprintf(cModelName, MODEL_NAME_4);
			break;
		case MODELTYPE_KONTENA001:					//	�R���e�i001�@��
			wsprintf(cModelName, MODEL_NAME_5);
			break;
		case MODELTYPE_KONTENA002:					//	�R���e�i002	�傫���R���e�i�̐���
			wsprintf(cModelName, MODEL_NAME_6);
			break;
		case MODELTYPE_SHIPON:						//	�D��
			wsprintf(cModelName, MODEL_NAME_7);
			break;
		case MODELTYPE_STAGEEND:					//	�X�e�[�W�̃S�[��
			wsprintf(cModelName, MODEL_NAME_8);
			break;
		case MODELTYPE_DOOR:						//	�X�e�[�W�̃S�[��
			wsprintf(cModelName, MODEL_NAME_9);
			break;
		case MODELTYPE_BILLING000:					//	�r��000
			wsprintf(cModelName, MODEL_NAME_10);
			break;
		case MODELTYPE_BRONZESTATUE:				//	����
			wsprintf(cModelName, MODEL_NAME_11);
			break;
		case MODELTYPE_TREEWOOD:					//	�؂̉�����
			wsprintf(cModelName, MODEL_NAME_12);
			break;
		case MODELTYPE_TREEGRASS:					//	�؂̏㕔��
			wsprintf(cModelName, MODEL_NAME_13);
			break;
		case MODELTYPE_KONTENA003:					//	�R���e�i003	��
			wsprintf(cModelName, MODEL_NAME_14);
			break;
		case MODELTYPE_KONTENA004:					//	�R���e�i004	�傫���R���e�i�̐�
			wsprintf(cModelName, MODEL_NAME_15);
			break;
		case MODELTYPE_KONTENA005:					//	�R���e�i005	�����
			wsprintf(cModelName, MODEL_NAME_16);
			break;
		case MODELTYPE_GRASSBIG:					//	�傫����
			wsprintf(cModelName, MODEL_NAME_17);
			break;
		case	MODELTYPE_BILLING001:				//	�r��001
			wsprintf(cModelName, MODEL_NAME_18);
			break;
		case	MODELTYPE_BILLING002:				//	�r��002
			wsprintf(cModelName, MODEL_NAME_19);
			break;
		case	MODELTYPE_BILLING003:				//	�r��003
			wsprintf(cModelName, MODEL_NAME_20);
			break;
		case	MODELTYPE_BILLING004:				//	�r��004
			wsprintf(cModelName, MODEL_NAME_21);
			break;
		case MODELTYPE_BILLING005:					//	�r��005
			wsprintf(cModelName, MODEL_NAME_22);
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
				if (FAILED(D3DXCreateTextureFromFile(pDevice,pmat[tex].pTextureFilename,&m_pTexture[nCntIndex][tex])))
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
// �A�����[�h����
//=============================================================================
void CBlock::Unload(void)
{
	for (int nCntIndex = 0; nCntIndex < m_MaxModel; nCntIndex++)
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
// �m�ۏ���
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype)
{
	CBlock *pBlock = NULL;	// �|�C���^
	if (pBlock == NULL)
	{// NULL�̏ꍇ
		pBlock = new CBlock;	// �������m��

		if (pBlock != NULL)
		{// NULL�ȊO�̏ꍇ
			pBlock->Init(pos,rot, scale,modelType, coltype);		// ����������
		}
	}
	// �l��Ԃ�
	return pBlock;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype)
{
	//	���f���̕ϐ��̏�����
	CSceneX::SetInitAll(m_pTexture[modelType], m_pMesh[modelType], m_pBuffMat[modelType], m_nNumMat[modelType], pos, rot, scale);
	CSceneX::Init();				//	���f���̏�����
	CSceneX::Setpos(pos);			//	�ʒu�̐ݒ�
	CSceneX::Setrot(rot);			//	��]�̐ݒ�
	CSceneX::SetScale(scale);		//	�傫���̐ݒ�

	m_modelType = modelType;		//	���f���̎��
	m_colType = coltype;			//	���f���̔���̎��

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlock::Uninit(void)
{
	// �I������
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBlock::Update(void)
{
	for (int nCount = 0; nCount < 6; nCount++)
	{//	���������ꏊ�̐ݒ�
		m_bHit[nCount] = false;
	}
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);	//	���f���̑傫���ő�l
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);	//	���f���̑傫���ŏ��l

	D3DXVECTOR3 pos = CSceneX::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 rot = CSceneX::Getrot();			//	��]�̎擾
	D3DXVECTOR3 scale = CSceneX::GetScale();		//	�g��k���̎擾

	CSceneX::Setpos(pos);							//	�ʒu�̐ݒ�
	CSceneX::Setrot(rot);							//	��]�̐ݒ�
	CSceneX::SetScale(scale);						//	�傫���̐ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBlock::Draw(void)
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

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CBlock::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	for (int nCount = 0; nCount < 6; nCount++)
	{//	���������ꏊ�̐ݒ�
		m_bHit[nCount] = false;
	}

	bool bHit = false;

	D3DXVECTOR3 BlockPos = CSceneX::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 BlockRot = CSceneX::Getrot();			//	��]�̎擾
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);		//	�傫���̍ŏ��l

	if (BlockRot.y == 0.0f || BlockRot.y == D3DX_PI * 1.0f)
	{//	��O���������������ꍇ
		if (m_colType == COLTYPE_BOX)
		{//	�{�b�N�X�R���W�����������ꍇ
			if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) &&
				(pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x) &&
				(BlockPos.z + BlockSizeMin.z) < (pos->z + (sizeMax.z)) &&
				(pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.z))
			{// X/Z�͈͊m�F
				if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
				{// �ォ��̓����蔻��
					m_bHit[0] = true;
					bHit = true;
					pos->y = posOld->y;
					move->y = 0.0f;
				}
				else if ((BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (BlockPos.y + BlockSizeMin.y))
				{// ������̓����蔻��
					m_bHit[1] = true;
					bHit = true;
					pos->y = posOld->y;
					move->y = 0.0f;
				}
			}
			if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
			{// Y�͈͊m�F
				if ((BlockPos.z + BlockSizeMin.z) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.z))
				{// Z�͈͊m�F
					if ((BlockPos.x + BlockSizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.x))
					{// ������̓����蔻��

						m_bHit[2] = true;
						bHit = true;
						pos->x = posOld->x;
						move->x = 0;
					}
					else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.x) && (BlockPos.x + BlockSizeMax.x) <= (posOld->x + sizeMin.x))
					{// �E����̓����蔻��
						m_bHit[3] = true;
						bHit = true;
						pos->x = posOld->x;
						move->x = 0;
					}
				}
			}
			if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
			{// Y�͈͊m�F
				if ((BlockPos.x + BlockSizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.x))
				{// X�͈͊m�F
					if ((BlockPos.z + BlockSizeMin.z) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (BlockPos.z + BlockSizeMin.z))
					{// ��O����̓����蔻��
						m_bHit[4] = true;
						bHit = true;
						pos->z = posOld->z;
						move->z = 0;
					}
					else if ((pos->z + sizeMin.z) <= (BlockPos.z + BlockSizeMax.z) && (BlockPos.z + BlockSizeMax.z) <= (posOld->z + sizeMin.z))
					{// ��납��̓����蔻��
						m_bHit[5] = true;
						bHit = true;
						pos->z = posOld->z;
						move->z = 0;
					}
				}
			}
		}
	}
	else if (BlockRot.y == D3DX_PI * 0.5f || BlockRot.y == -D3DX_PI * 0.5f)
	{//	�E���������������ꍇ
		if (m_colType == COLTYPE_BOX)
		{
			if ((BlockPos.x + BlockSizeMin.z) < (pos->x + (sizeMax.x)) &&
				(pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.z) &&
				(BlockPos.z + BlockSizeMin.x) < (pos->z + (sizeMax.z)) &&
				(pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.x))
			{// X/Z�͈͊m�F
				if ((pos->y + sizeMin.y) <= (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMax.y) <= (posOld->y + sizeMin.y))
				{// �ォ��̓����蔻��
					m_bHit[0] = true;
					bHit = true;
					pos->y = posOld->y;
					move->y = 0.0f;

				}
				else if ((BlockPos.y + BlockSizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (BlockPos.y + BlockSizeMin.y))
				{// ������̓����蔻��
					m_bHit[1] = true;
					bHit = true;
					pos->y = posOld->y;
					move->y = 0.0f;
				}
			}
			if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
			{// Y�͈͊m�F
				if ((BlockPos.z + BlockSizeMin.x) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.x))
				{// Z�͈͊m�F
					if ((BlockPos.x + BlockSizeMin.z) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (BlockPos.x + BlockSizeMin.z))
					{// ������̓����蔻��

						m_bHit[2] = true;
						bHit = true;
						pos->x = posOld->x;
						move->x = 0;
					}
					else if ((pos->x + sizeMin.x) <= (BlockPos.x + BlockSizeMax.z) && (BlockPos.x + BlockSizeMax.z) <= (posOld->x + sizeMin.x))
					{// �E����̓����蔻��
						m_bHit[3] = true;
						bHit = true;
						pos->x = posOld->x;
						move->x = 0;
					}
				}
			}
			if ((pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) && (BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
			{// Y�͈͊m�F
				if ((BlockPos.x + BlockSizeMin.z) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.z))
				{// X�͈͊m�F
					if ((BlockPos.z + BlockSizeMin.x) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (BlockPos.z + BlockSizeMin.x))
					{// ��O����̓����蔻��
						m_bHit[4] = true;
						bHit = true;
						pos->z = posOld->z;
						move->z = 0;
					}
					else if ((pos->z + sizeMin.z) <= (BlockPos.z + BlockSizeMax.x) && (BlockPos.z + BlockSizeMax.x) <= (posOld->z + sizeMin.z))
					{// ��납��̓����蔻��
						m_bHit[5] = true;
						bHit = true;
						pos->z = posOld->z;
						move->z = 0;
					}
				}
			}
		}
	}
	return bHit;
}

//=============================================================================
// �X�e���X�u���b�N�̓����蔻�菈��
//=============================================================================
bool CBlock::StealthCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	D3DXVECTOR3 BlockPos = CSceneX::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 BlockRot = CSceneX::Getrot();			//	��]�̎擾
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);		//	�傫���̍ŏ��l
	if (m_colType == COLTYPE_STEALTH)
	{//	�X�e���X�R���W����
		if ((BlockPos.x + BlockSizeMin.z) < (pos->x + (sizeMax.x)) &&
			(pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.x) &&
			(pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.z) &&
			(BlockPos.z + BlockSizeMin.x) < (pos->z + (sizeMax.z)) &&
			(pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) &&
			(BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
		{// X/Z/Y�͈͊m�F
			m_bStealthIN = true;
		}
		else
		{
			m_bStealthIN = false;
		}
	}
	return m_bStealthIN;
}

//=============================================================================
// ���̃X�e�[�W��������
//=============================================================================
bool CBlock::StageNxstCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bIn = false;		//	���ɓ��������ǂ���

	D3DXVECTOR3 BlockPos = CSceneX::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 BlockRot = CSceneX::Getrot();			//	��]�̎擾
	D3DXVECTOR3 BlockSizeMax = CSceneX::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 BlockSizeMin = CSceneX::Getsize(1);		//	�傫���̍ŏ��l
	if (m_colType == COLTYPE_STAGENXST)
	{//	�X�e���X�R���W����
		if ((BlockPos.x + BlockSizeMin.z) < (pos->x + (sizeMax.x)) &&
			(pos->z + (sizeMin.z)) < (BlockPos.z + BlockSizeMax.x) &&
			(pos->x + (sizeMin.x)) < (BlockPos.x + BlockSizeMax.z) &&
			(BlockPos.z + BlockSizeMin.x) < (pos->z + (sizeMax.z)) &&
			(pos->y + sizeMin.y) < (BlockPos.y + BlockSizeMax.y) &&
			(BlockPos.y + BlockSizeMin.y) < (pos->y + sizeMax.y))
		{// X/Z/Y�͈͊m�F
			bIn = true;										//	���ɓ������ꍇ
			CGame::SetGameState(CGame::GAMESTATE_CLEAR);	//	�Q�[���N���A�ɂ���
		}
	}
	return bIn;
}