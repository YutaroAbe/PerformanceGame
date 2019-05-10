//=============================================================================
//
//	�e3D�̏���[bullet.h]
//	Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"	//	���C��
#include "scenex.h"	//	�V�[����

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_USE_VALSE (20)		//	�e���g�p����Ă���l

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
//	�N���X�̒�`
//*****************************************************************************
class CBullet3D :public CSceneX
{//	�e3D�e�F CSceneX
public:

	typedef enum
	{//	�e�̎��
		BULLET3D_TYPE_BOOM = 0,		//	�{��
		BULLET3D_MAX				//	�e�̎�ނ̍ő�
	}BULLET3DTYPE;

	typedef enum
	{//�e�̃X�e�[�^�X
		BULLET_NONE = 0,			//	�������ĂȂ�
		BULLET_HIT,					//	�e����������
		BULLET_DISP,				//	�e��������
		BULLET_MAX
	}BULLETSTATE;

	CBullet3D();					//	�R���X�g���N�^
	~CBullet3D();					//	�f�X�g���N�^
	static HRESULT Load(void);		//	���f���ƃe�N�X�`���ǂݍ���
	static void Unload(void);		//	���f���̃e�N�X�`���̊J��
	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType);	//	����
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType);				//	����������
	void Uninit(void);				//	�I������
	void Update(void);				//	�X�V����
	void Draw(void);				//	�`�揈��
	int GetDispCut(void) { return m_nDispCounter; }

private:
	static LPDIRECT3DTEXTURE9 *m_pTexture[BULLET3D_MAX];		//	�e�N�X�`���̏��ւ̃|�C���^
	static LPD3DXMESH			m_pMesh[BULLET3D_MAX];			// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[BULLET3D_MAX];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[BULLET3D_MAX];		// �}�e���A�����̐�

	BULLET3DTYPE m_Bullet3DType;								//	�e�̃��f���̎��
	BULLETSTATE m_BulletState;									//	�e�̏��

	//	�X�e�[�^�X
	D3DXVECTOR3 m_move;											//	����
	D3DXVECTOR3 m_posOld;										//	�O��̈ʒu�̕ۑ�
	int			m_nDispCounter;									//	�e��������܂ł̃J�E���g
	bool		m_bExplColl;									//	�I�u�W�F�N�g�̏Փ˔���

};
#endif