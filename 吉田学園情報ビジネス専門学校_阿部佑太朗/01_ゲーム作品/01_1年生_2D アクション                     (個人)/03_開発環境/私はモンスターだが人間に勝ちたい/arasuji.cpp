//=============================================================================
//
// タイトル処理 [Arasuji.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "arasuji.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define Arasuji_TEXTURENAMRE "data/TEXTURE/Arasuji.png"				//	読み込むテクスチャ
#define Arasuji_TEXTURENAMRE2 "data/TEXTURE/Skip000.png"			//	読み込むテクスチャ
#define Arasuji_TEXTURENAMRE3 "data/TEXTURE/Arasuji000.png"			//	読み込むテクスチャ
#define MAX_Arasuji_TEX (3)
#define BG_WIDTH   (SCREEN_WIDTH)									//	背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)									//	背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureArasuji[MAX_Arasuji_TEX] = {};			//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArasuji = NULL;					//頂点バッファのポイント
D3DXVECTOR3 g_PosArasuji;
D3DXVECTOR3 g_ARAPressEnter;
int g_aAPress;														//タイトルプレスエンター
ARASUJISTATE g_TState;
D3DXVECTOR2 g_AS[2];
int g_aArasujiEND;
//=============================================================================
//初期化処理タイトル
//=============================================================================
void InitArasuji(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	//初期値設定
	g_PosArasuji = D3DXVECTOR3(600, 680, 0.0f);     //タイトル
	g_ARAPressEnter = D3DXVECTOR3(1000, 690, 0.0f);//プレスエンター
	g_aAPress = 0;
	g_aArasujiEND = 0;
	g_AS[0] = D3DXVECTOR2(0.0f, 0.0f);
	g_AS[1] = D3DXVECTOR2(0.0f, 0.0f);
	g_TState = ARASUJI_NOMAL;
	//g_aArasujiEND = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE3, &g_pTextureArasuji[0]);//背景
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE, &g_pTextureArasuji[1]);//プレスエンター
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE2, &g_pTextureArasuji[2]);//タイトル

																				 //頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Arasuji_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArasuji, //頂点バッファのポイント
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(0 + 100, 0+50, 0.0f);		             //右上
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH - 100, 0 + 50, 0.0f);              //右下
	pVtx[2].pos = D3DXVECTOR3(0 + 100, BG_HEIGHT - 100, 0.0f);				 //左上
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH - 100, BG_HEIGHT - 100, 0.0f);		 //左下
																 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);				//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);				//左下

														//頂点バッファアンロックする
	g_pVtxBuffArasuji->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_PosArasuji.x - 600, g_PosArasuji.y - 80, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_PosArasuji.x + 600, g_PosArasuji.y - 80, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_PosArasuji.x - 600, g_PosArasuji.y + 80, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_PosArasuji.x + 600, g_PosArasuji.y + 80, 0.0f);		 //
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファアンロックする
	g_pVtxBuffArasuji->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 8;	//頂点ポインタを4つ進める

				//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_ARAPressEnter.x - 100, g_ARAPressEnter.y - 30, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_ARAPressEnter.x + 100, g_ARAPressEnter.y - 30, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_ARAPressEnter.x - 100, g_ARAPressEnter.y + 30, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_ARAPressEnter.x + 100, g_ARAPressEnter.y + 30, 0.0f);		 //左下
																							 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファアンロックする
	g_pVtxBuffArasuji->Unlock();
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitArasuji(void)
{
	//テクスチャの破棄[2]
	for (int nCount = 0; nCount < MAX_Arasuji_TEX; nCount++)
	{

		if (g_pTextureArasuji[nCount] != NULL)
		{
			g_pTextureArasuji[nCount]->Release();
			g_pTextureArasuji[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffArasuji != NULL)
	{
		g_pVtxBuffArasuji->Release();
		g_pVtxBuffArasuji = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateArasuji(void)
{
	g_aAPress++;
	g_AS[0].y -= 0.0002f;
	g_AS[1].x += 0.003f;
	g_aArasujiEND++;
	FADE pFade;
	pFade = *GetFade();
	if (g_aArasujiEND >= 2100)
	{//放置してたらタイトル画面へ

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_SELECT);
		}
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - g_AS[0].y);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - g_AS[0].y);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f - g_AS[0].y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f - g_AS[0].y);
	pVtx += 4;
	pVtx[0].tex = D3DXVECTOR2(g_AS[1].x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_AS[1].x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_AS[1].x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_AS[1].x, 1.0f);

	//頂点バッファアンロックする
	g_pVtxBuffArasuji->Unlock();
	if (g_aAPress >= 60)
	{
		g_aAPress = 0;
	}

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_TState = ARASUJI_END;
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_SELECT);
		}
	}

}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawArasuji(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffArasuji, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_Arasuji_TEX - 1; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureArasuji[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_TState)
	{
	case ARASUJI_NOMAL:
		if (g_aAPress >= 30 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureArasuji[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	case ARASUJI_END:
		if (g_aAPress % 6 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureArasuji[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}
}