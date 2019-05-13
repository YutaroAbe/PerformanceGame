//=============================================================================
//
// 制限時間の処理 [gauge.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "gauge.h"
#include "game.h"
#include "ColorBall.h"
#include "model.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_GAUGE000		"data/TEXTURE/LifeFrame000.png"		// 読み込むテクスチャフェイル名
#define MAX_GAUGE				(2)									// ゲージの最大数	
#define REDUCE_GAUGE			(0.20f)								// ゲージの減る量(毎フレーム)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGauge[MAX_GAUGE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;				// 頂点バッファへのポインタ
float g_fGauge;												// ゲージの値
float g_fGaugeColR;											// ゲージの色(赤)
float g_fGaugeColG;											// ゲージの色(緑)
float g_fGaugeColB;											// ゲージの色(青)
GAUGE g_aGauge;
//=============================================================================
// 初期化処理
//=============================================================================
void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ゲージの初期化
	g_fGauge = 340.0f;
	g_fGaugeColR = 0.0f;
	g_fGaugeColG = 1.0f;
	g_fGaugeColB = 0.0f;
	g_aGauge.nChargeGauge = 1;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE000, &g_pTextureGauge[1]);
	//D3DXCreateTextureFromFile(pDevice, TEXTURE_GAUGE001, &g_pTextureGauge[1]);
	// 頂点情報の作成
	MakeVertexGauge(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGauge(void)
{
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		// テクスチャの開放
		if (g_pTextureGauge[nCntGauge] != NULL)
		{
			g_pTextureGauge[nCntGauge]->Release();
			g_pTextureGauge[nCntGauge] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGauge(void)
{
	//ゲームステイトの取得
	FADE *pFade;
	pFade = GetFade();
	COLORBALL *pColorBall;
	pColorBall = GetColorBall();
	Player *pPlayer;
	pPlayer = GetPlayer();

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	//正しい色に乗っていないときゲージが減る
	if (pPlayer->pModel != NULL)
	{
		if (pColorBall->nType + 1 != pPlayer->pModel->col 
			&& pPlayer->pModel->col != BLOCKCOLOR_START
			&& pColorBall->state == COLORBALLSTATE_STOP)
		{
			g_fGauge += (REDUCE_GAUGE * g_aGauge.nChargeGauge);
			PlaySound(SOUND_LABEL_SE015);
		}
	}
	//ゲージの初期位置
	if (g_fGauge < 340.0f)
	{
		g_fGauge = 341.0f;
	}

	pVtx[0].pos = D3DXVECTOR3(100.0f, g_fGauge, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(150.0f, g_fGauge, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f, 580.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(150.0f, 580.0f, 0.0f);

	// 色の変化(ゲージ)
	if (g_fGauge >= 320.0f && g_fGauge <= 381.9f)
	{
		// ゲージ(緑色)
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
	}
	else if (g_fGauge >= 381.9f && g_fGauge <= 484.9f)
	{
		// ゲージ(オレンジ色)
		g_fGaugeColG += 0.004f;
		g_fGaugeColR += 0.004f;
		if (g_fGaugeColG >= 0.5f)
		{
			g_fGaugeColG = 0.5f;
		}
		if (g_fGaugeColR >= 1.0f)
		{
			g_fGaugeColR = 1.0f;
		}
		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
	}
	else if (g_fGauge >= 484.9f && g_fGauge <= 580.0f)
	{
		// ゲージ(赤色)
		g_fGaugeColG -= 0.004f;
		if (g_fGaugeColG <= 0.0f)
		{
			g_fGaugeColG = 0.0f;
		}
		pVtx[0].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(g_fGaugeColR, g_fGaugeColG, 0.0f, 0.8f);
	}
	//ゲージがなくなるとゲームオーバー
	if (g_fGauge >= 580.0f && *pFade != FADE_OUT)
	{	// 体力がなくなった(GAMEOVER)
		SetFade(MODE_GAMEOVER);
	}
	//頂点バッファのアンロック
	g_pVtxBuffGauge->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureGauge[nCntGauge]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntGauge * 4, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GAUGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	// 頂点情報の作成
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGauge = 0; nCntGauge < MAX_GAUGE; nCntGauge++)
	{
		if (nCntGauge == 0)
		{	//ゲージ
			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(100.0f, g_fGauge, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(150.0f, g_fGauge, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(100.0f, 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(150.0f, 580.0f, 0.0f);

			//頂点カラー設定
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f);
		}
		else if (nCntGauge == 1)
		{	//体力のフレーム
			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(98.0f, 315.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(150.0f, 315.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(98.0f, 582.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(150.0f, 582.0f, 0.0f);

			//頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファのアンロック
	g_pVtxBuffGauge->Unlock();
}


//*****************************************************************************
//モデルポインタ処理
//*****************************************************************************
GAUGE *GetGauge(void)
{
	return &g_aGauge;
}
