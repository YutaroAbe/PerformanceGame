//=============================================================================
//
// 下にいる人の処理 [human.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "human.h"
#include "demandpresent.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "explosion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define HUMAN_TEXTURE_NAME0 "data/TEXTURE/boy.png"                    // テクスチャのファイル名
#define HUMAN_TEXTURE_NAME1 "data/TEXTURE/girl.png"                   // テクスチャのファイル名
#define ANIMATION_PATTERNX    ((1.0f / 5.0f) * (g_aHuman[nCntHuman].nPatternAnim % 4))// テクスチャ座標(U)を切り替える計算式
#define HUMAN_TEXTURE_PATTERN (4)                                           // テクスチャのパターン数

//=============================================================================
// 構造体定義
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureHuman[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHuman = NULL;	// 頂点バッファへのポインタ
Human                   g_aHuman[MAX_HUMAN];    // 下にいる人の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitHuman(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// 人間の数だけ繰り返し
		g_aHuman[nCntHuman].pos = D3DXVECTOR3(1400.0f, 400.0f, 0.0f);    // 現在の位置を初期化
		g_aHuman[nCntHuman].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // 前回の位置を初期化
		g_aHuman[nCntHuman].move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);      // 移動量を初期化
		g_aHuman[nCntHuman].state = HUMANSTATE_NORMAL;                   // 状態は通常の状態に
		g_aHuman[nCntHuman].fWidth = 20;                                 // 幅を初期化
		g_aHuman[nCntHuman].fHeight = 60;                                // 高さを初期化
		g_aHuman[nCntHuman].nPresentCounter = 0;                          // Presentカウンターを初期化
		g_aHuman[nCntHuman].bUse = false;                                // 使用していない状態にする
		g_aHuman[nCntHuman].nNumtex = 0;                                 // テクスチャの番号を初期化
	}

	// 頂点バッファの作成
	MakeVertexHuman(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitHuman(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureHuman[nCntTex] != NULL)
		{
			g_pTextureHuman[nCntTex]->Release();
			g_pTextureHuman[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffHuman != NULL)
	{
		g_pVtxBuffHuman->Release();
		g_pVtxBuffHuman = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateHuman(void)
{
	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// 人間の数だけ繰り返し
		if (g_aHuman[nCntHuman].bUse == true)
		{// 使用されている
			g_aHuman[nCntHuman].posold = g_aHuman[nCntHuman].pos;  		// 前回の位置更新

			if (g_aHuman[nCntHuman].state != HUMANSTATE_STOP)
			{// 止まっている状態でない
			    // 移動量更新
				g_aHuman[nCntHuman].pos += g_aHuman[nCntHuman].move;

				if (g_aHuman[nCntHuman].nCounterAnim % 7 == 0)
				{// カウンターがある程度進んだ
					g_aHuman[nCntHuman].nPatternAnim = (g_aHuman[nCntHuman].nPatternAnim + 1) % HUMAN_TEXTURE_PATTERN;   // パターンNo. 更新

					// テクスチャ座標の更新
					pVtx[0].tex.x = 0.0f + ANIMATION_PATTERNX;           
					pVtx[1].tex.x = (1.0f / 5.0f) + ANIMATION_PATTERNX;
					pVtx[2].tex.x = 0.0f + ANIMATION_PATTERNX;;
					pVtx[3].tex.x = (1.0f / 5.0f) + ANIMATION_PATTERNX;
				}
				g_aHuman[nCntHuman].nCounterAnim++;  // カウンターを進める

				g_aHuman[nCntHuman].move.y += 1.0f;

				if (g_aHuman[nCntHuman].pos.y > SCREEN_HEIGHT)
				{
					g_aHuman[nCntHuman].pos.y = SCREEN_HEIGHT;
					g_aHuman[nCntHuman].move.y = 0.0f;
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_NORMAL)
			{// 通常の状態だったら
				g_aHuman[nCntHuman].nPresentCounter--;
				if (g_aHuman[nCntHuman].nPresentCounter <= 0)
				{// プレゼントカウンターが0になった
					g_aHuman[nCntHuman].nStopConter = 60;        // ストップカウンターを設定
					g_aHuman[nCntHuman].state = HUMANSTATE_STOP; // 止まっている状態に設定
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_STOP)
			{// 止まっている状態だったら
				g_aHuman[nCntHuman].nStopConter--;   // カウンターを減らす
				if (g_aHuman[nCntHuman].nStopConter == 40)
				{// カウンターがある程度減った
					PlaySound(SOUND_LABEL_SE_WANT);
					SetDemandPresent(D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth + 10.0f, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight - 30.0f, 0.0f),nCntHuman,g_aHuman[nCntHuman].nNumtex);  // 欲しいアイテムを表示
				}
				if (g_aHuman[nCntHuman].nStopConter <= 0)
				{// プレゼントカウンターが0になった
					g_aHuman[nCntHuman].state = HUMANSTATE_GIVEME_PRESENT; // 通常の状態に設定
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_GIVEME_PRESENT)
			{// 止まっている状態だったら
				if (CollisionBullet(&g_aHuman[nCntHuman].pos, g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].fHeight, &g_aHuman[nCntHuman].itemtype) == true)
				{// プレゼントカウンターが0になった

					if (g_aHuman[nCntHuman].nNumtex == *g_aHuman[nCntHuman].itemtype)
					{
						PlaySound(SOUND_LABEL_SE_HIT);
						g_aHuman[nCntHuman].state = HUMANSTATE_HAVEPRESENT; // プレゼントをもらった状態に設定
						DeleteDemandPresent(nCntHuman);                     // 吹き出しを消す

						g_aHuman[nCntHuman].move.y -= 17.0f;

						// スコアの加算
						AddScore(5000, D3DXVECTOR3(g_aHuman[nCntHuman].pos.x, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight - 10.0f, 0.0f));
					}
				}
			}

			// 画面端に行ったら消す
			if (g_aHuman[nCntHuman].move.x > 0 && g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth > SCREEN_WIDTH)
			{// 右端に到達した
				g_aHuman[nCntHuman].bUse = false;
			}
			if (g_aHuman[nCntHuman].move.x < 0 && g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth < 0)
			{// 左端に到達した
				g_aHuman[nCntHuman].bUse = false;
			}

			//---------------------
			// 頂点バッファの更新
			//---------------------

			// 頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

			//// テクスチャ座標
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;    // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawHuman(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffHuman, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// 人間の数だけ繰り返し
		if (g_aHuman[nCntHuman].bUse == true)
		{// 使用されている
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureHuman[g_aHuman[nCntHuman].nNumtex]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHuman * 4, 2);
		}
	}
}
//=============================================================================
// 頂点バッファの作成
//=============================================================================
void MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		HUMAN_TEXTURE_NAME0,
		&g_pTextureHuman[0]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		HUMAN_TEXTURE_NAME1,
		&g_pTextureHuman[1]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HUMAN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHuman,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// 人間の数だけ繰り返し
		// 頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

		// 頂点テクスチャ
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / 5.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / 5.0f), 0.5f);

		pVtx += 4;     // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// 人間の設定
//=============================================================================
void SetHuman(void)
{
	int randPos;       // 位置を左右のどちらかにするために使用
	float texV;        // テクスチャのV座標
	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	// 値の設定
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// 人間の数だけ繰り返し
		if (g_aHuman[nCntHuman].bUse == false)
		{// 使用されていない
			randPos = rand() % 2;   // 出現位置をどちらにするか決定
			if (randPos == 0)
			{// 左側から出現するなら
				g_aHuman[nCntHuman].pos = D3DXVECTOR3(-100.0f, SCREEN_HEIGHT, 0.0f);   // 位置を設定
				g_aHuman[nCntHuman].move = D3DXVECTOR3(2.0f, 1.0f, 0.0f);              // 移動量を設定
				texV = 0.0f;
			}
			else if (randPos == 1)
			{// 右側から出現するなら
				g_aHuman[nCntHuman].pos = D3DXVECTOR3(SCREEN_WIDTH + 100, SCREEN_HEIGHT, 0.0f);   // 位置を設定
				g_aHuman[nCntHuman].move = D3DXVECTOR3(-2.0f, 1.0f, 0.0f);                        // 移動量を設定
				texV = 0.5f;
			}
			g_aHuman[nCntHuman].nPresentCounter = rand() % 50 + 80;          // プレゼントカウンターを設定
			g_aHuman[nCntHuman].nNumtex = rand() % 2;                         // テクスチャ番号を設定
			g_aHuman[nCntHuman].state = HUMANSTATE_NORMAL;                    // 通常の状態に
			g_aHuman[nCntHuman].bUse = true;                                  // 使用している状態にする

			//--------------------
			// 頂点バッファの設定
			//--------------------

			// 頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

			// テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, texV);
			pVtx[1].tex = D3DXVECTOR2((1.0f / 5.0f), texV);
			pVtx[2].tex = D3DXVECTOR2(0.0f, texV + 0.5f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / 5.0f), texV + 0.5f);

			break;
		}
		pVtx += 4;   // ポインタを進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// 人間の取得
//=============================================================================
Human *GetHuman(void)
{
	return &g_aHuman[0];
}