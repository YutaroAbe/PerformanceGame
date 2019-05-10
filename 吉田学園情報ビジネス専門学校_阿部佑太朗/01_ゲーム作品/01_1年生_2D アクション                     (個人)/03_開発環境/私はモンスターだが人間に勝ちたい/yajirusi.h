//=============================================================================
//
// ��󏈗� [yajirusi.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _YAJIRUSI_H_
#define _YAJIRUSI_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DCOLOR col;		//���_�J���[
	float fAngle;
	float fLength;
	float fWindth;		//��
	float fHeight;		//����
	int nType;			//���
	bool bUse;			//�g�p����Ă��邩�ǂ���
	int nCounterState;  //��ԊǗ��̃J�E���^�[
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No
	int nNumYajirusi;
}Yajirusi;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitYajirusi(void);
void UninitYajirusi(void);
void UpdateYajirusi(void);
void DrawYajirusi(void);
void SetYajirusi(int nType,D3DXVECTOR3 pos);
Yajirusi *GetYajirusi(void);


#endif
