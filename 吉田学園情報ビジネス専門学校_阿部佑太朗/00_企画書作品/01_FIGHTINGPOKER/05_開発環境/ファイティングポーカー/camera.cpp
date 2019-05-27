//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// カメラ処理 [camera.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "camera.h"
#include "player.h"
#include "main.h"
#include "battle.h"
#include "cardModel.h"
#include "fade.h"
#include "game.h"
#include "gamefade.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define POS_V_1P	D3DXVECTOR3(0.0f, 750.0f, -100.0f)		// 1P時の視点
#define POS_R_1P	D3DXVECTOR3(0.0f, 0.0f, 0.0f)			// 1P時の注視点
#define POS_V_2P	D3DXVECTOR3(-200.0f, 750.0f, 150.0f)	// 2P時の視点
#define POS_R_2P	D3DXVECTOR3(-200.0f, 0.0f, 50.0f)		// 2P時の注視点
#define POS_V_ALL	D3DXVECTOR3(0.0f,650.0f,-100.0f)		// 終了時の視点
#define POS_R_ALL	D3DXVECTOR3(0.0f,0.0f,0.0f)				// 終了時の注視点

#define CAMERA_V_CHASE		(0.1f)		// 視点の追跡割合
#define CAMERA_R_CHASE		(0.5f)		// 注視点の追跡割合
#define CAMERA_VR_LENGTH	(10.0f)		// カメラの距離

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXVECTOR3 rot;			// 角度
	D3DVIEWPORT9 viewport;		// ビューポート
}CameraInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
Camera g_aCamera[MAX_CAMERA];	// カメラの情報

// バトルモードのカメラ情報
CameraInfo g_aInfoBattleCamera[BATTLE_CAMERA_TYPE_MAX] =
{
	// メインカメラ
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 100.0f, -270.0f) ,	D3DXVECTOR3(0.0f, 100.0f, 0.0f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x位置,			y位置,					幅,					高さ,			奥行Min,	奥行Max
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f) ,		{0,						0,						SCREEN_WIDTH,		SCREEN_HEIGHT,	0.0f,		1.0f } },
};

// プレイヤーショウモードのカメラ情報
CameraInfo g_aInfoPlayerShowCamera[PLAYERSHOW_CAMERA_TYPE_MAX] =
{
	// 1Pビューポートカメラ
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f) ,	D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x位置,			y位置,					幅,					高さ,			奥行Min,	奥行Max
	D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f) ,		{ 0,					0,						SCREEN_WIDTH / 2,	700,			0.0f,		1.0f } },

	// 2Pビューポートカメラ
	// posV,								posR,							vecU,
	{ D3DXVECTOR3(0.0f, 0.0f, -150.0f) ,	D3DXVECTOR3(0.0f, 0.0f, -50.0f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x位置,			y位置,					幅,					高さ,			奥行Min,	奥行Max
	D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f),		{ SCREEN_WIDTH / 2,		0,						SCREEN_WIDTH / 2,	700,			0.0f,		1.0f } },

	// 3DUIビューポートカメラ
	// posV,								posR,							vecU,
	{ POS_V_ALL ,							POS_R_ALL,						D3DXVECTOR3(0.0f, 1.0f, 0.0f),
	// rot,									viewport x位置,			y位置,					幅,					高さ,			奥行Min,	奥行Max
	D3DXVECTOR3(0.0f, 0.0f, 0.0f) ,			{ 0,					0,						SCREEN_WIDTH,		SCREEN_HEIGHT,	0.0f,		1.0f } },
};
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// カメラの初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitCamera(void)
{
	MODE Mode = GetMode();

	CARDSIDE side = GetPokerState();
	GAMEMODE GameMode = GetGameMode();
	FADE pFade;
	pFade = GetFade();

	if (Mode != MODE_GAME)
	{ // モードゲーム以外
	  /* ポーカーの時 */
		g_aCamera[0].posV = POS_V_1P;										// 視点
		g_aCamera[0].posR = POS_R_1P;										// 注視点
		g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// 上方向ベクトル
		g_aCamera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転
		g_aCamera[0].fLength = g_aCamera[0].posR.z - g_aCamera[0].posV.z;	// Zの距離
																			//======== [ ビューポート ] ===========//
		g_aCamera[0].viewport.X = 0;										// 位置
		g_aCamera[0].viewport.Y = 0;										// 位置
		g_aCamera[0].viewport.Width = SCREEN_WIDTH;							// 幅
		g_aCamera[0].viewport.Height = SCREEN_HEIGHT;						// 高さ
		g_aCamera[0].viewport.MinZ = 0.0f;									// 奥行き
		g_aCamera[0].viewport.MaxZ = 1.0f;									// 奥行き
	}
	else
	{
		switch (GameMode)
		{
		case GAMEMODE_POKER:	// ポーカーモードの場合
			/* ポーカーの時 */
			g_aCamera[0].posV = POS_V_1P;										// 視点
			g_aCamera[0].posR = POS_R_1P;										// 注視点
			g_aCamera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// 上方向ベクトル
			g_aCamera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 回転
			g_aCamera[0].fLength = g_aCamera[0].posR.z - g_aCamera[0].posV.z;	// Zの距離
			//======== [ ビューポート ] ===========//
			g_aCamera[0].viewport.X = 0;										// 位置
			g_aCamera[0].viewport.Y = 0;										// 位置
			g_aCamera[0].viewport.Width = SCREEN_WIDTH;							// 幅
			g_aCamera[0].viewport.Height = SCREEN_HEIGHT;						// 高さ
			g_aCamera[0].viewport.MinZ = 0.0f;									// 奥行き
			g_aCamera[0].viewport.MaxZ = 1.0f;									// 奥行き
			break;
		case GAMEMODE_PLAYERSHOW:	//
			for (int nCntCamera = 0; nCntCamera < PLAYERSHOW_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoPlayerShowCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoPlayerShowCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoPlayerShowCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoPlayerShowCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoPlayerShowCamera[nCntCamera].viewport;
			}
			break;
		case GAMEMODE_BATTLE:	// バトルモードの場合
			for (int nCntCamera = 0; nCntCamera < BATTLE_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoBattleCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoBattleCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoBattleCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoBattleCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoBattleCamera[nCntCamera].viewport;
			}
			break;
		case GAMEMODE_RESULT:	//
			for (int nCntCamera = 0; nCntCamera < PLAYERSHOW_CAMERA_TYPE_MAX; nCntCamera++)
			{
				g_aCamera[nCntCamera].posV = g_aInfoPlayerShowCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posVDest = g_aCamera[nCntCamera].posV;
				g_aCamera[nCntCamera].posR = g_aInfoPlayerShowCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].posRDest = g_aCamera[nCntCamera].posR;
				g_aCamera[nCntCamera].vecU = g_aInfoPlayerShowCamera[nCntCamera].vecU;
				g_aCamera[nCntCamera].rot = g_aInfoPlayerShowCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].rotDest = g_aCamera[nCntCamera].rot;
				g_aCamera[nCntCamera].fLength = g_aCamera[nCntCamera].posR.z - g_aCamera[nCntCamera].posV.z;
				g_aCamera[nCntCamera].fHeight = g_aCamera[nCntCamera].posR.y - g_aCamera[nCntCamera].posV.y;
				g_aCamera[nCntCamera].viewport = g_aInfoPlayerShowCamera[nCntCamera].viewport;
			}
			break;
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// カメラの終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitCamera(void)
{
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// カメラの更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();
	pPlayer = GetPlayer();

	CARDSIDE side = GetPokerState();
	GAMEMODE GameMode = GetGameMode();
	GAMEFADE pGameFade;
	pGameFade = GetGameFade();

	switch (GameMode)
	{
	case GAMEMODE_POKER:	// ポーカーモードの場合
		if (pGameFade == FADE_IN)
		{
			if (side == CARD_SIDE_1P)
			{// 1P操作時のカメラ
				g_aCamera[0].posV = POS_V_1P;	// 視点
				g_aCamera[0].posR = POS_R_1P;	// 注視点
			}
			else if (side == CARD_SIDE_2P)
			{// 2P操作時のカメラ
				g_aCamera[0].posV = POS_V_2P;	// 視点
				g_aCamera[0].posR = POS_R_2P;	// 注視点
			}
		}
		break;
	case GAMEMODE_PLAYERSHOW:	// プレイヤーショウの場合
		// 1Pビューポートカメラ
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x - sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z - cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 250.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x + sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z + cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 250.0f;

		// 2Pビューポートカメラ
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x - sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z - cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 250.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x + sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z + cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 250.0f;
		break;
	case GAMEMODE_BATTLE:	// バトルモード
		if (pPlayer->bUse == true)
		{
			Player *pPlayer = GetPlayer();
			BATTLESTATE BattleState = GetBattleState();

			float fWidth = pPlayer[0].pos.x - pPlayer[1].pos.x;
			float fHeight = pPlayer[0].pos.y - pPlayer[1].pos.y;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x = pPlayer[0].pos.x - fWidth / 2;
			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.y = pPlayer[0].pos.y - fHeight / 2 + 50.0f;
			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 5.0f;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.x = g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x + sinf(g_aCamera[BATTLE_CAMERA_TYPE_MAIN].rot.y) * g_aCamera[BATTLE_CAMERA_TYPE_MAIN].fLength;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.y = pPlayer[0].pos.y - fHeight / 2 + 50.0f;

			g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.z = g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.z + cosf(g_aCamera[BATTLE_CAMERA_TYPE_MAIN].rot.y) * g_aCamera[BATTLE_CAMERA_TYPE_MAIN].fLength;

			if (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x >= PLAYER_MOVE_LIMIT_LEFT + float(PLAYER_MOVE_RIMIT) / 2.0f
				&& g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.x <= PLAYER_MOVE_LIMIT_RIGHT - float(PLAYER_MOVE_RIMIT) / 2.0)
			{
				// 現在の位置に差分の何割かを代入
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR) * CAMERA_R_CHASE;
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV) * CAMERA_V_CHASE;
			}
			else
			{// Y方向は常に行う
				// 現在の位置に差分の何割かを代入
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR.y += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posRDest.y - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posR.y) * CAMERA_R_CHASE;
				g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV.y += (g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posVDest.y - g_aCamera[BATTLE_CAMERA_TYPE_MAIN].posV.y) * CAMERA_V_CHASE;
			}

		}
		break;
	case GAMEMODE_RESULT:	// リザルトの場合
		// 1Pビューポートカメラ
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.x - sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posR.z - cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 200.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV = pPlayer[0].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.x + sinf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER01].posV.z + cosf(pPlayer[0].rot.y - D3DX_PI + D3DX_PI / 5.0f) * 200.0f;

		// 2Pビューポートカメラ
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.x - sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posR.z - cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 200.0f;

		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV = pPlayer[1].pos;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.y + 50.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.x + sinf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 100.0f;
		g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z = g_aCamera[PLAYERSHOW_CAMERA_TYPE_PLAYER02].posV.z + cosf(pPlayer[1].rot.y + D3DX_PI - D3DX_PI / 5.0f) * 200.0f;
		break;
	}

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// カメラの設定処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetCamera(int nIdyCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nIdyCamera].mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_aCamera[nIdyCamera].mtxProjection,
								D3DXToRadian(45.0f),	// 画角、視野角
								(float)g_aCamera[nIdyCamera].viewport.Width / (float)g_aCamera[nIdyCamera].viewport.Height,
								10.0f,					// 10.0f~
								7000.0f);				// 1000.fの間のポリゴンだけを描画

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_aCamera[nIdyCamera].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_aCamera[nIdyCamera].mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_aCamera[nIdyCamera].mtxView,
						&g_aCamera[nIdyCamera].posV,
						&g_aCamera[nIdyCamera].posR,
						&g_aCamera[nIdyCamera].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_aCamera[nIdyCamera].mtxView);

	// ビューポートの設定
	pDevice->SetViewport(&g_aCamera[nIdyCamera].viewport);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// カメラの取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Camera *GetCamera(void)
{
	return &g_aCamera[0];
}
