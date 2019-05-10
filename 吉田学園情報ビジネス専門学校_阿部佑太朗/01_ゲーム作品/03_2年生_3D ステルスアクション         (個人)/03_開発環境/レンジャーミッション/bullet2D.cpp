//=============================================================================
//
// 弾2D処理 [bullet2D.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"		// シーン3D
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力
#include "camera.h"			// カメラ
#include "item.h"			// アイテム
#include "effect.h"			// エフェクト
#include "bullet2D.h"		// 弾2D
#include "floor.h"			// 床
#include "scene.h"			// シーン

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet2D::m_pTexture[BULT2D_TYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet2D::CBullet2D() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_BULLET2D)
{
	m_nLife = 0;					//	寿命の初期化
	m_BulletState = BULLET_NONE;	//	弾のステータスの初期化
	m_pShadow = NULL;
	m_nDispCounter = 0;				//	消えるまでのカウント
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	過去の位置の保存
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet2D::~CBullet2D()
{

}

//=============================================================================
//	アイテムの生成
//=============================================================================
CBullet2D *CBullet2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nLife, TYPEBULT BultType)
{
	CBullet2D *pBullet2D = {};

	if (pBullet2D == NULL)
	{//	アイテムの生成
		pBullet2D = new CBullet2D;
		if (pBullet2D != NULL)
		{//アイテムの初期化
			pBullet2D->Init(pos, move, size, col, TexUV, nLife,BultType);
		}
	}
	return pBullet2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nLife, TYPEBULT BultType)
{
	//	シーン3Dの初期化
	CScene3D::SetInitAll(pos, D3DXVECTOR3(0.0f,0.0f,0.0f), size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	//	テクスチャの割り当て
	CScene3D::BindTexture(m_pTexture[(int)BultType]);
	m_nLife = nLife;		//	寿命を代入する
	m_move = move;			//	動きの代入
	//	影の生成
	if (m_pShadow == NULL)
	{//	影が使われていなかったら
		m_pShadow = CShadow::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(size.x, 0.0f, size.y), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet2D::Uninit(void)
{

	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet2D::Update(void)
{

	D3DXVECTOR3 pos = CScene3D::Getpos();					//	大きさの取得
	D3DXVECTOR3 size = CScene3D::Getsize();					//	大きさの取得
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// 現在　
	CScene *pSceneNext = NULL;								// 次
	m_posOld = pos;											//位置の保存
	switch (m_BulletState)
	{
		//--------------------------------------------------
		//	通常
		//--------------------------------------------------
	case BULLET_NONE:
		m_nLife--;			//	寿命の減少
		pos += m_move;		//	動きの加算
		if (m_pShadow != NULL)
		{//	影が使用されたいたっばい
		 //	影の位置の設定
			CManager::m_CDebugProcRight->Print("\n弾位置  ( %.1f : %.1f  : %.1f)", pos.x, pos.y, pos.z);
			m_pShadow->Setpos(D3DXVECTOR3(pos.x, 10.0f, pos.z));
		}
		CScene3D::Setpos(pos);					//	位置の設定
		CScene3D::Update();
		while (pScene != NULL)
		{// NULL以外の場合
		 // 次オブジェクト情報を保存
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
			{//	床だった場合
				CFloor *pFloor = (CFloor*)pScene;						//	床にキャスト
				if (pFloor->Collision(&pos, &m_posOld, &m_move, size, size) == true)// 当たり判定
				{
					m_BulletState = BULLET_HIT;		//	弾が消える
				}
			}
			// 次のオブジェクトに設定
			pScene = pSceneNext;
		}

		if (m_nLife <= 0)
		{//	寿命が指定の値を超えた場合
			m_BulletState = BULLET_HIT;		//	弾が消える
		}
		break;
		//--------------------------------------------------
		//	弾が当たった
		//--------------------------------------------------
	case BULLET_HIT:
		m_nDispCounter++;
		if (m_nDispCounter < 10)
		{//	カウントが指定の値以上になった場合
			size.x += 0.95f;
			size.y += 0.95f;
		}
		else
		{
			m_BulletState = BULLET_DISP;	//	弾が消える
		}

		CScene3D::Setsize(size);					//	位置の設定
		CScene3D::Update();
		break;
		//--------------------------------------------------
		//	弾が消える
		//--------------------------------------------------
	case BULLET_DISP:
		//	影を消す
		m_pShadow->Uninit();
		//	終了処理
		Uninit();
		break;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet2D::Draw(void)
{
	CScene3D::Draw();
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBullet2D::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BULLET\\bullet2D_000.png", &m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// アンロード処理
//=============================================================================
void CBullet2D::Unload(void)
{
	for (int nCount = 0; nCount < BULT2D_TYPE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==============================================================================================================================
// アイテムのあたり判定の作成
//==============================================================================================================================
bool  CBullet2D::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;
	D3DXVECTOR3 pos = CScene3D::Getpos();				//	弾の位置
	D3DXVECTOR3 size = CScene3D::Getsize();				//	弾の大きさ
	//	プレイヤーとの角度
	float fAngle = atan2f(pPos->x - pos.x, pPos->z - pos.z);
	// 当たるものの距離
	float fPosX = (pos.x - pPos->x);
	float fPosY = (pos.y + size.y) - (pPos->y+ sizeMax.y);
	float fPosZ = (pos.z - pPos->z);

	float fRadiusA = fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ;
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x/2 + size.x)* (sizeMax.z/2 + size.x);

	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{
		//	影を消す
		m_pShadow->Uninit();
		bHit = true;
	}

	return bHit;
}