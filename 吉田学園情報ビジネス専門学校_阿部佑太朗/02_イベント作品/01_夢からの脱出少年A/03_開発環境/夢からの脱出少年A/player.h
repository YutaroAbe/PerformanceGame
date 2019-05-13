//=============================================================================
//
// �v���C���[���� [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"
//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{// �v���C���[�̏�Ԃ̎��
	PLAYERSTATE_NORMAL = 0,			// �ʏ���
	PLAYERSTATE_DAMAGE,				// �_���[�W���
	PLAYERSTATE_DEATH,				// ���S���
	PLAYERSTATE_END,
	PLAYERSTATE_MAX					// ��Ԃ̑���
}PLAYERSTATE;

typedef enum
{// �v���C���[�̃��[�V�����̎��
	PLAYERMOTIONTYPE_NEUTRAL = 0,	// �j���[�g����
	PLAYERMOTIONTYPE_MOVE,			// �ړ�
	PLAYERMOTIONTYPE_MAX			// ��ނ̑���
}PLAYERMOTIONTYPE;

typedef struct
{// �v���C���[�̃��f���̏��
	LPD3DXMESH		pMesh = NULL;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	*pTex = NULL;	// �e�N�X�`�����ւ̃|�C���^
	D3DMATERIAL9	*pCol = NULL;		// ���݂̐F�ւ̃|�C���^
	D3DMATERIAL9	*pColDef = NULL;	// �f�t�H���g�̐F�ւ̃|�C���^
	DWORD			nNumMat = 0;		// �}�e���A�����̐�
	D3DXMATRIX		mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3		posFarst;			// �����̈ʒu
	D3DXVECTOR3		pos;				// �ʒu
	D3DXVECTOR3		rot;				// ����
	int				nIdxModelParent;	// �e���f���̃C���f�b�N�X
	char			aName[128];			// �ǂݍ��ރ��f���̖��O
} PlayerModel;

typedef struct
{// �v���C���[�̃L�[�̏��
	D3DXVECTOR3	*aPos = NULL;	// �ʒu
	D3DXVECTOR3	*aRot = NULL;	// ����
	int			nNumFrame;		// �X�V����t���[����
} PlayerKey;

typedef struct
{// �v���C���[�̃��[�V�����̏��
	int			nLoop;					// ���[�v���邩�ǂ���[ ���Ȃ� = 0, ���� = 1 ]
	int			nNumKey;				// �L�[�̐�
	PlayerKey	*aPlayerKey = NULL;		// �L�[�̏��
} PlayerMotion;

typedef struct
{// �v���C���[�̏��
	D3DXMATRIX			mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;					// ���݂̈ʒu
	D3DXVECTOR3			posOld;					// �O��̈ʒu
	D3DXVECTOR3			move;					// �ړ���
	D3DXVECTOR3			rot;					// ����
	D3DXVECTOR3			rotDest;				// �ړI�̌���
	D3DXVECTOR3			vtxMin;					// �����蔻��̍ŏ��l
	D3DXVECTOR3			vtxMax;					// �����蔻��̍ő�l
	int					nNumModel;				// ���f����
	PlayerModel			*aPlayerModel = NULL;	// ���f���̏��ւ̃|�C���^
	PlayerMotion		aPlayerMotion[PLAYERMOTIONTYPE_MAX];	// ���[�V�����̏��
	PLAYERMOTIONTYPE	motionType;				// ���݂̃��[�V�����̎��
	int					nKey;					// ���݂̃L�[
	int					nIdxShadow;				// �e�̔ԍ�
	int					nLife;					// �̗�
	int					nCntFrame;				// �o�߃t���[��
	int					nMaxCntFrame;			// �����o�߃t���[��
	D3DXVECTOR3 Destrot;						// �ړI�̊p�x
	int					nCounterState = 0;		//��ԊǗ��̃J�E���^�[
	PLAYERSTATE			state;					// ���
	int					nCntState;				// ��ԊǗ��̃J�E���^�[
	int					nCntEffect;				// �G�t�F�N�g�̃J�E���^�[
	bool				bJump;					// �W�����v�����ǂ���
	bool				bDisp;					// �o�����Ă邩�ǂ���
	MODEL *pModel;

} Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
Player *GetPlayer(void);

#endif
