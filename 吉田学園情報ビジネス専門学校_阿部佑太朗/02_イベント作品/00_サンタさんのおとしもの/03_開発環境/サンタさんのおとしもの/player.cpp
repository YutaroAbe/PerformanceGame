//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURENAME	"data\\TEXTURE\\player000.png"		// テクスチャ名
#define POLYGON_X			(600)								// ポリゴンのX座標
#define POLYGON_Y			(200)								// ポリゴンのY座標
#define PLAYER_WIDTH		(40)								// プレイヤーの幅
#define PLAYER_HEIGHT		(40)								// プレイヤーの高さ
#define DAMAGE_TIME			(5)									// ダメージ状態の時間
#define PLAYER_LIFE			(5)									// プレイヤーのライフ
#define MAX_PARTTERN		(3)									// パターンの最大
#define POLYGON_COUNT		(8)									// アニメーションに使う数値
#define PLAYER_INERTIA		(1.0f)								// アニメーションに使う数値
#define UPDATE_ANIM_X		(((1.0f / 3.0f) * g_player.nPatternAnim))	// 読み込むテクスチャのパターン
#define UPDATE_ANIM_Y		((0.5f * g_player.nDirection))		// 読み込むテクスチャのパターン
#define PLAYER_MOVE			(1.0f)								// プレイヤーの速度


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファへのポインタ
int g_nCounterAnim;									// アニメーションカウンター
int g_nPartternAnim;								// アニメーションパターンNo.
Player g_player;
ITEMKIND g_bulletkind;

//=============================================================================
// プレイヤー初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// プレイヤーの情報の初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fPlayerHeight = 0.0f;
	g_player.fPlayerWidth = 0.0f;
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.nDirection = 1;
	g_player.nItem = NULL;
	g_player.kind = ITEMKIND_NONE;
	g_player.bDis = true;
	g_player.nCounterItem = 0;

	// ポリゴン座標の設定
	g_player.pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);

	g_nCounterAnim = 0;		// カウンターを初期化する
	g_nPartternAnim = 0;	// パターンNo.を初期化する

	// プレイヤーの高さと幅を設定
	g_player.fPlayerHeight = PLAYER_HEIGHT;	// 高さ
	g_player.fPlayerWidth = PLAYER_WIDTH;		// 幅

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &g_pTexturePlayer);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			// 頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(POLYGON_X - g_player.fPlayerWidth, POLYGON_Y - g_player.fPlayerHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_X + g_player.fPlayerWidth, POLYGON_Y - g_player.fPlayerHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_X - g_player.fPlayerWidth, POLYGON_Y + g_player.fPlayerHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_X + g_player.fPlayerWidth, POLYGON_Y + g_player.fPlayerHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 3.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 3.0f, 0.5f);

	// 頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// プレイヤー終了処理
//=============================================================================
void UninitPlayer(void)
{
	// テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// プレイヤー更新処理
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	g_nCounterAnim++;	// カウンター加算
	D3DXVECTOR3 SetPos(0.0f, 0.0f, 0.0f);

	// 移動
	float fPlayerMove = PLAYER_MOVE;

	g_player.posOld = g_player.pos;

	// ブロックの取得
	Item *pItem;
	pItem = GetItem();
	
	if (g_player.bDis == true)
	{
		// 頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_A) == true)
		{// 左方向に移動
			g_player.move.x -= fPlayerMove;

			if (g_player.nDirection != 0)
			{
				g_player.nDirection = 0;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}

			SetEffect(D3DXVECTOR3(g_player.pos.x + 40.0f, g_player.pos.y + 20.0f, g_player.pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 10);
		}

		if (GetKeyboardPress(DIK_D) == true)
		{// 右方向に移動
			g_player.move.x += fPlayerMove;

			if (g_player.nDirection != 1)
			{
				g_player.nDirection = 1;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
			SetEffect(D3DXVECTOR3(g_player.pos.x - 40.0f, g_player.pos.y + 20.0f, g_player.pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 10);
		}

		if (g_player.move.x >= 0.25f || g_player.move.x <= -0.25f)
		{
			if ((g_player.nCounterAnim % POLYGON_COUNT) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % MAX_PARTTERN;	// パターンNo.を更新

																					// テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + UPDATE_ANIM_X, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f) + UPDATE_ANIM_X, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[2].tex = D3DXVECTOR2(0.0f + UPDATE_ANIM_X, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f) + UPDATE_ANIM_X, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
			}
			g_player.nCounterAnim++;	// カウンター加算
		}
		else if (g_player.move.x < 0.25f && g_player.move.x > -0.25)
		{
			if ((g_player.nCounterAnim % POLYGON_COUNT) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % MAX_PARTTERN;	// パターンNo.を更新

				// テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f), 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f), 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
			}
			g_player.nCounterAnim++;	// カウンター加算
		}
		
		if (g_player.pos.x > SCREEN_WIDTH + g_player.fPlayerWidth)
		{// 機体が画面外に出たら逆に
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x < -g_player.fPlayerWidth)
		{// 機体が画面外に出たら逆に
			g_player.pos.x = SCREEN_WIDTH;
		}
		

		// 位置更新（移動）
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		g_player.move.x += (0.0f - g_player.move.x) * 0.15f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

		// 頂点座標を更新
		pVtx[0].pos.x = g_player.pos.x - g_player.fPlayerWidth;	// 左上のX座標を設定
		pVtx[0].pos.y = g_player.pos.y - g_player.fPlayerHeight;	// 左上のY座標を設定
		pVtx[1].pos.x = g_player.pos.x + g_player.fPlayerWidth;	// 右上のX座標を設定
		pVtx[1].pos.y = g_player.pos.y - g_player.fPlayerHeight;	// 右上のY座標を設定
		pVtx[2].pos.x = g_player.pos.x - g_player.fPlayerWidth;	// 左下のX座標を設定
		pVtx[2].pos.y = g_player.pos.y + g_player.fPlayerHeight;	// 左下のY座標を設定
		pVtx[3].pos.x = g_player.pos.x + g_player.fPlayerWidth;	// 右下のX座標を設定
		pVtx[3].pos.y = g_player.pos.y + g_player.fPlayerHeight;	// 右下のY座標を設定

		// 頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();
	}

	// アイテムの当たり判定
	if (g_player.nCounterItem == 0)
	{
		if (CollisionItem(&g_player.pos, g_player.fPlayerHeight, g_player.fPlayerWidth, &g_player.nItem) == true)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				if (g_player.nItem != NULL)
				{// アイテムの種類のアドレスが空ではない
					pItem += *g_player.nItem;  // アイテムの種類の分ポインタを進める
				}
				SetExplosion(pItem->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
				pItem->bUse = false;      // 見えない状態にする
				g_player.nCounterItem++;
				PlaySound(SOUND_LABEL_SE_GET);
			}
		}
	}

	if (g_player.nCounterItem > 0)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, 7.0f, 0.0f), g_player.nItem);
			PlaySound(SOUND_LABEL_SE_FALL);
			g_player.nCounterItem = 0;
		}
	}
}

//=============================================================================
// プレイヤー描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// デバイスへのポインタ
	pDevice = GetDevice();			// デバイスを取得する

	if (g_player.bDis == true)
	{
		// 頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
ITEMKIND *GetItemKind(void)
{
	return &g_player.kind;
}