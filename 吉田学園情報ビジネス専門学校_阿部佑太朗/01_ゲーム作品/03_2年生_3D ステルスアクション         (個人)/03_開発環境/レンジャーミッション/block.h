//=============================================================================
//
// �u���b�N���� [block.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"		// ���C��
#include "scenex.h"		// �V�[��x

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBlock : public CSceneX
{// �u���b�N�e�FCSceneX
public:
	typedef enum
	{//	�u���b�N�̎��
		MODELTYPE_GIRISUTU = 0,		//	�M���[�X�[�c
		MODELTYPE_CYLINDER,			//	�R���C�_�[
		MODELTYPE_KONTENA000,		//	�R���e�i000
		MODELTYPE_SHIPOBJ,			//	�D
		MODELTYPE_GRASS,			//	��
		MODELTYPE_KONTENA001,		//	�R���e�i001
		MODELTYPE_KONTENA002,		//	�R���e�i002
		MODELTYPE_SHIPON,			//	�D��
		MODELTYPE_SHIPUNDER,		//	�D
		MODELTYPE_STAGEEND,			//	�X�e�[�W�̃S�[��
		MODELTYPE_DOOR,				//	�h�A
		MODELTYPE_BILLING000,		//	�r��000
		MODELTYPE_BRONZESTATUE,		//	����
		MODELTYPE_TREEWOOD,			//	�؂̉�����
		MODELTYPE_TREEGRASS,		//	�؂̏㕔��
		MODELTYPE_KONTENA003,		//	�R���e�i003
		MODELTYPE_KONTENA004,		//	�R���e�i004
		MODELTYPE_KONTENA005,		//	�R���e�i005
		MODELTYPE_GRASSBIG,			//	�傫����
		MODELTYPE_BILLING001,		//	�r��001
		MODELTYPE_BILLING002,		//	�r��002
		MODELTYPE_BILLING003,		//	�r��003
		MODELTYPE_BILLING004,		//	�r��004
		MODELTYPE_BILLING005,		//	�r��005
		MODELTYPE_MAX
	}MODELTYPE;

	typedef enum
	{//	�u���b�N�̔���̎��
		COLTYPE_NONE = 0,	//	�����蔻��Ȃ�
		COLTYPE_BOX,		//	�{�b�N�X�R���W����
		COLTYPE_STEALTH,	//	�X�e���X�R���W����
		COLTYPE_STAGENXST,	//	���̃X�e�[�W�ɍs���ׂ̃R���W����
		COLTYPE_MAX
	}COLTYPE;
	const static int m_MaxModel = MODELTYPE_MAX;			// ���f����
	CBlock();												// �R���X�g���N�^
	~CBlock();												// �f�X�g���N�^
	static HRESULT Load(void);								// ���f���ƃe�N�X�`���ǂݍ���
	static void Unload(void);								// ���f���ƃe�N�X�`���J��
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype);		// ����
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype);				// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);			// �����蔻��
	bool StealthCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);	// �����蔻��
	bool StageNxstCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);// ���̃X�e�[�W��������
	bool *GetHit(void) { return m_bHit; }					// ���������ꏊ�̎擾
	bool GetStealthIN(void) { return m_bStealthIN; }		//  Stealth���[�h�̎擾
	COLTYPE GetCOlType(void) { return m_colType; }			//	�R���W�����̃^�C�v

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture[m_MaxModel];	// �e�N�X�`�����ւ̃|�C���^
	static LPD3DXMESH			m_pMesh[m_MaxModel];		// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMat[m_MaxModel];		// �}�e���A�����ւ̃|�C���^
	static DWORD				m_nNumMat[m_MaxModel];		// �}�e���A�����̐�

	MODELTYPE					m_modelType;				// ���f���̎��
	COLTYPE						m_colType;					// ���
	D3DXVECTOR3					m_posOld;					// �ߋ��̈ʒu
	bool						m_bHit[6];					// ���������ꏊ
	bool						m_bStealthIN;				// �X�e���X�I�u�W�F�N�g�ɓ������ꍇ
protected:

};

#endif