//=============================================================================
//
// yajirusi処理 [Yajirusi.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "Yajirusi.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_Yajirusi		(4)								// 敵の種類Yajirusi
#define Yajirusi_01 "data/TEXTURE/yaji000.png"
#define Yajirusi_02 "data/TEXTURE/yaji001.png"
#define Yajirusi_03 "data/TEXTURE/Yajirusi002.png"
#define Yajirusi_04 "data/TEXTURE/Yajirusi003.png"
#define Yajirusi_PMAX (15)											//敵の大きさ
#define	MAX_Yajirusi	(128)	// 敵の最大数

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureYajirusi[MAX_TYPE_Yajirusi] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffYajirusi = NULL;					// 頂点バッファへのポインタ
Yajirusi g_aYajirusi[MAX_Yajirusi];										//敵の情報
int g_YajiSe;
int g_YjirusiTime;

//=============================================================================
// 初期化処理
//=============================================================================
void InitYajirusi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntYajirusi;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		g_aYajirusi[nCntYajirusi].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aYajirusi[nCntYajirusi].nType = 0;
		g_aYajirusi[nCntYajirusi].fHeight = 0;
		g_aYajirusi[nCntYajirusi].fWindth = 0;
		g_aYajirusi[nCntYajirusi].bUse = false;
		g_aYajirusi[nCntYajirusi].nCounterAnim = 0;
		g_aYajirusi[nCntYajirusi].nPatternAnim = 0;
		g_aYajirusi[nCntYajirusi].nCounterState = 0;

		g_YajiSe = 0;
	}
	g_YjirusiTime = 0;
	
	// テクスチャの読み込み(４体分)
	// [1]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_01, &g_apTextureYajirusi[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_02, &g_apTextureYajirusi[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_03, &g_apTextureYajirusi[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_04, &g_apTextureYajirusi[3]);
	
	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Yajirusi,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffYajirusi,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		//ポジション
		pVtx[nCntYajirusi * 4].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
		
		//RHW
		pVtx[nCntYajirusi * 4].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 1].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 2].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 3].rhw = 1.0f;
		//カラー
		pVtx[nCntYajirusi * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[nCntYajirusi * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[nCntYajirusi * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[nCntYajirusi * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[nCntYajirusi * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffYajirusi->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitYajirusi(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_Yajirusi; nCntTex++)
	{
		if (g_apTextureYajirusi[nCntTex] != NULL)
		{
			g_apTextureYajirusi[nCntTex]->Release();
			g_apTextureYajirusi[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffYajirusi != NULL)
	{
		g_pVtxBuffYajirusi->Release();
		g_pVtxBuffYajirusi = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateYajirusi(void)
{
	VERTEX_2D*pVtx = NULL;	

	PLAYER *pPlyer;
	pPlyer = GetPlayer();
		
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
			g_aYajirusi[nCntYajirusi].pos.x -= pPlyer->move.x;
		
		if (g_aYajirusi[nCntYajirusi].bUse == true)//エネミーが使用されているか 
		{
			g_aYajirusi[nCntYajirusi].nCounterAnim++;
			if ((g_aYajirusi[nCntYajirusi].nCounterAnim % 15) == 0)
			{
				//パターンNo,更新
				g_aYajirusi[nCntYajirusi].nPatternAnim = (g_aYajirusi[nCntYajirusi].nPatternAnim + 1) % 4;				//パターンを初期化に戻す 
			}

			pVtx[0].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4), 0.0f);				 //右上
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4) + 0.25f, 0.0f);       //右上
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4), 1.0f);				 //右上
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4) + 0.25f, 1.0f);       //右上
		}
		pVtx += 4;
		
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffYajirusi->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawYajirusi(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffYajirusi, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		if (g_aYajirusi[nCntYajirusi].bUse == true) //敵が使用されているかどうか
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureYajirusi[g_aYajirusi[nCntYajirusi].nType]);
			//ポリゴンの描画
			if (g_aYajirusi[nCntYajirusi].bUse == true)//敵が使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntYajirusi * 4,2);
			}
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetYajirusi(int nType,D3DXVECTOR3 pos)
{
	int nCntYajirusi;
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		if (g_aYajirusi[nCntYajirusi].bUse == false)		//敵が使用されていない
		{
			g_aYajirusi[nCntYajirusi].pos = pos;
			g_aYajirusi[nCntYajirusi].nType = nType;
			g_aYajirusi[nCntYajirusi].fHeight = 0;
			g_aYajirusi[nCntYajirusi].fWindth = 0;
			g_aYajirusi[nCntYajirusi].bUse = true;			//敵が使用されている
			g_aYajirusi[nCntYajirusi].nCounterAnim = 0;
			g_aYajirusi[nCntYajirusi].nPatternAnim = 0;

			//ポジション
			pVtx[nCntYajirusi * 4].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			break;
		}

	}
	//頂点バッファアンロックする
	g_pVtxBuffYajirusi->Unlock();
}
//=============================================================================
// 敵の取得
//=============================================================================
Yajirusi *GetYajirusi(void)
{
	return &g_aYajirusi[0];
}