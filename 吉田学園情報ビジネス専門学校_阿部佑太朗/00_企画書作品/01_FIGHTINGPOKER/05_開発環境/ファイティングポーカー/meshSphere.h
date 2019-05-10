//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッシュドーム処理 [meshSphere.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_MESHSPHERE				(1280)

typedef enum
{
	MESHSPHERE_TYPE_ATTACK = 0,		// 攻撃用
	MESHSPHERE_TYPE_DEFENSE,		// 防御用
	MESHSPHERE_TYPE_MAX,			// 最大数
}MESHSPHERE_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
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
