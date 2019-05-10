//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "player.h"			// �v���C���[
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
#include "enemy.h"			// �G
#include "bullet2D.h"		// �e2D
#include "block.h"			//	�u���b�N
#include "bulletNumber.h"
#include "UI.h"				//	UI
#include "sound.h"			//	�T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME						("data\\TEXT\\player\\motion.txt")		//	�ǂݍ��ރe�L�X�g�̖��O
#define GRAVITY							(0.7f)									//	�d��
#define WALK_SPEED						(0.95f)									//	�����X�s�[�h
#define MOVE_DOWNSPEED_NOR				(0.25f)									//	�����X�s�[�h
#define MOVE_UPSPEED					(1.05f)									//	�����X�s�[�h

#define ATTACK_COLL_EXPAND_Z_000		(20)									//	�U������̓G�̔���̊g�嗦 1�i��
#define ATTACK_COLL_EXPAND_X_000		(20)									//	�U������̓G�̔���̊g�嗦 1�i��
#define ATTACK_COLL_EXPAND_Y_000		(10)									//	�U������̓G�̔���̊g�嗦 1�i��
#define ATTACK_COLL_EXPAND_Z_001		(20)									//	�U������̓G�̔���̊g�嗦 2�i��
#define ATTACK_COLL_EXPAND_X_001		(20)									//	�U������̓G�̔���̊g�嗦 2�i��
#define ATTACK_COLL_EXPAND_Y_001		(25)									//	�U������̓G�̔���̊g�嗦 2�i��


//*****************************************************************************
//	�ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH					CPlayer::m_pMesh[MAX_NUMPARTS] = {};
LPD3DXBUFFER				CPlayer::m_pBuffMat[MAX_NUMPARTS] = {};
LPDIRECT3DTEXTURE9			*CPlayer::m_pTexture[MAX_NUMPARTS] = {};
DWORD						CPlayer::m_nNumMat[MAX_NUMPARTS] = {};
int							CPlayer::m_nNumParts = 0;
//=============================================================================
//�v���C���[�N���X �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CScene(PRIORITY_4, CScene::OBJTYPE_PLAYER)
{
	m_bJump = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	����
	m_state = STATE_NONE;						//	���
	D3DXMatrixIdentity(&m_mtxWorld);			//	���[���h�}�g���b�N�X
	m_pKeyInfo[MAX_NUMMOTION] = {};				//	�L�[���ւ̃|�C���^
	m_nKey = 0;									//	���݂̃L�[�i���o�[
	m_nCountFlame = 0;							//	�t���[��
	m_bMotionEnd = false;						//	���[�V�����̏I��
	m_nMotionType = 0;							//	���݂̃��[�V�����^�C�v
	m_bMove = false;							//	�����Ă���
	m_bBlock = false;							//	�u���b�N�ɓ������Ă��邩
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�v���C���[�̑傫���̍ő�l
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�v���C���[�̑傫���̍ŏ��l
	m_MosionState = MOSION_NEUTRAL;				//	�j���[�g�������[�V����
	m_nCouterFreamMax[MAX_NUMMOTION] = {};		//	���[�V�����̃t���[���̍��v�l
	m_bSquat = false;							//	���Ⴊ��ł�����
	m_nCntNumMosion = 0;						//	�e�L�X�g�ɏ�����Ă��郂�[�V�����̐�
	m_fMoveControl = 0.0f;						//	�ړ��̕ω�
	m_nMotionTypeOld = 0;						//	���[�V�����̉ߋ��̎��
	m_pBullet3D = NULL;							//	�e�̃|�C���^�ϐ�
	m_pOrbit = NULL;							//	�O�Ղ̃|�C���^�ϐ�
	m_pShadow = NULL;							//	�e�̃|�C���^�ϐ�
	m_pBlock = NULL;							//	�u���b�N�̃|�C���^�ϐ�
	m_bAttack = false;							//	�U�������ǂ���
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ړI�̌���
	m_bJump = false;							//	�W�����v���
	m_nAtkFream = 0;							//	�U���̃R���W�������ł�^�C�~���O
	m_bAtkLastHit = false;						//	�Ō�̍U���ɓ����������ǂ���
	m_nAtkCombFream = 0;						//	�R���{�ł���t���[��
	m_bDisp = false;							//	���񂾏��
	m_bDamage = false;							//	�_���[�W���
	m_nStateCounter = 0;						//	�X�e�[�^�X�̃J�E���^�[
	m_bStealthMode = false;						//	�X�e���X���[�h
	m_bLifeState[0] = false;					//	�̗͂̕ω��_���[�W
	m_bLifeState[1] = false;					//	�̗͂̕ω���
	m_nBltCut = 0;								//	�e�̒e��
	m_nStealthLife = 0;							//	�X�e���X�o����J�E���^�[���
	m_nStealthCut = 0;
	m_nLifeInit = 0;							//	�����̗̑�
	m_bStlBlockHitIn = false;					//	�X�e���X�u���b�N�̒��ɓ�����
	m_nNumBlock = 0;							//	�X�e���X�u���b�N�̐�
	m_nInvincible = 0;							//	���G��Ԃ̃J�E���^�[
	m_nDashLife = 0;							//	�_�b�V���ł������
	m_nDashCut = 0;								//	�_�b�V����Ԃɖ߂�J�E���^�[
	m_bDash = false;							//	�_�b�V�����Ă��邩�ǂ���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nBltCut, int nStealthLife,int nDashLife)
{
	//�v���C���[�|�C���^
	CPlayer *pPlayer = {};
	if (pPlayer == NULL)
	{//	�v���C���[���g���Ă��Ȃ������ꍇ
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{//	������
			pPlayer->m_nDashLife = nDashLife;		//	dash�ł������
			pPlayer->m_nStealthLife = nStealthLife;	//	�X�e���X�o�������
			pPlayer->m_nBltCut = nBltCut;			//	�e�̒e��
			pPlayer->m_pos = pos;					//	�ʒu�̐ݒ�
			pPlayer->m_rot = rot;					//	��]�̐ݒ�
			pPlayer->m_nLife = nLife;				//	����
			pPlayer->Init();						//	����������
		}
	}
	//�v���C���[�̏���Ԃ�
	return pPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�v���C���[���̓ǂݍ���
	FileLoad();
	// �g��k���p�ϐ�
	m_fScaleX = 2.0f, m_fScaleY = 2.0f, m_fScaleZ = 2.0f;
	// ����ݒ�
	m_vtxMax = D3DXVECTOR3(10.0f *m_fScaleX, 35.0f*m_fScaleY, 10.0f*m_fScaleZ);
	m_vtxMin = D3DXVECTOR3(-10.0f*m_fScaleX, 0.0f*m_fScaleY, -10.0f*m_fScaleZ);

	//	�e�̐���
	if (m_pShadow == NULL)
	{//	�e���g���Ă��Ȃ�������
		m_pShadow = CShadow::Create(m_pos, m_rot, D3DXVECTOR3(m_vtxMax.x, 0.0f, m_vtxMax.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	if (m_pBlock == NULL)
	{//	�u���b�N���g���Ă��Ȃ�������
		m_pBlock = CBlock::Create(D3DXVECTOR3(m_apModel[1]->GetMtxWorld()._41, m_apModel[1]->GetMtxWorld()._42, m_apModel[1]->GetMtxWorld()._43),
			m_rot, D3DXVECTOR3(0.5f, 0.5f, 0.5f), CBlock::MODELTYPE_GIRISUTU, CBlock::COLTYPE_NONE);
	}
	for (int nCnterMosion = 0; nCnterMosion < MAX_NUMMOTION; nCnterMosion++)
	{//	���[�V�����̊m�ۉ�
		if (m_nCntNumMosion >= nCnterMosion)
		{//	���[�V�����̃e�L�X�g�ɏ�����Ă����ޕ���
			for (int nCounter = 0; nCounter < m_aMotionInfo[nCnterMosion].nNumKey; nCounter++)
			{//	�����郂�[�V�����̃L�[������
				m_nCouterFreamMax[nCnterMosion] += m_aMotionInfo[nCnterMosion].aKayInfo[nCounter].nFrame;
			}
		}
	}
	m_MosionState = MOSION_NEUTRAL;				//	�j���[�g�������[�V����
	m_nMotionType = 0;							//	���[�V�����̎��
	m_bJump = false;							//	�W�����v���
	m_bAttack = false;							//	�U�����
	m_bSquat = false;							//	���Ⴊ��ł�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	����
	m_bMove = true;								//	��������
	m_nLifeInit = m_nLife;						//	�����̗̑͂̐ݒ�
	return S_OK;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
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
	CGame::SetPlayer();

	// �t���O�𗧂Ă�
	CScene::SetDeath();
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �ʒu�ۑ�
	m_posOld = m_pos;
	//	���[�V�����̕ۑ�
	m_nMotionTypeOld = m_nMotionType;

	// ����ݒ�
	m_vtxMax = D3DXVECTOR3(10.0f *m_fScaleX, 33.0f*m_fScaleY, 10.0f*m_fScaleZ);
	m_vtxMin = D3DXVECTOR3(-10.0f*m_fScaleX, 0.0f*m_fScaleY, -10.0f*m_fScaleZ);

	switch (m_state)
	{// ���
		//-----------------------------------------
		//	�ʏ�
		//-----------------------------------------
	case STATE_NONE:
		//	�����̊Ǘ�
		ManagementMovement();
		//	���Z���铮���̏���
		ManagementAddMovement();
		break;
		//-----------------------------------------
		// �_���[�W
		//-----------------------------------------
	case STATE_DAMAGE:
		m_bDamage = true;				//	�_���[�W���
		m_nStateCounter++;
		if (m_nStateCounter > 30)
		{//	�J�E���^�[���w��̒l�𒴂����ꍇ
			m_state = STATE_INVINCIBLE;	//	���G��Ԃɂ���
			m_bDamage = false;			//	�_���[�W��Ԃ�߂�
			m_nStateCounter = 0;		//	�J�E���^�[������
		}
		break;
		//-----------------------------------------
		// ���G���
		//-----------------------------------------
	case STATE_INVINCIBLE:
		m_nInvincible++;
		//	�����̊Ǘ�
		ManagementMovement();
		//	���Z���铮���̏���
		ManagementAddMovement();
		if (m_nInvincible > 50)
		{//	�J�E���^�[���w��̒l�𒴂����ꍇ
			m_state = STATE_NONE;		//	�ʏ��Ԃɖ߂�
			m_nInvincible = 0;
		}
		break;
		//-----------------------------------------
		// ���S
		//-----------------------------------------
	case STATE_DEATH:
		m_bDisp = true;					//	����ł�����
		break;
	}
	//	�����蔻��̊Ǘ�
	ManagementCollision();
	//	���[�V�����̐ݒ�Ǘ�
	ManagementSetMosion();
#ifdef _DEBUG
	CManager::m_CDebugProcRight->Print("\n----------�v���C���[�̃X�e�[�^�X------------------");
	CManager::m_CDebugProcRight->Print("\n�v���C���[�̈ʒu  ( %.1f : %.1f  : %.1f)", m_pos.x, m_pos.y, m_pos.z);
	CManager::m_CDebugProcRight->Print("\n�v���C���[�̓����@( %.1f : %.1f  : %.1f)", m_move.x, m_move.y, m_move.z);
	CManager::m_CDebugProcRight->Print("\n�v���C���[�̌����@( %.1f : %.1f  : %.1f)", m_rot.x, m_rot.y, m_rot.z);
	CManager::m_CDebugProcRight->Print("\nMAX�@( %.1f : %.1f  : %.1f)", m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	CManager::m_CDebugProcRight->Print("\nMIN�@( %.1f : %.1f  : %.1f)", m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
	CManager::m_CDebugProcRight->Print("\n�X�P�[���l�@( %.1f : %.1f  : %.1f)", m_fScaleX, m_fScaleY, m_fScaleZ);
	CManager::m_CDebugProcRight->Print("\n�̗́@( %d)", m_nLife);
	CManager::m_CDebugProcRight->Print("\n-------------------------------------------------");
#endif
	if (m_pShadow != NULL)
	{//	�e���g���Ă�����
		if (m_bBlock == true)
		{//	�u���b�N�ɓ������Ă����ꍇ�e��POSY���W�Ɉړ�������
			//	�e�̈ʒu�̐ݒ�
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_pos.y, m_apModel[0]->GetMtxWorld()._43));
		}
		else
		{//	�u���b�N�ɓ������Ă��Ȃ��ꍇ�n�ʂ�
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, 0.5f, m_apModel[0]->GetMtxWorld()._43));
		}
	}

	//���[�V�����X�V
	UpdateMotion();
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
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
	D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, m_fScaleZ);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &matScale);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̕`�揈��
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);
	//	���C�g�̐ݒ�
	VecLight = D3DXVECTOR4(0.0f,1.0f, 0.0f, 0.0f);
	//	�e�̈ʒu�ݒ�
	pos = D3DXVECTOR3(0.0f, m_pShadow->Getpos().y, 0.0f);
	//	�@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	���ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//	�e�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//	���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//	���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	//{//	�p�[�c���`�悷��
	//	if (m_apModel[nCnt] != NULL)
	//	{//	�`��̏�����
	//		m_apModel[nCnt]->Draw();
	//	}
	//}
	//	�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	 //���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_state == STATE_INVINCIBLE)
	{//	���G��Ԃ������ꍇ
		if ((m_nInvincible % 12) == 0)
		{//	�_�ł�����
			for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
			{//	�p�[�c����
				if (m_apModel[nCnt] != NULL)
				{//	�`�揈��
					m_apModel[nCnt]->Draw();
				}
			}
		}
	}
	else
	{//	����ȊO�̏��
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{//	�p�[�c����
			if (m_apModel[nCnt] != NULL)
			{//	�`�揈��
				m_apModel[nCnt]->Draw();
			}
		}
	}
}


//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	return S_OK;
}

//=============================================================================
// �j������
//=============================================================================
void CPlayer::UnLoad(void)
{
	for (int nCntIndex = 0; nCntIndex < m_nNumParts; nCntIndex++)
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
//	�����̑���
//=============================================================================
void CPlayer::ManagementMovement(void)
{
	//	�J�����̉�]�̎擾
	D3DXVECTOR3 cameraRot = CCamera::GetCameraRotate();

	if (m_bJump == false)
	{//	�W�����v���Ă��Ȃ�
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true && m_nCntMosionChange <= 0 || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
		{//	�X�y�[�X�L�[���������@�����@���n���[�V�������Ă��Ȃ������ꍇ
		 //	�ړ�����
			m_move.y += 12.0f;
			//	�W�����v��
			m_bJump = true;
		}
	}
	else if (m_bJump == true)
	{//	�W�����v��
		if (m_move.y <= 0.1f && m_move.y >= -0.1f)
		{//	�W�����v���Ă��Ȃ�
			m_bJump = false;
		}
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_X, 0) == true)
	{//	�U�����[�V����
		m_bAttack = true;
	}

	//	�`���[�g���A���̕\�L�I��������ǂ���
	bool bTuto = false;
	if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
	{//	�`���[�g���A���̏ꍇ
		bTuto = CUI::GetTutoEnd();	//	�`���[�g���A�����I��������ǂ���
	}
	else
	{//	�`���[�g���A���ȊO�̏ꍇ
		bTuto = true;	//	�`���[�g���A�����I��������ǂ���
	}

	if ((CManager::GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::GetInputXPad()->GetPress(XINPUT_GAMEPAD_LEFT_SHOULDER, 0) == true ) &&
		m_nStealthLife > 0&&m_bJump ==false&&m_bAttack ==false && bTuto ==true)
	{
	 //	�{�^���̉������݁@�X�e���X�̎���������@�W�����v���ĂȂ��@�U�����Ă��Ȃ�
		m_bSquat = true;
		//	�ړ����x���Ȃ�
		m_fMoveControl = -(WALK_SPEED / 1.5f);
		if (m_pBlock != NULL)
		{//	�u���b�N���g���Ă�����
			m_pBlock->Setpos(D3DXVECTOR3(m_apModel[1]->GetMtxWorld()._41, m_apModel[1]->GetMtxWorld()._42 + 8, m_apModel[1]->GetMtxWorld()._43));
			m_pBlock->Setrot(m_rot);
			m_pBlock->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		}
		if (m_nStealthLife > 0)
		{//	0�ȏ�Ȃ�������炷
			m_nStealthLife--;
		}
	}
	else if ((CManager::GetInputKeyboard()->GetPress(DIK_N) == true ||
		CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_TRIGGER_LEFT, 0) == true)&&
		m_nDashLife > 0 && m_bJump == false && m_bAttack == false && bTuto == true)
	{//	Z�L�[�@// L �g���K�[
		m_bDash = true;		//	�_�b�V�����Ă���
		//	�ړ��������Ȃ�
		m_fMoveControl = MOVE_UPSPEED;

		if (m_nDashLife > 0)
		{//	�_�b�V���̃W���~���E���炷
			m_nDashLife--;
		}
	}
	else
	{//	���Ⴊ��ł��Ȃ����
		m_bSquat = false;
		// ���Ⴊ�ݒ�����Ȃ����͈ړ��x�����Ȃ�
		m_fMoveControl = 0.0f;
		m_bDash = false;		//	�_�b�V�����Ă��Ȃ�
	}

		if (m_bSquat == false|| m_bDamage == true)
		{
			if (m_pBlock != NULL)
			{//	�u���b�N���g���Ă�����
				m_pBlock->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//�@����������
			}
			if (m_nStealthLife == 0)
			{//	�X�e���X�̎�����0�������ꍇ
				m_nStealthCut++;
				if (m_nStealthCut > MAX_STEALTHCUT)
				{//	0�ȏ�Ȃ��������
					m_nStealthLife = 300;
					m_nStealthCut = 0;
				}
			}
		}
		if (m_bDash == false || m_bDamage == true)
		{
			if (m_nDashLife == 0)
			{//	�_�b�V���̎�����0�������ꍇ
				m_nDashCut++;
				if (m_nDashCut > MAX_DASHTHCUT)
				{//	0�ȏ�Ȃ��������
					m_nDashLife = 80;
					m_nDashCut = 0;
				}
			}
		}

	CManager::m_CDebugProcLeft->Print("\nm_nDashLife%d", m_nDashLife);
	CManager::m_CDebugProcLeft->Print("\nm_nDashCut%d", m_nDashCut);

	if (m_bMove == true)
	{//	�����Ă�����
		if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_LEFT) == true*/)
		{
			if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true /*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
			{//	����ɓ���
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.25f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true /*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
			{//	�����ɓ���
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.75f;
			}
			else
			{//	���ɓ���
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.5f;
			}
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_RIGHT) == true*/)
		{
			if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true/*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
			{//	�E��ɓ���
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.25f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true/* ||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
			{//	�E���ɓ���
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.75f;
			}
			else
			{//	�E�ɓ���
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.5f;
			}
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true/* ||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
		{//	�O�ɓ���
			m_move.x += sinf(cameraRot.y + (D3DX_PI * 1.0f))*(WALK_SPEED + m_fMoveControl);
			m_move.z += cosf(cameraRot.y + (D3DX_PI * 1.0f))*(WALK_SPEED + m_fMoveControl);
			m_rotDest.y = cameraRot.y;
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
		{//	���ɓ���
			m_move.x += sinf(cameraRot.y)*(WALK_SPEED + m_fMoveControl);
			m_move.z += cosf(cameraRot.y)*(WALK_SPEED + m_fMoveControl);
			m_rotDest.y = D3DX_PI + cameraRot.y;
		}
	}
}

//=============================================================================
//	���Z���铮���̊Ǘ�
//=============================================================================
void CPlayer::ManagementAddMovement(void)
{
	//�ړI�̌����̏C��
	if (m_rotDest.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}
	//	��]�̊p�x�̃u�����h
	float fAngle = m_rotDest.y - m_rot.y;
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
	//	�d��
	m_move.y -= GRAVITY;
	// �ړ��ʉ��Z
	m_pos += m_move;
	// ��������
	m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
	m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	CManager::m_CDebugProcRight->Print("\n�U���̃t���[����( %d )", m_nAtkFream);
}

//=============================================================================
//	���[�V�����̐ݒ�Ǘ�
//=============================================================================
void CPlayer::ManagementSetMosion(void)
{
	//	�J�����̉�]�̎擾
	D3DXVECTOR3 cameraRot = CCamera::GetCameraRotate();
	switch (m_MosionState)
	{//	���[�V�����̏��
		//---------------------------------------------------------
		//	�j���[�g�������[�V�������
		//---------------------------------------------------------
	case MOSION_NEUTRAL:
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	�ړ����Ă����ꍇ	//	�ړ����[�V����
			m_nMotionType = 1;					//	�ړ����[�V����
			m_MosionState = MOSION_MOVE;		//	�ړ����[�V�����̏��
		}
		else if (m_bJump == true)
		{//	�W�����v�����ꍇ
			m_nMotionType = 2;					//	�W�����v���[�V����
			m_MosionState = MOSION_JUMP;		//	�W�����v���[�V�����̏��
		}
		else if (m_bSquat == true)
		{//	�X�N���b�g���Ă�����
			m_nMotionType = 6;					//	���Ⴊ�݃��[�V����
			m_MosionState = MOSION_SQUAT;		//	���Ⴊ�ݏ�Ԃ�
		}
		else if (m_bAttack == true)
		{//	�U�����[�V����
			m_nMotionType = 8;					//	�U�����[�V����
			m_MosionState = MOSION_ATTACK_000;	//	�U����Ԃ�
		}
		else if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;					//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;		//	���񂾏�Ԃ�
		}
		else if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;					//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;		//	�_���[�W��Ԃ�
		}
		if (m_nBltCut > 0)
		{//	�e��0�ȏゾ�����ꍇ
			if ((CManager::GetInputKeyboard()->GetPress(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetPress(XINPUT_GAMEPAD_B, 0) == true))
			{//	�G���^�[�L�[���������Ƃ�
				if (m_pBullet3D == NULL)
				{//	�e���g���ċ��Ȃ�������
					m_nMotionType = 4;				//	�e�𓊂��鏀�����[�V����
					m_MosionState = MOSION_BLTPRPE;	//	�e�𓊂��鏀�����
				}
			}
		}
		break;
		//---------------------------------------------------------
		//	�ړ����[�V�������
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
		{//	�ړ����Ă��Ȃ��ꍇ		//	�j���[�g�������[�V����
			m_nMotionType = 0;					//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
		}
		else if (m_bJump == true)
		{//	�W�����v��Ԃ������ꍇ
			m_nMotionType = 2;					//	�W�����v���[�V����
			m_MosionState = MOSION_JUMP;		//	�ړ����[�V�����̏��
		}
		else if (m_bSquat == true)
		{//	�X�N���b�g���Ă�����
			m_nMotionType = 7;					//	���Ⴊ��a�������[�V����
			m_MosionState = MOSION_SQUATMOVE;	//	���Ⴊ�ݕ������
		}
		else if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;					//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;		//	���񂾏�Ԃ�
		}
		else if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;					//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;		//	�_���[�W��Ԃ�
		}
		if (m_nBltCut > 0)
		{//	�e��0�ȏゾ�����ꍇ
			if ((CManager::GetInputKeyboard()->GetRelease(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetRelease(XINPUT_GAMEPAD_B, 0) == true))
			{//	�G���^�[�L�[���������Ƃ�
				if (m_pBullet3D == NULL)
				{//	�e���g���ċ��Ȃ�������
					m_nMotionType = 4;				//	�e�𓊂��鏀�����[�V����
					m_MosionState = MOSION_BLTPRPE;	//	�e�𓊂��鏀�����
				}
			}
		}
		break;
		//---------------------------------------------------------
		//	�W�����v���[�V�������
		//---------------------------------------------------------
	case MOSION_JUMP:
		if (m_bJump == false && m_move.y < 0.1f && m_move.y > -0.1f)
		{//	�W�����v����W�����v������Ȃ��Ȃ�v���C���[�̓������~�܂�����
			m_nMotionType = 3;							//	���n���[�V����
			m_move = D3DXVECTOR3(0.0f, m_move.y, 0.0f);	//	���n���͓������~�߂�
			m_nCntMosionChange++;						//	���[�V�����̕ύX����J�E���^�[���Z
		}
		else if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;					//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;		//	���񂾏�Ԃ�
		}
		else if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;					//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;		//	�_���[�W��Ԃ�
		}

		if (m_nCntMosionChange > 10)
		{//	���n�̃t���[�����w��̐��ȏア������
			m_MosionState = MOSION_LAND;		//	���n���[�V�������
		}

		break;
		//---------------------------------------------------------
		//	���n���[�V�������
		//---------------------------------------------------------
	case MOSION_LAND:
		if (m_bJump == false)
		{//	�W�����v������Ȃ������ꍇ
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;				//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;	//	�j���[�g�������[�V�����̏��
			}
			else if (m_bDisp == true)
			{//	���񂾏ꍇ
				m_nMotionType = 10;				//	���񂾃��[�V����
				m_MosionState = MOSION_DISP;	//	���񂾏�Ԃ�
			}
			else if (m_bDamage == true)
			{//	�_���[�W���󂯂��ꍇ
				m_nMotionType = 11;					//	�_���[�W���[�V����
				m_MosionState = MOSION_DAMAGE;		//	�_���[�W��Ԃ�
			}
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	�ړ����Ă�����
			m_nMotionType = 1;				//	�ړ����[�V����
			m_MosionState = MOSION_MOVE;	//	�ړ����[�V�����̏��
		}
		break;
		//---------------------------------------------------------
		//	�e�𓊂��鏀�����[�V����
		//---------------------------------------------------------
	case MOSION_BLTPRPE:
		m_nCntMosionChange++;					//	���[�V�����̕ύX����J�E���^�[���Z
		if ((CManager::GetInputKeyboard()->GetRelease(DIK_RETURN) == true ||
			CManager::GetInputXPad()->GetRelease(XINPUT_GAMEPAD_B, 0) == true))
		{//	�G���^�[�L�[��b�����Ƃ�
			if (m_nBltCut > 0)
			{//	�e��0�ȏゾ�����ꍇ
				m_nMotionType = 5;						//	�e�𓊂���
				m_MosionState = MOSION_BLTTHROW;		//	�e�𓊂���
			}
		}
		else
		{
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ				//	�ړ����[�V����
				m_nMotionType = 1;				//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;	//	�ړ����[�V�����̏��
			}
			else if (m_bJump == true)
			{//	�W�����v�����ꍇ
				m_nMotionType = 2;				//	�W�����v���[�V����
				m_MosionState = MOSION_JUMP;	//	�ړ����[�V�����̏��
			}
			else if (m_bDisp == true)
			{//	���񂾏ꍇ
				m_nMotionType = 10;				//	���񂾃��[�V����
				m_MosionState = MOSION_DISP;	//	���񂾏�Ԃ�
			}
			else if (m_bDamage == true)
			{//	�_���[�W���󂯂��ꍇ
				m_nMotionType = 11;					//	�_���[�W���[�V����
				m_MosionState = MOSION_DAMAGE;		//	�_���[�W��Ԃ�
			}
		}
		break;
		//---------------------------------------------------------
		//	�e�����郂�[�V����
		//---------------------------------------------------------
	case MOSION_BLTTHROW:
		m_nCntMosionChange++;							//	���[�V�����̕ύX����J�E���^�[���Z
		if (m_pBullet3D == NULL && m_nCntMosionChange >= m_nCouterFreamMax[MOSION_BLTTHROW] - 35)
		{//	�e���g���Ă��Ȃ�������
		 //	�e�̐���
			m_pBullet3D = CBullet3D::Create
			(D3DXVECTOR3(m_apModel[3]->GetMtxWorld()._41 + sinf(m_rot.y*D3DX_PI)*9.0f, m_apModel[3]->GetMtxWorld()._42 - 7.0f, m_apModel[3]->GetMtxWorld()._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(sinf(m_rot.y - D3DX_PI)*5.0f, 7.0f, cosf(m_rot.y - D3DX_PI)* 5.0f), CBullet3D::BULLET3D_TYPE_BOOM);
			AddBulletGan(-1);							//	�e�̐������炷
		}
		if (m_pBullet3D != NULL && m_nCntMosionChange >= m_nCouterFreamMax[MOSION_BLTTHROW])
		{//	���[�V�����̍ő吔����������		//	���[�V�����̍ő吔�𒴂����ꍇ
			m_nMotionType = 0;					//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			m_pBullet3D = NULL;
		}
		if (m_pBullet3D == NULL)
		{//	�e���g���Ă��Ȃ�������
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ	//	�ړ����[�V����
				m_nMotionType = 1;				//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;	//	�ړ����[�V�����̏��
			}
			else if (m_bJump == true)
			{//	�W�����v������
				m_nMotionType = 2;				//	�W�����v���[�V����
				m_MosionState = MOSION_JUMP;	//	�ړ����[�V�����̏��
			}
			else if (m_bDisp == true)
			{//	���񂾏ꍇ
				m_nMotionType = 10;				//	���񂾃��[�V����
				m_MosionState = MOSION_DISP;	//	���񂾏�Ԃ�
			}
			else if (m_bDamage == true)
			{//	�_���[�W���󂯂��ꍇ
				m_nMotionType = 11;				//	�_���[�W���[�V����
				m_MosionState = MOSION_DAMAGE;	//	�_���[�W��Ԃ�
			}
		}
		break;
		//---------------------------------------------------------
		//	���Ⴊ�݃��[�V����
		//---------------------------------------------------------
	case MOSION_SQUAT:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f&&m_bSquat == false)
		{//	�ړ����Ă��Ȃ��ꍇ
			m_nMotionType = 0;				//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;	//	�j���[�g�������[�V�����̏��
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	�ړ����Ă����ꍇ	//	�X�N���b�g���Ă����Ԃ̂Ƃ�
			m_nMotionType = 7;					//	�ړ����[�V����
			m_MosionState = MOSION_SQUATMOVE;	//	�ړ����[�V�����̏��
		}
		else if (m_bJump == true)
		{//	�W�����v��Ԃ������ꍇ
			m_nMotionType = 2;					//	�W�����v���[�V����
			m_MosionState = MOSION_JUMP;		//	�ړ����[�V�����̏��
		}
		else if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;					//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;		//	���񂾏�Ԃ�
		}
		else if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;				//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;	//	�_���[�W��Ԃ�
		}
		break;
		//---------------------------------------------------------
		//	���Ⴊ�ݕ������[�V����
		//---------------------------------------------------------
	case MOSION_SQUATMOVE:

		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f &&m_bSquat == true)
		{//	�ړ����Ă��Ȃ��ꍇ
			m_nMotionType = 6;				//	�j���[�g�������[�V����
			m_MosionState = MOSION_SQUAT;	//	�j���[�g�������[�V�����̏��
		}
		if (m_bSquat == false)
		{//	�ړ����Ă��Ȃ��ꍇ					//	�j���[�g�������[�V����
			m_nMotionType = 0;					//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
		}
		else if (m_bJump == true)
		{//	�W�����v��Ԃ������ꍇ
			m_nMotionType = 2;					//	�W�����v���[�V����
			m_MosionState = MOSION_JUMP;		//	�ړ����[�V�����̏��
		}
		else if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;					//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;		//	���񂾏�Ԃ�
		}
		else if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;				//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;	//	�_���[�W��Ԃ�
		}
		break;
		//---------------------------------------------------------
		//	�U�����[�V����	�L�b�N
		//---------------------------------------------------------
	case MOSION_ATTACK_000:
		m_nCntMosionChange++;							//	���[�V�����̕ύX����J�E���^�[���Z
		if (m_nCouterFreamMax[MOSION_ATTACK_000] + 25 > m_nCntMosionChange  && m_nCouterFreamMax[MOSION_ATTACK_000] - 15 < m_nCntMosionChange)
		{//	�R���{�ł���܂ł̃t���[���ȏ�܂ł������ꍇ
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_F) == true ||
				CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_X, 0) == true)
			{	//	�R���{�o����t���[��
				m_nMotionType = 9;					//	���̍U�����[�V������
				m_MosionState = MOSION_ATTACK_001;	//	���̍U���Ɉڍs�̏��
				m_bAttack = true;					//	�U��������Ȃ�
			}
		}
		else if (m_nCntMosionChange > m_nCouterFreamMax[MOSION_ATTACK_000] + 25)
		{//	�J�E���^�[���t���[���̍��v�l��
			m_nMotionType = 0;					//	�j���[�g�������[�V����
			m_MosionState = MOSION_NEUTRAL;		//	�j���[�g�������[�V�����̏��
			m_bAttack = false;
		}
		if (m_bDamage == true)
		{//	�_���[�W���󂯂��ꍇ
			m_nMotionType = 11;				//	�_���[�W���[�V����
			m_MosionState = MOSION_DAMAGE;	//	�_���[�W��Ԃ�
		}
		break;
		//---------------------------------------------------------
		//	�U�����[�V����	�p���`
		//---------------------------------------------------------
	case MOSION_ATTACK_001:
		m_nCntMosionChange++;					//	���[�V�����̕ύX����J�E���^�[���Z
		if (m_nCouterFreamMax[MOSION_ATTACK_001] < m_nCntMosionChange)
		{//	���[�V�����̃t���[�����߂����ꍇ
			m_bAttack = false;					//	�U����Ԃ�����
			m_bMove = true;						//	�������Ԃɖ߂�
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ	//	�ړ����[�V����
				m_nMotionType = 1;				//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;	//	�ړ����[�V�����̏��
				m_bAttack = false;
			}
			else if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;				//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;	//	�j���[�g�������[�V�����̏��
			}
			else if (m_bDamage == true)
			{//	�_���[�W���󂯂��ꍇ
				m_nMotionType = 11;				//	�_���[�W���[�V����
				m_MosionState = MOSION_DAMAGE;	//	�_���[�W��Ԃ�
			}
		}
		else
		{//	�U�����������瓮�����Ȃ�
			m_bMove = false;					//	�����Ȃ����
		}
		break;
		//---------------------------------------------------------
		//	���񂾃��[�V����
		//---------------------------------------------------------
	case MOSION_DISP:
		break;
		//---------------------------------------------------------
		//	�_���[�W���[�V����
		//---------------------------------------------------------
	case MOSION_DAMAGE:
		if (m_bDamage == false)
		{//	�_���[�W��Ԃ���Ȃ�������
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	�ړ����Ă����ꍇ	//	�ړ����[�V����
				m_nMotionType = 1;				//	�ړ����[�V����
				m_MosionState = MOSION_MOVE;	//	�ړ����[�V�����̏��
				m_bAttack = false;
			}
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	�ړ����Ă��Ȃ��ꍇ
				m_nMotionType = 0;				//	�j���[�g�������[�V����
				m_MosionState = MOSION_NEUTRAL;	//	�j���[�g�������[�V�����̏��
			}
		}
		if (m_bDisp == true)
		{//	���񂾏ꍇ
			m_nMotionType = 10;				//	���񂾃��[�V����
			m_MosionState = MOSION_DISP;	//	���񂾏�Ԃ�
		}
		break;
	}
	if (m_nMotionType != m_nMotionTypeOld)
	{//	���[�V�������ς�����ꍇ
		m_nCntMosionChange = 0;				//	�J�E���^�[�̏�����
		m_nAtkFream = 0;					//
	}

	CManager::m_CDebugProcLeft->Print("\n���C�t�@( %d )", m_nLife);
}
//=============================================================================
//	�����蔻��̑���
//=============================================================================
void CPlayer::ManagementCollision(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	m_bBlock = false;	// �������Ă��Ȃ�
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// ���݁@
	CScene *pSceneNext = NULL;								// ��

	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
	 // ���I�u�W�F�N�g����ۑ�
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
		{//	���������ꍇ
			CFloor *pFloor = (CFloor*)pScene;				//	���ɃL���X�g
			pFloor->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		// �����蔻��
		}
		// ���̃I�u�W�F�N�g�ɐݒ�
		pScene = pSceneNext;
	}

	// �V�[��
	pScene = CScene::GetScene(CScene::PRIORITY_3);		// ����
	pSceneNext = NULL;									// ��

	bool bHitIn = false;
	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
	 // ���I�u�W�F�N�g����ۑ�
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{// �I�u�W�F�N�g�^�C�v���u���b�N��������
			CBlock *pBlock = (CBlock*)pScene;									// �u���b�N�ɃL���X�g
			pBlock->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);	// �����蔻��
			if (pBlock->StealthCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin)==true )
			{
				bHitIn = true;							//	�X�e���X�u���b�N�̒��ɓ������ꍇ
			}
			if (pBlock->StageNxstCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin) == true)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	������7�~�߂�
			}

			//if (pBlock->StealthCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin) == true && bHitIn == true)
			//{
			//	m_bStealthMode = true;							//	�X�e���X�u���b�N�̒��ɓ������ꍇ
			//	CManager::m_CDebugProcLeft->Print("\n�X�e���X���[�h");
			//}
			//else
			//{
			//	m_bStealthMode = false;							//	�X�e���X�u���b�N�̒��ɓ������ꍇ
			//}

			bool *bLand = pBlock->GetHit();
			if (bLand[0] == true)
			{// �㔻��
				m_bBlock = true;			// ��������
			}
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
		{//	�ǂ������ꍇ
			CWall *pWall = (CWall*)pScene;					//	�ǂɃL���X�g
			pWall->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		// �����蔻��
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
		{//	�G�������ꍇ
			CEnemy *pEnemy = (CEnemy*)pScene;				//	�G�ɃL���X�g
			pEnemy->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		//	�����蔻��

			CEnemyRobotSpine *pEnemyRobotSpine = (CEnemyRobotSpine*)pScene;				//	�G�ɃL���X�g
			if (pEnemyRobotSpine->Gettype() == 2)
			{//	���ɓG�������ꍇ
				if (pEnemyRobotSpine->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
				{//	�v���C���[�Ƃ̊p�x
					if (m_MosionState != MOSION_DAMAGE &&m_state != STATE_DAMAGE)
					{//	�_���[�W��Ԃ������ꍇ
						float fAngle = atan2f(m_pos.x - pEnemyRobotSpine->Getpos().x, m_pos.z - pEnemyRobotSpine->Getpos().z);
						HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 30.25f, 0.0f, cosf(fAngle) * 30.25f));
						pEnemyRobotSpine->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						//m_nEffectCounter++;	//	�G�t�F�N�g���o�͂����J�E���^�[
						//if ((m_nEffectCounter % 8) == 0)
					}
					//	�@HIT�G�t�F�N�g
					CEffect::Create
					(D3DXVECTOR3(pEnemyRobotSpine->Getpos().x + sinf(pEnemyRobotSpine->Getrot().y - D3DX_PI)*30.0f,
						pEnemyRobotSpine->Getsize(1).y / 2 + 40,
						pEnemyRobotSpine->Getpos().z + cosf(pEnemyRobotSpine->Getrot().y - D3DX_PI)*30.0f), 1, 6);
				}
			}
			CEnemyRobotNomal *pEnemyRobotNomal = (CEnemyRobotNomal*)pScene;				//	�G�ɃL���X�g
			if (pEnemyRobotNomal->Gettype() == 0)
			{//	�ʏ�̓G�������ꍇ
				if (pEnemyRobotNomal->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
				{//	�v���C���[�Ƃ̊p�x
					if (m_MosionState != MOSION_DAMAGE &&m_state != STATE_DAMAGE)
					{//	�_���[�W��Ԃ������ꍇ
						pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE001);	//	�_���[�W��
						float fAngle = atan2f(m_pos.x - pEnemyRobotNomal->Getpos().x, m_pos.z - pEnemyRobotNomal->Getpos().z);
						HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 30.25f, 0.0f, cosf(fAngle) * 30.25f));
					}
				}
			}
		}
		// ���̃I�u�W�F�N�g�ɐݒ�
		pScene = pSceneNext;
	}
	// �V�[��
	pScene = CScene::GetScene(CScene::PRIORITY_4);		// ����
	pSceneNext = NULL;									// ��
	while (pScene != NULL)
	{// NULL�ȊO�̏ꍇ
		pSceneNext = pScene->GetSceneNext();			//	���̃I�u�W�F�N�g�̏����擾
		if (pScene->GetObjType() == CScene::OBJTYPE_ITEM)
		{//	�I�u�W�F�N�g���A�C�e����������
			CItem *pItem = (CItem*)pScene;				//	�A�C�e���ɃL���X�g
			if (pItem->CollisionItem(&m_pos, &m_move, m_vtxMax, m_vtxMin) == true)
			{//	�A�C�e���ɓ��������ꍇ
				if (pItem->GetItemType() == pItem->TYPE_BULLETADD)
				{//	�e�̉��Z�A�C�e���������ꍇ
					CPlayer::AddBulletGan(1);
				}
				else if (pItem->GetItemType() == pItem->TYPE_LIFEUP)
				{//	�e�̉��Z�A�C�e���������ꍇ
					HitLife(1,D3DXVECTOR3(0.0f,0.0f,0.0f));
				}
			}
		}
		if (pScene->GetObjType() == CScene::OBJTYPE_BULLET2D)
		{//	�e��
			CBullet2D *pBullet2D = (CBullet2D*)pScene;	//	�e2D�ɃL���X�g
			D3DXVECTOR3 moveOld = m_move;
			if (pBullet2D->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
			{//	�e�̔���
			 //	�v���C���[�Ƃ̊p�x
				float fAngle = atan2f(m_pos.x - pBullet2D->Getpos().x, m_pos.z - pBullet2D->Getpos().z);
				HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 15.25f, 0.0f, cosf(fAngle) * 15.25f));
				//	�@HIT�G�t�F�N�g
				CEffect::Create(D3DXVECTOR3(pBullet2D->Getpos().x ,pBullet2D->Getpos().y,pBullet2D->Getpos().z), 1, 7);
				pBullet2D->Uninit();
			}
		}
		pScene = pSceneNext;		//	����ݒ�
	}

	if (bHitIn == true)
	{//	�X�e���X�u���b�N�̒��ɓ������ꍇ
		m_bStealthMode = true;
		CManager::m_CDebugProcLeft->Print("\n�X�e���X���[�h");
	}
	else
	{//	�X�e���X�u���b�N�̒��ɓ����Ă��Ȃ��ꍇ
		m_bStealthMode = false;
	}
}

//==============================================================================
//	�_���[�W�v�Z
//==============================================================================
void CPlayer::HitLife(int nDamage, D3DXVECTOR3 move)
{
	CSound *pSound = CManager::GetSound();
	int nLifeValue = nDamage;		//	�v�Z�p�̗͂̒l
	if (m_nLife >= 0)
	{//�v�Z�����l�������̍ő�l��艺�̏ꍇ
		if (m_state != STATE_INVINCIBLE)
		{//	���G��ԈȊO
			m_move += move;
			if (nLifeValue <= -1)
			{//	HP���܂��c���Ă�����
				m_state = STATE_DAMAGE;		//	�_���[�W��Ԃɐ؂�ւ�
				if (m_state == STATE_DAMAGE)
				{//	�_���[�W��Ԃ������ꍇ
					m_nLife += nLifeValue;			//	�v�Z�����l�����C�t�ɑ��
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);	// �_���[�W��
				}
			}
			else if (nLifeValue >= 1&& m_nLife<10)
			{
				m_nLife += nLifeValue;			//	�v�Z�����l�����C�t�ɑ��
			}
		}
	}
	if (m_nLife <= 0 && nDamage <= -1)
	{//	���C�t��0�ȉ��ɂȂ����ꍇ
		m_nLife += nLifeValue;			//	�v�Z�����l�����C�t�ɑ��
		m_state = STATE_DEATH;		//	�X�e�[�^�X�����S��Ԃɕς���
	}
}
//==============================================================================
//	�e�̐�
//==============================================================================
void CPlayer::AddBulletGan(int nAdd)
{
	m_nBltCut = m_nBltCut + nAdd;		//	�e�̒e�����炷
	CBulletNumber::AddNum(nAdd);		//	�e�̐��l�̂̌��Z
}

//=============================================================================
// �v���C���[�̓����蔻��
//=============================================================================
void  CPlayer::BoxCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	D3DXVECTOR3 PlayerPos = CPlayer::Getpos();				//	�ʒu�̎擾
	D3DXVECTOR3 PlayerMove = CPlayer::Getmove();			//	�����̎擾
	D3DXVECTOR3 PlayerRot = CPlayer::Getrot();				//	��]�̎擾
	D3DXVECTOR3 PlayerSizeMax = CPlayer::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 PlayerSizeMin = CPlayer::Getsize(1);		//	�傫���̍ŏ��l

	if ((PlayerPos.x + PlayerSizeMin.x) < (pPos->x + (sizeMax.x)) &&
		(pPos->x + (sizeMin.x)) < (PlayerPos.x + PlayerSizeMax.x) &&
		(PlayerPos.z + PlayerSizeMin.z) < (pPos->z + (sizeMax.z)) &&
		(pPos->z + (sizeMin.z)) < (PlayerPos.z + PlayerSizeMax.z))
	{// X/Z�͈͊m�F
		if ((pPos->y + sizeMin.y) <= (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMax.y) <= (pPosOld->y + sizeMin.y))
		{// �ォ��̓����蔻��
			pPos->y = PlayerPos.y + PlayerSizeMax.y + (sizeMin.y);
			move->y = 0.0f;
		}
		else if ((PlayerPos.y + PlayerSizeMin.y) <= (pPos->y + sizeMax.y) && (pPosOld->y + sizeMax.y) <= (PlayerPos.y + PlayerSizeMin.y))
		{// ������̓����蔻��
			pPos->y = pPosOld->y;
			move->y = 0.0f;
		}
	}
	if ((pPos->y + sizeMin.y) < (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMin.y) < (pPos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((PlayerPos.z + PlayerSizeMin.z) < (pPos->z + (sizeMax.z)) && (pPos->z + (sizeMin.z)) < (PlayerPos.z + PlayerSizeMax.z))
		{// Z�͈͊m�F
			if ((PlayerPos.x + PlayerSizeMin.x) <= (pPos->x + sizeMax.x) && (pPosOld->x + sizeMax.x) <= (PlayerPos.x + PlayerSizeMin.x))
			{// ������̓����蔻��
				pPos->x = PlayerPos.x + PlayerSizeMin.x + (sizeMin.x);
				move->x = 0.0f;
			}
			else if ((pPos->x + sizeMin.x) <= (PlayerPos.x + PlayerSizeMax.x) && (PlayerPos.x + PlayerSizeMax.x) <= (pPosOld->x + sizeMin.x))
			{// �E����̓����蔻��
				pPos->x = PlayerPos.x + PlayerSizeMax.x + (sizeMax.x);
				move->x = 0.0f;
			}
		}
	}
	if ((pPos->y + sizeMin.y) < (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMin.y) < (pPos->y + sizeMax.y))
	{// Y�͈͊m�F
		if ((PlayerPos.x + PlayerSizeMin.x) < (pPos->x + (sizeMax.x)) && (pPos->x + (sizeMin.x)) < (PlayerPos.x + PlayerSizeMax.x))
		{// X�͈͊m�F
			if ((PlayerPos.z + PlayerSizeMin.z) <= (pPos->z + sizeMax.z) && (pPosOld->z + sizeMax.z) <= (PlayerPos.z + PlayerSizeMin.z))
			{// ��O����̓����蔻��
				pPos->z = PlayerPos.z + PlayerSizeMin.z + (sizeMin.z);
				move->x = 0.0f;
			}
			else if ((pPos->z + sizeMin.z) <= (PlayerPos.z + PlayerSizeMax.z) && (PlayerPos.z + PlayerSizeMax.z) <= (pPosOld->z + sizeMin.z))
			{// ��납��̓����蔻��
				pPos->z = PlayerPos.z + PlayerSizeMax.z + (sizeMax.z);
				move->x = 0.0f;
			}
		}
	}
}

//=============================================================================
// �~�̓����蔻��
//=============================================================================
void CPlayer::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	D3DXVECTOR3 pos = CPlayer::Getpos();					//	�ʒu�̎擾
	//	�����̌v�Z
	float fLength = (pPos->x - m_pos.x)* (pPos->x - m_pos.x) + (pPos->z - m_pos.z)* (pPos->z - m_pos.z);

}

//=============================================================================
// �U���̓����蔻��
//=============================================================================
bool CPlayer::AttackCollsion(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{

	bool bHit = false;			//	�U���������������ǂ���
	D3DXVECTOR3 PlayerPos = CPlayer::Getpos();				//	�ʒu�̎擾
	D3DXVECTOR3 PlayerMove = CPlayer::Getmove();			//	�����̎擾
	D3DXVECTOR3 PlayerRot = CPlayer::Getrot();				//	��]�̎擾
	D3DXVECTOR3 PlayerSizeMax = CPlayer::Getsize(0);		//	�傫���̍ő�l
	D3DXVECTOR3 PlayerSizeMin = CPlayer::Getsize(1);		//	�傫���̍ŏ��l

	if (m_bAttack == true)
	{//	�U�����Ă��邩�ǂ���
		if (m_MosionState == MOSION_ATTACK_000)
		{//	�U��000���������ꍇ
			m_nAtkFream++;
			if (m_nAtkFream < 12 && m_nAtkFream > 6)
			{//	�U���̃R���W�������ł�t���[��
				if ((m_apModel[9]->GetMtxWorld()._41) < (pPos->x + sizeMax.x + ATTACK_COLL_EXPAND_X_000) &&
					(pPos->x + sizeMin.x + -ATTACK_COLL_EXPAND_X_000) < (m_apModel[9]->GetMtxWorld()._41) &&
					(m_apModel[9]->GetMtxWorld()._42) < (pPos->y + sizeMax.y + ATTACK_COLL_EXPAND_Y_000) &&
					(pPos->y + sizeMin.y + -ATTACK_COLL_EXPAND_Y_000) < (m_apModel[9]->GetMtxWorld()._42) &&
					(m_apModel[9]->GetMtxWorld()._43 < (pPos->z + sizeMax.z + ATTACK_COLL_EXPAND_Z_000)) &&
					(pPos->z + sizeMin.z + -ATTACK_COLL_EXPAND_Z_000) < (m_apModel[9]->GetMtxWorld()._43))
				{//	��̃I�t�Z�b�g�̃x�N�g�����G�̑傫��+�w��̒l�͈͓̔��������ꍇ
					bHit = true;			//	��������
					m_bAttack = false;		//	�U��������Ȃ�
				}
			}
		}
		else if (m_MosionState == MOSION_ATTACK_001)
		{//	�U��001���������ꍇ
			m_nAtkFream++;
			if (m_nAtkFream < m_nCouterFreamMax[MOSION_ATTACK_001] -10 && m_nAtkFream > 5)
			{//	�U���̃R���W�������ł�t���[��
				if ((m_apModel[3]->GetMtxWorld()._41) < (pPos->x + sizeMax.x + ATTACK_COLL_EXPAND_X_001) &&
					(pPos->x + sizeMin.x + -ATTACK_COLL_EXPAND_X_001) < (m_apModel[3]->GetMtxWorld()._41) &&
					(m_apModel[3]->GetMtxWorld()._42) < (pPos->y + sizeMax.y + ATTACK_COLL_EXPAND_Y_001) &&
					(pPos->y + sizeMin.y + -ATTACK_COLL_EXPAND_Y_001) < (m_apModel[3]->GetMtxWorld()._42) &&
					(m_apModel[3]->GetMtxWorld()._43 < (pPos->z + sizeMax.z + ATTACK_COLL_EXPAND_Z_001)) &&
					(pPos->z + sizeMin.z + -ATTACK_COLL_EXPAND_Z_001) < (m_apModel[3]->GetMtxWorld()._43))
				{//	��̃I�t�Z�b�g�̃x�N�g�����G�̑傫��+�w��̒l�͈͓̔��������ꍇ
					m_bAtkLastHit = true;	//	�ŏI�U������������
					bHit = true;			//	��������
					m_bAttack = false;		//	�U��������Ȃ�
				}
			}
		}
	}
	if (m_bAttack == false)
	{//	�t���[���̏�����
		m_nAtkFream = 0;		//	�U���̃t���[��
		m_bAtkLastHit = false;	//	�ŏI�̍U��������������
	}
	//	�l��Ԃ�
	return bHit;
}

//=============================================================================
// ���[�V�����̍X�V
//=============================================================================
void CPlayer::UpdateMotion(void)
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
			if (m_nMotionType == m_nMotionTypeOld )
			{//	���̎�ނ��ߋ��̎�ނ������������ꍇ
				//	���݂̃L�[���擾
				pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
				//	���̃L�[���擾
				pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

				//	���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

				//POSX
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//POSY
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//POSZ
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);

				//ROTX
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

				//ROTY
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);

				//ROTZ
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);


				//	�ړI�̌����̏C���̏C��
				if (rotmotion.x < -D3DX_PI){rotmotion.x += D3DX_PI * 2.0f;}
				else if (rotmotion.x > D3DX_PI){rotmotion.x -= D3DX_PI * 2.0f;}
				if (rotmotion.y < -D3DX_PI){rotmotion.y += D3DX_PI * 2.0f;}
				else if (rotmotion.y > D3DX_PI){rotmotion.y -= D3DX_PI * 2.0f;}
				if (rotmotion.z < -D3DX_PI){rotmotion.z += D3DX_PI * 2.0f;}
				else if (rotmotion.z > D3DX_PI){rotmotion.z -= D3DX_PI * 2.0f;}

				//	�p�[�c�𓮂���
				m_apModel[nCntParts]->Setrot(rotmotion);
				//	�ʒu��ݒ肷��
				m_apModel[nCntParts]->Setpos(m_OffSetPos[nCntParts] + posmotion);
			}
			else	if (m_nMotionType != m_nMotionTypeOld)
			{
				//	���݂̃L�[���擾
				pKey = &m_pKeyInfo[m_nMotionTypeOld][m_nKey].aKey[nCntParts];
				//	���̃L�[���擾
				pNextKey = &m_pKeyInfo[m_nMotionType][0].aKey[nCntParts];

				//	���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fRateMotion =((float)m_nCountFlame - 60) * 1.0f;

				//POSX
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.x = (fDiffMotion / fRateMotion);

				//POSY
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.y = (fDiffMotion / fRateMotion);

				//POSZ
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.z = (fDiffMotion / fRateMotion);

				//ROTX
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.x = (fDiffMotion / fRateMotion);

				//ROTY
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.z = (fDiffMotion / fRateMotion);

				//ROTZ
				//	���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	�����̏C��
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.y = (fDiffMotion / fRateMotion);

				//	�ړI�̌����̏C���̏C��
				if (rotmotion.x < -D3DX_PI) { rotmotion.x += D3DX_PI * 2.0f; }
				else if (rotmotion.x > D3DX_PI) { rotmotion.x -= D3DX_PI * 2.0f; }
				if (rotmotion.y < -D3DX_PI) { rotmotion.y += D3DX_PI * 2.0f; }
				else if (rotmotion.y > D3DX_PI) { rotmotion.y -= D3DX_PI * 2.0f; }
				if (rotmotion.z < -D3DX_PI) { rotmotion.z += D3DX_PI * 2.0f; }
				else if (rotmotion.z > D3DX_PI) { rotmotion.z -= D3DX_PI * 2.0f; }

				//	�p�[�c�𓮂���
				m_apModel[nCntParts]->Setrot(m_apModel[nCntParts]->Getrot() + rotmotion);
				//	�ʒu��ݒ肷��
				m_apModel[nCntParts]->Setpos(m_OffSetPos[nCntParts] + posmotion);

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
void CPlayer::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile= NULL;		//	�t�@�C���|�C���^
	char *pStrcur;			//	���݂̐擪�̕�����
	char aLine[256];		//	������
	char aStr[256];			//	�ꎞ�ۑ�������
	int nIndex = 0;			//	���݂̃C���f�b�N�X
	int nWord = 0;			//	�|�b�v�ŕԂ��ꂽ�l��ێ�
	int nCounter = 0;		//	�J�E���^�[

	D3DXVECTOR3 ParentPos;	//�e�̈ʒu�����擾
	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "r");
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
							&m_pBuffMat[nCntModel],
							NULL,
							&m_nNumMat[nCntModel],
							&m_pMesh[nCntModel]);

						D3DXMATERIAL *pmat;									// �}�e���A���f�[�^�ւ̃|�C���^
						D3DMATERIAL9 *matDef;								// ���݂̃}�e���A���ۑ��p
						pmat = (D3DXMATERIAL*)m_pBuffMat[nCntModel]->GetBufferPointer();
						matDef = new D3DMATERIAL9[m_nNumMat[nCntModel]];						//	�}�e���A���̃������̊m��
						m_pTexture[nCntModel] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntModel]];	//	�e�N�X�`���̃������̊m��

						for (DWORD tex = 0; tex < m_nNumMat[nCntModel]; tex++)
						{// �J�E���g
							matDef[tex] = pmat[tex].MatD3D;						//�@�}�e���A���̃v���p�e�B���L�q���� D3DMATERIAL9 �\����
							matDef[tex].Ambient = matDef[tex].Diffuse;			//�@���̒��ړ����镔���̐F�����𓖂���Ȃ������Ɠ���������
							m_pTexture[nCntModel][tex] = NULL;					//	�e�N�X�`��������ɂ���
							if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
							{// �e�N�X�`�����g�p���Ă��� & ������̒�����0�ȏゾ������
								if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTexture[nCntModel][tex])))
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
								D3DXVECTOR3(m_aKayOffset[nIndex].fposX,m_aKayOffset[nIndex].fposY, m_aKayOffset[nIndex].fposZ),
								D3DXVECTOR3(m_aKayOffset[nIndex].frotX,m_aKayOffset[nIndex].frotY,m_aKayOffset[nIndex].frotZ));

								//�ʒu���
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//���f�������蓖��
								m_apModel[nIndex]->BindModel(m_nNumMat[nIndex], m_pMesh[nIndex], m_pBuffMat[nIndex]);

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
char *CPlayer::ReadLine(FILE *pFile, char *pDst)
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
char * CPlayer::GetLineTop(char * pStr)
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
int CPlayer::PopString(char * pStr, char * pDest)
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
