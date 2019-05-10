//=============================================================================
//
//	エネミー数のカウントの処理 [time.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "enemycount.h"
#include "enemy.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
CNumber *CEnemycount::m_apNumber[MAX_ENEMYCOUNT] = {};		//	エネミー数のカウントのポインタ型変数初期化
int CEnemycount::m_nEnemyCount = NULL;						//	エネミー数のカウント変数初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemycount::CEnemycount() :CScene(3)
{
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemycount::~CEnemycount()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemycount::Init(void)
{
	m_nEnemyCount = 0;
	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{//	番号の生成
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(400.0f + (nCount * 30), 47.0f, 0.0f), D3DXVECTOR3(17.0f, 17.0f, 0.0f));
	}



	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CEnemycount::Uninit(void)
{
	if (m_apNumber != NULL)
	{
		for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
		{//数字の開放
			m_apNumber[nCount]->Uninit();
		}
	}
	//自分自身の開放
	Release();
}

//==============================================================================
//	更新処理
//==============================================================================
void CEnemycount::Update(void)
{
}

//==============================================================================
//	描画処理
//==============================================================================
void CEnemycount::Draw(void)
{
	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{//	番号の描画
		m_apNumber[nCount]->Draw();
	}
}

//==============================================================================
//	タイマーの生成処理
//==============================================================================
CEnemycount *CEnemycount::Create(void)
{
	CEnemycount *pEnemyCount = {};

	if (pEnemyCount == NULL)
	{
		pEnemyCount = new CEnemycount;

		if (pEnemyCount != NULL)
		{
			pEnemyCount->Init();
		}
		else
		{
		}
	}
	return pEnemyCount;
}

//==============================================================================
//	タイマーの取得
//==============================================================================
int  CEnemycount::GetTime(void)
{
	return m_nEnemyCount;
}

//==============================================================================
//	タイマーの取得
//==============================================================================
void  CEnemycount::AddEnemyCount(int nValue)
{
	int aNumber[MAX_ENEMYCOUNT];

	m_nEnemyCount += nValue;

	aNumber[0] = m_nEnemyCount % 1000 / 100;
	aNumber[1] = m_nEnemyCount % 100 / 10;
	aNumber[2] = m_nEnemyCount % 10 / 1;

	for (int nCount = 0; nCount < MAX_ENEMYCOUNT; nCount++)
	{
		m_apNumber[nCount]->SetNumber(aNumber[nCount]);
	}
}