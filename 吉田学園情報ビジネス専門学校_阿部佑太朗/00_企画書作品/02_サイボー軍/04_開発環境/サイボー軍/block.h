//=============================================================================
//
// �v���b�N�̏��� [blook.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define TEXTURE_NAME_BLOCK_000 "data/TEXTURE/BLOCK/block000.png"
#define TEXTURE_NAME_BLOCK_001 "data/TEXTURE/BLOCK/block001.png"
#define TEXTURE_NAME_BLOCK_002 "data/TEXTURE/BLOCK/block002.png"
#define TEXTURE_NAME_BLOCK_003 "data/TEXTURE/BLOCK/block003.png"
#define TEXTURE_NAME_BLOCK_004 "data/TEXTURE/BLOCK/block004.png"
#define TEXTURE_NAME_BLOCK_005 "data/TEXTURE/BLOCK/block005.png"
#define TEXTURE_NAME_BLOCK_006 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_007 "data/TEXTURE/BLOCK/block007.png"
#define TEXTURE_NAME_BLOCK_008 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_009 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_010 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_011 "data/TEXTURE/BLOCK/.png"
#define BLOCK_POLIGON_X (25)		//	�u���b�N�̉��̑傫��
#define BLOCK_POLIGON_Y (25)		//	�u���b�N�̏c�̑傫��
#define MAX_BLOCK (TYPE_MAX)		//	�u���b�N�̐�

//=============================================================================
//	�u���b�N�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CBlock : public CScene2D
{
public:
	typedef enum
	{//	�u���b�N�̎��
		TYPE_NOMAL = 0,		//	�ʏ�
		TYPE_JUMP,			//	�W�����v��
		TYPE_L_PLAYERMOVE,	//	�x���g�R���x�A[��]
		TYPE_R_PLAYERMOVE,	//	�x���g�R���x�A[�E]
		TYPE_BREAKBLOCK,	//	����u���b�N
		TYPE_FALL,			//	������u���b�N
		TYPE_DAMAGE,		//	�_���[�W�󂯂�u���b�N
		TYPE_STAGE,			//	�K�i�p�u���b�N
		TYPE_ITEMBLOCK,		//	�A�C�e�����o��u���b�N
		TYPE_MAX			//	��ނ̍ő�
	}BLOCK_TYPE;

	CBlock();																												//	�R���X�g���N�^
	~CBlock();																												//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos,  float fWindth, float fHeight,int nType,float fTexSplitX, float fTexSplitY);				//	�u���b�N�̏���������
	void Uninit(void);																										//	�u���b�N�̏I������
	void Update(void);																										//	�u���b�N�̍X�V����
	void Draw(void);																										//	�u���b�N�̕`�揈��
	static CBlock *Create(D3DXVECTOR3 pos,  float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY);	//	�u���b�N�̐���
	static HRESULT Laod(void);																								//	�u���b�N�̃e�N�X�`����ǂݍ���
	static void UnLoad(void);																								//	�u���b�N�̃e�N�X�`���̊J��
	static int GetNumBlock(void);																							//	�u���b�N�̐��̎擾
	static int GetTypeBlock(void);
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_BLOCK];																			//	�u���b�N�̋��ʃe�N�X�`���̃|�C���^
	static int m_nType;																										//	�u���b�N�̎��
	static int m_NumBlock;																									//	�u���b�N�̐�
protected:
	float m_fWindth;																										//	�u���b�N�̕�
	float m_fHeight;																										//	�u���b�N�̍���
};

//=============================================================================
//	������u���b�N�N���X�i�u���b�N�̔h���N���X�j
//=============================================================================
class CBlockDrop : public CBlock
{
public:
	CBlockDrop();																											//	�R���X�g���N�^
	~CBlockDrop();																											//	�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY);				//	�u���b�N�̏���������
	void Uninit(void);																										//	�u���b�N�̏I������
	void Update(void);																										//	�u���b�N�̍X�V����
	void Draw(void);																										//	�u���b�N�̕`�揈��
private:

};
#endif
