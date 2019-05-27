//=============================================================================
//
// �A�C�e���̏��� [item.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_ITEM_HP "data/TEXTURE/ITEM/HP000.png"
#define TEXTURE_NAME_ITEM_001 "data/TEXTURE/ITEM/001.jpg"
#define TEXTURE_NAME_ITEM_002 "data/TEXTURE/ITEM/002.png"
#define TEXTURE_NAME_ITEM_003 "data/TEXTURE/ITEM/003.png"
#define TEXTURE_NAME_ITEM_004 "data/TEXTURE/ITEM/004.png"
#define ITEM_POLIGON_X (25)
#define ITEM_POLIGON_Y (25)
#define MAX_TEX_ITEM (4)

//=============================================================================
//	�v���C���[�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CItem : public CScene2D
{
public:
	CItem();																								//	�R���X�g���N�^
	~CItem();																								//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos,int nType);																//	�A�C�e���̏���������
	void Uninit(void);																						//	�A�C�e���̏I������
	void Update(void);																						//	�A�C�e���̍X�V����
	void Draw(void);																						//	�A�C�e���̕`�揈��
	static CItem *Create(D3DXVECTOR3 pos, int nType);														//	�A�C�e���̐���
	static HRESULT Laod(void);																				//	�e�N�X�`����ǂݍ���
	static void UnLoad(void);																				//	�e�N�X�`���̊J��
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEX_ITEM];														//	���ʃe�N�X�`���̃|�C���^
	int m_nType;																							//	���
};
#endif
