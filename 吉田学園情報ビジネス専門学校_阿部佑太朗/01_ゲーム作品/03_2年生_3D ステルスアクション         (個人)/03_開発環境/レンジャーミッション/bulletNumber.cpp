//=============================================================================
//
//	ライフに数値の処理 [LifeNUmber.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "bulletNumber.h"
#include "number.h"
#include "game.h"
#include "player.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
CNumber *CBulletNumber::m_apNumber[MAX_LIFENUMBER] = {};
int CBulletNumber::m_nNumber = NULL;

//==============================================================================
//	コンストラクタ
//==============================================================================
CBulletNumber::CBulletNumber() :CScene(PRIORITY_UI, OBJTYPE_LIFENUMBER)
{

}

//==============================================================================
//	デストラクタ
//==============================================================================
CBulletNumber::~CBulletNumber()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CBulletNumber::Init(void)
{
	m_nNumber = 0;
	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{//	番号の生成
		if (nCount == 0 || nCount == 1)
		{
			m_apNumber[nCount] = CNumber::Create(D3DXVECTOR3((SCREEN_WIDTH - 130.0f) + (nCount * 35), (SCREEN_HEIGHT - 40.0f), 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f));
		}
	}

	AddNum(CGame::GetPlayer()->GetBltNum());				//	初期のライフの数値設定
	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CBulletNumber::Uninit(void)
{
	if (m_apNumber != NULL)
	{
		for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
		{//数字の開放
			m_apNumber[nCount]->Uninit();
		}
	}
	//自分自身の開放
	CScene::SetDeath();
}

//==============================================================================
//	更新処理
//==============================================================================
void CBulletNumber::Update(void)
{
}

//==============================================================================
//	描画処理
//==============================================================================
void CBulletNumber::Draw(void)
{
	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{//	番号の描画
		m_apNumber[nCount]->Draw();
	}
}

//==============================================================================
//	スコアの生成処理
//==============================================================================
CBulletNumber *CBulletNumber::Create(void)
{
	CBulletNumber *pBuletNum = {};

	if (pBuletNum == NULL)
	{//	メモリ確保
		pBuletNum = new CBulletNumber;

		if (pBuletNum != NULL)
		{//	モリが確保出来たら
			pBuletNum->Init();				//	の初期化処理
		}
	}
	return pBuletNum;
}

//==============================================================================
//	取得
//==============================================================================
int  CBulletNumber::GetLefeNum(void)
{
	return m_nNumber;
}

//==============================================================================
//	設定
//==============================================================================
void  CBulletNumber::AddNum(int nValue)
{
	int aNumber[MAX_LIFENUMBER];

	m_nNumber += nValue;

	aNumber[0] = m_nNumber % 100 / 10;
	aNumber[1] = m_nNumber % 10 / 1;


	for (int nCount = 0; nCount < MAX_LIFENUMBER; nCount++)
	{
		m_apNumber[nCount]->SetNumber(aNumber[nCount]);
	}
}