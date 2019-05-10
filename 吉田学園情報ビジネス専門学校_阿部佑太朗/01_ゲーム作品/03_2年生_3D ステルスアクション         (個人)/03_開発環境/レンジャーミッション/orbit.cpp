//=============================================================================
//
// メッシュオービット処理 [orbit.cpp]
// Author :YUTARO ABE
//
//=============================================================================
#include "orbit.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"

//=============================================================================
//	静的メンバ変数の初期化
//=============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
COrbit::COrbit() : CScene(CScene::PRIORITY_5, OBJECTE_ORBIT)
{
	m_pTexture = NULL;												//　テクスチャへのポインタの初期化
	m_pVtxBuff = NULL;												//　頂点バッファへのポイの初期化ンタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//　位置の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//　向きの初期化
	m_fWidth = NULL;												//	幅
	m_fHeight = NULL;												//	高さ
	m_fOffSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fOffSet[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{
		m_aPosVerTex[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================================================================
//	コンストラクタ
//=============================================================================
COrbit::COrbit(int nPriority, CScene::OBJTYPE objType) : CScene(CScene::PRIORITY_3, OBJECTE_ORBIT)
{
	m_pTexture = NULL;												//　テクスチャへのポインタの初期化
	m_pVtxBuff = NULL;												//　頂点バッファへのポイの初期化ンタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//　位置の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//　向きの初期化
	m_fWidth = NULL;												//	幅
	m_fHeight = NULL;												//	高さ
	m_fOffSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fOffSet[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{
		m_aPosVerTex[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
//	デストラクタ
//=============================================================================
COrbit::~COrbit()
{

}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
COrbit *COrbit::Create(D3DXVECTOR3 offsetstate, D3DXVECTOR3 offsetend)
{
	COrbit *pOrbit = {};

	if (pOrbit == NULL)
	{//	3Dポリゴンの生成
		pOrbit = new COrbit;
		if (pOrbit != NULL)
		{
			pOrbit->m_fOffSet[0] = offsetstate;
			pOrbit->m_fOffSet[1] = offsetend;
			// ポリゴンの初期化処理
			pOrbit->Init();
		}
	}
	return pOrbit;
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT COrbit::Init(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gradation004.jpg", &m_pTexture);
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_SIZE
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < MAX_XSIZE + 1; nCount++)
	{
		pVtx[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCount + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//	法線情報の計算
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCount + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCount + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// テクスチャ座標の設定
		pVtx[nCount].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCount + 1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 1;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void COrbit::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{//	頂点バッファが使われていたら
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// シーン開放
	CScene::SetDeath();
}

//=============================================================================
//	更新処理
//=============================================================================
void COrbit::Update(void)
{
}

//=============================================================================
//	更新処理
//=============================================================================
void COrbit::Draw(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// 裏面をカリング
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// Zバッファへの書き込み
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						// ライト影響受けない

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = MAX_SIZE - 1; nCount > 1; nCount--)
	{//
		m_aPosVerTex[nCount] = m_aPosVerTex[nCount - 2];
	}

	//	親のマトリックスと掛け合わせる
	D3DXVec3TransformCoord(&m_aPosVerTex[0], &m_fOffSet[0], m_pMtxParrentState);
	D3DXVec3TransformCoord(&m_aPosVerTex[1], &m_fOffSet[1], m_pMtxParrentState);

	for (int nCount = 0; nCount < MAX_SIZE; nCount++)
	{//	入れ替えたベクトルを頂点情報に入れる
		pVtx[nCount].pos = m_aPosVerTex[nCount];
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	if (m_pMtxParrentState != NULL)
	{
		// ポリゴンの描画// プリミティブの種類// 開始する頂点のインデックス// 描画するプリミティブの数
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, MAX_PORIGON_ORBIT);
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					// Zバッファへの書き込み
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライト影響受けない

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
//	マトリックスの設定
//=============================================================================
void COrbit::SetMtxParent(D3DXMATRIX *pMtxstate)
{
	m_pMtxParrentState = pMtxstate;
}
