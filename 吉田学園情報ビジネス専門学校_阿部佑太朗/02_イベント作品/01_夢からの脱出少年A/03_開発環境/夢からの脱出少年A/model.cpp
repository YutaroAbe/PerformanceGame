//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "model.h"
#include "camera.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshModel[BLOCKCOLOR_MAX][MAX_NUM_MODEL] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatModel[BLOCKCOLOR_MAX][MAX_NUM_MODEL] = {};//マテリアル情報へのポインタ

MODEL g_Model[BLOCKCOLOR_MAX][MAX_NUM_MODEL];
//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPCSTR FileName[BLOCKCOLOR_MAX] = { MODEL_FILENAME0,
										MODEL_FILENAME1,
										MODEL_FILENAME2,
										MODEL_FILENAME3,
										MODEL_FILENAME4,
										MODEL_FILENAME5 };

	
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
		{
			// Xファイルの読み込み
			D3DXLoadMeshFromX(FileName[nCntCol],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatModel[nCntCol][nCntModel],
				NULL,
				&g_Model[nCntCol][nCntModel].NumMatModel,
				&g_pMeshModel[nCntCol][nCntModel]);

			/*当たり判定の設定*/
			SetModelVertex(nCntModel, nCntCol);
			//頂点数の取得

			// 位置・向きの初期設定
			g_Model[nCntCol][nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model[nCntCol][nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量・回転量の初期化
			g_Model[nCntCol][nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Model[nCntCol][nCntModel].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Model[nCntCol][nCntModel].bUse = false;

		}
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntMesh = 0; nCntMesh < MAX_NUM_MODEL; nCntMesh++)
		{
			// メッシュの解放
			if (g_pMeshModel[nCntCol][nCntMesh] != NULL)
			{
				g_pMeshModel[nCntCol][nCntMesh]->Release();
				g_pMeshModel[nCntCol][nCntMesh] = NULL;
			}
			/*テクスチャの解放*/
			//マテリアルの解放
			if (g_pBuffMatModel[nCntCol][nCntMesh] != NULL)
			{
				g_pBuffMatModel[nCntCol][nCntMesh]->Release();
				g_pBuffMatModel[nCntCol][nCntMesh] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntModel = 0; nCntModel < MAX_NUM_MODEL; nCntModel++)
		{
			if (g_Model[nCntCol][nCntModel].bUse == true)
			{

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Model[nCntCol][nCntModel].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Model[nCntCol][nCntModel].rot.y,
					g_Model[nCntCol][nCntModel].rot.x,
					g_Model[nCntCol][nCntModel].rot.z);

				D3DXMatrixMultiply(&g_Model[nCntCol][nCntModel].mtxWorld,
					&g_Model[nCntCol][nCntModel].mtxWorld,
					&mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans,
					g_Model[nCntCol][nCntModel].pos.x,
					g_Model[nCntCol][nCntModel].pos.y,
					g_Model[nCntCol][nCntModel].pos.z);

				D3DXMatrixMultiply(&g_Model[nCntCol][nCntModel].mtxWorld,
					&g_Model[nCntCol][nCntModel].mtxWorld,
					&mtxTrans);
				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCntCol][nCntModel].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCntCol][nCntModel]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Model[nCntCol][nCntModel].NumMatModel; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*テクスチャの設定*/
					pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

					// モデル(パーツ)の描画
					g_pMeshModel[nCntCol][nCntModel]->DrawSubset(nCntMat);
				}

				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}

		}
	}
}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax, 
	MODEL		**pModel)
{
	//変数宣言
	bool bLand = false;
	for (int nCntCol = 0; nCntCol < BLOCKCOLOR_MAX; nCntCol++)
	{
		for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
		{
			if (g_Model[nCntCol][nCntData].bUse == true)
			{
				if (g_Model[nCntCol][nCntData].VtxMin.z + g_Model[nCntCol][nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Model[nCntCol][nCntData].VtxMax.z + g_Model[nCntCol][nCntData].pos.z >= pPos->z + pVtxMin->z)
				{
					if (g_Model[nCntCol][nCntData].VtxMin.x + g_Model[nCntCol][nCntData].pos.x <= pPos->x + pVtxMax->x&&
						g_Model[nCntCol][nCntData].VtxMax.x + g_Model[nCntCol][nCntData].pos.x >= pPos->x + pVtxMin->x)
					{
						if (g_Model[nCntCol][nCntData].VtxMin.y + g_Model[nCntCol][nCntData].pos.y <= pPos->y + pVtxMin->y &&
							g_Model[nCntCol][nCntData].VtxMax.y + g_Model[nCntCol][nCntData].pos.y >= pOldPos->y + pVtxMin->y)
						{
							bLand = true;

							pMove->y = 0.0f;
							pPos->y = g_Model[nCntCol][nCntData].VtxMax.y + g_Model[nCntCol][nCntData].pos.y;
							*pModel = &g_Model[nCntCol][nCntData];

						}
					}
				}

			}
		}
	}
	return bLand;

}
//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetModelVertex(int nCntModel, int ColNum)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Model[ColNum][nCntModel].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Model[ColNum][nCntModel].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshModel[ColNum][nCntModel]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel[ColNum][nCntModel]->GetFVF());

	//頂点バッファのロック
	g_pMeshModel[ColNum][nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Model[ColNum][nCntModel].VtxMin.x > vtx.x)
		{
			g_Model[ColNum][nCntModel].VtxMin.x = vtx.x;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.x < vtx.x)
		{
			g_Model[ColNum][nCntModel].VtxMax.x = vtx.x;
		}

		//y
		if (g_Model[ColNum][nCntModel].VtxMin.y > vtx.y)
		{
			g_Model[ColNum][nCntModel].VtxMin.y = vtx.y;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.y < vtx.y)
		{
			g_Model[ColNum][nCntModel].VtxMax.y = vtx.y;
		}

		//z
		if (g_Model[ColNum][nCntModel].VtxMin.z > vtx.z)
		{
			g_Model[ColNum][nCntModel].VtxMin.z = vtx.z;
		}
		if (g_Model[ColNum][nCntModel].VtxMax.z < vtx.z)
		{
			g_Model[ColNum][nCntModel].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshModel[ColNum][nCntModel]->UnlockVertexBuffer();

}

//=============================================================================
// モデルの位置設定
//=============================================================================
void SetModel(D3DXVECTOR3 pos, BLOCKCOLOR col)
{
	for (int nCntData = 0; nCntData < MAX_NUM_MODEL; nCntData++)
	{
		if (g_Model[col][nCntData].bUse == false)
		{
			g_Model[col][nCntData].pos = pos;
			g_Model[col][nCntData].col = col;
			g_Model[col][nCntData].bUse = true;
			break;
		}
	}
}