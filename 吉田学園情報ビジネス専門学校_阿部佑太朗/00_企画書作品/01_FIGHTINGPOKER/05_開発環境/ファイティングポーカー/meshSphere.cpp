//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッシュスフィア処理 [meshSphere.cpp]
// Author : 圷和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "meshSphere.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESHSPHERE_SMALL_BLOCK_NUM	(32)
#define MESHSPHERE_LARGE_BLOCK_NUM	(64)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;	// インデックスバッファのポインタ
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 rot;					// 向き
	D3DXCOLOR col;						// 色
	D3DXMATRIX	mtxWorld;				// ワールドマトリックス
	float fRadius;						// 半径
	int nVBlock;						// X方向のブロック数
	int nHBlock;						// Y方向のブロック数
	int nNumVertex;						// 頂点数
	int nNumIndex;						// インデックス数
	int nNumPolygon;					// ポリゴン数
	int nTexType;						// テクスチャー種類
	bool bInside;						// 内側かどうか
	bool bUp;							// 上向きかどうか
	bool bUse;							// 使用しているかどうか
	bool bDisp;							// 表示するかどうか
	MESHSPHERE_TYPE type;				// 種別
}MeshSphere;

typedef enum
{
	POLYGON_TEX_000 = 0,	// ポリゴンテクスチャ000
	POLYGON_TEX_MAX,		// 総数
}MeshSphereTexName;

typedef struct
{
	char *pFilename;	// ファイル名
} MeshSphereTexInfo;
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexMeshSphere(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9			g_apTextureMeshSphere[POLYGON_TEX_MAX] = {};	// テクスチャへのポインタ

MeshSphere g_aMeshSphere[MAX_MESHSPHERE];				// メッシュドームの情報

// 読み込むテクスチャ名の設定
MeshSphereTexInfo g_apTextureMeshSphereInfo[POLYGON_TEX_MAX] =
{
	{ "data//TEXTURE//.png" },		// テクスチャ0
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャの読み込み
	for (int nCntMeshSphereTex = 0; nCntMeshSphereTex < POLYGON_TEX_MAX; nCntMeshSphereTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMeshSphereInfo[nCntMeshSphereTex].pFilename,
			&g_apTextureMeshSphere[nCntMeshSphereTex]);
	}

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		g_aMeshSphere[nCntMeshSphere].pVtxBuff = NULL;
		g_aMeshSphere[nCntMeshSphere].pIdxBuff = NULL;
		g_aMeshSphere[nCntMeshSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshSphere[nCntMeshSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aMeshSphere[nCntMeshSphere].nVBlock = 0;
		g_aMeshSphere[nCntMeshSphere].nHBlock = 0;
		g_aMeshSphere[nCntMeshSphere].fRadius = 0.0f;
		g_aMeshSphere[nCntMeshSphere].nNumVertex = 0;
		g_aMeshSphere[nCntMeshSphere].nNumIndex = 0;
		g_aMeshSphere[nCntMeshSphere].nNumPolygon = 0;
		g_aMeshSphere[nCntMeshSphere].nTexType = 0;
		g_aMeshSphere[nCntMeshSphere].bInside = false;
		g_aMeshSphere[nCntMeshSphere].bUp = false;
		g_aMeshSphere[nCntMeshSphere].bUse = false;
		g_aMeshSphere[nCntMeshSphere].bDisp = false;
		g_aMeshSphere[nCntMeshSphere].type = MESHSPHERE_TYPE_ATTACK;
	}
	// 配置メッシュの情報
	/*g_aMeshSphere[0].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_aMeshSphere[0].nVBlock = 64;
	g_aMeshSphere[0].nHBlock = 64;
	g_aMeshSphere[0].fRadius = 10.0f;
	g_aMeshSphere[0].bInside = true;
	g_aMeshSphere[0].bUse = true;
	g_aMeshSphere[0].bDisp = true;

	g_aMeshSphere[1].pos = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
	g_aMeshSphere[1].nVBlock = 64;
	g_aMeshSphere[1].nHBlock = 64;
	g_aMeshSphere[1].fRadius = 10.0f;
	g_aMeshSphere[1].bInside = true;
	g_aMeshSphere[1].bUse = true;
	g_aMeshSphere[1].bDisp = true;*/


	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		// インデックス数計算
		g_aMeshSphere[nCntMeshSphere].nNumIndex = 2 + g_aMeshSphere[nCntMeshSphere].nVBlock * 2;
		g_aMeshSphere[nCntMeshSphere].nNumIndex += (g_aMeshSphere[nCntMeshSphere].nNumIndex + 2) * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

		// ポリゴン数計算
		g_aMeshSphere[nCntMeshSphere].nNumPolygon = (g_aMeshSphere[nCntMeshSphere].nVBlock * g_aMeshSphere[nCntMeshSphere].nHBlock) * 2 + 4 * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

		// 頂点数計算
		g_aMeshSphere[nCntMeshSphere].nNumVertex = (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)*(g_aMeshSphere[nCntMeshSphere].nHBlock + 1);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMeshSphere(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < POLYGON_TEX_MAX; nCntTex++)
	{
		if (g_apTextureMeshSphere[nCntTex] != NULL)
		{
			g_apTextureMeshSphere[nCntTex]->Release();
			g_apTextureMeshSphere[nCntTex] = NULL;
		}
	}

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		// 頂点バッファの開放
		if (g_aMeshSphere[nCntMeshSphere].pVtxBuff != NULL)
		{
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Release();
			g_aMeshSphere[nCntMeshSphere].pVtxBuff = NULL;
		}

		// インデックスバッファの開放
		if (g_aMeshSphere[nCntMeshSphere].pIdxBuff != NULL)
		{
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Release();
			g_aMeshSphere[nCntMeshSphere].pIdxBuff = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMeshSphere(void)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse == true)
		{
			VERTEX_3D *pVtx;		// 頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点カラーの設定
			for (int nCntCol = 0; nCntCol < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntCol++)
			{
				pVtx[nCntCol].col = g_aMeshSphere[nCntMeshSphere].col;
			}

			// 頂点バッファをアンロックする
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Unlock();

		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot,mtxTrans;					// 計算用マトリックス距離

	// ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse && g_aMeshSphere[nCntMeshSphere].bDisp)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshSphere[nCntMeshSphere].mtxWorld);

			// 回転を反映	Y,X,Zの順番が大切
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshSphere[nCntMeshSphere].rot.y, g_aMeshSphere[nCntMeshSphere].rot.x, g_aMeshSphere[nCntMeshSphere].rot.z);
			D3DXMatrixMultiply(&g_aMeshSphere[nCntMeshSphere].mtxWorld, &g_aMeshSphere[nCntMeshSphere].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshSphere[nCntMeshSphere].pos.x, g_aMeshSphere[nCntMeshSphere].pos.y, g_aMeshSphere[nCntMeshSphere].pos.z);
			D3DXMatrixMultiply(&g_aMeshSphere[nCntMeshSphere].mtxWorld, &g_aMeshSphere[nCntMeshSphere].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshSphere[nCntMeshSphere].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_aMeshSphere[nCntMeshSphere].pVtxBuff, 0, sizeof(VERTEX_3D));

			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_aMeshSphere[nCntMeshSphere].pIdxBuff);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureMeshSphere[0]);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshSphere[nCntMeshSphere].nNumVertex, 0, g_aMeshSphere[nCntMeshSphere].nNumPolygon);
		}
	}
	// ライトオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// メッシュスフィアの作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点情報の作成
	MakeVertexMeshSphere(pDevice);

	// インデックス情報の作成
	MakeIndexMeshSphere(pDevice);
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse)
		{
			// 頂点バッファを生成
			// 頂点情報の作成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshSphere[nCntMeshSphere].nNumVertex,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_3D,
				D3DPOOL_MANAGED,
				&g_aMeshSphere[nCntMeshSphere].pVtxBuff,
				NULL);

			VERTEX_3D *pVtx;		// 頂点情報へのポインタ

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


			// 頂点情報の設定	座標の直接指定はここでは基本的にはしない(g_pos~~等を足し引きはしないD3DXMatrixTranslationでやってる
			for (int nCntPos = 0; nCntPos < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntPos++)
			{
				int nInside = 1;
				if (g_aMeshSphere[nCntMeshSphere].bInside == true)
				{
					nInside *= -1;
				}

				int nTest = (g_aMeshSphere[nCntMeshSphere].nNumVertex / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)) - (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1));


				//if (nCntPos < g_aMeshSphere[nCntMeshSphere].nNumVertex / 2)
				{
					pVtx[nCntPos].pos =
						D3DXVECTOR3(sinf(-(D3DX_PI*nInside) / 2.0f - ((-(D3DX_PI*nInside) * 2.0f) / g_aMeshSphere[nCntMeshSphere].nVBlock) * (nCntPos % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * (sinf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius),
							cosf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius,
							cosf(-(D3DX_PI*nInside) / 2.0f - ((-(D3DX_PI*nInside) * 2.0f) / g_aMeshSphere[nCntMeshSphere].nVBlock) * float(nCntPos % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * (sinf((D3DX_PI / g_aMeshSphere[nCntMeshSphere].nHBlock) * (nCntPos / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1))) * g_aMeshSphere[nCntMeshSphere].fRadius));
				}
			}

			// 法線の設定　法線は「1」にしなくてはならない？「1.0」以下にしなければならない？
			for (int nCntNor = 0; nCntNor < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntNor++)
			{
				D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].pos);		// 正規化する
			}

			// 頂点カラーの設定
			for (int nCntCol = 0; nCntCol < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntCol++)
			{
				pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// テクスチャの設定
			for (int nCntTex = 0; nCntTex < g_aMeshSphere[nCntMeshSphere].nNumVertex; nCntTex++)
			{
				pVtx[nCntTex].tex = D3DXVECTOR2(1.0f / 2.0f / g_aMeshSphere[nCntMeshSphere].nVBlock * (nCntTex % (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)) * 2, // 最後の*2はその場しのぎ
					1.0f / 2.0f / g_aMeshSphere[nCntMeshSphere].nHBlock * (nCntTex / (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)));
			}


			// 頂点バッファをアンロックする
			g_aMeshSphere[nCntMeshSphere].pVtxBuff->Unlock();
		}
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// インデックス情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeIndexMeshSphere(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (g_aMeshSphere[nCntMeshSphere].bUse)
		{
			// インデックスバッファを生成
			// インデックス情報の作成
			pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshSphere[nCntMeshSphere].nNumIndex,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,			// 一つの数字に2バイトしか使わない
				D3DPOOL_MANAGED,
				&g_aMeshSphere[nCntMeshSphere].pIdxBuff,
				NULL);

			WORD *pIdx;				// インデックスデータへのポインタ

			// インデックスバッファをロックし、インデックスデータへのポインタを取得
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

			// インデックスの設定
			for (int nCntIdx = 0, nCntPos = 0; nCntIdx < g_aMeshSphere[nCntMeshSphere].nNumIndex; nCntIdx += 2)
			{
				if ((nCntIdx / 2) % (g_aMeshSphere[nCntMeshSphere].nVBlock + 2) == g_aMeshSphere[nCntMeshSphere].nVBlock + 1)
				{
					pIdx[nCntIdx] = nCntPos - 1;
					pIdx[nCntIdx + 1] = nCntPos + g_aMeshSphere[nCntMeshSphere].nVBlock + 1;
				}
				else
				{
					pIdx[nCntIdx] = nCntPos + g_aMeshSphere[nCntMeshSphere].nVBlock + 1;
					pIdx[nCntIdx + 1] = nCntPos;

					nCntPos++;
				}
			}

			// 頂点バッファをアンロックする
			g_aMeshSphere[nCntMeshSphere].pIdxBuff->Unlock();
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スフィアの設定処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int SetSphere(D3DXVECTOR3 const pos, float const fRadius, MESHSPHERE_TYPE const type, bool const bInside)
{
	int nCntMeshSphere;

	for (nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		if (!g_aMeshSphere[nCntMeshSphere].bUse)
		{// 使用していない場合
			g_aMeshSphere[nCntMeshSphere].pos = pos;
			g_aMeshSphere[nCntMeshSphere].fRadius = fRadius;
			g_aMeshSphere[nCntMeshSphere].type = type;
			g_aMeshSphere[nCntMeshSphere].bInside = bInside;
			if (fRadius < 1000)
			{ // 一定の大きさ内ならポリゴン数を少なくする
				g_aMeshSphere[nCntMeshSphere].nVBlock = MESHSPHERE_SMALL_BLOCK_NUM;
				g_aMeshSphere[nCntMeshSphere].nHBlock = MESHSPHERE_SMALL_BLOCK_NUM;
			}
			else
			{
				g_aMeshSphere[nCntMeshSphere].nVBlock = MESHSPHERE_LARGE_BLOCK_NUM;
				g_aMeshSphere[nCntMeshSphere].nHBlock = MESHSPHERE_LARGE_BLOCK_NUM;
			}
			g_aMeshSphere[nCntMeshSphere].bUse = true;

			// インデックス数計算
			g_aMeshSphere[nCntMeshSphere].nNumIndex = 2 + g_aMeshSphere[nCntMeshSphere].nVBlock * 2;
			g_aMeshSphere[nCntMeshSphere].nNumIndex += (g_aMeshSphere[nCntMeshSphere].nNumIndex + 2) * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

			// ポリゴン数計算
			g_aMeshSphere[nCntMeshSphere].nNumPolygon = (g_aMeshSphere[nCntMeshSphere].nVBlock * g_aMeshSphere[nCntMeshSphere].nHBlock) * 2 + 4 * (g_aMeshSphere[nCntMeshSphere].nHBlock - 1);

			// 頂点数計算
			g_aMeshSphere[nCntMeshSphere].nNumVertex = (g_aMeshSphere[nCntMeshSphere].nVBlock + 1)*(g_aMeshSphere[nCntMeshSphere].nHBlock + 1);

			switch (g_aMeshSphere[nCntMeshSphere].type)
			{
			case MESHSPHERE_TYPE_ATTACK:
				g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
				break;
			case MESHSPHERE_TYPE_DEFENSE:
				g_aMeshSphere[nCntMeshSphere].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
				g_aMeshSphere[nCntMeshSphere].bDisp = true;
				break;
			}
			break;
		}
	}
	return nCntMeshSphere;
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スフィアの移動処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPositionSphere(int const nIDSphere, D3DXVECTOR3 const pos)
{
	if (g_aMeshSphere[nIDSphere].bUse == true)
	{
		g_aMeshSphere[nIDSphere].pos = pos;

		//g_aMeshSphere[nIDSphere].pos.z = -10.0f;
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スフィアの表示切替処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetDispSphere(int const nIDSphere, bool bDisp)
{
	if (g_aMeshSphere[nIDSphere].bUse == true)
	{
		g_aMeshSphere[nIDSphere].bDisp = bDisp;
	}
}