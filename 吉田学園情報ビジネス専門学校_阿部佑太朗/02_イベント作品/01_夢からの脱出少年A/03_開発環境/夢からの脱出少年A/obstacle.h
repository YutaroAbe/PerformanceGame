//=============================================================================
//
// モデル処理 [obstacle.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"
//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{
	OBSTACLETYPE_MINE = 0,
	OBSTACLETYPE_SPIKE,
	OBSTACLETYPE_MAX
}OBS_TYPE;
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotMove;
	D3DXVECTOR3 difPos;
	D3DXVECTOR3 difAngle;
	D3DXMATRIX  mtxWorld;
	int nIdxShadow;
	bool bUse;
	D3DXVECTOR3 VtxMin;	//モデルの当たり判定の最小
	D3DXVECTOR3 VtxMax;	//モデルの当たり判定の最大
	DWORD NumMatObstacle;	//マテリアル情報の数
}OBSTACLE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitObstacle(void);
void UninitObstacle(void);
void UpdateObstacle(void);
void DrawObstacle(void);

bool CollisionObstacle(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);

void SetObstacle(D3DXVECTOR3 pos,OBS_TYPE type);
void SetObstacleVertex(int nCntObstacle ,int nCntType);

#endif
