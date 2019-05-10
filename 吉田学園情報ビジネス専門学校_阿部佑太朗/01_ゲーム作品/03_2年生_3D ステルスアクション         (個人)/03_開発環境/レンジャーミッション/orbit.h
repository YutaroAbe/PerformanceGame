//=============================================================================
//
// �I�[�r�b�g���� [orbit.h]
// Author :YUTARO ABE
//
//=============================================================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "main.h"
#include "scene.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_YSIZE (1)
#define MAX_XSIZE (50)
#define MAX_SIZE ((MAX_XSIZE +1)*(MAX_YSIZE +1))
#define MAX_PORIGON_ORBIT (MAX_XSIZE * MAX_YSIZE * 2 + (MAX_YSIZE - 1) * 4)

//=============================================================================
//	���b�V���I�[�r�b�g�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class COrbit : public CScene
{
public:
	COrbit();															//	�R���X�g���N�^
	COrbit(int nPriarity, CScene::OBJTYPE objtype);						//	�R���X�g���N�^
	~COrbit();															//	�f�X�g���N�^
	HRESULT Init(void);													//	���b�V���I�[�r�b�g�̏���������
	void Uninit(void);													//	���b�V���I�[�r�b�g�̏I������
	void Update(void);													//	���b�V���I�[�r�b�g�̍X�V����
	void Draw(void);													//	���b�V���I�[�r�b�g�̕`�揈��
																		//	���b�V���I�[�r�b�g�̐���
	static COrbit *Create(D3DXVECTOR3 offsetstate, D3DXVECTOR3 offsetend);
	void SetMtxParent(D3DXMATRIX *pmtxworld);							//	�}�g���b�N�X�̐ݒ�
private:
	LPDIRECT3DTEXTURE9		m_pTexture;									//�@�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									//�@���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;										//�@�ʒu
	D3DXVECTOR3				m_rot;										//�@����
	D3DXMATRIX				m_mtxworld;									//	���[���h�}�g���b�N�X
	D3DXMATRIX				*m_pMtxParrentState;						//	�e�̃}�g���b�N�X�̃|�C���^

	float					m_fWidth;									//	��
	float					m_fHeight;									//	����
	D3DXVECTOR3				m_fOffSet[2];								//	�I�t�Z�b�g�̈ʒu���W
	D3DXVECTOR3				m_aPosVerTex[MAX_SIZE];						//	����ւ��p�ϐ�
protected:
};
#endif