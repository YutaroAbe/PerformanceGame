//=============================================================================
//
// ステータス [status.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "status.h"
#include "fade.h"
#include "PlayerShow.h"
#include "cardModel.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BLADE_TEX		"data/TEXTURE/ken.png"
#define SHIELD_TEX		"data/TEXTURE/tate.png"
#define FRAME_TEX		"data/TEXTURE/status_frame.png"
#define BRADE_SIZE		(50.0f)
#define SHIELD_SIZE		(50.0f)
#define FRAME_Y_POS		(100.0f)
#define FRAME_1P_POS	(0.0f)
#define FRAME_2P_POS	(1080.0f)
#define FRAME_WIDTH		(200.0f)
#define FRAME_HEIGHT	(300.0f)
#define FIRST_Y_POS		(210.0f)
#define BRADE_1P_POS	(25.0f)
#define BRADE_2P_POS	(1105.0f)
#define MAX_PLAYER		(2)
#define MAX_UP			(12)
#define MAX_FRAME		(2)
#define MAX_DRAW		(MAX_UP + MAX_FRAME)
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureStatus[STATUSINFO_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStatus = NULL;		// 頂点バッファのポインタ
STATUS g_aStatus[MAX_UP + MAX_FRAME] = {};
int g_nDrawNum;
int g_nAttackUp[MAX_PLAYER] = {0};
int g_nShieldUp[MAX_PLAYER] = {0};
int g_nIndex = 0;
//=============================================================================
// 初期化処理
//=============================================================================
void InitStatus(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_nAttackUp[nCntPlayer] = 0;
		g_nShieldUp[nCntPlayer] = 0;
	}
	g_nDrawNum = 0;
	g_nIndex = 0;

	SetStatusUp();

	g_nDrawNum = (g_nAttackUp[0] + g_nAttackUp[1] + g_nShieldUp[0] + g_nShieldUp[1]) + MAX_FRAME;

	for (int nCnt = 0; nCnt < MAX_DRAW; nCnt++)
	{
		g_aStatus[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStatus[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aStatus[nCnt].fWidth = 0.0f;
		g_aStatus[nCnt].fHeight = 0.0f;
		g_aStatus[nCnt].type = STATUSINFO_ATTACK;
		g_aStatus[nCnt].bUse = false;
	}

	MakeVertexStatus(pDevice);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		SetStatus(D3DXVECTOR3(FRAME_1P_POS + (nCntFrame * FRAME_2P_POS), FRAME_Y_POS, 0.0f), FRAME_WIDTH, FRAME_HEIGHT, STATUSINFO_FRAME);
	}
	for (int nCntAttack1P = 0; nCntAttack1P < g_nAttackUp[0]; nCntAttack1P++)
	{
		SetStatus(D3DXVECTOR3(BRADE_1P_POS, FIRST_Y_POS + (nCntAttack1P * BRADE_SIZE), 0.0f), BRADE_SIZE, SHIELD_SIZE, STATUSINFO_ATTACK);
	}
	for (int nCntDefense1P = 0; nCntDefense1P < g_nShieldUp[0]; nCntDefense1P++)
	{
		SetStatus(D3DXVECTOR3(BRADE_1P_POS + (BRADE_SIZE * 2), FIRST_Y_POS + (nCntDefense1P * SHIELD_SIZE), 0.0f), BRADE_SIZE, SHIELD_SIZE, STATUSINFO_DEFENSE);
	}
	for (int nCntAttack2P = 0; nCntAttack2P < g_nAttackUp[1]; nCntAttack2P++)
	{
		SetStatus(D3DXVECTOR3(BRADE_2P_POS, FIRST_Y_POS + (nCntAttack2P * BRADE_SIZE), 0.0f), BRADE_SIZE, SHIELD_SIZE, STATUSINFO_ATTACK);
	}
	for (int nCntDefense2P = 0; nCntDefense2P < g_nShieldUp[1]; nCntDefense2P++)
	{
		SetStatus(D3DXVECTOR3(BRADE_2P_POS + (BRADE_SIZE * 2), FIRST_Y_POS + (nCntDefense2P * SHIELD_SIZE), 0.0f), BRADE_SIZE, SHIELD_SIZE, STATUSINFO_DEFENSE);
	}
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitStatus(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < STATUSINFO_MAX; nCnt++)
	{
		if (g_pTextureStatus[nCnt] != NULL)
		{
			g_pTextureStatus[nCnt]->Release();
			g_pTextureStatus[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStatus != NULL)
	{
		g_pVtxBuffStatus->Release();
		g_pVtxBuffStatus = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateStatus(void)
{
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawStatus(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイス取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStatus, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_DRAW; nCnt++)
	{
		if (g_aStatus[nCnt].bUse == true)		//使用しているなら描画する
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureStatus[g_aStatus[nCnt].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//=============================================================================
// 設定
//=============================================================================
void SetStatus(D3DXVECTOR3 pos, float fWidth, float fHeight, STATUSINFO type)
{
	VERTEX_2D * pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStatus->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aStatus[g_nIndex].bUse == false)
	{
		g_aStatus[g_nIndex].pos = pos;		// 位置
		g_aStatus[g_nIndex].fWidth = fWidth;	// 高さ
		g_aStatus[g_nIndex].fHeight = fHeight;	// 幅
		g_aStatus[g_nIndex].type = type;		// 種類

		pVtx[g_nIndex * 4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aStatus[g_nIndex].pos;
		pVtx[g_nIndex * 4 + 1].pos = D3DXVECTOR3(g_aStatus[g_nIndex].fWidth, 0.0f, 0.0f) + g_aStatus[g_nIndex].pos;
		pVtx[g_nIndex * 4 + 2].pos = D3DXVECTOR3(0.0f, g_aStatus[g_nIndex].fHeight, 0.0f) + g_aStatus[g_nIndex].pos;
		pVtx[g_nIndex * 4 + 3].pos = D3DXVECTOR3(g_aStatus[g_nIndex].fWidth, g_aStatus[g_nIndex].fHeight, 0.0f) + g_aStatus[g_nIndex].pos;
		g_aStatus[g_nIndex].bUse = true;
		g_nIndex++;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffStatus->Unlock();
}
//=============================================================================
// 頂点情報生成処理
//=============================================================================
void MakeVertexStatus(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DRAW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStatus,
		NULL);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BLADE_TEX, &g_pTextureStatus[STATUSINFO_ATTACK]);
	D3DXCreateTextureFromFile(pDevice, SHIELD_TEX, &g_pTextureStatus[STATUSINFO_DEFENSE]);
	D3DXCreateTextureFromFile(pDevice, FRAME_TEX, &g_pTextureStatus[STATUSINFO_FRAME]);

	VERTEX_2D * pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffStatus->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_DRAW; nCnt++, pVtx += 4)
	{
		// ポリゴンの座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aStatus[nCnt].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aStatus[nCnt].fWidth, 0.0f, 0.0f) + g_aStatus[nCnt].pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f, g_aStatus[nCnt].fHeight, 0.0f) + g_aStatus[nCnt].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aStatus[nCnt].fWidth, g_aStatus[nCnt].fHeight, 0.0f) + g_aStatus[nCnt].pos;
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
	g_pVtxBuffStatus->Unlock();
}
//=============================================================================
// ステータス上昇値設定
//=============================================================================
void SetStatusUp(void)
{
	char ReadText[256];	// 読み込んだ文字列を入れておく
	char HeadText[256];	// 比較用
	char DustBox[256];	// 使用しないものを入れておく

	int nUp = 0;
	// ファイルのポインタ取得
	FILE *pFile;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer == 0)
		{
			pFile = fopen(LOAD_TEXT_1P, "r");
		}
		else
		{
			pFile = fopen(LOAD_TEXT_2P, "r");
		}
		if (pFile != NULL)
		{
			while (strcmp(HeadText, "END_SCRIPT") != 0)
			{// "END_SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);
				if (strcmp(HeadText, "\n") == 0)
				{// 文字列の先頭が [\n](改行) の場合処理しない
					int nCnt = 0;
				}
				else if (strcmp(HeadText, "攻撃力") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &nUp);
					g_nAttackUp[nCntPlayer] = nUp;
				}
				else if (strcmp(HeadText, "防御力") == 0)
				{
					sscanf(ReadText, "%s %d", &DustBox, &nUp);
					g_nShieldUp[nCntPlayer] = nUp;
				}
			}
			fclose(pFile);
		}
		for (int nCnt = 0; nCnt < 256; nCnt++)
		{
			ReadText[nCnt] = NULL;
			HeadText[nCnt] = NULL;
		}
	}
}
