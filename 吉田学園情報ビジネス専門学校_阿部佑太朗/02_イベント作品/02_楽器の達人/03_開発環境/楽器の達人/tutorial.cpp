//=============================================================================
//
// 背景描画処理 [tutorial.cpp]
// Author :YUTARO ABE
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "serect.h"
#include "tutorial.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIAL_TEXTURE_NAME "data/TEXTURE/TUTORIAL.png"	 // 読み込むテクスチャファイル名

#define TUTORIAL_POS_X        (0)                              // 背景の左上Ｘ座標
#define TUTORIAL_POS_Y        (0)                              // 背景の左上Ｙ座標
#define TUTORIAL_WIDTH        (SCREEN_WIDTH)                   // 背景の幅
#define TUTORIAL_HEIGHT       (SCREEN_HEIGHT)                  // 背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9  g_pTextureTutorial = NULL;                  // テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;              // 頂点バッファへのポインタ
int g_nCountTime3 = 0;

//=============================================================================
// ポリゴン初期化処理
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	////サウンド
	//PlaySound(SOUND_LABEL_bgm_maoudamashii_acoustic37);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE_NAME,
		&g_pTextureTutorial);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D *pVtxTutorial;   // 頂点情報へのポインタ

							   // 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtxTutorial, 0);

	// 頂点座標
	pVtxTutorial[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtxTutorial[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtxTutorial[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtxTutorial[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

	// 頂点テクスチャ
	pVtxTutorial[0].rhw = 1.0f;
	pVtxTutorial[1].rhw = 1.0f;
	pVtxTutorial[2].rhw = 1.0f;
	pVtxTutorial[3].rhw = 1.0f;

	// 頂点カラー
	pVtxTutorial[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxTutorial[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxTutorial[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtxTutorial[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtxTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtxTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtxTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtxTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//=============================================================================
// ポリゴン終了処理
//=============================================================================
void UninitTutorial(void)
{
	// テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//=============================================================================
// ポリゴン更新処理
//=============================================================================
void UpdateTutorial(void)
{
	FADE pFade;

	pFade = *GetFade();

	g_nCountTime3++;
	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//モード設定
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_SELECTMODE);
		}
	}

}

//=============================================================================
// ポリゴン描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}