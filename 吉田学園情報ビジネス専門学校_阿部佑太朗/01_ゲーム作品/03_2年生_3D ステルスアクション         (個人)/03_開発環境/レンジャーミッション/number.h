//=============================================================================
//
// 数字０～9の処理 [number.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_NUMBER_0 "data/TEXTURE/number000.png"			//	読み込むテクスチャの場所指定

#define MAX_NUMBER_TEXTURE (3)										//	テクスチャの最大数
#define NUMBER_POLIGON_X (10)										//	数字の大きさX軸
#define NUMBER_POLIGON_Y (10)										//	数字の大きさY軸

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CNumber
{
public:
	CNumber();														//	コンストラクタ
	~CNumber();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Length);				//	数字の初期化処理（位置、半径）
	void Uninit(void);												//	数字の終了処理
	void Update(void);												//	数字の更新処理
	void Draw(void);												//	数字の描画処理
	static HRESULT Laod(void);										//	テクスチャを読み込む
	static void UnLoad(void);										//	テクスチャの開放
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Length);	//	数字の生成（位置、半径）
	static void BindTexture(LPDIRECT3DTEXTURE9	pTexture);			//	テクスチャの割り当て
	 void SetNumber(int nNumber);									//	番号の設定
	 static int GetNumNumber(void);									//	番号の作られた数の取得
private:
	static LPDIRECT3DTEXTURE9 m_Texture;							//	共通テクスチャのポインタ
	 LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//  頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;									//  ポリゴンの位置
	D3DXVECTOR3				m_Length;								//	半径
	static int m_NumNumber;											//	番号の作られた数の取得
protected:
};
#endif
