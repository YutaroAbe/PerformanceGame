//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "enemy.h"			// プレイヤー
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "game.h"			// ゲーム
#include "input.h"			// 入力
#include "model.h"			// モデル
#include "camera.h"			// カメラ
#include "block.h"			// ブロック
#include "item.h"			// アイテム
#include "effect.h"			// エフェクト
#include "fade.h"			// フェイド
#include "orbit.h"			// 軌跡
#include "floor.h"			// 床
#include "shadow.h"			// 影
#include "wall.h"			// 壁
#include "bullet3D.h"		// 弾3D
#include "player.h"			// プレイヤー
#include "hpber3D.h"		//	敵のHPバー
#include "bullet2D.h"		//	弾2D
#include "sound.h"			//	音

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME_ROBOT_000				("data\\TEXT\\enemymotion\\ROBOT_000\\enemymotion_000.txt")		//	読み込むテキストの名前
#define FILE_NAME_ROBOT_001				("data\\TEXT\\enemymotion\\ROBOT_001\\enemymotion_001.txt")		//	読み込むテキストの名前
#define FILE_NAME_ROBOT_002				("data\\TEXT\\enemymotion\\ROBOT_002\\enemymotion_002.txt")		//	読み込むテキストの名前
#define FILE_NAME_ROBOT_003				("data\\TEXT\\enemymotion\\ROBOT_003\\enemymotion_003.txt")		//	読み込むテキストの名前
#define FILE_NAME_LASTOBJ				("data\\TEXT\\enemymotion\\LASTOBJ\\lastobj.txt")				//	読み込むテキストの名前


#define GRAVITY							(0.7f)															//	重力
#define WALK_SPEED						(0.75f)															//	歩くスピード
#define MOVE_DOWNSPEED_NOR				(0.25f)															//	減速スピード
#define BULLET_DAMAGE_RANGE				(25)															//	弾のダメージの範囲
#define DAMEGE_COUNTER					(20)															//	ダメージ中のカウンター
#define HOMINGRANGE						(200)															//	追従する距離

//*****************************************************************************
//	静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH					CEnemy::m_pMeshModel[MAX_NUMPARTS] = {};
LPD3DXBUFFER				CEnemy::m_pBuffMatModel[MAX_NUMPARTS] = {};
LPDIRECT3DTEXTURE9			*CEnemy::m_pTextureModel[MAX_NUMPARTS] = {};
DWORD						CEnemy::m_nNumMatModel[MAX_NUMPARTS] = {};
int							CEnemy::m_nNumPartsMax = 0;					//	パーツの最大数
bool CEnemy::m_bLastObDisp = false;						//	最後のオブジェクトがあるかどうか
//=============================================================================
// 敵クラス コンストラクタ
//=============================================================================
CEnemy::CEnemy() : CScene(PRIORITY_3, CScene::OBJTYPE_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	前回の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	向き
	m_state = STATE_NONE;						//	状態
	D3DXMatrixIdentity(&m_mtxWorld);			//	ワールドマトリックス
	m_pKeyInfo[MAX_NUMMOTION] = {};				//	キー情報へのポインタ
	m_nKey = 0;									//	現在のキーナンバー
	m_nCountFlame = 0;							//	フレーム
	m_bMotionEnd = false;						//	モーションの終了
	m_nMotionType = 0;							//	現在のモーションタイプ
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	プレイヤーの大きさの最大値
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	プレイヤーの大きさの最小値
	m_nCouterFreamMax[MAX_NUMMOTION] = {};		//	モーションのフレームの合計値
	m_nCntNumMosion = 0;						//	テキストに書かれているモーションの数
	m_nMotionTypeOld = 0;						//	モーションの過去の種類
	m_bHit = false;								//	当たったかどうか
	m_nLife = 0;								//	ライフ
	m_nDameCuter = 0;							//	ダメージカウンター
	m_nDispCuter = 0;							//	死んだときのカウンター
	m_AIEnemy = AI_NONE;						//	敵のAIの初期化
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	敵の最初の位置
	m_nAISelect = 0;							//	動きの選択
	m_bOtherEnemyHit = false;					//	敵同士当たった場合
	m_pShadow = NULL;							//	影の初期化
	m_pHpBer3D = NULL;							//	HPバーの初期化
	m_fAngle = 0.0f;							//	角度
	m_bLand = false;							//	乗っていない
	m_bPStealthMode = false;					//	プレイヤーがステルス状態入っているかどうか
	m_LengthDawn = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//	プレイヤーとの距離を短くする
	m_nMoveLength = 0;							//	移動する距離
	m_nType = 0;								//	種類
	m_fNoneSpeed = 0;							//	何もしていない時の速さ
	m_fFormingSpeed = 0;						//	追従する時の速さ
	m_bWallHit = false;							//	壁に当たったかどうか

}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nType, int nMoveLength,float fNoneSpeed, float fFormingSpeed, ENEMY_AI nAISelect)
{
	//敵のポインタ
	CEnemy *pEnemy = {};
	if (pEnemy == NULL)
	{//	敵が使われていなかった場合
		if (nType == 0)
		{//	通常の敵
			pEnemy = new CEnemyRobotNomal;
		}
		else if (nType == 1)
		{//	弾を撃つ敵
			pEnemy = new CEnemyRobotBullet;
		}
		else if (nType == 2)
		{//	棘の敵
			pEnemy = new CEnemyRobotSpine;
		}
		else if (nType == 3)
		{//	下にを撃つ敵
			pEnemy = new CEnemyRobotUndeBulletr;
		}
		else if (nType == 99)
		{//	最後のオブジェクト
			pEnemy = new CEnemyLastObj;
		}
		else
		{//	それ以外の数字だったら
			pEnemy = new CEnemyRobotNomal;
		}
		if (pEnemy != NULL)
		{//	初期化
			pEnemy->m_pos = pos;						//	位置の設定
			pEnemy->Setpos(pos);
			pEnemy->m_rot = rot;						//	回転の設定
			pEnemy->m_nLife = nLife;					//	ライフの設定
			pEnemy->m_nType = nType;					//	敵の種類
			pEnemy->m_nAISelect = nAISelect;			//	敵の動きの選択
			pEnemy->m_nMoveLength = nMoveLength;		//	移動する距離
			pEnemy->m_fNoneSpeed = fNoneSpeed;			//	何もしていない時の速さ
			pEnemy->m_fFormingSpeed = fFormingSpeed;	//	追従する時の速さ
			pEnemy->Init();								//	初期化処理
		}
	}
	//情報を返す
	return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	m_bLastObDisp = false;	//最後のオブジェクトが消えたかどうか
	if (m_nType == 0)
	{// 判定設定 000
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	 // 拡大縮小用変数
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 70.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 1)
	{// 判定設定 001
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	 // 拡大縮小用変数

		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 85.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 2)
	{// 判定設定 001
		m_Scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);	 // 拡大縮小用変数
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 60.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 3)
	{// 判定設定 001
		m_Scale = D3DXVECTOR3(1.2f, 1.2f, 1.2f);	 // 拡大縮小用変数
		m_vtxMax = D3DXVECTOR3(15.0f *m_Scale.x, 50.0f*m_Scale.y, 15.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-15.0f*m_Scale.x, 0.0f*m_Scale.y, -15.0f*m_Scale.z);
	}
	else if (m_nType == 99)
	{// 判定設定 最後のオブジェクト
		m_Scale = D3DXVECTOR3(5.2f, 5.2f, 5.2f);	 // 拡大縮小用変数
		m_vtxMax = D3DXVECTOR3(29.0f *m_Scale.x, 20.0f*m_Scale.y, 17.0f*m_Scale.z);
		m_vtxMin = D3DXVECTOR3(-29.0f*m_Scale.x, 0.0f*m_Scale.y, -17.0f*m_Scale.z);
	}
	//敵情報の読み込み
	FileLoad();
	for (int nCnterMosion = 0; nCnterMosion < MAX_NUMMOTION; nCnterMosion++)
	{//	モーションの確保回す
		if (m_nCntNumMosion >= nCnterMosion)
		{//	モーションのテキストに書かれている種類分回す
			for (int nCounter = 0; nCounter < m_aMotionInfo[nCnterMosion].nNumKey; nCounter++)
			{//	モーションのキー数分回す
				m_nCouterFreamMax[nCnterMosion] += m_aMotionInfo[nCnterMosion].aKayInfo[nCounter].nFrame;
			}
		}
	}
	if (m_nType == 1|| m_nType == 3)
	{// 判定設定 001
	 //	影の生成
		if (m_pShadow == NULL)
		{//	影が使われていなかったら
			m_pShadow = CShadow::Create(m_pos, m_rot, D3DXVECTOR3(m_vtxMax.x, 0.0f, m_vtxMax.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
		}
	}
	CPlayer *pPlayer = CGame::GetPlayer();				//	プレイヤーの情報の取得
	if (pPlayer != NULL)
	{//	プレイヤーが使われていた場合
	 //	HPバーの生成
		if (m_pHpBer3D == NULL)
		{//	HPバーが使われていなかったら
			m_pHpBer3D =
				CHpBer3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y + 5, m_pos.z), m_rot,
					D3DXVECTOR3(5.0f*m_nLife, 5.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
	}

	m_InitPos = m_pos;		//	初期の位置の保存
	m_nNumPartsMax = m_nNumParts;		//	パーツの最大数の設定
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{

	if (m_pShadow != NULL)
	{//	影が使用されたいたっばい
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
	if (m_pHpBer3D != NULL)
	{//	HPバーが使用されたいたっばい
		m_pHpBer3D->Uninit();
		m_pHpBer3D = NULL;
	}

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{//	モデルの数回す
		if (m_apModel[nCnt] != NULL)
		{//	終了処理
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}

	//	プレイヤーの開放
	CGame::SetEnemy();

	// フラグを立てる
	CScene::SetDeath();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// 位置保存
	m_posOld = m_pos;
	//	モーションの保存
	m_nMotionTypeOld = m_nMotionType;

	switch (m_state)
	{// 状態
	 //-----------------------------------------
	 //	通常
	 //-----------------------------------------
	case STATE_NONE:
		if (m_pShadow != NULL)
		{//	影が使用されたいたっばい
		 //	影の位置の設定
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_pos.y, m_apModel[0]->GetMtxWorld()._43));
		}
		if (m_pHpBer3D != NULL)
		{//	影が使用されたいたっばい
		 //	影の位置の設定
			m_pHpBer3D->Setpos(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y + 7, m_pos.z));
		}
		break;
		//-----------------------------------------
		// ダメージ
		//-----------------------------------------
	case STATE_DAMAGE:
		m_nDameCuter++;			//	ダメージカウンター
		if (m_nDameCuter <= DAMEGE_COUNTER / 2)
		{//	ダメージフレーム/2以内の数値だった場合
			m_Scale.x += 0.0065f;			//	大きさを変えるX軸
			m_Scale.z += 0.0065f;			//	大きさを変えるZ軸
			m_Scale.y += 0.0095f;			//	大きさを変えるY軸
		}
		else if (m_nDameCuter <= DAMEGE_COUNTER)
		{//	ダメージのフレーム
			m_Scale.x -= 0.0065f;			//	大きさを変えるX軸
			m_Scale.z -= 0.0065f;			//	大きさを変えるZ軸
			m_Scale.y -= 0.0095f;			//	大きさを変えるY軸
		}
		else
		{//	ダメージカウンターが超えたら通常にもどす
			m_nDameCuter = 0;					//	ダメージカウンターの初期化
			m_state = STATE_NONE;				//	ステータスを通常
		}
		break;
		//-----------------------------------------
		// 死亡
		//-----------------------------------------
	case STATE_DEATH:
		if (m_nType ==99)
		{//最後のオブジェクトが壊れたとき
		 //	ゴールブロックの生成
			CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, 5500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 0.7f, 2.0f), (CBlock::MODELTYPE)9, (CBlock::COLTYPE)3);
			m_bLastObDisp = true;
		}
		m_nDispCuter++;
		if (m_nDispCuter <= 15)
		{//	死んだときのカウンター
			m_Scale.x += 0.0075f;				//	大きさを変えるX軸
			m_Scale.z += 0.0075f;				//	大きさを変えるZ軸
			m_Scale.y += 0.0105f;				//	大きさを変えるY軸
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y / 2, m_pos.z), 2, 2);	//	雷のエフェクト
		}
		if (m_nDispCuter < 20 && m_nDispCuter > 15)
		{//	死んだときのカウンター
			CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + m_vtxMax.y / 2, m_pos.z), 1, 0);	//	煙のエフェクト
		}
		break;
	}
	//	位置の加算
	m_pos += m_move;

	//	当たり判定の管理
	ManagementCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);

	//モーション更新
	UpdateMotion();


	if (m_state == STATE_DEATH && m_nDispCuter >=20)
	{//	敵が死んだ場合　かつ　カウンターが指定の数値以上いった場合
		Uninit();							//	敵が消える時
	}

	CScene *pScene = CScene::GetScene(CScene::PRIORITY_3);	// 現在　
	CScene *pSceneNext = NULL;								// 次
	if (m_bLastObDisp == true)
	{//	最後のオブジェクトが消えた場合
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y , m_pos.z), 1, 0);	//	煙のエフェクト
		CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y+10 , m_pos.z), 1, 0);	//	煙のエフェクト

		Uninit();							//	敵が消える時
	}
#ifdef _DEBUG
	//CManager::m_CDebugProcRight->Print("\n----------エネミーのステータス------------------");
	CManager::m_CDebugProcLeft->Print("\nエネミーの位置  ( %.1f : %.1f  : %.1f)", m_pos.x, m_pos.y, m_pos.z);
	//CManager::m_CDebugProcLeft->Print("\nエネミーの動き　( %.4f : %.4f  : %.4f)", m_move.x, m_move.y, m_move.z);
	//CManager::m_CDebugProcRight->Print("\nエネミーの向き　( %.1f : %.1f  : %.1f)", m_rot.x, m_rot.y, m_rot.z);
	//CManager::m_CDebugProcLeft->Print("\n現在のモーション　( %d)", m_nMotionType);
	//CManager::m_CDebugProcRight->Print("\n-------------------------------------------------");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//	計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, matScale, mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//拡大縮小行列の作成
	D3DXMatrixScaling(&matScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &matScale);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{//	パーツ分回す
		if (m_apModel[nCnt] != NULL)
		{//	描画処理
			m_apModel[nCnt]->Draw();
		}
	}

}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	return S_OK;
}

//=============================================================================
// 破棄処理
//=============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCntIndex = 0; nCntIndex < m_nNumPartsMax; nCntIndex++)
	{//	モデルの最大数分回す
	 // テクスチャの破棄
		for (DWORD tex = 0; tex < m_nNumMatModel[nCntIndex]; tex++)
		{// カウント
			if (m_pTextureModel[nCntIndex][tex] != NULL)
			{// NULL以外の場合
				m_pTextureModel[nCntIndex][tex]->Release();		// メモリの解放
				m_pTextureModel[nCntIndex][tex] = NULL;			// NULLへ
			}
		}
		//	テクスチャの開放
		delete[] m_pTextureModel[nCntIndex];
		m_pTextureModel[nCntIndex] = NULL;

		// マテリアルの開放
		if (m_pBuffMatModel[nCntIndex] != NULL)
		{// NULL以外の場合
			m_pBuffMatModel[nCntIndex]->Release();				// メモリの解放
			m_pBuffMatModel[nCntIndex] = NULL;					// NULLへ
		}

		// マテリアルの開放
		if (m_pMeshModel[nCntIndex] != NULL)
		{// NULL以外の場合
			m_pMeshModel[nCntIndex]->Release();					// メモリの解放
			m_pMeshModel[nCntIndex] = NULL;						// NULLへ
		}
		// マテリアルの初期化
		m_nNumMatModel[nCntIndex] = 0;
	}
}


//=============================================================================
//	角度を加算する
//=============================================================================
void CEnemy::ManagementAddRod(D3DXVECTOR3 rotDest)
{
	//目的の向きの修正
	if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2.0f;
	}
	else if (rotDest.y > D3DX_PI)
	{
		rotDest.y -= D3DX_PI * 2.0f;
	}
	//	回転の角度のブレンド
	float fAngle = rotDest.y - m_rot.y;
	if (fAngle < -D3DX_PI)
	{
		fAngle += D3DX_PI * 2.0f;
	}
	else if (fAngle > D3DX_PI)
	{
		fAngle -= D3DX_PI * 2.0f;
	}
	//	回転のブレンドする値を回転に代入
	m_rot.y += fAngle * 0.1f;
	//向きの修正
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	//	回転のブレンドする値を回転に代入
	m_rot.y += fAngle * 0.085f;

}

//=============================================================================
//	当たり判定の総括
//=============================================================================
void CEnemy::ManagementCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// 現在　
	CScene *pSceneNext = NULL;								// 次

	while (pScene != NULL)
	{// NULL以外の場合
	 // 次オブジェクト情報を保存
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
		{//	床だった場合
			CFloor *pFloor = (CFloor*)pScene;				//	床にキャスト
			pFloor->Collision(pos, posOld, move, sizeMax, sizeMin);		// 当たり判定
		}
		// 次のオブジェクトに設定
		pScene = pSceneNext;
	}

	// シーン
	pScene = CScene::GetScene(CScene::PRIORITY_3);	// 現在　
	pSceneNext = NULL;								// 次

	while (pScene != NULL)
	{// NULL以外の場合
	 // 次オブジェクト情報を保存
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{// オブジェクトタイプがブロックだったら
			CBlock *pBlock = (CBlock*)pScene;									// ブロックにキャスト
			if (pBlock->Collision(pos, posOld, move, sizeMax, sizeMin) == true)
			{// 当たり判定
				m_bWallHit = true;		//	壁に当たった
			}

			bool *bLand = pBlock->GetHit();

		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
		{//	壁だった場合
			CWall *pWall = (CWall*)pScene;					//	壁にキャスト
			if (pWall->Collision(pos, posOld, move, sizeMax, sizeMin)==true)		// 当たり判定
			{//	壁に当たった場合
				m_bWallHit = true;		//	壁に当たった
			}
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_BULLET3D)
		{
			CBullet3D *pBullet3D = (CBullet3D*)pScene;				//	弾にキャスト
			D3DXVECTOR3 BulletPos = pBullet3D->Getpos();			//	弾の位置
			int nCounter = pBullet3D->GetDispCut();					//	弾が消えるまでのカウンター
			if (nCounter >= BULLET_USE_VALSE)
			{//	弾が消えるまでの時間超えたら
				if (BulletPos.x - BULLET_DAMAGE_RANGE < m_pos.x + m_vtxMax.x &&
					m_pos.x + m_vtxMin.x < BulletPos.x + BULLET_DAMAGE_RANGE &&
					BulletPos.y - BULLET_DAMAGE_RANGE < m_pos.y + m_vtxMax.y &&
					m_pos.y + m_vtxMin.y < BulletPos.y + BULLET_DAMAGE_RANGE &&
					BulletPos.z - BULLET_DAMAGE_RANGE < m_pos.z + m_vtxMax.z &&
					m_pos.z + m_vtxMin.z < BulletPos.z + BULLET_DAMAGE_RANGE)
				{//	爆発の範囲に入った場合
					HitDamege(2);	//	ダメージ
				}
			}
		}
		else if (pScene->GetObjType() == CScene3D::OBJTYPE_ENEMY)
		{
			CEnemy *pEnemy = (CEnemy*)pScene;
			// 敵同士の当たり判定
			pEnemy->OtherEnemyCollision(pos, posOld, move, sizeMax, sizeMin);		// 当たり判定
		}
		// 次のオブジェクトに設定
		pScene = pSceneNext;
	}

	pScene = CScene::GetScene(CScene::PRIORITY_4);	// 現在　
	pSceneNext = NULL;								// 次

	while (pScene != NULL)
	{// NULL以外の場合
	 // 次オブジェクト情報を保存
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
		{// オブジェクトタイプがブロックだったら
			CPlayer *pPlayer = (CPlayer*)pScene;				// ブロックにキャスト
			D3DXVECTOR3 Playerrot = pPlayer->Getrot();			//	動きの取得
			bool bAtkLastHit = pPlayer->GetLastHit();			//	最終攻撃の取得
			bool bPlayerInBlock = pPlayer->GetStealthMode();		//	ステルスモードの取得
			m_bPStealthMode = bPlayerInBlock;						//	ステルスモードの設定
																	//	攻撃当たり判定
			if (pPlayer->AttackCollsion(pos, posOld, move, sizeMax, sizeMin)== true)
			{//	攻撃の範囲内に入った場合
				HitDamege(1);										//	ダメージ
				if (bAtkLastHit == true)
				{//	最終攻撃が当たった場合
					//m_move.x += Playerrot.y * -10.0f;				//	動きの加算
					//m_rotDest.y = Playerrot.y * -1;					//	向きの切り替え
				}

			}
			// 当たり判定
			pPlayer->BoxCollision(pos, posOld, move, sizeMax, sizeMin);		// 当たり判定
		}
		// 次のオブジェクトに設定
		pScene = pSceneNext;
	}

}

//==============================================================================
//	ダメージ計算
//==============================================================================
void CEnemy::HitDamege(int nDamage)
{
	int nValue = m_nLife - nDamage;	//	ダメージをHPにひく
	m_nLife = nValue;				//	計算した値をライフに代入
	if (m_nLife <= 0)
	{//	ライフが0以下になった場合
		m_state = STATE_DEATH;		//	ステータスを死亡状態に変える
	}
	else
	{//	HPがまだ残っている状態
		if (m_pHpBer3D != NULL)
		{//	ｈPバーが使用されていた場合
			m_pHpBer3D->SizeChange(nDamage, this);				//	Hpばーのサイズ変更
		}
		m_state = STATE_DAMAGE;								//	ダメージ状態に切り替える
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CEnemy::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *m_move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	//	当たっているかの設定
	m_bHit = false;
	//	乗っているかどうか
	m_bLand = false;
	D3DXVECTOR3 EnemyPos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 EnemyMove = CEnemy::Getmove();			//	位置の取得
	D3DXVECTOR3 EnemyRot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 EnemySizeMax = CEnemy::Getsize(0);		//	大きさの最大値
	D3DXVECTOR3 EnemySizeMin = CEnemy::Getsize(1);		//	大きさの最小値

	if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) &&
		(pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x) &&
		(EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) &&
		(pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
	{// X/Z範囲確認
		if ((pos->y + sizeMin.y) <= (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMax.y) <= (posOld->y + sizeMin.y))
		{// 上からの当たり判定
			m_bHit = true;
			m_bLand = true;
			pos->y = EnemyPos.y + EnemySizeMax.y + (sizeMin.y);
			m_move->y = 0.0f;
			pos->x += EnemyMove.x;
			pos->z += EnemyMove.z;

		}
		else if ((EnemyPos.y + EnemySizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (EnemyPos.y + EnemySizeMin.y))
		{// 下からの当たり判定
			m_bHit = true;
			pos->y = posOld->y;
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y範囲確認
		if ((EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
		{// Z範囲確認
			if ((EnemyPos.x + EnemySizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (EnemyPos.x + EnemySizeMin.x))
			{// 左からの当たり判定
				m_bHit = true;
				pos->x = EnemyPos.x + EnemySizeMin.x + (sizeMin.x);
				m_move->x = 0.0f;
			}
			else if ((pos->x + sizeMin.x) <= (EnemyPos.x + EnemySizeMax.x) && (EnemyPos.x + EnemySizeMax.x) <= (posOld->x + sizeMin.x))
			{// 右からの当たり判定
				m_bHit = true;
				pos->x = EnemyPos.x + EnemySizeMax.x + (sizeMax.x);
				m_move->x = 0.0f;
			}
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y範囲確認
		if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x))
		{// X範囲確認
			if ((EnemyPos.z + EnemySizeMin.z) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (EnemyPos.z + EnemySizeMin.z))
			{// 手前からの当たり判定
				m_bHit = true;
				pos->z = EnemyPos.z + EnemySizeMin.z + (sizeMin.z);
				m_move->z = 0.0f;
			}
			else if ((pos->z + sizeMin.z) <= (EnemyPos.z + EnemySizeMax.z) && (EnemyPos.z + EnemySizeMax.z) <= (posOld->z + sizeMin.z))
			{// 後ろからの当たり判定
				m_bHit = true;
				pos->z = EnemyPos.z + EnemySizeMax.z + (sizeMax.z);
				m_move->z = 0.0f;

			}
		}
	}
}

//=============================================================================
// 敵同士の当たり判定処理
//=============================================================================
void CEnemy::OtherEnemyCollision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *m_move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	m_bOtherEnemyHit = false;	//	当たっていない
	D3DXVECTOR3 EnemyPos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 EnemyRot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 EnemySizeMax = CEnemy::Getsize(0);		//	大きさの最大値
	D3DXVECTOR3 EnemySizeMin = CEnemy::Getsize(1);		//	大きさの最小値

	if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) &&
		(pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x) &&
		(EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) &&
		(pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
	{// X/Z範囲確認
		if ((pos->y + sizeMin.y) <= (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMax.y) <= (posOld->y + sizeMin.y))
		{// 上からの当たり判定
			m_bOtherEnemyHit = true;	//	当たっている
			pos->y = EnemyPos.y + EnemySizeMax.y + (sizeMin.y);
			m_move->y = 0.0f;
		}
		else if ((EnemyPos.y + EnemySizeMin.y) <= (pos->y + sizeMax.y) && (posOld->y + sizeMax.y) <= (EnemyPos.y + EnemySizeMin.y))
		{// 下からの当たり判定
			pos->y = posOld->y;
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y範囲確認
		if ((EnemyPos.z + EnemySizeMin.z) < (pos->z + (sizeMax.z)) && (pos->z + (sizeMin.z)) < (EnemyPos.z + EnemySizeMax.z))
		{// Z範囲確認
			if ((EnemyPos.x + EnemySizeMin.x) <= (pos->x + sizeMax.x) && (posOld->x + sizeMax.x) <= (EnemyPos.x + EnemySizeMin.x))
			{// 左からの当たり判定
				m_bOtherEnemyHit = true;	//	当たっている
				pos->x = EnemyPos.x + EnemySizeMin.x + (sizeMin.x);
				m_move->x = 0.0f;
			}
			else if ((pos->x + sizeMin.x) <= (EnemyPos.x + EnemySizeMax.x) && (EnemyPos.x + EnemySizeMax.x) <= (posOld->x + sizeMin.x))
			{// 右からの当たり判定
				m_bOtherEnemyHit = true;	//	当たっている
				pos->x = EnemyPos.x + EnemySizeMax.x + (sizeMax.x);
				m_move->x = 0.0f;
			}
		}
	}
	if ((pos->y + sizeMin.y) < (EnemyPos.y + EnemySizeMax.y) && (EnemyPos.y + EnemySizeMin.y) < (pos->y + sizeMax.y))
	{// Y範囲確認
		if ((EnemyPos.x + EnemySizeMin.x) < (pos->x + (sizeMax.x)) && (pos->x + (sizeMin.x)) < (EnemyPos.x + EnemySizeMax.x))
		{// X範囲確認
			if ((EnemyPos.z + EnemySizeMin.z) <= (pos->z + sizeMax.z) && (posOld->z + sizeMax.z) <= (EnemyPos.z + EnemySizeMin.z))
			{// 手前からの当たり判定
				m_bOtherEnemyHit = true;	//	当たっている
				pos->z = EnemyPos.z + EnemySizeMin.z + (sizeMin.z);
				m_move->z = 0.0f;
			}
			else if ((pos->z + sizeMin.z) <= (EnemyPos.z + EnemySizeMax.z) && (EnemyPos.z + EnemySizeMax.z) <= (posOld->z + sizeMin.z))
			{// 後ろからの当たり判定
				m_bOtherEnemyHit = true;	//	当たっている
				pos->z = EnemyPos.z + EnemySizeMax.z + (sizeMax.z);
				m_move->z = 0.0f;
			}
		}
	}
}


//=============================================================================
// モーションの更新
//=============================================================================
void CEnemy::UpdateMotion(void)
{
	//	モーション
	KEY *pKey, *pNextKey;	//	キーと次のキー
	float fRateMotion;		//	モーションの相対値
	float fDiffMotion;		//	キーと次のキーの差分
	D3DXVECTOR3 posmotion;	//	モーションの位置
	D3DXVECTOR3 rotmotion;	//	モーションの回転

	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{//	キーが最大数を上回らないように
		m_nKey = 0;
	}

	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{//	パーツ分のモーション更新
		if (m_apModel[nCntParts] != NULL)
		{
			if (m_nMotionType == m_nMotionTypeOld)
			{//	今の種類が過去の種類が同じだった場合
			 //	現在のキーを取得
				pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
				//	次のキーを取得
				pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

				//	現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

				//	回転の算出
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	相対値を差分を使って各要素の値を算出
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

				//	位置の算出
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	相対値を差分を使って各要素の値を算出
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	相対値を差分を使って各要素の値を算出
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				//POS
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	相対値を差分を使って各要素の値を算出
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	相対値を差分を使って各要素の値を算出
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				//POS
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	相対値を差分を使って各要素の値を算出
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);

				//	パーツを動かす
				m_apModel[nCntParts]->Setrot(rotmotion);
				//	位置を設定する
				m_apModel[nCntParts]->Setpos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x, m_OffSetPos[nCntParts].y + posmotion.y, m_OffSetPos[nCntParts].z + posmotion.z));
			}
		}
	}
	//	ループの判定
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{//	ループするかしないか
	case true:

		//　ループする場合
		//	フレームを進める
		m_nCountFlame++;
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{//	キーの更新
			if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
			{//	前のキーと現在のキーが同じ場合
				m_nKey = 0;
			}
			else
			{//	現在のキーが
				m_nKey += 1;
			}
			//	フレーム数を初期化する
			m_nCountFlame = 0;
		}
		break;
	case false:
		//	ループしない
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//	フレームを進める
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{//	前のキーと現在のキーが同じ場合モーションを止める
			m_bMotionEnd = true;
		}
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{//	キーの更新
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{//	現在のキーより大きかった場合
				m_nKey += 1;	//	キーを進める
			}
			//	フレーム数を初期化する
			m_nCountFlame = 0;
		}
		break;
	}
}
//=============================================================================
// ファイル読み込み
//=============================================================================
void CEnemy::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile = NULL;		//	ファイルポインタ
	char *pStrcur;			//	現在の先頭の文字列
	char aLine[256];		//	文字列
	char aStr[256];			//	一時保存文字列
	int nIndex = 0;			//	現在のインデックス
	int nWord = 0;			//	ポップで返された値を保持

							//ファイルを開く 読み込み
	if (m_nType == 0)
	{//	種類 通常の敵
		pFile = fopen(FILE_NAME_ROBOT_000, "r");
	}
	else if (m_nType == 1)
	{//	種類　弾を撃つ敵
		pFile = fopen(FILE_NAME_ROBOT_001, "r");
	}
	else if (m_nType == 2)
	{//	種類　弾を撃つ敵
		pFile = fopen(FILE_NAME_ROBOT_002, "r");
	}
	else if (m_nType == 3)
	{//	種類　弾を撃つ敵
		pFile = fopen(FILE_NAME_ROBOT_003, "r");
	}
	else if (m_nType == 99)
	{//	種類　最後のオブジェクト
		pFile = fopen(FILE_NAME_LASTOBJ, "r");
	}
	else
	{
		pFile = fopen(FILE_NAME_ROBOT_000, "r");
	}
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_NUMMOTION; nCntMotion++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);
			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				m_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り戻す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("MODEL_FILENAME = ");
						//文字列を設定
						strcpy(aStr, pStrcur);
						//必要な文字列の最後の文字までの文字数を数える
						int nNullNum = PopString(pStrcur, &aStr[0]);
						//文字列を取り戻す
						strcpy(aStr, pStrcur);
						//最後の文字にNULL文字を入れる
						aStr[nNullNum - 1] = '\0';
						//対象の文字列から抜き出し
						strcpy(&m_aFileNameModel[nCntModel][0], aStr);
						// Xファイルの読み込み
						D3DXLoadMeshFromX(&m_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);

						D3DXMATERIAL *pmat;									// マテリアルデータへのポインタ
						D3DMATERIAL9 *matDef;								// 現在のマテリアル保存用
						pmat = (D3DXMATERIAL*)m_pBuffMatModel[nCntModel]->GetBufferPointer();
						matDef = new D3DMATERIAL9[m_nNumMatModel[nCntModel]];						//	マテリアルのメモリの確保
						m_pTextureModel[nCntModel] = new LPDIRECT3DTEXTURE9[m_nNumMatModel[nCntModel]];	//	テクスチャのメモリの確保

						for (DWORD tex = 0; tex < m_nNumMatModel[nCntModel]; tex++)
						{// カウント
							matDef[tex] = pmat[tex].MatD3D;						//　マテリアルのプロパティを記述する D3DMATERIAL9 構造体
							matDef[tex].Ambient = matDef[tex].Diffuse;			//　光の直接当たる部分の色を光を当たらない部分と同期させる
							m_pTextureModel[nCntModel][tex] = NULL;				//	テクスチャ情報を空にする
							if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
							{// テクスチャを使用している & 文字列の長さが0以上だったら
								if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTextureModel[nCntModel][tex])))
								{
								}
							}
						}
						//	マテリアルの開放
						delete[] matDef;
						matDef = NULL;
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_PARTS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEXを読み込み
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{//	番号の設定
								pStrcur += strlen("INDEX = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								nIndex = atoi(pStrcur);
							}
							//PARENTを読み込み
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{//	親の設定　
								pStrcur += strlen("PARENT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{//	オフセット位置設定
								pStrcur += strlen("POS = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{//	回転の設定
								pStrcur += strlen("ROT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);
							}
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{//	パーツの設定の終了

							 //モデルを生成	オフセット設定
								m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_aKayOffset[nIndex].fposX, m_aKayOffset[nIndex].fposY, m_aKayOffset[nIndex].fposZ),
									D3DXVECTOR3(m_aKayOffset[nIndex].frotX, m_aKayOffset[nIndex].frotY, m_aKayOffset[nIndex].frotZ));
								//位置代入
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//モデルを割り当て
								m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{//モデルの親の設定
									m_apModel[nIndex]->SetParent(NULL);
								}
								else
								{//モデルの子の設定
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}
								break;
							}
						}
					}
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{//キャラクターセット終了
						break;
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{//モーション設定
				m_nCntNumMosion += 1;			//	モーションの数の加算
												//頭出し
				pStrcur += strlen("MOTIONSET");
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{//	モーションのループするかしないか
						pStrcur += strlen("LOOP = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
					}
					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_KEY = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
						//文字列を取り出す
						strcpy(aStr, pStrcur);
					}

					//キーの設定
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{//	キーの設定
						 //頭出し
							pStrcur += strlen("KEYSET");
							//文字列の先頭を設定
							strcpy(aStr, pStrcur);
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{//	フレームの設定
								pStrcur += strlen("FRAME = ");
								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
							}
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{//パーツ分回す
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{//	キーの設定
								 //文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);
									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{//	位置の設定
									 //頭出し
										pStrcur += strlen("POS = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{//	回転の設定
									 //頭出し
										pStrcur += strlen("ROT = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{//	キーの設定の終了
									 //頭出し
										pStrcur += strlen("END_KEY");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
										//パーツのカウントを進める
										nCntParts++;
									}
								}
								else
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{//	キーの設定の終了
							 //文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
								//カウントを進める
								nCntKey++;
							}
						}
						else
						{//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{//モーションの設定の終了
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						break;
					}
				}
			}
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{//rテキストでの終了
				break;
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}

//=============================================================================
//	1行読み込み
//=============================================================================
char *CEnemy::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{//	文字列が　＃　だった場合
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{//	文字列が　\t　だった場合
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{//	while抜ける
					break;
				}
			}
			//	while抜ける
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{//	文字列が　空白　だった場合
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{//	文字列が　空白　だった場合
					pDst += strlen(" ");
				}
				else
				{//	while抜ける
					break;
				}
			}
			//	while抜ける
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{//	文字列が　\n　だった場合
			pDst += strlen("\n");
		}
		else
		{//	while抜ける
			break;
		}
	}
	//	文字列の値を返す
	return pDst;
}

//=============================================================================
//	行の先頭を取得
//=============================================================================
char * CEnemy::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{//	文字列が　空白　だった場合
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{//	文字列が　空白　だった場合
					pStr += strlen(" ");
				}
				else
				{//	while抜ける
					break;
				}
				//	while抜ける
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{//	文字列が　\t　だった場合
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{//	文字列が　\t　だった場合
					pStr += strlen("\t");
				}
				else
				{//	while抜ける
					break;
				}
			}
		}
		else
		{//	while抜ける
			break;
		}
	}
	//	文字列の値を返す
	return pStr;
}

//=============================================================================
//	行の最後を切り捨て
//=============================================================================
int CEnemy::PopString(char * pStr, char * pDest)
{
	int nStr = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nStr += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{//	文字列が　空白　だった場合
			pStr = "\0";
			nStr += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{//	文字列が　\t　だった場合
			pStr = "\0";
			nStr += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{//	文字列が　\n　だった場合
			nStr += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nStr;
}



//---------------------------------------------------------------------------
//	プレイヤーとの距離
//---------------------------------------------------------------------------
float CEnemy::GetLength(void)
{
	//	プレイヤーとの角度計算-----------------------------
	CPlayer *pPlayer = CGame::GetPlayer();				//	プレイヤーの情報の取得
	float fAngle = 0.0f;								//	角度
	float fDiffese = 0.0f;								//	差分
	D3DXVECTOR3 VecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	ベクトルの計算用
	bool bPlayerSquat = false;							//	しゃがんでいるかどうか
	float	fLength = 0;	//	長さ

	if (pPlayer != NULL && m_bLand == false)
	{
		//	プレイヤーと敵との距離を求める
		VecA = pPlayer->Getpos() - m_pos;
		//	プレイヤーと敵の角度を求める
		fAngle = atan2f(VecA.x, VecA.z);
		//	現在の角度と目的の角度の差を求める
		fDiffese = fAngle - m_fAngle;
		//	差分の修正
		if (fDiffese < -D3DX_PI)
		{
			fDiffese += D3DX_PI * 2.0f;
		}
		if (fDiffese > D3DX_PI)
		{
			fDiffese -= D3DX_PI * 2.0f;
		}
		//	角度の変化量を求める
		m_fAngle += fDiffese;
		//	角度の修正
		if (m_fAngle < -D3DX_PI)
		{
			m_fAngle += D3DX_PI * 2.0f;
		}
		if (m_fAngle > D3DX_PI)
		{
			m_fAngle -= D3DX_PI * 2.0f;
		}
		//	プレイヤーのしゃがんでいる状態の取得
		bPlayerSquat = pPlayer->GetSquat();
		if (bPlayerSquat == true)
		{//	しゃがんでいた場合
		 //	プレイヤーとの距離計算[a2 + b2 = c2]-----------------------------
			fLength = sqrtf((pPlayer->Getpos().x - m_pos.x - m_LengthDawn.x)*(pPlayer->Getpos().x - m_pos.x - m_LengthDawn.x) +
				(pPlayer->Getpos().z - m_pos.z - m_LengthDawn.z)*(pPlayer->Getpos().z - m_pos.z - m_LengthDawn.z));
			fLength *= 3;	//	長さの半減
		}
		else
		{// しゃがんでいない場合
		 //	プレイヤーとの距離計算[a2 + b2 = c2]-----------------------------
			fLength = sqrtf((pPlayer->Getpos().x - m_pos.x)*(pPlayer->Getpos().x - m_pos.x) +
				(pPlayer->Getpos().z - m_pos.z)*(pPlayer->Getpos().z - m_pos.z));
		}
	}
	//	距離の値を返す
	return fLength;
}

//***************************************************************************************************************************************
//
//		敵　ロボット　通常の処理
//
//***************************************************************************************************************************************
//#define NROBO_MAX_MOVEFORMING (0.275f)				//	追従の最大値
//#define NROBO_MAX_MOVE		 (0.125f)				//	動きの最大値

//=============================================================================
//	コンストラクタ //	親のコンストラクタから派生のコンストラクタ
//=============================================================================
CEnemyRobotNomal::CEnemyRobotNomal()
{
	m_state = STATE_NONE;						//	ステータスの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_AIEnemy = AI_NONE;						//	敵のAIの処理
	m_MosionState = MOSION_NEUTRAL;				//	モーションの状態
	m_bAttack = false;							//	攻撃したかどうか
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
	m_nEffectCounter = 0;						//	エフェクトを出すカウンター
}
//=============================================================================
//	デストラクタ
//=============================================================================
CEnemyRobotNomal::~CEnemyRobotNomal()
{

}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CEnemyRobotNomal::Init(void)
{
	//	初期化
	CEnemy::Init();
	//	値を返す
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CEnemyRobotNomal::Uninit(void)
{
	//	初期化
	CEnemy::Uninit();
}
//=============================================================================
//	更新処理
//=============================================================================
void CEnemyRobotNomal::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	位置の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値

	if (m_state == STATE_NONE)
	{//	通常の状態
	 //	動きの管理
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	追従していない場合 && 攻撃していない
			if (m_move.x <= -0.1f)
			{//	動きで向きを変える	【　左向き　】
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	動きで向きを変える	【　右向き　】
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	動きで向きを変える	【　前向き　】
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	動きで向きを変える	【　後ろ向き　】
				m_rotDest.y = D3DX_PI;
			}
		}

		ManagementMovement(m_nAISelect);
		//	モーションの設定管理
		ManagementSetMosion();
		//	加算する動きの処理
		ManagementAddRod(m_rotDest);
		//	重力
		m_move.y -= GRAVITY;
		// 移動量加算
		//pos += m_move;
		// 減速処理
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}

	//	動きの設定
	CEnemy::SetMove(m_move);
	//	動きの設定
	//CEnemy::Setpos(pos);
	//	初期化
	CEnemy::Update();
}
//=============================================================================
//	描画処理
//=============================================================================
void CEnemyRobotNomal::Draw(void)
{//	初期化
	CEnemy::Draw();

}
//=============================================================================
//	動きの総括
//=============================================================================
void CEnemyRobotNomal::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	初期の位置取得
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置取得
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値
	bool bLand = CEnemy::GetLand();				//	乗っているかの取得
	CPlayer *pPlayer = CGame::GetPlayer();		//	プレイヤーの取得
	float fDiffPosZ = pos.z - InitPos.z;		//	初期の位置から現在の位置の差分
	float fDiffPosX = pos.x - InitPos.x;		//	初期の位置から現在の位置の差分
	float fLength = CEnemy::GetLength();		//	プレイヤーとの距離の取得
											//-------------------------------------------------------
											//	nAIdata_Move = 1 　上 から 下の巡回
											//	nAIdata_Move = 2 　下 から 上の巡回
											//	nAIdata_Move = 3　左 から 右の巡回
											//	nAIdata_Move = 4 　右 から 左の巡回
											//	nAIdata_Move = 5 　上下左右の巡回
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	何もない状態だった場合
		switch (m_AIEnemy)
		{//	敵の動きの
		 //----------------------------------------
		 //	何もしてない
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	値の代入
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	プレイヤーの座標まで移動するかつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			break;
			//----------------------------------------
			//	前に進む	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	後ろに進む	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	左に進む	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	右に進む	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていた場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;			//	壁に当たっていない
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	追従する	[ プレイヤー座標 ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	プレイヤーが使われていた場合
				if (m_bPStealthMode == true || bLand == true)
				{//	ステルスブロックの中に入った場合または乗られていた場合
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	範囲内に入った場合
					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			}

			break;
			//----------------------------------------
			//	攻撃する	[ プレイヤーへ ]
			//----------------------------------------
		case AI_ATTACK:
			m_nEffectCounter++;	//	エフェクトが出力されるカウンター
			if ((m_nEffectCounter % 8) == 0)
			{//	　雷エフェクト
				CEffect::Create
				(D3DXVECTOR3(pos.x + sinf(rot.y - D3DX_PI)*30.0f, 10 + pos.y + SizeMax.y / 2, pos.z + cosf(rot.y - D3DX_PI)*30.0f), 1, 5);
			}
			if (m_bPStealthMode == true || bLand == true)
			{//	ステルスブロックの中に入った場合または乗られていた場合
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	範囲内に入った場合
				m_AIEnemy = AI_FOLLOWING;			//	追従させる
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			break;
		}
	}

	CEnemy::Setpos(pos);			//	位置の設定
}

//==============================================================================================================================
// あたり判定の作成
//==============================================================================================================================
bool  CEnemyRobotNomal::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;											//	範囲内に入ったかどうか
	D3DXVECTOR3 pos = CEnemyRobotNomal::Getpos();				//	弾の位置
	D3DXVECTOR3 size = CEnemyRobotNomal::Getsize(0);			//	弾の大きさ
	m_bAttack = false;
	//	プレイヤーとの角度
	float fAngle = atan2f(pPos->x - (m_apModel[6]->GetMtxWorld()._41- size.z/2), pPos->z - m_apModel[6]->GetMtxWorld()._43);
	// 当たるものの距離
	float fPosX = ((m_apModel[6]->GetMtxWorld()._41 - size.x / 2) - pPos->x);
	float fPosY = (m_apModel[6]->GetMtxWorld()._42 -( pPos->y+(sizeMax.y / 2)));
	float fPosZ = (m_apModel[6]->GetMtxWorld()._43 - pPos->z);

	float fRadiusA = (fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ);
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x + 15)* (sizeMax.z + 15);
	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{//	範囲内に入った場合
		bHit = true;											//	当たった
		m_bAttack = true;										//	攻撃している

	}
	//	値を返す
	return bHit;
}


//=============================================================================
//	モーションの設定管理
//=============================================================================
void CEnemyRobotNomal::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	プレイヤーの情報の取得
	float	fLength = CEnemy::GetLength();			//	プレイヤーとの距離

	switch (m_MosionState)
	{//	モーションの状態
	 //---------------------------------------------------------
	 //	ニュートラルモーション状態
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_bAttack == true)
			{//	攻撃状態
				m_nMotionType = 3;					//	攻撃モーション
				m_MosionState = MOSION_ATTACK;		//	攻撃モーションの状態
			}
			else  	if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	動いているモーション状態
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	通常状態の場合

			if (m_bAttack == true)
			{//	攻撃状態
				m_nMotionType = 3;					//	攻撃モーション6
				m_MosionState = MOSION_ATTACK;		//	攻撃モーションの状態
			}
			else if(m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	ダメージモーション状態
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		break;
		//---------------------------------------------------------
		//	攻撃モーション状態
		//---------------------------------------------------------
	case MOSION_ATTACK:
		if (m_bAttack == false)
		{
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}

		break;
	}
}


//**********************************************************************************************************************************************
//
//		敵　ロボット　弾を撃つ敵
//
//**********************************************************************************************************************************************
//#define BROBO_MAX_MOVEFORMING (0.375f)				//	追従の最大値
//#define BROBO_MAX_MOVE		 (0.225f)				//	動きの最大値

//=============================================================================
//	コンストラクタ //	親のコンストラクタから派生のコンストラクタ
//=============================================================================
CEnemyRobotBullet::CEnemyRobotBullet()
{
	m_nBulletCunter = 0;						//	弾のカウンター
	m_pBullet2D = NULL;							//	たま2D
	m_state = STATE_NONE;						//	ステータスの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_AIEnemy = AI_NONE;						//	敵のAIの処理
	m_MosionState = MOSION_NEUTRAL;				//	モーションの状態
	m_bAttack = false;							//	攻撃したかどうか
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
}
//=============================================================================
//	デストラクタ
//=============================================================================
CEnemyRobotBullet::~CEnemyRobotBullet()
{

}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CEnemyRobotBullet::Init(void)
{
	//	初期化
	CEnemy::Init();
	//	値を返す
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CEnemyRobotBullet::Uninit(void)
{

	if (m_pBullet2D != NULL)
	{//	弾が使われていた場合
		m_pBullet2D->Uninit();
		delete m_pBullet2D;
		m_pBullet2D = NULL;
	}
	//	終了処理
	CEnemy::Uninit();
}
//=============================================================================
//	更新処理
//=============================================================================
void CEnemyRobotBullet::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	位置の取得
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値

	if (m_state == STATE_NONE)
	{//	通常の状態
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	追従していない場合 && 攻撃していない
			if (m_move.x <= -0.1f)
			{//	動きで向きを変える	【　左向き　】
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	動きで向きを変える	【　右向き　】
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	動きで向きを変える	【　前向き　】
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	動きで向きを変える	【　後ろ向き　】
				m_rotDest.y = D3DX_PI;
			}
		}
	 //	動きの管理
		ManagementMovement(m_nAISelect);
		//	モーションの設定管理
		ManagementSetMosion();
		//	加算する動きの処理
		ManagementAddRod(m_rotDest);
		//	重力
		m_move.y -= GRAVITY;
		// 減速処理
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	動きの設定
	CEnemy::SetMove(m_move);
	//	更新処理
	CEnemy::Update();
}
//=============================================================================
//	描画処理
//=============================================================================
void CEnemyRobotBullet::Draw(void)
{
	//	描画処理
	CEnemy::Draw();

}
//=============================================================================
//	動きの総括
//=============================================================================
void CEnemyRobotBullet::ManagementMovement(int nAIdata_Move)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	初期の位置取得
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置取得
	bool bLand = CEnemy::GetLand();				//	乗っているかの取得
	CPlayer *pPlayer = CGame::GetPlayer();		//	プレイヤーの取得
	float fDiffPosZ = pos.z - InitPos.z;		//	初期の位置から現在の位置の差分
	float fDiffPosX = pos.x - InitPos.x;		//	初期の位置から現在の位置の差分
	float fLength = CEnemy::GetLength();		//	プレイヤーとの距離の取得
											//-------------------------------------------------------
											//	nAIdata_Move = 1 　上 から 下の巡回
											//	nAIdata_Move = 2 　下 から 上の巡回
											//	nAIdata_Move = 3　左 から 右の巡回
											//	nAIdata_Move = 4 　右 から 左の巡回
											//	nAIdata_Move = 5 　上下左右の巡回
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	何もない状態だった場合
		switch (m_AIEnemy)
		{//	敵の動きの
		 //----------------------------------------
		 //	何もしてない
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	値の代入
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	プレイヤーの座標まで移動するかつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			break;
			//----------------------------------------
			//	前に進む	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;			//	壁に当たっていない
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	後ろに進む	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	左に進む	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	右に進む	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていた場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	追従する	[ プレイヤー座標 ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	プレイヤーが使われていた場合
				if (m_bPStealthMode == true || bLand == true)
				{//	ステルスブロックの中に入った場合または乗られていた場合
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	範囲内に入った場合

					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			}

			break;
			//----------------------------------------
			//	攻撃する	[ プレイヤーへ ]
			//----------------------------------------
		case AI_ATTACK:
			if (m_bPStealthMode == true || bLand == true)
			{//	ステルスブロックの中に入った場合または乗られていた場合
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400いないだった場合
				if (pPlayer != NULL)
				{//	ロボット001
					m_nBulletCunter++;				//	弾を撃つ感覚のフレーム加算
					if (m_nBulletCunter > 40)
					{//	弾の出力
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET);	//	弾が出る音
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[2]->GetMtxWorld()._41, m_apModel[2]->GetMtxWorld()._42, m_apModel[2]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * (1.8f+ m_fFormingSpeed), 0.0f, cosf(m_fAngle) * (1.8f + m_fFormingSpeed)), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_nBulletCunter = 0;
					}
				}
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	範囲内に入った場合
				m_AIEnemy = AI_FOLLOWING;			//	追従させる
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			break;
		}
	}

	CEnemy::Setpos(pos);			//	位置の設定
}

//=============================================================================
//	モーションの設定管理
//=============================================================================
void CEnemyRobotBullet::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	プレイヤーの情報の取得
	float	fLength = CEnemy::GetLength();			//	プレイヤーとの距離

	switch (m_MosionState)
	{//	モーションの状態
	 //---------------------------------------------------------
	 //	ニュートラルモーション状態
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
			else if (m_bAttack == true)
			{//	攻撃状態
				m_nMotionType = 3;					//	攻撃モーション
				m_MosionState = MOSION_ATTACK;		//	攻撃モーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	動いているモーション状態
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			else if (m_bAttack == true && m_nAISelect == AI_ATTACK)
			{//	攻撃状態
				m_nMotionType = 3;					//	攻撃モーション6
				m_MosionState = MOSION_ATTACK;		//	攻撃モーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	ダメージモーション状態
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		break;
		//---------------------------------------------------------
		//	攻撃モーション状態
		//---------------------------------------------------------
	case MOSION_ATTACK:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
		{//	移動していない場合
			m_nMotionType = 0;					//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	移動していた場合
			m_nMotionType = 1;					//	移動モーション
			m_MosionState = MOSION_MOVE;		//	移動モーションの状態
		}
		break;
	}
}

//**********************************************************************************************************************************************
//
//		敵　ロボット　棘の敵
//
//**********************************************************************************************************************************************
//#define SROBO_MAX_MOVEFORMING (0.575f)				//	追従の最大値
//#define SROBO_MAX_MOVE		 (0.295f)				//	動きの最大値

//=============================================================================
//	コンストラクタ //	親のコンストラクタから派生のコンストラクタ
//=============================================================================
CEnemyRobotSpine::CEnemyRobotSpine()
{
	m_state = STATE_NONE;						//	ステータスの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_AIEnemy = AI_NONE;						//	敵のAIの処理
	m_MosionState = MOSION_NEUTRAL;				//	モーションの状態
	m_bAttack = false;							//	攻撃したかどうか
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
	m_fAddRot = 0.0f;							//	回転の加算
}
//=============================================================================
//	デストラクタ
//=============================================================================
CEnemyRobotSpine::~CEnemyRobotSpine()
{

}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CEnemyRobotSpine::Init(void)
{
	//	初期化
	CEnemy::Init();
	//	値を返す
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CEnemyRobotSpine::Uninit(void)
{
	//	終了処理
	CEnemy::Uninit();
}
//=============================================================================
//	更新処理
//=============================================================================
void CEnemyRobotSpine::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	位置の取得
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値
	if (m_state == STATE_NONE)
	{//	通常の状態
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	追従していない場合 && 攻撃していない
			if (m_move.x <= -0.1f)
			{//	動きで向きを変える	【　左向き　】
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	動きで向きを変える	【　右向き　】
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	動きで向きを変える	【　前向き　】
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	動きで向きを変える	【　後ろ向き　】
				m_rotDest.y = D3DX_PI;
			}
		}
	 //	動きの管理
		ManagementMovement(m_nAISelect);
		//	モーションの設定管理
		ManagementSetMosion();
		//	加算する動きの処理
		ManagementAddRod(m_rotDest);
		//	重力
		m_move.y -= GRAVITY;
		// 減速処理
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	動きの設定
	CEnemy::SetMove(m_move);
	//	更新処理
	CEnemy::Update();

	m_fAddRot++;
	if (m_apModel[2] != NULL || m_apModel[3] != NULL)
	{
		//	パーツを動かす
		m_apModel[2]->Setrot(D3DXVECTOR3(0.0f, m_fAddRot, 0.0f));
		m_apModel[3]->Setrot(D3DXVECTOR3(0.0f, m_fAddRot, 0.0f));
	}
}
//=============================================================================
//	描画処理
//=============================================================================
void CEnemyRobotSpine::Draw(void)
{
	//	描画処理
	CEnemy::Draw();

}
//=============================================================================
//	動きの総括
//=============================================================================
void CEnemyRobotSpine::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	初期の位置取得
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置取得

	CPlayer *pPlayer = CGame::GetPlayer();		//	プレイヤーの取得
	float fDiffPosZ = pos.z - InitPos.z;	//	初期の位置から現在の位置の差分
	float fDiffPosX = pos.x - InitPos.x;	//	初期の位置から現在の位置の差分

	float fLength = CEnemy::GetLength();	//	プレイヤーとの距離の取得
											//-------------------------------------------------------
											//	nAIdata_Move = 1 　上 から 下の巡回
											//	nAIdata_Move = 2 　下 から 上の巡回
											//	nAIdata_Move = 3　左 から 右の巡回
											//	nAIdata_Move = 4 　右 から 左の巡回
											//	nAIdata_Move = 5 　上下左右の巡回
											//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	何もない状態だった場合
		switch (m_AIEnemy)
		{//	敵の動きの
		 //----------------------------------------
		 //	何もしてない
		 //----------------------------------------
		case AI_NONE:
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	値の代入
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false)
			{//	プレイヤーの座標まで移動する // プレイヤーがステルス状態に入っていた場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			break;
			//----------------------------------------
			//	前に進む	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			m_move.z += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false)
			{//	範囲内に入った場合// プレイヤーがステルス状態に入っていた場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	後ろに進む	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			m_move.z -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	範囲内に入った場合// プレイヤーがステルス状態に入っていた場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			 if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true)
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	左に進む	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			m_move.x += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	範囲内に入った場合// プレイヤーがステルス状態に入っていた場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	右に進む	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			m_move.x -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false)
			{//	範囲内に入った場合// プレイヤーがステルス状態に入っていた場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*1.5f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	追従する	[ プレイヤー座標 ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	プレイヤーが使われていた場合
				if (m_bPStealthMode == true)
				{//	ステルスブロックの中に入った場合
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	範囲内に入った場合
					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			}

			break;
			//----------------------------------------
			//	攻撃する	[ プレイヤーへ ]
			//----------------------------------------
		case AI_ATTACK:
			if (m_bPStealthMode == true)
			{//	ステルスブロックの中に入った場合
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400いないだった場合

			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	範囲内に入った場合
				m_AIEnemy = AI_FOLLOWING;			//	追従させる
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			break;
		}
	}

	CEnemy::Setpos(pos);			//	位置の設定
}

//=============================================================================
//	モーションの設定管理
//=============================================================================
void CEnemyRobotSpine::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	プレイヤーの情報の取得
	float	fLength = CEnemy::GetLength();			//	プレイヤーとの距離

	switch (m_MosionState)
	{//	モーションの状態
	 //---------------------------------------------------------
	 //	ニュートラルモーション状態
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	動いているモーション状態
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	ダメージモーション状態
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		break;
	}
}
//==============================================================================================================================
// あたり判定の作成
//==============================================================================================================================
bool  CEnemyRobotSpine::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove, D3DXVECTOR3 *rot, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	bool bHit = false;
	D3DXVECTOR3 pos = CEnemyRobotSpine::Getpos();				//	弾の位置
	D3DXVECTOR3 size = CEnemyRobotSpine::Getsize(0);			//	弾の大きさ
	//	プレイヤーとの角度
	float fAngle = atan2f(pPos->x - pos.x, pPos->z - pos.z);
	// 当たるものの距離
	float fPosX = (pos.x - pPos->x);
	float fPosY = (pos.y - pPos->y);
	float fPosZ = (pos.z - pPos->z);

	float fRadiusA =( fPosX*fPosX + fPosY*fPosY + fPosZ*fPosZ);
	float fRadiusB = 0;
	fRadiusB = (sizeMax.x*1.5f + size.x)* (sizeMax.z*1.5f + size.z);
	if (fRadiusB > fRadiusA&&-fRadiusB < fRadiusA)
	{
		bHit = true;
	}

	return bHit;
}


//**********************************************************************************************************************************************
//
//		敵　ロボット　si下に弾を弾を撃つ敵
//
//**********************************************************************************************************************************************
//#define UROBO_MAX_MOVEFORMING (0.825f)				//	追従の最大値
//#define UROBO_MAX_MOVE		 (0.225f)				//	動きの最大値
#define UROBO_MAX_POS		(150)					//	上がってくる最大位置
#define UROBO_POS			(30)						//	上がってくる位置
#define UROBO_MOVE_Y			(0.55f)					//	縦の動き
#define UROBO_MAX_MOVE_Y		(0.65f)				//	縦の最大の動き


//=============================================================================
//	コンストラクタ //	親のコンストラクタから派生のコンストラクタ
//=============================================================================
CEnemyRobotUndeBulletr::CEnemyRobotUndeBulletr()
{
	m_nBulletCunter = 0;						//	弾のカウンター
	m_pBullet2D = NULL;							//	たま2D
	m_state = STATE_NONE;						//	ステータスの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_AIEnemy = AI_NONE;						//	敵のAIの処理
	m_MosionState = MOSION_NEUTRAL;				//	モーションの状態
	m_bAttack = false;							//	攻撃したかどうか
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
	m_fAddPos = 0.0f;							//	位置の加算
	m_nEffectCounter = 0;					//	エフェクトが出るカウンタ
}
//=============================================================================
//	デストラクタ
//=============================================================================
CEnemyRobotUndeBulletr::~CEnemyRobotUndeBulletr()
{

}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CEnemyRobotUndeBulletr::Init(void)
{
	//	初期化
	CEnemy::Init();
	//	値を返す
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CEnemyRobotUndeBulletr::Uninit(void)
{
	if (m_pBullet2D != NULL)
	{//	弾が使われていた場合
		m_pBullet2D->Uninit();
		delete m_pBullet2D;
		m_pBullet2D = NULL;
	}
	//	終了処理
	CEnemy::Uninit();
}
//=============================================================================
//	更新処理
//=============================================================================
void CEnemyRobotUndeBulletr::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	位置の取得
	D3DXVECTOR3 rot = CEnemy::Getrot();			//	回転の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値

	if (m_state == STATE_NONE)
	{//	通常の状態
		if (m_AIEnemy != AI_FOLLOWING &&m_AIEnemy != AI_ATTACK)
		{//	追従していない場合 && 攻撃していない
			if (m_move.x <= -0.1f)
			{//	動きで向きを変える	【　左向き　】
				m_rotDest.y = D3DX_PI * 0.5f;
			}
			if (m_move.x >= 0.1f)
			{//	動きで向きを変える	【　右向き　】
				m_rotDest.y = -D3DX_PI * 0.5f;
			}
			if (m_move.z <= -0.1f)
			{//	動きで向きを変える	【　前向き　】
				m_rotDest.y = 0.0f;
			}
			if (m_move.z >= 0.1f)
			{//	動きで向きを変える	【　後ろ向き　】
				m_rotDest.y = D3DX_PI;
			}
		}
		m_nEffectCounter++;	//	エフェクトが出力されるカウンター
		if ((m_nEffectCounter % 15) == 0)
		{//	炎のエフェクト
			CEffect::Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42-5, m_apModel[0]->GetMtxWorld()._43), 1, 4);
		}

		//	動きの管理
		ManagementMovement(m_nAISelect);
		//	モーションの設定管理
		ManagementSetMosion();
		//	加算する動きの処理
		ManagementAddRod(m_rotDest);
		//	重力
		m_move.y -= 0.45f;
		// 減速処理
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}
	//	動きの設定
	CEnemy::SetMove(m_move);
	//	更新処理
	CEnemy::Update();
}
//=============================================================================
//	描画処理
//=============================================================================
void CEnemyRobotUndeBulletr::Draw(void)
{
	//	描画処理
	CEnemy::Draw();

}
//=============================================================================
//	動きの総括
//=============================================================================
void CEnemyRobotUndeBulletr::ManagementMovement(int nAIdata_Move)
{
	D3DXVECTOR3 InitPos = CEnemy::GetInitpos();	//	初期の位置取得
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置取得
	bool bLand = CEnemy::GetLand();				//	乗っているかの取得
	CPlayer *pPlayer = CGame::GetPlayer();		//	プレイヤーの取得
	float fDiffPosZ = pos.z - InitPos.z;		//	初期の位置から現在の位置の差分
	float fDiffPosX = pos.x - InitPos.x;		//	初期の位置から現在の位置の差分
	float fLength = CEnemy::GetLength();		//	プレイヤーとの距離の取得
												//-------------------------------------------------------
												//	nAIdata_Move = 1 　上 から 下の巡回
												//	nAIdata_Move = 2 　下 から 上の巡回
												//	nAIdata_Move = 3　左 から 右の巡回
												//	nAIdata_Move = 4 　右 から 左の巡回
												//	nAIdata_Move = 5 　上下左右の巡回
												//-------------------------------------------------------

	if (m_state == STATE_NONE)
	{//	何もない状態だった場合
		switch (m_AIEnemy)
		{//	敵の動きの
		 //----------------------------------------
		 //	何もしてない
		 //----------------------------------------
		case AI_NONE:
			if (pos.y <= 50)
			{//	位置が50以上なら
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			m_AIEnemy = (ENEMY_AI)nAIdata_Move;		//	値の代入
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	プレイヤーの座標まで移動するかつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			break;
			//----------------------------------------
			//	前に進む	[ Z+ ]
			//----------------------------------------
		case AI_UP:
			if (pos.y <= UROBO_POS)
			{//	位置が50以上なら
				m_move.y += 1.00f;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			m_move.z += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE  &&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_DOWN;
				m_move.z -= m_fNoneSpeed*2.0f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_DOWN;
			}

			break;
			//----------------------------------------
			//	後ろに進む	[ Z- ]
			//----------------------------------------
		case AI_DOWN:
			if (pos.y <= UROBO_POS)
			{//	位置が50以上なら
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			m_move.z -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if(m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_UP;
				m_move.z += m_fNoneSpeed*2.0f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosZ < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_UP;
			}
			break;
			//----------------------------------------
			//	左に進む	[ X+ ]
			//----------------------------------------
		case AI_LEFT:
			if (pos.y <= UROBO_POS)
			{//	位置が50以上なら
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			m_move.x += m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていない場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_RIGHT;
				m_move.x -= m_fNoneSpeed*2.0f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX > m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_RIGHT;
			}
			break;
			//----------------------------------------
			//	右に進む	[ X- ]
			//----------------------------------------
		case AI_RIGHT:
			if (pos.y <= UROBO_POS)
			{//	位置が50以上なら
				m_move.y += UROBO_MOVE_Y;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			m_move.x -= m_fNoneSpeed;				//	動きの加算
			if (fLength < HOMINGRANGE&&m_bPStealthMode == false && bLand == false)
			{//	範囲内に入った場合かつプレイヤーがステルス状態に入っていた場合かつ乗られていなかった場合
				m_AIEnemy = AI_FOLLOWING;	//	追従させる
				if (m_move.y < 0.1f)
				{//	飛んでいなかった場合
					m_move.y += 6.35f;			//	ジャンプさせる
				}
			}
			if (m_bWallHit == true)
			{//	壁に当たった
				m_AIEnemy = AI_LEFT;
				m_move.x += m_fNoneSpeed*2.0f;	//	動きの加算
				m_bWallHit = false;		//	壁に当たっていない
			}
			else if (fDiffPosX < -m_nMoveLength || m_bOtherEnemyHit == true )
			{//	差分で動きを変えるまたは敵同士当たった場合
				m_AIEnemy = AI_LEFT;
			}
			break;
			//----------------------------------------
			//	追従する	[ プレイヤー座標 ]
			//----------------------------------------
		case AI_FOLLOWING:
			if (pPlayer != NULL)
			{//	プレイヤーが使われていた場合
				if (pos.y <= UROBO_MAX_POS)
				{//	位置が50以上なら
					m_move.y += UROBO_MAX_MOVE_Y;
				}
				else
				{//	それ以外の場合
					m_move.y = 0.0f;
				}
				if (m_bPStealthMode == true || bLand == true)
				{//	ステルスブロックの中に入った場合または乗られていた場合
					m_AIEnemy = AI_NONE;
				}
				else if (fLength < HOMINGRANGE + m_nMoveLength)
				{//	範囲内に入った場合

					m_AIEnemy = AI_ATTACK;
				}
				else if (fLength > HOMINGRANGE + m_nMoveLength)
				{
					m_AIEnemy = AI_NONE;
				}

				m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
				m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
				m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			}

			break;
			//----------------------------------------
			//	攻撃する	[ プレイヤーへ ]
			//----------------------------------------
		case AI_ATTACK:
			if (pos.y <= UROBO_MAX_POS)
			{//	位置が50以上なら
				m_move.y += UROBO_MAX_MOVE_Y;
			}
			else
			{//	それ以外の場合
				m_move.y = 0.0f;
			}
			if (m_bPStealthMode == true || bLand == true)
			{//	ステルスブロックの中に入った場合または乗られていた場合
				m_AIEnemy = AI_NONE;
			}
			else if (fLength < HOMINGRANGE * 2)
			{//	400いないだった場合
				if (pPlayer != NULL)
				{//	ロボット001
					m_nBulletCunter++;				//	弾を撃つ感覚のフレーム加算
					if (m_nBulletCunter > 40)
					{//	弾の出力
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * 1.0f,-3.5f, cosf(m_fAngle) * 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_pBullet2D->Create(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43),
							D3DXVECTOR3(sinf(m_fAngle) * 0.0f, -3.5f, cosf(m_fAngle) * 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
							D3DXVECTOR2(1.0f, 1.0f), 240, CBullet2D::TYPE_BULT000);
						m_nBulletCunter = 0;
					}
				}
			}
			else if (fLength < HOMINGRANGE + m_nMoveLength / 2 && m_bPStealthMode == false)
			{//	範囲内に入った場合
				m_AIEnemy = AI_FOLLOWING;			//	追従させる
			}
			else if (fLength > HOMINGRANGE + m_nMoveLength / 2)
			{
				m_AIEnemy = AI_NONE;
			}
			m_rotDest.y = (D3DX_PI - m_fAngle)*-1;	//	角度をプレイヤーに向ける
			m_move.x += sinf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			m_move.z += cosf(m_fAngle) * m_fFormingSpeed;	//	動きの加算
			break;
		}
	}

	CEnemy::Setpos(pos);			//	位置の設定
}

//=============================================================================
//	モーションの設定管理
//=============================================================================
void CEnemyRobotUndeBulletr::ManagementSetMosion(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();			//	プレイヤーの情報の取得
	float	fLength = CEnemy::GetLength();			//	プレイヤーとの距離

	switch (m_MosionState)
	{//	モーションの状態
	 //---------------------------------------------------------
	 //	ニュートラルモーション状態
	 //---------------------------------------------------------
	case MOSION_NEUTRAL:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	動いているモーション状態
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
		}
		else if (m_state == STATE_DAMAGE)
		{//	ダメージ状態の場合
			m_nMotionType = 2;						//	ダメージモーション
			m_MosionState = MOSION_DAMEGA;			//	ダメージモーションの状態
		}
		break;
		//---------------------------------------------------------
		//	ダメージモーション状態
		//---------------------------------------------------------
	case MOSION_DAMEGA:
		if (m_state == STATE_NONE)
		{//	通常状態の場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;					//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			}
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合
				m_nMotionType = 1;					//	移動モーション
				m_MosionState = MOSION_MOVE;		//	移動モーションの状態
			}
		}
		break;
	}
}
//***************************************************************************************************************************************
//
//		最後のオブジェクト
//
//***************************************************************************************************************************************


//=============================================================================
//	コンストラクタ //	親のコンストラクタから派生のコンストラクタ
//=============================================================================
CEnemyLastObj::CEnemyLastObj()
{
	m_state = STATE_NONE;						//	ステータスの初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
	m_nEffectCounter = 0;						//	エフェクトを出すカウンター
}
//=============================================================================
//	デストラクタ
//=============================================================================
CEnemyLastObj::~CEnemyLastObj()
{

}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CEnemyLastObj::Init(void)
{
	//	初期化
	CEnemy::Init();
	//	値を返す
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CEnemyLastObj::Uninit(void)
{


	//	初期化
	CEnemy::Uninit();
}
//=============================================================================
//	更新処理
//=============================================================================
void CEnemyLastObj::Update(void)
{
	D3DXVECTOR3 pos = CEnemy::Getpos();			//	位置の取得
	D3DXVECTOR3 posOld = CEnemy::GetposOld();	//	位置の取得
	D3DXVECTOR3 SizeMax = CEnemy::Getsize(0);	//	大きさの最大値
	D3DXVECTOR3 SizeMin = CEnemy::Getsize(1);	//	大きさの最小値

	if (m_state == STATE_NONE)
	{//	通常の状態
	 //	動きの管理
		//	加算する動きの処理
		ManagementAddRod(m_rotDest);
		//	重力
		m_move.y -= GRAVITY;
		// 移動量加算
		//pos += m_move;
		// 減速処理
		m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
		m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	}

	//	動きの設定
	CEnemy::SetMove(m_move);
	//	初期化
	CEnemy::Update();
}
//=============================================================================
//	描画処理
//=============================================================================
void CEnemyLastObj::Draw(void)
{//	初期化
	CEnemy::Draw();
}
