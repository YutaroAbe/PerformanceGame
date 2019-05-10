///=============================================================================
//
// �v���C���[���� [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		//	���C��
#include "scene.h"		//	�V�[��
#include "shadow.h"		//	�e

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CModel;			//	���f��
class CMotion;			//	���[�V����
class COrbit;			//�@�O��
class CShadow;			//	�e
class CBullet3D;		//	�e
class CScene;			//	�V�[��
class CEnemy;			//	�G
class CCamera;			//	�J����
class CBlock;			//	�u���b�N

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMPARTS	(30)
#define MAX_NUMMOTION	(30)
#define MAX_STEALTHCUT	(500)		//	�X�e���X�̃J�E���^�[���߂�ő�l
#define MAX_DASHTHCUT	(300)		//	�_�b�V���̃J�E���^�[���߂�ő�l


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CScene
{
public:
	typedef enum
	{//	���[�V�����̎��
		MOSION_NEUTRAL = 0,	//	�j���[�g�������[�V����
		MOSION_MOVE,		//	�ړ����[�V����
		MOSION_JUMP,		//	�W�����v���[�V����
		MOSION_LAND,		//	���n���[�V����
		MOSION_BLTPRPE,		//	�e�𓊂��鏀�����[�V�����@(�@BLT:�o���b�g PRPE:�v���y�A)
		MOSION_BLTTHROW,	//	�e�����郂�[�V����		�@(�@BLT:�o���b�g THROW:����   )
		MOSION_SQUAT,		//	���Ⴊ�ރ��[�V����
		MOSION_SQUATMOVE,	//	���Ⴊ�ޕ������[�V����
		MOSION_ATTACK_000,	//	�U�����[�V����000�@�L�b�N
		MOSION_ATTACK_001,	//	�U�����[�V����001�@�p���`
		MOSION_DISP,		//	���񂾏��
		MOSION_DAMAGE,		//	�_���[�W���[�V����
		MOSION_MAX			//	�ő吔
	}MOSION_STATE;

	typedef enum
	{//	�X�e�[�^�X
		STATE_NONE = 0,						//	�ʏ�
		STATE_DAMAGE,						//	�_���[�W
		STATE_INVINCIBLE,					//	���G
		STATE_DEATH,						//	���S
		STATE_MAX							//	�X�e�[�^�X�̍ő吔
	}STATE;
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

	CPlayer();														//	�R���X�g���N�^
	~CPlayer();														//	�f�X�g���N�^
	HRESULT Init(void);												//	������
	void Uninit(void);												//	�I������
	void Update(void);												//	�X�V����
	void Draw(void);												//	�`�揈��
	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	�ʒu�̐ݒ�
							//	�ʒu�@�����@�̗́@�e�̐��� �X�e���X�o������� �_�b�V���o�������
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,int nBltCut,int nStealthLife, int nDashLife);
	void HitLife(int nDamage,D3DXVECTOR3 move);										//	�_���[�W�v�Z����
	void AddBulletGan(int nAdd);									//	�e�̐�

	static HRESULT Load(void);										//	�ǂݍ��݂̏���
	static void UnLoad(void);										//	����̏���

	 D3DXVECTOR3 Getpos(void) { return m_pos; }						//	�ʒu�̎擾
	 D3DXVECTOR3 Getmove(void) { return m_move; }					//	�����̎擾
	 D3DXVECTOR3 GetposOld(void) { return m_posOld; }				//	�ߋ��̈ʒu�̎擾
	 D3DXVECTOR3 Getrot(void) { return m_rot; }						//	��]�̎擾
	 int GetLife(void) { return m_nLife; }							//	�̗͂̎擾
	 int GetBltNum(void) { return m_nBltCut; }						//	�e�̒e��
	 bool GetSquat(void) { return m_bSquat; }						//	���Ⴊ��ł����Ԃ̎擾
	 bool GetLastHit(void) { return m_bAtkLastHit;}					//	�Ō�̍U���̎擾
	 bool GetStealthMode(void) { return m_bStealthMode; }			//	�X�e���X���[�h�̎擾
	 int GetStealthCut(void) { return m_nStealthCut; }				//	�X�e���X���A����J�E���^�[�̎擾
	 int GetStealthLife(void) { return m_nStealthLife; }			//	�X�e���X�̎����̎擾
	 int GetDashCut(void) { return m_nDashCut; }					//	�_�b�V�����A����J�E���^�[�̎擾
	 int GetDashLife(void) { return m_nDashLife; }					//	�_�b�V���̎����̎擾
	 bool GetDisp(void) { return m_bDisp; }							//	�S���Ȃ������ǂ���
	 STATE GetState(void) { return m_state; }						//	��Ԃ̎擾
	 bool GetDash(void) { return m_bDash; }							//	�S���Ȃ������ǂ���

	 D3DXVECTOR3 Getsize(int nNum) { if (nNum == 0) { return m_vtxMax; } else { return m_vtxMin; } }
	void UpdateMotion(void);										//	���[�V�����̍X�V
	void FileLoad(void);											//	�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);						//	1�s�ǂݍ���
	char *GetLineTop(char *pStr);									//	�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);						//	�s�̍Ō��؂�̂�

	void ManagementCollision(void);									//	�����蔻��̊Ǘ�
	void ManagementMovement(void);									//	�����̊Ǘ�
	void ManagementAddMovement(void);								//	���Z���铮���̊Ǘ�
	void ManagementSetMosion(void);									//	���[�V�����̐ݒ�Ǘ�
																	//	�����蔻��
	bool AttackCollsion(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void BoxCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);

private:
	//	���f���ɕK�v�ȕϐ�
	static LPD3DXMESH			m_pMesh[MAX_NUMPARTS];			//	���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[MAX_NUMPARTS];		//	�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	*m_pTexture[MAX_NUMPARTS];		//	�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMat[MAX_NUMPARTS];		//	�}�e���A�����̐�
	//	���[�V�����֘A�ϐ�
	KEY_INFO					*m_pKeyInfo[MAX_NUMMOTION];			//	�L�[���ւ̃|�C���^
	int							m_nKey;								//	���݂̃L�[�i���o�[
	int							m_nCountFlame;						//	�t���[����
	static int					m_nNumParts;						//	�p�[�c��
	int							m_aIndexParent[MAX_NUMPARTS];		//	�e�̃C���f�b�N�X
	KEY							m_aKayOffset[MAX_NUMPARTS];			//	�I�t�Z�b�g���
	MOTION_INFO					m_aMotionInfo[MAX_NUMMOTION];		//	���[�V�������
	bool						m_bMotionEnd;						//	���[�V�����̏I��
	D3DXVECTOR3					m_OffSetPos[MAX_NUMPARTS];			//	�I�t�Z�b�g�ʒu
	D3DXVECTOR3					m_OffSetRot[MAX_NUMPARTS];			//	�I�t�Z�b�g�ʒu
	int							m_nMotionType;						//	���[�V�����̎��
	int							m_nMotionTypeOld;					//	���[�V�����̉ߋ��̎��
	int							m_nNumModel;						//	���f���̐�
	char						m_aFileNameModel[MAX_NUMPARTS][256];//	�ǂݍ��ރ��f���̖��O
	//	�L�����N�^�[�̏��
	D3DXVECTOR3					m_pos;								//	�ʒu
	D3DXVECTOR3					m_posOld;							//	�O��̈ʒu
	D3DXVECTOR3					m_move;								//	�ړ���
	D3DXVECTOR3					m_rot;								//	����
	STATE						m_state;							//	�X�e�[�^�X
	D3DXMATRIX					m_mtxWorld;							//	���[���h�}�g���b�N�X
	D3DXVECTOR3					m_rotDest;							//	�ڕW����
	D3DXVECTOR3					m_vtxMax;							//	����ő�
	D3DXVECTOR3					m_vtxMin;							//	����ŏ�
	FLOAT						m_fScaleX, m_fScaleY, m_fScaleZ;	//	�g��k���p�ϐ�
	CModel						*m_apModel[MAX_NUMPARTS];			//	���f���̃|�C���^
	MOSION_STATE				m_MosionState;						//	���[�V�����̏��
	int							m_nCntNumMosion;					//	�e�L�X�g�ɏ�����Ă��郂�[�V�����̐�
	int							m_nCouterFreamMax[MAX_NUMMOTION];	//	���[�V�����̃t���[���̍��v�l
	int							m_nCntMosionChange;					//	���[�V�����̐؂�ւ���J�E���^�[
	int							m_nAtkFream;						//	�U���̃R���W�������ł�t���[��
	int							m_nAtkCombFream;					//	�U���̃R���{�̃t���[��
	bool						m_bAtkLastHit;						//	�U���̍Ō�̍U������������
	int							m_nLife;							//	����
	int							m_nLifeInit;						//	�����̎���
	int							m_nBltCut;							//	��֒e�̒e��
	//	�L�����N�^�[�̏�ԗp
	bool						m_bBlock;							//	�u���b�N�ɓ������Ă��邩�ǂ���
	bool						m_bJump;							//	�W�����v���
	bool						m_bLand;							//	���n���
	bool						m_bMove;							//	�����Ă�����
	bool						m_bSquat;							//	���Ⴊ��ł�����
	bool						m_bAttack;							//	�U����Ԃ�
	bool						m_bDash;							//	�_�b�V�����Ă��邩�ǂ���
	float						m_fMoveControl;						//	�ړ��̕ω�
	bool						m_bDisp;							//	����ł��邩�ǂ���
	bool						m_bDamage;							//	�_���[�W���
	int							m_nStateCounter;					//	�_���[�W���̃J�E���^�[
	bool						m_bStealthMode;						//	�X�e���X���Ă��邩�ǂ���
	bool						m_bLifeState[2];					//	�̗͂̕ω����Ă�����[0]�_���[�W[1]��
	bool						*m_bStlBlockHitIn;					//	�X�e���X�u���b�N�̒��ɓ��������ǂ���
	int							m_nNumBlock;						//	�X�e���X�u���b�N�̐�
	int							m_nInvincible;						//	���G���
	int							m_nStealthLife;						//	�X�e���X�o�������
	int							m_nStealthCut;						//	�X�e���X��Ԃɖ߂�J�E���^�[
	int							m_nDashLife;						//	�_�b�V���ł������
	int							m_nDashCut;							//	�_�b�V����Ԃɖ߂�J�E���^�[

	//	�v���C���[�Ɏg�p����N���X
	CShadow						*m_pShadow;							//	�e
	COrbit						*m_pOrbit;							//	�O��
	CBullet3D					*m_pBullet3D;						//	�e
	CCamera						*m_pCamera;							//	�J����
	CBlock						*m_pBlock;							//	�u���b�N
public:
};

#endif