//=========================================================================================================================
//
// ランキング処理 [Ranking.cpp]
// Author :
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "ranking.h"//スコア
#include "input.h"//キーボード
#include "fade.h"
#include "score.h"
#include "bg.h"
#include "sound.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_RANKING_NUMBER (8)
#define TEXTURE_RANKING "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;// 頂点バッファへのポインタ
int g_aRanking = 0;//ランキング
int g_aNumber[MAX_RANKING_NUMBER] = {0,0,0,0,0,0,0,0};

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//	デバイスポインタ
	int nCntRanking;							//	スコアカウント
	float nRankingPos;							//	スコア位置
	//	初期化処理バックグラウンド
	InitBG();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,TEXTURE_RANKING,&g_pTextureRanking);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKING_NUMBER,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffRanking,
								NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffRanking->Lock(0,0,(void**)&pVtx,0);

	for (nCntRanking = 0, nRankingPos = 100; nCntRanking < MAX_RANKING_NUMBER; nCntRanking++, nRankingPos += 130)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(nRankingPos, 550.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(nRankingPos + 150.0f, 550.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(nRankingPos, 650.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(nRankingPos + 150.0f, 650.0f, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}

//=========================================================================================================================
// スコア終了処理
//=========================================================================================================================
void UninitRanking(void)
{
	// 終了処理バックグラウンド
	UninitBG();

	//テクスチャーの破棄
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=========================================================================================================================
// スコア更新処理
//=========================================================================================================================
void UpdateRanking(void)
{
	// 更新処理バックグラウンド
	UpdateBG();
	FADE pFade;

	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_SELECTMODE);
		}
	}
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffRanking->Lock(0,0,(void**)&pVtx,0);

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING_NUMBER; nCntRanking++)
	{//スコアカウント
		 //テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aNumber[nCntRanking]  * 0.1f ) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(((g_aNumber[nCntRanking] ) * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f ) + 0.1f, 1.0f);
		pVtx += 4;//頂点データのポインタを４つ分進める
	}

		//頂点バッファをアンロック
	g_pVtxBuffRanking->Unlock();
}

//=========================================================================================================================
// スコア描画処理
//=========================================================================================================================
void DrawRanking(void)
{
	//描画処理バックグラウンド
	DrawBG();
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	int nCntRanking;//スコアカウント

				  //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(0,g_pVtxBuffRanking,0,sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//スコアの描画
	for (nCntRanking = 0; nCntRanking< MAX_RANKING_NUMBER; nCntRanking++)
	{//スコアカウント
	 //テクスチャ設定
		pDevice->SetTexture(0, g_pTextureRanking);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRanking * 4, 2);
	}
}
//=========================================================================================================================
//セットランキング
//=========================================================================================================================
void SetRankScore(int nScore)
{
	if (nScore > g_aRanking)
	{
		g_aRanking = nScore;		//ハイスコア更新
	}
	g_aNumber[0] = g_aRanking / 100000000 / 10000000;
	g_aNumber[1] = g_aRanking % 10000000 / 1000000;
	g_aNumber[2] = g_aRanking % 1000000 / 100000;
	g_aNumber[3] = g_aRanking % 100000 / 10000;
	g_aNumber[4] = g_aRanking % 10000 / 1000;
	g_aNumber[5] = g_aRanking % 1000 / 100;
	g_aNumber[6] = g_aRanking % 100 / 10;
	g_aNumber[7] = g_aRanking % 10 / 1;
}
