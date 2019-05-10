//=============================================================================
//
// 中ボス敵の処理 [tbossenemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _TBOSSENEMY_H_
#define _TBOSSENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TBOSSENEMY	(4)				//  敵の最大数
#define BOSSENEMY_SIZEMAX (100)			// 	敵の大きさ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//敵の状態の種類

	TBOSSENEMYSTATE_NOMAL = 0, // 通常ダメージ
	TBOSSENEMYSTATE_DAMAGE,//ダメージ状態
	//ENEMYSTATE_DEATH,//死亡状態
	TBOSSENEMYSTATE_MAX

}TBOSSENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//動き
	D3DCOLOR col;		//頂点カラー
	int nType;			//種類
	bool bUse;			//使用されているかどうか
	int nCounterBullet;
	//bool bDisp;
	TBOSSENEMYSTATE state;	//敵の状態
	int nCounterState;  //状態管理のカウンター
	int nLife;			//体力
}TBossEnemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTBossEnemy(void);
void UninitTBossEnemy(void);
void UpdateTBossEnemy(void);
void DrawTBossEnemy(void);
void SetTBossEnemy(D3DXVECTOR3 pos,int nType);
TBossEnemy *GetTBossEnemy(void);
void HitTBossEnemy(int nCntTBossEnemy, int nDamage);


#endif
