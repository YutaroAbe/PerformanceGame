//=============================================================================
//
// �����O�`9�̏��� [number.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_NUMBER_0 "data/TEXTURE/number000.png"			//	�ǂݍ��ރe�N�X�`���̏ꏊ�w��

#define MAX_NUMBER_TEXTURE (3)										//	�e�N�X�`���̍ő吔
#define NUMBER_POLIGON_X (10)										//	�����̑傫��X��
#define NUMBER_POLIGON_Y (10)										//	�����̑傫��Y��

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CNumber
{
public:
	CNumber();														//	�R���X�g���N�^
	~CNumber();														//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length);				//	�����̏����������i�ʒu�A���a�j
	void Uninit(void);												//	�����̏I������
	void Update(void);												//	�����̍X�V����
	void Draw(void);												//	�����̕`�揈��
	static HRESULT Laod(void);										//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);										//	�e�N�X�`���̊J��
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length);	//	�����̐����i�ʒu�A���a�j
	static void BindTexture(LPDIRECT3DTEXTURE9	pTexture);			//	�e�N�X�`���̊��蓖��
	 void SetNumber(int nNumber);									//	�ԍ��̐ݒ�
	 static int GetNumNumber(void);									//	�ԍ��̍��ꂽ���̎擾
private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	���ʃe�N�X�`���̃|�C���^
	 LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//  ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;									//  �|���S���̈ʒu
	D3DXVECTOR3				m_Length;								//	���a
	static int m_NumNumber;											//	�ԍ��̍��ꂽ���̎擾
protected:
};
#endif
