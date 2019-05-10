//=============================================================================
//
// トラップの処理 [Trap.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "trap.h"
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
#define Trap_TEXTURENAMRE0 "data/TEXTURE/trap000.png"
#define Trap_TEXTURENAMRE1 "data/TEXTURE/trap001.png"
#define Trap_TEXTURENAMRE2 "data/TEXTURE/trap002.png"
#define Trap_TEXTURENAMRE3 "data/TEXTURE/trap000.png"
#define Trap_TEXTURENAMRE4 "data/TEXTURE/trap003.png"

#define	MAX_Trap		(126)					// ブロックの最大数
#define POS_X (150)								//ポジション_X
#define POS_Y (25)								//ポジション_Y
#define TEX_MAX (5)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTrap[TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTrap = NULL;	// 頂点バッファへのポインタ
TRAP g_aTrap[MAX_Trap];						//ブロックの情報
bool g_BreakTrap;
//bool g_Item = false;
bool g_TrapSwitti;
//=============================================================================
// 初期化処理
//=============================================================================
void InitTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTrap[nCntTrap].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTrap[nCntTrap].nCounterrMove = 0;
		g_aTrap[nCntTrap].nType = 0;
		g_aTrap[nCntTrap].fWindth = 0;		//幅
		g_aTrap[nCntTrap].fHeight = 0;		//高さ
		g_aTrap[nCntTrap].bUse = false;
	}
	g_TrapSwitti = 0;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE0, &g_pTextureTrap[0]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE1, &g_pTextureTrap[1]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE2, &g_pTextureTrap[2]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE3, &g_pTextureTrap[3]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE4, &g_pTextureTrap[4]);


	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Trap,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTrap,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		//ポジション
		pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);													//左上
		pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);						//右上
		pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);						//左上
		pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//右下
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
	g_pVtxBuffTrap->Unlock();

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitTrap(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャの開放
		if (g_pTextureTrap[nCount] != NULL)
		{
			g_pTextureTrap[nCount]->Release();
			g_pTextureTrap[nCount] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTrap != NULL)
	{
		g_pVtxBuffTrap->Release();
		g_pVtxBuffTrap = NULL;
	}
}
//=============================================================================
// 更新処理 
//=============================================================================
void UpdateTrap(void)
{
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].posOld.x = g_aTrap[nCntTrap].pos.x;
	}
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].nCounterrMove++;
		if (g_aTrap[nCntTrap].pos.x == 0)
		{
			g_aTrap[nCntTrap].move.x = 0;
		}
		if (g_aTrap[nCntTrap].bUse == true)
		{
			g_aTrap[nCntTrap].pos.x += g_aTrap[nCntTrap].move.x;
			g_aTrap[nCntTrap].pos.y += g_aTrap[nCntTrap].move.y;
			if (pPlyer->pos.x >= 0)
			{//プレイヤーが0以上ならブロックをプレイヤーとは反対方向に動かす
				g_aTrap[nCntTrap].pos.x -= pPlyer->move.x;
				//	g_aTrap[nCntTrap].pos.x -= pPlyer->pos.x - pPlyer->posOld.x;

			}
			
			//タイプ3
			if (g_aTrap[nCntTrap].nCounterrMove % 60 == 0)
			{
				if (g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
				{
					g_aTrap[nCntTrap].move.y *= 1.0f;
				}
			}
			if (g_aTrap[nCntTrap].nCounterrMove % 120 == 0)
			{
				if (g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
				{
					g_aTrap[nCntTrap].move.y *= -1.0f;
				}
			}
			
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//左上
			pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//右上
			pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//左上
			pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//右下
			pVtx += 4;	//頂点ポインタを4つ進める
		}
	}
	//頂点バッファアンロックする
	g_pVtxBuffTrap->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTrap, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTrap[g_aTrap[nCntTrap].nType]);
			// ポリゴンの描画
			if (g_aTrap[nCntTrap].bUse == true)//ブロックが使用されている
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTrap, 2);
			}
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == false)	//ブロックが使用されていない
		{
			g_aTrap[nCntTrap].pos = pos;
			g_aTrap[nCntTrap].move = move;
			g_aTrap[nCntTrap].fHeight = fHeight;
			g_aTrap[nCntTrap].fWindth = fWindth;
			g_aTrap[nCntTrap].nType = nType;
			g_aTrap[nCntTrap].bUse = true;		//ブロックが使用されている
			//ポジション
			pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//左上
			pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//右上
			pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//左上
			pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//右下
			
			break;
		}
		pVtx += 4;								//該当の位置で進める
	}
	//頂点バッファアンロックする
	g_pVtxBuffTrap->Unlock();
}
//=============================================================================
//ブロックとプレイヤーとの判定処理
//=============================================================================
void CollisionTrap(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 Enemy *pEnemy;
	 pEnemy = GetEnemy();

	 for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	 {
		 if (g_aTrap[nCntTrap].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aTrap[nCntTrap].pos.x  &&									//プレイヤーが右からめり込んでるとき
				 pPos->x - (*fWindth / 2) <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&		//プレイヤーが左からめり込んでるとき
				 pPos->y >= g_aTrap[nCntTrap].pos.y &&															//プレイヤーが上から下にめり込んでるとき
				 pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)					//プレイヤーが下から上にめり込んでるとき
			 {//YXが範囲内
				 if (pPosOld->y <= g_aTrap[nCntTrap].pos.y && pPos->y >= g_aTrap[nCntTrap].pos.y)			//昔の位置が上に居て現在の位置がプロックにめり込んでるとき
				 {//ブロック上判定
					 pPos->y = g_aTrap[nCntTrap].pos.y;		//プレイヤーをブロックのポジションYに出現させる
					 pMove->y = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 1)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					
				 }
				 else if (pPosOld->y - *fHeight >= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight &&	//プレイヤーの中心を頭にしてその中心の昔の位置は下にあって
					 pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)				//現在の位置がめり込んでるとき
				 {//ブロック下判定
					 //bLand = true;
					 pPos->y = g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight + *fHeight;				//プレイヤーをブロック中心+ブロックの高さ+プレイヤーの高さの位置に出現させる
					 pMove->y = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = 15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = 15.0f;
						 HitPlayer(1);
					 }
				 }
				 else if (pPosOld->x + *fWindth >= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&	//昔の位置がブロックより右にあって現在の位置がめり込んでる場合
					 pPos->x - *fWindth <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth)
				 {//ブロック右判定
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = 15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = 15.0f;
						 pMove->y = -10.0f;
						 HitPlayer(1);
					 }
				 }
				 else if (pPosOld->x - *fWindth <= g_aTrap[nCntTrap].pos.x &&									//昔の位置がブロックより左にあって現在の位置がめり込んでる場合
					 pPos->x + *fWindth >= g_aTrap[nCntTrap].pos.x)
				 {//ブロック左判定
					 //bLand = true;
					 pPos->x = pPosOld->x;																		//昔の位置に出現させる
					 pMove->x = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = -15.0f;
						 pMove->y = -10.0f;
						 HitPlayer(1);
					 }
				 }
				 
			 }
		 }
	 }
}
//=============================================================================
//ブロックとエネミーとの判定処理
//=============================================================================
void CollisionTrapEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aTrap[nCntTrap].pos.x  &&
				pPos->x - (*fWindth / 2) <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&
				pPos->y >= g_aTrap[nCntTrap].pos.y &&
				pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)
			{//YXが範囲内
				if (pPosOld->y <= g_aTrap[nCntTrap].pos.y && pPos->y >= g_aTrap[nCntTrap].pos.y)
				{//ブロック上判定
					pPos->y = g_aTrap[nCntTrap].pos.y;
					pMove->y = 0.0f;

				}
				else if (pPosOld->y - *fHeight >= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight &&
					pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)
				{//ブロック下判定
				 //bLand = true;
					pPos->y = g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight + *fHeight;
					pMove->y = 0.0f;

				}
				else if (pPosOld->x + *fWindth >= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&
					pPos->x - *fWindth <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth)
				{//ブロック右判定
				 //	bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
				}
				else if (pPosOld->x - *fWindth <= g_aTrap[nCntTrap].pos.x &&
					pPos->x + *fWindth >= g_aTrap[nCntTrap].pos.x)
				{//ブロック左判定
				 //bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
				}
			}
		}
	}
}
			
//=============================================================================
// 敵の取得
//=============================================================================
TRAP *GetTrap(void)
{
	return &g_aTrap[0];
}