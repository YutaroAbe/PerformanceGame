//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�V���h�[������ [meshSphere.h]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_MESHSPHERE				(1280)

typedef enum
{
	MESHSPHERE_TYPE_ATTACK = 0,		// �U���p
	MESHSPHERE_TYPE_DEFENSE,		// �h��p
	MESHSPHERE_TYPE_MAX,			// �ő吔
}MESHSPHERE_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitMeshSphere(void);
void UninitMeshSphere(void);
void UpdateMeshSphere(void);
void DrawMeshSphere(void);
void MakeMeshSphere(void);
int SetSphere(D3DXVECTOR3 const pos, float const fRadius, MESHSPHERE_TYPE const type, bool const bInside);
void SetPositionSphere(int const nIDSphere, D3DXVECTOR3 const pos);
void SetDispSphere(int const nIDSphere, bool bDisp);
#endif
