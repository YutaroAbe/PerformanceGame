//=============================================================================
//
//	ブロックの処理 [block.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "scene.h"
#include "block.h"
//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CBlock::m_Texture[MAX_BLOCK] = {};	//	ブロックの共通テクスチャのポインタ初期化
int CBlock::m_NumBlock = NULL;							//	ブロックの数初期化
int CBlock::m_nType = NULL;								//	種類の初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CBlock::CBlock() : CScene2D(3)
{
	m_NumBlock++;			//	ブロックの数の加算
	m_fWindth = NULL;		//	幅の初期化
	m_fHeight = NULL;		//	縦の初期化
}

//==============================================================================
//	デストラクタ
//==============================================================================
CBlock::~CBlock()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY)
{
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_BLOCK);

	//	初期化処理
	CScene2D::Init();
	m_fWindth = fWindth;	//	幅の代入
	m_fHeight = fHeight;	//	縦の代入
	m_nType = nType;		//	種類の代入

	//	ポリゴンの位置
	D3DXVECTOR3 pPos[4];

	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(m_fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, m_fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(m_fWindth, m_fHeight, 0.0f);

	//	UV
	D3DXVECTOR2 tex[4];

	tex[0] = D3DXVECTOR2(0.0f, 0.0f);
	tex[1] = D3DXVECTOR2(1.0f*fTexSplitX, 0.0f);
	tex[2] = D3DXVECTOR2(0.0f, 1.0f*fTexSplitY);
	tex[3] = D3DXVECTOR2(1.0f*fTexSplitX, 1.0f*fTexSplitY);

	SetVtxPosition(&pPos[0], pos);				//	位置の設定
	SetTexture(&tex[0]);						//	UV設定
	SetType(m_nType);							//	種類の設定
	SetWindthHeigth(m_fWindth, m_fHeight);		//	幅と高さの設定

	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CBlock::Uninit(void)
{
	//	終了処理
	CScene2D::Uninit();
	m_NumBlock--;								//	ブロックの数の減算
}

//==============================================================================
//	更新処理
//==============================================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();				//	位置
	D3DXVECTOR3 move = GetMoveing();				//	動き
	 float fWindth = GetfWindth();					//	幅
	 float fHeight = GetfHeight();					//	高さ
	fWindth = m_fWindth;							//	幅の代入
	fHeight = m_fHeight;							//	高さの代入
	D3DXVECTOR3 PlayerMove = CPlayer::GetMove();	//	プレイヤーの動きの取得

	if (PlayerMove.x >= 0.1f)
	{//	プレイヤーのX座標が0.1以上だった場合
	 //	ブロックをプレイヤーの移動のベクトルとは反対に動かす
		move.x -= PlayerMove.x;
	}
	else if (PlayerMove.x <= -0.1f)
	{//	プレイヤーのX座標が0.1イカだった場合
	//	ブロックをプレイヤーの移動のベクトルとは反対に動かす
		move.x += -PlayerMove.x;
	}

	//	動きを位置に加算
	pos.x += move.x;
	pos.y += move.y;

	//	頂点情報の設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, fHeight, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);
}

//==============================================================================
//	描画処理
//==============================================================================
void CBlock::Draw(void)
{
	//	シーン2Dの描画
	CScene2D::Draw();
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, float fWindth, float fHeight,int nType, float fTexSplitX, float fTexSplitY)
{
	CBlock *pBlock = {};		//	ブロックの変数

	if (pBlock == NULL)
	{//	ブロックが使われていなかったっ場合
		if (nType != TYPE_FALL)
		{//	ブロックのメモリの確保
			pBlock = new CBlock;
		}
		else if (nType == TYPE_FALL)
		{//	落ちるブロックのメモリの確保
			pBlock = new CBlockDrop;
		}
		if (pBlock != NULL)
		{//ブロックのメモリが確保されたら
			// 背景の初期化処理
			pBlock->Init(pos, fWindth, fHeight, nType, fTexSplitX, fTexSplitY);
			//	背景のテクスチャの割り当て
			pBlock->BindTexture(m_Texture[nType]);
		}
	}
	//	値を返す
	return pBlock;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CBlock::Laod(void)
{
	//	デバイスの設定
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_000, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_001, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_002, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_003, &m_Texture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_004, &m_Texture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_005, &m_Texture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_006, &m_Texture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_007, &m_Texture[7]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_008, &m_Texture[8]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_009, &m_Texture[9]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_010, &m_Texture[10]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BLOCK_011, &m_Texture[11]);

	//	値を返す
	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CBlock::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
	{//	ブロックのテクスチャの最大数分
		//	テクスチャの破棄
		if (m_Texture[nCount] != NULL)
		{//	テクスチャが使用されていた場合
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}

//==============================================================================
//	敵の数の取得
//==============================================================================
int  CBlock::GetNumBlock(void)
{
	return m_NumBlock;
}

//==============================================================================
//	敵の種類の取得
//==============================================================================
int CBlock::GetTypeBlock(void)
{
	return m_nType;
}
//-------------------------------------------------------------------------------------------------------------------------------
//落ちるブロック
//-------------------------------------------------------------------------------------------------------------------------------
//==============================================================================
// コンストラクタ
//==============================================================================
CBlockDrop::CBlockDrop()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CBlockDrop::~CBlockDrop()
{
}

//==============================================================================
//	ブロックの初期化処理
//==============================================================================
HRESULT CBlockDrop::Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY)
{
	CBlock::Init(pos, fWindth, fHeight, nType, fTexSplitX, fTexSplitY);
	return S_OK;
}

//==============================================================================
//	ブロックの終了処理
//==============================================================================
void CBlockDrop::Uninit(void)
{
	CBlock::Uninit();
}
//==============================================================================
//	ブロックの更新処理
//==============================================================================
void CBlockDrop::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();				//	位置取得
	D3DXVECTOR3 move = GetMoveing();				//	動き取得
	float fWindth = GetfWindth();					//	幅取得
	float fHeight = GetfHeight();					//	高さの代入
	fWindth = m_fWindth;							//	幅の代入
	fHeight = m_fHeight;							//	高さの代入
	D3DXVECTOR3 PlayerMove = CPlayer::GetMove();	//	プレイヤーの動きの取得
	bool bLand = CPlayer::GetLand();				//	プレイヤーがブロックに乗っているかどうか

	if (PlayerMove.x >= 0.1f)
	{//	プレイヤーのX座標が0.1以上だった場合
	 //	ブロックをプレイヤーの移動のベクトルとは反対に動かす
		move.x -= PlayerMove.x;
	}
	else if (PlayerMove.x <= -0.1f)
	{//	プレイヤーのX座標が0.1イカだった場合
	 //	ブロックをプレイヤーの移動のベクトルとは反対に動かす
		move.x += -PlayerMove.x;
	}
	if (bLand == true)
	{//	プレイヤーがブロックに乗っていた場合
		move.y += 0.55f;	//	ブロック落とす
	}
	//	動きを位置に加算
	pos.x += move.x;
	pos.y += move.y;

	//	頂点情報の設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(0.0f, fHeight, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, fHeight, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);
}

//==============================================================================
//	ブロックの描画処理
//==============================================================================
void CBlockDrop::Draw(void)
{
	CBlock::Draw();
}