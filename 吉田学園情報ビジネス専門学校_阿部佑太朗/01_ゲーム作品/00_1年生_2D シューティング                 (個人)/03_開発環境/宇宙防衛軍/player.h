//=============================================================================
//
// プレイヤーの処理 [Player.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _PLAYER_H_			//	2重インクルード防止のマクロ定義
#define _PLAYER_H_

//*****************************************************************************
//構造体
//*****************************************************************************
typedef enum
{//	プレイヤーの状態
	PLAYERSTATE_NOMAL = 0,		//	通常ダメージ
	PLAYERSTATE_DAMAGE,			//	ダメージ状態
	PLAYERSTATE_DEATH,			//	死亡状態
	PLAYERSTATE_END,			//
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//	位置
	D3DXVECTOR3 move;	//	動き
	PLAYERSTATE state;	//	状態
	int nCounterState;  //	状態管理のカウンター
	int nLife;			//	体力
	bool bDisp;			//	表示するかしないか｜初期はtreu
	int nType;			//	種類
}Player;


//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);		//初期化処理ポリゴン
void UninitPlayer(void);		//終了処理ポリゴン
void UpdatePlayer(void);	//更新処理ポリゴン
void DrawPlayer(void);		//描画処理ポリゴン
void HitPlayer(int nDamage);
void SetPlayer(D3DXVECTOR3 pos, int nType);
Player *GetPlayer(void);

#endif // !

