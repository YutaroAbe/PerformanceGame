//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_EFFECT "data/TEXTURE/EFFCT/effect000.jpg"	//	�G�t�F�N�g�̃e�N�X�`��
#define EFFECT_POLIGON_X (15.0f)								//	�G�t�F�N�g�̉��̑傫��
#define EFFECT_POLIGON_Y (15.0f)								//	�G�t�F�N�g�̏c�̑傫��

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CEffect : public CScene2D
{
public:
	CEffect();																					//	�R���X�g���N�^
	~CEffect();																					//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos,int nLife, float fRadius, D3DXCOLOR Col);						//	�G�t�F�N�g�̏���������
	void Uninit(void);																			//	�G�t�F�N�g�̏I������
	void Update(void);																			//	�G�t�F�N�g�̍X�V����
	 void Draw(void);																			//	�G�t�F�N�g�̕`�揈��
	static HRESULT Laod(void);																	//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);																	//	�e�N�X�`���̊J��
	static CEffect *Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col);			//	�G�t�F�N�g�̐���

private:
	static LPDIRECT3DTEXTURE9 m_Texture;														//	���ʃe�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;															//	���_�o�b�t�@�ւ̃|�C���^
	int m_nLife;																				//	�\������(����)
	float m_fRadius;																			//	���a(�傫��)
	D3DXCOLOR m_Color;																			//	�J���[
};
#endif
