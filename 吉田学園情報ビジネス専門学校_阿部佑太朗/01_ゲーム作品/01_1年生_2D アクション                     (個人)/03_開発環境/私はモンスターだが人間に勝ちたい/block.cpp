//=============================================================================
//
// ブロックの処理 [Block.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "player.h"	
#include "input.h"
#include "sound.h"
#include "item.h"
#include "switch.h"
#include "fade.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define Block_TEXTURENAMRE0 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE1 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE2 "data/TEXTURE/block002.jpg"
#define Block_TEXTURENAMRE3 "data/TEXTURE/block003.jpg"
#define Block_TEXTURENAMRE4 "data/TEXTURE/block004.jpg"
#define Block_TEXTURENAMRE5 "data/TEXTURE/block001.jpg"
#define Block_TEXTURENAMRE6 "data/TEXTURE/beltkon000.png"
#define Block_TEXTURENAMRE7 "data/TEXTURE/bane000.png"
#define Block_TEXTURENAMRE8 "data/TEXTURE/kaidan000.png"
#define Block_TEXTURENAMRE9 "data/TEXTURE/Dokan001.png"
#define Block_TEXTURENAMRE10 "data/TEXTURE/kumo000.png"
#define Block_TEXTURENAMRE11 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE12 "data/TEXTURE/hatena000.png"
#define Block_TEXTURENAMRE13 "data/TEXTURE/bane001.png"
#define Block_TEXTURENAMRE14 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE15 "data/TEXTURE/.png"
#define Block_TEXTURENAMRE16 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE17 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE18 "data/TEXTURE/tuto000.png"
#define Block_TEXTURENAMRE19 "data/TEXTURE/kanban000.png"
#define Block_TEXTURENAMRE20 "data/TEXTURE/kanban001.png"
#define Block_TEXTURENAMRE21 "data/TEXTURE/kanban002.png"
#define Block_TEXTURENAMRE22 "data/TEXTURE/kanban003.png"
#define Block_TEXTURENAMRE23 "data/TEXTURE/kanban004.png"
#define Block_TEXTURENAMRE24 "data/TEXTURE/hatena000.png"
#define Block_TEXTURENAMRE25 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE26 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE27 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE28 "data/TEXTURE/kanban005.png"
#define Block_TEXTURENAMRE29 "data/TEXTURE/kanban006.png"
#define Block_TEXTURENAMRE30 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE31 "data/TEXTURE/Dokan000.png"
#define Block_TEXTURENAMRE32 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE33 "data/TEXTURE/aaa.png"
#define Block_TEXTURENAMRE34 "data/TEXTURE/111.png"
#define Block_TEXTURENAMRE35 "data/TEXTURE/upblock000.png"
#define	MAX_Block		(266)					// ブロックの最大数
#define POS_X (150)								//ポジション_X
#define POS_Y (25)								//ポジション_Y
#define TEX_MAX (36)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ
Block g_aBlock[MAX_Block];						//ブロックの情報
bool g_BreakBlock;
bool g_Item =false;
bool g_blockSwitti;
//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nCounterrMove = 0;
		g_aBlock[nCntBlock].nType = 0;
		g_aBlock[nCntBlock].fWindth = 0;		//幅
		g_aBlock[nCntBlock].fHeight = 0;		//高さ
		g_aBlock[nCntBlock].bUse = false;
	}
	g_blockSwitti = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE0, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE7, &g_pTextureBlock[7]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE8, &g_pTextureBlock[8]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE9, &g_pTextureBlock[9]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE10, &g_pTextureBlock[10]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE11, &g_pTextureBlock[11]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE12, &g_pTextureBlock[12]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE13, &g_pTextureBlock[13]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE14, &g_pTextureBlock[14]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE15, &g_pTextureBlock[15]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE16, &g_pTextureBlock[16]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE17, &g_pTextureBlock[17]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE18, &g_pTextureBlock[18]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE19, &g_pTextureBlock[19]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE20, &g_pTextureBlock[20]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE21, &g_pTextureBlock[21]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE22, &g_pTextureBlock[22]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE23, &g_pTextureBlock[23]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE24, &g_pTextureBlock[24]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE25, &g_pTextureBlock[25]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE26, &g_pTextureBlock[26]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE27, &g_pTextureBlock[27]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE28, &g_pTextureBlock[28]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE29, &g_pTextureBlock[29]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE30, &g_pTextureBlock[30]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE31, &g_pTextureBlock[31]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE32, &g_pTextureBlock[32]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE33, &g_pTextureBlock[33]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE34, &g_pTextureBlock[34]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE35, &g_pTextureBlock[35]);
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Block,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);													//左上
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);						//右上
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);						//左上
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//右下
		 //RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//左上
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//右上
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//左上
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//右下

		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャの開放
		if (g_pTextureBlock[nCount] != NULL)
		{
			g_pTextureBlock[nCount]->Release();
			g_pTextureBlock[nCount] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=============================================================================
// 更新処理 
//=============================================================================
void UpdateBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		g_aBlock[nCntBlock].posOld.x = g_aBlock[nCntBlock].pos.x;
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].pos.x == 0)
		{
			g_aBlock[nCntBlock].move.x = 0;
		}
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPlyer->pos.x >= 0)
			{//プレイヤーが0以上ならブロックをプレイヤーとは反対方向に動かす
				g_aBlock[nCntBlock].pos.x -= pPlyer->move.x;
				//	g_aBlock[nCntBlock].pos.x -= pPlyer->pos.x - pPlyer->posOld.x;

			}
			if (pPlyer->pos.y >= -0.1f)
			{
				g_aBlock[nCntBlock].pos.y -= pPlyer->move.y;
			}
			if (pPlyer->pos.y >= 0.1f)
			{
				g_aBlock[nCntBlock].pos.y += pPlyer->move.y;
			}

			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			g_aBlock[nCntBlock].nCounterrMove++;

			//タイプ3
			if (g_aBlock[nCntBlock].nCounterrMove % 60 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 3)
				{
					g_aBlock[nCntBlock].move.y *= 1.0f;
				}
			}
			if (g_aBlock[nCntBlock].nCounterrMove % 120 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 3)
				{
					g_aBlock[nCntBlock].move.y *= -1.0f;
				}
			}
			//タイプ15
			if (g_aBlock[nCntBlock].nCounterrMove % 60 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 15)
				{
					g_aBlock[nCntBlock].move.x *= 1.0f;
				}
			}
			if (g_aBlock[nCntBlock].nCounterrMove % 120 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 15)
				{
					g_aBlock[nCntBlock].move.x *= -1.0f;
				}
			}
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//左上
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//右上
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//左上
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//右下
			
		}
		pVtx += 4;	//頂点ポインタを4つ進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);

		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)	//ブロックが使用されていない
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWindth = fWindth;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;//ブロックが使用されている
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//左上
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//右上
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//左上
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//右下
			
			if (g_aBlock[nCntBlock].nType == 0)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//左上
				pVtx[1].tex = D3DXVECTOR2(10.0f * 10/10, 0.0f);						//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f * 10 / 10);					//左上
				pVtx[3].tex = D3DXVECTOR2(10.0f * 10 / 10, 5.0f * 10 / 10);			//右下
			}
			if (g_aBlock[nCntBlock].nType == 16)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//左上
				pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);								//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f * 10 / 10);					//左上
				pVtx[3].tex = D3DXVECTOR2(1.0, 5.0f * 10 / 10);						//右下
			}
			if (g_aBlock[nCntBlock].nType == 17)
			{
				//テクスチャ座標
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//左上
				pVtx[1].tex = D3DXVECTOR2(50.0f * 10 / 10, 0.0f);					//右上
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);								//左上
				pVtx[3].tex = D3DXVECTOR2(50.0f * 10 / 10,1.0f);					//右下
			}
			break;
		}
		pVtx += 4;			//該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
//ブロックとプレイヤーとの判定処理
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 bool bLand = false;	//着地したかどうか
	 Enemy *pEnemy;
	 pEnemy = GetEnemy();

	 for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	 {
		 if (g_aBlock[nCntBlock].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aBlock[nCntBlock].pos.x  &&									//プレイヤーが右からめり込んでるとき
				 pPos->x - (*fWindth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&		//プレイヤーが左からめり込んでるとき
				 pPos->y >= g_aBlock[nCntBlock].pos.y &&															//プレイヤーが上から下にめり込んでるとき
				 pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)					//プレイヤーが下から上にめり込んでるとき
			 {//YXが範囲内
				 if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
				 {//ブロック上判定
					 bLand = true;
					 pPos->y = g_aBlock[nCntBlock].pos.y;		//プレイヤーをブロックのポジションYに出現させる
					 if (pMove->y >= 20.0f)
					 {
						 HitPlayer(1);
					 }
					 pMove->y = 0.0f;
					 //タイプ2------------------------
					 if (g_aBlock[nCntBlock].nType == 2)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ブロック(ブロック落ちる)
						 bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;														//プレイヤーをブロックのポジションYに出現させる
						 g_aBlock[nCntBlock].move.y = 0.8f;
					 }
					 //タイプ6------------------------
					 if (g_aBlock[nCntBlock].nType == 6)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ベルトコンベア
					  //bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;																						//プレイヤーをブロックのポジションYに出現させる
						 pMove->x = pMove->x + 1.0f;
					 }
					 //タイプ7------------------------
					 if (g_aBlock[nCntBlock].nType == 13)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ばね
						 bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;																						//プレイヤーをブロックのポジションYに出現させる
						 pMove->y -= 20;				//重力
						 g_aBlock[nCntBlock].nType = 7;
					 }
					 else if (g_aBlock[nCntBlock].nType == 7)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ばね
						 PlaySound(SOUND_LABEL_SE_BANE);

						 g_aBlock[nCntBlock].nType = 13;
					 }

					 //タイプ3------------------------
					 if (g_aBlock[nCntBlock].nType == 3)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ブロック上(動く床上下)
						 bLand = true;

						 pPos->y = g_aBlock[nCntBlock].pos.y;														//プレイヤーをブロックのポジションYに出現させる
						 //pPos->y += g_aBlock[nCntBlock].move.y;
						 pPos->y += g_aBlock[nCntBlock].move.y;

					 }
					 //タイプ15------------------------
					 if (g_aBlock[nCntBlock].nType == 15)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ブロック上(動く床)
						 bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x;
						 pPos->x += g_aBlock[nCntBlock].move.x;
						 //pMove->x += g_aBlock[nCntBlock].move.x;
						 /*if (g_aBlock[nCntBlock].move.y >= 1.0f)
						 {
						 pPos->y -= g_aBlock[nCntBlock].move.y;
						 }
						 if (g_aBlock[nCntBlock].move.y <= -1.0f)
						 {
						 pPos->y += g_aBlock[nCntBlock].move.y;
						 }*/
					 }
					 //タイプ10------------------------
					 if (g_aBlock[nCntBlock].nType == 10)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ブロック上(手動で動く)
					  //bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;														//プレイヤーをブロックのポジションYに出現させる
						 g_aBlock[nCntBlock].pos.x = pPos->x;
						 g_aBlock[nCntBlock].pos.x = 560;
					 }
					 //タイプ4-----------------------
					 if (g_aBlock[nCntBlock].nType == 4)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
					 {//ブロック上に乗ったらfalse
						 bLand = true;
						 PlaySound(SOUND_LABEL_SE_BAKEHATU);
						 g_aBlock[nCntBlock].pos.y = 900;
					 }
					 //タイプ14-----------------------
					 if (g_aBlock[nCntBlock].nType == 14)
					 {

						 /*( g_aBlock[nCntBlock].nType = 14)=g_aBlock[nCntBlock].move.y = 1;
						 if (g_aBlock[nCntBlock].nType = 14 && g_aBlock[nCntBlock].posOld.y >= g_aBlock[nCntBlock].pos.y + 30)
						 {
							 g_aBlock[nCntBlock].move.y = -1;
						 }
						  pPos->y = g_aBlock[nCntBlock].pos.y;*/
					 }
				 }
				 else if (pPosOld->y - *fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&	//プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
					 pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)				//現在の位置がめり込んでるとき
				 {//ブロック下判定
					 //bLand = true;
					 pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;				//プレイヤーをブロック中心+ブロックの高さ+プレイヤーの高さの位置に出現させる
					 pMove->y = 0.0f;
					 //タイプ12------------------------
					 if (g_aBlock[nCntBlock].nType == 12)
					 {////?ブロックコイン
						 PlaySound(SOUND_LABEL_SE_HATENA);
						 bLand = true;
						 //スイッチ
						 SetItem(0, D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWindth / 2), g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						 g_aBlock[nCntBlock].nType = 0;

					 }
					 //タイプ24------------------------
					 if (g_aBlock[nCntBlock].nType == 24)
					 {//?ブロック回復
						 PlaySound(SOUND_LABEL_SE_HATENA);
						 SetItem(2, D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWindth / 2), g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						 g_aBlock[nCntBlock].nType = 0;

					 }
				 }
				 else if (pPosOld->x + *fWindth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&	//昔の位置がブロックより右にあって現在の位置がめり込んでる場合
					 pPos->x - *fWindth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth)
				 {//ブロック右判定
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 pEnemy->move.x = 3.0f;
					 //タイプ5------------------------
					 if (g_aBlock[nCntBlock].nType == 5)
					 {//左右に手動で動かす
						 g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x - 1.0f;
					 }
					 //タイプ11------------------------
					 if (g_aBlock[nCntBlock].nType == 11)
					 {//Nキーで上に上がる
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;

						 }
						 else  if (GetKeyboardTrigger(DIK_N) == false)
						 {
							 g_aBlock[nCntBlock].pos.y += *fHeight;
						 }
					 }

				 }
				 else if (pPosOld->x - *fWindth <= g_aBlock[nCntBlock].pos.x &&									//昔の位置がブロックより左にあって現在の位置がめり込んでる場合
					 pPos->x + *fWindth >= g_aBlock[nCntBlock].pos.x)
				 {//ブロック左判定
					 //bLand = true;
					 pPos->x = pPosOld->x;																		//昔の位置に出現させる
					 pMove->x = 0.0f;
					 pEnemy->move.x = -3.0f;
					 //タイプ5------------------------
					 if (g_aBlock[nCntBlock].nType == 5)
					 {//左右に手動で動かす
						 g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x + 2.0f;
					 }
					 //タイプ8------------------------
					 if (g_aBlock[nCntBlock].nType == 8)															//昔の位置がブロックより左にあって現在の位置がめり込んでる場合
					 {//ブロック左判定 (階段)
						 //bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x;													//昔の位置に出現させる
						 pPos->y = g_aBlock[nCntBlock].pos.y;
						 pMove->x = 5.0f;

						 // g_aBlock[nCntBlock].move.y = 1.0f;
					 }
					 if (g_aBlock[nCntBlock].nType == 11)
					 {//Nキーで上に上がる
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 25)
					 {//Nキーで上に上がる
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 //セットエネミー
							 SetEnemy(3, D3DXVECTOR3(1000, 300.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 50, 70, 7);
							 SetEnemy(2, D3DXVECTOR3(900, 300.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(2, D3DXVECTOR3(1150, 300.0f, 0), D3DXVECTOR3(0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(1, D3DXVECTOR3(1300, 300.0f, 0), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), 30, 60, 3);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 30)
					 {//Nキーで上に上がる
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 //セットエネミー
							 SetEnemy(3, D3DXVECTOR3(1000, 300.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 50, 70, 7);
							 SetEnemy(2, D3DXVECTOR3(900, 300.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(3, D3DXVECTOR3(1150, 300.0f, 0), D3DXVECTOR3(0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(1, D3DXVECTOR3(4300, 500.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
							 SetEnemy(1, D3DXVECTOR3(4500, 500.0f, 0), D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30, 60, 2);
							 SetEnemy(1, D3DXVECTOR3(4800, 500.0f, 0), D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30, 60, 2);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 32)
					 {//Nキーで上に上がる
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 SetBlock(D3DXVECTOR3(1400, 355.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 50.0f, 33);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 //タイプ9------------------------
					 if (g_aBlock[nCntBlock].nType == 9)
					 {//土管横から上
					  //bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x + *fWindth;																		//昔の位置に出現させる
						 pMove->x = 0.0f;
						 pMove->y = -30;
					 }
					 if (g_aBlock[nCntBlock].nType == 14)
					 {//ドア
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //モード設定
								 SetFade(MODE_SELECT);

							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 26)
					 {//ドア
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //モード設定
								 SetFade(MODE_GAME2);

							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 27)
					 {//ドア
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //モード設定
								 SetFade(MODE_GAME3);
							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 33)
					 {
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 //モード設定
							 SetFade(MODE_CLIA);
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 35)
					 {//ドア
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
				 }

			 }
		 }
	 }
	 return bLand;
}
//=============================================================================
//ブロックとエネミーとの判定処理
//=============================================================================
void CollisionBlockEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aBlock[nCntBlock].pos.x  &&
				pPos->x - (*fWindth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&
				pPos->y >= g_aBlock[nCntBlock].pos.y &&
				pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//YXが範囲内
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//ブロック上判定
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;

				}
				else if (pPosOld->y - *fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//ブロック下判定
				 //bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;
					pMove->y = 0.0f;

				}
				else if (pPosOld->x + *fWindth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&
					pPos->x - *fWindth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth)
				{//ブロック右判定
				 //	bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
					if (pMove->x <= 0)
					{
						pMove->x = 1.0f;
					}
				}
				else if (pPosOld->x - *fWindth <= g_aBlock[nCntBlock].pos.x &&
					pPos->x + *fWindth >= g_aBlock[nCntBlock].pos.x)
				{//ブロック左判定
				 //bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
					if (pMove->x <= 0)
					{
						pMove->x -= 1.0f;
					}
				}
			}
		}
	}
}
			
//=============================================================================
// 敵の取得
//=============================================================================
Block *Getblock(void)
{
	return &g_aBlock[0];
}