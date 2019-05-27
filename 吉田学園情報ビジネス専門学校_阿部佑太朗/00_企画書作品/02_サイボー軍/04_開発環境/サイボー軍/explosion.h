//=============================================================================
//
// �����̏��� [explosion.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_EXPLPSION "data/TEXTURE/EXPLOSION/s_uzu.png"
#define EXPLOSION_POLIGON_X (10)
#define EXPLOSION_POLIGON_Y (10)

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CExplosion : public CScene2D
{
public:
	CExplosion();													//	�R���X�g���N�^
	~CExplosion();													//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);									//	�e�̏���������
	void Uninit(void);												//	�e�̏I������
	void Update(void);												//	�e�̍X�V����
	void Draw(void);												//	�e�̕`�揈��
	static HRESULT Laod(void);										//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);										//	�e�N�X�`���̊J��
	static CExplosion *Create(D3DXVECTOR3 pos);						//	�e�̐���

private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	���ʃe�N�X�`���̃|�C���^
	 int m_CounterAnim;												//	�A�j���[�V�����J�E���^�[
	 int m_PatternAnim;												//	�A�j���[�V�����p�^�[��
protected:

};
#endif
