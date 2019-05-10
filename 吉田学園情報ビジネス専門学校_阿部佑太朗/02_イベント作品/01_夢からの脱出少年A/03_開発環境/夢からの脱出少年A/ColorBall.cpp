//=============================================================================
//
// モデル処理 [ColorBall.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "ColorBall.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COLORFIELD_NAME000		 "data\\MODEL\\BallRed.x"		//テクスチャのファイル名
#define COLORFIELD_NAME001		 "data\\MODEL\\BallGreen.x"		//テクスチャのファイル名
#define COLORFIELD_NAME002		 "data\\MODEL\\BallBlue.x"		//テクスチャのファイル名
#define COLORFIELD_NAME003		 "data\\MODEL\\BallPurple.x"		//テクスチャのファイル名
#define COLORFIELD_NAME004		 "data\\MODEL\\BallYellow.x"		//テクスチャのファイル名

#define MOVE_MODEL			(2.0f)							//モデル移動量
#define MOVE_SIN_COS_TOP	(0.75f)							//ポリゴン移動量
#define MOVE_SIN_COS_BOT	(0.25f)							//ポリゴン移動量
#define FIELD_MAX_SIZE		(FIELD_SIZE - 10)
#define MAX_MODEL			(1)								//モデル配置の最大数
#define MAX_COLORFIELD_TYPE	(5)								//モデル種類の最大数
#define CHANGE_TIMER		(240)							//変化中の時間(フレーム数)
#define MOVE_OK_TIMER		(600)							//移動可能時間(フレーム数)
#define CHANGE_FRAME		(5)								//変化のスピード(フレーム数)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshColorBall[MAX_COLORFIELD_TYPE];						//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatColorBall[MAX_COLORFIELD_TYPE];				//マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9	g_pTextureColorBall[MAX_COLORFIELD_TYPE];			//テクスチャへのポインタ
DWORD g_nNumMatColorBall[MAX_COLORFIELD_TYPE] = {};					//マテリアル情報の数
COLORBALL g_aColorBall[MAX_MODEL];
//=============================================================================
// 初期化処理
//=============================================================================
void InitColorBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// Xファイルの読み込み
	D3DXLoadMeshFromX(COLORFIELD_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[0],
		NULL,
		&g_nNumMatColorBall[0],
		&g_pMeshColorBall[0]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(COLORFIELD_NAME001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[1],
		NULL,
		&g_nNumMatColorBall[1],
		&g_pMeshColorBall[1]);
	
	// Xファイルの読み込み
	D3DXLoadMeshFromX(COLORFIELD_NAME002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[2],
		NULL,
		&g_nNumMatColorBall[2],
		&g_pMeshColorBall[2]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(COLORFIELD_NAME003,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[3],
		NULL,
		&g_nNumMatColorBall[3],
		&g_pMeshColorBall[3]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(COLORFIELD_NAME004,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatColorBall[4],
		NULL,
		&g_nNumMatColorBall[4],
		&g_pMeshColorBall[4]);



	D3DXVECTOR3 vtx[MAX_MODEL];
	
	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{//モデルの初期化
		g_aColorBall[nCntColorBall].nType = 0;
		g_aColorBall[nCntColorBall].bUse = false;
		g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
		g_aColorBall[nCntColorBall].CntState = COUNTERSTATE_CHANGE;
		g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;
		g_aColorBall[nCntColorBall].nStateCounter = 0;
		g_aColorBall[nCntColorBall].nFrameCounter = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		COLORFIELD_NAME000,
		&g_pTextureColorBall[2]);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitColorBall(void)
{
	for (int nCntColorBall = 0; nCntColorBall < MAX_COLORFIELD_TYPE; nCntColorBall++)
	{
		// メッシュの開放
		if (g_pMeshColorBall[nCntColorBall] != NULL)
		{
			g_pMeshColorBall[nCntColorBall]->Release();
			g_pMeshColorBall[nCntColorBall] = NULL;
		}
		// マテリアルの開放
		if (g_pBuffMatColorBall[nCntColorBall] != NULL)
		{
			g_pBuffMatColorBall[nCntColorBall]->Release();
			g_pBuffMatColorBall[nCntColorBall] = NULL;
		}
		//テクスチャの破棄
		if (g_pTextureColorBall[nCntColorBall] != NULL)
		{
			g_pTextureColorBall[nCntColorBall]->Release();
			g_pTextureColorBall[nCntColorBall] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateColorBall(void)
{
	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == true)	//モデルが使用されている
		{
			if (g_aColorBall[nCntColorBall].state == COLORBALLSTATE_STOP)
			{
				g_aColorBall[nCntColorBall].nStateCounter++;
			}

			if (g_aColorBall[nCntColorBall].nStateCounter > MOVE_OK_TIMER)
			{
				g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
			}

			if (g_aColorBall[nCntColorBall].nTimerChange < 0)
			{	//一定時間経過後にランダムで色を決定
				g_aColorBall[nCntColorBall].nType = rand() % MAX_COLORFIELD_TYPE;
				g_aColorBall[nCntColorBall].state = COLORBALLSTATE_STOP;
				g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;
				g_aColorBall[nCntColorBall].nStateCounter = 0;
			}
			
			if (g_aColorBall[nCntColorBall].state == COLORBALLSTATE_CHANGE)
			{	//お題を変える
				//フレームのカウンター
				g_aColorBall[nCntColorBall].nFrameCounter++;
				//止めるためのカウンター
				g_aColorBall[nCntColorBall].nTimerChange--;
				if(g_aColorBall[nCntColorBall].nFrameCounter > CHANGE_FRAME)
				{	//10フレームに一回変える
					g_aColorBall[nCntColorBall].nFrameCounter = 0;
					g_aColorBall[nCntColorBall].nType++;
					PlaySound(SOUND_LABEL_SE004);
					if (g_aColorBall[nCntColorBall].nType > MAX_COLORFIELD_TYPE - 1)
					{	//上回ったら0に戻す
						g_aColorBall[nCntColorBall].nType = 0;
					}
				}				
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawColorBall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == true)	//モデルが使用されている
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aColorBall[nCntColorBall].mtxWorld);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aColorBall[nCntColorBall].rot.y, g_aColorBall[nCntColorBall].rot.x, g_aColorBall[nCntColorBall].rot.z);
			D3DXMatrixMultiply(&g_aColorBall[nCntColorBall].mtxWorld, &g_aColorBall[nCntColorBall].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aColorBall[nCntColorBall].pos.x, g_aColorBall[nCntColorBall].pos.y, g_aColorBall[nCntColorBall].pos.z);
			D3DXMatrixMultiply(&g_aColorBall[nCntColorBall].mtxWorld, &g_aColorBall[nCntColorBall].mtxWorld, &mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aColorBall[nCntColorBall].mtxWorld);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatColorBall[g_aColorBall[nCntColorBall].nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatColorBall[g_aColorBall[nCntColorBall].nType]; nCntMat++)
			{	// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャ
				pDevice->SetTexture(0, g_pTextureColorBall[0]);
				// モデル(パーツ)の描画
				g_pMeshColorBall[g_aColorBall[nCntColorBall].nType]->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//*****************************************************************************
//モデルポインタ処理
//*****************************************************************************
COLORBALL *GetColorBall(void)
{
	return &g_aColorBall[0];
}

//=============================================================================
// カラーフィルドの設定処理
//=============================================================================
void SetColorBall(D3DXVECTOR3 pos, int nType)
{

	D3DXVECTOR3 vtx[MAX_MODEL];

	for (int nCntColorBall = 0; nCntColorBall < MAX_MODEL; nCntColorBall++)
	{
		if (g_aColorBall[nCntColorBall].bUse == false)
		{
			// 位置・向きの初期設定
			g_aColorBall[nCntColorBall].pos = pos;
			g_aColorBall[nCntColorBall].rot = D3DXVECTOR3(0, 0, 0);
			g_aColorBall[nCntColorBall].nType = nType;
			g_aColorBall[nCntColorBall].bUse = true;
			g_aColorBall[nCntColorBall].state = COLORBALLSTATE_CHANGE;
			g_aColorBall[nCntColorBall].CntState = COUNTERSTATE_CHANGE;
			g_aColorBall[nCntColorBall].nTimerChange = CHANGE_TIMER;	
			g_aColorBall[nCntColorBall].nStateCounter = 0;
			g_aColorBall[nCntColorBall].nFrameCounter = 0;
			break;
		}
	}
}