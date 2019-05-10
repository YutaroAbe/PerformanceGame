//=============================================================================
//
// 背景(バックグラウンド)処理 [FRONTBG.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"


//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define FRONTBG_TEXTURENAMRE "data/TEXTURE/bg002.png" //読み込むテクスチャ
#define FRONTBG_POS_X  (0)　　　//背景の左上X座標
#define FRONTBG_POS_Y  (0)　　　//背景の左上Y座標
#define FRONTBG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define FRONTBG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define MAX_TEX (1)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureFRONTBG = NULL;		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFRONTBG = NULL;  //頂点バッファのポイント

//=============================================================================
//初期化処理背景
//=============================================================================
void InitFRONTBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
													//デバイス取得
	pDevice = GetDevice();


	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, FRONTBG_TEXTURENAMRE, &g_pTextureFRONTBG);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFRONTBG,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ

	g_pVtxBuffFRONTBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//頂点座標設定
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //右上
		pVtx[1].pos = D3DXVECTOR3(FRONTBG_WIDTH, 0, 0.0f);//右下
		pVtx[2].pos = D3DXVECTOR3(0, FRONTBG_HEIGHT, 0.0f);				 //左上
		pVtx[3].pos = D3DXVECTOR3(FRONTBG_WIDTH, FRONTBG_HEIGHT, 0.0f);		 //左下
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める

	}
	//頂点バッファアンロックする
	g_pVtxBuffFRONTBG->Unlock();

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitFRONTBG(void)
{
		//テクスチャの破棄
		if (g_pTextureFRONTBG != NULL)
		{
			g_pTextureFRONTBG->Release();
			g_pTextureFRONTBG = NULL;
		}

	//頂点バッファの破棄
	if (g_pVtxBuffFRONTBG != NULL)
	{
		g_pVtxBuffFRONTBG->Release();
		g_pVtxBuffFRONTBG = NULL;
	}
}
//=============================================================================
//更新処理背景
//=============================================================================
void UpdateFRONTBG(void)
{
}
//=============================================================================
//描画処理背景
//=============================================================================
void DrawFRONTBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
									//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFRONTBG, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureFRONTBG);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 3);
	}
}
