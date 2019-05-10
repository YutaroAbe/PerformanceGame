//=============================================================================
//
//	ミッションメッセージ処理 [credit.cpp]
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
#include"missionmessage.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CMissionMessage::m_pTexture[MAX_MISSONMESSAGE_UI] = {};	// テクスチャ
int CMissionMessage::m_nGameTextCounter = NULL;
int CMissionMessage::m_nNumText = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CMissionMessage::CMissionMessage()
{
	for (int nCount = 0; nCount < MAX_MISSONMESSAGE_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_bPressState = false;

}

//=============================================================================
//デストラクタ
//=============================================================================
CMissionMessage::~CMissionMessage()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMissionMessage::Init(void)
{
	m_bPressState = false;
	m_nGameTextCounter = 0;
	m_nNumText = 0;

	CMissionMessage::Load();
	for (int nCount = 0; nCount < MAX_MISSONMESSAGE_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	メモリの確保
			m_apScene2D[nCount] = new CScene2D;

			if (m_apScene2D[nCount] != NULL)
			{
				// 初期化処理
				m_apScene2D[nCount]->Init();
				m_apScene2D[nCount]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
void CMissionMessage::Uninit(void)
{
	CMissionMessage::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_MISSONMESSAGE_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	//	すべてのオブジェクトの破棄
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMissionMessage::Update(void)
{
	m_nGameTextCounter++;
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	フェイドが終わったら
		if ((pInputKeyboard->GetTrigger(DIK_M) == true || pInputGamepad->GetGamePadTrigger(BUTTON_X) == true ) &&m_nGameTextCounter > 120)
		{//	エンター押したら画面遷移
			m_nGameTextCounter = 0;
			m_nNumText += 1;
			CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTO);
		}
	}

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	フェイドが終わったら
		if (m_nNumText > 4)
		{
			if (pInputKeyboard->GetTrigger(DIK_N) == true || pInputGamepad->GetGamePadTrigger(BUTTON_Y) == true)
			{//	エンター押したら画面遷移
				pFade->SetFade(CManager::MODE_STAGESELECT);
			}
		}
	}
	//	背景
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(400.0f, 240.0f, 0.0f),400.0f,90.0f);
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}

//=============================================================================
// 描画処理
//=============================================================================
void CMissionMessage::Draw(void)
{
}


//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CMissionMessage::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/MISSIONMESSAGE/bossmesssage.png", &m_pTexture[0]);			//	クレジット背景

	return S_OK;
}

//=============================================================================
// テクスチャを開放
//=============================================================================
void CMissionMessage::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_MISSONMESSAGE_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//ゲームの文字のテキストを出力するカウンター
//=============================================================================
int CMissionMessage::GetGameText(void)
{
	return m_nGameTextCounter;
}
//=============================================================================
//ゲームの文字のテキストを出力するカウンター
//=============================================================================
int CMissionMessage::GetNumText(void)
{
	return m_nNumText;
}