//=============================================================================
//
//	数字の処理 [number.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "scene.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_Texture = NULL;
int CNumber::m_NumNumber = NULL;

//==============================================================================
//	コンストラクタ
//==============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	デストラクタ
//==============================================================================
CNumber::~CNumber()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_Length = Length;

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f - m_Length.y, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_Length.x, 0.0f + m_Length.y, 0.0f) + m_pos;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CNumber::Uninit(void)
{
	m_NumNumber--;
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
//	更新処理
//==============================================================================
void CNumber::Update(void)
{

}

//==============================================================================
//	描画処理
//==============================================================================
void CNumber::Draw(void)
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

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==============================================================================
//	スコアの生成処理
//==============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length)
{
	CNumber *pNumber = {};
	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		if (pNumber != NULL)
		{
			m_NumNumber++;
			pNumber->Init(pos, Length);
			pNumber->BindTexture(m_Texture);
		}
		else
		{
		}
	}
	return pNumber;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CNumber::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_NUMBER_0, &m_Texture);

	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CNumber::UnLoad(void)
{
	//	テクスチャの破棄
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}
//==============================================================================
//	スコアの取得
//==============================================================================
void CNumber::SetNumber(int nNumber)
{
	int aNumber = nNumber;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
 	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	 //テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber * 0.1f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	共通テクスチャを割り当てる処理
//=============================================================================
void CNumber::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_Texture = pTexture;
}

//=============================================================================
//	作られている番号の数の取得
//=============================================================================
int  CNumber::GetNumNumber(void)
{
	return m_NumNumber;
}