//=============================================================================
//
// パーティクル処理 [PARTICLE.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_PARTICLE					(10000)									// パーティクルの最大数
#define	TEXTURE_PARTICLE_NAME_000 "data/TEXTURE/PARTICL/darkmatter.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_PARTICLE_NAME_001	"data/TEXTURE/PARTICL/stone.png"			// 読み込むテクスチャファイル名
#define MAX_TEX						(PARTICLETYPE_MAX)

//	ダークマター
#define DARK_COL_000			(D3DXCOLOR(0.6f, 0.0f, 0.0f, 0.8f))				//	[　ダークマター　]色1
#define DARK_COL_001			(D3DXCOLOR(0.6f, 0.8f, 0.0f, 0.5f))				//	[　ダークマター　]色2
#define DARK_COL_002			(D3DXCOLOR(0.6f, 1.0f, 1.0f, 0.3f))				//	[　ダークマター　]色3
#define DARK_NUM_TEX			(1)												//	[　ダークマター　]テクスチャ番号
#define DARK_POLIGON_MAX		(50)											//	[　ダークマター　]ポリゴンの数
#define DARK_LIFE				(60)											//	[　ダークマター　]寿命
#define DARK_RDIUS				((rand() % 10 + 1) * 1.0f)						//	[　ダークマター　]半径
#define DARK_MOVE_X				(sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1))
#define DARK_MOVE_Y				(cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1))

//	いし　
#define STONE_NUM_TEX			(2)												//	[　いし ]テクスチャ番号
#define STONE_POLIGON_MAX		(50)											//	[　いし ]ポリゴンの数
#define STONE_LIFE				((rand() % 50) + 1)								//	[　いし ]寿命
#define STONE_RDIUS				((rand() % 6 + 1) * 1.0f)						//	[　いし ]半径
#define STONE_NUM1_MOVE_X		(sinf((rand() % 314 / 2) / 100.0f) * ((rand() % 3) + 1))
#define STONE_NUM1_MOVE_Y		(cosf((rand() % 314 / 2) / 100.0f) * ((rand() % 3) + 1))
#define STONE_NUM2_MOVE_X		(sinf((rand() % -314 / 2) / -100.0f) * ((rand() % 3) + 1))
#define STONE_NUM2_MOVE_Y		(cosf((rand() % -314 / 2) / -100.0f) * ((rand() % 3) + 1))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9				g_pTexturePARTICLE[MAX_TEX] = {};				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffPARTICLE = NULL;						// 頂点バッファへのポインタ
PARTICLE						g_aPARTICLE[MAX_PARTICLE];						// パーティクルの情報

//=============================================================================
// パーティクル初期化処理
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスを取得
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PARTICLE_NAME_000, &g_pTexturePARTICLE[PARTICLETYPE_DARKMATTER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PARTICLE_NAME_001, &g_pTexturePARTICLE[PARTICLETYPE_STONE]);
	MakeVertexParticle(pDevice);
}

//=============================================================================
// パーティクル終了処理
//=============================================================================
void UninitParticle(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTexturePARTICLE[nCnt] != NULL)
		{
			g_pTexturePARTICLE[nCnt]->Release();
			g_pTexturePARTICLE[nCnt] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffPARTICLE != NULL)
	{
		g_pVtxBuffPARTICLE->Release();
		g_pVtxBuffPARTICLE = NULL;
	}
}

//=============================================================================
// パーティクル更新処理
//=============================================================================
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	g_pVtxBuffPARTICLE->Lock(0,0,(void**)&pVtx,0);

	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{// パーティクルをカウント
		if (g_aPARTICLE[nCntPARTICLE].bUse == true)
		{// パーティクルが使用されている場合
			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
			{// ダークマターパーティクルの場合
				g_aPARTICLE[nCntPARTICLE].pos += g_aPARTICLE[nCntPARTICLE].move;	// 移動値代入
				g_aPARTICLE[nCntPARTICLE].nLife--;									// 寿命減少
				// 半径減少
				if (g_aPARTICLE[nCntPARTICLE].nLife > 0)
				{
					g_aPARTICLE[nCntPARTICLE].fRadius += 0.005f;
				}
				else
				{
					g_aPARTICLE[nCntPARTICLE].fRadius -= 0.5f;
				}

				if (g_aPARTICLE[nCntPARTICLE].fRadius <= 0)
				{// ライフが0以下の場合
					g_aPARTICLE[nCntPARTICLE].bUse = false;
				}
			}
			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_STONE)
			{// 石パーティクルの場合
				g_aPARTICLE[nCntPARTICLE].pos += g_aPARTICLE[nCntPARTICLE].move;	// 移動値代入
				g_aPARTICLE[nCntPARTICLE].nLife--;									// 寿命減少
																					// 半径減少
				if (g_aPARTICLE[nCntPARTICLE].nLife > 0)
				{
					g_aPARTICLE[nCntPARTICLE].fRadius += 0.005f;
				}
				else
				{
					g_aPARTICLE[nCntPARTICLE].fRadius -= 0.5f;
				}

				if (g_aPARTICLE[nCntPARTICLE].fRadius <= 0)
				{// ライフが0以下の場合
					g_aPARTICLE[nCntPARTICLE].bUse = false;
				}
			}
		}
		// 頂点設定
		pVtx[nCntPARTICLE * 4].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius,g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 1].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 2].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius, -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 3].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius,  -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
	}
	// 頂点バッファをアンロック
	g_pVtxBuffPARTICLE->Unlock();
}

//=============================================================================
// パーティクル描画処理
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスを取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//計算用マトリックス
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aPARTICLE[nCntPARTICLE].mtxWorld);
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aPARTICLE[nCntPARTICLE].mtxWorld._11 = mtxView._11;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._12 = mtxView._21;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._13 = mtxView._31;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._21 = mtxView._12;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._22 = mtxView._22;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._23 = mtxView._32;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._31 = mtxView._13;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._32 = mtxView._23;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._33 = mtxView._33;
		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPARTICLE[nCntPARTICLE].rot.y, g_aPARTICLE[nCntPARTICLE].rot.x, g_aPARTICLE[nCntPARTICLE].rot.z);
		D3DXMatrixMultiply(&g_aPARTICLE[nCntPARTICLE].mtxWorld, &g_aPARTICLE[nCntPARTICLE].mtxWorld, &mtxRot);
		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aPARTICLE[nCntPARTICLE].pos.x, g_aPARTICLE[nCntPARTICLE].pos.y, g_aPARTICLE[nCntPARTICLE].pos.z);
		D3DXMatrixMultiply(&g_aPARTICLE[nCntPARTICLE].mtxWorld, &g_aPARTICLE[nCntPARTICLE].mtxWorld, &mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aPARTICLE[nCntPARTICLE].mtxWorld);
		//アルファテスト
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						//基準値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//比較方法（より大きい））
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);		//比較方法（より大きい））
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPARTICLE, 0, sizeof(VERTEX_3D));
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aPARTICLE[nCntPARTICLE].bUse == true)
		{// パーティクルが使用されている場合
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePARTICLE[g_aPARTICLE[nCntPARTICLE].nTypeTx]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPARTICLE * 4, 2);
		}
		//アルファ値を戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
}

//=============================================================================
// 	パーティクルの設定
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, PARTICLETYPE Type)
{
	int nCount = 0;			// パーティクル個数カウンタ
	VERTEX_3D *pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	g_pVtxBuffPARTICLE->Lock(0,0,(void**)&pVtx,0);
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++, pVtx += 4)
	{// パーティクルをカウント
		if (g_aPARTICLE[nCntPARTICLE].bUse == false)
		{// パーティクルが使用されていない
			g_aPARTICLE[nCntPARTICLE].pos = pos;											// 位置
			g_aPARTICLE[nCntPARTICLE].Type = Type;											// 種類設定
			g_aPARTICLE[nCntPARTICLE].bUse = true;											// 使用している状態

			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
			{//	[ダークマター]
				g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);			// カラー
				g_aPARTICLE[nCntPARTICLE].nTypeTx = DARK_NUM_TEX;							// 種類設定
				g_aPARTICLE[nCntPARTICLE].nSetMax = DARK_POLIGON_MAX;						//ポリゴンの数
				g_aPARTICLE[nCntPARTICLE].nLife = DARK_LIFE;								// 寿命設定
				// 移動ランダム化
				g_aPARTICLE[nCntPARTICLE].move.x = DARK_MOVE_X;
				g_aPARTICLE[nCntPARTICLE].move.y = DARK_MOVE_Y;
				int nNumber = rand() % 3 + 1;
				if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
				{
					if (nNumber == 1) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_000; }
					if (nNumber == 2) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_001; }
					if (nNumber == 3) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_002; }
				}
				g_aPARTICLE[nCntPARTICLE].fRadius = DARK_RDIUS;								// 半径設定
			}

			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_STONE)
			{//	[石]
				g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);			// カラー
				g_aPARTICLE[nCntPARTICLE].nTypeTx = STONE_NUM_TEX;							// 種類設定
				g_aPARTICLE[nCntPARTICLE].nSetMax = STONE_POLIGON_MAX;
				g_aPARTICLE[nCntPARTICLE].nLife = (STONE_LIFE);								// 寿命設定
				int nNumber = rand() % 2 + 1;
				// 移動ランダム化
				if (nNumber == 1)
				{
					g_aPARTICLE[nCntPARTICLE].move.x = STONE_NUM1_MOVE_X;
					g_aPARTICLE[nCntPARTICLE].move.y = STONE_NUM1_MOVE_Y;
				}
				if (nNumber == 2)
				{
					g_aPARTICLE[nCntPARTICLE].move.x = STONE_NUM2_MOVE_X;
					g_aPARTICLE[nCntPARTICLE].move.y = STONE_NUM2_MOVE_Y;
				}

				g_aPARTICLE[nCntPARTICLE].fRadius = STONE_RDIUS;							// 半径設定
			}
			// 頂点設定
			pVtx[0].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius,  -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			// 頂点カラー設定
			pVtx[0].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[1].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[2].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[3].col = g_aPARTICLE[nCntPARTICLE].col;
			nCount++;		// 個数をカウント
			if ( nCount == g_aPARTICLE[nCntPARTICLE].nSetMax)
			{// 個数が最大数になった場合
				break;
			}
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffPARTICLE->Unlock();
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{// パーティクルをカウント
		g_aPARTICLE[nCntPARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// パーティクル中心値
		g_aPARTICLE[nCntPARTICLE].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// パーティクル中心値
		g_aPARTICLE[nCntPARTICLE].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// パーティクル移動値
		g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// パーティクル色
		g_aPARTICLE[nCntPARTICLE].Type = PARTICLETYPE_NONE;						// パーティクル種類設定
		g_aPARTICLE[nCntPARTICLE].nTypeTx;										// パーティクルテクスチャ種類設定
		g_aPARTICLE[nCntPARTICLE].fRadius = 0.0f;								// パーティクル半径
		g_aPARTICLE[nCntPARTICLE].nLife = 0;									// パーティクル寿命
		g_aPARTICLE[nCntPARTICLE].bUse = false;									// パーティクル使用していない状態
	}
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffPARTICLE, NULL);
	// 頂点情報の作成
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{
	 // 頂点設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// 頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPARTICLE->Unlock();
}
