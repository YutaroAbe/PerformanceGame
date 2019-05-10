//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "player.h"			// プレイヤー
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
#include "enemy.h"			// 敵
#include "bullet2D.h"		// 弾2D
#include "block.h"			//	ブロック
#include "bulletNumber.h"
#include "UI.h"				//	UI
#include "sound.h"			//	サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME						("data\\TEXT\\player\\motion.txt")		//	読み込むテキストの名前
#define GRAVITY							(0.7f)									//	重力
#define WALK_SPEED						(0.95f)									//	歩くスピード
#define MOVE_DOWNSPEED_NOR				(0.25f)									//	減速スピード
#define MOVE_UPSPEED					(1.05f)									//	増速スピード

#define ATTACK_COLL_EXPAND_Z_000		(20)									//	攻撃判定の敵の判定の拡大率 1段目
#define ATTACK_COLL_EXPAND_X_000		(20)									//	攻撃判定の敵の判定の拡大率 1段目
#define ATTACK_COLL_EXPAND_Y_000		(10)									//	攻撃判定の敵の判定の拡大率 1段目
#define ATTACK_COLL_EXPAND_Z_001		(20)									//	攻撃判定の敵の判定の拡大率 2段目
#define ATTACK_COLL_EXPAND_X_001		(20)									//	攻撃判定の敵の判定の拡大率 2段目
#define ATTACK_COLL_EXPAND_Y_001		(25)									//	攻撃判定の敵の判定の拡大率 2段目


//*****************************************************************************
//	静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH					CPlayer::m_pMesh[MAX_NUMPARTS] = {};
LPD3DXBUFFER				CPlayer::m_pBuffMat[MAX_NUMPARTS] = {};
LPDIRECT3DTEXTURE9			*CPlayer::m_pTexture[MAX_NUMPARTS] = {};
DWORD						CPlayer::m_nNumMat[MAX_NUMPARTS] = {};
int							CPlayer::m_nNumParts = 0;
//=============================================================================
//プレイヤークラス コンストラクタ
//=============================================================================
CPlayer::CPlayer() : CScene(PRIORITY_4, CScene::OBJTYPE_PLAYER)
{
	m_bJump = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	前回の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	向き
	m_state = STATE_NONE;						//	状態
	D3DXMatrixIdentity(&m_mtxWorld);			//	ワールドマトリックス
	m_pKeyInfo[MAX_NUMMOTION] = {};				//	キー情報へのポインタ
	m_nKey = 0;									//	現在のキーナンバー
	m_nCountFlame = 0;							//	フレーム
	m_bMotionEnd = false;						//	モーションの終了
	m_nMotionType = 0;							//	現在のモーションタイプ
	m_bMove = false;							//	動いている
	m_bBlock = false;							//	ブロックに当たっているか
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	プレイヤーの大きさの最大値
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	プレイヤーの大きさの最小値
	m_MosionState = MOSION_NEUTRAL;				//	ニュートラルモーション
	m_nCouterFreamMax[MAX_NUMMOTION] = {};		//	モーションのフレームの合計値
	m_bSquat = false;							//	しゃがんでいる状態
	m_nCntNumMosion = 0;						//	テキストに書かれているモーションの数
	m_fMoveControl = 0.0f;						//	移動の変化
	m_nMotionTypeOld = 0;						//	モーションの過去の種類
	m_pBullet3D = NULL;							//	弾のポインタ変数
	m_pOrbit = NULL;							//	軌跡のポインタ変数
	m_pShadow = NULL;							//	影のポインタ変数
	m_pBlock = NULL;							//	ブロックのポインタ変数
	m_bAttack = false;							//	攻撃中かどうか
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	目的の向き
	m_bJump = false;							//	ジャンプ状態
	m_nAtkFream = 0;							//	攻撃のコリジョンがでるタイミング
	m_bAtkLastHit = false;						//	最後の攻撃に当たったかどうか
	m_nAtkCombFream = 0;						//	コンボできるフレーム
	m_bDisp = false;							//	死んだ状態
	m_bDamage = false;							//	ダメージ状態
	m_nStateCounter = 0;						//	ステータスのカウンター
	m_bStealthMode = false;						//	ステルスモード
	m_bLifeState[0] = false;					//	体力の変化ダメージ
	m_bLifeState[1] = false;					//	体力の変化回復
	m_nBltCut = 0;								//	弾の弾数
	m_nStealthLife = 0;							//	ステルス出来るカウンター状態
	m_nStealthCut = 0;
	m_nLifeInit = 0;							//	初期の体力
	m_bStlBlockHitIn = false;					//	ステルスブロックの中に入った
	m_nNumBlock = 0;							//	ステルスブロックの数
	m_nInvincible = 0;							//	無敵状態のカウンター
	m_nDashLife = 0;							//	ダッシュできる寿命
	m_nDashCut = 0;								//	ダッシュ状態に戻るカウンター
	m_bDash = false;							//	ダッシュしているかどうか
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, int nBltCut, int nStealthLife,int nDashLife)
{
	//プレイヤーポインタ
	CPlayer *pPlayer = {};
	if (pPlayer == NULL)
	{//	プレイヤーが使われていなかった場合
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{//	初期化
			pPlayer->m_nDashLife = nDashLife;		//	dashできる寿命
			pPlayer->m_nStealthLife = nStealthLife;	//	ステルス出来る寿命
			pPlayer->m_nBltCut = nBltCut;			//	弾の弾数
			pPlayer->m_pos = pos;					//	位置の設定
			pPlayer->m_rot = rot;					//	回転の設定
			pPlayer->m_nLife = nLife;				//	寿命
			pPlayer->Init();						//	初期化処理
		}
	}
	//プレイヤーの情報を返す
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//プレイヤー情報の読み込み
	FileLoad();
	// 拡大縮小用変数
	m_fScaleX = 2.0f, m_fScaleY = 2.0f, m_fScaleZ = 2.0f;
	// 判定設定
	m_vtxMax = D3DXVECTOR3(10.0f *m_fScaleX, 35.0f*m_fScaleY, 10.0f*m_fScaleZ);
	m_vtxMin = D3DXVECTOR3(-10.0f*m_fScaleX, 0.0f*m_fScaleY, -10.0f*m_fScaleZ);

	//	影の生成
	if (m_pShadow == NULL)
	{//	影が使われていなかったら
		m_pShadow = CShadow::Create(m_pos, m_rot, D3DXVECTOR3(m_vtxMax.x, 0.0f, m_vtxMax.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	if (m_pBlock == NULL)
	{//	ブロックが使われていなかったら
		m_pBlock = CBlock::Create(D3DXVECTOR3(m_apModel[1]->GetMtxWorld()._41, m_apModel[1]->GetMtxWorld()._42, m_apModel[1]->GetMtxWorld()._43),
			m_rot, D3DXVECTOR3(0.5f, 0.5f, 0.5f), CBlock::MODELTYPE_GIRISUTU, CBlock::COLTYPE_NONE);
	}
	for (int nCnterMosion = 0; nCnterMosion < MAX_NUMMOTION; nCnterMosion++)
	{//	モーションの確保回す
		if (m_nCntNumMosion >= nCnterMosion)
		{//	モーションのテキストに書かれている種類分回す
			for (int nCounter = 0; nCounter < m_aMotionInfo[nCnterMosion].nNumKey; nCounter++)
			{//	投げるモーションのキー数分回す
				m_nCouterFreamMax[nCnterMosion] += m_aMotionInfo[nCnterMosion].aKayInfo[nCounter].nFrame;
			}
		}
	}
	m_MosionState = MOSION_NEUTRAL;				//	ニュートラルモーション
	m_nMotionType = 0;							//	モーションの種類
	m_bJump = false;							//	ジャンプ状態
	m_bAttack = false;							//	攻撃状態
	m_bSquat = false;							//	しゃがんでいる状態
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	向き
	m_bMove = true;								//	動ける状態
	m_nLifeInit = m_nLife;						//	初期の体力の設定
	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
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
	CGame::SetPlayer();

	// フラグを立てる
	CScene::SetDeath();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 位置保存
	m_posOld = m_pos;
	//	モーションの保存
	m_nMotionTypeOld = m_nMotionType;

	// 判定設定
	m_vtxMax = D3DXVECTOR3(10.0f *m_fScaleX, 33.0f*m_fScaleY, 10.0f*m_fScaleZ);
	m_vtxMin = D3DXVECTOR3(-10.0f*m_fScaleX, 0.0f*m_fScaleY, -10.0f*m_fScaleZ);

	switch (m_state)
	{// 状態
		//-----------------------------------------
		//	通常
		//-----------------------------------------
	case STATE_NONE:
		//	動きの管理
		ManagementMovement();
		//	加算する動きの処理
		ManagementAddMovement();
		break;
		//-----------------------------------------
		// ダメージ
		//-----------------------------------------
	case STATE_DAMAGE:
		m_bDamage = true;				//	ダメージ状態
		m_nStateCounter++;
		if (m_nStateCounter > 30)
		{//	カウンターが指定の値を超えた場合
			m_state = STATE_INVINCIBLE;	//	無敵状態にする
			m_bDamage = false;			//	ダメージ状態を戻す
			m_nStateCounter = 0;		//	カウンター初期化
		}
		break;
		//-----------------------------------------
		// 無敵状態
		//-----------------------------------------
	case STATE_INVINCIBLE:
		m_nInvincible++;
		//	動きの管理
		ManagementMovement();
		//	加算する動きの処理
		ManagementAddMovement();
		if (m_nInvincible > 50)
		{//	カウンターが指定の値を超えた場合
			m_state = STATE_NONE;		//	通常状態に戻す
			m_nInvincible = 0;
		}
		break;
		//-----------------------------------------
		// 死亡
		//-----------------------------------------
	case STATE_DEATH:
		m_bDisp = true;					//	死んでいる状態
		break;
	}
	//	当たり判定の管理
	ManagementCollision();
	//	モーションの設定管理
	ManagementSetMosion();
#ifdef _DEBUG
	CManager::m_CDebugProcRight->Print("\n----------プレイヤーのステータス------------------");
	CManager::m_CDebugProcRight->Print("\nプレイヤーの位置  ( %.1f : %.1f  : %.1f)", m_pos.x, m_pos.y, m_pos.z);
	CManager::m_CDebugProcRight->Print("\nプレイヤーの動き　( %.1f : %.1f  : %.1f)", m_move.x, m_move.y, m_move.z);
	CManager::m_CDebugProcRight->Print("\nプレイヤーの向き　( %.1f : %.1f  : %.1f)", m_rot.x, m_rot.y, m_rot.z);
	CManager::m_CDebugProcRight->Print("\nMAX　( %.1f : %.1f  : %.1f)", m_vtxMax.x, m_vtxMax.y, m_vtxMax.z);
	CManager::m_CDebugProcRight->Print("\nMIN　( %.1f : %.1f  : %.1f)", m_vtxMin.x, m_vtxMin.y, m_vtxMin.z);
	CManager::m_CDebugProcRight->Print("\nスケール値　( %.1f : %.1f  : %.1f)", m_fScaleX, m_fScaleY, m_fScaleZ);
	CManager::m_CDebugProcRight->Print("\n体力　( %d)", m_nLife);
	CManager::m_CDebugProcRight->Print("\n-------------------------------------------------");
#endif
	if (m_pShadow != NULL)
	{//	影が使われていたら
		if (m_bBlock == true)
		{//	ブロックに当たっていた場合影をPOSY座標に移動させる
			//	影の位置の設定
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_pos.y, m_apModel[0]->GetMtxWorld()._43));
		}
		else
		{//	ブロックに当たっていない場合地面に
			m_pShadow->Setpos(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, 0.5f, m_apModel[0]->GetMtxWorld()._43));
		}
	}

	//モーション更新
	UpdateMotion();
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
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
	D3DXMatrixScaling(&matScale, m_fScaleX, m_fScaleY, m_fScaleZ);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &matScale);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//影の描画処理
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);
	//	ライトの設定
	VecLight = D3DXVECTOR4(0.0f,1.0f, 0.0f, 0.0f);
	//	影の位置設定
	pos = D3DXVECTOR3(0.0f, m_pShadow->Getpos().y, 0.0f);
	//	法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//	影マトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//	ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//	ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	//{//	パーツ分描画する
	//	if (m_apModel[nCnt] != NULL)
	//	{//	描画の処理リ
	//		m_apModel[nCnt]->Draw();
	//	}
	//}
	//	レンダーステイトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	 //ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_state == STATE_INVINCIBLE)
	{//	無敵状態だった場合
		if ((m_nInvincible % 12) == 0)
		{//	点滅させる
			for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
			{//	パーツ分回す
				if (m_apModel[nCnt] != NULL)
				{//	描画処理
					m_apModel[nCnt]->Draw();
				}
			}
		}
	}
	else
	{//	それ以外の状態
		for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
		{//	パーツ分回す
			if (m_apModel[nCnt] != NULL)
			{//	描画処理
				m_apModel[nCnt]->Draw();
			}
		}
	}
}


//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	return S_OK;
}

//=============================================================================
// 破棄処理
//=============================================================================
void CPlayer::UnLoad(void)
{
	for (int nCntIndex = 0; nCntIndex < m_nNumParts; nCntIndex++)
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
//	動きの総括
//=============================================================================
void CPlayer::ManagementMovement(void)
{
	//	カメラの回転の取得
	D3DXVECTOR3 cameraRot = CCamera::GetCameraRotate();

	if (m_bJump == false)
	{//	ジャンプしていない
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_SPACE) == true && m_nCntMosionChange <= 0 || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
		{//	スペースキーを押した　＆＆　着地モーションしていなかった場合
		 //	移動処理
			m_move.y += 12.0f;
			//	ジャンプ中
			m_bJump = true;
		}
	}
	else if (m_bJump == true)
	{//	ジャンプ中
		if (m_move.y <= 0.1f && m_move.y >= -0.1f)
		{//	ジャンプしていない
			m_bJump = false;
		}
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_X, 0) == true)
	{//	攻撃モーション
		m_bAttack = true;
	}

	//	チュートリアルの表記終わったかどうか
	bool bTuto = false;
	if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
	{//	チュートリアルの場合
		bTuto = CUI::GetTutoEnd();	//	チュートリアルが終わったかどうか
	}
	else
	{//	チュートリアル以外の場合
		bTuto = true;	//	チュートリアルが終わったかどうか
	}

	if ((CManager::GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::GetInputXPad()->GetPress(XINPUT_GAMEPAD_LEFT_SHOULDER, 0) == true ) &&
		m_nStealthLife > 0&&m_bJump ==false&&m_bAttack ==false && bTuto ==true)
	{
	 //	ボタンの押し込み　ステルスの寿命がある　ジャンプしてない　攻撃していない
		m_bSquat = true;
		//	移動が遅くなる
		m_fMoveControl = -(WALK_SPEED / 1.5f);
		if (m_pBlock != NULL)
		{//	ブロックが使われていたら
			m_pBlock->Setpos(D3DXVECTOR3(m_apModel[1]->GetMtxWorld()._41, m_apModel[1]->GetMtxWorld()._42 + 8, m_apModel[1]->GetMtxWorld()._43));
			m_pBlock->Setrot(m_rot);
			m_pBlock->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
		}
		if (m_nStealthLife > 0)
		{//	0以上なら寿命減らす
			m_nStealthLife--;
		}
	}
	else if ((CManager::GetInputKeyboard()->GetPress(DIK_N) == true ||
		CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_TRIGGER_LEFT, 0) == true)&&
		m_nDashLife > 0 && m_bJump == false && m_bAttack == false && bTuto == true)
	{//	Zキー　// L トリガー
		m_bDash = true;		//	ダッシュしている
		//	移動が早くなる
		m_fMoveControl = MOVE_UPSPEED;

		if (m_nDashLife > 0)
		{//	ダッシュのジュミョウ減らす
			m_nDashLife--;
		}
	}
	else
	{//	しゃがんでいない状態
		m_bSquat = false;
		// しゃがみ中じゃない時は移動遅くしない
		m_fMoveControl = 0.0f;
		m_bDash = false;		//	ダッシュしていない
	}

		if (m_bSquat == false|| m_bDamage == true)
		{
			if (m_pBlock != NULL)
			{//	ブロックが使われていたら
				m_pBlock->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//　小さくする
			}
			if (m_nStealthLife == 0)
			{//	ステルスの寿命が0だった場合
				m_nStealthCut++;
				if (m_nStealthCut > MAX_STEALTHCUT)
				{//	0以上なら寿命つける
					m_nStealthLife = 300;
					m_nStealthCut = 0;
				}
			}
		}
		if (m_bDash == false || m_bDamage == true)
		{
			if (m_nDashLife == 0)
			{//	ダッシュの寿命が0だった場合
				m_nDashCut++;
				if (m_nDashCut > MAX_DASHTHCUT)
				{//	0以上なら寿命つける
					m_nDashLife = 80;
					m_nDashCut = 0;
				}
			}
		}

	CManager::m_CDebugProcLeft->Print("\nm_nDashLife%d", m_nDashLife);
	CManager::m_CDebugProcLeft->Print("\nm_nDashCut%d", m_nDashCut);

	if (m_bMove == true)
	{//	動いている状態
		if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_LEFT, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_LEFT) == true*/)
		{
			if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true /*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
			{//	左上に動く
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.25f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true /*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
			{//	左下に動く
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.75f;
			}
			else
			{//	左に動く
				m_move.x += sinf(cameraRot.y - (-D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (-D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y - D3DX_PI * 0.5f;
			}
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_RIGHT, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_RIGHT) == true*/)
		{
			if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true/*||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
			{//	右上に動く
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.75f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.25f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true/* ||
				CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
			{//	右下に動く
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.25f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.75f;
			}
			else
			{//	右に動く
				m_move.x += sinf(cameraRot.y - (D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_move.z += cosf(cameraRot.y - (D3DX_PI * 0.5f))*(WALK_SPEED + m_fMoveControl);
				m_rotDest.y = cameraRot.y + D3DX_PI * 0.5f;
			}
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true/* ||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_DOWN) == true*/)
		{//	前に動く
			m_move.x += sinf(cameraRot.y + (D3DX_PI * 1.0f))*(WALK_SPEED + m_fMoveControl);
			m_move.z += cosf(cameraRot.y + (D3DX_PI * 1.0f))*(WALK_SPEED + m_fMoveControl);
			m_rotDest.y = cameraRot.y;
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true /*||
			CManager::GetInputDIPad()->GetPress(CInputDIPad::DIPADOTHER_STICK_L_UP) == true*/)
		{//	後ろに動く
			m_move.x += sinf(cameraRot.y)*(WALK_SPEED + m_fMoveControl);
			m_move.z += cosf(cameraRot.y)*(WALK_SPEED + m_fMoveControl);
			m_rotDest.y = D3DX_PI + cameraRot.y;
		}
	}
}

//=============================================================================
//	加算する動きの管理
//=============================================================================
void CPlayer::ManagementAddMovement(void)
{
	//目的の向きの修正
	if (m_rotDest.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}
	//	回転の角度のブレンド
	float fAngle = m_rotDest.y - m_rot.y;
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
	//	重力
	m_move.y -= GRAVITY;
	// 移動量加算
	m_pos += m_move;
	// 減速処理
	m_move.x -= (m_move.x - 0.0f) * MOVE_DOWNSPEED_NOR;
	m_move.z -= (m_move.z - 0.0f) * MOVE_DOWNSPEED_NOR;
	CManager::m_CDebugProcRight->Print("\n攻撃のフレームの( %d )", m_nAtkFream);
}

//=============================================================================
//	モーションの設定管理
//=============================================================================
void CPlayer::ManagementSetMosion(void)
{
	//	カメラの回転の取得
	D3DXVECTOR3 cameraRot = CCamera::GetCameraRotate();
	switch (m_MosionState)
	{//	モーションの状態
		//---------------------------------------------------------
		//	ニュートラルモーション状態
		//---------------------------------------------------------
	case MOSION_NEUTRAL:
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	移動していた場合	//	移動モーション
			m_nMotionType = 1;					//	移動モーション
			m_MosionState = MOSION_MOVE;		//	移動モーションの状態
		}
		else if (m_bJump == true)
		{//	ジャンプした場合
			m_nMotionType = 2;					//	ジャンプモーション
			m_MosionState = MOSION_JUMP;		//	ジャンプモーションの状態
		}
		else if (m_bSquat == true)
		{//	スクワットしている状態
			m_nMotionType = 6;					//	しゃがみモーション
			m_MosionState = MOSION_SQUAT;		//	しゃがみ状態へ
		}
		else if (m_bAttack == true)
		{//	攻撃モーション
			m_nMotionType = 8;					//	攻撃モーション
			m_MosionState = MOSION_ATTACK_000;	//	攻撃状態へ
		}
		else if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;					//	死んだモーション
			m_MosionState = MOSION_DISP;		//	死んだ状態へ
		}
		else if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;					//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;		//	ダメージ状態へ
		}
		if (m_nBltCut > 0)
		{//	弾が0以上だった場合
			if ((CManager::GetInputKeyboard()->GetPress(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetPress(XINPUT_GAMEPAD_B, 0) == true))
			{//	エンターキーを押したとき
				if (m_pBullet3D == NULL)
				{//	弾を使って居なかったら
					m_nMotionType = 4;				//	弾を投げる準備モーション
					m_MosionState = MOSION_BLTPRPE;	//	弾を投げる準備状態
				}
			}
		}
		break;
		//---------------------------------------------------------
		//	移動モーション状態
		//---------------------------------------------------------
	case MOSION_MOVE:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
		{//	移動していない場合		//	ニュートラルモーション
			m_nMotionType = 0;					//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
		}
		else if (m_bJump == true)
		{//	ジャンプ状態だった場合
			m_nMotionType = 2;					//	ジャンプモーション
			m_MosionState = MOSION_JUMP;		//	移動モーションの状態
		}
		else if (m_bSquat == true)
		{//	スクワットしている状態
			m_nMotionType = 7;					//	しゃがみa歩きモーション
			m_MosionState = MOSION_SQUATMOVE;	//	しゃがみ歩き状態
		}
		else if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;					//	死んだモーション
			m_MosionState = MOSION_DISP;		//	死んだ状態へ
		}
		else if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;					//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;		//	ダメージ状態へ
		}
		if (m_nBltCut > 0)
		{//	弾が0以上だった場合
			if ((CManager::GetInputKeyboard()->GetRelease(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetRelease(XINPUT_GAMEPAD_B, 0) == true))
			{//	エンターキーを押したとき
				if (m_pBullet3D == NULL)
				{//	弾を使って居なかったら
					m_nMotionType = 4;				//	弾を投げる準備モーション
					m_MosionState = MOSION_BLTPRPE;	//	弾を投げる準備状態
				}
			}
		}
		break;
		//---------------------------------------------------------
		//	ジャンプモーション状態
		//---------------------------------------------------------
	case MOSION_JUMP:
		if (m_bJump == false && m_move.y < 0.1f && m_move.y > -0.1f)
		{//	ジャンプからジャンプ中じゃなくなりプレイヤーの動きが止まった時
			m_nMotionType = 3;							//	着地モーション
			m_move = D3DXVECTOR3(0.0f, m_move.y, 0.0f);	//	着地中は動きを止める
			m_nCntMosionChange++;						//	モーションの変更するカウンター加算
		}
		else if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;					//	死んだモーション
			m_MosionState = MOSION_DISP;		//	死んだ状態へ
		}
		else if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;					//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;		//	ダメージ状態へ
		}

		if (m_nCntMosionChange > 10)
		{//	着地のフレームが指定の数以上いったら
			m_MosionState = MOSION_LAND;		//	着地モーション状態
		}

		break;
		//---------------------------------------------------------
		//	着地モーション状態
		//---------------------------------------------------------
	case MOSION_LAND:
		if (m_bJump == false)
		{//	ジャンプ中じゃなかった場合
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;				//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;	//	ニュートラルモーションの状態
			}
			else if (m_bDisp == true)
			{//	死んだ場合
				m_nMotionType = 10;				//	死んだモーション
				m_MosionState = MOSION_DISP;	//	死んだ状態へ
			}
			else if (m_bDamage == true)
			{//	ダメージを受けた場合
				m_nMotionType = 11;					//	ダメージモーション
				m_MosionState = MOSION_DAMAGE;		//	ダメージ状態へ
			}
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	移動していた場
			m_nMotionType = 1;				//	移動モーション
			m_MosionState = MOSION_MOVE;	//	移動モーションの状態
		}
		break;
		//---------------------------------------------------------
		//	弾を投げる準備モーション
		//---------------------------------------------------------
	case MOSION_BLTPRPE:
		m_nCntMosionChange++;					//	モーションの変更するカウンター加算
		if ((CManager::GetInputKeyboard()->GetRelease(DIK_RETURN) == true ||
			CManager::GetInputXPad()->GetRelease(XINPUT_GAMEPAD_B, 0) == true))
		{//	エンターキーを話したとき
			if (m_nBltCut > 0)
			{//	弾が0以上だった場合
				m_nMotionType = 5;						//	弾を投げる
				m_MosionState = MOSION_BLTTHROW;		//	弾を投げる
			}
		}
		else
		{
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合				//	移動モーション
				m_nMotionType = 1;				//	移動モーション
				m_MosionState = MOSION_MOVE;	//	移動モーションの状態
			}
			else if (m_bJump == true)
			{//	ジャンプした場合
				m_nMotionType = 2;				//	ジャンプモーション
				m_MosionState = MOSION_JUMP;	//	移動モーションの状態
			}
			else if (m_bDisp == true)
			{//	死んだ場合
				m_nMotionType = 10;				//	死んだモーション
				m_MosionState = MOSION_DISP;	//	死んだ状態へ
			}
			else if (m_bDamage == true)
			{//	ダメージを受けた場合
				m_nMotionType = 11;					//	ダメージモーション
				m_MosionState = MOSION_DAMAGE;		//	ダメージ状態へ
			}
		}
		break;
		//---------------------------------------------------------
		//	弾投げるモーション
		//---------------------------------------------------------
	case MOSION_BLTTHROW:
		m_nCntMosionChange++;							//	モーションの変更するカウンター加算
		if (m_pBullet3D == NULL && m_nCntMosionChange >= m_nCouterFreamMax[MOSION_BLTTHROW] - 35)
		{//	弾が使われていなかったら
		 //	弾の生成
			m_pBullet3D = CBullet3D::Create
			(D3DXVECTOR3(m_apModel[3]->GetMtxWorld()._41 + sinf(m_rot.y*D3DX_PI)*9.0f, m_apModel[3]->GetMtxWorld()._42 - 7.0f, m_apModel[3]->GetMtxWorld()._43),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(sinf(m_rot.y - D3DX_PI)*5.0f, 7.0f, cosf(m_rot.y - D3DX_PI)* 5.0f), CBullet3D::BULLET3D_TYPE_BOOM);
			AddBulletGan(-1);							//	弾の数を減らす
		}
		if (m_pBullet3D != NULL && m_nCntMosionChange >= m_nCouterFreamMax[MOSION_BLTTHROW])
		{//	モーションの最大数分超えたら		//	モーションの最大数を超えた場合
			m_nMotionType = 0;					//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			m_pBullet3D = NULL;
		}
		if (m_pBullet3D == NULL)
		{//	弾が使われていなかったら
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合	//	移動モーション
				m_nMotionType = 1;				//	移動モーション
				m_MosionState = MOSION_MOVE;	//	移動モーションの状態
			}
			else if (m_bJump == true)
			{//	ジャンプした場
				m_nMotionType = 2;				//	ジャンプモーション
				m_MosionState = MOSION_JUMP;	//	移動モーションの状態
			}
			else if (m_bDisp == true)
			{//	死んだ場合
				m_nMotionType = 10;				//	死んだモーション
				m_MosionState = MOSION_DISP;	//	死んだ状態へ
			}
			else if (m_bDamage == true)
			{//	ダメージを受けた場合
				m_nMotionType = 11;				//	ダメージモーション
				m_MosionState = MOSION_DAMAGE;	//	ダメージ状態へ
			}
		}
		break;
		//---------------------------------------------------------
		//	しゃがみモーション
		//---------------------------------------------------------
	case MOSION_SQUAT:
		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f&&m_bSquat == false)
		{//	移動していない場合
			m_nMotionType = 0;				//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;	//	ニュートラルモーションの状態
		}
		if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
		{//	移動していた場合	//	スクワットしている状態のとき
			m_nMotionType = 7;					//	移動モーション
			m_MosionState = MOSION_SQUATMOVE;	//	移動モーションの状態
		}
		else if (m_bJump == true)
		{//	ジャンプ状態だった場合
			m_nMotionType = 2;					//	ジャンプモーション
			m_MosionState = MOSION_JUMP;		//	移動モーションの状態
		}
		else if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;					//	死んだモーション
			m_MosionState = MOSION_DISP;		//	死んだ状態へ
		}
		else if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;				//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;	//	ダメージ状態へ
		}
		break;
		//---------------------------------------------------------
		//	しゃがみ歩きモーション
		//---------------------------------------------------------
	case MOSION_SQUATMOVE:

		if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f &&m_bSquat == true)
		{//	移動していない場合
			m_nMotionType = 6;				//	ニュートラルモーション
			m_MosionState = MOSION_SQUAT;	//	ニュートラルモーションの状態
		}
		if (m_bSquat == false)
		{//	移動していない場合					//	ニュートラルモーション
			m_nMotionType = 0;					//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
		}
		else if (m_bJump == true)
		{//	ジャンプ状態だった場合
			m_nMotionType = 2;					//	ジャンプモーション
			m_MosionState = MOSION_JUMP;		//	移動モーションの状態
		}
		else if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;					//	死んだモーション
			m_MosionState = MOSION_DISP;		//	死んだ状態へ
		}
		else if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;				//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;	//	ダメージ状態へ
		}
		break;
		//---------------------------------------------------------
		//	攻撃モーション	キック
		//---------------------------------------------------------
	case MOSION_ATTACK_000:
		m_nCntMosionChange++;							//	モーションの変更するカウンター加算
		if (m_nCouterFreamMax[MOSION_ATTACK_000] + 25 > m_nCntMosionChange  && m_nCouterFreamMax[MOSION_ATTACK_000] - 15 < m_nCntMosionChange)
		{//	コンボできるまでのフレーム以上までいった場合
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_F) == true ||
				CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_X, 0) == true)
			{	//	コンボ出来るフレーム
				m_nMotionType = 9;					//	次の攻撃モーションへ
				m_MosionState = MOSION_ATTACK_001;	//	次の攻撃に移行の状態
				m_bAttack = true;					//	攻撃中じゃない
			}
		}
		else if (m_nCntMosionChange > m_nCouterFreamMax[MOSION_ATTACK_000] + 25)
		{//	カウンターがフレームの合計値を
			m_nMotionType = 0;					//	ニュートラルモーション
			m_MosionState = MOSION_NEUTRAL;		//	ニュートラルモーションの状態
			m_bAttack = false;
		}
		if (m_bDamage == true)
		{//	ダメージを受けた場合
			m_nMotionType = 11;				//	ダメージモーション
			m_MosionState = MOSION_DAMAGE;	//	ダメージ状態へ
		}
		break;
		//---------------------------------------------------------
		//	攻撃モーション	パンチ
		//---------------------------------------------------------
	case MOSION_ATTACK_001:
		m_nCntMosionChange++;					//	モーションの変更するカウンター加算
		if (m_nCouterFreamMax[MOSION_ATTACK_001] < m_nCntMosionChange)
		{//	モーションのフレームを過ぎた場合
			m_bAttack = false;					//	攻撃状態を消す
			m_bMove = true;						//	動ける状態に戻す
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合	//	移動モーション
				m_nMotionType = 1;				//	移動モーション
				m_MosionState = MOSION_MOVE;	//	移動モーションの状態
				m_bAttack = false;
			}
			else if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;				//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;	//	ニュートラルモーションの状態
			}
			else if (m_bDamage == true)
			{//	ダメージを受けた場合
				m_nMotionType = 11;				//	ダメージモーション
				m_MosionState = MOSION_DAMAGE;	//	ダメージ状態へ
			}
		}
		else
		{//	攻撃中だったら動かさない
			m_bMove = false;					//	動けない状態
		}
		break;
		//---------------------------------------------------------
		//	死んだモーション
		//---------------------------------------------------------
	case MOSION_DISP:
		break;
		//---------------------------------------------------------
		//	ダメージモーション
		//---------------------------------------------------------
	case MOSION_DAMAGE:
		if (m_bDamage == false)
		{//	ダメージ状態じゃなかったら
			if ((m_move.x >= 0.1f || m_move.z >= 0.1f || m_move.x <= -0.1f || m_move.z <= -0.1f))
			{//	移動していた場合	//	移動モーション
				m_nMotionType = 1;				//	移動モーション
				m_MosionState = MOSION_MOVE;	//	移動モーションの状態
				m_bAttack = false;
			}
			if (m_move.x <= 0.1f && m_move.x >= -0.1f && m_move.z <= 0.1f && m_move.z >= -0.1f)
			{//	移動していない場合
				m_nMotionType = 0;				//	ニュートラルモーション
				m_MosionState = MOSION_NEUTRAL;	//	ニュートラルモーションの状態
			}
		}
		if (m_bDisp == true)
		{//	死んだ場合
			m_nMotionType = 10;				//	死んだモーション
			m_MosionState = MOSION_DISP;	//	死んだ状態へ
		}
		break;
	}
	if (m_nMotionType != m_nMotionTypeOld)
	{//	モーションが変わった場合
		m_nCntMosionChange = 0;				//	カウンターの初期化
		m_nAtkFream = 0;					//
	}

	CManager::m_CDebugProcLeft->Print("\nライフ　( %d )", m_nLife);
}
//=============================================================================
//	当たり判定の総括
//=============================================================================
void CPlayer::ManagementCollision(void)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	m_bBlock = false;	// 当たっていない
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_2);	// 現在　
	CScene *pSceneNext = NULL;								// 次

	while (pScene != NULL)
	{// NULL以外の場合
	 // 次オブジェクト情報を保存
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTEPE_FLOOR)
		{//	床だった場合
			CFloor *pFloor = (CFloor*)pScene;				//	床にキャスト
			pFloor->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		// 当たり判定
		}
		// 次のオブジェクトに設定
		pScene = pSceneNext;
	}

	// シーン
	pScene = CScene::GetScene(CScene::PRIORITY_3);		// 現在
	pSceneNext = NULL;									// 次

	bool bHitIn = false;
	while (pScene != NULL)
	{// NULL以外の場合
	 // 次オブジェクト情報を保存
		pSceneNext = pScene->GetSceneNext();
		if (pScene->GetObjType() == CScene::OBJTYPE_BLOCK)
		{// オブジェクトタイプがブロックだったら
			CBlock *pBlock = (CBlock*)pScene;									// ブロックにキャスト
			pBlock->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);	// 当たり判定
			if (pBlock->StealthCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin)==true )
			{
				bHitIn = true;							//	ステルスブロックの中に入った場合
			}
			if (pBlock->StageNxstCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin) == true)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	動きを7止める
			}

			//if (pBlock->StealthCollision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin) == true && bHitIn == true)
			//{
			//	m_bStealthMode = true;							//	ステルスブロックの中に入った場合
			//	CManager::m_CDebugProcLeft->Print("\nステルスモード");
			//}
			//else
			//{
			//	m_bStealthMode = false;							//	ステルスブロックの中に入った場合
			//}

			bool *bLand = pBlock->GetHit();
			if (bLand[0] == true)
			{// 上判定
				m_bBlock = true;			// 当たった
			}
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_WALL)
		{//	壁だった場合
			CWall *pWall = (CWall*)pScene;					//	壁にキャスト
			pWall->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		// 当たり判定
		}
		else if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
		{//	敵だった場合
			CEnemy *pEnemy = (CEnemy*)pScene;				//	敵にキャスト
			pEnemy->Collision(&m_pos, &m_posOld, &m_move, m_vtxMax, m_vtxMin);		//	当たり判定

			CEnemyRobotSpine *pEnemyRobotSpine = (CEnemyRobotSpine*)pScene;				//	敵にキャスト
			if (pEnemyRobotSpine->Gettype() == 2)
			{//	棘に敵だった場合
				if (pEnemyRobotSpine->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
				{//	プレイヤーとの角度
					if (m_MosionState != MOSION_DAMAGE &&m_state != STATE_DAMAGE)
					{//	ダメージ状態だった場合
						float fAngle = atan2f(m_pos.x - pEnemyRobotSpine->Getpos().x, m_pos.z - pEnemyRobotSpine->Getpos().z);
						HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 30.25f, 0.0f, cosf(fAngle) * 30.25f));
						pEnemyRobotSpine->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						//m_nEffectCounter++;	//	エフェクトが出力されるカウンター
						//if ((m_nEffectCounter % 8) == 0)
					}
					//	　HITエフェクト
					CEffect::Create
					(D3DXVECTOR3(pEnemyRobotSpine->Getpos().x + sinf(pEnemyRobotSpine->Getrot().y - D3DX_PI)*30.0f,
						pEnemyRobotSpine->Getsize(1).y / 2 + 40,
						pEnemyRobotSpine->Getpos().z + cosf(pEnemyRobotSpine->Getrot().y - D3DX_PI)*30.0f), 1, 6);
				}
			}
			CEnemyRobotNomal *pEnemyRobotNomal = (CEnemyRobotNomal*)pScene;				//	敵にキャスト
			if (pEnemyRobotNomal->Gettype() == 0)
			{//	通常の敵だった場合
				if (pEnemyRobotNomal->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
				{//	プレイヤーとの角度
					if (m_MosionState != MOSION_DAMAGE &&m_state != STATE_DAMAGE)
					{//	ダメージ状態だった場合
						pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE001);	//	ダメージ音
						float fAngle = atan2f(m_pos.x - pEnemyRobotNomal->Getpos().x, m_pos.z - pEnemyRobotNomal->Getpos().z);
						HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 30.25f, 0.0f, cosf(fAngle) * 30.25f));
					}
				}
			}
		}
		// 次のオブジェクトに設定
		pScene = pSceneNext;
	}
	// シーン
	pScene = CScene::GetScene(CScene::PRIORITY_4);		// 現在
	pSceneNext = NULL;									// 次
	while (pScene != NULL)
	{// NULL以外の場合
		pSceneNext = pScene->GetSceneNext();			//	次のオブジェクトの情報を取得
		if (pScene->GetObjType() == CScene::OBJTYPE_ITEM)
		{//	オブジェクトがアイテムだったら
			CItem *pItem = (CItem*)pScene;				//	アイテムにキャスト
			if (pItem->CollisionItem(&m_pos, &m_move, m_vtxMax, m_vtxMin) == true)
			{//	アイテムに当たった場合
				if (pItem->GetItemType() == pItem->TYPE_BULLETADD)
				{//	弾の加算アイテムだった場合
					CPlayer::AddBulletGan(1);
				}
				else if (pItem->GetItemType() == pItem->TYPE_LIFEUP)
				{//	弾の加算アイテムだった場合
					HitLife(1,D3DXVECTOR3(0.0f,0.0f,0.0f));
				}
			}
		}
		if (pScene->GetObjType() == CScene::OBJTYPE_BULLET2D)
		{//	弾の
			CBullet2D *pBullet2D = (CBullet2D*)pScene;	//	弾2Dにキャスト
			D3DXVECTOR3 moveOld = m_move;
			if (pBullet2D->CircleCollision(&m_pos, &m_move, &m_rot, m_vtxMax, m_vtxMin) == true)
			{//	弾の判定
			 //	プレイヤーとの角度
				float fAngle = atan2f(m_pos.x - pBullet2D->Getpos().x, m_pos.z - pBullet2D->Getpos().z);
				HitLife(-1, D3DXVECTOR3(sinf(fAngle) * 15.25f, 0.0f, cosf(fAngle) * 15.25f));
				//	　HITエフェクト
				CEffect::Create(D3DXVECTOR3(pBullet2D->Getpos().x ,pBullet2D->Getpos().y,pBullet2D->Getpos().z), 1, 7);
				pBullet2D->Uninit();
			}
		}
		pScene = pSceneNext;		//	次を設定
	}

	if (bHitIn == true)
	{//	ステルスブロックの中に入った場合
		m_bStealthMode = true;
		CManager::m_CDebugProcLeft->Print("\nステルスモード");
	}
	else
	{//	ステルスブロックの中に入っていない場合
		m_bStealthMode = false;
	}
}

//==============================================================================
//	ダメージ計算
//==============================================================================
void CPlayer::HitLife(int nDamage, D3DXVECTOR3 move)
{
	CSound *pSound = CManager::GetSound();
	int nLifeValue = nDamage;		//	計算用体力の値
	if (m_nLife >= 0)
	{//計算した値が寿命の最大値より下の場合
		if (m_state != STATE_INVINCIBLE)
		{//	無敵状態以外
			m_move += move;
			if (nLifeValue <= -1)
			{//	HPがまだ残っている状態
				m_state = STATE_DAMAGE;		//	ダメージ状態に切り替え
				if (m_state == STATE_DAMAGE)
				{//	ダメージ状態だった場合
					m_nLife += nLifeValue;			//	計算した値をライフに代入
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);	// ダメージ音
				}
			}
			else if (nLifeValue >= 1&& m_nLife<10)
			{
				m_nLife += nLifeValue;			//	計算した値をライフに代入
			}
		}
	}
	if (m_nLife <= 0 && nDamage <= -1)
	{//	ライフが0以下になった場合
		m_nLife += nLifeValue;			//	計算した値をライフに代入
		m_state = STATE_DEATH;		//	ステータスを死亡状態に変える
	}
}
//==============================================================================
//	弾の数
//==============================================================================
void CPlayer::AddBulletGan(int nAdd)
{
	m_nBltCut = m_nBltCut + nAdd;		//	弾の弾数減らす
	CBulletNumber::AddNum(nAdd);		//	弾の数値のの減算
}

//=============================================================================
// プレイヤーの当たり判定
//=============================================================================
void  CPlayer::BoxCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	D3DXVECTOR3 PlayerPos = CPlayer::Getpos();				//	位置の取得
	D3DXVECTOR3 PlayerMove = CPlayer::Getmove();			//	動きの取得
	D3DXVECTOR3 PlayerRot = CPlayer::Getrot();				//	回転の取得
	D3DXVECTOR3 PlayerSizeMax = CPlayer::Getsize(0);		//	大きさの最大値
	D3DXVECTOR3 PlayerSizeMin = CPlayer::Getsize(1);		//	大きさの最小値

	if ((PlayerPos.x + PlayerSizeMin.x) < (pPos->x + (sizeMax.x)) &&
		(pPos->x + (sizeMin.x)) < (PlayerPos.x + PlayerSizeMax.x) &&
		(PlayerPos.z + PlayerSizeMin.z) < (pPos->z + (sizeMax.z)) &&
		(pPos->z + (sizeMin.z)) < (PlayerPos.z + PlayerSizeMax.z))
	{// X/Z範囲確認
		if ((pPos->y + sizeMin.y) <= (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMax.y) <= (pPosOld->y + sizeMin.y))
		{// 上からの当たり判定
			pPos->y = PlayerPos.y + PlayerSizeMax.y + (sizeMin.y);
			move->y = 0.0f;
		}
		else if ((PlayerPos.y + PlayerSizeMin.y) <= (pPos->y + sizeMax.y) && (pPosOld->y + sizeMax.y) <= (PlayerPos.y + PlayerSizeMin.y))
		{// 下からの当たり判定
			pPos->y = pPosOld->y;
			move->y = 0.0f;
		}
	}
	if ((pPos->y + sizeMin.y) < (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMin.y) < (pPos->y + sizeMax.y))
	{// Y範囲確認
		if ((PlayerPos.z + PlayerSizeMin.z) < (pPos->z + (sizeMax.z)) && (pPos->z + (sizeMin.z)) < (PlayerPos.z + PlayerSizeMax.z))
		{// Z範囲確認
			if ((PlayerPos.x + PlayerSizeMin.x) <= (pPos->x + sizeMax.x) && (pPosOld->x + sizeMax.x) <= (PlayerPos.x + PlayerSizeMin.x))
			{// 左からの当たり判定
				pPos->x = PlayerPos.x + PlayerSizeMin.x + (sizeMin.x);
				move->x = 0.0f;
			}
			else if ((pPos->x + sizeMin.x) <= (PlayerPos.x + PlayerSizeMax.x) && (PlayerPos.x + PlayerSizeMax.x) <= (pPosOld->x + sizeMin.x))
			{// 右からの当たり判定
				pPos->x = PlayerPos.x + PlayerSizeMax.x + (sizeMax.x);
				move->x = 0.0f;
			}
		}
	}
	if ((pPos->y + sizeMin.y) < (PlayerPos.y + PlayerSizeMax.y) && (PlayerPos.y + PlayerSizeMin.y) < (pPos->y + sizeMax.y))
	{// Y範囲確認
		if ((PlayerPos.x + PlayerSizeMin.x) < (pPos->x + (sizeMax.x)) && (pPos->x + (sizeMin.x)) < (PlayerPos.x + PlayerSizeMax.x))
		{// X範囲確認
			if ((PlayerPos.z + PlayerSizeMin.z) <= (pPos->z + sizeMax.z) && (pPosOld->z + sizeMax.z) <= (PlayerPos.z + PlayerSizeMin.z))
			{// 手前からの当たり判定
				pPos->z = PlayerPos.z + PlayerSizeMin.z + (sizeMin.z);
				move->x = 0.0f;
			}
			else if ((pPos->z + sizeMin.z) <= (PlayerPos.z + PlayerSizeMax.z) && (PlayerPos.z + PlayerSizeMax.z) <= (pPosOld->z + sizeMin.z))
			{// 後ろからの当たり判定
				pPos->z = PlayerPos.z + PlayerSizeMax.z + (sizeMax.z);
				move->x = 0.0f;
			}
		}
	}
}

//=============================================================================
// 円の当たり判定
//=============================================================================
void CPlayer::CircleCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{
	D3DXVECTOR3 pos = CPlayer::Getpos();					//	位置の取得
	//	距離の計算
	float fLength = (pPos->x - m_pos.x)* (pPos->x - m_pos.x) + (pPos->z - m_pos.z)* (pPos->z - m_pos.z);

}

//=============================================================================
// 攻撃の当たり判定
//=============================================================================
bool CPlayer::AttackCollsion(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *move, D3DXVECTOR3 sizeMax, D3DXVECTOR3 sizeMin)
{

	bool bHit = false;			//	攻撃が当たったかどうか
	D3DXVECTOR3 PlayerPos = CPlayer::Getpos();				//	位置の取得
	D3DXVECTOR3 PlayerMove = CPlayer::Getmove();			//	動きの取得
	D3DXVECTOR3 PlayerRot = CPlayer::Getrot();				//	回転の取得
	D3DXVECTOR3 PlayerSizeMax = CPlayer::Getsize(0);		//	大きさの最大値
	D3DXVECTOR3 PlayerSizeMin = CPlayer::Getsize(1);		//	大きさの最小値

	if (m_bAttack == true)
	{//	攻撃しているかどうか
		if (m_MosionState == MOSION_ATTACK_000)
		{//	攻撃000中だった場合
			m_nAtkFream++;
			if (m_nAtkFream < 12 && m_nAtkFream > 6)
			{//	攻撃のコリジョンがでるフレーム
				if ((m_apModel[9]->GetMtxWorld()._41) < (pPos->x + sizeMax.x + ATTACK_COLL_EXPAND_X_000) &&
					(pPos->x + sizeMin.x + -ATTACK_COLL_EXPAND_X_000) < (m_apModel[9]->GetMtxWorld()._41) &&
					(m_apModel[9]->GetMtxWorld()._42) < (pPos->y + sizeMax.y + ATTACK_COLL_EXPAND_Y_000) &&
					(pPos->y + sizeMin.y + -ATTACK_COLL_EXPAND_Y_000) < (m_apModel[9]->GetMtxWorld()._42) &&
					(m_apModel[9]->GetMtxWorld()._43 < (pPos->z + sizeMax.z + ATTACK_COLL_EXPAND_Z_000)) &&
					(pPos->z + sizeMin.z + -ATTACK_COLL_EXPAND_Z_000) < (m_apModel[9]->GetMtxWorld()._43))
				{//	手のオフセットのベクトルが敵の大きさ+指定の値の範囲内だった場合
					bHit = true;			//	当たった
					m_bAttack = false;		//	攻撃中じゃない
				}
			}
		}
		else if (m_MosionState == MOSION_ATTACK_001)
		{//	攻撃001中だった場合
			m_nAtkFream++;
			if (m_nAtkFream < m_nCouterFreamMax[MOSION_ATTACK_001] -10 && m_nAtkFream > 5)
			{//	攻撃のコリジョンがでるフレーム
				if ((m_apModel[3]->GetMtxWorld()._41) < (pPos->x + sizeMax.x + ATTACK_COLL_EXPAND_X_001) &&
					(pPos->x + sizeMin.x + -ATTACK_COLL_EXPAND_X_001) < (m_apModel[3]->GetMtxWorld()._41) &&
					(m_apModel[3]->GetMtxWorld()._42) < (pPos->y + sizeMax.y + ATTACK_COLL_EXPAND_Y_001) &&
					(pPos->y + sizeMin.y + -ATTACK_COLL_EXPAND_Y_001) < (m_apModel[3]->GetMtxWorld()._42) &&
					(m_apModel[3]->GetMtxWorld()._43 < (pPos->z + sizeMax.z + ATTACK_COLL_EXPAND_Z_001)) &&
					(pPos->z + sizeMin.z + -ATTACK_COLL_EXPAND_Z_001) < (m_apModel[3]->GetMtxWorld()._43))
				{//	手のオフセットのベクトルが敵の大きさ+指定の値の範囲内だった場合
					m_bAtkLastHit = true;	//	最終攻撃が当たった
					bHit = true;			//	当たった
					m_bAttack = false;		//	攻撃中じゃない
				}
			}
		}
	}
	if (m_bAttack == false)
	{//	フレームの初期化
		m_nAtkFream = 0;		//	攻撃のフレーム
		m_bAtkLastHit = false;	//	最終の攻撃が当たった時
	}
	//	値を返す
	return bHit;
}

//=============================================================================
// モーションの更新
//=============================================================================
void CPlayer::UpdateMotion(void)
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
			if (m_nMotionType == m_nMotionTypeOld )
			{//	今の種類が過去の種類が同じだった場合
				//	現在のキーを取得
				pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
				//	次のキーを取得
				pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

				//	現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

				//POSX
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	相対値を差分を使って各要素の値を算出
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//POSY
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	相対値を差分を使って各要素の値を算出
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//POSZ
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	相対値を差分を使って各要素の値を算出
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);

				//ROTX
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

				//ROTY
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);

				//ROTZ
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);


				//	目的の向きの修正の修正
				if (rotmotion.x < -D3DX_PI){rotmotion.x += D3DX_PI * 2.0f;}
				else if (rotmotion.x > D3DX_PI){rotmotion.x -= D3DX_PI * 2.0f;}
				if (rotmotion.y < -D3DX_PI){rotmotion.y += D3DX_PI * 2.0f;}
				else if (rotmotion.y > D3DX_PI){rotmotion.y -= D3DX_PI * 2.0f;}
				if (rotmotion.z < -D3DX_PI){rotmotion.z += D3DX_PI * 2.0f;}
				else if (rotmotion.z > D3DX_PI){rotmotion.z -= D3DX_PI * 2.0f;}

				//	パーツを動かす
				m_apModel[nCntParts]->Setrot(rotmotion);
				//	位置を設定する
				m_apModel[nCntParts]->Setpos(m_OffSetPos[nCntParts] + posmotion);
			}
			else	if (m_nMotionType != m_nMotionTypeOld)
			{
				//	現在のキーを取得
				pKey = &m_pKeyInfo[m_nMotionTypeOld][m_nKey].aKey[nCntParts];
				//	次のキーを取得
				pNextKey = &m_pKeyInfo[m_nMotionType][0].aKey[nCntParts];

				//	現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fRateMotion =((float)m_nCountFlame - 60) * 1.0f;

				//POSX
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//	相対値を差分を使って各要素の値を算出
				posmotion.x = (fDiffMotion / fRateMotion);

				//POSY
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//	相対値を差分を使って各要素の値を算出
				posmotion.y = (fDiffMotion / fRateMotion);

				//POSZ
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//	相対値を差分を使って各要素の値を算出
				posmotion.z = (fDiffMotion / fRateMotion);

				//ROTX
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.x = (fDiffMotion / fRateMotion);

				//ROTY
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.z = (fDiffMotion / fRateMotion);

				//ROTZ
				//	現在のキーと次のキーの各要素の差分を算出
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//	差分の修正
				if (fDiffMotion < -D3DX_PI) { fDiffMotion += D3DX_PI * 2.0f; }
				else if (fDiffMotion > D3DX_PI) { fDiffMotion -= D3DX_PI * 2.0f; }
				//	相対値を差分を使って各要素の値を算出
				rotmotion.y = (fDiffMotion / fRateMotion);

				//	目的の向きの修正の修正
				if (rotmotion.x < -D3DX_PI) { rotmotion.x += D3DX_PI * 2.0f; }
				else if (rotmotion.x > D3DX_PI) { rotmotion.x -= D3DX_PI * 2.0f; }
				if (rotmotion.y < -D3DX_PI) { rotmotion.y += D3DX_PI * 2.0f; }
				else if (rotmotion.y > D3DX_PI) { rotmotion.y -= D3DX_PI * 2.0f; }
				if (rotmotion.z < -D3DX_PI) { rotmotion.z += D3DX_PI * 2.0f; }
				else if (rotmotion.z > D3DX_PI) { rotmotion.z -= D3DX_PI * 2.0f; }

				//	パーツを動かす
				m_apModel[nCntParts]->Setrot(m_apModel[nCntParts]->Getrot() + rotmotion);
				//	位置を設定する
				m_apModel[nCntParts]->Setpos(m_OffSetPos[nCntParts] + posmotion);

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
void CPlayer::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile= NULL;		//	ファイルポインタ
	char *pStrcur;			//	現在の先頭の文字列
	char aLine[256];		//	文字列
	char aStr[256];			//	一時保存文字列
	int nIndex = 0;			//	現在のインデックス
	int nWord = 0;			//	ポップで返された値を保持
	int nCounter = 0;		//	カウンター

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");
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
							&m_pBuffMat[nCntModel],
							NULL,
							&m_nNumMat[nCntModel],
							&m_pMesh[nCntModel]);

						D3DXMATERIAL *pmat;									// マテリアルデータへのポインタ
						D3DMATERIAL9 *matDef;								// 現在のマテリアル保存用
						pmat = (D3DXMATERIAL*)m_pBuffMat[nCntModel]->GetBufferPointer();
						matDef = new D3DMATERIAL9[m_nNumMat[nCntModel]];						//	マテリアルのメモリの確保
						m_pTexture[nCntModel] = new LPDIRECT3DTEXTURE9[m_nNumMat[nCntModel]];	//	テクスチャのメモリの確保

						for (DWORD tex = 0; tex < m_nNumMat[nCntModel]; tex++)
						{// カウント
							matDef[tex] = pmat[tex].MatD3D;						//　マテリアルのプロパティを記述する D3DMATERIAL9 構造体
							matDef[tex].Ambient = matDef[tex].Diffuse;			//　光の直接当たる部分の色を光を当たらない部分と同期させる
							m_pTexture[nCntModel][tex] = NULL;					//	テクスチャ情報を空にする
							if (pmat[tex].pTextureFilename != NULL &&lstrlen(pmat[tex].pTextureFilename) > 0)
							{// テクスチャを使用している & 文字列の長さが0以上だったら
								if (FAILED(D3DXCreateTextureFromFile(pDevice, pmat[tex].pTextureFilename, &m_pTexture[nCntModel][tex])))
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
								D3DXVECTOR3(m_aKayOffset[nIndex].fposX,m_aKayOffset[nIndex].fposY, m_aKayOffset[nIndex].fposZ),
								D3DXVECTOR3(m_aKayOffset[nIndex].frotX,m_aKayOffset[nIndex].frotY,m_aKayOffset[nIndex].frotZ));

								//位置代入
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//モデルを割り当て
								m_apModel[nIndex]->BindModel(m_nNumMat[nIndex], m_pMesh[nIndex], m_pBuffMat[nIndex]);

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
char *CPlayer::ReadLine(FILE *pFile, char *pDst)
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
char * CPlayer::GetLineTop(char * pStr)
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
int CPlayer::PopString(char * pStr, char * pDest)
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
