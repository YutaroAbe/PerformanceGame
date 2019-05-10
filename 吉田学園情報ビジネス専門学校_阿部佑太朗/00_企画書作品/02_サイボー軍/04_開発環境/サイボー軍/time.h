//=============================================================================
//
//	�^�C�}�[�̏��� [time.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_TIME (3)												//	�ǂݍ��ރe�N�X�`���̏ꏊ�w��
#define TIME_POLIGON_X (10)											//	�^�C�}�[�̑傫��X��
#define TIMEE_POLIGON_Y (10)										//	�^�C�}�[�̑傫��Y��

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CTime : public CScene
{
public:
	CTime();														//	�R���X�g���N�^
	~CTime();														//	�f�X�g���N�^
	HRESULT Init(void);												//	�^�C�}�[�̏���������
	void Uninit(void);												//	�^�C�}�[�̏I������
	void Update(void);												//	�^�C�}�[�̍X�V����
	void Draw(void);												//	�^�C�}�[�̕`�揈��
	static CTime *Create(void);										//	�^�C�}�[�̐���
	int GetTime(void);												//	�^�C�}�[�̎擾
	static void AddTime(int nValue);								//	�^�C�}�[�̐ݒ�
private:
	static CNumber *m_apNumber[MAX_TIME];							//	�^�C�}�[�̃|�C���^�^�ϐ�
	static int m_nTime;												//	�^�C�}�[�̕ϐ�
protected:
};
#endif
