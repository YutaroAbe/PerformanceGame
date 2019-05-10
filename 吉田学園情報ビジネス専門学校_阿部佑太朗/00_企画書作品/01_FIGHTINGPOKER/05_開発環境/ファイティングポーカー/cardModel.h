//=============================================================================
//
// モデル処理 [model.h]
// Author : 舘田 翼
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MODEL_TEX	(60)
#define MAX_PLAYER		(2)							// プレイヤーの最大数
#define LOAD_TEXT_1P	"data/TEXT/1PInfo.txt"		// 1Pの情報格納テキスト
#define LOAD_TEXT_2P	"data/TEXT/2PInfo.txt"		// 2Pの情報格納テキスト
//=============================================================================
// 列挙型定義(カードの種類)
//=============================================================================
typedef enum
{
	TYPE_BRAVE = 0,
	TYPE_KING,
	TYPE_DEVIL,
	TYPE_JOKER,
	TYPE_COMMONER,
	TYPE_GOD,
	TYPE_MAX
}CARDTYPE;

//=============================================================================
//構造体定義
//=============================================================================
typedef enum
{
	STATUS_ATTACK = 0,
	STATUS_DEFENSE,
	STATUS_MAX
}PARAM;

typedef enum
{
	CARD_SET = 0,
	CARD_DECK,
	CARD_ENUM_MAX
}POSENUM;
typedef enum
{
	CARD_POS_LEFT = 0,			// 左
	CARD_POS_CENTERLEFT,		// センター左
	CARD_POS_CENTER,			// センター
	CARD_POS_CENTERRIGHT,		// 右
	CARD_POS_RIGHT,				// センター右
	CARD_POS_MAX
}CARDPOS;

typedef enum
{
	CARD_SIDE_1P,			// 1P
	CARD_SIDE_2P,			// 2P
	CARD_SIDE_ALL,			// 1Pと2P終了後
	CARD_SIDE_MAX,
}CARDSIDE;

typedef struct
{
	D3DXVECTOR3 pos;		// 位
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 move;		// 移動量
	int			ModelType;	// モデルタイプ
	D3DXMATRIX  mtxWorld;	// マトリックスワールド
	bool		bUse;       // 使用しているかどうか
	CARDPOS		PosType;	// カードのポジション
	D3DXVECTOR3 DestPos;	// 目的の位置
	D3DXVECTOR3 distance;	// 距離
	bool		bMove;		// 動いてるか
	bool		bSelect;	// 選ばれてるか
	bool		bChange;	// チェンジしているか
	bool		bSet;		// セットされたかどうか
	CARDTYPE type;			// カードの種類
	CARDSIDE side;			// ゲームの状態
} CardModel;

typedef struct
{
	D3DXVECTOR3			vtxMin;
	D3DXVECTOR3			vtxMax;
	LPD3DXMESH			pMesh;
	LPD3DXBUFFER		pBuffMat;
	DWORD				nNumMat;
	LPDIRECT3DTEXTURE9  pTextureModel[MAX_MODEL_TEX];	// モデル一体に対するテクスチャ
}CardData;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCardModel(void);
void UninitCardModel(void);
void UpdateCardModel(void);
void DrawCardModel(void);
void PlayerShowSetCard1P(void);
void PlayerShowSetCard2P(void);
void SetSide(CARDSIDE side);
void SetCard(void);														// 1P・2P・山札全てのカードを配置する
void SetCardModel1P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side);	// 1Pのカード設定
void SelectCard1P(CARDPOS CardPos);										// カードを選ぶ処理
void ChangeCard1P(void);												// 選んだカードを山札に動かす処理
void CheckHand1P(void);													// 役確認
void CheckType1P(void);													// タイプ確認
void WriteText1P(void);													// 手札を記憶する
void ExchangeCard1P(void);												// カードの交換
void LoadText1P(void);
void LoadText2P(void);
D3DXVECTOR3 GetCardPos1P(int nSelectNum);								// 1Pの位置情報取得用
CARDTYPE Get1PHand(int nIndex);											// 1Pの手札確認用
void SetCardModel2P(D3DXVECTOR3 pos, CARDPOS CardPos, CARDSIDE side, D3DXVECTOR3 rot);	// 2Pのカード設定
void SelectCard2P(CARDPOS CardPos);										// カードを選ぶ処理
void ChangeCard2P(void);												// 選んだカードを山札に動かす処理
void CheckHand2P(void);													// 役確認
void CheckType2P(void);													// タイプ確認
void WriteText2P(void);													// 手札を記憶する
void ExchangeCard2P(void);												// カードの交換
void LoadText2P(void);
D3DXVECTOR3 GetCardPos2P(int nSelectNum);								// 2Pの位置情報取得用
CARDTYPE Get2PHand(int nIndex);											// 2Pの手札確認用
void SetDeckCard(D3DXVECTOR3 pos);										// 山札の設定
void MoveCursor(void);													// カーソル移動
void LoadModel(LPDIRECT3DDEVICE9 pDevice);								// モデルとテクスチャの読み込み
int GetNum(void);
int GetHandNum(int nNowPlayer);
CARDTYPE GetType(int nNowPlayer);
CARDSIDE GetPokerState(void);
D3DXVECTOR3 GetLockPos1P(int nNumber);
D3DXVECTOR3 GetLockPos2P(int nNumber);
int GetNowPlayer(void);
bool GetSet(void);
#endif

