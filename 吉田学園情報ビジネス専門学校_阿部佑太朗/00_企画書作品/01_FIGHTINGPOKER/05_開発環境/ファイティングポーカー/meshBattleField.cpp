//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッシュバトルフィールド処理 [meshBattleField.cpp]
// Author : 圷和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "meshBattleField.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	POLYGON_TEX_000 = 0,	// ポリゴンテクスチャ000
	POLYGON_TEX_MAX,		// 総数
}MeshBattleFieldTexName;

typedef struct
{
	char *pFilename;	// ファイル名
} MeshBattleFieldTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	float fWidth;			// 幅
	float fDepth;			// 奥
	int nXBlock;			// X方向のブロック数
	int nZBlock;			// Y方向のブロック数
}MeshBattleFieldInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMeshBattleField(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexMeshBattleField(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9			g_apTextureMeshBattleField[POLYGON_TEX_MAX] = {};	// テクスチャへのポインタ

MeshBattleField g_aMeshBattleField[MAX_MESHBATTLEFIELD];				// メッシュフィールドの情報

// 読み込むテクスチャ名の設定
MeshBattleFieldTexInfo g_apTextureMeshBattleFieldInfo[POLYGON_TEX_MAX] =
{
	{ "data//TEXTURE//Floor001.jpg" },		// テクスチャ0
};

MeshBattleFieldInfo g_aMeshBattleFieldInfo[] =
{	//	位置,								向き,									幅,			奥,			X数		Z数
	{ D3DXVECTOR3(0.0f, 0.0f, 600.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		12,		20 },
	/*{ D3DXVECTOR3(0.0f, 0.0f, 400.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		2,		4 },
	{ D3DXVECTOR3(0.0f, 0.0f, 600.0f),		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			100.0f,		100.0f,		4,		4 },*/
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMeshBattleField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	for (int nCntMeshBattleFieldTex = 0; nCntMeshBattleFieldTex < POLYGON_TEX_MAX; nCntMeshBattleFieldTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMeshBattleFieldInfo[nCntMeshBattleFieldTex].pFilename,
			&g_apTextureMeshBattleField[nCntMeshBattleFieldTex]);
	}

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshBattleField[nCntMeshBattleField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshBattleField[nCntMeshBattleField].nXBlock = 0;
		g_aMeshBattleField[nCntMeshBattleField].nZBlock = 0;
		g_aMeshBattleField[nCntMeshBattleField].fWidth = 0.0f;
		g_aMeshBattleField[nCntMeshBattleField].fDepth = 0.0f;
		g_aMeshBattleField[nCntMeshBattleField].nNumVertex = 0;
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex = 0;
		g_aMeshBattleField[nCntMeshBattleField].nNumPolygon = 0;
		g_aMeshBattleField[nCntMeshBattleField].nTexType = 0;
	}

	// INFO
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < sizeof g_aMeshBattleFieldInfo / sizeof(MeshBattleFieldInfo); nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].pos = g_aMeshBattleFieldInfo[nCntMeshBattleField].pos;
		g_aMeshBattleField[nCntMeshBattleField].rot = g_aMeshBattleFieldInfo[nCntMeshBattleField].rot;
		g_aMeshBattleField[nCntMeshBattleField].fDepth = g_aMeshBattleFieldInfo[nCntMeshBattleField].fDepth;
		g_aMeshBattleField[nCntMeshBattleField].fWidth = g_aMeshBattleFieldInfo[nCntMeshBattleField].fWidth;
		g_aMeshBattleField[nCntMeshBattleField].nXBlock = g_aMeshBattleFieldInfo[nCntMeshBattleField].nXBlock;
		g_aMeshBattleField[nCntMeshBattleField].nZBlock = g_aMeshBattleFieldInfo[nCntMeshBattleField].nZBlock;
	}

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// インデックス数計算
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex = 2 + g_aMeshBattleField[nCntMeshBattleField].nXBlock * 2;
		g_aMeshBattleField[nCntMeshBattleField].nNumIndex += (g_aMeshBattleField[nCntMeshBattleField].nNumIndex + 2) * (g_aMeshBattleField[nCntMeshBattleField].nZBlock - 1);

		// ポリゴン数計算
		g_aMeshBattleField[nCntMeshBattleField].nNumPolygon = (g_aMeshBattleField[nCntMeshBattleField].nXBlock * g_aMeshBattleField[nCntMeshBattleField].nZBlock) * 2 + 4 * (g_aMeshBattleField[nCntMeshBattleField].nZBlock - 1);

		// 頂点数計算
		g_aMeshBattleField[nCntMeshBattleField].nNumVertex = (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)*(g_aMeshBattleField[nCntMeshBattleField].nZBlock + 1);
	}

	// 頂点情報の作成
	MakeVertexMeshBattleField(pDevice);

	// インデックス情報の作成
	MakeIndexMeshBattleField(pDevice);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMeshBattleField(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < POLYGON_TEX_MAX; nCntTex++)
	{
		if (g_apTextureMeshBattleField[nCntTex] != NULL)
		{
			g_apTextureMeshBattleField[nCntTex]->Release();
			g_apTextureMeshBattleField[nCntTex] = NULL;
		}
	}
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// 頂点バッファの開放
		if (g_aMeshBattleField[nCntMeshBattleField].pVtxBuff != NULL)
		{
			g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Release();
			g_aMeshBattleField[nCntMeshBattleField].pVtxBuff = NULL;
		}

		// インデックスバッファの開放
		if (g_aMeshBattleField[nCntMeshBattleField].pIdxBuff != NULL)
		{
			g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Release();
			g_aMeshBattleField[nCntMeshBattleField].pIdxBuff = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMeshBattleField(void)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		g_aMeshBattleField[nCntMeshBattleField].posOld = g_aMeshBattleField[nCntMeshBattleField].pos;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMeshBattleField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot,mtxTrans;					// 計算用マトリックス距離

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld);

		// 回転を反映	Y,X,Zの順番が大切
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshBattleField[nCntMeshBattleField].rot.y, g_aMeshBattleField[nCntMeshBattleField].rot.x, g_aMeshBattleField[nCntMeshBattleField].rot.z);
		D3DXMatrixMultiply(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aMeshBattleField[nCntMeshBattleField].pos.x, g_aMeshBattleField[nCntMeshBattleField].pos.y, g_aMeshBattleField[nCntMeshBattleField].pos.z);
		D3DXMatrixMultiply(&g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshBattleField[nCntMeshBattleField].mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_aMeshBattleField[nCntMeshBattleField].pVtxBuff, 0, sizeof(VERTEX_3D));

		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_aMeshBattleField[nCntMeshBattleField].pIdxBuff);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureMeshBattleField[0]);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshBattleField[nCntMeshBattleField].nNumVertex, 0, g_aMeshBattleField[nCntMeshBattleField].nNumPolygon);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMeshBattleField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{
		// 頂点バッファを生成
		// 頂点情報の作成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshBattleField[nCntMeshBattleField].nNumVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aMeshBattleField[nCntMeshBattleField].pVtxBuff,
			NULL);

		VERTEX_3D *pVtx;		// 頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		// 頂点情報の設定	座標の直接指定はここでは基本的にはしない(g_pos~~等を足し引きはしないD3DXMatrixTranslationでやってる
		for (int nCntPos = 0; nCntPos < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntPos++)
		{
			pVtx[nCntPos].pos = D3DXVECTOR3(float(-((g_aMeshBattleField[nCntMeshBattleField].nXBlock * g_aMeshBattleField[nCntMeshBattleField].fWidth) / 2) + g_aMeshBattleField[nCntMeshBattleField].fWidth * (nCntPos % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1))),
				0.0f,
				float((g_aMeshBattleField[nCntMeshBattleField].nZBlock * g_aMeshBattleField[nCntMeshBattleField].fDepth) / 2 - g_aMeshBattleField[nCntMeshBattleField].fDepth * (nCntPos / (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1))));
		}

		// 法線の設定　法線は「1」にしなくてはならない？「1.0」以下にしなければならない？
		for (int nCntNor = 0; nCntNor < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntNor++)
		{
			pVtx[nCntNor].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		// 頂点カラーの設定
		for (int nCntCol = 0; nCntCol < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntCol++)
		{
			pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// テクスチャの設定
		for (int nCntTex = 0; nCntTex < g_aMeshBattleField[nCntMeshBattleField].nNumVertex; nCntTex++)
		{
			pVtx[nCntTex].tex = D3DXVECTOR2(1.0f * (nCntTex % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)),
				1.0f * (nCntTex / (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)));
		}


		// 頂点バッファをアンロックする
		g_aMeshBattleField[nCntMeshBattleField].pVtxBuff->Unlock();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// インデックス情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeIndexMeshBattleField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{


		// インデックスバッファを生成
		// インデックス情報の作成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshBattleField[nCntMeshBattleField].nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,			// 一つの数字に2バイトしか使わない
			D3DPOOL_MANAGED,
			&g_aMeshBattleField[nCntMeshBattleField].pIdxBuff,
			NULL);

		WORD *pIdx;				// インデックスデータへのポインタ

		// インデックスバッファをロックし、インデックスデータへのポインタを取得
		g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// インデックスの設定
		for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshBattleField[nCntMeshBattleField].nNumIndex; nCntIdx += 2)
		{
			if ((nCntIdx / 2) % (g_aMeshBattleField[nCntMeshBattleField].nXBlock + 2) == g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1)
			{
				pIdx[nCntIdx] = nCntPos - 1;
				pIdx[nCntIdx + 1] = nCntPos + g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1;
			}
			else
			{
				pIdx[nCntIdx] = nCntPos + g_aMeshBattleField[nCntMeshBattleField].nXBlock + 1;
				pIdx[nCntIdx + 1] = nCntPos;

				nCntPos++;
			}
		}


		// 頂点バッファをアンロックする
		g_aMeshBattleField[nCntMeshBattleField].pIdxBuff->Unlock();
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// メッシュフィールドの当たり判定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionMeshBattleField(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fRadius)
{
	bool bLand = false;

	for (int nCntMeshBattleField = 0; nCntMeshBattleField < MAX_MESHBATTLEFIELD; nCntMeshBattleField++)
	{

			// 当たり判定
		if (pPos->x + fRadius > g_aMeshBattleField[nCntMeshBattleField].pos.x - (g_aMeshBattleField[nCntMeshBattleField].fWidth * g_aMeshBattleField[nCntMeshBattleField].nXBlock) / 2
			&& pPos->x - fRadius < g_aMeshBattleField[nCntMeshBattleField].pos.x + (g_aMeshBattleField[nCntMeshBattleField].fWidth * g_aMeshBattleField[nCntMeshBattleField].nXBlock) / 2
			&& pPos->z + fRadius > g_aMeshBattleField[nCntMeshBattleField].pos.z - (g_aMeshBattleField[nCntMeshBattleField].fDepth * g_aMeshBattleField[nCntMeshBattleField].nZBlock) / 2
			&& pPos->z - fRadius < g_aMeshBattleField[nCntMeshBattleField].pos.z + (g_aMeshBattleField[nCntMeshBattleField].fDepth * g_aMeshBattleField[nCntMeshBattleField].nZBlock) / 2)
		{ // XZが範囲内
			if (pPos->y < g_aMeshBattleField[nCntMeshBattleField].pos.y
				&& pPosOld->y >= g_aMeshBattleField[nCntMeshBattleField].posOld.y)
			{ // Y+から
				pPos->y = g_aMeshBattleField[nCntMeshBattleField].pos.y;
				pMove->y = 0;
				bLand = true;
			}
		}

	}

	return bLand;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// メッシュフィールドの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
MeshBattleField *GetMeshBattleField(void)
{
	return &g_aMeshBattleField[0];
}