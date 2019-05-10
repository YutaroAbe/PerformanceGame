//=============================================================================
//
//	弾3Dの処理[bullet.h]
//	Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"	//	メイン
#include "scenex.h"	//	シーンｘ

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_USE_VALSE (20)		//	弾が使用されている値

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
//	クラスの定義
//*****************************************************************************
class CBullet3D :public CSceneX
{//	弾3D親： CSceneX
public:

	typedef enum
	{//	弾の種類
		BULLET3D_TYPE_BOOM = 0,		//	ボム
		BULLET3D_MAX				//	弾の種類の最大
	}BULLET3DTYPE;

	typedef enum
	{//弾のステータス
		BULLET_NONE = 0,			//	何もしてない
		BULLET_HIT,					//	弾が当たった
		BULLET_DISP,				//	弾が消えた
		BULLET_MAX
	}BULLETSTATE;

	CBullet3D();					//	コンストラクタ
	~CBullet3D();					//	デストラクタ
	static HRESULT Load(void);		//	モデルとテクスチャ読み込み
	static void Unload(void);		//	モデルのテクスチャの開放
	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType);	//	生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType);				//	初期化処理
	void Uninit(void);				//	終了処理
	void Update(void);				//	更新処理
	void Draw(void);				//	描画処理
	int GetDispCut(void) { return m_nDispCounter; }

private:
	static LPDIRECT3DTEXTURE9 *m_pTexture[BULLET3D_MAX];		//	テクスチャの情報へのポインタ
	static LPD3DXMESH			m_pMesh[BULLET3D_MAX];			// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMat[BULLET3D_MAX];		// マテリアル情報へのポインタ
	static DWORD				m_nNumMat[BULLET3D_MAX];		// マテリアル情報の数

	BULLET3DTYPE m_Bullet3DType;								//	弾のモデルの種類
	BULLETSTATE m_BulletState;									//	弾の状態

	//	ステータス
	D3DXVECTOR3 m_move;											//	動き
	D3DXVECTOR3 m_posOld;										//	前回の位置の保存
	int			m_nDispCounter;									//	弾が消えるまでのカウント
	bool		m_bExplColl;									//	オブジェクトの衝突判定

};
#endif