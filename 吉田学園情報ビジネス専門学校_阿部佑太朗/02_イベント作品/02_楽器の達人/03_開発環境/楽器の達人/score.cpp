//=========================================================================================================================
//
// スコアの処理 [score.cpp]
// Author :　YUTARO　ABE
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "score.h"//スコア
#include "input.h"//キーボード
#include "ranking.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_SCORE_NUMBER (8)
#define TEXTURE_SCORE "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名
#define TEXTURE_SCORE1 "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名
#define TEXTURE_SCORE2 "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;// 頂点バッファへのポインタ
int g_nScore;// スコア
D3DXVECTOR3 g_posScore;

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	float nCntScore;//スコアカウント
					//float nScorePos;//スコア位置

					//デバイスの取得
	pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 0;

	//位置
	g_posScore = D3DXVECTOR3(880, 70, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(pDevice, TEXTURE_SCORE, &g_pTextureScore);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファをロック
	g_pVtxBuffScore->Lock
	(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y - 30, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y - 30, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y + 30, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y + 30, 0.0f);
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
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
		g_posScore.x += 50;
	}

	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=========================================================================================================================
// スコア終了処理
//=========================================================================================================================
void UninitScore(void)
{
	//テクスチャーの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
	SortRanking(g_nScore);
}

//=========================================================================================================================
// スコア更新処理
//=========================================================================================================================
void UpdateScore(void)
{
}

//=========================================================================================================================
// スコア描画処理
//=========================================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	int nCntScore;//スコアカウント

				  //デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureScore);

	//スコアの描画
	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{//スコアカウント
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//=========================================================================================================================
// スコアの加算
//=========================================================================================================================
void AddScore(int nValue)
{

	int nCntScore;
	int aNumber[MAX_SCORE_NUMBER];

	g_nScore += nValue;

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファをロック
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	aNumber[0] = g_nScore / 100000000 / 10000000;
	aNumber[1] = g_nScore % 10000000 / 1000000;
	aNumber[2] = g_nScore % 1000000 / 100000;
	aNumber[3] = g_nScore % 100000 / 10000;
	aNumber[4] = g_nScore % 10000 / 1000;
	aNumber[5] = g_nScore % 1000 / 100;
	aNumber[6] = g_nScore % 100 / 10;
	aNumber[7] = g_nScore % 10 / 1;


	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{//スコアカウント
	 //テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
int GetScore(void)
{
	return g_nScore;
}
