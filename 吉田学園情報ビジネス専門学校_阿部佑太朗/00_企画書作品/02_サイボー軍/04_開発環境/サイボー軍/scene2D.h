//=============================================================================
//
// 2Dポリゴン処理 [scene2D.h]
// Author :
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "main.h"
#include "scene.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_POLIGON (2)

//=============================================================================
//	2Dポリゴンクラス（シーンの派生クラス）
//=============================================================================
class CScene2D : public CScene
{
public:
	CScene2D();																			//	コンストラクタ
	CScene2D(int nPriarity);															//	コンストラクタ
	~CScene2D();																		//	デストラクタ
	HRESULT Init(void);																	//	2Dポリゴンの初期化処理
	void Uninit(void);																	//	2Dポリゴンの終了処理
	void Update(void);																	//	2Dポリゴンの更新処理
	void Draw(void);																	//	2Dポリゴンの描画処理
	void BindTexture(LPDIRECT3DTEXTURE9		pTexture);									//	共通テクスチャを割り当てる

	void ColorChange(D3DXCOLOR m_Col);													//	カラーの変更
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);												//	バッファの取得
	void BGMove(D3DXVECTOR3 move);														//	背景動かす

	int GetType(void);
	int GetLife(void);																	//	ライフポイントの取得
	D3DXVECTOR3 GetPosition(void);														//	2Dポリゴンの座標取得
	D3DXVECTOR3 GetMoveing(void);
	 void SetPosition(D3DXVECTOR3 pos, float PolygonSizeX, float PolygonSizeY);
	float GetfWindth(void);
	 float GetfHeight(void);
	 void SetLife(int nLife);															//	ライフポイントの設定
	 void SetType(int nType);
	 void SetWindthHeigth(float fWindth, float m_fHeight);								//	幅と高さの設定
	void SetTexture(D3DXVECTOR2 *pTex);
	void SetVtxPosition(D3DXVECTOR3 *pPos,D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR *color);
	 void HitDamage(int nDamage);														//	プレイヤーのダメージ設定
private:
	LPDIRECT3DTEXTURE9		m_pTexture;													// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;													// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;														// ポリゴンの位置
	D3DXVECTOR3				m_move;														// ポリゴンの動き
	int m_nLife;																		//	ライフポイント
	int m_nType;
	 float m_fWindth;																	//	幅
	 float m_fHeight;																	//	高さ
protected:
	void SetAnimation(int PatternAnim, float Split, int SplitAnim);						//	アニメーションの設定
	void InitAnimationTex(float Split);													//	アニメーションのテクスチャの初期化設定

};
#endif