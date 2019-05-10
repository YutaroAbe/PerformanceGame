//=============================================================================
//
// モデル処理 [model.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//=============================================================================
//コンストラクタ
//=============================================================================
CModel::CModel()
{
	m_pMesh = NULL;					//	メッシュ情報へのポインタ
	m_pBuffMat = NULL;				//	マテリアル情報へのポインタ
	m_pTexture= NULL;				//	テクスチャへのポインタ
	m_nNumMat = 0;					//	マテリアル情報の数
	m_pParent = NULL;				//	親モデルへのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel = {};

	if (pModel == NULL)
	{//	モデルが使われていなかった場合
		pModel = new CModel;	//	メモリの確保
		if (pModel != NULL)
		{//	初期化処理量
			pModel->m_pos = pos;	//	位置
			pModel->m_rot = rot;	//	向き
			pModel->Init();			//	初期化
		}
	}
	//	値を返す
	return pModel;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	//ポインタのNULLチェック
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{
			//ポインタ内のポインタのNULLチェック
			if (m_pTexture[nCnt] != NULL)
			{
				//テクスチャ破棄
				m_pTexture[nCnt]->Release();
				m_pTexture[nCnt] = NULL;
			}
		}
		//メモリを開放
		delete[] m_pTexture;
		//NULLを入れる
		m_pTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxParent;

	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	//	ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 頂点法線の自動正規化		開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{//親のマトリックスを取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{	//Drawで呼ばれたとき最新のmtxをpDeviceから取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//親の情報を入れる	掛け合わせている
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		if (pMat != NULL)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャがある場合
				pDevice->SetTexture(0, m_pTexture[nCntMat]);
			}
			else
			{	// テクスチャを使っていない
				pDevice->SetTexture(0, NULL);
			}
		}
		//オブジェクト(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
	// 頂点法線の自動正規化		開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//	ライトを戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// マテリアル割り当て処理
//=============================================================================
void CModel::BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	m_pBuffMat = Buff;
	m_nNumMat = nNumMat;
	m_pMesh = Mesh;
	//マテリアル情報からテクスチャの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	//テクスチャをマテリアルの数分動的確保
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];
	//マテリアルの数回す
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat; nCntMatTex++)
	{
		//NULLを入れる 中身を空に
		m_pTexture[nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// テクスチャの設定
			D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
				pMat[nCntMatTex].pTextureFilename,		// ファイルの名前
				&m_pTexture[nCntMatTex]);				// テクスチャへのポインタ
		}
	}
}

//=============================================================================
// 親の設定処理
//=============================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ワールドマトリックスの取得処理
//=============================================================================
D3DXMATRIX &CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// ワールドマトリックスの設定処理
//=============================================================================
void CModel::SetMtxWorld(D3DXMATRIX MtxWorld)
{
	m_mtxWorld = MtxWorld;
}

