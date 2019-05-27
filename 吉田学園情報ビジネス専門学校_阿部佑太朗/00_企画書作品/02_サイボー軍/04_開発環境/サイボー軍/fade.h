//=============================================================================
//
//  �t�F�[�h�̏��� [fade.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_FADE_0 "data/TEXTURE/bg004.png"
#define FADE_POLIGON_X (10)
#define FADE_POLIGON_Y (10)
#define BG_WIDTH   (SCREEN_WIDTH)				//�w�i�̕�
#define BG_HEIGHT   (SCREEN_HEIGHT)				//�w�i�̍���

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CFade
{
public:
	typedef enum
	{//�t�F�C�h�̏��
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	CFade();													//	�R���X�g���N�^
	~CFade();													//	�f�X�g���N�^
	void Init(CManager::MODE modeNext);							//	�t�F�C�h�̏���������
	void Uninit(void);											//	�t�F�C�h�̏I������
	void Update(void);											//	�t�F�C�h�̍X�V����
	void Draw(void);											//	�t�F�C�h�̕`�揈��
	static HRESULT Laod(void);									//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);									//	�e�N�X�`���̊J��
	//static CFade *Create(CManager::MODE modenext);				//	�t�F�C�h�̐���
	FADE m_fade;												//	�t�F�C�h�̏��
	void SetFade(CManager::MODE modeNext);						//	���ɏo�����
private:
	static LPDIRECT3DTEXTURE9 m_Texture;						//	���ʃe�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//	���_�o�b�t�@�ւ̃|�C���^
	 CManager::MODE  m_modenext;								//	���[�h�̑J��
	D3DXCOLOR m_colorFade;

protected:
};
#endif
