//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "input.h"
#include "pause.h"
#include "fade.h"
#include "renderer.h"

//=============================================================================
//  静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSE] = {};	// テクスチャ

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause() : CScene(7)
{
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_apScene2D[nCntPause] = NULL;
	}

	m_nNumSelect = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{

	// 背景の生成
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] == NULL)
		{
			m_apScene2D[nCntPause] = new CScene2D(7);

			if (m_apScene2D[nCntPause] != NULL)
			{
				// 初期化処理
				m_apScene2D[nCntPause]->Init();

				// テクスチャの設定
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);
			}
		}
	}
	 //背景の大きさを設定
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 200);
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 200, 50);
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f), 200, 50);
	m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 50);

	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_apScene2D[2]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	m_apScene2D[3]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	m_nNumSelect = 1;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}
	// 自分を消す
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	// 操作
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetPovTtigger(CROSSKEY_UP) == true)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nNumSelect = (m_nNumSelect + SELECT_MAX - 1) % SELECT_MAX;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = 3;
			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetPovTtigger(CROSSKEY_DOWN) == true)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			m_nNumSelect = (m_nNumSelect + 1) % SELECT_MAX;
			if (m_nNumSelect == 0)
			{
				m_nNumSelect = 3;

			}
			m_apScene2D[m_nNumSelect]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

	CFade *pFade = CManager::GetFade();
	// モード遷移
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A)==true)
	{
		CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
		if (m_nNumSelect == 1)
		{//　選択１つ目
			CGame::SetPause(false);
		}
		else if (m_nNumSelect == 2)
		{//　選択2つ目
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_GAME);
			}
		}
		else if (m_nNumSelect == 3)
		{//　選択3つ目
			if (pFade->m_fade == pFade->FADE_NONE)
			{
				pFade->SetFade(CManager::MODE_SELECT);
			}
		}
	}
	// 背景の大きさを設定
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f), 200, 200);

	//	大きさカラーの設定
	for (int nCount = 1; nCount < MAX_PAUSE; nCount++)
	{
		if (nCount != m_nNumSelect)
		{
			//　カラーの設定
			m_apScene2D[nCount]->ColorChange(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		m_apScene2D[nCount]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f + (nCount * 100), 0.0f), 200, 50);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// PAUSEの生成処理
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = {};
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			// 初期化
			pPause->Init();
		}
		else
		{
		}
	}
	return  pPause;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CPause::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause100.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause000.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause001.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/PAUSE/pause002.png", &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// テクスチャを開放
//=============================================================================
void CPause::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_PAUSE; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}
