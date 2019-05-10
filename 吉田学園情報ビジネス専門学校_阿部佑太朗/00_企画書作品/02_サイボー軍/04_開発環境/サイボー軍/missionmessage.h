//=============================================================================
//
//�@�~�b�V�������b�Z�[�W�̏��� [missionMessage.h]
//	Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _MISSONMESSAGE_H_
#define _MISSONMESSAGE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_MISSONMESSAGE_UI (1)

//=============================================================================
//	�}�l�[�W���[�N���X
//=============================================================================
class CMissionMessage
{
public:
	CMissionMessage();														// �R���X�g���N�^
	~CMissionMessage();														// �f�X�g���N�^
	HRESULT Init(void);														// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	static  HRESULT Load(void);												// �e�N�X�`�������[�h
	static void UnLoad(void);												// �e�N�X�`�����J��
	static int GetGameText(void);											//�Q�[���̕����̃e�L�X�g���o�͂̎擾
	static int GetNumText(void);											//�����̏o�鏇�Ԃ̎擾
private:
	CScene2D *m_apScene2D[MAX_MISSONMESSAGE_UI];
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_MISSONMESSAGE_UI];		// �e�N�X�`������
	bool m_bPressState;														//	�{�^�������Ă��邩�ǂ���
	static int m_nGameTextCounter;
	static int m_nNumText;													//	�����̏o�鏇��
};

#endif // _MANAGER_H_
