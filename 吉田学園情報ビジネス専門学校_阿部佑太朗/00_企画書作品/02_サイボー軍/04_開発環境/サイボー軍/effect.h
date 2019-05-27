//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_EFFECT "data/TEXTURE/EFFCT/effect000.jpg"	//	エフェクトのテクスチャ
#define EFFECT_POLIGON_X (15.0f)								//	エフェクトの横の大きさ
#define EFFECT_POLIGON_Y (15.0f)								//	エフェクトの縦の大きさ

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CEffect : public CScene2D
{
public:
	CEffect();																					//	コンストラクタ
	~CEffect();																					//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos,int nLife, float fRadius, D3DXCOLOR Col);						//	エフェクトの初期化処理
	void Uninit(void);																			//	エフェクトの終了処理
	void Update(void);																			//	エフェクトの更新処理
	 void Draw(void);																			//	エフェクトの描画処理
	static HRESULT Laod(void);																	//	テクスチャを読み込む
	static void UnLoad(void);																	//	テクスチャの開放
	static CEffect *Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR Col);			//	エフェクトの生成

private:
	static LPDIRECT3DTEXTURE9 m_Texture;														//	共通テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;															//	頂点バッファへのポインタ
	int m_nLife;																				//	表示時間(寿命)
	float m_fRadius;																			//	半径(大きさ)
	D3DXCOLOR m_Color;																			//	カラー
};
#endif
