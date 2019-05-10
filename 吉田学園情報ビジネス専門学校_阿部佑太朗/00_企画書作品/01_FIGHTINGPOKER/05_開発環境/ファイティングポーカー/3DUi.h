//=============================================================================
//
// 3DUI���� [3DUi.h]
// Author : Ebina Riku
//
//=============================================================================
#ifndef _3DUI_H_
#define _3DUI_H_

#include "main.h"

//=============================================================================
// �񋓌^��`
//=============================================================================
typedef enum
{
	UI_3D_CURSOR = 0,
	UI_3D_LOCKMARK,
	UI_3D_MAX
}UI3DTYPE;
//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	LPD3DXMESH pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pTexture;	// �e�N�X�`���̃|�C���^
	DWORD nNumMat;					// �}�e���A�����̐�
}P3DUI;

typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ�
	D3DXVECTOR3 rot;					// ����
	D3DXVECTOR2 tex;					// �I�u�W�F�N�g�̃e�N�X�`�����
	D3DXMATRIX mtxWorldUI;			// ���[���h�}�g���b�N�X
	int nIdShadow;						// �e�̔ԍ�
	bool bUse;							// �g�p��
	UI3DTYPE type;
}UI_3D;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Init3DUI(void);
void Uninit3DUI(void);
void Update3DUI(void);
void Draw3DUI(void);
#endif
