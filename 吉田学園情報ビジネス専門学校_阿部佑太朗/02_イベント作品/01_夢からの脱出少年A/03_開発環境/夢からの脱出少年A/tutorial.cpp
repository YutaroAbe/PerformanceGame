//=============================================================================
//
// チュートリアル処理 [Tutorial.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "Tutorial.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Tutorial_TEXTURENAME1	"data/TEXTURE/TUTORIAL/Tutorial.png"	// 読み込むテクスチャの名前１
#define Tutorial_TEXTURENAME2	"data/TEXTURE/TUTORIAL/Tutorial.jpg"	// 読み込むテクスチャの名前２
#define Tutorial_TEXTURENAME3	"data/TEXTURE/TUTORIAL/PressAnyBotton000.png"		// 読み込むテクスチャの名前３
#define Tutorial_LOGO_POS_X		(140.0f)							// ロゴのX座標
#define Tutorial_LOGO_POS_Y		(35.0f)								// ロゴのY座標
#define Tutorial_LOGO_WIDTH		(280.0f)							// ロゴの幅
#define Tutorial_LOGO_HEIGHT	(70.0f)								// ロゴの高さ
#define Tutorial_ENTER_POS_X	(SCREEN_WIDTH  - 180.0f)			// エンターのX座標
#define Tutorial_ENTER_POS_Y	(SCREEN_HEIGHT - 70.0f)				// エンターのY座標
#define Tutorial_ENTER_WIDTH	(300.0f)							// エンターの幅
#define Tutorial_ENTER_HEIGHT	(90.0f)								// エンターの高さ
#define Tutorial_FLASH_ENTER	(60)								// エンターの点滅間隔

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	TutorialTEX_BG = 0,	// 背景
	TutorialTEX_ENTER,	// エンター
	TutorialTEX_MAX		// テクスチャの総数
} TutorialTEX;

typedef struct
{
	int nCntFps;		// 経過時間
	bool bPush;			// 押されたかどうか
} Tutorial;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TutorialTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
Tutorial g_Tutorial;
bool g_bDrawTutorial[TutorialTEX_MAX];	// 描画するかどうか

//=============================================================================
// チュートリアル初期化処理
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスを取得する
	pDevice = GetDevice();

	// 設定の初期化
	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++)
	{
		g_bDrawTutorial[nCntTex] = true;
		if (nCntTex == TutorialTEX_ENTER)
		{// エンターの場合
			g_bDrawTutorial[nCntTex] = false;
		}
	}
	g_Tutorial.nCntFps = 0;
	g_Tutorial.bPush = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME1, &g_apTextureTutorial[TutorialTEX_BG]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME3, &g_apTextureTutorial[TutorialTEX_ENTER]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TutorialTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTutorial
		, NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++, pVtx += 4)
	{
		// 頂点座標の設定
		if (nCntTex == TutorialTEX_BG)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}

		else if (nCntTex == TutorialTEX_ENTER)
		{
			pVtx[0].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X - Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y - Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X + Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y - Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X - Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y + Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X + Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y + Tutorial_ENTER_HEIGHT / 2, 0.0f);
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		if (nCntTex == TutorialTEX_ENTER)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();


}

//=============================================================================
// チュートリアル終了処理
//=============================================================================
void UninitTutorial(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++)
	{
		if (g_apTextureTutorial[nCntTex] != NULL)
		{
			g_apTextureTutorial[nCntTex]->Release();
			g_apTextureTutorial[nCntTex] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}

//=============================================================================
// チュートリアル更新処理
//=============================================================================
void UpdateTutorial(void)
{
	FADE pFade = *GetFade(); // フェードの取得


	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true)
	{// 決定キー(ENTERキー)が押された場合
		if (pFade == FADE_NONE)
		{// フェードが何もしていない状態の場合
			PlaySound(SOUND_LABEL_SE000);
			g_Tutorial.bPush = true;
			SetFade(MODE_SELCT);
		}
	}


	g_Tutorial.nCntFps++;
	if (g_Tutorial.bPush == true)
	{// 決定キー(ENTERキー)が押された場合
		if (g_Tutorial.nCntFps % 2 == 0)
		{
			g_bDrawTutorial[TutorialTEX_ENTER] = g_bDrawTutorial[TutorialTEX_ENTER] ? false : true;
		}
	}
	else
	{// 決定キー(ENTERキー)が押されていない場合
		if (g_Tutorial.nCntFps % Tutorial_FLASH_ENTER == 0)
		{// １秒経過した場合
			g_bDrawTutorial[TutorialTEX_ENTER] = g_bDrawTutorial[TutorialTEX_ENTER] ? false : true;
		}
	}
}

//=============================================================================
// チュートリアル描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_bDrawTutorial[nCntTex] == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTutorial[nCntTex]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// プリミティブの種類
				, nCntTex * 4		// 開始する頂点のインデックス
				, 2);				// 描画するプリミティブの数
		}
	}
}
