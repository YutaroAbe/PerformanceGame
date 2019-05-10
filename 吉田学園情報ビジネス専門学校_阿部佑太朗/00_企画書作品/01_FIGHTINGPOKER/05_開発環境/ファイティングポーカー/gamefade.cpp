//=============================================================================
//
// ゲームフェード処理 [gamefade.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "gamefade.h"
#include "poker.h"
#include "cardModel.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_TEXTURENAME	"data//TEXTURE//fadeTitle.jpg"			//読み込む背景
#define NUM_FADE			(2)
#define FADE_POS_X			(0)								//フェードの左上X座標
#define FADE_POS_Y			(0)								//フェードの左上Y座標

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGameFade = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameFade = NULL;		// 頂点バッファへのポインタ
GAMEFADE				g_Gamefade;							// フェード状態
GAMEMODE				g_GameNext;						// 次のモード
D3DXCOLOR				g_colorGameFade;				// フェード色
CARDSIDE				g_SideNext;						// 1P2P交代
bool g_bChangeMode;
bool g_bChangeSide;
//=============================================================================
// 初期化処理
//=============================================================================
void InitGameFade(GAMEMODE mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_Gamefade = GAMEFADE_IN;			//フェードイン状態
	g_GameNext = mode;
	g_SideNext = CARD_SIDE_1P;
	g_bChangeMode = false;
	g_bChangeSide = false;
	g_colorGameFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FADE_TEXTURENAME, &g_pTextureGameFade);

	// 頂点情報の設定
	MakeVertexGameFade(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameFade(void)
{
	//テクスチャの破棄
	if (g_pTextureGameFade != NULL)
	{
		g_pTextureGameFade->Release();
		g_pTextureGameFade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameFade != NULL)
	{
		g_pVtxBuffGameFade->Release();
		g_pVtxBuffGameFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameFade(void)
{
	VERTEX_2D *pVtx;

	if (g_Gamefade != GAMEFADE_NONE)
	{
		if (g_Gamefade == GAMEFADE_IN)			//フェードイン状態にする
		{
			g_colorGameFade.a -= 0.05f;			//画面を透明にしていく
			if (g_colorGameFade.a <= 0.0f)
			{
				g_colorGameFade.a -= 0.0f;
				g_Gamefade = GAMEFADE_NONE;
			}
		}
		else if (g_Gamefade == GAMEFADE_OUT)
		{
			g_colorGameFade.a += 0.07f;			//画面を不透明にしていく
			if (g_colorGameFade.a >= 1.0f)
			{
				g_colorGameFade.a += 1.0f;
				g_Gamefade = GAMEFADE_IN;
				//モードの設定
				if (g_bChangeMode == true)
				{
					SetGameMode(g_GameNext);
					g_bChangeMode = false;
				}
				if (g_bChangeSide == true)
				{
					SetSide(g_SideNext);
					g_bChangeSide = false;
				}
			}
		}
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = g_colorGameFade;
		pVtx[1].col = g_colorGameFade;
		pVtx[2].col = g_colorGameFade;
		pVtx[3].col = g_colorGameFade;
		//頂点バッファをアンロックする
		g_pVtxBuffGameFade->Unlock();
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawGameFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffGameFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_FADE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameFade,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGameFade->Unlock();
}
//=============================================================================
// フェードの設定
//=============================================================================
void SetGameFade(GAMEMODE modeNext)
{
	g_Gamefade = GAMEFADE_OUT;					//フェードアウト状態に
	g_bChangeMode = true;
	g_GameNext = modeNext;
	g_colorGameFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}
//=============================================================================
// フェードの設定
//=============================================================================
void SetPokerFade(CARDSIDE sideNext)
{
	g_Gamefade = GAMEFADE_OUT;					//フェードアウト状態に
	g_bChangeSide = true;
	g_SideNext = sideNext;
	g_colorGameFade = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
}
//=============================================================================
// フェードの取得
//=============================================================================
GAMEFADE GetGameFade(void)
{
	return g_Gamefade;
}
