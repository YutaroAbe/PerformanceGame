//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// プレイヤー処理 [player.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "game.h"
#include "player.h"
#include "input.h"
#include "light.h"
#include "gamepad.h"
#include "camera.h"
#include "sound.h"
#include "shadow.h"
#include "meshBattleField.h"
#include "battle.h"
#include "meshSphere.h"
#include "cardModel.h"
#include "fade.h"
#include "hpGage.h"
#include "spGage.h"
#include "effect.h"
#include "particle.h"
#include "textureanim.h"
#include "gamefade.h"
#include "message.h"
#include "timer.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define PLAYER_MOVE_SPEED			(0.5f)		// プレイヤーの移動スピード初期値
#define PLAYER_MOVE_INERTIA			(0.1f)		// プレイヤーの移動の慣性
#define PLAYER_SPIN_INERTIA			(0.5f)		// プレイヤーの回転の慣性
#define PLAYER_GRAVITY				(0.5f)		// プレイヤーにかかる重力
#define PLAYER_JUMP_MOVE			(15.0f)		// プレイヤーのジャンプ力の初期値
#define PLAYER_COLISION_RADIUS		(10.0f)		// プレイヤーの当たり判定の半径の初期値
#define PLAYER_COLISION_HEIGHT		(100.0f)	// プレイヤーの当たり判定の高さの初期値
#define PLAYER_MOTION_BLEND_FRAME	(3)			// モーションブレンドのフレーム数
#define PLAYER_FALL_DEATH_LINE		(-100)		// プレイヤーの死亡する高さ

#define PLAYER_MOTION_LOADTXT_NAME	"data//TEXT//motion_player.txt"		// プレイヤーのモーションテキストファイル名
#define SAVE_RESULT_TEXT			"data/TEXT/result.txt"

// ステータス時間
#define DAMAGE_TIME					(30)		// ダメージの時間
#define DOWN_TIME					(50)		// ダウンの時間
#define DEATH_TIME					(60)		// 死亡時の時間
#define APPEAR_TIME					(120)		// 出現時の無敵時間
#define INVINCIBLE_TIME				(60)			// 無敵時間

#define PLAYER_SHADOW_RADIUS		(15.0f)		// プレイヤーの影の半径

// ダメージ計算用
#define PLAYER_GUARD_DAMAGE			(0.2)		// プレイヤーのガード時のダメージ減少量
#define PLAYER_ADVANTAGEOUS_DAMEGE	(1.2f)		// 有利相性時のダメージ計算率
#define PLAYER_UNFAVORABLE_DAMEGE	(0.7f)		// 不利相性時のダメージ計算率

#define PLAYER_SKILL_ADD_ATTACK		(5)			// 攻撃をしたときのスキルポイントの増加量
#define PLAYER_SKILL_ADD_DEFENSE	(10)		// 攻撃を受けたときのスキルポイントの増加量

#define PLAYER_1P_HP_SKILL_TXT_NAME	"data//TEXT//1PlayerHpSkill.txt"		// 1PのHP保存テキストファイル名
#define PLAYER_2P_HP_SKILL_TXT_NAME	"data//TEXT//2PlayerHpSkill.txt"		// 2PのHP保存テキストファイル名

// スキル情報
// スキル情報
#define BRAVE_SKILL_DAMAGE_RANK1	(10)				// 勇者スキルダメージ量（1段階目
#define BRAVE_SKILL_DAMAGE_RANK2	(15)				// 勇者スキルダメージ量（2段階目
#define BRAVE_SKILL_DAMAGE_RANK3	(30)				// 勇者スキルダメージ量（3段階目
#define BRAVE_SKILL_DAMAGE_WIDTH	(RAIZIN_RADIUS_X_R*2.0f)	// 勇者スキル範囲・幅
#define BRAVE_SKILL_DAMAGE_HEIGHT	(RAIZIN_RADIUS_Y_R*2.0f)	// 勇者スキル範囲・高さ
#define BRAVE_SKILL_POS_Y			(30.0f)				// 勇者スキルY位置

#define DEVIL_SKILL_DAMAGE_RANK1	(10)				// 魔王スキルダメージ量（1段階目
#define DEVIL_SKILL_DAMAGE_RANK2	(15)				// 魔王スキルダメージ量（2段階目
#define DEVIL_SKILL_DAMAGE_RANK3	(30)				// 魔王スキルダメージ量（3段階目
#define DEVIL_SKILL_DAMAGE_WIDTH	(DARK_RADIUS_X*2.0f)		// 魔王スキル範囲・幅
#define DEVIL_SKILL_DAMAGE_HEIGHT	(DARK_RADIUS_Y*2.0f)		// 魔王スキル範囲・高さ
#define DEVIL_SKILL_POS_Y			(50.0f)				// 魔王スキルY位置

#define KING_SKILL_DAMAGE_RANK1		(10)				// 王様スキルダメージ量（1段階目
#define KING_SKILL_DAMAGE_RANK2		(15)				// 王様スキルダメージ量（2段階目
#define KING_SKILL_DAMAGE_RANK3		(30)				// 王様スキルダメージ量（3段階目
#define KING_SKILL_DAMAGE_WIDTH		(GRAVITY_RADIUS_X*2.0f)	// 王様スキル範囲・幅
#define KING_SKILL_DAMAGE_HEIGHT	(GRAVITY_RADIUS_Y*2.0f)	// 王様スキル範囲・高さ
#define KING_SKILL_POS_Y			(10.0f)				// 王様スキルY位置

#define PEOPLE_SKILL_DAMAGE_RANK1	(10)				// 平民スキルダメージ量（1段階目
#define PEOPLE_SKILL_DAMAGE_RANK2	(15)				// 平民スキルダメージ量（2段階目
#define PEOPLE_SKILL_DAMAGE_RANK3	(30)				// 平民スキルダメージ量（3段階目
#define PEOPLE_SKILL_DAMAGE_WIDTH	(FISSURES_RADIUS_X*2.0f)	// 平民スキル範囲・幅
#define PEOPLE_SKILL_DAMAGE_HEIGHT	(FISSURES_RADIUS_Y*2.0f)	// 平民スキル範囲・高さ
#define PEOPLE_SKILL_POS_Y			(30.0f)				// 平民スキルY位置

#define GOD_SKILL_DAMAGE_RANK1		(15)				// 平民(神)スキルダメージ量（1段階目
#define GOD_SKILL_DAMAGE_RANK2		(20)				// 平民(神)スキルダメージ量（2段階目
#define GOD_SKILL_DAMAGE_RANK3		(35)				// 平民(神)スキルダメージ量（3段階目
#define GOD_SKILL_DAMAGE_WIDTH		(GOD_RADIUS_X*2.0f)		// 平民(神)スキル範囲・幅
#define GOD_SKILL_DAMAGE_HEIGHT		(GOD_RADIUS_X*2.0f)		// 平民(神)スキル範囲・高さ
#define GOD_SKILL_POS_Y				(40.0f)				// 平民(神)スキルY位置

#define PLAYER_MAX_SKILL_RANK		(3)			// スキルの段階の種類
#define PLAYER_SKILL_RANK_1			(30)		// スキルの段階1の必要量
#define PLAYER_SKILL_RANK_2			(65)		// スキルの段階2の必要量
#define PLAYER_SKILL_RANK_3			(100)		// スキルの段階3の必要量

#define PLAYER_SKILL_DISTANCE		(30.0f)	// スキル被弾時のぶっとび量
#define PLAYER_SKILL_START_FRAME	(8)			// スキルの判定を開始するフレーム数


//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{ // プレイヤーの配置情報
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	PLAYER_TYPE type;
	bool bUse;
}PlayerSetInfo;

typedef struct
{
	char *pFilename;	// ファイル名
} PlayerTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
Player g_aPlayer[MAX_PLAYER];						// プレイヤーの情報
													// 読み込むプレイヤー名の設定
													//PlayerModelData g_apPlayer[MAX_PLAYER_PARTS] = {};	// モデルへのポインタ
PlayerTypeData g_aPlayerType[PLAYER_TYPE_MAX];
PlayerSetInfo g_aPlayerSetInfo[MAX_PLAYER];			// プレイヤーの配置情報
bool g_aAttackCollisionDisp[MAX_PLAYER];
int g_nMoveRimit;

// 攻撃ランクのダメージボーナス量
int g_nAttackRankDamage[PLAYER_ATTACK_RANK_MAX] =
{
	0,		// 非上昇状態
	1,		// 攻撃1段階上昇時
	2,		// 攻撃2段階上昇時
	3		// 攻撃3段階上昇時
};

// 防御ランクのダメージ減少ボーナス量
int g_nDefenseRankDamage[PLAYER_DEFENSE_RANK_MAX] =
{
	0,		// 非上昇状態
	1,		// 防御1段階上昇時
	3,		// 防御2段階上昇時
	5		// 防御3段階上昇時
};

// 回復ランクのダメージ減少ボーナス量
int g_nRecoveryRank[PLAYER_RECOVERY_RANK_MAX] =
{
	0,		// 非上昇状態
	5,		// 回復1段階上昇時
	10,		// 回復2段階上昇時
	15,		// 回復3段階上昇時
	20,		// 回復4段階上昇時
	25,		// 回復5段階上昇時
};


int g_nPlayerSkillDamage[PLAYER_MAX_SKILL_RANK][PLAYER_TYPE_MAX];	// スキルダメージ量
float g_nPlayerSkillWidth[PLAYER_TYPE_MAX];							// スキル判定幅
float g_nPlayerSkillHeight[PLAYER_TYPE_MAX];						// スキル判定高さ
float g_nPlayerSkillPosY[PLAYER_TYPE_MAX];							// スキル判定Y位置


bool g_bTestPlayerDisp;	// デバッグ用

LPDIRECT3DTEXTURE9		g_pTexturePlayerGod = NULL;	// ゴッドテクスチャへのポインタ
// 2P用テクスチャ
LPDIRECT3DTEXTURE9		g_pTexturePlayer2P[PLAYER_TYPE_MAX] = {};	// テクスチャへのポインタ
// 読み込むテクスチャ名の設定
PlayerTexInfo g_apTexturePlayer2PInfo[PLAYER_TYPE_MAX] =
{
	{ "data//MODEL//brave//TEXTURE//yuusya2P.jpg" },		// 勇者2P
	{ "data//MODEL//devil//TEXTURE//maou2P.jpg" },			// 魔王2P
	{ "data//MODEL//king//TEXTURE//ousama2P.jpg" },			// 王様2P
	{ "data//MODEL//Commoner//TEXTURE//heimin2P.jpg" },		// 平民2P
	{ "data//MODEL//Commoner//TEXTURE//god2P.jpg" },		// 平民神2P
};

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPlayer(void)
{
	// デバッグ用
	g_bTestPlayerDisp = false;

	// スキル情報
	// 勇者
	g_nPlayerSkillDamage[0][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK1;		// スキルダメージ量（1段階目
	g_nPlayerSkillDamage[1][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK2;		// スキルダメージ量（2段階目
	g_nPlayerSkillDamage[2][PLAYER_TYPE_BRAVE]	= BRAVE_SKILL_DAMAGE_RANK3;		// スキルダメージ量（3段階目
	g_nPlayerSkillWidth[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_DAMAGE_WIDTH;		// スキル判定幅
	g_nPlayerSkillHeight[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_DAMAGE_HEIGHT;	// スキル判定高さ
	g_nPlayerSkillPosY[PLAYER_TYPE_BRAVE]		= BRAVE_SKILL_POS_Y;			// スキル判定Y位置
	// 魔王
	g_nPlayerSkillDamage[0][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK1;		// スキルダメージ量（1段階目
	g_nPlayerSkillDamage[1][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK2;		// スキルダメージ量（2段階目
	g_nPlayerSkillDamage[2][PLAYER_TYPE_DEVIL]	= DEVIL_SKILL_DAMAGE_RANK3;		// スキルダメージ量（3段階目
	g_nPlayerSkillWidth[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_DAMAGE_WIDTH;		// スキル判定幅
	g_nPlayerSkillHeight[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_DAMAGE_HEIGHT;	// スキル判定高さ
	g_nPlayerSkillPosY[PLAYER_TYPE_DEVIL]		= DEVIL_SKILL_POS_Y;			// スキル判定Y位置
	// 王様
	g_nPlayerSkillDamage[0][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK1;		// スキルダメージ量（1段階目
	g_nPlayerSkillDamage[1][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK2;		// スキルダメージ量（2段階目
	g_nPlayerSkillDamage[2][PLAYER_TYPE_KING]	= KING_SKILL_DAMAGE_RANK3;		// スキルダメージ量（3段階目
	g_nPlayerSkillWidth[PLAYER_TYPE_KING]		= KING_SKILL_DAMAGE_WIDTH;		// スキル判定幅
	g_nPlayerSkillHeight[PLAYER_TYPE_KING]		= KING_SKILL_DAMAGE_HEIGHT;		// スキル判定高さ
	g_nPlayerSkillPosY[PLAYER_TYPE_KING]		= KING_SKILL_POS_Y;				// スキル判定Y位置
	// 平民
	g_nPlayerSkillDamage[0][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK1;	// スキルダメージ量（1段階目
	g_nPlayerSkillDamage[1][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK2;	// スキルダメージ量（2段階目
	g_nPlayerSkillDamage[2][PLAYER_TYPE_PEOPLE] = PEOPLE_SKILL_DAMAGE_RANK3;	// スキルダメージ量（3段階目
	g_nPlayerSkillWidth[PLAYER_TYPE_PEOPLE]		= PEOPLE_SKILL_DAMAGE_WIDTH;	// スキル判定幅
	g_nPlayerSkillHeight[PLAYER_TYPE_PEOPLE]	= PEOPLE_SKILL_DAMAGE_HEIGHT;	// スキル判定高さ
	g_nPlayerSkillPosY[PLAYER_TYPE_PEOPLE]		= PEOPLE_SKILL_POS_Y;			// スキル判定Y位置
	// 平民（神
	g_nPlayerSkillDamage[0][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK1;		// スキルダメージ量（1段階目
	g_nPlayerSkillDamage[1][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK2;		// スキルダメージ量（2段階目
	g_nPlayerSkillDamage[2][PLAYER_TYPE_GOD]	= GOD_SKILL_DAMAGE_RANK3;		// スキルダメージ量（3段階目
	g_nPlayerSkillWidth[PLAYER_TYPE_GOD]		= GOD_SKILL_DAMAGE_WIDTH;		// スキル判定幅
	g_nPlayerSkillHeight[PLAYER_TYPE_GOD]		= GOD_SKILL_DAMAGE_HEIGHT;		// スキル判定高さ
	g_nPlayerSkillPosY[PLAYER_TYPE_GOD]			= GOD_SKILL_POS_Y;				// スキル判定Y位置

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤー情報の初期化
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayer[nCntPlayer].fMoveSpeed = PLAYER_MOVE_SPEED;
		g_aPlayer[nCntPlayer].fJampMove = PLAYER_JUMP_MOVE;
		g_aPlayer[nCntPlayer].fRadius = PLAYER_COLISION_RADIUS;
		g_aPlayer[nCntPlayer].fHeight = PLAYER_COLISION_HEIGHT;
		g_aPlayer[nCntPlayer].fCollisionRadius = 20.0f;
		g_aPlayer[nCntPlayer].nLife = PLAYER_LIFE;
		g_aPlayer[nCntPlayer].nSkillPoint = PLAYER_SKILL;
		g_aPlayer[nCntPlayer].nSkillRank = 0;
		g_aPlayer[nCntPlayer].nModelParts = 0;
		g_aPlayer[nCntPlayer].nIdyShadow = 0;
		g_aPlayer[nCntPlayer].type = PLAYER_TYPE_BRAVE;
		g_aPlayer[nCntPlayer].nCounterState = APPEAR_TIME;
		g_aPlayer[nCntPlayer].state = PLAYERSTATE_APPEAR;
		g_aPlayer[nCntPlayer].MotionType = PLAYER_MOTION_TYPE_NEUTRAL;
		g_aPlayer[nCntPlayer].MotionTypeHit = PLAYER_MOTION_TYPE_NEUTRAL;
		g_aPlayer[nCntPlayer].fGravity = PLAYER_GRAVITY;
		g_aPlayer[nCntPlayer].b2PColor = false;
		g_aPlayer[nCntPlayer].nRecovery = 0;

		for (int nCntBool = 0; nCntBool < PLAYER_BOOL_MAX; nCntBool++)
		{
			g_aPlayer[nCntPlayer].bBool[nCntBool] = false;
			g_aPlayer[nCntPlayer].bBoolOld[nCntBool] = false;
		}
		// ジャンプ中にする
		g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = true;

		g_aPlayer[nCntPlayer].bUse = false;
		g_aPlayer[nCntPlayer].bDisp = true;
		for (int nCntModel = 0; nCntModel < MAX_PLAYER_PARTS; nCntModel++)
		{
			g_aPlayer[nCntPlayer].aModel[nCntModel].posAddMotion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayer[nCntPlayer].aModel[nCntModel].rotAddMotion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// モーション設定
		g_aPlayer[nCntPlayer].nKeyCnt = 0;
		g_aPlayer[nCntPlayer].nFrameCounter = 0;
		g_aPlayer[nCntPlayer].nAllFrameCounter = 0;
		g_aPlayer[nCntPlayer].bBlend = false;

		// 移動可能範囲の場所にいるかどうか
		for (int nCntArea = 0; nCntArea < PLAYER_SIDE_MAX; nCntArea++)
		{
			g_aPlayer[nCntPlayer].bAreaLimit[nCntArea] = false;
		}
	}

	g_nMoveRimit = PLAYER_MOVE_RIMIT;


	// 配置情報をもとに配置を行う
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		SetPlayer(g_aPlayerSetInfo[nCntPlayer].pos, g_aPlayerSetInfo[nCntPlayer].rot, g_aPlayerSetInfo[nCntPlayer].type);
	}

	// ゴッドテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data//MODEL//Commoner//TEXTURE//god.jpg",&g_pTexturePlayerGod);

	// 2P用テクスチャの読み込み
	for (int nCntTex = 0; nCntTex < PLAYER_TYPE_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePlayer2PInfo[nCntTex].pFilename,
			&g_pTexturePlayer2P[nCntTex]);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPlayer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PLAYER_TYPE_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (g_pTexturePlayer2P[nCntTex] != NULL)
		{
			g_pTexturePlayer2P[nCntTex]->Release();
			g_pTexturePlayer2P[nCntTex] = NULL;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePlayer(void)
{
	BATTLESTATE BattleState = GetBattleState();
	GAMEMODE mode = GetGameMode();
	// カメラを取得
	Camera *pCamera = GetCamera();
	float fDiffAngle;		// 差分
	float fDestAngle;		// 目的の角度
	float fMoveAngle;		// 現在の角度

							// 移動制限調整デバッグ用
	//if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_nMoveRimit--;
	//}
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_nMoveRimit++;
	//}

	//// デバッグ用
	//if (GetKeyboardTrigger(DIK_O) == true)
	//{
	//	g_bTestPlayerDisp = g_bTestPlayerDisp ? false : true;
	//}

	/*if (GetKeyboardTrigger(DIK_C) == true)
	{
		g_aPlayer[0].nSkillPoint = 100;
	}*/


	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true)
		{ // 使用している場合
			for (int nCntBool = 0; nCntBool < PLAYER_BOOL_MAX; nCntBool++)
			{ // 前回の状況を記録
				g_aPlayer[nCntPlayer].bBoolOld[nCntBool] = g_aPlayer[nCntPlayer].bBool[nCntBool];
			}

			// 前回の位置・モーションの種類を記録
			g_aPlayer[nCntPlayer].posOld = g_aPlayer[nCntPlayer].pos;
			g_aPlayer[nCntPlayer].MotionTypeOld = g_aPlayer[nCntPlayer].MotionType;

			if (mode == GAMEMODE_BATTLE)
			{ // バトルモードの場合
				switch (g_aPlayer[nCntPlayer].state)
				{ // プレイヤーの状態の処理
				case PLAYERSTATE_APPEAR:
					g_aPlayer[nCntPlayer].nCounterState--;
					// ここがVSの待機時間？？

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // カウンターが0以下になったらプレイヤーの状態を通常状態に戻す
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
						g_aPlayer[nCntPlayer].bDisp = true;
					}
					break;
				case PLAYERSTATE_NORMAL:
					break;
				case PLAYERSTATE_DAMAGE:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // カウンターが0以下になったらプレイヤーの状態を通常状態に戻す
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_DAMAGE] = false;
					}
					break;
				case PLAYERSTATE_DOWN:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // カウンターが0以下になったらプレイヤーの状態を起き上がり
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_GETUP;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_GETUP] = true;
						g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_BLOW] = false;
					}
					break;
				case PLAYERSTATE_GETUP:
					break;
				case PLAYERSTATE_DEATH:
					//g_aPlayer[nCntPlayer].nCounterState--;
					//if (g_aPlayer[nCntPlayer].nCounterState == 0)
					//{ // カウンターが0以下になったらリザルト画面に送る
					//	// ゲームステート設定
					//	SetGameFade(GAMEMODE_RESULT);
					//}
					break;
				case PLAYERSTATE_INVINCIBLE:
					g_aPlayer[nCntPlayer].nCounterState--;

					if (g_aPlayer[nCntPlayer].nCounterState <= 0)
					{ // カウンターが0以下になったらプレイヤーの状態を起き上がり
						g_aPlayer[nCntPlayer].state = PLAYERSTATE_NORMAL;
					}
					break;
				}
				// 現在の角度を代入(Y)
				fMoveAngle = g_aPlayer[nCntPlayer].rot.y;

				if (g_aPlayer[nCntPlayer].state != PLAYERSTATE_DEATH && BattleState != BATTLESTATE_TIMEOVER && BattleState != BATTLESTATE_CLEAR
					&& BattleState != BATTLESTATE_START)
				{
					// プレイヤー操作処理
					PlayerController((PLAYER_CONTROL)nCntPlayer);
				}

				// 移動距離制限Check
				CheckMove(nCntPlayer);

				// 方向Check
				CheckRot(nCntPlayer);

				// 重力加算
				g_aPlayer[nCntPlayer].move.y -= g_aPlayer[nCntPlayer].fGravity;

				// 位置更新
				g_aPlayer[nCntPlayer].pos.x += g_aPlayer[nCntPlayer].move.x;
				g_aPlayer[nCntPlayer].pos.y += g_aPlayer[nCntPlayer].move.y;
				g_aPlayer[nCntPlayer].pos.z += g_aPlayer[nCntPlayer].move.z;

				g_aPlayer[nCntPlayer].move.x += float(-g_aPlayer[nCntPlayer].move.x) * PLAYER_MOVE_INERTIA;
				g_aPlayer[nCntPlayer].move.y += float(-g_aPlayer[nCntPlayer].move.y) * PLAYER_MOVE_INERTIA;
				g_aPlayer[nCntPlayer].move.z += float(-g_aPlayer[nCntPlayer].move.z) * PLAYER_MOVE_INERTIA;


				// めくり＆プレイヤー同士対決
				CollisionMove(nCntPlayer);

				// 移動可能範囲制限
				CheckMoveArea(nCntPlayer);

				// 目的の角度を代入
				fDestAngle = g_aPlayer[nCntPlayer].rot.y;
				// 差分を計算
				fDiffAngle = (fDestAngle - fMoveAngle);

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle += -D3DX_PI * 2;
				}
				else if (fDiffAngle < -D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2;
				}

				// 現在の角度に差分の何割かを代入
				fMoveAngle += fDiffAngle * PLAYER_SPIN_INERTIA;

				if (fMoveAngle > D3DX_PI)
				{
					fMoveAngle += -D3DX_PI * 2;
				}
				else if (fMoveAngle < -D3DX_PI)
				{
					fMoveAngle += D3DX_PI * 2;
				}

				g_aPlayer[nCntPlayer].rot.y = fMoveAngle;

				// オブジェクトとメッシュフィールド当たり判定
				if (CollisionMeshBattleField(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, g_aPlayer[nCntPlayer].fRadius) == true)
				{
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = false;
				}
				else
				{
					if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false)
					{ // ジャンプしていなくても空中に出た場合
						//g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] = true;
					}
				}

				// 影の移動処理
				SetPositionShadow(g_aPlayer[nCntPlayer].nIdyShadow, g_aPlayer[nCntPlayer].pos);

				// 着地の条件(格ゲーに着地モーションはいらないが攻撃終了のため必要
				if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBoolOld[PLAYER_BOOL_JUMP] == true)
				{
					// 攻撃を強制的に終了させる
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
					g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
				}

				// モーションタイプ設定
				PlayerMotionTypeSet(nCntPlayer);

				// プレイヤーモーション処理
				PlayerMotion(nCntPlayer);

				// 攻撃当たり判定
				if (CollisionAttack(nCntPlayer))
				{ // 当たり判定
				  // 攻撃があたったモーションを記録
					g_aPlayer[nCntPlayer].MotionTypeHit = g_aPlayer[nCntPlayer].MotionType;
				}
				// スキル攻撃当たり判定
				if (CollisionSkillAttack(nCntPlayer))
				{ // 当たり判定
				  // 攻撃があたったモーションを記録
					g_aPlayer[nCntPlayer].MotionTypeHit = g_aPlayer[nCntPlayer].MotionType;
				}

				if (g_aPlayer[nCntPlayer].MotionType == PLAYER_MOTION_TYPE_NEUTRAL || g_aPlayer[nCntPlayer].MotionType == PLAYER_MOTION_TYPE_NEUTRAL_SQUAT)
				{
					g_aPlayer[nCntPlayer].MotionTypeHit = PLAYER_MOTION_TYPE_NEUTRAL;
				}
			}
			else if (mode == GAMEMODE_PLAYERSHOW)
			{ // プレイヤーショウの場合

			  // プレイヤーモーション処理
				PlayerMotion(nCntPlayer);
			}
		}
#if DEBUG_SPHERE
		// デバッグ用防御判定スフィア更新処理
		PlayerDebugDeffSphereUpdate(nCntPlayer);
#endif // DEBUG_SPHERE
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			// 計算用マトリックス
	D3DMATERIAL9 matDef;					// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;						// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;					// 親子関係反映用のマトリックス

	BATTLESTATE BattleState = GetBattleState();
	if (BattleState == BATTLESTATE_TIMEOVER)
	{
		// アルファテストの設定
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテストを開始する
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// 基準値(REF)を決める
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 処理(FUNC)を決める,D3DCMP_GREATER,比較(CMP),GREATER(〇〇より大きい)
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == true && g_aPlayer[nCntPlayer].bDisp == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].rot.y, g_aPlayer[nCntPlayer].rot.x, g_aPlayer[nCntPlayer].rot.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].pos.x, g_aPlayer[nCntPlayer].pos.y, g_aPlayer[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].mtxWorld, &g_aPlayer[nCntPlayer].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].mtxWorld);

			for (int nCntModel = 0; nCntModel < g_aPlayer[nCntPlayer].nModelParts; nCntModel++)
			{
				if (g_aPlayer[nCntPlayer].aModel[nCntModel].nIdxModelParent == -1)
				{
					mtxParent = g_aPlayer[nCntPlayer].mtxWorld;
				}
				else
				{
					mtxParent = g_aPlayer[nCntPlayer].aModel[g_aPlayer[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer[nCntPlayer].aModel[nCntModel].rot.y + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.y,
					g_aPlayer[nCntPlayer].aModel[nCntModel].rot.x + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.x,
					g_aPlayer[nCntPlayer].aModel[nCntModel].rot.z + g_aPlayer[nCntPlayer].aModel[nCntModel].rotMotion.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRot);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_aPlayer[nCntPlayer].aModel[nCntModel].pos.x + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.x,
					g_aPlayer[nCntPlayer].aModel[nCntModel].pos.y + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.y,
					g_aPlayer[nCntPlayer].aModel[nCntModel].pos.z + g_aPlayer[nCntPlayer].aModel[nCntModel].posMotion.z);
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTrans);

				// 親のワールドマトリックスを反映
				D3DXMatrixMultiply(&g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxParent);

				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer[nCntPlayer].aModel[nCntModel].mtxWorld);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				if (g_bTestPlayerDisp == false)
				{ // デバッグ用
				  // マテリアルデータへのポインタを取得
					pMat = (D3DXMATERIAL*)g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].nNumMat; nCntMat++)
					{
						if (g_aPlayer[nCntPlayer].b2PColor == true)
						{// 2Pの場合
							pDevice->SetTexture(0, g_pTexturePlayer2P[g_aPlayer[nCntPlayer].type]);
						}
						else
						{
							if (g_aPlayer[nCntPlayer].type == PLAYER_TYPE_GOD)
							{// 神の場合
								pDevice->SetTexture(0, g_pTexturePlayerGod);
							}
							else
							{
								// テクスチャの設定
								pDevice->SetTexture(0, g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pTexture[nCntMat]);
							}
						}

						// マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						// 敵(パーツ)の描画
						g_aPlayerType[g_aPlayer[nCntPlayer].type].apPlayer[g_aPlayer[nCntPlayer].aModel[nCntModel].nModelType].pMesh->DrawSubset(nCntMat);
					}
				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}

	if (BattleState == BATTLESTATE_TIMEOVER)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテストを終了する
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤータイプデータの初期化
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPlayerTypeData(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// 当たり判定を表示するか
		g_aAttackCollisionDisp[nCntPlayer] = false;
	}

	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		g_aPlayerType[nCntType].nModelParts = 0;
		g_aPlayerType[nCntType].fMoveSpeed = 0.0f;
		g_aPlayerType[nCntType].fJampMove = 0.0f;
		g_aPlayerType[nCntType].fRadius = 0.0f;
		g_aPlayerType[nCntType].fHeight = 0.0f;
		g_aPlayerType[nCntType].fDamage = 0.0f;
		g_aPlayerType[nCntType].fKnockBack = 0.0f;

		// モーション情報内の防御当たり判定の初期化
		for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
		{
			g_aPlayerType[nCntType].collisionD[nCntCollision].bUse = false;
			g_aPlayerType[nCntType].collisionD[nCntCollision].fRadius = 0.0f;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nDamage = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].fDistance = 0.0f;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nFrameS = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nFrameE = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].nPartsId = 0;
			g_aPlayerType[nCntType].collisionD[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aPlayerType[nCntType].collisionD[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
			}

			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
			}
#endif // DEBUG_SPHERE
		}

		// タイプデータ内のモーション情報の初期化
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = false;
			g_aPlayerType[nCntType].aMotion[nCntMotion].nAllFrame = 0;
			g_aPlayerType[nCntType].aMotion[nCntMotion].nNumKey = 0;

			// モーション情報内の攻撃当たり判定の初期化
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
			{
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].bUse = false;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].fRadius = 0.0f;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nDamage = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nFrameS = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nFrameE = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nPartsId = 0;
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
#if DEBUG_SPHERE
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nSpherID[nCntPlayer] = MAX_MESHSPHERE;
				}
#endif // DEBUG_SPHERE
			}


			// モーション情報内のキー情報の初期化
			for (int nCntKey = 0; nCntKey < MAX_PLAYER_KEY; nCntKey++)
			{
				g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].nFrame = 0;
				// キー情報内のパーツ情報の初期化
				for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS; nCntParts++)
				{
					g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
		PlayerModelData	apPlayer[MAX_PLAYER_PARTS] = {};	// モデルへのポインタ
		MotionPlayer	aMotion[PLAYER_MOTION_TYPE_MAX];	// モーション
		PlayerModel		aModel[MAX_PLAYER_PARTS];			// パーツ情報
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayerSetInfo[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerSetInfo[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPlayerSetInfo[nCntPlayer].type = PLAYER_TYPE_BRAVE;
		g_aPlayerSetInfo[nCntPlayer].bUse = false;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤータイプデータの終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPlayerTypeData(void)
{
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < sizeof g_aPlayerType[nCntType].apPlayer / sizeof(PlayerModelData); nCntModel++)
		{
			// テクスチャの開放
			for (int nCntTex = 0; nCntTex < (int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat; nCntTex++)
			{
				if (g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex] != NULL)
				{
					g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex]->Release();
					g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntTex] = NULL;
				}
			}

			// メッシュの開放
			if (g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh != NULL)
			{
				g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh->Release();
				g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh = NULL;
			}
			// マテリアルの開放
			if (g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat != NULL)
			{
				g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat->Release();
				g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat = NULL;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer[nCntPlayer].bUse == false)
		{ // 敵が使用されていない場合
			// 2Pカラー使用の初期化
			g_aPlayer[nCntPlayer].b2PColor = false;

			g_aPlayer[nCntPlayer].pos = pos;
			g_aPlayer[nCntPlayer].rot = rot;
			// 敵の種類を設定
			g_aPlayer[nCntPlayer].type = type;

			g_aPlayer[nCntPlayer].fMoveSpeed = g_aPlayerType[g_aPlayer[nCntPlayer].type].fMoveSpeed;
			g_aPlayer[nCntPlayer].fJampMove = g_aPlayerType[g_aPlayer[nCntPlayer].type].fJampMove;
			g_aPlayer[nCntPlayer].fRadius = g_aPlayerType[g_aPlayer[nCntPlayer].type].fRadius;

			g_aPlayer[nCntPlayer].nModelParts = g_aPlayerType[g_aPlayer[nCntPlayer].type].nModelParts;

			for (int nCntParts = 0; nCntParts < g_aPlayer[nCntPlayer].nModelParts; nCntParts++)
			{
				// インデックスを反映
				g_aPlayer[nCntPlayer].aModel[nCntParts].nIdxModelParent = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].nIdxModelParent;

				g_aPlayer[nCntPlayer].aModel[nCntParts].nModelType = nCntParts;

				// 位置・向きを反映
				g_aPlayer[nCntPlayer].aModel[nCntParts].pos = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].pos;
				g_aPlayer[nCntPlayer].aModel[nCntParts].rot = g_aPlayerType[g_aPlayer[nCntPlayer].type].aModel[nCntParts].rot;
			}

			// 影を設定
			g_aPlayer[nCntPlayer].nIdyShadow = SetShadow(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot, g_aPlayer[nCntPlayer].fRadius * 2, g_aPlayer[nCntPlayer].fRadius * 2);

			g_aPlayer[nCntPlayer].bUse = true; // 使用している状態にする

			if (nCntPlayer != 0)
			{
				// 2Pカラーにするか確認
				for (int nCnt2P = 0; nCnt2P < MAX_PLAYER; nCnt2P++)
				{
					if (g_aPlayer[nCnt2P].bUse == true && nCnt2P != nCntPlayer)
					{
						if (g_aPlayer[nCnt2P].type == g_aPlayer[nCntPlayer].type)
						{
							g_aPlayer[nCntPlayer].b2PColor = true;
						}
					}
				}
			}
			break;	// このbreakはかなり大切
		}
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーの配置情報設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPlayerInfo(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (g_aPlayerSetInfo[nCnt].bUse == false)
		{ // 敵が使用されていない場合
			g_aPlayerSetInfo[nCnt].pos = pos;
			g_aPlayerSetInfo[nCnt].rot = rot;
			// 敵の種類を設定
			g_aPlayerSetInfo[nCnt].type = type;

			g_aPlayerSetInfo[nCnt].bUse = true; // 使用している状態にする

			break;	// このbreakはかなり大切
		}
	}
}
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーのモーション
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotion(int nPlayerID)
{
	int nFrame = 0; // モーションの分割フレームを記録

	if (g_aPlayer[nPlayerID].MotionType != g_aPlayer[nPlayerID].MotionTypeOld)
	{ // 現在のモーションと前回のモーションが違った時
		g_aPlayer[nPlayerID].nFrameCounter = 0;	// フレームをリセット
		g_aPlayer[nPlayerID].nKeyCnt = 0;			// キーをリセット
		g_aPlayer[nPlayerID].nAllFrameCounter = 0;	// 全てのフレームをリセット
		g_aPlayer[nPlayerID].bBlend = true;		// ブレンドをする
		nFrame = PLAYER_MOTION_BLEND_FRAME;			// ブレンドのフレーム数
	}
	else
	{ // 通常時のモーションの分割フレーム
		nFrame = g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].nFrame;
	}

	if (g_aPlayer[nPlayerID].nFrameCounter == 0)
	{ // 1フレームごとの追加量を計算
		for (int nCntPartsKey = 0; nCntPartsKey < g_aPlayer[nPlayerID].nModelParts; nCntPartsKey++)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].posAddMotion =
				(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].aPartsKey[nCntPartsKey].pos - g_aPlayer[nPlayerID].aModel[nCntPartsKey].posMotion)
				/ float(nFrame);

			// 差分を計算
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion =
				(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].aPartsKey[nCntPartsKey].rot - g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion)
				/ float(nFrame);

			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.x += D3DX_PI * 2;
			}
			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.y += D3DX_PI * 2;
			}
			if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z > D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z += -D3DX_PI * 2;
			}
			else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z < -D3DX_PI)
			{
				g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion.z += D3DX_PI * 2;
			}
		}
	}

	if (g_aPlayer[nPlayerID].nKeyCnt == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1
		&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].bLoop == false
		&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1].nFrame == g_aPlayer[nPlayerID].nFrameCounter + 1)
	{ // 攻撃着地終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] = false;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] = false;
	}
	// 弱攻撃
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SMALL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SMALL)
	{ // 弱攻撃終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
	}
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL)
	{ // しゃがみ弱攻撃終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] = false;
	}

	// 強攻撃
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_BIG &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_BIG)
	{ // 強攻撃終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
	}
	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG)
	{ // しゃがみ強攻撃終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_LANDING &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_LANDING)
	{ // 着地終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_GETUP &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_GETUP)
	{ // 起き上がり終了判定
		g_aPlayer[nPlayerID].state = PLAYERSTATE_INVINCIBLE;
		g_aPlayer[nPlayerID].nCounterState = INVINCIBLE_TIME;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] = false;
	}

	if (g_aPlayer[nPlayerID].MotionTypeOld == PLAYER_MOTION_TYPE_SKILL &&g_aPlayer[nPlayerID].MotionType != PLAYER_MOTION_TYPE_SKILL)
	{ // スキル終了判定
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = false;
	}

	// モーション加算
	for (int nCntPartsKey = 0; nCntPartsKey < g_aPlayer[nPlayerID].nModelParts; nCntPartsKey++)
	{
		g_aPlayer[nPlayerID].aModel[nCntPartsKey].posMotion += g_aPlayer[nPlayerID].aModel[nCntPartsKey].posAddMotion;
		g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion += g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotAddMotion;

		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.x += D3DX_PI * 2;
		}
		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.y += D3DX_PI * 2;
		}
		if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z > D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z += -D3DX_PI * 2;
		}
		else if (g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z < -D3DX_PI)
		{
			g_aPlayer[nPlayerID].aModel[nCntPartsKey].rotMotion.z += D3DX_PI * 2;
		}
	}

	// フレームカウンター増加
	g_aPlayer[nPlayerID].nFrameCounter++;
	g_aPlayer[nPlayerID].nAllFrameCounter++;

	if (g_aPlayer[nPlayerID].bBlend == true && g_aPlayer[nPlayerID].nFrameCounter == PLAYER_MOTION_BLEND_FRAME)
	{ // ブレンド時リセット
		g_aPlayer[nPlayerID].nFrameCounter = 0;
		g_aPlayer[nPlayerID].bBlend = false;
		g_aPlayer[nPlayerID].nKeyCnt = 1;
	}
	else if (g_aPlayer[nPlayerID].nFrameCounter == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].aKey[g_aPlayer[nPlayerID].nKeyCnt].nFrame)
	{ // フレームカウンターリセット
		g_aPlayer[nPlayerID].nFrameCounter = 0;
		if (g_aPlayer[nPlayerID].nKeyCnt == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey - 1
			&& g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].bLoop == false)
		{ //ループせずかつ最大キー数を超える

		}
		else
		{
			g_aPlayer[nPlayerID].nKeyCnt = (g_aPlayer[nPlayerID].nKeyCnt + 1) % g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nNumKey;
		}
	}

	if (g_aPlayer[nPlayerID].nAllFrameCounter == g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].nAllFrame)
	{
		g_aPlayer[nPlayerID].nAllFrameCounter = 0;
	}

}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーモーションの種類の設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotionTypeSet(int nPlayerID)
{
	if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] == true)
	{ // 起き上がりを行っているか判定
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GETUP;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] == true)
	{ // ぶっ飛ばされているか判定
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_BLOW;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] == true)
	{ // ダメージを受けているか判定
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // しゃがみ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_DAMAGE_SQUAT;
		}
		else
		{ // それ以外の場合
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_DAMAGE;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true)
	{ // スキルを使っているか
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_SKILL;
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] == true)
	{ // ガードをしているか判定
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // しゃがみ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GUARD_SQUAT;
		}
		else
		{ // それ以外の場合
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_GUARD;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] == true)
	{ // 弱攻撃判定
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // しゃがみ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SQUAT_SMALL;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // ジャンプ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_JUMP_SMALL;
		}
		else
		{ // それ以外の場合
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SMALL;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG] == true)
	{ // 強攻撃判定
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
		{ // しゃがみ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_SQUAT_BIG;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // ジャンプ状態か
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_JUMP_BIG;
		}
		else
		{ // それ以外の場合
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_ATTACK_BIG;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
	{ // ジャンプ状態か
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_FRONT] == true)
		{ // 前
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_FRONT;
		}
		else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BACK] == true)
		{ // 後
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_BACK;
		}
		else
		{
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_JUMP_UP;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
	{ // しゃがみ状態か
		if (g_aPlayer[nPlayerID].bBoolOld[PLAYER_BOOL_SQUAT] == true)
		{ // 前回がしゃがみ状態かどうか
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_NEUTRAL_SQUAT;
		}
		else
		{ // 前回がしゃがみ状態じゃない場合
			g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_SQUAT;
		}
	}
	else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_LANDING] == true)
	{ // 着地状態か
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_LANDING;
	}
	else if (g_aPlayer[nPlayerID].move.x > 1.0f || g_aPlayer[nPlayerID].move.x < -1.0f
		|| g_aPlayer[nPlayerID].move.z > 1.0f || g_aPlayer[nPlayerID].move.z < -1.0f)
	{ // 歩行状態か
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_WALK;
	}
	else
	{ // ニュートラルか
		g_aPlayer[nPlayerID].MotionType = PLAYER_MOTION_TYPE_NEUTRAL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーモーションの種類の設定(直接指定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerMotionTypeSet(int nPlayerID, PLAYER_MOTION_TYPE motionType)
{
	g_aPlayer[nPlayerID].MotionType = motionType;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーのダメージ処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void HitPlayer(D3DXVECTOR3 HitPos, int nPlayerID, int nDamage, float fDistance, bool bigAttack, bool bSkill)
{
	PLAYER_TYPE atkType; // 攻撃側のタイプ

	// ダメージボーナスの確認
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // 攻撃を受けたプレイヤーではない場合
		  // 攻撃ランクのダメージボーナスを計算
			nDamage += g_nAttackRankDamage[g_aPlayer[nCntPlayer].atkRank];

			// 攻撃側の種類を記録
			atkType = g_aPlayer[nCntPlayer].type;

			break;
		}
	}
	// 防御ランクのダメージ減少ボーナスを計算
	nDamage -= g_nDefenseRankDamage[g_aPlayer[nPlayerID].defRank];

	// 相性の有利不利のダメージ計算
	switch (g_aPlayer[nPlayerID].type)
	{
	case PLAYER_TYPE_BRAVE:	// 攻撃を受けた側が勇者の場合
		if (atkType == PLAYER_TYPE_DEVIL)
		{ // 攻撃したのが魔王の場合
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_KING)
		{ // 攻撃したのが王様の場合
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		break;
	case PLAYER_TYPE_DEVIL:	// 攻撃を受けた側が魔王の場合
		if (atkType == PLAYER_TYPE_BRAVE)
		{ // 攻撃したのが勇者の場合
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_KING)
		{ // 攻撃したのが王様の場合
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		break;
	case PLAYER_TYPE_KING:	// 攻撃を受けた側が王様の場合
		if (atkType == PLAYER_TYPE_BRAVE)
		{ // 攻撃したのが勇者の場合
			nDamage = int(nDamage * PLAYER_UNFAVORABLE_DAMEGE);
		}
		else if (atkType == PLAYER_TYPE_DEVIL)
		{ // 攻撃したのが魔王の場合
			nDamage = int(nDamage * PLAYER_ADVANTAGEOUS_DAMEGE);
		}
		break;
	}

	// 被弾時の移動方向の確認
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // 攻撃を受けたプレイヤーではない場合
		  // 攻撃をしたプレイヤーがどちらにいたか
			if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
			{ // 攻撃したプレイヤーが右側にいた場合
			  // 移動量を逆転させる
				fDistance *= -1;
			}
		}
	}

	bool bGuardSuccess = false;

	// ガード成功判定
	if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] == true)
	{ // ガードをしているか
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{ // 攻撃を行ったプレイヤーの場合
				if (bSkill == true)
				{ // SKILL攻撃の場合は自分の状態にかかわらずガード可能
					bGuardSuccess = true;
				}
				if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == true)
				{ // ジャンプしていた場合
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true || g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] != true)
					{ // 攻撃をうけたプレイヤーもジャンプしていた場合
						// ガード成功
						bGuardSuccess = true;
					}
				}
				else if (g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == true)
				{ // しゃがんでいた場合
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true)
					{ // 攻撃をうけたプレイヤーもしゃがんでいた場合
					  // ガード成功
						bGuardSuccess = true;
					}
				}
				else
				{ // ジャンプもしゃがみも行っていない場合
					if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] != true
						&& g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] != true)
					{ // 攻撃をうけたプレイヤーもジャンプもしゃがみも行っていない場合
						// ガード成功
						bGuardSuccess = true;
					}
				}
			}
		}
	}

	if (bGuardSuccess == true)
	{ //ガード成功時
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD_HIT] = true;

		// ガードに成功したのでダメージ量を減少させる
		nDamage = int(nDamage * PLAYER_GUARD_DAMAGE);

		// ガードに成功したので相手を少し後退させる
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{ // 攻撃を受けたプレイヤーではない場合
			  // 攻撃被弾時の移動量
				g_aPlayer[nCntPlayer].move.x -= fDistance;
			}
		}

		// ガードエフェクト
		SetEffect(HitPos, EFFECTTYPE_GUARD);
	}
	else
	{ // ガード失敗時
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
		{ // プレイヤーがジャンプ中だった場合
		  // ぶっ飛び状態にする
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DOWN;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = false;
			g_aPlayer[nPlayerID].nCounterState = DOWN_TIME;

			if (bigAttack == true)
			{ // 大攻撃
				// ヒットエフェクト大
				SetEffect(HitPos, EFFECTTYPE_HIT_001);

				switch (g_aPlayer[nPlayerID].type)
				{// ぶっとびボイス
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_003_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_003_SE, 0.8f);
					break;
				}
			}
			else
			{ // 小攻撃
				// ヒットエフェクト小
				SetEffect(HitPos, EFFECTTYPE_HIT_000);

				switch (g_aPlayer[nPlayerID].type)
				{// ぶっとびボイス
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_002_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_002_SE, 0.8f);
					break;
				}
			}
		}
		else if (bigAttack == true)
		{ // 大攻撃だった場合
		  // ぶっ飛び状態にする
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DOWN;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = false;
			g_aPlayer[nPlayerID].nCounterState = DOWN_TIME;
			// ヒットエフェクト大
			SetEffect(HitPos, EFFECTTYPE_HIT_001);

			switch (g_aPlayer[nPlayerID].type)
			{// ぶっとびボイス
			case PLAYER_TYPE_BRAVE:
				SelectVolume(SOUND_LABEL_SE_YUSHA_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_DEVIL:
				SelectVolume(SOUND_LABEL_SE_MAOU_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_KING:
				SelectVolume(SOUND_LABEL_SE_OU_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_PEOPLE:
				SelectVolume(SOUND_LABEL_HEIMIN_003_SE, 0.8f);
				break;
			case PLAYER_TYPE_GOD:
				SelectVolume(SOUND_LABEL_GOD_003_SE, 0.8f);
				break;
			}
		}
		else
		{ // その他処理
			g_aPlayer[nPlayerID].state = PLAYERSTATE_DAMAGE;
			g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] = true;
			g_aPlayer[nPlayerID].nCounterState = DAMAGE_TIME;
			// ヒットエフェクト小
			SetEffect(HitPos, EFFECTTYPE_HIT_000);
			switch (g_aPlayer[nPlayerID].type)
			{// ぶっとびボイス
			case PLAYER_TYPE_BRAVE:
				SelectVolume(SOUND_LABEL_SE_YUSHA_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_DEVIL:
				SelectVolume(SOUND_LABEL_SE_MAOU_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_KING:
				SelectVolume(SOUND_LABEL_SE_OU_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_PEOPLE:
				SelectVolume(SOUND_LABEL_HEIMIN_002_SE, 0.8f);
				break;
			case PLAYER_TYPE_GOD:
				SelectVolume(SOUND_LABEL_GOD_002_SE, 0.8f);
				break;
			}
		}

		// 攻撃被弾時の移動量
		if (g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_RIGHT] == false
			&& g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_LEFT] == false)
		{ // 攻撃をうけたプレイヤーが画面端にいない場合
			// 攻撃をうけたプレイヤーを下げる
			g_aPlayer[nPlayerID].move.x += fDistance;
		}
		else
		{ // 攻撃をうけたプレイヤーが画面端にいる場合
			// 移動量を反転
			fDistance *= -1;
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (nCntPlayer != nPlayerID)
				{ // 攻撃を受けたプレイヤーではない場合

					g_aPlayer[nCntPlayer].move.x += fDistance;
				}
			}
		}

	}

	// SEの再生



	if (nDamage < 0)
	{ // ダメージ量が0より大きい場合のみダメージを与える
	  // 最低ダメージ1いれる
		nDamage = 1;
	}

	g_aPlayer[nPlayerID].nLife -= nDamage;

	// HPゲージ更新
	SetHpGageDestLife(g_aPlayer[nPlayerID].nLife, (PLAYER_CONTROL)nPlayerID);

	//SP増加
	AddPlayerSkillPoint(nPlayerID, PLAYER_SKILL_ADD_DEFENSE);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // 攻撃をしたプレイヤー場合
			AddPlayerSkillPoint(nCntPlayer, PLAYER_SKILL_ADD_ATTACK);
		}
	}

	if (g_aPlayer[nPlayerID].nLife <= 0)
	{ // ライフ0以下の処理
		g_aPlayer[nPlayerID].nLife = PLAYER_LIFE;

		// 残機が0以下になった時の処理
		g_aPlayer[nPlayerID].state = PLAYERSTATE_DEATH;
		g_aPlayer[nPlayerID].nCounterState = DEATH_TIME;
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] = true;
		g_aPlayer[nPlayerID].nLife = 0;

		//
		SetBattleState(BATTLESTATE_CLEAR);

		// KOを表示
		SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_KO);
		SelectVolume(SOUND_LABEL_KO_SE, 0.8f);

		// タイマーを停止
		SetTimerSwitch(false);

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (nCntPlayer != nPlayerID)
			{
				PlayerBattleResultSave(nCntPlayer);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ライフの増加
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddPlayerLife(int nPlayerID, int nLife)
{
	g_aPlayer[nPlayerID].nLife += nLife;

	if (g_aPlayer[nPlayerID].nLife > PLAYER_LIFE)
	{// 最大値を超える場合
		g_aPlayer[nPlayerID].nLife = PLAYER_LIFE;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// スキルポイントの増加
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void AddPlayerSkillPoint(int nPlayerID,int nSkillPoint)
{
	g_aPlayer[nPlayerID].nSkillPoint += nSkillPoint;

	if (g_aPlayer[nPlayerID].nSkillPoint > PLAYER_MAX_SKILL_POINT)
	{// 最大値を超える場合
		g_aPlayer[nPlayerID].nSkillPoint = PLAYER_MAX_SKILL_POINT;
	}

	// スキルゲージの変更
	SetSpGageDestSkillPoint(g_aPlayer[nPlayerID].nSkillPoint, (PLAYER_CONTROL)nPlayerID);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Player *GetPlayer(void)
{
	return &g_aPlayer[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーモデルの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
PlayerTypeData *GetPlayerTypeData(void)
{
	return &g_aPlayerType[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーコントローラー
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerController(PLAYER_CONTROL control)
{
	DIJOYSTATE2 *pGamePad = GetgamePadStick((int)control);
	// カメラを取得
	Camera *pCamera = GetCamera();

	if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
	{ // 攻撃中じゃない場合
	  // しゃがみ状態をリセット
		g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;
	}

	// ガード状態をリセット
	g_aPlayer[control].bBool[PLAYER_BOOL_GUARD] = false;

	if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
	{ // ジャンプ中じゃない場合
	  // 方向状態をリセット
		g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = false;
		g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = false;
	}

	if (g_aPlayer[control].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[control].bBool[PLAYER_BOOL_BLOW] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_GETUP] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false && g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
	{ // ダメージ・ぶっ飛び・起き上がり・ジャンプ・攻撃状態でない場合
		if (GetController(control, PLAYER_CONTROLLER_SKILL))
		{ // スキル
			// スキル関数を呼ぶ
			SkillAttack(control);
		}
	}

	if (g_aPlayer[control].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[control].bBool[PLAYER_BOOL_BLOW] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_GETUP] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false
		&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false && g_aPlayer[control].bBool[PLAYER_BOOL_SKILL] == false)
	{ // ダメージ・ぶっ飛び・起き上がり・攻撃・スキル状態でない場合
		if (GetController(control, PLAYER_CONTROLLER_DOWN))
		{ // しゃがみ
			if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
			{
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = true;
			}
		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] == false && g_aPlayer[control].bBool[PLAYER_BOOL_GUARD_HIT] == false
			&& g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false)
		{ // 攻撃・しゃがみ・ジャンプ中じゃない
			 // 移動処理
			if (GetController(control, PLAYER_CONTROLLER_LEFT))
			{ // 左移動
				g_aPlayer[control].move.x -= g_aPlayer[control].fMoveSpeed;
			}
			else if (GetController(control, PLAYER_CONTROLLER_RIGHT))
			{ // 右移動
				g_aPlayer[control].move.x += g_aPlayer[control].fMoveSpeed;
			}
		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
		{ // 攻撃中じゃない
			if (GetController(control, PLAYER_CONTROLLER_ATTACK_SMALL))
			{ // 弱攻撃
				g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] = true;
				switch (g_aPlayer[control].type)
				{// 攻撃ボイス
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_000_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_000_SE, 0.8f);
					break;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_ATTACK_BIG))
			{ // 強攻撃
				g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] = true;
				switch (g_aPlayer[control].type)
				{// 攻撃ボイス
				case PLAYER_TYPE_BRAVE:
					SelectVolume(SOUND_LABEL_SE_YUSHA_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_DEVIL:
					SelectVolume(SOUND_LABEL_SE_MAOU_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_KING:
					SelectVolume(SOUND_LABEL_SE_OU_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_PEOPLE:
					SelectVolume(SOUND_LABEL_HEIMIN_001_SE, 0.8f);
					break;
				case PLAYER_TYPE_GOD:
					SelectVolume(SOUND_LABEL_GOD_001_SE, 0.8f);
					break;
				}
			}
			else
			{ // 攻撃入力をしなかった場合
			  // ガードをしているか確認
				CheckGuard(control);
			}
		}

		if (g_aPlayer[control].MotionType != PLAYER_MOTION_TYPE_ATTACK_SMALL)
		{ // 攻撃モーションじゃない時
		  // 攻撃SEの停止

		}

		if (g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] == false
			&& g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[control].bBool[PLAYER_BOOL_ATTACK_BIG] == false)
		{ // ジャンプ・攻撃中じゃない時
			if (GetController(control, PLAYER_CONTROLLER_LEFT_UP))
			{ // 左ジャンプ
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.x = sinf(-D3DX_PI / 4) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// しゃがみ状態を解除
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;

				if (g_aPlayer[control].side == PLAYER_SIDE_LEFT)
				{ // プレイヤーが左側にいる場合
					g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = true;
				}
				else
				{ // 右側にいる場合
					g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = true;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_RIGHT_UP))
			{ // 右ジャンプ
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.x = sinf(D3DX_PI / 4) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// しゃがみ状態を解除
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;

				if (g_aPlayer[control].side == PLAYER_SIDE_RIGHT)
				{ // プレイヤーが右側にいる場合
					g_aPlayer[control].bBool[PLAYER_BOOL_BACK] = true;
				}
				else
				{ // 左側にいる場合
					g_aPlayer[control].bBool[PLAYER_BOOL_FRONT] = true;
				}
			}
			else if (GetController(control, PLAYER_CONTROLLER_UP))
			{ // 上ジャンプ
				g_aPlayer[control].nKeyCnt = 0;
				g_aPlayer[control].move.y = cosf(0) * g_aPlayer[control].fJampMove;
				g_aPlayer[control].bBool[PLAYER_BOOL_JUMP] = true;
				// しゃがみ状態を解除
				g_aPlayer[control].bBool[PLAYER_BOOL_SQUAT] = false;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	攻撃当たり判定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionAttack(int nPlayerID)
{
#if DEBUG_SPHERE
	// デバッグ用のスフィアを非表示にする(攻撃
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
			{
				SetDispSphere(g_aPlayerType[nCntType].aMotion[nCntMotion].collisionA[nCntCollision].nSpherID[nPlayerID], false);
			}
		}
	}
#endif // DEBUG_SPHERE

	bool bHit = false;

	if (g_aPlayer[nPlayerID].MotionTypeHit != g_aPlayer[nPlayerID].MotionType)
	{ // 前回当てた攻撃が今回と違う場合のみ判定を行う
		for (int nCntCollisionA = 0; nCntCollisionA < MAX_PLAYER_ATTACK_COLLISION; nCntCollisionA++)
		{
			if (g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].bUse == true
				&& g_aPlayer[nPlayerID].nAllFrameCounter >= g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nFrameS
				&& g_aPlayer[nPlayerID].nAllFrameCounter <= g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nFrameE)
			{
				D3DXMATRIX mtxWorldA, mtxRotA, mtxTransA;			// 計算用マトリックス

				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&mtxWorldA);

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotA, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.y,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.x,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].rot.z);

				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA, &mtxRotA);

				// 位置を反映
				D3DXMatrixTranslation(&mtxTransA, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.x,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.y,
					g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].pos.z);

				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA, &mtxTransA);

				// 親のワールドマトリックスを反映
				D3DXMatrixMultiply(&mtxWorldA, &mtxWorldA,
					&g_aPlayer[nPlayerID].aModel[g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nPartsId].mtxWorld);

#if DEBUG_SPHERE
				// デバッグ用のスフィア移動処理
				SetPositionSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nSpherID[nPlayerID],
					D3DXVECTOR3(mtxWorldA._41, mtxWorldA._42, mtxWorldA._43));

				// デバッグ用のスフィアを表示
				SetDispSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nSpherID[nPlayerID], true);
#endif // DEBUG_SPHERE

				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{
					if (nCntPlayer != nPlayerID && g_aPlayer[nCntPlayer].state != PLAYERSTATE_DOWN && g_aPlayer[nCntPlayer].state != PLAYERSTATE_GETUP)
					{ // 攻撃を受けるプレイヤーが攻撃したプレイヤーではなく、ぶっ飛び状態でも起き上がり状態でもない場合
						for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
						{
							if (g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].bUse == true && bHit == false)
							{ // 防御判定が使用されておりまだ被弾していない場合
								D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// 計算用マトリックス

								// ワールドマトリックスの初期化
								D3DXMatrixIdentity(&mtxWorldD);

								// 回転を反映
								D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.y,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.x,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.z);

								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

								// 位置を反映
								D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.x,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.y,
									g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.z);

								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

								// 親のワールドマトリックスを反映
								D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
									&g_aPlayer[nCntPlayer].aModel[g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

								float fLength = sqrtf((mtxWorldA._41 - mtxWorldD._41) * (mtxWorldA._41 - mtxWorldD._41)
									+ (mtxWorldA._42 - mtxWorldD._42) * (mtxWorldA._42 - mtxWorldD._42));

								if (fLength < g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].fRadius
									+ g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // 範囲内
									D3DXVECTOR3 HitPos = D3DXVECTOR3(mtxWorldA._41, mtxWorldA._42, mtxWorldA._43);
									HitPos += D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43);
									HitPos /= 2.0f;
								  // ダメージを与える
									HitPlayer(HitPos, nCntPlayer, g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].nDamage,
										g_aPlayerType[g_aPlayer[nPlayerID].type].aMotion[g_aPlayer[nPlayerID].MotionType].collisionA[nCntCollisionA].fDistance, g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_BIG],false);
									bHit = true;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return bHit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	スキル攻撃当たり判定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool CollisionSkillAttack(int nPlayerID)
{
	bool bHit = false;

	if (g_aPlayer[nPlayerID].MotionTypeHit != g_aPlayer[nPlayerID].MotionType)
	{ // 前回当てた攻撃が今回と違う場合のみ判定を行う
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true
			&& g_aPlayer[nPlayerID].nAllFrameCounter == PLAYER_SKILL_START_FRAME)
		{ // スキルを使用中/スキル判定開始フレームを超えた場合
			if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
			{  // 攻撃を行ったプレイヤーが左側にいる
				switch (g_aPlayer[nPlayerID].type)
				{
				case PLAYER_TYPE_BRAVE:
					// スキルエフェクトを使用
					//SetTextureAnim(D3DXVECTOR3(0.0f, 100.0f, 0.0f), TEXANIM_RAIZIN_R);
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_R);
					break;
				case PLAYER_TYPE_DEVIL:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
					break;
				case PLAYER_TYPE_KING:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
					break;
				case PLAYER_TYPE_PEOPLE:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
					break;
				case PLAYER_TYPE_GOD:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
					break;
				}

			}
			else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
			{  // 攻撃を行ったプレイヤーが右側にいる
				switch (g_aPlayer[nPlayerID].type)
				{
				case PLAYER_TYPE_BRAVE:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_L);
					break;
				case PLAYER_TYPE_DEVIL:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
					break;
				case PLAYER_TYPE_KING:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
					break;
				case PLAYER_TYPE_PEOPLE:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
					break;
				case PLAYER_TYPE_GOD:
					// スキルエフェクトを使用
					SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
					break;
				}
			}
		}
		if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] == true
			&& g_aPlayer[nPlayerID].nAllFrameCounter >= PLAYER_SKILL_START_FRAME)
		{ // スキルを使用中/スキル判定開始フレームを超えた場合
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (nCntPlayer != nPlayerID && g_aPlayer[nCntPlayer].state != PLAYERSTATE_DOWN && g_aPlayer[nCntPlayer].state != PLAYERSTATE_GETUP)
				{ // 攻撃を受けるプレイヤーが攻撃したプレイヤーではなく、ぶっ飛び状態でも起き上がり状態でもない場合
					for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
					{
						if (g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].bUse == true && bHit == false)
						{ // 防御判定が使用されておりまだ被弾していない場合
							D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// 計算用マトリックス

							// ワールドマトリックスの初期化
							D3DXMatrixIdentity(&mtxWorldD);

							// 回転を反映
							D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.y,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.x,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].rot.z);

							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

							// 位置を反映
							D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.x,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.y,
								g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].pos.z);

							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

							// 親のワールドマトリックスを反映
							D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
								&g_aPlayer[nCntPlayer].aModel[g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

							g_nPlayerSkillDamage[PLAYER_MAX_SKILL_RANK][PLAYER_TYPE_MAX];	// スキルダメージ量
							g_nPlayerSkillWidth[PLAYER_TYPE_MAX];							// スキル判定幅
							g_nPlayerSkillHeight[PLAYER_TYPE_MAX];						// スキル判定高さ

							D3DXVECTOR3 HitPos = D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43);
							if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
							{  // 攻撃を行ったプレイヤーが左側にいる
								if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius < mtxWorldD._41 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nCntPlayer].type] > mtxWorldD._41 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] < mtxWorldD._42 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] + g_nPlayerSkillHeight[g_aPlayer[nCntPlayer].type] > mtxWorldD._42 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // 範囲内
									// ダメージを与える
									HitPlayer(HitPos, nCntPlayer, g_nPlayerSkillDamage[g_aPlayer[nPlayerID].nSkillRank-1][(int)g_aPlayer[nPlayerID].type], PLAYER_SKILL_DISTANCE, true,true);
									bHit = true;
									break;
								}
							}
							else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
							{  // 攻撃を行ったプレイヤーが右側にいる
								if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius > mtxWorldD._41 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nCntPlayer].type] < mtxWorldD._41 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] < mtxWorldD._42 + g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius
									&& g_nPlayerSkillPosY[g_aPlayer[nCntPlayer].type] + g_nPlayerSkillHeight[g_aPlayer[nCntPlayer].type] > mtxWorldD._42 - g_aPlayerType[g_aPlayer[nCntPlayer].type].collisionD[nCntCollisionD].fRadius)
								{ // 範囲内
								  // ダメージを与える
									HitPlayer(HitPos, nCntPlayer, g_nPlayerSkillDamage[g_aPlayer[nPlayerID].nSkillRank-1][(int)g_aPlayer[nPlayerID].type], PLAYER_SKILL_DISTANCE, true,true);
									bHit = true;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return bHit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	スキル攻撃処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool SkillAttack(int nPlayerID)
{
	bool bSkill = false;

	if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_3)
	{
		g_aPlayer[nPlayerID].nSkillRank = 3;
		bSkill = true;
	}
	else if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_2)
	{
		g_aPlayer[nPlayerID].nSkillRank = 2;
		bSkill = true;
	}
	else if (g_aPlayer[nPlayerID].nSkillPoint >= PLAYER_SKILL_RANK_1)
	{
		g_aPlayer[nPlayerID].nSkillRank = 1;
		bSkill = true;
	}

	if (bSkill == true)
	{
		g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SKILL] = true;
		g_aPlayer[nPlayerID].nSkillPoint = 0;
		// スキルゲージの変更
		SetSpGageDestSkillPoint(g_aPlayer[nPlayerID].nSkillPoint, (PLAYER_CONTROL)nPlayerID);
		// バトル状態をスキルにする
		SetBattleState(BATTLESTATE_SKILL);

		//if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_LEFT)
		//{  // 攻撃を行ったプレイヤーが左側にいる
		//	switch (g_aPlayer[nPlayerID].type)
		//	{
		//	case PLAYER_TYPE_BRAVE:
		//		// スキルエフェクトを使用
		//		//SetTextureAnim(D3DXVECTOR3(0.0f, 100.0f, 0.0f), TEXANIM_RAIZIN_R);
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_R);
		//		break;
		//	case PLAYER_TYPE_DEVIL:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
		//		break;
		//	case PLAYER_TYPE_KING:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
		//		break;
		//	case PLAYER_TYPE_PEOPLE:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
		//		break;
		//	case PLAYER_TYPE_GOD:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius + g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
		//		break;
		//	}

		//}
		//else if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
		//{  // 攻撃を行ったプレイヤーが右側にいる
		//	switch (g_aPlayer[nPlayerID].type)
		//	{
		//	case PLAYER_TYPE_BRAVE:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_RAIZIN_L);
		//		break;
		//	case PLAYER_TYPE_DEVIL:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_DARK);
		//		break;
		//	case PLAYER_TYPE_KING:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GRAVITY);
		//		break;
		//	case PLAYER_TYPE_PEOPLE:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type], 0.0f), TEXANIM_FISSURES);
		//		break;
		//	case PLAYER_TYPE_GOD:
		//		// スキルエフェクトを使用
		//		SetTextureAnim(D3DXVECTOR3(g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius - g_nPlayerSkillWidth[g_aPlayer[nPlayerID].type] / 2.0f, g_nPlayerSkillPosY[g_aPlayer[nPlayerID].type] + g_nPlayerSkillHeight[g_aPlayer[nPlayerID].type] / 2.0f, 0.0f), TEXANIM_GOD);
		//		break;
		//	}
		//}

		switch (g_aPlayer[nPlayerID].type)
		{// スキルボイス
		case PLAYER_TYPE_BRAVE:
			SelectVolume(SOUND_LABEL_SE_YUSHA_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_DEVIL:
			SelectVolume(SOUND_LABEL_SE_MAOU_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_KING:
			SelectVolume(SOUND_LABEL_SE_OU_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_PEOPLE:
			SelectVolume(SOUND_LABEL_HEIMIN_004_SE, 0.8f);
			break;
		case PLAYER_TYPE_GOD:
			SelectVolume(SOUND_LABEL_GOD_004_SE, 0.8f);
			break;
		}
	}

	return bSkill;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//	判定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CollisionMove(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != nPlayerID)
		{ // 自分じゃない場合

			float fIDPlayerMoveX = g_aPlayer[nPlayerID].move.x;
			float fCntPlayerMoveX = g_aPlayer[nCntPlayer].move.x;

			if (fIDPlayerMoveX < 0)
			{
				fIDPlayerMoveX *= -1.0f;
			}
			if (fCntPlayerMoveX < 0)
			{
				fCntPlayerMoveX *= -1.0f;
			}

			D3DXVECTOR3 posID;
			posID.x = g_aPlayer[nPlayerID].pos.x;
			posID.y = g_aPlayer[nPlayerID].pos.y + g_aPlayer[nPlayerID].fHeight / 2.0f;
			posID.z = g_aPlayer[nPlayerID].pos.z;

			D3DXVECTOR3 posCnt;
			posCnt.x = g_aPlayer[nCntPlayer].pos.x;
			posCnt.y = g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight / 2.0f;
			posCnt.z = g_aPlayer[nCntPlayer].pos.z;

			float fLength = sqrtf((posID.x - posCnt.x) * (posID.x - posCnt.x)
				+ (posID.y - posCnt.y) * (posID.y - posCnt.y));

#if 0
			if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_JUMP] == false
				&& g_aPlayer[nPlayerID].bBoolOld[PLAYER_BOOL_JUMP] == false && g_aPlayer[nCntPlayer].bBoolOld[PLAYER_BOOL_JUMP] == false)
			{
				if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius
					&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius
					&& g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
					&& g_aPlayer[nPlayerID].posOld.y >= g_aPlayer[nCntPlayer].posOld.y + g_aPlayer[nCntPlayer].fHeight)
				{
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//IDのプレイヤーの移動量の方が大きい場合
						if (g_aPlayer[nPlayerID].pos.x > g_aPlayer[nCntPlayer].pos.x)
						{ // IDプレイヤーが右側にいる場合
							g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius - g_aPlayer[nPlayerID].fCollisionRadius;
						}
						else
						{ // 左側にいる場合
							g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius + g_aPlayer[nPlayerID].fCollisionRadius;
						}
					}
					else
					{ //Cntプレイヤーの移動量の方が大きい場合
						if (g_aPlayer[nPlayerID].pos.x < g_aPlayer[nCntPlayer].pos.x)
						{ // Cntプレイヤーが右側にいる場合
							g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nPlayerID].fCollisionRadius - g_aPlayer[nCntPlayer].fCollisionRadius;
						}
						else
						{ // 左側にいる場合
							g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius;
						}
					}
				}
				else if (g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
					&& g_aPlayer[nPlayerID].pos.y + g_aPlayer[nCntPlayer].fHeight > g_aPlayer[nCntPlayer].pos.y)
				{ // Yが範囲内（左右判定用
					if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius
						&& g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius)
					{ // Xが範囲内
						if (fIDPlayerMoveX > fCntPlayerMoveX)
						{//IDのプレイヤーの移動量の方が大きい場合
							if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
							{ // IDプレイヤーが右側にいる場合
								g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fCollisionRadius - g_aPlayer[nPlayerID].fCollisionRadius;
							}
							else
							{ // 左側にいる場合
								g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fCollisionRadius + g_aPlayer[nPlayerID].fCollisionRadius;
							}
						}
						else
						{ //Cntプレイヤーの移動量の方が大きい場合
							if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
							{ // Cntプレイヤーが右側にいる場合
								g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nPlayerID].fCollisionRadius - g_aPlayer[nCntPlayer].fCollisionRadius;
							}
							else
							{ // 左側にいる場合
								g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius;
							}
						}
					}
				}
			}
#endif
			if (fLength < g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius)
			{ // 範囲内
				if (fIDPlayerMoveX > 0.0f && fCntPlayerMoveX > 0.0f)
				{//IDのプレイヤーの移動量の方が大きい場合
					D3DXVECTOR3 posCenter;

					// 当たり判定の中心位置
					posCenter = (posID + posCnt) / 2.0f;

					float fAngle = atan2f((posID.x - posCnt.x), (posID.y - posCnt.y));

					g_aPlayer[nPlayerID].pos = posCenter + D3DXVECTOR3(sinf(fAngle), cosf(fAngle), 0.0f) * (g_aPlayer[nPlayerID].fCollisionRadius);
					g_aPlayer[nPlayerID].pos.y -= g_aPlayer[nPlayerID].fHeight / 2.0f;


					float fAngle2 = atan2f((posCnt.x - posID.x), (posCnt.y - posID.y));

					g_aPlayer[nCntPlayer].pos = posCenter + D3DXVECTOR3(sinf(fAngle2), cosf(fAngle2), 0.0f) * (g_aPlayer[nCntPlayer].fCollisionRadius);
					g_aPlayer[nCntPlayer].pos.y -= g_aPlayer[nCntPlayer].fHeight / 2.0f;

					// オブジェクトとメッシュフィールド当たり判定
					CollisionMeshBattleField(&g_aPlayer[nCntPlayer].pos, &g_aPlayer[nCntPlayer].posOld, &g_aPlayer[nCntPlayer].move, g_aPlayer[nCntPlayer].fRadius);
				}
				else if (fIDPlayerMoveX < fCntPlayerMoveX)
				{//IDのプレイヤーの移動量の方が大きい場合
					float fAngle = atan2f((posID.x - posCnt.x), (posID.y - posCnt.y));

					g_aPlayer[nPlayerID].pos = posCnt + D3DXVECTOR3(sinf(fAngle), cosf(fAngle), 0.0f) * (g_aPlayer[nPlayerID].fCollisionRadius + g_aPlayer[nCntPlayer].fCollisionRadius);
					g_aPlayer[nPlayerID].pos.y -= g_aPlayer[nPlayerID].fHeight / 2.0f;

				}

			}

#if 0
			if (g_aPlayer[nPlayerID].pos.y < g_aPlayer[nCntPlayer].pos.y + g_aPlayer[nCntPlayer].fHeight
				&& g_aPlayer[nPlayerID].pos.y + g_aPlayer[nCntPlayer].fHeight > g_aPlayer[nCntPlayer].pos.y)
			{ // Yが範囲内（左右判定用
				if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fRadius > g_aPlayer[nCntPlayer].pos.x - g_aPlayer[nCntPlayer].fRadius
					&& g_aPlayer[nPlayerID].posOld.x + g_aPlayer[nPlayerID].fRadius <= g_aPlayer[nCntPlayer].posOld.x - g_aPlayer[nCntPlayer].fRadius)
				{ // 左から
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//IDのプレイヤーの移動量の方が大きい場合
						g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x + g_aPlayer[nCntPlayer].fRadius + g_aPlayer[nPlayerID].fRadius;
						// 移動量を変更
						g_aPlayer[nCntPlayer].move.x = g_aPlayer[nPlayerID].move.x;
					}
					else
					{ //Cntプレイヤーの移動量の方が大きい場合
						g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fRadius + g_aPlayer[nCntPlayer].fRadius;
						// 移動量を変更
						g_aPlayer[nPlayerID].move.x = g_aPlayer[nCntPlayer].move.x;
					}
				}
				else if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fRadius < g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nCntPlayer].fRadius
					&& g_aPlayer[nPlayerID].posOld.x - g_aPlayer[nPlayerID].fRadius >= g_aPlayer[nCntPlayer].posOld.x + g_aPlayer[nCntPlayer].fRadius)
				{ // 右から
					if (fIDPlayerMoveX > fCntPlayerMoveX)
					{//IDのプレイヤーの移動量の方が大きい場合
						g_aPlayer[nCntPlayer].pos.x = g_aPlayer[nPlayerID].pos.x - g_aPlayer[nCntPlayer].fRadius - g_aPlayer[nPlayerID].fRadius;
						// 移動量を変更
						g_aPlayer[nCntPlayer].move.x = g_aPlayer[nPlayerID].move.x;
					}
					else
					{ //Cntプレイヤーの移動量の方が大きい場合
						g_aPlayer[nPlayerID].pos.x = g_aPlayer[nCntPlayer].pos.x + g_aPlayer[nPlayerID].fRadius + g_aPlayer[nCntPlayer].fRadius;
						// 移動量を変更
						g_aPlayer[nPlayerID].move.x = g_aPlayer[nCntPlayer].move.x;
					}
				}
			}
#endif
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// モーションtxtデータの読み込み
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadMotion(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	FILE *pFileInFile;
	char cLine[MAX_LOAD_LINE];			// 1行の一時的読み込み
	char cData[MAX_LOAD_LINE];			// 一時的読み込み

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;
	D3DXMATERIAL *pMat;						// マテリアルデータへのポインタ

	pFile = fopen(PLAYER_MOTION_LOADTXT_NAME, "r"); // ファイルを開く

	if (pFile != NULL) // pFileがNULL(空白）ではないときを真
	{ // ファイルが開けた際の処理
		while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
		{
			sscanf(cLine, "%s", cData);
			if (strcmp(cData, "MOTION_FILENAME") == 0)
			{
				int nCntModel = 0;
				int nCntMotion = 0;			// モーション数

				sscanf(cLine, "%s %s %s", cData, cData, cData);

				pFileInFile = fopen(cData, "r"); // ファイルを開く

				if (pFileInFile != NULL) // pFileがNULL(空白）ではないときを真
				{ // ファイルが開けた際の処理ss
					while (fgets(cLine, MAX_LOAD_LINE, pFileInFile) != NULL)
					{
						sscanf(cLine, "%s", cData);
						if (strcmp(cData, "NUM_MODEL") == 0)
						{
							sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].nModelParts);
						}
						else if (strcmp(cData, "MODEL_FILENAME") == 0)
						{
							sscanf(cLine, "%s %s %s", cData, cData, cData);

							D3DXLoadMeshFromX(cData,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat,
								NULL,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat,
								&g_aPlayerType[nCntType].apPlayer[nCntModel].pMesh);

							// マテリアルデータへのポインタを取得
							pMat = (D3DXMATERIAL*)g_aPlayerType[nCntType].apPlayer[nCntModel].pBuffMat->GetBufferPointer();

							g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[(int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat];

							for (int nCntMat = 0; nCntMat < (int)g_aPlayerType[nCntType].apPlayer[nCntModel].nNumMat; nCntMat++)
							{
								g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntMat] = NULL;
								if (pMat[nCntMat].pTextureFilename != NULL)
								{
									D3DXCreateTextureFromFile(pDevice,
										pMat[nCntMat].pTextureFilename,
										&g_aPlayerType[nCntType].apPlayer[nCntModel].pTexture[nCntMat]);
								}
							}
							nCntModel++;
						}
						else if (strcmp(cData, "CHARACTERSET") == 0)
						{
							int nCntParts = 0;

							while (strcmp(cData, "END_CHARACTERSET") != 0)
							{
								fgets(cLine, MAX_LOAD_LINE, pFileInFile);

								sscanf(cLine, "%s", cData);

								if (strcmp(cData, "MOVE") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fMoveSpeed);
								}
								else if (strcmp(cData, "JUMP") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fJampMove);
								}
								else if (strcmp(cData, "RADIUS") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fRadius);
								}
								else if (strcmp(cData, "HEIGHT") == 0)
								{
									sscanf(cLine, "%s %s %f", cData, cData, &g_aPlayerType[nCntType].fHeight);
								}
								else if (strcmp(cData, "NUM_PARTS") == 0)
								{
									sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].nModelParts);
								}
								else if (strcmp(cData, "PARTSSET") == 0)
								{
									int nIndex = 0;
									while (strcmp(cData, "END_PARTSSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "INDEX") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nIndex);

											g_aPlayerType[nCntType].aModel[nCntParts].nModelType = nIndex;
										}
										else if (strcmp(cData, "PARENT") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].nIdxModelParent);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].pos.x,
												&g_aPlayerType[nCntType].aModel[nCntParts].pos.y,
												&g_aPlayerType[nCntType].aModel[nCntParts].pos.z);
										}
										else if (strcmp(cData, "ROT") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aModel[nCntParts].rot.x,
												&g_aPlayerType[nCntType].aModel[nCntParts].rot.y,
												&g_aPlayerType[nCntType].aModel[nCntParts].rot.z);
										}
									}
									nCntParts++;
								}
								else if (strcmp(cData, "DAMAGE") == 0)
								{
									sscanf(cLine, "%s %s %f %f", cData, cData, &g_aPlayerType[nCntType].fDamage, &g_aPlayerType[nCntType].fKnockBack);
								}
								else if (strcmp(cData, "COLLISIONSET") == 0)
								{
									int nPartsId;
									D3DXVECTOR3 pos;
									float fRadius;

									while (strcmp(cData, "END_COLLISIONSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "PARTSID") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nPartsId);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
										}
										else if (strcmp(cData, "RADIUS") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fRadius);
										}
									}
									// 当たり判定を設定
									SetCollisionDefense(nCntType, nPartsId, pos, fRadius);
								}


							}
						}
						else if (strcmp(cData, "MOTIONSET") == 0)
						{
							int nCntKey = 0;
							while (strcmp(cData, "END_MOTIONSET") != 0)
							{
								fgets(cLine, MAX_LOAD_LINE, pFileInFile);
								sscanf(cLine, "%s", cData);

								if (strcmp(cData, "LOOP") == 0)
								{
									int nLoop;
									sscanf(cLine, "%s %s %d", cData, cData, &nLoop);
									if (nLoop == 0)
									{
										g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = false;
									}
									else
									{
										g_aPlayerType[nCntType].aMotion[nCntMotion].bLoop = true;
									}
								}
								else if (strcmp(cData, "NUM_KEY") == 0)
								{
									sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].nNumKey);
								}
								else if (strcmp(cData, "KEYSET") == 0)
								{
									int nCntParts = 0;
									while (strcmp(cData, "END_KEYSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].nFrame);
										}
										else if (strcmp(cData, "KEY") == 0)
										{
											while (strcmp(cData, "END_KEY") != 0)
											{
												fgets(cLine, MAX_LOAD_LINE, pFileInFile);
												sscanf(cLine, "%s", cData);
												if (strcmp(cData, "POS") == 0)
												{
													sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.x,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.y,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].pos.z);
												}
												else if (strcmp(cData, "ROT") == 0)
												{
													sscanf(cLine, "%s %s %f %f %f", cData, cData, &g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.x,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.y,
														&g_aPlayerType[nCntType].aMotion[nCntMotion].aKey[nCntKey].aPartsKey[nCntParts].rot.z);
												}
											}
											nCntParts++;
										}
									}
									nCntKey++;
								}
								else if (strcmp(cData, "COLLISIONSET") == 0)
								{
									int nPartsId, nFrameS, nFrameE, nDamage;
									D3DXVECTOR3 pos;
									float fRadius, fDistance;

									fDistance = 0.0f;

									while (strcmp(cData, "END_COLLISIONSET") != 0)
									{
										fgets(cLine, MAX_LOAD_LINE, pFileInFile);
										sscanf(cLine, "%s", cData);

										if (strcmp(cData, "PARTSID") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nPartsId);
										}
										else if (strcmp(cData, "POS") == 0)
										{
											sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
										}
										else if (strcmp(cData, "RADIUS") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fRadius);
										}
										else if (strcmp(cData, "START_FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nFrameS);
										}
										else if (strcmp(cData, "END_FRAME") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nFrameE);
										}
										else if (strcmp(cData, "DAMAGE") == 0)
										{
											sscanf(cLine, "%s %s %d", cData, cData, &nDamage);
										}
										else if (strcmp(cData, "DISTANCE") == 0)
										{
											sscanf(cLine, "%s %s %f", cData, cData, &fDistance);
										}
									}

									// コリジョン = パーツ番号,x,y,z,半径,判定 開始フレーム 終了フレーム
									//sscanf(cLine, "%s %s %d %f %f %f %f %d %d", cData, cData, &nPartsId, &pos.x, &pos.y, &pos.z,&fRadius, &nFrameS, &nFrameE);

									// 当たり判定を設定
									SetCollisionAttack(nCntType, nCntMotion, nPartsId, pos, fRadius, nFrameS, nFrameE, nDamage, fDistance);
								}
							}
							nCntMotion++;
						}
					}
					fclose(pFileInFile); // ファイルを閉じる

										 // モデルのデータを進める
					nCntType++;
				}
				else
				{ // ファイルが開けなかった際の処理

				}

			}
			else if (strcmp(cData, "PLAYERSET") == 0)
			{
				PLAYER_TYPE type;
				D3DXVECTOR3 pos;
				D3DXVECTOR3 rot;

				while (strcmp(cData, "END_PLAYERSET") != 0)
				{
					fgets(cLine, MAX_LOAD_LINE, pFile);
					sscanf(cLine, "%s", cData);

					if (strcmp(cData, "TYPE") == 0)
					{
						sscanf(cLine, "%s %s %d", cData, cData, &type);
					}
					else if (strcmp(cData, "POS") == 0)
					{
						sscanf(cLine, "%s %s %f %f %f", cData, cData, &pos.x, &pos.y, &pos.z);
					}
					else if (strcmp(cData, "ROT") == 0)
					{
						sscanf(cLine, "%s %s %f %f %f", cData, cData, &rot.x, &rot.y, &rot.z);
					}
				}
				SetPlayerInfo(pos, rot, type);
			}
		}
		fclose(pFile); // ファイルを閉じる
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 攻撃判定設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCollisionAttack(int nPlayerType, int nMotionType, int nPartsId, D3DXVECTOR3 pos, float fRadius, int nFrameS, int nFrameE, int nDamage, float fDistance)
{
	for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_ATTACK_COLLISION; nCntCollision++)
	{
		if (!g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].bUse)
		{
			// 親パーツを設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nPartsId = nPartsId;
			// 位置を設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].pos = pos;
			// 半径を設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fRadius = fRadius;
			// 開始フレームを設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nFrameS = nFrameS;
			// 終了フレームを設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nFrameE = nFrameE;
			// ダメージ量を設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nDamage = nDamage;
			// 攻撃Hit時の移動量を設定
			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fDistance = fDistance;

			g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].bUse = true;

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// デバッグ用のスフィアを生成
				g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].nSpherID[nCntPlayer]
					= SetSphere(g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].pos, g_aPlayerType[nPlayerType].aMotion[nMotionType].collisionA[nCntCollision].fRadius,
						MESHSPHERE_TYPE_ATTACK, true);
			}
#endif // DEBUG_SPHERE
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 防御判定設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCollisionDefense(int nPlayerType, int nPartsId, D3DXVECTOR3 pos, float fRadius)
{
	for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
	{
		if (!g_aPlayerType[nPlayerType].collisionD[nCntCollision].bUse)
		{
			// 親パーツを設定
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].nPartsId = nPartsId;
			// 位置を設定
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].pos = pos;
			// 半径を設定
			g_aPlayerType[nPlayerType].collisionD[nCntCollision].fRadius = fRadius;

			g_aPlayerType[nPlayerType].collisionD[nCntCollision].bUse = true;

#if DEBUG_SPHERE
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// デバッグ用のスフィアを生成
				g_aPlayerType[nPlayerType].collisionD[nCntCollision].nSpherID[nCntPlayer]
					= SetSphere(g_aPlayerType[nPlayerType].collisionD[nCntCollision].pos, g_aPlayerType[nPlayerType].collisionD[nCntCollision].fRadius,
						MESHSPHERE_TYPE_DEFENSE, true);
			}
#endif // DEBUG_SPHERE
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 移動確認処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckMove(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer)
		{ // 自分以外のプレイヤーの場合
		  // 自分と他のプレイヤーとの距離を算出
			float fWidth = (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].move.x) - g_aPlayer[nCntPlayer].pos.x;
			if (fWidth < 0)
			{
				fWidth *= -1;
			}

			if (fWidth > g_nMoveRimit)
			{ // 距離が制限距離を超える場合移動量を0にする
				g_aPlayer[nPlayerID].move.x = 0.0f;
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 移動可能範囲確認処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckMoveArea(int nPlayerID)
{
	// 移動可能範囲の場所にいるかどうか
	for (int nCntArea = 0; nCntArea < PLAYER_SIDE_MAX; nCntArea++)
	{
		g_aPlayer[nPlayerID].bAreaLimit[nCntArea] = false;
	}

	if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < PLAYER_MOVE_LIMIT_LEFT + 10.0f)
	{
		g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_LEFT] = true;
	}
	else if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > PLAYER_MOVE_LIMIT_RIGHT - 10.0f)
	{
		g_aPlayer[nPlayerID].bAreaLimit[PLAYER_SIDE_RIGHT] = true;
	}

	if (g_aPlayer[nPlayerID].pos.x - g_aPlayer[nPlayerID].fCollisionRadius < PLAYER_MOVE_LIMIT_LEFT)
	{
		g_aPlayer[nPlayerID].pos.x = PLAYER_MOVE_LIMIT_LEFT + g_aPlayer[nPlayerID].fCollisionRadius;
	}
	else if (g_aPlayer[nPlayerID].pos.x + g_aPlayer[nPlayerID].fCollisionRadius > PLAYER_MOVE_LIMIT_RIGHT)
	{
		g_aPlayer[nPlayerID].pos.x = PLAYER_MOVE_LIMIT_RIGHT - g_aPlayer[nPlayerID].fCollisionRadius;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 向き確認処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckRot(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_ATTACK_SMALL] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == false
			&& g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_DAMAGE] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_BLOW] == false && g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GETUP] == false)
		{ // 自分以外のプレイヤーの場合
			if (g_aPlayer[nPlayerID].pos.x > g_aPlayer[nCntPlayer].pos.x)
			{ // 左向き
				g_aPlayer[nPlayerID].side = PLAYER_SIDE_RIGHT;
			}
			else
			{ // 右向き
				g_aPlayer[nPlayerID].side = PLAYER_SIDE_LEFT;
			}
		}
	}

	if (g_aPlayer[nPlayerID].side == PLAYER_SIDE_RIGHT)
	{ // 左向き
		g_aPlayer[nPlayerID].rot.y = (D3DX_PI / 4) * 2;
	}
	else
	{ // 右向き
		g_aPlayer[nPlayerID].rot.y = -(D3DX_PI / 4) * 2;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ガード確認処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void CheckGuard(int nPlayerID)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nPlayerID != nCntPlayer)
		{ // 自分以外のプレイヤーの場合
			if (g_aPlayer[nCntPlayer].side == PLAYER_SIDE_RIGHT)
			{ // 相手が右にいる場合
				if (GetController((PLAYER_CONTROL)nPlayerID, PLAYER_CONTROLLER_LEFT))
				{ // 左入力
					//if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_JUMP] == true)
					//{ // 自分がジャンプ中場合
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					//else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == true
					//	&& g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == true)
					//{ // 自分も相手もしゃがみ中の場合
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					//else if (g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_SQUAT] == false
					//	&& g_aPlayer[nCntPlayer].bBool[PLAYER_BOOL_SQUAT] == false)
					//{ // 自分も相手もしゃがみ中でない場合
					//	g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
					//}
					g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
				}
			}
			else
			{ // 相手が左にいる場合
				if (GetController((PLAYER_CONTROL)nPlayerID, PLAYER_CONTROLLER_RIGHT))
				{ // 右入力
					g_aPlayer[nPlayerID].bBool[PLAYER_BOOL_GUARD] = true;
				}
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 移動制限取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int GetMoveRimit(void)
{
	return g_nMoveRimit;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// プレイヤーのステータス情報読み込み
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void LoadPlayerStatus(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1行の一時的読み込み
	char cData[MAX_LOAD_LINE];			// 一時的読み込み

	int nData = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1Pの場合
			pFile = fopen(LOAD_TEXT_1P, "r"); // ファイルを開く
		}
		else
		{ // 2Pの場合
			pFile = fopen(LOAD_TEXT_2P, "r"); // ファイルを開く
		}

		if (pFile != NULL) // pFileがNULL(空白）ではないときを真
		{ // ファイルが開けた際の処理
			while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
			{
				sscanf(cLine, "%s", cData);
				if (strcmp(cData, "キャラ") == 0)
				{ // キャラの場合
					sscanf(cLine, "%s %d", cData, &nData);
					// タイプを設定する
					g_aPlayer[nCntPlayer].type = (PLAYER_TYPE)nData;
				}
				else if (strcmp(cData, "攻撃力") == 0)
				{ // 攻撃力の場合
					sscanf(cLine, "%s %d", cData, &nData);
					// 攻撃ランクを設定する
					g_aPlayer[nCntPlayer].atkRank = (PLAYER_ATTACK_RANK)nData;
				}
				else if (strcmp(cData, "防御力") == 0)
				{ // 防御力の場合
					sscanf(cLine, "%s %d", cData, &nData);
					// 防御ランクを設定する
					g_aPlayer[nCntPlayer].defRank = (PLAYER_DEFENSE_RANK)nData;
				}
				else if (strcmp(cData, "回復力") == 0)
				{ // 回復力の場合
					sscanf(cLine, "%s %d", cData, &nData);
					// ライフの回復量を設定
					g_aPlayer[nCntPlayer].nRecovery = g_nRecoveryRank[nData];
				}
			}

			// プレイヤーを再設定する
			DeletShadow(g_aPlayer[nCntPlayer].nIdyShadow);
			g_aPlayer[nCntPlayer].bUse = false;
			SetPlayer(g_aPlayer[nCntPlayer].pos, g_aPlayer[nCntPlayer].rot, g_aPlayer[nCntPlayer].type);
			fclose(pFile); // ファイルを閉じる
		}
	}
}

#if DEBUG_SPHERE
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// デバッグ用防御判定スフィアの更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void PlayerDebugDeffSphereUpdate(int nPlayerID)
{
	// デバッグ用のスフィアを非表示にする(防御
	for (int nCntType = 0; nCntType < PLAYER_TYPE_MAX; nCntType++)
	{
		for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_TYPE_MAX; nCntMotion++)
		{
			for (int nCntCollision = 0; nCntCollision < MAX_PLAYER_DEFENSE_COLLISION; nCntCollision++)
			{
				if (g_aPlayer[nPlayerID].type == nCntType)
				{
					SetDispSphere(g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nPlayerID], true);
				}
				else
				{
					SetDispSphere(g_aPlayerType[nCntType].collisionD[nCntCollision].nSpherID[nPlayerID], false);
				}
			}
		}
	}

	// デバッグスフィア移動処理
	for (int nCntCollisionD = 0; nCntCollisionD < MAX_PLAYER_DEFENSE_COLLISION; nCntCollisionD++)
	{

		if (g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].bUse == true)
		{
			D3DXMATRIX mtxWorldD, mtxRotD, mtxTransD;			// 計算用マトリックス

																// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorldD);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotD, g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.y,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.x,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].rot.z);

			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxRotD);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTransD, g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.x,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.y,
				g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].pos.z);

			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD, &mtxTransD);

			// 親のワールドマトリックスを反映
			D3DXMatrixMultiply(&mtxWorldD, &mtxWorldD,
				&g_aPlayer[nPlayerID].aModel[g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].nPartsId].mtxWorld);

			// デバッグ用のスフィア移動処理
			SetPositionSphere(g_aPlayerType[g_aPlayer[nPlayerID].type].collisionD[nCntCollisionD].nSpherID[nPlayerID],
				D3DXVECTOR3(mtxWorldD._41, mtxWorldD._42, mtxWorldD._43));
		}
	}
}
#endif // DEBUG_SPHERE

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 操作状況取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
bool GetController(PLAYER_CONTROL control, PLAYER_CONTROLLER Controller)
{
	bool bButton = false;
	switch (control)
	{
		// 1Pの操作
	case PLAYER_CONTROL_1P:
		switch (Controller)
		{
		case PLAYER_CONTROLLER_LEFT:	// 左入力
			if (GetKeyboardPress(DIK_A) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P,POV_LEFT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT:	// 右入力
			if (GetKeyboardPress(DIK_D) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_RIGHT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_UP:	// 上入力
			if (GetKeyboardTrigger(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_LEFT_UP:	// 左上入力
			if ((GetKeyboardTrigger(DIK_W) == true && GetKeyboardPress(DIK_A) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_LEFT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT_UP: // 右上入力
			if ((GetKeyboardTrigger(DIK_W) == true && GetKeyboardPress(DIK_D) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_RIGHT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_DOWN:	// 下入力
			if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_LEFT_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_SMALL:	// 弱攻撃入力
			if (GetKeyboardTrigger(DIK_G) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_BIG:	// 強攻撃入力
			if (GetKeyboardTrigger(DIK_H) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_B) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_SKILL:	// スキル入力
			if (GetKeyboardTrigger(DIK_Y) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_Y) == true)
			{
				bButton = true;
			}
			break;
		}
		break;
		// 2Pの操作
	case PLAYER_CONTROL_2P:
		switch (Controller)
		{
		case PLAYER_CONTROLLER_LEFT:	// 左入力
			if (GetKeyboardPress(DIK_LEFT) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_LEFT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT:	// 右入力
			if (GetKeyboardPress(DIK_RIGHT) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_RIGHT) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_UP:	// 上入力
			if (GetKeyboardTrigger(DIK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_LEFT_UP:	// 左上入力
			if ((GetKeyboardTrigger(DIK_UP) == true && GetKeyboardPress(DIK_LEFT) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_LEFT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_RIGHT_UP: // 右上入力
			if ((GetKeyboardTrigger(DIK_UP) == true && GetKeyboardPress(DIK_RIGHT) == true) || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_RIGHT_UP) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_UP) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_DOWN:	// 下入力
			if (GetKeyboardPress(DIK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_LEFT_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_RIGHT_DOWN) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_SMALL:	// 弱攻撃入力
			if (GetKeyboardTrigger(DIK_DECIMAL) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_ATTACK_BIG:	// 強攻撃入力
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_NUMPADENTER) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_B) == true)
			{
				bButton = true;
			}
			break;
		case PLAYER_CONTROLLER_SKILL:	// スキル入力
			if (GetKeyboardTrigger(DIK_ADD) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_Y) == true)
			{
				bButton = true;
			}
			break;
		}
		break;
	}
	return bButton;
}

//=============================================================================
// プレイヤー体力とスキルポイント保存処理
//=============================================================================
void PlayerSaveHpSkill(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char *cTextName;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1Pの場合
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "w"); // ファイルを開く
			cTextName = PLAYER_1P_HP_SKILL_TXT_NAME;
		}
		else
		{ // 2Pの場合
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "w"); // ファイルを開く
			cTextName = PLAYER_2P_HP_SKILL_TXT_NAME;
		}

		if (pFile != NULL) // pFileがNULL(空白）ではないときを真
		{ // ファイルが開けた際の処理
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# 『HP・SkillPoint情報』スクリプトファイル [%s]\n", cTextName);
			fprintf(pFile, "# Author : 圷 和也\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT			# この行は絶対消さないこと！\n\n");

			fprintf(pFile, "\n");
			fprintf(pFile, "#------------------------------------------------------------------------------\n");
			fprintf(pFile, "# プレイヤー%d 情報\n", nCntPlayer + 1);
			fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

			fprintf(pFile, "HP = %d \n", g_aPlayer[nCntPlayer].nLife);
			fprintf(pFile, "SKILL = %d \n", g_aPlayer[nCntPlayer].nSkillPoint);

			fclose(pFile); // ファイルを閉じる
		}
	}
}

//=============================================================================
// プレイヤー体力とスキルポイント保存処理(初期設定
//=============================================================================
void PlayerSaveHpSkillInit(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char *cTextName;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1Pの場合
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "w"); // ファイルを開く
			cTextName = PLAYER_1P_HP_SKILL_TXT_NAME;
		}
		else
		{ // 2Pの場合
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "w"); // ファイルを開く
			cTextName = PLAYER_2P_HP_SKILL_TXT_NAME;
		}

		if (pFile != NULL) // pFileがNULL(空白）ではないときを真
		{ // ファイルが開けた際の処理
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "# 『HP・SkillPoint情報』スクリプトファイル [%s]\n", cTextName);
			fprintf(pFile, "# Author : 圷 和也\n");
			fprintf(pFile, "#\n");
			fprintf(pFile, "#==============================================================================\n");
			fprintf(pFile, "SCRIPT			# この行は絶対消さないこと！\n\n");

			fprintf(pFile, "\n");
			fprintf(pFile, "#------------------------------------------------------------------------------\n");
			fprintf(pFile, "# プレイヤー%d 情報\n", nCntPlayer + 1);
			fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

			fprintf(pFile, "HP = %d \n", PLAYER_LIFE);
			fprintf(pFile, "SKILL = %d \n", PLAYER_SKILL);

			fclose(pFile); // ファイルを閉じる
		}
	}
}
//=============================================================================
// プレイヤー体力とスキルポイント読み込み処理
//=============================================================================
void PlayerLoadHpSkill(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char cLine[MAX_LOAD_LINE];			// 1行の一時的読み込み
	char cData[MAX_LOAD_LINE];			// 一時的読み込み

	int nData = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntType = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{ // 1Pの場合
			pFile = fopen(PLAYER_1P_HP_SKILL_TXT_NAME, "r"); // ファイルを開く
		}
		else
		{ // 2Pの場合
			pFile = fopen(PLAYER_2P_HP_SKILL_TXT_NAME, "r"); // ファイルを開く
		}

		if (pFile != NULL) // pFileがNULL(空白）ではないときを真
		{ // ファイルが開けた際の処理
			while (fgets(cLine, MAX_LOAD_LINE, pFile) != NULL)
			{
				sscanf(cLine, "%s", cData);
				if (strcmp(cData, "HP") == 0)
				{ // HPの場合
					sscanf(cLine, "%s %s %d", cData, cData, &nData);
					// HPを設定する
					g_aPlayer[nCntPlayer].nLife = nData;
					// HPゲージ更新
					SetHpGageLife(g_aPlayer[nCntPlayer].nLife, (PLAYER_CONTROL)nCntPlayer);
				}
				else if (strcmp(cData, "SKILL") == 0)
				{ // SKILLの場合
					sscanf(cLine, "%s %s %d", cData, cData, &nData);
					// SKILL_POINTを設定する
					g_aPlayer[nCntPlayer].nSkillPoint = nData;
					// SKILLゲージ更新
					SetSpGageSkillPoint(g_aPlayer[nCntPlayer].nSkillPoint, (PLAYER_CONTROL)nCntPlayer);
				}
			}
			fclose(pFile); // ファイルを閉じる
		}
	}
}

//=============================================================================
// 戦闘結果表示
//=============================================================================
void PlayerBattleResultSave(int nPlayerID)
{
	// ローカル変数宣言
	FILE *pFile = NULL;

	pFile = fopen(SAVE_RESULT_TEXT, "w"); // ファイルを開く

	if (pFile != NULL) // pFileがNULL(空白）ではないときを真
	{ // ファイルが開けた際の処理
		fprintf(pFile, "%d \n", (nPlayerID + 1));
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# 勝利プレイヤー情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# 『戦闘結果』スクリプトファイル [%s]\n", SAVE_RESULT_TEXT);
		fprintf(pFile, "# Author : 圷 和也\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT			# この行は絶対消さないこと！\n\n");

		fclose(pFile); // ファイルを閉じる
	}

}