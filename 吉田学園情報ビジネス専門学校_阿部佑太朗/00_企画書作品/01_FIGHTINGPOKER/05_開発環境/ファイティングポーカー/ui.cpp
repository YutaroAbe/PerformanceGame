//=============================================================================
//
// UI [ui.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "game.h"
#include "ui.h"
#include "cardModel.h"
#include "fade.h"
#include "PlayerShow.h"
#include "input.h"
#include "gamefade.h"
#include "sound.h"
#include "gamepad.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define LOAD_TEXT			"data/TEXT/result.txt"
#define TEX_TYPE			"data/TEXTURE/typelist.jpg"
#define TEX_GUIDE			"data/TEXTURE/guide.png"
#define TEX_1P				"data/TEXTURE/1P.png"
#define TEX_2P				"data/TEXTURE/2P.png"
#define TEX_VS				"data/TEXTURE/vs.png"
#define TEX_READY			"data/TEXTURE/ready.png"
#define TEX_RESULT			"data/TEXTURE/win_lose.png"
#define MAX_UI				(8) // 最大数
#define READY_POS			D3DXVECTOR3(300.0f, 130.0f, 0.0f)
#define READY_WIDTH			(450.0f)
#define READY_HEIGHT		(430.0f)
#define TYPELIST_POS		D3DXVECTOR3(1000.0f, 0.0f, 0.0f)
#define TYPELIST_WIDTH		(280.0f)
#define TYPELIST_HEIGHT		(720.0f)
#define OPERATION_POS		D3DXVECTOR3(0.0f, 600.0f, 0.0f)
#define OPERATION_WIDTH		(SCREEN_WIDTH - TYPELIST_WIDTH)
#define OPERATION_HEIGHT	(120.0f)
#define PLAYERVIEW_WIDTH	(150.0f)
#define PLAYERVIEW_HEIGHT	(100.0f)
#define PLAYER_1P_POS		D3DXVECTOR3(SCREEN_WIDTH / 2 - PLAYERVIEW_WIDTH * 3, 0.0f, 0.0f)
#define PLAYER_2P_POS		D3DXVECTOR3(SCREEN_WIDTH / 2 + PLAYERVIEW_WIDTH * 2, 0.0f, 0.0f)
#define VS_WIDTH			(550.0f)
#define VS_HEIGHT			(300.0f)
#define VS_POS				D3DXVECTOR3(VS_WIDTH, VS_HEIGHT, 0.0f)
#define RESULT_WIDTH		(400.0f)
#define RESULT_HEIGHT		(100.0f)
#define RESULT_POS_1		D3DXVECTOR3(100.0f, 0.0f, 0.0f)
#define RESULT_POS_2		D3DXVECTOR3(800.0f, 0.0f, 0.0f)
//=============================================================================
// UIの情報
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	float fWidth;								//幅
	float fHeight;								//高さ
	UITYPE type;								//種類
}UiInfo;
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;	// 頂点バッファのポインタ
UI g_aUi[MAX_UI];
UiInfo g_aUiInfo[];
int g_nWinner;
bool g_bUseKeyboard;
bool g_bSetReady;
bool g_bSetUi;
bool g_bAnnounce;
//=============================================================================
// UIの配置
//=============================================================================
UiInfo g_aUiInfo[] =
{
	{ READY_POS, READY_WIDTH, READY_HEIGHT, UI_READY },					// 1P・2P確認表記
	{ TYPELIST_POS, TYPELIST_WIDTH, TYPELIST_HEIGHT, UI_TYPELIST },		// 相性の図
	{ OPERATION_POS,OPERATION_WIDTH , OPERATION_HEIGHT, UI_GUIDE },		// 操作説明
	{ PLAYER_1P_POS, PLAYERVIEW_WIDTH, PLAYERVIEW_HEIGHT, UI_1P },		// 1P
	{ PLAYER_2P_POS, PLAYERVIEW_WIDTH, PLAYERVIEW_HEIGHT, UI_2P },		// 2P
	{ VS_POS, PLAYERVIEW_WIDTH, PLAYERVIEW_HEIGHT, UI_VS },				// VS
	{ RESULT_POS_1, RESULT_WIDTH, RESULT_HEIGHT, UI_RESULT },			// 勝敗
	{ RESULT_POS_2, RESULT_WIDTH, RESULT_HEIGHT, UI_RESULT },			// 勝敗
};
//=============================================================================
// 初期化処理
//=============================================================================
void InitUI(void)
{
	g_nWinner = 0;
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_UI; nCnt++)
	{
		g_aUi[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aUi[nCnt].fWidth = 0.0f;
		g_aUi[nCnt].fHeight = 0.0f;
		g_aUi[nCnt].type = UI_MAX;
		g_aUi[nCnt].bUse = false;
	}
	MakeVertexUI(pDevice);

	//位置　→　幅　→　高さ　→　種類
	for (int nCntUi = 0; nCntUi < sizeof g_aUiInfo / sizeof(UiInfo); nCntUi++)
	{
		SetUI(g_aUiInfo[nCntUi].pos, g_aUiInfo[nCntUi].fWidth, g_aUiInfo[nCntUi].fHeight, g_aUiInfo[nCntUi].type);
	}
	g_bUseKeyboard = false;
	g_bSetReady = false;
	g_bSetUi = false;
	g_bAnnounce = false;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitUI(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateUI(void)
{
	VERTEX_2D * pVtx;
	bool bSet = GetSet();
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();
	CARDSIDE side = GetPokerState();
	GAMEMODE GameMode = GetGameMode();
	int nNowPlayer = GetNowPlayer();
	if (GameMode == GAMEMODE_POKER)
	{
		if (side == CARD_SIDE_1P)
		{
			g_aUi[0].bUse = false;
			if (bSet == true && g_bSetReady == false)
			{
				g_aUi[0].bUse = true;
				g_bSetUi = true;
				// 頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				// 頂点バッファをアンロックする
				g_pVtxBuffUI->Unlock();
			}
		}
		else if (side == CARD_SIDE_2P)
		{
			if (g_bSetReady == false)
			{
				g_aUi[0].bUse = true;
				g_bSetUi = true;
				// 頂点バッファをロックし、頂点情報へのポインタを取得 
				g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				// 頂点バッファをアンロックする
				g_pVtxBuffUI->Unlock();
			}
		}
		if (g_bAnnounce == false && g_bSetUi == true)
		{
			PlaySound(SOUND_LABEL_SE_ANNOUNCE);
			g_bAnnounce = true;
		}
		g_aUi[1].bUse = true;
		g_aUi[2].bUse = true;
		g_aUi[3].bUse = false;
		g_aUi[4].bUse = false;
		g_aUi[5].bUse = false;
		g_aUi[6].bUse = false;
		g_aUi[7].bUse = false;
	}
	if (GameMode == GAMEMODE_PLAYERSHOW)
	{
		if (pGameFade == GAMEFADE_IN)
		{
			g_aUi[0].bUse = false;
			g_aUi[1].bUse = false;
			g_aUi[2].bUse = false;
			g_aUi[3].bUse = true;
			g_aUi[4].bUse = true;
			g_aUi[5].bUse = true;
			g_aUi[6].bUse = false;
			g_aUi[7].bUse = false;
		}
	}
	if (GameMode == GAMEMODE_RESULT)
	{
		WhichWinner();	// どちらが勝ったか
		if (pGameFade == GAMEFADE_IN)
		{
			g_aUi[0].bUse = false;
			g_aUi[1].bUse = false;
			g_aUi[2].bUse = false;
			g_aUi[3].bUse = false;
			g_aUi[4].bUse = false;
			g_aUi[5].bUse = false;
			g_aUi[6].bUse = true;
			g_aUi[7].bUse = true;
		}
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

		// 1Pが勝ったとき
		if (g_nWinner == 1)
		{
			pVtx += 24;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx += 4;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 2Pが勝ったとき
		if (g_nWinner == 2)
		{
			pVtx += 24;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx += 4;
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffUI->Unlock();

	}
	if (g_bSetUi == true)
	{
		if (nNowPlayer == 0)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A))
			{
				g_bSetReady = true;
				g_bSetUi = false;
				PlaySound(SOUND_LABEL_SE_CARD_OPEN);
				g_aUi[0].bUse = false;
				g_bAnnounce = false;
			}
		}
		if (nNowPlayer == 1)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A))
			{
				g_bSetReady = true;
				g_bSetUi = false;
				PlaySound(SOUND_LABEL_SE_CARD_OPEN);
				g_aUi[0].bUse = false;
				g_bAnnounce = false;
			}
		}
	}
	if (GetKeyboardTrigger(DIK_1) == true || GetKeyboardTrigger(DIK_NUMPAD1) == true)
	{
		g_bUseKeyboard = false;
	}
	if (GetKeyboardTrigger(DIK_2) == true || GetKeyboardTrigger(DIK_NUMPAD2) == true)
	{
		g_bUseKeyboard = true;
	}
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 8;
	if (g_bUseKeyboard == false)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	}
	else if (g_bUseKeyboard == true)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawUI(void)
{
	MODE Mode = GetMode();

	CARDSIDE side = GetPokerState();
	LPDIRECT3DDEVICE9 pDevice;

	//デバイス取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_UI; nCnt++)
	{
		if (g_aUi[nCnt].bUse == true)		//使用しているなら描画する
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureUI[g_aUi[nCnt].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//=============================================================================
// UI設定
//=============================================================================
void SetUI(D3DXVECTOR3 pos, float fWidth, float fHeight, UITYPE type)
{
	VERTEX_2D * pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_UI; nCnt++, pVtx += 4)
	{
		if (g_aUi[nCnt].bUse == false)
		{
			g_aUi[nCnt].pos = pos;			// 位置
			g_aUi[nCnt].fWidth = fWidth;	// 高さ
			g_aUi[nCnt].fHeight = fHeight;	// 幅
			g_aUi[nCnt].type = type;		// 種類

			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aUi[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCnt].fWidth, 0.0f, 0.0f) + g_aUi[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(0.0f, g_aUi[nCnt].fHeight, 0.0f) + g_aUi[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCnt].fWidth, g_aUi[nCnt].fHeight, 0.0f) + g_aUi[nCnt].pos;
			g_aUi[nCnt].bUse = true;
			break;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();
}
//=============================================================================
// 頂点情報生成処理
//=============================================================================
void MakeVertexUI(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEX_TYPE, &g_pTextureUI[UI_TYPELIST]);
	D3DXCreateTextureFromFile(pDevice, TEX_GUIDE, &g_pTextureUI[UI_GUIDE]);
	D3DXCreateTextureFromFile(pDevice, TEX_1P, &g_pTextureUI[UI_1P]);
	D3DXCreateTextureFromFile(pDevice, TEX_2P, &g_pTextureUI[UI_2P]);
	D3DXCreateTextureFromFile(pDevice, TEX_VS, &g_pTextureUI[UI_VS]);
	D3DXCreateTextureFromFile(pDevice, TEX_READY, &g_pTextureUI[UI_READY]);
	D3DXCreateTextureFromFile(pDevice, TEX_RESULT, &g_pTextureUI[UI_RESULT]);

	VERTEX_2D * pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_UI; nCnt++, pVtx += 4)
	{
		// ポリゴンの座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, -g_aUi[nCnt].fHeight, 0.0f) + g_aUi[nCnt].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aUi[nCnt].fWidth, -g_aUi[nCnt].fHeight, 0.0f) + g_aUi[nCnt].pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aUi[nCnt].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aUi[nCnt].fWidth, 0.0f, 0.0f) + g_aUi[nCnt].pos;
		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// ポリゴンの色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffUI->Unlock();
}
//=============================================================================
// どちらが勝ったか
//=============================================================================
void WhichWinner(void)
{
	// ファイルのポインタ取得
	FILE *pFile;
	pFile = fopen(LOAD_TEXT, "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &g_nWinner);
		fclose(pFile);
	}
}
//=============================================================================
// セット確認
//=============================================================================
bool GetReady(void)
{
	return g_bSetReady;
}
void SetReady(bool bSet)
{
	g_bSetReady = bSet;
}
int GetWinnerPlayer(void)
{
	return g_nWinner;
}

