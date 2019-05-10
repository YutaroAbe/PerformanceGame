//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// 影処理 [shadow.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "shadow.h"
#include "meshBattleField.h"
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_SHADOW		(128)

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	SHADOW_TEX_000 = 0,	// 影テクスチャ000
	SHADOW_TEX_MAX,		// 総数
}ShadowTexName;

typedef struct
{
	char *pFilename;	// ファイル名
} ShadowTexInfo;
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffShadow = NULL;			// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9	g_apTextureShadow[SHADOW_TEX_MAX] = {};	// テクスチャへのポインタ
Shadow	g_aShadow[MAX_SHADOW];								// 影の情報

// 読み込むテクスチャ名の設定
ShadowTexInfo g_apTextureShadowInfo[SHADOW_TEX_MAX] =
{
	{ "data//TEXTURE//shadow000.jpg" },		// テクスチャ0
};
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	// テクスチャの読み込み
	for (int nCntShadowTex = 0; nCntShadowTex < SHADOW_TEX_MAX; nCntShadowTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureShadowInfo[nCntShadowTex].pFilename,
			&g_apTextureShadow[nCntShadowTex]);
	}

	// 頂点情報の作成
	MakeVertexShadow(pDevice);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitShadow(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < SHADOW_TEX_MAX; nCntTex++)
	{
		if (g_apTextureShadow[nCntTex] != NULL)
		{
			g_apTextureShadow[nCntTex]->Release();
			g_apTextureShadow[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateShadow(void)
{

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot,mtxTrans;					// 計算用マトリックス距離

	// アルファテストの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// アルファテストを開始する
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);					// 基準値(REF)を決める
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 処理(FUNC)を決める,D3DCMP_GREATER,比較(CMP),GREATER(〇〇より大きい)

	// αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// 回転を反映	Y,X,Zの順番が大切
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureShadow[0]);

			// 影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// アルファテストを終了する
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;		// 頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		// 頂点情報の設定	座標の直接指定はここでは基本的にはしない
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 法線の設定　法線は「1」にしなくてはならない？「1.0」以下にしなければならない？
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 影の設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fDepth)
{
	VERTEX_3D *pVtx;		// 頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{ // 影が使用されていない場合
			// 位置の設定
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].pos.y = 2.0f;
			// 向きの設定
			g_aShadow[nCntShadow].rot = rot;

			// 大きさの設定
			g_aShadow[nCntShadow].fWidth = fWidth;
			g_aShadow[nCntShadow].fDepth = fDepth;

			g_aShadow[nCntShadow].bUse = true; // 使用している状態にする

			pVtx[0].pos = D3DXVECTOR3(- g_aShadow[nCntShadow].fWidth / 2, 0.0f, g_aShadow[nCntShadow].fDepth / 2);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2, 0.0f, g_aShadow[nCntShadow].fDepth / 2);
			pVtx[2].pos = D3DXVECTOR3( -g_aShadow[nCntShadow].fWidth / 2, 0.0f, - g_aShadow[nCntShadow].fDepth / 2);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWidth / 2, 0.0f, - g_aShadow[nCntShadow].fDepth / 2);

			break;	// このbreakはかなり大切
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 影の設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPositionShadow(int nIdyShadow, D3DXVECTOR3 pos)
{
	if (g_aShadow[nIdyShadow].bUse == true)
	{
		g_aShadow[nIdyShadow].pos = pos;
		g_aShadow[nIdyShadow].pos.y = -1000000.0f;

		MeshBattleField *pMeshBattleField = GetMeshBattleField();
		for (int nCntField = 0; nCntField < MAX_MESHBATTLEFIELD; nCntField++)
		{

			if (pos.y >= pMeshBattleField[nCntField].pos.y && g_aShadow[nIdyShadow].pos.y < pMeshBattleField[nCntField].pos.y
				&& pos.x > pMeshBattleField[nCntField].pos.x - (pMeshBattleField[nCntField].fWidth * pMeshBattleField[nCntField].nXBlock)/2.0f && pos.x < pMeshBattleField[nCntField].pos.x + (pMeshBattleField[nCntField].fWidth * pMeshBattleField[nCntField].nXBlock) / 2.0f
				&& pos.z > pMeshBattleField[nCntField].pos.z - (pMeshBattleField[nCntField].fDepth * pMeshBattleField[nCntField].nZBlock) / 2.0f && pos.z < pMeshBattleField[nCntField].pos.z + (pMeshBattleField[nCntField].fDepth * pMeshBattleField[nCntField].nZBlock) / 2.0f)
			{ // 影の持ち主より低い位置にあり、他の比較したものより高い位置にある場合
				g_aShadow[nIdyShadow].pos.y = pMeshBattleField[nCntField].pos.y;
			}

		}

		g_aShadow[nIdyShadow].pos.y += 1.0f;

		VERTEX_3D *pVtx;		// 頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nIdyShadow;

		// 影の高さ上限25.0f
		float fRadius = 0.0f;

		fRadius += (pos.y - g_aShadow[nIdyShadow].pos.y) / 100.0f;

		if (fRadius >= 1.0f)
		{
			fRadius = 0.0f;
		}

		if (pos.y - g_aShadow[nIdyShadow].pos.y > 100.0f)
		{
			fRadius = 0.0f;
		}
		float fAlpha = 1.0f;

		fAlpha -= (pos.y - g_aShadow[nIdyShadow].pos.y) / 100.0f;

		if (fAlpha <= 0)
		{
			fAlpha = 0.0f;
		}

		pVtx[0].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f,(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, (g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-(g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, -(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aShadow[nIdyShadow].fWidth + (g_aShadow[nIdyShadow].fWidth* fRadius)) / 2.0f, 0.0f, -(g_aShadow[nIdyShadow].fDepth + (g_aShadow[nIdyShadow].fDepth* fRadius)) / 2.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		// 頂点バッファをアンロックする
		g_pVtxBuffShadow->Unlock();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 影の取得
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
Shadow *GetShadow(void)
{
	return &g_aShadow[0];
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 影の消去
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DeletShadow(int nIdyShadow)
{
	g_aShadow[nIdyShadow].bUse = false;
}