//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// プレイヤー処理 [player.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_PLAYER						(2)		// プレイヤーの最大人数
#define MAX_PLAYER_PARTS				(20)	// プレイヤーの最大パーツ数
#define MAX_PLAYER_TEX					(50)	// プレイヤー1つに対するテクスチャの最大数
#define MAX_PLAYER_KEY					(10)	// モーション1つに対するキーフレームの最大数
#define MAX_PLAYER_ATTACK_COLLISION		(20)	// モーション1つに対する攻撃当たり判定の数
#define MAX_PLAYER_DEFENSE_COLLISION	(50)	// モーション1つに対する防御当たり判定の数
#define PLAYER_LIFE						(100)	// プレイヤーの初期体力
#define PLAYER_MAX_SKILL_POINT			(100)	// プレイヤーのスキルポイントの最大値
#define PLAYER_SKILL					(0)		// プレイヤーの初期スキルポイント

#define DEBUG_SPHERE					(0)		// デバッグ用球を使用するかどうか

// プレイヤー移動制限
#define PLAYER_MOVE_RIMIT			(350)		// プレイヤーの離れられる距離
#define PLAYER_MOVE_LIMIT_LEFT		(-400.0f)	// プレイヤーが移動できる左側の限界値
#define PLAYER_MOVE_LIMIT_RIGHT		(400.0f)	// プレイヤーが移動できる右側の限界値

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // 操作の種類
	PLAYER_CONTROLLER_LEFT = 0,		// 左入力
	PLAYER_CONTROLLER_RIGHT,		// 右入力
	PLAYER_CONTROLLER_UP,			// 上入力
	PLAYER_CONTROLLER_LEFT_UP,		// 左上入力
	PLAYER_CONTROLLER_RIGHT_UP,		// 右上入力
	PLAYER_CONTROLLER_DOWN,			// 下入力
	PLAYER_CONTROLLER_ATTACK_SMALL,	// 弱攻撃
	PLAYER_CONTROLLER_ATTACK_BIG,	// 強攻撃
	PLAYER_CONTROLLER_SKILL,		// スキル
	PLAYER_CONTROLLER_MAX,			// 総数
}PLAYER_CONTROLLER;

typedef enum
{ // bool変数の種類
	PLAYER_BOOL_JUMP = 0,			// ジャンプ
	PLAYER_BOOL_SQUAT,				// しゃがみ
	PLAYER_BOOL_LANDING,			// 着地
	PLAYER_BOOL_DAMAGE,				// ダメージ
	PLAYER_BOOL_BLOW,				// ぶっ飛び
	PLAYER_BOOL_GETUP,				// 起き上がり
	PLAYER_BOOL_ATTACK_SMALL,		// 弱攻撃
	PLAYER_BOOL_ATTACK_BIG,			// 強攻撃
	PLAYER_BOOL_SKILL,				// スキル
	PLAYER_BOOL_GUARD,				// ガード
	PLAYER_BOOL_GUARD_HIT,			// ガード成功時
	PLAYER_BOOL_FRONT,				// 前
	PLAYER_BOOL_BACK,				// 後
	PLAYER_BOOL_MAX
}PLAYER_BOOL;

typedef enum
{ // プレイヤーの種別
	PLAYER_TYPE_BRAVE = 0,		// 勇者
	PLAYER_TYPE_DEVIL,			// 魔王
	PLAYER_TYPE_KING,			// 王様
	PLAYER_TYPE_PEOPLE,			// 平民
	PLAYER_TYPE_GOD,			// 平民（神
	PLAYER_TYPE_MAX,			// 総数
}PLAYER_TYPE;

typedef enum
{ // プレイヤーの状態
	PLAYERSTATE_APPEAR = 0,		// 出現状態
	PLAYERSTATE_NORMAL,			// 通常状態
	PLAYERSTATE_DAMAGE,			// ダメージ状態
	PLAYERSTATE_DOWN,			// ぶっ飛び状態
	PLAYERSTATE_GETUP,			// 起き上がり状態
	PLAYERSTATE_DEATH,			// 死亡状態
	PLAYERSTATE_INVINCIBLE,		// 無敵状態
	PLAYERSTATE_MAX				// 総数
}PLAYERSTATE;

typedef enum
{ // 操作プレイヤー
	PLAYER_CONTROL_1P = 0,		// 1P
	PLAYER_CONTROL_2P,			// 2P
	PLAYER_CONTROL_MAX			// 総数
}PLAYER_CONTROL;

typedef enum
{ // 右左どちらにいるか
	PLAYER_SIDE_RIGHT = 0,		// 右
	PLAYER_SIDE_LEFT,			// 左
	PLAYER_SIDE_MAX				// 総数
}PLAYER_SIDE;

typedef enum
{ // プレイヤーの攻撃ランク
	PLAYER_ATTACK_RANK_0 = 0,		// 非上昇状態
	PLAYER_ATTACK_RANK_1,			// 1つ上昇状態
	PLAYER_ATTACK_RANK_2,			// 2つ上昇状態
	PLAYER_ATTACK_RANK_3,			// 3つ上昇状態
	PLAYER_ATTACK_RANK_MAX			// 総数
}PLAYER_ATTACK_RANK;

typedef enum
{ // プレイヤーの防御ランク
	PLAYER_DEFENSE_RANK_0 = 0,		// 非上昇状態
	PLAYER_DEFENSE_RANK_1,			// 1つ上昇状態
	PLAYER_DEFENSE_RANK_2,			// 2つ上昇状態
	PLAYER_DEFENSE_RANK_3,			// 3つ上昇状態
	PLAYER_DEFENSE_RANK_MAX			// 総数
}PLAYER_DEFENSE_RANK;

typedef enum
{ // プレイヤーの回復ランク
	PLAYER_RECOVERY_RANK_0 = 0,		// 非上昇状態
	PLAYER_RECOVERY_RANK_1,			// 1つ上昇状態
	PLAYER_RECOVERY_RANK_2,			// 2つ上昇状態
	PLAYER_RECOVERY_RANK_3,			// 3つ上昇状態
	PLAYER_RECOVERY_RANK_4,			// 4つ上昇状態
	PLAYER_RECOVERY_RANK_5,			// 5つ上昇状態
	PLAYER_RECOVERY_RANK_MAX		// 総数
}PLAYER_RECOVERY_RANK;


typedef enum
{ // モーションの種類
	PLAYER_MOTION_TYPE_NEUTRAL = 0,			// [0]	ニュートラル
	PLAYER_MOTION_TYPE_NEUTRAL_SQUAT,		// [1]	しゃがみニュートラル
	PLAYER_MOTION_TYPE_WALK,				// [2]	移動
	PLAYER_MOTION_TYPE_GUARD,				// [3]	ガード
	PLAYER_MOTION_TYPE_GUARD_SQUAT,			// [4]	しゃがみガード
	PLAYER_MOTION_TYPE_GUARD_AIR,			// [5]	空中ガード
	PLAYER_MOTION_TYPE_BLOW,				// [6]	ぶっ飛び
	PLAYER_MOTION_TYPE_DAMAGE,				// [7]	ダメージ
	PLAYER_MOTION_TYPE_DAMAGE_SQUAT,		// [8]	しゃがみダメージダメージ
	PLAYER_MOTION_TYPE_JUMP_FRONT,			// [9]	ジャンプ前
	PLAYER_MOTION_TYPE_JUMP_UP,				// [10]	ジャンプ上
	PLAYER_MOTION_TYPE_JUMP_BACK,			// [11]	ジャンプ後
	PLAYER_MOTION_TYPE_SQUAT,				// [12]	しゃがみ
	PLAYER_MOTION_TYPE_GETUP,				// [13]	起き上がり
	PLAYER_MOTION_TYPE_LANDING,				// [14]	着地
	PLAYER_MOTION_TYPE_ATTACK_JUMP_SMALL,	// [15]	ジャンプ攻撃[ 弱 ]
	PLAYER_MOTION_TYPE_ATTACK_JUMP_BIG,		// [16]	ジャンプ攻撃[ 強 ]
	PLAYER_MOTION_TYPE_ATTACK_SMALL,		// [17]	攻撃[ 弱 ]
	PLAYER_MOTION_TYPE_ATTACK_BIG,			// [18]	攻撃[ 強 ]
	PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL,	// [19]	しゃがみ攻撃[ 弱 ]
	PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG,	// [20]	しゃがみ攻撃[ 強 ]
	PLAYER_MOTION_TYPE_SKILL,				// [21]	スキル
	PLAYER_MOTION_TYPE_FIGHTING_RIGHT,		// [22]	ファイティングモーション(右
	PLAYER_MOTION_TYPE_FIGHTING_LEFT,		// [23]	ファイティングモーション(左
	PLAYER_MOTION_TYPE_LOSS,				// [24]	負けモーション
	PLAYER_MOTION_TYPE_WIN,					// [25]	勝ちモーション
	PLAYER_MOTION_TYPE_MAX,					// 総数
}PLAYER_MOTION_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}PartsKeyPlayer;

typedef struct
{
	int nFrame;									// キーフレーム
	PartsKeyPlayer aPartsKey[MAX_PLAYER_PARTS];	// パーツごとのキー情報
}KeyPlayer;

typedef struct
{ // 当たり判定用球体
	D3DXVECTOR3 pos;			// 当たり判定の位置
	D3DXVECTOR3 rot;			// 当たり判定の向き
	int nPartsId;				// 当たり判定の親ID
	float fRadius;				// 当たり判定の半径
	int nFrameS;				// 当たり判定の開始フレーム
	int nFrameE;				// 当たり判定の終了フレーム
	int nDamage;				// 当たり判定のダメージ量
	float fDistance;			// 攻撃Hit時の移動量
	bool bUse;					// 当たり判定を使用するかどうか

#if DEBUG_SPHERE
	int nSpherID[MAX_PLAYER];	// デバッグ用円のID
#endif // DEBUG_SPHERE

}CollisionSpherePlayer;

typedef struct
{ // モーション情報
	bool bLoop;														// ループするかどうか
	int nNumKey;													// キー数
	KeyPlayer aKey[MAX_PLAYER_KEY];									// キー情報
	CollisionSpherePlayer collisionA[MAX_PLAYER_ATTACK_COLLISION];	// 攻撃判定用
	int nAllFrame;													// モーション全体のフレーム数
}MotionPlayer;

typedef struct
{ // モデルデータ
	LPD3DXMESH pMesh;				// メッシュ（頂点の集まり）情報へのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアル情報へのポインタ
	DWORD nNumMat;					// マテリアル情報の数
	LPDIRECT3DTEXTURE9 *pTexture;	// モデル一つに対するテクスチャ
#if DEBUG_SPHERE
	int nIDSphere;					// 球体のID
#endif // DEBUG_SPHERE
}PlayerModelData;

typedef struct
{ // プレイヤーの使用モデル情報
	int nModelType;				// どのモデルを使用するか
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3	pos;			// 位置（中心座標）
	D3DXVECTOR3	rot;			// 向き
	D3DXVECTOR3	posMotion;		// モーション位置
	D3DXVECTOR3	rotMotion;		// モーション向き
	D3DXVECTOR3	posAddMotion;	// 加算モーション位置
	D3DXVECTOR3	rotAddMotion;	// 加算モーション向き
	int nIdxModelParent;		// 親モデルのインデックス
}PlayerModel;

typedef struct
{ // プレイヤーのタイプごとの情報
	int nModelParts;												// パーツ数
	float fMoveSpeed;												// 移動速度
	float fJampMove;												// ジャンプ量
	float fRadius;													// 半径
	float fHeight;													// 高さ
	float fDamage;													// ダメージ量
	float fKnockBack;												// ノックバック距離
	PlayerModelData	apPlayer[MAX_PLAYER_PARTS] = {};				// モデルへのポインタ
	MotionPlayer	aMotion[PLAYER_MOTION_TYPE_MAX];				// モーション
	PlayerModel		aModel[MAX_PLAYER_PARTS];						// パーツ情報
	CollisionSpherePlayer collisionD[MAX_PLAYER_DEFENSE_COLLISION];	// 防御判定用
}PlayerTypeData;

typedef struct
{ // プレイヤー情報
	D3DXMATRIX mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3	pos;								// 位置
	D3DXVECTOR3	posOld;								// 前回位置
	D3DXVECTOR3	rot;								// 向き
	D3DXCOLOR col;									// メイン色
	D3DXCOLOR colSub;								// サブ色
	PlayerModel aModel[MAX_PLAYER_PARTS];			// パーツ数
	int nModelParts;								// パーツ数
	D3DXVECTOR3	move;								// 移動量
	float fMoveSpeed;								// 移動速度
	float fJampMove;								// ジャンプ量
	float fRadius;									// 半径
	float fHeight;									// 高さ
	float fCollisionRadius;
	int nIdyShadow;									// 影のID
	PLAYER_TYPE type;								// プレイヤーの種類
	int nLife;										// 体力
	int nSkillPoint;								// スキルポイント
	int nSkillRank;									// スキルランク
	PLAYERSTATE state;								// 状態
	int nCounterState;								// ステータスのカウンター
	PLAYER_MOTION_TYPE MotionType;					// モーションの種類
	PLAYER_MOTION_TYPE MotionTypeOld;				// 前回のモーションの種類
	PLAYER_MOTION_TYPE MotionTypeHit;				// 攻撃を当てた
	PLAYER_SIDE side;								// 右左どちらにいるか
	float fGravity;									// 重力
	bool bBool[PLAYER_BOOL_MAX];					// チェック用
	bool bBoolOld[PLAYER_BOOL_MAX];					// 前回チェック用
	bool bUse;										// 使用しているかどうか
	bool bDisp;										// 描画するかどうか
	int nKeyCnt;									// キーカウント
	int nFrameCounter;								// フレームカウンター
	int nAllFrameCounter;							// 全体のフレームカウンター
	bool bBlend;									// ブレンド中かどうか
	PLAYER_ATTACK_RANK atkRank;						// 攻撃ランク
	PLAYER_DEFENSE_RANK defRank;					// 防御ランク
	int nRecovery;									// 回復量
	bool bAreaLimit[PLAYER_SIDE_MAX];				// 移動可能エリアのぎりにいるかどうか
	bool b2PColor;									// 2PColorを使用するか
}Player;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void InitPlayerTypeData(void);
void UninitPlayerTypeData(void);

void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
void SetPlayerInfo(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
Player *GetPlayer(void);
PlayerTypeData *GetPlayerTypeData(void);
void PlayerMotion(int nPlayerID);
void PlayerMotionTypeSet(int nPlayerID);
void PlayerMotionTypeSet(int nPlayerID, PLAYER_MOTION_TYPE motionType);
void PlayerController(PLAYER_CONTROL control);
bool CollisionAttack(int nPlayerID);
bool CollisionSkillAttack(int nPlayerID);
bool SkillAttack(int nPlayerID);
void CollisionMove(int nPlayerID);
void SetCollisionAttack(int nPlayerType, int nMotionType, int nPartsId, D3DXVECTOR3 pos, float fRadius, int nFrameS, int nFrameE, int nDamage, float fDistance);
void SetCollisionDefense(int nPlayerType, int nPartsId, D3DXVECTOR3 pos, float fRadius);
void HitPlayer(D3DXVECTOR3 HitPos, int nPlayerID, int nDamage, float fDistance, bool bigAttack, bool bSkill);
void CheckMove(int nPlayerID);
void CheckMoveArea(int nPlayerID);
void CheckRot(int nPlayerID);
void CheckGuard(int nPlayerID);
void LoadMotion(void);
int GetMoveRimit(void);
bool GetController(PLAYER_CONTROL control, PLAYER_CONTROLLER Controller);
void LoadPlayerStatus(void);
void AddPlayerLife(int nPlayerID, int nLife);
void AddPlayerSkillPoint(int nPlayerID,int nSkillPoint);
void PlayerBattleResultSave(int nPlayerID);

void PlayerSaveHpSkill(void);
void PlayerSaveHpSkillInit(void);
void PlayerLoadHpSkill(void);

#if DEBUG_SPHERE
void PlayerDebugDeffSphereUpdate(int nPlayerID);
#endif // DEBUG_SPHERE

#endif
