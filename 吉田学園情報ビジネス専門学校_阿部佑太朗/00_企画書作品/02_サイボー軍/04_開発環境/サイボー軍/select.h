//=============================================================================
//
//　セレクトの処理 [select.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_SELECT_UI (7)
#define MAX_SELECT (3)

//=============================================================================
//	マネージャークラス
//=============================================================================
class CSelect
{
public:
	CSelect();																// コンストラクタ
	~CSelect();																// デストラクタ
	HRESULT Init(void);														// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static  HRESULT Load(void);												// テクスチャをロード
	static void UnLoad(void);												// テクスチャを開放
	static int GetNumSelect(void);											// 選択する番号の取得
	static int GetSelWordCounter(void);										//　セレクトの文字列表示カウンターの取得
private:
	CScene2D						*m_apScene2D[MAX_SELECT_UI];	//	シーン2Dのポインタ型変数
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_SELECT_UI];		// テクスチャ複数
	static int						m_nNumSelect;					// 選択する
	static int						m_nSelectWordCounter;			//　セレクトの文字列表示カウンター
	int m_nNextCounter;												//	画面が止まっていたらタイトルに戻る処理
	bool m_bPress;													//	決定ボタンを押している状態か
};

#endif // _MANAGER_H_
