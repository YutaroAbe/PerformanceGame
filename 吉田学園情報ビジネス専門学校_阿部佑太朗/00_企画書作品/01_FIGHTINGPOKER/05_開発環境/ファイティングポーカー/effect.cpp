//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author :  YUTARO ABE
//
//=============================================================================
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	EFFECT_TEX_NAME1	"data/TEXTURE/EFFECT/effect000.jpg"			// 読み込むテクスチャ ガード
#define	EFFECT_TEX_NAME2	"data/TEXTURE/EFFECT/effect001.jpg"			// 読み込むテクスチャ ヒット弱
#define	EFFECT_TEX_NAME3	"data/TEXTURE/EFFECT/effect001.jpg"			// 読み込むテクスチャ ヒット強
#define	EFFECT_TEX_NAME4	"data/TEXTURE/EFFECT/smoke001.jpg"			// 読み込むテクスチャ 煙[ジャンプ時]
#define	EFFECT_TEX_NAME5	"data/TEXTURE/EFFECT/smoke002.jpg"			// 読み込むテクスチャ 煙[着地時]
#define	MAX_EFFECT			(4096)										// エフェクトの最大数
#define EFFECT_TRANS		(0.3f)										// エフェクトの変化率
//	ガード
#define GUARD_MOVE			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[　ガード　]動き
#define GUARD_COL			(D3DXCOLOR(0.2f, 0.7f, 0.7f, 1.0f))			//	[　ガード　]色
#define GUARD_RADIUS_X		(40)										//	[　ガード　]半径X軸
#define GUARD_RADIUS_Y		(60)										//	[　ガード　]半径Y軸
#define GUARD_CLEAR			(1.0f / 60)									//	[　ガード　]透過
#define GUARD_LIFE			(60)										//	[　ガード　]寿命
//	ヒット弱
#define HIT_000_MOVE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[　ヒット弱　]動き
#define HIT_000_COL			(D3DXCOLOR(0.7f, 0.3f, 0.0f, 1.0f))			//	[　ヒット弱　]色
#define HIT_000_RADIUS_X	(80)										//	[　ヒット弱　]半径X軸
#define HIT_000_RADIUS_Y	(80)										//	[　ヒット弱　]半径Y軸
#define HIT_000_CLEAR		( 1.0f / 60)								//	[　ヒット弱　]透過
#define HIT_000_LIFE		(60)										//	[　ヒット弱　]寿命
//	ヒット強
#define HIT_001_MOVE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[　ヒット強　]動き
#define HIT_001_COL			(D3DXCOLOR(1.0f, 0.8f, 0.2f, 1.0f))			//	[　ヒット強　]色
#define HIT_001_RADIUS_X	(100)										//	[　ヒット強　]半径X軸
#define HIT_001_RADIUS_Y	(100)										//	[　ヒット強　]半径Y軸
#define HIT_001_CLEAR		( 1.0f / 60)								//	[　ヒット強　]透過
#define HIT_001_LIFE		(60)										//	[　ヒット強　]寿命
//	スモークジャンプ時
#define SMOKE_000_MOVE		(D3DXVECTOR3(0.0f, -0.45f, 0.0f))			//	[　スモークジャンプ時 ]動き
#define SMOKE_000_COL		(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f))			//	[　スモークジャンプ時　]色
#define SMOKE_000_RADIUS_X	(60)										//	[　スモークジャンプ時　]半径X軸
#define SMOKE_000_RADIUS_Y	(60)										//	[　スモークジャンプ時　]半径Y軸
#define SMOKE_000_CLEAR		( 1.0f / 60)								//	[　スモークジャンプ時　]透過
#define SMOKE_000_LIFE		(60)										//	[　スモークジャンプ時 ]寿命
//	スモーク着地時
#define SMOKE_001_MOVE		(D3DXVECTOR3(0.0f, -0.45f, 0.0f))			//	[　スモーク着地時　]動き
#define SMOKE_001_COL		(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f))			//	[　スモーク着地時　]色
#define SMOKE_001_RADIUS_X	(60)										//	[　スモーク着地時　]半径X軸
#define SMOKE_001_RADIUS_Y	(60)										//	[　スモーク着地時　]半径Y軸
#define SMOKE_001_CLEAR		( 1.0f / 60)								//	[　スモーク着地時　]透過
#define SMOKE_001_LIFE		(60)										//	[　スモーク着地時　]寿命



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEffect[EFFECTTYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;				// 頂点バッファへのポインタ
EFFECT					g_aEffect[MAX_EFFECT];					// エフェクトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME1, &g_apTextureEffect[EFFECTTYPE_GUARD]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME2, &g_apTextureEffect[EFFECTTYPE_HIT_000]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME3, &g_apTextureEffect[EFFECTTYPE_HIT_001]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME4, &g_apTextureEffect[EFFECTTYPE_SMOKE_001]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME5, &g_apTextureEffect[EFFECTTYPE_SMOKE_002]);

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < EFFECTTYPE_MAX; nCntTex++)
	{
		if (g_apTextureEffect[nCntTex] != NULL)
		{
			g_apTextureEffect[nCntTex]->Release();
			g_apTextureEffect[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用されている場合
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			switch (g_aEffect[nCntEffect].size)
			{
			case EFFECTSIZE_NONE:
				break;
			case EFFECTSIZE_UP:
				g_aEffect[nCntEffect].fRadius_X += EFFECT_TRANS;	//	半径の拡大X軸
				g_aEffect[nCntEffect].fRadius_Y += EFFECT_TRANS;	//	半径の拡大Y軸
				break;
			case EFFECTSIZE_DOWN:
				g_aEffect[nCntEffect].fRadius_X -= EFFECT_TRANS;	//	半径の縮小X軸
				g_aEffect[nCntEffect].fRadius_Y -= EFFECT_TRANS;	//	半径の縮小Y軸
				break;
			}

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);

			g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fClear;
			// 頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0)
			{// 寿命が0になった場合
				g_aEffect[nCntEffect].bUse = false;
			}
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			// 計算用マトリックス

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ライティングの無効化
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);	// Zテストの無効化

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用されている場合
		 // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			// ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// 逆行列を設定
			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCntEffect].type]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);
		}
	}
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Zテストの有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライティングの有効化
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffEffect
		, NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
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
	g_pVtxBuffEffect->Unlock();

	// 情報の初期化
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius_X = 0.0f;
		g_aEffect[nCntEffect].fRadius_Y = 0.0f;
		g_aEffect[nCntEffect].fClear = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
}


//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, EFFECTTYPE type)
{//位置・動き・カラー・半径(大きさ)・寿命・拡大/縮小・種類
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{// エフェクトが使用されていない場合
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].type = type;
			if (type == EFFECTTYPE_GUARD)
			{//		ガード [0]
				PlaySound(SOUND_LABEL_GUARD_000);
				g_aEffect[nCntEffect].move = GUARD_MOVE;
				g_aEffect[nCntEffect].col = GUARD_COL;
				g_aEffect[nCntEffect].fRadius_X = GUARD_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = GUARD_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = GUARD_CLEAR;
				g_aEffect[nCntEffect].nLife = GUARD_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_HIT_000)
			{//		ヒット	[弱]
				PlaySound(SOUND_LABEL_HIT_000);
				g_aEffect[nCntEffect].move = HIT_000_MOVE;
				g_aEffect[nCntEffect].col = HIT_000_COL;
				g_aEffect[nCntEffect].fRadius_X = HIT_000_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = HIT_000_RADIUS_X;
				g_aEffect[nCntEffect].fClear = HIT_000_CLEAR;
				g_aEffect[nCntEffect].nLife = HIT_000_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_HIT_001)
			{//		 ヒット	[強]
				PlaySound(SOUND_LABEL_HIT_001);
				g_aEffect[nCntEffect].move = HIT_001_MOVE;
				g_aEffect[nCntEffect].col = HIT_001_COL;
				g_aEffect[nCntEffect].fRadius_X = HIT_001_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = HIT_001_RADIUS_X;
				g_aEffect[nCntEffect].fClear = HIT_001_CLEAR;
				g_aEffect[nCntEffect].nLife = HIT_001_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_SMOKE_001)
			{//		煙	[ジャンプ]
				g_aEffect[nCntEffect].move = SMOKE_000_MOVE;
				g_aEffect[nCntEffect].col = SMOKE_000_COL;
				g_aEffect[nCntEffect].fRadius_X = SMOKE_000_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = SMOKE_000_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = SMOKE_000_CLEAR;
				g_aEffect[nCntEffect].nLife = SMOKE_000_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;

			}
			else	if (type == EFFECTTYPE_SMOKE_002)
			{//		 煙 [着地]
				g_aEffect[nCntEffect].move = SMOKE_001_MOVE;
				g_aEffect[nCntEffect].col = SMOKE_001_COL;
				g_aEffect[nCntEffect].fRadius_X = SMOKE_001_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = SMOKE_001_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = SMOKE_001_CLEAR;
				g_aEffect[nCntEffect].nLife = SMOKE_001_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;

			}
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].bUse = true;	// 使用されている状態にする
			break;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}