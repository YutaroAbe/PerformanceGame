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
#include "title.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TITLE_UI] = {};	// テクスチャ

//=============================================================================
//コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_nCounterAnim[nCount] = NULL;
		m_nPatternAnim[nCount] = NULL;
	}
	 m_bPressState = false;

}

//=============================================================================
//デストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
	{
		m_nCounterAnim[nCount] = 0;
		m_nPatternAnim[nCount] = 0;
	}
	m_bPressState = false;

	CTitle::Load();

	for (int nCount = 0; nCount < MAX_TITLE_UI; nCount++)
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
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f), 1280.0f / 2, 720.0f / 2);	//	タイトル背景  位置
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));										//	タイトル背景　色
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 2, 560.0f, 0.0f), 180, 50);						//	PRESSENTER	位置
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));										//	PRESSENTER　色
	m_apScene2D[2]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f / 2.5, 0.0f), 500, 140);				//	タイトルロゴ

	//テクスチャの設定
	D3DXVECTOR2 tex[4];
	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 4.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f));
	tex[3] = D3DXVECTOR2((1.0f / 4.0f), (1.0f / 2.0f));
	m_apScene2D[0]->SetTexture(&tex[0]);

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f));
	tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f));
	m_apScene2D[1]->SetTexture(&tex[0]);

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 7.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	tex[3] = D3DXVECTOR2((1.0f / 7.0f), 1.0f);
	m_apScene2D[2]->SetTexture(&tex[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CTitle::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_TITLE_UI; nCntPause++)
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
void CTitle::Update(void)
{
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	フェイドが終わったら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadRelease(BUTTON_A) == true)
		{//	エンター押したら画面遷移
			pFade->SetFade(CManager::MODE_SELECT);
			m_bPressState = true;
		}
	}
	m_nCounterAnim[0]++;//	タイトルロゴがアニメーションする時間の加算
	m_nCounterAnim[1]++;//	PRESS ENTERがアニメーションする時間の加算
	m_nCounterAnim[2]++;//	タイトル背景がアニメーションする時間の加算
	if (m_bPressState == false)
	{
		if ((m_nCounterAnim[0] % 100) == 0)
		{//	タイトル背景がアニメーションする時間間隔
			m_nPatternAnim[0] += 1;
			//	タイトル背景のアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + 0.0f, 0.0f);
			tex[1] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + (1.0f / 4.0f), 0.0f);
			tex[2] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4 + 0.0f), 0.5f);
			tex[3] = D3DXVECTOR2((1.0f / 4.0f) * (m_nPatternAnim[0] % 4) + (1.0f / 4.0f), 0.5f);
			m_apScene2D[0]->SetTexture(&tex[0]);
		}
		if ((m_nCounterAnim[2] % 30) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim[1] += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}

		if ((m_nCounterAnim[2] % 12) == 0 || m_nCounterAnim[2] >= 600)
		{//	タイトルロゴがアニメーションする時間間隔
			if (m_nCounterAnim[2] <= 600)
			{
				m_nPatternAnim[2] += 1;
			}
			else if (m_nCounterAnim[2] >= 600)
			{
				m_nPatternAnim[2] = 0;
				m_nCounterAnim[2] = 0;
			}

			if (m_nPatternAnim[2] <= 6)
			{
				//	タイトルロゴのアニメーション
				D3DXVECTOR2 tex[4];
				tex[0] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + 0.0f, 0.0f);
				tex[1] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + (1.0f / 7.0f), 0.0f);
				tex[2] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7 + 0.0f), 1.0f);
				tex[3] = D3DXVECTOR2((1.0f / 7.0f) * (m_nPatternAnim[2] % 7) + (1.0f / 7.0f), 1.0f);
				m_apScene2D[2]->SetTexture(&tex[0]);

			}

		}
	}
	if (m_bPressState == true)
	{//	PRESSENTERが押されたら
		if ((m_nCounterAnim[2] % 5) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim[1] += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim[1] % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CTitle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/titlebg.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/pressabutton.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE/titlelogo.png", &m_pTexture[2]);



	return S_OK;
}

//=============================================================================
// テクスチャを開放
//=============================================================================
void CTitle::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_TITLE_UI; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}