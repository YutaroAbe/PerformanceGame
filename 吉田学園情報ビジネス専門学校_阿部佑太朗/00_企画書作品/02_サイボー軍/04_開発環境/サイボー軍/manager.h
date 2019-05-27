//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "select.h"
#include "result.h"
#include "stageselect.h"
#include "credit.h"
#include "missionmessage.h"

class CFade;

//=============================================================================
//	マネージャークラス
//=============================================================================
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_SELECT,
		MODE_STAGESELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_CREDIT,
		MODE_MAX
	}MODE;

	CManager();														// コンストラクタ
	~CManager();													// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputGamePad *GetInputGamepad(void);
	static void SetMode(MODE mode);									//	モードの設定
	static MODE GetMode(void);
	static CFade *GetFade(void) { return m_pFade; }
private:
	CScene2D  *m_pScene2d;
	static CRenderer *m_pRenderer;									//	レンダーのポインタ型変数
	static CInputKeyboard *m_pInputKeyboard;						//	入力のポインタ型変数
	static CSound *m_pSound;
	static MODE m_mode;

	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CResult *m_pResult;
	static CFade *m_pFade;
	static CSelect *m_pSelect;
	static CStageSelect *m_pStageSelect;
	static CInputGamePad *m_pInputGamepad;
	static CCredit *m_pCredit;
	static CMissionMessage *m_pMissionMessage;
};

#endif // _MANAGER_H_
