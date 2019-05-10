//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "game.h"			//	ゲーム
#include "manager.h"		//	マネージャー
#include "renderer.h"		//	レンダラー
#include "input.h"			//	入力
#include "camera.h"			//	カメラ
#include "fade.h"			//	フェード
#include "player.h"			//	プレイヤー
#include "block.h"			//	ブロック
#include "item.h"			//	アイテム
#include "time.h"			//	タイム
#include "effect.h"			//	エフェクト
#include "item.h"			//	アイテム
#include "3dobject.h"		//	3D背景オブジェクト
#include "floor.h"			//	床
#include "shadow.h"			//	影
#include "UI.h"				//	Ui
#include "number.h"			//	番号
#include "score.h"			//	スコア
#include "wall.h"			//	壁
#include "bulletNumber.h"	//	ライフの数値
#include "effect.h"			//	エフェクト
#include "bullet3D.h"		//	弾3D
#include "enemy.h"			//	敵
#include "hpber3D.h"		//　HPバー3D
#include "bullet2D.h"		//	弾の2D
#include "pause.h"			//	Pause
#include "sound.h"			//	音
#include <iostream>
#include <string>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CFloor *CGame::m_pFloor[MAX_FLOOR] = {};
CEnemy *CGame::m_pEnemy = NULL;
CPause *CGame::m_pPause = NULL;
bool CGame::m_bPause = false;
CGame::STAGETYPE  CGame::m_StageType = STAGE_NONE;		//	ステージ種類
CGame::GAMESTATE CGame::m_GameState = GAMESTATE_NONE;	//	ゲームのステータス
int CGame::m_nOverNum = 0;								//	ゲームオーバーの選択項目
bool CGame::m_bClear = false;							//	クリアしたかどうか
//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	m_pPlayer = NULL;										//	プレイヤー
	for (int nCount = 0; nCount < MAX_FLOOR; nCount++)
	{//	床
		m_pFloor[nCount] = NULL;
	}

	for (int nCountb = 0; nCountb < OBJTYPE_MAX; nCountb++)
	{//	テキストのオブジェクトの種類
		m_textState[nCountb].nCnter = NULL;
		for (int nCount = 0; nCount < OBJ_MAX; nCount++)
		{//	テキストの中身の初期化
			m_textState[nCountb].nType[nCount] = NULL;		//	種類
			m_textState[nCountb].nColType[nCount] = NULL;	//	当たり判定の種類
			m_textState[nCountb].pos[nCount] = {};			//	位置
			m_textState[nCountb].rot[nCount] = {};			//	回転
			m_textState[nCountb].size[nCount] = {};			//	大きさ
			m_textState[nCountb].pVtxFloor[nCount] = {};	//	床の頂点の高さ
			m_textState[nCountb].col[nCount] = {};			//	色
			m_textState[nCountb].uv[nCount] = {};			//	UV
			m_textState[nCountb].nColType[nCount] = {};		//	当たり判定の種類
			m_textState[nCountb].nLife[nCount] = {};		//	種類
			m_textState[nCountb].nAIType[nCount] = {};		//	AIの種類
			m_textState[nCountb].nMoveLength[nCount] = {};	//	動く距離
			m_textState[nCountb].fNoneSpeed[nCount] = {};	//	オブジェクトの通常の速さ
			m_textState[nCountb].fFomSpeed[nCount] = {};	//	オブジェクトの追従するときの速さ
		}
	}
	m_GameState = GAMESTATE0_NORMAL;	//	ゲームの状態
	m_nCounterState = 0;				//	カウンターの初期化
	m_StageType = STAGE_TUTORIAL;		//	ステージの設定
	m_bClear = false;					//	クリアしたかどうか
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(STAGETYPE StageType, int nPlayerLife)
{
	//	エフェクトのテキストの名前の読み込み
	CEffect::LoadNameEffect();			//	エフェクトのテキスト読み込み
	CEffect::LoadDataEffect();			//	エフェクトのデータ読み込み
	CEffect::Load();					//	エフェクトの読み込み
	CPlayer::Load();					//	プレイヤーの読み込み
	CEnemy::Load();						//	プレイヤーの読み込み
	CItem::Load();						//	アイテムの
	CBlock::Load();						//	ブロックの読み込み
	C3Dobject::Load();					//	3Dオブジェクトの読み込み
	CFloor::Load();						//	床の読み込み
	CShadow::Load();					//	影の読み込み
	CNumber::Laod();					//	数の読み込み
	CWall::Load();						//	壁の読み込み
	CBullet3D::Load();					//	弾3Dの読み込み
	CHpBer3D::Load();					//	HPバーの読み込み
	CBullet2D::Load();					//	弾の2Dの読み込み
	m_StageType = StageType;
	switch (m_StageType)
	{
		//-----------------------------------------------------------
		//	チュートリアルステージ
		//------------------------------------------------------------
	case STAGE_TUTORIAL:
		CUI::Load(CManager::MODE_GAMETUTO);				//  Uiの読み込み
		ObjectLoad(STAGE_TUTORIAL);						//	テキスト読み込み
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -1650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300,80);
		CUI::CreateMode(CManager::MODE_GAMETUTO);		//UIの生成
		break;
		//-----------------------------------------------------------
		//	ステージ	1
		//------------------------------------------------------------
	case STAGE_001:
		CUI::Load(CManager::MODE_GAMESTAGE000);			//  Uiの読み込み
		ObjectLoad(STAGE_001);							//	テキスト読み込み
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE000);	//UIの生成
		break;
		//-----------------------------------------------------------
		//	ステージ	2
		//------------------------------------------------------------
	case STAGE_002:
		CUI::Load(CManager::MODE_GAMESTAGE000);			//  Uiの読み込み
		ObjectLoad(STAGE_002);							//	テキスト読み込み
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE000);	//UIの生成
		break;
		//-----------------------------------------------------------
		//	ステージ	3
		//------------------------------------------------------------
	case STAGE_003:
		CUI::Load(CManager::MODE_GAMESTAGE002);			//  Uiの読み込み
		ObjectLoad(STAGE_003);							//	テキスト読み込み
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 300, 80);
		CUI::CreateMode(CManager::MODE_GAMESTAGE002);	//UIの生成
		break;
	}
	//弾の数字
	CBulletNumber::Create();

	for (int nCount = 0; nCount < m_textState[OBJTYPE_ENEMY].nCnter; nCount++)
	{//	敵設定	位置　回転　寿命　種類　追従範囲　動く範囲 オブジェクトの通常の速さ オブジェクトの追従するときの速さ　敵の動きの種類
		m_pEnemy = CEnemy::Create
		(m_textState[OBJTYPE_ENEMY].pos[nCount], m_textState[OBJTYPE_ENEMY].rot[nCount], m_textState[OBJTYPE_ENEMY].nLife[nCount],
			m_textState[OBJTYPE_ENEMY].nType[nCount], m_textState[OBJTYPE_ENEMY].nMoveLength[nCount], m_textState[OBJTYPE_ENEMY].fNoneSpeed[nCount],
			m_textState[OBJTYPE_ENEMY].fFomSpeed[nCount],(CEnemy::ENEMY_AI)m_textState[OBJTYPE_ENEMY].nAIType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_ITEM].nCnter; nCount++)
	{//	アイテムの設定	位置　回転　大きさ　色　UV　種類
		CItem::Create
		(m_textState[OBJTYPE_ITEM].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[OBJTYPE_ITEM].size[nCount],
			m_textState[OBJTYPE_ITEM].col[nCount], m_textState[OBJTYPE_ITEM].uv[nCount], m_textState[OBJTYPE_ITEM].nType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_BLOCK].nCnter; nCount++)
	{//	ブロックの設定　位置　回転　大きさ　種類　　当たり判定の種類
		CBlock::Create
		(m_textState[OBJTYPE_BLOCK].pos[nCount],
			D3DXVECTOR3(m_textState[OBJTYPE_BLOCK].rot[nCount].x, D3DX_PI*m_textState[OBJTYPE_BLOCK].rot[nCount].y, m_textState[OBJTYPE_BLOCK].rot[nCount].z),
			m_textState[OBJTYPE_BLOCK].size[nCount], (CBlock::MODELTYPE)m_textState[OBJTYPE_BLOCK].nType[nCount], (CBlock::COLTYPE)m_textState[OBJTYPE_BLOCK].nColType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_3DPORI].nCnter; nCount++)
	{//	3Dポリゴンの設定	位置　回転　大きさ　色　UV　種類
		C3Dobject::Create
		(m_textState[OBJTYPE_3DPORI].pos[nCount], D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_textState[OBJTYPE_3DPORI].size[nCount],
			m_textState[OBJTYPE_3DPORI].col[nCount], m_textState[OBJTYPE_3DPORI].uv[nCount], m_textState[OBJTYPE_3DPORI].nType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_FLOOR].nCnter; nCount++)
	{//	床設定	位置　回転　大きさ　頂点の高さ　色　UV　種類
		CFloor::Create
		(m_textState[OBJTYPE_FLOOR].pos[nCount], D3DXVECTOR3(0.0f, 0.0f,0.0f), m_textState[OBJTYPE_FLOOR].size[nCount],
			m_textState[OBJTYPE_FLOOR].col[nCount], m_textState[OBJTYPE_FLOOR].uv[nCount], m_textState[OBJTYPE_FLOOR].nType[nCount], (CFloor::COLTYPE)m_textState[OBJTYPE_FLOOR].nColType[nCount]);
	}
	for (int nCount = 0; nCount < m_textState[OBJTYPE_WALL].nCnter; nCount++)
	{//	壁設定	位置　回転　大きさ　色　UV　種類
		CWall::Create
		(m_textState[OBJTYPE_WALL].pos[nCount], D3DXVECTOR3(0.0f, D3DX_PI*m_textState[OBJTYPE_WALL].rot[nCount].y, 0.0f), m_textState[OBJTYPE_WALL].size[nCount],
			m_textState[OBJTYPE_WALL].col[nCount], m_textState[OBJTYPE_WALL].uv[nCount], m_textState[OBJTYPE_WALL].nType[nCount]);
	}

	m_bPause = false;
	m_nOverNum = 0;						//	ゲームオーバーの選択項目
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CEnemy::UnLoad();			//	敵の開放
	CItem::Unload();			//	アイテムの開放
	CBlock::Unload();			//	ブロックの開放
	C3Dobject::Unload();		//	3Dポリゴンの開放
	CFloor::Unload();			//	床の開放
	CShadow::Unload();			//	影の開放
	CUI::Unload();				//  Uiの開放
	CNumber::UnLoad();			//　数字のテクスチャ開放
	CWall::Unload();			//	壁の破棄
	CBullet3D::Unload();		//	弾3Dの破棄
	CEffect::Unload();			//	エフェクトの開放
	CPlayer::UnLoad();			//	プレイヤーの開放
	CHpBer3D::Unload();			//	Hpバーーの開放
	CBullet2D::Unload();		//	弾の2Dの読み込み

	if (m_pPause != NULL)
	{//	ポーズの破棄
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}

	CScene::ReleaseMode();		// モード終了

}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	CSound *pSound = CManager::GetSound();	//	サウンドの取得

	switch (m_GameState)
	{
	case GAMESTATE0_NORMAL:
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_START, 0) == true)
			{//キーボード（P）を押した
				m_bPause = m_bPause ? false : true;		// 使用切り替え
				if (m_bPause == true)
				{// 使用する
					if (m_pPause == NULL)
					{// NULLの場合
					 // ポーズ生成
						m_pPause = new CPause;
						if (m_pPause != NULL)
						{
							m_pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
						}
					}
					if (m_pPause != NULL)
					{
						// 更新範囲をポーズから
						CScene::SetStartUp(CScene::PRIORITY_PAUSE);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);	//	SE鳴らす
					}
				}
				else
				{// その他
					if (m_pPause != NULL)
					{// NULL以外の場合
						m_pPause->Uninit();		// 終了処理
						delete m_pPause;		// メモリ開放
						m_pPause = NULL;		// NULLへ
					}
					CScene::SetStartUp(0);
				}
			}
			if (m_pPause != NULL && m_bPause == true)
			{// NULL以外の場合
				m_pPause->Update();		// ポーズ更新
			}
		}
		if (m_pPlayer->GetDisp() == true)
		{//	プレイヤーが亡くなった場合
			m_GameState = GAMESTATE_END;
		}

		break;
	case GAMESTATE_END:
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{//	指定の値を超えた場合
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
				|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
			{	// W 又は　↑キーを押した場合
				m_nOverNum = (m_nOverNum + 1) % 2;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			}
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
				|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
			{	// S 又は　↓キーを押した場合
				m_nOverNum = (m_nOverNum + 1) % 2;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			}
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PRESS);	//	決定音
				if (m_nOverNum == 0)
				{//	やり直す
					if (CFade::GetFade() == CFade::FADE_NONE)
					{//	何もしていないフェイドだった場合
						if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
						{//	チュートリアルだった場合
							CFade::Create(CManager::MODE_GAMETUTO, CFade::FADE_OUT,0);
						}
						else if (CGame::GetStage() == CGame::STAGE_001)
						{//	ステージ1だった場合
							CFade::Create(CManager::MODE_GAMESTAGE000, CFade::FADE_OUT, 0);
						}
						else if (CGame::GetStage() == CGame::STAGE_002)
						{//	ステージ2だった場合
							CFade::Create(CManager::MODE_GAMESTAGE001, CFade::FADE_OUT, 1);
						}
						else if (CGame::GetStage() == CGame::STAGE_003)
						{//	ステージ2だった場合
							CFade::Create(CManager::MODE_GAMESTAGE002, CFade::FADE_OUT, 1);
						}
					}
				}
				else if (m_nOverNum == 1)
				{	//　タイトル画面へ
					if (CFade::GetFade() == CFade::FADE_NONE)
					{//	何もしていないフェイドだった場合
						CFade::Create(CManager::MODE_OVER, CFade::FADE_OUT, 0);
					}
				}
			}
		}
		break;
	case GAMESTATE_CLEAR:
		CScene::SetStartUp(CScene::PRIORITY_PAUSE);
		m_nCounterState++;
		if (m_nCounterState >= 60)
		{//	指定の値を超えた場合
			if (CFade::GetFade() == CFade::FADE_NONE)
			{// フェードしていない状態
				if (m_StageType == STAGE_TUTORIAL)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE000, CFade::FADE_OUT, 0);
				}
				else if (m_StageType == STAGE_001)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE001, CFade::FADE_OUT, 1);
				}
				else if (m_StageType == STAGE_002)
				{
					CScene::SetStartUp(0);
					CFade::Create(CManager::MODE_GAMESTAGE002, CFade::FADE_OUT, 1);
				}
				else if (m_StageType == STAGE_003)
				{
					m_bClear = true;	//	ゲームクリアした
					if (CUI::GetNumTxst() > 5)
					{//	文字のテキストが値文進んだ場合
						CScene::SetStartUp(0);
						CFade::Create(CManager::MODE_CLEAR, CFade::FADE_OUT, 1);
					}
				}
			}
		}
		break;
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
	if (m_pPause != NULL)
	{// NULL以外の場合
		m_pPause->Draw();	// ポーズ描画
	}
}

//=============================================================================
// テキスト読み込み
//=============================================================================
void CGame::ObjectLoad(STAGETYPE stage)
{
	FILE *pFile;
	char read[128];										//	読み込む文字列
	char *txstName[STAGE_MAX][OBJTYPE_MAX][128] = {};	//	読み込むテキストのファイル

	if (stage == STAGE_TUTORIAL)
	{//	チュートリアル
		txstName[STAGE_TUTORIAL][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_TUTO/ItemSet.txt";		//	ステージ1のアイテム
		txstName[STAGE_TUTORIAL][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_TUTO/BlockSet.txt";	//	ステージ1ブロック
		txstName[STAGE_TUTORIAL][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_TUTO/3DPorSet.txt";	//	ステージ1Dポリゴンビルボード
		txstName[STAGE_TUTORIAL][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_TUTO/FloorSet.txt";	//	ステージ1Dポリゴン床
		txstName[STAGE_TUTORIAL][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_TUTO/WallSet.txt";		//	ステージ1Dポリゴン壁
		txstName[STAGE_TUTORIAL][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_TUTO/EnemySet.txt";	//	ステージ1Dポリゴン敵
	}
	else if (stage == STAGE_001)
	{//	ステージ1
		txstName[STAGE_001][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_000/ItemSet.txt";		//	ステージ1のアイテム
		txstName[STAGE_001][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_000/BlockSet.txt";		//	ステージ1ブロック
		txstName[STAGE_001][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_000/3DPorSet.txt";		//	ステージ1Dポリゴンビルボード
		txstName[STAGE_001][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_000/FloorSet.txt";		//	ステージ1Dポリゴン床
		txstName[STAGE_001][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_000/WallSet.txt";		//	ステージ1Dポリゴン壁
		txstName[STAGE_001][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_000/EnemySet.txt";		//	ステージ1Dポリゴン敵
	}
	else if (stage == STAGE_002)
	{//	ステージ2
		txstName[STAGE_002][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_001/ItemSet.txt";		//	ステージ2のアイテム
		txstName[STAGE_002][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_001/BlockSet.txt";		//	ステージ2ブロック
		txstName[STAGE_002][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_001/3DPorSet.txt";		//	ステージ2Dポリゴンビルボード
		txstName[STAGE_002][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_001/FloorSet.txt";		//	ステージ2Dポリゴン床
		txstName[STAGE_002][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_001/WallSet.txt";		//	ステージ2Dポリゴン壁
		txstName[STAGE_002][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_001/EnemySet.txt";		//	ステージ2Dポリゴン敵
	}
	else if (stage == STAGE_003)
	{//	ステージ3
		txstName[STAGE_003][OBJTYPE_ITEM][0] = "data/TEXT/STAGESET_002/ItemSet.txt";		//	ステージ3のアイテム
		txstName[STAGE_003][OBJTYPE_BLOCK][0] = "data/TEXT/STAGESET_002/BlockSet.txt";		//	ステージ3ブロック
		txstName[STAGE_003][OBJTYPE_3DPORI][0] = "data/TEXT/STAGESET_002/3DPorSet.txt";		//	ステージ3Dポリゴンビルボード
		txstName[STAGE_003][OBJTYPE_FLOOR][0] = "data/TEXT/STAGESET_002/FloorSet.txt";		//	ステージ3Dポリゴン床
		txstName[STAGE_003][OBJTYPE_WALL][0] = "data/TEXT/STAGESET_002/WallSet.txt";		//	ステージ3Dポリゴン壁
		txstName[STAGE_003][OBJTYPE_ENEMY][0] = "data/TEXT/STAGESET_002/EnemySet.txt";		//	ステージ3Dポリゴン敵
	}

	//-------------------------------------アイテム--------------------------------------------
	//	読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_ITEM][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "ITEM_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].y, &m_textState[OBJTYPE_ITEM].pos[m_textState[OBJTYPE_ITEM].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].y, &m_textState[OBJTYPE_ITEM].size[m_textState[OBJTYPE_ITEM].nCnter].z);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_ITEM].nType[m_textState[OBJTYPE_ITEM].nCnter]);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].r, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].g, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].b, &m_textState[OBJTYPE_ITEM].col[m_textState[OBJTYPE_ITEM].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_ITEM].uv[m_textState[OBJTYPE_ITEM].nCnter].x, &m_textState[OBJTYPE_ITEM].uv[m_textState[OBJTYPE_ITEM].nCnter].y);
				}
			} while (strcmp(&read[0], "ITEM_END") != 0);
			//	読み込んだアイテムの数加算
			m_textState[OBJTYPE_ITEM].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		//	テキストを占める
		fclose(pFile);
	}
	//-------------------------------------ブロック-------------------------------------------
	//	読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_BLOCK][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "BLOCK_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].pos[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT") == 0)
				{//	回転の設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].rot[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].x, &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].y, &m_textState[OBJTYPE_BLOCK].size[m_textState[OBJTYPE_BLOCK].nCnter].z);
				}
				else if (strcmp(&read[0], "MODELTYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_BLOCK].nType[m_textState[OBJTYPE_BLOCK].nCnter]);
				}
				else if (strcmp(&read[0], "COLTYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_BLOCK].nColType[m_textState[OBJTYPE_BLOCK].nCnter]);
				}
			} while (strcmp(&read[0], "BLOCK_END") != 0);
			//	読み込んだモデルの数加算
			m_textState[OBJTYPE_BLOCK].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------3Dポリゴン-------------------------------------------
	//	読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_3DPORI][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "3DPORIGON_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].y, &m_textState[OBJTYPE_3DPORI].pos[m_textState[OBJTYPE_3DPORI].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f%f",
					&read[0], &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].y, &m_textState[OBJTYPE_3DPORI].size[m_textState[OBJTYPE_3DPORI].nCnter].z);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
					&read[0], &m_textState[OBJTYPE_3DPORI].nType[m_textState[OBJTYPE_3DPORI].nCnter]);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].r, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].g, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].b, &m_textState[OBJTYPE_3DPORI].col[m_textState[OBJTYPE_3DPORI].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_3DPORI].uv[m_textState[OBJTYPE_3DPORI].nCnter].x, &m_textState[OBJTYPE_3DPORI].uv[m_textState[OBJTYPE_3DPORI].nCnter].y);
				}
			} while (strcmp(&read[0], "3DPORIGON_END") != 0);
			//	読み込んだモデルの数加算
			m_textState[OBJTYPE_3DPORI].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------床-------------------------------------------
	//読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_FLOOR][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "FLOOR_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].y, &m_textState[OBJTYPE_FLOOR].pos[m_textState[OBJTYPE_FLOOR].nCnter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].y, &m_textState[OBJTYPE_FLOOR].size[m_textState[OBJTYPE_FLOOR].nCnter].z);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].r, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].g, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].b, &m_textState[OBJTYPE_FLOOR].col[m_textState[OBJTYPE_FLOOR].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_FLOOR].uv[m_textState[OBJTYPE_FLOOR].nCnter].x, &m_textState[OBJTYPE_FLOOR].uv[m_textState[OBJTYPE_FLOOR].nCnter].y);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_FLOOR].nType[m_textState[OBJTYPE_FLOOR].nCnter]);
				}
				else if (strcmp(&read[0], "COLTYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_FLOOR].nColType[m_textState[OBJTYPE_FLOOR].nCnter]);
				}
			} while (strcmp(&read[0], "FLOOR_END") != 0);
			//	読み込んだモデルの数加算
			m_textState[OBJTYPE_FLOOR].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
	//-------------------------------------壁-------------------------------------------
	//	読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_WALL][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "WALL_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].y, &m_textState[OBJTYPE_WALL].pos[m_textState[OBJTYPE_WALL].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT_Y") == 0)
				{//	Y回転の設定4
					fscanf(pFile, "%s%f",
						&read[0], &m_textState[OBJTYPE_WALL].rot[m_textState[OBJTYPE_WALL].nCnter].y);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].y, &m_textState[OBJTYPE_WALL].size[m_textState[OBJTYPE_WALL].nCnter].z);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].r, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].g, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].b, &m_textState[OBJTYPE_WALL].col[m_textState[OBJTYPE_WALL].nCnter].a);
				}
				else if (strcmp(&read[0], "UV") == 0)
				{//	大きさの設定4
					fscanf(pFile, "%s%f%f",
						&read[0], &m_textState[OBJTYPE_WALL].uv[m_textState[OBJTYPE_WALL].nCnter].x, &m_textState[OBJTYPE_WALL].uv[m_textState[OBJTYPE_WALL].nCnter].y);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_WALL].nType[m_textState[OBJTYPE_WALL].nCnter]);
				}


			} while (strcmp(&read[0], "WALL_END") != 0);
			//	読み込んだモデルの数加算
			m_textState[OBJTYPE_WALL].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}

	//-------------------------------------敵-------------------------------------------
	//	読み込むテキスト
	pFile = fopen(txstName[stage][OBJTYPE_ENEMY][0], "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%s", &read[0]);
		while (read[0] != NULL && strcmp(&read[0], "ENEMY_SET") == 0)
		{//	文字列が読み込まれていた場合
			do
			{
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POS") == 0)
				{//	位置の設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].x, &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].y, &m_textState[OBJTYPE_ENEMY].pos[m_textState[OBJTYPE_ENEMY].nCnter].z);
				}
				else if (strcmp(&read[0], "ROT") == 0)
				{//	向きの設定
					fscanf(pFile, "%s%f%f%f",
						&read[0], &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].x, &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].y, &m_textState[OBJTYPE_ENEMY].rot[m_textState[OBJTYPE_ENEMY].nCnter].z);
				}
				else if (strcmp(&read[0], "LIFE") == 0)
				{//	体力の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nLife[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "TYPE") == 0)
				{//	種類の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nType[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "MOVELENGTH") == 0)
				{//	動く距離の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nMoveLength[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "NONESPEED") == 0)
				{//	通常の速さ
					fscanf(pFile, "%s%3f",
						&read[0], &m_textState[OBJTYPE_ENEMY].fNoneSpeed[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "FOMSPEED") == 0)
				{//	追従するときの速さ
					fscanf(pFile, "%s%3f",
						&read[0], &m_textState[OBJTYPE_ENEMY].fFomSpeed[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
				else if (strcmp(&read[0], "AITYPE") == 0)
				{//	AIの種類の設定
					fscanf(pFile, "%s%d",
						&read[0], &m_textState[OBJTYPE_ENEMY].nAIType[m_textState[OBJTYPE_ENEMY].nCnter]);
				}
			} while (strcmp(&read[0], "ENEMY_END") != 0);
			//	読み込んだモデルの数加算
			m_textState[OBJTYPE_ENEMY].nCnter++;
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
		}
		fclose(pFile);
	}
}
//=============================================================================
// ポーズ設定
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;		// ポーズ切り替え

	if (m_bPause == true)
	{// 使用する
		if (m_pPause == NULL)
		{// NULLの場合
		 // ポーズ生成
			m_pPause = new CPause;	// メモリ確保
			m_pPause->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, 170.0f, 0.0f), D3DXVECTOR3(150.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
		// 更新範囲をポーズから
		CScene::SetStartUp(CScene::PRIORITY_PAUSE);
	}
	else if(m_bPause == false)
	{// その他
		if (m_pPause != NULL)
		{// NULL以外の場合
			m_pPause->Uninit();		// 終了処理
			delete m_pPause;		// メモリ開放
			m_pPause = NULL;		// NULLへ
		}
		// 更新範囲を戻す
		CScene::SetStartUp(0);
	}
}