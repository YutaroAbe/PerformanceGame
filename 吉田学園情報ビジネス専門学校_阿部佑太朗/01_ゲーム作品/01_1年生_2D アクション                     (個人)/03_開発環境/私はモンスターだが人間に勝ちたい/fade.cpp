//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAMRE1 "data/TEXTURE/fade000.png" //読み込むテクスチャ

#define BG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// 頂点バッファへのポインタ
FADE					g_fade;					// フェード状態
MODE					g_modeNext;				// 次のモード
D3DXCOLOR				g_colorFade;			// フェード色

//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_fade = FADE_IN;	//フェードの状態に
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);	//黒い画面(不透明)にしておく

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAMRE1, &g_pTextureFade);


	// 頂点情報の設定
	MakeVertexFade(pDevice);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// 頂点バッファの情報を設定
	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//右下
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);				 //左上
	pVtx[3].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);		 //左下
														 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				//右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//左下

	//頂点バッファアンロックする
	g_pVtxBuffFade->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	// テクスチャの開放
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// 頂点バッファの開放
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	// 頂点バッファの情報を設定
	VERTEX_2D*pVtx;									//頂点情報のポインタ							
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)	//フェード状態
		{
			g_colorFade.r -= 1.0f / 60;	//画面を透明にしておく
			g_colorFade.g -= 1.0f / 60;	//画面を透明にしておく
			g_colorFade.b -= 1.0f / 60;	//画面を透明にしておく
			g_colorFade.a -= 1.0f / 60;	//画面を透明にしておく

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//何もしていない状態
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.r += 1.0f / 60;
			g_colorFade.g += 1.0f / 60;
			g_colorFade.b += 1.0f / 60;
			g_colorFade.a += 1.0f / 60;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	//フェード状態に

				//モードの設定
				SetMode(g_modeNext);
			}
		}
		//カラー
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//頂点バッファアンロックする
		g_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	if (g_colorFade.a >= 0.25f)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
}

//=============================================================================
// フェードの設定
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒い画面(透明)にしておく
}

//=============================================================================
// フェードの取得
//=============================================================================
FADE *GetFade(void)
{
	return &g_fade;
}