//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_BULLET_0 "data/TEXTURE/BULLET/bullet000.png"
#define TEXTURE_NAME_BULLET_1 "data/TEXTURE/BULLET/bullet001.png"
#define TEXTURE_NAME_BULLET_2 "data/TEXTURE/BULLET/bullet002.png"
#define TEXTURE_NAME_BULLET_3 "data/TEXTURE/BULLET/bullet003.png"
#define TEXTURE_NAME_BULLET_4 "data/TEXTURE/BULLET/bullet004.png"
#define BULLET_POLIGON_X (15)		//	弾の横の大きさ
#define BULLET_POLIGON_Y (15)		//	弾の縦の大きさ
#define MAX_BULLET (5)				//	弾の種類の最大数

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CBullet : public CScene2D
{
public:
	typedef enum
	{//	弾の種類
		BULLET_NONE = 0,	//	通常
		BULLET_PLAYER,		//	プレイヤー
		BULLET_ENEMY,		//	敵
		BULLET_MAX			//	最大数
	}BULLET_TYPE;

	CBullet();																						//	コンストラクタ
	~CBullet();																						//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType);			//	弾の初期化処理
	void Uninit(void);																				//	弾の終了処理
	void Update(void);																				//	弾の更新処理
	void Draw(void);																				//	弾の描画処理
	static HRESULT Laod(void);																		//	テクスチャを読み込む
	static void UnLoad(void);																		//	テクスチャの開放
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType);	//	弾の生成

private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_BULLET];												//	共通テクスチャのポインタ
	BULLET_TYPE m_BulletType;																		//	弾の種類
	 D3DXVECTOR3 m_move;																			//	移動量
	 int m_nType;																					//	弾の種類
	 int m_nLife;																					//	弾の寿命
	 CScene2D *m_apScene2D;																			//	シーン2Dのポインタ型変数
};
#endif
