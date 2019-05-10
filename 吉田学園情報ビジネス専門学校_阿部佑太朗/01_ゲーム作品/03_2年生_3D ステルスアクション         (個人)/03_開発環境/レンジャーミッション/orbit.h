//=============================================================================
//
// オービット処理 [orbit.h]
// Author :YUTARO ABE
//
//=============================================================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "main.h"
#include "scene.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define MAX_YSIZE (1)
#define MAX_XSIZE (50)
#define MAX_SIZE ((MAX_XSIZE +1)*(MAX_YSIZE +1))
#define MAX_PORIGON_ORBIT (MAX_XSIZE * MAX_YSIZE * 2 + (MAX_YSIZE - 1) * 4)

//=============================================================================
//	メッシュオービットクラス（シーンの派生クラス）
//=============================================================================
class COrbit : public CScene
{
public:
	COrbit();															//	コンストラクタ
	COrbit(int nPriarity, CScene::OBJTYPE objtype);						//	コンストラクタ
	~COrbit();															//	デストラクタ
	HRESULT Init(void);													//	メッシュオービットの初期化処理
	void Uninit(void);													//	メッシュオービットの終了処理
	void Update(void);													//	メッシュオービットの更新処理
	void Draw(void);													//	メッシュオービットの描画処理
																		//	メッシュオービットの生成
	static COrbit *Create(D3DXVECTOR3 offsetstate, D3DXVECTOR3 offsetend);
	void SetMtxParent(D3DXMATRIX *pmtxworld);							//	マトリックスの設定
private:
	LPDIRECT3DTEXTURE9		m_pTexture;									//　テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									//　頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;										//　位置
	D3DXVECTOR3				m_rot;										//　向き
	D3DXMATRIX				m_mtxworld;									//	ワールドマトリックス
	D3DXMATRIX				*m_pMtxParrentState;						//	親のマトリックスのポインタ

	float					m_fWidth;									//	幅
	float					m_fHeight;									//	高さ
	D3DXVECTOR3				m_fOffSet[2];								//	オフセットの位置座標
	D3DXVECTOR3				m_aPosVerTex[MAX_SIZE];						//	入れ替え用変数
protected:
};
#endif