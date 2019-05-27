//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_ENEMY_0 "data/TEXTURE/ENEMY/enemy001.png"
#define TEXTURE_NAME_ENEMY_1 "data/TEXTURE/ENEMY/enemy002.png"
#define TEXTURE_NAME_ENEMY_2 "data/TEXTURE/ENEMY/enemy003.png"
#define TEXTURE_NAME_ENEMY_3 "data/TEXTURE/ENEMY/enemy004.png"
#define ENEMY_POLIGON_X_000 (25)				//	�G�̕��̑傫��000
#define ENEMY_POLIGON_Y_000 (50)				//	�G�̏c�̑傫��000
#define ENEMY_POLIGON_X_001 (25)				//	�G�̕��̑傫��001
#define ENEMY_POLIGON_Y_001 (50)				//	�G�̏c�̑傫��001
#define MAX_ENEMY (128)							//	�G�̎g����ő吔
#define MAX_ENEMY_TYPE (4)						//	�G�̎��

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CEnemy : public CScene2D
{
public:
	typedef enum
	{//	�G�̏��
		ENEMYSTATE_NOMAL = 0,	//	�ʏ�
		ENEMYSTATE_DAMAGE,		//	�_���[�W
		ENEMYSTATE_MAX			//	��Ԃ̍ő吔
	}ENEMYSTATE;

	CEnemy();																//	�R���X�g���N�^
	~CEnemy();																//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,int nType);	//	�G�̏���������
	void Uninit(void);														//	�G�̏I������
	void Update(void);														//	�G�̍X�V����
	void Draw(void);														//	�G�̕`�揈��
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);
	static HRESULT Laod(void);												//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);												//	�e�N�X�`���̊J��
	static int GetNUMENEMY(void);											//	�G�̐��̎擾
	void Hit(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_ENEMY_TYPE];					//	���ʃe�N�X�`���̃|�C���^
	 int m_nType;															//	���
	 static int m_nNUM_ENEMY;												//	�G�̐�������ϐ�
	 int m_nCounterState;													//
protected:
	ENEMYSTATE enemystate;													//	�G�̏��
	 D3DXVECTOR3 m_posOld;													//	�ߋ��̈ʒu
	 int m_nAICounter;														//	�G�̍s���p�^�[���̃J�E���g
	 bool m_bBulletAttck;													//	�G���e�������Ă��邩
	 int m_nLife;															//	�G�l�~�[�̗̑�
};
//=============================================================================
//	�G�l�~�[�^�C�v1
//=============================================================================
class CEnemyType000 : public CEnemy
{
public:
	typedef enum
	{//	�G�̋������
		MOVE_AI_NONE = 0,		//	�ʏ�̓���
		MOVE_AI_LEFT,			//	���ɍs������
		MOVE_AI_RIGHT,			//	�E�̍s������
		MOVE_AI_MAX				//	�����̍ő吔
	}MOVE_AI;
	CEnemyType000();														//	�R���X�g���N�^
	~CEnemyType000();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	�G�̏���������
	void Uninit(void);														//	�G�̏I������
	 void Update(void);														//	�G�̍X�V����
	void Draw(void);														//	�G�̕`�揈��
private:
	MOVE_AI move_ai;														//	�G�̓����̕ϐ�
	bool m_bAttackMove;														//	�v���C���[�ւ̍U���͈͂��ǂ���

};
//=============================================================================
//	�G�l�~�[�^�C�v2
//=============================================================================
class CEnemyType001 : public CEnemy
{
public:
	typedef enum
	{//	�G�̋������
		MOVE_AI_NONE = 0,		//	�ʏ�̓���
		MOVE_AI_LEFT,			//	���ɍs������
		MOVE_AI_RIGHT,			//	�E�̍s������
		MOVE_AI_MAX				//	�����̍ő吔
	}MOVE_AI;
	CEnemyType001();														//	�R���X�g���N�^
	~CEnemyType001();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	�G�̏���������
	void Uninit(void);														//	�G�̏I������
	 void Update(void);														//	�G�̍X�V����
	void Draw(void);														//	�G�̕`�揈��
private:
	MOVE_AI move_ai;														//	�G�̓����̕ϐ�
	bool m_bAttackMove;														//	�v���C���[�ւ̍U���͈͂��ǂ���
};

//=============================================================================
//	�G�l�~�[�^�C�v3
//=============================================================================
class CEnemyType002 : public CEnemy
{
public:
	typedef enum
	{//	�G�̋������
		MOVE_AI_NONE = 0,		//	�ʏ�̓���
		MOVE_AI_LEFT,			//	���ɍs������
		MOVE_AI_RIGHT,			//	�E�̍s������
		MOVE_AI_MAX				//	�����̍ő吔
	}MOVE_AI;
	CEnemyType002();														//	�R���X�g���N�^
	~CEnemyType002();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	�G�̏���������
	void Uninit(void);														//	�G�̏I������
	void Update(void);														//	�G�̍X�V����
	void Draw(void);														//	�G�̕`�揈��
private:
	MOVE_AI move_ai;														//	�G�̓����̕ϐ�
	bool m_bAttackMove;														//	�v���C���[�ւ̍U���͈͂��ǂ���
};

//=============================================================================
//	�G�l�~�[�^�C�v4
//=============================================================================
class CEnemyType003 : public CEnemy
{
public:
	typedef enum
	{//	�G�̋������
		MOVE_AI_NONE = 0,		//	�ʏ�̓���
		MOVE_AI_LEFT,			//	���ɍs������
		MOVE_AI_RIGHT,			//	�E�̍s������
		MOVE_AI_MAX				//	�����̍ő吔
	}MOVE_AI;
	CEnemyType003();														//	�R���X�g���N�^
	~CEnemyType003();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	�G�̏���������
	void Uninit(void);														//	�G�̏I������
	void Update(void);														//	�G�̍X�V����
	void Draw(void);														//	�G�̕`�揈��
private:
	MOVE_AI move_ai;														//	�G�̓����̕ϐ�
	bool m_bAttackMove;														//	�v���C���[�ւ̍U���͈͂��ǂ���
};
#endif