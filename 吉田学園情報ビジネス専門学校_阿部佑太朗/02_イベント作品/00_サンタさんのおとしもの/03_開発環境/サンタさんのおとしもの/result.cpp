//=============================================================================
//
//	リザルト処理 [result.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define RESULT_TEXTURENAMRE "data/TEXTURE/Result.jpg"				//読み込むテクスチャ
#define RESULT_TEXTURENAMRE1 "data/TEXTURE/メリークリスマス.png"   //読み込むテクスチャ
#define RESULT_TEXTURENAMRE2 "data/TEXTURE/PRESSENTER.png"			 //読み込むテクスチャ
#define MAX_RESULT (3)
#define RESULT_WIDTH   (SCREEN_WIDTH)			 //背景の幅
#define RESULT_HEIGHT   (SCREEN_HEIGHT)			 //背景の高さ


//*****************************************************************************
//グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRESULT[MAX_RESULT] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRESULT = NULL;			//頂点バッファのポイント
D3DXVECTOR3 g_posResult[2];
int g_aRPress;										//リザルトプレイヤー
RESULTSTATE g_RState;
D3DXVECTOR2 g_RS;
int nCounterRS;
//=============================================================================
//初期化処理リザルト
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	g_posResult[0] = D3DXVECTOR3(640, 150, 0.0f);
	g_posResult[1] = D3DXVECTOR3(1000, 600, 0.0f);
	g_aRPress = 0;
	g_RState = RESULT_NOMAL;
	g_RS = D3DXVECTOR2(0.0f, 0.0f);
	nCounterRS = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE, &g_pTextureRESULT[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE1, &g_pTextureRESULT[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE2, &g_pTextureRESULT[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRESULT,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		     //右上
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, 0, 0.0f);//右下
	pVtx[2].pos = D3DXVECTOR3(0, RESULT_HEIGHT, 0.0f);				         //左上
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);		     //左下
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
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffRESULT->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//タイトル
	//ポジション
	pVtx[4].pos = D3DXVECTOR3(g_posResult[0].x - 600, g_posResult[0].y - 200, 0.0f);		 //右上
	pVtx[5].pos = D3DXVECTOR3(g_posResult[0].x + 600, g_posResult[0].y - 200, 0.0f);		 //右下
	pVtx[6].pos = D3DXVECTOR3(g_posResult[0].x - 600, g_posResult[0].y +200, 0.0f);		 //左上
	pVtx[7].pos = D3DXVECTOR3(g_posResult[0].x + 600, g_posResult[0].y + 200, 0.0f);		 //左下
																							 //RHW
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//カラー
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
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
	pVtx[8].pos = D3DXVECTOR3(g_posResult[1].x - 200, g_posResult[1].y - 50, 0.0f);		      //右上
	pVtx[9].pos = D3DXVECTOR3(g_posResult[1].x + 200, g_posResult[1].y - 50, 0.0f);	         //右下
	pVtx[10].pos = D3DXVECTOR3(g_posResult[1].x - 200, g_posResult[1].y + 50, 0.0f);		 //左上
	pVtx[11].pos = D3DXVECTOR3(g_posResult[1].x + 200, g_posResult[1].y + 50, 0.0f);		 //左下
																							 //RHW
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;
	//カラー
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffRESULT->Unlock();
}
//=============================================================================
//終了処理リザルト
//=============================================================================
void UninitResult(void)
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
//更新処理リザルト
//=============================================================================
void UpdateResult(void)
{
	g_aRPress++;
	nCounterRS++;

	if (g_aRPress >= 60)
	{
		g_aRPress = 0;
	}

	//エンターでモードエンターに移行
	FADE pFade;
	pFade = *GetFade();
	if (nCounterRS >= 300)
	{
		if (pFade == FADE_NONE)
		{
				//PlaySound(SOUND_LABEL_SE_DECIDE);
				//モード設定
				SetFade(MODE_RANK);
				g_RState = RESULT_END;
			}
	}
	
	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_RANK);
			g_RState = RESULT_END;
		}
	}

	//switch (g_RState)
	//{
	//case RESULT_NOMAL:
	//		//頂点バッファをロックし、頂点データへのポインタ
	//		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//		pVtx[8].col = D3DCOLOR_RGBA(g_aRPress * 2, 0, 0, g_aRPress * 2);
	//		pVtx[9].col = D3DCOLOR_RGBA(g_aRPress * 2, 0, 0, g_aRPress * 2);
	//		pVtx[10].col = D3DCOLOR_RGBA(g_aRPress * 2, 0, 0, g_aRPress * 2);
	//		pVtx[11].col = D3DCOLOR_RGBA(g_aRPress * 2, 0, 0, g_aRPress * 2);

	//		//頂点バッファアンロックする
	//		g_pVtxBuffRESULT->Unlock();
	//	break;
	//case RESULT_END:
	//		//頂点バッファをロックし、頂点データへのポインタ
	//		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//		pVtx[8].col = D3DCOLOR_RGBA(g_aRPress * 120, 0, 0, g_aRPress * 120);
	//		pVtx[9].col = D3DCOLOR_RGBA(g_aRPress * 120, 0, 0, g_aRPress * 120);
	//		pVtx[10].col = D3DCOLOR_RGBA(g_aRPress * 120, 0, 0, g_aRPress * 120);
	//		pVtx[11].col = D3DCOLOR_RGBA(g_aRPress * 120, 0, 0, g_aRPress * 120);

	//		//頂点バッファアンロックする
	//		g_pVtxBuffRESULT->Unlock();
	//	break;
	//}
	
}
//=============================================================================
//描画処理リザルト
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRESULT, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_RESULT-2; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureRESULT[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_RState)
	{
	case RESULT_NOMAL:
		if (g_aRPress >= 50 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureRESULT[1]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		if (g_aRPress >= 30 == 0)
		{
			
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureRESULT[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	case RESULT_END:
		if (g_aRPress % 12 == 0)
		{
			// テェクスチャの設定
				pDevice->SetTexture(0, g_pTextureRESULT[1]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		}
		if (g_aRPress % 6 == 0)
		{
			
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureRESULT[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}
}