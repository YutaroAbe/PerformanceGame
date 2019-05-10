//=============================================================================
// 
// モニターの処理 [Monitor.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "Monitor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MONITOR_TEXTURENAME		"data\\TEXTURE\\Monitor.png"	//テクスチャのファイル名
#define MONITOR_X				(880)							//左上座標X
#define MONITOR_Y				(0)							//左上座標Y	
#define MONITOR_WIDTH			(1180)				//正方形の横幅座標
#define MONITOR_HEIGHT			(200)				//正方形の縦幅座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMonitor = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMonitor = NULL;	//頂点バッファへのポインタ
//*****************************************************************************
// 初期化
//*****************************************************************************
void InitMonitor(void)
{	//ローカル変数
	VERTEX_2D *pVtx;//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MONITOR_TEXTURENAME,
		&g_pTextureMonitor);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMonitor,
		NULL);

	//頂点バッファをロックし頂点データのポインタを取得
	g_pVtxBuffMonitor->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(MONITOR_X, MONITOR_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(MONITOR_WIDTH, MONITOR_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(MONITOR_X, MONITOR_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(MONITOR_WIDTH, MONITOR_HEIGHT, 0.0f);
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
	g_pVtxBuffMonitor->Unlock();

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMonitor(void)
{	//テクスチャの破棄
	if (g_pTextureMonitor != NULL)
	{
		g_pTextureMonitor->Release();
		g_pTextureMonitor = NULL;
	}
	//頂点バッファの破棄の破棄
	if (g_pVtxBuffMonitor != NULL)
	{
		g_pVtxBuffMonitor->Release();
		g_pVtxBuffMonitor = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateMonitor(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawMonitor(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得する
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMonitor, 0, sizeof(VERTEX_2D));
	//頂点フォーマットを設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMonitor);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//開始する頂点のインデックス
		2); //描画するプリミティブ数
}