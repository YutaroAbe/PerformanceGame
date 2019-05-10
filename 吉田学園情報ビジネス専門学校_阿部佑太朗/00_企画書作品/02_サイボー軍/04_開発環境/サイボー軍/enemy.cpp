//=============================================================================
//
//	敵の処理 [enemy.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//=============================================================================
//	インクルードファイル
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "score.h"
#include "bullet.h"
#include "scene.h"
#include "explosion.h"
#include "enemycount.h"

//==============================================================================
//	静的メンバ変数初期化
// ==============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_Texture[MAX_ENEMY_TYPE] = {};	//	テクスチャの初期化
int CEnemy::m_nNUM_ENEMY = NULL;							//	敵の加算の初期化

//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemy::CEnemy() : CScene2D(4)
{
	m_nType = 0;						//	種類の初期化
	m_nAICounter = 0;					//	AI今後新規取引ローラー
	m_bBulletAttck = false;				//	攻撃の状態の初期化
	m_nLife = 0;						//	寿命の初期化
	enemystate = ENEMYSTATE_NOMAL;		//	状態の初期化
	m_nCounterState = 0;				//	ステータスカウンターの初期化
	m_nNUM_ENEMY++;						//	敵の数の加算
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemy::~CEnemy()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, int nType)
{
	m_nAICounter = rand() % 200 + 1;	//	敵の移動のラウンド設定
	m_bBulletAttck = false;				//	弾を撃っていない状態
	enemystate = ENEMYSTATE_NOMAL;		//	通常状態
	m_nCounterState = 0;				//	カウンターの初期化
	CScene2D::Init();
	//オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_ENEMY);

	m_nType = nType;					//	種類の代入
	m_nLife = nLife;					//	寿命の代入

	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
	pPos[1] = D3DXVECTOR3(0.0f, -0.0f, 0.0f);
	pPos[2] = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetVtxPosition(&pPos[0], pos);		//	位置の反映
	SetType(m_nType);					//	種類の反映
	SetLife(m_nLife);					//	寿命の反映
	CEnemycount::AddEnemyCount(+1);		//	敵の加算

	//	値を返す
	return S_OK;
}

//==============================================================================
//	終了処理
//==============================================================================
void CEnemy::Uninit(void)
{
	//	シーン2Dの終了処理
	CScene2D::Uninit();
	m_nNUM_ENEMY--;		//	敵の減算
}

//==============================================================================
//	更新処理
//==============================================================================
void CEnemy::Update(void)
{
	m_nAICounter++;

	switch (enemystate)
	{
	case ENEMYSTATE_NOMAL:
		break;
	case ENEMYSTATE_DAMAGE:
		CScene2D::ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			enemystate = ENEMYSTATE_NOMAL;
			CScene2D::ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
//	プレイヤーの生成処理
//==============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, int nType)
{
	CEnemy *pEnemy = {};

	if (pEnemy == NULL)
	{
		if (nType == 0)
		{
			pEnemy = new CEnemyType000;
		}
		else if (nType == 1)
		{
			pEnemy = new CEnemyType001;
		}
		else if (nType == 2)
		{
			pEnemy = new CEnemyType002;
		}
		else if (nType == 3)
		{
			pEnemy = new CEnemyType003;
		}
		else
		{//	タイプ以外だったら
			pEnemy = new CEnemyType000;
		}

		if (pEnemy != NULL)
		{
			// 背景の初期化処理
			pEnemy->Init(pos,move, nLife,nType);
			//	背景のテクスチャの割り当て
			pEnemy->BindTexture(m_Texture[nType]);
		}
		else
		{
		}
	}
	return pEnemy;
}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CEnemy::Laod(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_0, &m_Texture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_1, &m_Texture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_2, &m_Texture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_3, &m_Texture[3]);
	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		//	テクスチャの破棄
		if (m_Texture[nCount] != NULL)
		{
			m_Texture[nCount]->Release();
			m_Texture[nCount] = NULL;
		}
	}
}
//==============================================================================
//	ダメージ計算
//==============================================================================
void CEnemy::Hit(int nDamage)
{
	D3DXVECTOR3 pos = GetPosition();
	float fHeight = GetfHeight();							//	高さ
	m_nLife -= nDamage;
	CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);
	if (m_nLife <= 0)
	{
		CScore::AddScore(100);											//　スコア加算
		CExplosion::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f));									//	爆発の生成
		Uninit();														//

		CEnemycount::AddEnemyCount(-1);
	}
	else
	{
		m_nCounterState = 15;
		enemystate = ENEMYSTATE_DAMAGE;
	}
}

//==============================================================================
//	敵の数の取得
//==============================================================================
int  CEnemy::GetNUMENEMY(void)
{
	return m_nNUM_ENEMY;
}

//============================================================================================================================================================
//	エネミータイプ000
//============================================================================================================================================================
//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemyType000::CEnemyType000()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemyType000::~CEnemyType000()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemyType000::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;

	CEnemy::Init(pos, move,nLife, nType);

	return S_OK;
}
//==============================================================================
//	終了処理
//==============================================================================
void CEnemyType000::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	更新処理
//==============================================================================
void CEnemyType000::Update(void)
{

	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	位置
	D3DXVECTOR3 move = GetMoveing();						//	動き
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	プレイヤーの動きの取得
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	プレイヤーの動きの取得
	float fWindth = GetfWindth();							//	幅
	float fHeight = GetfHeight();							//	高さ
	fWindth = ENEMY_POLIGON_X_000;
	fHeight = ENEMY_POLIGON_Y_000;
	m_bAttackMove = false;									//	プレイヤーへの攻撃範囲じゃない

	m_posOld = pos;

	float fDiffAngle;				//差分
	float fDestAngle;				//目的の角度
	float fMoveAngle;				//現在の角度
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 1.0f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 200 <= playerpos.x && pos.x + 200 >= playerpos.x)
	{//	プレイヤーへの攻撃範囲
		m_bAttackMove = true;
		if (playermove.x >= 0.0f)
		{
			move.x -= playermove.x;
			move.x += sinf(fDiffAngle)*1.05f;
		}
		else if (playermove.x <= 0.0f)
		{
			move.x += -playermove.x;
			move.x += sinf(fDiffAngle)*1.05f;
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch(move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.75f;
		if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.75f;
		if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	重力
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	ブロックの位置
					float block_fWindth = pScene->GetfWindth();		//	ブロックの幅
					float block_fHeight = pScene->GetfHeight();		//	ブロックの高さ

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight )
					{//	YXが範囲内
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	ブロック上判定
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight )
						{//	ブロック下判定
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth )
						{//ブロック右判定
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fWindth >= block_pos.x)
						{//ブロック左判定
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);


	if (pos.y >= 760)
	{
		Hit(2);
	}
}
//==============================================================================
//	描画処理
//==============================================================================
void CEnemyType000::Draw(void)
{
	CEnemy::Draw();
}
//============================================================================================================================================================
//	エネミータイプ001
//============================================================================================================================================================
//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemyType001::CEnemyType001()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemyType001::~CEnemyType001()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemyType001::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	終了処理
//==============================================================================
void CEnemyType001::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	更新処理
//==============================================================================
void CEnemyType001::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	位置
	D3DXVECTOR3 move = GetMoveing();						//	動き
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	プレイヤーの動きの取得
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	プレイヤーの動きの取得
	float fWindth = GetfWindth();							//	幅
	float fHeight = GetfHeight();							//	高さ
	bool bLand = false;										//	ブロックに乗っているかどうか

	fWindth = ENEMY_POLIGON_X_001;
	fHeight = ENEMY_POLIGON_Y_001;
	m_bAttackMove = false;									//	プレイヤーへの攻撃範囲じゃない
	m_bBulletAttck = false;									//	弾の撃っていない
	m_posOld = pos;

	float fDiffAngle;				//差分
	float fDestAngle;				//目的の角度
	float fMoveAngle;				//現在の角度
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 300 <= playerpos.x && pos.x + 300 >= playerpos.x)
	{
		m_bAttackMove = true;					//	プレイヤーへの攻撃範囲
		if (rand() % 120 == 0 )
		{
			m_bBulletAttck = true;									//	弾の撃っている
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f+move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}

	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.75f;
		if ((m_nAICounter + 1) % 90 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.75f;
		if ((m_nAICounter + 1) % 90 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	重力
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	ブロックの位置
					float block_fWindth = pScene->GetfWindth();		//	ブロックの幅
					float block_fHeight = pScene->GetfHeight();		//	ブロックの高さ

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight)
					{//	YXが範囲内
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	ブロック上判定
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight)
						{//	ブロック下判定
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//ブロック右判定
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fHeight >= block_pos.x)
						{//ブロック左判定
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	描画処理
//==============================================================================
void CEnemyType001::Draw(void)
{
	CEnemy::Draw();
}

//============================================================================================================================================================
//	エネミータイプ002
//============================================================================================================================================================
//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemyType002::CEnemyType002()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemyType002::~CEnemyType002()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemyType002::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	終了処理
//==============================================================================
void CEnemyType002::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	更新処理
//==============================================================================
void CEnemyType002::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	位置
	D3DXVECTOR3 move = GetMoveing();						//	動き
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	プレイヤーの動きの取得
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	プレイヤーの動きの取得
	float fWindth = GetfWindth();							//	幅
	float fHeight = GetfHeight();							//	高さ
	bool bLand = false;										//	ブロックに乗っているかどうか

	fWindth = ENEMY_POLIGON_X_001;
	fHeight = ENEMY_POLIGON_Y_001;
	m_bAttackMove = false;									//	プレイヤーへの攻撃範囲じゃない
	m_bBulletAttck = false;									//	弾の撃っていない
	m_posOld = pos;

	float fDiffAngle;				//差分
	float fDestAngle;				//目的の角度
	float fMoveAngle;				//現在の角度
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 300 <= playerpos.x && pos.x + 300 >= playerpos.x)
	{
		m_bAttackMove = true;					//	プレイヤーへの攻撃範囲
		if (rand() % 70 == 0)
		{
			m_bBulletAttck = true;									//	弾の撃っている
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, -2.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	重力
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	ブロックの位置
					float block_fWindth = pScene->GetfWindth();		//	ブロックの幅
					float block_fHeight = pScene->GetfHeight();		//	ブロックの高さ

					if (pos.x + (fWindth / 2) >= block_pos.x  &&																		//	プレイヤーが右からめり込んでるとき
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&														//	プレイヤーが左からめり込んでるとき
						pos.y >= block_pos.y &&																									//	プレイヤーが上から下にめり込んでるとき
						pos.y - fHeight <= block_pos.y + block_fHeight)																	//	プレイヤーが下から上にめり込んでるとき
					{//	YXが範囲内
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)																//	昔の位置が上に居て現在の位置がプロックにめり込んでるとき
						{//	ブロック上判定
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;																						//	プレイヤーをブロックのポジションYに出現させる
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&											//	プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
							pos.y - fHeight <= block_pos.y + block_fHeight)														//	現在の位置がめり込んでるとき
						{//	ブロック下判定
							pos.y = block_pos.y + block_fHeight + fHeight;														//	プレイヤーをブロック中心+ブロックの高さ+プレイヤーの高さの位置に出現させる
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&											//	昔の位置がブロックより右にあって現在の位置がめり込んでる場合
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//ブロック右判定
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&																//	昔の位置がブロックより左にあって現在の位置がめり込んでる場合
							pos.x + fHeight >= block_pos.x)
						{//ブロック左判定
							pos.x = m_posOld.x;																							//	昔の位置に出現させる
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	描画処理
//==============================================================================
void CEnemyType002::Draw(void)
{
	CEnemy::Draw();
}
//============================================================================================================================================================
//	エネミータイプ003
//============================================================================================================================================================
//==============================================================================
//	コンストラクタ
//==============================================================================
CEnemyType003::CEnemyType003()
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CEnemyType003::~CEnemyType003()
{

}

//==============================================================================
//	初期化処理
//==============================================================================
HRESULT CEnemyType003::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	move_ai = MOVE_AI_NONE;
	m_bAttackMove = false;
	CEnemy::Init(pos, move, nLife, nType);
	return S_OK;
}
//==============================================================================
//	終了処理
//==============================================================================
void CEnemyType003::Uninit(void)
{
	CEnemy::Uninit();
}
//==============================================================================
//	更新処理
//==============================================================================
void CEnemyType003::Update(void)
{
	CEnemy::Update();

	D3DXVECTOR3 pos = GetPosition();						//	位置
	D3DXVECTOR3 move = GetMoveing();						//	動き
	D3DXVECTOR3 playermove = CPlayer::GetMove();			//	プレイヤーの動きの取得
	D3DXVECTOR3 playerpos = CPlayer::GetPosition();			//	プレイヤーの動きの取得
	float fWindth = GetfWindth();							//	幅
	float fHeight = GetfHeight();							//	高さ
	bool bLand = false;										//	ブロックに乗っているかどうか

	fWindth = ENEMY_POLIGON_X_001+15;
	fHeight = ENEMY_POLIGON_Y_001+15;
	m_bAttackMove = false;									//	プレイヤーへの攻撃範囲じゃない
	m_bBulletAttck = false;									//	弾の撃っていない
	m_posOld = pos;

	float fDiffAngle;				//差分
	float fDestAngle;				//目的の角度
	float fMoveAngle;				//現在の角度
	fDestAngle = D3DX_PI;
	fDestAngle = atan2f(playerpos.x - pos.x, playerpos.y - pos.y);
	fMoveAngle = (0.0f, 0.0f, 0.0f);

	fDiffAngle = fDestAngle - fMoveAngle;
	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	if (fDiffAngle < -D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.7f;
	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	if (fMoveAngle < -D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}

	if (pos.x - 280 <= playerpos.x && pos.x + 280 >= playerpos.x)
	{
		m_bAttackMove = true;					//	プレイヤーへの攻撃範囲
		if (rand() % 100 == 0)
		{
			m_bBulletAttck = true;									//	弾の撃っている
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, 0.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, cosf(fDiffAngle)*4.05f + move.y, 0.0f), 4, CBullet::BULLET_ENEMY);
			CBullet::Create(pos + D3DXVECTOR3(0.0f, -fHeight / 2, 0.0f), D3DXVECTOR3(sinf(fDiffAngle)*4.05f + move.x, -2.0f, 0.0f), 4, CBullet::BULLET_ENEMY);
		}
		if (m_bBulletAttck == false)
		{
			if (playermove.x >= 0.0f)
			{
				move.x -= playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
			else if (playermove.x <= 0.0f)
			{
				move.x += -playermove.x;
				move.x += sinf(fDiffAngle)*1.05f;
			}
		}
	}
	else
	{
		if (playermove.x >= 0.1f)
		{
			move.x -= playermove.x;
		}
		else if (playermove.x <= -0.1f)
		{
			move.x += -playermove.x;
		}
	}

	switch (move_ai)
	{
	case MOVE_AI_NONE:
		if ((m_nAICounter + 1) % 30 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	case MOVE_AI_LEFT:
		move.x += sinf(D3DX_PI * -0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_RIGHT;
		}
		break;
	case MOVE_AI_RIGHT:
		move.x += sinf(D3DX_PI * 0.5f)*0.55f;
		if ((m_nAICounter + 1) % 70 == 0 && m_bAttackMove == false)
		{
			move_ai = MOVE_AI_LEFT;
		}
		else if ((m_nAICounter + 1) % 60 == 0 && m_bAttackMove == true)
		{
			move_ai = MOVE_AI_LEFT;
		}
		break;
	}

	//	重力
	move.y += 0.95f;

	pos.x += move.x;
	pos.y += move.y;

	for (int nCnt = 0; nCnt < MAX_DROW; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_NUM; nCntScene++)
		{//	オブジェクトの総数分
			CScene2D *pScene;
			pScene = (CScene2D*)CScene::GetScene(nCnt, nCntScene);

			if (pScene != NULL)
			{
				//	オブジェクトの取得
				CScene::OBJTYPE objtype = pScene->GetObjType();
				if (objtype == CScene::OBJECT_BLOCK)
				{
					D3DXVECTOR3 block_pos = pScene->GetPosition();	//	ブロックの位置
					float block_fWindth = pScene->GetfWindth();		//	ブロックの幅
					float block_fHeight = pScene->GetfHeight();		//	ブロックの高さ

					if (pos.x + (fWindth / 2) >= block_pos.x  &&
						pos.x - (fWindth / 2) <= block_pos.x + block_fWindth  &&
						pos.y >= block_pos.y &&
						pos.y - fHeight <= block_pos.y + block_fHeight)
					{//	YXが範囲内
						if (m_posOld.y <= block_pos.y && pos.y >= block_pos.y)
						{//	ブロック上判定
							bLand = true;
							pos.y = block_pos.y;
							move.y = 0.0f;
						}
						else if (m_posOld.y - fHeight >= block_pos.y + block_fHeight  &&
							pos.y - fHeight <= block_pos.y + block_fHeight)
						{//	ブロック下判定
							pos.y = block_pos.y + block_fHeight + fHeight;
							move.y = 0.0f;
						}
						else if (m_posOld.x + fWindth >= block_pos.x + block_fWindth  &&
							pos.x - fWindth <= block_pos.x + block_fWindth)
						{//ブロック右判定
							pos.x = m_posOld.x;
							move.x = 4.0f;
						}
						else if (m_posOld.x - fWindth <= block_pos.x &&
							pos.x + fHeight >= block_pos.x)
						{//ブロック左判定
							pos.x = m_posOld.x;
							move.x = -4.0f;
						}
					}
				}
			}
		}
	}
	//	大きさの設定
	D3DXVECTOR3 pPos[4];
	pPos[0] = D3DXVECTOR3(-fWindth, -fHeight, 0.0f);
	pPos[1] = D3DXVECTOR3(fWindth, -fHeight, 0.0f);
	pPos[2] = D3DXVECTOR3(-fWindth, 0.0f, 0.0f);
	pPos[3] = D3DXVECTOR3(fWindth, 0.0f, 0.0f);
	CScene2D::SetVtxPosition(&pPos[0], pos);

	SetWindthHeigth(fWindth, fHeight);
	if (pos.y >= 760)
	{
		Hit(10);
	}

}
//==============================================================================
//	描画処理
//==============================================================================
void CEnemyType003::Draw(void)
{
	CEnemy::Draw();
}