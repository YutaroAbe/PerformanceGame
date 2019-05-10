//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_POSV_Y			(140.0f)	// カメラの初期視点[高さ]
#define CAMERA_POSV_Z			(-300.0f)	// カメラの初期視点[奥行]
#define CAMERA_POSR_Y			(50.0f)		// カメラの初期注視点[高さ]
#define CAMERA_SPEED			(2.0f)		// カメラの平行移動速度
#define CAMERA_ROT_SPEED		(0.025f)		// カメラの回転速度
#define CAMERA_ZOOMIN_MAX		(50.0f)		// カメラの最大拡大距離
#define CAMERA_ZOOMOUT_MAX		(500.0f)	// カメラの最大縮小距離
#define CAMERA_PLAYER_MIN		(20.0f)		// 注視点とプレイヤーの最低距離
#define CAMERA_PLAYER_ADD		(10.0f)		// 移動量により加算される距離
#define CAMERA_FOLLOW_MIN_R		(0.05f)		// 注視点の最低追跡速度
#define CAMERA_FOLLOW_MIN_V		(0.04f)		// 視点の最低追跡速度
#define CAMERA_FOLLOW_ADD		(0.01f)		// 移動量により加算される追跡速度
#define CAMERA_AROUND_TIME		(60 * 2)	// 回り込みを開始するまでの時間
#define CAMERA_AROUND_SPEED		(0.02f)		// カメラの回り込み速度
#define CAMERA_MOVIE_SPEED		(0.005f)	// 紹介映像での回転速度

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_aCamera[2];	// カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{

	g_aCamera[0].Viewport.X = 0;
	g_aCamera[0].Viewport.Y = 0;
	g_aCamera[0].Viewport.Width = SCREEN_WIDTH;
	g_aCamera[0].Viewport.Height = SCREEN_HEIGHT;
	g_aCamera[0].Viewport.MinZ = 0.0f;
	g_aCamera[0].Viewport.MaxZ = 1.0f;


	g_aCamera[0].posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -750.0f);
	g_aCamera[0].posR = D3DXVECTOR3(0.0f, CAMERA_POSR_Y, -450.0f);

	g_aCamera[0].posVDest = g_aCamera[0].posV;
	g_aCamera[0].posRDest = g_aCamera[0].posR;
	g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aCamera[0].rot = D3DXVECTOR3(0.0f, atan2f((g_aCamera[0].posV.x - g_aCamera[0].posR.x),
		(g_aCamera[0].posV.z - g_aCamera[0].posR.z)), 0.0f);
	g_aCamera[0].rotDest = g_aCamera[0].rot;
	g_aCamera[0].fLength = sqrtf((g_aCamera[0].posV.x - g_aCamera[0].posR.x) * (g_aCamera[0].posV.x - g_aCamera[0].posR.x) +
		(g_aCamera[0].posV.z - g_aCamera[0].posR.z) * (g_aCamera[0].posV.z - g_aCamera[0].posR.z));
	g_aCamera[0].nCntStop = 0;
	g_aCamera[0].bOperation = false;

	g_aCamera[1].Viewport.X = 928;
	g_aCamera[1].Viewport.Y = 10;
	g_aCamera[1].Viewport.Width = 205;
	g_aCamera[1].Viewport.Height = 162;
	g_aCamera[1].Viewport.MinZ = 0.0f;
	g_aCamera[1].Viewport.MaxZ = 1.0f;

	g_aCamera[1].posV = D3DXVECTOR3(0.0f, 50.0f, 70.0f);
	g_aCamera[1].posR = D3DXVECTOR3(0.0f, -5.0f, 5.0f);
	g_aCamera[1].vecU = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	g_aCamera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{

		if (GetKeyboardPress(DIK_UP) == true)
		{// カメラ前方移動
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - D3DX_PI) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - D3DX_PI) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// カメラ後方移動
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{// カメラ左移動
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - (-D3DX_PI * 0.5f)) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - (-D3DX_PI * 0.5f)) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// カメラ右移動
			g_aCamera[0].posV.x += sinf(g_aCamera[0].rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
			g_aCamera[0].posV.z += cosf(g_aCamera[0].rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_Q) == true)
		{// 注視点左旋回
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_E) == true)
		{// 注視点右旋回
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}

			g_aCamera[0].posR.x = sinf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.x;
			g_aCamera[0].posR.z = cosf(g_aCamera[0].rot.y - D3DX_PI) * g_aCamera[0].fLength + g_aCamera[0].posV.z;
		}
		else if (GetKeyboardPress(DIK_Z) == true)
		{// 視点左旋回
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}

			g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
			g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
		}
		else if (GetKeyboardPress(DIK_C) == true)
		{// 視点右旋回
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}

			g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
			g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
		}
		else if (GetKeyboardPress(DIK_Y) == true)
		{// 視点上昇
			g_aCamera[0].posV.y += CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_N) == true)
		{// 視点下降
			g_aCamera[0].posV.y -= CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_T) == true)
		{// 注視点上昇
			g_aCamera[0].posR.y += CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_B) == true)
		{// 注視点下降
			g_aCamera[0].posR.y -= CAMERA_SPEED;
		}
		else if (GetKeyboardPress(DIK_U) == true)
		{// 視点拡大
			if (g_aCamera[0].fLength >= CAMERA_ZOOMIN_MAX)
			{// 距離が最大拡大距離以上の場合
				g_aCamera[0].fLength -= CAMERA_SPEED;
				g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
				g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
			}
		}
		else if (GetKeyboardPress(DIK_M) == true)
		{// 視点縮小
			if (g_aCamera[0].fLength <= CAMERA_ZOOMOUT_MAX)
			{// 距離が最大縮小距離以下の場合
				g_aCamera[0].fLength += CAMERA_SPEED;
				g_aCamera[0].posV.x = sinf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.x;
				g_aCamera[0].posV.z = cosf(g_aCamera[0].rot.y) * g_aCamera[0].fLength + g_aCamera[0].posR.z;
			}
		}


		Player *pPlayer = GetPlayer();
		D3DXVECTOR3 move = pPlayer->move;

		// 移動量が負の場合正に直す
		if (move.x < 0.0f)
		{
			move.x *= -1;
		}
		if (move.y < 0.0f)
		{
			move.y *= -1;
		}
		if (move.z < 0.0f)
		{
			move.z *= -1;
		}

		if (pPlayer->move == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{// プレイヤーが移動していない場合
			g_aCamera[0].nCntStop++;
		}
		else
		{// プレイヤーが移動している場合
			g_aCamera[0].nCntStop = 0;
		}

		//// プレイヤーの背後に回り込む
		//if (g_aCamera[0].nCntStop >= CAMERA_AROUND_TIME)
		//{
		//	g_aCamera[0].rotDest.y = pPlayer->rot.y - g_aCamera[0].rot.y;
		//	if (g_aCamera[0].rotDest.y < -D3DX_PI)
		//	{
		//		g_aCamera[0].rotDest.y += D3DX_PI * 2.0f;
		//	}
		//	else if (g_aCamera[0].rotDest.y > D3DX_PI)
		//	{
		//		g_aCamera[0].rotDest.y -= D3DX_PI * 2.0f;
		//	}

		//	g_aCamera[0].rot.y += g_aCamera[0].rotDest.y * CAMERA_AROUND_SPEED;
		//	if (g_aCamera[0].rot.y < -D3DX_PI)
		//	{
		//		g_aCamera[0].rot.y += D3DX_PI * 2.0f;
		//	}
		//	else if (g_aCamera[0].rot.y > D3DX_PI)
		//	{
		//		g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
		//	}
		//}

		if (GetKeyboardPress(DIK_LEFT) == true)
		{// 視点右旋回
			g_aCamera[0].rot.y -= CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y < -D3DX_PI)
			{
				g_aCamera[0].rot.y += D3DX_PI * 2.0f;
			}
			g_aCamera[0].nCntStop = 0;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// 視点左旋回
			g_aCamera[0].rot.y += CAMERA_ROT_SPEED;
			if (g_aCamera[0].rot.y > D3DX_PI)
			{
				g_aCamera[0].rot.y -= D3DX_PI * 2.0f;
			}
			g_aCamera[0].nCntStop = 0;
		}

		// 目的の注視点と視点を設定
		g_aCamera[0].posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y - D3DX_PI) * (CAMERA_PLAYER_MIN + move.x * CAMERA_PLAYER_ADD);
		g_aCamera[0].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y - D3DX_PI) * (CAMERA_PLAYER_MIN + move.z * CAMERA_PLAYER_ADD);
		g_aCamera[0].posRDest.y = pPlayer->pos.y + CAMERA_POSR_Y;
		g_aCamera[0].posVDest.x = g_aCamera[0].posRDest.x + sinf(g_aCamera[0].rot.y) * (g_aCamera[0].fLength + move.x * CAMERA_PLAYER_ADD);
		g_aCamera[0].posVDest.z = g_aCamera[0].posRDest.z + cosf(g_aCamera[0].rot.y) * (g_aCamera[0].fLength + move.z * CAMERA_PLAYER_ADD);
		g_aCamera[0].posVDest.y = g_aCamera[0].posRDest.y + (CAMERA_POSV_Y - CAMERA_POSR_Y);

		// カメラをプレイヤーに合わせる
		g_aCamera[0].posR.x += (g_aCamera[0].posRDest.x - g_aCamera[0].posR.x) * (CAMERA_FOLLOW_MIN_R + move.x * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posR.z += (g_aCamera[0].posRDest.z - g_aCamera[0].posR.z) * (CAMERA_FOLLOW_MIN_R + move.z * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posR.y += (g_aCamera[0].posRDest.y - g_aCamera[0].posR.y) * CAMERA_FOLLOW_MIN_R;
		g_aCamera[0].posV.x += (g_aCamera[0].posVDest.x - g_aCamera[0].posV.x) * (CAMERA_FOLLOW_MIN_V + move.x * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posV.z += (g_aCamera[0].posVDest.z - g_aCamera[0].posV.z) * (CAMERA_FOLLOW_MIN_V + move.z * CAMERA_FOLLOW_ADD);
		g_aCamera[0].posV.y += (g_aCamera[0].posVDest.y - g_aCamera[0].posV.y) * CAMERA_FOLLOW_MIN_V;

}
//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(int IdxViewport)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

												//　ビューポートの設定
	pDevice->SetViewport(&g_aCamera[IdxViewport].Viewport);

												// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[IdxViewport].mtxProjection);

	if (IdxViewport == 0)
	{
		// プロジェクションマトリックスを作成
		D3DXMatrixPerspectiveFovLH(&g_aCamera[IdxViewport].mtxProjection,
			D3DXToRadian(45.0f),
			(float)g_aCamera[IdxViewport].Viewport.Width / (float)g_aCamera[IdxViewport].Viewport.Height,
			10.0f,
			6000.0f);
	}
	if (IdxViewport == 1)
	{
		// プロジェクションマトリックスを作成
		D3DXMatrixPerspectiveFovLH(&g_aCamera[IdxViewport].mtxProjection,
			D3DXToRadian(30.0f),
			(float)g_aCamera[IdxViewport].Viewport.Width / (float)g_aCamera[IdxViewport].Viewport.Height,
			10.0f,
			6000.0f);
	}
	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[IdxViewport].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[IdxViewport].mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_aCamera[IdxViewport].mtxView
		, &g_aCamera[IdxViewport].posV
		, &g_aCamera[IdxViewport].posR
		, &g_aCamera[IdxViewport].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[IdxViewport].mtxView);
}

//=============================================================================
// カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}
