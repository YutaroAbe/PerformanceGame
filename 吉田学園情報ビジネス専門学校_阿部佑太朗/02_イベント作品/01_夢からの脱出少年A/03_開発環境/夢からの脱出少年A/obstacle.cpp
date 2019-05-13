//=============================================================================
//
// モデル処理 [obstacle.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "obstacle.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBSTACLE_FILENAME0 "data/MODEL/mine1.x"
#define OBSTACLE_FILENAME1 "data/MODEL/object.x"
#define OBSTACLE_MOVE_SPEED (0.7f)
#define OBSTACLE_ROTMOVE_COEFFICIENT (0.13f)
#define MAX_NUM_OBSTACLE (100)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshObstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatObstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE] = {};//マテリアル情報へのポインタ

OBSTACLE g_Obstacle[OBSTACLETYPE_MAX][MAX_NUM_OBSTACLE];
//=============================================================================
// 初期化処理
//=============================================================================
void InitObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPCSTR ObsFileName[OBSTACLETYPE_MAX] = { OBSTACLE_FILENAME0,
											OBSTACLE_FILENAME1 };

	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{

		for (int nCntObstacle = 0; nCntObstacle < MAX_NUM_OBSTACLE; nCntObstacle++)
		{
			// Xファイルの読み込み
			D3DXLoadMeshFromX(ObsFileName[nCntType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatObstacle[nCntType][nCntObstacle],
				NULL,
				&g_Obstacle[nCntType][nCntObstacle].NumMatObstacle,
				&g_pMeshObstacle[nCntType][nCntObstacle]);

			/*当たり判定の設定*/
			SetObstacleVertex(nCntObstacle,nCntType);
			//頂点数の取得

			// 位置・向きの初期設定
			g_Obstacle[nCntType][nCntObstacle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Obstacle[nCntType][nCntObstacle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//移動量・回転量の初期化
			g_Obstacle[nCntType][nCntObstacle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Obstacle[nCntType][nCntObstacle].rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_Obstacle[nCntType][nCntObstacle].bUse = false;

		}
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObstacle(void)
{
	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{
		for (int nCntMesh = 0; nCntMesh < MAX_NUM_OBSTACLE; nCntMesh++)
		{
			// メッシュの解放
			if (g_pMeshObstacle[nCntType][nCntMesh] != NULL)
			{
				g_pMeshObstacle[nCntType][nCntMesh]->Release();
				g_pMeshObstacle[nCntType][nCntMesh] = NULL;
			}
			/*テクスチャの解放*/
			//マテリアルの解放
			if (g_pBuffMatObstacle[nCntType][nCntMesh] != NULL)
			{
				g_pBuffMatObstacle[nCntType][nCntMesh]->Release();
				g_pBuffMatObstacle[nCntType][nCntMesh] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObstacle(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObstacle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{

		for (int nCntObstacle = 0; nCntObstacle < MAX_NUM_OBSTACLE; nCntObstacle++)
		{
			if (g_Obstacle[nCntType][nCntObstacle].bUse == true)
			{

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Obstacle[nCntType][nCntObstacle].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					g_Obstacle[nCntType][nCntObstacle].rot.y,
					g_Obstacle[nCntType][nCntObstacle].rot.x,
					g_Obstacle[nCntType][nCntObstacle].rot.z);

				D3DXMatrixMultiply(&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans,
					g_Obstacle[nCntType][nCntObstacle].pos.x,
					g_Obstacle[nCntType][nCntObstacle].pos.y,
					g_Obstacle[nCntType][nCntObstacle].pos.z);

				D3DXMatrixMultiply(&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&g_Obstacle[nCntType][nCntObstacle].mtxWorld,
					&mtxTrans);
				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Obstacle[nCntType][nCntObstacle].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatObstacle[nCntType][nCntObstacle]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Obstacle[nCntType][nCntObstacle].NumMatObstacle; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					/*テクスチャの設定*/
					pDevice->SetTexture(0, NULL);//テクスチャの設定(使わなければNULLを入れる)

					// モデル(パーツ)の描画
					g_pMeshObstacle[nCntType][nCntObstacle]->DrawSubset(nCntMat);
				}

				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=============================================================================
// 障害物の設置
//=============================================================================
void SetObstacle(D3DXVECTOR3 pos, OBS_TYPE type)
{
	for (int nCntData = 0; nCntData < MAX_NUM_OBSTACLE; nCntData++)
	{
		if (g_Obstacle[type][nCntData].bUse == false)
		{
			g_Obstacle[type][nCntData].pos = pos;

			g_Obstacle[type][nCntData].bUse = true;
			break;
		}

	}
}
//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CollisionObstacle(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax)
{
	//変数宣言
	bool bLand = false;
	for (int nCntType = 0; nCntType < OBSTACLETYPE_MAX; nCntType++)
	{
		for (int nCntData = 0; nCntData < MAX_NUM_OBSTACLE; nCntData++)
		{
			if (g_Obstacle[nCntType][nCntData].bUse == true)
			{
				if (g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z <= pPos->z&&
					g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z >= pPos->z)
				{
					if (g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x <= pPos->x&&
						g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x >= pOldPos->x)
					{//左から右
						pPos->x = g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x;
						pMove->x = 0.0f;
					}
					else if (g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x >= pPos->x &&
						g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x <= pOldPos->x)
					{//右から左
						pPos->x = g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x;
						pMove->x = 0.0f;
					}
				}

				if (g_Obstacle[nCntType][nCntData].VtxMin.x + g_Obstacle[nCntType][nCntData].pos.x < pPos->x &&
					g_Obstacle[nCntType][nCntData].VtxMax.x + g_Obstacle[nCntType][nCntData].pos.x > pPos->x)
				{
					if (g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z <= pPos->z&&
						g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z >= pOldPos->z)
					{//手前から奥
						pPos->z = g_Obstacle[nCntType][nCntData].VtxMin.z + g_Obstacle[nCntType][nCntData].pos.z;
						pMove->z = 0.0f;
					}
					else if (g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z >= pPos->z&&
						g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z <= pOldPos->z)
					{//奥から手前
						pPos->z = g_Obstacle[nCntType][nCntData].VtxMax.z + g_Obstacle[nCntType][nCntData].pos.z;
						pMove->z = 0.0f;
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
void SetObstacleVertex(int nCntObstacle,int nCntType)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	g_Obstacle[nCntType][nCntObstacle].VtxMin = D3DXVECTOR3(1000000, 1000000, 1000000);
	g_Obstacle[nCntType][nCntObstacle].VtxMax = D3DXVECTOR3(-1000000, -1000000, -1000000);

	//頂点数の取得
	nNumVtx = g_pMeshObstacle[nCntType][nCntObstacle]->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObstacle[nCntType][nCntObstacle]->GetFVF());

	//頂点バッファのロック
	g_pMeshObstacle[nCntType][nCntObstacle]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

													//頂点を比較してモデルの最小・最大を抜き出す
													//x
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.x > vtx.x)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.x = vtx.x;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.x < vtx.x)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.x = vtx.x;
		}

		//y
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.y > vtx.y)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.y = vtx.y;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.y < vtx.y)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.y = vtx.y;
		}

		//z
		if (g_Obstacle[nCntType][nCntObstacle].VtxMin.z > vtx.z)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMin.z = vtx.z;
		}
		if (g_Obstacle[nCntType][nCntObstacle].VtxMax.z < vtx.z)
		{
			g_Obstacle[nCntType][nCntObstacle].VtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	g_pMeshObstacle[nCntType][nCntObstacle]->UnlockVertexBuffer();

}