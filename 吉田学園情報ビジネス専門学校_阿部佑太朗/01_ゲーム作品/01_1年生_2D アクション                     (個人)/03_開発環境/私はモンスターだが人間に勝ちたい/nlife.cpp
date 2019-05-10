//=============================================================================
//
// ライフ外付け処理 [nlife.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "nlife.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/nHP001.png" //読み込むテクスチャ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureNlife = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNlife = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_Nlife;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitNlife(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

		g_Nlife = D3DXVECTOR2(190, 45);
	
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureNlife);
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNlife,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffNlife->Lock(0, 0, (void**)&pVtx,0);

		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(g_Nlife.x - 135.0f, g_Nlife.y -40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Nlife.x + 135.0f, g_Nlife.y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Nlife.x - 135.0f, g_Nlife.y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Nlife.x + 135.0f, g_Nlife.y + 40.0f, 0.0f);
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下

	//頂点バッファアンロックする
	g_pVtxBuffNlife->Unlock();
	
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitNlife(void)
{
		//テクスチャの破棄
	if (g_pTextureNlife != NULL)
	{
		g_pTextureNlife->Release();
		g_pTextureNlife = NULL;
	}
	
	//頂点バッファの破棄
	if (g_pVtxBuffNlife != NULL)
	{
		g_pVtxBuffNlife->Release();
		g_pVtxBuffNlife = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateNlife(void)
{
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawNlife(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffNlife, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テェクスチャの設定
	pDevice->SetTexture(0, g_pTextureNlife);
	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
