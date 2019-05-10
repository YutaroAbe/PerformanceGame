//=============================================================================
//
// セレクト画面処理 [Selectmode.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "Selectmode.h"
#include "fade.h"
#include "enemy.h"
#include "bg.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE1 "data/TEXTURE/GameSel000.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE2 "data/TEXTURE/GameSel001.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE3 "data/TEXTURE/GameSel002.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE4 "data/TEXTURE/GameSel003.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE5 "data/TEXTURE/Key/KeyW.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE6 "data/TEXTURE/Key/KeyS.png" //読み込むテクスチャ
#define BG_TEXTURENAMRE7  "data/TEXTURE/title002.png" //読み込むテクスチャ
#define SEL_WIDTH   (SCREEN_WIDTH)//背景の幅
#define SEL_HEIGHT   (SCREEN_HEIGHT)//背景の高さ
#define MAX_SEL (8)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelectmode[MAX_SEL] = {};		//テクスチャポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectmode = NULL;  //頂点バッファのポイント
D3DXVECTOR2 g_Selectmode[MAX_SEL];
int g_aSelectMenu;
int g_aPress;
int g_aCountSel;
SELECTSTATE g_aSelstate;

//=============================================================================
//初期化処理ポリゴン
//=============================================================================
void InitSelectmode(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();

	//初期化処理バックグラウンド
	InitBG();

	g_aPress = 0;
	g_aSelstate = SELECT_NOMAL;
	g_aCountSel = 0;

	g_Selectmode[0] = D3DXVECTOR2(200, 200);//メインゲーム
	g_Selectmode[1] = D3DXVECTOR2(400, 550);
	g_Selectmode[2] = D3DXVECTOR2(700, 200);
	g_Selectmode[3] = D3DXVECTOR2(1000, 550);//終了
	g_Selectmode[4] = D3DXVECTOR2(1000, 550);
	g_Selectmode[5] = D3DXVECTOR2(1100, 40);
	g_Selectmode[6] = D3DXVECTOR2(1100, 170);
	g_Selectmode[7] = D3DXVECTOR2(1100, 100);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureSelectmode[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTextureSelectmode[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTextureSelectmode[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTextureSelectmode[3]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE4, &g_pTextureSelectmode[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE5, &g_pTextureSelectmode[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE6, &g_pTextureSelectmode[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE7, &g_pTextureSelectmode[7]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4* MAX_SEL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectmode,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(SEL_WIDTH, 0, 0.0f);//右下
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

	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//頂点座標設定
		//頂点設定
		pVtx[4].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 150.0f, g_Selectmode[nCount].y - 150.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 150.0f, g_Selectmode[nCount].y - 150.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 150.0f, g_Selectmode[nCount].y + 150.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 150.0f, g_Selectmode[nCount].y + 150.0f, 0.0f);
		//RHW
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;
		//カラー
		pVtx[4].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[5].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[6].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[7].col = D3DCOLOR_RGBA(90, 90, 90, 90);

		//テクスチャ座標
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 5; nCount < 7; nCount++)
	{
		//頂点座標設定
		//頂点設定
		pVtx[20].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[21].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[22].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		pVtx[23].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		//RHW
		pVtx[20].rhw = 1.0f;
		pVtx[21].rhw = 1.0f;
		pVtx[22].rhw = 1.0f;
		pVtx[23].rhw = 1.0f;
		//カラー
		pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標
		pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
		pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
		pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
		pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標設定
	//頂点設定
	pVtx[28].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[29].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[30].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
	pVtx[31].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
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
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);				//右上
	pVtx[29].tex = D3DXVECTOR2(1.0f, 0.0f);				//右下
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
	pVtx[31].tex = D3DXVECTOR2(1.0f, 1.0f);				//左下
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();



	g_aSelectMenu = 0;

}
//=============================================================================
//終了処理更新処理ポリゴン
//=============================================================================
void UninitSelectmode(void)
{
	//終了処理バックグラウンド
	UninitBG();

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
	//エンターでモードエンターに移行
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//キーボード設定
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//エンターでセレクト画面へ
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{//エンター押したらセレクトエンドへ
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_aSelstate = SELECT_END;
			}
		}
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//更新処理バックグラウンド
	UpdateBG();


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
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			switch (g_aSelectMenu)
			{
			case  0://ゲームモードへ
				SetFade(MODE_GAME);
				break;
			case 1://チュートリアルへ
				SetFade(MODE_TUTORIAL);
				break;
			case 2://スコアへ
				SetFade(MODE_RANKING);
				break;
			case 3://終了
				g_aSelstate = SELECT_QUIT;
				break;
			}
		}
	}
	g_aCountSel++;
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//プレスエンターカラー
	pVtx[28].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[29].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[30].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[31].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx += 4;	//頂点ポインタを4つ進める
					//カラー
		pVtx[0].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[1].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[2].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[3].col = D3DCOLOR_RGBA(90, 90, 90, 90);
	}
	//頂点バッファアンロックする
	g_pVtxBuffSelectmode->Unlock();

	switch (g_aSelstate)
	{
	case SELECT_NOMAL://通常
		///選択したモードの色を戻す
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		if (GetKeyboardTrigger(DIK_RETURN) == false)
		{
			pVtx += 4 * (g_aSelectMenu + 1);
			//カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
		break;

	case SELECT_END://選択を点滅
		g_aPress++;
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * (g_aSelectMenu + 1);
		pVtx[0].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[1].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[2].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[3].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);

		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
		break;
	}


	if (GetKeyboardTrigger(DIK_W) == true)//----Wボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラーW
		pVtx[20].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[21].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[22].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[23].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardPress(DIK_W) == false)//----Wボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[20].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[21].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[22].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[23].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == true)//----Wボタン押してる場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラーW
		pVtx[24].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[25].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[26].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[27].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardPress(DIK_S) == false)//----Wボタン押していない場合
	{
		//頂点バッファをロックし、頂点データへのポインタ
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//カラー
		pVtx[24].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[25].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[26].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[27].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//頂点バッファアンロックする
		g_pVtxBuffSelectmode->Unlock();
	}
}
//=============================================================================
//描画処理ポリゴン
//=============================================================================
void DrawSelectmode(void)
{
	//描画処理バックグラウンド
	DrawBG();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	//デバイス取得
	pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSelectmode, 0, sizeof(VERTEX_2D));
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_SEL; nCount++)
	{
		//テェクスチャの設定
		pDevice->SetTexture(0, g_pTextureSelectmode[nCount]);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//=============================================================================
//セレクト終了
//=============================================================================
SELECTSTATE GetSelstate(void)
{
	return g_aSelstate;
}
