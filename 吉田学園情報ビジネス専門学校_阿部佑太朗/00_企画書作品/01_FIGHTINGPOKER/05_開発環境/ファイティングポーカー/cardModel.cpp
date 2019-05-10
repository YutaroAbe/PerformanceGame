//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 舘田　翼
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "time.h"

#include "input.h"
#include "camera.h"
#include "poker.h"
#include "cardModel.h"
#include "timer.h"
#include "3DUi.h"
#include "PlayerShow.h"
#include "ui.h"
#include "gamefade.h"
#include "sound.h"
#include "gamepad.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_CARD		"data/MODEL/card.x"			// カードのモデル
#define TEX_BRAVE		"data/TEXTURE/breve.png"	// 勇者マークのテクスチャ
#define TEX_KING		"data/TEXTURE/king.png"		// 王様マークのテクスチャ
#define TEX_DEVIL		"data/TEXTURE/devil.png"	// 魔王マークのテクスチャ
#define TEX_HEART		"data/TEXTURE/heart.png"	// ハートマークのテクスチャ
#define TEX_JOKER		"data/TEXTURE/joker.png"	// ジョーカーマークのテクスチャ
#define PRESS_CNT				(30)		// プレスのカウント
#define POS_1P_XFIRST			(-400.0f)	// 左のX位置
#define POS_1P_Z_1				(-100.0f)	// Z位置
#define POS_1P_XSPACE_1			(-150.0f)	// Xのスペース
#define POS_LEFT_1P_1			D3DXVECTOR3(POS_1P_XFIRST,0.0f,POS_1P_Z_1)								// 1P 左の位置
#define POS_CENTERLEFT_1P_1		D3DXVECTOR3((POS_1P_XFIRST - POS_1P_XSPACE_1), 0.0f, POS_1P_Z_1)		// 1P センター左の位置
#define POS_CENTER_1P_1			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 2)), 0.0f, POS_1P_Z_1)	// 1P センターの位置
#define POS_RIGHTCENTER_1P_1	D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 3)), 0.0f, POS_1P_Z_1)	// 1P センター右の位置
#define POS_RIGHT_1P_1			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_1 * 4)), 0.0f, POS_1P_Z_1)	// 1P 右の位置

#define POS_1P_XSPACE_2			(-75.0f)	// Xのスペース
#define POS_1P_Z_2				(-200.0f)	// Z位置
#define POS_LEFT_1P_2			D3DXVECTOR3(POS_1P_XFIRST,0.0f,POS_1P_Z_2)								// 1P 左の位置
#define POS_CENTERLEFT_1P_2		D3DXVECTOR3((POS_1P_XFIRST - POS_1P_XSPACE_2), 0.0f, POS_1P_Z_2)		// 1P センター左の位置
#define POS_CENTER_1P_2			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 2)), 0.0f, POS_1P_Z_2)	// 1P センターの位置
#define POS_RIGHTCENTER_1P_2	D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 3)), 0.0f, POS_1P_Z_2)	// 1P センター右の位置
#define POS_RIGHT_1P_2			D3DXVECTOR3((POS_1P_XFIRST - (POS_1P_XSPACE_2 * 4)), 0.0f, POS_1P_Z_2)	// 1P 右の位置

#define POS_2P_XFIRST_1			(-400.0f)	// 左のX位置
#define POS_2P_Z_1				(150.0f)	// Z位置
#define POS_2P_XSPACE_1			(-150.0f)	// Xのスペース
#define POS_LEFT_2P_1			D3DXVECTOR3(POS_2P_XFIRST_1,0.0f,POS_2P_Z_1)								// 2P 左の位置
#define POS_CENTERLEFT_2P_1		D3DXVECTOR3((POS_2P_XFIRST_1 - POS_2P_XSPACE_1), 0.0f, POS_2P_Z_1)			// 2P センター左の位置
#define POS_CENTER_2P_1			D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 2)), 0.0f, POS_2P_Z_1)	// 2P センターの位置
#define POS_RIGHTCENTER_2P_1	D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 3)), 0.0f, POS_2P_Z_1)	// 2P センター右の位置
#define POS_RIGHT_2P_1			D3DXVECTOR3((POS_2P_XFIRST_1 - (POS_2P_XSPACE_1 * 4)), 0.0f, POS_2P_Z_1)	// 2P 右の位置

#define POS_2P_XFIRST_2			(95.0f)		// 左のX位置
#define POS_2P_XSPACE_2			(-75.0f)	// Xのスペース
#define POS_2P_Z_2				(-200.0f)	// Z位置
#define POS_LEFT_2P_2			D3DXVECTOR3(POS_2P_XFIRST_2,0.0f,POS_2P_Z_2)								// 2P 左の位置
#define POS_CENTERLEFT_2P_2		D3DXVECTOR3((POS_2P_XFIRST_2 - POS_2P_XSPACE_2), 0.0f, POS_2P_Z_2)			// 2P センター左の位置
#define POS_CENTER_2P_2			D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 2)), 0.0f, POS_2P_Z_2)	// 2P センターの位置
#define POS_RIGHTCENTER_2P_2	D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 3)), 0.0f, POS_2P_Z_2)	// 2P センター右の位置
#define POS_RIGHT_2P_2			D3DXVECTOR3((POS_2P_XFIRST_2 - (POS_2P_XSPACE_2 * 4)), 0.0f, POS_2P_Z_2)	// 2P 右の位置

#define DECK_POS_Z				(POS_1P_Z_1 + POS_2P_Z_1 / 2) - (POS_1P_Z_1 / 2)							// 山札の位置(Z)
#define DECK_POS				D3DXVECTOR3(POS_1P_XFIRST - (POS_1P_XSPACE_1 * 2), 0.0f, DECK_POS_Z)		// 山札の位置
#define SELECT_POS				(30.0f)		// 選択したカードがどこまで移動するか
#define ROT_SPEED				(0.1f)		// 回転する速さ
#define WIDTH					(5.0f)		// 位置判定の幅
#define MAX_SET_CARD			(5)			// 配布カードの最大
#define MAX_MODEL				(1)			// 読み込むモデルの最大数
#define MAX_BRAVE				(13)		// 勇者カードの枚数
#define MAX_ROUND				(5)			// 最大ラウンド数
#define MAX_KING				(13)		// 王様カードの枚数
#define MAX_DEVIL				(13)		// 魔王カードの枚数
#define MAX_HEART				(13)		// 回復カードの枚数
#define MAX_JOKER				(2)			// ジョーカーの枚数
#define MAX_CARD				(MAX_BRAVE + MAX_KING + MAX_DEVIL + MAX_HEART+ MAX_JOKER)	// 全カードの枚数
#define MAX_STATUS				(PARAMETER_MAX)	// 攻撃力　防御力
#define AUTO_FADE_TIME			(120)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nStatus1P[STATUS_MAX]; // 1Pのステータス管理
int g_nStatus2P[STATUS_MAX]; // 2Pのステータス管理
int g_nNowPlayer;
int g_nSelectCard;			// 交換するカードの番号
int g_nTwoRandType;			// ツーペア時にどちらかのタイプに割り当てる
int g_nData[MAX_PLAYER];	// 役判定用の数字を格納する
int g_nPressCnt;			// プレスのカウンター
int g_nSetCnt;				// カードを配布するカウント
int g_nNumBrave1P;			// 勇者の枚数
int g_nNumKing1P;			// 王様の枚数
int g_nNumDevil1P;			// 魔王の枚数
int g_nNumCommoner1P;		// 回復の枚数
int g_nNumJoker1P;			// ジョーカーの枚数
int g_nNumBrave2P;			// 勇者の枚数
int g_nNumKing2P;			// 王様の枚数
int g_nNumDevil2P;			// 魔王の枚数
int g_nNumCommoner2P;		// 回復の枚数
int g_nNumJoker2P;			// ジョーカーの枚数
int g_nFadeCnt;				// プレイヤーチェンジまでのカウント
bool g_bTwoPair1P;			// どのタイプ同士でツーペアになっているか
bool g_bTwoPair2P;			// どのタイプ同士でツーペアになっているか
bool g_bSet;				// 配布済みかどうか
bool g_bChangePlayer;		// プレイヤーが交代されたか
bool g_bRotFin;				// 回転が終了したか
bool g_bFinish;				// ポーカーが終了したか
CARDSIDE g_PokerState;		// ゲームの状態判断
CARDTYPE g_aType[MAX_PLAYER];				// 現在のタイプを保存する
D3DXVECTOR3	g_ChangePos;					// 山札の位置
CardModel	g_aCardModel1P[MAX_SET_CARD];	// 1Pの情報
CardModel	g_aCardModel2P[MAX_SET_CARD];	// 2Pの情報
CardModel	g_CardDeck;						// 山札の情報
											// 読み込むオブジェクト名の設定
CardData		g_apCardModel[TYPE_MAX] = {};
D3DXVECTOR3		g_aDestCard1P[CARD_POS_MAX] =
{// 1Pの位置設定
	POS_LEFT_1P_1,				// 1P 左
	POS_CENTERLEFT_1P_1,		// 1P センター左
	POS_CENTER_1P_1,			// 1P センター
	POS_RIGHTCENTER_1P_1,		// 1P センター右
	POS_RIGHT_1P_1,				// 1P 右
};
D3DXVECTOR3		g_aDestCard2P[CARD_POS_MAX] =
{// 2Pの位置設定
	POS_RIGHT_2P_1,				// 2P 左
	POS_RIGHTCENTER_2P_1,		// 2P センター左
	POS_CENTER_2P_1,			// 2P センター
	POS_CENTERLEFT_2P_1,		// 2P センター右
	POS_LEFT_2P_1,				// 2P 右
};
D3DXVECTOR3		g_aShowCard1P[CARD_POS_MAX] =
{// 1Pの位置設定
	POS_LEFT_1P_2,				// 1P 左
	POS_CENTERLEFT_1P_2,		// 1P センター左
	POS_CENTER_1P_2,			// 1P センター
	POS_RIGHTCENTER_1P_2,		// 1P センター右
	POS_RIGHT_1P_2,				// 1P 右
};
D3DXVECTOR3		g_aShowCard2P[CARD_POS_MAX] =
{// 2Pの位置設定
	POS_RIGHT_2P_2,				// 2P 左
	POS_RIGHTCENTER_2P_2,		// 2P センター左
	POS_CENTER_2P_2,			// 2P センター
	POS_CENTERLEFT_2P_2,		// 2P センター右
	POS_LEFT_2P_2,				// 2P 右
};
//=============================================================================
// 初期化処理
//=============================================================================
void InitCardModel(void)
{
	srand((unsigned int)time(0));	// 起動する時間で値を変える
									//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// モデルの読み込み
	LoadModel(pDevice);

	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{// 1Pの情報初期化
		g_aCardModel1P[nCntModel].type = TYPE_BRAVE;							// 種類
		g_aCardModel1P[nCntModel].ModelType = 0;								// 描画用
		g_aCardModel1P[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
		g_aCardModel1P[nCntModel].rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);			// 向き
		g_aCardModel1P[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動量
		g_aCardModel1P[nCntModel].bUse = false;									// 使用しているか
		g_aCardModel1P[nCntModel].distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 距離
		g_aCardModel1P[nCntModel].bMove = false;								// 移動しているか
		g_aCardModel1P[nCntModel].bSelect = false;								// 選択されているか
		g_aCardModel1P[nCntModel].bChange = false;								// チェンジしているか
	}
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{// 2Pの情報初期化
		g_aCardModel2P[nCntModel].type = TYPE_BRAVE;									// 種類
		g_aCardModel2P[nCntModel].ModelType = 0;										// 描画用
		g_aCardModel2P[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
		g_aCardModel2P[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
		g_aCardModel2P[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 移動量
		g_aCardModel2P[nCntModel].bUse = false;											// 使用しているか
		g_aCardModel2P[nCntModel].distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 距離
		g_aCardModel2P[nCntModel].bMove = false;										// 移動しているか
		g_aCardModel2P[nCntModel].bSelect = false;										// 選択されているか
		g_aCardModel2P[nCntModel].bChange = false;										// チェンジしているか
	}
	// 山札の情報初期化
	g_CardDeck.pos = DECK_POS;	// 位置
	g_ChangePos = DECK_POS;		// 山札の位置
	g_CardDeck.bUse = false;	// 使用しているか
								// ツーペア判断用
	g_bTwoPair1P = false;	// どのタイプ同士でツーペアになっているか
	g_bTwoPair2P = false;	// どのタイプ同士でツーペアになっているか
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_nData[nCntPlayer] = 0;			// 役判定用
		g_aType[nCntPlayer] = TYPE_BRAVE;	// 現在のタイプを保存する
	}
	g_bSet = false;					// カードがセットされているか
	g_bChangePlayer = false;		// プレイヤーが交代されたか
	g_bRotFin = false;				// 回転し終わったか
	g_PokerState = CARD_SIDE_1P;	// ポーカーの状態
	g_nFadeCnt = 0;					// 自動でフェードするカウント
	g_nSelectCard = 0;				// 何番のカードが選ばれているか
	g_nTwoRandType = 0;				// ツーペア時にどちらかランダムで割り振る
	g_nPressCnt = 0;				// カード選択のプレスカウント
	g_nSetCnt = 0;					// カードを配るカウント
	g_nNumBrave1P = 0;				// 勇者の数
	g_nNumKing1P = 0;				// 王様の数
	g_nNumDevil1P = 0;				// 魔王の数
	g_nNumCommoner1P = 0;			// 平民の数
	g_nNumJoker1P = 0;				// 姫の数
	g_nNumBrave2P = 0;				// 勇者の数
	g_nNumKing2P = 0;				// 王様の数
	g_nNumDevil2P = 0;				// 魔王の数
	g_nNumCommoner2P = 0;			// 平民の数
	g_nNumJoker2P = 0;				// 姫の数
	g_nNowPlayer = 1;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitCardModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// メッシュの開放
		if (g_apCardModel[nCntModel].pMesh != NULL)
		{
			g_apCardModel[nCntModel].pMesh->Release();
			g_apCardModel[nCntModel].pMesh = NULL;
		}
		// マテリアルの開放
		if (g_apCardModel[nCntModel].pBuffMat != NULL)
		{
			g_apCardModel[nCntModel].pBuffMat->Release();
			g_apCardModel[nCntModel].pBuffMat = NULL;
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateCardModel(void)
{
	bool bReady = GetReady();
	GAMEMODE GameMode = GetGameMode();
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();
	Timer *pTimer = GetTimer();

	if (GameMode == GAMEMODE_POKER)
	{
		g_CardDeck.bUse = true;
		SetCard();	// カードセット
		for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
		{
			if (g_aCardModel1P[nCntModel].pos.x > g_aCardModel1P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel1P[nCntModel].pos.x < g_aCardModel1P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel1P[nCntModel].pos.z > g_aCardModel1P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel1P[nCntModel].pos.z < g_aCardModel1P[nCntModel].DestPos.z + WIDTH)
			{// カードの判定
				g_aCardModel1P[nCntModel].bMove = false;
			}
			if (g_aCardModel2P[nCntModel].pos.x > g_aCardModel2P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel2P[nCntModel].pos.x < g_aCardModel2P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel2P[nCntModel].pos.z > g_aCardModel2P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel2P[nCntModel].pos.z < g_aCardModel2P[nCntModel].DestPos.z + WIDTH)
			{// カードの判定
				g_aCardModel2P[nCntModel].bMove = false;
			}
			// 位置更新
			if (g_aCardModel1P[nCntModel].bMove == true)
			{
				g_aCardModel1P[nCntModel].pos += g_aCardModel1P[nCntModel].move;
			}
			if (g_aCardModel2P[nCntModel].bMove == true)
			{
				g_aCardModel2P[nCntModel].pos += g_aCardModel2P[nCntModel].move;
			}
		}
		if (bReady == true)
		{
			MoveCursor();	// カーソル移動
		}
		if (pTimer->bFinish == false)
		{
			//=============== [ 1P操作 ] ===============//
			if (g_PokerState == CARD_SIDE_1P)
			{
				g_nNowPlayer = 0;
				for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
				{
					if (bReady == true)
					{
						if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) || GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP))
						{// 交換するカードを選択
							SelectCard1P((CARDPOS)g_nSelectCard);
							PlaySound(SOUND_LABEL_SE_CARD_SET);
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P)
						{// 自分のカードは全て表にする
							g_aCardModel1P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel1P[nCntModel].rot.z >= D3DX_PI)
							{
								g_aCardModel1P[nCntModel].rot.z = D3DX_PI;
								g_bRotFin = true;
							}
						}
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P && g_aCardModel2P[nCntModel].PosType == CARD_POS_RIGHT)
						{// 相手カードの右端を表にする
							g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel2P[nCntModel].rot.z >= D3DX_PI)
							{
								g_aCardModel2P[nCntModel].rot.z = D3DX_PI;
								g_bRotFin = true;
							}
						}
					}
					if (g_bRotFin == true)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P,ELECOM_A))
						{// カードを山札に戻す(交換)
							PlaySound(SOUND_LABEL_SE_CARD_SELECT);
							ChangeCard1P();
							pTimer->nTime = 0;
						}
					}
				}
				if (bReady == false)
				{
					SetReady(false);
				}
			}
			//=============== [ 2P操作 ] ===============//
			if (g_PokerState == CARD_SIDE_2P)
			{
				g_nNowPlayer = 1;
				for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
				{
					if (bReady == true)
					{
						if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) || GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP))
						{// 交換するカードを選択
							SelectCard2P((CARDPOS)g_nSelectCard);
							PlaySound(SOUND_LABEL_SE_CARD_SET);
						}
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P)
						{// 自分のカードは全て表にする
							g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel2P[nCntModel].rot.z >= -D3DX_PI)
							{
								g_aCardModel2P[nCntModel].rot.z = -D3DX_PI;
								g_bRotFin = true;
							}
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType == CARD_POS_RIGHT)
						{// 相手カードの右端以外を裏にする
							g_aCardModel1P[nCntModel].rot.z += ROT_SPEED;
							if (g_aCardModel1P[nCntModel].rot.z >= -D3DX_PI)
							{
								g_aCardModel1P[nCntModel].rot.z = -D3DX_PI;
								g_bRotFin = true;
							}
						}
					}
					if (bReady == false)
					{
						SetReady(false);
						if (g_aCardModel2P[nCntModel].side == CARD_SIDE_2P)
						{// 自分のカードは全て表にする
							g_aCardModel2P[nCntModel].rot.z = -D3DX_PI * 2;
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType == CARD_POS_RIGHT)
						{// 相手カードの右端以外を裏にする
							g_aCardModel1P[nCntModel].rot.z = -D3DX_PI * 2;
						}
						if (g_aCardModel1P[nCntModel].side == CARD_SIDE_1P && g_aCardModel1P[nCntModel].PosType != CARD_POS_RIGHT)
						{// 相手カードの右端以外を裏にする
							g_aCardModel1P[nCntModel].rot.z = D3DX_PI * 2;
						}
					}
					if (g_bRotFin == true)
					{
						if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A))
						{// カードを山札に戻す(交換)
							PlaySound(SOUND_LABEL_SE_CARD_SELECT);
							ChangeCard2P();
							pTimer->nTime = 0;
						}
					}
				}
			}
		}
		if (pTimer->nTime == 0)
		{// 制限時間になったら
			g_nFadeCnt++;
			if (pTimer->bFinish == false)
			{
				if (g_PokerState == CARD_SIDE_1P)
				{
					ChangeCard1P();					// カードを山札に戻す
					ExchangeCard1P();				// カード交換
					CheckHand1P();					// 役確認
					CheckType1P();					// タイプ確認
					WriteText1P();					// タイプ保存
				}
				else if (g_PokerState == CARD_SIDE_2P)
				{
					ChangeCard2P();					// カードを山札に戻す
					ExchangeCard2P();				// カード交換
					CheckHand2P();					// 役確認
					CheckType2P();					// タイプ確認
					WriteText2P();					// タイプ保存
				}
				pTimer->bFinish = true;
			}
			g_nSelectCard = 0;
			if (g_nFadeCnt >= AUTO_FADE_TIME)
			{
				switch (g_PokerState)
				{
				case CARD_SIDE_1P:
					if (pGameFade == GAMEFADE_NONE)
					{
						SetPokerFade(CARD_SIDE_2P);
					}
					break;
				case CARD_SIDE_2P:
					if (pGameFade == GAMEFADE_IN)
					{
						SetReady(false);
						pTimer->nTime = MAX_TIME;
						pTimer->bFinish = false;
						g_bRotFin = false;
						g_nFadeCnt = 0;
					}
					if (pGameFade == GAMEFADE_NONE)
					{// プレイヤー表示画面へ遷移
						SetGameFade(GAMEMODE_PLAYERSHOW);
					}
					break;
				}
			}
		}
	}
	if (GameMode == GAMEMODE_PLAYERSHOW)
	{
		for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
		{
			if (g_aCardModel1P[nCntModel].pos.x > g_aCardModel1P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel1P[nCntModel].pos.x < g_aCardModel1P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel1P[nCntModel].pos.z > g_aCardModel1P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel1P[nCntModel].pos.z < g_aCardModel1P[nCntModel].DestPos.z + WIDTH)
			{// カードの判定
				g_aCardModel1P[nCntModel].bMove = false;
			}
			if (g_aCardModel2P[nCntModel].pos.x > g_aCardModel2P[nCntModel].DestPos.x - WIDTH &&
				g_aCardModel2P[nCntModel].pos.x < g_aCardModel2P[nCntModel].DestPos.x + WIDTH &&
				g_aCardModel2P[nCntModel].pos.z > g_aCardModel2P[nCntModel].DestPos.z - WIDTH &&
				g_aCardModel2P[nCntModel].pos.z < g_aCardModel2P[nCntModel].DestPos.z + WIDTH)
			{// カードの判定
				g_aCardModel2P[nCntModel].bMove = false;
			}
			// 位置更新
			if (g_aCardModel1P[nCntModel].bMove == true)
			{
				g_aCardModel1P[nCntModel].pos += g_aCardModel1P[nCntModel].move;
			}
			if (g_aCardModel2P[nCntModel].bMove == true)
			{
				g_aCardModel2P[nCntModel].pos += g_aCardModel2P[nCntModel].move;
			}
			g_aCardModel1P[nCntModel].rot.z = D3DX_PI;
			g_aCardModel2P[nCntModel].rot.z += ROT_SPEED;
			if (g_aCardModel2P[nCntModel].rot.z >= -D3DX_PI)
			{
				g_aCardModel2P[nCntModel].rot.z = -D3DX_PI;
			}
		}
		g_CardDeck.bUse = false;
		PlayerShowSetCard1P();
		PlayerShowSetCard2P();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawCardModel(void)
{
	MODE Mode = GetMode();
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアル保存用
	D3DXMATERIAL *pMat;						//マテリアルデータへのポインタ

											/* カード本体の描画 */
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aCardModel1P[nCntModel].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCardModel1P[nCntModel].rot.y, g_aCardModel1P[nCntModel].rot.x, g_aCardModel1P[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aCardModel1P[nCntModel].mtxWorld, &g_aCardModel1P[nCntModel].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_aCardModel1P[nCntModel].pos.x, g_aCardModel1P[nCntModel].pos.y, g_aCardModel1P[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aCardModel1P[nCntModel].mtxWorld, &g_aCardModel1P[nCntModel].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aCardModel1P[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_apCardModel[g_aCardModel1P[nCntModel].ModelType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_aCardModel1P[nCntModel].ModelType].nNumMat; nCntMat++)
			{
				if (g_aCardModel1P[nCntModel].bUse == true)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの描画
					pDevice->SetTexture(0, g_apCardModel[g_aCardModel1P[nCntModel].type].pTextureModel[nCntMat]);

					// モデル(パーツ)の描画
					g_apCardModel[g_aCardModel1P[nCntModel].ModelType].pMesh->DrawSubset(nCntMat);
				}
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aCardModel2P[nCntModel].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aCardModel2P[nCntModel].rot.y, g_aCardModel2P[nCntModel].rot.x, g_aCardModel2P[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aCardModel2P[nCntModel].mtxWorld, &g_aCardModel2P[nCntModel].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_aCardModel2P[nCntModel].pos.x, g_aCardModel2P[nCntModel].pos.y, g_aCardModel2P[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aCardModel2P[nCntModel].mtxWorld, &g_aCardModel2P[nCntModel].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aCardModel2P[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_apCardModel[g_aCardModel2P[nCntModel].ModelType].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_aCardModel2P[nCntModel].ModelType].nNumMat; nCntMat++)
			{
				if (g_aCardModel2P[nCntModel].bUse == true)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの描画
					pDevice->SetTexture(0, g_apCardModel[g_aCardModel2P[nCntModel].type].pTextureModel[nCntMat]);

					// モデル(パーツ)の描画
					g_apCardModel[g_aCardModel2P[nCntModel].ModelType].pMesh->DrawSubset(nCntMat);

				}
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}

	/* 山札の描画 */
	if (g_CardDeck.bUse == true)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_CardDeck.mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_CardDeck.rot.y, g_CardDeck.rot.x, g_CardDeck.rot.z);
		D3DXMatrixMultiply(&g_CardDeck.mtxWorld, &g_CardDeck.mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_CardDeck.pos.x, g_CardDeck.pos.y, g_CardDeck.pos.z);
		D3DXMatrixMultiply(&g_CardDeck.mtxWorld, &g_CardDeck.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_CardDeck.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_apCardModel[g_CardDeck.ModelType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_apCardModel[g_CardDeck.ModelType].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの描画
			pDevice->SetTexture(0, g_apCardModel[g_CardDeck.ModelType].pTextureModel[nCntMat]);

			// モデル(パーツ)の描画
			g_apCardModel[g_CardDeck.ModelType].pMesh->DrawSubset(nCntMat);
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// 1P2P切り替え
//=============================================================================
void SetSide(CARDSIDE side)
{
	g_PokerState = side;
}
//=============================================================================
// カードセット
//=============================================================================
void SetCardModel1P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side)
{
	GAMEMODE GameMode = GetGameMode();
	int nRandType = 0;
	// マテリアルデータへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bUse == false)
		{
			g_aCardModel1P[nCntModel].pos = pos;				// ポジション
			if (GameMode == GAMEMODE_POKER)
			{
				g_aCardModel1P[nCntModel].PosType = CardPos;		// カードのポジション
				g_aCardModel1P[nCntModel].DestPos = g_aDestCard1P[g_aCardModel1P[nCntModel].PosType]; //目的
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel1P[nCntModel].PosType = CardPos;		// カードのポジション
				g_aCardModel1P[nCntModel].DestPos = g_aShowCard1P[g_aCardModel1P[nCntModel].PosType]; //目的
			}
			g_aCardModel1P[nCntModel].side = side;
			//　距離をだす
			g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;

			g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
			g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;

			g_aCardModel1P[nCntModel].bUse = true;
			g_aCardModel1P[nCntModel].bMove = true;
			if (GameMode == GAMEMODE_POKER)
			{
#if 1
				nRandType = rand() % MAX_CARD;	// ランダム
				if (nRandType == 0)
				{
					nRandType = 1;
				}
				if (nRandType >= 1 && nRandType <= 13)
				{
					g_aCardModel1P[nCntModel].type = TYPE_BRAVE;
					g_nNumBrave1P++;
				}
				else if (nRandType >= 14 && nRandType <= 26)
				{
					g_aCardModel1P[nCntModel].type = TYPE_KING;
					g_nNumKing1P++;
				}
				else if (nRandType >= 27 && nRandType <= 39)
				{
					g_aCardModel1P[nCntModel].type = TYPE_DEVIL;
					g_nNumDevil1P++;
				}
				else if (nRandType >= 40 && nRandType <= 52)
				{
					g_aCardModel1P[nCntModel].type = TYPE_COMMONER;
					g_nNumCommoner1P++;
				}
				else if (nRandType == 53 || nRandType == 54)
				{
					g_aCardModel1P[nCntModel].type = TYPE_JOKER;
					g_nNumJoker1P++;
				}
#endif
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel1P[nCntModel].type = g_aCardModel1P[nCntModel].type;
			}
			break;
		}
	}
}
//=============================================================================
// カードセット
//=============================================================================
void SetCardModel2P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side, D3DXVECTOR3 rot)
{
	GAMEMODE GameMode = GetGameMode();
	int nRandType = 0;
	// マテリアルデータへのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bUse == false)
		{
			g_aCardModel2P[nCntModel].pos = pos;				// ポジション
			if (GameMode == GAMEMODE_POKER)
			{
				g_aCardModel2P[nCntModel].PosType = CardPos;		// カードのポジション
				g_aCardModel2P[nCntModel].DestPos = g_aDestCard2P[g_aCardModel2P[nCntModel].PosType]; //目的
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel2P[nCntModel].PosType = CardPos;		// カードのポジション
				g_aCardModel2P[nCntModel].DestPos = g_aShowCard2P[g_aCardModel2P[nCntModel].PosType]; //目的
			}
			g_aCardModel2P[nCntModel].side = side;
			g_aCardModel2P[nCntModel].rot = rot;
			//　距離をだす
			g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;

			g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
			g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;

			g_aCardModel2P[nCntModel].bUse = true;
			g_aCardModel2P[nCntModel].bMove = true;
			if (GameMode == GAMEMODE_POKER)
			{
#if 1
				nRandType = rand() % MAX_CARD;	// ランダム
				if (nRandType == 0)
				{
					nRandType = 1;
				}
				if (nRandType >= 1 && nRandType <= 13)
				{
					g_aCardModel2P[nCntModel].type = TYPE_BRAVE;
					g_nNumBrave2P++;
				}
				else if (nRandType >= 14 && nRandType <= 26)
				{
					g_aCardModel2P[nCntModel].type = TYPE_KING;
					g_nNumKing2P++;
				}
				else if (nRandType >= 27 && nRandType <= 39)
				{
					g_aCardModel2P[nCntModel].type = TYPE_DEVIL;
					g_nNumDevil2P++;
				}
				else if (nRandType >= 40 && nRandType <= 52)
				{
					g_aCardModel2P[nCntModel].type = TYPE_COMMONER;
					g_nNumCommoner2P++;
				}
				else if (nRandType == 53 || nRandType == 54)
				{
					g_aCardModel2P[nCntModel].type = TYPE_JOKER;
					g_nNumJoker2P++;
				}
#endif
			}
			if (GameMode == GAMEMODE_PLAYERSHOW)
			{
				g_aCardModel2P[nCntModel].type = g_aCardModel2P[nCntModel].type;
			}
			break;
		}
	}
}
//=============================================================================
// カードの配置
//=============================================================================
void SetCard(void)
{
	if (g_bSet == false)
	{
		g_nSetCnt++;
		if (g_nSetCnt == 1)
		{
			SetDeckCard(DECK_POS);
		}
		if (g_nSetCnt == 60)
		{
			SetCardModel1P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 120)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 180)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 240)
		{
			SetCardModel1P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 300)
		{
			SetCardModel1P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_1P);
			SetCardModel2P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			PlaySound(SOUND_LABEL_SE_CARD_SET);
		}
		if (g_nSetCnt == 360)
		{
			g_bSet = true;
			g_nSetCnt = 0;
		}
	}
}
//=============================================================================
// プレイヤー表示時のカードのセット (1P)
//=============================================================================
void PlayerShowSetCard1P(void)
{
	LoadText1P();
	SetCardModel1P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_1P);
	SetCardModel1P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_1P);
}
//=============================================================================
// プレイヤー表示時のカードのセット (2P)
//=============================================================================
void PlayerShowSetCard2P(void)
{
	LoadText2P();
	SetCardModel2P(DECK_POS, CARD_POS_RIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTERRIGHT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTER, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_CENTERLEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
	SetCardModel2P(DECK_POS, CARD_POS_LEFT, CARD_SIDE_2P, D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f));
}
//=============================================================================
// 山札セット
//=============================================================================
void SetDeckCard(D3DXVECTOR3 pos)
{
	g_CardDeck.pos = pos;		// ポジション
	g_CardDeck.bUse = true;
}
//=============================================================================
// カード選択処理(1P)
//=============================================================================
void SelectCard1P(CARDPOS CardPos)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_bSet == true)
		{
			if (g_aCardModel1P[nCntModel].PosType == CardPos)
			{
				g_aCardModel1P[nCntModel].bMove = true;
				if (g_aCardModel1P[nCntModel].bSelect == false && g_aCardModel1P[nCntModel].bChange == false)
				{// カードが選択されていない && チェンジしていない
				 // 移動させる
					g_aCardModel1P[nCntModel].bSelect = true;
					g_aCardModel1P[nCntModel].DestPos.z += SELECT_POS;
				}
				else if (g_aCardModel1P[nCntModel].bSelect == true)
				{// カードが選択されている
				 // 元の場所に戻す
					g_aCardModel1P[nCntModel].bSelect = false;
					g_aCardModel1P[nCntModel].DestPos.z -= SELECT_POS;
				}
				// 距離を出す
				g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;
				// カードを移動させる
				g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
				g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;
			}
		}
	}
}
//=============================================================================
// カード選択処理(2P)
//=============================================================================
void SelectCard2P(CARDPOS CardPos)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_bSet == true)
		{
			if (g_aCardModel2P[nCntModel].PosType == CardPos)
			{
				g_aCardModel2P[nCntModel].bMove = true;
				if (g_aCardModel2P[nCntModel].bSelect == false && g_aCardModel2P[nCntModel].bChange == false)
				{// カードが選択されていない && チェンジしていない
				 // 移動させる
					g_aCardModel2P[nCntModel].bSelect = true;
					g_aCardModel2P[nCntModel].DestPos.z -= SELECT_POS;
				}
				else if (g_aCardModel2P[nCntModel].bSelect == true)
				{// カードが選択されている
				 // 元の場所に戻す
					g_aCardModel2P[nCntModel].bSelect = false;
					g_aCardModel2P[nCntModel].DestPos.z += SELECT_POS;
				}
				// 距離を出す
				g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;
				// カードを移動させる
				g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
				g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;
			}
		}
	}
}
//=============================================================================
// カードをチェンジする処理 (1P)
//=============================================================================
void ChangeCard1P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bSelect == true)
		{//カードが選ばれているとき
		 // 目的の場所(中心)
			g_aCardModel1P[nCntModel].DestPos = g_ChangePos;
			// 距離をだす
			g_aCardModel1P[nCntModel].distance = g_aCardModel1P[nCntModel].DestPos - g_aCardModel1P[nCntModel].pos;
			// カードを移動させる
			g_aCardModel1P[nCntModel].move.x = g_aCardModel1P[nCntModel].distance.x / 10.0f;
			g_aCardModel1P[nCntModel].move.z = g_aCardModel1P[nCntModel].distance.z / 10.0f;

			g_aCardModel1P[nCntModel].bMove = true;
			g_aCardModel1P[nCntModel].bChange = true;
			g_aCardModel1P[nCntModel].bSelect = false;
			g_aCardModel1P[nCntModel].bUse = false;
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_BRAVE)
			{
				g_nNumBrave1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_KING)
			{
				g_nNumKing1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_DEVIL)
			{
				g_nNumDevil1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_COMMONER)
			{
				g_nNumCommoner1P--;
			}
			if (g_aCardModel1P[nCntModel].bUse == false && g_aCardModel1P[nCntModel].type == TYPE_JOKER)
			{
				g_nNumJoker1P--;
			}
		}
	}
}
//=============================================================================
// カードをチェンジする処理 (2P)
//=============================================================================
void ChangeCard2P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bSelect == true)
		{//カードが選ばれているとき
		 // 目的の場所(中心)
			g_aCardModel2P[nCntModel].DestPos = g_ChangePos;
			// 距離をだす
			g_aCardModel2P[nCntModel].distance = g_aCardModel2P[nCntModel].DestPos - g_aCardModel2P[nCntModel].pos;
			// カードを移動させる
			g_aCardModel2P[nCntModel].move.x = g_aCardModel2P[nCntModel].distance.x / 10.0f;
			g_aCardModel2P[nCntModel].move.z = g_aCardModel2P[nCntModel].distance.z / 10.0f;

			g_aCardModel2P[nCntModel].bMove = true;
			g_aCardModel2P[nCntModel].bChange = true;
			g_aCardModel2P[nCntModel].bSelect = false;
			g_aCardModel2P[nCntModel].bUse = false;
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_BRAVE)
			{
				g_nNumBrave2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_KING)
			{
				g_nNumKing2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_DEVIL)
			{
				g_nNumDevil2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_COMMONER)
			{
				g_nNumCommoner2P--;
			}
			if (g_aCardModel2P[nCntModel].bUse == false && g_aCardModel2P[nCntModel].type == TYPE_JOKER)
			{
				g_nNumJoker2P--;
			}
		}
	}
}
//=============================================================================
// テキスト書き込み処理 (1P)
//=============================================================================
void WriteText1P(void)
{
	// ファイルのポインタ取得
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_1P, "w");
	if (pFile != NULL)
	{// テキストが開けたら
		fprintf(pFile, "キャラ ");
		switch (g_aType[0])
		{
		case TYPE_BRAVE:
			fprintf(pFile, "0\n");
			break;
		case TYPE_DEVIL:
			fprintf(pFile, "1\n");
			break;
		case TYPE_KING:
			fprintf(pFile, "2\n");
			break;
		case TYPE_COMMONER:
			fprintf(pFile, "3\n");
			break;
		case TYPE_GOD:
			fprintf(pFile, "4\n");
			break;
		}
		switch (g_nData[0])
		{
		case 100:
			fprintf(pFile, "役 [ STRONG ZERO ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 10:
			fprintf(pFile, "役 [ フルハウス ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 5:
			fprintf(pFile, "役 [ フラッシュ ]\n");
			g_nStatus1P[STATUS_ATTACK] = 3;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 4:
			fprintf(pFile, "役 [ フォーカード ]\n");
			g_nStatus1P[STATUS_ATTACK] = 2;
			g_nStatus1P[STATUS_DEFENSE] = 3;
			break;
		case 3:
			fprintf(pFile, "役 [ スリーカード ]\n");
			g_nStatus1P[STATUS_ATTACK] = 2;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 2:
			fprintf(pFile, "役 [ ツーペア ]\n");
			g_nStatus1P[STATUS_ATTACK] = 1;
			g_nStatus1P[STATUS_DEFENSE] = 2;
			break;
		case 1:
			fprintf(pFile, "役 [ ワンペア ]\n");
			g_nStatus1P[STATUS_ATTACK] = 1;
			g_nStatus1P[STATUS_DEFENSE] = 1;
			break;
		}
		fprintf(pFile, "攻撃力 %d \n", g_nStatus1P[STATUS_ATTACK]);
		fprintf(pFile, "防御力 %d \n", g_nStatus1P[STATUS_DEFENSE]);
		fprintf(pFile, "回復力 %d \n", g_nNumCommoner1P);
		for (int nCnt = 0; nCnt < MAX_SET_CARD; nCnt++)
		{
			switch (g_aCardModel1P[nCnt].type)
			{
			case TYPE_BRAVE:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_KING:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_DEVIL:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_COMMONER:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			case TYPE_JOKER:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel1P[nCnt].type);
				break;
			}
		}
		fprintf(pFile, "END_SCRIPT\n");
		fclose(pFile);
	}
	else
	{// テキストが開けなかったら

	}
}
//=============================================================================
// テキスト書き込み処理 (2P)
//=============================================================================
void WriteText2P(void)
{
	// ファイルのポインタ取得
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_2P, "w");
	if (pFile != NULL)
	{// テキストが開けたら
		fprintf(pFile, "キャラ ");
		switch (g_aType[1])
		{
		case TYPE_BRAVE:
			fprintf(pFile, "0\n");
			break;
		case TYPE_DEVIL:
			fprintf(pFile, "1\n");
			break;
		case TYPE_KING:
			fprintf(pFile, "2\n");
			break;
		case TYPE_COMMONER:
			fprintf(pFile, "3\n");
			break;
		case TYPE_GOD:
			fprintf(pFile, "4\n");
			break;
		}
		switch (g_nData[1])
		{
		case 100:
			fprintf(pFile, "役 [ STRONG ZERO ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 10:
			fprintf(pFile, "役 [ フルハウス ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 5:
			fprintf(pFile, "役 [ フラッシュ ]\n");
			g_nStatus2P[STATUS_ATTACK] = 3;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 4:
			fprintf(pFile, "役 [ フォーカード ]\n");
			g_nStatus2P[STATUS_ATTACK] = 2;
			g_nStatus2P[STATUS_DEFENSE] = 3;
			break;
		case 3:
			fprintf(pFile, "役 [ スリーカード ]\n");
			g_nStatus2P[STATUS_ATTACK] = 2;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 2:
			fprintf(pFile, "役 [ ツーペア ]\n");
			g_nStatus2P[STATUS_ATTACK] = 1;
			g_nStatus2P[STATUS_DEFENSE] = 2;
			break;
		case 1:
			fprintf(pFile, "役 [ ワンペア ]\n");
			g_nStatus2P[STATUS_ATTACK] = 1;
			g_nStatus2P[STATUS_DEFENSE] = 1;
			break;
		}
		fprintf(pFile, "攻撃力 %d \n", g_nStatus2P[STATUS_ATTACK]);
		fprintf(pFile, "防御力 %d \n", g_nStatus2P[STATUS_DEFENSE]);
		fprintf(pFile, "回復力 %d \n", g_nNumCommoner2P);
		for (int nCnt = 0; nCnt < MAX_SET_CARD; nCnt++)
		{
			switch (g_aCardModel2P[nCnt].type)
			{
			case TYPE_BRAVE:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_KING:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_DEVIL:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_COMMONER:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			case TYPE_JOKER:
				fprintf(pFile, "%d枚目 %d \n", nCnt + 1, g_aCardModel2P[nCnt].type);
				break;
			}
		}
		fprintf(pFile, "END_SCRIPT\n");
		fclose(pFile);
	}
	else
	{// テキストが開けなかったら

	}
}
//=============================================================================
// テキスト読み込み処理 (1P)
//=============================================================================
void LoadText1P(void)
{
	char ReadText[256];			// 読み込んだ文字列を入れておく
	char HeadText[256];			// 比較用
	char DustBox[256];			// 使用しないものを入れておく

								// ファイルのポインタ取得
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_1P, "r");
	if (pFile != NULL)
	{
		while (strcmp(HeadText, "END_SCRIPT") != 0)
		{// "END_SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
			{
				if (strcmp(HeadText, "\n") == 0)
				{// 文字列の先頭が [\n](改行) の場合処理しない
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "1枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[0].type);
				}
				else if (strcmp(HeadText, "2枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[1].type);
				}
				else if (strcmp(HeadText, "3枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[2].type);
				}
				else if (strcmp(HeadText, "4枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[3].type);
				}
				else if (strcmp(HeadText, "5枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel1P[4].type);
				}
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// テキスト読み込み処理 (2P)
//=============================================================================
void LoadText2P(void)
{
	char ReadText[256];			// 読み込んだ文字列を入れておく
	char HeadText[256];			// 比較用
	char DustBox[256];			// 使用しないものを入れておく

								// ファイルのポインタ取得
	FILE *pFile;
	pFile = fopen(LOAD_TEXT_2P, "r");
	if (pFile != NULL)
	{
		while (strcmp(HeadText, "END_SCRIPT") != 0)
		{// "END_SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
			{
				if (strcmp(HeadText, "\n") == 0)
				{// 文字列の先頭が [\n](改行) の場合処理しない
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "1枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[0].type);
				}
				else if (strcmp(HeadText, "2枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[1].type);
				}
				else if (strcmp(HeadText, "3枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[2].type);
				}
				else if (strcmp(HeadText, "4枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[3].type);
				}
				else if (strcmp(HeadText, "5枚目") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &g_aCardModel2P[4].type);
				}
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// 役確認	(1P)
//=============================================================================
void CheckHand1P(void)
{
	if (g_nNumBrave1P == 1 && g_nNumKing1P == 1 && g_nNumDevil1P == 1 && g_nNumCommoner1P == 1 && g_nNumJoker1P == 1)
	{// STRONG　ZERO
		g_nData[0] = 100;
	}
	else if (g_nNumBrave1P == 5 || g_nNumKing1P == 5 || g_nNumDevil1P == 5 || g_nNumCommoner1P == 5)
	{// フラッシュ
		g_nData[0] = 5;
	}
	else if (g_nNumBrave1P == 4 || g_nNumKing1P == 4 || g_nNumDevil1P == 4 || g_nNumCommoner1P == 4)
	{// フォーカード
		g_nData[0] = 4;
	}
	else if (g_nNumBrave1P == 3 || g_nNumKing1P == 3 || g_nNumDevil1P == 3 || g_nNumCommoner1P == 3)
	{// スリーカード
		g_nData[0] = 3;
		if (g_nNumBrave1P == 2 || g_nNumKing1P == 2 || g_nNumDevil1P == 2 || g_nNumCommoner1P == 2)
		{// フルハウス
			g_nData[0] = 10;
		}
	}
	else if (g_nNumBrave1P == 2 || g_nNumKing1P == 2 || g_nNumDevil1P == 2 || g_nNumCommoner1P == 2 || g_nNumJoker1P == 2)
	{// ワンペア
		g_nData[0] = 1;
		if (g_nNumBrave1P == 3 || g_nNumKing1P == 3 || g_nNumDevil1P == 3 || g_nNumCommoner1P == 3)
		{// フルハウス
			g_nData[0] = 10;
		}
	}
	// ツーペア判定
	if (g_nNumBrave1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_BRAVE;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_KING;
		g_bTwoPair1P = true;
	}
	if (g_nNumDevil1P == 2 && g_nNumCommoner1P == 2 && g_bTwoPair1P == false
		|| g_nNumCommoner1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// ランダム
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_BRAVE;
		}
		if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_DEVIL;
		}
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false
		|| g_nNumKing1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// ランダム
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_KING;
		}
		g_bTwoPair1P = true;
	}
	if (g_nNumBrave1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false
		|| g_nNumJoker1P == 2 && g_nNumBrave1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_BRAVE;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false
		|| g_nNumJoker1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_KING;
		g_bTwoPair1P = true;
	}
	if (g_nNumJoker1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumJoker1P == 2 && g_bTwoPair1P == false)
	{
		g_aType[0] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing1P == 2 && g_nNumDevil1P == 2 && g_bTwoPair1P == false
		|| g_nNumDevil1P == 2 && g_nNumKing1P == 2 && g_bTwoPair1P == false)
	{
		g_nTwoRandType = rand() % 2;	// ランダム
		if (g_nTwoRandType == 0)
		{
			g_aType[0] = TYPE_KING;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[0] = TYPE_DEVIL;
		}
		g_bTwoPair1P = true;
	}
	if (g_bTwoPair1P == true)
	{
		g_nData[0] = 2;
	}
}
//=============================================================================
// 役確認	(2P)
//=============================================================================
void CheckHand2P(void)
{
	if (g_nNumBrave2P == 1 && g_nNumKing2P == 1 && g_nNumDevil2P == 1 && g_nNumCommoner2P == 1 && g_nNumJoker2P == 1)
	{// STRONG　ZERO
		g_nData[1] = 100;
	}
	if (g_nNumBrave2P == 5 || g_nNumKing2P == 5 || g_nNumDevil2P == 5 || g_nNumCommoner2P == 5)
	{// フラッシュ
		g_nData[1] = 5;
	}
	if (g_nNumBrave2P == 4 || g_nNumKing2P == 4 || g_nNumDevil2P == 4 || g_nNumCommoner2P == 4)
	{// フォーカード
		g_nData[1] = 4;
	}
	if (g_nNumBrave2P == 3 || g_nNumKing2P == 3 || g_nNumDevil2P == 3 || g_nNumCommoner2P == 3)
	{// スリーカード
		g_nData[1] = 3;
		if (g_nNumBrave2P == 2 || g_nNumKing2P == 2 || g_nNumDevil2P == 2 || g_nNumCommoner2P == 2)
		{// フルハウス
			g_nData[1] = 10;
		}
	}
	if (g_nNumBrave2P == 2 || g_nNumKing2P == 2 || g_nNumDevil2P == 2 || g_nNumCommoner2P == 2)
	{// ワンペア
		g_nData[1] = 1;
		if (g_nNumBrave2P == 3 || g_nNumKing2P == 3 || g_nNumDevil2P == 3 || g_nNumCommoner2P == 3)
		{// フルハウス
			g_nData[1] = 10;
		}
	}
	// ツーペア判定
	if (g_nNumBrave2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_BRAVE;
		g_bTwoPair2P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_KING;
		g_bTwoPair2P = true;
	}
	if (g_nNumDevil2P == 2 && g_nNumCommoner2P == 2)
	{
		g_aType[1] = TYPE_DEVIL;
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumDevil2P == 2)
	{
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_DEVIL;
		}
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumKing2P == 2)
	{
		g_nTwoRandType = rand() % 2;	// ランダム
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_BRAVE;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_KING;
		}
		g_bTwoPair2P = true;
	}
	if (g_nNumBrave2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_BRAVE;
		g_bTwoPair2P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_KING;
		g_bTwoPair2P = true;
	}
	if (g_nNumDevil2P == 2 && g_nNumJoker2P == 2)
	{
		g_aType[1] = TYPE_DEVIL;
		g_bTwoPair1P = true;
	}
	if (g_nNumKing2P == 2 && g_nNumDevil2P == 2)
	{
		g_nTwoRandType = rand() % 2;	// ランダム
		if (g_nTwoRandType == 0)
		{
			g_aType[1] = TYPE_KING;
		}
		else if (g_nTwoRandType == 1)
		{
			g_aType[1] = TYPE_DEVIL;
		}
		g_bTwoPair2P = true;
	}
	if (g_bTwoPair2P == true)
	{
		g_nData[1] = 2;
	}
}
//=============================================================================
// タイプ確認	(1P)
//=============================================================================
void CheckType1P(void)
{
	if (g_bTwoPair1P == false)
	{
		if (g_nData[0] == 10)
		{
			if (g_nNumCommoner1P == 3)
			{
				if (g_nNumBrave1P == 2)
				{
					g_aType[0] = TYPE_BRAVE;
				}
				if (g_nNumKing1P == 2)
				{
					g_aType[0] = TYPE_KING;
				}
				if (g_nNumDevil1P == 2)
				{
					g_aType[0] = TYPE_DEVIL;
				}
			}
			else
			{
				if (g_nNumBrave1P >= g_nNumKing1P && g_nNumBrave1P >= g_nNumDevil1P && g_nNumBrave1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_BRAVE;
				}
				if (g_nNumKing1P >= g_nNumBrave1P && g_nNumKing1P >= g_nNumDevil1P && g_nNumKing1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_KING;
				}
				if (g_nNumDevil1P >= g_nNumBrave1P && g_nNumDevil1P >= g_nNumKing1P && g_nNumDevil1P >= g_nNumCommoner1P)
				{
					g_aType[0] = TYPE_DEVIL;
				}
			}
		}
		if (g_nData[0] != 10)
		{
			if (g_nNumBrave1P >= g_nNumKing1P && g_nNumBrave1P >= g_nNumDevil1P && g_nNumBrave1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_BRAVE;
			}
			if (g_nNumKing1P >= g_nNumBrave1P && g_nNumKing1P >= g_nNumDevil1P && g_nNumKing1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_KING;
			}
			if (g_nNumDevil1P >= g_nNumBrave1P && g_nNumDevil1P >= g_nNumKing1P && g_nNumDevil1P >= g_nNumCommoner1P)
			{
				g_aType[0] = TYPE_DEVIL;
			}
			if (g_nNumCommoner1P >= g_nNumBrave1P && g_nNumCommoner1P >= g_nNumKing1P && g_nNumCommoner1P >= g_nNumDevil1P)
			{
				g_aType[0] = TYPE_COMMONER;
			}
			if (g_nNumBrave1P == 1 && g_nNumKing1P == 1 && g_nNumDevil1P == 1 && g_nNumCommoner1P == 1 && g_nNumJoker1P == 1)
			{
				g_aType[0] = TYPE_GOD;
			}
		}
	}
}
//=============================================================================
// タイプ確認	(2P)
//=============================================================================
void CheckType2P(void)
{
	if (g_bTwoPair2P == false)
	{
		if (g_nData[1] == 10)
		{
			if (g_nNumCommoner2P == 3)
			{
				if (g_nNumBrave2P == 2)
				{
					g_aType[1] = TYPE_BRAVE;
				}
				if (g_nNumKing2P == 2)
				{
					g_aType[1] = TYPE_KING;
				}
				if (g_nNumDevil2P == 2)
				{
					g_aType[1] = TYPE_DEVIL;
				}
			}
			else
			{
				if (g_nNumBrave2P >= g_nNumKing2P && g_nNumBrave2P >= g_nNumDevil2P && g_nNumBrave2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_BRAVE;
				}
				if (g_nNumKing2P >= g_nNumBrave2P && g_nNumKing2P >= g_nNumDevil2P && g_nNumKing2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_KING;
				}
				if (g_nNumDevil2P >= g_nNumBrave2P && g_nNumDevil2P >= g_nNumKing2P && g_nNumDevil2P >= g_nNumCommoner2P)
				{
					g_aType[1] = TYPE_DEVIL;
				}
			}
		}
		if (g_nData[1] != 10)
		{
			if (g_nNumBrave2P >= g_nNumKing2P && g_nNumBrave2P >= g_nNumDevil2P && g_nNumBrave2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_BRAVE;
			}
			if (g_nNumKing2P >= g_nNumBrave2P && g_nNumKing2P >= g_nNumDevil2P && g_nNumKing2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_KING;
			}
			if (g_nNumDevil2P >= g_nNumBrave2P && g_nNumDevil2P >= g_nNumKing2P && g_nNumDevil2P >= g_nNumCommoner2P)
			{
				g_aType[1] = TYPE_DEVIL;
			}
			if (g_nNumCommoner2P >= g_nNumBrave2P && g_nNumCommoner2P >= g_nNumKing2P && g_nNumCommoner2P >= g_nNumDevil2P)
			{
				g_aType[1] = TYPE_COMMONER;
			}
			if (g_nNumBrave2P == 1 && g_nNumKing2P == 1 && g_nNumDevil2P == 1 && g_nNumCommoner2P == 1 && g_nNumJoker2P == 1)
			{
				g_aType[1] = TYPE_GOD;
			}
		}
	}
}
//=============================================================================
// カード交換 (1P)
//=============================================================================
void ExchangeCard1P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel1P[nCntModel].bChange == true)
		{
			g_aCardModel1P[nCntModel].bMove = true;
			g_aCardModel1P[nCntModel].bChange = false;
			g_aCardModel1P[nCntModel].bSelect = false;
			g_aCardModel1P[nCntModel].bUse = false;
			SetCardModel1P(DECK_POS, CARDPOS(nCntModel), CARD_SIDE_1P);
		}
	}
}
//=============================================================================
// カード交換 (2P)
//=============================================================================
void ExchangeCard2P(void)
{
	for (int nCntModel = 0; nCntModel < MAX_SET_CARD; nCntModel++)
	{
		if (g_aCardModel2P[nCntModel].bChange == true)
		{
			g_aCardModel2P[nCntModel].bMove = true;
			g_aCardModel2P[nCntModel].bChange = false;
			g_aCardModel2P[nCntModel].bSelect = false;
			g_aCardModel2P[nCntModel].bUse = false;
			SetCardModel2P(DECK_POS, CARDPOS(nCntModel), CARD_SIDE_2P, D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));
		}
	}
}
//=============================================================================
// カーソル移動
//=============================================================================
void MoveCursor(void)
{
	if (g_bSet == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true || GetGamePadPovPress(g_nNowPlayer,POV_RIGHT) || GetGamePadStickPress(g_nNowPlayer,STICK_RIGHT))
		{
			g_nPressCnt++;
			if (g_nPressCnt % PRESS_CNT == 0)
			{
				g_nSelectCard = (g_nSelectCard + 1) % (CARD_POS_MAX - 1);
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetGamePadPovPress(g_nNowPlayer, POV_LEFT) || GetGamePadStickPress(g_nNowPlayer, STICK_LEFT))
		{
			g_nPressCnt++;
			if (g_nPressCnt % PRESS_CNT == 0)
			{
				g_nSelectCard = (g_nSelectCard + 3) % (CARD_POS_MAX - 1);
			}
		}
		if (GetKeyboardTrigger(DIK_RIGHT) == true || GetGamePadPovTrigger(g_nNowPlayer, POV_RIGHT) || GetGamePadStickTrigger(g_nNowPlayer, STICK_RIGHT))
		{
			g_nSelectCard = (g_nSelectCard + 1) % (CARD_POS_MAX - 1);
		}
		else if (GetKeyboardTrigger(DIK_LEFT) == true || GetGamePadPovTrigger(g_nNowPlayer, POV_LEFT) || GetGamePadStickTrigger(g_nNowPlayer, STICK_LEFT))
		{
			g_nSelectCard = (g_nSelectCard + 3) % (CARD_POS_MAX - 1);
		}
		if (GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true
			|| GetGamePadPovRelease(g_nNowPlayer, POV_RIGHT) || GetGamePadPovRelease(g_nNowPlayer, POV_LEFT)
			|| GetGamePadStickRelease(g_nNowPlayer,STICK_RIGHT) ||  GetGamePadStickRelease(g_nNowPlayer, STICK_LEFT))
		{
			g_nPressCnt = 0;
		}
	}
}
//=============================================================================
// モデル読み込み
//=============================================================================
void LoadModel(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXLoadMeshFromX(MODEL_CARD,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_apCardModel[0].pBuffMat,
		NULL,
		&g_apCardModel[0].nNumMat,
		&g_apCardModel[0].pMesh);

	D3DXCreateTextureFromFile(pDevice, TEX_BRAVE, g_apCardModel[TYPE_BRAVE].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_KING, g_apCardModel[TYPE_KING].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_DEVIL, g_apCardModel[TYPE_DEVIL].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_JOKER, g_apCardModel[TYPE_JOKER].pTextureModel);
	D3DXCreateTextureFromFile(pDevice, TEX_HEART, g_apCardModel[TYPE_COMMONER].pTextureModel);
}
//=============================================================================
// ガイド表示に使うもの
//=============================================================================
int GetNum(void)
{// 選ばれているカードの番号
	return g_nSelectCard;
}
int GetHandNum(int nNowPlayer)
{// 役判定で使う値
	return g_nData[nNowPlayer];
}
CARDTYPE GetType(int nNowPlayer)
{// タイプ確認
	return g_aType[nNowPlayer];
}
CARDTYPE Get1PHand(int nIndex)
{// 5枚の中身
	return g_aCardModel1P[nIndex].type;
}
CARDTYPE Get2PHand(int nIndex)
{// 5枚の中身
	return g_aCardModel2P[nIndex].type;
}
bool GetSet(void)
{// カードが配置されたか
	return g_bSet;
}
/* カーソルの位置をカードに合わせる */
D3DXVECTOR3 GetCardPos1P(int nSelectNum)
{// 1P
	return g_aCardModel1P[nSelectNum].pos;
}
D3DXVECTOR3 GetCardPos2P(int nSelectNum)
{// 2P
	return g_aCardModel2P[nSelectNum].pos;
}
CARDSIDE GetPokerState(void)
{// ポーカーの状況
	return g_PokerState;
}
D3DXVECTOR3 GetLockPos1P(int nNumber)
{// 1P 右のカード上にロックマークをつける
	return g_aDestCard1P[nNumber];
}
D3DXVECTOR3 GetLockPos2P(int nNumber)
{// 2P 左のカード上にロックマークをつける
	return g_aDestCard2P[nNumber];
}
int GetNowPlayer(void)
{
	return g_nNowPlayer;
}