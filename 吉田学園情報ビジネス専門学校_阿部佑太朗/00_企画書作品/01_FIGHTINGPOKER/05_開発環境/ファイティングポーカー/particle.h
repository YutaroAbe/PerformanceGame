//========================================================================
//
// パーティクル処理 [particle.h]
// Author : YUTARO ABE
//
//========================================================================
#ifndef _PARTICL_H_
#define _PARTICL_H_

//************************************************************************
// インクルードファイル
//************************************************************************
#include "main.h"

//************************************************************************
// 構造体定義
//************************************************************************
typedef enum
{
	PARTICLETYPE_NONE = 0,
	PARTICLETYPE_DARKMATTER,
	PARTICLETYPE_STONE,
	PARTICLETYPE_MAX
}PARTICLETYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//	位置
	D3DXVECTOR3 nor;			//	法線ベクトル
	D3DXVECTOR3 move;			//	移動値
	D3DXCOLOR col;				//	色
	PARTICLETYPE Type;			//	種類
	D3DXVECTOR3 rot;			//	法線ベクトル
	D3DXMATRIX mtxWorld;		//	頂点カラー
	float fRadius;				//	半径(大きさ)
	float fLength;				//	距離
	int nTypeTx;
	int nLife;					//	表示時間(寿命)
	bool bUse;					//	使用しているかどうか
	int nSetMax;				//	パーティクルのポリゴン数の設定
} PARTICLE;

//************************************************************************
// プロトタイプ宣言
//************************************************************************
void InitParticle(void);			// エフェクト初期化処理
void UninitParticle(void);			// エフェクト終了処理
void UpdateParticle(void);			// エフェクト更新処理
void DrawParticle(void);			// エフェクト描画処理
void SetParticle(D3DXVECTOR3 pos,PARTICLETYPE Type);		// パーティクルの設定

#endif