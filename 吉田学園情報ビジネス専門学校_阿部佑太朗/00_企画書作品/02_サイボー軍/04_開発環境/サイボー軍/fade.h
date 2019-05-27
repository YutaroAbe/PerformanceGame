//=============================================================================
//
//  フェードの処理 [fade.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_FADE_0 "data/TEXTURE/bg004.png"
#define FADE_POLIGON_X (10)
#define FADE_POLIGON_Y (10)
#define BG_WIDTH   (SCREEN_WIDTH)				//背景の幅
#define BG_HEIGHT   (SCREEN_HEIGHT)				//背景の高さ

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CFade
{
public:
	typedef enum
	{//フェイドの状態
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;

	CFade();													//	コンストラクタ
	~CFade();													//	デストラクタ
	void Init(CManager::MODE modeNext);							//	フェイドの初期化処理
	void Uninit(void);											//	フェイドの終了処理
	void Update(void);											//	フェイドの更新処理
	void Draw(void);											//	フェイドの描画処理
	static HRESULT Laod(void);									//	テクスチャを読み込む
	static void UnLoad(void);									//	テクスチャの開放
	//static CFade *Create(CManager::MODE modenext);				//	フェイドの生成
	FADE m_fade;												//	フェイドの状態
	void SetFade(CManager::MODE modeNext);						//	次に出す画面
private:
	static LPDIRECT3DTEXTURE9 m_Texture;						//	共通テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//	頂点バッファへのポインタ
	 CManager::MODE  m_modenext;								//	モードの遷移
	D3DXCOLOR m_colorFade;

protected:
};
#endif
