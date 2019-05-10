//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_BG_0 "data/TEXTURE/BG/000.png"			//	�ꖇ�ڂ̔q�[
#define TEXTURE_NAME_BG_1 "data/TEXTURE/BG/bg001.png"		//	�񖇖ڂ̔q�[
#define TEXTURE_NAME_BG_2 "data/TEXTURE/BG/bg002.png"		//	�O���ڂ̔q�[
#define TEXTURE_NAME_BG_3 "data/TEXTURE/BG/bg003.png"		//	�l���ڂ̔q�[
#define MAX_TEXTURE (4)										//	�e�N�X�`���̍ő吔
#define BG_POLIGON_X (10)									//	�e�N�X�`���̑傫��X��
#define BG_POLIGON_Y (10)									//	�e�N�X�`���̑傫��Yjiku

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CBg : public CScene
{
public:
	CBg();														//	�R���X�g���N�^
	~CBg();														//	�f�X�g���N�^
	HRESULT Init(void);											//	�w�i�̏���������
	void Uninit(void);											//	�w�i�̏I������
	void Update(void);											//	�w�i�̍X�V����
	void Draw(void);											//	�w�i�̕`�揈��
	static HRESULT Laod(void);									//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);									//	�e�N�X�`���̊J��
	static CBg *Create(void);									//	�w�i�̐���
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEXTURE];			//	���ʃe�N�X�`���̃|�C���^
	CScene2D *m_apScene2D[MAX_TEXTURE];							//	2D�|���S���̕ϐ�
	D3DXVECTOR3 m_move;											//	�w�i�̓���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//	���_�o�b�t�@�ւ̃|�C���^
protected:
};
#endif
