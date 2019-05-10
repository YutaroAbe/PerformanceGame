//=============================================================================
//
//	爆発の処理 [bullet.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_Texture = NULL;

//==============================================================================
//	コンストラクタ
//==============================================================================
CExplosion::CExplosion() : CScene2D(3)
{
	m_CounterAnim = 0;
	m_PatternAnim = 0;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CExplosion::~CExplosion()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init();

	//テクスチャの設定
	D3DXVECTOR2 tex[4];

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2((1.0f / 5.0f), 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f);
	tex[3] = D3DXVECTOR2((1.0f / 5.0f), 1.0f);

	CScene2D::SetTexture(&tex[0]);


	SetPosition(pos, EXPLOSION_POLIGON_X, EXPLOSION_POLIGON_Y);

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	更新処理
//==============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMoveing();							//	動き

	D3DXVECTOR3 playermove = CPlayer::GetMove();

	if (playermove.x >= 0.1f)
	{
		move.x -= playermove.x;
	}
	else if (playermove.x <= -0.1f)
	{
		move.x += -playermove.x;
	}

	pos.x += move.x;
	pos.y += move.y;

	SetPosition(pos, EXPLOSION_POLIGON_X, EXPLOSION_POLIGON_Y);

	m_CounterAnim++;

	if ((m_CounterAnim % 5) == 0)
	{
		m_PatternAnim = (m_PatternAnim + 1) % 5;

		D3DXVECTOR2 tex[4];

		tex[0] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + 0.0f, 0.0f);
		tex[1] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + (1.0f / 5.0f), 0.0f);
		tex[2] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5 + 0.0f), 1.0f);
		tex[3] = D3DXVECTOR2((1.0f / 5.0f) * (m_PatternAnim % 5) + (1.0f / 5.0f), 1.0f);

		CScene2D::SetTexture(&tex[0]);

		if (m_PatternAnim <= 0)
		{
			Uninit();
		}
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = {};

	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;

		if (pExplosion != NULL)
		{
			// ポリゴンの初期化処理
			pExplosion->Init(pos);
			//弾のテクスチャの割り当て
			pExplosion->BindTexture(m_Texture);

		}
		else
		{

		}
	}
	return pExplosion;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CExplosion::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EXPLPSION, &m_Texture);

	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CExplosion::UnLoad(void)
{
	//テクスチャの破棄
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}

