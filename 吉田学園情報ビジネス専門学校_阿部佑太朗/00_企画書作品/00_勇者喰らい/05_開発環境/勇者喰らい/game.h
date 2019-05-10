#pragma once
//=========================================================================================================//
//
// �|���S���F�v���g�^�C�v�錾 [Scan.h]
// Author : Ryo Sugimoto
//
//=========================================================================================================//
#ifndef _GAME_H_
#define _GAME_H_

#include"model.h"
#include"main.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define	MAX_MAP_CHANGE	(3)			//�}�b�v�o������̐�

#define SPEECH_FLOW	(5)		//��b��1�������ł鎞��
#define SPEECH_STOP	(120)	//��b�ŕ������S�ďo�Ă��玟�̉�b�Ɉڂ�܂ł�F

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_START,		//�G���^�[�҂�
	GAMESTATE_NORMAL,
	GAMESTATE_NORMAL1,		//�L�����X�e�m�F
	GAMESTATE_END,
	GAMESTATE_PAUSE

}GAMESTATE;

typedef struct
{
	GAMESTATE now;		//���݂̏��
	MODE CHANGE;		//�ς��郂�[�h
	int nCntGameState;	//�J�E���g�p

}GAME;

typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_INVINCBLE,		//���G���
	PLAYERSTATE_DNORMAL,		//���Ⴊ�݌�W�����v����񂵂��ł��Ȃ��̂�h��
	PLAYERSTATE_FALL,			//���蔲�����
	PLAYERSTATE_ATTACK,			//�U����ԁ@�A�Œ�
	PLAYERSTATE_SATTACK,		//�󒆍U����ԁ@�A�Œ�
	PLAYERSTATE_SKYATTACK,		//�U����Ԃւ̈ڍs�@��]��
	PLAYERSTATE_WAIT,			//�U����Ԃւ̑ҋ@�@��]��
	PLAYERSTATE_CATCH,			//�R���܂���
	PLAYERSTATE_CLIMBR,			//�R������Ă�����
	PLAYERSTATE_CLIMBL,			//�R������Ă�����
	PLAYERSTATE_BACK,			//�m�b�N�o�b�N���
	PLAYERSTATE_DOWN,			//���Ⴊ�ݏ��
	PLAYERSTATE_KNOCKBACK,		//�m�b�N�o�b�N���
	PLAYERSTATE_DAMAGE,			//�_���[�W���

}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ��l�̎c���
	D3DXCOLOR col;			// �F
	float fSteep;			//�p�x
	float fSpeed;
	float fRadius;			// ���a(�傫��)
	bool bUse;				// �g�p���Ă��邩�ǂ���

} EFFECT;

typedef enum
{
	ANIMTYPE_COIN = 0,	//�R�C��
	ANIMTYPE_CHECK0,		//�����n�_�X�V
	ANIMTYPE_CHECK1,		//�g�p�ςݕ����n�_
	ANIMTYPE_POWERUP,		//�p���[�A�b�vItem
	ANIMTYPE_HEEL,			//��
	ANIMTYPE_ALLHEEL,		//�S��
	ANIMTYPE_CLOCK,			//���v
	ANIMTYPE_BOARD,		//�Ŕ�
	ANIMTYPE_MESSAGE,	//�Ŕ���o�郁�b�Z�[�W
	ANIMTYPE_NONE,		//�X�N���[�����Ȃ�����

}ANIMTYPE;
//typedef enum
//{//�A�j���[�V�����̎g�p���
//	ANIMATION_NORMAL = 0,
//	ANIMATION_LOOP,
//	ANIMATION_PLAYER,			//�v���C���[�̃p�^�[���ɉ����ĕύX
//	ANIMATION_MAX,
//
//}ANIMATION;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 initpos;//�����ʒu
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 col;	//�F
	int nLengthX;		//X�̒���
	int nLengthY;		//Y�̒���
	int nCntAnim;		//Animation�̃J�E���g
	int nPtnAnim;		//�w�肳�ꂽ���W�ŕ\��
	int nPtnHeight;		//�摜�̏c�̕�����
	int nPtnWide;		//�摜�̉��̕�����
	int nPtnSpeed;		//Animation���x
	int nType;			//�摜�̎w��
	int nCntState;
	ANIMATION anim;		//�A�j���[�V�����̎g����
	ANIMTYPE type;	//���
	bool bUse;
}Animation;

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX	mtxWorldShadow;		//���[���h�}�g���b�N�X
	float		fLengthX;			//����X
	float		fLengthZ;			//����Y
	int			nType;
	bool		bUse;				//�g�p�� or �ҋ@��

}Shadow;

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXCOLOR col;	//�F
	D3DXMATRIX	mtxWorldShadow;		//���[���h�}�g���b�N�X
	float		fLengthX;			//����X
	float		fLengthZ;			//����Y
	int			nType;
	bool		bUse;				//�g�p�� or �ҋ@��

}ZPolygon;

//*****************************************************************************
// �r���{�[�h�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posBillBoord;		//�ʒu
	D3DXVECTOR3 rotBillBoord;		//����
	D3DXMATRIX mtxWorldBillBoord;	//���[���h�}�g���b�N�X
	WINDOWTYPE	ViewType;			//�\�����@
	int			nTexType;			//�摜�̎��
	float		fLengthX;			//����X
	float		fLengthY;			//����Y
	bool bUse;						//�g�p���Ă邩�ǂ���

}BillBoord;

typedef struct
{
	D3DXVECTOR3 Entrance;		//����
	int			nNumber;		//�o���̔ԍ�
	int			nLengthX;		//�͈�X
	int			nLengthZ;		//�͈�Z
	bool		bUse;			//�g�p���Ă邩�ǂ���

}ENEMY_APPEAR;

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@Game
//*********************************************************************************************************//
void InitGame(int nFadeType);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void InitGame0(void);
GAME *GetGameState(void);
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState);
void ButtonKeybord(void);
void ButtonJoypad(void);

//*****************************************************************************
// �v���g�^�C�v�錾�@�n��
//*****************************************************************************
void InitMeshField(char *aMapName);
void BreakMeshField(void);
int CollisionMeshField(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float *fPos, bool bJump, MODEL_SETTING *set);

//*****************************************************************************
// �v���g�^�C�v�錾�@��
//*****************************************************************************
void InitMeshBack(char *aMapName, int nPlus);
void BreakMeshWall(void);
void CollisionMeshWall(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float nLength);
void CollisionVertical(D3DXVECTOR3 *clsPos, D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, int nCntVertical, int nCntCross, int nCntVtx, int nCntWall, float nLength);
void CollisionCross(D3DXVECTOR3 *clsPos, D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, int nCntVertical, int nCntCross, int nCntVtx, int nCntWall, float nLength);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLengthX, float fLengthZ, float fHeight, int nShadow);
void SettingShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLengthX, float fLengthZ, int nNumber);
void BreakShadow(int nNumber);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
int SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nType);
void SettingPolygon(D3DXVECTOR3 pos);
void BreakPolygon(int nNumber);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void UpdateBullet(void);
void UpdateEBullet(int nCntBullet);
void UpdateABullet(int nCntBullet, int nEnemy, float fAtk);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 blown, MODEL_USE use, float fAttack, float fAtkplus, float fRange,
	float fSlip, float fLife, int nCntAtk, int nInvincible, int nType, int nAtkType, int nCntStop, int nCntModel);
void BreakBullet(void);
#endif