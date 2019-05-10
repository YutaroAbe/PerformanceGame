//=============================================================================
//
// スコア表示処理 [getscore.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "getscore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NAME_GETSCORE  "data/TEXTURE/number.png"	// 読み込むテクスチャファイル名
#define MAX_SCORENUMBER       (4)                           // スコアの桁数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexGetScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGetScore = NULL;	   // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGetScore = NULL;	   // 頂点バッファへのポインタ
int                     g_TextureGetScorePos;          // テクスチャX座標
GETSCORE                g_aGetScore[MAX_DRAW_SCORE];   // スコア表示情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGetScore = 0; nCntGetScore < MAX_DRAW_SCORE; nCntGetScore++)
	{// 表示できるスコアの数だけ繰り返し
		g_aGetScore[nCntGetScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 座標を初期化
		g_aGetScore[nCntGetScore].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 移動量を初期化
		g_aGetScore[nCntGetScore].fWidth = 0.0f;                          // 幅を初期化
		g_aGetScore[nCntGetScore].fHeight = 0.0f;                         // 高さを初期化
		g_aGetScore[nCntGetScore].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);   // 色を初期化
		g_aGetScore[nCntGetScore].bUse = false;                           // 使用していない状態にする
		g_aGetScore[nCntGetScore].GetScore = 0;                           // 表示するスコアを初期化
		g_aGetScore[nCntGetScore].nCounterDraw = 0;                       // 表示する時間を初期化
	}
												
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,   // デバイスへのポインタ
		TEXTURE_NAME_GETSCORE,	         // ファイルの名前
		&g_pTextureGetScore);	         // テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexGetScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGetScore(void)
{
	// テクスチャの開放
	if (g_pTextureGetScore != NULL)
	{
		g_pTextureGetScore->Release();
		g_pTextureGetScore = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffGetScore != NULL)
	{
		g_pVtxBuffGetScore->Release();
		g_pVtxBuffGetScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGetScore(void)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// 表示できるスコアだけ繰り返し
		if (g_aGetScore[nCntGetScore1].bUse == true)
		{// 使用されている
			float posS = 0.0f;
			g_aGetScore[nCntGetScore1].pos += g_aGetScore[nCntGetScore1].move;
			g_aGetScore[nCntGetScore1].nCounterDraw--;
			for (float nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// 表示するスコアの桁数だけ繰り返し
				float pow = powf(10.0f, nCntGetScore2);  // 10のn乗を用意
				int Score = (int)pow;                    // float型をint型に変換
				g_TextureGetScorePos = g_aGetScore[nCntGetScore1].GetScore % (Score * 10) / Score;

				// 頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 1.0f);

				pVtx += 4;
				posS -= 18.0f;
			}
			if (g_aGetScore[nCntGetScore1].nCounterDraw <= 0)
			{// カウンターが0になった
				g_aGetScore[nCntGetScore1].bUse = false;
			}
		}
		else
		{// 使用していない
			pVtx += 4 * MAX_SCORENUMBER;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGetScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGetScore);

	// ポリゴンの描画
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// 表示できるスコアだけ繰り返し
		if (g_aGetScore[nCntGetScore1].bUse == true)
		{// 使用されている
			for (int nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// 表示するスコアの桁数だけ繰り返し
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					(nCntGetScore1 * 16) + (nCntGetScore2 * 4),
					2);
			}
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexGetScore(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORENUMBER * MAX_DRAW_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGetScore,
		NULL);

	// 頂点バッファを生成
	VERTEX_2D *pVtx;
	float posS = 0.0f;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// 表示できるスコアだけ繰り返し
		for (int nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
		{// 表示するスコアの桁数だけ繰り返し
		 // 頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

			// 頂点テクスチャ
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// 頂点カラー
			pVtx[0].col = g_aGetScore[nCntGetScore1].col;
			pVtx[1].col = g_aGetScore[nCntGetScore1].col;
			pVtx[2].col = g_aGetScore[nCntGetScore1].col;
			pVtx[3].col = g_aGetScore[nCntGetScore1].col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
			posS -= 18.0f;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// スコアのセット
//=============================================================================
void SetScore(D3DXVECTOR3 pos, float width, float height,int score)
{
	float posS = 0.0f;
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// 表示できるスコアの数だけ繰り返し
		if (g_aGetScore[nCntGetScore1].bUse == false)
		{// 使用されていない
			g_aGetScore[nCntGetScore1].pos = pos;
			g_aGetScore[nCntGetScore1].fWidth = width;
			g_aGetScore[nCntGetScore1].fHeight = height;
			g_aGetScore[nCntGetScore1].GetScore = score;
			g_aGetScore[nCntGetScore1].move.y = -2.0f;
			g_aGetScore[nCntGetScore1].nCounterDraw = 30;
			g_aGetScore[nCntGetScore1].bUse = true;
			for (float nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// 表示するスコアの桁数だけ繰り返し
				float pow = powf(10.0f, nCntGetScore2);  // 10のn乗を用意
				int Score = (int)pow;                    // float型をint型に変換
				g_TextureGetScorePos = g_aGetScore[nCntGetScore1].GetScore % (Score * 10) / Score;
			    // 頂点座標
				pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 1.0f);

				pVtx += 4;
				posS -= 18.0f;
			}
			break;
		}
		pVtx += 4 * MAX_SCORENUMBER;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// スコア表示情報の取得
//=============================================================================
GETSCORE *GetGetScore(void)
{
	return &g_aGetScore[0];
}