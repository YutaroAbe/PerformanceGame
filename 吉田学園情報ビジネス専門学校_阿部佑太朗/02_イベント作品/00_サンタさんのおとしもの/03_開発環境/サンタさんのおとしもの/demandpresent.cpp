//=============================================================================
//
// 欲しいプレゼント表示の処理 [demandpresent.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "demandpresent.h"
#include "human.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEAMND_TEXTURE_NAME0       "data/TEXTURE/DemandPresent001.png"    // 読み込むテクスチャファイル名
#define DEAMND_TEXTURE_NAME1       "data/TEXTURE/DemandPresent000.png"    // 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexDemandPresent(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDemandPresent[2] = {};	  // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDemandPresent = NULL;	      // 頂点バッファへのポインタ
DemandPresent           g_aDemandPresent[MAX_DEMANDPRESENT];  // 表示の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitDemandPresent(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// 表示できる欲しいプレゼントの数だけ繰り返し
		g_aDemandPresent[nCntDemand].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 位置を初期化
		g_aDemandPresent[nCntDemand].bDisp = false;                        // 表示しない状態にする
	}

	// 頂点情報の設定
	MakeVertexDemandPresent(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDemandPresent(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureDemandPresent[nCntTex] != NULL)
		{
			g_pTextureDemandPresent[nCntTex]->Release();
			g_pTextureDemandPresent[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffDemandPresent != NULL)
	{
		g_pVtxBuffDemandPresent->Release();
		g_pVtxBuffDemandPresent = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateDemandPresent(void)
{
	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	Human *pHuman;
	pHuman = GetHuman();

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++,pHuman++)
	{// 表示できる欲しいプレゼントの数だけ繰り返し
		if (g_aDemandPresent[nCntDemand].bDisp == true)
		{// 表示する状態だったら
			
			// 位置更新
			g_aDemandPresent[nCntDemand].pos = D3DXVECTOR3(pHuman->pos.x + pHuman->fWidth + 10.0f, pHuman->pos.y - pHuman->fHeight - 30.0f, 0.0f);

			// 頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);

			// 画面端に行ったら消す
			if (pHuman == false)
			{// 右端に到達した
				g_aDemandPresent[nCntDemand].bDisp = false;
			}
			if (pHuman->bUse == false)
			{// 左端に到達した
				g_aDemandPresent[nCntDemand].bDisp = false;
			}
		}

		pVtx += 4;  // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// タイトル画面
//=============================================================================
void DrawDemandPresent(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffDemandPresent, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// 表示できる欲しいプレゼントの数だけ繰り返し
		if (g_aDemandPresent[nCntDemand].bDisp == true)
		{// 表示する状態だったら
		 // テクスチャの設定
			pDevice->SetTexture(0, g_pTextureDemandPresent[g_aDemandPresent[nCntDemand].nIdxHuman]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDemand * 4, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexDemandPresent(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		DEAMND_TEXTURE_NAME0,
		&g_pTextureDemandPresent[0]);
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		DEAMND_TEXTURE_NAME1,
		&g_pTextureDemandPresent[1]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DEMANDPRESENT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDemandPresent,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDemand = 0; nCntDemand < MAX_DEMANDPRESENT; nCntDemand++)
	{// 表示できる欲しいプレゼントの数だけ繰り返し
	    // 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y - 35, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x - 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nCntDemand].pos.x + 35, g_aDemandPresent[nCntDemand].pos.y + 35, 0.0f);

		// 頂点テクスチャ
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;  // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// 位置の設定
//=============================================================================
void SetDemandPresent(D3DXVECTOR3 pos, int nIdxHuman,int nNumTex)
{
	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffDemandPresent->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nIdxHuman;  // ポインタを人間の番号分進める

	if (g_aDemandPresent[nIdxHuman].bDisp == false)
	{// 表示しない状態だったら
		g_aDemandPresent[nIdxHuman].pos = pos;     // 位置を設定
		g_aDemandPresent[nIdxHuman].bDisp = true;  // 使用している状態にする
		g_aDemandPresent[nIdxHuman].nIdxHuman = nNumTex;

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x - 35, g_aDemandPresent[nIdxHuman].pos.y - 35, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x + 35, g_aDemandPresent[nIdxHuman].pos.y - 35, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x - 35, g_aDemandPresent[nIdxHuman].pos.y + 35, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aDemandPresent[nIdxHuman].pos.x + 35, g_aDemandPresent[nIdxHuman].pos.y + 35, 0.0f);

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffDemandPresent->Unlock();
}
//=============================================================================
// 位置の設定
//=============================================================================
void DeleteDemandPresent(int nIdxHuman)
{
	g_aDemandPresent[nIdxHuman].bDisp = false;  // 使用していない状態にする
}