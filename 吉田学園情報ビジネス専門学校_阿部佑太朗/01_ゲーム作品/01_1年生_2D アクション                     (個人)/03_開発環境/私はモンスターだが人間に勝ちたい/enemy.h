//=============================================================================
//
// 敵の処理 [enemy.h]
// Author :YUUTAROU ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ENEMY	(128)	// 敵の最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{//敵の状態の種類

	ENEMYSTATE_NOMAL = 0, // 通常ダメージ
	ENEMYSTATE_DAMAGE,//ダメージ状態
	//ENEMYSTATE_DEATH,//死亡状態
	ENEMYSTATE_MAX

}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//位置
	D3DXVECTOR3 move;	//移動
	D3DCOLOR col;		//頂点カラー
	int nType;			//種類
	int CountLife;	//出現時間
	float fWindth;		//幅
	float fHeight;		//高さ
	bool bUse;			//使用されているかどうか
	ENEMYSTATE state;	//敵の状態
	int nCounterState;  //状態管理のカウンター
	int nLife;			//体力
	int nCounterMove;   //アニメーションカウンター
	int nCounterAnim;   //アニメーションカウンター
	int nPatternAnim;   //アニメーションパターンNo

}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight,int nLife);
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);


#endif
