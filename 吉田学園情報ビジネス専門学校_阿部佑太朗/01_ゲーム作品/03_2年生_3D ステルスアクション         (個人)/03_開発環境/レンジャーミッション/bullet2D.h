//=============================================================================
//
// 弾2Dの処理 [bullet2D.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET2D_H_
#define _BULLET2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene3d.h"		// シーン
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULT2D_TYPE_MAX  (TYPE_BULTMAX)			//	弾の種類
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CShadow;		//	影

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBullet2D : public CScene3D
{// シーン3D（親：CScene3D）
public:
	typedef enum
	{//	弾の種類
		TYPE_BULT000 = 0,
		TYPE_BULTMAX
	}TYPEBULT;

	typedef enum
	{//弾のステータス
		BULLET_NONE = 0,			//	何もしてない
		BULLET_HIT,					//	弾が当たった
		BULLET_DISP,				//	弾が消えた
		BULLET_MAX
	}BULLETSTATE;

	CBullet2D();														// コンストラクタ
	~CBullet2D();														// デストラクタ
																		// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV,int nLife, TYPEBULT BultType);
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	D3DXVECTOR3 GetMove(void) { return m_move; }						// 動きの取得
																		// 生成
	static CBullet2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV , int nLife, TYPEBULT BultType);
	static HRESULT Load(void);											// テクスチャの読み込み
	static void Unload(void);											// 破棄
																		// 当たり判定
	bool CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[BULT2D_TYPE_MAX];		// テクスチャ情報へのポインタ
	D3DXMATRIX						m_mtxWorld;							// ワールドマトリックス
	int								m_nLife;							// 寿命
	BULLETSTATE						m_BulletState;						// 弾のステータス
	D3DXVECTOR3						m_move;								// 動き
	CShadow							*m_pShadow;							// 影
	int								m_nDispCounter;						// 消えるまでのカウント
	D3DXVECTOR3						m_posOld;							//	過去の位置
protected:

};

#endif