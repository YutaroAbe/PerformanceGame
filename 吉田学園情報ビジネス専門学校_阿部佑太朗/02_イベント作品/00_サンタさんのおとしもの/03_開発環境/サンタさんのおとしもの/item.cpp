//=============================================================================
//
// アイテムの処理 [item.cpp]
// Author :長山拓実
//
//=============================================================================
#include "item.h"
#include "game.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM0_TEXTURE_NAME	"data\\TEXTURE\\present_boy.png"		// 読み込むテクスチャ名
#define ITEM1_TEXTURE_NAME	"data\\TEXTURE\\present_girl.png"  // 読み込むテクスチャ名
#define ITEM_SIZE_WIDTH		(35.0f)						    // 読み込むテクスチャの幅の大きさ
#define ITEM_SIZE_HEIGHT	(45.0f)							// 読み込むテクスチャの縦の大きさ
#define ITEM_HIT			(8)								// アイテムとの当たり判定
#define ITEM_HIT1			(5)								// アイテムとの当たり判定
#define MAX_TYPE_ITEM		(2)								// アイテムの種類

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// 頂点バッファへのポインタ
Item					g_aItem[MAX_ITEM];		// 使用しているかどうか
int g_nCntItemTimer;

//=============================================================================
// 初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// アイテムの初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].itemtype = ITEMTYPE_COIN;
		g_aItem[nCntItem].fItemHeight = 0.0f;
		g_aItem[nCntItem].fItemWidth = 0.0f;
		g_aItem[nCntItem].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ITEM0_TEXTURE_NAME, &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM1_TEXTURE_NAME, &g_apTextureItem[1]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,												// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// 頂点データを４つ分進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{
		if (g_apTextureItem[nCntTex] != NULL)
		{
			g_apTextureItem[nCntTex]->Release();
			g_apTextureItem[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].nCounterAnim++;
			if (g_aItem[nCntItem].bUse == true)	// アイテムが使用されている
			{
				// テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			if (g_aItem[nCntItem].bUse == false)// アイテムが使用されていない
			{
				g_nCntItemTimer++;

				if (g_nCntItemTimer >= 80)
				{
					g_aItem[nCntItem].bUse = true;
					g_nCntItemTimer = 0;
				}
			}
		pVtx += 4;	// 該当の位置まで進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)	// アイテムが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].itemtype]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntItem,
				2);
		}
	}
}

//=============================================================================
// アイテムの設定処理
//=============================================================================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE itemtype)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			VERTEX_2D *pVtx;	// 頂点情報へのポインタ

			// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntItem * 4);	// 該当の位置まで進める

			g_aItem[nCntItem].itemtype = itemtype;

			switch (itemtype)
			{
			case ITEMTYPE_COIN:
				g_aItem[nCntItem].fItemHeight = ITEM_SIZE_HEIGHT;
				g_aItem[nCntItem].fItemWidth = ITEM_SIZE_WIDTH;
				break;

			case ITEMTYPE_MIKIYA:
				g_aItem[nCntItem].fItemHeight = ITEM_SIZE_HEIGHT;
				g_aItem[nCntItem].fItemWidth = ITEM_SIZE_WIDTH;
				break;
			}

			g_aItem[nCntItem].pos = pos;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
			g_aItem[nCntItem].nPatternAnim = 0;

			// テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点バッファをアンロック
			g_pVtxBuffItem->Unlock();

			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].bUse = true;	// 使用している状態
			break;
		}
	}
}

//=============================================================================
// アイテムの取得
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// アイテムの当たり判定の処理
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **nItem)
{
	int nCntItem;

	bool bItem = false;

	// プレイヤーの取得
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPos->x + fWidth > g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth
				&& pPos->x - fWidth < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth)
			{
				bItem = true;
				*nItem = &g_aItem[nCntItem].itemtype;   // アイテムの種類のアドレスを入れる
			}
		}
	}
	return bItem;
}