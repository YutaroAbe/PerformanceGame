//=============================================================================
//
//�@�^�C�g���̏��� [title.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_TITLE_UI (3)

//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CTitle
{
public:
	CTitle();																// �R���X�g���N�^
	~CTitle();																// �f�X�g���N�^
	 HRESULT Init(void);													// ����������
	 void Uninit(void);														// �I������
	 void Update(void);														// �X�V����
	 void Draw(void);														// �`�揈��
	static  HRESULT Load(void);												// �e�N�X�`�������[�h
	static void UnLoad(void);												// �e�N�X�`�����J��
private:
	 CScene2D *m_apScene2D[MAX_TITLE_UI];
	 static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TITLE_UI];				// �e�N�X�`������
	 int m_nCounterAnim[3];													//
	 int m_nPatternAnim[3];
	 bool m_bPressState;
};

#endif // _MANAGER_H_
