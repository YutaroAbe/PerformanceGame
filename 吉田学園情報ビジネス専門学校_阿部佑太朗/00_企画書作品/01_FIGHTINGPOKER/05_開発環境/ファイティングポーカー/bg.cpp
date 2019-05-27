//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "main.h"
#include "bg.h"
#include "game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_TEX_1			"data/TEXTURE/bg.jpg"
#define BG_TEX_2			"data/TEXTURE/bg2.jpg"
#define BG_WIDTH			(SCREEN_WIDTH)				//背景の幅
#define BG_HEIGHT			(SCREEN_HEIGHT)				//背景の高さ
#define BG_POS_X			(0)							//背景の左上X座標
#define BG_POS_Y			(0)							//背景の左上Y座標
#define MAX_BG				(1)							//背景の最大数
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//頂点バッファのポインタ
BG g_BG;												//構造体
//=============================================================================
// 初期化処理
//=============================================================================
void InitBG(void)
{
	MODE mode = GetMode();
	GAMEMODE GameMode = GetGameMode();

	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	//各種初期化
	g_BG.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_BG.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの読み込み
	if (mode == MODE_SELECT || GameMode == GAMEMODE_PLAYERSHOW)
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEX_1, &g_pTextureBG);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, BG_TEX_2, &g_pTextureBG);
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D * pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// 終了処理　
//=============================================================================
void UninitBG(void)
{
	//テクスチャの破棄
	if (g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();
		g_pTextureBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// 更新処理　
//=============================================================================
void UpdateBG(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイス取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 背景の取得
//=============================================================================
BG *GetBG(void)
{
	return &g_BG;
}
