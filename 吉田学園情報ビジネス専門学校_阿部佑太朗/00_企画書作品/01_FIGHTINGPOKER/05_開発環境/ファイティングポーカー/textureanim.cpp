//=============================================================================
//
// テクスチャアニメーション処理 [textureanim.cpp]
// Author :  YUTARO ABE
//
//=============================================================================
#include "textureanim.h"
#include "camera.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXANIM_TEXTURENAME_000	"data/TEXTURE/explosion008.png"						// 読み込むテクスチャの名前[	グラビティバインド	]
#define TEXANIM_TEXTURENAME_001	"data/TEXTURE/explosion003.png"						// 読み込むテクスチャの名前[	地割れ	]
#define TEXANIM_TEXTURENAME_002	"data/TEXTURE/raizin000.png"						// 読み込むテクスチャの名前[	ライジンR	]
#define TEXANIM_TEXTURENAME_003	"data/TEXTURE/raizin001.png"						// 読み込むテクスチャの名前[	ライジンL	]
#define TEXANIM_TEXTURENAME_004	"data/TEXTURE/god000.png"							// 読み込むテクスチャの名前[	神のいかずち	]
#define TEXANIM_TEXTURENAME_005	"data/TEXTURE/dark000.png"							// 読み込むテクスチャの名前[	ダークマター	]

#define TEXANIM_TEXTYPE_MAX				(TEXANIM_MAX)								//	テクスチャの種類
#define TEXANIM_MAX								(100)								//	最大数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTextureAnim(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTextureAnim[TEXANIM_TEXTYPE_MAX] = {};	// 　テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTextureAnim = NULL;						// 　頂点バッファへのポインタ
Explosion g_aTextureAnim[TEXANIM_MAX];										// 　テクスチャアニメーションの情報
float g_fmoveX = 0.0f;														//	グラビティバインドのポリゴン揺らす変数
float g_fmoveY = 0.0f;														//	グラビティバインドのポリゴン揺らす変数

//=============================================================================
// 初期化処理
//=============================================================================
void InitTextureAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_000, &g_pTextureTextureAnim[TEXANIM_GRAVITY]);	//	[グラビティバインド]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_001, &g_pTextureTextureAnim[TEXANIM_FISSURES]);	//	[地割れ]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_002, &g_pTextureTextureAnim[TEXANIM_RAIZIN_R]);	//	[ライジンR]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_003, &g_pTextureTextureAnim[TEXANIM_RAIZIN_L]);	//	[ライジンL]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_004, &g_pTextureTextureAnim[TEXANIM_GOD]);		//	[神のいかず]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_005, &g_pTextureTextureAnim[TEXANIM_DARK]);		//	[ダークマター]
	// 頂点情報の作成
	MakeVertexTextureAnim(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTextureAnim(void)
{
	// テクスチャの開放
	for(int nCntTextureAnim = 0; nCntTextureAnim <TEXANIM_TEXTYPE_MAX; nCntTextureAnim++)
	{
		if (g_pTextureTextureAnim[nCntTextureAnim] != NULL)
		{
			g_pTextureTextureAnim[nCntTextureAnim]->Release();
			g_pTextureTextureAnim[nCntTextureAnim] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTextureAnim != NULL)
	{
		g_pVtxBuffTextureAnim->Release();
		g_pVtxBuffTextureAnim = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTextureAnim(void)
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == true)
		{// テクスチャが使用されている場合
			g_aTextureAnim[nCntTextureAnim].nCounterAnim++;	// カウンター加算
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GRAVITY)
			{//	[	グラビティバインド	]
				g_aTextureAnim[nCntTextureAnim].nLife--;
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GRAVITY_CNT_FPS) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % GRAVITY_MAX_PATTERN; // パターンNO.更新

					// テクスチャ座標の更新w
					pVtx[0].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);

					if (g_aTextureAnim[nCntTextureAnim].nLife <= g_aTextureAnim[nCntTextureAnim].nPatternAnim)
					{//	ポリゴンを設定した時間に消す
						g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
					g_fmoveY += GRAVITY_MOVE_X;
				}
				else if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GRAVITY_CNT_FPS) == GRAVITY_MAX_PATTERN)
				{
					g_fmoveY -= GRAVITY_MOVE_Y;
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_FISSURES)
			{//	[	地割れ	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % FISSURES_CNT_FPS) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % FISSURES_MAX_PATTERN; // パターンNO.更新

					 // テクスチャ座標の更新w
					pVtx[0].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// パターンが最初に戻った場合
					 g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_R)
			{//	[	ライジンR	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % RAIZIN_CNT_FPS_R) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % RAIZIN_MAX_PATTERN_R; // パターンNO.更新
					 // テクスチャ座標の更新
					pVtx[0].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// パターンが最初に戻った場合
						g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_L)
			{//	[	ライジンL	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % RAIZIN_CNT_FPS_L) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % RAIZIN_MAX_PATTERN_L; // パターンNO.更新
																																			  // テクスチャ座標の更新
					pVtx[0].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// パターンが最初に戻った場合
						g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GOD	)
			{//	[	神のいかずち	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GOD_CNT_FPS) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % GOD_MAX_PATTERN; // パターンNO.更新
																																			 // テクスチャ座標の更新
					pVtx[0].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// パターンが最初に戻った場合
						g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_DARK)
			{//	[	神のいかずち	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % DARK_CNT_FPS) == 0)
				{// 一定時間経過した場合
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % DARK_MAX_PATTERN; // パターンNO.更新
																																		 // テクスチャ座標の更新
					pVtx[0].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// パターンが最初に戻った場合
						g_aTextureAnim[nCntTextureAnim].bUse = false; // 使用されていない状態にする
					}
				}
			}

				// 頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, -g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, -g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);

		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTextureAnim->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTextureAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		// 計算用マトリックス

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ライティングの無効化
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);	// Zテストの無効化

	// αテストによる透明領域の切り抜き
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// アルファ基準値
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		// 比較方法

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == true)
		{// 爆発が使用されている場合
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aTextureAnim[nCntTextureAnim].mtxWorld);

			// ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// 逆行列を設定
			g_aTextureAnim[nCntTextureAnim].mtxWorld._11 = mtxView._11;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._12 = mtxView._21;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._13 = mtxView._31;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._21 = mtxView._12;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._22 = mtxView._22;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._23 = mtxView._32;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._31 = mtxView._13;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._32 = mtxView._23;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aTextureAnim[nCntTextureAnim].pos.x, g_aTextureAnim[nCntTextureAnim].pos.y, g_aTextureAnim[nCntTextureAnim].pos.z);
			D3DXMatrixMultiply(&g_aTextureAnim[nCntTextureAnim].mtxWorld, &g_aTextureAnim[nCntTextureAnim].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aTextureAnim[nCntTextureAnim].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffTextureAnim, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTextureAnim[g_aTextureAnim[nCntTextureAnim].type]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTextureAnim, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Zテストの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライティングの有効化
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTextureAnim(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * TEXANIM_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTextureAnim
		, NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTextureAnim->Unlock();
	// 情報の初期化
	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++)
	{
		g_aTextureAnim[nCntTextureAnim].type = TEXANIM_NONE;
		g_aTextureAnim[nCntTextureAnim].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTextureAnim[nCntTextureAnim].fRadius_X = 0.0f;
		g_aTextureAnim[nCntTextureAnim].fRadius_Y = 0.0f;
		g_aTextureAnim[nCntTextureAnim].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTextureAnim[nCntTextureAnim].nCounterAnim = 0;
		g_aTextureAnim[nCntTextureAnim].nPatternAnim = 0;
		g_aTextureAnim[nCntTextureAnim].bUse = false;
		g_aTextureAnim[nCntTextureAnim].nLife = 0;
		 g_fmoveX = 0.0f;
		 g_fmoveY = 0.0f;
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetTextureAnim(D3DXVECTOR3 pos, TEXANIMTYPA type)
{
	int nCount =0;
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == false)
		{// 爆発が使用されていない場合
			g_aTextureAnim[nCntTextureAnim].pos = pos;									//	位置
			g_aTextureAnim[nCntTextureAnim].type = type;								//	種類
			g_aTextureAnim[nCntTextureAnim].fRadius_X = 0;								//	半径X軸
			g_aTextureAnim[nCntTextureAnim].fRadius_Y = 0;								//	半径Y軸
			g_aTextureAnim[nCntTextureAnim].nLife = 0;									//	寿命
			g_aTextureAnim[nCntTextureAnim].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	色
			g_aTextureAnim[nCntTextureAnim].nCounterAnim = 0;							//	アニメーションカウンター
			g_aTextureAnim[nCntTextureAnim].nPatternAnim = 0;							//	パターンアニメーション

			// 頂点カラーの設定
			pVtx[0].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[1].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[2].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[3].col = g_aTextureAnim[nCntTextureAnim].col;

			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GRAVITY)
			{//	グラビティバインドの設定
				PlaySound(SOUND_LABEL_SKILL_OU_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = GRAVITY_RADIUS_X;	//	半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = GRAVITY_RADIUS_Y;	//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].nLife = GRAVITY_LIFE;			//	寿命
				g_aTextureAnim[nCntTextureAnim].col = GRAVITY_COLOR;			//	色
				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_FISSURES)
			{//	地割れの設定
				PlaySound(SOUND_LABEL_SKILL_HEIMIN_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = FISSURES_RADIUS_X;	//　半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = FISSURES_RADIUS_Y;	//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].col = FISSURES_COLOR;			//	色
				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_R)
			{//	ライジンRの設定
			 // 頂点座標の設定
				PlaySound(SOUND_LABEL_SKILL_YUSHA_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = RAIZIN_RADIUS_X_R;	//　半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = RAIZIN_RADIUS_Y_R;	//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].col = RAIZIN_COLOR_R;				//	色
				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_L)
			{//	ライジンLの設定
			 // 頂点座標の設定
				PlaySound(SOUND_LABEL_SKILL_YUSHA_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;							//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = RAIZIN_RADIUS_X_L;		//　半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = RAIZIN_RADIUS_Y_L;		//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].col = RAIZIN_COLOR_L;				//	色
																					// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.9f-(RAIZIN_TEX_WIDTH_L), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.9f - (RAIZIN_TEX_WIDTH_L), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GOD)
			{//	かみのいかずちの設定
			 // 頂点座標の設定
				PlaySound(SOUND_LABEL_SKILL_GOD_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = GOD_RADIUS_X;		//　半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = GOD_RADIUS_Y;		//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].col = GOD_COLOR;				//	色
																				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(GOD_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(GOD_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_DARK)
			{//だーうまたの設定
			 // 頂点座標の設定
				PlaySound(SOUND_LABEL_SKILL_MAOU_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	位置
				g_aTextureAnim[nCntTextureAnim].fRadius_X = DARK_RADIUS_X;		//　半径X軸
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = DARK_RADIUS_Y;		//	半径Y軸
				g_aTextureAnim[nCntTextureAnim].col = DARK_COLOR;				//	色
																				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(DARK_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(DARK_TEX_WIDTH, 1.0f);
			}

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X, g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X, g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X, -g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X, -g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);

			g_aTextureAnim[nCntTextureAnim].bUse = true;	// 使用されている状態にする
			break;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTextureAnim->Unlock();
}
