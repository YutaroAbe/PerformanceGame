//=============================================================================
//
//	アイテムの処理 [item.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "item.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CItem::m_Texture[MAX_TEX_ITEM] = {};					//	テクスチャの初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CItem::CItem() : CScene2D(3)
{
	 m_nType = NULL;																					//	種類
}

//==============================================================================
//	デストラクタ
//==============================================================================
CItem::~CItem()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, int nType)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_BULLET);

	m_nType = nType;

	SetPosition(pos, ITEM_POLIGON_X, ITEM_POLIGON_Y);

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
//	更新処理
//==============================================================================
void CItem::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();															//	弾の位置
	D3DXVECTOR3 move = GetMoveing();															//	弾の位置

	D3DXVECTOR3 playermove = CPlayer::GetMove();

	if (playermove.x >= 0.1f)
	{
		move.x -= playermove.x;
	}
	else if (playermove.x <= -0.1f)
	{
		move.x += -playermove.x;
	}

	pos.x += move.x;
	pos.y += move.y;
	SetPosition(pos, ITEM_POLIGON_X, ITEM_POLIGON_Y);							//	弾の位置と大きさ設定

	for (int nCnt= 0; nCnt < MAX_DROW; nCnt++)
	{//
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			//プレイヤーの判定--------------------------------------------------------------------------------------
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_PLAYER)
				{//	オブジェクトがプレイヤーだったら
					D3DXVECTOR3 player_pos = pScene->GetPosition();

					if (player_pos.x - 40 < pos.x &&	player_pos.x + 40 > pos.x &&
						player_pos.y - 50 < pos.y &&	player_pos.y > pos.y)
					{//プレイヤーの範囲設定
						int player_life = pScene->GetLife();
						Uninit();
						if (m_nType == 0)
						{
							CPlayer::UpLife(15);

						}
						else if (m_nType == 1)
						{
							CPlayer::BulletChange(2);
						}
					}
				}
			}
		}
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, int m_nType)
{
	CItem *pItem = {};

	if (pItem == NULL)
	{
		pItem = new CItem;									//	弾のメモリの確保

		if (pItem != NULL)
		{
			// ポリゴンの初期化処理
			pItem->Init(pos, m_nType);
			//	弾のテクスチャの割り当て
			pItem->BindTexture(m_Texture[m_nType]);
		}
		else
		{
		}
	}
	return pItem;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CItem::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_HP, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_001, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_002, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_003, &m_Texture[3]);

	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CItem::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEX_ITEM; nCount++)
	{
		//テクスチャの破棄
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}