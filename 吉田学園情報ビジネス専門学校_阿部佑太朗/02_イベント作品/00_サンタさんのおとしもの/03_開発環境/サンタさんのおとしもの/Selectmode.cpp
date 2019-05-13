//=============================================================================
//
// セレクト画面処理 [Selectmode.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "Selectmode.h"
#include "input.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE1 "data/TEXTURE/.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE2 "data/TEXTURE/sel0000.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE3 "data/TEXTURE/sel0001.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE4 "data/TEXTURE/sel0002.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE5 "data/TEXTURE/sel0003.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE6 "data/TEXTURE/KeyW.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE7 "data/TEXTURE/KeyS.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE8  "data/TEXTURE/Press000.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE9  "data/TEXTURE/1.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE10  "data/TEXTURE/2.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE11 "data/TEXTURE/3.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE12  "data/TEXTURE/4.png" //読み込むテクスチャ
#define SEL_WIDTH   (SCREEN_WIDTH)//背景の幅
#define SEL_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define MAX_SEL (12)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelectmode[MAX_SEL] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectmode = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_Selectmode[MAX_SEL];
int g_aSelectMenu;
SELECTSTATE g_aSelstate;
int g_PressEnter;
int g_aPress;
int g_nCounterTitle;
//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitSelectmode(void)
{
	//終了処理エネミー
	InitEnemy();
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	g_nCounterTitle = 0;
	g_aSelectMenu = 0;
	g_aSelstate = SELECT_NOMAL;
	g_PressEnter = 0;
	g_aPress = 0;

	g_Selectmode[0] = D3DXVECTOR2(920, 130);//メインゲーム
	g_Selectmode[1] = D3DXVECTOR2(920, 290);
	g_Selectmode[2] = D3DXVECTOR2(920, 450);
	g_Selectmode[3] = D3DXVECTOR2(920, 610);//終了
	g_Selectmode[4] = D3DXVECTOR2(500, 570);
	g_Selectmode[5] = D3DXVECTOR2(500, 650);
	g_Selectmode[6] = D3DXVECTOR2(0, 0);
	g_Selectmode[7] = D3DXVECTOR2(300,630);//プレスエンター

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE9, &g_pTextureSelectmode[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE10, &g_pTextureSelectmode[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE11, &g_pTextureSelectmode[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE12, &g_pTextureSelectmode[3]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTextureSelectmode[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTextureSelectmode[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE4, &g_pTextureSelectmode[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE5, &g_pTextureSelectmode[7]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE6, &g_pTextureSelectmode[8]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE7, &g_pTextureSelectmode[9]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE8, &g_pTextureSelectmode[10]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTextureSelectmode[11]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SEL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectmode,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);						 //右上
		pVtx[1].pos = D3DXVECTOR3(SEL_WIDTH, 0, 0.0f);				 //右下
		pVtx[2].pos = D3DXVECTOR3(0, SEL_HEIGHT, 0.0f);				 //左上
		pVtx[3].pos = D3DXVECTOR3(SEL_WIDTH, SEL_HEIGHT, 0.0f);		 //左下
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

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}

	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//頂点座標設定
		//頂点設定
		pVtx[16].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y - 70.0f, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y - 70.0f, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y + 70.0f, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y + 70.0f, 0.0f);
		//RHW
		pVtx[16].rhw = 1.0f;
		pVtx[17].rhw = 1.0f;
		pVtx[18].rhw = 1.0f;
		pVtx[19].rhw = 1.0f;
		//カラー
		pVtx[16].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[17].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[18].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[19].col = D3DCOLOR_RGBA(90, 90, 90, 255);

		//テクスチャ座標
		pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 4; nCount < 6; nCount++)
	{
		//頂点座標設定
		//頂点設定
		pVtx[32].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[33].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[34].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		pVtx[35].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		//RHW
		pVtx[32].rhw = 1.0f;
		pVtx[33].rhw = 1.0f;
		pVtx[34].rhw = 1.0f;
		pVtx[35].rhw = 1.0f;
		//カラー
		pVtx[32].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[33].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[34].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[35].col = D3DCOLOR_RGBA(120, 120, 120, 120);

		//テクスチャ座標
		pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//頂点設定
	pVtx[40].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[41].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[42].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
	pVtx[43].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
	//RHW
	pVtx[40].rhw = 1.0f;
	pVtx[41].rhw = 1.0f;
	pVtx[42].rhw = 1.0f;
	pVtx[43].rhw = 1.0f;
	//カラー
	pVtx[40].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[41].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[42].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[43].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	//テクスチャ座標
	pVtx[40].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
	pVtx[41].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[42].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
	pVtx[43].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();
	SetEnemy(0, D3DXVECTOR3(1200, 430, 0.0f), D3DXVECTOR3(-2, 2, 0.0f), ENEMYSTATE_NOMAL);

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitSelectmode(void)
{
	//終了処理エネミー
	UninitEnemy();
	for (int nCount = 0; nCount < MAX_SEL; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureSelectmode[nCount] != NULL)
		{
			g_pTextureSelectmode[nCount]->Release();
			g_pTextureSelectmode[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSelectmode != NULL)
	{
		g_pVtxBuffSelectmode->Release();
		g_pVtxBuffSelectmode = NULL;
	}
}
//=============================================================================
//更新処理ポリゴン
//=============================================================================
void UpdateSelectmode(void)
{
	//更新処理エネミー
	UpdateEnemy();
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	g_PressEnter++;
	g_nCounterTitle++;
	FADE pFade;
	pFade = *GetFade();
	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_W) == true)
	{
		g_nCounterTitle = 0;
		PlaySound(SOUND_LABEL_SE_PAUSESELECT);
	}
	if (g_nCounterTitle >= 600)
	{//放置してたらタイトル画面へ
		
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}
	if (g_PressEnter >= 60)
	{
		g_PressEnter = 0;
	}
		//エンターでセレクト画面へ
		if (pFade == FADE_NONE &&  GetKeyboardTrigger(DIK_RETURN) == true)
		{//エンター押したらセレクトエンドへ
			g_aSelstate = SELECT_END;
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_aSelectMenu = (g_aSelectMenu + 1) % 4;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_aSelectMenu = (g_aSelectMenu + 3) % 4;
	}

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (pFade == FADE_NONE && GetKeyboardTrigger(DIK_RETURN) == true)
		{//エンターでセレクト画面へ
			switch (g_aSelectMenu)
			{
			case  0://チュートリアルへ
				SetFade(MODE_TUTO);
				break;
			case 1://ゲームモードへ
					SetFade(MODE_GAME);
				break;
			case 2://ランキング
				SetFade(MODE_RANK);
				break;
					
			case 3://終了
				g_aSelstate = SELECT_QUIT;
				break;
			}
		/*	PlaySound(SOUND_LABEL_SE_DECIDE);*/
		}
	}
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx += 4;	//頂点ポインタを4つ進める
		//カラー
		pVtx[12].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[13].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[14].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[15].col = D3DCOLOR_RGBA(90, 90, 90, 255);
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();


	switch (g_aSelstate)
	{
	case SELECT_NOMAL://通常
		
	//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		
			pVtx += 4 * (g_aSelectMenu + 1);
			//カラー
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		
		//頂点バッファアンロックするd
		g_pVtxBuffSelectmode->Unlock();
		break;

	case SELECT_END://選択を点滅
		g_aPress++;
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * (g_aSelectMenu + 1);
		pVtx[12].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[13].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[14].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[15].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);

		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
		break;
	}

	if (GetKeyboardTrigger(DIK_W) == true)//----Wボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラーW
		pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_W) == false)//----Wボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[32].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[33].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[34].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[35].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == true)//----Wボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラーW
		pVtx[36].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[37].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[38].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[39].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == false)//----Wボタン押していない場合
	{
		
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[36].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[37].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[38].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[39].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	Enemy *pEnemy;
	pEnemy = GetEnemy();

	if (pEnemy->pos.y >= 750)
	{//エネミーの位置Yが750以上になったら
		pEnemy->move.y = 0;
		//pEnemy->nType= 0;
		if (pEnemy->move.y == 0)
		{
			pEnemy->move.y = -2;
		}
	}
	if (pEnemy->pos.x >= 1280)
	{//エネミーの位置Xが1280以上になったら
		pEnemy->move.x = 0;
		//pEnemy->nType = 1;
		if (pEnemy->move.x == 0)
		{
			pEnemy->move.x = -2;
		}
	}
	if (pEnemy->pos.y <= 0)
	{// エネミーの位置Yが0以下になったら
		pEnemy->move.y = 0;
		//pEnemy->nType = 0;
		if (pEnemy->move.y == 0)
		{
			pEnemy->move.y = 2;
		}
	}
	if (pEnemy->pos.x <= 0)
	{//エネミーの位置Xが0以下になったら
		pEnemy->move.x = 0;
		//pEnemy->nType = 1;
		if (pEnemy->move.x == 0)
		{
			pEnemy->move.x = 2;
		}
	}
	if (pEnemy->move.x <= 0.1)
	{
		pEnemy->nType = 0;
	}
	else
	{
		pEnemy->nType = 1;
	}
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawSelectmode(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelectmode, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	switch (g_aSelectMenu)
	{
	case  0://ゲームモードへ
			//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[0]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);
		break;
	case 1://チュートリアルへ
		   //テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[1]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		break;
	case 2://スコアへ
		   //テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[2]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		break;
	case 3://終了
		   //テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[3]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 3 * 4, 2);
		break;
	}
	for (int nCount = 4; nCount < 10; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_aSelstate)
	{
	case SELECT_NOMAL:
		if (g_PressEnter >= 30 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureSelectmode[10]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 10 * 4, 2);
		}
		break;
	case SELECT_END:
		if (g_PressEnter % 6 == 0)
		{
			//テェクスチャの設定
			pDevice->SetTexture(0, g_pTextureSelectmode[10]);
			//ポリゴン描
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 10 * 4, 2);
		}
		break;
	}
	
	//描画処理エネミー
	DrawEnemy();
}
//=============================================================================
//セレクト終了
//=============================================================================
SELECTSTATE GetSelstate(void)
{
	return g_aSelstate;
}
