//=============================================================================
//
// テクスチャアニメーション処理 [textureanim.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _TEXTUREANIM_H_
#define _TEXTUREANIM_H_

#include "main.h"

//*****************************************************************************
//	構造体
//*****************************************************************************
typedef enum
{
	TEXANIM_NONE = 0,
	TEXANIM_GRAVITY,		//	グラビティバインド
	TEXANIM_FISSURES,		//	地割れ
	TEXANIM_RAIZIN_R,		//	ライジン右向き
	TEXANIM_RAIZIN_L,		//	ライジン左向き
	TEXANIM_GOD,			//	神のいかずち
	TEXANIM_DARK,			//	ダークマター
	TEXANIM_MAX				//	テクスチャアニメーションの最大数
}TEXANIMTYPA;

typedef struct
{
	TEXANIMTYPA type;		//	テクスチャアニメーションの種類
	D3DXVECTOR3 pos;		// 位置
	D3DXMATRIX	mtxWorld;	// ワールドマトリックス
	float fRadius_X;		// 幅
	float fRadius_Y;		// 高さ
	D3DXCOLOR col;			// 色
	int nCounterAnim;		// アニメーションカウンター
	int nPatternAnim;		// アニメーションパターンNO.
	int nLife;				// ポリゴンの出現時間
	bool bUse;				// 使用しているかどうか
	int nSetMax;			// ポリゴンの数
} Explosion;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//		[	グラビティバインド	]
#define GRAVITY_CNT_FPS					(6)											//	[	グラビティバインド	]更新するフレーム数
#define	GRAVITY_MAX_PATTERN				(2)											//	[	グラビティバインド	]パターンの最大数
#define GRAVITY_TEX_WIDTH				(1.0f / GRAVITY_MAX_PATTERN)				//	[	グラビティバインド	]テクスチャの幅
#define GRAVITY_COLOR					(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			//	[	グラビティバインド	]色
#define GRAVITY_RADIUS_X				(50.0f)										//　[	グラビティバインド	]の半径
#define GRAVITY_RADIUS_Y				(100.0f)										//	[	グラビティバインド	]の高さ
#define GRAVITY_LIFE					(60)										//	[	グラビティバインド	]の寿命
#define GRAVITY_MOVE_X					(4.5f)										//	[	グラビティバインド	]の横に動き揺れる量
#define GRAVITY_MOVE_Y					(4.5f)										//	[	グラビティバインド	]の縦に動き揺れる量
//	[	地割れ	]
#define FISSURES_MAX_PATTERN			(6)											//	[	地割れ	]パターンの最大数
#define FISSURES_CNT_FPS				(8)											//	[	地割れ	]更新するフレーム数
#define FISSURES_TEX_WIDTH				(1.0f / FISSURES_MAX_PATTERN)				//	[	地割れ	]テクスチャの幅
#define FISSURES_COLOR					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	地割れ	]色
#define FISSURES_RADIUS_X				(100.0f)									//　[	地割れ	]の半径
#define FISSURES_RADIUS_Y				(150.0f)									//	[	地割れ	]の高さ
//	[	ライジンR向き	]
#define RAIZIN_MAX_PATTERN_R			(10)										//	[	ライジンR　]パターンの最大数
#define	RAIZIN_CNT_FPS_R				(4)											//	[	ライジンR　]更新するフレーム数
#define RAIZIN_TEX_WIDTH_R				(1.0f / RAIZIN_MAX_PATTERN_R)				//	[	ライジンR　]テクスチャの幅
#define RAIZIN_COLOR_R					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))			//	[	ライジンR　]色
#define RAIZIN_RADIUS_X_R				(100.0f)									//　[	ライジンR　]の幅
#define RAIZIN_RADIUS_Y_R				(60.0f)										//	[	ライジンR　]の高さ
//	[	ライジンL向き	]
#define RAIZIN_MAX_PATTERN_L			(10)										//	[	ライジンL　]パターンの最大数
#define	RAIZIN_CNT_FPS_L				(4)											//	[	ライジンL　]更新するフレーム数
#define RAIZIN_TEX_WIDTH_L				(1.0f / RAIZIN_MAX_PATTERN_L)				//	[	ライジンL　]テクスチャの幅
#define RAIZIN_COLOR_L					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))			//	[	ライジンL　]色
#define RAIZIN_RADIUS_X_L				(100.0f)									//　[	ライジンL　]の幅
#define RAIZIN_RADIUS_Y_L				(60.0f)										//	[	ライジンL　]の高さ
//	[	神のいかずち	]
#define GOD_MAX_PATTERN					(8)											//	[	神のいかずち　]パターンの最大数
#define	GOD_CNT_FPS						(8)											//	[	神のいかずち　]更新するフレーム数
#define GOD_TEX_WIDTH					(1.0f / GOD_MAX_PATTERN)					//	[	神のいかずち　]テクスチャの幅
#define GOD_COLOR						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	神のいかずち　]色
#define GOD_RADIUS_X					(120.0f)									//　[	神のいかずち　]の半径
#define GOD_RADIUS_Y					(270.0f)									//	[	神のいかずち　]の高さ
//	[	ダークマター	]
#define DARK_MAX_PATTERN				(10)										//	[	ダークマター　]パターンの最大数
#define DARK_CNT_FPS					(6)											//	[	ダークマター　]更新するフレーム数
#define DARK_TEX_WIDTH					(1.0f / DARK_MAX_PATTERN)					//	[	ダークマター　]テクスチャの幅
#define DARK_COLOR						(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//	[	ダークマター　]色
#define DARK_RADIUS_X					(60.0f)										//　[	ダークマター　]の半径
#define DARK_RADIUS_Y					(60.0f)										//	[	ダークマター　]の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTextureAnim(void);
void UninitTextureAnim(void);
void UpdateTextureAnim(void);
void DrawTextureAnim(void);
void SetTextureAnim(D3DXVECTOR3 pos, TEXANIMTYPA type);

#endif
