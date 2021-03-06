//=============================================================================
//
// 3DUI処理 [3DUi.h]
// Author : Ebina Riku
//
//=============================================================================
#ifndef _3DUI_H_
#define _3DUI_H_

#include "main.h"

//=============================================================================
// 列挙型定義
//=============================================================================
typedef enum
{
	UI_3D_CURSOR = 0,
	UI_3D_LOCKMARK,
	UI_3D_MAX
}UI3DTYPE;
//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	LPD3DXMESH pMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9 pTexture;	// テクスチャのポインタ
	DWORD nNumMat;					// マテリアル情報の数
}P3DUI;

typedef struct
{
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 move;					// 移動
	D3DXVECTOR3 rot;					// 向き
	D3DXVECTOR2 tex;					// オブジェクトのテクスチャ情報
	D3DXMATRIX mtxWorldUI;			// ワールドマトリックス
	int nIdShadow;						// 影の番号
	bool bUse;							// 使用状況
	UI3DTYPE type;
}UI_3D;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Init3DUI(void);
void Uninit3DUI(void);
void Update3DUI(void);
void Draw3DUI(void);
#endif
