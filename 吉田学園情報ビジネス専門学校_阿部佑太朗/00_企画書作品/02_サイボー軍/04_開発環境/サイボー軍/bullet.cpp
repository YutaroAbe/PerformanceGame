//=============================================================================
//
//	弾の処理 [bullet.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "life.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_Texture[MAX_BULLET] = {};					//	テクスチャの初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CBullet::CBullet() : CScene2D(4)
{
	m_BulletType = BULLET_NONE;											//	弾の初期化
	 m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//	動きの初期化
	 m_nLife = 0;														//	寿命の初期化
}

//==============================================================================
//	デストラクタ
//==============================================================================
CBullet::~CBullet()
{
}

//==============================================================================
//	初期化処理
//==================================    ============================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_BULLET);

	m_move = move;

	if (m_nType == 0)
	{
		m_nLife = 35;
	}
	else if (m_nType == 1)
	{
		m_nLife = 35;
	}
	else if (m_nType == 2)
	{
		m_nLife = 35;
	}
	else if (m_nType == 3)
	{
		m_nLife = 35;
	}
	else if (m_nType == 4)
	{//	エネミーの弾
		m_nLife = 160;
	}

	SetPosition(pos, BULLET_POLIGON_X, BULLET_POLIGON_Y);

	m_BulletType = BulletType;

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	更新処理
//==============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();											//	弾の位置の取得
	D3DXVECTOR3 move = GetMoveing();
	D3DXVECTOR3 playermove = CPlayer::GetMove();								//	プレイヤーの動きの取得
	move += m_move;

	if (playermove.x >= 0.0f)
	{
		move.x -= playermove.x;
	}
	else if (playermove.x <= 0.0f)
	{
		move.x += -playermove.x;
	}
	pos.x += move.x;															//	弾の動きの更新X座標
	pos.y += move.y;															//	弾の動きの更新Y座標

	SetPosition(pos, BULLET_POLIGON_X, BULLET_POLIGON_Y);						//	弾の位置と大きさ設定



	m_nLife--;																	//	弾の寿命

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			//	エネミーの判定--------------------------------------------------------------------------------------
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();

				if (objtype == CScene::OBJECT_ENEMY &&m_BulletType == BULLET_ENEMY)
				{
					CEffect::Create(pos, 80, BULLET_POLIGON_X, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
				}
				else if (objtype == CScene::OBJECT_PLAYER &&m_BulletType == BULLET_PLAYER)
				{
					CEffect::Create(pos, 80, BULLET_POLIGON_X, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}

				if (objtype == CScene::OBJECT_ENEMY &&	m_BulletType == BULLET_PLAYER)
				{//	オブジェクトが敵だったら
					D3DXVECTOR3 enemy_pos = pScene->GetPosition();
					CEnemy * pEnemy = (CEnemy*)pScene;
					if (enemy_pos.x - 25 < pos.x &&	enemy_pos.x + 25 > pos.x &&
						enemy_pos.y - 25 * 2 < pos.y && enemy_pos.y > pos.y)
					{//敵の範囲設定
						m_nLife = 0;
						pEnemy->Hit(1);
					}
				}
				else if (objtype == CScene::OBJECT_PLAYER &&m_BulletType == BULLET_ENEMY)
				{//	オブジェクトがプレイヤーだったら
					D3DXVECTOR3 player_pos = pScene->GetPosition();
					if (player_pos.x - 25 < pos.x &&	player_pos.x + 25 > pos.x &&
						player_pos.y - 25 * 2 < pos.y && player_pos.y > pos.y)
					{//プレイヤーの範囲設定
						m_nLife = 0;
						pScene->HitDamage(1);
					}
				}
				else if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();		//	ブロックの位置
					float block_fWindth = pScene->GetfWindth();			//	ブロックの幅
					float block_fHeight = pScene->GetfHeight();			//	ブロックの高さ

					if (pos.x + (BULLET_POLIGON_X / 2) >= block_pos.x  &&
						pos.x - (BULLET_POLIGON_X / 2) <= block_pos.x + block_fWindth &&
						pos.y >= block_pos.y &&
						pos.y - BULLET_POLIGON_Y <= block_pos.y + block_fHeight)
					{//	 YXが範囲内
						m_nLife = 0;
						CExplosion::Create(pos + D3DXVECTOR3(2.0f, 2.0f, 0.0f));		//	爆発の生成
					}
				}
			}
		}
	}
	if (m_nLife <= 0)
	{
		Uninit();																//	終了処理
	}
}
//==============================================================================
//	描画処理
//==============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int m_nType, BULLET_TYPE BulletType)
{
	CBullet *pBullet = {};

	if (pBullet == NULL)
	{
		pBullet = new CBullet;									//	弾のメモリの確保

		if (pBullet != NULL)
		{
			// ポリゴンの初期化処理
			pBullet->Init(pos, move,  m_nType, BulletType);
			//	弾のテクスチャの割り当て
			pBullet->BindTexture(m_Texture[m_nType]);
		}
		else
		{
		}
	}
	return pBullet;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CBullet::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_3, &m_Texture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_4, &m_Texture[4]);
	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CBullet::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{
		//テクスチャの破棄
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}