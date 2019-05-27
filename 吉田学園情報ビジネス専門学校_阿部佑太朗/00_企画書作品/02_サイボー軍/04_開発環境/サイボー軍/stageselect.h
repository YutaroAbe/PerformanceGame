//=============================================================================
//
//　ステージの選択の処理 [stageselect.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_STAGESELECT_UI (8)
#define MAX_STAGESELECT (4)

//=============================================================================
//	マネージャークラス
//=============================================================================
class CStageSelect
{
public:
	CStageSelect();																// コンストラクタ
	~CStageSelect();																// デストラクタ
	HRESULT Init(void);														// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static  HRESULT Load(void);												// テクスチャをロード
	static void UnLoad(void);												// テクスチャを開放
	static int GetNumSelect(void);											// 選択する番号の取得
	static int GetSelWordCounter(void);										//　セレクトの文字列表示カウンターの取得
private:
	CScene2D						*m_apScene2D[MAX_STAGESELECT_UI];	//	シーン2Dのポインタ型変数
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_STAGESELECT_UI];		// テクスチャ複数
	static int						m_nNumSelect;						// 選択する項目番号
	static int						m_nSelectWordCounter;				//　セレクトの文字列表示カウンター
	bool m_bPress;
};

#endif // _MANAGER_H_
