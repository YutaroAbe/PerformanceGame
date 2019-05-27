//=============================================================================
//
// 体力処理 [number.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_LIFE "data/TEXTURE/GAMEUI/HP101.png"
#define NUMBER_POLIGON_X (10)
#define NUMBER_POLIGON_Y (10)

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CLife : CScene2D
{
public:
	CLife();														//	コンストラクタ
	~CLife();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length);				//	弾の初期化処理（位置、半径）
	 void Uninit(void);												//	弾の終了処理
	void Update(void);												//	弾の更新処理
	void Draw(void);												//	弾の描画処理
	static HRESULT Laod(void);										//	テクスチャを読み込む
	static void UnLoad(void);										//	テクスチャの開放
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length);		//	数字の生成（位置、半径）
	static void BindTexture(LPDIRECT3DTEXTURE9	pTexture);

private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	共通テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								//  頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;									//  ポリゴンの位置
	D3DXVECTOR3				m_Length;								//	半径
	int m_nLife = CPlayer::GetLife();								//	プレイヤーの体力
protected:
};
#endif
