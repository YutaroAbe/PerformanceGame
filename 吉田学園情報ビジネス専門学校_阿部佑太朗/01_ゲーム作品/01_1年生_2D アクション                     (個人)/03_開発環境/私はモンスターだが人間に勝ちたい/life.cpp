//=========================================================================================================================
//
// ライフの処理 [life.cpp]
// Author : 
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "life.h"//タイム
#include "input.h"//キーボード
#include "player.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_LIFE_NUMBER (10)
#define TEXTURE_LIFE "data/TEXTURE/HP101.png"// 読み込むテクスチャファイル名
#define MAX_PLIFE (30)							//ライフの大きさ

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;// 頂点バッファへのポインタ
D3DXVECTOR3 g_posLife;

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;  //デバイスポインタ
	float  nCntLife;			//スコアカウント


	//デバイスの取得
	pDevice = GetDevice();
	for (nCntLife = 0; nCntLife < MAX_LIFE_NUMBER; nCntLife++)
	{
		//位置
		g_posLife = D3DXVECTOR3(190, 40, 0.0f);
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_LIFE, &g_pTextureLife);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0;  nCntLife < MAX_LIFE_NUMBER; nCntLife++, g_posLife.x += 30)

	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_posLife.x - 18.0f, g_posLife.y - 16.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife.x + 18.0f, g_posLife.y - 18.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife.x - 18.0f, g_posLife.y + 18.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife.x + 18.0f, g_posLife.y + 18.0f, 0.0f);
		//RHW
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffLife->Unlock();

}

//=========================================================================================================================
// スコア終了処理
//=========================================================================================================================
void UninitLife(void)
{
	for (int nCntLife = 0; nCntLife < MAX_LIFE_NUMBER; nCntLife++)
	{
		//テクスチャーの破棄
		if (g_pTextureLife != NULL)
		{
			g_pTextureLife->Release();
			g_pTextureLife = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=========================================================================================================================
// スコア更新処理
//=========================================================================================================================
void UpdateLife(void)
{
}

//=========================================================================================================================
// スコア描画処理
//=========================================================================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	int nCntLife;//スコアカウント

				  //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(0,g_pVtxBuffLife,0,sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureLife);
		PLAYER *pPlayer;
		pPlayer = GetPlayer();

		if (pPlayer->nLife == 10)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 10; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 9)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 9; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 8)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 8; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 7)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 7; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 6)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 6; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 5)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 5; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 4)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 4; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 3)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 3; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 2)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 2; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 1)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 1; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
		else if (pPlayer->nLife == 0)
		{
			//スコアの描画
			for (nCntLife = 0; nCntLife < 0
				; nCntLife++)
			{//スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
			}
		}
}

