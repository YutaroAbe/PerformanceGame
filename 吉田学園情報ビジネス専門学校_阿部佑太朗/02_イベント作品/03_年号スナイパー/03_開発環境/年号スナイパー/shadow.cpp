//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"		// シーン3D
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力
#include "camera.h"			// カメラ
#include "shadow.h"			// 3dオブジェクト
#include "effect.h"			// エフェクト

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CShadow::m_pTexture= NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow() : CScene3D(CScene::PRIORITY_4, CScene::OBJECTE_SHADOW)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
//	アイテムの生成
//=============================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV)
{
	CShadow *pShadow = {};

	if (pShadow == NULL)
	{//	アイテムの生成
		pShadow = new CShadow;
		if (pShadow != NULL)
		{//アイテムの初期化
			pShadow->Init(pos, rot, size, col, TexUV);
		}
	}
	return pShadow;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV)
{
	CScene3D::SetInitAll(pos /*+ D3DXVECTOR3(0.0f, size.y, 0.0f)*/, rot, size, col, TexUV, CScene3D::SCENE3DTYPE_SUBSYNTHESIS);
	CScene3D::Init();
	CScene3D::BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShadow::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CShadow::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CShadow::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &m_pTexture);

	return S_OK;
}
//=============================================================================
// アンロード処理
//=============================================================================
void CShadow::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
