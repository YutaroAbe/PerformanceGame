//=============================================================================
//
// ���f������ [ColorBall.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _COLORBALL_H_
#define _COLORBALL_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	COLORBALLSTATE_STOP = 0,	//��~���
	COLORBALLSTATE_CHANGE,		//�ω����
}COLORBALLSTATE;				//�񋓌^
typedef enum
{
	COUNTERSTATE_CHANGE = 0,//�ω����
	COUNTERSTATE_WAIT,		//�ҋ@���
}COUNTERSTATE;				//�񋓌^

typedef struct
{
	DWORD nNumMat = 0;						//�}�e���A�����̐�
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X
	float fShadow;							//�e�̑傫��
	int nIdxShadow;							//�e�̃C���f�b�N�X
	int nType;								//���f���̎��
	bool bUse;								//�g�p���Ă��邩
	COLORBALLSTATE state;
	COUNTERSTATE CntState;
	int nTimerChange;
	int nStateCounter;
	int nFrameCounter;
} COLORBALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitColorBall(void);
void UninitColorBall(void);
void UpdateColorBall(void);
void DrawColorBall(void);
COLORBALL *GetColorBall(void);
void SetColorBall(D3DXVECTOR3 pos,int nType);
#endif