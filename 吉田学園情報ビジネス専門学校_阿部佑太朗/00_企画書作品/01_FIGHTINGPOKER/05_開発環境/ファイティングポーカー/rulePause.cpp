//=========================================================================================================================
//
// ポーズルールの処理 [rulePause.cpp]
// Author :  舘田 翼
//
//=========================================================================================================================
#include "rulePause.h"	// ポーズ
#include "input.h"		// キーボード
#include "game.h"		// ポーズ
#include"main.h"        // メイン
#include "rule.h"
#include "battle.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//******************************************************************************************************************************
// 構造体定義
//******************************************************************************************************************************
typedef struct
{// 情報
	D3DXVECTOR3 pos;			// 中心座標
	RULEPAUSETYPE nType;			// 種類
	float fWidth;				// 幅
	float fHeight;				// 高さ
} RulePauseInfo;

typedef struct
{// テクスチャ
	char *pFileName;
}RulePauseTexture;
//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define RULEPAUSESELECT_MAX (6)
// テクスチャ関連=====================================================================================
#define MAX_TEXTURE					(RULEPAUSETYPE_MAX)					// テクスチャの最大数
// セットルール関連======================================================================================
#define SETRULE_WIDTH			(SCREEN_WIDTH)					// セットルールの横幅
#define SETRULE_HEIGHT			(SCREEN_HEIGHT)					// セットルールの縦幅
#define SETRULE_POS_X			(SCREEN_WIDTH / 2)				// セットルールのX座標
#define SETRULE_POS_Y			(SCREEN_HEIGHT / 2)				// セットルールのY座標
// プレスエンター
#define SETRULE_PRESS_WIDTH		(200.0f)						// セットルール　プレスエンターの横幅
#define SETRULE_PRESS_HEIGHT	(100.0f)						// セットルール　プレスエンターの縦幅
#define SETRULE_PRESS_POS_X		(1000.0f)						// セットルール　プレスエンターの位置
#define SETRULE_PRESS_POS_Y		(700.0f)						// セットルール　プレスエンターの位置
//メニューのカラー========================================================================================
#define RULEPAUSE_NORMAL_COLOR			(1.0f)							// 通常の時のカラー
#define RULEPAUSE_DEC_COLOR				(0.004f)						// カラーを減らしていくときの値
#define RULEPAUSE_CHANGE_COLOR			(0.5f)							// 減らしたカラーがこの値を超えたら
//メニューの大きさー========================================================================================
#define RULEMENU_WIDTH (400.0f)
#define RULEMENU_HEIGHT (100.0f)


//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureRulePause[RULEPAUSETYPE_MAX] = {};// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRulePause = NULL;				// 頂点バッファへのポインタ
RULEPAUSEMENU g_aRulePause[RULEPAUSETYPE_MAX];					// ポスの情報
int g_nPressCount;
int g_nSelect;
bool g_bMenu;
float g_SelectColor;										// セレクトカラー

RulePauseInfo g_aRulePauseInfo[] =
{	//位置　→　種類　→　大きさ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),RULEPAUSETYPE_BG,SCREEN_WIDTH - 100,SCREEN_HEIGHT-100 },		// 背景
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 110.0f, 0.0f),RULEPAUSETYPE_FLOW,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// ゲームの流れ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 210.0f, 0.0f),RULEPAUSETYPE_KEYBORD,RULEMENU_WIDTH,RULEMENU_HEIGHT },					// キーボード操作
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 310.0f, 0.0f), RULEPAUSETYPE_CONTROLLER,RULEMENU_WIDTH,RULEMENU_HEIGHT },				// コントローラー操作
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 410.0f, 0.0f), RULEPAUSETYPE_ROLE,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// 役の説明
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 510.0f, 0.0f), RULEPAUSETYPE_CHARA,RULEMENU_WIDTH,RULEMENU_HEIGHT },					// キャラ
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 610.0f, 0.0f), RULEPAUSETYPE_BACK,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// 戻る
};

RulePauseTexture g_aRulebookTex[RULEPAUSETYPE_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },					// 読み込むテクスチャ
	{ "data/TEXTURE/RULEBOOK/GameFlowContents.png" },		// 読み込むテクスチャ1
	{ "data/TEXTURE/RULEBOOK/OperateContentsKEY.png" },		// 読み込むテクスチャ2
	{ "data/TEXTURE/RULEBOOK/OperateContentsCON.png" },		// 読み込むテクスチャ2
	{ "data/TEXTURE/RULEBOOK/CardRoleContents.png" },		// 読み込むテクスチャ2
	{ "data/TEXTURE/RULEBOOK/CharacterRulesContents.png" },	// 読み込むテクスチャ2
	{ "data/TEXTURE/RULEBOOK/Backselect.png" },				// 読み込むテクスチャ2	戻る
};
//=========================================================================================================================
// ポーズ初期化処理
//=========================================================================================================================
void InitRulePause(void)
{
	g_nSelect = 0;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ルールの初期化処理
	InitRule();

	// 頂点情報へのポインタ
	VERTEX_2D*pVtx;

	for (int nTex = 0; nTex < RULEPAUSETYPE_MAX; nTex++)
	{// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_aRulebookTex[nTex].pFileName,
			&g_apTextureRulePause[nTex]);
	}

	//情報の初期化
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++)
	{
		g_aRulePause[nCntPause].SelectNum = 0;
		g_aRulePause[nCntPause].SelectColor = 1.0f;
		g_aRulePause[nCntPause].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRulePause[nCntPause].bMenu = false;
		g_aRulePause[nCntPause].bRule = false;
		g_nPressCount = 0;
	}


	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRulePause,
		NULL
	);



	//頂点バッファをロック
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[1].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[2].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[3].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;

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
	g_pVtxBuffRulePause->Unlock();

	// 情報のセット
	for (int nCntPause = 0; nCntPause < sizeof g_aRulePauseInfo / sizeof(RulePauseInfo); nCntPause++)
	{
		SetRulePause(g_aRulePauseInfo[nCntPause].pos, g_aRulePauseInfo[nCntPause].nType, g_aRulePauseInfo[nCntPause].fWidth, g_aRulePauseInfo[nCntPause].fHeight);
	}
}

//=========================================================================================================================
// ポーズ終了処理
//=========================================================================================================================
void UninitRulePause(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
	 //テクスチャーの破棄
		if (g_apTextureRulePause[nCount] != NULL)
		{
			g_apTextureRulePause[nCount]->Release();
			g_apTextureRulePause[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRulePause != NULL)
	{
		g_pVtxBuffRulePause->Release();
		g_pVtxBuffRulePause = NULL;
	}
	// ルールの初期化
	UninitRule();
}

//=========================================================================================================================
// ポーズ更新処理
//=========================================================================================================================
void UpdateRulePause(void)
{
	// ルールの更新処理
	UpdateRule();

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	RULE *pRule;
	pRule = GetRule();


	// 頂点バッファをロック
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	if (g_bMenu == false)
	{
		if (GetKeyboardTrigger(DIK_W) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P,STICK_UP) == true)
		{//矢印キーの上を押したとき
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
			SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		 // 頂点カラー設定
			pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			g_nSelect = (g_nSelect + RULEPAUSESELECT_MAX - 1) % RULEPAUSESELECT_MAX;
			g_SelectColor = RULEPAUSE_NORMAL_COLOR;
		}

		if (GetKeyboardTrigger(DIK_S) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_DOWN) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_DOWN) == true)
		{//矢印キーの下を押したとき
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
			SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		 // 頂点カラー設定
			pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			g_nSelect = (g_nSelect + 1) % RULEPAUSESELECT_MAX;
			g_SelectColor = RULEPAUSE_NORMAL_COLOR;
		}
		// 長押しの処理
		if (GetKeyboardPress(DIK_S) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)
		{
			g_nPressCount++;
			if (g_nPressCount > 30)
			{
				if (g_nPressCount % 5 == 0)
				{
					pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

					g_nSelect = (g_nSelect + 1) % RULEPAUSESELECT_MAX;
				}
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_UP) == true || GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_UP) == true)
		{
			g_nPressCount++;
			if (g_nPressCount > 30)
			{
				if (g_nPressCount % 5 == 0)
				{
					pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
					g_nSelect = (g_nSelect + (RULEPAUSESELECT_MAX - 1)) % RULEPAUSESELECT_MAX;
				}
			}
		}

		// ポーズカウンターの初期化
		if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
		{
			g_nPressCount = 0;
		}
		else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
		{
			g_nPressCount = 0;
		}
		//点滅処理
		//選択しているカラーの値を減らしていく
		g_SelectColor -= RULEPAUSE_DEC_COLOR;

		if (g_SelectColor < RULEPAUSE_CHANGE_COLOR)
		{//選択しているカラーが0.5を切ったらカラーの値が増えてく
			g_SelectColor = RULEPAUSE_NORMAL_COLOR;
		}

		// 頂点カラー設定
		pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
	}

	// 頂点バッファをロック
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		g_bMenu = g_bMenu ? false : true;

		if (g_bMenu == true)
		{
			if (g_nSelect == RULE_FLOW)
			{// 1番目が選ばれたら
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_FLOW);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_KEYBORD)
			{// 2番目が選ばれたら
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_KEYBORD);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_CONTROLLER)
			{// 3番目が選ばれたら
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CONTROLLER);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_ROLE)
			{// 4番目が選ばれたら
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_ROLE);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_CHARA)
			{
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CHARA);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else
			{// 4番目が選ばれたら
				PlaySound(SOUND_LABEL_SE_CANCEL);
				SetPauseState(true);		// ポーズ使用
				SetRulePauseState(false);	// ルールポーズ不使用
				g_bMenu = false;
				g_nSelect = 0;
			}
		}
		else
		{
			g_bMenu = false;
			for (int nCount = 0; nCount < RULE_MAX; nCount++)
			{// ルールを全て使用していない状態にする
				pRule[nCount].bUse = false;
			}
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffRulePause->Unlock();
}

//=========================================================================================================================
// ポーズ描画処理
//=========================================================================================================================
void DrawRulePause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスポインタ

	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++)
	{
		if (g_aRulePause[nCntPause].bUse == true)
		{
			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource
			(0, g_pVtxBuffRulePause, 0, sizeof(VERTEX_2D));

			//頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureRulePause[g_aRulePause[nCntPause].nType]);

			//ポーズの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
		}
	}

	// ルールの描画処理
	DrawRule();
}
//==============================================================================================================================
// ポーズの設定
//==============================================================================================================================
void SetRulePause(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;

	// 頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		if (g_aRulePause[nCntPause].bUse == false)
		{// 背景が使用されていない
			g_aRulePause[nCntPause].pos = pos;
			g_aRulePause[nCntPause].nType = nType;
			g_aRulePause[nCntPause].fWidth = fWidth;
			g_aRulePause[nCntPause].fHeight = fHeight;

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[1].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[2].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[3].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;

			g_aRulePause[nCntPause].bUse = true;	// 使用している状態にする
			break;
		}
	}
	g_pVtxBuffRulePause->Unlock();
}

//=========================================================================================================================
// ポーズ描画処理
//=========================================================================================================================
bool GetbMenu(void)
{
	return g_aRulePause[0].bRule;
}
