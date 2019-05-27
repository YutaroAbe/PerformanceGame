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
#include "stageselect.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CStageSelect::m_pTexture[MAX_STAGESELECT_UI] = {};	// テクスチャ
int CStageSelect::m_nNumSelect = 1;
int CStageSelect::m_nSelectWordCounter = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	//変数の初期化
	for (int nCount = 0; nCount < MAX_STAGESELECT_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	m_bPress = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CStageSelect::~CStageSelect()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageSelect::Init(void)
{
	//変数の初期化
	m_nNumSelect = 1;
	m_nSelectWordCounter = 0;
	m_bPress = false;
	CStageSelect::Load();

	for (int nCount = 0; nCount < MAX_STAGESELECT_UI; nCount++)
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
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f / 2, 720.0f / 2);	//	セレクト背景
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(280.0f, 250.0f, 0.0f), 100, 100);							//　チュートリアル
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(520.0f, 250.0f,0.0f), 100, 100);							//	ステージ1
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(760.0f, 250.0f, 0.0f), 100, 100);							//	ステージ2
	m_apScene2D[4]->SetPosition(D3DXVECTOR3(1000.0f, 250.0f, 0.0f), 100, 100);							//　セレクトに戻る
	m_apScene2D[5]->SetPosition(D3DXVECTOR3(1280.0f / 2, 580, 0.0f), 450, 130);							//	メッセージウィンドウ
	m_apScene2D[6]->SetPosition(D3DXVECTOR3(1280.0f / 2, 90, 0.0f), 350, 130);							//	セレクトロゴ
	m_apScene2D[7]->SetPosition(D3DXVECTOR3(250, 205, 0.0f), 40, 100);									//	矢印

	//セレクトカラーの設定
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[2]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[3]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[4]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[5]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[6]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[7]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageSelect::Uninit(void)
{

	CStageSelect::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_STAGESELECT_UI; nCntPause++)
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
void CStageSelect::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();
	m_nSelectWordCounter++;
	if (pInputKeyboard->GetTrigger(DIK_A) == true || pInputKeyboard->GetTrigger(DIK_D) == true
		|| pInputGamepad->GetPovTtigger(CROSSKEY_LEFT)==true||pInputGamepad->GetPovTtigger(CROSSKEY_RIGHT)==true)
	{//	セレクトの説明欄文字列の初期化
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);

	}
	if (m_bPress == false)
	{
		// 操作
		if (pInputKeyboard->GetTrigger(DIK_A) == true || pInputGamepad->GetPovTtigger(CROSSKEY_LEFT) == true)
		{
			m_nSelectWordCounter = 0;
			m_nNumSelect = (m_nNumSelect + MAX_STAGESELECT - 1) % MAX_STAGESELECT;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = MAX_STAGESELECT;

			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_D) == true || pInputGamepad->GetPovTtigger(CROSSKEY_RIGHT) == true)
		{
			m_nSelectWordCounter = 0;
			m_nNumSelect = (m_nNumSelect + 1) % MAX_STAGESELECT;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = MAX_STAGESELECT;
			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// モード遷移
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true||pInputGamepad->GetGamePadTrigger(BUTTON_A)==true)
	{
		m_bPress = true;
		if (m_nNumSelect == 1)
		{//　選択１つ目	[ゲームモード]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				CGame::SetStage(CGame::SETSTEGEMODE_000);
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
		else if (m_nNumSelect == 2)
		{//　選択2つ目	[クレジット]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				CGame::SetStage(CGame::SETSTEGEMODE_001);
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
		else if (m_nNumSelect == 3)
		{//　選択3つ目	[セレクトに戻る]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				CGame::SetStage(CGame::SETSTEGEMODE_002);
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
		else if (m_nNumSelect == 4)
		{//　選択3つ目	[セレクトに戻る]
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_SELECT);
			}
		}
	}

	//	矢印の設定
	if (m_nNumSelect == 1)
	{//　選択１つ目	[チュートリアルへ]
		m_apScene2D[7]->SetPosition(D3DXVECTOR3(200.0f, 250, 0.0f), 40, 100);							//	矢印
	}
	else if (m_nNumSelect == 2)
	{//　選択2つ目	[ステージ1]
		m_apScene2D[7]->SetPosition(D3DXVECTOR3(440.0f, 250, 0.0f), 40, 100);							//	矢印
	}
	else if (m_nNumSelect == 3)
	{//　選択2つ目	[ステージ2]
		m_apScene2D[7]->SetPosition(D3DXVECTOR3(680, 250, 0.0f), 40, 100);							//	矢印
	}
	else if (m_nNumSelect == 4)
	{//　選択2つ目	[ステージ2]
		m_apScene2D[7]->SetPosition(D3DXVECTOR3(920, 250, 0.0f), 40, 100);							//	矢印
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
void CStageSelect::Draw(void)
{

}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CStageSelect::Load(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//	テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/selectbg.jpg", &m_pTexture[0]);		//	背景
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/stage000.png", &m_pTexture[1]);		//	チュートリアル
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/stage001.png", &m_pTexture[2]);		//	ステージ1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/stage002.png", &m_pTexture[3]);		//	ステージ2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/selectback.png", &m_pTexture[4]);		//	ステージ2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/Message.png", &m_pTexture[5]);			//	メッセージボックス
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/stageselectLogo.png", &m_pTexture[6]);	//
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/STAGESELECT/yajirusi.png", &m_pTexture[7]);		//	➤
	return S_OK;
}

//=============================================================================
//	テクスチャを開放
//=============================================================================
void CStageSelect::UnLoad(void)
{
	//	テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_STAGESELECT_UI; nCntTex++)
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
int CStageSelect::GetNumSelect(void)
{
	return m_nNumSelect;
}

//=============================================================================
//　セレクトの文字列表示カウンターの取得
//=============================================================================
int  CStageSelect::GetSelWordCounter(void)
{
	return m_nSelectWordCounter;
}
