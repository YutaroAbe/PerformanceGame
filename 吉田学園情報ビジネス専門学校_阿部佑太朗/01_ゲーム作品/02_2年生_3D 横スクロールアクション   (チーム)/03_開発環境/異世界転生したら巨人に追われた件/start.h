//=============================================================================
//
// スタート処理 [start.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _START_H_
#define _START_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene3d.h"		// シーン

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStart : public CScene3D
{// シーン3D（親：CScene）
public:
	CStart();														// コンストラクタ
	~CStart();														// デストラクタ
																		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
																		// 生成
	static CStart *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);											// テクスチャの読み込み
	static void Unload(void);											// 破棄

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;							// テクスチャ情報へのポインタ

	int m_AnimCounter;
	int m_AnimPattern;

protected:

};

#endif