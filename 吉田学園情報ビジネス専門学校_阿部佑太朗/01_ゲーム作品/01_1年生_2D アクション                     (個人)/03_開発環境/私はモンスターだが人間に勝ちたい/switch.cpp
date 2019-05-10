//=============================================================================
//
// ブロックの処理 [Switch.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "switch.h"
#include "main.h"
#include "player.h"	
#include "input.h"
#include "sound.h"
#include "item.h"
#include "yajirusi.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Switch_TEXTURENAMRE0 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE1 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE2 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE3 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE4 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE5 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE6 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE7 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE8 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE9 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE10 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE11 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE12 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE13 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE14 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE15 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE16 "data/TEXTURE/Switti001.png"
#define	MAX_SWITCH		(126)					// ブロックの最大数
#define POS_X (150)								//ポジション_X
#define POS_Y (25)								//ポジション_Y
#define TEX_MAX (17)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSwitch[TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSwitch = NULL;	// 頂点バッファへのポインタ
Switch g_aSwitch[MAX_SWITCH];						//ブロックの情報
bool g_BreakSwitch;
bool g_SwitchSwitti;

//=============================================================================
// 初期化処理
//=============================================================================
void InitSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		g_aSwitch[nCntSwitch].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCntSwitch].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCntSwitch].nType = 0;
		g_aSwitch[nCntSwitch].fWindth = 0;		//幅
		g_aSwitch[nCntSwitch].fHeight = 0;		//高さ
		g_aSwitch[nCntSwitch].bUse = false;
	}
	g_SwitchSwitti = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE0, &g_pTextureSwitch[0]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE1, &g_pTextureSwitch[1]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE2, &g_pTextureSwitch[2]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE3, &g_pTextureSwitch[3]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE4, &g_pTextureSwitch[4]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE5, &g_pTextureSwitch[5]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE6, &g_pTextureSwitch[6]);//使用済みSWITCH
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE4, &g_pTextureSwitch[7]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE5, &g_pTextureSwitch[8]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE9, &g_pTextureSwitch[9]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE10, &g_pTextureSwitch[10]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE11, &g_pTextureSwitch[11]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE12, &g_pTextureSwitch[12]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE13, &g_pTextureSwitch[13]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE14, &g_pTextureSwitch[14]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE15, &g_pTextureSwitch[15]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE16, &g_pTextureSwitch[16]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWITCH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSwitch,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);													//左上
		pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);						//右上
		pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);						//左上
		pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//右下
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
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSwitch->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSwitch(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャの開放
		if (g_pTextureSwitch[nCount] != NULL)
		{
			g_pTextureSwitch[nCount]->Release();
			g_pTextureSwitch[nCount] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffSwitch != NULL)
	{
		g_pVtxBuffSwitch->Release();
		g_pVtxBuffSwitch = NULL;
	}
}
//=============================================================================
// 更新処理 
//=============================================================================
void UpdateSwitch(void)
{
	PLAYER *pPlyer;
	pPlyer = GetPlayer();
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == true)	//ブロックが使用されてru
		{
			g_aSwitch[nCntSwitch].pos.x -= pPlyer->move.x;

			g_aSwitch[nCntSwitch].pos.x += g_aSwitch[nCntSwitch].move.x;
			g_aSwitch[nCntSwitch].pos.y += g_aSwitch[nCntSwitch].move.y;

			
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);													//左上
			pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);						//右上
			pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);						//左上
			pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//右下
			pVtx += 4;	//頂点ポインタを4つ進める	
		}
	}
	//頂点バッファアンロックする
	g_pVtxBuffSwitch->Unlock();
	
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffSwitch, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSwitch[g_aSwitch[nCntSwitch].nType]);
			// ポリゴンの描画
			if (g_aSwitch[nCntSwitch].bUse == true)//ブロックが使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntSwitch, 2);
			}
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == false)	//ブロックが使用されていない
		{
			g_aSwitch[nCntSwitch].pos = pos;
			g_aSwitch[nCntSwitch].fHeight = fHeight;
			g_aSwitch[nCntSwitch].fWindth = fWindth;
			g_aSwitch[nCntSwitch].nType = nType;
			g_aSwitch[nCntSwitch].bUse = true;//ブロックが使用されている
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);//左上
			pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);//右上
			pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//左上
			pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//右下
			
			break;
		}
		pVtx += 4;			//該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffSwitch->Unlock();
}
//=============================================================================
//ブロックとプレイヤーとの判定処理
//=============================================================================
void CollisionSwitch(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 bool bLand = false;	//着地したかどうか
	 Item *pItem;
	 pItem = Getitem();

	 for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	 {
		 if (g_aSwitch[nCntSwitch].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aSwitch[nCntSwitch].pos.x  &&									//プレイヤーが右からめり込んでるとき
				 pPos->x - (*fWindth / 2) <= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth &&		//プレイヤーが左からめり込んでるとき
				 pPos->y >= g_aSwitch[nCntSwitch].pos.y &&															//プレイヤーが上から下にめり込んでるとき
				 pPos->y - *fHeight <= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight)					//プレイヤーが下から上にめり込んでるとき
			 {//YXが範囲内
				 if (pPosOld->y <= g_aSwitch[nCntSwitch].pos.y && pPos->y >= g_aSwitch[nCntSwitch].pos.y)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
				 {//ブロック上判定
					 bLand = true;
					 pPos->y = g_aSwitch[nCntSwitch].pos.y;														//プレイヤーをブロックのポジションYに出現させる
					 pMove->y = 0.0f;
				 }
				 else if (pPosOld->y - *fHeight >= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight &&	//プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
					 pPos->y - *fHeight <= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight)				//現在の位置がめり込んでるとき
				 {//ブロック下判定
					 //bLand = true;
					 pPos->y = g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight + *fHeight;				//プレイヤーをブロック中心+ブロックの高さ+プレイヤーの高さの位置に出現させる
					 pMove->y = 0.0f;
				 }
				 else if (pPosOld->x + *fWindth >= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth &&	//昔の位置がブロックより右にあって現在の位置がめり込んでる場合
					 pPos->x - *fWindth <= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth)
				 {//ブロック右判定
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 //タイプ14------------------------
					 if (g_aSwitch[nCntSwitch].nType == 0)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 1;
						 }

					 }
					 if (g_aSwitch[nCntSwitch].nType == 15)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 16;
						 }
					 }
				 }
				 else if (pPosOld->x - *fWindth <= g_aSwitch[nCntSwitch].pos.x &&									//昔の位置がブロックより左にあって現在の位置がめり込んでる場合
					 pPos->x + *fWindth >= g_aSwitch[nCntSwitch].pos.x)
				 {//ブロック左判定
					 pPos->x = pPosOld->x;																		//昔の位置に出現させる
					 pMove->x = 0.0f;
					 if (g_aSwitch[nCntSwitch].nType == 2)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 3;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 4)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 5;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 7)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 8;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 9)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 10;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 11)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 12;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 13)
					 {//スイッチOFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 14;
						 }
					 }
					 
				 }
				 if (g_aSwitch[nCntSwitch].nType == 1)
				 {//スイッチON
					 SetBlock(D3DXVECTOR3(1300, 580.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 70.0f, 5);
					
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 3)
				 {//スイッチON
					 for (int nCut = 0; nCut < 8; nCut++)
					 {//階段
						 SetBlock(D3DXVECTOR3(900 + (nCut * 50.0f), 580 - (nCut * 20.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					// SetBlock(D3DXVECTOR3(1600.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 20.0f, 1);
					 //SWITCH
					// SetSwitch(D3DXVECTOR3(1670.0f, 260.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 4);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 5)
				 {//スイッチON
					 for (int nCut = 0; nCut < 4; nCut++)
					 {//階段
						 SetBlock(D3DXVECTOR3(460.0f - (nCut * 50.0f), 325 - (nCut * 20.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 8)	//チュートリアルでしよう
				 {//スイッチON
					 //ノーマルブロック
						 SetBlock(D3DXVECTOR3(800.0f, 585, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1);
						 //はてな
						// SetBlock(D3DXVECTOR3(850, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 12);
						 ////上に取ったらfalse
						// SetBlock(D3DXVECTOR3(900, 500, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 10.0f, 4);
						 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 10)	
				 {//スイッチON
				  //ノーマルブロック
					 SetBlock(D3DXVECTOR3(800.0f, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 20.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 12)	
				 {//スイッチON
					 SetBlock(D3DXVECTOR3(700.0f, 220, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 20.0f, 3);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 14)
				 {//スイッチON
					 SetYajirusi(1, D3DXVECTOR3(100, 150.0f, 0));
					 SetYajirusi(0, D3DXVECTOR3(-90, 150.0f, 0));
					 SetBlock(D3DXVECTOR3(-110, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 30.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 14)
				 {//スイッチON
					 SetYajirusi(1, D3DXVECTOR3(100, 150.0f, 0));
					 SetYajirusi(0, D3DXVECTOR3(-90, 150.0f, 0));
					 SetBlock(D3DXVECTOR3(-110, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 30.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 16)
				 {//スイッチON
					 for (int nCut = 0; nCut < 10; nCut++)
					 {//階段
						 SetBlock(D3DXVECTOR3(1500.0f + (nCut * 50.0f), 585 - (nCut * 30.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 
			 }
		 }
	 }
}
			
//=============================================================================
// 敵の取得
//=============================================================================
Switch *GetSwitch(void)
{
	return &g_aSwitch[0];
}
