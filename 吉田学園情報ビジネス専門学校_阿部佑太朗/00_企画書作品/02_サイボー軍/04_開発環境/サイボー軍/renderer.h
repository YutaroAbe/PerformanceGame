//=============================================================================
//
// レンダー処理 [renderer.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
//レンダリングクラス
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();													// コンストラクタ
	~CRenderer();													// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	LPDIRECT3DDEVICE9 GetDevice(void);								// デバイスの取得
	void DrawSelect(void);											// セレクトの説明欄文字列
	void DrawStageSelect(void);										// ステージセレクトの説明欄文字列
	void DrawGameTutorial(void);									// ゲームのチュートリアルの説明欄文字列
private:

#ifdef _DEBUG
	void DrawFPS(void);
	void DrawPosition(void);
#endif
	CManager				*m_pManager;								//	マネージャーのポインタ型変数
	LPDIRECT3D9				m_pD3D;										// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	    m_pD3DDevice;								// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;									// フォントへのポインタ
	LPD3DXFONT				m_pDebugFont;								// フォントへのポインタ
};
#endif	// _RENDERER_H_
