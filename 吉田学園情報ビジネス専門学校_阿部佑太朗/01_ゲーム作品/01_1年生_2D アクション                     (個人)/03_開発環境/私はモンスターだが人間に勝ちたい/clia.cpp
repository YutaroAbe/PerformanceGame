//=============================================================================
//
// タイトル処理 [CLIA.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "clia.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define CLIA_TEXTURENAMRE "data/TEXTURE/clia001.png" //読み込むテクスチャ
#define CLIA_TEXTURENAMRE2 "data/TEXTURE/Skip000.png" //読み込むテクスチャ
#define CLIA_TEXTURENAMRE3 "data/TEXTURE/clia555.png" //読み込むテクスチャ
#define MAX_CLIA_TEX (3)
#define BG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureCLIA[MAX_CLIA_TEX] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCLIA = NULL;  //頂点バッファのポイント
D3DXVECTOR3 g_PosCLIA;
D3DXVECTOR3 g_CRAPressEnter;
int g_aCPress;												//タイトルプレスエンター
CLIASTATE g_TState;
D3DXVECTOR2 g_CS[2];
int g_aCLIAEND;
//int g_aCLIAEND;
//=============================================================================
//初期化処理タイトル
//=============================================================================
void InitCLIA(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	//初期値設定
	g_PosCLIA = D3DXVECTOR3(600, 680, 0.0f);     //タイトル
	g_CRAPressEnter = D3DXVECTOR3(1000, 690, 0.0f);//プレスエンター
	g_aCPress = 0;
	g_aCLIAEND = 0;
	g_CS[0] = D3DXVECTOR2(0.0f, 0.0f);
	g_CS[1] = D3DXVECTOR2(0.0f, 0.0f);
	g_TState = CLIA_NOMAL;
	//g_aCLIAEND = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, CLIA_TEXTURENAMRE3, &g_pTextureCLIA[0]);//背景
	D3DXCreateTextureFromFile(pDevice, CLIA_TEXTURENAMRE, &g_pTextureCLIA[1]);//プレスエンター
	D3DXCreateTextureFromFile(pDevice, CLIA_TEXTURENAMRE2, &g_pTextureCLIA[2]);//タイトル

																				 //頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CLIA_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCLIA, //頂点バッファのポイント
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffCLIA->Lock(0, 0, (void**)&pVtx, 0);
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(0 + 100, 0+50, 0.0f);		             //右上
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH - 100, 0 + 50, 0.0f);              //右下
	pVtx[2].pos = D3DXVECTOR3(0 + 100, BG_HEIGHT - 100, 0.0f);				 //左上
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH - 100, BG_HEIGHT - 100, 0.0f);		 //左下
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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);				//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);				//左下

	//頂点バッファアンロックする
	g_pVtxBuffCLIA->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffCLIA->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_PosCLIA.x - 600, g_PosCLIA.y - 80, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_PosCLIA.x + 600, g_PosCLIA.y - 80, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_PosCLIA.x - 600, g_PosCLIA.y + 80, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_PosCLIA.x + 600, g_PosCLIA.y + 80, 0.0f);		 //
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
	g_pVtxBuffCLIA->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffCLIA->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 8;	//頂点ポインタを4つ進める

				//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_CRAPressEnter.x - 100, g_CRAPressEnter.y - 30, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_CRAPressEnter.x + 100, g_CRAPressEnter.y - 30, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_CRAPressEnter.x - 100, g_CRAPressEnter.y + 30, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_CRAPressEnter.x + 100, g_CRAPressEnter.y + 30, 0.0f);		 //左下
																							 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファアンロックする
	g_pVtxBuffCLIA->Unlock();
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitCLIA(void)
{
	//テクスチャの破棄[2]
	for (int nCount = 0; nCount < MAX_CLIA_TEX; nCount++)
	{
		if (g_pTextureCLIA[nCount] != NULL)
		{
			g_pTextureCLIA[nCount]->Release();
			g_pTextureCLIA[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffCLIA != NULL)
	{
		g_pVtxBuffCLIA->Release();
		g_pVtxBuffCLIA = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateCLIA(void)
{
	g_aCPress++;
	g_CS[0].y -= 0.0002f;
	g_CS[1].x += 0.003f;
	
	g_aCLIAEND++;
	FADE pFade;
	pFade = *GetFade();
	if (g_aCLIAEND >= 1900)
	{//放置してたらタイトル画面へ
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_SELECT);
		}
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffCLIA->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - g_CS[0].y);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - g_CS[0].y);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f - g_CS[0].y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f - g_CS[0].y);
	pVtx += 4;											
	pVtx[0].tex = D3DXVECTOR2(g_CS[1].x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_CS[1].x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_CS[1].x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_CS[1].x, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffCLIA->Unlock();
	if (g_aCPress >= 60)
	{
		g_aCPress = 0;
	}

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_TState = CLIA_END;
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_SELECT);
		}
	}

}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawCLIA(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCLIA, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_CLIA_TEX - 1; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureCLIA[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_TState)
	{
	case CLIA_NOMAL:
		if (g_aCPress >= 30 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureCLIA[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	case CLIA_END:
		if (g_aCPress % 6 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureCLIA[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}
}