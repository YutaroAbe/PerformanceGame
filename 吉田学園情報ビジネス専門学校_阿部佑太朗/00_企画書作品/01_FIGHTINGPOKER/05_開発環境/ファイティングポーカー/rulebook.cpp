////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ポーズの処理 [pause.cpp]
// Author : Ryota Kinoshita
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "rulebook.h"
#include "input.h"
#include "rule.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef struct
{// 情報
	D3DXVECTOR3 pos;			// 中心座標
	RULEBOOKTYPE nType;			// 種類
	float fWidth;				// 幅
	float fHeight;				// 高さ
} RulebookInfo;

typedef struct
{// テクスチャ
	char *pFileName;
}RulebookTexture;

//******************************************************************************************************************************
// マクロ定義
//******************************************************************************************************************************
#define RULEBUUKSELECT_MAX	(6)
// セットルール関連======================================================================================
#define SETRULE_WIDTH			(SCREEN_WIDTH)					// セットルールの横幅
#define SETRULE_HEIGHT			(SCREEN_HEIGHT)					// セットルールの縦幅
#define SETRULE_POS_X			(SCREEN_WIDTH / 2)				// セットルールのX座標
#define SETRULE_POS_Y			(SCREEN_HEIGHT / 2)				// セットルールのY座標
// プレスエンター
#define SETRULE_PRESS_WIDTH		(300.0f)						// セットルール　プレスエンターの横幅
#define SETRULE_PRESS_HEIGHT	(100.0f)						// セットルール　プレスエンターの縦幅
#define SETRULE_PRESS_POS_X		(150.0f)						// セットルール　プレスエンターの縦幅
#define SETRULE_PRESS_POS_Y		(50.0f)						// セットルール　プレスエンターの縦幅

//メニューのカラー========================================================================================
#define MENU_NORMAL_COLOR			(1.0f)							// 通常の時のカラー
#define MENU_DEC_COLOR				(0.004f)						// カラーを減らしていくときの値
#define MENU_CHANGE_COLOR			(0.5f)							// 減らしたカラーがこの値を超えたら
//メニューの大きさー========================================================================================
#define RULEBOOK_WIDTH (400.0f)
#define RULEBOOK_HEIGHT (100.0f)

//******************************************************************************************************************************
// グローバル変数
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureRulebook[PAUSETYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRulebook = NULL;			// 頂点バッファへのポインタ
RULEBOOK g_aRulebook[PAUSETYPE_MAX];						// ルールブックのグローバル変数
int g_nSelectBook;												// セレクト番号
int g_nPressCounter;										// セレクトカウンタ
float g_SelectColorBook;										// セレクトカラー
bool g_bMenuBook;												// 使用されているかどうか

RulebookInfo g_aRulebookInfo[] =
{	//位置　→　種類　→　大きさ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),BOOKTYPE_BG,SCREEN_WIDTH,SCREEN_HEIGHT },						// 背景
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 100.0f, 0.0f),BOOKTYPE_FLOW,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },						// ゲームの流れ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 200.0f, 0.0f),BOOKTYPE_KEYBORD,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// キーボード操作
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 300.0f, 0.0f), BOOKTYPE_CONTROLLER,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },				// コントローラー操作
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 400.0f, 0.0f), BOOKTYPE_ROLE,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// 役の説明
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 500.0f, 0.0f), BOOKTYPE_CHARA,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// キャラ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 600.0f, 0.0f), BOOKTYPE_BACK,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// 戻る
};
RulebookTexture g_aRulebookTex[PAUSETYPE_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },					// 読み込むテクスチャ
	{ "data/TEXTURE/RULEBOOK/GameFlowContents.png" },		// 読み込むテクスチャ1	ゲーム流れ
	{ "data/TEXTURE/RULEBOOK/OperateContentsKEY.png" },		// 読み込むテクスチャ2	キーボード
	{ "data/TEXTURE/RULEBOOK/OperateContentsCON.png" },		// 読み込むテクスチャ2	コントローラー操作
	{ "data/TEXTURE/RULEBOOK/CardRoleContents.png" },		// 読み込むテクスチャ2	役
	{ "data/TEXTURE/RULEBOOK/CharacterRulesContents.png" },	// 読み込むテクスチャ2	キャラ
	{ "data/TEXTURE/RULEBOOK/Backselect.png" },				// 読み込むテクスチャ2	戻る
};

//==============================================================================================================================
// 初期化処理（ポリゴン）
//==============================================================================================================================
void InitRulebook(void)
{
	// ルールの初期化処理
	InitRule();

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報へのポインタ
	VERTEX_2D*pVtx;

	for (int nTex = 0; nTex < PAUSETYPE_MAX; nTex++)
	{// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_aRulebookTex[nTex].pFileName,
			&g_apTextureRulebook[nTex]);
	}

	// 背景の情報の初期化
	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++)
	{
		g_aRulebook[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 座標
		g_aRulebook[nCntPause].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_aRulebook[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 背景の移動量
		g_aRulebook[nCntPause].nType = 0;								// タイプ
		g_aRulebook[nCntPause].nCounterAnim = 0;						// カウンター
		g_aRulebook[nCntPause].nPatternAnim = 0;						// パターンNo
		g_aRulebook[nCntPause].fWidth = 0;								// 幅
		g_aRulebook[nCntPause].fHeight = 0;								// 高さ
		g_aRulebook[nCntPause].bUse = false;							// 使用されているかどうか
	}
	g_nSelectBook = 0;
	g_nPressCounter = 0;
	g_SelectColorBook = 1.0f;
	g_bMenuBook = false;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRulebook,
		NULL);

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[1].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[2].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[3].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// rhwの設定
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].rhw = 1.0f;
		}

		if (nCntPause == 0)
		{
			//頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// 一番上の色以外は半分にする
		 //頂点カラー設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffRulebook->Unlock();

	// 情報のセット
	for (int nCntPause = 0; nCntPause < sizeof g_aRulebookInfo / sizeof(RulebookInfo); nCntPause++)
	{
		SetRulebook(g_aRulebookInfo[nCntPause].pos, g_aRulebookInfo[nCntPause].nType, g_aRulebookInfo[nCntPause].fWidth, g_aRulebookInfo[nCntPause].fHeight);
	}
}

//==============================================================================================================================
// 終了処理（ポリゴン）
//==============================================================================================================================
void UninitRulebook(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PAUSETYPE_MAX; nCntTex++)
	{
		if (g_apTextureRulebook[nCntTex] != NULL)
		{
			g_apTextureRulebook[nCntTex]->Release();
			g_apTextureRulebook[nCntTex] = NULL;
		}
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffRulebook != NULL)
	{
		g_pVtxBuffRulebook->Release();
		g_pVtxBuffRulebook = NULL;
	}

	// ルールの初期化
	UninitRule();
}

//==============================================================================================================================
// 更新処理（ポリゴン）
//==============================================================================================================================
void UpdateRulebook(void)
{
	VERTEX_2D*pVtx;

	FADE pFade = GetFade(); // フェードの取得

							// ルールのポインタの取得
	RULE *pRule;
	pRule = GetRule();

	// ルールの更新処理
	UpdateRule();

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);

	if (g_bMenuBook == false)
	{
		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP) == true)

		{//矢印キーの上を押したとき
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		 // 頂点カラー設定
			pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			g_nSelectBook = (g_nSelectBook + RULEBUUKSELECT_MAX - 1) % RULEBUUKSELECT_MAX;
			g_SelectColorBook = MENU_NORMAL_COLOR;
		}

		if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_DOWN) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_DOWN) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_DOWN) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)

		{//矢印キーの下を押したとき
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		 // 頂点カラー設定
			pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			g_nSelectBook = (g_nSelectBook + 1) % RULEBUUKSELECT_MAX;
			g_SelectColorBook = MENU_NORMAL_COLOR;
		}
		// 長押しの処理
		if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
		{
			g_nPressCounter++;
			if (g_nPressCounter > 30)
			{
				if (g_nPressCounter % 5 == 0)
				{
					pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					g_nSelectBook = (g_nSelectBook + 1) % RULEBUUKSELECT_MAX;
				}
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
		{
			g_nPressCounter++;
			if (g_nPressCounter > 30)
			{
				if (g_nPressCounter % 5 == 0)
				{
					pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					g_nSelectBook = (g_nSelectBook + (RULEBUUKSELECT_MAX  - 1)) % RULEBUUKSELECT_MAX;
				}
			}
		}

		// ポーズカウンターの初期化
		if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
		{
			g_nPressCounter = 0;
		}
		else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
		{
			g_nPressCounter = 0;
		}
		//点滅処理
		//選択しているカラーの値を減らしていく
		g_SelectColorBook -= MENU_DEC_COLOR;

		if (g_SelectColorBook < MENU_CHANGE_COLOR)
		{//選択しているカラーが0.5を切ったらカラーの値が増えてく
			g_SelectColorBook = MENU_NORMAL_COLOR;
		}

		// 頂点カラー設定
		pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{// エンターを押したときに true falseを切り替える
		g_bMenuBook = g_bMenuBook ? false : true;

		if (g_bMenuBook == true)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			if (g_nSelectBook == RULE_FLOW)
			{// 1番目が選ばれたら	ゲームの流れ
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_FLOW);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_KEYBORD)
			{// 2番目が選ばれたら	キーボード説明
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_KEYBORD);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);

			}
			else if (g_nSelectBook == RULE_CONTROLLER)
			{// 3番目が選ばれたら	コントローラー説明
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CONTROLLER);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_ROLE)
			{// 4番目が選ばれたら	役の説明
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_ROLE);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_CHARA)
			{// 4番目が選ばれたら	キャラ説明
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CHARA);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == 5)
			{
				if (pFade != FADE_OUT)
				{// フェードが何もしていない状態の場合
					SetFade(MODE_SELECT);
				}
			}
		}
		else
		{//使用していない状態にする
			g_bMenuBook = false;
			for (int nCount = 0; nCount < RULE_MAX; nCount++)
			{// ルールを全て使用していない状態にする
				pRule[nCount].bUse = false;
			}
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffRulebook->Unlock();
}
//==============================================================================================================================
// 描画処理（ポリゴン）
//==============================================================================================================================
void DrawRulebook(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
								// デバイスを取得する
	pDevice = GetDevice();

	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++)
	{
		if (g_aRulebook[nCntPause].bUse == true)
		{
			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffRulebook, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureRulebook[g_aRulebook[nCntPause].nType]);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntPause * 4,
				2);
		}
	}
	// ルールの描画処理
	DrawRule();
}
//==============================================================================================================================
// ポーズの設定
//==============================================================================================================================
void SetRulebook(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		if (g_aRulebook[nCntPause].bUse == false)
		{// 背景が使用されていない
			g_aRulebook[nCntPause].pos = pos;
			g_aRulebook[nCntPause].nType = nType;
			g_aRulebook[nCntPause].fWidth = fWidth;
			g_aRulebook[nCntPause].fHeight = fHeight;

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[1].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[2].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[3].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;

			g_aRulebook[nCntPause].bUse = true;	// 使用している状態にする
			break;
		}
	}
	g_pVtxBuffRulebook->Unlock();
}
