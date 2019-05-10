//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �v���C���[���� [player.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_PLAYER						(2)		// �v���C���[�̍ő�l��
#define MAX_PLAYER_PARTS				(20)	// �v���C���[�̍ő�p�[�c��
#define MAX_PLAYER_TEX					(50)	// �v���C���[1�ɑ΂���e�N�X�`���̍ő吔
#define MAX_PLAYER_KEY					(10)	// ���[�V����1�ɑ΂���L�[�t���[���̍ő吔
#define MAX_PLAYER_ATTACK_COLLISION		(20)	// ���[�V����1�ɑ΂���U�������蔻��̐�
#define MAX_PLAYER_DEFENSE_COLLISION	(50)	// ���[�V����1�ɑ΂���h�䓖���蔻��̐�
#define PLAYER_LIFE						(100)	// �v���C���[�̏����̗�
#define PLAYER_MAX_SKILL_POINT			(100)	// �v���C���[�̃X�L���|�C���g�̍ő�l
#define PLAYER_SKILL					(0)		// �v���C���[�̏����X�L���|�C���g

#define DEBUG_SPHERE					(0)		// �f�o�b�O�p�����g�p���邩�ǂ���

// �v���C���[�ړ�����
#define PLAYER_MOVE_RIMIT			(350)		// �v���C���[�̗�����鋗��
#define PLAYER_MOVE_LIMIT_LEFT		(-400.0f)	// �v���C���[���ړ��ł��鍶���̌��E�l
#define PLAYER_MOVE_LIMIT_RIGHT		(400.0f)	// �v���C���[���ړ��ł���E���̌��E�l

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // ����̎��
	PLAYER_CONTROLLER_LEFT = 0,		// ������
	PLAYER_CONTROLLER_RIGHT,		// �E����
	PLAYER_CONTROLLER_UP,			// �����
	PLAYER_CONTROLLER_LEFT_UP,		// �������
	PLAYER_CONTROLLER_RIGHT_UP,		// �E�����
	PLAYER_CONTROLLER_DOWN,			// ������
	PLAYER_CONTROLLER_ATTACK_SMALL,	// ��U��
	PLAYER_CONTROLLER_ATTACK_BIG,	// ���U��
	PLAYER_CONTROLLER_SKILL,		// �X�L��
	PLAYER_CONTROLLER_MAX,			// ����
}PLAYER_CONTROLLER;

typedef enum
{ // bool�ϐ��̎��
	PLAYER_BOOL_JUMP = 0,			// �W�����v
	PLAYER_BOOL_SQUAT,				// ���Ⴊ��
	PLAYER_BOOL_LANDING,			// ���n
	PLAYER_BOOL_DAMAGE,				// �_���[�W
	PLAYER_BOOL_BLOW,				// �Ԃ����
	PLAYER_BOOL_GETUP,				// �N���オ��
	PLAYER_BOOL_ATTACK_SMALL,		// ��U��
	PLAYER_BOOL_ATTACK_BIG,			// ���U��
	PLAYER_BOOL_SKILL,				// �X�L��
	PLAYER_BOOL_GUARD,				// �K�[�h
	PLAYER_BOOL_GUARD_HIT,			// �K�[�h������
	PLAYER_BOOL_FRONT,				// �O
	PLAYER_BOOL_BACK,				// ��
	PLAYER_BOOL_MAX
}PLAYER_BOOL;

typedef enum
{ // �v���C���[�̎��
	PLAYER_TYPE_BRAVE = 0,		// �E��
	PLAYER_TYPE_DEVIL,			// ����
	PLAYER_TYPE_KING,			// ���l
	PLAYER_TYPE_PEOPLE,			// ����
	PLAYER_TYPE_GOD,			// �����i�_
	PLAYER_TYPE_MAX,			// ����
}PLAYER_TYPE;

typedef enum
{ // �v���C���[�̏��
	PLAYERSTATE_APPEAR = 0,		// �o�����
	PLAYERSTATE_NORMAL,			// �ʏ���
	PLAYERSTATE_DAMAGE,			// �_���[�W���
	PLAYERSTATE_DOWN,			// �Ԃ���я��
	PLAYERSTATE_GETUP,			// �N���オ����
	PLAYERSTATE_DEATH,			// ���S���
	PLAYERSTATE_INVINCIBLE,		// ���G���
	PLAYERSTATE_MAX				// ����
}PLAYERSTATE;

typedef enum
{ // ����v���C���[
	PLAYER_CONTROL_1P = 0,		// 1P
	PLAYER_CONTROL_2P,			// 2P
	PLAYER_CONTROL_MAX			// ����
}PLAYER_CONTROL;

typedef enum
{ // �E���ǂ���ɂ��邩
	PLAYER_SIDE_RIGHT = 0,		// �E
	PLAYER_SIDE_LEFT,			// ��
	PLAYER_SIDE_MAX				// ����
}PLAYER_SIDE;

typedef enum
{ // �v���C���[�̍U�������N
	PLAYER_ATTACK_RANK_0 = 0,		// ��㏸���
	PLAYER_ATTACK_RANK_1,			// 1�㏸���
	PLAYER_ATTACK_RANK_2,			// 2�㏸���
	PLAYER_ATTACK_RANK_3,			// 3�㏸���
	PLAYER_ATTACK_RANK_MAX			// ����
}PLAYER_ATTACK_RANK;

typedef enum
{ // �v���C���[�̖h�䃉���N
	PLAYER_DEFENSE_RANK_0 = 0,		// ��㏸���
	PLAYER_DEFENSE_RANK_1,			// 1�㏸���
	PLAYER_DEFENSE_RANK_2,			// 2�㏸���
	PLAYER_DEFENSE_RANK_3,			// 3�㏸���
	PLAYER_DEFENSE_RANK_MAX			// ����
}PLAYER_DEFENSE_RANK;

typedef enum
{ // �v���C���[�̉񕜃����N
	PLAYER_RECOVERY_RANK_0 = 0,		// ��㏸���
	PLAYER_RECOVERY_RANK_1,			// 1�㏸���
	PLAYER_RECOVERY_RANK_2,			// 2�㏸���
	PLAYER_RECOVERY_RANK_3,			// 3�㏸���
	PLAYER_RECOVERY_RANK_4,			// 4�㏸���
	PLAYER_RECOVERY_RANK_5,			// 5�㏸���
	PLAYER_RECOVERY_RANK_MAX		// ����
}PLAYER_RECOVERY_RANK;


typedef enum
{ // ���[�V�����̎��
	PLAYER_MOTION_TYPE_NEUTRAL = 0,			// [0]	�j���[�g����
	PLAYER_MOTION_TYPE_NEUTRAL_SQUAT,		// [1]	���Ⴊ�݃j���[�g����
	PLAYER_MOTION_TYPE_WALK,				// [2]	�ړ�
	PLAYER_MOTION_TYPE_GUARD,				// [3]	�K�[�h
	PLAYER_MOTION_TYPE_GUARD_SQUAT,			// [4]	���Ⴊ�݃K�[�h
	PLAYER_MOTION_TYPE_GUARD_AIR,			// [5]	�󒆃K�[�h
	PLAYER_MOTION_TYPE_BLOW,				// [6]	�Ԃ����
	PLAYER_MOTION_TYPE_DAMAGE,				// [7]	�_���[�W
	PLAYER_MOTION_TYPE_DAMAGE_SQUAT,		// [8]	���Ⴊ�݃_���[�W�_���[�W
	PLAYER_MOTION_TYPE_JUMP_FRONT,			// [9]	�W�����v�O
	PLAYER_MOTION_TYPE_JUMP_UP,				// [10]	�W�����v��
	PLAYER_MOTION_TYPE_JUMP_BACK,			// [11]	�W�����v��
	PLAYER_MOTION_TYPE_SQUAT,				// [12]	���Ⴊ��
	PLAYER_MOTION_TYPE_GETUP,				// [13]	�N���オ��
	PLAYER_MOTION_TYPE_LANDING,				// [14]	���n
	PLAYER_MOTION_TYPE_ATTACK_JUMP_SMALL,	// [15]	�W�����v�U��[ �� ]
	PLAYER_MOTION_TYPE_ATTACK_JUMP_BIG,		// [16]	�W�����v�U��[ �� ]
	PLAYER_MOTION_TYPE_ATTACK_SMALL,		// [17]	�U��[ �� ]
	PLAYER_MOTION_TYPE_ATTACK_BIG,			// [18]	�U��[ �� ]
	PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL,	// [19]	���Ⴊ�ݍU��[ �� ]
	PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG,	// [20]	���Ⴊ�ݍU��[ �� ]
	PLAYER_MOTION_TYPE_SKILL,				// [21]	�X�L��
	PLAYER_MOTION_TYPE_FIGHTING_RIGHT,		// [22]	�t�@�C�e�B���O���[�V����(�E
	PLAYER_MOTION_TYPE_FIGHTING_LEFT,		// [23]	�t�@�C�e�B���O���[�V����(��
	PLAYER_MOTION_TYPE_LOSS,				// [24]	�������[�V����
	PLAYER_MOTION_TYPE_WIN,					// [25]	�������[�V����
	PLAYER_MOTION_TYPE_MAX,					// ����
}PLAYER_MOTION_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}PartsKeyPlayer;

typedef struct
{
	int nFrame;									// �L�[�t���[��
	PartsKeyPlayer aPartsKey[MAX_PLAYER_PARTS];	// �p�[�c���Ƃ̃L�[���
}KeyPlayer;

typedef struct
{ // �����蔻��p����
	D3DXVECTOR3 pos;			// �����蔻��̈ʒu
	D3DXVECTOR3 rot;			// �����蔻��̌���
	int nPartsId;				// �����蔻��̐eID
	float fRadius;				// �����蔻��̔��a
	int nFrameS;				// �����蔻��̊J�n�t���[��
	int nFrameE;				// �����蔻��̏I���t���[��
	int nDamage;				// �����蔻��̃_���[�W��
	float fDistance;			// �U��Hit���̈ړ���
	bool bUse;					// �����蔻����g�p���邩�ǂ���

#if DEBUG_SPHERE
	int nSpherID[MAX_PLAYER];	// �f�o�b�O�p�~��ID
#endif // DEBUG_SPHERE

}CollisionSpherePlayer;

typedef struct
{ // ���[�V�������
	bool bLoop;														// ���[�v���邩�ǂ���
	int nNumKey;													// �L�[��
	KeyPlayer aKey[MAX_PLAYER_KEY];									// �L�[���
	CollisionSpherePlayer collisionA[MAX_PLAYER_ATTACK_COLLISION];	// �U������p
	int nAllFrame;													// ���[�V�����S�̂̃t���[����
}MotionPlayer;

typedef struct
{ // ���f���f�[�^
	LPD3DXMESH pMesh;				// ���b�V���i���_�̏W�܂�j���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD nNumMat;					// �}�e���A�����̐�
	LPDIRECT3DTEXTURE9 *pTexture;	// ���f����ɑ΂���e�N�X�`��
#if DEBUG_SPHERE
	int nIDSphere;					// ���̂�ID
#endif // DEBUG_SPHERE
}PlayerModelData;

typedef struct
{ // �v���C���[�̎g�p���f�����
	int nModelType;				// �ǂ̃��f�����g�p���邩
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3	pos;			// �ʒu�i���S���W�j
	D3DXVECTOR3	rot;			// ����
	D3DXVECTOR3	posMotion;		// ���[�V�����ʒu
	D3DXVECTOR3	rotMotion;		// ���[�V��������
	D3DXVECTOR3	posAddMotion;	// ���Z���[�V�����ʒu
	D3DXVECTOR3	rotAddMotion;	// ���Z���[�V��������
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
}PlayerModel;

typedef struct
{ // �v���C���[�̃^�C�v���Ƃ̏��
	int nModelParts;												// �p�[�c��
	float fMoveSpeed;												// �ړ����x
	float fJampMove;												// �W�����v��
	float fRadius;													// ���a
	float fHeight;													// ����
	float fDamage;													// �_���[�W��
	float fKnockBack;												// �m�b�N�o�b�N����
	PlayerModelData	apPlayer[MAX_PLAYER_PARTS] = {};				// ���f���ւ̃|�C���^
	MotionPlayer	aMotion[PLAYER_MOTION_TYPE_MAX];				// ���[�V����
	PlayerModel		aModel[MAX_PLAYER_PARTS];						// �p�[�c���
	CollisionSpherePlayer collisionD[MAX_PLAYER_DEFENSE_COLLISION];	// �h�䔻��p
}PlayerTypeData;

typedef struct
{ // �v���C���[���
	D3DXMATRIX mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3	pos;								// �ʒu
	D3DXVECTOR3	posOld;								// �O��ʒu
	D3DXVECTOR3	rot;								// ����
	D3DXCOLOR col;									// ���C���F
	D3DXCOLOR colSub;								// �T�u�F
	PlayerModel aModel[MAX_PLAYER_PARTS];			// �p�[�c��
	int nModelParts;								// �p�[�c��
	D3DXVECTOR3	move;								// �ړ���
	float fMoveSpeed;								// �ړ����x
	float fJampMove;								// �W�����v��
	float fRadius;									// ���a
	float fHeight;									// ����
	float fCollisionRadius;
	int nIdyShadow;									// �e��ID
	PLAYER_TYPE type;								// �v���C���[�̎��
	int nLife;										// �̗�
	int nSkillPoint;								// �X�L���|�C���g
	int nSkillRank;									// �X�L�������N
	PLAYERSTATE state;								// ���
	int nCounterState;								// �X�e�[�^�X�̃J�E���^�[
	PLAYER_MOTION_TYPE MotionType;					// ���[�V�����̎��
	PLAYER_MOTION_TYPE MotionTypeOld;				// �O��̃��[�V�����̎��
	PLAYER_MOTION_TYPE MotionTypeHit;				// �U���𓖂Ă�
	PLAYER_SIDE side;								// �E���ǂ���ɂ��邩
	float fGravity;									// �d��
	bool bBool[PLAYER_BOOL_MAX];					// �`�F�b�N�p
	bool bBoolOld[PLAYER_BOOL_MAX];					// �O��`�F�b�N�p
	bool bUse;										// �g�p���Ă��邩�ǂ���
	bool bDisp;										// �`�悷�邩�ǂ���
	int nKeyCnt;									// �L�[�J�E���g
	int nFrameCounter;								// �t���[���J�E���^�[
	int nAllFrameCounter;							// �S�̂̃t���[���J�E���^�[
	bool bBlend;									// �u�����h�����ǂ���
	PLAYER_ATTACK_RANK atkRank;						// �U�������N
	PLAYER_DEFENSE_RANK defRank;					// �h�䃉���N
	int nRecovery;									// �񕜗�
	bool bAreaLimit[PLAYER_SIDE_MAX];				// �ړ��\�G���A�̂���ɂ��邩�ǂ���
	bool b2PColor;									// 2PColor���g�p���邩
}Player;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void InitPlayerTypeData(void);
void UninitPlayerTypeData(void);

void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
void SetPlayerInfo(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
Player *GetPlayer(void);
PlayerTypeData *GetPlayerTypeData(void);
void PlayerMotion(int nPlayerID);
void PlayerMotionTypeSet(int nPlayerID);
void PlayerMotionTypeSet(int nPlayerID, PLAYER_MOTION_TYPE motionType);
void PlayerController(PLAYER_CONTROL control);
bool CollisionAttack(int nPlayerID);
bool CollisionSkillAttack(int nPlayerID);
bool SkillAttack(int nPlayerID);
void CollisionMove(int nPlayerID);
void SetCollisionAttack(int nPlayerType, int nMotionType, int nPartsId, D3DXVECTOR3 pos, float fRadius, int nFrameS, int nFrameE, int nDamage, float fDistance);
void SetCollisionDefense(int nPlayerType, int nPartsId, D3DXVECTOR3 pos, float fRadius);
void HitPlayer(D3DXVECTOR3 HitPos, int nPlayerID, int nDamage, float fDistance, bool bigAttack, bool bSkill);
void CheckMove(int nPlayerID);
void CheckMoveArea(int nPlayerID);
void CheckRot(int nPlayerID);
void CheckGuard(int nPlayerID);
void LoadMotion(void);
int GetMoveRimit(void);
bool GetController(PLAYER_CONTROL control, PLAYER_CONTROLLER Controller);
void LoadPlayerStatus(void);
void AddPlayerLife(int nPlayerID, int nLife);
void AddPlayerSkillPoint(int nPlayerID,int nSkillPoint);
void PlayerBattleResultSave(int nPlayerID);

void PlayerSaveHpSkill(void);
void PlayerSaveHpSkillInit(void);
void PlayerLoadHpSkill(void);

#if DEBUG_SPHERE
void PlayerDebugDeffSphereUpdate(int nPlayerID);
#endif // DEBUG_SPHERE

#endif
