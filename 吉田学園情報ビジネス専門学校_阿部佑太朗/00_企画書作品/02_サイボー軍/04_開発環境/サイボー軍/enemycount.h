//=============================================================================
//
//	エネミー数のカウントの処理 [enemycount.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMYCOUNT_H_
#define _ENEMYCOUNT_H_

#include "main.h"
#include "scene2D.h"
#include "number.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_ENEMYCOUNT (3)												//	読み込むテクスチャの場所指定
#define ENEMYCOUNT_POLIGON_X (10)											//	タイマーの大きさX軸
#define ENEMYCOUNT_POLIGON_Y (10)										//	タイマーの大きさY軸

//=============================================================================
//	スコアクラス（シーンの派生クラス）
//=============================================================================
class CEnemycount : public CScene
{
public:
	CEnemycount();													//	コンストラクタ
	~CEnemycount();													//	デストラクタ
	HRESULT Init(void);												//	タイマーの初期化処理
	void Uninit(void);												//	タイマーの終了処理
	void Update(void);												//	タイマーの更新処理
	void Draw(void);												//	タイマーの描画処理
	static CEnemycount *Create(void);								//	タイマーの生成
	int GetTime(void);												//	タイマーの取得
	static void AddEnemyCount(int nValue);								//	タイマーの設定
private:
	static CNumber *m_apNumber[MAX_ENEMYCOUNT];						//	タイマーのポインタ型変数
	static int m_nEnemyCount;												//	タイマーの変数
protected:
};
#endif
