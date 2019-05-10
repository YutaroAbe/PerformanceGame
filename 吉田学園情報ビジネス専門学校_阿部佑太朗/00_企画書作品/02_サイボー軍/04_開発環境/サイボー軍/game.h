//=============================================================================
//
// ゲームの処理 [manager.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"
#include "player.h"
//=============================================================================
//	マクロ定義
//=============================================================================
#define EMEMY_NUM_MAX (128)
#define ITEM_NUM_MAX (128)
#define	BLOCK_NUM_MAX (128)
//=============================================================================
//	マネージャークラス
//=============================================================================
class CGame
{
public:

	typedef enum
	{
		GAMESTATE_NONE = 0,				//何もしていない
		GAMESTATE0_NORMAL,				//通常状態
		GAMESTATE_END,					//オーバー状態
		GAMESTATE_CLEAR,				//クリア状態
		GAMESTATE_MAX
	}GAMESTATE;

	typedef enum
	{//	ステージのモード設定
		SETSTEGEMODE_000 = 0,	//	チュートリアルステージ
		SETSTEGEMODE_001,		//	ステージ1
		SETSTEGEMODE_002,		//	ステージ2
		SETSTEGEMODE_MAX
	}SETSTEGEMODE;
	CGame();																// コンストラクタ
	~CGame();																// デストラクタ
	 HRESULT Init(void);													// 初期化処理
	 void Uninit(void);														// 終了処理
	 void Update(void);														// 更新処理
	 void Draw(void);														// 描画処理
	static CPlayer *m_pPlayer;												//	プレイヤーのポインタ型
	static bool GetPause(void);												//	ポーズの状態の取得
	static void SetPause(bool bPause);										//	ポーズの状態の設定
	static void LoadSetTutorial(void);										//	チュートリアルのオブジェクトの設置
	static void LoadSetGame(void);											//	ゲームのオブジェクトの設置
	static void LoadSetGameStage2(void);									//	ゲームのオブジェクトの設置[２ステージ目]
	static void SetStage(SETSTEGEMODE SetStageMode);						//	ステージの選択
	static GAMESTATE GetGameState(void);
	static SETSTEGEMODE GetStageState(void);
private:
	static GAMESTATE m_GameState;
	int m_nCounterState;
	static SETSTEGEMODE m_SetStageMode;										//	ステージのモード設定
	static bool m_bPause;
	static int m_nEnemyCount;												//	エネミーの数
	static D3DXVECTOR3 m_EnemyPos[EMEMY_NUM_MAX];							//	エネミーのポジション
	static int m_nEnemyLife[EMEMY_NUM_MAX];									//	エネミーの種類
	static int m_nEnemyType[EMEMY_NUM_MAX];									//	エネミーの種類

	static int m_nItemCount;												//	アイテムの数
	static D3DXVECTOR3 m_ItemPos[ITEM_NUM_MAX];								//	アイテムのポジション
	static int m_nItemType[ITEM_NUM_MAX];									//	アイテムの種類

	static int m_nBlockCount;												//	ブロックの数
	static D3DXVECTOR3 m_BlockPos[BLOCK_NUM_MAX];							//	ブロックのポジション
	static int m_nBlockType[BLOCK_NUM_MAX];									//	ブロックの種類
	static float m_fBlockfWindth[BLOCK_NUM_MAX];							//	ブロックの幅
	static float m_fBlockfHeight[BLOCK_NUM_MAX];							//	ブロックの高さ
	static float m_fBlockTexSplitX[BLOCK_NUM_MAX];							//	ブロックのテクスチャの分割数X軸
	static float m_fBlockTexSplitY[BLOCK_NUM_MAX];							//	ブロックのテクスチャの分割数Y軸
};

#endif // _MANAGER_H_
