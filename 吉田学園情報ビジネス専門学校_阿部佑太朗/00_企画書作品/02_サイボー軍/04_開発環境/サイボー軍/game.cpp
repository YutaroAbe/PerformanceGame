//=============================================================================
//
// ゲーム処理 [main.cpp]
// Author :
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "sound.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "game.h"
#include "life.h"
#include "time.h"
#include "fade.h"
#include "block.h"
#include "item.h"
#include "pause.h"
#include "input.h"
#include "missionmessage.h"
#include "enemycount.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
CGame::GAMESTATE CGame::m_GameState = GAMESTATE_NONE;
CGame::SETSTEGEMODE CGame::m_SetStageMode = SETSTEGEMODE_001;
CPlayer *CGame::m_pPlayer = NULL;							//	プレイヤーの初期化
bool CGame::m_bPause = false;								//	ポーズの状態の初期化
int CGame::m_nEnemyCount = NULL;							//	敵の数の初期化
D3DXVECTOR3 CGame::m_EnemyPos[EMEMY_NUM_MAX] = {};			//	敵のポジションの初期化
int CGame::m_nEnemyType[EMEMY_NUM_MAX] = {};				//	敵の種類の初期化
int CGame::m_nEnemyLife[EMEMY_NUM_MAX] = {};				//	敵の種類の初期化
int CGame::m_nItemCount = NULL;								//	アイテムの初期化
D3DXVECTOR3 CGame::m_ItemPos[ITEM_NUM_MAX] = {};			//	アイテムのポジションの初期化
int CGame::m_nItemType[ITEM_NUM_MAX] = {};					//	アイテムの種類の初期化
int CGame::m_nBlockCount = NULL;							//	ブロックの初期化
D3DXVECTOR3 CGame::m_BlockPos[ITEM_NUM_MAX] = {};			//	ブロックのポジションの初期化
int CGame::m_nBlockType[ITEM_NUM_MAX] = {};					//	ブロックの種類の初期化
float CGame::m_fBlockfWindth[BLOCK_NUM_MAX] = {};			//	ブロックの幅
float CGame::m_fBlockfHeight[BLOCK_NUM_MAX] = {};			//	ブロックの高さ
float CGame::m_fBlockTexSplitX[BLOCK_NUM_MAX] = {};			//	ブロックのテクスチャの分割数X軸
float CGame::m_fBlockTexSplitY[BLOCK_NUM_MAX] = {};			//	ブロックのテクスチャの分割数Y軸

//=============================================================================
//コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_nCounterState = NULL;
}
//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	switch (m_SetStageMode)
	{
	case SETSTEGEMODE_000:
		LoadSetTutorial();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		break;
	case SETSTEGEMODE_001:
		LoadSetGame();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_STAGE1);
		break;
	case SETSTEGEMODE_002:
		LoadSetGameStage2();
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_STAGE2);
		break;
	}
	//　エフェクトのテクスチャの開放
	CEffect::Laod();
	//	フェイドのテクスチャの読み込み
	CFade::Laod();
	//	数女のテクスチャの読み込み
	CNumber::Laod();
	//	ブロックのテクスチャ読み込み
	CBlock::Laod();
	//	弾のテクスチャの読み込み
	CBullet::Laod();
	//	爆発のテクスチャの読み込み
	CExplosion::Laod();
	//	敵のテクスチャの読み込み
	CEnemy::Laod();
	//	プレイヤーのテクスチャの読み込み
	CPlayer::Laod();
	//	背景のテクスチャ読み込み
	CBg::Laod();
	//　体力のテクスチャ読み込み
	CLife::Laod();
	//	アイテムのテクスチャ読み込み
	CItem::Laod();
	//	ポーズのテクスチャの読み込み
	CPause::Load();
	//　背景の生成
	CBg::Create();
	//	スコアの生成
	CScore::Create();

	//	タイマーの生成
	CTime::Create();
	//	プレイヤーの生成
	m_pPlayer->Create(D3DXVECTOR3(600.0f, 500.0f, 0.0f));
	//	ライフの設定
	CLife::Create(D3DXVECTOR3(90.0f, 44.0f, 0.0f), D3DXVECTOR3(11.8f, 13.8f, 0.0f));
	//	エネミーの総数
	CEnemycount::Create();
	//	敵の生成
	for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
	{
		CEnemy::Create(D3DXVECTOR3(m_EnemyPos[nCount].x, m_EnemyPos[nCount].y, m_EnemyPos[nCount].z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nEnemyLife[nCount], m_nEnemyType[nCount]);
	}

	//アイテムの生成
	for (int nCount = 0; nCount < m_nItemCount; nCount++)
	{
		CItem::Create(D3DXVECTOR3(m_ItemPos[nCount].x, m_ItemPos[nCount].y, m_ItemPos[nCount].z), m_nItemType[nCount]);
	}
	//	ブロックの生成
	for (int nCount = 0; nCount < m_nBlockCount; nCount++)
	{
		CBlock::Create(D3DXVECTOR3(m_BlockPos[nCount].x, m_BlockPos[nCount].y, m_BlockPos[nCount].z),
		m_fBlockfWindth[nCount], m_fBlockfHeight[nCount], m_nBlockType[nCount], m_fBlockTexSplitX[nCount], m_fBlockTexSplitY[nCount]);	//位置/動き/幅/高さ/種類/テクスチャ分割X/テクスチャ分割Y
	}
	//	PAUSEの生成
	CPause::Create();

	//ポーズの状態の初期化
	m_bPause = false;

	m_GameState = GAMESTATE0_NORMAL;
	m_nCounterState = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//	プレイヤーのテクスチャの開放
	CPlayer::UnLoad();
	//	敵のテクスチャ開放
	CEnemy::UnLoad();
	//	爆発のテクスチャの開放
	CExplosion::UnLoad();
	//	弾のテクスチャの開放
	CBullet::UnLoad();
	//　数字のテクスチャ開放
	CNumber::UnLoad();
	//	背景のテクスチャの開放
	CBg::UnLoad();
	//　エフェクトのテクスチャの開放
	CEffect::UnLoad();
	//　体力のテクスチャ開放
	CLife::UnLoad();
	//	ブロックの開放
	CBlock::UnLoad();
	//	アイテムの開放
	CItem::UnLoad();
	//	ポーズの開放
	CPause::UnLoad();
	//すべてのポリゴンの開放
	CScene::ReleaseAll();

	CSound::StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_STAGE1);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_STAGE2);
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetGamePadTrigger(BUTTON_START)==true)
	{// ポーズを true false 切り替える
		CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
		m_bPause = m_bPause ? false : true;
	}


	switch (m_GameState)
	{
	case GAMESTATE0_NORMAL:
		break;
	case GAMESTATE_END:
		m_nCounterState++;
		if (m_nCounterState >= 20)
		{
			m_GameState = GAMESTATE_NONE;
		}
		break;
	case GAMESTATE_CLEAR:
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{
			if (pFade->m_fade == pFade->FADE_NONE && m_SetStageMode != SETSTEGEMODE_000)
			{
				pFade->SetFade(CManager::MODE_RESULT);
			}
		}
		break;
	}

		int nNumEnemy = CEnemy::GetNUMENEMY();
		if (nNumEnemy <= 0)
		{//	エネミーを総数分倒したらゲームクリア
			m_GameState = GAMESTATE_CLEAR;
		}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_GameState;
}

//=============================================================================
//	ポーズの状態の取得
//=============================================================================
bool CGame::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
//	ポーズの状態の設定
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;
}
//=============================================================================
//	ゲームのオブジェクトの設置
//=============================================================================
void CGame::LoadSetTutorial(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage0.txt", "r");

	if (pFile != NULL)
	{//	ファイルが開けた場合

	 //	数の設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// エネミーの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// アイテムの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// ブロックの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	文字列　/　数　/　文字列
		}

		//	エネミーの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	エネミーの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	エネミーの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	エネミーの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	エネミーの体力の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	アイテムの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	アイテムの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	アイテムの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	アイテムの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	ブロックの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	ブロックの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	ブロックの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	ブロックの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "テキストに問題があります", "警告", MB_OK);
	}
}
//=============================================================================
//	ゲームのオブジェクトの設置
//=============================================================================
void CGame::LoadSetGame(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage1.txt", "r");

	if (pFile != NULL)
	{//	ファイルが開けた場合

		//	数の設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// エネミーの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// アイテムの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// ブロックの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	文字列　/　数　/　文字列
		}

		//	エネミーの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++){fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); }}
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	エネミーの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	エネミーの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	エネミーの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	エネミーの体力の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	アイテムの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	アイテムの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	アイテムの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	アイテムの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	ブロックの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	ブロックの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	ブロックの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	ブロックの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "テキストに問題があります", "警告", MB_OK);
	}
}
//=============================================================================
//	ゲームのオブジェクトの設置
//=============================================================================
void CGame::LoadSetGameStage2(void)
{
	FILE *pFile;
	char read[128];

	pFile = fopen("data/TEXT/gamestage2.txt", "r");

	if (pFile != NULL)
	{//	ファイルが開けた場合

	 //	数の設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		// エネミーの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ENEMY_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nEnemyCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// アイテムの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "ITEM_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nItemCount, &read[0]);	//	文字列　/　数　/　文字列
		}
		// ブロックの数の設定
		fscanf(pFile, "%s", &read[0]);
		if (strcmp(&read[0], "BLOCK_MAX") == 0)
		{
			fscanf(pFile, "%s%d%s", &read[0], &m_nBlockCount, &read[0]);	//	文字列　/　数　/　文字列
		}

		//	エネミーの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nEnemyCount; nCount++)
		{//	エネミーの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ENEMY_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	エネミーの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_EnemyPos[nCount].x, &m_EnemyPos[nCount].y, &m_EnemyPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	エネミーの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyType[nCount]);
					}
					else if (strcmp(&read[0], "LIFE") == 0)
					{//	エネミーの体力の設定
						fscanf(pFile, "%s%d", &read[0], &m_nEnemyLife[nCount]);
					}
				} while (strcmp(&read[0], "ENEMY_END") != 0);

			}
		}
		//	アイテムの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nItemCount; nCount++)
		{//	アイテムの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "ITEM_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	アイテムの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_ItemPos[nCount].x, &m_ItemPos[nCount].y, &m_ItemPos[nCount].z);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	アイテムの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nItemType[nCount]);
					}

				} while (strcmp(&read[0], "ITEM_END") != 0);

			}
		}
		//	ブロックの設定のテキスト上コメントアウト
		for (int nCount = 0; nCount < 3; nCount++) { fscanf(pFile, "%s", &read[0]); if (strcmp(&read[0], "#") == 0) { do { fscanf(pFile, "%c", &read[0]); } while (strcmp(&read[0], "\n") != 0); } }
		for (int nCount = 0; nCount < m_nBlockCount; nCount++)
		{//	ブロックの設定
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "BLOCK_SET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "POS") == 0)
					{//	ブロックの位置の設定
						fscanf(pFile, "%s%f%f%f", &read[0], &m_BlockPos[nCount].x, &m_BlockPos[nCount].y, &m_BlockPos[nCount].z);
					}
					else if (strcmp(&read[0], "WINDTH") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfWindth[nCount]);
					}
					else if (strcmp(&read[0], "HEIGHT") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockfHeight[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_X") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitX[nCount]);
					}
					else if (strcmp(&read[0], "TEXSPLIT_Y") == 0)
					{
						fscanf(pFile, "%s%f", &read[0], &m_fBlockTexSplitY[nCount]);
					}
					else if (strcmp(&read[0], "TYPE") == 0)
					{//	ブロックの種類の設定
						fscanf(pFile, "%s%d", &read[0], &m_nBlockType[nCount]);
					}

				} while (strcmp(&read[0], "BLOCK_END") != 0);

			}
		}
		fclose(pFile);
	}
	else
	{
		MessageBox(0, "テキストに問題があります", "警告", MB_OK);
	}
}
//=============================================================================
//	ステージの選択
//=============================================================================
void CGame::SetStage(SETSTEGEMODE SetStageMode)
{
	m_SetStageMode = SetStageMode;
}

//=============================================================================
//ステージの取得
//=============================================================================
CGame::SETSTEGEMODE CGame::GetStageState(void)
{
	return m_SetStageMode;
}