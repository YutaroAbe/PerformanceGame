//=============================================================================
//
//�@�X�e�[�W�̑I���̏��� [stageselect.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_STAGESELECT_UI (8)
#define MAX_STAGESELECT (4)

//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CStageSelect
{
public:
	CStageSelect();																// �R���X�g���N�^
	~CStageSelect();																// �f�X�g���N�^
	HRESULT Init(void);														// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static  HRESULT Load(void);												// �e�N�X�`�������[�h
	static void UnLoad(void);												// �e�N�X�`�����J��
	static int GetNumSelect(void);											// �I������ԍ��̎擾
	static int GetSelWordCounter(void);										//�@�Z���N�g�̕�����\���J�E���^�[�̎擾
private:
	CScene2D						*m_apScene2D[MAX_STAGESELECT_UI];	//	�V�[��2D�̃|�C���^�^�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_STAGESELECT_UI];		// �e�N�X�`������
	static int						m_nNumSelect;						// �I�����鍀�ڔԍ�
	static int						m_nSelectWordCounter;				//�@�Z���N�g�̕�����\���J�E���^�[
	bool m_bPress;
};

#endif // _MANAGER_H_
