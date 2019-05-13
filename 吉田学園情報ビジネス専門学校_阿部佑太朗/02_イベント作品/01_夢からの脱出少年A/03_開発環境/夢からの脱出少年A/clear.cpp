//=============================================================================
//
// クレジット処理 [Clear.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "clear.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Clear_TEXTURENAME1	"data/TEXTURE/CLEAR/Clear.png"	// 読み込むテクスチャの名前１
#define Clear_TEXTURENAME2	"data/TEXTURE/CLEAR/Clear.jpg"	// 読み込むテクスチャの名前２
#define Clear_TEXTURENAME3	"data/TEXTURE/CLEAR/PressAnyBotton000.png"		// 読み込むテクスチャの名前３
#define Clear_LOGO_POS_X		(140.0f)							// ロゴのX座標
#define Clear_LOGO_POS_Y		(35.0f)								// ロゴのY座標
#define Clear_LOGO_WIDTH		(280.0f)							// ロゴの幅
#define Clear_LOGO_HEIGHT	(70.0f)								// ロゴの高さ
#define Clear_ENTER_POS_X	(SCREEN_WIDTH /2)			// エンターのX座標
#define Clear_ENTER_POS_Y	(SCREEN_HEIGHT /2 +230)				// エンターのY座標
#define Clear_ENTER_WIDTH	(300.0f)							// エンターの幅
#define Clear_ENTER_HEIGHT	(90.0f)								// エンターの高さ
#define Clear_FLASH_ENTER	(60)								// エンターの点滅間隔

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	ClearTEX_BG = 0,	// 背景
	ClearTEX_ENTER,	// エンター
	ClearTEX_MAX		// テクスチャの総数
} ClearTEX;

typedef struct
{
	int nCntFps;		// 経過時間
	bool bPush;			// 押されたかどうか
} Clear;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureClear[ClearTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;
Clear g_Clear;
bool g_bDrawClear[ClearTEX_MAX];	// 描画するかどうか

//=============================================================================
// クリア初期化処理
//=============================================================================
void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスを取得する
	pDevice = GetDevice();

	// 設定の初期化
	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++)
	{
		g_bDrawClear[nCntTex] = true;
		if (nCntTex == ClearTEX_ENTER)
		{// エンターの場合
			g_bDrawClear[nCntTex] = false;
		}
	}
	g_Clear.nCntFps = 0;
	g_Clear.bPush = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME1, &g_apTextureClear[ClearTEX_BG]);
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME3, &g_apTextureClear[ClearTEX_ENTER]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ClearTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffClear
		, NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++, pVtx += 4)
	{
		// 頂点座標の設定
		if (nCntTex == ClearTEX_BG)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}

		else if (nCntTex == ClearTEX_ENTER)
		{
			pVtx[0].pos = D3DXVECTOR3(Clear_ENTER_POS_X - Clear_ENTER_WIDTH / 2-100, Clear_ENTER_POS_Y - Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Clear_ENTER_POS_X + Clear_ENTER_WIDTH / 2 + 100, Clear_ENTER_POS_Y - Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Clear_ENTER_POS_X - Clear_ENTER_WIDTH / 2 - 100, Clear_ENTER_POS_Y + Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Clear_ENTER_POS_X + Clear_ENTER_WIDTH / 2 + 100, Clear_ENTER_POS_Y + Clear_ENTER_HEIGHT / 2, 0.0f);
		}

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		if (nCntTex == ClearTEX_ENTER)
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
	g_pVtxBuffClear->Unlock();


}

//=============================================================================
// クリア終了処理
//=============================================================================
void UninitClear(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++)
	{
		if (g_apTextureClear[nCntTex] != NULL)
		{
			g_apTextureClear[nCntTex]->Release();
			g_apTextureClear[nCntTex] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}

}

//=============================================================================
// クリア更新処理
//=============================================================================
void UpdateClear(void)
{
	FADE pFade = *GetFade(); // フェードの取得


	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true)
	{// 決定キー(ENTERキー)が押された場合
		if (pFade == FADE_NONE)
		{// フェードが何もしていない状態の場合
			PlaySound(SOUND_LABEL_SE000);
			g_Clear.bPush = true;
			SetFade(MODE_SELCT);
		}
	}


	g_Clear.nCntFps++;
	if (g_Clear.bPush == true)
	{// 決定キー(ENTERキー)が押された場合
		if (g_Clear.nCntFps % 2 == 0)
		{
			g_bDrawClear[ClearTEX_ENTER] = g_bDrawClear[ClearTEX_ENTER] ? false : true;
		}
	}
	else
	{// 決定キー(ENTERキー)が押されていない場合
		if (g_Clear.nCntFps % Clear_FLASH_ENTER == 0)
		{// １秒経過した場合
			g_bDrawClear[ClearTEX_ENTER] = g_bDrawClear[ClearTEX_ENTER] ? false : true;
		}
	}
}

//=============================================================================
// クリア描画処理
//=============================================================================
void DrawClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_bDrawClear[nCntTex] == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureClear[nCntTex]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// プリミティブの種類
				, nCntTex * 4		// 開始する頂点のインデックス
				, 2);				// 描画するプリミティブの数
		}
	}
}
