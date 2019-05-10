//=============================================================================
//
// HPバー3D 処理 [hpber3D.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _HPBER3D_H_
#define _HPBER3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene3d.h"	// シーン
#include "enemy.h"		// 敵

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CHpBer3D : public CScene3D
{// シーン3D（親：CScene）
public:
	CHpBer3D();															// コンストラクタ
	~CHpBer3D();														// デストラクタ
																		// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
																		// 生成
	static CHpBer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	static HRESULT Load(void);											// テクスチャの読み込み
	static void Unload(void);											// 破棄

	void SizeChange(int nDamage, CEnemy *m_pEnemy);						// 大きさを変える
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;							// テクスチャ情報へのポインタ
	D3DXMATRIX						m_mtxWorld;							// ワールドマトリックス
	CEnemy							*m_pEnemy;							// 敵
	bool							m_bColChange;						// 色の変更
	int								m_nColFream;						// 色の変更するフレーム
protected:

};

#endif