//=============================================================================
//
// メイン処理 [main.cpp]
// Author :　YUTARO ABE
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include <string>
#include <time.h>
#include "enemy.h"

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene2D::CScene2D() : CScene(3)
{
	m_pTexture = NULL;										//	テクスチャへのポインタ
	m_pVtxBuff = NULL;										//	頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//	ポリゴンの位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	ポリゴンオ動き
	m_fWindth = NULL;										//	幅の初期化
	m_fHeight = NULL;										//	高さの初期化
	m_nLife = NULL;											//	ライフの初期化
	m_nType = NULL;
}

//=============================================================================
//	優先順位のコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriarity) : CScene(nPriarity)
{
	m_pTexture = NULL;										//	テクスチャへのポインタ
	m_pVtxBuff = NULL;										//	頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//	ポリゴンの位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	ポリゴンオ動き
	m_fWindth = NULL;										//	幅の初期化
	m_fHeight = NULL;										//	高さの初期化
	m_nLife = NULL;
	m_nType = NULL;
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + m_pos;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分自身の破棄
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, MAX_POLIGON);

}

//=============================================================================
//	プレイヤーの位置の設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float PolygonSizeX, float PolygonSizeY)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	m_pos = pos;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-PolygonSizeX, -PolygonSizeY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(PolygonSizeX, -PolygonSizeY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-PolygonSizeX, PolygonSizeY, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(PolygonSizeX, PolygonSizeY, 0.0f) + m_pos;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	アニメーションの設定
//=============================================================================
void CScene2D::SetAnimation(int PatternAnim, float Split, int SplitAnim)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f/ Split) * (PatternAnim % SplitAnim) + 0.0f, 0.0f);				 //右上
	pVtx[1].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim) + (1.0f / Split), 0.0f);				 //右上
	pVtx[2].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim + 0.0f), 1.0f);				 //右上
	pVtx[3].tex = D3DXVECTOR2((1.0f / Split) * (PatternAnim % SplitAnim) + (1.0f / Split), 1.0f);				 //右上

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	アニメーションのテクスチャの初期化
//=============================================================================
void CScene2D::InitAnimationTex(float Split)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
	pVtx[1].tex = D3DXVECTOR2((1.0f / Split), 0.0f);			//右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//左上
	pVtx[3].tex = D3DXVECTOR2((1.0f / Split), 1.0f);			//右下

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	背景動かす
//=============================================================================
void CScene2D::BGMove(D3DXVECTOR3 move)
{
	m_move = move;
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_move.x, 0.0f);						//左上
	pVtx[1].tex = D3DXVECTOR2(m_move.x - 1.0f, 0.0f);				//右上
	pVtx[2].tex = D3DXVECTOR2(m_move.x, 1.0f);						//左上
	pVtx[3].tex = D3DXVECTOR2(m_move.x - 1.0f, 1.0f);				//右下

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
//	カラー変更
//=============================================================================
void  CScene2D::ColorChange(D3DXCOLOR m_Col)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	頂点情報の設定
//=============================================================================
void CScene2D::SetVtxPosition(D3DXVECTOR3 *pPos, D3DXVECTOR3 pos)
{
	m_pos = pos;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].pos = pPos[0] + m_pos;
	pVtx[1].pos = pPos[1] + m_pos;
	pVtx[2].pos = pPos[2] + m_pos;
	pVtx[3].pos = pPos[3] + m_pos;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
//幅と高さの設定
//=============================================================================
void CScene2D::SetWindthHeigth(float fWindth, float fHeight)
{
	m_fWindth = fWindth;
	m_fHeight = fHeight;
}

//=============================================================================
//	カラーの設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR * color)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].col = color[0];
	pVtx[1].col = color[1];
	pVtx[2].col = color[2];
	pVtx[3].col = color[3];

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
//	Textureの設定
//=============================================================================
void CScene2D::SetTexture(D3DXVECTOR2 *pTex)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = pTex[0];
	pVtx[1].tex = pTex[1];
	pVtx[2].tex = pTex[2];
	pVtx[3].tex = pTex[3];

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//
//=============================================================================
void CScene2D::SetType(int nType)
{
	m_nType = nType;
}
//=============================================================================
//	ライフポイントの設定
//=============================================================================
void CScene2D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
//	バッファの取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetBuff(void)
{
	return m_pVtxBuff;
}

//=============================================================================
//	プレイヤーの位置取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
//プレイヤーの動き取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetMoveing(void)
{
	return m_move;
}
//=============================================================================
//	2Dポリゴンの幅の取得
//=============================================================================
float CScene2D::GetfWindth(void)
{
	return m_fWindth;
}
//=============================================================================
//	2Dポリゴンの高さの取得
//=============================================================================
float CScene2D::GetfHeight(void)
{
	return m_fHeight;
}
//==============================================================================
//プレイヤーのダメージ設定
//==============================================================================
void CScene2D::HitDamage(int nDamage)
{
	CPlayer::HitDamage(nDamage);

}

//=============================================================================
//	共通テクスチャを割り当てる処理
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9	pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//　HPの取得
//=============================================================================
int CScene2D::GetLife(void)
{
	return m_nLife;
}
//=============================================================================
//　種類の取得
//=============================================================================
int  CScene2D::GetType(void)
{
	return m_nType;
}