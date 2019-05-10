//=============================================================================
//
// �����_�[���� [renderer.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
//�����_�����O�N���X
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();													// �R���X�g���N�^
	~CRenderer();													// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);								// �f�o�C�X�̎擾
	void DrawSelect(void);											// �Z���N�g�̐�����������
	void DrawStageSelect(void);										// �X�e�[�W�Z���N�g�̐�����������
	void DrawGameTutorial(void);									// �Q�[���̃`���[�g���A���̐�����������
private:

#ifdef _DEBUG
	void DrawFPS(void);
	void DrawPosition(void);
#endif
	CManager				*m_pManager;								//	�}�l�[�W���[�̃|�C���^�^�ϐ�
	LPDIRECT3D9				m_pD3D;										// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9	    m_pD3DDevice;								// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;									// �t�H���g�ւ̃|�C���^
	LPD3DXFONT				m_pDebugFont;								// �t�H���g�ւ̃|�C���^
};
#endif	// _RENDERER_H_
