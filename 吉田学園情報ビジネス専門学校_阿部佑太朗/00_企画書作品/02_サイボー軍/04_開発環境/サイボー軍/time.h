//=============================================================================
//
//	タイマーの処理 [time.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_TIME (3)												//	読み込むテクスチャの場所指定
#define TIME_POLIGON_X (10)											//	タイマーの大きさX軸
#define TIMEE_POLIGON_Y (10)										//	タイマーの大きさY軸

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CTime : public CScene
{
public:
	CTime();														//	コンストラクタ
	~CTime();														//	デストラクタ
	HRESULT Init(void);												//	タイマーの初期化処理
	void Uninit(void);												//	タイマーの終了処理
	void Update(void);												//	タイマーの更新処理
	void Draw(void);												//	タイマーの描画処理
	static CTime *Create(void);										//	タイマーの生成
	int GetTime(void);												//	タイマーの取得
	static void AddTime(int nValue);								//	タイマーの設定
private:
	static CNumber *m_apNumber[MAX_TIME];							//	タイマーのポインタ型変数
	static int m_nTime;												//	タイマーの変数
protected:
};
#endif
