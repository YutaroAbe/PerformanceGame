//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// オブジェクト処理 [gameobject.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_GAMEOBJECT			(64)
#define MAX_GAMEOBJECT_TEX		(6)		// オブジェクト一つに対するテクスチャの最大数

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	GAMEOBJECTCATEGORY_00 = 0,		// ブロック
	GAMEOBJECTCATEGORY_01,			// ブロック
	GAMEOBJECTCATEGORY_02,			// ブロック
	GAMEOBJECTCATEGORY_03,			// ブロック
	GAMEOBJECTCATEGORY_04,			// ブロック
	GAMEOBJECTCATEGORY_05,			// ブロック
	GAMEOBJECTCATEGORY_06,			// ブロック
	GAMEOBJECTCATEGORY_07,			// ブロック
	GAMEOBJECTCATEGORY_08,			// ブロック
	GAMEOBJECTCATEGORY_09,			// ブロック
	GAMEOBJECTCATEGORY_10,			// ブロック
	GAMEOBJECTCATEGORY_MAX				// 総数
}GAMEOBJECTCATEGORY;


typedef struct
{
	LPD3DXMESH pMesh;				// メッシュ（頂点の集まり）情報へのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアル情報へのポインタ
	DWORD nNumMat;					// マテリアル情報の数
	LPDIRECT3DTEXTURE9 pTexture[MAX_GAMEOBJECT_TEX];	// オブジェクト一体に対するテクスチャ
	char *pFilename;				// ファイル名
	D3DXVECTOR3 vtxMin;				// 頂点座標の最小値
	D3DXVECTOR3	vtxMax;				// 頂点座標の最大値
}GameObjectModelData;

typedef struct
{
	D3DXVECTOR3	pos;				// 位置（中心座標）
	D3DXVECTOR3	posOld;				// 前回位置（中心座標）
	D3DXVECTOR3	move;				// 移動量
	D3DXCOLOR col;					// 色
	D3DXVECTOR3	rot;				// 向き
	D3DXMATRIX	mtxWorldGameObject;	// ワールドマトリックス
	int ModelType;					// 使用するモデルの種類
	bool bUse;						// 使用しているかどうか
	bool bDisp;						// 表示するかどうか
}GameObject;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitGameObject(void);
void UninitGameObject(void);
void UpdateGameObject(void);
void DrawGameObject(void);
void SetGameObject(D3DXVECTOR3 pos, int ModelType);
GameObject *GetGameObject(void);
GameObjectModelData *GetGameObjectModel(void);
void LoadModelGameObject(void);
#endif
