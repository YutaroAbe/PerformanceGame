//=============================================================================
//
// 背景の処理 [bg.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_BG_0 "data/TEXTURE/BG/000.png"			//	一枚目の拝啓
#define TEXTURE_NAME_BG_1 "data/TEXTURE/BG/bg001.png"		//	二枚目の拝啓
#define TEXTURE_NAME_BG_2 "data/TEXTURE/BG/bg002.png"		//	三枚目の拝啓
#define TEXTURE_NAME_BG_3 "data/TEXTURE/BG/bg003.png"		//	四枚目の拝啓
#define MAX_TEXTURE (4)										//	テクスチャの最大数
#define BG_POLIGON_X (10)									//	テクスチャの大きさX軸
#define BG_POLIGON_Y (10)									//	テクスチャの大きさYjiku

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CBg : public CScene
{
public:
	CBg();														//	コンストラクタ
	~CBg();														//	デストラクタ
	HRESULT Init(void);											//	背景の初期化処理
	void Uninit(void);											//	背景の終了処理
	void Update(void);											//	背景の更新処理
	void Draw(void);											//	背景の描画処理
	static HRESULT Laod(void);									//	テクスチャを読み込む
	static void UnLoad(void);									//	テクスチャの開放
	static CBg *Create(void);									//	背景の生成
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEXTURE];			//	共通テクスチャのポインタ
	CScene2D *m_apScene2D[MAX_TEXTURE];							//	2Dポリゴンの変数
	D3DXVECTOR3 m_move;											//	背景の動き
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//	頂点バッファへのポインタ
protected:
};
#endif
