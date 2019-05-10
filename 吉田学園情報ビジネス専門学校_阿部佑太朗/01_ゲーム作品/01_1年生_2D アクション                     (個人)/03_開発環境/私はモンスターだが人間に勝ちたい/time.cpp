//=========================================================================================================================
//
// タイムの処理 [time.cpp]
// Author : 
//
//=========================================================================================================================
#include "time.h"//タイム
#include "input.h"//キーボード
#include "fade.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_TIME_NUMBER (3)
#define TEXTURE_TIME "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;// 頂点バッファへのポインタ
int g_nTime;// スコア
D3DXVECTOR3 g_posTime;
int nCounterTime;

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	float nCntTime;//スコアカウント

	//デバイスの取得
	pDevice = GetDevice();

	// スコアの初期化
	g_nTime = 150 * 60;
	nCounterTime = 0;

	//位置
	g_posTime = D3DXVECTOR3(630, 40, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,TEXTURE_TIME,&g_pTextureTime);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUMBER ,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTime,
								NULL);	

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	 
	for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - 25.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 25.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - 25.0f, g_posTime.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 25.0f, g_posTime.y + 20.0f, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
		g_posTime.x += 50;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();

}

//=========================================================================================================================
// スコア終了処理
//=========================================================================================================================
void UninitTime(void)
{
	//テクスチャーの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=========================================================================================================================
// スコア更新処理
//=========================================================================================================================
void UpdateTime(void)
{
	nCounterTime++;
	if (nCounterTime % 60 == 0)
	{
		AddTime(1);
	}
	if (g_nTime <= 0)
	{
		g_nTime = 0;
	}
}

//=========================================================================================================================
// スコア描画処理
//=========================================================================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	int nCntTime;//スコアカウント

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(0,g_pVtxBuffTime,0,sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTime);

	//スコアの描画
	for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
	{//スコアカウント
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//=========================================================================================================================
// スコアの加算
//=========================================================================================================================
void AddTime(int nValue )
{
	int nCntScore;
	int aNumber[MAX_TIME_NUMBER];

	g_nTime -= nValue;

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	

	/*aNumber[0] = g_nTime / 100000000 / 10000000;
	aNumber[1] = g_nTime % 10000000 / 1000000;
	aNumber[2] = g_nTime % 1000000 / 100000;*/
	aNumber[0] = g_nTime / 60 % 1000/ 100;
	aNumber[1] = g_nTime / 60 % 100 / 10;
	aNumber[2] = g_nTime / 60 % 10 / 1;
	//aNumber[6] = g_nTime % 100 / 10;
	//aNumber[7] = g_nTime % 10 / 1;

	//頂点バッファをロック
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntScore = 0; nCntScore < MAX_TIME_NUMBER; nCntScore++)
	{//スコアカウント
	 //テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();

	FADE pFade;
		pFade = *GetFade();
	if (g_nTime <= 0)
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RESULT);
		}
	}


}


