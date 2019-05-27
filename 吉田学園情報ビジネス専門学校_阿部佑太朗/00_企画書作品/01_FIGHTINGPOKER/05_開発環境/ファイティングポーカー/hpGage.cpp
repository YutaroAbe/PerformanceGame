//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// HPゲージ処理 [hpGage.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "hpGage.h"
#include "main.h"
#include "game.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define HPGAGE_MAX					(10)				// HPゲージの最大数
#define HPGAGE_WIDTH				(500)				// 幅
#define HPGAGE_HEIGHT				(70)				// 高さ
#define HPGAGE_FRAME_WIDTH			(10)				// 枠の幅
#define HPGAGE_DEST_APPROX			(0.5f)				// 目的地の近似値
#define HPGAGE_ADD_FRAME			(10)				// HPゲージの目的の値までにかかるフレーム数
#define HPGAGE_ADD_FRAME_RED		(60)				// 赤HPゲージの目的の値までにかかるフレーム数
#define HPGAGE_RED_ADD_START_FRAME	(90)				// 赤HPゲージの減少開始までにかかるフレーム数

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // テクスチャの種類の列挙体
	HPGAGE_TEX_FRAME = 0,	// フレーム
	HPGAGE_TEX_HPBLACK,		// HP黒
	HPGAGE_TEX_HPRED,		// HP赤
	HPGAGE_TEX_HP,			// HP
	HPGAGE_TEX_MAX,			// 総数
}HPGAGE_TEX_NAME;

typedef enum
{ // 状態の列挙体
	HPGAGE_STATE_NONE = 0,	// 通常状態
	HPGAGE_STATE_UP,		// 上昇状態
	HPGAGE_STATE_DOWN,		// 減少状態
	HPGAGE_STATE_MAX,		// 総数
}HPGAGE_STATE;

typedef struct
{
	char *pFilename;	// ファイル名
} HpGageTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fHeight;			// 高さ
	float fInitWidth;		// 初期幅
	float fDestWidth;		// 目的の幅
	float fAddWidth;		// 幅の増減値
	float fFrameWidth;		// 枠の幅
	HPGAGE_TYPE type;		// 種類
	int nTexType;			// テクスチャの種類
	HPGAGE_STATE state;		// 状態
	bool bUse;				// 使用しているかどうか
}HpGage;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexHpGage(LPDIRECT3DDEVICE9 pDevice);
void UpdateVertexHpGage(void);
void UpdateVertexHpGage(int nCntHpGage);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTextureHpGage[HPGAGE_TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHpGage = NULL;				// 頂点バッファへのポインタ
HpGage					g_aHpGage[HPGAGE_TYPE_MAX];				// HPゲージの情報
int						g_aLife[MAX_PLAYER];					// ライフ
int						g_aRedLifeGageCounter[MAX_PLAYER];		// 赤ライフのカウンター
// 読み込むテクスチャ名の設定
HpGageTexInfo g_apTextureHpGageTInfo[HPGAGE_TEX_MAX] =
{
	{ "" },		// フレーム
	{ "" },		// HP黒
	{ "data//TEXTURE//Life_Red.jpg" },		// HP赤
	{ "data//TEXTURE//Life_Normal.jpg" },	// HP
};


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitHpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 情報の初期化
	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		g_aHpGage[nCntHpGage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHpGage[nCntHpGage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aHpGage[nCntHpGage].fWidth = 0.0f;
		g_aHpGage[nCntHpGage].fHeight = 0.0f;
		g_aHpGage[nCntHpGage].fInitWidth = 0.0f;
		g_aHpGage[nCntHpGage].fDestWidth = 0.0f;
		g_aHpGage[nCntHpGage].fFrameWidth = 0.0f;
		g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
		g_aHpGage[nCntHpGage].type = HPGAGE_TYPE_1P_FRAME;
		g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
		g_aHpGage[nCntHpGage].bUse = false;
	}

	for (int nCntHpGageTex = 0; nCntHpGageTex < HPGAGE_TEX_MAX; nCntHpGageTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureHpGageTInfo[nCntHpGageTex].pFilename,
			&g_pTextureHpGage[nCntHpGageTex]);
	}

	// 頂点情報の作成
	MakeVertexHpGage(pDevice);

	// HP情報の初期化
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // プレイヤー人数分回す
		g_aLife[nCntPlayer] = PLAYER_LIFE;
	}
	
	SetHpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100.0f, HPGAGE_HEIGHT / 2.0f + 10.0f, 0.0f), PLAYER_CONTROL_1P);
	SetHpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, HPGAGE_HEIGHT / 2.0f + 10.0f, 0.0f), PLAYER_CONTROL_2P);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitHpGage(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < HPGAGE_TEX_MAX; nCntTex++)
	{
		if (g_pTextureHpGage[nCntTex] != NULL)
		{
			g_pTextureHpGage[nCntTex]->Release();
			g_pTextureHpGage[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffHpGage != NULL)
	{
		g_pVtxBuffHpGage->Release();
		g_pVtxBuffHpGage = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateHpGage()
{
	// 赤ライフのカウンター増加
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // プレイヤー人数分回す
		g_aRedLifeGageCounter[nCntPlayer]--;
	}
	


	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)
		{
			// 赤ゲージ処理
			if (g_aRedLifeGageCounter[PLAYER_CONTROL_1P] == 0 && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED)
			{ // 1P用のカウンターが0になり赤ゲージの場合
			  // 目的の値を設定
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[PLAYER_CONTROL_1P] / float(PLAYER_LIFE));

				// 目的の値までの1フレームあたりの増加量を算出
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME_RED;

				// 状態の設定
				if (g_aHpGage[nCntHpGage].fDestWidth < g_aHpGage[nCntHpGage].fWidth)
				{ // 元の幅の方が大きい場合
				  // 減少状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_DOWN;
				}
				else
				{
					// 上昇状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_UP;
				}
			}
			else if (g_aRedLifeGageCounter[PLAYER_CONTROL_2P] == 0 && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // 2P用のカウンターが0になり赤ゲージの場合
			  // 目的の値を設定
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[PLAYER_CONTROL_2P] / float(PLAYER_LIFE));

				// 目的の値までの1フレームあたりの増加量を算出
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME_RED;

				// 状態の設定
				if (g_aHpGage[nCntHpGage].fDestWidth < g_aHpGage[nCntHpGage].fWidth)
				{ // 元の幅の方が大きい場合
				  // 減少状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_DOWN;
				}
				else
				{
					// 上昇状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_UP;
				}
			}

			// 幅の増減を行う
			g_aHpGage[nCntHpGage].fWidth += g_aHpGage[nCntHpGage].fAddWidth;

			if (g_aHpGage[nCntHpGage].state == HPGAGE_STATE_DOWN)
			{ // ゲージが減少中の場合
				if (g_aHpGage[nCntHpGage].fWidth < g_aHpGage[nCntHpGage].fDestWidth)
				{ // 目的の値より小さくなった場合
					// 目的の値を代入
					g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fDestWidth;
					// 増減量をリセット
					g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
					// 状態を通常状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
				}
			}
			else if (g_aHpGage[nCntHpGage].state == HPGAGE_STATE_UP)
			{ // ゲージが上昇中の場合
				if (g_aHpGage[nCntHpGage].fWidth > g_aHpGage[nCntHpGage].fDestWidth)
				{ // 目的の値より大きくなった場合
				  // 目的の値を代入
					g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fDestWidth;
					// 増減量をリセット
					g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
					// 状態を通常状態にする
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
				}
			}


			// 頂点情報の更新(個別)
			UpdateVertexHpGage(nCntHpGage);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawHpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffHpGage, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HPゲージが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureHpGage[g_aHpGage[nCntHpGage].nTexType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpGage * 4, 2);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HPゲージの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, HPGAGE_TYPE type)
{
	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == false)
		{ // HPゲージが使用されていない場合
		  // 頂点情報の設定
			g_aHpGage[nCntHpGage].pos = pos;
			g_aHpGage[nCntHpGage].rot = rot;
			g_aHpGage[nCntHpGage].fFrameWidth = HPGAGE_FRAME_WIDTH;
			g_aHpGage[nCntHpGage].type = type;

			if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
			{ // フレームの場合
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_FRAME;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPBLACK || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPBLACK)
			{ // HP黒の場合
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HPBLACK;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // HP赤の場合
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HPRED;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP)
			{ // HPの場合
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HP;
			}


			if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPBLACK || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPBLACK)
			{ // HP黒の場合色を黒に設定する
				g_aHpGage[nCntHpGage].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // HP赤の場合色を赤に設定する
				g_aHpGage[nCntHpGage].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			// 種類別頂点位置設定
			if(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
			{ // フレームの場合フレームの幅を設定
				g_aHpGage[nCntHpGage].fWidth = HPGAGE_WIDTH;
				g_aHpGage[nCntHpGage].fHeight = HPGAGE_HEIGHT;
			}
			else
			{ // フレーム以外の場合
				g_aHpGage[nCntHpGage].fWidth = HPGAGE_WIDTH - g_aHpGage[nCntHpGage].fFrameWidth * 2.0f;
				g_aHpGage[nCntHpGage].fHeight = HPGAGE_HEIGHT - g_aHpGage[nCntHpGage].fFrameWidth * 2.0f;
			}

			// 初期幅を記録
			g_aHpGage[nCntHpGage].fInitWidth = g_aHpGage[nCntHpGage].fWidth;

			// 頂点情報の更新(個別)
			UpdateVertexHpGage(nCntHpGage);

			g_aHpGage[nCntHpGage].bUse = true;	// 使用する状態にする
			break;	// このbreakはかなり大切
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HPゲージのまとめ設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpAsset(D3DXVECTOR3 pos, PLAYER_CONTROL playerID)
{
	D3DXVECTOR3 rot;
	if (playerID == PLAYER_CONTROL_1P)
	{ // 1P用の場合
		rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_FRAME);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HPBLACK);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HPRED);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HP);
	}
	else if (playerID == PLAYER_CONTROL_2P)
	{ // 2P用の場合
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_FRAME);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HPBLACK);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HPRED);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HP);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HPゲージの値設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGageLife(int nLife, PLAYER_CONTROL playerID)
{
	// lifeを代入
	g_aLife[playerID] = nLife;

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HPゲージが使用されている
		{
			if (playerID == PLAYER_CONTROL_1P && 
				(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED))
			{ // 1P用の場合
			  // 値を設定
				g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));
			}
			else if (playerID == PLAYER_CONTROL_2P &&
				(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED))
			{ // 2P用の場合
			  // 値を設定
				g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HPゲージの目的の値設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGageDestLife(int nLife, PLAYER_CONTROL playerID)
{
	HPGAGE_STATE state;

	// 状態の設定
	if (g_aLife[playerID] > nLife)
	{ // 元のLifeの方が大きい場合
		// 減少状態にする
		state = HPGAGE_STATE_DOWN;
	}
	else
	{
		// 上昇状態にする
		state = HPGAGE_STATE_UP;
	}

	// lifeを代入
	g_aLife[playerID] = nLife;

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HPゲージが使用されている
		{
			if (playerID == PLAYER_CONTROL_1P && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP)
			{ // 1P用の場合
				// 目的の値を設定
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));

				// 目的の値までの1フレームあたりの増加量を算出
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME;

				// 状態を設定する
				g_aHpGage[nCntHpGage].state = state;
			}
			else if (playerID == PLAYER_CONTROL_2P && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP)
			{ // 2P用の場合
			  // 目的の値を設定
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));

				// 目的の値までの1フレームあたりの増加量を算出
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME;

				// 状態を設定する
				g_aHpGage[nCntHpGage].state = state;
			}
		}
	}

	// 赤HPゲージの減少開始までにかかるフレーム数を設定
	g_aRedLifeGageCounter[playerID] = HPGAGE_RED_ADD_START_FRAME;			
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の更新
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexHpGage(void)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHpGage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++, pVtx += 4)
	{
		// 種類別頂点位置設定
		if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
		{ // フレームの場合フレームの幅を設定
			// 回転情報
			float fAngleUp = atan2f((g_aHpGage[nCntHpGage].fWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			float fLength = sqrtf((g_aHpGage[nCntHpGage].fWidth) * (g_aHpGage[nCntHpGage].fWidth) + (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
			float fAngleDown = atan2f((g_aHpGage[nCntHpGage].fWidth), (g_aHpGage[nCntHpGage].fHeight / 2));

			// 頂点情報の設定
			pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), cosf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
			pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
			pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aHpGage[nCntHpGage].rot.y), cosf(0.0f + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
			pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
		}
		else
		{ // フレーム以外の場合
			// 回転情報
			// 頂点情報[0]の角度
			float fAngle0 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			// 頂点情報[2]の角度
			float fAngle2 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
			// 頂点情報[0][2]の距離
			float fLength02 = sqrtf((g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fFrameWidth)
				+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
			// 頂点情報[1]の角度
			float fAngle1 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			// 頂点情報[3]の角度
			float fAngle3 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
			// 頂点情報[1][3]の距離
			float fLength13 = sqrtf((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth)
				+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));

			// 頂点情報の設定
			pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
			pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
			pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
			pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
		}
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = g_aHpGage[nCntHpGage].col;
		pVtx[1].col = g_aHpGage[nCntHpGage].col;
		pVtx[2].col = g_aHpGage[nCntHpGage].col;
		pVtx[3].col = g_aHpGage[nCntHpGage].col;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の個別更新
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexHpGage(int nCntHpGage)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHpGage->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を進める
	pVtx += 4 * nCntHpGage;

	// 種類別頂点位置設定
	if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
	{ // フレームの場合フレームの幅を設定
		// 回転情報
		float fAngleUp = atan2f((g_aHpGage[nCntHpGage].fWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		float fLength = sqrtf((g_aHpGage[nCntHpGage].fWidth) * (g_aHpGage[nCntHpGage].fWidth) + (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
		float fAngleDown = atan2f((g_aHpGage[nCntHpGage].fWidth), (g_aHpGage[nCntHpGage].fHeight / 2));

		// 頂点情報の設定
		pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), cosf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
		pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
		pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aHpGage[nCntHpGage].rot.y), cosf(0.0f + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
		pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
	}
	else
	{ // フレーム以外の場合
		// 回転情報
		// 頂点情報[0]の角度
		float fAngle0 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		// 頂点情報[2]の角度
		float fAngle2 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
		// 頂点情報[0][2]の距離
		float fLength02 = sqrtf((g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fFrameWidth)
			+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
		// 頂点情報[1]の角度
		float fAngle1 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		// 頂点情報[3]の角度
		float fAngle3 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
		// 頂点情報[1][3]の距離
		float fLength13 = sqrtf((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth)
			+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));

		// 頂点情報の設定
		pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
		pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
		pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
		pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
	}
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_aHpGage[nCntHpGage].col;
	pVtx[1].col = g_aHpGage[nCntHpGage].col;
	pVtx[2].col = g_aHpGage[nCntHpGage].col;
	pVtx[3].col = g_aHpGage[nCntHpGage].col;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffHpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexHpGage(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPGAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHpGage,
		NULL);

	// 頂点情報の更新
	UpdateVertexHpGage();
}

