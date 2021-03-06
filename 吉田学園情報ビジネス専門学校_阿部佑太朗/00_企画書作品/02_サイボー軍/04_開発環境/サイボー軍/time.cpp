//=============================================================================
//
//	タイマーの処理 [time.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "time.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
CNumber *CTime::m_apNumber[MAX_TIME] = {};		//	タイマーのポインタ型変数初期化
int CTime::m_nTime = NULL;							//	タイマーの変数初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CTime::CTime() :CScene(3)
{

}

//==============================================================================
//	デストラクタ
//==============================================================================
CTime::~CTime()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CTime::Init(void)
{
	m_nTime = 0;

	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{//	番号の生成
		m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3(560.0f+(nCount*30), 47.0f, 0.0f), D3DXVECTOR3(17.0f, 17.0f, 0.0f));
	}

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CTime::Uninit(void)
{
	if (m_apNumber != NULL)
	{
		for (int nCount = 0; nCount < MAX_TIME; nCount++)
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
void CTime::Update(void)
{
	int nCount = 0;
		nCount++;

		if (nCount %= 6)
		{
			AddTime(nCount);
		}
}

//==============================================================================
//	描画処理
//==============================================================================
void CTime::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{//	番号の描画
		m_apNumber[nCount]->Draw();
	}
}

//==============================================================================
//	タイマーの生成処理
//==============================================================================
CTime *CTime::Create(void)
{
	CTime *pTime = {};

	if (pTime == NULL)
	{
		pTime = new CTime;

		if (pTime != NULL)
		{
			pTime->Init();
		}
		else
		{
		}
	}
	return pTime;
}

//==============================================================================
//	タイマーの取得
//==============================================================================
int  CTime::GetTime(void)
{
	return m_nTime;
}

//==============================================================================
//	タイマーの取得
//==============================================================================
void  CTime::AddTime(int nValue)
{
	int aNumber[MAX_TIME];

	m_nTime += nValue;

	aNumber[0] = m_nTime % 100000 / 10000;
	aNumber[1] = m_nTime % 10000 / 1000;
	aNumber[2] = m_nTime % 1000 / 100;

	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_apNumber[nCount]->SetNumber(aNumber[nCount]);
	}
}