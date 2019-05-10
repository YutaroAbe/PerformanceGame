//=============================================================================
//
// アイテム処理 [item.cpp]
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
#include "fade.h"
#include "sound.h"			//	サウンド

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
LPDIRECT3DTEXTURE9 CItem::m_pTexture[ITEM_MAXTYPE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem() : CScene3D(CScene::PRIORITY_4, CScene::OBJTYPE_ITEM)
{
	m_ItemType = {};
	m_pPlayer = NULL;	//	プレイヤー
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
//	アイテムの生成
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CItem *pItem = {};

	if (pItem == NULL)
	{//	アイテムの生成
		pItem = new CItem;
		if (pItem != NULL)
		{//アイテムの初期化
			pItem->Init(pos, rot, size, col, TexUV, itemType);
		}
	}
	return pItem;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int itemType)
{
	CScene3D::SetInitAll(pos, rot, size, col, TexUV, CScene3D::SCENE3DTYPE_BILLBOARD);
	CScene3D::Init();
	CScene3D::BindTexture(m_pTexture[itemType]);
	m_ItemType = (ITEMTYPE)itemType;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	CScene3D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene3D::Draw();
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CItem::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\boom.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item\\HP000.png", &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// アンロード処理
//=============================================================================
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < ITEM_MAXTYPE; nCount++)
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
bool  CItem::CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;							//	当たったかどうか
	D3DXVECTOR3 pos = CScene3D::Getpos();		//	位置の取得
	D3DXVECTOR3 size = CScene3D::Getsize();		//	大きさの取得
	CSound *pSound = CManager::GetSound();		//	音の取得

	if (pos.x + (size.x / 2) >= pPos->x + sizeMin.x &&		// 上
		pos.x - (size.x / 2) <= pPos->x + sizeMax.x &&		// 下
		pos.z + (size.z / 2) >= pPos->z + sizeMin.z &&		// 右
		pos.z - (size.z / 2) <= pPos->z + sizeMax.z &&		// 左
		pos.y + (size.y/ 2) >= pPos->y + sizeMin.y &&		// 手前
		pos.y - (size.y/2) <= pPos->y + sizeMax.y)			// 奥
	{// アイテムにぶつかった場合
		if (m_ItemType == TYPE_BULLETADD)
		{//	スピードアイテムだったら
			bHit = true;										//	当たった
			Uninit();											//	開放
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEM000);	//	アイテム取得時の音
		}
		else if (m_ItemType == TYPE_LIFEUP)
		{//	回復アイテムだったら
			bHit = true;										//	当たった
			Uninit();											//	開放
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEM001);	//	アイテム取得時の音

		}
	}

	return bHit;
}