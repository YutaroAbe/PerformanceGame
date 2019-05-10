//=============================================================================
//
//	�G�l�~�[���̃J�E���g�̏��� [enemycount.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMYCOUNT_H_
#define _ENEMYCOUNT_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_ENEMYCOUNT (3)												//	�ǂݍ��ރe�N�X�`���̏ꏊ�w��
#define ENEMYCOUNT_POLIGON_X (10)											//	�^�C�}�[�̑傫��X��
#define ENEMYCOUNT_POLIGON_Y (10)										//	�^�C�}�[�̑傫��Y��

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CEnemycount : public CScene
{
public:
	CEnemycount();													//	�R���X�g���N�^
	~CEnemycount();													//	�f�X�g���N�^
	HRESULT Init(void);												//	�^�C�}�[�̏���������
	void Uninit(void);												//	�^�C�}�[�̏I������
	void Update(void);												//	�^�C�}�[�̍X�V����
	void Draw(void);												//	�^�C�}�[�̕`�揈��
	static CEnemycount *Create(void);								//	�^�C�}�[�̐���
	int GetTime(void);												//	�^�C�}�[�̎擾
	static void AddEnemyCount(int nValue);								//	�^�C�}�[�̐ݒ�
private:
	static CNumber *m_apNumber[MAX_ENEMYCOUNT];						//	�^�C�}�[�̃|�C���^�^�ϐ�
	static int m_nEnemyCount;												//	�^�C�}�[�̕ϐ�
protected:
};
#endif
