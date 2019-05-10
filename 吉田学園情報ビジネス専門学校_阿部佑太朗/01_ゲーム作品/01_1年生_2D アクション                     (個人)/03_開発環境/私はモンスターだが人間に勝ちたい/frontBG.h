//=============================================================================
//
// �t�����gBG���� [frontBG.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _FRONTBG_H_
#define _FRONTBG_H_

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
	int nNumYajirusi;
}FrontBG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFrontBG(void);
void UninitFrontBG(void);
void UpdateFrontBG(void);
void DrawFrontBG(void);
void SetFrontBG(int nType,D3DXVECTOR3 pos, float fHeight, float fWindth);
FrontBG *GetFrontBG(void);

#endif
