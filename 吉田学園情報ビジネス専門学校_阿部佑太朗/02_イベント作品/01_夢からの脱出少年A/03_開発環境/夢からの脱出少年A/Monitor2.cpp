//=============================================================================
// 
// モニターの処理 [Monitor.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Monitor2.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MONITOR2_TEXTURENAME		"data\\TEXTURE\\timerframe.png"	//テクスチャのファイル名
#define MONITOR2_X				(930)							//左上座標X
#define MONITOR2_Y				(500)							//左上座標Y	
#define MONITOR2_WIDTH			(1230)				//正方形の横幅座標
#define MONITOR2_HEIGHT			(700)				//正方形の縦幅座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMonitor2 = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMonitor2 = NULL;	//頂点バッファへのポインタ
//*****************************************************************************
// 初期化
//*****************************************************************************
void InitMonitor2(void)
{	//ローカル変数
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MONITOR2_TEXTURENAME,
		&g_pTextureMonitor2);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMonitor2,
		NULL);

	//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffMonitor2->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(MONITOR2_X, MONITOR2_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MONITOR2_WIDTH, MONITOR2_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MONITOR2_X, MONITOR2_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MONITOR2_WIDTH, MONITOR2_HEIGHT, 0.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffMonitor2->Unlock();

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMonitor2(void)
{	//テクスチャの破棄
	if (g_pTextureMonitor2 != NULL)
	{
		g_pTextureMonitor2->Release();
		g_pTextureMonitor2 = NULL;
	}
	//頂点バッファの破棄の破棄
	if (g_pVtxBuffMonitor2 != NULL)
	{
		g_pVtxBuffMonitor2->Release();
		g_pVtxBuffMonitor2 = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonitor2(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawMonitor2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMonitor2, 0, sizeof(VERTEX_2D));
	//頂点フォーマットを設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMonitor2);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//開始する頂点のインデックス
		2); //描画するプリミティブ数
}