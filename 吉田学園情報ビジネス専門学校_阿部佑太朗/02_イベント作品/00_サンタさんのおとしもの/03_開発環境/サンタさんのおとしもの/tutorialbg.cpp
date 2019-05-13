//=============================================================================
//
// チュートリアル背景処理 [tutorialbg.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "bg.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "tutorialbg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIALBG_TEXTURE_NAME  "data/TEXTURE/tutorial.jpg" // 読み込むテクスチャファイル名
#define TUTORIALBG_TEXTURE_NAME2 "data/TEXTURE/PRESSENTER.png" //読み込むテクスチャ
#define TUTORIALBG_POS_X         (0)                            // 背景の左上Ｘ座標
#define TUTORIALBG_POS_Y         (0)                            // 背景の左上Ｙ座標
#define TUTORIALBG_WIDTH         (SCREEN_WIDTH)                 // 背景の幅
#define TUTORIALBG_HEIGHT        (SCREEN_HEIGHT)                // 背景の高さ
#define MAX_TUTO_TEX (2)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureTutorialBG[MAX_TUTO_TEX] = {};       // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;   // 頂点バッファへのポインタ 
D3DXVECTOR3 g_posEnter;
int g_PressTUTO;
TUTOSTATE  g_TSTATE;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();
	g_PressTUTO = 0;

	g_posEnter = D3DXVECTOR3(200, 100, 0);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG_TEXTURE_NAME,
		&g_pTextureTutorialBG[0]);
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG_TEXTURE_NAME2,
		&g_pTextureTutorialBG[1]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_TUTO_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(TUTORIALBG_POS_X, TUTORIALBG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIALBG_WIDTH, TUTORIALBG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIALBG_POS_X, TUTORIALBG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIALBG_WIDTH, TUTORIALBG_HEIGHT, 0.0f);


	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorialBG->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;	//頂点ポインタを8つ進める

				//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_posEnter.x - 200, g_posEnter.y - 50, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_posEnter.x + 200, g_posEnter.y - 50, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_posEnter.x - 200, g_posEnter.y + 50, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_posEnter.x + 200, g_posEnter.y + 50, 0.0f);		 //左下
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
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffTutorialBG->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorialBG(void)
{

	//テクスチャの破棄
	for (int nCount = 0; nCount < MAX_TUTO_TEX; nCount++)
	{
		// テクスチャの破棄
		if (g_pTextureTutorialBG[nCount] != NULL)
		{
			g_pTextureTutorialBG[nCount]->Release();
			g_pTextureTutorialBG[nCount] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorialBG(void)
{
	g_PressTUTO++;

	if (g_PressTUTO >= 60)
	{
		g_PressTUTO = 0;
	}
	//キーボード設定
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_TSTATE = TUTO_END;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_TUTO_TEX-1; nCount++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCount]);

		// タイトル画面の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCount * 4,2);
	}
	switch (g_TSTATE)
	{
	case TUTO_NOMAL:
		if (g_PressTUTO >= 30 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureTutorialBG[1]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		break;
	case TUTO_END:
		if (g_PressTUTO % 6 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureTutorialBG[1]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		break;
	}
}