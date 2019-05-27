
//=============================================================================
//
// 3DUI処理 [3DUi.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "camera.h"
#include "poker.h"
#include "3DUi.h"
#include "cardModel.h"
#include "fade.h"
#include "gamefade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOAD_CURSOR		"data/MODEL/cursor.x"	// 読み込むXファイル名
#define LOAD_KEY		"data/MODEL/key_0.25.x"	// 読み込むXファイル名
#define MAX_MODEL		(2)						// モデルの最大数
#define LOCK_SPACE		(100.0f)				// 鍵のスペース
#define CURSOR_SPACE	(85.0f)					// カーソルのスペース
//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI_3D g_aUi[MAX_MODEL];			// モデルの構造体(総数)
P3DUI g_pUi[MAX_MODEL];			// モデルの構造体(種類)
//=============================================================================
// 初期化処理
//=============================================================================
void Init3DUI(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み(カーソル)
#if 1
	D3DXLoadMeshFromX(LOAD_CURSOR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pUi[0].pBuffMat,
		NULL,
		&g_pUi[0].nNumMat,
		&g_pUi[0].pMesh);
#endif
	// Xファイルの読み込み(鍵マーク)
#if 1
	D3DXLoadMeshFromX(LOAD_KEY,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pUi[1].pBuffMat,
		NULL,
		&g_pUi[1].nNumMat,
		&g_pUi[1].pMesh);
#endif
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// 初期設定
		g_aUi[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void Uninit3DUI(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// テクスチャの破棄
		if (g_pUi[nCnt].pTexture != NULL)
		{
			g_pUi[nCnt].pTexture->Release();
			g_pUi[nCnt].pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// メッシュの開放
		if (g_pUi[nCnt].pMesh != NULL)
		{
			g_pUi[nCnt].pMesh->Release();
			g_pUi[nCnt].pMesh = NULL;
		}
		// マテリアルの開放
		if (g_pUi[nCnt].pBuffMat != NULL)
		{
			g_pUi[nCnt].pBuffMat->Release();
			g_pUi[nCnt].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update3DUI(void)
{
	CARDSIDE side = GetPokerState();				// ポーカーの状態取得
	D3DXVECTOR3 LockPos1P = GetLockPos1P(4);		// 1P鍵マーク
	D3DXVECTOR3 LockPos2P = GetLockPos2P(4);		// 2P鍵マーク
	D3DXVECTOR3 g_ButtonPos1P = GetLockPos1P(2);	// 完了ボタン
	D3DXVECTOR3 g_ButtonPos2P = GetLockPos2P(2);	// 完了ボタン
	bool bSetFinish = GetSet();						// 配布されたか
	int nSelectCard = GetNum();						// 何番のカードを選んでいるか

	GAMEFADE pGameFade;
	pGameFade = GetGameFade();
	if (bSetFinish == true)
	{
		if (side == CARD_SIDE_1P)
		{// 1P
			D3DXVECTOR3 CursorPos1P = GetCardPos1P(nSelectCard);
			g_aUi[0].pos.x = CursorPos1P.x;
			g_aUi[0].pos.z = CursorPos1P.z - CURSOR_SPACE;
			g_aUi[0].rot.y = 0.0f;
			g_aUi[1].pos.x = LockPos1P.x;
			g_aUi[1].pos.z = LockPos1P.z + LOCK_SPACE;
		}
		else if (side == CARD_SIDE_2P)
		{// 2P
			D3DXVECTOR3 CursorPos2P = GetCardPos2P(nSelectCard);
			g_aUi[0].pos.x = CursorPos2P.x;
			g_aUi[0].pos.z = CursorPos2P.z + CURSOR_SPACE;
			g_aUi[0].rot.y = D3DX_PI * 1.0f;
			g_aUi[1].pos.x = LockPos2P.x;
			g_aUi[1].pos.z = LockPos2P.z - LOCK_SPACE;
			g_aUi[1].rot.y = D3DX_PI * 1.0f;;
		}
		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			g_aUi[nCnt].bUse = true;
		}
	}
	if (pGameFade == GAMEFADE_OUT)
	{
		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			g_aUi[nCnt].bUse = false;
		}
	}
	if (pGameFade == GAMEFADE_IN)
	{
		if (bSetFinish == true)
		{
			g_aUi[0].bUse = true;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void Draw3DUI(void)
{
	GAMEMODE GameMode = GetGameMode();
	CARDSIDE side = GetPokerState();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aUi[nCnt].bUse == true && GameMode == GAMEMODE_POKER)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aUi[nCnt].mtxWorldUI);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aUi[nCnt].rot.y,						// Y,X,Zの順番
				g_aUi[nCnt].rot.x,
				g_aUi[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aUi[nCnt].mtxWorldUI,
				&g_aUi[nCnt].mtxWorldUI,
				&mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_aUi[nCnt].pos.x,
				g_aUi[nCnt].pos.y,
				g_aUi[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aUi[nCnt].mtxWorldUI,
				&g_aUi[nCnt].mtxWorldUI,
				&mtxTrans);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pUi[nCnt].pBuffMat->GetBufferPointer();

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aUi[nCnt].mtxWorldUI);

			for (int nCntMat = 0; nCntMat < (int)g_pUi[nCnt].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pUi[nCnt].pTexture);

				// モデル(パーツ)の描画
				g_pUi[nCnt].pMesh->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
