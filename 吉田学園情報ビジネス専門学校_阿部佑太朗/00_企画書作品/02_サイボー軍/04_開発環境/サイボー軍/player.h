//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_PLAYER "data/TEXTURE/PLAYER/PPPPPP.png"
#define PLAYER_POLIGON_X (20)
#define PLAYER_POLIGON_Y (40)

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		//PLAYERSTATE_APPEAR=0,		//出現状態（無敵）
		PLAYERSTATE_NOMAL = 0,		//通常ダメージ
		PLAYERSTATE_DAMAGE,			//ダメージ状態
		PLAYERSTATE_DEATH,			//死亡状態
		PLAYERSTATE_END,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer();											//	コンストラクタ
	~CPlayer();											//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);						//	プレイヤーの初期化処理
	void Uninit(void);									//	プレイヤーの終了処理
	void Update(void);									//	プレイヤーの更新処理
	void Draw(void);									//	プレイヤーの描画処理
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Laod(void);							//	テクスチャを読み込む
	static void UnLoad(void);							//	テクスチャの開放
	static void HitDamage(int nDamage);					//	プレイヤーのダメージ設定
	static void UpLife(int nLife);						//	プレイヤーの体力回復
	static void BulletChange(int nBulletType);			//	プレイヤーの弾の変化
	static bool GetLand(void);							//	ブロックに乗ったかの情報取得

	static	int GetLife(void);							//	プレイヤーのライフの取得
	static D3DXVECTOR3 GetPosition(void);				//	プレイヤーのポジションの取得
	static D3DXVECTOR3 GetMove(void);					//	プレイヤーの動きの取得
	static int GetTexNumber(void);						//	プレイヤーのテクスチャの分割の番号取得
	static void LoadPlayer(void);						//	プレイヤーのテキスト読み込み

private:
	static int m_nCounterState;							//状態管理のカウンター
	static PLAYERSTATE m_PlayerState;					//	プレイヤーの状態
	static LPDIRECT3DTEXTURE9 m_Texture;				//	共通テクスチャのポインタ
	static int m_nBulletType;							//	弾の種類変化
	static bool bDisp;									//	プレイヤーが生きているかどうか
	static int m_nLife;									//	プレイヤーの体力の変数
	static int m_nTexChange;							//	テクスチャの変化用
	int m_nCounterAnim;									//	アニメーション用カウンター
	int m_nPatternAnim;									//	アニメーションパターン
	int m_nBulletRot;									//	左右に合わせて弾の向き変える
	static D3DXVECTOR3 m_move;							//	プレイヤーの動き
	static D3DXVECTOR3 m_posold;						//	過去の位置
	static float m_fWindth;								//	幅
	static float m_fHeight;								//	高さ
	static D3DXVECTOR3 m_GetPos;						//	プレイヤーの位置の取得
	static D3DXVECTOR3 m_GetMove;						//	プレイヤーの動きの取得
	static bool m_bLandDropBlock;						//	落ちるブロックに乗っているか判定

	 bool m_bLandBlock;									//	ブロックに乗っているか判定
	int m_nMotionState;									//	現在のモーション状態
	int m_nMotionStateID;								//	現在のモーションの保存用変数
	bool m_bBullet;										//	弾を飛ばしているかどうか
};
#endif
