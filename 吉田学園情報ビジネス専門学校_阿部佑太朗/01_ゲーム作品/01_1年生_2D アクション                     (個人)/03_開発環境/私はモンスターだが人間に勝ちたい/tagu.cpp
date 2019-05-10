//=============================================================================
//
// ゲームタグ処理 [Tagu.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "tagu.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/tagu.png" //読み込むテクスチャ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTagu = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTagu = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_Tagu;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitTagu(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

		g_Tagu = D3DXVECTOR2(0, 0);
	
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureTagu);
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTagu,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ

	g_pVtxBuffTagu->Lock(0, 0, (void**)&pVtx,0);


		//頂点座標設定
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_Tagu.x - 0, g_Tagu.y -0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Tagu.x + 1280.0f, g_Tagu.y -0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Tagu.x - 0, g_Tagu.y + 70.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Tagu.x + 1280.0f, g_Tagu.y + 70.0f, 0.0f);
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
	g_pVtxBuffTagu->Unlock();
	
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitTagu(void)
{
		//テクスチャの破棄
		if (g_pTextureTagu != NULL)
		{
			g_pTextureTagu->Release();
			g_pTextureTagu = NULL;
		}
	
	//頂点バッファの破棄
	if (g_pVtxBuffTagu != NULL)
	{
		g_pVtxBuffTagu->Release();
		g_pVtxBuffTagu = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateTagu(void)
{
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawTagu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTagu,0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);	

	
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureTagu);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}
