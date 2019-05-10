//=============================================================================
//
// �e2D�̏��� [bullet2D.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET2D_H_
#define _BULLET2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene3d.h"		// �V�[��
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULT2D_TYPE_MAX  (TYPE_BULTMAX)			//	�e�̎��
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CShadow;		//	�e

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet2D : public CScene3D
{// �V�[��3D�i�e�FCScene3D�j
public:
	typedef enum
	{//	�e�̎��
		TYPE_BULT000 = 0,
		TYPE_BULTMAX
	}TYPEBULT;

	typedef enum
	{//�e�̃X�e�[�^�X
		BULLET_NONE = 0,			//	�������ĂȂ�
		BULLET_HIT,					//	�e����������
		BULLET_DISP,				//	�e��������
		BULLET_MAX
	}BULLETSTATE;

	CBullet2D();														// �R���X�g���N�^
	~CBullet2D();														// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV,int nLife, TYPEBULT BultType);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
	D3DXVECTOR3 GetMove(void) { return m_move; }						// �����̎擾
																		// ����
	static CBullet2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV , int nLife, TYPEBULT BultType);
	static HRESULT Load(void);											// �e�N�X�`���̓ǂݍ���
	static void Unload(void);											// �j��
																		// �����蔻��
	bool CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[BULT2D_TYPE_MAX];		// �e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX						m_mtxWorld;							// ���[���h�}�g���b�N�X
	int								m_nLife;							// ����
	BULLETSTATE						m_BulletState;						// �e�̃X�e�[�^�X
	D3DXVECTOR3						m_move;								// ����
	CShadow							*m_pShadow;							// �e
	int								m_nDispCounter;						// ������܂ł̃J�E���g
	D3DXVECTOR3						m_posOld;							//	�ߋ��̈ʒu
protected:

};

#endif