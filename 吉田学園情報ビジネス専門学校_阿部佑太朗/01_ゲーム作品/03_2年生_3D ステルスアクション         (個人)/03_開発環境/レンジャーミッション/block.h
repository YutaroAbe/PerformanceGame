//=============================================================================
//
// ブロック処理 [block.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scenex.h"		// シーンx

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBlock : public CSceneX
{// ブロック親：CSceneX
public:
	typedef enum
	{//	ブロックの種類
		MODELTYPE_GIRISUTU = 0,		//	ギリースーツ
		MODELTYPE_CYLINDER,			//	コライダー
		MODELTYPE_KONTENA000,		//	コンテナ000
		MODELTYPE_SHIPOBJ,			//	船
		MODELTYPE_GRASS,			//	草
		MODELTYPE_KONTENA001,		//	コンテナ001
		MODELTYPE_KONTENA002,		//	コンテナ002
		MODELTYPE_SHIPON,			//	船上
		MODELTYPE_SHIPUNDER,		//	船
		MODELTYPE_STAGEEND,			//	ステージのゴール
		MODELTYPE_DOOR,				//	ドア
		MODELTYPE_BILLING000,		//	ビル000
		MODELTYPE_BRONZESTATUE,		//	銅像
		MODELTYPE_TREEWOOD,			//	木の下部分
		MODELTYPE_TREEGRASS,		//	木の上部分
		MODELTYPE_KONTENA003,		//	コンテナ003
		MODELTYPE_KONTENA004,		//	コンテナ004
		MODELTYPE_KONTENA005,		//	コンテナ005
		MODELTYPE_GRASSBIG,			//	大きい草
		MODELTYPE_BILLING001,		//	ビル001
		MODELTYPE_BILLING002,		//	ビル002
		MODELTYPE_BILLING003,		//	ビル003
		MODELTYPE_BILLING004,		//	ビル004
		MODELTYPE_BILLING005,		//	ビル005
		MODELTYPE_MAX
	}MODELTYPE;

	typedef enum
	{//	ブロックの判定の種類
		COLTYPE_NONE = 0,	//	当たり判定なし
		COLTYPE_BOX,		//	ボックスコリジョン
		COLTYPE_STEALTH,	//	ステルスコリジョン
		COLTYPE_STAGENXST,	//	次のステージに行く為のコリジョン
		COLTYPE_MAX
	}COLTYPE;
	const static int m_MaxModel = MODELTYPE_MAX;			// モデル数
	CBlock();												// コンストラクタ
	~CBlock();												// デストラクタ
	static HRESULT Load(void);								// モデルとテクスチャ読み込み
	static void Unload(void);								// モデルとテクスチャ開放
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype);		// 生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, MODELTYPE modelType, COLTYPE coltype);				// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);			// 当たり判定
	bool StealthCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);	// 当たり判定
	bool StageNxstCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);// 次のステージいく判定
	bool *GetHit(void) { return m_bHit; }					// 当たった場所の取得
	bool GetStealthIN(void) { return m_bStealthIN; }		//  Stealthモードの取得
	COLTYPE GetCOlType(void) { return m_colType; }			//	コリジョンのタイプ

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture[m_MaxModel];	// テクスチャ情報へのポインタ
	static LPD3DXMESH			m_pMesh[m_MaxModel];		// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[m_MaxModel];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat[m_MaxModel];		// マテリアル情報の数

	MODELTYPE					m_modelType;				// モデルの種類
	COLTYPE						m_colType;					// 種類
	D3DXVECTOR3					m_posOld;					// 過去の位置
	bool						m_bHit[6];					// 当たった場所
	bool						m_bStealthIN;				// ステルスオブジェクトに入った場合
protected:

};

#endif