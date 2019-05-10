//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		//	メイン
#include "scene.h"		//	シーン

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CModel;			//	モデル
class CShadow;			//	影
class CHpBer3D;			//	Hpバー3D
class CBullet2D;		//	弾2D

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMPARTS	(30)
#define MAX_NUMMOTION	(30)

//*****************************************************************************
// クラス定義 敵
//*****************************************************************************
class CEnemy : public CScene
{
public:
	typedef enum
	{//	ステータス
		STATE_NONE = 0,						//	通常
		STATE_DAMAGE,						//	ダメージ
		STATE_DEATH,						//	死亡
		STATE_MAX							//	ステータスの最大数
	}STATE;

	typedef enum
	{
		AI_NONE,		//	何もしない
		AI_UP,			//	前に進む
		AI_DOWN,		//	後ろに進む
		AI_LEFT,		//	左に進む
		AI_RIGHT,		//	右に進む
		AI_FOLLOWING,	//	プレイヤーに追従する
		AI_ATTACK,		//	攻撃する
		AI_MAX
	}ENEMY_AI;


	typedef struct
	{//キー要素
		float fposX;						//	位置のX
		float fposY;						//	位置のY
		float fposZ;						//	位置のZ
		float frotX;						//	回転のX
		float frotY;						//	回転のY
		float frotZ;						//	回転のZ
	}KEY;

	typedef struct
	{//キー情報
		int nFrame;							//	キーフレーム
		KEY aKey[MAX_NUMPARTS];				//	各キー要素
	}KEY_INFO;

	typedef struct
	{//モーション情報
		bool bLoop;							//	ループするかしないか
		int nNumKey;						//	キーの番号
		KEY_INFO aKayInfo[MAX_NUMMOTION];	//	各キー情報
	}MOTION_INFO;

	CEnemy();														//	コンストラクタ
	~CEnemy();														//	デストラクタ
	HRESULT Init(void);												//	初期化
	void Uninit(void);												//	終了処理
	void Update(void);												//	更新処理
	void Draw(void);												//	描画処理
	//	     位置　           向き　  ライフ　  敵の種類　追従する範囲 　動く範囲　  敵の動きの選択
	static CEnemy *Create	//	敵の生成
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nType, int nMoveLength,float fNoneSpeed, float fFormingSpeed, ENEMY_AI nAISelect);
	static HRESULT Load(void);										//	読み込みの処理
	static void UnLoad(void);										//	解放の処理
	D3DXVECTOR3 GetposOld(void) { return m_posOld; }				//	位置の取得
	D3DXVECTOR3 Getpos(void) { return m_pos; }						//	位置の取得
	D3DXVECTOR3 GetInitpos(void) { return m_InitPos; }				//	位置の取得
	D3DXVECTOR3 Getrot(void) { return m_rot; }						//	回転の取得
	D3DXVECTOR3 Getmove(void) { return m_move; }					//	動きの取得
	int Gettype(void) { return m_nType; }							//	種類の取得
	bool GetLand(void) { return m_bLand; };							//	乗っているかの取得
	int GetLife(void) { return m_nLife; }							//	HPの取得
	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	位置の設定
	void SetposOld(D3DXVECTOR3 posOld) { m_pos = posOld; }			//	過去位置の設定
	void Setrot(D3DXVECTOR3 rot) { m_rot = rot; }					//	向きの設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				//	向きの設定

	bool GetHit(void) { return m_bHit; }							//	当たったかの取得
	float GetLength(void);											//	プレイヤー都の距離
																	//  大きさ取得
	D3DXVECTOR3 Getsize(int nNum) { if (nNum == 0) { return m_vtxMax; /*0番最大値*/ } else { return m_vtxMin/*1最小値*/; } }
	void UpdateMotion(void);										//	モーションの更新
																	//	ファイル読み込みに関する関数
	void FileLoad(void);											//	ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);						//	1行読み込み
	char *GetLineTop(char *pStr);									//	行の先頭を取得
	int  PopString(char *pStr, char *pDest);						//	行の最後を切り捨

		//	キャラクターの管理する関数
																	//	当たり判定の管理
	void ManagementCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void ManagementAddRod(D3DXVECTOR3 rotDest);						//角度を加算する

																	//	当たり判定
	void Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	//	敵同士の当たり判定
	void OtherEnemyCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void HitDamege(int Damege);										//	攻撃のダメージ

private:
	//	モデルに必要な変数
	static LPD3DXMESH			m_pMeshModel[MAX_NUMPARTS];			//	メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_NUMPARTS];		//	マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	*m_pTextureModel[MAX_NUMPARTS];		//	テクスチャへのポインタ
	static DWORD				m_nNumMatModel[MAX_NUMPARTS];		//	マテリアル情報の数
																	//	モーション関連変数
	char						m_aFileNameModel[MAX_NUMPARTS][256];//	読み込むモデルの名前
	KEY_INFO					*m_pKeyInfo[MAX_NUMMOTION];			//	キー情報へのポインタ
	int							m_nKey;								//	現在のキーナンバー
	int							m_nCountFlame;						//	フレーム数
	int							m_nNumParts;						//	パーツ数
	int							m_aIndexParent[MAX_NUMPARTS];		//	親のインデックス
	KEY							m_aKayOffset[MAX_NUMPARTS];			//	オフセット情報
	MOTION_INFO					m_aMotionInfo[MAX_NUMMOTION];		//	モーション情報
	bool						m_bMotionEnd;						//	モーションの終了
	D3DXVECTOR3					m_OffSetPos[MAX_NUMPARTS];			//	オフセット位置
	int							m_nNumModel;						//	モデルの数
	int							m_nCntNumMosion;					//	テキストに書かれているモーションの数
	int							m_nCouterFreamMax[MAX_NUMMOTION];	//	モーションのフレームの合計値
	int							m_nCntMosionChange;					//	モーションの切り替えるカウンター
	//	キャラクターの情報
	D3DXMATRIX					m_mtxWorld;							//	ワールドマトリックス
	D3DXVECTOR3					m_pos;								//	位置
	D3DXVECTOR3					m_posOld;							//	前回の位置
	D3DXVECTOR3					m_InitPos;							//	初期の位置
	D3DXVECTOR3					m_rot;								//	向き
	D3DXVECTOR3					m_move;								//	動き
	D3DXVECTOR3					m_vtxMax;							//	判定最大
	D3DXVECTOR3					m_vtxMin;							//	判定最小
	D3DXVECTOR3					m_Scale;							//	拡大縮小用変数
	bool						m_bHit;								//	当たり判定の当たったかどうか
	int							m_nLife;							//	体力
	int							m_nType;							//	敵の種類
	int							m_nDameCuter;						//　ダメージカウンター
	int							m_nDispCuter;						//	死んだときのカウンター
	STATE						m_state;							//	ステータス
	ENEMY_AI					m_AIEnemy;							//	敵のAIの処理
	D3DXVECTOR3					m_LengthDawn;						//	プレイヤーとの距離を短くする
	static	int					m_nNumPartsMax;						//	partsの最大数
	bool						m_bLand;							//	乗ってるかどうか
	//	プレイヤーに使用するクラス
	CShadow						*m_pShadow;							//	影
	CHpBer3D					*m_pHpBer3D;						//	Hpバー3D
protected:
	CModel						*m_apModel[MAX_NUMPARTS];			//	モデルのポインタ
	int							m_nMotionType;						//	モーションの種類
	int							m_nMotionTypeOld;					//	モーションの過去の種類
	float						m_fAngle;							//	角度
	int							m_nMoveLength;						//	移動する距離を距離
	bool						m_bOtherEnemyHit;					//	敵同士当たった場合
	bool						m_bPStealthMode;					//	プレイヤーがステルスモードに入った場合
	int							m_nAISelect;						//	動きの選択
	float						m_fNoneSpeed;						//	何もしていない時の速さ
	float						m_fFormingSpeed;					//	追従する時の速さ
	bool						m_bWallHit;							//	壁に当たったかどうか
	static bool					m_bLastObDisp;						//	最後のオブジェクトがあるかどうか

};

//*****************************************************************************
// クラス定義 　敵 ROBOT 000
//*****************************************************************************
class CEnemyRobotNomal : public CEnemy
{//	親　CEnemy 敵
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,					//	ニュートラルモーション
		MOSION_MOVE,						//	移動モーション
		MOSION_DAMEGA,						//	ダメージモーション
		MOSION_ATTACK,						//	攻撃モーション
		MOSION_MAX							//	最大数
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	何もしない
		AI_UP,			//	前に進む
		AI_DOWN,		//	後ろに進む
		AI_LEFT,		//	左に進む
		AI_RIGHT,		//	右に進む
		AI_FOLLOWING,	//	プレイヤーに追従する
		AI_ATTACK,		//	攻撃する
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotNomal();							//	コンストラクタ
	~CEnemyRobotNomal();						//	デストラクタ
	HRESULT Init(void);							//	初期化処理
	void Uninit(void);							//	終了処理
	void Update(void);							//	更新処理
	void Draw(void);							//	描画処理
	void ManagementMovement(int nAIdata_Move);						//	動きの管理[	敵の動き管理	]
	void ManagementSetMosion(void);									//	モーションの設定管理
	bool  CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	STATE						m_state;		//	ステータス
	ENEMY_AI					m_AIEnemy;							//	敵のAIの処理
	MOSION_STATE				m_MosionState;						//	モーションの状態
	bool						m_bAttack;							//	攻撃したかどうか
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rotDest;							//	目的の向き
	int							m_nEffectCounter;					//	エフェクトを出すカウンター
};

//*****************************************************************************
// クラス定義 　敵 ROBOT 弾撃つ
//*****************************************************************************
class CEnemyRobotBullet : public CEnemy
{//	親　CEnemy 敵
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,					//	ニュートラルモーション
		MOSION_MOVE,						//	移動モーション
		MOSION_DAMEGA,						//	ダメージモーション
		MOSION_ATTACK,						//	攻撃モーション
		MOSION_MAX							//	最大数
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	何もしない
		AI_UP,			//	前に進む
		AI_DOWN,		//	後ろに進む
		AI_LEFT,		//	左に進む
		AI_RIGHT,		//	右に進む
		AI_FOLLOWING,	//	プレイヤーに追従する
		AI_ATTACK,		//	攻撃する
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotBullet();						//	コンストラクタ
	~CEnemyRobotBullet();						//	デストラクタ
	HRESULT Init(void);							//	初期化処理
	void Uninit(void);							//	終了処理
	void Update(void);							//	更新処理
	void Draw(void);							//	描画処理
	void ManagementMovement(int nAIdata_Move);						//	動きの管理[	敵の動き管理	]
	void ManagementSetMosion(void);									//	モーションの設定管理
private:
	STATE						m_state;		//	ステータス
	ENEMY_AI					m_AIEnemy;							//	敵のAIの処理
	MOSION_STATE				m_MosionState;						//	モーションの状態
	bool						m_bAttack;							//	攻撃したかどうか
	int							m_nBulletCunter;					//	弾のカウンター
	CBullet2D					*m_pBullet2D;						//	弾2D
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rotDest;							//	目的の向き

};

//*****************************************************************************
// クラス定義 　敵 ROBOT　棘
//*****************************************************************************
class CEnemyRobotSpine : public CEnemy
{//	親　CEnemy 敵
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,					//	ニュートラルモーション
		MOSION_MOVE,						//	移動モーション
		MOSION_DAMEGA,						//	ダメージモーション
		MOSION_MAX							//	最大数
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	何もしない
		AI_UP,			//	前に進む
		AI_DOWN,		//	後ろに進む
		AI_LEFT,		//	左に進む
		AI_RIGHT,		//	右に進む
		AI_FOLLOWING,	//	プレイヤーに追従する
		AI_ATTACK,		//	攻撃する
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotSpine();						//	コンストラクタ
	~CEnemyRobotSpine();						//	デストラクタ
	HRESULT Init(void);							//	初期化処理
	void Uninit(void);							//	終了処理
	void Update(void);							//	更新処理
	void Draw(void);							//	描画処理
	void ManagementMovement(int nAIdata_Move);						//	動きの管理[	敵の動き管理	]
	void ManagementSetMosion(void);									//	モーションの設定管理
	bool  CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	STATE						m_state;		//	ステータス
	ENEMY_AI					m_AIEnemy;							//	敵のAIの処理
	MOSION_STATE				m_MosionState;						//	モーションの状態
	bool						m_bAttack;							//	攻撃したかどうか
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rotDest;							//	目的の向き
	float						m_fAddRot;							//	回転の加算
};

//*****************************************************************************
// クラス定義 　敵 ROBOT　下に弾を撃つ
//*****************************************************************************
class CEnemyRobotUndeBulletr : public CEnemy
{//	親　CEnemy 敵
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,					//	ニュートラルモーション
		MOSION_MOVE,						//	移動モーション
		MOSION_DAMEGA,						//	ダメージモーション
		MOSION_MAX							//	最大数
	}MOSION_STATE;
	typedef enum
	{
		AI_NONE,		//	何もしない
		AI_UP,			//	前に進む
		AI_DOWN,		//	後ろに進む
		AI_LEFT,		//	左に進む
		AI_RIGHT,		//	右に進む
		AI_FOLLOWING,	//	プレイヤーに追従する
		AI_ATTACK,		//	攻撃する
		AI_MAX
	}ENEMY_AI;
	CEnemyRobotUndeBulletr();					//	コンストラクタ
	~CEnemyRobotUndeBulletr();					//	デストラクタ
	HRESULT Init(void);							//	初期化処理
	void Uninit(void);							//	終了処理
	void Update(void);							//	更新処理
	void Draw(void);							//	描画処理
	void ManagementMovement(int nAIdata_Move);						//	動きの管理[	敵の動き管理	]
	void ManagementSetMosion(void);									//	モーションの設定管理
private:
	STATE						m_state;							//	ステータス
	ENEMY_AI					m_AIEnemy;							//	敵のAIの処理
	MOSION_STATE				m_MosionState;						//	モーションの状態
	bool						m_bAttack;							//	攻撃したかどうか
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rotDest;							//	目的の向き
	int							m_nBulletCunter;					//	弾のカウンター
	CBullet2D					*m_pBullet2D;						//	弾2D
	float						m_fAddPos;							//	位置の加算
	int							m_nEffectCounter;					//	エフェクトが出るカウンタ
};

//*****************************************************************************
// クラス定義 　最後のオブジェクト
//*****************************************************************************
class CEnemyLastObj: public CEnemy
{//	親　CEnemy 敵
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,					//	ニュートラルモーション
		MOSION_MAX							//	最大数
	}MOSION_STATE;

	CEnemyLastObj();							//	コンストラクタ
	~CEnemyLastObj();							//	デストラクタ
	HRESULT Init(void);							//	初期化処理
	void Uninit(void);							//	終了処理
	void Update(void);							//	更新処理
	void Draw(void);							//	描画処理

private:
	STATE						m_state;							//	ステータス
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rotDest;							//	目的の向き
	int							m_nEffectCounter;					//	エフェクトが出るカウンタ
};

#endif