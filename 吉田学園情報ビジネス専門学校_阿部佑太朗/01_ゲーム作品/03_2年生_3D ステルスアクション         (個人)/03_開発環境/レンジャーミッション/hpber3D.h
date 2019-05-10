//=============================================================================
//
// HP�o�[3D ���� [hpber3D.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _HPBER3D_H_
#define _HPBER3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene3d.h"	// �V�[��
#include "enemy.h"		// �G

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CHpBer3D : public CScene3D
{// �V�[��3D�i�e�FCScene�j
public:
	CHpBer3D();															// �R���X�g���N�^
	~CHpBer3D();														// �f�X�g���N�^
																		// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
																		// ����
	static CHpBer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	static HRESULT Load(void);											// �e�N�X�`���̓ǂݍ���
	static void Unload(void);											// �j��

	void SizeChange(int nDamage, CEnemy *m_pEnemy);						// �傫����ς���
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;							// �e�N�X�`�����ւ̃|�C���^
	D3DXMATRIX						m_mtxWorld;							// ���[���h�}�g���b�N�X
	CEnemy							*m_pEnemy;							// �G
	bool							m_bColChange;						// �F�̕ύX
	int								m_nColFream;						// �F�̕ύX����t���[��
protected:

};

#endif