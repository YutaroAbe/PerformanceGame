//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ゲームオブジェクト処理 [gameobject.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "gameobject.h"
#include "game.h"



//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_GAMEOBJECT_MODEL		(40)		// 読み込めるゲームオブジェクトモデルの最大数
#define GAMEOBJECT_LOADTXT_NAME			"data//TEXT//model_game.txt"			// オブジェクト配置のテキストファイル名
#define MAX_LOAD_LINE				(256)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffGameObject = NULL;	// 頂点バッファへのポインタ
GameObject	g_aGameObject[MAX_GAMEOBJECT];						// ゲームオブジェクトの情報
GameObjectModelData g_apGameObject[MAX_GAMEOBJECT_MODEL] = {};	// ゲームオブジェクトへのポインタ
int g_nGameObjectLoadNum = 0;

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitGameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		g_aGameObject[nCntGameObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].posOld = g_aGameObject[nCntGameObject].pos;
		g_aGameObject[nCntGameObject].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGameObject[nCntGameObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGameObject[nCntGameObject].ModelType = 0;
		g_aGameObject[nCntGameObject].bUse = false;
		g_aGameObject[nCntGameObject].bDisp = true;
	}

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT_MODEL; nCntGameObject++)
	{
		g_apGameObject[nCntGameObject].pFilename = NULL;
		g_apGameObject[nCntGameObject].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_apGameObject[nCntGameObject].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
	}
	LoadModelGameObject();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitGameObject(void)
{
	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT_MODEL; nCntGameObject++)
	{
		// テクスチャの開放
		for (int nCntTex = 0; nCntTex < MAX_GAMEOBJECT_TEX; nCntTex++)
		{
			if (g_apGameObject[nCntGameObject].pTexture[nCntTex] != NULL)
			{
				g_apGameObject[nCntGameObject].pTexture[nCntTex]->Release();
				g_apGameObject[nCntGameObject].pTexture[nCntTex] = NULL;
			}
		}

		// メッシュの開放
		if (g_apGameObject[nCntGameObject].pMesh != NULL)
		{
			g_apGameObject[nCntGameObject].pMesh->Release();
			g_apGameObject[nCntGameObject].pMesh = NULL;
		}
		// マテリアルの開放
		if (g_apGameObject[nCntGameObject].pBuffMat != NULL)
		{
			g_apGameObject[nCntGameObject].pBuffMat->Release();
			g_apGameObject[nCntGameObject].pBuffMat = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffGameObject != NULL)
	{
		g_pVtxBuffGameObject->Release();
		g_pVtxBuffGameObject = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateGameObject(void)
{

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawGameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			// 計算用マトリックス
	D3DMATERIAL9 matDef;					// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;						// マテリアルデータへのポインタ

	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		if (g_aGameObject[nCntGameObject].bUse == true && g_aGameObject[nCntGameObject].bDisp == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aGameObject[nCntGameObject].mtxWorldGameObject);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGameObject[nCntGameObject].rot.y, g_aGameObject[nCntGameObject].rot.x, g_aGameObject[nCntGameObject].rot.z);
			D3DXMatrixMultiply(&g_aGameObject[nCntGameObject].mtxWorldGameObject, &g_aGameObject[nCntGameObject].mtxWorldGameObject, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_aGameObject[nCntGameObject].pos.x, g_aGameObject[nCntGameObject].pos.y, g_aGameObject[nCntGameObject].pos.z);
			D3DXMatrixMultiply(&g_aGameObject[nCntGameObject].mtxWorldGameObject, &g_aGameObject[nCntGameObject].mtxWorldGameObject, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aGameObject[nCntGameObject].mtxWorldGameObject);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pBuffMat->GetBufferPointer();

			//pMat->pTextureFilename[0]
				//g_pTextureGameObject
			for (int nCntMat = 0; nCntMat < (int)g_apGameObject[g_aGameObject[nCntGameObject].ModelType].nNumMat; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pTexture[nCntMat]);

				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// ゲームオブジェクト(パーツ)の描画
				g_apGameObject[g_aGameObject[nCntGameObject].ModelType].pMesh->DrawSubset(nCntMat);

			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームオブジェクトの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetGameObject(D3DXVECTOR3 pos, int ModelType)
{
	for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
	{
		if (g_aGameObject[nCntGameObject].bUse == false)
		{
			g_aGameObject[nCntGameObject].pos = pos;
			g_aGameObject[nCntGameObject].ModelType = ModelType;
			g_aGameObject[nCntGameObject].bUse = true;

			break;
		}
	}
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームオブジェクトの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
GameObject *GetGameObject(void)
{
	return &g_aGameObject[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームオブジェクトモデルの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
GameObjectModelData *GetGameObjectModel(void)
{
	return &g_apGameObject[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ゲームオブジェクトtxtデータの読み込み
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadModelGameObject(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1行の一時的読み込み
	char cData[MAX_LOAD_LINE];			// 一時的読み込み

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;						// マテリアルデータへのポインタ
	int nCntModel = 0;
	char cTexName[MAX_LOAD_LINE] = {};

	pFile = fopen(GAMEOBJECT_LOADTXT_NAME, "r"); // ファイルを開く

	if (pFile != NULL) // pFileがNULL(空白）ではないときを真
	{ // ファイルが開けた際の処理ss
		while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
		{
			sscanf(cLine, "%s", cData);
			if (strcmp(cData, "NUM_MODEL") == 0)
			{
				int nNumModel;
				sscanf(cLine, "%s %s %d", cData, cData, &nNumModel);
			}
			else if (strcmp(cData, "MODEL_FILENAME") == 0)
			{
				sscanf(cLine, "%s %s %s", cData, cData, cData);

				D3DXLoadMeshFromX(cData,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_apGameObject[nCntModel].pBuffMat,
					NULL,
					&g_apGameObject[nCntModel].nNumMat,
					&g_apGameObject[nCntModel].pMesh);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_apGameObject[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_apGameObject[nCntModel].nNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_apGameObject[nCntModel].pTexture[nCntMat]);
					}
				}

				int nNumVtx;			// 頂点数
				DWORD sizeFVF;			// 頂点フォーマットのサイズ
				BYTE *pVtxBuff;			// 頂点バッファへのポインタ

				// 頂点数を取得
				nNumVtx = g_apGameObject[nCntModel].pMesh->GetNumVertices();

				// 頂点フォーマットのサイズを取得
				sizeFVF = D3DXGetFVFVertexSize(g_apGameObject[nCntModel].pMesh->GetFVF());

				// 頂点バッファをロック
				g_apGameObject[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入

					// 全ての頂点数を比較してモデルの最小値最大値を抜き出す
					if (vtx.x < g_apGameObject[nCntModel].vtxMin.x)
					{
						g_apGameObject[nCntModel].vtxMin.x = vtx.x;
					}
					if (vtx.y < g_apGameObject[nCntModel].vtxMin.y)
					{
						g_apGameObject[nCntModel].vtxMin.y = vtx.y;
					}
					if (vtx.z < g_apGameObject[nCntModel].vtxMin.z)
					{
						g_apGameObject[nCntModel].vtxMin.z = vtx.z;
					}

					if (vtx.x > g_apGameObject[nCntModel].vtxMax.x)
					{
						g_apGameObject[nCntModel].vtxMax.x = vtx.x;
					}
					if (vtx.y > g_apGameObject[nCntModel].vtxMax.y)
					{
						g_apGameObject[nCntModel].vtxMax.y = vtx.y;
					}
					if (vtx.z > g_apGameObject[nCntModel].vtxMax.z)
					{
						g_apGameObject[nCntModel].vtxMax.z = vtx.z;
					}

					pVtxBuff += sizeFVF;		// サイズ分ポインタを進める
				}

				// 頂点バッファをアンロック
				g_apGameObject[nCntModel].pMesh->UnlockVertexBuffer();

				nCntModel++;
			}
			else if (strcmp(cData, "MODELSET") == 0)
			{
				for (int nCntGameObject = 0; nCntGameObject < MAX_GAMEOBJECT; nCntGameObject++)
				{
					if (g_aGameObject[nCntGameObject].bUse == false)
					{
						while (strcmp(cData, "END_MODELSET") != 0)
						{
							fgets(cLine, MAX_LOAD_LINE, pFile);

							sscanf(cLine, "%s", cData);

							if (strcmp(cData, "TYPE") == 0)
							{
								sscanf(cLine, "%s %s %d", cData, cData, &g_aGameObject[nCntGameObject].ModelType);
								g_aGameObject[nCntGameObject].bUse = true;
							}
							else if (strcmp(cData, "POS") == 0)
							{
								sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aGameObject[nCntGameObject].pos.x,
									&g_aGameObject[nCntGameObject].pos.y,
									&g_aGameObject[nCntGameObject].pos.z);
							}
							else if (strcmp(cData, "ROT") == 0)
							{
								sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aGameObject[nCntGameObject].rot.x,
									&g_aGameObject[nCntGameObject].rot.y,
									&g_aGameObject[nCntGameObject].rot.z);
							}
						}
						break;
					}
				}
			}
		}
		fclose(pFile); // ファイルを閉じる
	}
	else
	{ // ファイルが開けなかった際の処理

	}
}

