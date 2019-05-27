//=============================================================================
//
//　ミッションメッセージの処理 [missionMessage.h]
//	Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _MISSONMESSAGE_H_
#define _MISSONMESSAGE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_MISSONMESSAGE_UI (1)

//=============================================================================
//	マネージャークラス
//=============================================================================
class CMissionMessage
{
public:
	CMissionMessage();														// コンストラクタ
	~CMissionMessage();														// デストラクタ
	HRESULT Init(void);														// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	static  HRESULT Load(void);												// テクスチャをロード
	static void UnLoad(void);												// テクスチャを開放
	static int GetGameText(void);											//ゲームの文字のテキストを出力の取得
	static int GetNumText(void);											//文字の出る順番の取得
private:
	CScene2D *m_apScene2D[MAX_MISSONMESSAGE_UI];
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_MISSONMESSAGE_UI];		// テクスチャ複数
	bool m_bPressState;														//	ボタン押しているかどうか
	static int m_nGameTextCounter;
	static int m_nNumText;													//	文字の出る順番
};

#endif // _MANAGER_H_
