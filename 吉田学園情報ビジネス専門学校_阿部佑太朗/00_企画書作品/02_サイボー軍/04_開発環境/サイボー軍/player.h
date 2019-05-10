//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_PLAYER "data/TEXTURE/PLAYER/PPPPPP.png"
#define PLAYER_POLIGON_X (20)
#define PLAYER_POLIGON_Y (40)

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		//PLAYERSTATE_APPEAR=0,		//�o����ԁi���G�j
		PLAYERSTATE_NOMAL = 0,		//�ʏ�_���[�W
		PLAYERSTATE_DAMAGE,			//�_���[�W���
		PLAYERSTATE_DEATH,			//���S���
		PLAYERSTATE_END,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer();											//	�R���X�g���N�^
	~CPlayer();											//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);						//	�v���C���[�̏���������
	void Uninit(void);									//	�v���C���[�̏I������
	void Update(void);									//	�v���C���[�̍X�V����
	void Draw(void);									//	�v���C���[�̕`�揈��
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Laod(void);							//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);							//	�e�N�X�`���̊J��
	static void HitDamage(int nDamage);					//	�v���C���[�̃_���[�W�ݒ�
	static void UpLife(int nLife);						//	�v���C���[�̗͉̑�
	static void BulletChange(int nBulletType);			//	�v���C���[�̒e�̕ω�
	static bool GetLand(void);							//	�u���b�N�ɏ�������̏��擾

	static	int GetLife(void);							//	�v���C���[�̃��C�t�̎擾
	static D3DXVECTOR3 GetPosition(void);				//	�v���C���[�̃|�W�V�����̎擾
	static D3DXVECTOR3 GetMove(void);					//	�v���C���[�̓����̎擾
	static int GetTexNumber(void);						//	�v���C���[�̃e�N�X�`���̕����̔ԍ��擾
	static void LoadPlayer(void);						//	�v���C���[�̃e�L�X�g�ǂݍ���

private:
	static int m_nCounterState;							//��ԊǗ��̃J�E���^�[
	static PLAYERSTATE m_PlayerState;					//	�v���C���[�̏��
	static LPDIRECT3DTEXTURE9 m_Texture;				//	���ʃe�N�X�`���̃|�C���^
	static int m_nBulletType;							//	�e�̎�ޕω�
	static bool bDisp;									//	�v���C���[�������Ă��邩�ǂ���
	static int m_nLife;									//	�v���C���[�̗̑͂̕ϐ�
	static int m_nTexChange;							//	�e�N�X�`���̕ω��p
	int m_nCounterAnim;									//	�A�j���[�V�����p�J�E���^�[
	int m_nPatternAnim;									//	�A�j���[�V�����p�^�[��
	int m_nBulletRot;									//	���E�ɍ��킹�Ēe�̌����ς���
	static D3DXVECTOR3 m_move;							//	�v���C���[�̓���
	static D3DXVECTOR3 m_posold;						//	�ߋ��̈ʒu
	static float m_fWindth;								//	��
	static float m_fHeight;								//	����
	static D3DXVECTOR3 m_GetPos;						//	�v���C���[�̈ʒu�̎擾
	static D3DXVECTOR3 m_GetMove;						//	�v���C���[�̓����̎擾
	static bool m_bLandDropBlock;						//	������u���b�N�ɏ���Ă��邩����

	 bool m_bLandBlock;									//	�u���b�N�ɏ���Ă��邩����
	int m_nMotionState;									//	���݂̃��[�V�������
	int m_nMotionStateID;								//	���݂̃��[�V�����̕ۑ��p�ϐ�
	bool m_bBullet;										//	�e���΂��Ă��邩�ǂ���
};
#endif
