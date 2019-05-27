//=============================================================================
//
// UI [ui.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "rule.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_RULE		(RULE_MAX) // 最大数

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRule[RULE_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;	// 頂点バッファのポインタ
RULE g_aRule[MAX_RULE];
int	g_PlessEnterCount;
float fColor;
//=============================================================================
// 初期化処理
//=============================================================================
void InitRule(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++)
	{
		g_aRule[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRule[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRule[nCnt].fWidth = 0.0f;
		g_aRule[nCnt].fHeight = 0.0f;
		g_aRule[nCnt].type = RULE_FLOW;
		g_aRule[nCnt].bUse = false;
	}

	MakeVertexRule(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitRule(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < RULE_MAX; nCnt++)
	{
		if (g_pTextureRule[nCnt] != NULL)
		{
			g_pTextureRule[nCnt]->Release();
			g_pTextureRule[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateRule(void)
{
	VERTEX_2D  *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		switch (g_aRule[nCnt].type)
		{
		case RULE_PRESSBUTTON:
			//選択しているカラーの値を減らしていく
			fColor -= 0.004f;

			if (fColor < 0.5f)
			{//選択しているカラーが0.5を切ったらカラーの値が増えてく
				fColor = 1.0f;
			}
			// ポリゴンの色
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			break;
		}

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイス取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++)
	{
		if (g_aRule[nCnt].bUse == true)		//使用しているなら描画する
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRule[g_aRule[nCnt].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//=============================================================================
// UI設定
//=============================================================================
void SetRule(D3DXVECTOR3 pos, float fWidth, float fHeight, RULETYPE type)
{
	VERTEX_2D  *pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		if (g_aRule[nCnt].bUse == false)
		{
			g_aRule[nCnt].pos = pos;			// 位置
			g_aRule[nCnt].fWidth = fWidth;	// 高さ
			g_aRule[nCnt].fHeight = fHeight;	// 幅
			g_aRule[nCnt].type = type;		// 種類

			pVtx[0].pos = D3DXVECTOR3(-g_aRule[nCnt].fWidth / 2, -(g_aRule[nCnt].fHeight / 2), 0.0f) + g_aRule[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aRule[nCnt].fWidth / 2, -(g_aRule[nCnt].fHeight / 2), 0.0f) + g_aRule[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aRule[nCnt].fWidth / 2, g_aRule[nCnt].fHeight / 2, 0.0f) + g_aRule[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aRule[nCnt].fWidth / 2, g_aRule[nCnt].fHeight / 2, 0.0f) + g_aRule[nCnt].pos;
			g_aRule[nCnt].bUse = true;
			break;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();
}
//=============================================================================
// 頂点情報生成処理
//=============================================================================
void MakeVertexRule(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RULE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK/Flow.png", &g_pTextureRule[RULE_FLOW]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\OperateKeyboard.png", &g_pTextureRule[RULE_KEYBORD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\OperateController.png", &g_pTextureRule[RULE_CONTROLLER]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\CardRole.png", &g_pTextureRule[RULE_ROLE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\Chara.png", &g_pTextureRule[RULE_CHARA]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE\\PressAnyBotton.png", &g_pTextureRule[RULE_PRESSBUTTON]);


	VERTEX_2D * pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		// ポリゴンの座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// ポリゴンの色
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();
}
RULE *GetRule(void)
{
	return &g_aRule[0];
}
