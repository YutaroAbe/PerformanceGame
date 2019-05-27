//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_BULLET_0 "data/TEXTURE/BULLET/bullet000.png"
#define TEXTURE_NAME_BULLET_1 "data/TEXTURE/BULLET/bullet001.png"
#define TEXTURE_NAME_BULLET_2 "data/TEXTURE/BULLET/bullet002.png"
#define TEXTURE_NAME_BULLET_3 "data/TEXTURE/BULLET/bullet003.png"
#define TEXTURE_NAME_BULLET_4 "data/TEXTURE/BULLET/bullet004.png"
#define BULLET_POLIGON_X (15)		//	�e�̉��̑傫��
#define BULLET_POLIGON_Y (15)		//	�e�̏c�̑傫��
#define MAX_BULLET (5)				//	�e�̎�ނ̍ő吔

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CBullet : public CScene2D
{
public:
	typedef enum
	{//	�e�̎��
		BULLET_NONE = 0,	//	�ʏ�
		BULLET_PLAYER,		//	�v���C���[
		BULLET_ENEMY,		//	�G
		BULLET_MAX			//	�ő吔
	}BULLET_TYPE;

	CBullet();																						//	�R���X�g���N�^
	~CBullet();																						//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType);			//	�e�̏���������
	void Uninit(void);																				//	�e�̏I������
	void Update(void);																				//	�e�̍X�V����
	void Draw(void);																				//	�e�̕`�揈��
	static HRESULT Laod(void);																		//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);																		//	�e�N�X�`���̊J��
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType);	//	�e�̐���

private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_BULLET];												//	���ʃe�N�X�`���̃|�C���^
	BULLET_TYPE m_BulletType;																		//	�e�̎��
	 D3DXVECTOR3 m_move;																			//	�ړ���
	 int m_nType;																					//	�e�̎��
	 int m_nLife;																					//	�e�̎���
	 CScene2D *m_apScene2D;																			//	�V�[��2D�̃|�C���^�^�ϐ�
};
#endif
