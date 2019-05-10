//=============================================================================
//
// タイマー処理 [timer2.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "timer2.h"
//#include "dice.h"
//#include "game.h"
//#include "meter.h"
#include "ColorBall.h"
//=============================================================================
//	プロトタイプ宣言
//=============================================================================
void MakeTimer2Font(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
//	グローバル変数
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer2 = NULL;					//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTimer2 = NULL;						//テクスチャへのポインタ

LPD3DXFONT	pTimer2Font = NULL;	// フォントオブジェクト
D3DXCOLOR g_Timer2FontColor;		//フォントの色
char g_Timer2Text[256];	//フォントの文字[256で固定]

RECT g_Timer2Rect = {	//フォントを置く範囲
	1000,		// 左上のx座標
	500,			// 左上のy座標
	1600,		// 右下のx座標
	670			// 右下のy座標
};

int g_nCountTimer2;		//タイマーカウント用
int g_nDiceTime2;		//サイコロのタイマー

bool g_bSetTimer2Flag;		//タイマーのカウント制御

//=============================================================================
//	初期化処理
//=============================================================================
void InitTimer2(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//変数の初期化
	g_nCountTimer2 = 0;
	g_nDiceTime2 = -1;
	g_Timer2FontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);
	g_bSetTimer2Flag = true;
	//フォントの作成
	MakeTimer2Font(pDevice);

}

//=============================================================================
//	終了処理
//=============================================================================
void UninitTimer2(void)
{
	//フォントの解放
	if (pTimer2Font != NULL)
	{
		pTimer2Font->Release();
		pTimer2Font = NULL;
	}

}

//=============================================================================
//	更新処理
//=============================================================================
void UpdateTimer2(void)
{
	COLORBALL *pColBall;
	pColBall = GetColorBall();

	if (g_bSetTimer2Flag == true && g_nDiceTime2 != -1 && pColBall->state == COLORBALLSTATE_STOP)
	{
		g_nCountTimer2++;
		if (g_nCountTimer2 == 60)
		{
			//DeleteDice(2);
		}
		//タイマーのカウントダウン
		if (g_nCountTimer2 % TIMER_INTERVAL == 0)
		{
			g_nDiceTime2--;

		}

		//フォントの色の調整
		if (g_nDiceTime2 > 4)
		{
			g_Timer2FontColor = D3DXCOLOR(0.3f, 1.0f, 1.0f, 1.0f);

		}
		else
		{
			g_Timer2FontColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		}
		/*if (GetMeterSize() <= 0)
		{
			g_bSetTimer2Flag = false;
			g_nDiceTime2 = -1;
			SetGameState(GAMESTATE_OVER);
		}*/

		//if (GetKeyboardTrigger(DIK_L) == true)		//DEBUG
		//{
		//	g_nDiceTime2 = -1;
		//	SetDice(2);

		//}
		if (g_nDiceTime2 == 0 && g_nCountTimer2 % TIMER_INTERVAL == 59)
		{
			g_nDiceTime2 = 10;
			//SetDice(2);
			//SetTurnState(TURNSTATE_END);
			g_Timer2FontColor = D3DXCOLOR(0.4f, 1.0f, 1.0f, 1.0f);
		}

		//出力する文字列を設定
		wsprintf(g_Timer2Text, "%d.%d", g_nDiceTime2, 60 - (g_nCountTimer2 % TIMER_INTERVAL));
	}

}

//=============================================================================
//	描画処理
//=============================================================================
void DrawTimer2(void)
{
	if (g_nDiceTime2 != -1)
	{//プレイ中は表示
	 //フォントの描画
		pTimer2Font->DrawText(
			NULL,								// NULL
			g_Timer2Text,						// 描画するテキスト
			-1,									// 描画する文字数(-1で上のテキストの文字数を取得してくれる)
			&g_Timer2Rect,						// 描画範囲(上で定義したRECT型の変数のポインタを入れる)
			DT_VCENTER | DT_LEFT,				// 描画オプション
			g_Timer2FontColor					// 色指定
		);
	}

}

//=============================================================================
//	タイマーセット
//=============================================================================
void SetTimer2(int nTime)
{
	//取得した出目に応じて時間を決め、カウントを開始する
	g_nDiceTime2 = nTime /** TIMER_COUNT_COEFFICIENT*/ - 1;
	g_nCountTimer2 = 0;

	//出力する文字列を設定
	wsprintf(g_Timer2Text, "%d.%d", g_nDiceTime2, 60 - (g_nCountTimer2 % TIMER_INTERVAL));

}

//=============================================================================
//	フォントの作成
//=============================================================================
void MakeTimer2Font(LPDIRECT3DDEVICE9 pDevice)
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
		&pTimer2Font);				// フォントのポインタ

}

//=============================================================================
//	タイマーの取得
//=============================================================================
int GetTimer2(void)
{
	return g_nDiceTime2;
}

//=============================================================================
//	タイマーのカウントフラグの状態を取得
//=============================================================================
bool GetSetTimer2Flag(void)
{
	return g_bSetTimer2Flag;
}
