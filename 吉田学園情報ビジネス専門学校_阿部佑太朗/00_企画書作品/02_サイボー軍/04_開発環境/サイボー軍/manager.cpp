//=============================================================================
//
// メイン処理 [main.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CResult *CManager::m_pResult = NULL;
CSound *CManager::m_pSound = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CFade *CManager::m_pFade = NULL;
CSelect *CManager::m_pSelect = NULL;
CStageSelect *CManager::m_pStageSelect = NULL;
CInputGamePad *CManager::m_pInputGamepad = NULL;
CCredit *CManager::m_pCredit = NULL;
CMissionMessage *CManager::m_pMissionMessage = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{
}
//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL )
		{
			// レンダーの初期化処理
			if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
			{//フルスクリーン
				return -1;
			}
		}
		else
		{
			MessageBox(0, "初期化でメモリの確保ができていません", "警告", MB_OK);
		}
	}
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;

		if ( m_pInputKeyboard != NULL)
		{
			//	入力のの初期化処理
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{
			MessageBox(0, "初期化でメモリの確保ができていません", "警告", MB_OK);
		}
	}
	if (m_pInputGamepad == NULL)
	{
		m_pInputGamepad = new CInputGamePad;

		if (m_pInputGamepad != NULL)
		{
			//	入力のの初期化処理
			if (FAILED(m_pInputGamepad->Init(hInstance, hWnd)))
			{
				return -1;
			}
		}
		else
		{
			MessageBox(0, "初期化でメモリの確保ができていません", "警告", MB_OK);
		}
	}
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pSound != NULL)
		{//	サウンドの生成
			m_pSound->InitSound(hWnd);
		}
	}
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		if (m_pFade != NULL)
		{
			m_pFade->Init(m_mode);
		}
	}
	//モードの設定
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{
		// レンダーの終了処理
		m_pRenderer->Uninit();

		//メモリの開放
		delete m_pRenderer;

		//NULLにする
		m_pRenderer = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{
		//入力の終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}
	if (m_pInputGamepad != NULL)
	{
		//入力の終了処理
		m_pInputGamepad->Uninit();

		delete m_pInputGamepad;

		m_pInputGamepad = NULL;
	}
	if (m_pSound != NULL)
	{
		//サウンドの終了処理
		m_pSound->UninitSound();

		delete m_pSound;

		m_pSound = NULL;
	}
	if (m_pFade != NULL)
	{
		//ファイドの終了処理
		m_pFade->Uninit();

		delete m_pFade;

		m_pFade = NULL;
	}

	//全ての終了処理
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	int nStageMode = CGame::GetStageState();
	if (m_pRenderer != NULL)
	{
		// レンダー更新処理
		m_pRenderer->Update();

		//入力の更新処理
		m_pInputKeyboard->Update();

		m_pInputGamepad->Update();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Update();
		}
		break;
	case MODE_GAME:
		if (nStageMode == CGame::SETSTEGEMODE_000)
		{//	チュートリアルのみに出力する
			if (m_pMissionMessage != NULL)
			{//	ミッションメッセージ
				m_pMissionMessage->Update();
			}
		}
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Update();
		}
		break;
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	int nStageMode = CGame::GetStageState();
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{

			m_pSelect->Draw();
		}
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Draw();
		}
		break;
	case MODE_GAME:
		if(m_pGame != NULL)
		{
			m_pGame->Draw();
		}

		if (nStageMode == CGame::SETSTEGEMODE_000)
		{//	チュートリアルのみに出力する
			if (m_pMissionMessage != NULL)
			{//	ミッションメッセージ
				m_pMissionMessage->Draw();
			}
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Draw();
		}
		break;
	}
}

//=============================================================================
//レンダーの取得
//=============================================================================
CRenderer *CManager ::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
//入力の取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
//入力の取得
//=============================================================================
CInputGamePad *CManager::GetInputGamepad(void)
{
	return m_pInputGamepad;
}

//=============================================================================
//	モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{//終了処理
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{//	メモリにデータがあったら
			m_pTitle->Uninit();					//	タイトルの終了処理
			delete m_pTitle;
			m_pTitle = NULL;					//	メモリを空にする
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();					//	タイトルの終了処理
			delete m_pSelect;
			m_pSelect = NULL;					//	メモリを空にする
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			delete m_pStageSelect;
			m_pStageSelect = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		break;
	case MODE_GAME:
		if (m_pMissionMessage != NULL)
		{//	ミッションメッセージ
			m_pMissionMessage->Uninit();
			delete m_pMissionMessage;
			m_pMissionMessage = NULL;
		}
		if (m_pGame != NULL)
		{//	メモリにデータがあったら
			m_pGame->Uninit();					//	タイトルの終了処理
			delete m_pGame;
			m_pGame = NULL;						//	メモリを空にする
		}

		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	case MODE_CREDIT:
		if (m_pCredit != NULL)
		{
			m_pCredit->Uninit();
			delete m_pCredit;
			m_pCredit = NULL;
		}
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM_CREDIT);
		break;
	}

	switch (mode)
	{//初期化処理
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//タイトルに何もなかったら
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{//	メモリが確保出来たら
				m_pTitle->Init();				//タイトルの初期化処理
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		break;
	case MODE_SELECT:
		if (m_pSelect == NULL)
		{
			m_pSelect = new CSelect;
			if (m_pSelect != NULL)
			{//	メモリの確保が出来たら
				m_pSelect->Init();				//	セレクトの終了処理
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
		break;
	case MODE_STAGESELECT:
		if (m_pStageSelect == NULL)
		{
			m_pStageSelect = new CStageSelect;
			if (m_pStageSelect != NULL)
			{
				m_pStageSelect->Init();
			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//タイトルに何もなかったら
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{//	メモリが確保出来たら
				m_pGame->Init();				//ゲームの初期化処理
			}
		}
		if (m_pMissionMessage == NULL)
		{
			m_pMissionMessage = new CMissionMessage;
			if (m_pMissionMessage != NULL)
			{
				m_pMissionMessage->Init();
			}
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//タイトルに何もなかったら
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				m_pResult->Init();
			}
		}


		break;
	case MODE_CREDIT:
		if (m_pCredit == NULL)
		{
			m_pCredit = new CCredit;
			if (m_pCredit != NULL)
			{
				m_pCredit->Init();

			}
		}
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_CREDIT);

		break;
	}

	m_mode = mode;
 }

//=============================================================================
//	モードの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}