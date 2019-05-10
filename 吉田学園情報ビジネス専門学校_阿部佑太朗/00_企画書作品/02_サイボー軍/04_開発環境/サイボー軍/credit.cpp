//=============================================================================
//
//	クレジット処理 [credit.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
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
#include "credit.h"

//=============================================================================
//静的メンバ変数初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CCredit::m_pTexture[MAX_CREDIT_UI] = {};	// テクスチャ

//=============================================================================
//コンストラクタ
//=============================================================================
CCredit::CCredit()
{
	for (int nCount = 0; nCount < MAX_CREDIT_UI; nCount++)
	{//	クレジットの最大数分回す
		if (m_apScene2D[nCount] != NULL)
		{//	クレジットが使われていた場合
			m_apScene2D[nCount] = NULL;
		}
	}
	m_nCounterAnim = 0;			//	カウンターアニメーションの初期化
	m_nPatternAnim = 0;			//	パターンアニメーションの初期化
	m_bPressState = false;		//	押しているかどうかの初期化

}

//=============================================================================
//デストラクタ
//=============================================================================
CCredit::~CCredit()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCredit::Init(void)
{
	m_nCounterAnim = 0;			//	カウンターアニメーションの初期化
	m_nPatternAnim = 0;			//	パターンアニメーションの初期化
	m_bPressState = false;		//	押しているかどうかの初期化
	//	クレジットの読み込み
	CCredit::Load();

	for (int nCount = 0; nCount < MAX_CREDIT_UI; nCount++)
	{//	クレジットの最大数分回す
		if (m_apScene2D[nCount] == NULL)
		{//	クレジットが使用されていなかった場合
			//	メモリの確保
			m_apScene2D[nCount] = new CScene2D;
			if (m_apScene2D[nCount] != NULL)
			{//	クレジットが使われていた場合
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
void CCredit::Uninit(void)
{
	//	テクスチャの破棄
	CCredit::UnLoad();

	// CScene2Dを開放する
	for (int nCntPause = 0; nCntPause < MAX_CREDIT_UI; nCntPause++)
	{//	クレジットの最大数分っ回す
		if (m_apScene2D[nCntPause] != NULL)
		{//	クレジットがつかわれていた場合
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
void CCredit::Update(void)
{
	//キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	//ゲームパッドの情報取
	CInputGamePad *pInputGamepad = CManager::GetInputGamepad();
	CFade *pFade = CManager::GetFade();

	if (pFade->m_fade == pFade->FADE_NONE)
	{//	フェイドが終わったら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetGamePadTrigger(BUTTON_A) == true)
		{//	エンター押したら画面遷移
			m_bPressState = true;					//	ボタンを押した
			pFade->SetFade(CManager::MODE_SELECT);	//	フェイドの処理
		}
	}
	//	クレジット背景
	m_apScene2D[0]->SetPosition(D3DXVECTOR3(1280.0f / 2, 720.0f/2, 0.0f), 1280.0f / 2, 720.0f / 2);
	m_apScene2D[0]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//	PRESS A BUTTON
	m_apScene2D[1]->SetPosition(D3DXVECTOR3(1280.0f / 2, 650.0f, 0.0f), 180, 50);
	m_apScene2D[1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_nCounterAnim++;
	if (m_bPressState == false)
	{//	ボタンを押していなかった場合
		if ((m_nCounterAnim % 30) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}
	}
	 if (m_bPressState == true)
	{//	ボタンを押した場合
		if ((m_nCounterAnim % 5) == 0)
		{//	PRESSENTERがアニメーションする時間間隔
			m_nPatternAnim += 1;
			//	PRESSENTERのアニメーション
			D3DXVECTOR2 tex[4];
			tex[0] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[1] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + 0.0f);
			tex[2] = D3DXVECTOR2(0.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			tex[3] = D3DXVECTOR2(1.0f, (1.0f / 2.0f) * (m_nPatternAnim % 2) + (1.0f / 2.0f));
			m_apScene2D[1]->SetTexture(&tex[0]);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CCredit::Draw(void)
{
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CCredit::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CREDIT/bg.png", &m_pTexture[0]);			//	クレジット背景
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/CREDIT/pressabutton.png", &m_pTexture[1]);	//	press a button

	return S_OK;
}

//=============================================================================
// テクスチャを開放
//=============================================================================
void CCredit::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_CREDIT_UI; nCntTex++)
	{//	クレジットの最大数分回す
		if (m_pTexture[nCntTex] != NULL)
		{//	クレジットがつかわれていた場合
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}