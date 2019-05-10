//=============================================================================
//
// 敵横の処理 [sideenemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _SIDEENEMY_H_
#define _SIDEENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_SIDEENEMY	(128)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//敵の状態の種類

	SIDEENEMYSTATE_NOMAL = 0,
	SIDEENEMYSTATE_DAMAGE,
	SIDEENEMYSTATE_MAX

}SIDEENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	D3DCOLOR col;		//頂点カラー
	int nType;			//種類
	bool bUse;			//使用されているかどうか
	SIDEENEMYSTATE state;	//敵の状態
	int nCounterState;  //状態管理のカウンター
	//int nLife;			//体力
}SideEnemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSideEnemy(void);
void UninitSideEnemy(void);
void UpdateSideEnemy(void);
void DrawSideEnemy(void);
void SetSideEnemy(D3DXVECTOR3 pos, int nType);
SideEnemy *GetSideEnemy(void);
void HitSideEnemy(int nCntSideEnemy, int nDamage);


#endif
