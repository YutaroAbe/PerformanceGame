//=============================================================================
//
// UI処理 [UIe.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "ui.h"				// タイトルフレーム
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力
#include "bulletNumber.h"		// ライフの数値
#include "game.h"			// ゲーム
#include "pause.h"			//	Pause
#include "player.h"			//	プレイヤー
#include "bullet3D.h"		//	弾3D
#include "fade.h"			//	フェイド
#include "sound.h"			//	サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//	#	タイトル
#define	TEXTURE_TITLE000		"data\\TEXTURE\\UI\\TITLE\\title000.png"		// タイトルロゴ000テクスチャ
#define	TEXTURE_TITLE001		"data\\TEXTURE\\UI\\TITLE\\title001.png"		// タイトルロゴ001テクスチャ
#define	TEXTURE_TITLE002		"data\\TEXTURE\\UI\\TITLE\\title002.png"		// タイトルロゴ002テクスチャ
//	#	ゲーム
#define	TEXTURE_GAME000			"data\\TEXTURE\\UI\\GAME\\hpbar.png"			//  HPバーテクスチャ
#define	TEXTURE_GAME001			"data\\TEXTURE\\UI\\GAME\\caricon.png"			//  キャラアイコンbgテクスチャ
#define	TEXTURE_GAME002			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  HPゲージテクスチャ
#define	TEXTURE_GAME003			"data\\TEXTURE\\UI\\GAME\\lifebg.png"			//  HP数値BGテクスチャ
#define	TEXTURE_GAME004			"data\\TEXTURE\\UI\\GAME\\boombg.png"			//  弾のUBG
#define	TEXTURE_GAME005			"data\\TEXTURE\\UI\\GAME\\boom.png"				//  手榴弾の画像
#define	TEXTURE_GAME006			"data\\TEXTURE\\UI\\GAME\\suterusu.png"			//  Stealthの草の画像
#define	TEXTURE_GAME007			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  HPゲージテクスチャ
#define	TEXTURE_GAME008			"data\\TEXTURE\\UI\\GAME\\StealthUI.png"		//  ステルス状態の時の演出

#define	TEXTURE_GAME009			"data\\TEXTURE\\UI\\GAME\\butu.png"			//  ダッシュの靴の画像
#define	TEXTURE_GAME010			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  ダッシュゲージテクスチャ
#define	TEXTURE_GAME011			"data\\TEXTURE\\UI\\GAME\\StealthUI.png"		//  ダッシュ状態の時の演出

//	#	セレクトモード
#define	TEXTURE_SELECTMODEBG			"data\\TEXTURE\\UI\\select\\selectbg.png"				//  セレクトの背景
#define	TEXTURE_SELMODEGAMEMODE			"data\\TEXTURE\\UI\\select\\gamemode.png"				//  セレクトのゲームモード
#define	TEXTURE_SELMODEGAMEMODETXST		"data\\TEXTURE\\UI\\select\\gamemodetxst.png"			//  セレクトのゲームモード文字
#define	TEXTURE_SELMODECREDIT			"data\\TEXTURE\\UI\\select\\creditmode.png"				//  セレクトのクレジット
#define	TEXTURE_SELMODECREDITTXST		"data\\TEXTURE\\UI\\select\\creditmodetxst.png"			//  セレクトのクレジット文字
#define	TEXTURE_SELMODETITLERETURE		"data\\TEXTURE\\UI\\select\\titlereturn.png"			//  セレクトのタイトル戻る
#define	TEXTURE_SELMODETITLERETURETXST	"data\\TEXTURE\\UI\\select\\titlereturntxst.png"	//  セレクトのタイトル戻る文字
#define	TEXTURE_SELMODEDES00			"data\\TEXTURE\\UI\\select\\Description00.png"		//  セレクトの説明文字00
#define	TEXTURE_SELMODEDES01			"data\\TEXTURE\\UI\\select\\Description01.png"		//  セレクトの説明文字01
#define	TEXTURE_SELMODEDES02			"data\\TEXTURE\\UI\\select\\Description02.png"		//  セレクトの説明文字02
//	#	ポーズ
#define	TEXTURE_PAUSEBG			"data\\TEXTURE\\UI\\Pause\\pausebg.png"			//  ポーズの背景
#define	TEXTURE_PAUSESEL000		"data\\TEXTURE\\UI\\Pause\\pausesel000.png"		//  ポーズの背景
#define	TEXTURE_PAUSESEL001		"data\\TEXTURE\\UI\\Pause\\pausesel001.png"		//  ポーズの背景
#define	TEXTURE_PAUSESEL002		"data\\TEXTURE\\UI\\Pause\\pausesel002.png"		//  ポーズの背景
//	#	チュートリアル
#define	TEXTURE_TUTO_BG			"data\\TEXTURE\\UI\\TUTO\\tutobg.png"			//  チュートリアルの背景
#define	TEXTURE_TUTO_000		"data\\TEXTURE\\UI\\TUTO\\tuto000.png"			//  チュートリアルの説明文1
#define	TEXTURE_TUTO_001		"data\\TEXTURE\\UI\\TUTO\\tuto001.png"			//  チュートリアルの説明文2
#define	TEXTURE_TUTO_002		"data\\TEXTURE\\UI\\TUTO\\tuto002.png"			//  チュートリアルの説明文3
#define	TEXTURE_TUTO_003		"data\\TEXTURE\\UI\\TUTO\\tuto003.png"			//  チュートリアルの説明文4
#define	TEXTURE_TUTO_004		"data\\TEXTURE\\UI\\TUTO\\tuto004.png"			//  チュートリアルの説明文5
#define	TEXTURE_TUTO_005		"data\\TEXTURE\\UI\\TUTO\\tuto005.png"			//  チュートリアルの説明文6
#define	TEXTURE_TUTO_006		"data\\TEXTURE\\UI\\TUTO\\tuto006.png"			//  チュートリアルの説明文7
#define	TEXTURE_TUTO_007		"data\\TEXTURE\\UI\\TUTO\\tutoope.png"			//  チュートリアルの操作方法
#define	TEXTURE_TUTO_008		"data\\TEXTURE\\UI\\TUTO\\tutosankaku.png"		//  チュートリアルの操作方法右▽
#define	TEXTURE_TUTO_009		"data\\TEXTURE\\UI\\TUTO\\tutooperation.png"	//  チュートリアルの操作方法
#define	TEXTURE_TUTO_010		"data\\TEXTURE\\UI\\TUTO\\tutoneed.png"			//  チュートリアルの操作方法ありなし
#define	TEXTURE_BOTTON_ENTER	"data\\TEXTURE\\UI\\BUTTON\\PRESSENTER.png"		//  HPゲージテクスチャ
//	ゲームオーバー
#define TEXTURE_OVER_000	"data\\TEXTURE\\UI\\GAMEOVER\\redbg.png"			//  ゲームオーバー背景
#define TEXTURE_OVER_001	"data\\TEXTURE\\UI\\GAMEOVER\\oversel000.png"		//  ゲームオーバー選択[1]
#define TEXTURE_OVER_002	"data\\TEXTURE\\UI\\GAMEOVER\\oversel001.png"		//  ゲームオーバー背景[2]

// リザルト[ ゲームオーバー ]
#define TEXTURE_RESULT_000	"data\\TEXTURE\\UI\\RESULT\\GAMEOVER\\missionfailed.png"	//  missionfilede

// リザルト[ ゲームクリア]
#define TEXTURE_RESULT_001	"data\\TEXTURE\\UI\\RESULT\\GAMECLEAR\\missionclear.png"		//  missionfilede

//	ゲームクリア時の文字
#define	TEXTURE_CLEARTXST_000	"data\\TEXTURE\\UI\\CLEAR\\clear000.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_001	"data\\TEXTURE\\UI\\CLEAR\\clear001.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_002	"data\\TEXTURE\\UI\\CLEAR\\clear002.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_003	"data\\TEXTURE\\UI\\CLEAR\\clear003.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_004	"data\\TEXTURE\\UI\\CLEAR\\clear004.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_005	"data\\TEXTURE\\UI\\CLEAR\\clear005.png"		// ゲームクリア時の文字説明文1
#define	TEXTURE_CLEARTXST_006	"data\\TEXTURE\\UI\\CLEAR\\clear006.png"		// ゲームクリア時の文字説明文1

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CUI::m_pTexture[UI_TEXMAX] = {};			// テクスチャ情報へのポインタ
CManager::MODE		CUI::m_mode = CManager::MODE_NONE;			//	ゲームのモード
int					CUI::m_nNumSelectMode = 0;					//	セレクト番号
bool				CUI::m_bTutoEnd = false;					//	チュートリアルが終わったかどうか
int					CUI::m_nNextTxst = 0;						//	チュートリアルの表記設定

//=============================================================================
// コンストラクタ
//=============================================================================
CUI::CUI() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_UI)
{
	m_nType = 0;								//	種類
	m_nCounterAnim = 0;							//	アニメーション用カウンター
	m_nPatternAnim = 0;							//	アニメーションパターン
	m_sizeOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	初期の大きさの位置
	m_bFlash = false;								//	点滅しない
	m_bPressButton = false;						//	ボタン押したかどうかか
	m_fFrameValue = 0;							//	セレクト番号の大きさの値
	m_nNumSelectMode = 0;						//	セレクトの番号
	//m_nNextTxst = 0;							//	チュートリアルの表記設定
	m_nCutTuto = 0;								//	チュートリアルのカウンター
	m_bSize = false;							//	大きさの変化
	m_nPlayerLife = 0;							//	プレイヤーの体力
	m_nPlayerLifeOld = 0;						//	プレイヤーの体力の保存
	m_nPlayerLifeMax = 0;						//	プレイヤーの体力の最大
	m_Bullet3D = NULL;							//	弾3D
	m_nStealthLifeMax = 0;						//	プレイヤーのステルスの寿命最大値
	m_nStealthCut = 0;							//	プレイヤーのステルスの
	m_nPlayerSquat = false;						//	プレイヤーのステルス状態
	m_nStealthLife = 0;							//	プレイヤーのステルスの寿命
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	初期の位置
	m_bTutoOperation = false;					//	チュートリアルの操作説明描画するかしないか
	m_bColChange = false;						//	色を変えるかどうか
	m_nDashLifeMax = 0;							//	プレイヤーのダッシュの寿命最大
	m_nDashLife = 0;							//	プレイヤーのダッシュの寿命最大
	m_nPlayerDash = false;						//	ダッシュしているかどうか
	m_nDashCut = 0;								//	プレイヤーのダッシュのカウンター
}

//=============================================================================
// デストラクタ
//=============================================================================
CUI::~CUI()
{

}
//=============================================================================
// ロード処理
//=============================================================================
HRESULT CUI::Load(CManager::MODE mode)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成

	//	ゲームの設定
	m_mode = mode;
	switch (m_mode)
	{
	case CManager::MODE_TITLE://	タイトル
		 //	タイトルロゴ001
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE000, &m_pTexture[0]);		//	タイトルロゴ000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE001, &m_pTexture[6]);		//	タイトルロゴ001
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE002, &m_pTexture[7]);		//	タイトルロゴ002
		//	PRESS BOTTAN
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);	//	PRESSENTER
		break;
	case CManager::MODE_SELECTMODE://	セレクト
								   //	セレクトモード
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELECTMODEBG, &m_pTexture[12]);				//	背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEGAMEMODE, &m_pTexture[13]);			//	ゲームモード
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEGAMEMODETXST, &m_pTexture[14]);		//	ゲームモード文字
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODECREDIT, &m_pTexture[15]);				//	クレジット
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODECREDITTXST, &m_pTexture[16]);			//	クレジット文字
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODETITLERETURE, &m_pTexture[17]);		//	タイトルへ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODETITLERETURETXST, &m_pTexture[18]);	//	タイトルへ文字
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES00, &m_pTexture[19]);				//	下の文字表記
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES01, &m_pTexture[20]);				//	下の文字表記
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES02, &m_pTexture[21]);				//	下の文字表記
																								//	PRESS BOTTAN
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);	//	PRESSENTER
		break;
	case CManager::MODE_GAMETUTO:
		//	チュートリアル
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_BG, &m_pTexture[22]);				//	チュートリアル背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_000, &m_pTexture[23]);				//	チュートリアル説明1
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_001, &m_pTexture[24]);				//	チュートリアル説明2
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_002, &m_pTexture[25]);				//	チュートリアル説明3
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_003, &m_pTexture[26]);				//	チュートリアル説明4
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_004, &m_pTexture[27]);				//	チュートリアル説明5
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_005, &m_pTexture[28]);				//	チュートリアル説明6
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_006, &m_pTexture[29]);				//	チュートリアル説明7
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_007, &m_pTexture[30]);				//	チュートリアル操作方法
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_008, &m_pTexture[31]);				//	チュートリアル右▽
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_009, &m_pTexture[36]);				//	チュートリアル操作方法
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_010, &m_pTexture[37]);				//	チュートリアル操作方ありなし
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HPバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP→アイコン
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	弾の背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H手榴弾の画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	ステルスの画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	ステルスゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	ステルスUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	ダッシュの画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	ステルスUI
		//	ポーズ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause選択[ 1番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause背景[ 2番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause背景[ 3番 ]

		//	ゲームオーバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	ゲームオーバーの背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	ゲームオーバー選択[やり直す]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	ゲームオーバーの背景[あきらめる]


		break;
	case CManager::MODE_GAMESTAGE000://	ステージ1
		//	ゲーム
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HPバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP→アイコン
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	弾の背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H手榴弾の画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	H手榴弾の画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	ステルスUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	ダッシュの画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	ステルスUI

		//	ポーズ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause選択[ 1番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause背景[ 2番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause背景[ 3番 ]

		//	ゲームオーバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	ゲームオーバーの背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	ゲームオーバー選択[やり直す]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	ゲームオーバーの背景[あきらめる]

	case CManager::MODE_GAMESTAGE002:
		//	ゲーム
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HPバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP→アイコン
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	弾の背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H手榴弾の画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	H手榴弾の画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	ステルスUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	ダッシュの画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HPゲージ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	ステルスUI
		//	ポーズ
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause選択[ 1番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause背景[ 2番 ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause背景[ 3番 ]
		//	ゲームオーバー
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	ゲームオーバーの背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	ゲームオーバー選択[やり直す]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	ゲームオーバーの背景[あきらめる]
		//	ゲームクリア時の文字出し
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_BG, &m_pTexture[22]);				//	 文字の背景
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_000, &m_pTexture[43]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_001, &m_pTexture[44]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_002, &m_pTexture[45]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_003, &m_pTexture[46]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_004, &m_pTexture[47]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_005, &m_pTexture[48]);			//	クリア時の文字000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_006, &m_pTexture[49]);			//	クリア時の文字000

		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_007, &m_pTexture[30]);				//	チュートリアル操作方法
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_008, &m_pTexture[31]);				//	チュートリアル右▽
		break;
	case CManager::MODE_OVER:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	黒い背景画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);			//	PRESSENTER
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_000, &m_pTexture[42]);			//	missionfilede
		break;
	case CManager::MODE_CLEAR:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	黒い背景画像
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);			//	PRESSENTER　
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_001, &m_pTexture[50]);			//	missionfilede
		break;
	}

	return S_OK;
}

//=============================================================================
// アンロード処理
//=============================================================================
void CUI::Unload(void)
{
	for (int nCntTex = 0; nCntTex < UI_TEXMAX; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{// NULLの場合
		 // テクスチャの生成
			m_pTexture[nCntTex]->Release();		// 解放
			m_pTexture[nCntTex] = NULL;			// NULLへ
		}
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col ,D3DXVECTOR2 uv, int nType)
{
	CUI *pUI = {};				// Uiポインタ

	if (pUI == NULL)
	{// NULLの場合// メモリ確保
		pUI = new CUI;
		if (pUI != NULL)
		{// NULL以外の場合
			pUI->Init(pos, size, col, uv, nType);			// 初期化処理
		}
	}
	return pUI;
}

//=============================================================================
// UI作成するモード
//=============================================================================
void CUI::CreateMode(CManager::MODE mode)
{
	m_mode = mode;	//モードの同期
	switch (mode)
	{
	case CManager::MODE_TITLE://	タイトル	-------------------------------------------------------------------------------------------------------------------------------------
		//	タイトルロゴ000
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(350.0f, 120.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 0);
		//	タイトルロゴ001
		CUI::Create
		(D3DXVECTOR3(200, 300, 0.0f), D3DXVECTOR3(250.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 6);
		//	タイトルロゴ002
		CUI::Create
		(D3DXVECTOR3(1100, 460, 0.0f), D3DXVECTOR3(250.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 7);

		//	PRESS ENTER
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXVECTOR3(200.0f,50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);

		break;
	case  CManager::MODE_SELECTMODE://  セレクトモード	-------------------------------------------------------------------------------------------------------------------------------

		//	背景
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 12);
		//	ゲームモード
		CUI::Create
		(D3DXVECTOR3(400, 330, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 13);
		//	ゲームモード文字
		CUI::Create
		(D3DXVECTOR3(350, 370, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 14);
		//	クレジット
		CUI::Create
		(D3DXVECTOR3(850, 250, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 15);
		//	クレジット文字
		CUI::Create
		(D3DXVECTOR3(850, 320, 0.0f), D3DXVECTOR3(120.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 16);
		//	タイトルへ
		CUI::Create
		(D3DXVECTOR3(770, 500, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 17);
		//	タイトルへ文字
		CUI::Create
		(D3DXVECTOR3(670, 500, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 18);
		//	下の文字表記00
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2-100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 19);
		//	下の文字表記01
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 20);
		//	下の文字表記02
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 21);
		//	PRESS ENTER
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2+450, SCREEN_HEIGHT / 2 + 300, 0.0f), D3DXVECTOR3(150.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);
		break;
	case CManager::MODE_GAMETUTO://		ゲームチュートリアル		---------------------------------------------------------------------------------------------------------
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP背背景
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HPゲージ
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP右アイコン
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// 弾の背景　]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// 手榴弾の画像　]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealthの背景　]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	StealthゲージI　]
		(D3DXVECTOR3(195.0f, 70.0f,0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealthの草の画像　]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// ダッシュの背景　]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	ダッシュゲージI　]
		(D3DXVECTOR3(195.0f,85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// ダッシュの画像　]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);

		if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
		{//	チュートリアルステージだった場合
		// チュートリアル--------------------------------------------------------------------------------------------------------------------------------------------------|
			CUI::Create//	チュートリアル拝背景
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXVECTOR3(340.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 22);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 23);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 24);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 45.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 25);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 45.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 26);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 27);
			CUI::Create// チュートリアルUI[ 文字　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 28);
			CUI::Create// チュートリアルUI[ 説明文　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 125, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 29);
			CUI::Create// チュートリアルUI[ 操作方法　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 30);
			CUI::Create// チュートリアルUI[ 矢印　]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 31);
			CUI::Create// チュートリアルUI[操作説明キーボードパッド]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 +420, SCREEN_HEIGHT / 2-100, 0.0f), D3DXVECTOR3(0.0f, 170.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 36);
			CUI::Create// チュートリアルUI[操作説明ありなし]
			(D3DXVECTOR3(1100.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 37);
		}
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause選択[ 3番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// ゲームオーバーUI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// 赤い背景
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// ゲームオーバー選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// ゲームオーバー選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		break;
	case CManager::MODE_GAMESTAGE000://		ゲームステージ1		-----------------------------------------------------------------------------------------
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP背背景
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HPゲージ
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP右アイコン
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// 弾の背景　]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// 手榴弾の画像　]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealthの背景　]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	StealthゲージI　]
		(D3DXVECTOR3(195.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealthの草の画像　]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// ダッシュの背景　]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	ダッシュゲージI　]
		(D3DXVECTOR3(195.0f, 85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// ダッシュの画像　]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause選択[ 3番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// ゲームオーバーUI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// 赤い背景
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// ゲームオーバー選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// ゲームオーバー選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+100, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		break;
	case CManager::MODE_GAMESTAGE002://		ゲームステージ2		-----------------------------------------------------------------------------------------
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP背背景
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HPゲージ
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP右アイコン
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// 弾の背景　]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// 手榴弾の画像　]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealthの背景　]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	StealthゲージI　]
		(D3DXVECTOR3(195.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealthの草の画像　]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// ダッシュの背景　]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	ダッシュゲージI　]
		(D3DXVECTOR3(195.0f, 85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// ダッシュの画像　]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause選択[ 3番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// ゲームオーバーUI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// 赤い背景
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// ゲームオーバー選択[ 1番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// ゲームオーバー選択[ 2番　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		//	クリア時の文字------------------------------------------------------------------------------------------------------
		CUI::Create//	文字の拝背景
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 22);
		CUI::Create//	文字0つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 43);
		CUI::Create//	文字1つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 44);
		CUI::Create//	文字2つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 45);
		CUI::Create//	文字3つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 46);
		CUI::Create//	文字4つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 47);
		CUI::Create//	文字5つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f,55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 48);
		CUI::Create//	文字6つ目
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 49);
		//	クリア時の文字の出力方法------------------------------------------------------------------------------------------------
		CUI::Create// 文字一UI[ 操作方法　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 30);
		CUI::Create// 文字一UI[ 矢印　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 31);
		break;
	case CManager::MODE_OVER://	オーバー	-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create	// 黒い背景　]
		(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create	//	PRESS ENTER
		(D3DXVECTOR3(SCREEN_WIDTH / 2+400, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(150.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f),5);
		CUI::Create	//	MISSIONFILDE
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 450.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 42);
		break;
	case CManager::MODE_CLEAR://クリア	-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create	// Stealthしている演出　]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	PRESS ENTER
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);
		CUI::Create	//	MISSIONCLEAR
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 400.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 50);
		break;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR2 uv,int nType)
{
	CScene2D::SetInitAll(pos, size, col, uv);	// 初期値設定
	CScene2D::Init();							// 初期化処理
	CScene2D::BindTexture(m_pTexture[nType]);	// テクスチャ割り当て
	//	種類の設定
	m_nType = nType;
	//	昔の大きさの設定
	m_sizeOld = size;
	//	初期の位置
	m_InitPos = pos;
	//	セレクトの番号
	m_nNumSelectMode = 0;
	//	チュートリアルの表記設定
	m_nNextTxst = 0;
	//	チュートリアルが終わった場合
	m_bTutoEnd = false;
	//	チュートリアルの操作説明描画するかしないか
	m_bTutoOperation = false;
	if (m_mode == CManager::MODE_GAMETUTO || m_mode == CManager::MODE_GAMESTAGE000 || m_mode == CManager::MODE_GAMESTAGE002)
	{//	ゲームモードの場合
		m_nPlayerLifeMax = CGame::GetPlayer()->GetLife();			//	体力の最大数の設定
		m_nStealthLifeMax = CGame::GetPlayer()->GetStealthLife();	//	プレイヤーのステルスの寿命
		m_nDashLifeMax =CGame::GetPlayer()->GetDashLife();			//	プレイヤーのダッシュの寿命最大
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();						// 終了処理
}

//=============================================================================
// 更新処理
//=============================================================================
void CUI::Update(void)
{
	CSound *pSound = CManager::GetSound();	//	サウンドの取得
	D3DXVECTOR3 pos = CScene2D::Getpos();	//	位置の取得
	D3DXVECTOR3 size = CScene2D::Getsize();	//	大きさの取得
	D3DXCOLOR col = CScene2D::Getcol();		//	色の取得
	D3DXVECTOR2 tex[4];						//	テクスチャのUV4頂点
	bool bPause = CGame::GetPause();		//	Pauseの取得
	int nGameOver = CGame::GetOverNum();	//	Pauseの取得
	int nPauseNum = CPause::GetNum();		//	ポーズの番号の取得
	int nTutoNum = 0;						//	チュートリアル現在の数字
	m_nPlayerLifeOld = m_nPlayerLife;		//	体力の設定
	if (m_mode == CManager::MODE_GAMETUTO || m_mode == CManager::MODE_GAMESTAGE000 || m_mode == CManager::MODE_GAMESTAGE002)
	{//	ゲームモードだった場合
		m_nPlayerLife = CGame::GetPlayer()->GetLife();				//	プレイヤーの体力の取得
		m_nPlayerSquat = CGame::GetPlayer()->GetSquat();			//	プレイヤーのステルス状態かどうか
		m_nPlayerDash= CGame::GetPlayer()->GetDash();				//	プレイヤーのダッシュ状態かどうか
		m_nStealthCut = CGame::GetPlayer()->GetStealthCut();		//	プレイヤーのステルス状態に戻るカウンター
		m_nStealthLife = CGame::GetPlayer()->GetStealthLife();		//	プレイヤーのステルスの寿命
		m_nDashCut = CGame::GetPlayer()->GetDashCut();				//	プレイヤーのダッシュのカウンター
		m_nDashLife = CGame::GetPlayer()->GetDashLife();			//	プレイヤーのダッシュの寿命最大
	}
	// 更新処理
	CScene2D::Update();
	m_nCounterAnim++;
	switch (m_mode)
	{
		//*****************************************************************************************
		//	タイトル
		//*****************************************************************************************
	case CManager::MODE_TITLE:

		if (m_nType == 6)
		{//	タイトルロゴ001
			if (m_nCounterAnim <= 180)
			{
				if (pos.x < 350)
				{//	位置が400以下だった場合
					pos.x += 4.0f;	//	位置をずらす
				}
			}
			else if (m_nCounterAnim >= 180)
			{
				if (pos.y > 90)
				{//	位置が400以下だった場合
					pos.y -= 4.0f;	//	位置をずらす
				}
				if (pos.x > 230)
				{//	位置が400以下だった場合
					pos.x -= 4.0f;	//	位置をずらす
				}
			}
		}
		if (m_nType == 7)
		{//	タイトルロゴ002
			if (m_nCounterAnim <= 180)
			{
				if (pos.x > 850)
				{//	位置が400以下だった場合
					pos.x -= 4.0f;	//	位置をずらす
				}
			}
			else if (m_nCounterAnim >= 200)
			{
				if (pos.y < 620)
				{//	位置が400以下だった場合
					pos.y += 4.0f;	//	位置をずらす
				}
				if (pos.x < 1040)
				{//	位置が400以下だった場合
					pos.x += 4.0f;	//	位置をずらす
				}
			}
		}
		if (m_nType == 0)
		{//	タイトルロゴ000
			if (m_nCounterAnim >= 200)
			{
				if (size.y > 20.0f)
				{//	大きさが指定の値以下だった場合以下だった場合
					size.y -= 4.0f;	//	大きさをずらす
				}
				if (size.x > 60.0f)
				{//	大きさが指定の値以下だった場合以下だった場合
					size.x -= 6.0f;	//	大きさをずらす
				}
				if (size.y <= 20.0f && size.x <= 60.0f)
				{
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
				}
				if (pos.y > 90)
				{//	位置が400以下だった場合
					pos.y -= 4.0f;	//	位置をずらす
				}
				if (pos.x > 530)
				{//	位置が400以下だった場合
					pos.x -= 4.0f;	//	位置をずらす
				}
			}
		}
		if (m_nType == 0 || m_nType == 6 || m_nType == 7)
		{//	タイトルロゴだった場合
			if (m_nCounterAnim >= 1400)
			{//	カウンターがが指定の値以上たった場合
				size = m_sizeOld;
				pos = m_InitPos;
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_nCounterAnim = 0;
			}
		}
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// フェードしていない状態
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// キーボード（ENTER）を入力したら
				m_bPressButton = true;
			}

		}
		if (m_nType == 5)
		{//	プレスエンターだったら
			if (m_bPressButton == false)
			{//	ボタンを押していない
				if ((m_nCounterAnim % 60) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	ボタンを押した
				if ((m_nCounterAnim % 6) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	サイズをなくす
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	サイズを初期の大木さんイ戻す
				size.x = m_sizeOld.x;
			}
		}

		break;
		//*****************************************************************************************
		//	セレクトモード
		//*****************************************************************************************
	case CManager::MODE_SELECTMODE:
		if (m_bPressButton == false)
		{//	ボタン押していない
			if (CFade::GetFade() == CFade::FADE_NONE)
			{// フェードしていない状態
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
					|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{	// W 又は　↑キーを押した場合
					m_nNumSelectMode = (m_nNumSelectMode + 2) % 3;
					m_nCounterAnim = 0;
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
					|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
				{	// S 又は　↓キーを押した場合
					m_nNumSelectMode = (m_nNumSelectMode + 1) % 3;
					m_nCounterAnim = 0;
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				}
			}
		}
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// フェードしていない状態
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{//	ボタンを押した
				m_bPressButton = true;
			}
		}
		if (m_bPressButton == true)
		{//	ボタンを押した場合
			m_fFrameValue = 10.0f;
		}
		else if (m_bPressButton == false)
		{//	ボタンを押した場合
			m_fFrameValue = 20.0f;
		}

		if (m_nNumSelectMode == 0)
		{//	選択0番だった場合
			if (m_nType == 14)
			{//	タイトル文字
				if (m_nCounterAnim < m_fFrameValue)
				{//	20フレーム以下だった場合
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40フレーム以下だった場合
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60フレーム以下だった場合
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 19)
			{//	タイトルの下の説明//	拡大
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	それ以外だった場合
			if (m_nType == 19)
			{//	タイトルの下の説明//	縮小
				size.x = 0.0f;
				size.y = 0.0f;
			}
		}
		if (m_nNumSelectMode == 1)
		{//	選択1番だった場合
			if (m_nType == 16)
			{//	クレジット文字
				if (m_nCounterAnim < m_fFrameValue)
				{//	20フレーム以下だった場合
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40フレーム以下だった場合
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60フレーム以下だった場合
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 20)
			{//	クレジットの下の説明//	拡大
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	それ以外だった場合
			if (m_nType == 20)
			{//	タイトルの下の説明//	縮小
				size.x = 0.0f;
				size.y = 0.0f;
			}
		}
		if (m_nNumSelectMode == 2)
		{//	選択2番だった場合
			if (m_nType == 18)
			{//	タイトルへ文字
				if (m_nCounterAnim < m_fFrameValue)
				{//	20フレーム以下だった場合
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40フレーム以下だった場合
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60フレーム以下だった場合
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 21)
			{//	//	タイトルへの説明//	拡大
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	それ以外だった場合
			if (m_nType == 21)
			{//	//	タイトルへの説明//	縮小
				size.x = 0.0f;
				size.y = 0.0f;
			}
		}
		if (m_nCounterAnim == 0)
		{
			size.x = m_sizeOld.x;
			size.y = m_sizeOld.y;
		}
		if (m_nType == 5)
		{//	プレスエンターだったら
			if (m_bPressButton == false)
			{//	ボタンを押していない
				if ((m_nCounterAnim % 60) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	ボタンを押した
				if ((m_nCounterAnim % 6) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	サイズをなくす
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	サイズを初期の大木さんイ戻す
				size.x = m_sizeOld.x;
			}
		}

		break;
		//*****************************************************************************************
		//	ゲームチュートリアル
		//*****************************************************************************************
	case CManager::MODE_GAMETUTO:
		//------------------------------------------------------------------
		//	チュートリアル
		//------------------------------------------------------------------
		if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
		{//	チュートリアルステージだった場合
			if (m_nNextTxst < 7)
			{
				m_nCutTuto++;			//	チュートリアルカウンターの加算
				if (m_nCutTuto > 80)
				{//	カウンターが一定のフレームたった場合
					if (m_nType == 22)
					{
						if ((CManager::GetInputKeyboard()->GetTrigger(DIK_Y) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true) && bPause == false)
						{//	Yキー　&&Yボタン &&Pauseしていない
							m_nNextTxst += 1;	//	次の文へ
							m_nCutTuto = 0;		//	カウンターの初期化
							if (m_nNextTxst < 6)
							{// 文字の出る音
								pSound->PlaySound(CSound::SOUND_LABEL_SE_TEXTSE);
							}
						}
					}
					if (m_nType == 30)
					{//	操作方法UI　大きさの設定　
						size.x = 80.0f;
					}
					if ((m_nCutTuto % 30) == 0)
					{//	10フレームに1ッ回
						m_bSize = m_bSize ? false : true;		//	大きさの変化

					}
					if (m_nType == 31)
					{//　大きさの設定　
						if (m_bSize == true)
						{//	大きくする三角矢印
							size.x = 40.0f;
						}
						else if (m_bSize == false)
						{//	小さくする三角矢印
							size.x = 0.0f;
						}
					}
				}
				else
				{//	カウンターが一定のフレーム以下だった場合
					if (m_nType == 30)
					{//	操作方法UI　大きさの設定　
						size.x = 0.0f;
					}
					if (m_nType == 31)
					{//大きさの設定　
						size.x = 0.0f;
					}
				}
				//	チュートリアルの文の値の設定
				nTutoNum = 23 + m_nNextTxst;
				if (m_nType == nTutoNum)
				{//	種類が設定した値と同じだった場合
					if (m_nType == 23)
					{//	サイズを設定する
						size.x = 130;
					}
					else if (m_nType == 27)
					{//	サイズを設定する
						size.x = 200;
					}
					else if (m_nType == 28)
					{//	サイズを設定する
						size.x = 230;
					}
					else if (m_nType == 29)
					{//	サイズを設定する
						size.x = 230;
					}
					else
					{//	サイズを設定する
						size.x = 220;
					}
				}
				for (int nCount = 23; nCount < 29; nCount++)
				{//チュートリアルの数文回す
					if (nTutoNum != nCount &&m_nType == nCount)
					{//	現在表示されている以外のチュートリアルのUIのサイズを小さくする
						size.x = 0;
					}
				}
				if (m_nNextTxst > 5 && bPause == false)
				{//	ツーとリアルの文字表記が終わったら
					CScene::SetStartUp(0);
				}
				else if (m_nNextTxst < 5)
				{//	チュートリアル中は更新止める
					CScene::SetStartUp(CScene::PRIORITY_PAUSE);
				}
			}
		}
		if (m_nNextTxst > 6)
		{//	値の数字以上いった場合
			for (int nCount = 22; nCount < 32; nCount++)
			{//チュートリアルの数文回す
				if (m_nType == nCount)
				{
					Uninit();
				}
			}
			m_bTutoEnd = true;
		}

		//------------------------------------------------------------------
		//	ゲームUI
	    //------------------------------------------------------------------
		if (m_nType == 36)
		{//	操作方法
			if (m_bTutoEnd == true)
			{//	説明が終わった場合
				if ((CManager::GetInputKeyboard()->GetTrigger(DIK_1) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0) == true))
				{//  R又は　1キーを押した場合
					m_bTutoOperation = m_bTutoOperation ? false : true;
				}
				if (m_bTutoOperation == false)
				{//	操作説明の描画falseの場合大きくする
					size.x = 200;
				}
				else if (m_bTutoOperation == true)
				{//	操作説明の描画trueの場合小さくする
					size.x = 0;
				}
			}
		}
		if (m_nType == 37)
		{//	操作方法ありなし
			if (m_bTutoEnd == true)
			{//	説明が終わった場合
				size.x = 140;
			}
		}
		if (m_nType == 3)
		{//	HPゲージだったら
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	最大値より小さかった場合
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x = m_InitPos.x;	//	位置をずらす
					size.x = m_sizeOld.x;	//	大きさをライフに応じて減らす
				}
			}
		}
		if (m_nType == 2)
		{//	プレイヤーのアイコン
			if (m_nPlayerLife > 0)
			{//	プレイヤーのＨＰが0以上
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存の値が現在のＨＰより多かった場合
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	色を赤くする
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	保存の値が現在のＨＰと同じだった場合
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	色を赤くする
				}
			}

		}
		if (bPause == false)
		{//	Pauseしていなかった
			if (m_nType == 35)
			{//	StealthゲージI
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerSquat == true)
					{//	プレイヤーがステルスしている場合
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerSquat == false)
					{//	プレイヤーがステルスしていない
						if (m_nStealthLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする

						}
						else if (m_nStealthLife >= m_nStealthLifeMax)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}
					}
				}
			}
		}
		if (bPause == false)
		{//	Pauseしていなかった
			if (m_nType == 52)
			{//	ダッシュゲージ
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerDash == true)
					{//	プレイヤーがダッシュしている場合
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerDash == false)
					{//	プレイヤーがダッシュしていない
						if (m_nDashLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}
					}
				}
			}
		}
		if (m_nType == 38)
		{//	ステルス状態の時の演出
			if (m_nPlayerSquat == true)
			{//	プレイヤーがステルスしている場合
				if (size.y < 60)
				{
					size.y += 2.0f;	//	大きさする
				}
			}
			else if (m_nPlayerSquat == false)
			{//	プレイヤーがステルスしていない場合
				size.y = 0.0f;		//	小さくする

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	ゲームの状態がゲームエンドの場合
			if (m_nType == 39)
			{//	赤い背景
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	ゲームオーバー選択[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	ゲームオーバー選択[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	ゲームオーバーの選択文回す
				if (m_nType == 40 + nCutPause)
				{//	選択項目を明るくする
					if (nGameOver == 0 + nCutPause)
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
					}
				}
			}
		}
		//------------------------------------------------------------------
		//	Pauseの設定
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pauseの描画BG
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pauseの選択
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	ポーズの数文回す
			if (m_nType == 9 + nCutPause)
			{//	ポーズ選択1番
				if (nPauseNum == 0 + nCutPause)
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
				}
			}
		}
		break;
		//*****************************************************************************************
		//	ゲームステージ
		//*****************************************************************************************
	case CManager::MODE_GAMESTAGE000:
		//------------------------------------------------------------------
		//	ゲームUI
		//------------------------------------------------------------------
		if (m_nType == 3)
		{//	HPゲージだったら
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	最大値より小さかった場合
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x = m_InitPos.x;	//	位置をずらす
					size.x = m_sizeOld.x;	//	大きさをライフに応じて減らす
				}
			}
		}
		if (m_nType == 2)
		{//	プレイヤーのアイコン
			if (m_nPlayerLife > 0)
			{//	プレイヤーのＨＰが0以上
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存の値が現在のＨＰより多かった場合
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	色を赤くする
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	保存の値が現在のＨＰと同じだった場合
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	色を赤くする
				}
			}

		}
		if (bPause == false)
		{//	Pauseしていなかった
			if (m_nType == 35)
			{//	StealthゲージI
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerSquat == true)
					{//	プレイヤーがステルスしている場合
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerSquat == false)
					{//	プレイヤーがステルスしていない
						if (m_nStealthLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする

						}
						else if (m_nStealthLife >= 300)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}
					}
				}
			}
		}
		if (bPause == false)
		{//	Pauseしていなかった
			if (m_nType == 52)
			{//	ダッシュゲージ
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerDash == true)
					{//	プレイヤーがダッシュしている場合
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerDash == false)
					{//	プレイヤーがダッシュしていない
						if (m_nDashLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}
					}
				}
			}
		}
		if (m_nType == 38)
		{//	ステルス状態の時の演出
			if (m_nPlayerSquat == true)
			{//	プレイヤーがステルスしている場合
				if (size.y < 60)
				{
					size.y += 2.0f;	//	大きさする
				}
			}
			else if (m_nPlayerSquat == false)
			{//	プレイヤーがステルスしていない場合
				size.y = 0.0f;		//	小さくする

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	ゲームの状態がゲームエンドの場合
			if (m_nType == 39)
			{//	赤い背景
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	ゲームオーバー選択[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	ゲームオーバー選択[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	ゲームオーバーの選択文回す
				if (m_nType == 40 + nCutPause)
				{//	選択項目を明るくする
					if (nGameOver == 0 + nCutPause)
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
					}
				}
			}
		}
		//------------------------------------------------------------------
		//	Pauseの設定
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pauseの描画BG
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pauseの選択
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	ポーズの数文回す
			if (m_nType == 9 + nCutPause)
			{//	ポーズ選択1番
				if (nPauseNum == 0 + nCutPause)
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
				}
			}
		}
		break;
		//*****************************************************************************************
		//	ゲームステージ002
		//*****************************************************************************************
	case CManager::MODE_GAMESTAGE002:
		//------------------------------------------------------------------
		//	ゲームUI
		//------------------------------------------------------------------
		if (m_nType == 3)
		{//	HPゲージだったら
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	最大値より小さかった場合
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	位置をずらす
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	大きさをライフに応じて減らす
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	保存している値より小さかった場合
					pos.x = m_InitPos.x;	//	位置をずらす
					size.x = m_sizeOld.x;	//	大きさをライフに応じて減らす
				}
			}
		}
		if (m_nType == 2)
		{//	プレイヤーのアイコン
			if (m_nPlayerLife > 0)
			{//	プレイヤーのＨＰが0以上
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	保存の値が現在のＨＰより多かった場合
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	色を赤くする
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	保存の値が現在のＨＰと同じだった場合
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	色を赤くする
				}
			}
		}
		if (bPause == false && CGame::GetClear() == false)
		{//	Pauseしていなかった
			if (m_nType == 35)
			{//StealthゲージI
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerSquat == true)
					{//	プレイヤーがステルスしている場合
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerSquat == false)
					{//	プレイヤーがステルスしていない
						if (m_nStealthLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする

						}
						else if (m_nStealthLife >= m_nStealthLifeMax)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}
					}
				}
			}
		}
		if (bPause == false && CGame::GetClear() == false)
		{//	Pauseしていなかった
			if (m_nType == 52)
			{//	ダッシュゲージ
				if (CGame::GetPlayer() != NULL)
				{//	プレイヤーが使用されていた場合
					if (m_nPlayerDash == true)
					{//	プレイヤーがダッシュしている場合
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	位置をずらす
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	大きさを減らす
					}
					else if (m_nPlayerDash == false)
					{//	プレイヤーがダッシュしていない
						if (m_nDashLife == 0)
						{//	寿命が0の場合
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	位置をずらす
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	色を赤くする
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	大きさが同じになった場合
							pos.x = m_InitPos.x;					//	位置をずらす
							size.x = m_sizeOld.x;					//	大きさを増やす
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	色を戻す
						}

					}
				}
			}
		}
		if (m_nType == 38)
		{//	ステルス状態の時の演出
			if (m_nPlayerSquat == true)
			{//	プレイヤーがステルスしている場合
				if (size.y < 60)
				{
					size.y += 2.0f;	//	大きさする
				}
			}
			else if (m_nPlayerSquat == false)
			{//	プレイヤーがステルスしていない場合
				size.y = 0.0f;		//	小さくする

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	ゲームの状態がゲームエンドの場合
			if (m_nType == 39)
			{//	赤い背景
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	ゲームオーバー選択[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	ゲームオーバー選択[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	ゲームオーバーの選択文回す
				if (m_nType == 40 + nCutPause)
				{//	選択項目を明るくする
					if (nGameOver == 0 + nCutPause)
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
					}
				}
			}
		}
		//------------------------------------------------------------------
		//	Pauseの設定
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pauseの描画BG
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pauseの選択
			if (bPause == false)
			{//	Pauseしていなかった
				size.x = 0;
			}
			else
			{//	Pauseしている
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	ポーズの数文回す
			if (m_nType == 9 + nCutPause)
			{//	ポーズ選択1番
				if (nPauseNum == 0 + nCutPause)
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
				}
			}
		}
		if (CGame::GetClear() == true)
		{//	ゲームクリアした時
			m_nCutTuto++;			//	チュートリアルカウンターの加算
			if (m_nType == 30)
			{//	操作方法UI　大きさの設定　
				size.x = 80.0f;
			}
			if ((m_nCutTuto % 30) == 0)
			{//	//	大きさの変化
				m_bSize = m_bSize ? false : true;
			}
			if (m_nType == 31)
			{//　大きさの設定　
				if (m_bSize == true)
				{//	大きくする三角矢印
					size.x = 40.0f;
				}
				else if (m_bSize == false)
				{//	小さくする三角矢印
					size.x = 0.0f;
				}
			}
			if (m_nType == 22)
			{//	文字の背景
				size.x = 340.0f;			//	大きさの変更
				if (m_nNextTxst < 6)
				{
					if (m_nCutTuto > 80)
					{//	カウンターが一定のフレームたった場合
						if ((CManager::GetInputKeyboard()->GetTrigger(DIK_Y) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true) && bPause == false)
						{//	Yキー　&&Yボタン &&Pauseしていない
							m_nNextTxst += 1;	//	次の文へ
							m_nCutTuto = 0;		//	カウンターの初期化
							if (m_nNextTxst < 6)
							{// 文字の出る音
								pSound->PlaySound(CSound::SOUND_LABEL_SE_TEXTSE);
							}
							if (m_nNextTxst == 1)
							{//	音を止める
								pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGE3);
							}

						}
					}
				}
			}
			//	チュートリアルの文の値の設定
			nTutoNum = 43 + m_nNextTxst;
			if (m_nType == nTutoNum)
			{//	種類が設定した値と同じだった場合
				for (int nCount = 43; nCount < 50; nCount++)
				{//チュートリアルの数文回す
					if (m_nType == nCount)
					{//	サイズを設定する
						if (nCount == 43 || m_nType == 44 || m_nType == 49)
						{
							size.x = 130;
						}
						else
						{
							size.x = 180;
						}
					}
				}
			}
			for (int nCount = 43; nCount < 50; nCount++)
			{//チュートリアルの数文回す
				if (nTutoNum != nCount &&m_nType == nCount)
				{//	現在表示されている以外のチュートリアルのUIのサイズを小さくする
					size.x = 0;
				}
			}
			if (m_nNextTxst > 6 && bPause == false)
			{//	ツーとリアルの文字表記が終わったら
				CScene::SetStartUp(0);
			}
			else if (m_nNextTxst < 6)
			{//	チュートリアル中は更新止める
				CScene::SetStartUp(CScene::PRIORITY_PAUSE);
			}
		}
		break;
	case CManager::MODE_OVER:	//	ゲームオーバー
		if (m_nType == 42)
		{//	missionfild
			if (m_nCounterAnim <= 600)
			{//	600フレーム以下だった場合
				if (size.x <= 650)
				{//	大きくする
					size.x += 5.0f;
				}
			}
			else
			{//	600フレーム以上たった場合
				m_nCounterAnim = 0;	//	初期化する
				size.x = 0.0f;
			}
			if ((m_nCounterAnim % 40) == 0)
			{//	60秒で点滅
				m_bColChange = m_bColChange ? false : true;	//	色の変更
			}
			if (m_bColChange == false)
			{//	色の変更
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (m_bColChange == true)
			{//	色の変更
				col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
			}

		}
		if (m_nType == 5)
		{//	プレスエンターだったら
			if (m_bPressButton == false)
			{//	ボタンを押していない
				if ((m_nCounterAnim % 60) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	ボタンを押した
				if ((m_nCounterAnim % 6) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	サイズをなくす
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	サイズを初期の大木さんイ戻す
				size.x = m_sizeOld.x;
			}
		}
		break;
	case CManager::MODE_CLEAR://クリア	-------------------------------------------------------------------------------------------------------------------------------------
		if (m_nType == 5)
		{//	プレスエンターだったら
			if (m_bPressButton == false)
			{//	ボタンを押していない
				if ((m_nCounterAnim % 60) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	ボタンを押した
				if ((m_nCounterAnim % 6) == 0)
				{//	60秒で点滅
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	サイズをなくす
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	サイズを初期の大木さんイ戻す
				size.x = m_sizeOld.x;
			}
		}
		if (m_nType == 50)
		{//	missionfild
			if (m_nCounterAnim <= 600)
			{//	600フレーム以下だった場合
				if (size.x <= 650)
				{//	大きくする
					size.x += 5.0f;
				}
			}
			else
			{//	600フレーム以上たった場合
				m_nCounterAnim = 0;	//	初期化する
				size.x = 0.0f;
			}
		}
		break;
	}

	CScene2D::Setpos(pos);				//	位置の設定
	CScene2D::Setsize(size);			//	大きさの設定
	CScene2D::Setcol(col);				//	色の設定
}

//=============================================================================
// 描画処理
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();						// 描画処理
}


