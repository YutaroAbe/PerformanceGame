//=============================================================================
//
// �I�u�W�F�N�g���� [scene.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX_NUM (1000)
#define MAX_DROW (8)
//*****************************************************************************
//�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{//�I�u�W�F�N�g�̎��
		OBJECT_NONE = 0,
		OBJECT_PLAYER,
		OBJECT_ENEMY,
		OBJECT_BULLET,
		OBJECT_BLOCK,
		OBJECT_ITEM,
		OBJECT_MAX
	}OBJTYPE;

	CScene(int nPriarity = 3);								//�@�@�I�[�o�[���[�h���ꂽ�R���X�g���N�^
	CScene();												//	 �R���X�g���N�^
	~CScene();												//	 �f�X�g���N�^
	virtual HRESULT Init(void) = 0;							//	 �I�u�W�F�N�g�̏���������
	virtual void Uninit(void) = 0;							//	 �I�u�W�F�N�g�̏I������
	virtual void Update(void) = 0;							//	 �I�u�W�F�N�g�̍X�V����
	virtual void Draw(void) = 0;							//	 �I�u�W�F�N�g�̕`�揈��
	static void UpdateAll(void);							//	 �I�u�W�F�N�g�̑S�Ă̍X�V����
	static void DrawAll(void);								//	 �I�u�W�F�N�g�̑S�Ă̕`�揈��
	static void ReleaseAll(void);							//	 �I�u�W�F�N�g�̑S�Ă̏I������
	virtual void SetObjType(OBJTYPE Objtype);				//	 �I�u�W�F�N�g�̎�ސݒ�
	OBJTYPE GetObjType(void);								//
	static CScene *GetScene(int nPriarity,int nIndex);					//
	void Release(void);
	static int GetNumALL(void);

protected:

private:
	//static CScene					*m_apScene[MAX_NUM];	//  �ÓI�����o�֐� �I�u�W�F�N�g�|�C���^�^�̃V�[��
	static int m_nNumAll;									//  �ÓI�����o�֐� �I�u�W�F�N�g�̑���
	int m_nID;												//	�������g�̔ԍ�
	OBJTYPE m_object;										//	�I�u�W�F�N�g�̎��
	static CScene *m_apScene[MAX_DROW][MAX_NUM];			//	�D�揇�ʗp�ϐ�
	int m_nPriority;										//	�D�揇�ʂ̔ԍ�
	static bool m_bPasue;
};
#endif

