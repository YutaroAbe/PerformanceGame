//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_ENEMY_0 "data/TEXTURE/ENEMY/enemy001.png"
#define TEXTURE_NAME_ENEMY_1 "data/TEXTURE/ENEMY/enemy002.png"
#define TEXTURE_NAME_ENEMY_2 "data/TEXTURE/ENEMY/enemy003.png"
#define TEXTURE_NAME_ENEMY_3 "data/TEXTURE/ENEMY/enemy004.png"
#define ENEMY_POLIGON_X_000 (25)				//	敵の幅の大きさ000
#define ENEMY_POLIGON_Y_000 (50)				//	敵の縦の大きさ000
#define ENEMY_POLIGON_X_001 (25)				//	敵の幅の大きさ001
#define ENEMY_POLIGON_Y_001 (50)				//	敵の縦の大きさ001
#define MAX_ENEMY (128)							//	敵の使える最大数
#define MAX_ENEMY_TYPE (4)						//	敵の種類

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CEnemy : public CScene2D
{
public:
	typedef enum
	{//	敵の状態
		ENEMYSTATE_NOMAL = 0,	//	通常
		ENEMYSTATE_DAMAGE,		//	ダメージ
		ENEMYSTATE_MAX			//	状態の最大数
	}ENEMYSTATE;

	CEnemy();																//	コンストラクタ
	~CEnemy();																//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,int nType);	//	敵の初期化処理
	void Uninit(void);														//	敵の終了処理
	void Update(void);														//	敵の更新処理
	void Draw(void);														//	敵の描画処理
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);
	static HRESULT Laod(void);												//	テクスチャを読み込む
	static void UnLoad(void);												//	テクスチャの開放
	static int GetNUMENEMY(void);											//	敵の数の取得
	void Hit(int nDamage);
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_ENEMY_TYPE];					//	共通テクスチャのポインタ
	 int m_nType;															//	種類
	 static int m_nNUM_ENEMY;												//	敵の数数える変数
	 int m_nCounterState;													//
protected:
	ENEMYSTATE enemystate;													//	敵の状態
	 D3DXVECTOR3 m_posOld;													//	過去の位置
	 int m_nAICounter;														//	敵の行動パターンのカウント
	 bool m_bBulletAttck;													//	敵が弾を撃っているか
	 int m_nLife;															//	エネミーの体力
};
//=============================================================================
//	エネミータイプ1
//=============================================================================
class CEnemyType000 : public CEnemy
{
public:
	typedef enum
	{//	敵の挙動状態
		MOVE_AI_NONE = 0,		//	通常の動き
		MOVE_AI_LEFT,			//	左に行く動き
		MOVE_AI_RIGHT,			//	右の行く動き
		MOVE_AI_MAX				//	動きの最大数
	}MOVE_AI;
	CEnemyType000();														//	コンストラクタ
	~CEnemyType000();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	敵の初期化処理
	void Uninit(void);														//	敵の終了処理
	 void Update(void);														//	敵の更新処理
	void Draw(void);														//	敵の描画処理
private:
	MOVE_AI move_ai;														//	敵の動きの変数
	bool m_bAttackMove;														//	プレイヤーへの攻撃範囲かどうか

};
//=============================================================================
//	エネミータイプ2
//=============================================================================
class CEnemyType001 : public CEnemy
{
public:
	typedef enum
	{//	敵の挙動状態
		MOVE_AI_NONE = 0,		//	通常の動き
		MOVE_AI_LEFT,			//	左に行く動き
		MOVE_AI_RIGHT,			//	右の行く動き
		MOVE_AI_MAX				//	動きの最大数
	}MOVE_AI;
	CEnemyType001();														//	コンストラクタ
	~CEnemyType001();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	敵の初期化処理
	void Uninit(void);														//	敵の終了処理
	 void Update(void);														//	敵の更新処理
	void Draw(void);														//	敵の描画処理
private:
	MOVE_AI move_ai;														//	敵の動きの変数
	bool m_bAttackMove;														//	プレイヤーへの攻撃範囲かどうか
};

//=============================================================================
//	エネミータイプ3
//=============================================================================
class CEnemyType002 : public CEnemy
{
public:
	typedef enum
	{//	敵の挙動状態
		MOVE_AI_NONE = 0,		//	通常の動き
		MOVE_AI_LEFT,			//	左に行く動き
		MOVE_AI_RIGHT,			//	右の行く動き
		MOVE_AI_MAX				//	動きの最大数
	}MOVE_AI;
	CEnemyType002();														//	コンストラクタ
	~CEnemyType002();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	敵の初期化処理
	void Uninit(void);														//	敵の終了処理
	void Update(void);														//	敵の更新処理
	void Draw(void);														//	敵の描画処理
private:
	MOVE_AI move_ai;														//	敵の動きの変数
	bool m_bAttackMove;														//	プレイヤーへの攻撃範囲かどうか
};

//=============================================================================
//	エネミータイプ4
//=============================================================================
class CEnemyType003 : public CEnemy
{
public:
	typedef enum
	{//	敵の挙動状態
		MOVE_AI_NONE = 0,		//	通常の動き
		MOVE_AI_LEFT,			//	左に行く動き
		MOVE_AI_RIGHT,			//	右の行く動き
		MOVE_AI_MAX				//	動きの最大数
	}MOVE_AI;
	CEnemyType003();														//	コンストラクタ
	~CEnemyType003();														//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);	//	敵の初期化処理
	void Uninit(void);														//	敵の終了処理
	void Update(void);														//	敵の更新処理
	void Draw(void);														//	敵の描画処理
private:
	MOVE_AI move_ai;														//	敵の動きの変数
	bool m_bAttackMove;														//	プレイヤーへの攻撃範囲かどうか
};
#endif