//=============================================================================
//
//	�G�̏��� [enemy.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "score.h"
#include "bullet.h"
#include "scene.h"
#include "explosion.h"
#include "enemycount.h"

//==============================================================================
//	�ÓI�����o�ϐ�������
// ==============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_Texture[MAX_ENEMY_TYPE] = {};	//	�e�N�X�`���̏�����
int CEnemy::m_nNUM_ENEMY = NULL;							//	�G�̉��Z�̏�����

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemy::CEnemy() : CScene2D(4)
{
	m_nType = 0;						//	��ނ̏�����
	m_nAICounter = 0;					//	AI����V�K������[���[
	m_bBulletAttck = false;				//	�U���̏�Ԃ̏�����
	m_nLife = 0;						//	�����̏�����
	enemystate = ENEMYSTATE_NOMAL;		//	��Ԃ̏�����
	m_nCounterState = 0;				//	�X�e�[�^�X�J�E���^�[�̏�����
	m_nNUM_ENEMY++;						//	�G�̐��̉��Z
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemy::~CEnemy()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, int nType)
{
	m_nAICounter = rand() % 200 + 1;	//	�G�̈ړ��̃��E���h�ݒ�
	m_bBulletAttck = false;				//	�e�������Ă��Ȃ����
	enemystate = ENEMYSTATE_NOMAL;		//	�ʏ���
	m_nCounterState = 0;				//	�J�E���^�[�̏�����
	CScene2D::Init();
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_ENEMY);

	m_nType = nType;					//	��ނ̑��
	m_nLife = nLife;					//	�����̑��

	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(0.0f, -0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetVtxPosition(&pPos[0], pos);		//	�ʒu�̔��f
	SetType(m_nType);					//	��ނ̔��f
	SetLife(m_nLife);					//	�����̔��f
	CEnemycount::AddEnemyCount(+1);		//	�G�̉��Z

	//	�l��Ԃ�
	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CEnemy::Uninit(void)
{
	//	�V�[��2D�̏I������
	CScene2D::Uninit();
	m_nNUM_ENEMY--;		//	�G�̌��Z
}

//==============================================================================
//	�X�V����
//==============================================================================
void CEnemy::Update(void)
{
	m_nAICounter++;

	switch (enemystate)
	{
	case ENEMYSTATE_NOMAL:
		break;
	case ENEMYSTATE_DAMAGE:
		CScene2D::ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			enemystate = ENEMYSTATE_NOMAL;
			CScene2D::ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	�v���C���[�̐�������
//==============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, int nType)
{
	CEnemy *pEnemy = {};

	if (pEnemy == NULL)
	{
		if (nType == 0)
		{
			pEnemy = new CEnemyType000;
		}
		else if (nType == 1)
		{
			pEnemy = new CEnemyType001;
		}
		else if (nType == 2)
		{
			pEnemy = new CEnemyType002;
		}
		else if (nType == 3)
		{
			pEnemy = new CEnemyType003;
		}
		else
		{//	�^�C�v�ȊO��������
			pEnemy = new CEnemyType000;
		}

		if (pEnemy != NULL)
		{
			// �w�i�̏���������
			pEnemy->Init(pos,move, nLife,nType);
			//	�w�i�̃e�N�X�`���̊��蓖��
			pEnemy->BindTexture(m_Texture[nType]);
		}
		else
		{
		}
	}
	return pEnemy;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CEnemy::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_3, &m_Texture[3]);
	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		//	�e�N�X�`���̔j��
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}
//==============================================================================
//	�_���[�W�v�Z
//==============================================================================
void CEnemy::Hit(int nDamage)
{
	D3DXVECTOR3 pos = GetPosition();
	float fHeight = GetfHeight();							//	����
	m_nLife -= nDamage;
	CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);
	if (m_nLife <= 0)
	{
		CScore::AddScore(100);											//�@�X�R�A���Z
		CExplosion::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f));									//	�����̐���
		Uninit();														//

		CEnemycount::AddEnemyCount(-1);
	}
	else
	{
		m_nCounterState = 15;
		enemystate = ENEMYSTATE_DAMAGE;
	}
}

//==============================================================================
//	�G�̐��̎擾
//==============================================================================
int  CEnemy::GetNUMENEMY(void)
{
	return m_nNUM_ENEMY;
}

//============================================================================================================================================================
//	�G�l�~�[�^�C�v000
//============================================================================================================================================================
//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemyType000::CEnemyType000()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemyType000::~CEnemyType000()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemyType000::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;

	CEnemy::Init(pos, move,nLife, nType);

	return S_OK;
}
//==============================================================================
//	�I������
//==============================================================================
void CEnemyType000::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	�X�V����
//==============================================================================
void CEnemyType000::Update(void)
{

	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	�ʒu
	D3DXVECTOR3 move = GetMoveing();						//	����
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	�v���C���[�̓����̎擾
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	�v���C���[�̓����̎擾
	float fWindth = GetfWindth();							//	��
	float fHeight = GetfHeight();							//	����
	fWindth = ENEMY_POLIGON_X_000;
	fHeight = ENEMY_POLIGON_Y_000;
	m_bAttackMove = false;									//	�v���C���[�ւ̍U���͈͂���Ȃ�

	m_posOld = pos;

	float fDiffAngle;				//����
	float fDestAngle;				//�ړI�̊p�x
	float fMoveAngle;				//���݂̊p�x
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 1.0f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 200 <= playerpos.x && pos.x + 200 >= playerpos.x)
	{//	�v���C���[�ւ̍U���͈�
		m_bAttackMove = true;
		if (playermove.x >= 0.0f)
		{
			move.x -= playermove.x;
			move.x += sinf(fDiffAngle)*1.05f;
		}
		else if (playermove.x <= 0.0f)
		{
			move.x += -playermove.x;
			move.x += sinf(fDiffAngle)*1.05f;
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch(move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.75f;
		if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.75f;
		if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	�d��
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	�u���b�N�̈ʒu
					float block_fWindth = pScene->GetfWindth();		//	�u���b�N�̕�
					float block_fHeight = pScene->GetfHeight();		//	�u���b�N�̍���

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight )
					{//	YX���͈͓�
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	�u���b�N�㔻��
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight )
						{//	�u���b�N������
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth )
						{//�u���b�N�E����
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fWindth >= block_pos.x)
						{//�u���b�N������
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);


	if (pos.y >= 760)
	{
		Hit(2);
	}
}
//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemyType000::Draw(void)
{
	CEnemy::Draw();
}
//============================================================================================================================================================
//	�G�l�~�[�^�C�v001
//============================================================================================================================================================
//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemyType001::CEnemyType001()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemyType001::~CEnemyType001()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemyType001::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	�I������
//==============================================================================
void CEnemyType001::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	�X�V����
//==============================================================================
void CEnemyType001::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	�ʒu
	D3DXVECTOR3 move = GetMoveing();						//	����
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	�v���C���[�̓����̎擾
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	�v���C���[�̓����̎擾
	float fWindth = GetfWindth();							//	��
	float fHeight = GetfHeight();							//	����
	bool bLand = false;										//	�u���b�N�ɏ���Ă��邩�ǂ���

	fWindth = ENEMY_POLIGON_X_001;
	fHeight = ENEMY_POLIGON_Y_001;
	m_bAttackMove = false;									//	�v���C���[�ւ̍U���͈͂���Ȃ�
	m_bBulletAttck = false;									//	�e�̌����Ă��Ȃ�
	m_posOld = pos;

	float fDiffAngle;				//����
	float fDestAngle;				//�ړI�̊p�x
	float fMoveAngle;				//���݂̊p�x
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 300 <= playerpos.x && pos.x + 300 >= playerpos.x)
	{
		m_bAttackMove = true;					//	�v���C���[�ւ̍U���͈�
		if (rand() % 120 == 0 )
		{
			m_bBulletAttck = true;									//	�e�̌����Ă���
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f+move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}

	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.75f;
		if ((m_nAICounter + 1) % 90 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.75f;
		if ((m_nAICounter + 1) % 90 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	�d��
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	�u���b�N�̈ʒu
					float block_fWindth = pScene->GetfWindth();		//	�u���b�N�̕�
					float block_fHeight = pScene->GetfHeight();		//	�u���b�N�̍���

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight)
					{//	YX���͈͓�
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	�u���b�N�㔻��
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight)
						{//	�u���b�N������
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//�u���b�N�E����
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fHeight >= block_pos.x)
						{//�u���b�N������
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemyType001::Draw(void)
{
	CEnemy::Draw();
}

//============================================================================================================================================================
//	�G�l�~�[�^�C�v002
//============================================================================================================================================================
//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemyType002::CEnemyType002()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemyType002::~CEnemyType002()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemyType002::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	�I������
//==============================================================================
void CEnemyType002::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	�X�V����
//==============================================================================
void CEnemyType002::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	�ʒu
	D3DXVECTOR3 move = GetMoveing();						//	����
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	�v���C���[�̓����̎擾
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	�v���C���[�̓����̎擾
	float fWindth = GetfWindth();							//	��
	float fHeight = GetfHeight();							//	����
	bool bLand = false;										//	�u���b�N�ɏ���Ă��邩�ǂ���

	fWindth = ENEMY_POLIGON_X_001;
	fHeight = ENEMY_POLIGON_Y_001;
	m_bAttackMove = false;									//	�v���C���[�ւ̍U���͈͂���Ȃ�
	m_bBulletAttck = false;									//	�e�̌����Ă��Ȃ�
	m_posOld = pos;

	float fDiffAngle;				//����
	float fDestAngle;				//�ړI�̊p�x
	float fMoveAngle;				//���݂̊p�x
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 300 <= playerpos.x && pos.x + 300 >= playerpos.x)
	{
		m_bAttackMove = true;					//	�v���C���[�ւ̍U���͈�
		if (rand() % 70 == 0)
		{
			m_bBulletAttck = true;									//	�e�̌����Ă���
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, -2.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	�d��
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	�u���b�N�̈ʒu
					float block_fWindth = pScene->GetfWindth();		//	�u���b�N�̕�
					float block_fHeight = pScene->GetfHeight();		//	�u���b�N�̍���

					if (pos.x + (fWindth / 2) >= block_pos.x  &&																		//	�v���C���[���E����߂荞��ł�Ƃ�
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&														//	�v���C���[��������߂荞��ł�Ƃ�
						pos.y >= block_pos.y &&																									//	�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
						pos.y - fHeight <= block_pos.y + block_fHeight)																	//	�v���C���[���������ɂ߂荞��ł�Ƃ�
					{//	YX���͈͓�
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)																//	�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
						{//	�u���b�N�㔻��
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;																						//	�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&											//	�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
							pos.y - fHeight <= block_pos.y + block_fHeight)														//	���݂̈ʒu���߂荞��ł�Ƃ�
						{//	�u���b�N������
							pos.y = block_pos.y + block_fHeight + fHeight;														//	�v���C���[���u���b�N���S+�u���b�N�̍���+�v���C���[�̍����̈ʒu�ɏo��������
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&											//	�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//�u���b�N�E����
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&																//	�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
							pos.x + fHeight >= block_pos.x)
						{//�u���b�N������
							pos.x = m_posOld.x;																							//	�̂̈ʒu�ɏo��������
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemyType002::Draw(void)
{
	CEnemy::Draw();
}
//============================================================================================================================================================
//	�G�l�~�[�^�C�v003
//============================================================================================================================================================
//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CEnemyType003::CEnemyType003()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CEnemyType003::~CEnemyType003()
{

}

//==============================================================================
//	����������
//==============================================================================
HRESULT CEnemyType003::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	�I������
//==============================================================================
void CEnemyType003::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	�X�V����
//==============================================================================
void CEnemyType003::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	�ʒu
	D3DXVECTOR3 move = GetMoveing();						//	����
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	�v���C���[�̓����̎擾
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	�v���C���[�̓����̎擾
	float fWindth = GetfWindth();							//	��
	float fHeight = GetfHeight();							//	����
	bool bLand = false;										//	�u���b�N�ɏ���Ă��邩�ǂ���

	fWindth = ENEMY_POLIGON_X_001+15;
	fHeight = ENEMY_POLIGON_Y_001+15;
	m_bAttackMove = false;									//	�v���C���[�ւ̍U���͈͂���Ȃ�
	m_bBulletAttck = false;									//	�e�̌����Ă��Ȃ�
	m_posOld = pos;

	float fDiffAngle;				//����
	float fDestAngle;				//�ړI�̊p�x
	float fMoveAngle;				//���݂̊p�x
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 280 <= playerpos.x && pos.x + 280 >= playerpos.x)
	{
		m_bAttackMove = true;					//	�v���C���[�ւ̍U���͈�
		if (rand() % 100 == 0)
		{
			m_bBulletAttck = true;									//	�e�̌����Ă���
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, cosf(fDiffAngle)*4.05f + move.y, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, -2.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	�d��
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	�I�u�W�F�N�g�̑�����
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	�I�u�W�F�N�g�̎擾
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	�u���b�N�̈ʒu
					float block_fWindth = pScene->GetfWindth();		//	�u���b�N�̕�
					float block_fHeight = pScene->GetfHeight();		//	�u���b�N�̍���

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight)
					{//	YX���͈͓�
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	�u���b�N�㔻��
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight)
						{//	�u���b�N������
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//�u���b�N�E����
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fHeight >= block_pos.x)
						{//�u���b�N������
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	�`�揈��
//==============================================================================
void CEnemyType003::Draw(void)
{
	CEnemy::Draw();
}