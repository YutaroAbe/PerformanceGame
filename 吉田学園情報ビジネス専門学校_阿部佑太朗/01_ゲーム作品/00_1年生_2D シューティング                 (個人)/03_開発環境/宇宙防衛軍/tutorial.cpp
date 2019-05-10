//=============================================================================
//
// チュートリアル処理 [title.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "bg.h"
#include "tutorial.h"
#include "bullet.h"
#include"sound.h"
#include "effect.h"
#include "explosion.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define TUTORIAL_TEXTURENAMRE "data/TEXTURE/Key/KeyW.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE1 "data/TEXTURE/Key/KeyA.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE2 "data/TEXTURE/Key/KeyS.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE3 "data/TEXTURE/Key/KeyD.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE4 "data/TEXTURE/Key/KeyP.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE5 "data/TEXTURE/Key/KeySPACE.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE6 "data/TEXTURE/Key/KeySHIFT.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE7 "data/TEXTURE/Key/Key001.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE8 "data/TEXTURE/Key/Key002.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE9 "data/TEXTURE/Key/Key003.png" //読み込むテクスチャ
#define TUTORIAL_TEXTURENAMRE10 "data/TEXTURE/title002.png" //読み込むテクスチャ
#define TUTORIAL_POS_X  (0)　　　//背景の左上X座標
#define TUTORIAL_POS_Y  (0)　　　//背景の左上Y座標
#define TUTORIAL_WIDTH   (SCREEN_WIDTH)//背景の幅
#define TUTORIAL_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define TUTORIAL_MAX (11)	//テクスチャの最大数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTUTORIAL[TUTORIAL_MAX] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTORIAL = NULL;  //頂点バッファのポイント
D3DXVECTOR3 g_posTUTO[TUTORIAL_MAX];
D3DXCOLOR g_colTUTO[TUTORIAL_MAX];
int g_aCount2; //カウント2
int g_aCount3; //カウント3

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitTUTORIAL(void)
{
	//初期化処理バックグラウンド
	InitBG();
	//初期化処理バレット
	InitBullet();
	//初期化処理プレイヤー
	InitPlayer();
	//初期化処理エフェクト
	InitEffect();
	//初期化処理エクスプロージョン
	InitExplosion();

	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE, &g_pTextureTUTORIAL[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE1, &g_pTextureTUTORIAL[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE2, &g_pTextureTUTORIAL[2]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE3, &g_pTextureTUTORIAL[3]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE4, &g_pTextureTUTORIAL[4]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE5, &g_pTextureTUTORIAL[5]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE6, &g_pTextureTUTORIAL[6]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE7, &g_pTextureTUTORIAL[7]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE8, &g_pTextureTUTORIAL[8]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE9, &g_pTextureTUTORIAL[9]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE10, &g_pTextureTUTORIAL[10]);

	//ポジション
	g_posTUTO[0] = D3DXVECTOR3(600, 40, 0);//W
	g_posTUTO[1] = D3DXVECTOR3(500, 100, 0);//A
	g_posTUTO[2] = D3DXVECTOR3(600, 100, 0);//S
	g_posTUTO[3] = D3DXVECTOR3(700, 100, 0);//D
	g_posTUTO[4] = D3DXVECTOR3(200, 100, 0);//P
	g_posTUTO[5] = D3DXVECTOR3(300, 100, 0);//スペース
	g_posTUTO[6] = D3DXVECTOR3(400, 100, 0);//シフト
	g_posTUTO[7] = D3DXVECTOR3(600, 600, 0);//
	g_posTUTO[8] = D3DXVECTOR3(300, 600, 0);//1
	g_posTUTO[9] = D3DXVECTOR3(700, 600, 0);//2
	g_posTUTO[10] = D3DXVECTOR3(1100, 100, 0);//プレスエンター

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* TUTORIAL_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTUTORIAL,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < TUTORIAL_MAX - 1; nCount++)
	{
		//頂点座標設定
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_posTUTO[nCount].x - 50, g_posTUTO[nCount].y - 30, 0.0f);		 //右上
		pVtx[1].pos = D3DXVECTOR3(g_posTUTO[nCount].x + 50, g_posTUTO[nCount].y - 30, 0.0f);		 //右下
		pVtx[2].pos = D3DXVECTOR3(g_posTUTO[nCount].x - 50, g_posTUTO[nCount].y + 30, 0.0f);		 //左上
		pVtx[3].pos = D3DXVECTOR3(g_posTUTO[nCount].x + 50, g_posTUTO[nCount].y + 30, 0.0f);		 //左下
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);								//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);								//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);								//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//ポジション
	pVtx[28].pos = D3DXVECTOR3(g_posTUTO[7].x - 800, g_posTUTO[7].y - 200, 0.0f);		 //右上
	pVtx[29].pos = D3DXVECTOR3(g_posTUTO[7].x + 800, g_posTUTO[7].y - 200, 0.0f);		 //右下
	pVtx[30].pos = D3DXVECTOR3(g_posTUTO[7].x - 800, g_posTUTO[7].y + 200, 0.0f);		 //左上
	pVtx[31].pos = D3DXVECTOR3(g_posTUTO[7].x + 800, g_posTUTO[7].y + 200, 0.0f);		 //左下
	 //RHW
	pVtx[28].rhw = 1.0f;
	pVtx[29].rhw = 1.0f;
	pVtx[30].rhw = 1.0f;
	pVtx[31].rhw = 1.0f;
	//カラー
	pVtx[28].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[29].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[30].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[31].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);								//右上
	pVtx[29].tex = D3DXVECTOR2(1.0f, 0.0f);								//右下
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);								//左上
	pVtx[31].tex = D3DXVECTOR2(1.0f, 1.0f);								//左下

	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//ポジション
	pVtx[32].pos = D3DXVECTOR3(g_posTUTO[8].x - 200, g_posTUTO[8].y - 100, 0.0f);		 //右上
	pVtx[33].pos = D3DXVECTOR3(g_posTUTO[8].x + 200, g_posTUTO[8].y - 100, 0.0f);		 //右下
	pVtx[34].pos = D3DXVECTOR3(g_posTUTO[8].x - 200, g_posTUTO[8].y + 100, 0.0f);		 //左上
	pVtx[35].pos = D3DXVECTOR3(g_posTUTO[8].x + 200, g_posTUTO[8].y + 100, 0.0f);		 //左下
																						 //RHW
	pVtx[32].rhw = 1.0f;
	pVtx[33].rhw = 1.0f;
	pVtx[34].rhw = 1.0f;
	pVtx[35].rhw = 1.0f;
	//カラー
	pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標
	pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);								//右上
	pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);								//右下
	pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);								//左上
	pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);								//左下

	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//ポジション
	pVtx[36].pos = D3DXVECTOR3(g_posTUTO[9].x - 200, g_posTUTO[9].y - 100, 0.0f);		 //右上
	pVtx[37].pos = D3DXVECTOR3(g_posTUTO[9].x + 200, g_posTUTO[9].y - 100, 0.0f);		 //右下
	pVtx[38].pos = D3DXVECTOR3(g_posTUTO[9].x - 200, g_posTUTO[9].y + 100, 0.0f);		 //左上
	pVtx[39].pos = D3DXVECTOR3(g_posTUTO[9].x + 200, g_posTUTO[9].y + 100, 0.0f);		 //左下
																						 //RHW
	pVtx[36].rhw = 1.0f;
	pVtx[37].rhw = 1.0f;
	pVtx[38].rhw = 1.0f;
	pVtx[39].rhw = 1.0f;
	//カラー
	pVtx[36].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[37].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[38].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[39].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標
	pVtx[36].tex = D3DXVECTOR2(0.0f, 0.0f);								//右上
	pVtx[37].tex = D3DXVECTOR2(1.0f, 0.0f);								//右下
	pVtx[38].tex = D3DXVECTOR2(0.0f, 1.0f);								//左上
	pVtx[39].tex = D3DXVECTOR2(1.0f, 1.0f);								//左下

	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//ポジション
	pVtx[40].pos = D3DXVECTOR3(g_posTUTO[10].x - 100, g_posTUTO[10].y - 30, 0.0f);		 //右上
	pVtx[41].pos = D3DXVECTOR3(g_posTUTO[10].x + 100, g_posTUTO[10].y - 30, 0.0f);		 //右下
	pVtx[42].pos = D3DXVECTOR3(g_posTUTO[10].x - 100, g_posTUTO[10].y + 30, 0.0f);		 //左上
	pVtx[43].pos = D3DXVECTOR3(g_posTUTO[10].x + 100, g_posTUTO[10].y + 30, 0.0f);		 //左下
																						 //RHW
	pVtx[40].rhw = 1.0f;
	pVtx[41].rhw = 1.0f;
	pVtx[42].rhw = 1.0f;
	pVtx[43].rhw = 1.0f;
	//カラー
	pVtx[40].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[41].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[42].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[43].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ座標
	pVtx[40].tex = D3DXVECTOR2(0.0f, 0.0f);								//右上
	pVtx[41].tex = D3DXVECTOR2(1.0f, 0.0f);								//右下
	pVtx[42].tex = D3DXVECTOR2(0.0f, 1.0f);								//左上
	pVtx[43].tex = D3DXVECTOR2(1.0f, 1.0f);								//左下

	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	g_aCount2 = 0;

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitTUTORIAL(void)
{
	// 終了処理バックグラウンド
	UninitBG();
	//終了処理バレット
	UninitBullet();
	// 終了処理プレイヤー
	UninitPlayer();
	//終了処理エフェクト
	UninitEffect();
	// 終了処理エクスプロージョン
	UninitExplosion();

	for (int nCount = 0; nCount < TUTORIAL_MAX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureTUTORIAL[nCount] != NULL)
		{
			g_pTextureTUTORIAL[nCount]->Release();
			g_pTextureTUTORIAL[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTUTORIAL != NULL)
	{
		g_pVtxBuffTUTORIAL->Release();
		g_pVtxBuffTUTORIAL = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateTUTORIAL(void)
{
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	// 更新処理バックグラウンド
	UpdateBG();
	// 更新処理バレット
	UpdateBullet();
	// 更新処理プレイヤー
	UpdatePlayer();
	//更新処理エフェクト
	UpdateEffect();
	// 更新処理エクスプロージョン
	UpdateExplosion();
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
	g_aCount2++;
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//プレスエンターカラー
	pVtx[40].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[41].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[42].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[43].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	//頂点バッファアンロックする
	g_pVtxBuffTUTORIAL->Unlock();

	//ボタン点滅----------------------------------------------------------------------------------
	//キーボードW
	if (GetKeyboardTrigger(DIK_W) == true)//----Wボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーW
		pVtx[0].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[1].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[2].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[3].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_W) == false)//----Wボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	//キーボードA
	if (GetKeyboardPress(DIK_A) == true)//----Aボタンボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーA
		pVtx[4].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[5].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[6].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[7].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_A) == false)//----Aボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[4].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[5].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[6].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[7].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	//キーボードS
	if (GetKeyboardPress(DIK_S) == true)//----Sボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーS
		pVtx[8].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[9].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[10].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[11].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_S) == false)//----Sボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーS
		pVtx[8].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[9].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[10].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[11].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_D) == true)//----Dボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーD
		pVtx[12].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[13].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[14].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[15].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_D) == false)//----Dボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラーD
		pVtx[12].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[13].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[14].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[15].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_P) == true)//----Pボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[16].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[17].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[18].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[19].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_P) == false)//----Pボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[16].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[17].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[18].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[19].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_SPACE) == true)//----SPACEボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[20].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[21].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[22].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[23].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_SPACE) == false)//----SPACEボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[20].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[21].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[22].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[23].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_LSHIFT) == true)//----SHIFTボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[24].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[25].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[26].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[27].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_LSHIFT) == false)//----SHIFTボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[24].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[25].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[26].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[27].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffTUTORIAL->Unlock();
	}
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawTUTORIAL(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTUTORIAL, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
		for (int nCount = 0; nCount < TUTORIAL_MAX; nCount++)
		{  //テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureTUTORIAL[nCount]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	//描画処理バックグラウンド
	DrawBG();
	//描画処理バレット
	DrawBullet();
	//描画処理プレイヤー
	DrawPlayer();
	//描画処理エフェクト
	DrawEffect();
	// 描画処理エクスプロージョン
	DrawExplosion();
}

