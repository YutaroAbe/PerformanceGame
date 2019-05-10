//=============================================================================
//
// モデル処理 [model.h]
// Author :
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//モデルクラスの定義
//*********************************************************************
class CModel
{
public:
	typedef struct
	{
		DWORD nNumMat = 0;						//	マテリアル情報の数
		float fShadow;							//	影の大きさ
		int nIdxShadow;							//	影のインデックス
		int nType;								//	モデルの種類
		bool bUse;								//	使用しているか
	} MODEL;

	CModel();														//	コンストラクタ
	~CModel();														//	デストラクタ
	HRESULT Init();													//	初期化処理
	void Uninit(void);												//	終了処理
	void Update(void);												//	更新処理
	void Draw(void);												//	描画処理
	MODEL *GetModel(void) { return &m_aModel; }						//	モデルの取得
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//	Character
	void BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTUREを割り当てる
	void SetParent(CModel *pModel);									//
	D3DXMATRIX &GetMtxWorld(void);									//	マトリックスの取得
	void SetMtxWorld(D3DXMATRIX MtxWorld);							//	マトリックスの設定

	D3DXVECTOR3 VtxMax(void) { return m_vtxMax; }					//	大きさの最大値
	D3DXVECTOR3 VtxMin(void) { return m_vtxMin; }					//	大きさの最小値

	D3DXVECTOR3 Getrot(void) { return m_rot; }						//	向きの取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }						//	位置の取得

	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	位置の設定
	void Setrot(D3DXVECTOR3 rot) { m_rot = rot; }					//	向きの設定

	//メンバ変数
private:
	D3DXMATRIX				m_mtxWorld;						//	ワールドマトリックス
	LPD3DXMESH				m_pMesh;						//	メッシュ情報へのポインタ
	LPD3DXBUFFER			m_pBuffMat;						//	マテリアル情報へのポインタ
	LPDIRECT3DTEXTURE9		*m_pTexture;					//	テクスチャへのポインタ
	DWORD					m_nNumMat;						//	マテリアル情報の数
	MODEL					m_aModel;						//	モデル情報
	D3DXVECTOR3				m_vtxMin;						//	モデルの最小
	D3DXVECTOR3				m_vtxMax;						//	モデルの最大値
	CModel					*m_pParent;						//	親モデルへのポインタ
	D3DXVECTOR3				m_pos;							//	位置
	D3DXVECTOR3				m_rot;							//	向き
};


#endif