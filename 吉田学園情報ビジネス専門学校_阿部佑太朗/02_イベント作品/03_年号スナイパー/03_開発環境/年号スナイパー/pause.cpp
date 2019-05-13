//*****************************************************************************
//
//			ポーズの処理[pause.cpp]
//			Auther : YUTARO ABE
//
//*****************************************************************************

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"		// 入力
#include "manager.h"	// マネージャー
#include "renderer.h"	// レンダラー
#include "scene2D.h"	// シーン2D
#include "pause.h"		// ポーズ
#include "fade.h"		// フェード
#include "game.h"		//	Pause
#include "sound.h"		//	音

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define TEXTURE_NAME000	"data/Texture/pause/continue.png"	// 読み込むテクスチャ000
#define TEXTURE_NAME001	"data/Texture/pause/retry.png"		// 読み込むテクスチャ001
#define TEXTURE_NAME002	"data/Texture/pause/Quit.png"		// 読み込むテクスチャ002
#define COL_A			(0.009f)							// 透明度の変化量
#define COL_A_MAX		(0.65f)								// 透明度の限度量
#define POS_X_INTERVAL	(150.0f)							// X座標の間隔
#define PRESS_BUTTON_X	(50.0f)								// ボタンのサイズ(X軸)
#define PRESS_BUTTON_Y	(50.0f)								// ボタンのサイズ(Y軸)
#define PRESS_INTERVAL	(200.0f)							// メニューとの距離

//*****************************************************************************
//				静的メンバ変数
//*****************************************************************************
int				CPause::m_nNum = false;

//*****************************************************************************
//				生成処理
//*****************************************************************************
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	CPause *pPause = {};

	// シーンの生成
	if (pPause == NULL)
	{
		pPause = new CPause;
		if (pPause != NULL)
		{
			pPause->Init(pos, size, col, UV);
		}
	}
	return pPause;
}
//*****************************************************************************
//				ロード
//*****************************************************************************
HRESULT CPause::Load(void)
{

	return S_OK;
}
//*****************************************************************************
//				アンロード
//*****************************************************************************
void CPause::Unload(void)
{

}
//*****************************************************************************
//				コンストラクタ
//*****************************************************************************
CPause::CPause()
{

}
//*****************************************************************************
//				デストラクタ
//*****************************************************************************
CPause::~CPause()
{
}

//*****************************************************************************
//				初期化処理
//*****************************************************************************
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 UV)
{
	Load();		// 読み込み

	//　初期化
	m_nNum = 0;

	return S_OK;
}

//*****************************************************************************
//				終了処理
//*****************************************************************************
void CPause::Uninit()
{

}

//*****************************************************************************
//				更新処理
//*****************************************************************************
void CPause::Update()
{
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
	{	// W 又は　↑キーを押した場合
		m_nNum = (m_nNum + 2) % POLYGON_PAUSE;
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
		|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
	{	// S 又は　↓キーを押した場合
		m_nNum = (m_nNum + 1) % POLYGON_PAUSE;
		CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
	{
		if (m_nNum == 0)
		{	// ポーズ解除
			CGame::SetPause(false);
		}
		else if (m_nNum == 1)
		{	// ゲーム画面へ
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				if (CGame::GetStage() == CGame::STAGE_001)
				{//	ステージ1だった場合
					CFade::Create(CManager::MODE_GAME001, CFade::FADE_OUT, 0);
				}
			}
		}
		else if (m_nNum == 2)
		{	//　タイトル画面へ
			if (CFade::GetFade() == CFade::FADE_NONE)
			{
				CFade::Create(CManager::MODE_TITLE, CFade::FADE_OUT,0);
			}
		}
	}
}

//*****************************************************************************
//				描画処理
//*****************************************************************************
void CPause::Draw()
{

}
