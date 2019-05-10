//=============================================================================
//
// ���f������ [model.h]
// Author :
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//���f���N���X�̒�`
//*********************************************************************
class CModel
{
public:
	typedef struct
	{
		DWORD nNumMat = 0;						//	�}�e���A�����̐�
		float fShadow;							//	�e�̑傫��
		int nIdxShadow;							//	�e�̃C���f�b�N�X
		int nType;								//	���f���̎��
		bool bUse;								//	�g�p���Ă��邩
	} MODEL;

	CModel();														//	�R���X�g���N�^
	~CModel();														//	�f�X�g���N�^
	HRESULT Init();													//	����������
	void Uninit(void);												//	�I������
	void Update(void);												//	�X�V����
	void Draw(void);												//	�`�揈��
	MODEL *GetModel(void) { return &m_aModel; }						//	���f���̎擾
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//	Character
	void BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTURE�����蓖�Ă�
	void SetParent(CModel *pModel);									//
	D3DXMATRIX &GetMtxWorld(void);									//	�}�g���b�N�X�̎擾
	void SetMtxWorld(D3DXMATRIX MtxWorld);							//	�}�g���b�N�X�̐ݒ�

	D3DXVECTOR3 VtxMax(void) { return m_vtxMax; }					//	�傫���̍ő�l
	D3DXVECTOR3 VtxMin(void) { return m_vtxMin; }					//	�傫���̍ŏ��l

	D3DXVECTOR3 Getrot(void) { return m_rot; }						//	�����̎擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }						//	�ʒu�̎擾

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	�ʒu�̐ݒ�
	void Setrot(D3DXVECTOR3 rot) { m_rot = rot; }					//	�����̐ݒ�

	//�����o�ϐ�
private:
	D3DXMATRIX				m_mtxWorld;						//	���[���h�}�g���b�N�X
	LPD3DXMESH				m_pMesh;						//	���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;						//	�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9		*m_pTexture;					//	�e�N�X�`���ւ̃|�C���^
	DWORD					m_nNumMat;						//	�}�e���A�����̐�
	MODEL					m_aModel;						//	���f�����
	D3DXVECTOR3				m_vtxMin;						//	���f���̍ŏ�
	D3DXVECTOR3				m_vtxMax;						//	���f���̍ő�l
	CModel					*m_pParent;						//	�e���f���ւ̃|�C���^
	D3DXVECTOR3				m_pos;							//	�ʒu
	D3DXVECTOR3				m_rot;							//	����
};


#endif