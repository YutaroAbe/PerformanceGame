//=============================================================================
//
// 背景(バックグラウンド)処理 [bg.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "bg3.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/BG3.jpg" //読み込むテクスチャ
#define BG_POS_X  (0)　　　//背景の左上X座標
#define BG_POS_Y  (0)　　　//背景の左上Y座標
#define BG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define MAX_TEX (2)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureBG3 = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG3 = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_BG3;

//=============================================================================
//初期化処理背景
//=============================================================================
void InitBG3(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

	g_BG3 = D3DXVECTOR2(0.0f, 0.0f);
		
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureBG3);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG3,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ

	g_pVtxBuffBG3->Lock(0, 0, (void**)&pVtx,0);

		//頂点座標設定
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);						 //右上
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);				 //右下
		pVtx[2].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);				 //左上
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);		 //左下
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
	
	//頂点バッファアンロックする
	g_pVtxBuffBG3->Unlock();
	
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitBG3(void)
{
	
		//テクスチャの破棄
		if ( g_pTextureBG3 != NULL)
		{
			 g_pTextureBG3->Release();
			 g_pTextureBG3 = NULL;
		}
	
	//頂点バッファの破棄
	if (g_pVtxBuffBG3 != NULL)
	{
		g_pVtxBuffBG3->Release();
		g_pVtxBuffBG3 = NULL;
	}
}
//=============================================================================
//更新処理背景
//=============================================================================
void UpdateBG3(void)
{
}
//=============================================================================
//描画処理背景
//=============================================================================
void DrawBG3(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG3,0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);	

		//テェクスチャの設定
		pDevice->SetTexture(0,  g_pTextureBG3);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  0, 2);
	
}
