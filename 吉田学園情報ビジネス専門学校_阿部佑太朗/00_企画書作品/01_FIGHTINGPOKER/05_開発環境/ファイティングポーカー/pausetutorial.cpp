//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ポーズチュートリアル処理 [pausetutorial.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "main.h"
#include "pausetutorial.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_PAUSETUTORIAL				(4)							// ポーズチュートリアルの最大数
#define MAX_PAUSETUTORIALPAGE			(3)							// ポーズチュートリアルのスライドの枚数
#define PAUSETUTORIALPAGE_PATTERN_ANIM	float(1.0f / float(MAX_PAUSETUTORIALPAGE))	// ページの加算数
#define PAUSETUTORIAL_DISP_NORMAL		(30)						// 通常時の点滅の間隔
#define PAUSETUTORIAL_DISP_FAST			(2)							// 決定時の点滅の間隔
#define SLIDE_TIME					(20)							// スクロールスピード

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	PAUSETUTORIAL_TEX_MAIN = 0,		// メイン画像
	PAUSETUTORIAL_TEX_ARROWW_RIGHT,	// 矢印右
	PAUSETUTORIAL_TEX_ARROWW_LEFT,	// 矢印左
	PAUSETUTORIAL_TEX_MAX,			// 総数
}PauseTutorialTexName;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	PAUSETUTORIALTYPE type;	// 種類
	D3DXCOLOR	col;		// 色
	int nTexType;			// テクスチャの種類
	float fWidth;			// 横幅
	float fHeight;			// 縦幅
	int nMoveCounter;		// 様々な動きのカウンター
	int nDispSpeed;			// 点滅のスピード
	bool bDisp;				// 表示
	bool bUse;				// 使用しているかどうか
}PauseTutorial;

typedef struct
{
	char *pFilename;	// ファイル名
} PauseTutorialTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexPauseTutorial(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9 g_pTexturePauseTutorial[PAUSETUTORIAL_TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseTutorial = NULL;				// 頂点バッファへのポインタ
PauseTutorial g_aPauseTutorial[MAX_PAUSETUTORIAL];								// ポーズチュートリアルの情報

// 読み込むテクスチャ名の設定
PauseTutorialTexInfo g_apTexturePauseTutorialInfo[PAUSETUTORIAL_TEX_MAX] =
{
	{ "data//TEXTURE//pausetutorial.png" },		// メイン画像
	{ "data//TEXTURE//arrowRight.png" },		// 矢印右
	{ "data//TEXTURE//arrowLeft.png" },			// 矢印左
};

int g_nCntPagePause;			// 現在のページ数をカウント
int g_nSlideFrameCntPause;		// スライド時間のカウンター
bool g_bSlideUsePause;			// スライド中かどうか
float g_fSlideTexAnimPause;		// スライドのテクスチャの現在の値
float g_fSlideTexAnimAddPause;	// スライドのテクスチャの増加値
int g_nDispCounterPause;			// 点滅のカウンター

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズチュートリアル初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPauseTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ポーズチュートリアルの情報の初期化
	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		g_aPauseTutorial[nCntPauseTutorial].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPauseTutorial[nCntPauseTutorial].type = PAUSETUTORIALTYPE_MAIN;
		g_aPauseTutorial[nCntPauseTutorial].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPauseTutorial[nCntPauseTutorial].nTexType = PAUSETUTORIAL_TEX_MAIN;
		g_aPauseTutorial[nCntPauseTutorial].nDispSpeed = PAUSETUTORIAL_DISP_NORMAL;
		g_aPauseTutorial[nCntPauseTutorial].fWidth = 0;
		g_aPauseTutorial[nCntPauseTutorial].fHeight = 0;
		g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
		g_aPauseTutorial[nCntPauseTutorial].bUse = false;
	}

	g_nCntPagePause = 0;
	g_nSlideFrameCntPause = 0;
	g_bSlideUsePause = false;
	g_fSlideTexAnimPause = 0.0f;
	g_fSlideTexAnimAddPause = 0.0f;
	g_nDispCounterPause = 0;

	// テクスチャの読み込み
	for (int nCntPauseTutorialTex = 0; nCntPauseTutorialTex < PAUSETUTORIAL_TEX_MAX; nCntPauseTutorialTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePauseTutorialInfo[nCntPauseTutorialTex].pFilename,
			&g_pTexturePauseTutorial[nCntPauseTutorialTex]);
	}

	// 頂点情報
	MakeVertexPauseTutorial(pDevice);

	SetPauseTutorial(D3DXVECTOR3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_MAIN,(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	// 矢印
	SetPauseTutorial(D3DXVECTOR3(float(SCREEN_WIDTH - 40.0f), float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_ARROW_RIGHT, 70.0f, 200.0f);
	SetPauseTutorial(D3DXVECTOR3(40.0f, float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_ARROW_LEFT, 70.0f, 200.0f);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズチュートリアル終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPauseTutorial(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PAUSETUTORIAL_TEX_MAX; nCntTex++)
	{
		if (g_pTexturePauseTutorial[nCntTex] != NULL)
		{
			g_pTexturePauseTutorial[nCntTex]->Release();
			g_pTexturePauseTutorial[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffPauseTutorial != NULL)
	{
		g_pVtxBuffPauseTutorial->Release();
		g_pVtxBuffPauseTutorial = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズチュートリアル更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePauseTutorial(void)
{
	FADE pFade;
	// フェードモードの取得
	pFade = GetFade();
	g_nSlideFrameCntPause++;
	g_nDispCounterPause++;

	//if (g_bSlideUsePause == false)
	//{ // スライド中で無い場合

	//	if ((GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_D) == true || GetGamePadTrigger(ELECOM_RB) == true
	//		|| GetGamePadPovPress(POV_RIGHT) == true || GetGamePadStickTrigger(STICK_RIGHT) == true) && g_nCntPagePause != MAX_PAUSETUTORIALPAGE-1)
	//	{ // ページが最大値でない場合
	//		// ページを進める
	//		g_nCntPagePause++;
	//		g_bSlideUsePause = true;
	//		g_nSlideFrameCntPause = 0;
	//		g_fSlideTexAnimAddPause = float(PAUSETUTORIALPAGE_PATTERN_ANIM / SLIDE_TIME);

	//	}
	//	else if ((GetKeyboardTrigger(DIK_LEFT) == true || GetKeyboardTrigger(DIK_A) == true || GetGamePadTrigger(ELECOM_LB) == true
	//		|| GetGamePadPovPress(POV_LEFT) == true || GetGamePadStickTrigger(STICK_LEFT) == true) && g_nCntPagePause != 0)
	//	{ // ページが最小値でない場合
	//		// ページ戻す
	//		g_nCntPagePause--;
	//		g_bSlideUsePause = true;
	//		g_nSlideFrameCntPause = 0;
	//		g_fSlideTexAnimAddPause = float(-PAUSETUTORIALPAGE_PATTERN_ANIM / SLIDE_TIME);

	//	}

	//}

	// スライドのテクスチャの値に増加値を加算
	g_fSlideTexAnimPause += g_fSlideTexAnimAddPause;

	if (g_nSlideFrameCntPause == SLIDE_TIME && g_bSlideUsePause == true)
	{ // スライド中でフレームカウンターが規定値に達した場合
		g_nSlideFrameCntPause = 0;
		g_bSlideUsePause = false;
		g_fSlideTexAnimAddPause = 0.0f;
		g_fSlideTexAnimPause = g_nCntPagePause * PAUSETUTORIALPAGE_PATTERN_ANIM;
	}

	VERTEX_2D *pVtx;		// 頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == true)
		{
			if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_MAIN)
			{ // スライド
				pVtx[0].tex = D3DXVECTOR2(g_fSlideTexAnimPause, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_fSlideTexAnimPause + PAUSETUTORIALPAGE_PATTERN_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_fSlideTexAnimPause, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_fSlideTexAnimPause + PAUSETUTORIALPAGE_PATTERN_ANIM, 1.0f);
			}
			else if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_ARROW_RIGHT)
			{ // 右矢印
				if (g_nCntPagePause != MAX_PAUSETUTORIALPAGE - 1 && g_bSlideUsePause == false)
				{
					if (g_nDispCounterPause % g_aPauseTutorial[nCntPauseTutorial].nDispSpeed == 0)
					{
						g_aPauseTutorial[nCntPauseTutorial].bDisp = g_aPauseTutorial[nCntPauseTutorial].bDisp ? false : true;
					}
				}
				else
				{
					g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
				}
			}
			else if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_ARROW_LEFT)
			{ // 左矢印
				if (g_nCntPagePause != 0 && g_bSlideUsePause == false)
				{
					if (g_nDispCounterPause % g_aPauseTutorial[nCntPauseTutorial].nDispSpeed == 0)
					{
						g_aPauseTutorial[nCntPauseTutorial].bDisp = g_aPauseTutorial[nCntPauseTutorial].bDisp ? false : true;
					}
				}
				else
				{
					g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
				}
			}
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPauseTutorial->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズチュートリアル描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPauseTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseTutorial, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == true)
		{ // ポーズチュートリアルが使用されている
			if (g_aPauseTutorial[nCntPauseTutorial].bDisp == true)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTexturePauseTutorial[g_aPauseTutorial[nCntPauseTutorial].nTexType]);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseTutorial * 4, 2);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// PauseTutorialの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseTutorial(D3DXVECTOR3 pos, D3DXCOLOR col, PAUSETUTORIALTYPE type, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;		// 頂点情報へのポインタ
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++,pVtx+=4)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == false)
		{ // タイトルが使用されていない場合
		  // 頂点位置の設定
			g_aPauseTutorial[nCntPauseTutorial].pos = pos;
			g_aPauseTutorial[nCntPauseTutorial].fWidth = fWidth;
			g_aPauseTutorial[nCntPauseTutorial].fHeight = fHeight;
			// 色の設定
			g_aPauseTutorial[nCntPauseTutorial].col = col;
			// ポーズチュートリアルの種類の設定
			g_aPauseTutorial[nCntPauseTutorial].type = type;
			g_aPauseTutorial[nCntPauseTutorial].nTexType = type;

			 // 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x - g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y - g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x + g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y - g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x - g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y + g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x + g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y + g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);

			pVtx[0].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[1].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[2].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[3].col = g_aPauseTutorial[nCntPauseTutorial].col;

			if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_MAIN)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(PAUSETUTORIALPAGE_PATTERN_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(PAUSETUTORIALPAGE_PATTERN_ANIM, 1.0f);
			}

			g_aPauseTutorial[nCntPauseTutorial].bDisp = true;	// 表示状態にする
			g_aPauseTutorial[nCntPauseTutorial].bUse = true;	// 使用する状態にする
			break;	// このbreakはかなり大切
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffPauseTutorial->Unlock();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexPauseTutorial(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSETUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseTutorial,
		NULL);

	VERTEX_2D *pVtx;		// 頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++, pVtx += 4)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseTutorial->Unlock();

}