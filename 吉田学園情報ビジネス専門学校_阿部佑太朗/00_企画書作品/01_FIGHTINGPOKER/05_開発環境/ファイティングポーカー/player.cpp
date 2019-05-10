//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �v���C���[���� [player.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "game.h"
#include "player.h"
#include "input.h"
#include "light.h"
#include "gamepad.h"
#include "camera.h"
#include "sound.h"
#include "shadow.h"
#include "meshBattleField.h"
#include "battle.h"
#include "meshSphere.h"
#include "cardModel.h"
#include "fade.h"
#include "hpGage.h"
#include "spGage.h"
#include "effect.h"
#include "particle.h"
#include "textureanim.h"
#include "gamefade.h"
#include "message.h"
#include "timer.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define PLAYER_MOVE_SPEED			(0.5f)		// �v���C���[�̈ړ��X�s�[�h�����l
#define PLAYER_MOVE_INERTIA			(0.1f)		// �v���C���[�̈ړ��̊���
#define PLAYER_SPIN_INERTIA			(0.5f)		// �v���C���[�̉�]�̊���
#define PLAYER_GRAVITY				(0.5f)		// �v���C���[�ɂ�����d��
#define PLAYER_JUMP_MOVE			(15.0f)		// �v���C���[�̃W�����v�͂̏����l
#define PLAYER_COLISION_RADIUS		(10.0f)		// �v���C���[�̓����蔻��̔��a�̏����l
#define PLAYER_COLISION_HEIGHT		(100.0f)	// �v���C���[�̓����蔻��̍����̏����l
#define PLAYER_MOTION_BLEND_FRAME	(3)			// ���[�V�����u�����h�̃t���[����
#define PLAYER_FALL_DEATH_LINE		(-100)		// �v���C���[�̎��S���鍂��

#define PLAYER_MOTION_LOADTXT_NAME	"data//TEXT//motion_player.txt"		// �v���C���[�̃��[�V�����e�L�X�g�t�@�C����
#define SAVE_RESULT_TEXT			"data/TEXT/result.txt"

// �X�e�[�^�X����
#define DAMAGE_TIME					(30)		// �_���[�W�̎���
#define DOWN_TIME					(50)		// �_�E���̎���
#define DEATH_TIME					(60)		// ���S���̎���
#define APPEAR_TIME					(120)		// �o�����̖��G����
#define INVINCIBLE_TIME				(60)			// ���G����

#define PLAYER_SHADOW_RADIUS		(15.0f)		// �v���C���[�̉e�̔��a

// �_���[�W�v�Z�p
#define PLAYER_GUARD_DAMAGE			(0.2)		// �v���C���[�̃K�[�h���̃_���[�W������
#define PLAYER_ADVANTAGEOUS_DAMEGE	(1.2f)		// �L���������̃_���[�W�v�Z��
#define PLAYER_UNFAVORABLE_DAMEGE	(0.7f)		// �s���������̃_���[�W�v�Z��

#define PLAYER_SKILL_ADD_ATTACK		(5)			// �U���������Ƃ��̃X�L���|�C���g�̑�����
#define PLAYER_SKILL_ADD_DEFENSE	(10)		// �U�����󂯂��Ƃ��̃X�L���|�C���g�̑�����

#define PLAYER_1P_HP_SKILL_TXT_NAME	"data//TEXT//1PlayerHpSkill.txt"		// 1P��HP�ۑ��e�L�X�g�t�@�C����
#define PLAYER_2P_HP_SKILL_TXT_NAME	"data//TEXT//2PlayerHpSkill.txt"		// 2P��HP�ۑ��e�L�X�g�t�@�C����

// �X�L�����
// �X�L�����
#define BRAVE_SKILL_DAMAGE_RANK1	(10)				// �E�҃X�L���_���[�W�ʁi1�i�K��
#define BRAVE_SKILL_DAMAGE_RANK2	(15)				// �E�҃X�L���_���[�W�ʁi2�i�K��
#define BRAVE_SKILL_DAMAGE_RANK3	(30)				// �E�҃X�L���_���[�W�ʁi3�i�K��
#define BRAVE_SKILL_DAMAGE_WIDTH	(RAIZIN_RADIUS_X_R*2.0f)	// �E�҃X�L���͈́E��
#define BRAVE_SKILL_DAMAGE_HEIGHT	(RAIZIN_RADIUS_Y_R*2.0f)	// �E�҃X�L���͈́E����
#define BRAVE_SKILL_POS_Y			(30.0f)				// �E�҃X�L��Y�ʒu

#define DEVIL_SKILL_DAMAGE_RANK1	(10)				// �����X�L���_���[�W�ʁi1�i�K��
#define DEVIL_SKILL_DAMAGE_RANK2	(15)				// �����X�L���_���[�W�ʁi2�i�K��
#define DEVIL_SKILL_DAMAGE_RANK3	(30)				// �����X�L���_���[�W�ʁi3�i�K��
#define DEVIL_SKILL_DAMAGE_WIDTH	(DARK_RADIUS_X*2.0f)		// �����X�L���͈́E��
#define DEVIL_SKILL_DAMAGE_HEIGHT	(DARK_RADIUS_Y*2.0f)		// �����X�L���͈́E����
#define DEVIL_SKILL_POS_Y			(50.0f)				// �����X�L��Y�ʒu

#define KING_SKILL_DAMAGE_RANK1		(10)				// ���l�X�L���_���[�W�ʁi1�i�K��
#define KING_SKILL_DAMAGE_RANK2		(15)				// ���l�X�L���_���[�W�ʁi2�i�K��
#define KING_SKILL_DAMAGE_RANK3		(30)				// ���l�X�L���_���[�W�ʁi3�i�K��
#define KING_SKILL_DAMAGE_WIDTH		(GRAVITY_RADIUS_X*2.0f)	// ���l�X�L���͈́E��
#define KING_SKILL_DAMAGE_HEIGHT	(GRAVITY_RADIUS_Y*2.0f)	// ���l�X�L���͈́E����
#define KING_SKILL_POS_Y			(10.0f)				// ���l�X�L��Y�ʒu

#define PEOPLE_SKILL_DAMAGE_RANK1	(10)				// �����X�L���_���[�W�ʁi1�i�K��
#define PEOPLE_SKILL_DAMAGE_RANK2	(15)				// �����X�L���_���[�W�ʁi2�i�K��
#define PEOPLE_SKILL_DAMAGE_RANK3	(30)				// �����X�L���_���[�W�ʁi3�i�K��
#define PEOPLE_SKILL_DAMAGE_WIDTH	(FISSURES_RADIUS_X*2.0f)	// �����X�L���͈́E��
#define PEOPLE_SKILL_DAMAGE_HEIGHT	(FISSURES_RADIUS_Y*2.0f)	// �����X�L���͈́E����
#define PEOPLE_SKILL_POS_Y			(30.0f)				// �����X�L��Y�ʒu

#define GOD_SKILL_DAMAGE_RANK1		(15)				// ����(�_)�X�L���_���[�W�ʁi1�i�K��
#define GOD_SKILL_DAMAGE_RANK2		(20)				// ����(�_)�X�L���_���[�W�ʁi2�i�K��
#define GOD_SKILL_DAMAGE_RANK3		(35)				// ����(�_)�X�L���_���[�W�ʁi3�i�K��
#define GOD_SKILL_DAMAGE_WIDTH		(GOD_RADIUS_X*2.0f)		// ����(�_)�X�L���͈́E��
#define GOD_SKILL_DAMAGE_HEIGHT		(GOD_RADIUS_X*2.0f)		// ����(�_)�X�L���͈́E����
#define GOD_SKILL_POS_Y				(40.0f)				// ����(�_)�X�L��Y�ʒu

#define PLAYER_MAX_SKILL_RANK		(3)			// �X�L���̒i�K�̎��
#define PLAYER_SKILL_RANK_1			(30)		// �X�L���̒i�K1�̕K�v��
#define PLAYER_SKILL_RANK_2			(65)		// �X�L���̒i�K2�̕K�v��
#define PLAYER_SKILL_RANK_3			(100)		// �X�L���̒i�K3�̕K�v��

#define PLAYER_SKILL_DISTANCE		(30.0f)	// �X�L����e���̂Ԃ��Ƃї�
#define PLAYER_SKILL_START_FRAME	(8)			// �X�L���̔�����J�n����t���[����


//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{ // �v���C���[�̔z�u���
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	PLAYER_TYPE type;
	bool bUse;
}PlayerSetInfo;

typedef struct
{
	char *pFilename;	// �t�@�C����
} PlayerTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Player g_aPlayer[MAX_PLAYER];						// �v���C���[�̏��
													// �ǂݍ��ރv���C���[���̐ݒ�
													//PlayerModelData g_apPlayer[MAX_PLAYER_PARTS] = {};	// ���f���ւ̃|�C���^
PlayerTypeData g_aPlayerType[PLAYER_TYPE_MAX];
PlayerSetInfo g_aPlayerSetInfo[MAX_PLAYER];			// �v���C���[�̔z�u���
bool g_aAttackCollisionDisp[MAX_PLAYER];
int g_nMoveRimit;

// �U�������N�̃_���[�W�{�[�i�X��
int g_nAttackRankDamage[PLAYER_ATTACK_RANK_MAX] =
{
	0,		// ��㏸���
	1,		// �U��1�i�K�㏸��
	2,		// �U��2�i�K�㏸��
	3		// �U��3�i�K�㏸��
};

// �h�䃉���N�̃_���[�W�����{�[�i�X��
int g_nDefenseRankDamage[PLAYER_DEFENSE_RANK_MAX] =
{
	0,		// ��㏸���
	1,		// �h��1�i�K�㏸��
	3,		// �h��2�i�K�㏸��
	5		// �h��3�i�K�㏸��
};

// �񕜃����N�̃_���[�W�����{�[�i�X��
int g_nRecoveryRank[PLAYER_RECOVERY_RANK_MAX] =
{
	0,		// ��㏸���
	5,		// ��1�i�K�㏸��
	10,		// ��2�i�K�㏸��
	15,		// ��3�i�K�㏸��
	20,		// ��4�i�K�㏸��
	25,		// ��5�i�K�㏸��
};


int g_nPlayerSkillDamage[PLAYER_MAX_SKILL_RANK][PLAYER_TYPE_MAX];	// �X�L���_���[�W��
float g_nPlayerSkillWidth[PLAYER_TYPE_MAX];							// �X�L�����蕝
float g_nPlayerSkillHeight[PLAYER_TYPE_MAX];						// �X�L�����荂��
float g_nPlayerSkillPosY[PLAYER_TYPE_MAX];							// �X�L������Y�ʒu


bool g_bTestPlayerDisp;	// �f�o�b�O�p

LPDIRECT3DTEXTURE9		g_pTexturePlayerGod = NULL;	// �S�b�h�e�N�X�`���ւ̃|�C���^
// 2P�p�e�N�X�`��
LPDIRECT3DTEXTURE9		g_pTexturePlayer2P[PLAYER_TYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
// �ǂݍ��ރe�N�X�`�����̐ݒ�
PlayerTexInfo g_apTexturePlayer2PInfo[PLAYER_TYPE_MAX] =
{
	{ "data//MODEL//brave//TEXTURE//yuusya2P.jpg" },		// �E��2P
	{ "data//MODEL//devil//TEXTURE//maou2P.jpg" },			// ����2P
	{ "data//MODEL//king//TEXTURE//ousama2P.jpg" },			// ���l2P
	{ "data//MODEL//Commoner//TEXTURE//heimin2P.jpg" },		// ����2P
	{ "data//MODEL//Commoner//TEXTURE//god2P.jpg" },		// �����_2P
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPlayer(void)
{
	// �f�o�b�O�p
	g_bTestPlayerDisp = false;

	// �X�L�����
	// �E��
	g_nPlayerSkillDamage[0][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK1;		// �X�L���_���[�W�ʁi1�i�K��
	g_nPlayerSkillDamage[1][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK2;		// �X�L���_���[�W�ʁi2�i�K��
	g_nPlayerSkillDamage[2][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK3;		// �X�L���_���[�W�ʁi3�i�K��
	g_nPlayerSkillWidth[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_DAMAGE_WIDTH;		// �X�L�����蕝
	g_nPlayerSkillHeight[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_DAMAGE_HEIGHT;	// �X�L�����荂��
	g_nPlayerSkillPosY[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_POS_Y;			// �X�L������Y�ʒu
	// ����
	g_nPlayerSkillDamage[0][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK1;		// �X�L���_���[�W�ʁi1�i�K��
	g_nPlayerSkillDamage[1][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK2;		// �X�L���_���[�W�ʁi2�i�K��
	g_nPlayerSkillDamage[2][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK3;		// �X�L���_���[�W�ʁi3�i�K��
	g_nPlayerSkillWidth[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_DAMAGE_WIDTH;		// �X�L�����蕝
	g_nPlayerSkillHeight[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_DAMAGE_HEIGHT;	// �X�L�����荂��
	g_nPlayerSkillPosY[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_POS_Y;			// �X�L������Y�ʒu
	// ���l
	g_nPlayerSkillDamage[0][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK1;		// �X�L���_���[�W�ʁi1�i�K��
	g_nPlayerSkillDamage[1][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK2;		// �X�L���_���[�W�ʁi2�i�K��
	g_nPlayerSkillDamage[2][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK3;		// �X�L���_���[�W�ʁi3�i�K��
	g_nPlayerSkillWidth[PLAYER_TYPE_KING]		= KING_SKILL_DAMAGE_WIDTH;		// �X�L�����蕝
	g_nPlayerSkillHeight[PLAYER_TYPE_KING]		= KING_SKILL_DAMAGE_HEIGHT;		// �X�L�����荂��
	g_nPlayerSkillPosY[PLAYER_TYPE_KING]		= KING_SKILL_POS_Y;				// �X�L������Y�ʒu
	// ����
	g_nPlayerSkillDamage[0][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK1;	// �X�L���_���[�W�ʁi1�i�K��
	g_nPlayerSkillDamage[1][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK2;	// �X�L���_���[�W�ʁi2�i�K��
	g_nPlayerSkillDamage[2][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK3;	// �X�L���_���[�W�ʁi3�i�K��
	g_nPlayerSkillWidth[PLAYER_TYPE_PEOPLE]		= PEOPLE_SKILL_DAMAGE_WIDTH;	// �X�L�����蕝
	g_nPlayerSkillHeight[PLAYER_TYPE_PEOPLE]	= PEOPLE_SKILL_DAMAGE_HEIGHT;	// �X�L�����荂��
	g_nPlayerSkillPosY[PLAYER_TYPE_PEOPLE]		= PEOPLE_SKILL_POS_Y;			// �X�L������Y�ʒu
	// �����i�_
	g_nPlayerSkillDamage[0][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK1;		// �X�L���_���[�W�ʁi1�i�K��
	g_nPlayerSkillDamage[1][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK2;		// �X�L���_���[�W�ʁi2�i�K��
	g_nPlayerSkillDamage[2][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK3;		// �X�L���_���[�W�ʁi3�i�K��
	g_nPlayerSkillWidth[PLAYER_TYPE_GOD]		= GOD_SKILL_DAMAGE_WIDTH;		// �X�L�����蕝
	g_nPlayerSkillHeight[PLAYER_TYPE_GOD]		= GOD_SKILL_DAMAGE_HEIGHT;		// �X�L�����荂��
	g_nPlayerSkillPosY[PLAYER_TYPE_GOD]			= GOD_SKILL_POS_Y;				// �X�L������Y�ʒu

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���C���[���̏�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].fMoveSpeed = PLAYER_MOVE_SPEED;
		g_aPlayer[nCntPlayer].fJampMove = PLAYER_JUMP_MOVE;
		g_aPlayer[nCntPlayer].fRadius = PLAYER_COLISION_RADIUS;
		g_aPlayer[nCntPlayer].fHeight = PLAYER_COLISION_HEIGHT;
		g_aPlayer[nCntPlayer].fCollisionRadius = 20.0f;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].nSkillPoint = PLAYER_SKILL;
		g_aPlayer[nCntPlayer].nSkillRank = 0;
		g_aPlayer[nCntPlayer].nModelParts = 0;
		g_aPlayer[nCntPlayer].nIdyShadow = 0;
		g_aPlayer[nCntPlayer].type = PLAYER_TYPE_BRAVE;
		g_aPlayer[nCntPlayer].nCounterState = APPEAR_TIME;
		g_aPlayer[nCntPlayer].state = PLAYERSTATE_APPEAR;
		g_aPlayer[nCntPlayer].MotionType = PLAYER_MOTION_TYPE_NEUTRAL;
		g_aPlayer[nCntPlayer].MotionTypeHit = PLAYER_MOTION_TYPE_NEUTRAL;
		g_aPlayer[nCntPlayer].fGravity = PLAYER_GRAVITY;
		g_aPlayer[nCntPlayer].b2PColor = false;
		g_aPlayer[nCntPlayer].nRecovery = 0;

		for (int nCntBool = 0; nCntBool < PLAYER_BOOL_MAX; nCntBool++)
		{
			g_aPlayer[nCntPlayer].bBool[nCntBool] = false;
			g_aPlayer[nCntPlayer].bBoolOld[nCntBool] = false;
		}
		// �W�����v���ɂ���
		g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = true;

		g_aPlayer[nCntPlayer].bUse = false;
		g_aPlayer[nCntPlayer].bDisp = true;
		for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
		{
			g_aPlayer[nCntPlayer].aModel[nCntModel].posAddMotion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayer[nCntPlayer].aModel[nCntModel].rotAddMotion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// ���[�V�����ݒ�
		g_aPlayer[nCntPlayer].nKeyCnt = 0;
		g_aPlayer[nCntPlayer].nFrameCounter = 0;
		g_aPlayer[nCntPlayer].nAllFrameCounter = 0;
		g_aPlayer[nCntPlayer].bBlend = false;

		// �ړ��\�͈͂̏ꏊ�ɂ��邩�ǂ���
		for (int nCntArea = 0; nCntArea < PLAYER_SIDE_MAX; nCntArea++)
		{
			g_aPlayer[nCntPlayer].bAreaLimit[nCntArea] = false;
		}
	}

	g_nMoveRimit = PLAYER_MOVE_RIMIT;


	// �z�u�������Ƃɔz�u���s��
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		SetPlayer(g_aPlayerSetInfo[nCntPlayer].pos, g_aPlayerSetInfo[nCntPlayer].rot, g_aPlayerSetInfo[nCntPlayer].type);
	}

	// �S�b�h�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data//MODEL//Commoner//TEXTURE//god.jpg",&g_pTexturePlayerGod);

	// 2P�p�e�N�X�`���̓ǂݍ���
	for (int nCntTex = 0; nCntTex < PLAYER_TYPE_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePlayer2PInfo[nCntTex].pFilename,
			&g_pTexturePlayer2P[nCntTex]);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPlayer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PLAYER_TYPE_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_pTexturePlayer2P[nCntTex] != NULL)
		{
			g_pTexturePlayer2P[nCntTex]->Release();
			g_pTexturePlayer2P[nCntTex] = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePlayer(void)
{
	BATTLESTATE BattleState = GetBattleState();
	GAMEMODE mode = GetGameMode();
	// �J�������擾
	Camera *pCamera = GetCamera();
	float fDiffAngle;		// ����
	float fDestAngle;		// �ړI�̊p�x
	float fMoveAngle;		// ���݂̊p�x

							// �ړ����������f�o�b�O�p
	//if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_nMoveRimit--;
	//}
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_nMoveRimit++;
	//}

	//// �f�o�b�O�p
	//if (GetKeyboardTrigger(DIK_O) == true)
	//{
	//	g_bTestPlayerDisp = g_bTestPlayerDisp ? false : true;
	//}

	/*if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_aPlayer[0].nSkillPoint = 100;
	}*/


	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true)
		{ // �g�p���Ă���ꍇ
			for (int nCntBool = 0; nCntBool < PLAYER_BOOL_MAX; nCntBool++)
			{ // �O��̏󋵂��L�^
				g_aPlayer[nCntPlayer].bBoolOld[nCntBool] = g_aPlayer[nCntPlayer].bBool[nCntBool];
			}

			// �O��̈ʒu�E���[�V�����̎�ނ��L�^
			g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;
			g_aPlayer[nCntPlayer].MotionTypeOld = g_aPlayer[nCntPlayer].MotionType;

			if (mode == GAMEMODE_BATTLE)
			{ // �o�g�����[�h�̏ꍇ
				switch (g_aPlayer[nCntPlayer].state)
				{ // �v���C���[�̏�Ԃ̏���
				case PLAYERSTATE_APPEAR:
					g_aPlayer[nCntPlayer].nCounterState--;
					// ������VS�̑ҋ@���ԁH�H

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // �J�E���^�[��0�ȉ��ɂȂ�����v���C���[�̏�Ԃ�ʏ��Ԃɖ߂�
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
						g_aPlayer[nCntPlayer].bDisp = true;
					}
					break;
				case PLAYERSTATE_NORMAL:
					break;
				case PLAYERSTATE_DAMAGE:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // �J�E���^�[��0�ȉ��ɂȂ�����v���C���[�̏�Ԃ�ʏ��Ԃɖ߂�
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_DAMAGE] = false;
					}
					break;
				case PLAYERSTATE_DOWN:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // �J�E���^�[��0�ȉ��ɂȂ�����v���C���[�̏�Ԃ��N���オ��
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_GETUP;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_GETUP] = true;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_BLOW] = false;
					}
					break;
				case PLAYERSTATE_GETUP:
					break;
				case PLAYERSTATE_DEATH:
					//g_aPlayer[nCntPlayer].nCounterState--;
					//if (g_aPlayer[nCntPlayer].nCounterState == 0)
					//{ // �J�E���^�[��0�ȉ��ɂȂ����烊�U���g��ʂɑ���
					//	// �Q�[���X�e�[�g�ݒ�
					//	SetGameFade(GAMEMODE_RESULT);
					//}
					break;
				case PLAYERSTATE_INVINCIBLE:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // �J�E���^�[��0�ȉ��ɂȂ�����v���C���[�̏�Ԃ��N���オ��
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
					}
					break;
				}
				// ���݂̊p�x����(Y)
				fMoveAngle = g_aPlayer[nCntPlayer].rot.y;

				if (g_aPlayer[nCntPlayer].state != PLAYERSTATE_DEATH && BattleState != BATTLESTATE_TIMEOVER && BattleState != BATTLESTATE_CLEAR
					&& BattleState != BATTLESTATE_START)
				{
					// �v���C���[���쏈��
					PlayerController((PLAYER_CONTROL)nCntPlayer);
				}

				// �ړ���������Check
				CheckMove(nCntPlayer);

				// ����Check
				CheckRot(nCntPlayer);

				// �d�͉��Z
				g_aPlayer[nCntPlayer].move.y -= g_aPlayer[nCntPlayer].fGravity;

				// �ʒu�X�V
				g_aPlayer[nCntPlayer].pos.x += g_aPlayer[nCntPlayer].move.x;
				g_aPlayer[nCntPlayer].pos.y += g_aPlayer[nCntPlayer].move.y;
				g_aPlayer[nCntPlayer].pos.z += g_aPlayer[nCntPlayer].move.z;

				g_aPlayer[nCntPlayer].move.x += float(-g_aPlayer[nCntPlayer].move.x) * PLAYER_MOVE_INERTIA;
				g_aPlayer[nCntPlayer].move.y += float(-g_aPlayer[nCntPlayer].move.y) * PLAYER_MOVE_INERTIA;
				g_aPlayer[nCntPlayer].move.z += float(-g_aPlayer[nCntPlayer].move.z) * PLAYER_MOVE_INERTIA;


				// �߂��聕�v���C���[���m�Ό�
				CollisionMove(nCntPlayer);

				// �ړ��\�͈͐���
				CheckMoveArea(nCntPlayer);

				// �ړI�̊p�x����
				fDestAngle = g_aPlayer[nCntPlayer].rot.y;
				// �������v�Z
				fDiffAngle = (fDestAngle - fMoveAngle);

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle += -D3DX_PI * 2;
				}
				else if (fDiffAngle < -D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2;
				}

				// ���݂̊p�x�ɍ����̉���������
				fMoveAngle += fDiffAngle * PLAYER_SPIN_INERTIA;

				if (fMoveAngle > D3DX_PI)
				{
					fMoveAngle += -D3DX_PI * 2;
				}
				else if (fMoveAngle < -D3DX_PI)
				{
					fMoveAngle += D3DX_PI * 2;
				}

				g_aPlayer[nCntPlayer].rot.y = fMoveAngle;

				// �I�u�W�F�N�g�ƃ��b�V���t�B�[���h�����蔻��
				if (CollisionMeshBattleField(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, g_aPlayer[nCntPlayer].fRadius) == true)
				{
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = false;
				}
				else
				{
					if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false)
					{ // �W�����v���Ă��Ȃ��Ă��󒆂ɏo���ꍇ
						//g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = true;
					}
				}

				// �e�̈ړ�����
				SetPositionShadow(g_aPlayer[nCntPlayer].nIdyShadow, g_aPlayer[nCntPlayer].pos);

				// ���n�̏���(�i�Q�[�ɒ��n���[�V�����͂���Ȃ����U���I���̂��ߕK�v
				if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBoolOld[PLAYER_BOOL_JUMP] == true)
				{
					// �U���������I�ɏI��������
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
				}

				// ���[�V�����^�C�v�ݒ�
				PlayerMotionTypeSet(nCntPlayer);

				// �v���C���[���[�V��������
				PlayerMotion(nCntPlayer);

				// �U�������蔻��
				if (CollisionAttack(nCntPlayer))
				{ // �����蔻��
				  // �U���������������[�V�������L�^
					g_aPlayer[nCntPlayer].MotionTypeHit = g_aPlayer[nCntPlayer].MotionType;
				}
				// �X�L���U�������蔻��
				if (CollisionSkillAttack(nCntPlayer))
				{ // �����蔻��
				  // �U���������������[�V�������L�^
					g_aPlayer[nCntPlayer].MotionTypeHit = g_aPlayer[nCntPlayer].MotionType;
				}

				if (g_aPlayer[nCntPlayer].MotionType == PLAYER_MOTION_TYPE_NEUTRAL || g_aPlayer[nCntPlayer].MotionType == PLAYER_MOTION_TYPE_NEUTRAL_SQUAT)
				{
					g_aPlayer[nCntPlayer].MotionTypeHit = PLAYER_MOTION_TYPE_NEUTRAL;
				}
			}
			else if (mode == GAMEMODE_PLAYERSHOW)
			{ // �v���C���[�V���E�̏ꍇ

			  // �v���C���[���[�V��������
				PlayerMotion(nCntPlayer);
			}
		}
#if DEBUG_SPHERE
		// �f�o�b�O�p�h�䔻��X�t�B�A�X�V����
		PlayerDebugDeffSphereUpdate(nCntPlayer);
#endif // DEBUG_SPHERE
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;					// �e�q�֌W���f�p�̃}�g���b�N�X

	BATTLESTATE BattleState = GetBattleState();
	if (BattleState == BATTLESTATE_TIMEOVER)
	{
		// �A���t�@�e�X�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g���J�n����
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// ��l(REF)�����߂�
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ����(FUNC)�����߂�,D3DCMP_GREATER,��r(CMP),GREATER(�Z�Z���傫��)
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true && g_aPlayer[nCntPlayer].bDisp == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].mtxWorld);

			for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nModelParts; nCntModel++)
			{
				if (g_aPlayer[nCntPlayer].aModel[nCntModel].nIdxModelParent == -1)
				{
					mtxParent = g_aPlayer[nCntPlayer].mtxWorld;
				}
				else
				{
					mtxParent = g_aPlayer[nCntPlayer].aModel[g_aPlayer[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].aModel[nCntModel].rot.y + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.y,
					g_aPlayer[nCntPlayer].aModel[nCntModel].rot.x + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.x,
					g_aPlayer[nCntPlayer].aModel[nCntModel].rot.z + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRot);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].aModel[nCntModel].pos.x + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.x,
					g_aPlayer[nCntPlayer].aModel[nCntModel].pos.y + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.y,
					g_aPlayer[nCntPlayer].aModel[nCntModel].pos.z + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTrans);

				// �e�̃��[���h�}�g���b�N�X�𔽉f
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxParent);

				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld);

				// ���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				if (g_bTestPlayerDisp == false)
				{ // �f�o�b�O�p
				  // �}�e���A���f�[�^�ւ̃|�C���^���擾
					pMat = (D3DXMATERIAL*)g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].nNumMat; nCntMat++)
					{
						if (g_aPlayer[nCntPlayer].b2PColor == true)
						{// 2P�̏ꍇ
							pDevice->SetTexture(0, g_pTexturePlayer2P[g_aPlayer[nCntPlayer].type]);
						}
						else
						{
							if (g_aPlayer[nCntPlayer].type == PLAYER_TYPE_GOD)
							{// �_�̏ꍇ
								pDevice->SetTexture(0, g_pTexturePlayerGod);
							}
							else
							{
								// �e�N�X�`���̐ݒ�
								pDevice->SetTexture(0, g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pTexture[nCntMat]);
							}
						}

						// �}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						// �G(�p�[�c)�̕`��
						g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pMesh->DrawSubset(nCntMat);
					}
				}
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}

	if (BattleState == BATTLESTATE_TIMEOVER)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g���I������
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�^�C�v�f�[�^�̏�����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPlayerTypeData(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// �����蔻���\�����邩
		g_aAttackCollisionDisp[nCntPlayer] = false;
	}

	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		g_aPlayerType[nCntType].nModelParts = 0;
		g_aPlayerType[nCntType].fMoveSpeed = 0.0f;
		g_aPlayerType[nCntType].fJampMove = 0.0f;
		g_aPlayerType[nCntType].fRadius = 0.0f;
		g_aPlayerType[nCntType].fHeight = 0.0f;
		g_aPlayerType[nCntType].fDamage = 0.0f;
		g_aPlayerType[nCntType].fKnockBack = 0.0f;

		// ���[�V���������̖h�䓖���蔻��̏�����
		for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
		{
			g_aPlayerType[nCntType].collisionD[nCntCollision].bUse = false;
			g_aPlayerType[nCntType].collisionD[nCntCollision].fRadius = 0.0f;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nDamage = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].fDistance = 0.0f;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nFrameS = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nFrameE = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nPartsId = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayerType[nCntType].collisionD[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
			}

			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
			}
#endif // DEBUG_SPHERE
		}

		// �^�C�v�f�[�^���̃��[�V�������̏�����
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = false;
			g_aPlayerType[nCntType].aMotion[nCntMotion].nAllFrame = 0;
			g_aPlayerType[nCntType].aMotion[nCntMotion].nNumKey = 0;

			// ���[�V���������̍U�������蔻��̏�����
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
			{
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].bUse = false;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].fRadius = 0.0f;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nDamage = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nFrameS = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nFrameE = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nPartsId = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
#if DEBUG_SPHERE
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
				}
#endif // DEBUG_SPHERE
			}


			// ���[�V���������̃L�[���̏�����
			for (int nCntKey = 0; nCntKey < MAX_PLAYER_KEY; nCntKey++)
			{
				g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].nFrame = 0;
				// �L�[�����̃p�[�c���̏�����
				for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
				{
					g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
		PlayerModelData	apPlayer[MAX_PLAYER_PARTS] = {};	// ���f���ւ̃|�C���^
		MotionPlayer	aMotion[PLAYER_MOTION_TYPE_MAX];	// ���[�V����
		PlayerModel		aModel[MAX_PLAYER_PARTS];			// �p�[�c���
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayerSetInfo[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerSetInfo[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerSetInfo[nCntPlayer].type = PLAYER_TYPE_BRAVE;
		g_aPlayerSetInfo[nCntPlayer].bUse = false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�^�C�v�f�[�^�̏I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPlayerTypeData(void)
{
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < sizeof g_aPlayerType[nCntType].apPlayer / sizeof(PlayerModelData); nCntModel++)
		{
			// �e�N�X�`���̊J��
			for (int nCntTex = 0; nCntTex < (int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat; nCntTex++)
			{
				if (g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex] != NULL)
				{
					g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex]->Release();
					g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex] = NULL;
				}
			}

			// ���b�V���̊J��
			if (g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh != NULL)
			{
				g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh->Release();
				g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh = NULL;
			}
			// �}�e���A���̊J��
			if (g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat != NULL)
			{
				g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat->Release();
				g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat = NULL;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == false)
		{ // �G���g�p����Ă��Ȃ��ꍇ
			// 2P�J���[�g�p�̏�����
			g_aPlayer[nCntPlayer].b2PColor = false;

			g_aPlayer[nCntPlayer].pos = pos;
			g_aPlayer[nCntPlayer].rot = rot;
			// �G�̎�ނ�ݒ�
			g_aPlayer[nCntPlayer].type = type;

			g_aPlayer[nCntPlayer].fMoveSpeed = g_aPlayerType[g_aPlayer[nCntPlayer].type].fMoveSpeed;
			g_aPlayer[nCntPlayer].fJampMove = g_aPlayerType[g_aPlayer[nCntPlayer].type].fJampMove;
			g_aPlayer[nCntPlayer].fRadius = g_aPlayerType[g_aPlayer[nCntPlayer].type].fRadius;

			g_aPlayer[nCntPlayer].nModelParts = g_aPlayerType[g_aPlayer[nCntPlayer].type].nModelParts;

			for (int nCntParts = 0; nCntParts < g_aPlayer[nCntPlayer].nModelParts; nCntParts++)
			{
				// �C���f�b�N�X�𔽉f
				g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].nIdxModelParent;

				g_aPlayer[nCntPlayer].aModel[nCntParts].nModelType = nCntParts;

				// �ʒu�E�����𔽉f
				g_aPlayer[nCntPlayer].aModel[nCntParts].pos = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].pos;
				g_aPlayer[nCntPlayer].aModel[nCntParts].rot = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].rot;
			}

			// �e��ݒ�
			g_aPlayer[nCntPlayer].nIdyShadow = SetShadow(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot, g_aPlayer[nCntPlayer].fRadius * 2, g_aPlayer[nCntPlayer].fRadius * 2);

			g_aPlayer[nCntPlayer].bUse = true; // �g�p���Ă����Ԃɂ���

			if (nCntPlayer != 0)
			{
				// 2P�J���[�ɂ��邩�m�F
				for (int nCnt2P = 0; nCnt2P < MAX_PLAYER; nCnt2P++)
				{
					if (g_aPlayer[nCnt2P].bUse == true && nCnt2P != nCntPlayer)
					{
						if (g_aPlayer[nCnt2P].type == g_aPlayer[nCntPlayer].type)
						{
							g_aPlayer[nCntPlayer].b2PColor = true;
						}
					}
				}
			}
			break;	// ����break�͂��Ȃ���
		}
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̔z�u���ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPlayerInfo(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_aPlayerSetInfo[nCnt].bUse == false)
		{ // �G���g�p����Ă��Ȃ��ꍇ
			g_aPlayerSetInfo[nCnt].pos = pos;
			g_aPlayerSetInfo[nCnt].rot = rot;
			// �G�̎�ނ�ݒ�
			g_aPlayerSetInfo[nCnt].type = type;

			g_aPlayerSetInfo[nCnt].bUse = true; // �g�p���Ă����Ԃɂ���

			break;	// ����break�͂��Ȃ���
		}
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̃��[�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotion(int nPlayerID)
{
	int nFrame = 0; // ���[�V�����̕����t���[�����L�^

	if (g_aPlayer[nPlayerID].MotionType != g_aPlayer[nPlayerID].MotionTypeOld)
	{ // ���݂̃��[�V�����ƑO��̃��[�V�������������
		g_aPlayer[nPlayerID].nFrameCounter = 0;	// �t���[�������Z�b�g
		g_aPlayer[nPlayerID].nKeyCnt = 0;			// �L�[�����Z�b�g
		g_aPlayer[nPlayerID].nAllFrameCounter = 0;	// �S�Ẵt���[�������Z�b�g
		g_aPlayer[nPlayerID].bBlend = true;		// �u�����h������
		nFrame = PLAYER_MOTION_BLEND_FRAME;			// �u�����h�̃t���[����
	}
	else
	{ // �ʏ펞�̃��[�V�����̕����t���[��
		nFrame = g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].nFrame;
	}

	if (g_aPlayer[nPlayerID].nFrameCounter == 0)
	{ // 1�t���[�����Ƃ̒ǉ��ʂ��v�Z
		for (int nCntPartsKey = 0; nCntPartsKey < g_aPlayer[nPlayerID].nModelParts; nCntPartsKey++)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].posAddMotion =
				(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].aPartsKey[nCntPartsKey].pos - g_aPlayer[nPlayerID].aModel[nCntPartsKey].posMotion)
				/ float(nFrame);

			// �������v�Z
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion =
				(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].aPartsKey[nCntPartsKey].rot - g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion)
				/ float(nFrame);

			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x += D3DX_PI * 2;
			}
			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y += D3DX_PI * 2;
			}
			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z += D3DX_PI * 2;
			}
		}
	}

	if (g_aPlayer[nPlayerID].nKeyCnt == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1
		&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].bLoop == false
		&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1].nFrame == g_aPlayer[nPlayerID].nFrameCounter + 1)
	{ // �U�����n�I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] = false;
	}
	// ��U��
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SMALL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SMALL)
	{ // ��U���I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
	}
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL)
	{ // ���Ⴊ�ݎ�U���I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
	}

	// ���U��
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_BIG &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_BIG)
	{ // ���U���I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
	}
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG)
	{ // ���Ⴊ�݋��U���I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_LANDING &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_LANDING)
	{ // ���n�I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_GETUP &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_GETUP)
	{ // �N���オ��I������
		g_aPlayer[nPlayerID].state = PLAYERSTATE_INVINCIBLE;
		g_aPlayer[nPlayerID].nCounterState = INVINCIBLE_TIME;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_SKILL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_SKILL)
	{ // �X�L���I������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = false;
	}

	// ���[�V�������Z
	for (int nCntPartsKey = 0; nCntPartsKey < g_aPlayer[nPlayerID].nModelParts; nCntPartsKey++)
	{
		g_aPlayer[nPlayerID].aModel[nCntPartsKey].posMotion += g_aPlayer[nPlayerID].aModel[nCntPartsKey].posAddMotion;
		g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion += g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion;

		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x += D3DX_PI * 2;
		}
		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y += D3DX_PI * 2;
		}
		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z += D3DX_PI * 2;
		}
	}

	// �t���[���J�E���^�[����
	g_aPlayer[nPlayerID].nFrameCounter++;
	g_aPlayer[nPlayerID].nAllFrameCounter++;

	if (g_aPlayer[nPlayerID].bBlend == true && g_aPlayer[nPlayerID].nFrameCounter == PLAYER_MOTION_BLEND_FRAME)
	{ // �u�����h�����Z�b�g
		g_aPlayer[nPlayerID].nFrameCounter = 0;
		g_aPlayer[nPlayerID].bBlend = false;
		g_aPlayer[nPlayerID].nKeyCnt = 1;
	}
	else if (g_aPlayer[nPlayerID].nFrameCounter == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].nFrame)
	{ // �t���[���J�E���^�[���Z�b�g
		g_aPlayer[nPlayerID].nFrameCounter = 0;
		if (g_aPlayer[nPlayerID].nKeyCnt == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1
			&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].bLoop == false)
		{ //���[�v�������ő�L�[���𒴂���

		}
		else
		{
			g_aPlayer[nPlayerID].nKeyCnt = (g_aPlayer[nPlayerID].nKeyCnt + 1) % g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey;
		}
	}

	if (g_aPlayer[nPlayerID].nAllFrameCounter == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nAllFrame)
	{
		g_aPlayer[nPlayerID].nAllFrameCounter = 0;
	}

}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[���[�V�����̎�ނ̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotionTypeSet(int nPlayerID)
{
	if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] == true)
	{ // �N���オ����s���Ă��邩����
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GETUP;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] == true)
	{ // �Ԃ���΂���Ă��邩����
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_BLOW;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] == true)
	{ // �_���[�W���󂯂Ă��邩����
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // ���Ⴊ�ݏ�Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_DAMAGE_SQUAT;
		}
		else
		{ // ����ȊO�̏ꍇ
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_DAMAGE;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true)
	{ // �X�L�����g���Ă��邩
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_SKILL;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] == true)
	{ // �K�[�h�����Ă��邩����
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // ���Ⴊ�ݏ�Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GUARD_SQUAT;
		}
		else
		{ // ����ȊO�̏ꍇ
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GUARD;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] == true)
	{ // ��U������
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // ���Ⴊ�ݏ�Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // �W�����v��Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_JUMP_SMALL;
		}
		else
		{ // ����ȊO�̏ꍇ
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SMALL;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] == true)
	{ // ���U������
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // ���Ⴊ�ݏ�Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // �W�����v��Ԃ�
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_JUMP_BIG;
		}
		else
		{ // ����ȊO�̏ꍇ
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_BIG;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
	{ // �W�����v��Ԃ�
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_FRONT] == true)
		{ // �O
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_FRONT;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BACK] == true)
		{ // ��
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_BACK;
		}
		else
		{
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_UP;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
	{ // ���Ⴊ�ݏ�Ԃ�
		if (g_aPlayer[nPlayerID].bBoolOld[PLAYER_BOOL_SQUAT] == true)
		{ // �O�񂪂��Ⴊ�ݏ�Ԃ��ǂ���
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_NEUTRAL_SQUAT;
		}
		else
		{ // �O�񂪂��Ⴊ�ݏ�Ԃ���Ȃ��ꍇ
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_SQUAT;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] == true)
	{ // ���n��Ԃ�
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_LANDING;
	}
	else if (g_aPlayer[nPlayerID].move.x > 1.0f || g_aPlayer[nPlayerID].move.x < -1.0f
		|| g_aPlayer[nPlayerID].move.z > 1.0f || g_aPlayer[nPlayerID].move.z < -1.0f)
	{ // ���s��Ԃ�
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_WALK;
	}
	else
	{ // �j���[�g������
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_NEUTRAL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[���[�V�����̎�ނ̐ݒ�(���ڎw��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotionTypeSet(int nPlayerID, PLAYER_MOTION_TYPE motionType)
{
	g_aPlayer[nPlayerID].MotionType = motionType;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̃_���[�W����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void HitPlayer(D3DXVECTOR3 HitPos, int nPlayerID, int nDamage, float fDistance, bool bigAttack, bool bSkill)
{
	PLAYER_TYPE atkType; // �U�����̃^�C�v

	// �_���[�W�{�[�i�X�̊m�F
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // �U�����󂯂��v���C���[�ł͂Ȃ��ꍇ
		  // �U�������N�̃_���[�W�{�[�i�X���v�Z
			nDamage += g_nAttackRankDamage[g_aPlayer[nCntPlayer].atkRank];

			// �U�����̎�ނ��L�^
			atkType = g_aPlayer[nCntPlayer].type;

			break;
		}
	}
	// �h�䃉���N�̃_���[�W�����{�[�i�X���v�Z
	nDamage -= g_nDefenseRankDamage[g_aPlayer[nPlayerID].defRank];

	// �����̗L���s���̃_���[�W�v�Z
	switch (g_aPlayer[nPlayerID].type)
	{
	case PLAYER_TYPE_BRAVE:	// �U�����󂯂������E�҂̏ꍇ
		if (atkType == PLAYER_TYPE_DEVIL)
		{ // �U�������̂������̏ꍇ
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_KING)
		{ // �U�������̂����l�̏ꍇ
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		break;
	case PLAYER_TYPE_DEVIL:	// �U�����󂯂����������̏ꍇ
		if (atkType == PLAYER_TYPE_BRAVE)
		{ // �U�������̂��E�҂̏ꍇ
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_KING)
		{ // �U�������̂����l�̏ꍇ
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		break;
	case PLAYER_TYPE_KING:	// �U�����󂯂��������l�̏ꍇ
		if (atkType == PLAYER_TYPE_BRAVE)
		{ // �U�������̂��E�҂̏ꍇ
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_DEVIL)
		{ // �U�������̂������̏ꍇ
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		break;
	}

	// ��e���̈ړ������̊m�F
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // �U�����󂯂��v���C���[�ł͂Ȃ��ꍇ
		  // �U���������v���C���[���ǂ���ɂ�����
			if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
			{ // �U�������v���C���[���E���ɂ����ꍇ
			  // �ړ��ʂ��t�]������
				fDistance *= -1;
			}
		}
	}

	bool bGuardSuccess = false;

	// �K�[�h��������
	if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] == true)
	{ // �K�[�h�����Ă��邩
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{ // �U�����s�����v���C���[�̏ꍇ
				if (bSkill == true)
				{ // SKILL�U���̏ꍇ�͎����̏�Ԃɂ�����炸�K�[�h�\
					bGuardSuccess = true;
				}
				if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == true)
				{ // �W�����v���Ă����ꍇ
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true || g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] != true)
					{ // �U�����������v���C���[���W�����v���Ă����ꍇ
						// �K�[�h����
						bGuardSuccess = true;
					}
				}
				else if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == true)
				{ // ���Ⴊ��ł����ꍇ
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
					{ // �U�����������v���C���[�����Ⴊ��ł����ꍇ
					  // �K�[�h����
						bGuardSuccess = true;
					}
				}
				else
				{ // �W�����v�����Ⴊ�݂��s���Ă��Ȃ��ꍇ
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] != true
						&& g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] != true)
					{ // �U�����������v���C���[���W�����v�����Ⴊ�݂��s���Ă��Ȃ��ꍇ
						// �K�[�h����
						bGuardSuccess = true;
					}
				}
			}
		}
	}

	if (bGuardSuccess == true)
	{ //�K�[�h������
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] = true;

		// �K�[�h�ɐ��������̂Ń_���[�W�ʂ�����������
		nDamage = int(nDamage * PLAYER_GUARD_DAMAGE);

		// �K�[�h�ɐ��������̂ő����������ނ�����
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{ // �U�����󂯂��v���C���[�ł͂Ȃ��ꍇ
			  // �U����e���̈ړ���
				g_aPlayer[nCntPlayer].move.x -= fDistance;
			}
		}

		// �K�[�h�G�t�F�N�g
		SetEffect(HitPos, EFFECTTYPE_GUARD);
	}
	else
	{ // �K�[�h���s��
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // �v���C���[���W�����v���������ꍇ
		  // �Ԃ���я�Ԃɂ���
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DOWN;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = false;
			g_aPlayer[nPlayerID].nCounterState = DOWN_TIME;

			if (bigAttack == true)
			{ // ��U��
				// �q�b�g�G�t�F�N�g��
				SetEffect(HitPos, EFFECTTYPE_HIT_001);

				switch (g_aPlayer[nPlayerID].type)
				{// �Ԃ��Ƃу{�C�X
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_003_SE, 0.8f);
					break;
				}
			}
			else
			{ // ���U��
				// �q�b�g�G�t�F�N�g��
				SetEffect(HitPos, EFFECTTYPE_HIT_000);

				switch (g_aPlayer[nPlayerID].type)
				{// �Ԃ��Ƃу{�C�X
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_002_SE, 0.8f);
					break;
				}
			}
		}
		else if (bigAttack == true)
		{ // ��U���������ꍇ
		  // �Ԃ���я�Ԃɂ���
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DOWN;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = false;
			g_aPlayer[nPlayerID].nCounterState = DOWN_TIME;
			// �q�b�g�G�t�F�N�g��
			SetEffect(HitPos, EFFECTTYPE_HIT_001);

			switch (g_aPlayer[nPlayerID].type)
			{// �Ԃ��Ƃу{�C�X
			case PLAYER_TYPE_BRAVE:
				SelectVolume(SOUND_LABEL_SE_YUSHA_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_DEVIL:
				SelectVolume(SOUND_LABEL_SE_MAOU_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_KING:
				SelectVolume(SOUND_LABEL_SE_OU_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_PEOPLE:
				SelectVolume(SOUND_LABEL_HEIMIN_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_GOD:
				SelectVolume(SOUND_LABEL_GOD_003_SE, 0.8f);
				break;
			}
		}
		else
		{ // ���̑�����
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DAMAGE;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = true;
			g_aPlayer[nPlayerID].nCounterState = DAMAGE_TIME;
			// �q�b�g�G�t�F�N�g��
			SetEffect(HitPos, EFFECTTYPE_HIT_000);
			switch (g_aPlayer[nPlayerID].type)
			{// �Ԃ��Ƃу{�C�X
			case PLAYER_TYPE_BRAVE:
				SelectVolume(SOUND_LABEL_SE_YUSHA_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_DEVIL:
				SelectVolume(SOUND_LABEL_SE_MAOU_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_KING:
				SelectVolume(SOUND_LABEL_SE_OU_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_PEOPLE:
				SelectVolume(SOUND_LABEL_HEIMIN_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_GOD:
				SelectVolume(SOUND_LABEL_GOD_002_SE, 0.8f);
				break;
			}
		}

		// �U����e���̈ړ���
		if (g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_RIGHT] == false
			&& g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_LEFT] == false)
		{ // �U�����������v���C���[����ʒ[�ɂ��Ȃ��ꍇ
			// �U�����������v���C���[��������
			g_aPlayer[nPlayerID].move.x += fDistance;
		}
		else
		{ // �U�����������v���C���[����ʒ[�ɂ���ꍇ
			// �ړ��ʂ𔽓]
			fDistance *= -1;
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (nCntPlayer != nPlayerID)
				{ // �U�����󂯂��v���C���[�ł͂Ȃ��ꍇ

					g_aPlayer[nCntPlayer].move.x += fDistance;
				}
			}
		}

	}

	// SE�̍Đ�



	if (nDamage < 0)
	{ // �_���[�W�ʂ�0���傫���ꍇ�̂݃_���[�W��^����
	  // �Œ�_���[�W1�����
		nDamage = 1;
	}

	g_aPlayer[nPlayerID].nLife -= nDamage;

	// HP�Q�[�W�X�V
	SetHpGageDestLife(g_aPlayer[nPlayerID].nLife, (PLAYER_CONTROL)nPlayerID);

	//SP����
	AddPlayerSkillPoint(nPlayerID, PLAYER_SKILL_ADD_DEFENSE);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // �U���������v���C���[�ꍇ
			AddPlayerSkillPoint(nCntPlayer, PLAYER_SKILL_ADD_ATTACK);
		}
	}

	if (g_aPlayer[nPlayerID].nLife <= 0)
	{ // ���C�t0�ȉ��̏���
		g_aPlayer[nPlayerID].nLife = PLAYER_LIFE;

		// �c�@��0�ȉ��ɂȂ������̏���
		g_aPlayer[nPlayerID].state = PLAYERSTATE_DEATH;
		g_aPlayer[nPlayerID].nCounterState = DEATH_TIME;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
		g_aPlayer[nPlayerID].nLife = 0;

		//
		SetBattleState(BATTLESTATE_CLEAR);

		// KO��\��
		SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_KO);
		SelectVolume(SOUND_LABEL_KO_SE, 0.8f);

		// �^�C�}�[���~
		SetTimerSwitch(false);

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{
				PlayerBattleResultSave(nCntPlayer);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���C�t�̑���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddPlayerLife(int nPlayerID, int nLife)
{
	g_aPlayer[nPlayerID].nLife += nLife;

	if (g_aPlayer[nPlayerID].nLife > PLAYER_LIFE)
	{// �ő�l�𒴂���ꍇ
		g_aPlayer[nPlayerID].nLife = PLAYER_LIFE;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�L���|�C���g�̑���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddPlayerSkillPoint(int nPlayerID,int nSkillPoint)
{
	g_aPlayer[nPlayerID].nSkillPoint += nSkillPoint;

	if (g_aPlayer[nPlayerID].nSkillPoint > PLAYER_MAX_SKILL_POINT)
	{// �ő�l�𒴂���ꍇ
		g_aPlayer[nPlayerID].nSkillPoint = PLAYER_MAX_SKILL_POINT;
	}

	// �X�L���Q�[�W�̕ύX
	SetSpGageDestSkillPoint(g_aPlayer[nPlayerID].nSkillPoint, (PLAYER_CONTROL)nPlayerID);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Player *GetPlayer(void)
{
	return &g_aPlayer[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[���f���̎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
PlayerTypeData *GetPlayerTypeData(void)
{
	return &g_aPlayerType[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�R���g���[���[
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerController(PLAYER_CONTROL control)
{
	DIJOYSTATE2 *pGamePad = GetgamePadStick((int)control);
	// �J�������擾
	Camera *pCamera = GetCamera();

	if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
	{ // �U��������Ȃ��ꍇ
	  // ���Ⴊ�ݏ�Ԃ����Z�b�g
		g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;
	}

	// �K�[�h��Ԃ����Z�b�g
	g_aPlayer[control].bBool[PLAYER_BOOL_GUARD] = false;

	if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
	{ // �W�����v������Ȃ��ꍇ
	  // ������Ԃ����Z�b�g
		g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = false;
		g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = false;
	}

	if (g_aPlayer[control].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[control].bBool[PLAYER_BOOL_BLOW] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_GETUP] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false && g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
	{ // �_���[�W�E�Ԃ���сE�N���オ��E�W�����v�E�U����ԂłȂ��ꍇ
		if (GetController(control, PLAYER_CONTROLLER_SKILL))
		{ // �X�L��
			// �X�L���֐����Ă�
			SkillAttack(control);
		}
	}

	if (g_aPlayer[control].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[control].bBool[PLAYER_BOOL_BLOW] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_GETUP] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false && g_aPlayer[control].bBool[PLAYER_BOOL_SKILL] == false)
	{ // �_���[�W�E�Ԃ���сE�N���オ��E�U���E�X�L����ԂłȂ��ꍇ
		if (GetController(control, PLAYER_CONTROLLER_DOWN))
		{ // ���Ⴊ��
			if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
			{
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = true;
			}
		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] == false && g_aPlayer[control].bBool[PLAYER_BOOL_GUARD_HIT] == false
			&& g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
		{ // �U���E���Ⴊ�݁E�W�����v������Ȃ�
			 // �ړ�����
			if (GetController(control, PLAYER_CONTROLLER_LEFT))
			{ // ���ړ�
				g_aPlayer[control].move.x -= g_aPlayer[control].fMoveSpeed;
			}
			else if (GetController(control, PLAYER_CONTROLLER_RIGHT))
			{ // �E�ړ�
				g_aPlayer[control].move.x += g_aPlayer[control].fMoveSpeed;
			}
		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
		{ // �U��������Ȃ�
			if (GetController(control, PLAYER_CONTROLLER_ATTACK_SMALL))
			{ // ��U��
				g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] = true;
				switch (g_aPlayer[control].type)
				{// �U���{�C�X
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_000_SE, 0.8f);
					break;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_ATTACK_BIG))
			{ // ���U��
				g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] = true;
				switch (g_aPlayer[control].type)
				{// �U���{�C�X
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_001_SE, 0.8f);
					break;
				}
			}
			else
			{ // �U�����͂����Ȃ������ꍇ
			  // �K�[�h�����Ă��邩�m�F
				CheckGuard(control);
			}
		}

		if (g_aPlayer[control].MotionType != PLAYER_MOTION_TYPE_ATTACK_SMALL)
		{ // �U�����[�V��������Ȃ���
		  // �U��SE�̒�~

		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false
			&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
		{ // �W�����v�E�U��������Ȃ���
			if (GetController(control, PLAYER_CONTROLLER_LEFT_UP))
			{ // ���W�����v
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.x = sinf(-D3DX_PI / 4) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// ���Ⴊ�ݏ�Ԃ�����
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;

				if (g_aPlayer[control].side == PLAYER_SIDE_LEFT)
				{ // �v���C���[�������ɂ���ꍇ
					g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = true;
				}
				else
				{ // �E���ɂ���ꍇ
					g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = true;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_RIGHT_UP))
			{ // �E�W�����v
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.x = sinf(D3DX_PI / 4) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// ���Ⴊ�ݏ�Ԃ�����
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;

				if (g_aPlayer[control].side == PLAYER_SIDE_RIGHT)
				{ // �v���C���[���E���ɂ���ꍇ
					g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = true;
				}
				else
				{ // �����ɂ���ꍇ
					g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = true;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_UP))
			{ // ��W�����v
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// ���Ⴊ�ݏ�Ԃ�����
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	�U�������蔻��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionAttack(int nPlayerID)
{
#if DEBUG_SPHERE
	// �f�o�b�O�p�̃X�t�B�A���\���ɂ���(�U��
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
			{
				SetDispSphere(g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nSpherID[nPlayerID], false);
			}
		}
	}
#endif // DEBUG_SPHERE

	bool bHit = false;

	if (g_aPlayer[nPlayerID].MotionTypeHit != g_aPlayer[nPlayerID].MotionType)
	{ // �O�񓖂Ă��U��������ƈႤ�ꍇ�̂ݔ�����s��
		for (int nCntCollisionA = 0; nCntCollisionA < MAX_PLAYER_ATTACK_COLLISION; nCntCollisionA++)
		{
			if (g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].bUse == true
				&& g_aPlayer[nPlayerID].nAllFrameCounter >= g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nFrameS
				&& g_aPlayer[nPlayerID].nAllFrameCounter <= g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nFrameE)
			{
				D3DXMATRIX mtxWorldA, mtxRotA, mtxTransA;			// �v�Z�p�}�g���b�N�X

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxWorldA);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotA, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.y,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.x,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.z);

				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA, &mtxRotA);

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransA, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.x,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.y,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.z);

				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA, &mtxTransA);

				// �e�̃��[���h�}�g���b�N�X�𔽉f
				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA,
					&g_aPlayer[nPlayerID].aModel[g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nPartsId].mtxWorld);

#if DEBUG_SPHERE
				// �f�o�b�O�p�̃X�t�B�A�ړ�����
				SetPositionSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nSpherID[nPlayerID],
					D3DXVECTOR3(mtxWorldA._41, mtxWorldA._42, mtxWorldA._43));

				// �f�o�b�O�p�̃X�t�B�A��\��
				SetDispSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nSpherID[nPlayerID], true);
#endif // DEBUG_SPHERE

				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					if (nCntPlayer != nPlayerID && g_aPlayer[nCntPlayer].state != PLAYERSTATE_DOWN && g_aPlayer[nCntPlayer].state != PLAYERSTATE_GETUP)
					{ // �U�����󂯂�v���C���[���U�������v���C���[�ł͂Ȃ��A�Ԃ���я�Ԃł��N���オ���Ԃł��Ȃ��ꍇ
						for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
						{
							if (g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].bUse == true && bHit == false)
							{ // �h�䔻�肪�g�p����Ă���܂���e���Ă��Ȃ��ꍇ
								D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// �v�Z�p�}�g���b�N�X

								// ���[���h�}�g���b�N�X�̏�����
								D3DXMatrixIdentity(&mtxWorldD);

								// ��]�𔽉f
								D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.y,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.x,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.z);

								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

								// �ʒu�𔽉f
								D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.x,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.y,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.z);

								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

								// �e�̃��[���h�}�g���b�N�X�𔽉f
								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
									&g_aPlayer[nCntPlayer].aModel[g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

								float fLength = sqrtf((mtxWorldA._41 - mtxWorldD._41) * (mtxWorldA._41 - mtxWorldD._41)
									+ (mtxWorldA._42 - mtxWorldD._42) * (mtxWorldA._42 - mtxWorldD._42));

								if (fLength < g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].fRadius
									+ g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // �͈͓�
									D3DXVECTOR3 HitPos = D3DXVECTOR3(mtxWorldA._41, mtxWorldA._42, mtxWorldA._43);
									HitPos += D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43);
									HitPos /= 2.0f;
								  // �_���[�W��^����
									HitPlayer(HitPos, nCntPlayer, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nDamage,
										g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].fDistance, g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG],false);
									bHit = true;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return bHit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	�X�L���U�������蔻��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionSkillAttack(int nPlayerID)
{
	bool bHit = false;

	if (g_aPlayer[nPlayerID].MotionTypeHit != g_aPlayer[nPlayerID].MotionType)
	{ // �O�񓖂Ă��U��������ƈႤ�ꍇ�̂ݔ�����s��
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true
			&& g_aPlayer[nPlayerID].nAllFrameCounter == PLAYER_SKILL_START_FRAME)
		{ // �X�L�����g�p��/�X�L������J�n�t���[���𒴂����ꍇ
			if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
			{  // �U�����s�����v���C���[�������ɂ���
				switch (g_aPlayer[nPlayerID].type)
				{
				case PLAYER_TYPE_BRAVE:
					// �X�L���G�t�F�N�g���g�p
					//SetTextureAnim(D3DXVECTOR3(0.0f, 100.0f, 0.0f), TEXANIM_RAIZIN_R);
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_R);
					break;
				case PLAYER_TYPE_DEVIL:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
					break;
				case PLAYER_TYPE_KING:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
					break;
				case PLAYER_TYPE_PEOPLE:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
					break;
				case PLAYER_TYPE_GOD:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
					break;
				}

			}
			else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
			{  // �U�����s�����v���C���[���E���ɂ���
				switch (g_aPlayer[nPlayerID].type)
				{
				case PLAYER_TYPE_BRAVE:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_L);
					break;
				case PLAYER_TYPE_DEVIL:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
					break;
				case PLAYER_TYPE_KING:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
					break;
				case PLAYER_TYPE_PEOPLE:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
					break;
				case PLAYER_TYPE_GOD:
					// �X�L���G�t�F�N�g���g�p
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
					break;
				}
			}
		}
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true
			&& g_aPlayer[nPlayerID].nAllFrameCounter >= PLAYER_SKILL_START_FRAME)
		{ // �X�L�����g�p��/�X�L������J�n�t���[���𒴂����ꍇ
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (nCntPlayer != nPlayerID && g_aPlayer[nCntPlayer].state != PLAYERSTATE_DOWN && g_aPlayer[nCntPlayer].state != PLAYERSTATE_GETUP)
				{ // �U�����󂯂�v���C���[���U�������v���C���[�ł͂Ȃ��A�Ԃ���я�Ԃł��N���オ���Ԃł��Ȃ��ꍇ
					for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
					{
						if (g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].bUse == true && bHit == false)
						{ // �h�䔻�肪�g�p����Ă���܂���e���Ă��Ȃ��ꍇ
							D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// �v�Z�p�}�g���b�N�X

							// ���[���h�}�g���b�N�X�̏�����
							D3DXMatrixIdentity(&mtxWorldD);

							// ��]�𔽉f
							D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.y,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.x,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.z);

							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

							// �ʒu�𔽉f
							D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.x,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.y,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.z);

							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

							// �e�̃��[���h�}�g���b�N�X�𔽉f
							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
								&g_aPlayer[nCntPlayer].aModel[g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

							g_nPlayerSkillDamage[PLAYER_MAX_SKILL_RANK][PLAYER_TYPE_MAX];	// �X�L���_���[�W��
							g_nPlayerSkillWidth[PLAYER_TYPE_MAX];							// �X�L�����蕝
							g_nPlayerSkillHeight[PLAYER_TYPE_MAX];						// �X�L�����荂��

							D3DXVECTOR3 HitPos = D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43);
							if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
							{  // �U�����s�����v���C���[�������ɂ���
								if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius < mtxWorldD._41 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nCntPlayer].type] > mtxWorldD._41 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] < mtxWorldD._42 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] + g_nPlayerSkillHeight[g_aPlayer[nCntPlayer].type] > mtxWorldD._42 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // �͈͓�
									// �_���[�W��^����
									HitPlayer(HitPos, nCntPlayer, g_nPlayerSkillDamage[g_aPlayer[nPlayerID].nSkillRank-1][(int)g_aPlayer[nPlayerID].type], PLAYER_SKILL_DISTANCE, true,true);
									bHit = true;
									break;
								}
							}
							else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
							{  // �U�����s�����v���C���[���E���ɂ���
								if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius > mtxWorldD._41 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nCntPlayer].type] < mtxWorldD._41 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] < mtxWorldD._42 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] + g_nPlayerSkillHeight[g_aPlayer[nCntPlayer].type] > mtxWorldD._42 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // �͈͓�
								  // �_���[�W��^����
									HitPlayer(HitPos, nCntPlayer, g_nPlayerSkillDamage[g_aPlayer[nPlayerID].nSkillRank-1][(int)g_aPlayer[nPlayerID].type], PLAYER_SKILL_DISTANCE, true,true);
									bHit = true;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return bHit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	�X�L���U������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool SkillAttack(int nPlayerID)
{
	bool bSkill = false;

	if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_3)
	{
		g_aPlayer[nPlayerID].nSkillRank = 3;
		bSkill = true;
	}
	else if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_2)
	{
		g_aPlayer[nPlayerID].nSkillRank = 2;
		bSkill = true;
	}
	else if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_1)
	{
		g_aPlayer[nPlayerID].nSkillRank = 1;
		bSkill = true;
	}

	if (bSkill == true)
	{
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = true;
		g_aPlayer[nPlayerID].nSkillPoint = 0;
		// �X�L���Q�[�W�̕ύX
		SetSpGageDestSkillPoint(g_aPlayer[nPlayerID].nSkillPoint, (PLAYER_CONTROL)nPlayerID);
		// �o�g����Ԃ��X�L���ɂ���
		SetBattleState(BATTLESTATE_SKILL);

		//if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
		//{  // �U�����s�����v���C���[�������ɂ���
		//	switch (g_aPlayer[nPlayerID].type)
		//	{
		//	case PLAYER_TYPE_BRAVE:
		//		// �X�L���G�t�F�N�g���g�p
		//		//SetTextureAnim(D3DXVECTOR3(0.0f, 100.0f, 0.0f), TEXANIM_RAIZIN_R);
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_R);
		//		break;
		//	case PLAYER_TYPE_DEVIL:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
		//		break;
		//	case PLAYER_TYPE_KING:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
		//		break;
		//	case PLAYER_TYPE_PEOPLE:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
		//		break;
		//	case PLAYER_TYPE_GOD:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
		//		break;
		//	}

		//}
		//else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
		//{  // �U�����s�����v���C���[���E���ɂ���
		//	switch (g_aPlayer[nPlayerID].type)
		//	{
		//	case PLAYER_TYPE_BRAVE:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_L);
		//		break;
		//	case PLAYER_TYPE_DEVIL:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
		//		break;
		//	case PLAYER_TYPE_KING:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
		//		break;
		//	case PLAYER_TYPE_PEOPLE:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
		//		break;
		//	case PLAYER_TYPE_GOD:
		//		// �X�L���G�t�F�N�g���g�p
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
		//		break;
		//	}
		//}

		switch (g_aPlayer[nPlayerID].type)
		{// �X�L���{�C�X
		case PLAYER_TYPE_BRAVE:
			SelectVolume(SOUND_LABEL_SE_YUSHA_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_DEVIL:
			SelectVolume(SOUND_LABEL_SE_MAOU_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_KING:
			SelectVolume(SOUND_LABEL_SE_OU_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_PEOPLE:
			SelectVolume(SOUND_LABEL_HEIMIN_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_GOD:
			SelectVolume(SOUND_LABEL_GOD_004_SE, 0.8f);
			break;
		}
	}

	return bSkill;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CollisionMove(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // ��������Ȃ��ꍇ

			float fIDPlayerMoveX = g_aPlayer[nPlayerID].move.x;
			float fCntPlayerMoveX = g_aPlayer[nCntPlayer].move.x;

			if (fIDPlayerMoveX < 0)
			{
				fIDPlayerMoveX *= -1.0f;
			}
			if (fCntPlayerMoveX < 0)
			{
				fCntPlayerMoveX *= -1.0f;
			}

			D3DXVECTOR3 posID;
			posID.x = g_aPlayer[nPlayerID].pos.x;
			posID.y = g_aPlayer[nPlayerID].pos.y + g_aPlayer[nPlayerID].fHeight / 2.0f;
			posID.z = g_aPlayer[nPlayerID].pos.z;

			D3DXVECTOR3 posCnt;
			posCnt.x = g_aPlayer[nCntPlayer].pos.x;
			posCnt.y = g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight / 2.0f;
			posCnt.z = g_aPlayer[nCntPlayer].pos.z;

			float fLength = sqrtf((posID.x - posCnt.x) * (posID.x - posCnt.x)
				+ (posID.y - posCnt.y) * (posID.y - posCnt.y));

#if 0
			if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false
				&& g_aPlayer[nPlayerID].bBoolOld[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBoolOld[PLAYER_BOOL_JUMP] == false)
			{
				if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius
					&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius
					&& g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
					&& g_aPlayer[nPlayerID].posOld.y >= g_aPlayer[nCntPlayer].posOld.y + g_aPlayer[nCntPlayer].fHeight)
				{
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
						if (g_aPlayer[nPlayerID].pos.x > g_aPlayer[nCntPlayer].pos.x)
						{ // ID�v���C���[���E���ɂ���ꍇ
							g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius - g_aPlayer[nPlayerID].fCollisionRadius;
						}
						else
						{ // �����ɂ���ꍇ
							g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius + g_aPlayer[nPlayerID].fCollisionRadius;
						}
					}
					else
					{ //Cnt�v���C���[�̈ړ��ʂ̕����傫���ꍇ
						if (g_aPlayer[nPlayerID].pos.x < g_aPlayer[nCntPlayer].pos.x)
						{ // Cnt�v���C���[���E���ɂ���ꍇ
							g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nPlayerID].fCollisionRadius - g_aPlayer[nCntPlayer].fCollisionRadius;
						}
						else
						{ // �����ɂ���ꍇ
							g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius;
						}
					}
				}
				else if (g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
					&& g_aPlayer[nPlayerID].pos.y + g_aPlayer[nCntPlayer].fHeight > g_aPlayer[nCntPlayer].pos.y)
				{ // Y���͈͓��i���E����p
					if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius
						&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius)
					{ // X���͈͓�
						if (fIDPlayerMoveX > fCntPlayerMoveX)
						{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
							if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
							{ // ID�v���C���[���E���ɂ���ꍇ
								g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius - g_aPlayer[nPlayerID].fCollisionRadius;
							}
							else
							{ // �����ɂ���ꍇ
								g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius + g_aPlayer[nPlayerID].fCollisionRadius;
							}
						}
						else
						{ //Cnt�v���C���[�̈ړ��ʂ̕����傫���ꍇ
							if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
							{ // Cnt�v���C���[���E���ɂ���ꍇ
								g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nPlayerID].fCollisionRadius - g_aPlayer[nCntPlayer].fCollisionRadius;
							}
							else
							{ // �����ɂ���ꍇ
								g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius;
							}
						}
					}
				}
			}
#endif
			if (fLength < g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius)
			{ // �͈͓�
				if (fIDPlayerMoveX > 0.0f && fCntPlayerMoveX > 0.0f)
				{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
					D3DXVECTOR3 posCenter;

					// �����蔻��̒��S�ʒu
					posCenter = (posID + posCnt) / 2.0f;

					float fAngle = atan2f((posID.x - posCnt.x), (posID.y - posCnt.y));

					g_aPlayer[nPlayerID].pos = posCenter + D3DXVECTOR3(sinf(fAngle), cosf(fAngle), 0.0f) * (g_aPlayer[nPlayerID].fCollisionRadius);
					g_aPlayer[nPlayerID].pos.y -= g_aPlayer[nPlayerID].fHeight / 2.0f;


					float fAngle2 = atan2f((posCnt.x - posID.x), (posCnt.y - posID.y));

					g_aPlayer[nCntPlayer].pos = posCenter + D3DXVECTOR3(sinf(fAngle2), cosf(fAngle2), 0.0f) * (g_aPlayer[nCntPlayer].fCollisionRadius);
					g_aPlayer[nCntPlayer].pos.y -= g_aPlayer[nCntPlayer].fHeight / 2.0f;

					// �I�u�W�F�N�g�ƃ��b�V���t�B�[���h�����蔻��
					CollisionMeshBattleField(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, g_aPlayer[nCntPlayer].fRadius);
				}
				else if (fIDPlayerMoveX < fCntPlayerMoveX)
				{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
					float fAngle = atan2f((posID.x - posCnt.x), (posID.y - posCnt.y));

					g_aPlayer[nPlayerID].pos = posCnt + D3DXVECTOR3(sinf(fAngle), cosf(fAngle), 0.0f) * (g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius);
					g_aPlayer[nPlayerID].pos.y -= g_aPlayer[nPlayerID].fHeight / 2.0f;

				}

			}

#if 0
			if (g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
				&& g_aPlayer[nPlayerID].pos.y + g_aPlayer[nCntPlayer].fHeight > g_aPlayer[nCntPlayer].pos.y)
			{ // Y���͈͓��i���E����p
				if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fRadius
					&& g_aPlayer[nPlayerID].posOld.x + g_aPlayer[nPlayerID].fRadius <= g_aPlayer[nCntPlayer].posOld.x - g_aPlayer[nCntPlayer].fRadius)
				{ // ������
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
						g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fRadius + g_aPlayer[nPlayerID].fRadius;
						// �ړ��ʂ�ύX
						g_aPlayer[nCntPlayer].move.x = g_aPlayer[nPlayerID].move.x;
					}
					else
					{ //Cnt�v���C���[�̈ړ��ʂ̕����傫���ꍇ
						g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fRadius + g_aPlayer[nCntPlayer].fRadius;
						// �ړ��ʂ�ύX
						g_aPlayer[nPlayerID].move.x = g_aPlayer[nCntPlayer].move.x;
					}
				}
				else if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fRadius
					&& g_aPlayer[nPlayerID].posOld.x - g_aPlayer[nPlayerID].fRadius >= g_aPlayer[nCntPlayer].posOld.x + g_aPlayer[nCntPlayer].fRadius)
				{ // �E����
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//ID�̃v���C���[�̈ړ��ʂ̕����傫���ꍇ
						g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fRadius - g_aPlayer[nPlayerID].fRadius;
						// �ړ��ʂ�ύX
						g_aPlayer[nCntPlayer].move.x = g_aPlayer[nPlayerID].move.x;
					}
					else
					{ //Cnt�v���C���[�̈ړ��ʂ̕����傫���ꍇ
						g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fRadius + g_aPlayer[nCntPlayer].fRadius;
						// �ړ��ʂ�ύX
						g_aPlayer[nPlayerID].move.x = g_aPlayer[nCntPlayer].move.x;
					}
				}
			}
#endif
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���[�V����txt�f�[�^�̓ǂݍ���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadMotion(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	FILE *pFileInFile;
	char cLine[MAX_LOAD_LINE];			// 1�s�̈ꎞ�I�ǂݍ���
	char cData[MAX_LOAD_LINE];			// �ꎞ�I�ǂݍ���

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;
	D3DXMATERIAL *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	pFile = fopen(PLAYER_MOTION_LOADTXT_NAME, "r"); // �t�@�C�����J��

	if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
	{ // �t�@�C�����J�����ۂ̏���
		while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
		{
			sscanf(cLine, "%s", cData);
			if (strcmp(cData, "MOTION_FILENAME") == 0)
			{
				int nCntModel = 0;
				int nCntMotion = 0;			// ���[�V������

				sscanf(cLine, "%s %s %s", cData, cData, cData);

				pFileInFile = fopen(cData, "r"); // �t�@�C�����J��

				if (pFileInFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
				{ // �t�@�C�����J�����ۂ̏���ss
					while (fgets(cLine, MAX_LOAD_LINE, pFileInFile) != NULL)
					{
						sscanf(cLine, "%s", cData);
						if (strcmp(cData, "NUM_MODEL") == 0)
						{
							sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].nModelParts);
						}
						else if (strcmp(cData, "MODEL_FILENAME") == 0)
						{
							sscanf(cLine, "%s %s %s", cData, cData, cData);

							D3DXLoadMeshFromX(cData,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat,
								NULL,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh);

							// �}�e���A���f�[�^�ւ̃|�C���^���擾
							pMat = (D3DXMATERIAL*)g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat->GetBufferPointer();

							g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat];

							for (int nCntMat = 0; nCntMat < (int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat; nCntMat++)
							{
								g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntMat] = NULL;
								if (pMat[nCntMat].pTextureFilename != NULL)
								{
									D3DXCreateTextureFromFile(pDevice,
										pMat[nCntMat].pTextureFilename,
										&g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntMat]);
								}
							}
							nCntModel++;
						}
						else if (strcmp(cData, "CHARACTERSET") == 0)
						{
							int nCntParts = 0;

							while (strcmp(cData, "END_CHARACTERSET") != 0)
							{
								fgets(cLine, MAX_LOAD_LINE, pFileInFile);

								sscanf(cLine, "%s", cData);

								if (strcmp(cData, "MOVE") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fMoveSpeed);
								}
								else if (strcmp(cData, "JUMP") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fJampMove);
								}
								else if (strcmp(cData, "RADIUS") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fRadius);
								}
								else if (strcmp(cData, "HEIGHT") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fHeight);
								}
								else if (strcmp(cData, "NUM_PARTS") == 0)
								{
									sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].nModelParts);
								}
								else if (strcmp(cData, "PARTSSET") == 0)
								{
									int nIndex = 0;
									while (strcmp(cData, "END_PARTSSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "INDEX") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nIndex);

											g_aPlayerType[nCntType].aModel[nCntParts].nModelType = nIndex;
										}
										else if (strcmp(cData, "PARENT") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].nIdxModelParent);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].pos.x,
												&g_aPlayerType[nCntType].aModel[nCntParts].pos.y,
												&g_aPlayerType[nCntType].aModel[nCntParts].pos.z);
										}
										else if (strcmp(cData, "ROT") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].rot.x,
												&g_aPlayerType[nCntType].aModel[nCntParts].rot.y,
												&g_aPlayerType[nCntType].aModel[nCntParts].rot.z);
										}
									}
									nCntParts++;
								}
								else if (strcmp(cData, "DAMAGE") == 0)
								{
									sscanf(cLine, "%s %s %f %f", cData, cData, &g_aPlayerType[nCntType].fDamage, &g_aPlayerType[nCntType].fKnockBack);
								}
								else if (strcmp(cData, "COLLISIONSET") == 0)
								{
									int nPartsId;
									D3DXVECTOR3 pos;
									float fRadius;

									while (strcmp(cData, "END_COLLISIONSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "PARTSID") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nPartsId);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
										}
										else if (strcmp(cData, "RADIUS") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fRadius);
										}
									}
									// �����蔻���ݒ�
									SetCollisionDefense(nCntType, nPartsId, pos, fRadius);
								}


							}
						}
						else if (strcmp(cData, "MOTIONSET") == 0)
						{
							int nCntKey = 0;
							while (strcmp(cData, "END_MOTIONSET") != 0)
							{
								fgets(cLine, MAX_LOAD_LINE, pFileInFile);
								sscanf(cLine, "%s", cData);

								if (strcmp(cData, "LOOP") == 0)
								{
									int nLoop;
									sscanf(cLine, "%s %s %d", cData, cData, &nLoop);
									if (nLoop == 0)
									{
										g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = false;
									}
									else
									{
										g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = true;
									}
								}
								else if (strcmp(cData, "NUM_KEY") == 0)
								{
									sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].nNumKey);
								}
								else if (strcmp(cData, "KEYSET") == 0)
								{
									int nCntParts = 0;
									while (strcmp(cData, "END_KEYSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].nFrame);
										}
										else if (strcmp(cData, "KEY") == 0)
										{
											while (strcmp(cData, "END_KEY") != 0)
											{
												fgets(cLine, MAX_LOAD_LINE, pFileInFile);
												sscanf(cLine, "%s", cData);
												if (strcmp(cData, "POS") == 0)
												{
													sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.x,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.y,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.z);
												}
												else if (strcmp(cData, "ROT") == 0)
												{
													sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.x,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.y,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.z);
												}
											}
											nCntParts++;
										}
									}
									nCntKey++;
								}
								else if (strcmp(cData, "COLLISIONSET") == 0)
								{
									int nPartsId, nFrameS, nFrameE, nDamage;
									D3DXVECTOR3 pos;
									float fRadius, fDistance;

									fDistance = 0.0f;

									while (strcmp(cData, "END_COLLISIONSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "PARTSID") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nPartsId);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
										}
										else if (strcmp(cData, "RADIUS") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fRadius);
										}
										else if (strcmp(cData, "START_FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nFrameS);
										}
										else if (strcmp(cData, "END_FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nFrameE);
										}
										else if (strcmp(cData, "DAMAGE") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nDamage);
										}
										else if (strcmp(cData, "DISTANCE") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fDistance);
										}
									}

									// �R���W���� = �p�[�c�ԍ�,x,y,z,���a,���� �J�n�t���[�� �I���t���[��
									//sscanf(cLine, "%s %s %d %f %f %f %f %d %d", cData, cData, &nPartsId, &pos.x, &pos.y, &pos.z,&fRadius, &nFrameS, &nFrameE);

									// �����蔻���ݒ�
									SetCollisionAttack(nCntType, nCntMotion, nPartsId, pos, fRadius, nFrameS, nFrameE, nDamage, fDistance);
								}
							}
							nCntMotion++;
						}
					}
					fclose(pFileInFile); // �t�@�C�������

										 // ���f���̃f�[�^��i�߂�
					nCntType++;
				}
				else
				{ // �t�@�C�����J���Ȃ������ۂ̏���

				}

			}
			else if (strcmp(cData, "PLAYERSET") == 0)
			{
				PLAYER_TYPE type;
				D3DXVECTOR3 pos;
				D3DXVECTOR3 rot;

				while (strcmp(cData, "END_PLAYERSET") != 0)
				{
					fgets(cLine, MAX_LOAD_LINE, pFile);
					sscanf(cLine, "%s", cData);

					if (strcmp(cData, "TYPE") == 0)
					{
						sscanf(cLine, "%s %s %d", cData, cData, &type);
					}
					else if (strcmp(cData, "POS") == 0)
					{
						sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
					}
					else if (strcmp(cData, "ROT") == 0)
					{
						sscanf(cLine, "%s %s %f %f %f", cData, cData, &rot.x, &rot.y, &rot.z);
					}
				}
				SetPlayerInfo(pos, rot, type);
			}
		}
		fclose(pFile); // �t�@�C�������
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �U������ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCollisionAttack(int nPlayerType, int nMotionType, int nPartsId, D3DXVECTOR3 pos, float fRadius, int nFrameS, int nFrameE, int nDamage, float fDistance)
{
	for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
	{
		if (!g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].bUse)
		{
			// �e�p�[�c��ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nPartsId = nPartsId;
			// �ʒu��ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].pos = pos;
			// ���a��ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fRadius = fRadius;
			// �J�n�t���[����ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nFrameS = nFrameS;
			// �I���t���[����ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nFrameE = nFrameE;
			// �_���[�W�ʂ�ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nDamage = nDamage;
			// �U��Hit���̈ړ��ʂ�ݒ�
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fDistance = fDistance;

			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].bUse = true;

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// �f�o�b�O�p�̃X�t�B�A�𐶐�
				g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nSpherID[nCntPlayer]
					= SetSphere(g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].pos, g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fRadius,
						MESHSPHERE_TYPE_ATTACK, true);
			}
#endif // DEBUG_SPHERE
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �h�䔻��ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCollisionDefense(int nPlayerType, int nPartsId, D3DXVECTOR3 pos, float fRadius)
{
	for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
	{
		if (!g_aPlayerType[nPlayerType].collisionD[nCntCollision].bUse)
		{
			// �e�p�[�c��ݒ�
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].nPartsId = nPartsId;
			// �ʒu��ݒ�
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].pos = pos;
			// ���a��ݒ�
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].fRadius = fRadius;

			g_aPlayerType[nPlayerType].collisionD[nCntCollision].bUse = true;

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// �f�o�b�O�p�̃X�t�B�A�𐶐�
				g_aPlayerType[nPlayerType].collisionD[nCntCollision].nSpherID[nCntPlayer]
					= SetSphere(g_aPlayerType[nPlayerType].collisionD[nCntCollision].pos, g_aPlayerType[nPlayerType].collisionD[nCntCollision].fRadius,
						MESHSPHERE_TYPE_DEFENSE, true);
			}
#endif // DEBUG_SPHERE
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �ړ��m�F����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckMove(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer)
		{ // �����ȊO�̃v���C���[�̏ꍇ
		  // �����Ƒ��̃v���C���[�Ƃ̋������Z�o
			float fWidth = (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].move.x) - g_aPlayer[nCntPlayer].pos.x;
			if (fWidth < 0)
			{
				fWidth *= -1;
			}

			if (fWidth > g_nMoveRimit)
			{ // ���������������𒴂���ꍇ�ړ��ʂ�0�ɂ���
				g_aPlayer[nPlayerID].move.x = 0.0f;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �ړ��\�͈͊m�F����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckMoveArea(int nPlayerID)
{
	// �ړ��\�͈͂̏ꏊ�ɂ��邩�ǂ���
	for (int nCntArea = 0; nCntArea < PLAYER_SIDE_MAX; nCntArea++)
	{
		g_aPlayer[nPlayerID].bAreaLimit[nCntArea] = false;
	}

	if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < PLAYER_MOVE_LIMIT_LEFT + 10.0f)
	{
		g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_LEFT] = true;
	}
	else if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > PLAYER_MOVE_LIMIT_RIGHT - 10.0f)
	{
		g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_RIGHT] = true;
	}

	if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < PLAYER_MOVE_LIMIT_LEFT)
	{
		g_aPlayer[nPlayerID].pos.x = PLAYER_MOVE_LIMIT_LEFT + g_aPlayer[nPlayerID].fCollisionRadius;
	}
	else if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > PLAYER_MOVE_LIMIT_RIGHT)
	{
		g_aPlayer[nPlayerID].pos.x = PLAYER_MOVE_LIMIT_RIGHT - g_aPlayer[nPlayerID].fCollisionRadius;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �����m�F����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckRot(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == false
			&& g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] == false)
		{ // �����ȊO�̃v���C���[�̏ꍇ
			if (g_aPlayer[nPlayerID].pos.x > g_aPlayer[nCntPlayer].pos.x)
			{ // ������
				g_aPlayer[nPlayerID].side = PLAYER_SIDE_RIGHT;
			}
			else
			{ // �E����
				g_aPlayer[nPlayerID].side = PLAYER_SIDE_LEFT;
			}
		}
	}

	if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
	{ // ������
		g_aPlayer[nPlayerID].rot.y = (D3DX_PI / 4) * 2;
	}
	else
	{ // �E����
		g_aPlayer[nPlayerID].rot.y = -(D3DX_PI / 4) * 2;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �K�[�h�m�F����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckGuard(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer)
		{ // �����ȊO�̃v���C���[�̏ꍇ
			if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
			{ // ���肪�E�ɂ���ꍇ
				if (GetController((PLAYER_CONTROL)nPlayerID, PLAYER_CONTROLLER_LEFT))
				{ // ������
					//if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
					//{ // �������W�����v���ꍇ
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					//else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true
					//	&& g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == true)
					//{ // ��������������Ⴊ�ݒ��̏ꍇ
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					//else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == false
					//	&& g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == false)
					//{ // ��������������Ⴊ�ݒ��łȂ��ꍇ
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
				}
			}
			else
			{ // ���肪���ɂ���ꍇ
				if (GetController((PLAYER_CONTROL)nPlayerID, PLAYER_CONTROLLER_RIGHT))
				{ // �E����
					g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
				}
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �ړ������擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetMoveRimit(void)
{
	return g_nMoveRimit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �v���C���[�̃X�e�[�^�X���ǂݍ���
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadPlayerStatus(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1�s�̈ꎞ�I�ǂݍ���
	char cData[MAX_LOAD_LINE];			// �ꎞ�I�ǂݍ���

	int nData = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1P�̏ꍇ
			pFile = fopen(LOAD_TEXT_1P, "r"); // �t�@�C�����J��
		}
		else
		{ // 2P�̏ꍇ
			pFile = fopen(LOAD_TEXT_2P, "r"); // �t�@�C�����J��
		}

		if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
		{ // �t�@�C�����J�����ۂ̏���
			while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
			{
				sscanf(cLine, "%s", cData);
				if (strcmp(cData, "�L����") == 0)
				{ // �L�����̏ꍇ
					sscanf(cLine, "%s %d", cData, &nData);
					// �^�C�v��ݒ肷��
					g_aPlayer[nCntPlayer].type = (PLAYER_TYPE)nData;
				}
				else if (strcmp(cData, "�U����") == 0)
				{ // �U���͂̏ꍇ
					sscanf(cLine, "%s %d", cData, &nData);
					// �U�������N��ݒ肷��
					g_aPlayer[nCntPlayer].atkRank = (PLAYER_ATTACK_RANK)nData;
				}
				else if (strcmp(cData, "�h���") == 0)
				{ // �h��͂̏ꍇ
					sscanf(cLine, "%s %d", cData, &nData);
					// �h�䃉���N��ݒ肷��
					g_aPlayer[nCntPlayer].defRank = (PLAYER_DEFENSE_RANK)nData;
				}
				else if (strcmp(cData, "�񕜗�") == 0)
				{ // �񕜗͂̏ꍇ
					sscanf(cLine, "%s %d", cData, &nData);
					// ���C�t�̉񕜗ʂ�ݒ�
					g_aPlayer[nCntPlayer].nRecovery = g_nRecoveryRank[nData];
				}
			}

			// �v���C���[���Đݒ肷��
			DeletShadow(g_aPlayer[nCntPlayer].nIdyShadow);
			g_aPlayer[nCntPlayer].bUse = false;
			SetPlayer(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot, g_aPlayer[nCntPlayer].type);
			fclose(pFile); // �t�@�C�������
		}
	}
}

#if DEBUG_SPHERE
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �f�o�b�O�p�h�䔻��X�t�B�A�̍X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerDebugDeffSphereUpdate(int nPlayerID)
{
	// �f�o�b�O�p�̃X�t�B�A���\���ɂ���(�h��
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
			{
				if (g_aPlayer[nPlayerID].type == nCntType)
				{
					SetDispSphere(g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nPlayerID], true);
				}
				else
				{
					SetDispSphere(g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nPlayerID], false);
				}
			}
		}
	}

	// �f�o�b�O�X�t�B�A�ړ�����
	for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
	{

		if (g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].bUse == true)
		{
			D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// �v�Z�p�}�g���b�N�X

																// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorldD);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.y,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.x,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.z);

			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.x,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.y,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.z);

			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

			// �e�̃��[���h�}�g���b�N�X�𔽉f
			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
				&g_aPlayer[nPlayerID].aModel[g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

			// �f�o�b�O�p�̃X�t�B�A�ړ�����
			SetPositionSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].nSpherID[nPlayerID],
				D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43));
		}
	}
}
#endif // DEBUG_SPHERE

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����󋵎擾
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetController(PLAYER_CONTROL control, PLAYER_CONTROLLER Controller)
{
	bool bButton = false;
	switch (control)
	{
		// 1P�̑���
	case PLAYER_CONTROL_1P:
		switch (Controller)
		{
		case PLAYER_CONTROLLER_LEFT:	// ������
			if (GetKeyboardPress(DIK_A) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P,POV_LEFT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT:	// �E����
			if (GetKeyboardPress(DIK_D) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_RIGHT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_UP:	// �����
			if (GetKeyboardTrigger(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_LEFT_UP:	// �������
			if ((GetKeyboardTrigger(DIK_W) == true && GetKeyboardPress(DIK_A) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_LEFT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT_UP: // �E�����
			if ((GetKeyboardTrigger(DIK_W) == true && GetKeyboardPress(DIK_D) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_RIGHT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_DOWN:	// ������
			if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_SMALL:	// ��U������
			if (GetKeyboardTrigger(DIK_G) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_BIG:	// ���U������
			if (GetKeyboardTrigger(DIK_H) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_B) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_SKILL:	// �X�L������
			if (GetKeyboardTrigger(DIK_Y) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_Y) == true)
			{
				bButton = true;
			}
			break;
		}
		break;
		// 2P�̑���
	case PLAYER_CONTROL_2P:
		switch (Controller)
		{
		case PLAYER_CONTROLLER_LEFT:	// ������
			if (GetKeyboardPress(DIK_LEFT) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_LEFT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT:	// �E����
			if (GetKeyboardPress(DIK_RIGHT) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_RIGHT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_UP:	// �����
			if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_LEFT_UP:	// �������
			if ((GetKeyboardTrigger(DIK_UP) == true && GetKeyboardPress(DIK_LEFT) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_LEFT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT_UP: // �E�����
			if ((GetKeyboardTrigger(DIK_UP) == true && GetKeyboardPress(DIK_RIGHT) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_RIGHT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_DOWN:	// ������
			if (GetKeyboardPress(DIK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_SMALL:	// ��U������
			if (GetKeyboardTrigger(DIK_DECIMAL) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_BIG:	// ���U������
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_NUMPADENTER) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_B) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_SKILL:	// �X�L������
			if (GetKeyboardTrigger(DIK_ADD) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_Y) == true)
			{
				bButton = true;
			}
			break;
		}
		break;
	}
	return bButton;
}

//=============================================================================
// �v���C���[�̗͂ƃX�L���|�C���g�ۑ�����
//=============================================================================
void PlayerSaveHpSkill(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char *cTextName;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1P�̏ꍇ
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "w"); // �t�@�C�����J��
			cTextName = PLAYER_1P_HP_SKILL_TXT_NAME;
		}
		else
		{ // 2P�̏ꍇ
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "w"); // �t�@�C�����J��
			cTextName = PLAYER_2P_HP_SKILL_TXT_NAME;
		}

		if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
		{ // �t�@�C�����J�����ۂ̏���
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# �wHP�ESkillPoint���x�X�N���v�g�t�@�C�� [%s]\n", cTextName);
			fprintf(pFile, "# Author : �� �a��\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n\n");

			fprintf(pFile, "\n");
			fprintf(pFile, "#------------------------------------------------------------------------------\n");
			fprintf(pFile, "# �v���C���[%d ���\n", nCntPlayer + 1);
			fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

			fprintf(pFile, "HP = %d \n", g_aPlayer[nCntPlayer].nLife);
			fprintf(pFile, "SKILL = %d \n", g_aPlayer[nCntPlayer].nSkillPoint);

			fclose(pFile); // �t�@�C�������
		}
	}
}

//=============================================================================
// �v���C���[�̗͂ƃX�L���|�C���g�ۑ�����(�����ݒ�
//=============================================================================
void PlayerSaveHpSkillInit(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char *cTextName;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1P�̏ꍇ
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "w"); // �t�@�C�����J��
			cTextName = PLAYER_1P_HP_SKILL_TXT_NAME;
		}
		else
		{ // 2P�̏ꍇ
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "w"); // �t�@�C�����J��
			cTextName = PLAYER_2P_HP_SKILL_TXT_NAME;
		}

		if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
		{ // �t�@�C�����J�����ۂ̏���
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# �wHP�ESkillPoint���x�X�N���v�g�t�@�C�� [%s]\n", cTextName);
			fprintf(pFile, "# Author : �� �a��\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n\n");

			fprintf(pFile, "\n");
			fprintf(pFile, "#------------------------------------------------------------------------------\n");
			fprintf(pFile, "# �v���C���[%d ���\n", nCntPlayer + 1);
			fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

			fprintf(pFile, "HP = %d \n", PLAYER_LIFE);
			fprintf(pFile, "SKILL = %d \n", PLAYER_SKILL);

			fclose(pFile); // �t�@�C�������
		}
	}
}
//=============================================================================
// �v���C���[�̗͂ƃX�L���|�C���g�ǂݍ��ݏ���
//=============================================================================
void PlayerLoadHpSkill(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1�s�̈ꎞ�I�ǂݍ���
	char cData[MAX_LOAD_LINE];			// �ꎞ�I�ǂݍ���

	int nData = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1P�̏ꍇ
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "r"); // �t�@�C�����J��
		}
		else
		{ // 2P�̏ꍇ
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "r"); // �t�@�C�����J��
		}

		if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
		{ // �t�@�C�����J�����ۂ̏���
			while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
			{
				sscanf(cLine, "%s", cData);
				if (strcmp(cData, "HP") == 0)
				{ // HP�̏ꍇ
					sscanf(cLine, "%s %s %d", cData, cData, &nData);
					// HP��ݒ肷��
					g_aPlayer[nCntPlayer].nLife = nData;
					// HP�Q�[�W�X�V
					SetHpGageLife(g_aPlayer[nCntPlayer].nLife, (PLAYER_CONTROL)nCntPlayer);
				}
				else if (strcmp(cData, "SKILL") == 0)
				{ // SKILL�̏ꍇ
					sscanf(cLine, "%s %s %d", cData, cData, &nData);
					// SKILL_POINT��ݒ肷��
					g_aPlayer[nCntPlayer].nSkillPoint = nData;
					// SKILL�Q�[�W�X�V
					SetSpGageSkillPoint(g_aPlayer[nCntPlayer].nSkillPoint, (PLAYER_CONTROL)nCntPlayer);
				}
			}
			fclose(pFile); // �t�@�C�������
		}
	}
}

//=============================================================================
// �퓬���ʕ\��
//=============================================================================
void PlayerBattleResultSave(int nPlayerID)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;

	pFile = fopen(SAVE_RESULT_TEXT, "w"); // �t�@�C�����J��

	if (pFile != NULL) // pFile��NULL(�󔒁j�ł͂Ȃ��Ƃ���^
	{ // �t�@�C�����J�����ۂ̏���
		fprintf(pFile, "%d \n", (nPlayerID + 1));
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �����v���C���[���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �w�퓬���ʁx�X�N���v�g�t�@�C�� [%s]\n", SAVE_RESULT_TEXT);
		fprintf(pFile, "# Author : �� �a��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT			# ���̍s�͐�Ώ����Ȃ����ƁI\n\n");

		fclose(pFile); // �t�@�C�������
	}

}