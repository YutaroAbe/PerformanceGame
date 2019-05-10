//=============================================================================
//
// スコアの処理 [score.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_SCORE (8)												//	読み込むテクスチャの場所指定
#define SCORE_POLIGON_X (10)										//	スコアの大きさX軸
#define SCORE_POLIGON_Y (10)										//	スコアの大きさY軸

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CScore : public CScene
{
public:
	CScore();														//	コンストラクタ
	~CScore();														//	デストラクタ
	HRESULT Init(void);												//	スコアの初期化処理
	void Uninit(void);												//	スコアの終了処理
	void Update(void);												//	スコアの更新処理
	void Draw(void);												//	スコアの描画処理
	static CScore *Create(void);									//	スコアの生成
	int GetScore(void);												//	スコアの取得
	static void AddScore(int nValue);								//	スコアの設定

private:
	static CNumber *m_apNumber[MAX_SCORE];									//	スコアのポインタ型変数
	static int m_nScore;											//	スコアの変数
protected:
};
#endif
