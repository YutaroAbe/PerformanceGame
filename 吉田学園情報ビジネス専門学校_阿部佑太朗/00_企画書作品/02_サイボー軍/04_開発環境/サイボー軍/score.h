//=============================================================================
//
// �X�R�A�̏��� [score.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define MAX_SCORE (8)												//	�ǂݍ��ރe�N�X�`���̏ꏊ�w��
#define SCORE_POLIGON_X (10)										//	�X�R�A�̑傫��X��
#define SCORE_POLIGON_Y (10)										//	�X�R�A�̑傫��Y��

//=============================================================================
//	�X�R�A�N���X�i�V�[���̔h���N���X�j
//=============================================================================
class CScore : public CScene
{
public:
	CScore();														//	�R���X�g���N�^
	~CScore();														//	�f�X�g���N�^
	HRESULT Init(void);												//	�X�R�A�̏���������
	void Uninit(void);												//	�X�R�A�̏I������
	void Update(void);												//	�X�R�A�̍X�V����
	void Draw(void);												//	�X�R�A�̕`�揈��
	static CScore *Create(void);									//	�X�R�A�̐���
	int GetScore(void);												//	�X�R�A�̎擾
	static void AddScore(int nValue);								//	�X�R�A�̐ݒ�

private:
	static CNumber *m_apNumber[MAX_SCORE];									//	�X�R�A�̃|�C���^�^�ϐ�
	static int m_nScore;											//	�X�R�A�̕ϐ�
protected:
};
#endif
