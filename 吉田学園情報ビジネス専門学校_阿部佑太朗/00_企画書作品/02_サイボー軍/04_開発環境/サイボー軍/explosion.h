//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_EXPLPSION "data/TEXTURE/EXPLOSION/s_uzu.png"
#define EXPLOSION_POLIGON_X (10)
#define EXPLOSION_POLIGON_Y (10)

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CExplosion : public CScene2D
{
public:
	CExplosion();													//	コンストラクタ
	~CExplosion();													//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);									//	弾の初期化処理
	void Uninit(void);												//	弾の終了処理
	void Update(void);												//	弾の更新処理
	void Draw(void);												//	弾の描画処理
	static HRESULT Laod(void);										//	テクスチャを読み込む
	static void UnLoad(void);										//	テクスチャの開放
	static CExplosion *Create(D3DXVECTOR3 pos);						//	弾の生成

private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	共通テクスチャのポインタ
	 int m_CounterAnim;												//	アニメーションカウンター
	 int m_PatternAnim;												//	アニメーションパターン
protected:

};
#endif
