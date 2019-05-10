//=============================================================================
//
// �̗͏��� [number.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_LIFE "data/TEXTURE/GAMEUI/HP101.png"
#define NUMBER_POLIGON_X (10)
#define NUMBER_POLIGON_Y (10)

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CLife : CScene2D
{
public:
	CLife();														//	�R���X�g���N�^
	~CLife();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length);				//	�e�̏����������i�ʒu�A���a�j
	 void Uninit(void);												//	�e�̏I������
	void Update(void);												//	�e�̍X�V����
	void Draw(void);												//	�e�̕`�揈��
	static HRESULT Laod(void);										//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);										//	�e�N�X�`���̊J��
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length);		//	�����̐����i�ʒu�A���a�j
	static void BindTexture(LPDIRECT3DTEXTURE9	pTexture);

private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	���ʃe�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								//  ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;									//  �|���S���̈ʒu
	D3DXVECTOR3				m_Length;								//	���a
	int m_nLife = CPlayer::GetLife();								//	�v���C���[�̗̑�
protected:
};
#endif
