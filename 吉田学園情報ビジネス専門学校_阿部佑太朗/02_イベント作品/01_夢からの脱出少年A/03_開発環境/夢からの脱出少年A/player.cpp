//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "obstacle.h"
#include "goal.h"
#include "game.h"
#include "fade.h"
#include <stdio.h>
#include <stdlib.h>
#include "sound.h"
#include "ColorBall.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_FILENAME_LOAD	"data/player.txt"		// ロードするファイルの名前
#define PLAYER_SPEED			(0.45f)					// プレイヤーの移動速度
#define PLAYER_DECELERATE		(0.1f)					// プレイヤーの減速量
#define PLAYER_ROT_SPEED		(0.1f)					// プレイヤーの回転速度
#define PLAYER_STOP_SPEED		(0.01f)					// 止まったと見なす速度
#define PLAYER_NEUTRAL_SPEED	(0.1f)					// ニュートラルモーションになる速度
#define PLAYER_JUMP_POWER		(3.5f)					// プレイヤーのジャンプ力
#define PLAYER_GRAVITY			(0.15f)					// プレイヤーへの重力
#define PLAYER_SHADOW_WIDTH		(20.0f)					// プレイヤーの影の幅
#define PLAYER_SHADOW_DEPTH		(20.0f)					// プレイヤーの影の奥行
#define PLAYER_COLLISION_SIZE	(10.0f)					// プレイヤーの当たり判定の大きさ
#define PLAYER_LIFE				(10)						// プレイヤーの初期体力
#define PLAYER_LIFE_MAX			(10)						// プレイヤーの最大体力
#define PLAYER_DAMAGE_TIME		(6)						// プレイヤーのダメージ状態の時間
#define PLAYER_INVINCIBLE_TIME	(60)					// プレイヤーの無敵状態の時間
#define PLAYER_REACTION			(10.0f)					// プレイヤーの反動

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetMotionPlayer(void);
void MotionPlayer(void);
void LoadPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player		g_Player;								// プレイヤーの情報
float g_SiftMove;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	g_Player = {};

	// ロード処理
	LoadPlayer();

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(&g_Player.aPlayerModel[nCntModel].aName[0]
			, D3DXMESH_SYSTEMMEM
			, pDevice
			, NULL
			, &g_Player.aPlayerModel[nCntModel].pBuffMat
			, NULL
			, &g_Player.aPlayerModel[nCntModel].nNumMat
			, &g_Player.aPlayerModel[nCntModel].pMesh);

		// マテリアルの設定
		pMat = (D3DXMATERIAL*)g_Player.aPlayerModel[nCntModel].pBuffMat->GetBufferPointer();
		g_Player.aPlayerModel[nCntModel].pCol = new D3DMATERIAL9[(int)g_Player.aPlayerModel[nCntModel].nNumMat];
		g_Player.aPlayerModel[nCntModel].pColDef = new D3DMATERIAL9[(int)g_Player.aPlayerModel[nCntModel].nNumMat];
		g_Player.aPlayerModel[nCntModel].pTex = new LPDIRECT3DTEXTURE9[(int)g_Player.aPlayerModel[nCntModel].nNumMat];

		for (int nCntMat = 0; nCntMat < (int)g_Player.aPlayerModel[nCntModel].nNumMat; nCntMat++)
		{
			// デフォルトの色の保持
			g_Player.aPlayerModel[nCntModel].pColDef[nCntMat] = pMat[nCntMat].MatD3D;
			g_Player.aPlayerModel[nCntModel].pCol[nCntMat] = g_Player.aPlayerModel[nCntModel].pColDef[nCntMat];

			// テクスチャの設定
			g_Player.aPlayerModel[nCntModel].pTex[nCntMat] = NULL;
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// テクスチャがある場合
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Player.aPlayerModel[nCntModel].pTex[nCntMat]);
			}
		}
	}

	// 情報の初期化
	g_Player.pos = D3DXVECTOR3(200.0f, 0.0f, -100.0f);
	g_Player.posOld = D3DXVECTOR3(200.0f, 0.0f, -100.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.vtxMin = D3DXVECTOR3(-PLAYER_COLLISION_SIZE, 0.0f, -PLAYER_COLLISION_SIZE);
	g_Player.vtxMax = D3DXVECTOR3(PLAYER_COLLISION_SIZE, 60.0f, PLAYER_COLLISION_SIZE);
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		g_Player.aPlayerModel[nCntModel].rot = g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[0].aRot[nCntModel];
	}
	g_Player.nLife = PLAYER_LIFE;
	g_Player.bDisp = true;
	g_SiftMove = 0;

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_Player.aPlayerModel != NULL)
	{
		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			// メッシュの開放
			if (g_Player.aPlayerModel[nCntModel].pMesh != NULL)
			{
				g_Player.aPlayerModel[nCntModel].pMesh->Release();
				g_Player.aPlayerModel[nCntModel].pMesh = NULL;
			}

			// マテリアルの開放
			if (g_Player.aPlayerModel[nCntModel].pBuffMat != NULL)
			{
				g_Player.aPlayerModel[nCntModel].pBuffMat->Release();
				g_Player.aPlayerModel[nCntModel].pBuffMat = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//if (g_Player.pos.y <= 0)
	//{
	//	g_Player.move.y = 0;
	//	g_Player.pos.y = 0;
	//	if (GetKeyboardTrigger(DIK_SPACE) == true)
	//	{// [ジャンプ]
	//		g_Player.move.y += PLAYER_JUMP_POWER;
	//		g_VCPlayer.bJump = true;
	//	}
	//}
	COLORBALL *pColBall;
	pColBall = GetColorBall();
	Camera *pCamera = GetCamera();

	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCounterState--;	//カウントダウン
		if (g_Player.nCounterState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.nCounterState--;	//カウントダウン
		if (g_Player.nCounterState <= 0)
		{
			//if (pFade == FADE_NONE)
			//{// フェードが何もしていない状態の場合
			//	SetFade(MODE_RESULT);
			//}
		}
		return;
		break;

	case PLAYERSTATE_END:
		break;
	}
	if (pColBall->state == COLORBALLSTATE_STOP)
	{


		if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{// [左上移動]
				g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// [左下移動]
				g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
			}
			else
			{// [左移動]
				g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_W) == true)
			{// [右上移動]
				g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// [右下移動]
				g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
			}
			else
			{// [右移動]
				g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED * g_SiftMove;
				g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED * g_SiftMove;
				g_Player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// [上移動]
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI) * PLAYER_SPEED* g_SiftMove;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI) * PLAYER_SPEED * g_SiftMove;
			g_Player.rotDest.y = pCamera->rot.y;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// [下移動]
			g_Player.move.x += sinf(pCamera->rot.y) * PLAYER_SPEED * g_SiftMove;
			g_Player.move.z += cosf(pCamera->rot.y) * PLAYER_SPEED * g_SiftMove;
			g_Player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}

		if (GetJoyPadPress(DIJS_BUTTON_10, 0) == true || GetJoyPadPress(DIJS_BUTTON_11, 0) == true ||
			GetJoyPadPress(DIJS_BUTTON_12, 0) == true || GetJoyPadPress(DIJS_BUTTON_13, 0) == true)
		{// 左アナログスティックの入力がされた
			Camera *pCamera;
			pCamera = GetCamera();

			// 移動処理
			g_Player.move.x += sinf(pCamera->rot.y - GetJotPadRightStick(0)) * PLAYER_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - GetJotPadRightStick(0)) * PLAYER_SPEED;

			// 目的の角度変更
			g_Player.rotDest.y = pCamera->rot.y - (GetJotPadRightStick(0) + D3DX_PI);
		}
	}
	// 目的の向きの修正
	if (g_Player.rotDest.y < -D3DX_PI)
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_Player.rotDest.y > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}




	// 目的の向きに更新
	if (g_Player.bJump == true)
	{// 攻撃中ではないまたはジャンプ中の場合
		float fAngle = g_Player.rotDest.y - g_Player.rot.y;
		if (fAngle < -D3DX_PI)
		{
			fAngle += D3DX_PI * 2.0f;
		}
		else if (fAngle > D3DX_PI)
		{
			fAngle -= D3DX_PI * 2.0f;
		}
		g_Player.rot.y += fAngle * PLAYER_ROT_SPEED;
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2.0f;
		}
	}


	if (GetKeyboardPress(DIK_LSHIFT) == true )
	{
		g_SiftMove = 1.5f;
	}
	else
	{
		g_SiftMove = 1.2f;
	}


	if (CollisionObstacle(&g_Player.pos,
		&g_Player.posOld,
		&g_Player.move,
		&g_Player.vtxMin,
		&g_Player.vtxMax) == true)
	{

	}

	// 前回の位置を保持
	g_Player.posOld = g_Player.pos;

	// 重力
	g_Player.move.y -= PLAYER_GRAVITY;

	if (CollisionModel(&g_Player.pos,
		&g_Player.posOld,
		&g_Player.move,
		&g_Player.vtxMin,
		&g_Player.vtxMax,
		&g_Player.pModel) == true)
	{//モデルとの判定
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1,0) == true)
		{
			g_Player.move.y += PLAYER_JUMP_POWER;
			PlaySound(SOUND_LABEL_SE008);
		}

	}

	//if (g_Player.pModel != NULL)
	//{
	//	switch (g_Player.pModel->col)
	//	{
	//	case BLOCKCOLOR_RED:
	//		break;

	//	case BLOCKCOLOR_BLUE:
	//		break;
	//	}
	//}

	// 位置の更新
	if ( g_Player.bJump == true)
	{// 攻撃中ではないまたはジャンプ中の場合
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.z += g_Player.move.z;
	}
	g_Player.pos.y += g_Player.move.y;
	g_Player.bJump = true;
	//落下
	if (g_Player.pos.y < -500.0f && g_Player.move.y < 0.0f)
	{
		FADE *pFade;
		pFade = GetFade();
		if (*pFade != FADE_OUT)
		{
			SetFade(MODE_GAMEOVER);
		}
	}
	// 減速
	g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_DECELERATE;
	if (g_Player.move.x < PLAYER_STOP_SPEED && g_Player.move.x > -PLAYER_STOP_SPEED)
	{
		g_Player.move.x = 0.0f;
	}
	g_Player.move.z += (0.0f - g_Player.move.z) * PLAYER_DECELERATE;
	if (g_Player.move.z < PLAYER_STOP_SPEED && g_Player.move.z > -PLAYER_STOP_SPEED)
	{
		g_Player.move.z = 0.0f;
	}
	if (CollisionGoal(&g_Player.pos,
		&g_Player.posOld,
		&g_Player.move,
		&g_Player.vtxMin,
		&g_Player.vtxMax) == true)
	{
		SetGemeState(GAMESTATE_END);
	}

	SetMotionPlayer();
	MotionPlayer();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		if (g_Player.aPlayerModel[nCntModel].nIdxModelParent == -1)
		{// 親が設定されていない場合
			mtxParent = g_Player.mtxWorld;
		}
		else
		{// 親が設定されている場合
			mtxParent = g_Player.aPlayerModel[g_Player.aPlayerModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aPlayerModel[nCntModel].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aPlayerModel[nCntModel].rot.y, g_Player.aPlayerModel[nCntModel].rot.x, g_Player.aPlayerModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld, &g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aPlayerModel[nCntModel].pos.x, g_Player.aPlayerModel[nCntModel].pos.y, g_Player.aPlayerModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld, &g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxTrans);
		D3DXMatrixMultiply(&g_Player.aPlayerModel[nCntModel].mtxWorld, &g_Player.aPlayerModel[nCntModel].mtxWorld, &mtxParent);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aPlayerModel[nCntModel].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)g_Player.aPlayerModel[nCntModel].nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&g_Player.aPlayerModel[nCntModel].pCol[nCntMat]);

			// テクスチャの設定
			pDevice->SetTexture(0, g_Player.aPlayerModel[nCntModel].pTex[nCntMat]);

			if (g_Player.bDisp == true)
			{
				// モデルの描画
				g_Player.aPlayerModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

///=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	//int nCount;
	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//プレイヤーの体力が0以下になったとき
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCounterState = 60;				//ダメージ状態時間
		g_Player.bDisp = false;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;

	}
}

//=============================================================================
// プレイヤーの当たり判定
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	bool bHit = false;	// 当たったかどうか

	if (pPos->x + vtxMax.x > g_Player.pos.x + g_Player.vtxMin.x
		&& pPos->x + vtxMin.x < g_Player.pos.x + g_Player.vtxMax.x
		&& pPos->z + vtxMax.z > g_Player.pos.z + g_Player.vtxMin.z
		&& pPos->z + vtxMin.z < g_Player.pos.z + g_Player.vtxMax.z)
	{// 配置物の範囲内の場合[幅、奥行]
		if (pPosOld->y + vtxMin.y >= g_Player.posOld.y + g_Player.vtxMax.y
			&& pPos->y + vtxMin.y < g_Player.pos.y + g_Player.vtxMax.y)
		{// 上方にめり込んだ場合
			pPos->y = g_Player.pos.y + g_Player.vtxMax.y - vtxMin.y;
			bHit = true;
		}
		else if (pPosOld->y + vtxMax.y <= g_Player.posOld.y + g_Player.vtxMin.y
			&& pPos->y + vtxMax.y > g_Player.pos.y + g_Player.vtxMin.y)
		{// 下方にめり込んだ場合
			pPos->y = g_Player.pos.y + g_Player.vtxMin.y - vtxMax.y;
			bHit = true;
		}
	}

	if (pPos->y + vtxMax.y > g_Player.pos.y + g_Player.vtxMin.y
		&& pPos->y + vtxMin.y < g_Player.pos.y + g_Player.vtxMax.y)
	{// 配置物の範囲内の場合[高さ]
		if (pPos->x + vtxMax.x > g_Player.pos.x + g_Player.vtxMin.x
			&& pPos->x + vtxMin.x < g_Player.pos.x + g_Player.vtxMax.x)
		{// 配置物の範囲内の場合[幅]
			if (pPosOld->z + vtxMin.z >= g_Player.posOld.z + g_Player.vtxMax.z
				&& pPos->z + vtxMin.z < g_Player.pos.z + g_Player.vtxMax.z)
			{// 後方にめり込んだ場合
				pPos->z = g_Player.pos.z + g_Player.vtxMax.z - vtxMin.z;
				bHit = true;
			}
			else if (pPosOld->z + vtxMax.z <= g_Player.posOld.z + g_Player.vtxMin.z
				&& pPos->z + vtxMax.z > g_Player.pos.z + g_Player.vtxMin.z)
			{// 前方にめり込んだ場合
				pPos->z = g_Player.pos.z + g_Player.vtxMin.z - vtxMax.z;
				bHit = true;
			}
		}

		if (pPos->z + vtxMax.z > g_Player.pos.z + g_Player.vtxMin.z
			&& pPos->z + vtxMin.z < g_Player.pos.z + g_Player.vtxMax.z)
		{// 配置物の範囲内の場合[奥行]
			if (pPosOld->x + vtxMin.x >= g_Player.posOld.x + g_Player.vtxMax.x
				&& pPos->x + vtxMin.x < g_Player.pos.x + g_Player.vtxMax.x)
			{// 右方にめり込んだ場合
				pPos->x = g_Player.pos.x + g_Player.vtxMax.x - vtxMin.x;
				bHit = true;
			}
			else if (pPosOld->x + vtxMax.x <= g_Player.posOld.x + g_Player.vtxMin.x
				&& pPos->x + vtxMax.x > g_Player.pos.x + g_Player.vtxMin.x)
			{// 左方にめり込んだ場合
				pPos->x = g_Player.pos.x + g_Player.vtxMin.x - vtxMax.x;
				bHit = true;
			}
		}
	}
	return bHit;
}

//=============================================================================
// プレイヤーのモーションの設定
//=============================================================================
void SetMotionPlayer(void)
{
	PLAYERMOTIONTYPE motionType = g_Player.motionType;

	switch (g_Player.motionType)
	{
	case PLAYERMOTIONTYPE_NEUTRAL:
		if (g_Player.move.x >= PLAYER_NEUTRAL_SPEED || g_Player.move.x <= -PLAYER_NEUTRAL_SPEED
			|| g_Player.move.z >= PLAYER_NEUTRAL_SPEED || g_Player.move.z <= -PLAYER_NEUTRAL_SPEED)
		{
			motionType = PLAYERMOTIONTYPE_MOVE;
		}
		break;
	case PLAYERMOTIONTYPE_MOVE:
		if (g_Player.move.x <= PLAYER_NEUTRAL_SPEED && g_Player.move.x >= -PLAYER_NEUTRAL_SPEED
			&& g_Player.move.z <= PLAYER_NEUTRAL_SPEED && g_Player.move.z >= -PLAYER_NEUTRAL_SPEED)
		{
			motionType = PLAYERMOTIONTYPE_NEUTRAL;
		}
		break;

	}
	if (g_Player.motionType != motionType)
	{// 現在のモーションと違った場合
		g_Player.nKey = 0;
		g_Player.motionType = motionType;
		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aPlayerModel[nCntModel].pos = g_Player.aPlayerModel[nCntModel].posFarst;
			g_Player.aPlayerModel[nCntModel].rot = g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[0].aRot[nCntModel];
		}
		g_Player.nCntFrame = 0;
		g_Player.nMaxCntFrame = 0;
	}
}

//=============================================================================
// モーション処理
//=============================================================================
void MotionPlayer(void)
{
	if (g_Player.nCntFrame == g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[g_Player.nKey].nNumFrame)
	{// 一定フレーム経過した場合[キー更新]
		if (g_Player.aPlayerMotion[g_Player.motionType].nLoop == false)
		{// ループしない場合
			if (g_Player.nKey < g_Player.aPlayerMotion[g_Player.motionType].nNumKey)
			{// キー数を越えていない場合
				g_Player.nKey++;
			}
		}
		else
		{// ループする場合
			g_Player.nKey = (g_Player.nKey + 1) % g_Player.aPlayerMotion[g_Player.motionType].nNumKey;
			if (g_Player.nKey == 0)
			{// 最初のキーに戻った場合
				g_Player.nMaxCntFrame = 0;
			}
		}
		g_Player.nCntFrame = 0;
	}

	// モーション更新
	if (g_Player.nKey < g_Player.aPlayerMotion[g_Player.motionType].nNumKey)
	{// キー数を越えていない場合
		D3DXVECTOR3 angle;
		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			g_Player.aPlayerModel[nCntModel].pos += (g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[(g_Player.nKey + 1) % g_Player.aPlayerMotion[g_Player.motionType].nNumKey].aPos[nCntModel] - g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[g_Player.nKey].aPos[nCntModel]) / (float)g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[g_Player.nKey].nNumFrame;
			angle = g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[(g_Player.nKey + 1) % g_Player.aPlayerMotion[g_Player.motionType].nNumKey].aRot[nCntModel] - g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[g_Player.nKey].aRot[nCntModel];
			if (angle.x  < -D3DX_PI)
			{
				angle.x += D3DX_PI * 2.0f;
			}
			else if (angle.x > D3DX_PI)
			{
				angle.x -= D3DX_PI * 2.0f;
			}
			if (angle.y  < -D3DX_PI)
			{
				angle.y += D3DX_PI * 2.0f;
			}
			else if (angle.y > D3DX_PI)
			{
				angle.y -= D3DX_PI * 2.0f;
			}
			if (angle.z  < -D3DX_PI)
			{
				angle.z += D3DX_PI * 2.0f;
			}
			else if (angle.z > D3DX_PI)
			{
				angle.z -= D3DX_PI * 2.0f;
			}

			g_Player.aPlayerModel[nCntModel].rot += angle / (float)g_Player.aPlayerMotion[g_Player.motionType].aPlayerKey[g_Player.nKey].nNumFrame;
			if (g_Player.aPlayerModel[nCntModel].rot.x  < -D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			else if (g_Player.aPlayerModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			if (g_Player.aPlayerModel[nCntModel].rot.y  < -D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			else if (g_Player.aPlayerModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_Player.aPlayerModel[nCntModel].rot.z  < -D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
			else if (g_Player.aPlayerModel[nCntModel].rot.z > D3DX_PI)
			{
				g_Player.aPlayerModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
		}
	}

	g_Player.nCntFrame++;
	g_Player.nMaxCntFrame++;
}

//=============================================================================
// ロード処理
//=============================================================================
void LoadPlayer(void)
{
	FILE *pFile;
	char read[128];
	int nCntModel = 0, nCntMotion = 0, nCntKey, nCntColl;

	pFile = fopen(PLAYER_FILENAME_LOAD, "r");
	if (pFile != NULL)
	{// ファイルが開けた場合
		do
		{
			fscanf(pFile, "%s", &read[0]);
			if (strcmp(&read[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s%d", &read[0], &g_Player.nNumModel);
				g_Player.aPlayerModel = new PlayerModel[g_Player.nNumModel];
			}
			else if (strcmp(&read[0], "MODEL_FILENAME") == 0 && nCntModel < g_Player.nNumModel)
			{
				fscanf(pFile, "%s%s", &read[0], &g_Player.aPlayerModel[nCntModel].aName[0]);
				nCntModel++;
			}
			else if (strcmp(&read[0], "CHARACTERSET") == 0)
			{
				nCntModel = 0;
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "PARTSSET") == 0 && nCntModel < g_Player.nNumModel)
					{
						do
						{
							fscanf(pFile, "%s", &read[0]);
							if (strcmp(&read[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s%d", &read[0], &g_Player.aPlayerModel[nCntModel].nIdxModelParent);
							}
							else if (strcmp(&read[0], "POS") == 0)
							{
								fscanf(pFile, "%s%f%f%f", &read[0], &g_Player.aPlayerModel[nCntModel].pos.x, &g_Player.aPlayerModel[nCntModel].pos.y, &g_Player.aPlayerModel[nCntModel].pos.z);
								g_Player.aPlayerModel[nCntModel].posFarst = g_Player.aPlayerModel[nCntModel].pos;
							}
							else if (strcmp(&read[0], "ROT") == 0)
							{
								fscanf(pFile, "%s%f%f%f", &read[0], &g_Player.aPlayerModel[nCntModel].rot.x, &g_Player.aPlayerModel[nCntModel].rot.y, &g_Player.aPlayerModel[nCntModel].rot.z);
							}
						} while (strcmp(&read[0], "END_PARTSSET") != 0);
						nCntModel++;
					}
				} while (strcmp(&read[0], "END_CHARACTERSET") != 0);
			}
			else if (strcmp(&read[0], "MOTIONSET") == 0 && nCntMotion < PLAYERMOTIONTYPE_MAX)
			{
				nCntKey = 0;
				nCntColl = 0;
				do
				{
					fscanf(pFile, "%s", &read[0]);
					if (strcmp(&read[0], "LOOP") == 0)
					{
						fscanf(pFile, "%s%d", &read[0], &g_Player.aPlayerMotion[nCntMotion].nLoop);
					}
					else if (strcmp(&read[0], "NUM_KEY") == 0)
					{
						fscanf(pFile, "%s%d", &read[0], &g_Player.aPlayerMotion[nCntMotion].nNumKey);
						g_Player.aPlayerMotion[nCntMotion].aPlayerKey = new PlayerKey[g_Player.aPlayerMotion[nCntMotion].nNumKey];
					}
					else if (strcmp(&read[0], "KEYSET") == 0 && nCntKey < g_Player.aPlayerMotion[nCntMotion].nNumKey)
					{
						nCntModel = 0;
						g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aPos = new D3DXVECTOR3[g_Player.nNumModel];
						g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aRot = new D3DXVECTOR3[g_Player.nNumModel];
						do
						{
							fscanf(pFile, "%s", &read[0]);
							if (strcmp(&read[0], "#") == 0)
							{
								do
								{
									fscanf(pFile, "%c", &read[0]);
								} while (strcmp(&read[0], "\n") != 0);
							}
							else if (strcmp(&read[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s%d", &read[0], &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].nNumFrame);
							}
							else if (strcmp(&read[0], "KEY") == 0 && nCntModel < g_Player.nNumModel)
							{
								do
								{
									fscanf(pFile, "%s", &read[0]);
									if (strcmp(&read[0], "POS") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &read[0], &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aPos[nCntModel].x, &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aPos[nCntModel].y, &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aPos[nCntModel].z);
									}
									else if (strcmp(&read[0], "ROT") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &read[0], &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aRot[nCntModel].x, &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aRot[nCntModel].y, &g_Player.aPlayerMotion[nCntMotion].aPlayerKey[nCntKey].aRot[nCntModel].z);
									}
								} while (strcmp(&read[0], "END_KEY") != 0);
								nCntModel++;
							}
						} while (strcmp(&read[0], "END_KEYSET") != 0);
						nCntKey++;
					}
				} while (strcmp(&read[0], "END_MOTIONSET") != 0);
				nCntMotion++;
			}
		} while (strcmp(&read[0], "END_SCRIPT") != 0);
		fclose(pFile);
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}
