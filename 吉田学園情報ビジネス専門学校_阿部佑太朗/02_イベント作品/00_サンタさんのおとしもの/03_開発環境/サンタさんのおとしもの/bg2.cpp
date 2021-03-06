//=============================================================================
//
// 背景(バックグラウンド)処理 [bg.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "bg2.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/雪BG.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE2 "data/TEXTURE/雪BG.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE3 "data/TEXTURE/雪BG.png" //読み込むテクスチャ
#define BG_POS_X  (0)　　　//背景の左上X座標
#define BG_POS_Y  (0)　　　//背景の左上Y座標
#define BG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define MAX_TEX (2)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureBG2[2] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG2 = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_BG2[3];

//=============================================================================
//初期化処理背景
//=============================================================================
void InitBG2(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < 2; nCount++)
	{
		g_BG2[0] = D3DXVECTOR2(0.0f, 0.0f);
		g_BG2[1] = D3DXVECTOR2(0.0f, 0.0f);
		g_BG2[2] = D3DXVECTOR2(0.0f, 0.0f);
	}
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, & g_pTextureBG2[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, & g_pTextureBG2[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, & g_pTextureBG2[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG2,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ

	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx,0);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点座標設定
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //右上
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);//右下
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
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				    //右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める

	}
	//頂点バッファアンロックする
	g_pVtxBuffBG2->Unlock();
	
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitBG2(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テクスチャの破棄
		if ( g_pTextureBG2[nCount] != NULL)
		{
			 g_pTextureBG2[nCount]->Release();
			 g_pTextureBG2[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBG2 != NULL)
	{
		g_pVtxBuffBG2->Release();
		g_pVtxBuffBG2 = NULL;
	}
}
//=============================================================================
//更新処理背景
//=============================================================================
void UpdateBG2(void)
{
	VERTEX_2D*pVtx;

	g_BG2[0].y += 0.003f;
	g_BG2[1].y += 0.002f;
//_BG2[2].y += 0.001f;
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG2->Lock(0, 0, (void**)&pVtx, 0);
	
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[0].y);						//右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[0].y);					//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[0].y - 1.0f);						//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[0].y -1.0f);					//左下
		
	pVtx += 4;

	pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[1].y);						//右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[1].y);					//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[1].y - 1.0f);						//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[1].y - 1.0f);					//左下

	//pVtx += 4;

	//pVtx[0].tex = D3DXVECTOR2(0.0f, g_BG2[2].y);						//右上
	//pVtx[1].tex = D3DXVECTOR2(1.0f, g_BG2[2].y );					//右下
	//pVtx[2].tex = D3DXVECTOR2(0.0f, g_BG2[2].y - 1.0f);						//左上
	//pVtx[3].tex = D3DXVECTOR2(1.0f, g_BG2[2].y - 1.0f);					//左下
	
	// 頂点バッファをアンロックする
	g_pVtxBuffBG2->Unlock();
}
//=============================================================================
//描画処理背景
//=============================================================================
void DrawBG2(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG2,0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);	

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0,  g_pTextureBG2[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 3);
	}
}
