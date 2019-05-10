//**************************************************************
//
//		リザルトの処理[result.cpp]
//		Auther : YUTARO ABE
//
//**************************************************************
#include "scene2d.h"		// シーン2D
#include "result.h"			// リザルト
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "fade.h"			// フェード
#include "input.h"			// 入力
#include "scene.h"			// シーン
#include "UI.h"				// UI
#include "sound.h"			// サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
//		コンストラクタ
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
//		デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
//		初期化処理
//=============================================================================
HRESULT CResult::Init(GAMESTATE GameState)
{
	if (GAMESTATE_OVER == GameState)
	{//	ゲームオーバーだった場合
		m_rGameState = GAMESTATE_OVER;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_OVER);
		//  Uiの読み込み
		CUI::Load(CManager::MODE_OVER);
		//	UIの生成
		CUI::CreateMode(CManager::MODE_OVER);
	}
	else if (GAMESTATE_CLEAR == GameState )
	{//	ゲームクリアだった場合
		m_rGameState = GAMESTATE_CLEAR;
		CSound::PlaySound(CSound::SOUND_LABEL_BGM_CLEAR);
		//  Uiの読み込み
		CUI::Load(CManager::MODE_CLEAR);
		//	UIの生成
		CUI::CreateMode(CManager::MODE_CLEAR);
	}


	return S_OK;
}

//=============================================================================
//		終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CUI::Unload();			//   Uiの開放

	CScene::ReleaseMode();	// モード終了

	//	音を止める
	CSound::StopSound(CSound::SOUND_LABEL_BGM_CLEAR);
	CSound::StopSound(CSound::SOUND_LABEL_BGM_OVER);
}

//=============================================================================
//		更新処理
//=============================================================================
void CResult::Update(void)
{

	if (m_rGameState == GAMESTATE_CLEAR)
	{//	ゲームクリアだった場合
#ifdef _DEBUG
	CManager::m_CDebugProcLeft->Print("\n現在のモード【　クリア　】");
#endif // _DEBUG
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// フェードしていない状態
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// キーボード（ENTER）を入力したら
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT,1);
			}
		}
	}
	else if (m_rGameState == GAMESTATE_OVER)
	{
#ifdef _DEBUG
		CManager::m_CDebugProcLeft->Print("\n現在のモード【　オーバー　】");
#endif // _DEBUG

		if (CFade::GetFade() == CFade::FADE_NONE)
		{// フェードしていない状態
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// キーボード（ENTER）を入力したら
				CFade::Create(CManager::MODE_SELECTMODE, CFade::FADE_OUT, 0);
			}
		}
	}

}

//=============================================================================
//		描画処理
//=============================================================================
void CResult::Draw(void)
{

}