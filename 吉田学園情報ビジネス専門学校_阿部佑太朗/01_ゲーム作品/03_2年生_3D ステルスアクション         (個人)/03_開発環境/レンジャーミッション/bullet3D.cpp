//=============================================================================
//
//	弾3Dの処理[bullet.cpp]
//	Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"	//	マネージャー
#include "renderer.h"	//	レンダラー
#include "bullet3D.h"	//	弾3D
#include "block.h"		//	ブロック
#include "wall.h"		//	壁
#include "floor.h"		//	床
#include "effect.h"		//	エフェクト
#include "enemy.h"		//	敵
#include "sound.h"		//	音

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME_BOOM	"data\\MODEL\\Object\\boom.x"		// 通常ブロック

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		*CBullet3D::m_pTexture[BULLET3D_MAX] = {};			// テクスチャ情報へのポインタ
LPD3DXMESH				CBullet3D::m_pMesh[BULLET3D_MAX] = {};				// メッシュ情報へのポインタ
LPD3DXBUFFER			CBullet3D::m_pBuffMat[BULLET3D_MAX] = {};			// マテリアル情報へのポインタ
DWORD					CBullet3D::m_nNumMat[BULLET3D_MAX] = {};			// マテリアル情報の数

//=============================================================================
//	コンストラクタ
//=============================================================================
CBullet3D::CBullet3D() :CSceneX(CScene::PRIORITY_3,CScene::OBJTYPE_BULLET3D)
{
	m_Bullet3DType = BULLET3D_TYPE_BOOM;		//	弾の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	動きの初期化
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	前回の位置の初期化
	m_nDispCounter = 0;							//	弾が消えるまでのカウント
	m_BulletState = BULLET_NONE;				//	弾の状態
	m_bExplColl = false;						//
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet3D::~CBullet3D()
{

}

//=============================================================================
//	モデルのテクスチャの読み込み
//=============================================================================
HRESULT CBullet3D::Load(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	モデルの名前を格納のする変数
	char cModelName[256];

	for (int nCntIndex = 0; nCntIndex < BULLET3D_MAX; nCntIndex++)
	{//	モデルを最大数分回す
		switch (nCntIndex)
		{
		case BULLET3D_TYPE_BOOM:	//	弾種類[　ボム　]
			wsprintf(cModelName, MODEL_NAME_BOOM);
			break;
		}
		// Xファイルの読み込み
		D3DXLoadMeshFromX(cModelName,
			D3DXMESH_SYSTEMMEM,
			pDevice, NULL,
			&m_pBuffMat[nCntIndex],
			NULL,
			&m_nNumMat[nCntIndex],
			&m_pMesh[nCntIndex]);

		D3DXMATERIAL *pmat;									// マテリアルデータへのポインタ
		D3DMATERIAL9 *matDef;								// 現在のマテリアル保存用

		pmat = (D3DXMATERIAL*)m_pBuffMat[nCntIndex]->GetBufferPointer();
		matDef = new D3DMATERIAL9[m_nNumMat[nCntIndex]];						//	マテリアルのメモリの確保
		m_pTexture[nCntIndex] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntIndex]];	//	テクスチャのメモリの確保

		for (DWORD tex = 0; tex < m_nNumMat[nCntIndex]; tex++)
		{// カウント
			matDef[tex] = pmat[tex].MatD3D;					//　マテリアルのプロパティを記述する D3DMATERIAL9 構造体
			matDef[tex].Ambient = matDef[tex].Diffuse;		//　光の直接当たる部分の色を光を当たらない部分と同期させる
			m_pTexture[nCntIndex][tex] = NULL;				//	テクスチャ情報を空にする
			if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
			{// テクスチャを使用している & 文字列の長さが0以上だったら

				if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTexture[nCntIndex][tex])))
				{
					//MessageBox(NULL, "モデルのテクスチャ/マテリアルの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}
		//	マテリアルの開放
		delete[] matDef;
		matDef = NULL;
	}
	return S_OK;
}

//=============================================================================
//	モデルのテクスチャの開放
//=============================================================================
void CBullet3D::Unload(void)
{
	for (int nCntIndex = 0; nCntIndex < BULLET3D_MAX; nCntIndex++)
	{//	モデルの最大数分回す
	 // テクスチャの破棄
		for (DWORD tex = 0; tex < m_nNumMat[nCntIndex]; tex++)
		{// カウント
			if (m_pTexture[nCntIndex][tex] != NULL)
			{// NULL以外の場合
				m_pTexture[nCntIndex][tex]->Release();		// メモリの解放
				m_pTexture[nCntIndex][tex] = NULL;			// NULLへ
			}
		}
		//	テクスチャの開放
		delete[] m_pTexture[nCntIndex];
		m_pTexture[nCntIndex] = NULL;

		// マテリアルの開放
		if (m_pBuffMat[nCntIndex] != NULL)
		{// NULL以外の場合
			m_pBuffMat[nCntIndex]->Release();				// メモリの解放
			m_pBuffMat[nCntIndex] = NULL;					// NULLへ
		}

		// マテリアルの開放
		if (m_pMesh[nCntIndex] != NULL)
		{// NULL以外の場合
			m_pMesh[nCntIndex]->Release();					// メモリの解放
			m_pMesh[nCntIndex] = NULL;						// NULLへ
		}
		// マテリアルの初期化
		m_nNumMat[nCntIndex] = 0;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move, BULLET3DTYPE BulletType)
{
	CBullet3D *pBullet3D = {};	//	弾3Dのポインタ型変数

	if (pBullet3D == NULL)
	{//	弾が使われていなかった場合
		pBullet3D = new CBullet3D;	//	弾3Dのメモリ確保
		if (pBullet3D != NULL)
		{//	メモリの開放が出来た場合
			pBullet3D->Init(pos, rot, scale, move,BulletType);	//	初期化処理
		}
	}
	return pBullet3D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 move ,BULLET3DTYPE BulletType)
{
	//	変数の設定の初期化
	CSceneX::SetInitAll(m_pTexture[BulletType], m_pMesh[BulletType], m_pBuffMat[BulletType], m_nNumMat[BulletType], pos, rot, scale);
	CSceneX::Init();			//	初期化処理
	CSceneX::Setpos(pos);		//	位置の設定
	CSceneX::Setrot(rot);		//	回転の処理
	CSceneX::SetScale(scale);	//	拡大縮小

	//	弾の種類の設定
	m_Bullet3DType = BulletType;
	//	動きの設定
	m_move = move;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet3D::Uninit(void)
{
	//	終了処理
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet3D::Update(void)
{
	D3DXVECTOR3 vtxMax = CSceneX::Getsize(0);		//	大きさの最大値
	D3DXVECTOR3 vtxMix = CSceneX::Getsize(1);		//	大きさの最小値
	CSound *pSound = CManager::GetSound();			//	サウンドの取得
	D3DXVECTOR3 pos = CSceneX::Getpos();			//	位置の取得
	D3DXVECTOR3 rot = CSceneX::Getrot();			//	回転の取得
	D3DXVECTOR3 scale = CSceneX::GetScale();		//	拡大縮小の取得

	// シーン
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// 現在　
	CScene *pSceneNext = NULL;								// 次

	//	位置の保存
	m_posOld = pos;

	switch (m_BulletState)
	{
	case BULLET_NONE:

		//	重力量
		m_move.y -= 0.75f;
		//	位置の動きを加算する
		pos += m_move;

		while (pScene != NULL)
		{// NULL以外の場合
		 // 次オブジェクト情報を保存
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
			{//	床だった場合
				CFloor *pFloor = (CFloor*)pScene;				//	床にキャスト
				pFloor->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		// 当たり判定]
				bool bHit = pFloor->GetHit();
				if (bHit == true)
				{
					m_BulletState = BULLET_HIT;		//	弾が当たった
				}
			}
			// 次のオブジェクトに設定
			pScene = pSceneNext;
		}
		pScene = CScene::GetScene(CScene::PRIORITY_3);	// 現在　
		pSceneNext = NULL;								// 次

		while (pScene != NULL)
		{// NULL以外の場合
		 // 次オブジェクト情報を保存
			pSceneNext = pScene->GetSceneNext();
			if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
			{// オブジェクトタイプがブロックだったら
				CBlock *pBlock = (CBlock*)pScene;									// ブロックにキャスト
				pBlock->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		// 当たり判定
				bool *bLand = pBlock->GetHit();
				if (bLand[0] == true)
				{// 上判定
					m_BulletState = BULLET_HIT;		//	弾が当たった
				}
			}
			else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
			{//	壁だった場合
				CWall *pWall = (CWall*)pScene;										//	壁にキャスト
				pWall->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);			//  当たり判定
			}
			else if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{//	敵だった場合
				CEnemy *pEnemy = (CEnemy*)pScene;									//	敵にキャスト
				pEnemy->Collision(&pos, &m_posOld, &m_move, vtxMax, vtxMix);		//  当たり判定
				bool bHit = pEnemy->GetHit();
				if (bHit == true)
				{//	オブジェクトとあたった
					m_BulletState = BULLET_HIT;		//	弾が当たった
				}

			}
			// 次のオブジェクトに設定
			pScene = pSceneNext;
		}
		CSceneX::Setpos(pos);								//	位置の設定
		CSceneX::Setrot(rot);								//	回転の設定
		CSceneX::SetScale(scale);							//	大きさの設定
		break;
	case BULLET_HIT:
		//	動きを止める
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//	カウント加算
		m_nDispCounter++;
		if ((m_nDispCounter % 2) == 0)
		{//	6フレームに0.1秒ずつ大きくしていく
			scale *= 1.075f;

		}
		if (m_nDispCounter >= BULLET_USE_VALSE)
		{//	弾が消えるまでのカウントが60フレーム以上たったっ倍
			m_BulletState = BULLET_DISP;				//	消えた状態
		}
		CSceneX::Setpos(pos);							//	位置の設定
		CSceneX::Setrot(rot);							//	回転の設定
		CSceneX::SetScale(scale);						//	大きさの設定
		break;
	case BULLET_DISP:
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);	//	爆発音
		CEffect::Create(pos, 0, 1);								//	煙の炎のエフェクト
		CEffect::Create(pos, 0, 0);								//	煙のエフェクト
		Uninit();
		break;
	}

}
//=============================================================================
//描画処理
//=============================================================================
void CBullet3D::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//	ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 頂点法線の自動正規化		開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// 描画処理
	CSceneX::Draw();

	// 頂点法線の自動正規化		終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	//	ライトを戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
