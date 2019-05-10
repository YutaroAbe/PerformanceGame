//=============================================================================
//
// セレクト処理 [selsect.cpp]
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
#include "select.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CSelect::m_pTexture[MAX_SELECT_UI] = {};	// テクスチャ
int CSelect::m_nNumSelect = 1;
int CSelect::m_nSelectWordCounter = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CSelect::CSelect()
{
	//変数の初期化
	for (int nCount = 0; nCount < MAX_SELECT_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_nNextCounter = 0;
	m_bPress = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CSelect::~CSelect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelect::Init(void)
{
	//変数の初期化
	m_nNumSelect = 1;
	m_nSelectWordCounter = 0;
	m_nNextCounter = 0;
	m_bPress = false;
	CSelect::Load();

	for (int nCount = 0; nCount < MAX_SELECT_UI; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)
		{
			//	メモリの確保
			m_apScene2D[nCount] = new CScene2D;
			if (m_apScene2D[nCount] != NULL)
			{
				// 初期化処理
				m_apScene2D[nCount]->Init();

				// テクスチャの設定
				m_apScene2D[nCount]->BindTexture(m_pTexture[nCount]);

			}
		}
	}
	//	セレクト　位置の設定
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f / 2, 720.0f/2);	//	セレクト背景
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(500, 205, 0.0f), 250, 130);								//　ゲームモード
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(800, 310, 0.0f), 250, 130);								//	クレジットモード
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(500, 415, 0.0f), 250, 130);								//	ゲーム終了
	m_apScene2D[4]->SetPosition(D3DXVECTOR3(1280.0f/2, 580, 0.0f), 450, 130);						//	メッセージウィンドウ
	m_apScene2D[5]->SetPosition(D3DXVECTOR3(1280.0f / 2, 90, 0.0f), 350, 130);						//	セレクトロゴ
	m_apScene2D[6]->SetPosition(D3DXVECTOR3(250 , 205, 0.0f), 100, 100);							//	矢印

	//セレクトカラーの設定
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[2]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[3]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[4]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[5]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[6]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSelect::Uninit(void)
{

	CSelect::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_SELECT_UI; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSelect::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();


	 if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyboard->GetTrigger(DIK_S) == true
		 || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
	{//	セレクトの説明欄文字列の初期化
		 CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_nNextCounter = 0;

	}
	 m_nNextCounter++;
	 if (m_nNextCounter >= 600)
	 {
		 if (pFade->m_fade == pFade->FADE_NONE)
		 {
			 pFade->SetFade(CManager::MODE_TITLE);
		 }
	 }
	 if (m_bPress == false)
	 {
		 m_nSelectWordCounter++;
		 // 操作
		 if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true)
		 {
			 m_nSelectWordCounter = 0;
			 m_nNumSelect = (m_nNumSelect + MAX_SELECT - 1) % MAX_SELECT;
			 if (m_nNumSelect == 0)
			 {
				 m_nNumSelect = MAX_SELECT;

			 }
			 m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		 }
		 else if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
		 {
			 m_nSelectWordCounter = 0;
			 m_nNumSelect = (m_nNumSelect + 1) % MAX_SELECT;
			 if (m_nNumSelect == 0)
			 {
				 m_nNumSelect = MAX_SELECT;
			 }
			 m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		 }
	 }
	// モード遷移
	if (pInputKeyboard->GetRelease(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
	{
		m_bPress = true;
		if (m_nNumSelect == 1)
		{//　選択１つ目	[ゲームモード]
			if (pFade->m_fade == pFade->FADE_NONE)
			{

				pFade->SetFade(CManager::MODE_STAGESELECT);
			}
		}
		else if (m_nNumSelect == 2)
		{//　選択2つ目	[クレジット]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_CREDIT);
			}
		}
		else if (m_nNumSelect == 3)
		{//　選択3つ目	[クレジット]
			if (pFade->m_fade == pFade->FADE_NONE)
			{

				pFade->SetFade(CManager::MODE_TITLE);
			}
		}
	}

	//	矢印の設定
	if (m_nNumSelect == 1)
	{//　選択１つ目	[ゲームモード]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(250, 205, 0.0f), 100, 100);							//	矢印
	}
	else if (m_nNumSelect == 2)
	{//　選択2つ目	[クレジット]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(550, 310, 0.0f), 100, 100);							//	矢印
	}
	else if (m_nNumSelect == 3)
	{//　選択2つ目	[クレジット]
		m_apScene2D[6]->SetPosition(D3DXVECTOR3(250, 415, 0.0f), 100, 100);							//	矢印
	}
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//	大きさカラーの設定
	for (int nCount = 1; nCount < MAX_SELECT_UI; nCount++)
	{
		if (nCount != m_nNumSelect)
		{
			//　カラーの設定
			m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CSelect::Draw(void)
{

}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CSelect::Load(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//	テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/selectbg.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select000.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/select002.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/Message.png", &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/selectLogo.png", &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/SELECT/yajirusi.png", &m_pTexture[6]);
	return S_OK;
}

//=============================================================================
//	テクスチャを開放
//=============================================================================
void CSelect::UnLoad(void)
{
	//	テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_SELECT_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// 選択する番号の取得
//=============================================================================
int CSelect::GetNumSelect(void)
{
	return m_nNumSelect;
}

//=============================================================================
//　セレクトの文字列表示カウンターの取得
//=============================================================================
int  CSelect::GetSelWordCounter(void)
{
	return m_nSelectWordCounter;
}
