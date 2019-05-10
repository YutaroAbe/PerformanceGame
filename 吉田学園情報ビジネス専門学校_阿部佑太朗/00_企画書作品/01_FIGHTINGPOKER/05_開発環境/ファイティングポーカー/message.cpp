//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッセージ処理 [message.cpp]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "message.h"
#include "main.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESSAGE_MAX					(10)				// メッセージの最大数
#define MESSAGE_WIDTH				(500)				// 幅
#define MESSAGE_HEIGHT				(70)				// 高さ
#define MESSAGE_FRAME_WIDTH			(10)				// 枠の幅
#define MESSAGE_DEST_APPROX			(0.5f)				// 目的地の近似値

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // 状態の列挙体
	MESSAGE_STATE_NONE = 0,		// 通常状態
	MESSAGE_STATE_SIZE_CHANGE,	// サイズ変更状態
	MESSAGE_STATE_WAIT,			// 待機状態
	MESSAGE_STATE_DELETE,		// 削除状態
	MESSAGE_STATE_MAX,			// 総数
}MESSAGE_STATE;

typedef struct
{
	char *pFilename;	// ファイル名
} MessageTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXCOLOR col;			// 色
	float fWidth;			// 幅
	float fDestWidth;		// 目的の幅
	float fHeight;			// 高さ
	float fDestHeight;		// 目的の高さ
	int nTexType;			// テクスチャの種類
	MESSAGE_STATE state;	// 状態
	int nStateCounter;		// 状態のカウンター
	int nStateDestTime;		// 目的までの時間
	bool bUse;				// 使用しているかどうか
}Message;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice);
void UpdateVertexMessage(void);
void UpdateVertexMessage(int nCntMessage);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// グローバル変数宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTextureMessage[MESSAGE_TEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMessage = NULL;				// 頂点バッファへのポインタ
Message					g_aMessage[MESSAGE_MAX];				// メッセージの情報

// 読み込むテクスチャ名の設定
MessageTexInfo g_apTextureMessageTInfo[MESSAGE_TEX_MAX] =
{

	{ "data//TEXTURE//MESSAGE//round1_000.png" },		// ROUND1
	{ "data//TEXTURE//MESSAGE//round2_000.png" },		// ROUND2
	{ "data//TEXTURE//MESSAGE//round3_000.png" },		// ROUND3
	{ "data//TEXTURE//MESSAGE//round4_000.png" },		// ROUND4
	{ "data//TEXTURE//MESSAGE//finalround.png" },		// FinalROUND
	{ "data//TEXTURE//MESSAGE//fight000.png" },			// ファイト
	{ "data//TEXTURE//MESSAGE//KO002.png" },			// KO
	{ "data//TEXTURE//MESSAGE//timeover000.png" },		// TIMEOVER
};

int g_nMessageCounter = 0;	// メッセージ表示タイミングのカウンター
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 初期化処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMessage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 情報の初期化
	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		g_aMessage[nCntMessage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMessage[nCntMessage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aMessage[nCntMessage].fWidth = 0.0f;
		g_aMessage[nCntMessage].fDestWidth = 0.0f;
		g_aMessage[nCntMessage].fHeight = 0.0f;
		g_aMessage[nCntMessage].fDestHeight = 0.0f;
		g_aMessage[nCntMessage].state = MESSAGE_STATE_NONE;
		g_aMessage[nCntMessage].nStateCounter = 0;
		g_aMessage[nCntMessage].nStateDestTime = 0;
		g_aMessage[nCntMessage].bUse = false;
	}

	for (int nCntMessageTex = 0; nCntMessageTex < MESSAGE_TEX_MAX; nCntMessageTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMessageTInfo[nCntMessageTex].pFilename,
			&g_pTextureMessage[nCntMessageTex]);
	}

	// 初期化
	g_nMessageCounter = 0;

	// 頂点情報の作成
	MakeVertexMessage(pDevice);

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 終了処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMessage(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < MESSAGE_TEX_MAX; nCntTex++)
	{
		if (g_pTextureMessage[nCntTex] != NULL)
		{
			g_pTextureMessage[nCntTex]->Release();
			g_pTextureMessage[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMessage != NULL)
	{
		g_pVtxBuffMessage->Release();
		g_pVtxBuffMessage = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 更新処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMessage()
{
	// ラウンド数を取得
	int nRound = GetRoundCounter();

	g_nMessageCounter++;

	if (g_nMessageCounter == MESSAGE_ROUND_FRAME)
	{// ラウンド発生
		if (nRound == 1)
		{// 1ラウンド目
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND1);
			SelectVolume(SOUND_LABEL_R1_SE, 0.8f);
		}
		else if (nRound == 2)
		{// 2ラウンド目
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND2);
			SelectVolume(SOUND_LABEL_R2_SE, 0.8f);
		}
		else if (nRound == 3)
		{// 3ラウンド目
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND3);
			SelectVolume(SOUND_LABEL_R3_SE, 0.8f);
		}
		else if (nRound == 4)
		{// 4ラウンド目
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND4);
			SelectVolume(SOUND_LABEL_R4_SE, 0.8f);
		}
		else if (nRound == 5)
		{// ファイナルラウンド目
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND5);
			SelectVolume(SOUND_LABEL_R5_SE, 0.8f);
		}
	}

	if (g_nMessageCounter == MESSAGE_FIGHT_FRAME)
	{// ファイト発生
		SetMessage(D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f), 400.0f, 300.0f, MESSAGE_TEX_FIGHT);
		SelectVolume(SOUND_LABEL_FIGHT_SE, 0.8f);
	}


	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == true)
		{
			switch (g_aMessage[nCntMessage].state)
			{ // 状態の処理
			case MESSAGE_STATE_SIZE_CHANGE:
				g_aMessage[nCntMessage].nStateCounter++;

				// 幅の増減を行う
				g_aMessage[nCntMessage].fWidth += g_aMessage[nCntMessage].fDestWidth / (float)g_aMessage[nCntMessage].nStateDestTime;
				g_aMessage[nCntMessage].fHeight += g_aMessage[nCntMessage].fDestHeight / (float)g_aMessage[nCntMessage].nStateDestTime;

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // 指定した時間になった場合
				  // 目的の値を代入
					g_aMessage[nCntMessage].fWidth = g_aMessage[nCntMessage].fDestWidth;
					g_aMessage[nCntMessage].fHeight = g_aMessage[nCntMessage].fDestHeight;
					// 状態を待機状態にする
					g_aMessage[nCntMessage].state = MESSAGE_STATE_WAIT;
					// 目的の時間を設定
					g_aMessage[nCntMessage].nStateDestTime = MESSAGE_WAIT_FRAME;
					// カウンターをリセット
					g_aMessage[nCntMessage].nStateCounter = 0;
				}
				break;
			case MESSAGE_STATE_WAIT:
				g_aMessage[nCntMessage].nStateCounter++;

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // 指定した時間になった場合
					// 目的の時間を設定する
					g_aMessage[nCntMessage].nStateDestTime = 0;
					// 状態を削除状態にする
					g_aMessage[nCntMessage].state = MESSAGE_STATE_DELETE;
					// 目的の時間を設定
					g_aMessage[nCntMessage].nStateDestTime = MESSAGE_DELETE_FRAME;
					// カウンターをリセット
					g_aMessage[nCntMessage].nStateCounter = 0;
				}
				break;
			case MESSAGE_STATE_DELETE:
				g_aMessage[nCntMessage].nStateCounter++;

				g_aMessage[nCntMessage].col.a -= float(1.0f / (float)g_aMessage[nCntMessage].nStateDestTime);

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // 指定した時間になった場合
					g_aMessage[nCntMessage].bUse = false;
				}
				break;
			}

			// 頂点情報の更新(個別)
			UpdateVertexMessage(nCntMessage);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 描画処理
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMessage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffMessage, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == true)	// メッセージが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMessage[g_aMessage[nCntMessage].nTexType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMessage * 4, 2);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// メッセージの設定
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetMessage(D3DXVECTOR3 pos, float fDestWidth, float fDestHeight, MESSAGE_TEX_TYPE texType)
{
	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == false)
		{ // メッセージが使用されていない場合
		  // 頂点情報の設定
			g_aMessage[nCntMessage].pos = pos;
			g_aMessage[nCntMessage].nTexType = texType;
			g_aMessage[nCntMessage].fWidth = 0.0f;
			g_aMessage[nCntMessage].fHeight = 0.0f;
			g_aMessage[nCntMessage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			g_aMessage[nCntMessage].fDestWidth = fDestWidth;
			g_aMessage[nCntMessage].fDestHeight = fDestHeight;

			// 状態を削除状態にする
			g_aMessage[nCntMessage].state = MESSAGE_STATE_SIZE_CHANGE;
			// 目的の時間を設定
			g_aMessage[nCntMessage].nStateDestTime = MESSAGE_APPEAR_FRAME;
			// カウンターをリセット
			g_aMessage[nCntMessage].nStateCounter = 0;

			// 頂点情報の更新(個別)
			UpdateVertexMessage(nCntMessage);

			g_aMessage[nCntMessage].bUse = true;	// 使用する状態にする
			break;	// このbreakはかなり大切
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の更新
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexMessage(void)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++, pVtx += 4)
	{

		// 頂点情報の設定
		pVtx[0].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[1].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[2].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[3].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = g_aMessage[nCntMessage].col;
		pVtx[1].col = g_aMessage[nCntMessage].col;
		pVtx[2].col = g_aMessage[nCntMessage].col;
		pVtx[3].col = g_aMessage[nCntMessage].col;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffMessage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の個別更新
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexMessage(int nCntMessage)
{
	// 頂点バッファを生成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を進める
	pVtx += 4 * nCntMessage;

	pVtx[0].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_aMessage[nCntMessage].col;
	pVtx[1].col = g_aMessage[nCntMessage].col;
	pVtx[2].col = g_aMessage[nCntMessage].col;
	pVtx[3].col = g_aMessage[nCntMessage].col;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffMessage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// 頂点情報の作成
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MESSAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMessage,
		NULL);

	// 頂点情報の更新
	UpdateVertexMessage();
}

