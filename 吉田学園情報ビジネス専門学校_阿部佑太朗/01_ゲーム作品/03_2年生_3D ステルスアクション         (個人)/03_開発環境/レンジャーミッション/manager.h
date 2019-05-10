//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER		(2)								// プレイヤーの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputKeyboard;	// キーボード
class CInputDIPad;		// DIパッド
class CInputXPad;		// Xパッド
class CRenderer;		// レンダラー
class CCamera;			// カメラ
class CLight;			// ライト
class CTitle;			// タイト
class CGame;			// ゲーム
class CResult;			// リザルト
class CSelectMode;		// セレクトモード
class CSound;			// サウンド

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{// マネージャー
public:
	typedef enum
	{// モード
		MODE_NONE = 0,		// 何もしていない
		MODE_TITLE,			// タイトル
		MODE_SELECTMODE,	// タイトル
		MODE_GAMETUTO,		// ゲームチュートリアルステージ
		MODE_GAMESTAGE000,	// ゲームステージ1
		MODE_GAMESTAGE001,	// ゲームステージ2
		MODE_GAMESTAGE002,	// ゲームステージ3
		MODE_OVER,			// リザルト
		MODE_CLEAR,			// クリア
		MODE_MAX
	}MODE;

	CManager();											// コンストラクタ
	virtual ~CManager();								// デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	virtual void Uninit(void);							// 終了処理
	virtual void Update(void);							// 更新処理
	virtual void Draw(void);							// 描画処理
	static CSound *GetSound(void)					 { return m_pSound; }			// サウンド取得
	static CInputKeyboard *GetInputKeyboard(void)	{ return m_pInputKeyboard; }	// キーボード取得
	static CInputDIPad *GetInputDIPad(void)			{ return m_pInputDIPad; }		// DIパッド取得
	static CInputXPad *GetInputXPad(void)			{ return m_pInputXPad; }		// Xパッド取得
	static CRenderer *GetRenderer(void)				{ return m_pRenderer; }			// レンダラー取得
	static CCamera *GetCamera(void)					{ return m_pCamara; }			// カメラ取得
	static CLight *GetLight(void)					{ return m_pLight; }			// ライト取得

	static void SetMode(MODE mode);						// モード設定
	static MODE GetMode(void) { return m_mode; }		// モード取得

	static CDebugProcLEFT *m_CDebugProcLeft;			//	デバック左用ログ
	static CDebugProcRIGHT *m_CDebugProcRight;			//	デバック右用ログ

private:

	static MODE m_mode;									// モード

	static CInputKeyboard	*m_pInputKeyboard;			// キーボード
	static CInputDIPad		*m_pInputDIPad;				// DIパッド
	static CInputXPad		*m_pInputXPad;				// Xパッド
	static CCamera			*m_pCamara;					// カメラ
	static CLight			*m_pLight;					// ライト
	static CRenderer		*m_pRenderer;				// レンダラー
	static CSound			*m_pSound;					// サウンド

	static CTitle			*m_pTitle;					// タイトル
	static CSelectMode		*m_pSelectMode;				// セレクトモード
	static CGame			*m_pGame;					// ゲーム
	static CResult			*m_pResult;					// リザルト
	static int				m_nPlayerLife;				//	プレイヤーのライフ
protected:

};

#endif