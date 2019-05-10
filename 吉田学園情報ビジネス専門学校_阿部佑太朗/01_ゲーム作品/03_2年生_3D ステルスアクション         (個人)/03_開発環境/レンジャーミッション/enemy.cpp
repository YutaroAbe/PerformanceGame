//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "enemy.h"			// �v���C���[
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "game.h"			// �Q�[��
#include "input.h"			// ����
#include "model.h"			// ���f��
#include "camera.h"			// �J����
#include "block.h"			// �u���b�N
#include "item.h"			// �A�C�e��
#include "effect.h"			// �G�t�F�N�g
#include "fade.h"			// �t�F�C�h
#include "orbit.h"			// �O��
#include "floor.h"			// ��
#include "shadow.h"			// �e
#include "wall.h"			// ��
#include "bullet3D.h"		// �e3D
#include "player.h"			// �v���C���[
#include "hpber3D.h"		//	�G��HP�o�[
#include "bullet2D.h"		//	�e2D
#include "sound.h"			//	��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME_ROBOT_000				("data\\TEXT\\enemymotion\\ROBOT_000\\enemymotion_000.txt")		//	�ǂݍ��ރe�L�X�g�̖��O
#define FILE_NAME_ROBOT_001				("data\\TEXT\\enemymotion\\ROBOT_001\\enemymotion_001.txt")		//	�ǂݍ��ރe�L�X�g�̖��O
#define FILE_NAME_ROBOT_002				("data\\TEXT\\enemymotion\\ROBOT_002\\enemymotion_002.txt")		//	�ǂݍ��ރe�L�X�g�̖��O
#define FILE_NAME_ROBOT_003				("data\\TEXT\\enemymotion\\ROBOT_003\\enemymotion_003.txt")		//	�ǂݍ��ރe�L�X�g�̖��O
#define FILE_NAME_LASTOBJ				("data\\TEXT\\enemymotion\\LASTOBJ\\lastobj.txt")				//	�ǂݍ��ރe�L�X�g�̖��O


#define GRAVITY							(0.7f)															//	�d��
#define WALK_SPEED						(0.75f)															//	�����X�s�[�h
#define MOVE_DOWNSPEED_NOR				(0.25f)															//	�����X�s�[�h
#define BULLET_DAMAGE_RANGE				(25)															//	�e�̃_���[�W�͈̔�
#define DAMEGE_COUNTER					(20)															//	�_���[�W���̃J�E���^�[
#define HOMINGRANGE						(200)															//	�Ǐ]���鋗��

//*****************************************************************************
//	�ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH					CEnemy::m_pMeshModel[MAX_NUMPARTS] = {};
LPD3DXBUFFER				CEnemy::m_pBuffMatModel[MAX_NUMPARTS] = {};
LPDIRECT3DTEXTURE9			*CEnemy::m_pTextureModel[MAX_NUMPARTS] = {};
DWORD						CEnemy::m_nNumMatModel[MAX_NUMPARTS] = {};
int							CEnemy::m_nNumPartsMax = 0;					//	�p�[�c�̍ő吔
bool CEnemy::m_bLastObDisp = false;						//	�Ō�̃I�u�W�F�N�g�����邩�ǂ���
//=============================================================================
// �G�N���X �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() : CScene(PRIORITY_3, CScene::OBJTYPE_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	����
	m_state = STATE_NONE;						//	���
	D3DXMatrixIdentity(&m_mtxWorld);			//	���[���h�}�g���b�N�X
	m_pKeyInfo[MAX_NUMMOTION] = {};				//	�L�[���ւ̃|�C���^
	m_nKey = 0;									//	���݂̃L�[�i���o�[
	m_nCountFlame = 0;							//	�t���[��
	m_bMotionEnd = false;						//	���[�V�����̏I��
	m_nMotionType = 0;							//	���݂̃��[�V�����^�C�v
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�v���C���[�̑傫���̍ő�l
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�v���C���[�̑傫���̍ŏ��l
	m_nCouterFreamMax[MAX_NUMMOTION] = {};		//	���[�V�����̃t���[���̍��v�l
	m_nCntNumMosion = 0;						//	�e�L�X�g�ɏ�����Ă��郂�[�V�����̐�
	m_nMotionTypeOld = 0;						//	���[�V�����̉ߋ��̎��
	m_bHit = false;								//	�����������ǂ���
	m_nLife = 0;								//	���C�t
	m_nDameCuter = 0;							//	�_���[�W�J�E���^�[
	m_nDispCuter = 0;							//	���񂾂Ƃ��̃J�E���^�[
	m_AIEnemy = AI_NONE;						//	�G��AI�̏�����
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�G�̍ŏ��̈ʒu
	m_nAISelect = 0;							//	�����̑I��
	m_bOtherEnemyHit = false;					//	�G���m���������ꍇ
	m_pShadow = NULL;							//	�e�̏�����
	m_pHpBer3D = NULL;							//	HP�o�[�̏�����
	m_fAngle = 0.0f;							//	�p�x
	m_bLand = false;							//	����Ă��Ȃ�
	m_bPStealthMode = false;					//	�v���C���[���X�e���X��ԓ����Ă��邩�ǂ���
	m_LengthDawn = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//	�v���C���[�Ƃ̋�����Z������
	m_nMoveLength = 0;							//	�ړ����鋗��
	m_nType = 0;								//	���
	m_fNoneSpeed = 0;							//	�������Ă��Ȃ����̑���
	m_fFormingSpeed = 0;						//	�Ǐ]���鎞�̑���
	m_bWallHit = false;							//	�ǂɓ����������ǂ���

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nType, int nMoveLength,float fNoneSpeed, float fFormingSpeed, ENEMY_AI nAISelect)
{
	//�G�̃|�C���^
	CEnemy *pEnemy = {};
	if (pEnemy == NULL)
	{//	�G���g���Ă��Ȃ������ꍇ
		if (nType == 0)
		{//	�ʏ�̓G
			pEnemy = new CEnemyRobotNomal;
		}
		else if (nType == 1)
		{//	�e�����G
			pEnemy = new CEnemyRobotBullet;
		}
		else if (nType == 2)
		{//	���̓G
			pEnemy = new CEnemyRobotSpine;
		}
		else if (nType == 3)
		{//	���ɂ����G
			pEnemy = new CEnemyRobotUndeBulletr;
		}
		else if (nType == 99)
		{//	�Ō�̃I�u�W�F�N�g
			pEnemy = new CEnemyLastObj;
		}
		else
		{//	����ȊO�̐�����������
			pEnemy = new CEnemyRobotNomal;
		}
		if (pEnemy != NULL)
		{//	������
			pEnemy->m_pos = pos;						//	�ʒu�̐ݒ�
			pEnemy->Setpos(pos);
			pEnemy->m_rot = rot;						//	��]�̐ݒ�
			pEnemy->m_nLife = nLife;					//	���C�t�̐ݒ�
			pEnemy->m_nType = nType;					//	�G�̎��
			pEnemy->m_nAISelect = nAISelect;			//	�G�̓����̑I��
			pEnemy->m_nMoveLength = nMoveLength;		//	�ړ����鋗��
			pEnemy->m_fNoneSpeed = fNoneSpeed;			//	�������Ă��Ȃ����̑���
			pEnemy->m_fFormingSpeed = fFormingSpeed;	//	�Ǐ]���鎞�̑���
			pEnemy->Init();								//	����������
		}
	}
	//����Ԃ�
	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	m_bLastObDisp = false;	//�Ō�̃I�u�W�F�N�g�����������ǂ���
	if (m_nType == 0)
	{// ����ݒ� 000
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	 // �g��k���p�ϐ�
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 70.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 1)
	{// ����ݒ� 001
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	 // �g��k���p�ϐ�

		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 85.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 2)
	{// ����ݒ� 001
		m_Scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);	 // �g��k���p�ϐ�
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 60.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 3)
	{// ����ݒ� 001
		m_Scale = D3DXVECTOR3(1.2f, 1.2f, 1.2f);	 // �g��k���p�ϐ�
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 50.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 99)
	{// ����ݒ� �Ō�̃I�u�W�F�N�g
		m_Scale = D3DXVECTOR3(5.2f, 5.2f, 5.2f);	 // �g��k���p�ϐ�
		m_vtxMax = D3DXVECTOR3(29.0f *m_Scale.x, 20.0f*m_Scale.y, 17.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-29.0f*m_Scale.x, 0.0f*m_Scale.y, -17.0f*m_Scale.z);
	}
	//�G���̓ǂݍ���
	FileLoad();
	for (int nCnterMosion = 0; nCnterMosion < MAX_NUMMOTION; nCnterMosion++)
	{//	���[�V�����̊m�ۉ�
		if (m_nCntNumMosion >= nCnterMosion)
		{//	���[�V�����̃e�L�X�g�ɏ�����Ă����ޕ���
			for (int nCounter = 0; nCounter < m_aMotionInfo[nCnterMosion].nNumKey; nCounter++)
			{//	���[�V�����̃L�[������
				m_nCouterFreamMax[nCnterMosion] += m_aMotionInfo[nCnterMosion].aKayInfo[nCounter].nFrame;
			}
		}
	}
	if (m_nType == 1|| m_nType == 3)
	{// ����ݒ� 001
	 //	�e�̐���
		if (m_pShadow == NULL)
		{//	�e���g���Ă��Ȃ�������
			m_pShadow = CShadow::Create(m_pos, m_rot, D3DXVECTOR3(m_vtxMax.x, 0.0f, m_vtxMax.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
		}
	}
	CPlayer *pPlayer = CGame::GetPlayer();				//	�v���C���[�̏��̎擾
	if (pPlayer != NULL)
	{//	�v���C���[���g���Ă����ꍇ
	 //	HP�o�[�̐���
		if (m_pHpBer3D == NULL)
		{//	HP�o�[���g���Ă��Ȃ�������
			m_pHpBer3D =
				CHpBer3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y + 5, m_pos.z), m_rot,
					D3DXVECTOR3(5.0f*m_nLife, 5.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	m_InitPos = m_pos;		//	�����̈ʒu�̕ۑ�
	m_nNumPartsMax = m_nNumParts;		//	�p�[�c�̍ő吔�̐ݒ�
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{

	if (m_pShadow != NULL)
	{//	�e���g�p���ꂽ�������΂�
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
	if (m_pHpBer3D != NULL)
	{//	HP�o�[���g�p���ꂽ�������΂�
		m_pHpBer3D->Uninit();
		m_pHpBer3D = NULL;
	}

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{//	���f���̐���
		if (m_apModel[nCnt] != NULL)
		{//	�I������
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	//	�v���C���[�̊J��
	CGame::SetEnemy();

	// �t���O�𗧂Ă�
	CScene::SetDeath();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �ʒu�ۑ�
	m_posOld = m_pos;
	//	���[�V�����̕ۑ�
	m_nMotionTypeOld = m_nMotionType;

	switch (m_state)
	{// ���
	 //-----------------------------------------
	 //	�ʏ�
	 //-----------------------------------------
	case STATE_NONE:
		if (m_pShadow != NULL)
		{//	�e���g�p���ꂽ�������΂�
		 //	�e�̈ʒu�̐ݒ�
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_pos.y, m_apModel[0]->GetMtxWorld()._43));
		}
		if (m_pHpBer3D != NULL)
		{//	�e���g�p���ꂽ�������΂�
		 //	�e�̈ʒu�̐ݒ�
			m_pHpBer3D->Setpos(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y + 7, m_pos.z));
		}
		break;
		//-----------------------------------------
		// �_���[�W
		//-----------------------------------------
	case STATE_DAMAGE:
		m_nDameCuter++;			//	�_���[�W�J�E���^�[
		if (m_nDameCuter <= DAMEGE_COUNTER / 2)
		{//	�_���[�W�t���[��/2�ȓ��̐��l�������ꍇ
			m_Scale.x += 0.0065f;			//	�傫����ς���X��
			m_Scale.z += 0.0065f;			//	�傫����ς���Z��
			m_Scale.y += 0.0095f;			//	�傫����ς���Y��
		}
		else if (m_nDameCuter <= DAMEGE_COUNTER)
		{//	�_���[�W�̃t���[��
			m_Scale.x -= 0.0065f;			//	�傫����ς���X��
			m_Scale.z -= 0.0065f;			//	�傫����ς���Z��
			m_Scale.y -= 0.0095f;			//	�傫����ς���Y��
		}
		else
		{//	�_���[�W�J�E���^�[����������ʏ�ɂ��ǂ�
			m_nDameCuter = 0;					//	�_���[�W�J�E���^�[�̏�����
			m_state = STATE_NONE;				//	�X�e�[�^�X��ʏ�
		}
		break;
		//-----------------------------------------
		// ���S
		//-----------------------------------------
	case STATE_DEATH:
		if (m_nType ==99)
		{//�Ō�̃I�u�W�F�N�g����ꂽ�Ƃ�
		 //	�S�[���u���b�N�̐���
			CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, 5500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 0.7f, 2.0f), (CBlock::MODELTYPE)9, (CBlock::COLTYPE)3);
			m_bLastObDisp = true;
		}
		m_nDispCuter++;
		if (m_nDispCuter <= 15)
		{//	���񂾂Ƃ��̃J�E���^�[
			m_Scale.x += 0.0075f;				//	�傫����ς���X��
			m_Scale.z += 0.0075f;				//	�傫����ς���Z��
			m_Scale.y += 0.0105f;				//	�傫����ς���Y��
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y / 2, m_pos.z), 2, 2);	//	���̃G�t�F�N�g
		}
		if (m_nDispCuter < 20 && m_nDispCuter > 15)
		{//	���񂾂Ƃ��̃J�E���^�[
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y / 2, m_pos.z), 1, 0);	//	���̃G�t�F�N�g
		}
		break;
	}
	//	�ʒu�̉��Z
	m_pos += m_move;

	//	�����蔻��̊Ǘ�
	ManagementCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);

	//���[�V�����X�V
	UpdateMotion();


	if (m_state == STATE_DEATH && m_nDispCuter >=20)
	{//	�G�����񂾏ꍇ�@���@�J�E���^�[���w��̐��l�ȏア�����ꍇ
		Uninit();							//	�G�������鎞
	}

	CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);	// ���݁@
	CScene *pSceneNext = NULL;								// ��
	if (m_bLastObDisp == true)
	{//	�Ō�̃I�u�W�F�N�g���������ꍇ
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y , m_pos.z), 1, 0);	//	���̃G�t�F�N�g
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y+10 , m_pos.z), 1, 0);	//	���̃G�t�F�N�g

		Uninit();							//	�G�������鎞
	}
#ifdef _DEBUG
	//CManager::m_CDebugProcRight->Print("\n----------�G�l�~�[�̃X�e�[�^�X------------------");
	CManager::m_CDebugProcLeft->Print("\n�G�l�~�[�̈ʒu  ( %.1f : %.1f  : %.1f)", m_pos.x, m_pos.y, m_pos.z);
	//CManager::m_CDebugProcLeft->Print("\n�G�l�~�[�̓����@( %.4f : %.4f  : %.4f)", m_move.x, m_move.y, m_move.z);
	//CManager::m_CDebugProcRight->Print("\n�G�l�~�[�̌����@( %.1f : %.1f  : %.1f)", m_rot.x, m_rot.y, m_rot.z);
	//CManager::m_CDebugProcLeft->Print("\n���݂̃��[�V�����@( %d)", m_nMotionType);
	//CManager::m_CDebugProcRight->Print("\n-------------------------------------------------");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//	�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, matScale, mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�g��k���s��̍쐬
	D3DXMatrixScaling(&matScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &matScale);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{//	�p�[�c����
		if (m_apModel[nCnt] != NULL)
		{//	�`�揈��
			m_apModel[nCnt]->Draw();
		}
	}

}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	return S_OK;
}

//=============================================================================
// �j������
//=============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCntIndex = 0; nCntIndex < m_nNumPartsMax; nCntIndex++)
	{//	���f���̍ő吔����
	 // �e�N�X�`���̔j��
		for (DWORD tex = 0; tex < m_nNumMatModel[nCntIndex]; tex++)
		{// �J�E���g
			if (m_pTextureModel[nCntIndex][tex] != NULL)
			{// NULL�ȊO�̏ꍇ
				m_pTextureModel[nCntIndex][tex]->Release();		// �������̉��
				m_pTextureModel[nCntIndex][tex] = NULL;			// NULL��
			}
		}
		//	�e�N�X�`���̊J��
		delete[] m_pTextureModel[nCntIndex];
		m_pTextureModel[nCntIndex] = NULL;

		// �}�e���A���̊J��
		if (m_pBuffMatModel[nCntIndex] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pBuffMatModel[nCntIndex]->Release();				// �������̉��
			m_pBuffMatModel[nCntIndex] = NULL;					// NULL��
		}

		// �}�e���A���̊J��
		if (m_pMeshModel[nCntIndex] != NULL)
		{// NULL�ȊO�̏ꍇ
			m_pMeshModel[nCntIndex]->Release();					// �������̉��
			m_pMeshModel[nCntIndex] = NULL;						// NULL��
		}
		// �}�e���A���̏�����
		m_nNumMatModel[nCntIndex] = 0;
	}
}


//=============================================================================
//	�p�x�����Z����
//=============================================================================
void CEnemy::ManagementAddRod(D3DXVECTOR3 rotDest)
{
	//�ړI�̌����̏C��
	if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2.0f;
	}
	else if (rotDest.y > D3DX_PI)
	{
		rotDest.y -= D3DX_PI * 2.0f;
	}
	//	��]�̊p�x�̃u�����h
	float fAngle = rotDest.y - m_rot.y;
	if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	else if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	//	��]�̃u�����h����l����]�ɑ��
	m_rot.y += fAngle * 0.1f;
	//�����̏C��
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	//	��]�̃u�����h����l����]�ɑ��
	m_rot.y += fAngle * 0.085f;

}

//=============================================================================
//	�����蔻��̑���
//=============================================================================
void CEnemy::ManagementCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// ���݁@
	CScene *pSceneNext = NULL;								// ��

	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
	 // ���I�u�W�F�N�g����ۑ�
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
		{//	���������ꍇ
			CFloor *pFloor = (CFloor*)pScene;				//	���ɃL���X�g
			pFloor->Collision(pos, posOld, move, sizeMax, sizeMin);		// �����蔻��
		}
		// ���̃I�u�W�F�N�g�ɐݒ�
		pScene = pSceneNext;
	}

	// �V�[��
	pScene = CScene::GetScene(CScene::PRIORITY_3);	// ���݁@
	pSceneNext = NULL;								// ��

	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
	 // ���I�u�W�F�N�g����ۑ�
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{// �I�u�W�F�N�g�^�C�v���u���b�N��������
			CBlock *pBlock = (CBlock*)pScene;									// �u���b�N�ɃL���X�g
			if (pBlock->Collision(pos, posOld, move, sizeMax, sizeMin) == true)
			{// �����蔻��
				m_bWallHit = true;		//	�ǂɓ�������
			}

			bool *bLand = pBlock->GetHit();

		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
		{//	�ǂ������ꍇ
			CWall *pWall = (CWall*)pScene;					//	�ǂɃL���X�g
			if (pWall->Collision(pos, posOld, move, sizeMax, sizeMin)==true)		// �����蔻��
			{//	�ǂɓ��������ꍇ
				m_bWallHit = true;		//	�ǂɓ�������
			}
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_BULLET3D)
		{
			CBullet3D *pBullet3D = (CBullet3D*)pScene;				//	�e�ɃL���X�g
			D3DXVECTOR3 BulletPos = pBullet3D->Getpos();			//	�e�̈ʒu
			int nCounter = pBullet3D->GetDispCut();					//	�e��������܂ł̃J�E���^�[
			if (nCounter >= BULLET_USE_VALSE)
			{//	�e��������܂ł̎��Ԓ�������
				if (BulletPos.x - BULLET_DAMAGE_RANGE < m_pos.x + m_vtxMax.x &&
					m_pos.x + m_vtxMin.x < BulletPos.x + BULLET_DAMAGE_RANGE &&
					BulletPos.y - BULLET_DAMAGE_RANGE < m_pos.y + m_vtxMax.y &&
					m_pos.y + m_vtxMin.y < BulletPos.y + BULLET_DAMAGE_RANGE &&
					BulletPos.z - BULLET_DAMAGE_RANGE < m_pos.z + m_vtxMax.z &&
					m_pos.z + m_vtxMin.z < BulletPos.z + BULLET_DAMAGE_RANGE)
				{//	�����͈̔͂ɓ������ꍇ
					HitDamege(2);	//	�_���[�W
				}
			}
		}
		else if (pScene->GetObjType() == CScene3D::OBJTYPE_ENEMY)
		{
			CEnemy *pEnemy = (CEnemy*)pScene;
			// �G���m�̓����蔻��
			pEnemy->OtherEnemyCollision(pos, posOld, move, sizeMax, sizeMin);		// �����蔻��
		}
		// ���̃I�u�W�F�N�g�ɐݒ�
		pScene = pSceneNext;
	}

	pScene = CScene::GetScene(CScene::PRIORITY_4);	// ���݁@
	pSceneNext = NULL;								// ��

	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
	 // ���I�u�W�F�N�g����ۑ�
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{// �I�u�W�F�N�g�^�C�v���u���b�N��������
			CPlayer *pPlayer = (CPlayer*)pScene;				// �u���b�N�ɃL���X�g
			D3DXVECTOR3 Playerrot = pPlayer->Getrot();			//	�����̎擾
			bool bAtkLastHit = pPlayer->GetLastHit();			//	�ŏI�U���̎擾
			bool bPlayerInBlock = pPlayer->GetStealthMode();		//	�X�e���X���[�h�̎擾
			m_bPStealthMode = bPlayerInBlock;						//	�X�e���X���[�h�̐ݒ�
																	//	�U�������蔻��
			if (pPlayer->AttackCollsion(pos, posOld, move, sizeMax, sizeMin)== true)
			{//	�U���͈͓̔��ɓ������ꍇ
				HitDamege(1);										//	�_���[�W
				if (bAtkLastHit == true)
				{//	�ŏI�U�������������ꍇ
					//m_move.x += Playerrot.y * -10.0f;				//	�����̉��Z
					//m_rotDest.y = Playerrot.y * -1;					//	�����̐؂�ւ�
				}

			}
			// �����蔻��
			pPlayer->BoxCollision(pos, posOld, move, sizeMax, sizeMin);		// �����蔻��
		}
		// ���̃I�u�W�F�N�g�ɐݒ�
		pScene = pSceneNext;
	}

}

//==============================================================================
//	�_���[�W�v�Z
//==============================================================================
void CEnemy::HitDamege(int nDamage)
{
	int nValue = m_nLife - nDamage;	//	�_���[�W��HP�ɂЂ�
	m_nLife = nValue;				//	�v�Z�����l�����C�t�ɑ��
	if (m_nLife <= 0)
	{//	���C�t��0�ȉ��ɂȂ����ꍇ
		m_state = STATE_DEATH;		//	�X�e�[�^�X�����S��Ԃɕς���
	}
	else
	{//	HP���܂��c���Ă�����
		if (m_pHpBer3D != NULL)
		{//	��P�o�[���g�p����Ă����ꍇ
			m_pHpBer3D->SizeChange(nDamage, this);				//	Hp�΁[�̃T�C�Y�ύX
		}
		m_state = STATE_DAMAGE;								//	�_���[�W��Ԃɐ؂�ւ���
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CEnemy::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *m_move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	//	�������Ă��邩�̐ݒ�
	m_bHit = false;
	//	����Ă��邩�ǂ���
	m_bLand = false;
	D3DXVECTOR3 EnemyPos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 EnemyMove = CEnemy::Getmove();			//	�ʒu�̎擾
	D3DXVECTOR3 EnemyRot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 EnemySizeMax = CEnemy::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 EnemySizeMin = CEnemy::Getsize(1);		//	�傫���̍ŏ��l

	if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) &&
		(pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x) &&
		(EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) &&
		(pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
	{// X/Z�͈͊m�F
		if ((pos->y + sizeMin.y) <= (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMax.y) <= (posOld->y + sizeMin.y))
		{// �ォ��̓����蔻��
			m_bHit = true;
			m_bLand = true;
			pos->y = EnemyPos.y + EnemySizeMax.y + (sizeMin.y);
			m_move->y = 0.0f;
			pos->x += EnemyMove.x;
			pos->z += EnemyMove.z;

		}
		else if ((EnemyPos.y + EnemySizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (EnemyPos.y + EnemySizeMin.y))
		{// ������̓����蔻��
			m_bHit = true;
			pos->y = posOld->y;
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
		{// Z�͈͊m�F
			if ((EnemyPos.x + EnemySizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (EnemyPos.x + EnemySizeMin.x))
			{// ������̓����蔻��
				m_bHit = true;
				pos->x = EnemyPos.x + EnemySizeMin.x + (sizeMin.x);
				m_move->x = 0.0f;
			}
			else if ((pos->x + sizeMin.x) <= (EnemyPos.x + EnemySizeMax.x) && (EnemyPos.x + EnemySizeMax.x) <= (posOld->x + sizeMin.x))
			{// �E����̓����蔻��
				m_bHit = true;
				pos->x = EnemyPos.x + EnemySizeMax.x + (sizeMax.x);
				m_move->x = 0.0f;
			}
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x))
		{// X�͈͊m�F
			if ((EnemyPos.z + EnemySizeMin.z) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (EnemyPos.z + EnemySizeMin.z))
			{// ��O����̓����蔻��
				m_bHit = true;
				pos->z = EnemyPos.z + EnemySizeMin.z + (sizeMin.z);
				m_move->z = 0.0f;
			}
			else if ((pos->z + sizeMin.z) <= (EnemyPos.z + EnemySizeMax.z) && (EnemyPos.z + EnemySizeMax.z) <= (posOld->z + sizeMin.z))
			{// ��납��̓����蔻��
				m_bHit = true;
				pos->z = EnemyPos.z + EnemySizeMax.z + (sizeMax.z);
				m_move->z = 0.0f;

			}
		}
	}
}

//=============================================================================
// �G���m�̓����蔻�菈��
//=============================================================================
void CEnemy::OtherEnemyCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *m_move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	m_bOtherEnemyHit = false;	//	�������Ă��Ȃ�
	D3DXVECTOR3 EnemyPos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 EnemyRot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 EnemySizeMax = CEnemy::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 EnemySizeMin = CEnemy::Getsize(1);		//	�傫���̍ŏ��l

	if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) &&
		(pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x) &&
		(EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) &&
		(pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
	{// X/Z�͈͊m�F
		if ((pos->y + sizeMin.y) <= (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMax.y) <= (posOld->y + sizeMin.y))
		{// �ォ��̓����蔻��
			m_bOtherEnemyHit = true;	//	�������Ă���
			pos->y = EnemyPos.y + EnemySizeMax.y + (sizeMin.y);
			m_move->y = 0.0f;
		}
		else if ((EnemyPos.y + EnemySizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (EnemyPos.y + EnemySizeMin.y))
		{// ������̓����蔻��
			pos->y = posOld->y;
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
		{// Z�͈͊m�F
			if ((EnemyPos.x + EnemySizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (EnemyPos.x + EnemySizeMin.x))
			{// ������̓����蔻��
				m_bOtherEnemyHit = true;	//	�������Ă���
				pos->x = EnemyPos.x + EnemySizeMin.x + (sizeMin.x);
				m_move->x = 0.0f;
			}
			else if ((pos->x + sizeMin.x) <= (EnemyPos.x + EnemySizeMax.x) && (EnemyPos.x + EnemySizeMax.x) <= (posOld->x + sizeMin.x))
			{// �E����̓����蔻��
				m_bOtherEnemyHit = true;	//	�������Ă���
				pos->x = EnemyPos.x + EnemySizeMax.x + (sizeMax.x);
				m_move->x = 0.0f;
			}
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x))
		{// X�͈͊m�F
			if ((EnemyPos.z + EnemySizeMin.z) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (EnemyPos.z + EnemySizeMin.z))
			{// ��O����̓����蔻��
				m_bOtherEnemyHit = true;	//	�������Ă���
				pos->z = EnemyPos.z + EnemySizeMin.z + (sizeMin.z);
				m_move->z = 0.0f;
			}
			else if ((pos->z + sizeMin.z) <= (EnemyPos.z + EnemySizeMax.z) && (EnemyPos.z + EnemySizeMax.z) <= (posOld->z + sizeMin.z))
			{// ��납��̓����蔻��
				m_bOtherEnemyHit = true;	//	�������Ă���
				pos->z = EnemyPos.z + EnemySizeMax.z + (sizeMax.z);
				m_move->z = 0.0f;
			}
		}
	}
}


//=============================================================================
// ���[�V�����̍X�V
//=============================================================================
void CEnemy::UpdateMotion(void)
{
	//	���[�V����
	KEY *pKey, *pNextKey;	//	�L�[�Ǝ��̃L�[
	float fRateMotion;		//	���[�V�����̑��Βl
	float fDiffMotion;		//	�L�[�Ǝ��̃L�[�̍���
	D3DXVECTOR3 posmotion;	//	���[�V�����̈ʒu
	D3DXVECTOR3 rotmotion;	//	���[�V�����̉�]

	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{//	�L�[���ő吔������Ȃ��悤��
		m_nKey = 0;
	}

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{//	�p�[�c���̃��[�V�����X�V
		if (m_apModel[nCntParts] != NULL)
		{
			if (m_nMotionType == m_nMotionTypeOld)
			{//	���̎�ނ��ߋ��̎�ނ������������ꍇ
			 //	���݂̃L�[���擾
				pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
				//	���̃L�[���擾
				pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

				//	���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

				//	��]�̎Z�o
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

				//	�ʒu�̎Z�o
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				//POS
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				//POS
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);

				//	�p�[�c�𓮂���
				m_apModel[nCntParts]->Setrot(rotmotion);
				//	�ʒu��ݒ肷��
				m_apModel[nCntParts]->Setpos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x, m_OffSetPos[nCntParts].y + posmotion.y, m_OffSetPos[nCntParts].z + posmotion.z));
			}
		}
	}
	//	���[�v�̔���
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{//	���[�v���邩���Ȃ���
	case true:

		//�@���[�v����ꍇ
		//	�t���[����i�߂�
		m_nCountFlame++;
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{//	�L�[�̍X�V
			if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
			{//	�O�̃L�[�ƌ��݂̃L�[�������ꍇ
				m_nKey = 0;
			}
			else
			{//	���݂̃L�[��
				m_nKey += 1;
			}
			//	�t���[����������������
			m_nCountFlame = 0;
		}
		break;
	case false:
		//	���[�v���Ȃ�
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//	�t���[����i�߂�
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{//	�O�̃L�[�ƌ��݂̃L�[�������ꍇ���[�V�������~�߂�
			m_bMotionEnd = true;
		}
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{//	�L�[�̍X�V
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{//	���݂̃L�[���傫�������ꍇ
				m_nKey += 1;	//	�L�[��i�߂�
			}
			//	�t���[����������������
			m_nCountFlame = 0;
		}
		break;
	}
}
//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
void CEnemy::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile = NULL;		//	�t�@�C���|�C���^
	char *pStrcur;			//	���݂̐擪�̕�����
	char aLine[256];		//	������
	char aStr[256];			//	�ꎞ�ۑ�������
	int nIndex = 0;			//	���݂̃C���f�b�N�X
	int nWord = 0;			//	�|�b�v�ŕԂ��ꂽ�l��ێ�

							//�t�@�C�����J�� �ǂݍ���
	if (m_nType == 0)
	{//	��� �ʏ�̓G
		pFile = fopen(FILE_NAME_ROBOT_000, "r");
	}
	else if (m_nType == 1)
	{//	��ށ@�e�����G
		pFile = fopen(FILE_NAME_ROBOT_001, "r");
	}
	else if (m_nType == 2)
	{//	��ށ@�e�����G
		pFile = fopen(FILE_NAME_ROBOT_002, "r");
	}
	else if (m_nType == 3)
	{//	��ށ@�e�����G
		pFile = fopen(FILE_NAME_ROBOT_003, "r");
	}
	else if (m_nType == 99)
	{//	��ށ@�Ō�̃I�u�W�F�N�g
		pFile = fopen(FILE_NAME_LASTOBJ, "r");
	}
	else
	{
		pFile = fopen(FILE_NAME_ROBOT_000, "r");
	}
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_NUMMOTION; nCntMotion++)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);
			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				m_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������߂�
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//���o��
						pStrcur += strlen("MODEL_FILENAME = ");
						//�������ݒ�
						strcpy(aStr, pStrcur);
						//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
						int nNullNum = PopString(pStrcur, &aStr[0]);
						//����������߂�
						strcpy(aStr, pStrcur);
						//�Ō�̕�����NULL����������
						aStr[nNullNum - 1] = '\0';
						//�Ώۂ̕����񂩂甲���o��
						strcpy(&m_aFileNameModel[nCntModel][0], aStr);
						// X�t�@�C���̓ǂݍ���
						D3DXLoadMeshFromX(&m_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);

						D3DXMATERIAL *pmat;									// �}�e���A���f�[�^�ւ̃|�C���^
						D3DMATERIAL9 *matDef;								// ���݂̃}�e���A���ۑ��p
						pmat = (D3DXMATERIAL*)m_pBuffMatModel[nCntModel]->GetBufferPointer();
						matDef = new D3DMATERIAL9[m_nNumMatModel[nCntModel]];						//	�}�e���A���̃������̊m��
						m_pTextureModel[nCntModel] = new LPDIRECT3DTEXTURE9[m_nNumMatModel[nCntModel]];	//	�e�N�X�`���̃������̊m��

						for (DWORD tex = 0; tex < m_nNumMatModel[nCntModel]; tex++)
						{// �J�E���g
							matDef[tex] = pmat[tex].MatD3D;						//�@�}�e���A���̃v���p�e�B���L�q���� D3DMATERIAL9 �\����
							matDef[tex].Ambient = matDef[tex].Diffuse;			//�@���̒��ړ����镔���̐F�����𓖂���Ȃ������Ɠ���������
							m_pTextureModel[nCntModel][tex] = NULL;				//	�e�N�X�`��������ɂ���
							if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
							{// �e�N�X�`�����g�p���Ă��� & ������̒�����0�ȏゾ������
								if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTextureModel[nCntModel][tex])))
								{
								}
							}
						}
						//	�}�e���A���̊J��
						delete[] matDef;
						matDef = NULL;
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_PARTS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEX��ǂݍ���
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{//	�ԍ��̐ݒ�
								pStrcur += strlen("INDEX = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								nIndex = atoi(pStrcur);
							}
							//PARENT��ǂݍ���
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{//	�e�̐ݒ�@
								pStrcur += strlen("PARENT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{//	�I�t�Z�b�g�ʒu�ݒ�
								pStrcur += strlen("POS = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{//	��]�̐ݒ�
								pStrcur += strlen("ROT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);
							}
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{//	�p�[�c�̐ݒ�̏I��

							 //���f���𐶐�	�I�t�Z�b�g�ݒ�
								m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_aKayOffset[nIndex].fposX, m_aKayOffset[nIndex].fposY, m_aKayOffset[nIndex].fposZ),
									D3DXVECTOR3(m_aKayOffset[nIndex].frotX, m_aKayOffset[nIndex].frotY, m_aKayOffset[nIndex].frotZ));
								//�ʒu���
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//���f�������蓖��
								m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{//���f���̐e�̐ݒ�
									m_apModel[nIndex]->SetParent(NULL);
								}
								else
								{//���f���̎q�̐ݒ�
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}
								break;
							}
						}
					}
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{//�L�����N�^�[�Z�b�g�I��
						break;
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{//���[�V�����ݒ�
				m_nCntNumMosion += 1;			//	���[�V�����̐��̉��Z
												//���o��
				pStrcur += strlen("MOTIONSET");
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{//	���[�V�����̃��[�v���邩���Ȃ���
						pStrcur += strlen("LOOP = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
					}
					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_KEY = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
						//����������o��
						strcpy(aStr, pStrcur);
					}

					//�L�[�̐ݒ�
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{//	�L�[�̐ݒ�
						 //���o��
							pStrcur += strlen("KEYSET");
							//������̐擪��ݒ�
							strcpy(aStr, pStrcur);
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{//	�t���[���̐ݒ�
								pStrcur += strlen("FRAME = ");
								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
							}
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{//�p�[�c����
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{//	�L�[�̐ݒ�
								 //������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);
									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{//	�ʒu�̐ݒ�
									 //���o��
										pStrcur += strlen("POS = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{//	��]�̐ݒ�
									 //���o��
										pStrcur += strlen("ROT = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{//	�L�[�̐ݒ�̏I��
									 //���o��
										pStrcur += strlen("END_KEY");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
										//�p�[�c�̃J�E���g��i�߂�
										nCntParts++;
									}
								}
								else
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{//	�L�[�̐ݒ�̏I��
							 //������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
								//�J�E���g��i�߂�
								nCntKey++;
							}
						}
						else
						{//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{//���[�V�����̐ݒ�̏I��
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						break;
					}
				}
			}
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{//r�e�L�X�g�ł̏I��
				break;
			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
}

//=============================================================================
//	1�s�ǂݍ���
//=============================================================================
char *CEnemy::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{//	�����񂪁@���@�������ꍇ
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{//	�����񂪁@\t�@�������ꍇ
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{//	while������
					break;
				}
			}
			//	while������
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{//	�����񂪁@�󔒁@�������ꍇ
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{//	�����񂪁@�󔒁@�������ꍇ
					pDst += strlen(" ");
				}
				else
				{//	while������
					break;
				}
			}
			//	while������
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{//	�����񂪁@\n�@�������ꍇ
			pDst += strlen("\n");
		}
		else
		{//	while������
			break;
		}
	}
	//	������̒l��Ԃ�
	return pDst;
}

//=============================================================================
//	�s�̐擪���擾
//=============================================================================
char * CEnemy::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{//	�����񂪁@�󔒁@�������ꍇ
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{//	�����񂪁@�󔒁@�������ꍇ
					pStr += strlen(" ");
				}
				else
				{//	while������
					break;
				}
				//	while������
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{//	�����񂪁@\t�@�������ꍇ
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{//	�����񂪁@\t�@�������ꍇ
					pStr += strlen("\t");
				}
				else
				{//	while������
					break;
				}
			}
		}
		else
		{//	while������
			break;
		}
	}
	//	������̒l��Ԃ�
	return pStr;
}

//=============================================================================
//	�s�̍Ō��؂�̂�
//=============================================================================
int CEnemy::PopString(char * pStr, char * pDest)
{
	int nStr = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nStr += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{//	�����񂪁@�󔒁@�������ꍇ
			pStr = "\0";
			nStr += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{//	�����񂪁@\t�@�������ꍇ
			pStr = "\0";
			nStr += strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{//	�����񂪁@\n�@�������ꍇ
			nStr += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nStr;
}



//---------------------------------------------------------------------------
//	�v���C���[�Ƃ̋���
//---------------------------------------------------------------------------
float CEnemy::GetLength(void)
{
	//	�v���C���[�Ƃ̊p�x�v�Z-----------------------------
	CPlayer *pPlayer = CGame::GetPlayer();				//	�v���C���[�̏��̎擾
	float fAngle = 0.0f;								//	�p�x
	float fDiffese = 0.0f;								//	����
	D3DXVECTOR3 VecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�x�N�g���̌v�Z�p
	bool bPlayerSquat = false;							//	���Ⴊ��ł��邩�ǂ���
	float	fLength = 0;	//	����

	if (pPlayer != NULL && m_bLand == false)
	{
		//	�v���C���[�ƓG�Ƃ̋��������߂�
		VecA = pPlayer->Getpos() - m_pos;
		//	�v���C���[�ƓG�̊p�x�����߂�
		fAngle = atan2f(VecA.x, VecA.z);
		//	���݂̊p�x�ƖړI�̊p�x�̍������߂�
		fDiffese = fAngle - m_fAngle;
		//	�����̏C��
		if (fDiffese < -D3DX_PI)
		{
			fDiffese += D3DX_PI * 2.0f;
		}
		if (fDiffese > D3DX_PI)
		{
			fDiffese -= D3DX_PI * 2.0f;
		}
		//	�p�x�̕ω��ʂ����߂�
		m_fAngle += fDiffese;
		//	�p�x�̏C��
		if (m_fAngle < -D3DX_PI)
		{
			m_fAngle += D3DX_PI * 2.0f;
		}
		if (m_fAngle > D3DX_PI)
		{
			m_fAngle -= D3DX_PI * 2.0f;
		}
		//	�v���C���[�̂��Ⴊ��ł����Ԃ̎擾
		bPlayerSquat = pPlayer->GetSquat();
		if (bPlayerSquat == true)
		{//	���Ⴊ��ł����ꍇ
		 //	�v���C���[�Ƃ̋����v�Z[a2 + b2 = c2]-----------------------------
			fLength = sqrtf((pPlayer->Getpos().x - m_pos.x - m_LengthDawn.x)*(pPlayer->Getpos().x - m_pos.x - m_LengthDawn.x) +
				(pPlayer->Getpos().z - m_pos.z - m_LengthDawn.z)*(pPlayer->Getpos().z - m_pos.z - m_LengthDawn.z));
			fLength *= 3;	//	�����̔���
		}
		else
		{// ���Ⴊ��ł��Ȃ��ꍇ
		 //	�v���C���[�Ƃ̋����v�Z[a2 + b2 = c2]-----------------------------
			fLength = sqrtf((pPlayer->Getpos().x - m_pos.x)*(pPlayer->Getpos().x - m_pos.x) +
				(pPlayer->Getpos().z - m_pos.z)*(pPlayer->Getpos().z - m_pos.z));
		}
	}
	//	�����̒l��Ԃ�
	return fLength;
}

//***************************************************************************************************************************************
//
//		�G�@���{�b�g�@�ʏ�̏���
//
//***************************************************************************************************************************************
//#define NROBO_MAX_MOVEFORMING (0.275f)				//	�Ǐ]�̍ő�l
//#define NROBO_MAX_MOVE		 (0.125f)				//	�����̍ő�l

//=============================================================================
//	�R���X�g���N�^ //	�e�̃R���X�g���N�^����h���̃R���X�g���N�^
//=============================================================================
CEnemyRobotNomal::CEnemyRobotNomal()
{
	m_state = STATE_NONE;						//	�X�e�[�^�X�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_AIEnemy = AI_NONE;						//	�G��AI�̏���
	m_MosionState = MOSION_NEUTRAL;				//	���[�V�����̏��
	m_bAttack = false;							//	�U���������ǂ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
	m_nEffectCounter = 0;						//	�G�t�F�N�g���o���J�E���^�[
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CEnemyRobotNomal::~CEnemyRobotNomal()
{

}
//=============================================================================
//	����������
//=============================================================================
HRESULT CEnemyRobotNomal::Init(void)
{
	//	������
	CEnemy::Init();
	//	�l��Ԃ�
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CEnemyRobotNomal::Uninit(void)
{
	//	������
	CEnemy::Uninit();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CEnemyRobotNomal::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	�ʒu�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l

	if (m_state == STATE_NONE)
	{//	�ʏ�̏��
	 //	�����̊Ǘ�
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	�Ǐ]���Ă��Ȃ��ꍇ && �U�����Ă��Ȃ�
			if (m_move.x <= -0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	�����Ō�����ς���	�y�@�E�����@�z
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	�����Ō�����ς���	�y�@�O�����@�z
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI;
			}
		}

		ManagementMovement(m_nAISelect);
		//	���[�V�����̐ݒ�Ǘ�
		ManagementSetMosion();
		//	���Z���铮���̏���
		ManagementAddRod(m_rotDest);
		//	�d��
		m_move.y -= GRAVITY;
		// �ړ��ʉ��Z
		//pos += m_move;
		// ��������
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}

	//	�����̐ݒ�
	CEnemy::SetMove(m_move);
	//	�����̐ݒ�
	//CEnemy::Setpos(pos);
	//	������
	CEnemy::Update();
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemyRobotNomal::Draw(void)
{//	������
	CEnemy::Draw();

}
//=============================================================================
//	�����̑���
//=============================================================================
void CEnemyRobotNomal::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	�����̈ʒu�擾
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�擾
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l
	bool bLand = CEnemy::GetLand();				//	����Ă��邩�̎擾
	CPlayer *pPlayer = CGame::GetPlayer();		//	�v���C���[�̎擾
	float fDiffPosZ = pos.z - InitPos.z;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fDiffPosX = pos.x - InitPos.x;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fLength = CEnemy::GetLength();		//	�v���C���[�Ƃ̋����̎擾
											//-------------------------------------------------------
											//	nAIdata_Move = 1 �@�� ���� ���̏���
											//	nAIdata_Move = 2 �@�� ���� ��̏���
											//	nAIdata_Move = 3�@�� ���� �E�̏���
											//	nAIdata_Move = 4 �@�E ���� ���̏���
											//	nAIdata_Move = 5 �@�㉺���E�̏���
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	�����Ȃ���Ԃ������ꍇ
		switch (m_AIEnemy)
		{//	�G�̓�����
		 //----------------------------------------
		 //	�������ĂȂ�
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	�l�̑��
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�v���C���[�̍��W�܂ňړ����邩�v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			break;
			//----------------------------------------
			//	�O�ɐi��	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ�����C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	���ɐi��	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	���ɐi��	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	�E�ɐi��	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă����ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;			//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	�Ǐ]����	[ �v���C���[���W ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	�v���C���[���g���Ă����ꍇ
				if (m_bPStealthMode == true || bLand == true)
				{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	�͈͓��ɓ������ꍇ
					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			}

			break;
			//----------------------------------------
			//	�U������	[ �v���C���[�� ]
			//----------------------------------------
		case AI_ATTACK:
			m_nEffectCounter++;	//	�G�t�F�N�g���o�͂����J�E���^�[
			if ((m_nEffectCounter % 8) == 0)
			{//	�@���G�t�F�N�g
				CEffect::Create
				(D3DXVECTOR3(pos.x + sinf(rot.y - D3DX_PI)*30.0f, 10 + pos.y + SizeMax.y / 2, pos.z + cosf(rot.y - D3DX_PI)*30.0f), 1, 5);
			}
			if (m_bPStealthMode == true || bLand == true)
			{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ
				m_AIEnemy = AI_FOLLOWING;			//	�Ǐ]������
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			break;
		}
	}

	CEnemy::Setpos(pos);			//	�ʒu�̐ݒ�
}

//==============================================================================================================================
// �����蔻��̍쐬
//==============================================================================================================================
bool  CEnemyRobotNomal::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;											//	�͈͓��ɓ��������ǂ���
	D3DXVECTOR3 pos = CEnemyRobotNomal::Getpos();				//	�e�̈ʒu
	D3DXVECTOR3 size = CEnemyRobotNomal::Getsize(0);			//	�e�̑傫��
	m_bAttack = false;
	//	�v���C���[�Ƃ̊p�x
	float fAngle = atan2f(pPos->x - (m_apModel[6]->GetMtxWorld()._41- size.z/2), pPos->z - m_apModel[6]->GetMtxWorld()._43);
	// ��������̂̋���
	float fPosX = ((m_apModel[6]->GetMtxWorld()._41 - size.x / 2) - pPos->x);
	float fPosY = (m_apModel[6]->GetMtxWorld()._42 -( pPos->y+(sizeMax.y / 2)));
	float fPosZ = (m_apModel[6]->GetMtxWorld()._43 - pPos->z);

	float fRadiusA = (fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ);
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x + 15)* (sizeMax.z + 15);
	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{//	�͈͓��ɓ������ꍇ
		bHit = true;											//	��������
		m_bAttack = true;										//	�U�����Ă���

	}
	//	�l��Ԃ�
	return bHit;
}


//=============================================================================
//	���[�V�����̐ݒ�Ǘ�
//=============================================================================
void CEnemyRobotNomal::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	�v���C���[�̏��̎擾
	float	fLength = CEnemy::GetLength();			//	�v���C���[�Ƃ̋���

	switch (m_MosionState)
	{//	���[�V�����̏��
	 //---------------------------------------------------------
	 //	�j���[�g�������[�V�������
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_bAttack == true)
			{//	�U�����
				m_nMotionType = 3;					//	�U�����[�V����
				m_MosionState = MOSION_ATTACK;		//	�U�����[�V�����̏��
			}
			else  	if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�����Ă��郂�[�V�������
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ

			if (m_bAttack == true)
			{//	�U�����
				m_nMotionType = 3;					//	�U�����[�V����6
				m_MosionState = MOSION_ATTACK;		//	�U�����[�V�����̏��
			}
			else if(m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�_���[�W���[�V�������
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		break;
		//---------------------------------------------------------
		//	�U�����[�V�������
		//---------------------------------------------------------
	case MOSION_ATTACK:
		if (m_bAttack == false)
		{
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}

		break;
	}
}


//**********************************************************************************************************************************************
//
//		�G�@���{�b�g�@�e�����G
//
//**********************************************************************************************************************************************
//#define BROBO_MAX_MOVEFORMING (0.375f)				//	�Ǐ]�̍ő�l
//#define BROBO_MAX_MOVE		 (0.225f)				//	�����̍ő�l

//=============================================================================
//	�R���X�g���N�^ //	�e�̃R���X�g���N�^����h���̃R���X�g���N�^
//=============================================================================
CEnemyRobotBullet::CEnemyRobotBullet()
{
	m_nBulletCunter = 0;						//	�e�̃J�E���^�[
	m_pBullet2D = NULL;							//	����2D
	m_state = STATE_NONE;						//	�X�e�[�^�X�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_AIEnemy = AI_NONE;						//	�G��AI�̏���
	m_MosionState = MOSION_NEUTRAL;				//	���[�V�����̏��
	m_bAttack = false;							//	�U���������ǂ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CEnemyRobotBullet::~CEnemyRobotBullet()
{

}
//=============================================================================
//	����������
//=============================================================================
HRESULT CEnemyRobotBullet::Init(void)
{
	//	������
	CEnemy::Init();
	//	�l��Ԃ�
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CEnemyRobotBullet::Uninit(void)
{

	if (m_pBullet2D != NULL)
	{//	�e���g���Ă����ꍇ
		m_pBullet2D->Uninit();
		delete m_pBullet2D;
		m_pBullet2D = NULL;
	}
	//	�I������
	CEnemy::Uninit();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CEnemyRobotBullet::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	�ʒu�̎擾
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l

	if (m_state == STATE_NONE)
	{//	�ʏ�̏��
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	�Ǐ]���Ă��Ȃ��ꍇ && �U�����Ă��Ȃ�
			if (m_move.x <= -0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	�����Ō�����ς���	�y�@�E�����@�z
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	�����Ō�����ς���	�y�@�O�����@�z
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI;
			}
		}
	 //	�����̊Ǘ�
		ManagementMovement(m_nAISelect);
		//	���[�V�����̐ݒ�Ǘ�
		ManagementSetMosion();
		//	���Z���铮���̏���
		ManagementAddRod(m_rotDest);
		//	�d��
		m_move.y -= GRAVITY;
		// ��������
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	�����̐ݒ�
	CEnemy::SetMove(m_move);
	//	�X�V����
	CEnemy::Update();
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemyRobotBullet::Draw(void)
{
	//	�`�揈��
	CEnemy::Draw();

}
//=============================================================================
//	�����̑���
//=============================================================================
void CEnemyRobotBullet::ManagementMovement(int nAIdata_Move)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	�����̈ʒu�擾
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�擾
	bool bLand = CEnemy::GetLand();				//	����Ă��邩�̎擾
	CPlayer *pPlayer = CGame::GetPlayer();		//	�v���C���[�̎擾
	float fDiffPosZ = pos.z - InitPos.z;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fDiffPosX = pos.x - InitPos.x;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fLength = CEnemy::GetLength();		//	�v���C���[�Ƃ̋����̎擾
											//-------------------------------------------------------
											//	nAIdata_Move = 1 �@�� ���� ���̏���
											//	nAIdata_Move = 2 �@�� ���� ��̏���
											//	nAIdata_Move = 3�@�� ���� �E�̏���
											//	nAIdata_Move = 4 �@�E ���� ���̏���
											//	nAIdata_Move = 5 �@�㉺���E�̏���
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	�����Ȃ���Ԃ������ꍇ
		switch (m_AIEnemy)
		{//	�G�̓�����
		 //----------------------------------------
		 //	�������ĂȂ�
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	�l�̑��
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�v���C���[�̍��W�܂ňړ����邩�v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			break;
			//----------------------------------------
			//	�O�ɐi��	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ�����C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;			//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	���ɐi��	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	���ɐi��	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	�E�ɐi��	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă����ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	�Ǐ]����	[ �v���C���[���W ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	�v���C���[���g���Ă����ꍇ
				if (m_bPStealthMode == true || bLand == true)
				{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	�͈͓��ɓ������ꍇ

					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			}

			break;
			//----------------------------------------
			//	�U������	[ �v���C���[�� ]
			//----------------------------------------
		case AI_ATTACK:
			if (m_bPStealthMode == true || bLand == true)
			{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400���Ȃ��������ꍇ
				if (pPlayer != NULL)
				{//	���{�b�g001
					m_nBulletCunter++;				//	�e�������o�̃t���[�����Z
					if (m_nBulletCunter > 40)
					{//	�e�̏o��
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET);	//	�e���o�鉹
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[2]->GetMtxWorld()._41, m_apModel[2]->GetMtxWorld()._42, m_apModel[2]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * (1.8f+ m_fFormingSpeed), 0.0f, cosf(m_fAngle) * (1.8f + m_fFormingSpeed)), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_nBulletCunter = 0;
					}
				}
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ
				m_AIEnemy = AI_FOLLOWING;			//	�Ǐ]������
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			break;
		}
	}

	CEnemy::Setpos(pos);			//	�ʒu�̐ݒ�
}

//=============================================================================
//	���[�V�����̐ݒ�Ǘ�
//=============================================================================
void CEnemyRobotBullet::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	�v���C���[�̏��̎擾
	float	fLength = CEnemy::GetLength();			//	�v���C���[�Ƃ̋���

	switch (m_MosionState)
	{//	���[�V�����̏��
	 //---------------------------------------------------------
	 //	�j���[�g�������[�V�������
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
			else if (m_bAttack == true)
			{//	�U�����
				m_nMotionType = 3;					//	�U�����[�V����
				m_MosionState = MOSION_ATTACK;		//	�U�����[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�����Ă��郂�[�V�������
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			else if (m_bAttack == true && m_nAISelect == AI_ATTACK)
			{//	�U�����
				m_nMotionType = 3;					//	�U�����[�V����6
				m_MosionState = MOSION_ATTACK;		//	�U�����[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�_���[�W���[�V�������
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		break;
		//---------------------------------------------------------
		//	�U�����[�V�������
		//---------------------------------------------------------
	case MOSION_ATTACK:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
		{//	�ړ����Ă��Ȃ��ꍇ
			m_nMotionType = 0;					//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	�ړ����Ă����ꍇ
			m_nMotionType = 1;					//	�ړ����[�V����
			m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
		}
		break;
	}
}

//**********************************************************************************************************************************************
//
//		�G�@���{�b�g�@���̓G
//
//**********************************************************************************************************************************************
//#define SROBO_MAX_MOVEFORMING (0.575f)				//	�Ǐ]�̍ő�l
//#define SROBO_MAX_MOVE		 (0.295f)				//	�����̍ő�l

//=============================================================================
//	�R���X�g���N�^ //	�e�̃R���X�g���N�^����h���̃R���X�g���N�^
//=============================================================================
CEnemyRobotSpine::CEnemyRobotSpine()
{
	m_state = STATE_NONE;						//	�X�e�[�^�X�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_AIEnemy = AI_NONE;						//	�G��AI�̏���
	m_MosionState = MOSION_NEUTRAL;				//	���[�V�����̏��
	m_bAttack = false;							//	�U���������ǂ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
	m_fAddRot = 0.0f;							//	��]�̉��Z
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CEnemyRobotSpine::~CEnemyRobotSpine()
{

}
//=============================================================================
//	����������
//=============================================================================
HRESULT CEnemyRobotSpine::Init(void)
{
	//	������
	CEnemy::Init();
	//	�l��Ԃ�
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CEnemyRobotSpine::Uninit(void)
{
	//	�I������
	CEnemy::Uninit();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CEnemyRobotSpine::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	�ʒu�̎擾
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l
	if (m_state == STATE_NONE)
	{//	�ʏ�̏��
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	�Ǐ]���Ă��Ȃ��ꍇ && �U�����Ă��Ȃ�
			if (m_move.x <= -0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	�����Ō�����ς���	�y�@�E�����@�z
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	�����Ō�����ς���	�y�@�O�����@�z
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI;
			}
		}
	 //	�����̊Ǘ�
		ManagementMovement(m_nAISelect);
		//	���[�V�����̐ݒ�Ǘ�
		ManagementSetMosion();
		//	���Z���铮���̏���
		ManagementAddRod(m_rotDest);
		//	�d��
		m_move.y -= GRAVITY;
		// ��������
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	�����̐ݒ�
	CEnemy::SetMove(m_move);
	//	�X�V����
	CEnemy::Update();

	m_fAddRot++;
	if (m_apModel[2] != NULL || m_apModel[3] != NULL)
	{
		//	�p�[�c�𓮂���
		m_apModel[2]->Setrot(D3DXVECTOR3(0.0f, m_fAddRot, 0.0f));
		m_apModel[3]->Setrot(D3DXVECTOR3(0.0f, m_fAddRot, 0.0f));
	}
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemyRobotSpine::Draw(void)
{
	//	�`�揈��
	CEnemy::Draw();

}
//=============================================================================
//	�����̑���
//=============================================================================
void CEnemyRobotSpine::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	�����̈ʒu�擾
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�擾

	CPlayer *pPlayer = CGame::GetPlayer();		//	�v���C���[�̎擾
	float fDiffPosZ = pos.z - InitPos.z;	//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fDiffPosX = pos.x - InitPos.x;	//	�����̈ʒu���猻�݂̈ʒu�̍���

	float fLength = CEnemy::GetLength();	//	�v���C���[�Ƃ̋����̎擾
											//-------------------------------------------------------
											//	nAIdata_Move = 1 �@�� ���� ���̏���
											//	nAIdata_Move = 2 �@�� ���� ��̏���
											//	nAIdata_Move = 3�@�� ���� �E�̏���
											//	nAIdata_Move = 4 �@�E ���� ���̏���
											//	nAIdata_Move = 5 �@�㉺���E�̏���
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	�����Ȃ���Ԃ������ꍇ
		switch (m_AIEnemy)
		{//	�G�̓�����
		 //----------------------------------------
		 //	�������ĂȂ�
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	�l�̑��
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false)
			{//	�v���C���[�̍��W�܂ňړ����� // �v���C���[���X�e���X��Ԃɓ����Ă����ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			break;
			//----------------------------------------
			//	�O�ɐi��	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ// �v���C���[���X�e���X��Ԃɓ����Ă����ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	���ɐi��	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ// �v���C���[���X�e���X��Ԃɓ����Ă����ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			 if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	���ɐi��	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ// �v���C���[���X�e���X��Ԃɓ����Ă����ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	�E�ɐi��	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ// �v���C���[���X�e���X��Ԃɓ����Ă����ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	�Ǐ]����	[ �v���C���[���W ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	�v���C���[���g���Ă����ꍇ
				if (m_bPStealthMode == true)
				{//	�X�e���X�u���b�N�̒��ɓ������ꍇ
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	�͈͓��ɓ������ꍇ
					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			}

			break;
			//----------------------------------------
			//	�U������	[ �v���C���[�� ]
			//----------------------------------------
		case AI_ATTACK:
			if (m_bPStealthMode == true)
			{//	�X�e���X�u���b�N�̒��ɓ������ꍇ
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400���Ȃ��������ꍇ

			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ
				m_AIEnemy = AI_FOLLOWING;			//	�Ǐ]������
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			break;
		}
	}

	CEnemy::Setpos(pos);			//	�ʒu�̐ݒ�
}

//=============================================================================
//	���[�V�����̐ݒ�Ǘ�
//=============================================================================
void CEnemyRobotSpine::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	�v���C���[�̏��̎擾
	float	fLength = CEnemy::GetLength();			//	�v���C���[�Ƃ̋���

	switch (m_MosionState)
	{//	���[�V�����̏��
	 //---------------------------------------------------------
	 //	�j���[�g�������[�V�������
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�����Ă��郂�[�V�������
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�_���[�W���[�V�������
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		break;
	}
}
//==============================================================================================================================
// �����蔻��̍쐬
//==============================================================================================================================
bool  CEnemyRobotSpine::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;
	D3DXVECTOR3 pos = CEnemyRobotSpine::Getpos();				//	�e�̈ʒu
	D3DXVECTOR3 size = CEnemyRobotSpine::Getsize(0);			//	�e�̑傫��
	//	�v���C���[�Ƃ̊p�x
	float fAngle = atan2f(pPos->x - pos.x, pPos->z - pos.z);
	// ��������̂̋���
	float fPosX = (pos.x - pPos->x);
	float fPosY = (pos.y - pPos->y);
	float fPosZ = (pos.z - pPos->z);

	float fRadiusA =( fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ);
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x*1.5f + size.x)* (sizeMax.z*1.5f + size.z);
	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{
		bHit = true;
	}

	return bHit;
}


//**********************************************************************************************************************************************
//
//		�G�@���{�b�g�@si���ɒe��e�����G
//
//**********************************************************************************************************************************************
//#define UROBO_MAX_MOVEFORMING (0.825f)				//	�Ǐ]�̍ő�l
//#define UROBO_MAX_MOVE		 (0.225f)				//	�����̍ő�l
#define UROBO_MAX_POS		(150)					//	�オ���Ă���ő�ʒu
#define UROBO_POS			(30)						//	�オ���Ă���ʒu
#define UROBO_MOVE_Y			(0.55f)					//	�c�̓���
#define UROBO_MAX_MOVE_Y		(0.65f)				//	�c�̍ő�̓���


//=============================================================================
//	�R���X�g���N�^ //	�e�̃R���X�g���N�^����h���̃R���X�g���N�^
//=============================================================================
CEnemyRobotUndeBulletr::CEnemyRobotUndeBulletr()
{
	m_nBulletCunter = 0;						//	�e�̃J�E���^�[
	m_pBullet2D = NULL;							//	����2D
	m_state = STATE_NONE;						//	�X�e�[�^�X�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_AIEnemy = AI_NONE;						//	�G��AI�̏���
	m_MosionState = MOSION_NEUTRAL;				//	���[�V�����̏��
	m_bAttack = false;							//	�U���������ǂ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
	m_fAddPos = 0.0f;							//	�ʒu�̉��Z
	m_nEffectCounter = 0;					//	�G�t�F�N�g���o��J�E���^
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CEnemyRobotUndeBulletr::~CEnemyRobotUndeBulletr()
{

}
//=============================================================================
//	����������
//=============================================================================
HRESULT CEnemyRobotUndeBulletr::Init(void)
{
	//	������
	CEnemy::Init();
	//	�l��Ԃ�
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CEnemyRobotUndeBulletr::Uninit(void)
{
	if (m_pBullet2D != NULL)
	{//	�e���g���Ă����ꍇ
		m_pBullet2D->Uninit();
		delete m_pBullet2D;
		m_pBullet2D = NULL;
	}
	//	�I������
	CEnemy::Uninit();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CEnemyRobotUndeBulletr::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	�ʒu�̎擾
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	��]�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l

	if (m_state == STATE_NONE)
	{//	�ʏ�̏��
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	�Ǐ]���Ă��Ȃ��ꍇ && �U�����Ă��Ȃ�
			if (m_move.x <= -0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	�����Ō�����ς���	�y�@�E�����@�z
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	�����Ō�����ς���	�y�@�O�����@�z
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	�����Ō�����ς���	�y�@�������@�z
				m_rotDest.y = D3DX_PI;
			}
		}
		m_nEffectCounter++;	//	�G�t�F�N�g���o�͂����J�E���^�[
		if ((m_nEffectCounter % 15) == 0)
		{//	���̃G�t�F�N�g
			CEffect::Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42-5, m_apModel[0]->GetMtxWorld()._43), 1, 4);
		}

		//	�����̊Ǘ�
		ManagementMovement(m_nAISelect);
		//	���[�V�����̐ݒ�Ǘ�
		ManagementSetMosion();
		//	���Z���铮���̏���
		ManagementAddRod(m_rotDest);
		//	�d��
		m_move.y -= 0.45f;
		// ��������
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	�����̐ݒ�
	CEnemy::SetMove(m_move);
	//	�X�V����
	CEnemy::Update();
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemyRobotUndeBulletr::Draw(void)
{
	//	�`�揈��
	CEnemy::Draw();

}
//=============================================================================
//	�����̑���
//=============================================================================
void CEnemyRobotUndeBulletr::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	�����̈ʒu�擾
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�擾
	bool bLand = CEnemy::GetLand();				//	����Ă��邩�̎擾
	CPlayer *pPlayer = CGame::GetPlayer();		//	�v���C���[�̎擾
	float fDiffPosZ = pos.z - InitPos.z;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fDiffPosX = pos.x - InitPos.x;		//	�����̈ʒu���猻�݂̈ʒu�̍���
	float fLength = CEnemy::GetLength();		//	�v���C���[�Ƃ̋����̎擾
												//-------------------------------------------------------
												//	nAIdata_Move = 1 �@�� ���� ���̏���
												//	nAIdata_Move = 2 �@�� ���� ��̏���
												//	nAIdata_Move = 3�@�� ���� �E�̏���
												//	nAIdata_Move = 4 �@�E ���� ���̏���
												//	nAIdata_Move = 5 �@�㉺���E�̏���
												//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	�����Ȃ���Ԃ������ꍇ
		switch (m_AIEnemy)
		{//	�G�̓�����
		 //----------------------------------------
		 //	�������ĂȂ�
		 //----------------------------------------
		case AI_NONE:
			if (pos.y <= 50)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	�l�̑��
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�v���C���[�̍��W�܂ňړ����邩�v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			break;
			//----------------------------------------
			//	�O�ɐi��	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			if (pos.y <= UROBO_POS)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += 1.00f;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			m_move.z += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ�����C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*2.0f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	���ɐi��	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			if (pos.y <= UROBO_POS)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			m_move.z -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if(m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*2.0f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	���ɐi��	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			if (pos.y <= UROBO_POS)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			m_move.x += m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă��Ȃ��ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*2.0f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	�E�ɐi��	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			if (pos.y <= UROBO_POS)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			m_move.x -= m_fNoneSpeed;				//	�����̉��Z
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	�͈͓��ɓ������ꍇ���v���C���[���X�e���X��Ԃɓ����Ă����ꍇ������Ă��Ȃ������ꍇ
				m_AIEnemy = AI_FOLLOWING;	//	�Ǐ]������
				if (m_move.y < 0.1f)
				{//	���ł��Ȃ������ꍇ
					m_move.y += 6.35f;			//	�W�����v������
				}
			}
			if (m_bWallHit == true)
			{//	�ǂɓ�������
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*2.0f;	//	�����̉��Z
				m_bWallHit = false;		//	�ǂɓ������Ă��Ȃ�
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	�����œ�����ς���܂��͓G���m���������ꍇ
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	�Ǐ]����	[ �v���C���[���W ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	�v���C���[���g���Ă����ꍇ
				if (pos.y <= UROBO_MAX_POS)
				{//	�ʒu��50�ȏ�Ȃ�
					m_move.y += UROBO_MAX_MOVE_Y;
				}
				else
				{//	����ȊO�̏ꍇ
					m_move.y = 0.0f;
				}
				if (m_bPStealthMode == true || bLand == true)
				{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	�͈͓��ɓ������ꍇ

					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			}

			break;
			//----------------------------------------
			//	�U������	[ �v���C���[�� ]
			//----------------------------------------
		case AI_ATTACK:
			if (pos.y <= UROBO_MAX_POS)
			{//	�ʒu��50�ȏ�Ȃ�
				m_move.y += UROBO_MAX_MOVE_Y;
			}
			else
			{//	����ȊO�̏ꍇ
				m_move.y = 0.0f;
			}
			if (m_bPStealthMode == true || bLand == true)
			{//	�X�e���X�u���b�N�̒��ɓ������ꍇ�܂��͏���Ă����ꍇ
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400���Ȃ��������ꍇ
				if (pPlayer != NULL)
				{//	���{�b�g001
					m_nBulletCunter++;				//	�e�������o�̃t���[�����Z
					if (m_nBulletCunter > 40)
					{//	�e�̏o��
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * 1.0f,-3.5f, cosf(m_fAngle) * 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * 0.0f, -3.5f, cosf(m_fAngle) * 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_nBulletCunter = 0;
					}
				}
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	�͈͓��ɓ������ꍇ
				m_AIEnemy = AI_FOLLOWING;			//	�Ǐ]������
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	�p�x���v���C���[�Ɍ�����
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	�����̉��Z
			break;
		}
	}

	CEnemy::Setpos(pos);			//	�ʒu�̐ݒ�
}

//=============================================================================
//	���[�V�����̐ݒ�Ǘ�
//=============================================================================
void CEnemyRobotUndeBulletr::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	�v���C���[�̏��̎擾
	float	fLength = CEnemy::GetLength();			//	�v���C���[�Ƃ̋���

	switch (m_MosionState)
	{//	���[�V�����̏��
	 //---------------------------------------------------------
	 //	�j���[�g�������[�V�������
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�����Ă��郂�[�V�������
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	�_���[�W��Ԃ̏ꍇ
			m_nMotionType = 2;						//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMEGA;			//	�_���[�W���[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�_���[�W���[�V�������
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	�ʏ��Ԃ̏ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;					//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ
				m_nMotionType = 1;					//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
			}
		}
		break;
	}
}
//***************************************************************************************************************************************
//
//		�Ō�̃I�u�W�F�N�g
//
//***************************************************************************************************************************************


//=============================================================================
//	�R���X�g���N�^ //	�e�̃R���X�g���N�^����h���̃R���X�g���N�^
//=============================================================================
CEnemyLastObj::CEnemyLastObj()
{
	m_state = STATE_NONE;						//	�X�e�[�^�X�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
	m_nEffectCounter = 0;						//	�G�t�F�N�g���o���J�E���^�[
}
//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CEnemyLastObj::~CEnemyLastObj()
{

}
//=============================================================================
//	����������
//=============================================================================
HRESULT CEnemyLastObj::Init(void)
{
	//	������
	CEnemy::Init();
	//	�l��Ԃ�
	return S_OK;
}
//=============================================================================
//	�I������
//=============================================================================
void CEnemyLastObj::Uninit(void)
{


	//	������
	CEnemy::Uninit();
}
//=============================================================================
//	�X�V����
//=============================================================================
void CEnemyLastObj::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	�ʒu�̎擾
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	�ʒu�̎擾
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	�傫���̍ő�l
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	�傫���̍ŏ��l

	if (m_state == STATE_NONE)
	{//	�ʏ�̏��
	 //	�����̊Ǘ�
		//	���Z���铮���̏���
		ManagementAddRod(m_rotDest);
		//	�d��
		m_move.y -= GRAVITY;
		// �ړ��ʉ��Z
		//pos += m_move;
		// ��������
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}

	//	�����̐ݒ�
	CEnemy::SetMove(m_move);
	//	������
	CEnemy::Update();
}
//=============================================================================
//	�`�揈��
//=============================================================================
void CEnemyLastObj::Draw(void)
{//	������
	CEnemy::Draw();
}
