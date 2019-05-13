//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "timer.h"
//#include "dice.h"
//#include "game.h"
//#include "meter.h"

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;						//テクスチャへのポインタ

LPD3DXFONT	pTimerFont = NULL;	// フォントオブジェクト
D3DXCOLOR g_TimerFontColor;		//フォントの色
char g_TimerText[256];	//フォントの文字[256で固定]

RECT g_TimerRect = {	//フォントを置く範囲
	140,		// 左上のx座標
	50,			// 左上のy座標
	540,		// 右下のx座標
	150			// 右下のy座標
};

int g_nCountTimer;		//タイマーカウント用
int g_nDiceTime;		//サイコロのタイマー

bool g_bSetTimerFlag;		//タイマーのカウント制御

							//=============================================================================
							//	初期化処理
							//=============================================================================
void InitTimer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数の初期化
	g_nCountTimer = 0;
	g_nDiceTime = -1;
	g_TimerFontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);
	g_bSetTimerFlag = true;
	//フォントの作成
	MakeTimerFont(pDevice);

}

//=============================================================================
//	終了処理
//=============================================================================
void UninitTimer(void)
{
	//フォントの解放
	if (pTimerFont != NULL)
	{
		pTimerFont->Release();
		pTimerFont = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateTimer(void)
{
	/*TURNSTATE pTurnState;
	pTurnState = GetTurnState();*/

	if (g_bSetTimerFlag == true && g_nDiceTime != -1/* && pTurnState == TURNSTATE_MOVEandATTACK*/)
	{
		g_nCountTimer++;
		if (g_nCountTimer == 60)
		{
			//DeleteDice(2);
		}
		//タイマーのカウントダウン
		if (g_nCountTimer % TIMER_INTERVAL == 0)
		{
			g_nDiceTime++;

		}

		//フォントの色の調整
		if (g_nDiceTime > 4)
		{
			g_TimerFontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);

		}
		else
		{
			//g_TimerFontColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		}
		/*if (GetMeterSize() <= 0)
		{
		g_bSetTimerFlag = false;
		g_nDiceTime = -1;
		SetGameState(GAMESTATE_OVER);
		}*/

		//if (GetKeyboardTrigger(DIK_L) == true)		//DEBUG
		//{
		//	g_nDiceTime = -1;
		//	SetDice(2);

		//}
		if (g_nDiceTime == 0 && g_nCountTimer % TIMER_INTERVAL == 59)
		{
			//g_nDiceTime = 10;
			//SetDice(2);
			//SetTurnState(TURNSTATE_END);
			//g_TimerFontColor = D3DXCOLOR(0.4f, 1.0f, 1.0f, 1.0f);
		}

		//出力する文字列を設定
		wsprintf(g_TimerText, "%d.%d", g_nDiceTime, 0 + (g_nCountTimer % TIMER_INTERVAL));
	}

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawTimer(void)
{
	if (g_nDiceTime != -1)
	{//プレイ中は表示
	 //フォントの描画
		pTimerFont->DrawText(
			NULL,								// NULL
			g_TimerText,						// 描画するテキスト
			-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
			&g_TimerRect,						// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
			DT_VCENTER | DT_LEFT,				// 描画オプション
			g_TimerFontColor					// 色指定
		);
	}

}

//=============================================================================
//	タイマーセット
//=============================================================================
void SetTimer(int nTime)
{
	//取得した出目に応じて時間を決め、カウントを開始する
	g_nDiceTime = nTime /** TIMER_COUNT_COEFFICIENT*/;
	g_nCountTimer = 0;

	//出力する文字列を設定
	wsprintf(g_TimerText, "%d.%d", g_nDiceTime, 60 - (g_nCountTimer % TIMER_INTERVAL));

}

//=============================================================================
//	フォントの作成
//=============================================================================
void MakeTimerFont(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFont(
		pDevice,					// デバイスのポインタ
		80,							// 高さ
		40,							// 幅
		FW_BLACK,					// フォントの太さ
		NULL,						// 下線
		FALSE,						// 斜体(TRUEでon,FALSEでoff)
		SHIFTJIS_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度(OUT_DEFAULT_PRECISで固定)
		PROOF_QUALITY,				// 文字の品質
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリのインデックス
		TEXT("Meiryo UI"),			// フォント名(空白、大文字も含めて正確に入力すること)
		&pTimerFont);				// フォントのポインタ

}

//=============================================================================
//	タイマーの取得
//=============================================================================
int GetTimer(void)
{
	return g_nDiceTime;
}

//=============================================================================
//	タイマーのカウントフラグの状態を取得
//=============================================================================
bool GetSetTimerFlag(void)
{
	return g_bSetTimerFlag;
}
