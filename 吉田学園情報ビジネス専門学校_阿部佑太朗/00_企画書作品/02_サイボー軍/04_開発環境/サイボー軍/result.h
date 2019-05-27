//=============================================================================
//
//�@���U���g�̏��� [result.h]
//	Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_RESULT_UI (5)

//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CResult
{
public:

	typedef enum
	{
		GAMESTATE_NOMAL = 0,
		GAMESTATE_OVER,
		GAMESTATE_CLEAR,
		GAMESTATE_MAX
	}GAMESTATE;

	CResult();																// �R���X�g���N�^
	~CResult();																// �f�X�g���N�^
	HRESULT Init(void);														// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static  HRESULT Load(void);												// �e�N�X�`�������[�h
	static void UnLoad(void);												// �e�N�X�`�����J��
private:
	CScene2D *m_apScene2D[MAX_RESULT_UI];
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_RESULT_UI];				// �e�N�X�`������
	GAMESTATE gamestate;													//	�Q�[���̏��
	float m_fGameOverCounter;												//	�Q�[���I�[�o�[�\���J�E���^�[
	int m_nCounterAnim;														//
	int m_nPatternAnim;														//	�A�j���[�V�����J�E���^�[
	bool m_bPressState;														//	�{�^�������Ă��邩�ǂ���
};

#endif // _MANAGER_H_
