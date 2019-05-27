//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッシュバトルフィールド処理 [meshBattleField.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _MESHBATTLEFIELD_H_
#define _MESHBATTLEFIELD_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_MESHBATTLEFIELD	(1)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// インデックスバッファのポインタ
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 posOld;					// 前回位置
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX	mtxWorld;				// ワールドマトリックス
	float fWidth;						// 幅
	float fDepth;						// 奥行
	int nXBlock;						// X方向のブロック数
	int nZBlock;						// Z方向のブロック数
	int nNumVertex;						// 頂点数
	int nNumIndex;						// インデックス数
	int nNumPolygon;					// ポリゴン数
	int nTexType;						// テクスチャー種類
}MeshBattleField;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitMeshBattleField(void);
void UninitMeshBattleField(void);
void UpdateMeshBattleField(void);
void DrawMeshBattleField(void);

MeshBattleField *GetMeshBattleField(void);
bool CollisionMeshBattleField(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fRadius);

#endif
