//=============================================================================
//
//　リザルトの処理 [result.h]
//	Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_RESULT_UI (5)

//=============================================================================
//	マネージャークラス
//=============================================================================
class CResult
{
public:

	typedef enum
	{
		GAMESTATE_NOMAL = 0,
		GAMESTATE_OVER,
		GAMESTATE_CLEAR,
		GAMESTATE_MAX
	}GAMESTATE;

	CResult();																// コンストラクタ
	~CResult();																// デストラクタ
	HRESULT Init(void);														// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static  HRESULT Load(void);												// テクスチャをロード
	static void UnLoad(void);												// テクスチャを開放
private:
	CScene2D *m_apScene2D[MAX_RESULT_UI];
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_RESULT_UI];				// テクスチャ複数
	GAMESTATE gamestate;													//	ゲームの状態
	float m_fGameOverCounter;												//	ゲームオーバー表示カウンター
	int m_nCounterAnim;														//
	int m_nPatternAnim;														//	アニメーションカウンター
	bool m_bPressState;														//	ボタン押しているかどうか
};

#endif // _MANAGER_H_
