//? =============================================================================
//! ランキング処理 [ranking.cpp]
//! Author :
//? =============================================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
//? =============================================================================
//? マクロ定義
//? =============================================================================
#define	TEXTURE_SCORE		"data/TEXTURE/RANKING/number01.png"
#define	TEXTURE_SCORE1		"data/TEXTURE/RANKING/RANKING_UI.png"
#define	TEXTURE_SCORE2		"data/TEXTURE/RANKING/RANKING_BG02.png"
#define	TEXTURE_SCORE3		"data/TEXTURE/RANKING/RANKING_LOGO.png"

#define RANKING_POS_X	(60.0f)			// ランキングの横幅
#define RANKING_POS_Y	(80.0f)		// ランキングの縦幅
#define RANK_X			(150)
#define RANK_Y			(590)
#define RANKING_X		(SCREEN_WIDTH)
#define RANKING_Y		(100)
#define SCORE_PLACE		(D3DXVECTOR3(SCREEN_WIDTH/2 + RANKING_POS_X * 4,180.0f,0.0f))
#define RANK_PLACE		(D3DXVECTOR3(SCREEN_WIDTH/2 - 300 ,SCREEN_HEIGHT/2 + 55,0.0f))
#define RANKING_PLACE	(D3DXVECTOR3(SCREEN_WIDTH/2,60,0.0f))

#define MAX_RANKING		(5)
#define MAX_ELSE        (4)
#define MAX_TEX			(5)
//? =============================================================================
//? プロトタイプ宣言
//? =============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

//? =============================================================================
//? グローバル変数
//? =============================================================================
LPDIRECT3DTEXTURE9		g_pTextureRanking[MAX_TEX] = {};							// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;									// 頂点バッファへのポインタ
static int				g_nRanking[MAX_RANKING] = {0,0,0,0,0};	// スコア
int						nCounterFade;												// フェードカウンタ－
int						g_nScoreNow;												// 今のスコア
D3DXCOLOR				g_nScoreCol[MAX_RANKING + MAX_ELSE];								// 今のスコアの色
D3DXVECTOR3				g_nScorePos[MAX_RANKING + MAX_ELSE];
bool					bHeightScore;
int nFlash;
FLASH flash;
//? =============================================================================
//? 初期化処理
//? =============================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	nCounterFade = 0;
	nFlash = 0;
	flash = OFF;

	for (int nCnt = 0; nCnt < MAX_RANKING + MAX_ELSE; nCnt++)
	{
		g_nScoreCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_nScorePos[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,TEXTURE_SCORE,&g_pTextureRanking[RANKINGTYPE_SCORE]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_SCORE1,&g_pTextureRanking[RANKINGTYPE_RANK]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_SCORE2,&g_pTextureRanking[RANKINGTYPE_BG]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_SCORE3,&g_pTextureRanking[RANKINGTYPE_ROGO]);
	// 頂点情報の作成
	MakeVertexRanking(pDevice);
}

//? =============================================================================
//? 終了処理
//? =============================================================================
void UninitRanking(void)
{
	// テクスチャの開放
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_pTextureRanking[nCnt] != NULL)
		{
			g_pTextureRanking[nCnt]->Release();
			g_pTextureRanking[nCnt] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//? =============================================================================
//? 更新処理
//? =============================================================================
void UpdateRanking(void)
{
	FADE pFade;
	// フェードの取得
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		// 決定キー押したかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			// モード設定
			SetFade(MODE_SELECTMODE);
			PlaySound(SOUND_LABEL_SE_DECIDE);
			bHeightScore = false;
		}

	}

	//! =======================================================
	//! ランキングスコア
	//! =======================================================
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	if (bHeightScore == true)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			for (int nCnt = 0; nCnt < 8; nCnt++, pVtx += 4)
			{
				if (g_nRanking[nCntRanking] == g_nScoreNow)
				{


					switch (flash)
					{
					case ON:

						g_nScoreCol[nCntRanking].r += 0.03f;
						g_nScoreCol[nCntRanking].g = 0.0f;
						g_nScoreCol[nCntRanking].b = 0.0f;

						if (g_nScoreCol[nCntRanking].r >= 1.0f)
						{
							g_nScoreCol[nCntRanking].r = 1.0f;
							g_nScoreCol[nCntRanking].g = 0.0f;
							g_nScoreCol[nCntRanking].b = 0.0f;
							flash = OFF;
						}
						break;

					case OFF:

						g_nScoreCol[nCntRanking].r -= 0.03f;
						g_nScoreCol[nCntRanking].g = 0.0f;
						g_nScoreCol[nCntRanking].b = 0.0f;

						if (g_nScoreCol[nCntRanking].r <= 0.0f)
						{
							g_nScoreCol[nCntRanking].r = 0.0f;
							g_nScoreCol[nCntRanking].g = 0.0f;
							g_nScoreCol[nCntRanking].b = 0.0f;
							flash = ON;
						}
						break;
					}


					// 頂点カラーの設定
					pVtx[RANKINGTYPE_SCORE * 4].col = (g_nScoreCol[nCntRanking]);
					pVtx[RANKINGTYPE_SCORE * 4 + 1].col = (g_nScoreCol[nCntRanking]);
					pVtx[RANKINGTYPE_SCORE * 4 + 2].col = (g_nScoreCol[nCntRanking]);
					pVtx[RANKINGTYPE_SCORE * 4 + 3].col = (g_nScoreCol[nCntRanking]);


				}
			}
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();
}

//? =============================================================================
//? 描画処理
//? =============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//! 背景
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking[RANKINGTYPE_BG]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		4 * 8 * MAX_RANKING + 8,
		2);

	//! ランキングスコア
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking[RANKINGTYPE_ROGO]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		4 * 8 * MAX_RANKING + 12,
		2);
	//! 順位
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking[RANKINGTYPE_RANK]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		4 * 8 * MAX_RANKING + 4,
		2);

	//! ロゴ
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking[RANKINGTYPE_SCORE]);
	// ポリゴンの描画
	for (int nCnt = 0; nCnt < 8 * MAX_RANKING; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCnt,
			2);
	}
}

//? =============================================================================
//? 頂点情報の作成
//? =============================================================================
void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D*pVtx;		// 頂点情報へのポインタ
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8 * (MAX_RANKING + MAX_ELSE),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	//! ===================================
	//! ランキングスコア
	//! ===================================

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING ; nCntRanking++)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++, pVtx += 4)
		{
			// 頂点情報を設定
			pVtx[0].pos = D3DXVECTOR3(-(RANKING_POS_X / 2) - (RANKING_POS_X*nCnt), -(RANKING_POS_Y / 2) + ((40 + RANKING_POS_Y) * nCntRanking), 0.0f) + SCORE_PLACE;
			pVtx[1].pos = D3DXVECTOR3((RANKING_POS_X / 2) - (RANKING_POS_X*nCnt), -(RANKING_POS_Y / 2) + ((40 + RANKING_POS_Y) * nCntRanking), 0.0f) + SCORE_PLACE;
			pVtx[2].pos = D3DXVECTOR3(-(RANKING_POS_X / 2) - (RANKING_POS_X*nCnt), (RANKING_POS_Y / 2) + ((40 + RANKING_POS_Y) * nCntRanking), 0.0f) + SCORE_PLACE;
			pVtx[3].pos = D3DXVECTOR3((RANKING_POS_X / 2) - (RANKING_POS_X*nCnt), (RANKING_POS_Y / 2) + ((40 + RANKING_POS_Y) * nCntRanking), 0.0f) + SCORE_PLACE;
			// rhwの設定
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				pVtx[nCnt].rhw = 1.0f;
			}
			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			int nData = 1;

			for (int nCnt2 = nCnt; nCnt2 != 0; nCnt2--)
			{
				nData *= 10;
			}

			pVtx[0].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_nRanking[nCntRanking] % (10 * nData) / nData)* 0.1f + 0.1f, 1.0f);
		}
	}

	//! ===================================
	//! 順位
	//! ===================================
	pVtx += 4;
	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(-RANK_X / 2,- RANK_Y / 2, 0.0f) +RANK_PLACE;
	pVtx[1].pos = D3DXVECTOR3(RANK_X / 2,- RANK_Y / 2, 0.0f) + RANK_PLACE;
	pVtx[2].pos = D3DXVECTOR3(-RANK_X / 2, RANK_Y / 2, 0.0f) + RANK_PLACE;
	pVtx[3].pos = D3DXVECTOR3(RANK_X / 2, RANK_Y / 2, 0.0f) + RANK_PLACE;
	// rhwの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].rhw = 1.0f;
	}
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//! ===================================
	//! 背景
	//! ===================================
	pVtx += 4;
	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0,0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	// rhwの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].rhw = 1.0f;
	}
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//! ===================================
	//! ロゴ
	//! ===================================
	pVtx += 4;
	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(-RANKING_X / 2, -RANKING_Y / 2, 0.0f) + RANKING_PLACE;
	pVtx[1].pos = D3DXVECTOR3(RANKING_X / 2, -RANKING_Y / 2, 0.0f) + RANKING_PLACE;
	pVtx[2].pos = D3DXVECTOR3(-RANKING_X / 2, RANKING_Y / 2, 0.0f) + RANKING_PLACE;
	pVtx[3].pos = D3DXVECTOR3(RANKING_X / 2, RANKING_Y / 2, 0.0f) + RANKING_PLACE;
	// rhwの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].rhw = 1.0f;
	}
	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

}

//? =============================================================================
//? ランキングの入れ替え処理
//? =============================================================================
void SortRanking(int nScore)
{
	int nRank;
	int aData[6];
	aData[5] = nScore;

	for (int nCntNum = 0; nCntNum < 5; nCntNum++)
	{
		aData[nCntNum] = g_nRanking[nCntNum];
	}
	for (int nCntNum = 1; nCntNum < 6; nCntNum++)
	{
		for (int nCntNum1 = nCntNum; nCntNum1 > 0; nCntNum1--)
		{
			if (aData[nCntNum1 - 1] <= aData[nCntNum1])
			{
				nRank = aData[nCntNum1];
				aData[nCntNum1] = aData[nCntNum1 - 1];
				aData[nCntNum1 - 1] = nRank;
			}
		}
	}
	for (int nCntNum = 0; nCntNum < 5; nCntNum++)
	{
		g_nRanking[nCntNum] = aData[nCntNum];
	}
	bHeightScore = true;
	g_nScoreNow = nScore;

}
