///=============================================================================
//
// プレイヤー処理 [player.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		//	メイン
#include "scene.h"		//	シーン
#include "shadow.h"		//	影

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CModel;			//	モデル
class CMotion;			//	モーション
class COrbit;			//　軌跡
class CShadow;			//	影
class CBullet3D;		//	弾
class CScene;			//	シーン
class CEnemy;			//	敵
class CCamera;			//	カメラ
class CBlock;			//	ブロック

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMPARTS	(30)
#define MAX_NUMMOTION	(30)
#define MAX_STEALTHCUT	(500)		//	ステルスのカウンターが戻る最大値
#define MAX_DASHTHCUT	(300)		//	ダッシュのカウンターが戻る最大値


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CScene
{
public:
	typedef enum
	{//	モーションの種類
		MOSION_NEUTRAL = 0,	//	ニュートラルモーション
		MOSION_MOVE,		//	移動モーション
		MOSION_JUMP,		//	ジャンプモーション
		MOSION_LAND,		//	着地モーション
		MOSION_BLTPRPE,		//	弾を投げる準備モーション　(　BLT:バレット PRPE:プリペア)
		MOSION_BLTTHROW,	//	弾投げるモーション		　(　BLT:バレット THROW:準備   )
		MOSION_SQUAT,		//	しゃがむモーション
		MOSION_SQUATMOVE,	//	しゃがむ歩きモーション
		MOSION_ATTACK_000,	//	攻撃モーション000　キック
		MOSION_ATTACK_001,	//	攻撃モーション001　パンチ
		MOSION_DISP,		//	死んだ状態
		MOSION_DAMAGE,		//	ダメージモーション
		MOSION_MAX			//	最大数
	}MOSION_STATE;

	typedef enum
	{//	ステータス
		STATE_NONE = 0,						//	通常
		STATE_DAMAGE,						//	ダメージ
		STATE_INVINCIBLE,					//	無敵
		STATE_DEATH,						//	死亡
		STATE_MAX							//	ステータスの最大数
	}STATE;
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

	CPlayer();														//	コンストラクタ
	~CPlayer();														//	デストラクタ
	HRESULT Init(void);												//	初期化
	void Uninit(void);												//	終了処理
	void Update(void);												//	更新処理
	void Draw(void);												//	描画処理
	void Setpos(D3DXVECTOR3 pos) { m_pos = pos; }					//	位置の設定
							//	位置　向き　体力　弾の制限 ステルス出来る寿命 ダッシュ出来る寿命
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife,int nBltCut,int nStealthLife, int nDashLife);
	void HitLife(int nDamage,D3DXVECTOR3 move);										//	ダメージ計算処理
	void AddBulletGan(int nAdd);									//	弾の数

	static HRESULT Load(void);										//	読み込みの処理
	static void UnLoad(void);										//	解放の処理

	 D3DXVECTOR3 Getpos(void) { return m_pos; }						//	位置の取得
	 D3DXVECTOR3 Getmove(void) { return m_move; }					//	動きの取得
	 D3DXVECTOR3 GetposOld(void) { return m_posOld; }				//	過去の位置の取得
	 D3DXVECTOR3 Getrot(void) { return m_rot; }						//	回転の取得
	 int GetLife(void) { return m_nLife; }							//	体力の取得
	 int GetBltNum(void) { return m_nBltCut; }						//	弾の弾数
	 bool GetSquat(void) { return m_bSquat; }						//	しゃがんでいる状態の取得
	 bool GetLastHit(void) { return m_bAtkLastHit;}					//	最後の攻撃の取得
	 bool GetStealthMode(void) { return m_bStealthMode; }			//	ステルスモードの取得
	 int GetStealthCut(void) { return m_nStealthCut; }				//	ステルス復帰するカウンターの取得
	 int GetStealthLife(void) { return m_nStealthLife; }			//	ステルスの寿命の取得
	 int GetDashCut(void) { return m_nDashCut; }					//	ダッシュ復帰するカウンターの取得
	 int GetDashLife(void) { return m_nDashLife; }					//	ダッシュの寿命の取得
	 bool GetDisp(void) { return m_bDisp; }							//	亡くなったかどうか
	 STATE GetState(void) { return m_state; }						//	状態の取得
	 bool GetDash(void) { return m_bDash; }							//	亡くなったかどうか

	 D3DXVECTOR3 Getsize(int nNum) { if (nNum == 0) { return m_vtxMax; } else { return m_vtxMin; } }
	void UpdateMotion(void);										//	モーションの更新
	void FileLoad(void);											//	ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);						//	1行読み込み
	char *GetLineTop(char *pStr);									//	行の先頭を取得
	int  PopString(char *pStr, char *pDest);						//	行の最後を切り捨て

	void ManagementCollision(void);									//	当たり判定の管理
	void ManagementMovement(void);									//	動きの管理
	void ManagementAddMovement(void);								//	加算する動きの管理
	void ManagementSetMosion(void);									//	モーションの設定管理
																	//	当たり判定
	bool AttackCollsion(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void BoxCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
	void CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);

private:
	//	モデルに必要な変数
	static LPD3DXMESH			m_pMesh[MAX_NUMPARTS];			//	メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[MAX_NUMPARTS];		//	マテリアル情報へのポインタ
	static LPDIRECT3DTEXTURE9	*m_pTexture[MAX_NUMPARTS];		//	テクスチャへのポインタ
	static DWORD				m_nNumMat[MAX_NUMPARTS];		//	マテリアル情報の数
	//	モーション関連変数
	KEY_INFO					*m_pKeyInfo[MAX_NUMMOTION];			//	キー情報へのポインタ
	int							m_nKey;								//	現在のキーナンバー
	int							m_nCountFlame;						//	フレーム数
	static int					m_nNumParts;						//	パーツ数
	int							m_aIndexParent[MAX_NUMPARTS];		//	親のインデックス
	KEY							m_aKayOffset[MAX_NUMPARTS];			//	オフセット情報
	MOTION_INFO					m_aMotionInfo[MAX_NUMMOTION];		//	モーション情報
	bool						m_bMotionEnd;						//	モーションの終了
	D3DXVECTOR3					m_OffSetPos[MAX_NUMPARTS];			//	オフセット位置
	D3DXVECTOR3					m_OffSetRot[MAX_NUMPARTS];			//	オフセット位置
	int							m_nMotionType;						//	モーションの種類
	int							m_nMotionTypeOld;					//	モーションの過去の種類
	int							m_nNumModel;						//	モデルの数
	char						m_aFileNameModel[MAX_NUMPARTS][256];//	読み込むモデルの名前
	//	キャラクターの情報
	D3DXVECTOR3					m_pos;								//	位置
	D3DXVECTOR3					m_posOld;							//	前回の位置
	D3DXVECTOR3					m_move;								//	移動量
	D3DXVECTOR3					m_rot;								//	向き
	STATE						m_state;							//	ステータス
	D3DXMATRIX					m_mtxWorld;							//	ワールドマトリックス
	D3DXVECTOR3					m_rotDest;							//	目標向き
	D3DXVECTOR3					m_vtxMax;							//	判定最大
	D3DXVECTOR3					m_vtxMin;							//	判定最小
	FLOAT						m_fScaleX, m_fScaleY, m_fScaleZ;	//	拡大縮小用変数
	CModel						*m_apModel[MAX_NUMPARTS];			//	モデルのポインタ
	MOSION_STATE				m_MosionState;						//	モーションの状態
	int							m_nCntNumMosion;					//	テキストに書かれているモーションの数
	int							m_nCouterFreamMax[MAX_NUMMOTION];	//	モーションのフレームの合計値
	int							m_nCntMosionChange;					//	モーションの切り替えるカウンター
	int							m_nAtkFream;						//	攻撃のコリジョンがでるフレーム
	int							m_nAtkCombFream;					//	攻撃のコンボのフレーム
	bool						m_bAtkLastHit;						//	攻撃の最後の攻撃当たったか
	int							m_nLife;							//	寿命
	int							m_nLifeInit;						//	初期の寿命
	int							m_nBltCut;							//	手榴弾の弾数
	//	キャラクターの状態用
	bool						m_bBlock;							//	ブロックに当たっているかどうか
	bool						m_bJump;							//	ジャンプ状態
	bool						m_bLand;							//	着地状態
	bool						m_bMove;							//	動いている状態
	bool						m_bSquat;							//	しゃがんでいる状態
	bool						m_bAttack;							//	攻撃状態か
	bool						m_bDash;							//	ダッシュしているかどうか
	float						m_fMoveControl;						//	移動の変化
	bool						m_bDisp;							//	死んでいるかどうか
	bool						m_bDamage;							//	ダメージ状態
	int							m_nStateCounter;					//	ダメージ中のカウンター
	bool						m_bStealthMode;						//	ステルスしているかどうか
	bool						m_bLifeState[2];					//	体力の変化している状態[0]ダメージ[1]回復
	bool						*m_bStlBlockHitIn;					//	ステルスブロックの中に入ったかどうか
	int							m_nNumBlock;						//	ステルスブロックの数
	int							m_nInvincible;						//	無敵状態
	int							m_nStealthLife;						//	ステルス出来る寿命
	int							m_nStealthCut;						//	ステルス状態に戻るカウンター
	int							m_nDashLife;						//	ダッシュできる寿命
	int							m_nDashCut;							//	ダッシュ状態に戻るカウンター

	//	プレイヤーに使用するクラス
	CShadow						*m_pShadow;							//	影
	COrbit						*m_pOrbit;							//	軌跡
	CBullet3D					*m_pBullet3D;						//	弾
	CCamera						*m_pCamera;							//	カメラ
	CBlock						*m_pBlock;							//	ブロック
public:
};

#endif