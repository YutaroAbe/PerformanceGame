//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include  "input.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "effect.h"
#include "explosion.h"
#include "block.h"
#include "item.h"
#include "fade.h"
#define PLAYERTEX_X (6.0f)
#define PLAYERTEX_Y (6.0f)

//==============================================================================
//	�ÓI�����o�ϐ��̏�����
//==============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_Texture = NULL;
bool CPlayer::bDisp = true;
int CPlayer::m_nLife = NULL;
D3DXVECTOR3 CPlayer::m_GetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_GetMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CPlayer::m_nTexChange = NULL;										//	�e�N�X�`���̕ω��p�̏�����
D3DXVECTOR3  CPlayer::m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3  CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CPlayer::m_nBulletType = NULL;										//�@�e�̎�ނ̏�����n
float CPlayer::m_fWindth = NULL;
float CPlayer::m_fHeight = NULL;
bool CPlayer::m_bLandDropBlock = false;
CPlayer::PLAYERSTATE CPlayer::m_PlayerState = PLAYERSTATE_NOMAL;
int CPlayer::m_nCounterState = NULL;

//==============================================================================
//	�R���X�g���N�^
//==============================================================================
CPlayer::CPlayer() :CScene2D(3)
{
	m_nCounterAnim = NULL;												//	�e�N�X�`���A�j���[�V�����̏�����
	m_nPatternAnim = NULL;												//	�A�j���[�V�����p�^�[���̏�����
	m_nBulletRot = NULL;
	m_nMotionState = NULL;
	m_nMotionStateID = NULL;											//	���݂̃��[�V�����̕ۑ��p�ϐ�
	m_bBullet = false;
	m_bLandBlock = NULL;
}

//==============================================================================
//	�f�X�g���N�^
//==============================================================================
CPlayer::~CPlayer()
{
}

//==============================================================================
//	����������
//==============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init();

	//	�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_PLAYER);
	m_PlayerState = PLAYERSTATE_NOMAL;
	m_nBulletType = 0;
	m_nTexChange = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nBulletRot = 0;
	m_fWindth = 0;									//	��
	m_fHeight = 0;									//	����
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 15;
	m_nMotionStateID = 0;
	bDisp = true;
	m_bLandDropBlock = false;
	m_nMotionState = 0;
	m_bBullet = false;
	m_bLandBlock = 0;

	//	�傫���̐ݒ�
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-m_fWindth, -m_fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(m_fWindth,-m_fHeight, 0.0f) ;
	pPos[2] = D3DXVECTOR3(-m_fWindth, 0.0f, 0.0f) ;
	pPos[3] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f) ;
	CScene2D::SetVtxPosition(&pPos[0], pos);

	//�e�N�X�`���̐ݒ�
	D3DXVECTOR2 tex[4];
	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f/ PLAYERTEX_X), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
	tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
	CScene2D::SetTexture(&tex[0]);

	//	�e�L�X�g�̓ǂݍ���
	LoadPlayer();

	return S_OK;
}

//==============================================================================
//	�I������
//==============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	�X�V����
//==============================================================================
void CPlayer::Update(void)
{
	//�L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();
	D3DXVECTOR2 tex[4];

	switch (m_PlayerState)
	{
	case PLAYERSTATE_NOMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		m_bBullet = false;
		CScene2D::ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			m_PlayerState = PLAYERSTATE_NOMAL;
			CScene2D::ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	case PLAYERSTATE_DEATH:
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			if (pFade->m_fade == pFade->FADE_NONE)
			{//	�t�F�C�h���I�������
				pFade->SetFade(CManager::MODE_RESULT);
				Uninit();
			}

		}
		break;
	}
	if (bDisp == true)
	{
		m_nMotionState = 0;
		D3DXVECTOR3 pos;
		pos = CScene2D::GetPosition();
		m_bLandDropBlock = false;
		m_bLandBlock = false;

		if (pos.x = 600)
		{
			pos.x = 600;
		}
		m_posold = pos;

		if (m_bBullet == false)
		{//	�U�����[�V����������Ȃ�
				//�C�ӂ̃L�[(A�L�[)�������ꂽ���ǂ��� : ���ړ�
			if (pInputKeyboard->GetPress(DIK_A) == true || pInputGamepad->GetPovTpress(CROSSKEY_LEFT) == true)
			{
				m_move.x += sinf(-D3DX_PI * 0.5) * 2.25f;
			}
			else if (pInputKeyboard->GetPress(DIK_D) == true || pInputGamepad->GetPovTpress(CROSSKEY_RIGHT) == true)
			{//�C�ӂ̃L�[(D�L�[)�������ꂽ���ǂ����@�F�E�ړ�
				m_move.x += sinf(D3DX_PI * 0.5) * 2.25f;
			}
		}

		m_move.y += 0.95f;		//�d�͐ݒ�

		if (m_move.y >= 5)
		{
			m_move.y = 5;
		}
		pos.x += m_move.x;
		pos.y += m_move.y;
		m_move.x += (0.0f - m_move.x)*0.425f;
		m_GetMove = m_move;
		m_GetPos = pos;

		for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
		{
			//�u���b�N�̓����蔻��
			for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
			{//	�I�u�W�F�N�g�̑�����
				CScene2D *pScene;
				pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);
				if (pScene != NULL)
				{
					CScene::OBJTYPE objtype = pScene->GetObjType();
					//-----------------------------------------------------------------------------------------
					//�G�l�~�[�̓����蔻��
					//-----------------------------------------------------------------------------------------
					if (objtype == CScene::OBJECT_ENEMY)
					{
						D3DXVECTOR3 enemy_pos = pScene->GetPosition();		//	�G�̈ʒu
						float enemy_fWindth = pScene->GetfWindth();			//	�G�̕�
						float  enemy_fHeight = pScene->GetfHeight();			//	�G�̍���
						int nEnemy_Type = pScene->GetType();

						if (pos.x + (m_fWindth / 2) >= enemy_pos.x - (enemy_fWindth / 2) &&
							pos.x - (m_fWindth / 2) <= enemy_pos.x + (enemy_fWindth / 2) &&
							pos.y >= enemy_pos.y - enemy_fHeight &&
							pos.y - m_fHeight <= enemy_pos.y)
						{//	YX���͈͓�
							if (m_posold.y <= enemy_pos.y - enemy_fHeight && pos.y >= enemy_pos.y - enemy_fHeight)
							{//	�G�̏㔻��
								pos.y = enemy_pos.y - enemy_fHeight;
								m_move.y -= 15.0f;

								if (nEnemy_Type == 0)
								{//	���[0]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	���[1]�ɓ���������
									HitDamage(2);
								}
								else if (nEnemy_Type == 2)
								{//	���[2]�ɓ���������
									HitDamage(1);
								}
							}
							else if (m_posold.y - m_fHeight >= enemy_pos.y  &&
								pos.y - m_fHeight <= enemy_pos.y)
							{//	�G�̉�����
								pos.y = enemy_pos.y;
								m_move.y = 0.0f;
								if (nEnemy_Type == 0)
								{//	���[0]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	���[1]�ɓ���������
									HitDamage(2);
								}
								else if (nEnemy_Type == 2)
								{//	���[2]�ɓ���������
									HitDamage(1);
								}
							}
							else if (m_posold.x + (m_fWindth / 2) >= enemy_pos.x + (enemy_fWindth / 2) &&
								pos.x - (m_fWindth / 2) <= enemy_pos.x + (enemy_fWindth / 2))
							{//�G�̉E����
								pos.x = m_posold.x;
								m_move.x = 10.0f;
								m_move.y = -12.0f;
								if (nEnemy_Type == 0)
								{//	���[0]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	���[1]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 2)
								{//	���[2]�ɓ���������
									HitDamage(1);
								}
							}
							else if (m_posold.x - (m_fWindth / 2) <= enemy_pos.x - (enemy_fWindth / 2) &&
								pos.x + (m_fWindth / 2) >= enemy_pos.x - (enemy_fWindth / 2))
							{//�G�̍�����
								pos.x = m_posold.x;
								m_move.x = -10.0f;
								m_move.y = -12.0f;
								if (nEnemy_Type == 0)
								{//	���[0]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 1)
								{//	���[1]�ɓ���������
									HitDamage(1);
								}
								else if (nEnemy_Type == 2)
								{//	���[2]�ɓ���������
									HitDamage(1);
								}

							}
						}
					}
					//-----------------------------------------------------------------------------------------
					//�u���b�N�̓����蔻��
					//-----------------------------------------------------------------------------------------
					if (objtype == CScene::OBJECT_BLOCK)
					{
						D3DXVECTOR3 block_pos = pScene->GetPosition();		//	�u���b�N�̈ʒu
						D3DXVECTOR3 block_move = pScene->GetMoveing();		//	�u���b�N�̈ʒu
						float block_fWindth = pScene->GetfWindth();			//	�u���b�N�̕�
						float block_fHeight = pScene->GetfHeight();			//	�u���b�N�̍���
						int nBlock_Type = pScene->GetType();
						if (pos.x + (m_fWindth / 2) >= block_pos.x  &&
										//	�v���C���[���E����߂荞��ł�Ƃ�
							pos.x - (m_fWindth / 2) <= block_pos.x + block_fWindth &&														//	�v���C���[��������߂荞��ł�Ƃ�
							pos.y >= block_pos.y &&																							//	�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
							pos.y - m_fHeight <= block_pos.y + block_fHeight)																//	�v���C���[���������ɂ߂荞��ł�Ƃ�
						{//	YX���͈͓�
							if (m_posold.y <= block_pos.y && pos.y >= block_pos.y)															//	�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
							{//	�u���b�N�㔻��
								m_bLandBlock = true;
								pos.y = block_pos.y;
								if (nBlock_Type == CBlock::TYPE_BREAKBLOCK)
								{//	����u���b�N
									pScene->Uninit();
									CExplosion::Create(D3DXVECTOR3(block_pos.x + block_fWindth / 2, block_pos.y, block_pos.z));
								}
								else if (nBlock_Type == CBlock::TYPE_FALL)
								{//	������u���b�N
									m_bLandDropBlock = true;
								}
								else if (nBlock_Type == CBlock::TYPE_DAMAGE)
								{//	�_���[�W�󂯂�u���b�N
									HitDamage(1);
									m_move.y -= 17.0f;
								}
							}
							else if (m_posold.y - m_fHeight >= block_pos.y + block_fHeight  &&											//	�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
								pos.y - m_fHeight <= block_pos.y + block_fHeight)														//	���݂̈ʒu���߂荞��ł�Ƃ�
							{//	�u���b�N������
								pos.y = block_pos.y + block_fHeight + m_fHeight;														//	�v���C���[���u���b�N���S+�u���b�N�̍���+�v���C���[�̍����̈ʒu�ɏo��������
								m_move.y = 0.0f;
								if (nBlock_Type == CBlock::TYPE_ITEMBLOCK)
								{//	�A�C�e���o���p�u���b�N
									CItem::Create(D3DXVECTOR3(block_pos.x + block_fWindth / 2, block_pos.y, block_pos.z), 1);
									pScene->Uninit();
								}
							}
							else if (m_posold.x + m_fWindth >= block_pos.x + block_fWindth &&											//	�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
								pos.x - m_fWindth <= block_pos.x + block_fWindth)
							{//�u���b�N�E����
								if (nBlock_Type == CBlock::TYPE_STAGE)
								{//	�K�i�p�u���b�N
									pos.x = block_pos.x += block_fWindth;
									pos.y = block_pos.y;
								}
								else
								{
									pos.x = m_posold.x;
									m_move.x = 4.0f;
								}
							}
							else if (m_posold.x - m_fWindth <= block_pos.x &&																//	�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
								pos.x + m_fWindth >= block_pos.x)
							{//�u���b�N������
								if (nBlock_Type == CBlock::TYPE_STAGE)
								{//	�K�i�p�u���b�N
									pos = block_pos;
								}
								else
								{
									pos.x = m_posold.x;																							//	�̂̈ʒu�ɏo��������
									m_move.x = -4.0f;
								}
							}
						}
					}
				}
			}
		}

		//	���_���̐ݒ�
		D3DXVECTOR3 pPos[4];
		pPos[0] = D3DXVECTOR3(-m_fWindth, -m_fHeight, 0.0f);
		pPos[1] = D3DXVECTOR3(m_fWindth, -m_fHeight, 0.0f);
		pPos[2] = D3DXVECTOR3(-m_fWindth, 0.0f, 0.0f);
		pPos[3] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f);
		CScene2D::SetVtxPosition(&pPos[0], pos);

		if (m_move.x <= -2.0f)
		{// �v���C���[���������ɐi�񂾂�
			m_nMotionState = 2;
			m_nMotionStateID = m_nMotionState;
		}
		else if (m_move.x >= 2.0f)
		{// �v���C���[���E�����ɐi�񂾂�
			m_nMotionState = 1;
			m_nMotionStateID = m_nMotionState;
		}

		//if (m_bBullet == false)
		{//	�U�����[�V����������Ȃ�
			if ((pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_B) == true) && m_nMotionStateID == 2)
			{//	�U�����[�V����
				m_bBullet = true;
				m_nPatternAnim = 0;
				m_nCounterAnim = 0;
				m_nMotionState = 4;
			}
			else if ((pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_B) == true) && m_nMotionStateID == 1)
			{//	�U�����[�V����
				m_bBullet = true;
				m_nPatternAnim = 0;
				m_nCounterAnim = 0;
				m_nMotionState = 3;
			}
		}
		switch (m_nMotionState)
		{//	���[�V�����d�l�i���o�[
		case 0://	�����Ȃ�
			break;
		case 1://	���s[������]
			m_nPatternAnim++;
			m_nTexChange = 0;
			break;
		case 2://	���s[�E����]
			m_nPatternAnim++;
			m_nTexChange = 1;
			break;
		case 3://	�e������[������]
			m_nTexChange = 2;
			break;
		case 4://	�e������[�E����]
			m_nTexChange = 3;
			break;
		}

		if (m_bLandBlock == true)
		{//�u���b�N�ɏ���Ă���
			switch (m_nTexChange)
			{
			case 0:	//�������ɕ����Ă���
				m_nCounterAnim++;
				if ((m_nCounterAnim % 7) == 0)
				{
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), 0.0f);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), 0.0f);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					CScene2D::SetTexture(&tex[0]);
				}
				break;
			case 1:	//�E�����ɕ����Ă���
				m_nCounterAnim++;
				if ((m_nCounterAnim % 7) == 0)
				{
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					CScene2D::SetTexture(&tex[0]);
				}
				break;
			case 2://�e������[������]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 3)
				{
					m_nBulletRot = 0;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 4 * 3.5f)
				{
					m_nTexChange = 0;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 4) == 0)
				{
					m_nPatternAnim++;
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			case 3://�e������[�E����]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 3)
				{
					m_nBulletRot = 1;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 2, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 4 * 3.5f)
				{
					m_nTexChange = 1;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 4) == 0)
				{
					m_nPatternAnim++;

					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 3);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			}
		}
		if (m_bLandBlock == false)
		{//�u���b�N�ɏ���ĂȂ�������
			switch (m_nTexChange)
			{
			case 0:	//�������ɕ����Ă���
				tex[0] = D3DXVECTOR2(0.0f, 0.0f);
				tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X), 0.0f);
				tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
				tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
				CScene2D::SetTexture(&tex[0]);
				break;
			case 1:	//�E�����ɕ����Ă���
				tex[0] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y));
				tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y));
				tex[2] = D3DXVECTOR2(0.0f, (1.0f / PLAYERTEX_Y) * 2);
				tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 2);
				CScene2D::SetTexture(&tex[0]);
				break;
			case 2://�󒆂Œe������[������]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 2.5)
				{
					m_nBulletRot = 0;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(-6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 6 * 3.0f)
				{
					m_nTexChange = 0;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 6) == 0)
				{
					m_nPatternAnim++;
					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 4);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			case 3://�󒆂Œe������[�E����]
				m_nCounterAnim++;
				if (m_nCounterAnim == 4 * 2.5)
				{
					m_nBulletRot = 1;
					switch (m_nBulletRot)
					{
					case 0:
						CBullet::Create(pos + D3DXVECTOR3(15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					case 1:
						CBullet::Create(pos + D3DXVECTOR3(-15.0f, -m_fHeight / 3.0f, 0.0f), D3DXVECTOR3(-6.0f, 4.0f, 0.0f), m_nBulletType, CBullet::BULLET_PLAYER);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_BULLET);
						break;
					}
				}
				if (m_nCounterAnim >= 6 * 3.0f)
				{
					m_nTexChange = 1;
					m_nPatternAnim = 0;
					m_nCounterAnim = 0;
					m_bBullet = false;
				}
				else if ((m_nCounterAnim % 6) == 0)
				{
					m_nPatternAnim++;

					tex[0] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[1] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 5);
					tex[2] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 6);
					tex[3] = D3DXVECTOR2((1.0f / PLAYERTEX_X) * (m_nPatternAnim % (int)PLAYERTEX_X) + (1.0f / PLAYERTEX_X), (1.0f / PLAYERTEX_Y) * 6);
					CScene2D::SetTexture(&tex[0]);

				}
				break;
			}
		}
		if (pos.y >= 760.0f)
		{
			HitDamage(15);

		}
		if (m_bLandBlock == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true || pInputGamepad->GetPovTpress(CROSSKEY_UP) == true)
			{
				m_move.y += cosf(D3DX_PI) * 20.0f;
			}
		}
	}
}

//==============================================================================
//	�`�揈��
//==============================================================================
void CPlayer::Draw(void)
{
	if (bDisp == true)
	{
		CScene2D::Draw();
	}
}

//==============================================================================
//�v���C���[�̐�������
//==============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = {};

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//	�|���S���̏���������
			pPlayer->Init(pos);
			//	�e�̃e�N�X�`���̊��蓖��
			pPlayer->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pPlayer;
}

//==============================================================================
//	�e�N�X�`����ǂݍ���
//==============================================================================
HRESULT CPlayer::Laod(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//	�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_PLAYER, &m_Texture);

	return S_OK;
}

//==============================================================================
//	�e�N�X�`���̊J��
//==============================================================================
void CPlayer::UnLoad(void)
{
	//	�e�N�X�`���̔j��
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

//==============================================================================
//	�v���C���[�̃_���[�W�ݒ�
//==============================================================================
void  CPlayer::HitDamage(int nDamage)
{
	m_nLife -= nDamage;
	CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);
	if (m_nLife <= 0)
	{//�̗͂�0�ɂȂ�����
		bDisp = false;
		m_PlayerState = PLAYERSTATE_DEATH;
		m_nCounterState = 20;
	}
	else
	{
		m_PlayerState = PLAYERSTATE_DAMAGE;
		m_nCounterState = 15;
	}
}

//==============================================================================
//	�v���C���[�̗͉̑�
//==============================================================================
void CPlayer::UpLife(int nLife)
{
	m_nLife += nLife;

	if (m_nLife >= 15)
	{//	�v���C���[�̃��C�t��������z�����ꍇ�Œ�l�ɂ���
		m_nLife = 15;
	}
}
//==============================================================================
//�v���C���[�̒e�̕ω�
//==============================================================================
void CPlayer::BulletChange(int nBulletType)
{
	m_nBulletType = nBulletType;
}
//=============================================================================
//	�v���C���[�̗̑͂̎擾
//==============================================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}
//==============================================================================
//	�v���C���[�̃|�W�V�����̎擾
//==============================================================================
D3DXVECTOR3 CPlayer::GetPosition(void)
{
	return m_GetPos;
}
//==============================================================================
//	�v���C���[�̓����̎擾
//==============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_GetMove;
}
//==============================================================================
//	�v���C���[�̃e�N�X�`���p�^�[���̎擾
//==============================================================================
int CPlayer::GetTexNumber(void)
{
	return m_nTexChange;
}
//==============================================================================
//
//==============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLandDropBlock;
}

//==============================================================================
//	�v���C���[�̃e�L�X�g�ǂݍ���
//==============================================================================
void CPlayer::LoadPlayer(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/player.txt", "r");

	if (pFile != NULL)
	{//	�t�@�C�����J�����ꍇ

		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "PLAYER_SET") == 0)
		{
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "PLAYER_LIFE") == 0)
				{//	�v���C���[��HP�̐ݒ�
					fscanf(pFile, "%s%d\n", &read[0], &m_nLife);
				}
				else if (strcmp(&read[0], "PLAYER_WINDTH") == 0)
				{//	�v���C���[�̕��̐ݒ�
					fscanf(pFile, "%s%f\n", &read[0], &m_fWindth);
				}
				else if (strcmp(&read[0], "PLAYER_HEIGTH") == 0)
				{//	�v���C���[�̍����̐ݒ�
					fscanf(pFile, "%s%f\n", &read[0], &m_fHeight);
				}
			} while (strcmp(&read[0], "PLAYER_END") != 0);

		}
		fclose(pFile);												//*�N���[�Y*
	}
	else
	{
		MessageBox(0, "�v���C���[�̃e�L�X�g�ɖ�肪����܂�", "�x��", MB_OK);
	}

}