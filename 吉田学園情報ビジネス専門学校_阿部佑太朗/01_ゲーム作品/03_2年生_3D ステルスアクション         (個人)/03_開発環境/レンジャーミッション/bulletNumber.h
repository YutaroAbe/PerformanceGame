//=============================================================================
//
// 弾の弾数の処理 [lifeNumber.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLETNUMBER_H_
#define _BULLETNUMBER_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_LIFENUMBER (2)											//	読み込むテクスチャの場所指定
#define LIFENUM_POLIGON_X (10)										//	スコアの大きさX軸
#define LIFENUM_POLIGON_Y (10)										//	スコアの大きさY軸

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CBulletNumber : public CScene
{
public:
	CBulletNumber();													//	コンストラクタ
	~CBulletNumber();													//	デストラクタ
	HRESULT Init(void);												//	スコアの初期化処理
	void Uninit(void);												//	スコアの終了処理
	void Update(void);												//	スコアの更新処理
	void Draw(void);												//	スコアの描画処理
	static CBulletNumber *Create(void);								//	スコアの生成
	int GetLefeNum(void);											//	スコアの取得
	static void AddNum(int nValue);								//	スコアの設定

private:
	static CNumber *m_apNumber[MAX_LIFENUMBER];						//	スコアのポインタ型変数
	static int m_nNumber;										//	スコアの変数
protected:
};
#endif
