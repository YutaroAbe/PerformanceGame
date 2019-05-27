//=============================================================================
//
// ポーズ処理 [pause.h]
// Author :
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PAUSE (4)
#define SELECT_MAX	(3)				// 選択する最大数

//=============================================================================
// クラス定義
//=============================================================================
class CPause : public CScene
{
public:
	CPause();						// コンストラクタ
	~CPause();						// デストラクタ
	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理
	static CPause *Create(void);	// クリエイト
	static  HRESULT Load(void);		// テクスチャをロード
	static void UnLoad(void);		// テクスチャを開放

private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_PAUSE];			// テクスチャ複数
	CScene2D						*m_apScene2D[MAX_PAUSE];		// シーン2Dの変数
	int								m_nNumSelect;					// 選択する項目番号
};
#endif




