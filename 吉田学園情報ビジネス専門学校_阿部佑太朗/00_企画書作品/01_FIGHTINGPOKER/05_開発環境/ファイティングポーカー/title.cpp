//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : ABE YUTARO
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "gamepad.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURENAME1	"data/TEXTURE/TITLE/TitleLogo000.png"				// 読み込むテクスチャの名前１
#define TITLE_TEXTURENAME2	"data/TEXTURE/TITLE/TitleLogo001.png"				// 読み込むテクスチャの名前2
#define TITLE_TEXTURENAME3	"data/TEXTURE/TITLE/PressAnyBotton.png"				// 読み込むテクスチャの名前２
#define TITLE_TEXTURENAME4	"data/TEXTURE/TITLE/lightning.png"					// 読み込むテクスチャの名前２
#define TITLE_TEXTURENAME5	"data/TEXTURE/TITLE/KUROMEN.png"					// 読み込むテクスチャの名前２
#define TITLE_TEXTURENAME6	"data/TEXTURE/TITLE/Trump.png"					    // 読み込むテクスチャの名前２
#define TITLE_TEXTURENAME7	"data/TEXTURE/TITLE/sword.png"					    // 読み込むテクスチャの名前２

//タイトルBG---------------------------------------------------------------------------
#define TITLE_BG_POS_X_A	(SCREEN_WIDTH/2)				// ロゴのX座標_A
#define TITLE_BG_POS_Y_A	(SCREEN_HEIGHT/2)				// ロゴのY座標_A
#define TITLE_BG_WIDTH_A	(SCREEN_WIDTH)					// ロゴの幅
#define TITLE_BG_HEIGHT_A	(SCREEN_HEIGHT)					// ロゴの高さ
//ソード------------------------------------------------------------------------------
#define TITLE_SWORD_POS_X	(400.0f)						// ロゴのX座標_A
#define TITLE_SWORD_POS_Y	(250.0f)						// ロゴのY座標_A
#define TITLE_SWORD_WIDTH	(400.0f)						// ロゴの幅
#define TITLE_SWORDG_HEIGHT	(250.0f)						// ロゴの高さ
//ファイティング-----------------------------------------------------------------------
#define TITLE_LOGO_POS_X_A	(-200)							// ロゴのX座標_A
#define TITLE_LOGO_POS_Y_A	(450.0f)						// ロゴのY座標_A
#define TITLE_LOGO_MOVE_MAX_A_X	(350.0f)					// ロゴのx座標の限界
#define TITLE_LOGO_MOVE_MAX_A_Y	(280.0f)					// ロゴのY座標の限界
#define TITLE_LOGO_WIDTH_A	(750.0f)						// ロゴの幅
#define TITLE_LOGO_HEIGHT_A	(400.0f)						// ロゴの高さ
//ポーカー-----------------------------------------------------------------------------
#define TITLE_LOGO_POS_X_B	(1480)							// ロゴのX座標_B
#define TITLE_LOGO_POS_Y_B	(350.0f)						// ロゴのY座標_B
#define TITLE_LOGO_MOVE_MAX_B_X	(890.0f)					// ロゴのx座標の限界
#define TITLE_LOGO_MOVE_MAX_B_Y	(380.0f)					// ロゴのY座標の限界
#define TITLE_LOGO_WIDTH_B	(600.0f)						// ロゴの幅
#define TITLE_LOGO_HEIGHT_B	(400.0f)						// ロゴの高さ
//勇者喰らい共通-----------------------------------------------------------------------
#define TITLE_LOGO_MOVE_X		(4.0f)						// ロゴの移動速度
#define TITLE_LOGO_MOVE_Y		(5.0f)						// ロゴの移動速度
//PressAnyBotton-----------------------------------------------------------------------
#define TITLE_ENTER_POS_X	(SCREEN_WIDTH / 2)				// エンターのX座標
#define TITLE_ENTER_POS_Y	(600.0f)						// エンターのY座標
#define TITLE_ENTER_WIDTH	(400.0f)						// エンターの幅
#define TITLE_ENTER_HEIGHT	(120.0f)							// エンターの高さ
#define TITLE_FLASH_ENTER	(60)							// エンターの点滅間隔
//雷-----------------------------------------------------------------------------------
#define TITLE_CLAW_MARK_POS_X	(SCREEN_WIDTH / 2)			// 爪痕のX座標
#define TITLE_CLAW_MARK_POS_Y	(350.0f)					// 爪痕のY座標
#define TITLE_CLAW_MARK_WIDTH	(400.0f)					// 爪痕の幅
#define TITLE_CLAW_MARK_HEIGHT	(300.0f)					// 爪痕の高さ
//トランプ-----------------------------------------------------------------------------
#define TITLE_TRUNP_POS_X	(1150)					// トランプのX座標
#define TITLE_TRUNP_POS_Y	(380.0f)				// トランプのY座標
#define TITLE_TRUNP_WIDTH	(200.0f)					// トランプの幅
#define TITLE_TRUNP_HEIGHT	(200.0f)					// トランプの高さ
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{// テクスチャの種類

	TITLETEX_BG_A = 0,			// ロゴ
	TITLETEX_SWORD,
	TITLETEX_LOGO_A,			// ロゴ
	TITLETEX_LOGO_B,			// ロゴ
	TITLETEX_ENTER,				// エンター
	TITLETEX_CLAW_MARK,			//　爪痕
	TITLETEX_TRUNP,				//　トランプ
	TITLETEX_MAX				// テクスチャの総数
} TITLETEX;

typedef enum
{// テクスチャの種類
	TITLETEX_ENTERCOL_000 = 0,	// ロゴ
	TITLETEX_ENTERCOL_001,		// ロゴ
	TITLETEX_ENTER_MAX			// テクスチャの総数
} TITLEENTERTEX;

typedef struct
{// タイトルの情報
	D3DXVECTOR3 pos;			// 位置
	float fWidth;				// 幅
	float fHeight;				// 高さ
	bool bFlash;				// 点滅するかどうか
	bool bDraw;					// 描画するかどうか
} Title;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureTitle[TITLETEX_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTitle = NULL;					// 頂点バッファへのポインタ
Title					g_aTitle[TITLETEX_MAX];					// タイトルの情報
TITLEENTERTEX			g_aTitleEntreCol;						//　エンターのカラー変更
int						g_nCntFpsTitle;							// 経過時間
int						g_nCntLogoStopTitle;					// 経過時間
int						g_nPlaySpecialVoice = 0;
bool					g_bPlaySpecialVoice;
//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitTitle(void)
{
	g_nPlaySpecialVoice = 0;
	g_bPlaySpecialVoice = false;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 情報の初期化
	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		g_aTitle[nCntTex].bFlash = false;
		switch (nCntTex)
		{
		case TITLETEX_BG_A://BG
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_BG_POS_X_A, TITLE_BG_POS_Y_A, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_BG_WIDTH_A;
			g_aTitle[nCntTex].fHeight = TITLE_BG_HEIGHT_A;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_SWORD://ソード
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_SWORD_POS_X, TITLE_SWORD_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_SWORD_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_SWORDG_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_LOGO_A://勇者
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_LOGO_POS_X_A, TITLE_LOGO_POS_Y_A, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_LOGO_WIDTH_A;
			g_aTitle[nCntTex].fHeight = TITLE_LOGO_HEIGHT_A;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_LOGO_B://喰らい
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_LOGO_POS_X_B, TITLE_LOGO_POS_Y_B, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_LOGO_WIDTH_B;
			g_aTitle[nCntTex].fHeight = TITLE_LOGO_HEIGHT_B;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_ENTER://PressAnyBoyyon
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_ENTER_POS_X, TITLE_ENTER_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_ENTER_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_ENTER_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_CLAW_MARK://爪痕
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_CLAW_MARK_POS_X, TITLE_CLAW_MARK_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_CLAW_MARK_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_CLAW_MARK_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_TRUNP://トランプ
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_TRUNP_POS_X, TITLE_TRUNP_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_TRUNP_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_TRUNP_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		}
	}
	//変数の初期化
	g_nCntFpsTitle = 0;
	g_nCntLogoStopTitle = 0;
	g_aTitleEntreCol = TITLETEX_ENTERCOL_000;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME1, &g_apTextureTitle[TITLETEX_LOGO_A]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME2, &g_apTextureTitle[TITLETEX_LOGO_B]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME3, &g_apTextureTitle[TITLETEX_ENTER]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME4, &g_apTextureTitle[TITLETEX_CLAW_MARK]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME5, &g_apTextureTitle[TITLETEX_BG_A]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME6, &g_apTextureTitle[TITLETEX_TRUNP]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME7, &g_apTextureTitle[TITLETEX_SWORD]);

	// 頂点情報の作成
	MakeVertexTitle(pDevice);
	// カメラの初期化処理
	InitCamera();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitTitle(void)
{
	// 各種オブジェクトの終了処理
	UninitCamera();

	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		if (g_apTextureTitle[nCntTex] != NULL)
		{
			g_apTextureTitle[nCntTex]->Release();
			g_apTextureTitle[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateTitle(void)
{
	// スペシャルボイス再生
#if 1
	if (g_bPlaySpecialVoice == false)
	{
		if (GetKeyboardTrigger(DIK_BACKSPACE) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START))
		{
			g_bPlaySpecialVoice = true;
			g_nPlaySpecialVoice = 60;
		}
	}
	if (g_bPlaySpecialVoice == true)
	{
 		g_nPlaySpecialVoice--;
		if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_BACK) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_BACK))
		{
			if (g_nPlaySpecialVoice >= 0)
			{
				PlaySound(SOUND_LABEL_SE_SPECIAL);
				g_bPlaySpecialVoice = false;
				g_nPlaySpecialVoice = 0;
			}
		}
	}
#endif
	VERTEX_2D *pVtx;
	FADE pFade = GetFade(); // フェードの取得
	int nPressChange = 0;		//	PRESS　A　と　PRESS　ENTER　の入れ替え

	if (g_aTitle[TITLETEX_LOGO_A].pos.x == TITLE_LOGO_MOVE_MAX_A_X  && g_aTitle[TITLETEX_LOGO_A].pos.y == TITLE_LOGO_MOVE_MAX_A_Y
		|| g_aTitle[TITLETEX_LOGO_B].pos.x == TITLE_LOGO_MOVE_MAX_B_X  && g_aTitle[TITLETEX_LOGO_B].pos.y == TITLE_LOGO_MOVE_MAX_B_Y)
	{// ロゴが定めた位置にある場合
		g_nCntFpsTitle++;

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A))
		{// 決定キー(ENTERキー)が押された場合
			if (pFade != FADE_OUT)
			{// フェードが何もしていない状態の場合
				g_aTitle[TITLETEX_ENTER].bFlash = true;
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetFade(MODE_SELECT);
			}

		}

		for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
		{
			if (g_aTitle[nCntTex].bFlash == true)
			{

				if (g_nCntFpsTitle % 2 == 0)
				{// 2F経過ごとに
					g_aTitle[nCntTex].bDraw = g_aTitle[nCntTex].bDraw ? false : true;
				}
			}
			else
			{
				if (nCntTex == TITLETEX_ENTER)
				{// エンターの場合
					if (g_nCntFpsTitle % TITLE_FLASH_ENTER == 0)
					{// 一定時間経過ごとに
						g_aTitle[nCntTex].bDraw = g_aTitle[nCntTex].bDraw ? false : true;
					}
				}
			}
		}
	}
	else
	{// ロゴが定めた位置にない場合
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
		{// 決定キー(ENTERキー)が押された場合
			g_aTitle[TITLETEX_LOGO_A].pos.x = TITLE_LOGO_MOVE_MAX_A_X;			// 勇者のPOSX：400
			g_aTitle[TITLETEX_LOGO_A].pos.y = TITLE_LOGO_MOVE_MAX_A_Y;			// 勇者のPOSY：220

			g_aTitle[TITLETEX_LOGO_B].pos.x = TITLE_LOGO_MOVE_MAX_B_X;			// 喰らいのPOSX:890
			g_aTitle[TITLETEX_LOGO_B].pos.y = TITLE_LOGO_MOVE_MAX_B_Y;			// 喰らいのPOSY:380

			g_aTitle[TITLETEX_ENTER].bDraw = true;								// PressAnyBottonを使用した状態にする
			g_aTitle[TITLETEX_TRUNP].bDraw = true;								//
			g_aTitle[TITLETEX_SWORD].bDraw = true;								//
																				//g_aTitle[TITLETEX_CLAW_MARK].bDraw = true;							//爪を使用した状態にする
			g_aTitleEntreCol = TITLETEX_ENTERCOL_001;							//爪痕を暗くする
		}

		if (g_aTitle[TITLETEX_LOGO_A].pos.x > TITLE_LOGO_MOVE_MAX_A_X && g_aTitle[TITLETEX_LOGO_B].pos.x < TITLE_LOGO_MOVE_MAX_B_X)
		{// ロゴが定めた位置を超えた場合（勇者Xが450以上になったら:喰らい840以下になったら）

			g_nCntLogoStopTitle++;

			g_aTitle[TITLETEX_LOGO_A].pos.x = TITLE_LOGO_MOVE_MAX_A_X;		//X座標を定位置に
			g_aTitle[TITLETEX_LOGO_B].pos.x = TITLE_LOGO_MOVE_MAX_B_X;		//X座標を定位置に
			if (g_nCntLogoStopTitle > 5)
			{//5Fを超えたら
			 //g_aTitle[TITLETEX_CLAW_MARK].bDraw = true;					//爪痕を使用する
			}
			if (g_nCntLogoStopTitle > 13)
			{//13Fを超えたら
				g_aTitle[TITLETEX_ENTER].bDraw = true;						//PressAnyBottonを使用した状態にする

				g_aTitle[TITLETEX_LOGO_A].pos.y = TITLE_LOGO_MOVE_MAX_A_Y;	//Y座標を定位置に
				g_aTitle[TITLETEX_LOGO_B].pos.y = TITLE_LOGO_MOVE_MAX_B_Y;	//Y座標を定位置に
				g_aTitleEntreCol = TITLETEX_ENTERCOL_001;
				g_aTitle[TITLETEX_TRUNP].bDraw = true;
				g_aTitle[TITLETEX_SWORD].bDraw = true;
			}

		}
		// 頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 8;
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_A].fWidth / 2, -g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_A].fWidth / 2, -g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_A].fWidth / 2, g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_A].fWidth / 2, g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx += 4;
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_B].fWidth / 2, -g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_B].fWidth / 2, -g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_B].fWidth / 2, g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_B].fWidth / 2, g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;

		switch (g_aTitleEntreCol)
		{
		case TITLETEX_ENTERCOL_000:
			g_aTitle[TITLETEX_LOGO_A].pos.x += TITLE_LOGO_MOVE_X;				//AのMOVE量
			g_aTitle[TITLETEX_LOGO_B].pos.x -= TITLE_LOGO_MOVE_X;				//BのMOVE量
																				// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 8;
			// 頂点カラーの設定
			pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();
			break;
		case TITLETEX_ENTERCOL_001:

			// 頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 8;
			// 頂点カラーの設定
			pVtx[12].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[13].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[14].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[15].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);

			// 頂点バッファをアンロックする
			g_pVtxBuffTitle->Unlock();
			break;
		}
		// 頂点バッファをアンロックする
		g_pVtxBuffTitle->Unlock();
	}
}


//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得する
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		if (g_aTitle[nCntTex].bDraw == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTitle[nCntTex]);

			// ポリゴンの描画// プリミティブの種類// 開始する頂点のインデックス// 描画するプリミティブの数
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTitle
		, NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++, pVtx += 4)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[nCntTex].fWidth / 2, -g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].fWidth / 2, -g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[nCntTex].fWidth / 2, g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].fWidth / 2, g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
	g_pVtxBuffTitle->Unlock();
}
