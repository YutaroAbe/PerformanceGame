//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "meshField.h"
#include "input.h"
#include "game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FIELD_POKER_TEX			"data/TEXTURE/field_poker.jpg"	// 読み込むテクスチャ
#define FIELD_RESULT_TEX		"data/TEXTURE/field_select.jpg"	// 読み込むテクスチャ
#define FIELD_PLAYERSHOW_TEX	"data/TEXTURE/field_playershow.jpg"	// 読み込むテクスチャ
#define FIELD_POS_X				(200.0f)						// 位置(X)
#define FIELD_POS_Y				(100.0f)						// 位置(Y)
#define FIELD_POS_Z				(200.0f)						// 位置(Z)
#define DIVISION_X				(1)								// 分割数
#define DIVISION_Z				(1)								// 分割数
#define MAX_FIELD				(FIELD_MAX)						// 最大数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureField[FIELD_MAX] = {};			// テクスチャのポインタ
FIELD g_aField[FIELD_MAX];									// フィールドの構造体
//*****************************************************************************
// フィールドの情報
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	float fWidth;			// 幅
	float fDepth;			// 奥行き
	int nDivision_X;		// Xの分割数
	int nDivision_Z;		// Zの分割数
	FIELDTYPE type;
}FieldInfo;

//*****************************************************************************
// フィールドのセット
//*****************************************************************************
FieldInfo g_FieldInfo[] =
{// 位置　→ 向き　→ 幅　→ 高さ　→ X分割　→ Z分割 → 種類
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_POKER },
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_PLAYERSHOW },
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_RESULT },
};
//=============================================================================
// 初期化処理
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, FIELD_POKER_TEX, &g_pTextureField[FIELD_POKER]);
	D3DXCreateTextureFromFile(pDevice, FIELD_PLAYERSHOW_TEX, &g_pTextureField[FIELD_PLAYERSHOW]);
	D3DXCreateTextureFromFile(pDevice, FIELD_RESULT_TEX, &g_pTextureField[FIELD_RESULT]);
	// 各種初期化
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		g_aField[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].fWidth = 0;
		g_aField[nCnt].fDepth = 0;
		g_aField[nCnt].nDivision_X = 0;
		g_aField[nCnt].nDivision_Z = 0;
		g_aField[nCnt].MaxIndex = 0;
		g_aField[nCnt].MaxVertex = 0;
		g_aField[nCnt].MaxPolygon = 0;
		g_aField[nCnt].bUse = false;
		g_aField[nCnt].type = FIELD_POKER;
	}
	for (int nCnt = 0; nCnt < sizeof g_FieldInfo / sizeof(FieldInfo); nCnt++)
	{
		g_aField[nCnt].pos = g_FieldInfo[nCnt].pos;
		g_aField[nCnt].rot = g_FieldInfo[nCnt].rot;
		g_aField[nCnt].fWidth = g_FieldInfo[nCnt].fWidth;
		g_aField[nCnt].fDepth = g_FieldInfo[nCnt].fDepth;
		g_aField[nCnt].nDivision_X = g_FieldInfo[nCnt].nDivision_X;
		g_aField[nCnt].nDivision_Z = g_FieldInfo[nCnt].nDivision_Z;
		g_aField[nCnt].MaxVertex = (g_aField[nCnt].nDivision_X + 1) * (g_aField[nCnt].nDivision_Z + 1);
		g_aField[nCnt].MaxIndex = (g_aField[nCnt].nDivision_X * g_aField[nCnt].nDivision_Z) * 2 + (g_aField[nCnt].nDivision_Z - 1) * 4 + 2;
		g_aField[nCnt].MaxPolygon = g_aField[nCnt].MaxIndex - 2;
		g_aField[nCnt].bUse = true;
		g_aField[nCnt].type = g_FieldInfo[nCnt].type;
	}
	MakeVertexField(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		if (g_pTextureField[nCnt] != NULL)
		{
			g_pTextureField[nCnt]->Release();
			g_pTextureField[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		// 頂点バッファの開放
		if (g_aField[nCnt].pVtxBuffField != NULL)
		{
			g_aField[nCnt].pVtxBuffField->Release();
			g_aField[nCnt].pVtxBuffField = NULL;
		}
		// インデックスバッファの開放
		if (g_aField[nCnt].pIdxBuffField != NULL)
		{
			g_aField[nCnt].pIdxBuffField->Release();
			g_aField[nCnt].pIdxBuffField = NULL;
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	MODE mode = GetMode();
	GAMEMODE gamemode = GetGameMode();
	if (gamemode == GAMEMODE_POKER)
	{
		g_aField[0].bUse = true;
		g_aField[1].bUse = false;
		g_aField[2].bUse = false;
	}
	if (gamemode == GAMEMODE_PLAYERSHOW)
	{
		g_aField[0].bUse = false;
		g_aField[1].bUse = true;
		g_aField[2].bUse = false;
	}
	if (gamemode == GAMEMODE_RESULT)
	{
		g_aField[0].bUse = false;
		g_aField[1].bUse = false;
		g_aField[2].bUse = true;
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aField[nCntField].mtxWorldField);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aField[nCntField].rot.y,						//Y,X,Zの順番
			g_aField[nCntField].rot.x,
			g_aField[nCntField].rot.z);

		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorldField,
			&g_aField[nCntField].mtxWorldField,
			&mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			g_aField[nCntField].pos.x,
			g_aField[nCntField].pos.y,
			g_aField[nCntField].pos.z);

		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorldField,
			&g_aField[nCntField].mtxWorldField,
			&mtxTrans);


		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCntField].mtxWorldField);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_aField[nCntField].pVtxBuffField, 0, sizeof(VERTEX_3D));

		// インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_aField[nCntField].pIdxBuffField);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aField[nCntField].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureField[g_aField[nCntField].type]);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aField[nCntField].MaxIndex, 0, g_aField[nCntField].MaxPolygon);
		}
	}
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// 頂点情報の作成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FIELD * g_aField[nCntField].MaxVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aField[nCntField].pVtxBuffField,
			NULL);

		// インデックス情報の作成
		pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_FIELD * g_aField[nCntField].MaxIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aField[nCntField].pIdxBuffField,
			NULL);

		// 頂点情報へのポインタ取得
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし頂点データへのポインタを取得
		g_aField[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// ポリゴンの座標設定
		for (int nCntDepth = 0; nCntDepth < g_aField[nCntField].nDivision_Z + 1 ; nCntDepth++)
		{
			for (int nCntWidth = 0; nCntWidth < g_aField[nCntField].nDivision_X + 1 ; nCntWidth++)
			{
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].pos = D3DXVECTOR3(-g_aField[nCntField].fWidth + (g_aField[nCntField].fWidth * nCntWidth),
					0.0f,
					g_aField[nCntField].fDepth - (g_aField[nCntField].fDepth * nCntDepth));
				// テクスチャの座標設定
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].tex = D3DXVECTOR2(1.0f * nCntWidth, 1.0f * nCntDepth);

				// 法線ベクトルの設定
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// ポリゴンの色
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		// 頂点バッファをアンロックする
		g_aField[nCntField].pVtxBuffField->Unlock();

		// インデックスへのポインタ取得
		WORD *pIdx;

		// インデックスバッファをロックし頂点データへのポインタを取得
		g_aField[nCntField].pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntZ = 0, nCntIdx = 0; nCntZ < g_aField[nCntField].nDivision_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= g_aField[nCntField].nDivision_X; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aField[nCntField].nDivision_X + 1) + nCntIdx;
				pIdx[1] = nCntIdx;

				pIdx += 2;
				if (nCntZ < g_aField[nCntField].nDivision_Z - 1 && nCntX == g_aField[nCntField].nDivision_X)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aField[nCntField].nDivision_X + 1) + nCntIdx + 1;

					pIdx += 2;
				}
			}
		}
		// インデックスバッファをアンロックする
		g_aField[nCntField].pIdxBuffField->Unlock();
	}
}