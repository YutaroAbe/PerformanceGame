//=============================================================================
//
//�@�Z���N�g�̏��� [select.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_SELECT_UI (7)
#define MAX_SELECT (3)

//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CSelect
{
public:
	CSelect();																// �R���X�g���N�^
	~CSelect();																// �f�X�g���N�^
	HRESULT Init(void);														// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static  HRESULT Load(void);												// �e�N�X�`�������[�h
	static void UnLoad(void);												// �e�N�X�`�����J��
	static int GetNumSelect(void);											// �I������ԍ��̎擾
	static int GetSelWordCounter(void);										//�@�Z���N�g�̕�����\���J�E���^�[�̎擾
private:
	CScene2D						*m_apScene2D[MAX_SELECT_UI];	//	�V�[��2D�̃|�C���^�^�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_SELECT_UI];		// �e�N�X�`������
	static int						m_nNumSelect;					// �I������
	static int						m_nSelectWordCounter;			//�@�Z���N�g�̕�����\���J�E���^�[
	int m_nNextCounter;												//	��ʂ��~�܂��Ă�����^�C�g���ɖ߂鏈��
	bool m_bPress;													//	����{�^���������Ă����Ԃ�
};

#endif // _MANAGER_H_
