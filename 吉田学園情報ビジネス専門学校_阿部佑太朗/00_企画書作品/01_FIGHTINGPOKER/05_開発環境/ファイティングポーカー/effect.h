//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author :
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// エフェクトの種類
	EFFECTTYPE_GUARD = 0,	// ガード
	EFFECTTYPE_HIT_000,		// ヒット弱
	EFFECTTYPE_HIT_001,		// ヒット強
	EFFECTTYPE_SMOKE_001,	// 煙[ジャンプ時]
	EFFECTTYPE_SMOKE_002,	// 煙[着地時]
	EFFECTTYPE_MAX			// 種類の総数
} EFFECTTYPE;

typedef enum
{// エフェクトのサイズ変化の種類
	EFFECTSIZE_NONE = 0,	// 変わらない
	EFFECTSIZE_UP,			// 拡大
	EFFECTSIZE_DOWN,		// 縮小
	EFFECTSIZE_MAX			// 種類の総数
} EFFECTSIZE;

typedef struct
{
	D3DXMATRIX	mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR	col;		// 色
	float		fRadius_X;	// 半径(大きさ)
	float		fRadius_Y;	// 半径(大きさ)
	float		fClear;		// 透過
	int			nLife;		// 表示時間(寿命)
	EFFECTTYPE	type;		// 種類
	EFFECTSIZE	size;		// サイズ変化の種類
	bool		bUse;		// 使用しているかどうか
} EFFECT;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, EFFECTTYPE type);

#endif
