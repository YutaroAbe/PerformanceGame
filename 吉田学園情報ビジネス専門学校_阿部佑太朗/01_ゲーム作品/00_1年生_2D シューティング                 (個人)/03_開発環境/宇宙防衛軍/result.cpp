//=============================================================================
//
//	リザルト処理 [result.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define RESULT_TEXTURENAMRE "data/TEXTURE/OVER001.png"			//	読み込むテクスチャ
#define RESULT_TEXTURENAMRE1 "data/TEXTURE/OVER000.png"			//	読み込むテクスチャ
#define RESULT_TEXTURENAMRE2 "data/TEXTURE/title002.png"		//	読み込むテクスチャ
#define RESULT_POS_X  (0)　　　									//	背景の左上X座標
#define RESULT_POS_Y  (0)　　									//	背景の左上Y座標
#define RESULT_WIDTH   (SCREEN_WIDTH)							//	背景の幅
#define RESULT_HEIGHT   (SCREEN_HEIGHT)							//	背景の高さ
#define MAX_RESULT (3)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRESULT[MAX_RESULT] = {};			//	テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRESULT = NULL;				//	頂点バッファのポイント
D3DXVECTOR3 g_posResult[2];
int g_aResult;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//	デバイスへのポインタ
	//	デバイス取得
	pDevice = GetDevice();
	g_aResult = 0;
	g_posResult[0] = D3DXVECTOR3(600, 250, 0.0f);
	g_posResult[1] = D3DXVECTOR3(1000, 600, 0.0f);

	//	テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE, &g_pTextureRESULT[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE1, &g_pTextureRESULT[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE2, &g_pTextureRESULT[2]);

	//	頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4* MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRESULT,
		NULL);

	VERTEX_2D*pVtx;									//	頂点情報のポインタ
	//	頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx,0);

	//	頂点座標設定
	//	ポジション
	pVtx[0].pos = D3DXVECTOR3(RESULT_WIDTH, 0, 0.0f);				//右上
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);	//	右下
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);							//	左上
	pVtx[3].pos = D3DXVECTOR3(0, RESULT_HEIGHT, 0.0f);				//	左下
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(1.0f,0.0f);				//	右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//	右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//	左上
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//	左下

	//頂点バッファアンロックする
	g_pVtxBuffRESULT->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//タイトル
	//ポジション
	pVtx[4].pos = D3DXVECTOR3(g_posResult[0].x - 400, g_posResult[0].y - 100, 0.0f);		 //右上
	pVtx[5].pos = D3DXVECTOR3(g_posResult[0].x + 400, g_posResult[0].y - 100, 0.0f);		 //右下
	pVtx[6].pos = D3DXVECTOR3(g_posResult[0].x - 400, g_posResult[0].y + 100, 0.0f);		 //左上
	pVtx[7].pos = D3DXVECTOR3(g_posResult[0].x + 400, g_posResult[0].y + 100, 0.0f);		 //左下
																						 //RHW
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//カラー
	pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	//テクスチャ設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffRESULT->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
	//プレスエンター
	//ポジション
	pVtx[8].pos = D3DXVECTOR3(g_posResult[1].x - 100, g_posResult[1].y - 30, 0.0f);		 //右上
	pVtx[9].pos = D3DXVECTOR3(g_posResult[1].x + 100, g_posResult[1].y - 30, 0.0f);	     //右下
	pVtx[10].pos = D3DXVECTOR3(g_posResult[1].x - 100, g_posResult[1].y + 30, 0.0f);		 //左上
	pVtx[11].pos = D3DXVECTOR3(g_posResult[1].x + 100, g_posResult[1].y + 30, 0.0f);		 //左下
																						 //RHW
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;
	//カラー
	pVtx[8].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[9].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[10].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[11].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//テクスチャ設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffRESULT->Unlock();

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitRESULT(void)
{
	for (int nCount = 0; nCount < MAX_RESULT; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureRESULT[nCount] != NULL)
		{
			g_pTextureRESULT[nCount]->Release();
			g_pTextureRESULT[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRESULT != NULL)
	{
		g_pVtxBuffRESULT->Release();
		g_pVtxBuffRESULT = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateRESULT(void)
{
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	FADE pFade;

	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_RANKING);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == false)
	{
		g_aResult++;
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DCOLOR_RGBA(200- g_aResult, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(155 - g_aResult, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(55 - g_aResult, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0 - g_aResult, 255, 255, 255);
		//頂点バッファアンロックする
		g_pVtxBuffRESULT->Unlock();
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		//タイトルカラー
		pVtx[4].col = D3DCOLOR_RGBA(g_aResult + 250, g_aResult - 210, g_aResult - 0, 0);
		pVtx[5].col = D3DCOLOR_RGBA(g_aResult + 260, g_aResult - 220, g_aResult - 0, 0);
		pVtx[6].col = D3DCOLOR_RGBA(g_aResult + 270, g_aResult - 230, g_aResult - 0, 0);
		pVtx[7].col = D3DCOLOR_RGBA(g_aResult + 280, g_aResult - 240, g_aResult - 0, 0);
		//頂点バッファアンロックする
		g_pVtxBuffRESULT->Unlock();
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[8].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[9].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[10].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[11].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		//頂点バッファアンロックする
		g_pVtxBuffRESULT->Unlock();
	}
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRESULT,0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_RESULT; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureRESULT[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

