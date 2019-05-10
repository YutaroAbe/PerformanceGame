//=============================================================================
//
// UI���� [ui.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scene2d.h"	// �V�[��2D
#include "manager.h"	// �}�l�[�W���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_TEXMAX		(54)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPause;
class CBullet3D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUI : public CScene2D
{// UI �N���X
public:
	CUI();											// �R���X�g���N�^
	~CUI();											// �f�X�g���N�^

	static HRESULT Load(CManager::MODE mode);		// ���[�h
	static void Unload(void);						// �A�����[�h
													// ����
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col ,D3DXVECTOR2 uv , int nType);
													// ����������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR2 uv, int nType);
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��
	static void CreateMode(CManager::MODE mode);
	static bool GetTutoEnd(void) { return m_bTutoEnd; }	//	�`���[�g���A���̕����o�����I�������
													//	�Z���N�g���[�h�̔ԍ�
	static int GetSelectNUM(void) { return m_nNumSelectMode; }
	static int GetNumTxst(void) { return m_nNextTxst; }	//
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[UI_TEXMAX];		//  �e�N�X�`�����ւ̃|�C���^
	int m_nType;											//  ���
	int m_nCounterAnim;										//	�A�j���[�V�����p�J�E���^�[
	int m_nPatternAnim;										//	�A�j���[�V�����p�^�[��
	D3DXVECTOR3 m_sizeOld;									//	�����̑傫���̎擾
	bool m_bFlash;											//	�_��
	static CManager::MODE m_mode;							//	�Q�[���̃��[�h
	static int  	m_nNumSelectMode;						//	�Z���N�g�ԍ�
	float			m_fFrameValue;							//	�t���[���̒l
	bool			m_bPressButton;							//	�{�^�����������ǂ���
	static int		m_nNextTxst;							//	�`���[�g���A���̕\�L�ݒ�
	int				m_nCutTuto;								//	�`���[�g���A���̃J�E���^�[
	bool			m_bSize ;								//	�傫���̕ω�
	int				m_nPlayerLife;							//	�v���C���[�̗̑�
	int				m_nPlayerLifeOld ;						//	�v���C���[�̗̑͂̕ۑ�
	int				m_nPlayerLifeMax;						//	�v���C���[�̗̑͂̍ő�
	bool			m_nPlayerSquat;							//	�v���C���[���X�e���X���Ă��邩�ǂ���
	bool			m_nPlayerDash;							//	�v���C���[���X�e���X���Ă��邩�ǂ���
	D3DXVECTOR3		m_InitPos;								//	�ŏ��̈ʒu
	static bool		m_bTutoEnd;								//	�`���[�g���A�����ǂ���
	bool			m_bTutoOperation;						//	�`���[�g���A���̑�������`�悷�邩���Ȃ���
	CBullet3D		*m_Bullet3D;							//	�e3D
	bool			m_bColChange;							//	�F��ς��邩�ǂ���

	int				m_nStealthLifeMax;						//	�v���C���[�̃X�e���X�̎����ő�
	int				m_nStealthLife;							//	�v���C���[�̃X�e���X�̎����ő�
	int				m_nStealthCut;							//	�v���C���[�̃X�e���X�̃J�E���^�[

	int				m_nDashLifeMax;							//	�v���C���[�̃_�b�V���̎����ő�
	int				m_nDashLife;							//	�v���C���[�̃_�b�V���̎����ő�
	int				m_nDashCut;								//	�v���C���[�̃_�b�V���̃J�E���^�[
protected:

};

#endif