//=============================================================================
//
// タイトル処理 [title.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define TITLE_TEXTURENAMRE "data/TEXTURE/title.png" //読み込むテクスチャ
#define TITLE_TEXTURENAMRE2 "data/TEXTURE/title000.png" //読み込むテクスチャ
#define TITLE_TEXTURENAMRE3 "data/TEXTURE/title002.png" //読み込むテクスチャ
#define MAX_TITLE_TEX (3)
#define BG_WIDTH   (SCREEN_WIDTH)//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)//背景の高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTITLE[MAX_TITLE_TEX] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;  //頂点バッファのポイント
D3DXVECTOR3 g_PosTitle;
D3DXVECTOR3 g_PosPressEnter;
int g_aTPress;												//タイトルプレスエンター
TITLESTATE g_TState;
int g_aTitleCounter;
//=============================================================================
//初期化処理タイトル
//=============================================================================
void InitTitle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	//初期値設定
	g_PosTitle = D3DXVECTOR3(1280 / 2, 290, 0.0f);     //タイトル
	g_PosPressEnter = D3DXVECTOR3(600, 640, 0.0f);//プレスエンター
	g_aTPress = 0;
	g_aTitleCounter = 0;
	g_TState = TITLE_NOMAL;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE, &g_pTextureTITLE[0]);//背景
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE2, &g_pTextureTITLE[1]);//プレスエンター
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE3, &g_pTextureTITLE[2]);//タイトル

																				 //頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE, //頂点バッファのポイント
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		             //右上
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);              //右下
	pVtx[2].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);				 //左上
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);		 //左下
																 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				 //右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下

														//頂点バッファアンロックする
	g_pVtxBuffTITLE->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y - 210, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y - 210, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y + 210, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y + 210, 0.0f);		 //左下
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
	g_pVtxBuffTITLE->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 8;	//頂点ポインタを4つ進める

				//ポジション
	pVtx[0].pos = D3DXVECTOR3(g_PosPressEnter.x - 100, g_PosPressEnter.y - 30, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(g_PosPressEnter.x + 100, g_PosPressEnter.y - 30, 0.0f);		 //右下
	pVtx[2].pos = D3DXVECTOR3(g_PosPressEnter.x - 100, g_PosPressEnter.y + 30, 0.0f);		 //左上
	pVtx[3].pos = D3DXVECTOR3(g_PosPressEnter.x + 100, g_PosPressEnter.y + 30, 0.0f);		 //左下
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
	g_pVtxBuffTITLE->Unlock();
}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitTitle(void)
{
	//テクスチャの破棄[2]
	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{

		if (g_pTextureTITLE[nCount] != NULL)
		{
			g_pTextureTITLE[nCount]->Release();
			g_pTextureTITLE[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTITLE != NULL)
	{
		g_pVtxBuffTITLE->Release();
		g_pVtxBuffTITLE = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateTitle(void)
{
	g_aTPress++;
	g_aTitleCounter++;
	if (g_aTPress >= 60)
	{
		g_aTPress = 0;
	}
	//エンターでモードエンターに移行
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_TState = TITLE_END;
			//モード設定
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_SELECTMODE);
		}
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
													//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファアンロックする
	g_pVtxBuffTITLE->Unlock();

}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TITLE_TEX - 1; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureTITLE[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_TState)
	{
	case TITLE_NOMAL:
		if (g_aTPress >= 30 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureTITLE[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	case TITLE_END:
		if (g_aTPress % 6 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureTITLE[2]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}



}