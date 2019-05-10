//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
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
//	�}�l�[�W���[�N���X
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

	CManager();														// �R���X�g���N�^
	~CManager();													// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputGamePad *GetInputGamepad(void);
	static void SetMode(MODE mode);									//	���[�h�̐ݒ�
	static MODE GetMode(void);
	static CFade *GetFade(void) { return m_pFade; }
private:
	CScene2D  *m_pScene2d;
	static CRenderer *m_pRenderer;									//	�����_�[�̃|�C���^�^�ϐ�
	static CInputKeyboard *m_pInputKeyboard;						//	���͂̃|�C���^�^�ϐ�
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
