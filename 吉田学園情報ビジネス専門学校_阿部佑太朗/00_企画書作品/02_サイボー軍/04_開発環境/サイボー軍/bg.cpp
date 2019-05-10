//=============================================================================
//
//	背景の処理 [bg.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "bg.h"

//==============================================================================
//	静的メンバ変数初期化
// =============================================================================
LPDIRECT3DTEXTURE9 CBg::m_Texture[MAX_TEXTURE] = {};

//==============================================================================
//	コンストラクタ
//==============================================================================
CBg::CBg() :CScene(0)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	テクスチャの数だけ回す
		m_apScene2D[nCount] = NULL;
	}
	//	バッファの初期化
	m_pVtxBuff = NULL;
	//	動きの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
//	デストラクタ
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CBg::Init(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	テクスチャ分回す
		if (m_apScene2D[nCount] == NULL)
		{//	シーン2Dが使われていなかった場合
			//	背景１枚目の生成
			m_apScene2D[nCount] = new CScene2D;						//	メモリの確保
			if (m_apScene2D[nCount] != NULL)
			{
				m_apScene2D[nCount]->Init();							//	初期化処理
				m_pVtxBuff = m_apScene2D[nCount]->GetBuff();

				//頂点情報へのポインタ
				VERTEX_2D*pVtx;

				//バッファをロック
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//	位置の設定
				pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

				//頂点バッファをアンロックする
				m_pVtxBuff->Unlock();
				//	テクスチャ割り当て
				m_apScene2D[nCount]->BindTexture(m_Texture[nCount]);
			}
		}
	}
	//	値を返す
	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CBg::Uninit(void)
{
	//	背景の開放
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	テクスチャの数だけ回す
		if (m_apScene2D[nCount] != NULL)
		{//	シーン2Dが使われていた場合
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}
	//	バッファの開放
	if (m_pVtxBuff != NULL)
	{//	バッファが使われていた場合
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//	オブジェクトの破棄
	Release();
}

//==============================================================================
//	更新処理
//==============================================================================
void CBg::Update(void)
{
	D3DXVECTOR3 move[4];										//	背景の動き

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	背景の枚数分回す
		D3DXVECTOR3 pos = m_apScene2D[nCount]->GetPosition();	//	ポジションの取得

		move[nCount] = m_apScene2D[nCount]->GetMoveing();		//	動きの取得

			move[0].x -= 0.0005f;								//	背景1枚目の動き
			move[1].x -= 0.001f;								//	背景2枚目の動き
			move[2].x -= 0.002f;								//	背景3枚目の動き

		m_apScene2D[nCount]->BGMove(move[nCount]);
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CBg::Draw(void)
{
	//	シーンの派生だからDrawは何も書かない
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CBg *CBg::Create(void)
{
	CBg *pBg = {};		//	背景のポインタ

	if (pBg == NULL)
	{//	背景が使われていなかった場合
		pBg = new CBg;					//	メモリの確保
		if (pBg != NULL)
		{//	メモリの確保出来たら
			pBg->Init();				//	初期化処理
		}
	}
	//	値を返す
	return pBg;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CBg::Laod(void)
{
	//	デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_3, &m_Texture[3]);
	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//	背景の枚数分回す
		//	テクスチャの破棄
		if (m_Texture[nCount] != NULL)
		{//	テクスチャが使用されていたら
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}
