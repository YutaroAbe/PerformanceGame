//=============================================================================
//
//　タイトルの処理 [title.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_TITLE_UI (3)

//=============================================================================
//	マネージャークラス
//=============================================================================
class CTitle
{
public:
	CTitle();																// コンストラクタ
	~CTitle();																// デストラクタ
	 HRESULT Init(void);													// 初期化処理
	 void Uninit(void);														// 終了処理
	 void Update(void);														// 更新処理
	 void Draw(void);														// 描画処理
	static  HRESULT Load(void);												// テクスチャをロード
	static void UnLoad(void);												// テクスチャを開放
private:
	 CScene2D *m_apScene2D[MAX_TITLE_UI];
	 static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TITLE_UI];				// テクスチャ複数
	 int m_nCounterAnim[3];													//
	 int m_nPatternAnim[3];
	 bool m_bPressState;
};

#endif // _MANAGER_H_
