//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author :
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PAUSE (4)
#define SELECT_MAX	(3)				// �I������ő吔

//=============================================================================
// �N���X��`
//=============================================================================
class CPause : public CScene
{
public:
	CPause();						// �R���X�g���N�^
	~CPause();						// �f�X�g���N�^
	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��
	static CPause *Create(void);	// �N���G�C�g
	static  HRESULT Load(void);		// �e�N�X�`�������[�h
	static void UnLoad(void);		// �e�N�X�`�����J��

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_PAUSE];			// �e�N�X�`������
	CScene2D						*m_apScene2D[MAX_PAUSE];		// �V�[��2D�̕ϐ�
	int								m_nNumSelect;					// �I�����鍀�ڔԍ�
};
#endif




