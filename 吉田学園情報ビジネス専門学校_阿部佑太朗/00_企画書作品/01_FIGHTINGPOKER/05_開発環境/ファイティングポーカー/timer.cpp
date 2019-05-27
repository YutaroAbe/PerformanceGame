//=============================================================================
//
// タイム処理 [timer.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "timer.h"
#include "input.h"
#include "cardModel.h"
#include "poker.h"
#include "ui.h"
#include "game.h"
#include "gamefade.h"
#include "fade.h"
#include "battle.h"
#include "message.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number001.png"	// 読み込むテクスチャファイル名
#define INFINIT_TEX			"data/TEXTURE/infinite.png"		// 読み込むテクスチャファイル名
#define	FRAME_TEXTURE		"data/TEXTURE/frame_timer.png"	// 読み込むテクスチャファイル名
/* ポーカー時 */
#define POKER_TIME_WIDTH		(510.0f)			// X座標
#define POKER_TIME_WIDTH2		(570.0f)			// X座標
#define POKER_TIME_HEIGHT		(20.0f)				// Y座標
#define POKER_TIME_HEIGHT2		(80.0f)				// Y座標
#define POKER_FRAME_WIDTH		(380.0f)			// X座標
#define POKER_FRAME_WIDTH2		(630.0f)			// X座標
#define POKER_FRAME_HEIGHT		(0.0f)				// Y座標
#define POKER_FRAME_HEIGHT2		(100.0f)			// Y座標
/* バトル時 */
#define BATTLE_TIME_WIDTH		(SCREEN_WIDTH /2 + 5.0f)			// X座標
#define BATTLE_TIME_WIDTH2		(SCREEN_WIDTH /2 + 55.0f)			// X座標
#define BATTLE_TIME_HEIGHT		(0.0f)				// Y座標
#define BATTLE_TIME_HEIGHT2		(100.0f)				// Y座標

#define TIMER_SPACE			(40)				// 数字のスペース
#define TIME_COUNT			(2)					// スコアの桁数
#define FPM					(60)				// 60秒カウントする
#define MAX_TEXTURE			(TIMERTYPE_MAX)		// 読み込むテクスチャの最大数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTimer[MAX_TEXTURE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;				//頂点バッファへのポインタ
Timer					g_Time;								//タイマーの情報
bool					g_bSwitch = true;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTimer(void)
{
	GAMEMODE GameMode = GetGameMode();
	int nRound = GetRoundCounter();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// タイマーの初期化
	if (GameMode == GAMEMODE_POKER)
	{
		g_Time.nTime = MAX_TIME;
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TIME, &g_pTextureTimer[TIMERTYPE_COUNT]);
		D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE, &g_pTextureTimer[TIMERTYPE_FRAME]);
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		g_Time.nTime = BATTLE_TIME;
		if (nRound <= 4)
		{
			g_Time.nTime = BATTLE_TIME;
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, TEXTURE_TIME, &g_pTextureTimer[TIMERTYPE_COUNT]);
		}
		if (nRound == 5)
		{
			D3DXCreateTextureFromFile(pDevice, INFINIT_TEX, &g_pTextureTimer[TIMERTYPE_COUNT]);
		}

		g_bSwitch = false;
	}
	g_Time.bUseTime = false;
	g_Time.bFinish = false;

	// 頂点情報の作成
	MakeVertexTimer(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureTimer[nCnt] != NULL)
		{
			g_pTextureTimer[nCnt]->Release();
			g_pTextureTimer[nCnt] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{
	int nCntTime;
	int nPlus[TIME_COUNT];
	static int nCntFrame = 0;
	int nRound = GetRoundCounter();
	GAMEMODE GameMode = GetGameMode();

	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	BATTLESTATE batleState = GetBattleState();

	bool bReady = GetReady();		// プレイヤーの準備が完了しているか

	VERTEX_2D *pVtx;//頂点情報へのポインタ

#if _DEBUG
	if (GetKeyboardTrigger(DIK_T) == true)
	{
		g_bSwitch = g_bSwitch ? false : true;
	}
#endif
	switch (GameMode)
	{
	case GAMEMODE_POKER:
		if (bReady == true)
		{
			//フレーム数の加算
			nCntFrame++;
			if (nCntFrame % FPM == 0)
			{
				g_Time.nTime--;
				if (g_Time.nTime <= 0)
				{// カウントが0になったら
					g_Time.nTime = 0;
				}
			}
		}
		break;
	case GAMEMODE_BATTLE:
		//フレーム数の加算
		if (g_bSwitch == true)
		{
			if (nRound <= 4)
			{
				nCntFrame++;
				if (nCntFrame % FPM == 0)
				{
					g_Time.nTime--;
					if (g_Time.nTime <= 0)
					{// カウントが0になったら
						g_Time.nTime = 0;
						if (batleState != BATTLESTATE_TIMEOVER && batleState != BATTLESTATE_NONE && batleState != BATTLESTATE_CLEAR)
						{// バトルステートを時間切れに変更
							SetBattleState(BATTLESTATE_TIMEOVER);

							// タイムオーバーを表示
							SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_TIMEOVER);
							SelectVolume(SOUND_LABEL_TIMEOVER_SE, 0.8f);
						}
					}
				}
			}
		}
		break;
	}
	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	if (GameMode == GAMEMODE_POKER)
	{
		for (nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
		{
			int nTimeData = 1;
			for (int nCnt_Ftime = nCntTime; nCnt_Ftime != 0; nCnt_Ftime--)
			{
				nTimeData *= 10;
			}
			nPlus[nCntTime] = g_Time.nTime % (nTimeData * 10) / nTimeData;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 1.0f);
		}
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		if (nRound <= 4)
		{
			for (nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
			{
				int nTimeData = 1;
				for (int nCnt_Ftime = nCntTime; nCnt_Ftime != 0; nCnt_Ftime--)
				{
					nTimeData *= 10;
				}
				nPlus[nCntTime] = g_Time.nTime % (nTimeData * 10) / nTimeData;

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + float((nPlus[nCntTime] * 0.1)), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + float((nPlus[nCntTime] * 0.1)), 1.0f);
			}
		}
		if (nRound == 5)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	GAMEMODE GameMode = GetGameMode();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimer[TIMERTYPE_FRAME]);
	if (GameMode == GAMEMODE_POKER)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 + 8,	// 描画を開始する頂点インデックス
			2);
	}
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimer[TIMERTYPE_COUNT]);
	// ポリゴンの描画
	for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntTime * 4,// 描画を開始する頂点インデックス
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	GAMEMODE GameMode = GetGameMode();
	int nRound = GetRoundCounter();

	// 頂点情報を設定
	VERTEX_2D * pVtx;

	if (GameMode == GAMEMODE_POKER)
	{
		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_COUNT * MAX_TEXTURE,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTimer,
			NULL);
	}

	if (GameMode == GAMEMODE_BATTLE)
	{
		if (nRound <= 4)
		{
			// 頂点バッファを生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_COUNT,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_pVtxBuffTimer,
				NULL);
		}
		if (nRound == 5)
		{
			// 頂点バッファを生成
			pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
				D3DUSAGE_WRITEONLY,
				FVF_VERTEX_2D,
				D3DPOOL_MANAGED,
				&g_pVtxBuffTimer,
				NULL);
		}
	}

	if (GameMode == GAMEMODE_POKER)
	{
		// 頂点バッファをロックし頂点データへのポインタを取得
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
		/* 数字 */
		for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
		{
			// ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(POKER_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(POKER_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(POKER_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(POKER_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), POKER_TIME_HEIGHT2, 0.0f);
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			// ポリゴンの色
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			// テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		pVtx += 4;	// 頂点情報を4つ進める
					/* フレーム */
					// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(POKER_FRAME_WIDTH, POKER_FRAME_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(POKER_FRAME_WIDTH2, POKER_FRAME_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(POKER_FRAME_WIDTH, POKER_FRAME_HEIGHT2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(POKER_FRAME_WIDTH2, POKER_FRAME_HEIGHT2, 0.0f);
		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		g_pVtxBuffTimer->Unlock();
	}
	if (GameMode == GAMEMODE_BATTLE)
	{
		// 頂点バッファをロックし頂点データへのポインタを取得
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
		/* 数字 */
		if (nRound <= 4)
		{
			for (int nCntTime = 0; nCntTime < TIME_COUNT; nCntTime++, pVtx += 4)
			{
				// ポリゴンの座標設定
				pVtx[0].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(BATTLE_TIME_WIDTH2 - float((TIMER_SPACE * nCntTime)), BATTLE_TIME_HEIGHT2, 0.0f);
				// rhwの設定
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;
				// ポリゴンの色
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				// テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
			}
		}
		if (nRound == 5)
		{
			// ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(550.0f, POKER_FRAME_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(720.0f, POKER_FRAME_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(550.0f, POKER_FRAME_HEIGHT2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(720.0f, POKER_FRAME_HEIGHT2, 0.0f);
			// rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			// ポリゴンの色
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			// テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffTimer->Unlock();
	}
}



//=============================================================================
// タイマーの取得
//=============================================================================
Timer *GetTimer(void)
{
	return &g_Time;
}

//=============================================================================
// タイマーのON/OFF
//=============================================================================
void SetTimerSwitch(bool bSwitch)
{
	g_bSwitch = bSwitch;
}