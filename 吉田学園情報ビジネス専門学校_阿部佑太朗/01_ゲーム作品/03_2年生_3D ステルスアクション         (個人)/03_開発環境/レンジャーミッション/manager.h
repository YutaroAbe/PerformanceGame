//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER		(2)								// �v���C���[�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInputKeyboard;	// �L�[�{�[�h
class CInputDIPad;		// DI�p�b�h
class CInputXPad;		// X�p�b�h
class CRenderer;		// �����_���[
class CCamera;			// �J����
class CLight;			// ���C�g
class CTitle;			// �^�C�g
class CGame;			// �Q�[��
class CResult;			// ���U���g
class CSelectMode;		// �Z���N�g���[�h
class CSound;			// �T�E���h

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CManager
{// �}�l�[�W���[
public:
	typedef enum
	{// ���[�h
		MODE_NONE = 0,		// �������Ă��Ȃ�
		MODE_TITLE,			// �^�C�g��
		MODE_SELECTMODE,	// �^�C�g��
		MODE_GAMETUTO,		// �Q�[���`���[�g���A���X�e�[�W
		MODE_GAMESTAGE000,	// �Q�[���X�e�[�W1
		MODE_GAMESTAGE001,	// �Q�[���X�e�[�W2
		MODE_GAMESTAGE002,	// �Q�[���X�e�[�W3
		MODE_OVER,			// ���U���g
		MODE_CLEAR,			// �N���A
		MODE_MAX
	}MODE;

	CManager();											// �R���X�g���N�^
	virtual ~CManager();								// �f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	virtual void Uninit(void);							// �I������
	virtual void Update(void);							// �X�V����
	virtual void Draw(void);							// �`�揈��
	static CSound *GetSound(void)					 { return m_pSound; }			// �T�E���h�擾
	static CInputKeyboard *GetInputKeyboard(void)	{ return m_pInputKeyboard; }	// �L�[�{�[�h�擾
	static CInputDIPad *GetInputDIPad(void)			{ return m_pInputDIPad; }		// DI�p�b�h�擾
	static CInputXPad *GetInputXPad(void)			{ return m_pInputXPad; }		// X�p�b�h�擾
	static CRenderer *GetRenderer(void)				{ return m_pRenderer; }			// �����_���[�擾
	static CCamera *GetCamera(void)					{ return m_pCamara; }			// �J�����擾
	static CLight *GetLight(void)					{ return m_pLight; }			// ���C�g�擾

	static void SetMode(MODE mode);						// ���[�h�ݒ�
	static MODE GetMode(void) { return m_mode; }		// ���[�h�擾

	static CDebugProcLEFT *m_CDebugProcLeft;			//	�f�o�b�N���p���O
	static CDebugProcRIGHT *m_CDebugProcRight;			//	�f�o�b�N�E�p���O

private:

	static MODE m_mode;									// ���[�h

	static CInputKeyboard	*m_pInputKeyboard;			// �L�[�{�[�h
	static CInputDIPad		*m_pInputDIPad;				// DI�p�b�h
	static CInputXPad		*m_pInputXPad;				// X�p�b�h
	static CCamera			*m_pCamara;					// �J����
	static CLight			*m_pLight;					// ���C�g
	static CRenderer		*m_pRenderer;				// �����_���[
	static CSound			*m_pSound;					// �T�E���h

	static CTitle			*m_pTitle;					// �^�C�g��
	static CSelectMode		*m_pSelectMode;				// �Z���N�g���[�h
	static CGame			*m_pGame;					// �Q�[��
	static CResult			*m_pResult;					// ���U���g
	static int				m_nPlayerLife;				//	�v���C���[�̃��C�t
protected:

};

#endif