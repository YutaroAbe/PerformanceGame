//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ポーズメニュー処理 [pausemenu.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "pausemenu.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "battle.h"
#include "game.h"
#include "gamefade.h"
#include "sound.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define ANIM_CUT				(1)										// アニメーションの分割数
#define ANIM_CUT_WIDTH			(1.0f)									// アニメーションの横の分割数
#define ANIM_CUT_HEIGHT			(1.0f)									// アニメーションの縦の分割数
#define ANIM_PATTERN_WIDTH		float(1 / ANIM_CUT_WIDTH)				// アニメーションの横パターンの加算数
#define ANIM_PATTERN_HEIGHT		float(1 / ANIM_CUT_HEIGHT)				// アニメーションの縦パターンの加算数
#define PAUSEMENU_MAX			(4)										// 表示するオブジェクトの数
#define PAUSEMENU_SELECT_WIDTH	(350)									// 選択肢の横幅
#define PAUSEMENU_SELECT_HEIGHT	(100)									// 選択肢の縦幅
#define PAUSEMENU_WIDTH			(400)									// メニューの横幅
#define PAUSEMENU_HEIGHT		(400)									// メニューの縦幅

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	PAUSEMENU_TEX_BG = 0,		// メニュー背景
	PAUSEMENU_TEX_CONTINUE,		// コンテニュー
	PAUSEMENU_TEX_RULEBOOK,		// リトライ
	PAUSEMENU_TEX_QUIT,			// クイット
	PAUSEMENU_TEX_MAX,			// 総数
}PauseMenuTexName;

typedef struct
{
	char *pFilename;	// ファイル名
} PauseMenuTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexPausemenu(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTexturePausemenu[PAUSEMENU_TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPausemenu = NULL;					// 頂点バッファへのポインタ
Pausemenu				g_aPausemenu[PAUSEMENU_MAX];				// ポーズメニューの情報
int						g_nSelectCounter;							// 選択肢のカウンター
int						g_nPuressCounter;							// プレスのカウンター

// 読み込むテクスチャ名の設定
PauseMenuTexInfo g_apTexturePausemenuInfo[PAUSEMENU_TEX_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },		// メニュー背景
	{ "data//TEXTURE//pause000.png" },		// コンテニュー
	{ "data//TEXTURE//pause001.png" },		// リトライ
	{ "data//TEXTURE//pause002.png" },		// クイット
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPausemenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ポーズの情報の初期化
	for(int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		g_aPausemenu[nCntPausemenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPausemenu[nCntPausemenu].nTexType = PAUSEMENU_TEX_BG;
		g_aPausemenu[nCntPausemenu].fWidth = 0.0f;
		g_aPausemenu[nCntPausemenu].fHeight = 0.0f;
		g_aPausemenu[nCntPausemenu].bUse = false;
		g_aPausemenu[nCntPausemenu].bSelect = false;
	}

	g_nSelectCounter = 0;
	g_nPuressCounter = 0;

	// テクスチャの読み込み
	for (int nCntPausemenuTex = 0; nCntPausemenuTex < PAUSEMENU_TEX_MAX; nCntPausemenuTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePausemenuInfo[nCntPausemenuTex].pFilename,
			&g_pTexturePausemenu[nCntPausemenuTex]);
	}


	// 頂点情報の作成
	MakeVertexPausemenu(pDevice);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2), 0.0f), PAUSEMENU_TEX_BG,
		PAUSEMENU_WIDTH, PAUSEMENU_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2 - 100.0f), 0.0f), PAUSEMENU_TEX_CONTINUE,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2), 0.0f), PAUSEMENU_TEX_RULEBOOK,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

	SetPauseMenu(D3DXVECTOR3(float(SCREEN_WIDTH / 2) + 10.0f, float(SCREEN_HEIGHT / 2 + 100.0f), 0.0f), PAUSEMENU_TEX_QUIT,
		PAUSEMENU_SELECT_WIDTH, PAUSEMENU_SELECT_HEIGHT);

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPausemenu(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PAUSEMENU_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (g_pTexturePausemenu[nCntTex] != NULL)
		{
			g_pTexturePausemenu[nCntTex]->Release();
			g_pTexturePausemenu[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPausemenu != NULL)
	{
		g_pVtxBuffPausemenu->Release();
		g_pVtxBuffPausemenu = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePausemenu()
{
	int nRound = GetRoundCounter();
	// 単発押しの処理
	if (GetKeyboardTrigger(DIK_S) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
	{
		g_nSelectCounter = (g_nSelectCounter + 1) % MAX_MENU;
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);


	}
	else if (GetKeyboardTrigger(DIK_W) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP) == true)
	{
		PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		g_nSelectCounter = (g_nSelectCounter + MAX_MENU - 1) % MAX_MENU;
	}

	// 長押しの処理
	if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
	{
		g_nPuressCounter++;
		if (g_nPuressCounter > 30)
		{
			if (g_nPuressCounter % 5 == 0)
			{
				g_nSelectCounter = (g_nSelectCounter + 1) % MAX_MENU;
			}
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
	{
		g_nPuressCounter++;
		if (g_nPuressCounter > 30)
		{
			if (g_nPuressCounter % 5 == 0)
			{
				g_nSelectCounter = (g_nSelectCounter + MAX_MENU - 1) % MAX_MENU;
			}
		}
	}

	// ポーズカウンターの初期化
	if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
	{
		g_nPuressCounter = 0;
	}
	else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
	{
		g_nPuressCounter = 0;
	}

	for (int nCntPausemenu = 1; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		if (g_nSelectCounter == nCntPausemenu - 1)
		{
			g_aPausemenu[nCntPausemenu].bSelect = true;
		}
		else
		{
			g_aPausemenu[nCntPausemenu].bSelect = false;
		}
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
	{
		if (g_aPausemenu[nCntPausemenu].nTexType == PAUSEMENU_TEX_BG)
		{ // 選択肢が選択されている
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (g_aPausemenu[nCntPausemenu].bSelect == true)
		{ // 選択肢が選択されている
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_aPausemenu[nCntPausemenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		}
		pVtx[0].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[1].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[2].col = g_aPausemenu[nCntPausemenu].col;
		pVtx[3].col = g_aPausemenu[nCntPausemenu].col;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPausemenu->Unlock();


	FADE pFade;
	// フェードモードの取得
	pFade = GetFade();
	// フェードが通常状態か
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		if (pFade == FADE_NONE)
		{
			if (g_nSelectCounter == MENU_CONTINUE)
			{
				//キャンセル
				PlaySound(SOUND_LABEL_SE_CANCEL);
				SetPauseState(false);
				SetRulePauseState(false);
				g_nPuressCounter = 0;
			}
			else if (g_nSelectCounter == MENU_RULEBOOK)
			{
				//キャンセル
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetPauseState(false);
				SetRulePauseState(true);
			}
			else if (g_nSelectCounter == MENU_QUIT)
			{
				// ゲームタイトル
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				if (nRound < 5)
				{
					StopSound(SOUND_LABEL_GAME_R1R2R3R4_BGM);
				}
				else
				{
					StopSound(SOUND_LABEL_GAME_R5_BGM);
				}
				SetFade(MODE_TITLE);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPausemenu(void)
{
	int nCntPausemenu;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffPausemenu, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePausemenu[g_aPausemenu[nCntPausemenu].nTexType]);
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPausemenu * 4, 2);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexPausemenu(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSEMENU_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPausemenu,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
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
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ANIM_PATTERN_WIDTH, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ANIM_PATTERN_HEIGHT);
		pVtx[3].tex = D3DXVECTOR2(ANIM_PATTERN_WIDTH, ANIM_PATTERN_HEIGHT);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPausemenu->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズメニューの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseMenu(D3DXVECTOR3 pos, int Textype, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;		// 頂点情報へのポインタ
							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPausemenu->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPausemenu = 0; nCntPausemenu < PAUSEMENU_MAX; nCntPausemenu++, pVtx += 4)
	{
		if (g_aPausemenu[nCntPausemenu].bUse == false)
		{ // タイトルが使用されていない場合
		  // 頂点位置の設定
			g_aPausemenu[nCntPausemenu].pos = pos;
			g_aPausemenu[nCntPausemenu].fWidth = fWidth;
			g_aPausemenu[nCntPausemenu].fHeight = fHeight;

			// ポーズメニューの種類の設定
			g_aPausemenu[nCntPausemenu].nTexType = Textype;

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x - g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y - g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x + g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y - g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x - g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y + g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPausemenu[nCntPausemenu].pos.x + g_aPausemenu[nCntPausemenu].fWidth / 2, g_aPausemenu[nCntPausemenu].pos.y + g_aPausemenu[nCntPausemenu].fHeight / 2, 0.0f);

			g_aPausemenu[nCntPausemenu].bUse = true;	// 使用する状態にする
			break;	// このbreakはかなり大切
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffPausemenu->Unlock();
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetPauseSelect(void)
{
	return g_nSelectCounter;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ポーズ選択肢の初期化
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPauseSelect(void)
{
	g_nSelectCounter = MENU_CONTINUE;
}
