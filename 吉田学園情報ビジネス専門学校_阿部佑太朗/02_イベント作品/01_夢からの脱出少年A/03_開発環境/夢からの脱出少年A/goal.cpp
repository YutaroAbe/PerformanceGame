//=============================================================================
//
// モデル処理 [goal.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "goal.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GOAL_FILENAME "data/MODEL/goal.x"
#define GOAL_MOVE_SPEED (0.7f)
#define GOAL_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_GOAL (1)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshGoal[MAX_NUM_GOAL] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatGoal[MAX_NUM_GOAL] = {};//マテリアル情報へのポインタ

GOAL g_Goal[MAX_NUM_GOAL];
//=============================================================================
// 初期化処理
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(GOAL_FILENAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBuffMatGoal[nCntGoal],
			NULL,
			&g_Goal[nCntGoal].NumMatGoal,
			&g_pMeshGoal[nCntGoal]);

		/*当たり判定の設定*/
		SetGoalVertex(nCntGoal);
		//頂点数の取得

		// 位置・向きの初期設定
		g_Goal[nCntGoal].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_Goal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//移動量・回転量の初期化
		g_Goal[nCntGoal].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Goal[nCntGoal].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Goal[nCntGoal].bUse = true;

	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGoal(void)
{
	for (int nCntMesh = 0; nCntMesh < MAX_NUM_GOAL; nCntMesh++)
	{
		// メッシュの解放
		if (g_pMeshGoal[nCntMesh] != NULL)
		{
			g_pMeshGoal[nCntMesh]->Release();
			g_pMeshGoal[nCntMesh] = NULL;
		}
		/*テクスチャの解放*/
		//マテリアルの解放
		if (g_pBuffMatGoal[nCntMesh] != NULL)
		{
			g_pBuffMatGoal[nCntMesh]->Release();
			g_pBuffMatGoal[nCntMesh] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGoal(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Goal[nCntGoal].mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Goal[nCntGoal].rot.y,
			g_Goal[nCntGoal].rot.x,
			g_Goal[nCntGoal].rot.z);

		D3DXMatrixMultiply(&g_Goal[nCntGoal].mtxWorld,
			&g_Goal[nCntGoal].mtxWorld,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_Goal[nCntGoal].pos.x,
			g_Goal[nCntGoal].pos.y,
			g_Goal[nCntGoal].pos.z);

		D3DXMatrixMultiply(&g_Goal[nCntGoal].mtxWorld,
			&g_Goal[nCntGoal].mtxWorld,
			&mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Goal[nCntGoal].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatGoal[nCntGoal]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Goal[nCntGoal].NumMatGoal; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*テクスチャの設定*/
			pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

			// モデル(パーツ)の描画
			g_pMeshGoal[nCntGoal]->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// 位置設定処理
//=============================================================================
void SetGoal(D3DXVECTOR3 pos)
{
	for (int nCntGoal = 0; nCntGoal < MAX_NUM_GOAL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = pos;
	}

}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionGoal(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bEnter = false;

	for (int nCntData = 0; nCntData < MAX_NUM_GOAL; nCntData++)
	{
		if (g_Goal[nCntData].bUse == true)
		{
			if (g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z <= pPos->z + pVtxMax->z&&
				g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z >= pPos->z + pVtxMin->z)
			{
				if (g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x <= pPos->x + pVtxMax->x&&
					g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x >= pOldPos->x + pVtxMax->x)
				{//左から右
					bEnter = true;

				}
				if (g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x >= pPos->x + pVtxMin->x&&
					g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x <= pOldPos->x + pVtxMin->x)
				{//右から左
					bEnter = true;

				}
			}

			if (g_Goal[nCntData].VtxMin.x + g_Goal[nCntData].pos.x <= pPos->x + pVtxMax->x&&
				g_Goal[nCntData].VtxMax.x + g_Goal[nCntData].pos.x >= pPos->x + pVtxMin->x)
			{
				if (g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z <= pPos->z + pVtxMax->z&&
					g_Goal[nCntData].VtxMin.z + g_Goal[nCntData].pos.z >= pOldPos->z + pVtxMax->z)
				{//手前から奥
					bEnter = true;

				}
				if (g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z >= pPos->z + pVtxMin->z&&
					g_Goal[nCntData].VtxMax.z + g_Goal[nCntData].pos.z <= pOldPos->z + pVtxMin->z)
				{//奥から手前
					bEnter = true;
				}
			}
		}
	}
	return bEnter;

}
//=============================================================================
// 最大・最小の頂点座標を取得
//=============================================================================
void SetGoalVertex(int nCntGoal)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Goal[nCntGoal].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Goal[nCntGoal].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshGoal[nCntGoal]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshGoal[nCntGoal]->GetFVF());

	//頂点バッファのロック
	g_pMeshGoal[nCntGoal]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Goal[nCntGoal].VtxMin.x > vtx.x)
		{
			g_Goal[nCntGoal].VtxMin.x = vtx.x;
		}
		if (g_Goal[nCntGoal].VtxMax.x < vtx.x)
		{
			g_Goal[nCntGoal].VtxMax.x = vtx.x;
		}

		//y
		if (g_Goal[nCntGoal].VtxMin.y > vtx.y)
		{
			g_Goal[nCntGoal].VtxMin.y = vtx.y;
		}
		if (g_Goal[nCntGoal].VtxMax.y < vtx.y)
		{
			g_Goal[nCntGoal].VtxMax.y = vtx.y;
		}

		//z
		if (g_Goal[nCntGoal].VtxMin.z > vtx.z)
		{
			g_Goal[nCntGoal].VtxMin.z = vtx.z;
		}
		if (g_Goal[nCntGoal].VtxMax.z < vtx.z)
		{
			g_Goal[nCntGoal].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshGoal[nCntGoal]->UnlockVertexBuffer();

}