//=============================================================================
//
// クレジット処理 [credit.cpp]
// Author : ABE YUTARO
//
//=============================================================================
#include "credit.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "player.h"
#include "gamepad.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CREDIT_TEXTURENAME_LOGO_1	"data/TEXTURE/CREDIT/CREDIT000.png"			// 原案企画
#define CREDIT_TEXTURENAME_LOGO_2	"data/TEXTURE/CREDIT/CREDIT001.png"			// プログラマー
#define CREDIT_TEXTURENAME_LOGO_3	"data/TEXTURE/CREDIT/CREDIT002.png"			// プランナ
#define CREDIT_TEXTURENAME_LOGO_4	"data/TEXTURE/CREDIT/CREDIT003.png"			// UIデザイン
#define CREDIT_TEXTURENAME_LOGO_5	"data/TEXTURE/CREDIT/CREDIT004.png"			// モデル
#define CREDIT_TEXTURENAME_LOGO_6	"data/TEXTURE/CREDIT/CREDIT005.png"			// オブジェクト
#define CREDIT_TEXTURENAME_LOGO_7	"data/TEXTURE/CREDIT/CREDIT006.png"			// モーション
#define CREDIT_TEXTURENAME_LOGO_8	"data/TEXTURE/CREDIT/CREDIT007.png"			// サウンド
#define CREDIT_TEXTURENAME_LOGO_9	"data/TEXTURE/CREDIT/CREDIT008.png"			// プロジェクトリーダー
#define CREDIT_TEXTURENAME_LOGO_10	"data/TEXTURE/CREDIT/CREDIT009.png"			// 制作
#define CREDIT_TEXTURENAME_LOGO_11	"data/TEXTURE/CREDIT/CREDIT010.png"			//
#define CREDIT_TEXTURENAME_BG_1	"data/TEXTURE/CREDIT/CREDITbg002.png"			// 背景[1]
#define CREDIT_TEXTURENAME_BG_2	"data/TEXTURE/CREDIT/CREDITbg001.png"			// 背景[2]
#define CREDIT_TEXTURENAME_BG_3	"data/TEXTURE/CREDIT/CREDITbg000.png"			// 背景[3]

// 原案企画-------------------------------------------------------------------------------1
#define CREDIT_LOGO_POS_X_A	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_A
#define CREDIT_LOGO_POS_Y_A	(SCREEN_HEIGHT +100)					// ロゴのY座標_A
#define CREDIT_LOGO_WIDTH_A	(420)									// ロゴの幅
#define CREDIT_LOGO_HEIGHT_A	(200)								// ロゴの高さ
//プログラマー----------------------------------------------------------------------------2
#define CREDIT_LOGO_POS_X_B	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_B
#define CREDIT_LOGO_POS_Y_B	(SCREEN_HEIGHT + 600 )					// ロゴのY座標_B
#define CREDIT_LOGO_WIDTH_B	(400/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_B	(450/1.5f)							// ロゴの高さ
//プランナー-------------------------------------------------------------------------------3
#define CREDIT_LOGO_POS_X_C	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_C
#define CREDIT_LOGO_POS_Y_C	(SCREEN_HEIGHT + 1100 )					// ロゴのY座標_C
#define CREDIT_LOGO_WIDTH_C	(380/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_C	(210/1.5f)							// ロゴの高さ
//UIデザイン-------------------------------------------------------------------------------4
#define CREDIT_LOGO_POS_X_D	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_D
#define CREDIT_LOGO_POS_Y_D	(SCREEN_HEIGHT + 1450 )					// ロゴのY座標_D
#define CREDIT_LOGO_WIDTH_D	(400/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_D	(330/1.5f)							// ロゴの高さ
//モデル----------------------------------------------------------------------------------5
#define CREDIT_LOGO_POS_X_E	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_E
#define CREDIT_LOGO_POS_Y_E	(SCREEN_HEIGHT + 1800 )					// ロゴのY座標_E
#define CREDIT_LOGO_WIDTH_E	(400/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_E	(200/1.5f)							// ロゴの高さ
//オブジェクト----------------------------------------------------------------------------6
#define CREDIT_LOGO_POS_X_F	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_F
#define CREDIT_LOGO_POS_Y_F	(SCREEN_HEIGHT + 2100 )					// ロゴのY座標_F
#define CREDIT_LOGO_WIDTH_F	(400/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_F	(300/1.5f)							// ロゴの高さ
//モーション------------------------------------------------------------------------------7
#define CREDIT_LOGO_POS_X_G	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_G
#define CREDIT_LOGO_POS_Y_G	(SCREEN_HEIGHT + 2300 )					// ロゴのY座標_G
#define CREDIT_LOGO_WIDTH_G	(400/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_G	(200/1.5f)							// ロゴの高さ
//サウンド--------------------------------------------------------------------------------8
#define CREDIT_LOGO_POS_X_H	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_H
#define CREDIT_LOGO_POS_Y_H	(SCREEN_HEIGHT + 2700 )					// ロゴのY座標_H
#define CREDIT_LOGO_WIDTH_H	(450/1.4f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_H	(600)								// ロゴの高さ
//CV-----------------------------------------------------------------------------------10
#define CREDIT_LOGO_POS_X_K	((SCREEN_WIDTH/2)+300 )						// ロゴのX座標_J
#define CREDIT_LOGO_POS_Y_K	(SCREEN_HEIGHT + 3400 )					// ロゴのY座標_J
#define CREDIT_LOGO_WIDTH_K	(400)									// ロゴの幅
#define CREDIT_LOGO_HEIGHT_K	(600)								// ロゴの高さ
//プロジェクトリーダー-------------------------------------------------------------------9
#define CREDIT_LOGO_POS_X_I	((SCREEN_WIDTH/2) + 300)				// ロゴのX座標_I
#define CREDIT_LOGO_POS_Y_I	(SCREEN_HEIGHT + 3950 )					// ロゴのY座標_I
#define CREDIT_LOGO_WIDTH_I	(400/1.2f)								// ロゴの幅
#define CREDIT_LOGO_HEIGHT_I	(220/1.5f)							// ロゴの高さ
//制作-----------------------------------------------------------------------------------10
#define CREDIT_LOGO_POS_X_J	((SCREEN_WIDTH/2) )						// ロゴのX座標_J
#define CREDIT_LOGO_POS_Y_J	(SCREEN_HEIGHT + 4200 )					// ロゴのY座標_J
#define CREDIT_LOGO_WIDTH_J	(500)									// ロゴの幅
#define CREDIT_LOGO_HEIGHT_J	(200)								// ロゴの高さ
//背景[1]-----------------------------------------------------------------------------------1
#define CREDIT_BG_POS_X_A	((SCREEN_WIDTH/2/2)+50)					// ロゴのX座標_J
#define CREDIT_BG_POS_Y_A	((SCREEN_HEIGHT/2/2)+50 )				// ロゴのY座標_J
#define CREDIT_BG_WIDTH_A	(700)									// ロゴの幅
#define CREDIT_BG_HEIGHT_A	(400)									// ロゴの高さ
//背景[2]-----------------------------------------------------------------------------------2
#define CREDIT_BG_POS_X_B	((SCREEN_WIDTH/2/2)+50)					// ロゴのX座標_J
#define CREDIT_BG_POS_Y_B	((SCREEN_HEIGHT/2/2)+50 )				// ロゴのY座標_J
#define CREDIT_BG_WIDTH_B	(700)									// ロゴの幅
#define CREDIT_BG_HEIGHT_B	(400)									// ロゴの高さ
//背景[3]-----------------------------------------------------------------------------------3
#define CREDIT_BG_POS_X_C	((SCREEN_WIDTH/2/2)+50)					// ロゴのX座標_J
#define CREDIT_BG_POS_Y_C	((SCREEN_HEIGHT/2/2)+50 )				// ロゴのY座標_J
#define CREDIT_BG_WIDTH_C	(700)									// ロゴの幅
#define CREDIT_BG_HEIGHT_C	(400)									// ロゴの高さ
//ロゴ動き
#define CREDIT_MOVE_NOMAL	(2.0f)									// ロゴの動き
#define CREDIT_MOVE_ACCELERATA	(5.0f)								// ロゴの加速
//BGの数
#define CREDIT_BG_MAX (3)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// テクスチャの種類
	CREDITTEX_LOGO_A = 0,			// ロゴ[原案企画]
	CREDITTEX_LOGO_B,				// ロゴ[プログラマー]
	CREDITTEX_LOGO_C,				// ロゴ[演出]
	CREDITTEX_LOGO_D,				// ロゴ[マップ]
	CREDITTEX_LOGO_E,				// ロゴ[モデル]
	CREDITTEX_LOGO_F,				// ロゴ[オブジェクト]
	CREDITTEX_LOGO_G,				// ロゴ[モーション]
	CREDITTEX_LOGO_H,				// ロゴ[サウンド]
	CREDITTEX_LOGO_K,				// ロゴ[CV]
	CREDITTEX_LOGO_I,				// ロゴ[プロジェクトリーダー]
	CREDITTEX_LOGO_J,				// ロゴ[制作]
	CREDITTEX_BG_A,					//背景[1]
	CREDITTEX_BG_B,					//背景[2]
	CREDITTEX_BG_C,					//背景[2]
	CREDITTEX_MAX					// テクスチャの総数
} CREDITTEX;

typedef struct
{// タイトルの情報
	D3DXVECTOR3 pos;				// 位置
	float fWidth;					// 幅
	float fHeight;					// 高さ
	bool bDraw;						// 描画するかどうか
} CREDIT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexCredit(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureCREDIT[CREDITTEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffCREDIT = NULL;					// 頂点バッファへのポインタ
CREDIT					g_aCredit[CREDITTEX_MAX];					// タイトルの情報[ロゴ]
int						g_nCntFpsCREDIT;							// 経過時間
int						g_nLogoStopCREDIT;							// 経過時間

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 文字ロゴ情報初期化
	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		switch (nCntTex)
		{
		case CREDITTEX_LOGO_A://原案企画
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_A, CREDIT_LOGO_POS_Y_A, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_A;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_A;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_B://プログラマー
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_B, CREDIT_LOGO_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_C://演出
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_C, CREDIT_LOGO_POS_Y_C, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_C;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_C;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_D://マップ
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_D, CREDIT_LOGO_POS_Y_D, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_D;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_D;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_E://モデル
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_E, CREDIT_LOGO_POS_Y_E, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_E;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_E;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_F://オブジェクト
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_F, CREDIT_LOGO_POS_Y_F, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_F;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_F;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_G://モーション
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_G, CREDIT_LOGO_POS_Y_G, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_G;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_G;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_H://サウンド
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_H, CREDIT_LOGO_POS_Y_H, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_H;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_H;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_K:	//	背景2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_K, CREDIT_LOGO_POS_Y_K, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_K;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_K;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_I://プロジェクトリーダー]
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_I, CREDIT_LOGO_POS_Y_I, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_I;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_I;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_J://	制作
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_J, CREDIT_LOGO_POS_Y_J, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_J;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_J;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_BG_A:	//	背景1
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_A, CREDIT_BG_POS_Y_A, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_A;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_A;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_BG_B:	//	背景2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_B, CREDIT_BG_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = false;
			break;
		case CREDITTEX_BG_C:	//	背景2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_B, CREDIT_BG_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = false;
			break;

		}
	}
	//変数の初期化
	g_nCntFpsCREDIT = 0;
	g_nLogoStopCREDIT = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_1, &g_apTextureCREDIT[CREDITTEX_LOGO_A]);//原案企画
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_2, &g_apTextureCREDIT[CREDITTEX_LOGO_B]);//プログラマー
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_3, &g_apTextureCREDIT[CREDITTEX_LOGO_C]);//演出
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_4, &g_apTextureCREDIT[CREDITTEX_LOGO_D]);//マップ
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_5, &g_apTextureCREDIT[CREDITTEX_LOGO_E]);//モデル
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_6, &g_apTextureCREDIT[CREDITTEX_LOGO_F]);//オブジェクト
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_7, &g_apTextureCREDIT[CREDITTEX_LOGO_G]);//モーション
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_8, &g_apTextureCREDIT[CREDITTEX_LOGO_H]);//サウンド
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_9, &g_apTextureCREDIT[CREDITTEX_LOGO_I]);//プロジェクトリーダー]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_10, &g_apTextureCREDIT[CREDITTEX_LOGO_J]);//制作
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_11, &g_apTextureCREDIT[CREDITTEX_LOGO_K]);//CV
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_1, &g_apTextureCREDIT[CREDITTEX_BG_A]);		//背景[1]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_2, &g_apTextureCREDIT[CREDITTEX_BG_B]);		//背景[2]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_3, &g_apTextureCREDIT[CREDITTEX_BG_C]);		//背景[3]

																											// 頂点情報の作成
	MakeVertexCredit(pDevice);
	// カメラの初期化処理
	InitCamera();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitCredit(void)
{
	// 各種オブジェクトの終了処理
	UninitCamera();

	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		if (g_apTextureCREDIT[nCntTex] != NULL)
		{
			g_apTextureCREDIT[nCntTex]->Release();
			g_apTextureCREDIT[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffCREDIT != NULL)
	{
		g_pVtxBuffCREDIT->Release();
		g_pVtxBuffCREDIT = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateCredit(void)
{
	FADE pFade = GetFade(); // フェードの取得
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCREDIT->Lock(0, 0, (void**)&pVtx, 0);

	if (pFade != FADE_OUT)
	{
		for (int nCntTex = 0; nCntTex < CREDITTEX_MAX - CREDIT_BG_MAX; nCntTex++, pVtx += 4)
		{
			if (GetKeyboardPress(DIK_RETURN) == true
				|| GetGamePadPress((int)PLAYER_CONTROL_1P, ELECOM_A) == true
				|| GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true
				|| GetGamePadPress((int)PLAYER_CONTROL_2P, ELECOM_A) == true
				|| GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)

			{//エンターで加速
				g_aCredit[nCntTex].pos.y -= CREDIT_MOVE_ACCELERATA;
			}
			else
			{
				g_aCredit[nCntTex].pos.y -= CREDIT_MOVE_NOMAL;
			}
			if (g_aCredit[nCntTex].pos.y <= -400)
			{	//Y-100で消す
				g_aCredit[nCntTex].bDraw = false;
			}
			if (g_aCredit[CREDITTEX_LOGO_J].pos.y <= SCREEN_HEIGHT / 2)
			{//最後の制作は真ん中で止める
				g_aCredit[CREDITTEX_LOGO_J].pos.y = SCREEN_HEIGHT / 2;
				g_nLogoStopCREDIT++;
				if (g_nLogoStopCREDIT >= 1200 && g_aCredit[CREDITTEX_LOGO_J].pos.y == SCREEN_HEIGHT / 2)
				{
					SetFade(MODE_SELECT);
				}
			}

			if (g_aCredit[CREDITTEX_LOGO_A].bDraw == false)		//企画がFALSEになったら
			{
				g_aCredit[CREDITTEX_BG_A].bDraw = false;			//背景[1]をFALSEにする
				if (g_aCredit[CREDITTEX_BG_A].bDraw == false)		//背景[1]をFALSEになったら
				{
					g_aCredit[CREDITTEX_BG_B].bDraw = true;		//背景[2]をTRUEにする
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_C].bDraw == false)		//企画がFALSEになったら
			{
				g_aCredit[CREDITTEX_BG_B].bDraw = false;
				if (g_aCredit[CREDITTEX_BG_B].bDraw == false)
				{
					g_aCredit[CREDITTEX_BG_C].bDraw = true;
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_F].bDraw == false)		//サウンドがFALSEになったら
			{
				g_aCredit[CREDITTEX_BG_C].bDraw = false;			//背景[3をFALSE]
				if (g_aCredit[CREDITTEX_BG_C].bDraw == false)
				{
					g_aCredit[CREDITTEX_BG_C].bDraw = true;
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_K].bDraw == false)		//サウンドがFALSEになったら
			{
				g_aCredit[CREDITTEX_BG_C].bDraw = false;
			}
			if (GetKeyboardPress(DIK_BACKSPACE) == true
				 || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true
				 || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START) == true)
			{
				SetFade(MODE_SELECT);
			}

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		}

		// 頂点バッファをアンロックする
		g_pVtxBuffCREDIT->Unlock();
	}
}


//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCREDIT, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		if (g_aCredit[nCntTex].bDraw == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureCREDIT[nCntTex]);

			// ポリゴンの描画// プリミティブの種類// 開始する頂点のインデックス// 描画するプリミティブの数
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexCredit(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CREDITTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffCREDIT
		, NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffCREDIT->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++, pVtx += 4)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCREDIT->Unlock();
}
