//=============================================================================
//
// �e�̒e���̏��� [lifeNumber.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLETNUMBER_H_
#define _BULLETNUMBER_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_LIFENUMBER (2)											//	�ǂݍ��ރe�N�X�`���̏ꏊ�w��
#define LIFENUM_POLIGON_X (10)										//	�X�R�A�̑傫��X��
#define LIFENUM_POLIGON_Y (10)										//	�X�R�A�̑傫��Y��

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CBulletNumber : public CScene
{
public:
	CBulletNumber();													//	�R���X�g���N�^
	~CBulletNumber();													//	�f�X�g���N�^
	HRESULT Init(void);												//	�X�R�A�̏���������
	void Uninit(void);												//	�X�R�A�̏I������
	void Update(void);												//	�X�R�A�̍X�V����
	void Draw(void);												//	�X�R�A�̕`�揈��
	static CBulletNumber *Create(void);								//	�X�R�A�̐���
	int GetLefeNum(void);											//	�X�R�A�̎擾
	static void AddNum(int nValue);								//	�X�R�A�̐ݒ�

private:
	static CNumber *m_apNumber[MAX_LIFENUMBER];						//	�X�R�A�̃|�C���^�^�ϐ�
	static int m_nNumber;										//	�X�R�A�̕ϐ�
protected:
};
#endif
