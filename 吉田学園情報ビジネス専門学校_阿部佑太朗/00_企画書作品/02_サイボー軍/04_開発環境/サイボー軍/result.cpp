//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bg.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture[MAX_RESULT_UI] = {};	// テクスチャ

//=============================================================================
//コンストラクタ
//=============================================================================
CResult::CResult()
{
	for (int nCount = 0; nCount < MAX_RESULT_UI; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount] = NULL;
		}
	}
	gamestate = GAMESTATE_NOMAL;

	m_fGameOverCounter = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bPressState = false;

}

//=============================================================================
//デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	m_fGameOverCounter = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bPressState = false;

	int GameState =  CGame::GetGameState();
	if (GameState == CGame::GAMESTATE_CLEAR)
	{//
		gamestate = GAMESTATE_CLEAR;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_CLEAR);
	}
	else
	{
		gamestate = GAMESTATE_OVER;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_OVER);

	}


	CResult::Load();

	for (int nCount = 0; nCount < MAX_RESULT_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	メモリの確保
			m_apScene2D[nCount] = new CScene2D;

			if (m_apScene2D[nCount] != NULL)
			{
				// 初期化処理
				m_apScene2D[nCount]->Init();
				m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				// テクスチャの設定
				m_apScene2D[nCount]->BindTexture(m_pTexture[nCount]);
			}
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CResult::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_RESULT_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	//	すべてのオブジェクトの破棄
	CScene::ReleaseAll();

	CSound::StopSound(CSound::SOUND_LABEL_BGM_CLEAR);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_OVER);
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();



	if (pFade->m_fade == pFade->FADE_NONE)
	{//	フェイドが終わったら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
		{//	エンター押したら画面遷移

			pFade->SetFade(CManager::MODE_SELECT);
			m_bPressState = true;
		}
	}

	m_fGameOverCounter += 0.0075f;					//	ゲームオーバーまたはゲームクリアが出現する時間
	m_nCounterAnim++;								//	press abbuttomがアニメーションする間隔

	switch (gamestate)
	{
	case GAMESTATE_NOMAL:
		break;
	case GAMESTATE_OVER:
		//	ゲーム
		m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 3, 300.0f, 0.0f), 350.0f,150.0f);
		m_apScene2D[0]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f+ m_fGameOverCounter));
		//	オーバー
		m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 1.5f, 450.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[1]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));

		break;
	case GAMESTATE_CLEAR:
		//	ステージ
		m_apScene2D[3]->SetPosition(D3DXVECTOR3(1280.0f / 3, 300.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[3]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));
		//	クリア
		m_apScene2D[4]->SetPosition(D3DXVECTOR3(1280.0f / 1.5f, 450.0f, 0.0f), 350.0f, 150.0f);
		m_apScene2D[4]->ColorChange(D3DXCOLOR(0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter, 0.0f + m_fGameOverCounter));

		break;
	}
	//	PRESS A BUTTON
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(1280.0f / 2, 560.0f, 0.0f), 180, 50);
	m_apScene2D[2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	if (m_bPressState == false)
	{
		if ((m_nCounterAnim % 30) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[2]->SetTexture(&tex[0]);
		}
	}
	else if (m_bPressState == true)
	{
		if ((m_nCounterAnim % 5) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[2]->SetTexture(&tex[0]);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CResult::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/game.png", &m_pTexture[0]);	//	ゲーム
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/over.png", &m_pTexture[1]);	//	オーバー
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/pressabutton.png", &m_pTexture[2]);	//	press a button
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/stage.png", &m_pTexture[3]);	//	オーバー
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RESULT/clear.png", &m_pTexture[4]);	//	press a button

	return S_OK;
}

//=============================================================================
// テクスチャを開放
//=============================================================================
void CResult::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_RESULT_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}