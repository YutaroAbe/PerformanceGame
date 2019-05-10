//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		//	���C��
#include "scene.h"		//	�V�[��

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CModel;			//	���f��
class CShadow;			//	�e
class CHpBer3D;			//	Hp�o�[3D
class CBullet2D;		//	�e2D

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMPARTS	(30)
#define MAX_NUMMOTION	(30)

//*****************************************************************************
// �N���X��` �G
//*****************************************************************************
class CEnemy : public CScene
{
public:
	typedef enum
	{//	�X�e�[�^�X
		STATE_NONE = 0,						//	�ʏ�
		STATE_DAMAGE,						//	�_���[�W
		STATE_DEATH,						//	���S
		STATE_MAX							//	�X�e�[�^�X�̍ő吔
	}STATE;

	typedef enum
	{
		AI_NONE,		//	�������Ȃ�
		AI_UP,			//	�O�ɐi��
		AI_DOWN,		//	���ɐi��
		AI_LEFT,		//	���ɐi��
		AI_RIGHT,		//	�E�ɐi��
		AI_FOLLOWING,	//	�v���C���[�ɒǏ]����
		AI_ATTACK,		//	�U������
		AI_MAX
	}ENEMY_AI;


	typedef struct
	{//�L�[�v�f
		float fposX;						//	�ʒu��X
		float fposY;						//	�ʒu��Y
		float fposZ;						//	�ʒu��Z
		float frotX;						//	��]��X
		float frotY;						//	��]��Y
		float frotZ;						//	��]��Z
	}KEY;

	typedef struct
	{//�L�[���
		int nFrame;							//	�L�[�t���[��
		KEY aKey[MAX_NUMPARTS];				//	�e�L�[�v�f
	}KEY_INFO;

	typedef struct
	{//���[�V�������
		bool bLoop;							//	���[�v���邩���Ȃ���
		int nNumKey;						//	�L�[�̔ԍ�
		KEY_INFO aKayInfo[MAX_NUMMOTION];	//	�e�L�[���
	}MOTION_INFO;

	CEnemy();														//	�R���X�g���N�^
	~CEnemy();														//	�f�X�g���N�^
	HRESULT Init(void);												//	������
	void Uninit(void);												//	�I������
	void Update(void);												//	�X�V����
	void Draw(void);												//	�`�揈��
	//	     �ʒu�@           �����@  ���C�t�@  �G�̎�ށ@�Ǐ]����͈� �@�����͈́@  �G�̓����̑I��
	static CEnemy *Create	//	�G�̐���
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nType, int nMoveLength,float fNoneSpeed, float fFormingSpeed, ENEMY_AI nAISelect);
	static HRESULT Load(void);										//	�ǂݍ��݂̏���
	static void UnLoad(void);										//	����̏���
	D3DXVECTOR3 GetposOld(void) { return m_posOld; }				//	�ʒu�̎擾
	D3DXVECTOR3 Getpos(void) { return m_pos; }						//	�ʒu�̎擾
	D3DXVECTOR3 GetInitpos(void) { return m_InitPos; }				//	�ʒu�̎擾
	D3DXVECTOR3 Getrot(void) { return m_rot; }						//	��]�̎擾
	D3DXVECTOR3 Getmove(void) { return m_move; }					//	�����̎擾
	int Gettype(void) { return m_nType; }							//	��ނ̎擾
	bool GetLand(void) { return m_bLand; };							//	����Ă��邩�̎擾
	int GetLife(void) { return m_nLife; }							//	HP�̎擾
	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	�ʒu�̐ݒ�
	void SetposOld(D3DXVECTOR3 posOld) { m_pos = posOld; }			//	�ߋ��ʒu�̐ݒ�
	void Setrot(D3DXVECTOR3 rot) { m_rot = rot; }					//	�����̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				//	�����̐ݒ�

	bool GetHit(void) { return m_bHit; }							//	�����������̎擾
	float GetLength(void);											//	�v���C���[�s�̋���
																	//  �傫���擾
	D3DXVECTOR3 Getsize(int nNum) { if (nNum == 0) { return m_vtxMax; /*0�ԍő�l*/ } else { return m_vtxMin/*1�ŏ��l*/; } }
	void UpdateMotion(void);										//	���[�V�����̍X�V
																	//	�t�@�C���ǂݍ��݂Ɋւ���֐�
	void FileLoad(void);											//	�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);						//	1�s�ǂݍ���
	char *GetLineTop(char *pStr);									//	�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);						//	�s�̍Ō��؂��

		//	�L�����N�^�[�̊Ǘ�����֐�
																	//	�����蔻��̊Ǘ�
	void ManagementCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void ManagementAddRod(D3DXVECTOR3 rotDest);						//�p�x�����Z����

																	//	�����蔻��
	void Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	//	�G���m�̓����蔻��
	void OtherEnemyCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void HitDamege(int Damege);										//	�U���̃_���[�W

private:
	//	���f���ɕK�v�ȕϐ�
	static LPD3DXMESH			m_pMeshModel[MAX_NUMPARTS];			//	���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_NUMPARTS];		//	�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	*m_pTextureModel[MAX_NUMPARTS];		//	�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMatModel[MAX_NUMPARTS];		//	�}�e���A�����̐�
																	//	���[�V�����֘A�ϐ�
	char						m_aFileNameModel[MAX_NUMPARTS][256];//	�ǂݍ��ރ��f���̖��O
	KEY_INFO					*m_pKeyInfo[MAX_NUMMOTION];			//	�L�[���ւ̃|�C���^
	int							m_nKey;								//	���݂̃L�[�i���o�[
	int							m_nCountFlame;						//	�t���[����
	int							m_nNumParts;						//	�p�[�c��
	int							m_aIndexParent[MAX_NUMPARTS];		//	�e�̃C���f�b�N�X
	KEY							m_aKayOffset[MAX_NUMPARTS];			//	�I�t�Z�b�g���
	MOTION_INFO					m_aMotionInfo[MAX_NUMMOTION];		//	���[�V�������
	bool						m_bMotionEnd;						//	���[�V�����̏I��
	D3DXVECTOR3					m_OffSetPos[MAX_NUMPARTS];			//	�I�t�Z�b�g�ʒu
	int							m_nNumModel;						//	���f���̐�
	int							m_nCntNumMosion;					//	�e�L�X�g�ɏ�����Ă��郂�[�V�����̐�
	int							m_nCouterFreamMax[MAX_NUMMOTION];	//	���[�V�����̃t���[���̍��v�l
	int							m_nCntMosionChange;					//	���[�V�����̐؂�ւ���J�E���^�[
	//	�L�����N�^�[�̏��
	D3DXMATRIX					m_mtxWorld;							//	���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;								//	�ʒu
	D3DXVECTOR3					m_posOld;							//	�O��̈ʒu
	D3DXVECTOR3					m_InitPos;							//	�����̈ʒu
	D3DXVECTOR3					m_rot;								//	����
	D3DXVECTOR3					m_move;								//	����
	D3DXVECTOR3					m_vtxMax;							//	����ő�
	D3DXVECTOR3					m_vtxMin;							//	����ŏ�
	D3DXVECTOR3					m_Scale;							//	�g��k���p�ϐ�
	bool						m_bHit;								//	�����蔻��̓����������ǂ���
	int							m_nLife;							//	�̗�
	int							m_nType;							//	�G�̎��
	int							m_nDameCuter;						//�@�_���[�W�J�E���^�[
	int							m_nDispCuter;						//	���񂾂Ƃ��̃J�E���^�[
	STATE						m_state;							//	�X�e�[�^�X
	ENEMY_AI					m_AIEnemy;							//	�G��AI�̏���
	D3DXVECTOR3					m_LengthDawn;						//	�v���C���[�Ƃ̋�����Z������
	static	int					m_nNumPartsMax;						//	parts�̍ő吔
	bool						m_bLand;							//	����Ă邩�ǂ���
	//	�v���C���[�Ɏg�p����N���X
	CShadow						*m_pShadow;							//	�e
	CHpBer3D					*m_pHpBer3D;						//	Hp�o�[3D
protected:
	CModel						*m_apModel[MAX_NUMPARTS];			//	���f���̃|�C���^
	int							m_nMotionType;						//	���[�V�����̎��
	int							m_nMotionTypeOld;					//	���[�V�����̉ߋ��̎��
	float						m_fAngle;							//	�p�x
	int							m_nMoveLength;						//	�ړ����鋗��������
	bool						m_bOtherEnemyHit;					//	�G���m���������ꍇ
	bool						m_bPStealthMode;					//	�v���C���[���X�e���X���[�h�ɓ������ꍇ
	int							m_nAISelect;						//	�����̑I��
	float						m_fNoneSpeed;						//	�������Ă��Ȃ����̑���
	float						m_fFormingSpeed;					//	�Ǐ]���鎞�̑���
	bool						m_bWallHit;							//	�ǂɓ����������ǂ���
	static bool					m_bLastObDisp;						//	�Ō�̃I�u�W�F�N�g�����邩�ǂ���

};

//*****************************************************************************
// �N���X��` �@�G ROBOT 000
//*****************************************************************************
class CEnemyRobotNomal : public CEnemy
{//	�e�@CEnemy �G
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,					//	�j���[�g�������[�V����
		MOSION_MOVE,						//	�ړ����[�V����
		MOSION_DAMEGA,						//	�_���[�W���[�V����
		MOSION_ATTACK,						//	�U�����[�V����
		MOSION_MAX							//	�ő吔
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	�������Ȃ�
		AI_UP,			//	�O�ɐi��
		AI_DOWN,		//	���ɐi��
		AI_LEFT,		//	���ɐi��
		AI_RIGHT,		//	�E�ɐi��
		AI_FOLLOWING,	//	�v���C���[�ɒǏ]����
		AI_ATTACK,		//	�U������
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotNomal();							//	�R���X�g���N�^
	~CEnemyRobotNomal();						//	�f�X�g���N�^
	HRESULT Init(void);							//	����������
	void Uninit(void);							//	�I������
	void Update(void);							//	�X�V����
	void Draw(void);							//	�`�揈��
	void ManagementMovement(int nAIdata_Move);						//	�����̊Ǘ�[	�G�̓����Ǘ�	]
	void ManagementSetMosion(void);									//	���[�V�����̐ݒ�Ǘ�
	bool  CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	STATE						m_state;		//	�X�e�[�^�X
	ENEMY_AI					m_AIEnemy;							//	�G��AI�̏���
	MOSION_STATE				m_MosionState;						//	���[�V�����̏��
	bool						m_bAttack;							//	�U���������ǂ���
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rotDest;							//	�ړI�̌���
	int							m_nEffectCounter;					//	�G�t�F�N�g���o���J�E���^�[
};

//*****************************************************************************
// �N���X��` �@�G ROBOT �e����
//*****************************************************************************
class CEnemyRobotBullet : public CEnemy
{//	�e�@CEnemy �G
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,					//	�j���[�g�������[�V����
		MOSION_MOVE,						//	�ړ����[�V����
		MOSION_DAMEGA,						//	�_���[�W���[�V����
		MOSION_ATTACK,						//	�U�����[�V����
		MOSION_MAX							//	�ő吔
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	�������Ȃ�
		AI_UP,			//	�O�ɐi��
		AI_DOWN,		//	���ɐi��
		AI_LEFT,		//	���ɐi��
		AI_RIGHT,		//	�E�ɐi��
		AI_FOLLOWING,	//	�v���C���[�ɒǏ]����
		AI_ATTACK,		//	�U������
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotBullet();						//	�R���X�g���N�^
	~CEnemyRobotBullet();						//	�f�X�g���N�^
	HRESULT Init(void);							//	����������
	void Uninit(void);							//	�I������
	void Update(void);							//	�X�V����
	void Draw(void);							//	�`�揈��
	void ManagementMovement(int nAIdata_Move);						//	�����̊Ǘ�[	�G�̓����Ǘ�	]
	void ManagementSetMosion(void);									//	���[�V�����̐ݒ�Ǘ�
private:
	STATE						m_state;		//	�X�e�[�^�X
	ENEMY_AI					m_AIEnemy;							//	�G��AI�̏���
	MOSION_STATE				m_MosionState;						//	���[�V�����̏��
	bool						m_bAttack;							//	�U���������ǂ���
	int							m_nBulletCunter;					//	�e�̃J�E���^�[
	CBullet2D					*m_pBullet2D;						//	�e2D
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rotDest;							//	�ړI�̌���

};

//*****************************************************************************
// �N���X��` �@�G ROBOT�@��
//*****************************************************************************
class CEnemyRobotSpine : public CEnemy
{//	�e�@CEnemy �G
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,					//	�j���[�g�������[�V����
		MOSION_MOVE,						//	�ړ����[�V����
		MOSION_DAMEGA,						//	�_���[�W���[�V����
		MOSION_MAX							//	�ő吔
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	�������Ȃ�
		AI_UP,			//	�O�ɐi��
		AI_DOWN,		//	���ɐi��
		AI_LEFT,		//	���ɐi��
		AI_RIGHT,		//	�E�ɐi��
		AI_FOLLOWING,	//	�v���C���[�ɒǏ]����
		AI_ATTACK,		//	�U������
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotSpine();						//	�R���X�g���N�^
	~CEnemyRobotSpine();						//	�f�X�g���N�^
	HRESULT Init(void);							//	����������
	void Uninit(void);							//	�I������
	void Update(void);							//	�X�V����
	void Draw(void);							//	�`�揈��
	void ManagementMovement(int nAIdata_Move);						//	�����̊Ǘ�[	�G�̓����Ǘ�	]
	void ManagementSetMosion(void);									//	���[�V�����̐ݒ�Ǘ�
	bool  CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	STATE						m_state;		//	�X�e�[�^�X
	ENEMY_AI					m_AIEnemy;							//	�G��AI�̏���
	MOSION_STATE				m_MosionState;						//	���[�V�����̏��
	bool						m_bAttack;							//	�U���������ǂ���
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rotDest;							//	�ړI�̌���
	float						m_fAddRot;							//	��]�̉��Z
};

//*****************************************************************************
// �N���X��` �@�G ROBOT�@���ɒe������
//*****************************************************************************
class CEnemyRobotUndeBulletr : public CEnemy
{//	�e�@CEnemy �G
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,					//	�j���[�g�������[�V����
		MOSION_MOVE,						//	�ړ����[�V����
		MOSION_DAMEGA,						//	�_���[�W���[�V����
		MOSION_MAX							//	�ő吔
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	�������Ȃ�
		AI_UP,			//	�O�ɐi��
		AI_DOWN,		//	���ɐi��
		AI_LEFT,		//	���ɐi��
		AI_RIGHT,		//	�E�ɐi��
		AI_FOLLOWING,	//	�v���C���[�ɒǏ]����
		AI_ATTACK,		//	�U������
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotUndeBulletr();					//	�R���X�g���N�^
	~CEnemyRobotUndeBulletr();					//	�f�X�g���N�^
	HRESULT Init(void);							//	����������
	void Uninit(void);							//	�I������
	void Update(void);							//	�X�V����
	void Draw(void);							//	�`�揈��
	void ManagementMovement(int nAIdata_Move);						//	�����̊Ǘ�[	�G�̓����Ǘ�	]
	void ManagementSetMosion(void);									//	���[�V�����̐ݒ�Ǘ�
private:
	STATE						m_state;							//	�X�e�[�^�X
	ENEMY_AI					m_AIEnemy;							//	�G��AI�̏���
	MOSION_STATE				m_MosionState;						//	���[�V�����̏��
	bool						m_bAttack;							//	�U���������ǂ���
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rotDest;							//	�ړI�̌���
	int							m_nBulletCunter;					//	�e�̃J�E���^�[
	CBullet2D					*m_pBullet2D;						//	�e2D
	float						m_fAddPos;							//	�ʒu�̉��Z
	int							m_nEffectCounter;					//	�G�t�F�N�g���o��J�E���^
};

//*****************************************************************************
// �N���X��` �@�Ō�̃I�u�W�F�N�g
//*****************************************************************************
class CEnemyLastObj: public CEnemy
{//	�e�@CEnemy �G
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,					//	�j���[�g�������[�V����
		MOSION_MAX							//	�ő吔
	}MOSION_STATE;

	CEnemyLastObj();							//	�R���X�g���N�^
	~CEnemyLastObj();							//	�f�X�g���N�^
	HRESULT Init(void);							//	����������
	void Uninit(void);							//	�I������
	void Update(void);							//	�X�V����
	void Draw(void);							//	�`�揈��

private:
	STATE						m_state;							//	�X�e�[�^�X
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rotDest;							//	�ړI�̌���
	int							m_nEffectCounter;					//	�G�t�F�N�g���o��J�E���^
};

#endif