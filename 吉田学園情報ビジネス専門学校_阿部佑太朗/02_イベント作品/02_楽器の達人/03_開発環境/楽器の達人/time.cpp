//=========================================================================================================================
//
// タイムの処理 [time.cpp]
// Author :　YUTARO　ABE
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "time.h"//タイム
#include "input.h"//キーボード
#include "fade.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_TIME_NUMBER (7)
#define TEXTURE_TIME "data/TEXTURE/number000.png"// 読み込むテクスチャファイル名

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;// 頂点バッファへのポインタ
int g_nTime;// スコア
D3DXVECTOR3 g_posTime;
//int g_nCounterTimeState;

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスポインタ
	float nCntTime;//スコアカウント
	float nTimePos;//スコア位置

	//デバイスの取得
	pDevice = GetDevice();

	// スコアの初期化
	g_nTime = 2000;

	//位置
	g_posTime = D3DXVECTOR3(750, 70, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_TIME,
		&g_pTextureTime
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUMBER ,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTime,
								NULL
								);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファをロック
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0, nTimePos = 1100; nCntTime < 2; nCntTime++, g_posTime.x -= 40)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - 20.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 20.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - 20.0f, g_posTime.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 20.0f, g_posTime.y + 20.0f, 0.0f);
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
	}
	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();

	//頂点バッファをロック
	g_pVtxBuffTime->Lock(0,0,(void**)&pVtx,0);

	for (nCntTime = 0, nTimePos = 1200; nCntTime < 4 ; nCntTime++, g_posTime.x -= 50)
	{
		//頂点設定
		pVtx[8].pos = D3DXVECTOR3(g_posTime.x - 30.0f, g_posTime.y - 30.0f, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posTime.x + 30.0f, g_posTime.y - 30.0f, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posTime.x - 30.0f, g_posTime.y + 30.0f, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posTime.x + 30.0f, g_posTime.y + 30.0f, 0.0f);
		//1.0fで固定
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;
		//頂点カラー設定
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める
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
	if (g_nTime <= 0)
	{
		SetGemeState(GAMESTATE_END);

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
	int nCntTime;
	int nTexData;

	g_nTime -= nValue ;//タイムを代入
	nTexData = g_nTime;//タイムを格納

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffTime->Lock(0,0,(void**)&pVtx,0);

		for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
		{//スコアカウント
		 //テクスチャ設定
			pVtx[nCntTime * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
			pVtx[nCntTime * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
			nTexData /= 10;
		}

	//頂点バッファをアンロック
	g_pVtxBuffTime->Unlock();
}


