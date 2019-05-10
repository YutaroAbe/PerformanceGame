//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "game2.h"
#include "game3.h"
#include "game.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/pause100.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE1 "data/TEXTURE/pause000.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE2 "data/TEXTURE/pause001.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE3 "data/TEXTURE/pause002.png" //読み込むテクスチャ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[4] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_Pause[4];
int g_nSelectMenu;
D3DXCOLOR g_PColor;
MODE g_PMODE;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
													//デバイス取得
	pDevice = GetDevice();

	g_PColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_PMODE = MODE_TITLE;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		g_Pause[0] = D3DXVECTOR2(630, 370);
		g_Pause[1] = D3DXVECTOR2(630, 270);
		g_Pause[2] = D3DXVECTOR2(630, 370);
		g_Pause[3] = D3DXVECTOR2(630, 470);
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTexturePause[0]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTexturePause[1]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTexturePause[2]);
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTexturePause[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(g_Pause[0].x - 150.0f, g_Pause[0].y - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Pause[0].x + 150.0f, g_Pause[0].y - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Pause[0].x - 150.0f, g_Pause[0].y + 150.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Pause[0].x + 150.0f, g_Pause[0].y + 150.0f, 0.0f);
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
														//頂点バッファアンロックする
	g_pVtxBuffPause->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0 + 1; nCount < 4; nCount++)
	{
		//頂点座標設定
		//頂点設定
		pVtx[4].pos = D3DXVECTOR3(g_Pause[nCount].x - 100.0f, g_Pause[nCount].y - 30.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Pause[nCount].x + 100.0f, g_Pause[nCount].y - 30.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Pause[nCount].x - 100.0f, g_Pause[nCount].y + 30.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Pause[nCount].x + 100.0f, g_Pause[nCount].y + 30.0f, 0.0f);
		//RHW
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;
		//カラー
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		//テクスチャ座標
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}

	//頂点バッファアンロックする
	g_pVtxBuffPause->Unlock();

	g_nSelectMenu = 0;

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitPause(void)
{
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount]->Release();
			g_pTexturePause[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdatePause(void)
{
	FADE pFade;
	pFade = *GetFade();

	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_nSelectMenu = (g_nSelectMenu + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_nSelectMenu = (g_nSelectMenu + 2) % 3;
	}
	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//エンターでセレクト画面へ
		 //キーボード設定
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				switch (g_nSelectMenu)
				{
				case  0:
					PaauseGame();
					PaauseGame2();
					break;
				case 1:
						//モード設定
						SetFade(MODE_GAME);

					break;
				case 2:
					//モード設定
					SetFade(MODE_SELECT);
					break;
				}
			}
		}
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;	//頂点ポインタを4つ進める

	for (int nCount = 0 + 1; nCount < 4; nCount++)
	{
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		pVtx += 4;	//頂点ポインタを4つ進める

	}
	//頂点バッファアンロックする
	g_pVtxBuffPause->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * (g_nSelectMenu + 1);
	pVtx[0].col = g_PColor;
	pVtx[1].col = g_PColor;
	pVtx[2].col = g_PColor;
	pVtx[3].col = g_PColor;

	//頂点バッファアンロックする
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
									//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
