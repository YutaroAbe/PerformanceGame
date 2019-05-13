//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"
//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef enum
{// プレイヤーの状態の種類
	PLAYERSTATE_NORMAL = 0,			// 通常状態
	PLAYERSTATE_DAMAGE,				// ダメージ状態
	PLAYERSTATE_DEATH,				// 死亡状態
	PLAYERSTATE_END,
	PLAYERSTATE_MAX					// 状態の総数
}PLAYERSTATE;

typedef enum
{// プレイヤーのモーションの種類
	PLAYERMOTIONTYPE_NEUTRAL = 0,	// ニュートラル
	PLAYERMOTIONTYPE_MOVE,			// 移動
	PLAYERMOTIONTYPE_MAX			// 種類の総数
}PLAYERMOTIONTYPE;

typedef struct
{// プレイヤーのモデルの情報
	LPD3DXMESH		pMesh = NULL;		// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMat = NULL;	// マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9	*pTex = NULL;	// テクスチャ情報へのポインタ
	D3DMATERIAL9	*pCol = NULL;		// 現在の色へのポインタ
	D3DMATERIAL9	*pColDef = NULL;	// デフォルトの色へのポインタ
	DWORD			nNumMat = 0;		// マテリアル情報の数
	D3DXMATRIX		mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3		posFarst;			// 初期の位置
	D3DXVECTOR3		pos;				// 位置
	D3DXVECTOR3		rot;				// 向き
	int				nIdxModelParent;	// 親モデルのインデックス
	char			aName[128];			// 読み込むモデルの名前
} PlayerModel;

typedef struct
{// プレイヤーのキーの情報
	D3DXVECTOR3	*aPos = NULL;	// 位置
	D3DXVECTOR3	*aRot = NULL;	// 向き
	int			nNumFrame;		// 更新するフレーム数
} PlayerKey;

typedef struct
{// プレイヤーのモーションの情報
	int			nLoop;					// ループするかどうか[ しない = 0, する = 1 ]
	int			nNumKey;				// キーの数
	PlayerKey	*aPlayerKey = NULL;		// キーの情報
} PlayerMotion;

typedef struct
{// プレイヤーの情報
	D3DXMATRIX			mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3			pos;					// 現在の位置
	D3DXVECTOR3			posOld;					// 前回の位置
	D3DXVECTOR3			move;					// 移動量
	D3DXVECTOR3			rot;					// 向き
	D3DXVECTOR3			rotDest;				// 目的の向き
	D3DXVECTOR3			vtxMin;					// 当たり判定の最小値
	D3DXVECTOR3			vtxMax;					// 当たり判定の最大値
	int					nNumModel;				// モデル数
	PlayerModel			*aPlayerModel = NULL;	// モデルの情報へのポインタ
	PlayerMotion		aPlayerMotion[PLAYERMOTIONTYPE_MAX];	// モーションの情報
	PLAYERMOTIONTYPE	motionType;				// 現在のモーションの種類
	int					nKey;					// 現在のキー
	int					nIdxShadow;				// 影の番号
	int					nLife;					// 体力
	int					nCntFrame;				// 経過フレーム
	int					nMaxCntFrame;			// 総合経過フレーム
	D3DXVECTOR3 Destrot;						// 目的の角度
	int					nCounterState = 0;		//状態管理のカウンター
	PLAYERSTATE			state;					// 状態
	int					nCntState;				// 状態管理のカウンター
	int					nCntEffect;				// エフェクトのカウンター
	bool				bJump;					// ジャンプ中かどうか
	bool				bDisp;					// 出現してるかどうか
	MODEL *pModel;

} Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);
Player *GetPlayer(void);

#endif
