//=============================================================================
//
//	エフェクトの処理 [effect.cpp]
//	 Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_Texture = NULL;	//	テクスチャの初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CEffect::CEffect() : CScene2D(3)
{
	m_nLife = NULL;								//	エフェクトの寿命の初期化
	m_fRadius = NULL;							//	半径の初期化
	m_pVtxBuff = NULL;							//	頂点情報の初期化
	m_Color = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);	//	色の設定
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEffect::~CEffect()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col)
{
	CScene2D::Init();							//	2Dポリゴンの初期化処理
	SetPosition(pos, fRadius, fRadius);			//	ポジションと大きさの設定
	m_nLife = nLife;							//	エフェクトの寿命の設定
	m_fRadius = fRadius;						//	半径の設定
	m_Color = Col;								//	カラーの設定

	D3DXCOLOR col[4];
	//	色の設定
	col[0] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[1] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[2] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	col[3] = D3DXCOLOR(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	//	色の反映
	CScene2D::SetColor(&col[0]);

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CEffect::Uninit(void)
{
	//	シーン2Dの破棄
	CScene2D::Uninit();
}

//==============================================================================
//	更新処理
//==============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();							//	位置の取得
	//	位置のせてい
	SetPosition(pos, EFFECT_POLIGON_X, EFFECT_POLIGON_Y);

	m_nLife--;		//	寿命の減算
	m_fRadius--;	//	半径の減産ん

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//	頂点情報の取得
	m_pVtxBuff = CScene2D::GetBuff();

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (m_nLife <= 0 || m_fRadius <= 0)
	{//寿命が0いかまたは半径が0いかになった場合
		Uninit();
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CEffect::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	シーン2Dの描画
	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col)
{
	CEffect *pEffect = {};	//	エフェクトのポインタ

	if (pEffect == NULL)
	{//	エフェクトが使用されていなかった場合
		pEffect = new CEffect;		//	メモリの確保

		if (pEffect != NULL)
		{//	エフェクトが使用されていた場合
			// ポリゴンの初期化処理
			pEffect->Init(pos,nLife, fRadius, Col);
			//弾のテクスチャの割り当て
			pEffect->BindTexture(m_Texture);
		}
	}
	//	値を返す
	return pEffect;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CEffect::Laod(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EFFECT, &m_Texture);

	//	値を返す
	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CEffect::UnLoad(void)
{
	//テクスチャの破棄
	if (m_Texture != NULL)
	{//	テクスチャが使用されていた場合
		m_Texture->Release();
		m_Texture = NULL;
	}
}

