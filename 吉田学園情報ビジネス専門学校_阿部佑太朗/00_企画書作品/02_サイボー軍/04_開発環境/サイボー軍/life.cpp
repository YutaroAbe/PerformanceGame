//=============================================================================
//
//	体力の処理 [number.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"
#include "life.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CLife::m_Texture = NULL;

//==============================================================================
//	コンストラクタ
//==============================================================================
CLife::CLife() : CScene2D(3)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	デストラクタ
//==============================================================================
CLife::~CLife()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	m_pos = pos;
	m_Length = Length;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * m_nLife, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < m_nLife; nCount++)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
		pVtx[1].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;
		pVtx[3].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//テクスチャの座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		m_pos += D3DXVECTOR3(m_Length.x, 0.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CLife::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//==============================================================================
//	更新処理
//==============================================================================
void CLife::Update(void)
{

}

//==============================================================================
//	描画処理
//==============================================================================
void CLife::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	int nLife = CPlayer::GetLife();

	for (int nCount = 0; nCount < nLife; nCount++)
	{//　プレイヤーのHPと同期
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, MAX_POLIGON);
	}
}

//==============================================================================
//	スコアの生成処理
//==============================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	CLife *pLife = {};

	if (pLife == NULL)
	{
		pLife = new CLife;

		if (pLife != NULL)
		{
			pLife->Init(pos , Length);
			pLife->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pLife;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CLife::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFE, &m_Texture);


	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CLife::UnLoad(void)
{
	//	テクスチャの破棄
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}

//=============================================================================
//	共通テクスチャを割り当てる処理
//=============================================================================
void CLife::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_Texture = pTexture;

}