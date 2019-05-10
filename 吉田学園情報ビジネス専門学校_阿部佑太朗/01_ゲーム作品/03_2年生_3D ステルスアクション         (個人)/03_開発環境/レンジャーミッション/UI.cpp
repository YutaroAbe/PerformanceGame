//=============================================================================
//
// UI���� [UIe.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "ui.h"				// �^�C�g���t���[��
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "input.h"			// ����
#include "bulletNumber.h"		// ���C�t�̐��l
#include "game.h"			// �Q�[��
#include "pause.h"			//	Pause
#include "player.h"			//	�v���C���[
#include "bullet3D.h"		//	�e3D
#include "fade.h"			//	�t�F�C�h
#include "sound.h"			//	�T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//	#	�^�C�g��
#define	TEXTURE_TITLE000		"data\\TEXTURE\\UI\\TITLE\\title000.png"		// �^�C�g�����S000�e�N�X�`��
#define	TEXTURE_TITLE001		"data\\TEXTURE\\UI\\TITLE\\title001.png"		// �^�C�g�����S001�e�N�X�`��
#define	TEXTURE_TITLE002		"data\\TEXTURE\\UI\\TITLE\\title002.png"		// �^�C�g�����S002�e�N�X�`��
//	#	�Q�[��
#define	TEXTURE_GAME000			"data\\TEXTURE\\UI\\GAME\\hpbar.png"			//  HP�o�[�e�N�X�`��
#define	TEXTURE_GAME001			"data\\TEXTURE\\UI\\GAME\\caricon.png"			//  �L�����A�C�R��bg�e�N�X�`��
#define	TEXTURE_GAME002			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  HP�Q�[�W�e�N�X�`��
#define	TEXTURE_GAME003			"data\\TEXTURE\\UI\\GAME\\lifebg.png"			//  HP���lBG�e�N�X�`��
#define	TEXTURE_GAME004			"data\\TEXTURE\\UI\\GAME\\boombg.png"			//  �e��UBG
#define	TEXTURE_GAME005			"data\\TEXTURE\\UI\\GAME\\boom.png"				//  ��֒e�̉摜
#define	TEXTURE_GAME006			"data\\TEXTURE\\UI\\GAME\\suterusu.png"			//  Stealth�̑��̉摜
#define	TEXTURE_GAME007			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  HP�Q�[�W�e�N�X�`��
#define	TEXTURE_GAME008			"data\\TEXTURE\\UI\\GAME\\StealthUI.png"		//  �X�e���X��Ԃ̎��̉��o

#define	TEXTURE_GAME009			"data\\TEXTURE\\UI\\GAME\\butu.png"			//  �_�b�V���̌C�̉摜
#define	TEXTURE_GAME010			"data\\TEXTURE\\UI\\GAME\\hpgage.png"			//  �_�b�V���Q�[�W�e�N�X�`��
#define	TEXTURE_GAME011			"data\\TEXTURE\\UI\\GAME\\StealthUI.png"		//  �_�b�V����Ԃ̎��̉��o

//	#	�Z���N�g���[�h
#define	TEXTURE_SELECTMODEBG			"data\\TEXTURE\\UI\\select\\selectbg.png"				//  �Z���N�g�̔w�i
#define	TEXTURE_SELMODEGAMEMODE			"data\\TEXTURE\\UI\\select\\gamemode.png"				//  �Z���N�g�̃Q�[�����[�h
#define	TEXTURE_SELMODEGAMEMODETXST		"data\\TEXTURE\\UI\\select\\gamemodetxst.png"			//  �Z���N�g�̃Q�[�����[�h����
#define	TEXTURE_SELMODECREDIT			"data\\TEXTURE\\UI\\select\\creditmode.png"				//  �Z���N�g�̃N���W�b�g
#define	TEXTURE_SELMODECREDITTXST		"data\\TEXTURE\\UI\\select\\creditmodetxst.png"			//  �Z���N�g�̃N���W�b�g����
#define	TEXTURE_SELMODETITLERETURE		"data\\TEXTURE\\UI\\select\\titlereturn.png"			//  �Z���N�g�̃^�C�g���߂�
#define	TEXTURE_SELMODETITLERETURETXST	"data\\TEXTURE\\UI\\select\\titlereturntxst.png"	//  �Z���N�g�̃^�C�g���߂镶��
#define	TEXTURE_SELMODEDES00			"data\\TEXTURE\\UI\\select\\Description00.png"		//  �Z���N�g�̐�������00
#define	TEXTURE_SELMODEDES01			"data\\TEXTURE\\UI\\select\\Description01.png"		//  �Z���N�g�̐�������01
#define	TEXTURE_SELMODEDES02			"data\\TEXTURE\\UI\\select\\Description02.png"		//  �Z���N�g�̐�������02
//	#	�|�[�Y
#define	TEXTURE_PAUSEBG			"data\\TEXTURE\\UI\\Pause\\pausebg.png"			//  �|�[�Y�̔w�i
#define	TEXTURE_PAUSESEL000		"data\\TEXTURE\\UI\\Pause\\pausesel000.png"		//  �|�[�Y�̔w�i
#define	TEXTURE_PAUSESEL001		"data\\TEXTURE\\UI\\Pause\\pausesel001.png"		//  �|�[�Y�̔w�i
#define	TEXTURE_PAUSESEL002		"data\\TEXTURE\\UI\\Pause\\pausesel002.png"		//  �|�[�Y�̔w�i
//	#	�`���[�g���A��
#define	TEXTURE_TUTO_BG			"data\\TEXTURE\\UI\\TUTO\\tutobg.png"			//  �`���[�g���A���̔w�i
#define	TEXTURE_TUTO_000		"data\\TEXTURE\\UI\\TUTO\\tuto000.png"			//  �`���[�g���A���̐�����1
#define	TEXTURE_TUTO_001		"data\\TEXTURE\\UI\\TUTO\\tuto001.png"			//  �`���[�g���A���̐�����2
#define	TEXTURE_TUTO_002		"data\\TEXTURE\\UI\\TUTO\\tuto002.png"			//  �`���[�g���A���̐�����3
#define	TEXTURE_TUTO_003		"data\\TEXTURE\\UI\\TUTO\\tuto003.png"			//  �`���[�g���A���̐�����4
#define	TEXTURE_TUTO_004		"data\\TEXTURE\\UI\\TUTO\\tuto004.png"			//  �`���[�g���A���̐�����5
#define	TEXTURE_TUTO_005		"data\\TEXTURE\\UI\\TUTO\\tuto005.png"			//  �`���[�g���A���̐�����6
#define	TEXTURE_TUTO_006		"data\\TEXTURE\\UI\\TUTO\\tuto006.png"			//  �`���[�g���A���̐�����7
#define	TEXTURE_TUTO_007		"data\\TEXTURE\\UI\\TUTO\\tutoope.png"			//  �`���[�g���A���̑�����@
#define	TEXTURE_TUTO_008		"data\\TEXTURE\\UI\\TUTO\\tutosankaku.png"		//  �`���[�g���A���̑�����@�E��
#define	TEXTURE_TUTO_009		"data\\TEXTURE\\UI\\TUTO\\tutooperation.png"	//  �`���[�g���A���̑�����@
#define	TEXTURE_TUTO_010		"data\\TEXTURE\\UI\\TUTO\\tutoneed.png"			//  �`���[�g���A���̑�����@����Ȃ�
#define	TEXTURE_BOTTON_ENTER	"data\\TEXTURE\\UI\\BUTTON\\PRESSENTER.png"		//  HP�Q�[�W�e�N�X�`��
//	�Q�[���I�[�o�[
#define TEXTURE_OVER_000	"data\\TEXTURE\\UI\\GAMEOVER\\redbg.png"			//  �Q�[���I�[�o�[�w�i
#define TEXTURE_OVER_001	"data\\TEXTURE\\UI\\GAMEOVER\\oversel000.png"		//  �Q�[���I�[�o�[�I��[1]
#define TEXTURE_OVER_002	"data\\TEXTURE\\UI\\GAMEOVER\\oversel001.png"		//  �Q�[���I�[�o�[�w�i[2]

// ���U���g[ �Q�[���I�[�o�[ ]
#define TEXTURE_RESULT_000	"data\\TEXTURE\\UI\\RESULT\\GAMEOVER\\missionfailed.png"	//  missionfilede

// ���U���g[ �Q�[���N���A]
#define TEXTURE_RESULT_001	"data\\TEXTURE\\UI\\RESULT\\GAMECLEAR\\missionclear.png"		//  missionfilede

//	�Q�[���N���A���̕���
#define	TEXTURE_CLEARTXST_000	"data\\TEXTURE\\UI\\CLEAR\\clear000.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_001	"data\\TEXTURE\\UI\\CLEAR\\clear001.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_002	"data\\TEXTURE\\UI\\CLEAR\\clear002.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_003	"data\\TEXTURE\\UI\\CLEAR\\clear003.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_004	"data\\TEXTURE\\UI\\CLEAR\\clear004.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_005	"data\\TEXTURE\\UI\\CLEAR\\clear005.png"		// �Q�[���N���A���̕���������1
#define	TEXTURE_CLEARTXST_006	"data\\TEXTURE\\UI\\CLEAR\\clear006.png"		// �Q�[���N���A���̕���������1

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CUI::m_pTexture[UI_TEXMAX] = {};			// �e�N�X�`�����ւ̃|�C���^
CManager::MODE		CUI::m_mode = CManager::MODE_NONE;			//	�Q�[���̃��[�h
int					CUI::m_nNumSelectMode = 0;					//	�Z���N�g�ԍ�
bool				CUI::m_bTutoEnd = false;					//	�`���[�g���A�����I��������ǂ���
int					CUI::m_nNextTxst = 0;						//	�`���[�g���A���̕\�L�ݒ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUI::CUI() : CScene2D(CScene::PRIORITY_UI, CScene::OBJTYPE_UI)
{
	m_nType = 0;								//	���
	m_nCounterAnim = 0;							//	�A�j���[�V�����p�J�E���^�[
	m_nPatternAnim = 0;							//	�A�j���[�V�����p�^�[��
	m_sizeOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�����̑傫���̈ʒu
	m_bFlash = false;								//	�_�ł��Ȃ�
	m_bPressButton = false;						//	�{�^�����������ǂ�����
	m_fFrameValue = 0;							//	�Z���N�g�ԍ��̑傫���̒l
	m_nNumSelectMode = 0;						//	�Z���N�g�̔ԍ�
	//m_nNextTxst = 0;							//	�`���[�g���A���̕\�L�ݒ�
	m_nCutTuto = 0;								//	�`���[�g���A���̃J�E���^�[
	m_bSize = false;							//	�傫���̕ω�
	m_nPlayerLife = 0;							//	�v���C���[�̗̑�
	m_nPlayerLifeOld = 0;						//	�v���C���[�̗̑͂̕ۑ�
	m_nPlayerLifeMax = 0;						//	�v���C���[�̗̑͂̍ő�
	m_Bullet3D = NULL;							//	�e3D
	m_nStealthLifeMax = 0;						//	�v���C���[�̃X�e���X�̎����ő�l
	m_nStealthCut = 0;							//	�v���C���[�̃X�e���X��
	m_nPlayerSquat = false;						//	�v���C���[�̃X�e���X���
	m_nStealthLife = 0;							//	�v���C���[�̃X�e���X�̎���
	m_InitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�����̈ʒu
	m_bTutoOperation = false;					//	�`���[�g���A���̑�������`�悷�邩���Ȃ���
	m_bColChange = false;						//	�F��ς��邩�ǂ���
	m_nDashLifeMax = 0;							//	�v���C���[�̃_�b�V���̎����ő�
	m_nDashLife = 0;							//	�v���C���[�̃_�b�V���̎����ő�
	m_nPlayerDash = false;						//	�_�b�V�����Ă��邩�ǂ���
	m_nDashCut = 0;								//	�v���C���[�̃_�b�V���̃J�E���^�[
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUI::~CUI()
{

}
//=============================================================================
// ���[�h����
//=============================================================================
HRESULT CUI::Load(CManager::MODE mode)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���

	//	�Q�[���̐ݒ�
	m_mode = mode;
	switch (m_mode)
	{
	case CManager::MODE_TITLE://	�^�C�g��
		 //	�^�C�g�����S001
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE000, &m_pTexture[0]);		//	�^�C�g�����S000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE001, &m_pTexture[6]);		//	�^�C�g�����S001
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE002, &m_pTexture[7]);		//	�^�C�g�����S002
		//	PRESS BOTTAN
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);	//	PRESSENTER
		break;
	case CManager::MODE_SELECTMODE://	�Z���N�g
								   //	�Z���N�g���[�h
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELECTMODEBG, &m_pTexture[12]);				//	�w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEGAMEMODE, &m_pTexture[13]);			//	�Q�[�����[�h
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEGAMEMODETXST, &m_pTexture[14]);		//	�Q�[�����[�h����
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODECREDIT, &m_pTexture[15]);				//	�N���W�b�g
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODECREDITTXST, &m_pTexture[16]);			//	�N���W�b�g����
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODETITLERETURE, &m_pTexture[17]);		//	�^�C�g����
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODETITLERETURETXST, &m_pTexture[18]);	//	�^�C�g���֕���
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES00, &m_pTexture[19]);				//	���̕����\�L
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES01, &m_pTexture[20]);				//	���̕����\�L
		D3DXCreateTextureFromFile(pDevice, TEXTURE_SELMODEDES02, &m_pTexture[21]);				//	���̕����\�L
																								//	PRESS BOTTAN
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);	//	PRESSENTER
		break;
	case CManager::MODE_GAMETUTO:
		//	�`���[�g���A��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_BG, &m_pTexture[22]);				//	�`���[�g���A���w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_000, &m_pTexture[23]);				//	�`���[�g���A������1
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_001, &m_pTexture[24]);				//	�`���[�g���A������2
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_002, &m_pTexture[25]);				//	�`���[�g���A������3
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_003, &m_pTexture[26]);				//	�`���[�g���A������4
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_004, &m_pTexture[27]);				//	�`���[�g���A������5
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_005, &m_pTexture[28]);				//	�`���[�g���A������6
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_006, &m_pTexture[29]);				//	�`���[�g���A������7
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_007, &m_pTexture[30]);				//	�`���[�g���A��������@
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_008, &m_pTexture[31]);				//	�`���[�g���A���E��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_009, &m_pTexture[36]);				//	�`���[�g���A��������@
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_010, &m_pTexture[37]);				//	�`���[�g���A�����������Ȃ�
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HP�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP���A�C�R��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	�e�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H��֒e�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	�X�e���X�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	�X�e���X�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	�X�e���XUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	�_�b�V���̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	�X�e���XUI
		//	�|�[�Y
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause�w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause�I��[ 1�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause�w�i[ 2�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause�w�i[ 3�� ]

		//	�Q�[���I�[�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	�Q�[���I�[�o�[�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	�Q�[���I�[�o�[�I��[��蒼��]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	�Q�[���I�[�o�[�̔w�i[������߂�]


		break;
	case CManager::MODE_GAMESTAGE000://	�X�e�[�W1
		//	�Q�[��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HP�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP���A�C�R��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	�e�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H��֒e�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	H��֒e�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	�X�e���XUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	�_�b�V���̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	�X�e���XUI

		//	�|�[�Y
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause�w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause�I��[ 1�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause�w�i[ 2�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause�w�i[ 3�� ]

		//	�Q�[���I�[�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	�Q�[���I�[�o�[�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	�Q�[���I�[�o�[�I��[��蒼��]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	�Q�[���I�[�o�[�̔w�i[������߂�]

	case CManager::MODE_GAMESTAGE002:
		//	�Q�[��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME000, &m_pTexture[1]);				//	HP�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME001, &m_pTexture[2]);				//	HP���A�C�R��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME002, &m_pTexture[3]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME003, &m_pTexture[4]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME004, &m_pTexture[32]);				//	�e�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME005, &m_pTexture[33]);				//	H��֒e�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME006, &m_pTexture[34]);				//	H��֒e�̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME007, &m_pTexture[35]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	�X�e���XUI

		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME009, &m_pTexture[51]);				//	�_�b�V���̉摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME010, &m_pTexture[52]);				//	HP�Q�[�W
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME011, &m_pTexture[53]);				//	�X�e���XUI
		//	�|�[�Y
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSEBG, &m_pTexture[8]);				//	Pause�w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL000, &m_pTexture[9]);			//	Pause�I��[ 1�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL001, &m_pTexture[10]);			//	Pause�w�i[ 2�� ]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSESEL002, &m_pTexture[11]);			//	Pause�w�i[ 3�� ]
		//	�Q�[���I�[�o�[
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_000, &m_pTexture[39]);				//	�Q�[���I�[�o�[�̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_001, &m_pTexture[40]);				//	�Q�[���I�[�o�[�I��[��蒼��]
		D3DXCreateTextureFromFile(pDevice, TEXTURE_OVER_002, &m_pTexture[41]);				//	�Q�[���I�[�o�[�̔w�i[������߂�]
		//	�Q�[���N���A���̕����o��
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_BG, &m_pTexture[22]);				//	 �����̔w�i
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_000, &m_pTexture[43]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_001, &m_pTexture[44]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_002, &m_pTexture[45]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_003, &m_pTexture[46]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_004, &m_pTexture[47]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_005, &m_pTexture[48]);			//	�N���A���̕���000
		D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEARTXST_006, &m_pTexture[49]);			//	�N���A���̕���000

		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_007, &m_pTexture[30]);				//	�`���[�g���A��������@
		D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTO_008, &m_pTexture[31]);				//	�`���[�g���A���E��
		break;
	case CManager::MODE_OVER:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	�����w�i�摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);			//	PRESSENTER
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_000, &m_pTexture[42]);			//	missionfilede
		break;
	case CManager::MODE_CLEAR:
		D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME008, &m_pTexture[38]);				//	�����w�i�摜
		D3DXCreateTextureFromFile(pDevice, TEXTURE_BOTTON_ENTER, &m_pTexture[5]);			//	PRESSENTER�@
		D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULT_001, &m_pTexture[50]);			//	missionfilede
		break;
	}

	return S_OK;
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CUI::Unload(void)
{
	for (int nCntTex = 0; nCntTex < UI_TEXMAX; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{// NULL�̏ꍇ
		 // �e�N�X�`���̐���
			m_pTexture[nCntTex]->Release();		// ���
			m_pTexture[nCntTex] = NULL;			// NULL��
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CUI *CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col ,D3DXVECTOR2 uv, int nType)
{
	CUI *pUI = {};				// Ui�|�C���^

	if (pUI == NULL)
	{// NULL�̏ꍇ// �������m��
		pUI = new CUI;
		if (pUI != NULL)
		{// NULL�ȊO�̏ꍇ
			pUI->Init(pos, size, col, uv, nType);			// ����������
		}
	}
	return pUI;
}

//=============================================================================
// UI�쐬���郂�[�h
//=============================================================================
void CUI::CreateMode(CManager::MODE mode)
{
	m_mode = mode;	//���[�h�̓���
	switch (mode)
	{
	case CManager::MODE_TITLE://	�^�C�g��	-------------------------------------------------------------------------------------------------------------------------------------
		//	�^�C�g�����S000
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(350.0f, 120.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 0);
		//	�^�C�g�����S001
		CUI::Create
		(D3DXVECTOR3(200, 300, 0.0f), D3DXVECTOR3(250.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 6);
		//	�^�C�g�����S002
		CUI::Create
		(D3DXVECTOR3(1100, 460, 0.0f), D3DXVECTOR3(250.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 7);

		//	PRESS ENTER
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXVECTOR3(200.0f,50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);

		break;
	case  CManager::MODE_SELECTMODE://  �Z���N�g���[�h	-------------------------------------------------------------------------------------------------------------------------------

		//	�w�i
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 12);
		//	�Q�[�����[�h
		CUI::Create
		(D3DXVECTOR3(400, 330, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 13);
		//	�Q�[�����[�h����
		CUI::Create
		(D3DXVECTOR3(350, 370, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 14);
		//	�N���W�b�g
		CUI::Create
		(D3DXVECTOR3(850, 250, 0.0f), D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 15);
		//	�N���W�b�g����
		CUI::Create
		(D3DXVECTOR3(850, 320, 0.0f), D3DXVECTOR3(120.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 16);
		//	�^�C�g����
		CUI::Create
		(D3DXVECTOR3(770, 500, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 17);
		//	�^�C�g���֕���
		CUI::Create
		(D3DXVECTOR3(670, 500, 0.0f), D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 18);
		//	���̕����\�L00
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2-100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 19);
		//	���̕����\�L01
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 20);
		//	���̕����\�L02
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 650, 0.0f), D3DXVECTOR3(400.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 21);
		//	PRESS ENTER
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2+450, SCREEN_HEIGHT / 2 + 300, 0.0f), D3DXVECTOR3(150.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);
		break;
	case CManager::MODE_GAMETUTO://		�Q�[���`���[�g���A��		---------------------------------------------------------------------------------------------------------
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP�w�w�i
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HP�Q�[�W
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP�E�A�C�R��
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// �e�̔w�i�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// ��֒e�̉摜�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealth�̔w�i�@]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	Stealth�Q�[�WI�@]
		(D3DXVECTOR3(195.0f, 70.0f,0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealth�̑��̉摜�@]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// �_�b�V���̔w�i�@]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	�_�b�V���Q�[�WI�@]
		(D3DXVECTOR3(195.0f,85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// �_�b�V���̉摜�@]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);

		if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
		{//	�`���[�g���A���X�e�[�W�������ꍇ
		// �`���[�g���A��--------------------------------------------------------------------------------------------------------------------------------------------------|
			CUI::Create//	�`���[�g���A���q�w�i
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXVECTOR3(340.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 22);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 23);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 24);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 45.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 25);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 45.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 26);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 27);
			CUI::Create// �`���[�g���A��UI[ �����@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 35.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 28);
			CUI::Create// �`���[�g���A��UI[ �������@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 125, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 29);
			CUI::Create// �`���[�g���A��UI[ ������@�@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 30);
			CUI::Create// �`���[�g���A��UI[ ���@]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 31);
			CUI::Create// �`���[�g���A��UI[��������L�[�{�[�h�p�b�h]
			(D3DXVECTOR3(SCREEN_WIDTH / 2 +420, SCREEN_HEIGHT / 2-100, 0.0f), D3DXVECTOR3(0.0f, 170.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 36);
			CUI::Create// �`���[�g���A��UI[�����������Ȃ�]
			(D3DXVECTOR3(1100.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 37);
		}
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause�I��[ 3�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// �Q�[���I�[�o�[UI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// �Ԃ��w�i
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// �Q�[���I�[�o�[�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// �Q�[���I�[�o�[�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		break;
	case CManager::MODE_GAMESTAGE000://		�Q�[���X�e�[�W1		-----------------------------------------------------------------------------------------
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP�w�w�i
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HP�Q�[�W
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP�E�A�C�R��
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// �e�̔w�i�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// ��֒e�̉摜�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealth�̔w�i�@]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	Stealth�Q�[�WI�@]
		(D3DXVECTOR3(195.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealth�̑��̉摜�@]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// �_�b�V���̔w�i�@]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	�_�b�V���Q�[�WI�@]
		(D3DXVECTOR3(195.0f, 85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// �_�b�V���̉摜�@]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause�I��[ 3�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// �Q�[���I�[�o�[UI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// �Ԃ��w�i
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// �Q�[���I�[�o�[�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// �Q�[���I�[�o�[�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+100, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		break;
	case CManager::MODE_GAMESTAGE002://		�Q�[���X�e�[�W2		-----------------------------------------------------------------------------------------
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH, 0.0f + 20, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	HP�w�w�i
		(D3DXVECTOR3(160.0f, 40.0f, 0.0f), D3DXVECTOR3(140.0f, 26.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 1);
		CUI::Create//	HP�Q�[�W
		(D3DXVECTOR3(194.0f, 40.0f, 0.0f), D3DXVECTOR3(102.5f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 3);
		CUI::Create	//	HP�E�A�C�R��
		(D3DXVECTOR3(50.0f, 40.0f, 0.0f), D3DXVECTOR3(25.0f, 25.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 2);
		CUI::Create// �e�̔w�i�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 80, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(80.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create// ��֒e�̉摜�@]
		(D3DXVECTOR3(SCREEN_WIDTH - 40, (SCREEN_HEIGHT - 40), 0.0f), D3DXVECTOR3(32.0f, 32.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 33);
		CUI::Create// Stealth�̔w�i�@]
		(D3DXVECTOR3(193.0f, 70.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 32);
		CUI::Create//	Stealth�Q�[�WI�@]
		(D3DXVECTOR3(195.0f, 70.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 35);
		CUI::Create// Stealth�̑��̉摜�@]
		(D3DXVECTOR3(88.0f, 68.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 34);

		CUI::Create// �_�b�V���̔w�i�@]
		(D3DXVECTOR3(193.0f, 85.0f, 0.0f), D3DXVECTOR3(103.0f, 8.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 53);
		CUI::Create//	�_�b�V���Q�[�WI�@]
		(D3DXVECTOR3(195.0f, 85.0f, 0.0f), D3DXVECTOR3(100.0f, 6.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 52);
		CUI::Create// �_�b�V���̉摜�@]
		(D3DXVECTOR3(88.0f, 83.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 51);
		// Pause----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 250.0f, 0.0f), D3DXCOLOR(1.0f, 1.0, 1.0, 1.0), D3DXVECTOR2(1.0f, 1.0f), 8);
		CUI::Create// Pause�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 9);
		CUI::Create// Pause�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 10);
		CUI::Create// Pause�I��[ 3�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 130, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 11);
		// �Q�[���I�[�o�[UI----------------------------------------------------------------------------------------------------------------------------------------------------------|
		CUI::Create// �Ԃ��w�i
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.25f), D3DXVECTOR2(1.0f, 1.0f), 39);
		CUI::Create// �Q�[���I�[�o�[�I��[ 1�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 40);
		CUI::Create// �Q�[���I�[�o�[�I��[ 2�ԁ@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, 0.0f), D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 41);
		//	�N���A���̕���------------------------------------------------------------------------------------------------------
		CUI::Create//	�����̔q�w�i
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 0.0f), D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 22);
		CUI::Create//	����0��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 43);
		CUI::Create//	����1��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 44);
		CUI::Create//	����2��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 45);
		CUI::Create//	����3��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f, 55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 46);
		CUI::Create//	����4��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 47);
		CUI::Create//	����5��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 110, 0.0f), D3DXVECTOR3(0.0f,55.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 48);
		CUI::Create//	����6��
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 130, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 49);
		//	�N���A���̕����̏o�͕��@------------------------------------------------------------------------------------------------
		CUI::Create// ������UI[ ������@�@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 30);
		CUI::Create// ������UI[ ���@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 31);
		break;
	case CManager::MODE_OVER://	�I�[�o�[	-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create	// �����w�i�@]
		(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create	//	PRESS ENTER
		(D3DXVECTOR3(SCREEN_WIDTH / 2+400, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(150.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f),5);
		CUI::Create	//	MISSIONFILDE
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 450.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 42);
		break;
	case CManager::MODE_CLEAR://�N���A	-------------------------------------------------------------------------------------------------------------------------------------
		CUI::Create	// Stealth���Ă��鉉�o�@]
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 38);
		CUI::Create//	PRESS ENTER
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 5);
		CUI::Create	//	MISSIONCLEAR
		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 400.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0), D3DXVECTOR2(1.0f, 1.0f), 50);
		break;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR2 uv,int nType)
{
	CScene2D::SetInitAll(pos, size, col, uv);	// �����l�ݒ�
	CScene2D::Init();							// ����������
	CScene2D::BindTexture(m_pTexture[nType]);	// �e�N�X�`�����蓖��
	//	��ނ̐ݒ�
	m_nType = nType;
	//	�̂̑傫���̐ݒ�
	m_sizeOld = size;
	//	�����̈ʒu
	m_InitPos = pos;
	//	�Z���N�g�̔ԍ�
	m_nNumSelectMode = 0;
	//	�`���[�g���A���̕\�L�ݒ�
	m_nNextTxst = 0;
	//	�`���[�g���A�����I������ꍇ
	m_bTutoEnd = false;
	//	�`���[�g���A���̑�������`�悷�邩���Ȃ���
	m_bTutoOperation = false;
	if (m_mode == CManager::MODE_GAMETUTO || m_mode == CManager::MODE_GAMESTAGE000 || m_mode == CManager::MODE_GAMESTAGE002)
	{//	�Q�[�����[�h�̏ꍇ
		m_nPlayerLifeMax = CGame::GetPlayer()->GetLife();			//	�̗͂̍ő吔�̐ݒ�
		m_nStealthLifeMax = CGame::GetPlayer()->GetStealthLife();	//	�v���C���[�̃X�e���X�̎���
		m_nDashLifeMax =CGame::GetPlayer()->GetDashLife();			//	�v���C���[�̃_�b�V���̎����ő�
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUI::Uninit(void)
{
	CScene2D::Uninit();						// �I������
}

//=============================================================================
// �X�V����
//=============================================================================
void CUI::Update(void)
{
	CSound *pSound = CManager::GetSound();	//	�T�E���h�̎擾
	D3DXVECTOR3 pos = CScene2D::Getpos();	//	�ʒu�̎擾
	D3DXVECTOR3 size = CScene2D::Getsize();	//	�傫���̎擾
	D3DXCOLOR col = CScene2D::Getcol();		//	�F�̎擾
	D3DXVECTOR2 tex[4];						//	�e�N�X�`����UV4���_
	bool bPause = CGame::GetPause();		//	Pause�̎擾
	int nGameOver = CGame::GetOverNum();	//	Pause�̎擾
	int nPauseNum = CPause::GetNum();		//	�|�[�Y�̔ԍ��̎擾
	int nTutoNum = 0;						//	�`���[�g���A�����݂̐���
	m_nPlayerLifeOld = m_nPlayerLife;		//	�̗͂̐ݒ�
	if (m_mode == CManager::MODE_GAMETUTO || m_mode == CManager::MODE_GAMESTAGE000 || m_mode == CManager::MODE_GAMESTAGE002)
	{//	�Q�[�����[�h�������ꍇ
		m_nPlayerLife = CGame::GetPlayer()->GetLife();				//	�v���C���[�̗̑͂̎擾
		m_nPlayerSquat = CGame::GetPlayer()->GetSquat();			//	�v���C���[�̃X�e���X��Ԃ��ǂ���
		m_nPlayerDash= CGame::GetPlayer()->GetDash();				//	�v���C���[�̃_�b�V����Ԃ��ǂ���
		m_nStealthCut = CGame::GetPlayer()->GetStealthCut();		//	�v���C���[�̃X�e���X��Ԃɖ߂�J�E���^�[
		m_nStealthLife = CGame::GetPlayer()->GetStealthLife();		//	�v���C���[�̃X�e���X�̎���
		m_nDashCut = CGame::GetPlayer()->GetDashCut();				//	�v���C���[�̃_�b�V���̃J�E���^�[
		m_nDashLife = CGame::GetPlayer()->GetDashLife();			//	�v���C���[�̃_�b�V���̎����ő�
	}
	// �X�V����
	CScene2D::Update();
	m_nCounterAnim++;
	switch (m_mode)
	{
		//*****************************************************************************************
		//	�^�C�g��
		//*****************************************************************************************
	case CManager::MODE_TITLE:

		if (m_nType == 6)
		{//	�^�C�g�����S001
			if (m_nCounterAnim <= 180)
			{
				if (pos.x < 350)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.x += 4.0f;	//	�ʒu�����炷
				}
			}
			else if (m_nCounterAnim >= 180)
			{
				if (pos.y > 90)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.y -= 4.0f;	//	�ʒu�����炷
				}
				if (pos.x > 230)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.x -= 4.0f;	//	�ʒu�����炷
				}
			}
		}
		if (m_nType == 7)
		{//	�^�C�g�����S002
			if (m_nCounterAnim <= 180)
			{
				if (pos.x > 850)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.x -= 4.0f;	//	�ʒu�����炷
				}
			}
			else if (m_nCounterAnim >= 200)
			{
				if (pos.y < 620)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.y += 4.0f;	//	�ʒu�����炷
				}
				if (pos.x < 1040)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.x += 4.0f;	//	�ʒu�����炷
				}
			}
		}
		if (m_nType == 0)
		{//	�^�C�g�����S000
			if (m_nCounterAnim >= 200)
			{
				if (size.y > 20.0f)
				{//	�傫�����w��̒l�ȉ��������ꍇ�ȉ��������ꍇ
					size.y -= 4.0f;	//	�傫�������炷
				}
				if (size.x > 60.0f)
				{//	�傫�����w��̒l�ȉ��������ꍇ�ȉ��������ꍇ
					size.x -= 6.0f;	//	�傫�������炷
				}
				if (size.y <= 20.0f && size.x <= 60.0f)
				{
					col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
				}
				if (pos.y > 90)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.y -= 4.0f;	//	�ʒu�����炷
				}
				if (pos.x > 530)
				{//	�ʒu��400�ȉ��������ꍇ
					pos.x -= 4.0f;	//	�ʒu�����炷
				}
			}
		}
		if (m_nType == 0 || m_nType == 6 || m_nType == 7)
		{//	�^�C�g�����S�������ꍇ
			if (m_nCounterAnim >= 1400)
			{//	�J�E���^�[�����w��̒l�ȏソ�����ꍇ
				size = m_sizeOld;
				pos = m_InitPos;
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_nCounterAnim = 0;
			}
		}
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
				CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_A, 0) == true)
			{// �L�[�{�[�h�iENTER�j����͂�����
				m_bPressButton = true;
			}

		}
		if (m_nType == 5)
		{//	�v���X�G���^�[��������
			if (m_bPressButton == false)
			{//	�{�^���������Ă��Ȃ�
				if ((m_nCounterAnim % 60) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	�{�^����������
				if ((m_nCounterAnim % 6) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	�T�C�Y���Ȃ���
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	�T�C�Y�������̑�؂���C�߂�
				size.x = m_sizeOld.x;
			}
		}

		break;
		//*****************************************************************************************
		//	�Z���N�g���[�h
		//*****************************************************************************************
	case CManager::MODE_SELECTMODE:
		if (m_bPressButton == false)
		{//	�{�^�������Ă��Ȃ�
			if (CFade::GetFade() == CFade::FADE_NONE)
			{// �t�F�[�h���Ă��Ȃ����
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) || CManager::GetInputKeyboard()->GetTrigger(DIK_UP)
					|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_UP, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true)
				{	// W ���́@���L�[���������ꍇ
					m_nNumSelectMode = (m_nNumSelectMode + 2) % 3;
					m_nCounterAnim = 0;
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				}
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) || CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN)
					|| CManager::GetInputXPad()->GetTrigger(CInputXPad::XPADOTHER_STICK_L_DOWN, 0) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true)
				{	// S ���́@���L�[���������ꍇ
					m_nNumSelectMode = (m_nNumSelectMode + 1) % 3;
					m_nCounterAnim = 0;
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				}
			}
		}
		if (CFade::GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ����
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{//	�{�^����������
				m_bPressButton = true;
			}
		}
		if (m_bPressButton == true)
		{//	�{�^�����������ꍇ
			m_fFrameValue = 10.0f;
		}
		else if (m_bPressButton == false)
		{//	�{�^�����������ꍇ
			m_fFrameValue = 20.0f;
		}

		if (m_nNumSelectMode == 0)
		{//	�I��0�Ԃ������ꍇ
			if (m_nType == 14)
			{//	�^�C�g������
				if (m_nCounterAnim < m_fFrameValue)
				{//	20�t���[���ȉ��������ꍇ
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40�t���[���ȉ��������ꍇ
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60�t���[���ȉ��������ꍇ
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 19)
			{//	�^�C�g���̉��̐���//	�g��
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	����ȊO�������ꍇ
			if (m_nType == 19)
			{//	�^�C�g���̉��̐���//	�k��
				size.x = 0.0f;
				size.y = 0.0f;
			}
		}
		if (m_nNumSelectMode == 1)
		{//	�I��1�Ԃ������ꍇ
			if (m_nType == 16)
			{//	�N���W�b�g����
				if (m_nCounterAnim < m_fFrameValue)
				{//	20�t���[���ȉ��������ꍇ
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40�t���[���ȉ��������ꍇ
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60�t���[���ȉ��������ꍇ
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 20)
			{//	�N���W�b�g�̉��̐���//	�g��
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	����ȊO�������ꍇ
			if (m_nType == 20)
			{//	�^�C�g���̉��̐���//	�k��
				size.x = 0.0f;
				size.y = 0.0f;
			}
		}
		if (m_nNumSelectMode == 2)
		{//	�I��2�Ԃ������ꍇ
			if (m_nType == 18)
			{//	�^�C�g���֕���
				if (m_nCounterAnim < m_fFrameValue)
				{//	20�t���[���ȉ��������ꍇ
					size.x += 0.85f;
					size.y += 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 2)
				{//	40�t���[���ȉ��������ꍇ
					size.x -= 0.85f;
					size.y -= 0.85f;
				}
				else if (m_nCounterAnim < m_fFrameValue * 3)
				{//	60�t���[���ȉ��������ꍇ
					m_nCounterAnim = 0;
				}
			}
			if (m_nType == 21)
			{//	//	�^�C�g���ւ̐���//	�g��
				size.x = 400.0f;
				size.y = 50;
			}
		}
		else
		{//	����ȊO�������ꍇ
			if (m_nType == 21)
			{//	//	�^�C�g���ւ̐���//	�k��
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
		{//	�v���X�G���^�[��������
			if (m_bPressButton == false)
			{//	�{�^���������Ă��Ȃ�
				if ((m_nCounterAnim % 60) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	�{�^����������
				if ((m_nCounterAnim % 6) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	�T�C�Y���Ȃ���
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	�T�C�Y�������̑�؂���C�߂�
				size.x = m_sizeOld.x;
			}
		}

		break;
		//*****************************************************************************************
		//	�Q�[���`���[�g���A��
		//*****************************************************************************************
	case CManager::MODE_GAMETUTO:
		//------------------------------------------------------------------
		//	�`���[�g���A��
		//------------------------------------------------------------------
		if (CGame::GetStage() == CGame::STAGE_TUTORIAL)
		{//	�`���[�g���A���X�e�[�W�������ꍇ
			if (m_nNextTxst < 7)
			{
				m_nCutTuto++;			//	�`���[�g���A���J�E���^�[�̉��Z
				if (m_nCutTuto > 80)
				{//	�J�E���^�[�����̃t���[���������ꍇ
					if (m_nType == 22)
					{
						if ((CManager::GetInputKeyboard()->GetTrigger(DIK_Y) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true) && bPause == false)
						{//	Y�L�[�@&&Y�{�^�� &&Pause���Ă��Ȃ�
							m_nNextTxst += 1;	//	���̕���
							m_nCutTuto = 0;		//	�J�E���^�[�̏�����
							if (m_nNextTxst < 6)
							{// �����̏o�鉹
								pSound->PlaySound(CSound::SOUND_LABEL_SE_TEXTSE);
							}
						}
					}
					if (m_nType == 30)
					{//	������@UI�@�傫���̐ݒ�@
						size.x = 80.0f;
					}
					if ((m_nCutTuto % 30) == 0)
					{//	10�t���[����1�b��
						m_bSize = m_bSize ? false : true;		//	�傫���̕ω�

					}
					if (m_nType == 31)
					{//�@�傫���̐ݒ�@
						if (m_bSize == true)
						{//	�傫������O�p���
							size.x = 40.0f;
						}
						else if (m_bSize == false)
						{//	����������O�p���
							size.x = 0.0f;
						}
					}
				}
				else
				{//	�J�E���^�[�����̃t���[���ȉ��������ꍇ
					if (m_nType == 30)
					{//	������@UI�@�傫���̐ݒ�@
						size.x = 0.0f;
					}
					if (m_nType == 31)
					{//�傫���̐ݒ�@
						size.x = 0.0f;
					}
				}
				//	�`���[�g���A���̕��̒l�̐ݒ�
				nTutoNum = 23 + m_nNextTxst;
				if (m_nType == nTutoNum)
				{//	��ނ��ݒ肵���l�Ɠ����������ꍇ
					if (m_nType == 23)
					{//	�T�C�Y��ݒ肷��
						size.x = 130;
					}
					else if (m_nType == 27)
					{//	�T�C�Y��ݒ肷��
						size.x = 200;
					}
					else if (m_nType == 28)
					{//	�T�C�Y��ݒ肷��
						size.x = 230;
					}
					else if (m_nType == 29)
					{//	�T�C�Y��ݒ肷��
						size.x = 230;
					}
					else
					{//	�T�C�Y��ݒ肷��
						size.x = 220;
					}
				}
				for (int nCount = 23; nCount < 29; nCount++)
				{//�`���[�g���A���̐�����
					if (nTutoNum != nCount &&m_nType == nCount)
					{//	���ݕ\������Ă���ȊO�̃`���[�g���A����UI�̃T�C�Y������������
						size.x = 0;
					}
				}
				if (m_nNextTxst > 5 && bPause == false)
				{//	�c�[�ƃ��A���̕����\�L���I�������
					CScene::SetStartUp(0);
				}
				else if (m_nNextTxst < 5)
				{//	�`���[�g���A�����͍X�V�~�߂�
					CScene::SetStartUp(CScene::PRIORITY_PAUSE);
				}
			}
		}
		if (m_nNextTxst > 6)
		{//	�l�̐����ȏア�����ꍇ
			for (int nCount = 22; nCount < 32; nCount++)
			{//�`���[�g���A���̐�����
				if (m_nType == nCount)
				{
					Uninit();
				}
			}
			m_bTutoEnd = true;
		}

		//------------------------------------------------------------------
		//	�Q�[��UI
	    //------------------------------------------------------------------
		if (m_nType == 36)
		{//	������@
			if (m_bTutoEnd == true)
			{//	�������I������ꍇ
				if ((CManager::GetInputKeyboard()->GetTrigger(DIK_1) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0) == true))
				{//  R���́@1�L�[���������ꍇ
					m_bTutoOperation = m_bTutoOperation ? false : true;
				}
				if (m_bTutoOperation == false)
				{//	��������̕`��false�̏ꍇ�傫������
					size.x = 200;
				}
				else if (m_bTutoOperation == true)
				{//	��������̕`��true�̏ꍇ����������
					size.x = 0;
				}
			}
		}
		if (m_nType == 37)
		{//	������@����Ȃ�
			if (m_bTutoEnd == true)
			{//	�������I������ꍇ
				size.x = 140;
			}
		}
		if (m_nType == 3)
		{//	HP�Q�[�W��������
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	�ő�l��菬���������ꍇ
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x = m_InitPos.x;	//	�ʒu�����炷
					size.x = m_sizeOld.x;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
		}
		if (m_nType == 2)
		{//	�v���C���[�̃A�C�R��
			if (m_nPlayerLife > 0)
			{//	�v���C���[�̂g�o��0�ȏ�
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o��葽�������ꍇ
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	�F��Ԃ�����
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o�Ɠ����������ꍇ
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	�F��Ԃ�����
				}
			}

		}
		if (bPause == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 35)
			{//	Stealth�Q�[�WI
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerSquat == true)
					{//	�v���C���[���X�e���X���Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerSquat == false)
					{//	�v���C���[���X�e���X���Ă��Ȃ�
						if (m_nStealthLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����

						}
						else if (m_nStealthLife >= m_nStealthLifeMax)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}
					}
				}
			}
		}
		if (bPause == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 52)
			{//	�_�b�V���Q�[�W
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerDash == true)
					{//	�v���C���[���_�b�V�����Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerDash == false)
					{//	�v���C���[���_�b�V�����Ă��Ȃ�
						if (m_nDashLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}
					}
				}
			}
		}
		if (m_nType == 38)
		{//	�X�e���X��Ԃ̎��̉��o
			if (m_nPlayerSquat == true)
			{//	�v���C���[���X�e���X���Ă���ꍇ
				if (size.y < 60)
				{
					size.y += 2.0f;	//	�傫������
				}
			}
			else if (m_nPlayerSquat == false)
			{//	�v���C���[���X�e���X���Ă��Ȃ��ꍇ
				size.y = 0.0f;		//	����������

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	�Q�[���̏�Ԃ��Q�[���G���h�̏ꍇ
			if (m_nType == 39)
			{//	�Ԃ��w�i
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	�Q�[���I�[�o�[�I��[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	�Q�[���I�[�o�[�I��[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	�Q�[���I�[�o�[�̑I�𕶉�
				if (m_nType == 40 + nCutPause)
				{//	�I�����ڂ𖾂邭����
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
		//	Pause�̐ݒ�
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pause�̕`��BG
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pause�̑I��
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	�|�[�Y�̐�����
			if (m_nType == 9 + nCutPause)
			{//	�|�[�Y�I��1��
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
		//	�Q�[���X�e�[�W
		//*****************************************************************************************
	case CManager::MODE_GAMESTAGE000:
		//------------------------------------------------------------------
		//	�Q�[��UI
		//------------------------------------------------------------------
		if (m_nType == 3)
		{//	HP�Q�[�W��������
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	�ő�l��菬���������ꍇ
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x = m_InitPos.x;	//	�ʒu�����炷
					size.x = m_sizeOld.x;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
		}
		if (m_nType == 2)
		{//	�v���C���[�̃A�C�R��
			if (m_nPlayerLife > 0)
			{//	�v���C���[�̂g�o��0�ȏ�
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o��葽�������ꍇ
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	�F��Ԃ�����
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o�Ɠ����������ꍇ
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	�F��Ԃ�����
				}
			}

		}
		if (bPause == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 35)
			{//	Stealth�Q�[�WI
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerSquat == true)
					{//	�v���C���[���X�e���X���Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerSquat == false)
					{//	�v���C���[���X�e���X���Ă��Ȃ�
						if (m_nStealthLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����

						}
						else if (m_nStealthLife >= 300)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}
					}
				}
			}
		}
		if (bPause == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 52)
			{//	�_�b�V���Q�[�W
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerDash == true)
					{//	�v���C���[���_�b�V�����Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerDash == false)
					{//	�v���C���[���_�b�V�����Ă��Ȃ�
						if (m_nDashLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}
					}
				}
			}
		}
		if (m_nType == 38)
		{//	�X�e���X��Ԃ̎��̉��o
			if (m_nPlayerSquat == true)
			{//	�v���C���[���X�e���X���Ă���ꍇ
				if (size.y < 60)
				{
					size.y += 2.0f;	//	�傫������
				}
			}
			else if (m_nPlayerSquat == false)
			{//	�v���C���[���X�e���X���Ă��Ȃ��ꍇ
				size.y = 0.0f;		//	����������

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	�Q�[���̏�Ԃ��Q�[���G���h�̏ꍇ
			if (m_nType == 39)
			{//	�Ԃ��w�i
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	�Q�[���I�[�o�[�I��[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	�Q�[���I�[�o�[�I��[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	�Q�[���I�[�o�[�̑I�𕶉�
				if (m_nType == 40 + nCutPause)
				{//	�I�����ڂ𖾂邭����
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
		//	Pause�̐ݒ�
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pause�̕`��BG
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pause�̑I��
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	�|�[�Y�̐�����
			if (m_nType == 9 + nCutPause)
			{//	�|�[�Y�I��1��
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
		//	�Q�[���X�e�[�W002
		//*****************************************************************************************
	case CManager::MODE_GAMESTAGE002:
		//------------------------------------------------------------------
		//	�Q�[��UI
		//------------------------------------------------------------------
		if (m_nType == 3)
		{//	HP�Q�[�W��������
			if (m_nPlayerLifeMax > m_nPlayerLife)
			{//	�ő�l��菬���������ꍇ
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x -= m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
				if (m_nPlayerLifeOld < m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�ʒu�����炷
					size.x += m_sizeOld.x / m_nPlayerLifeMax;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
			else if (m_nPlayerLifeMax == m_nPlayerLife)
			{
				if (m_nPlayerLifeOld <= m_nPlayerLife)
				{//	�ۑ����Ă���l��菬���������ꍇ
					pos.x = m_InitPos.x;	//	�ʒu�����炷
					size.x = m_sizeOld.x;	//	�傫�������C�t�ɉ����Č��炷
				}
			}
		}
		if (m_nType == 2)
		{//	�v���C���[�̃A�C�R��
			if (m_nPlayerLife > 0)
			{//	�v���C���[�̂g�o��0�ȏ�
				if (m_nPlayerLifeOld > m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o��葽�������ꍇ
					col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//	�F��Ԃ�����
				}
				else if (m_nPlayerLifeOld == m_nPlayerLife)
				{//	�ۑ��̒l�����݂̂g�o�Ɠ����������ꍇ
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	�F��Ԃ�����
				}
			}
		}
		if (bPause == false && CGame::GetClear() == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 35)
			{//Stealth�Q�[�WI
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerSquat == true)
					{//	�v���C���[���X�e���X���Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nStealthLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerSquat == false)
					{//	�v���C���[���X�e���X���Ă��Ȃ�
						if (m_nStealthLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_STEALTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����

						}
						else if (m_nStealthLife >= m_nStealthLifeMax)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}
					}
				}
			}
		}
		if (bPause == false && CGame::GetClear() == false)
		{//	Pause���Ă��Ȃ�����
			if (m_nType == 52)
			{//	�_�b�V���Q�[�W
				if (CGame::GetPlayer() != NULL)
				{//	�v���C���[���g�p����Ă����ꍇ
					if (m_nPlayerDash == true)
					{//	�v���C���[���_�b�V�����Ă���ꍇ
						pos.x -= m_sizeOld.x / m_nDashLifeMax;	//	�ʒu�����炷
						size.x -= m_sizeOld.x / m_nDashLifeMax;	//	�傫�������炷
					}
					else if (m_nPlayerDash == false)
					{//	�v���C���[���_�b�V�����Ă��Ȃ�
						if (m_nDashLife == 0)
						{//	������0�̏ꍇ
							pos.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�ʒu�����炷
							size.x += m_sizeOld.x / MAX_DASHTHCUT;	//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//	�F��Ԃ�����
						}
						else if (m_nDashLife >= m_nDashLifeMax)
						{//	�傫���������ɂȂ����ꍇ
							pos.x = m_InitPos.x;					//	�ʒu�����炷
							size.x = m_sizeOld.x;					//	�傫���𑝂₷
							col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);//	�F��߂�
						}

					}
				}
			}
		}
		if (m_nType == 38)
		{//	�X�e���X��Ԃ̎��̉��o
			if (m_nPlayerSquat == true)
			{//	�v���C���[���X�e���X���Ă���ꍇ
				if (size.y < 60)
				{
					size.y += 2.0f;	//	�傫������
				}
			}
			else if (m_nPlayerSquat == false)
			{//	�v���C���[���X�e���X���Ă��Ȃ��ꍇ
				size.y = 0.0f;		//	����������

			}
		}
		if (CGame::GetGameState() == CGame::GAMESTATE_END)
		{//	�Q�[���̏�Ԃ��Q�[���G���h�̏ꍇ
			if (m_nType == 39)
			{//	�Ԃ��w�i
				size.x = SCREEN_WIDTH / 2;
			}
			if (m_nType == 40)
			{//	�Q�[���I�[�o�[�I��[1]
				size.x = 120;
			}
			if (m_nType == 41)
			{//	�Q�[���I�[�o�[�I��[2]
				size.x = 120;
			}
			for (int nCutPause = 0; nCutPause < 2; nCutPause++)
			{//	�Q�[���I�[�o�[�̑I�𕶉�
				if (m_nType == 40 + nCutPause)
				{//	�I�����ڂ𖾂邭����
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
		//	Pause�̐ݒ�
		//------------------------------------------------------------------
		if (m_nType == 8)
		{//	Pause�̕`��BG
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 250;
			}
		}

		if (m_nType == 10 || m_nType == 11 || m_nType == 9)
		{//	Pause�̑I��
			if (bPause == false)
			{//	Pause���Ă��Ȃ�����
				size.x = 0;
			}
			else
			{//	Pause���Ă���
				size.x = 180;
			}
		}
		for (int nCutPause = 0; nCutPause < 3; nCutPause++)
		{//	�|�[�Y�̐�����
			if (m_nType == 9 + nCutPause)
			{//	�|�[�Y�I��1��
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
		{//	�Q�[���N���A������
			m_nCutTuto++;			//	�`���[�g���A���J�E���^�[�̉��Z
			if (m_nType == 30)
			{//	������@UI�@�傫���̐ݒ�@
				size.x = 80.0f;
			}
			if ((m_nCutTuto % 30) == 0)
			{//	//	�傫���̕ω�
				m_bSize = m_bSize ? false : true;
			}
			if (m_nType == 31)
			{//�@�傫���̐ݒ�@
				if (m_bSize == true)
				{//	�傫������O�p���
					size.x = 40.0f;
				}
				else if (m_bSize == false)
				{//	����������O�p���
					size.x = 0.0f;
				}
			}
			if (m_nType == 22)
			{//	�����̔w�i
				size.x = 340.0f;			//	�傫���̕ύX
				if (m_nNextTxst < 6)
				{
					if (m_nCutTuto > 80)
					{//	�J�E���^�[�����̃t���[���������ꍇ
						if ((CManager::GetInputKeyboard()->GetTrigger(DIK_Y) == true || CManager::GetInputXPad()->GetTrigger(XINPUT_GAMEPAD_Y, 0) == true) && bPause == false)
						{//	Y�L�[�@&&Y�{�^�� &&Pause���Ă��Ȃ�
							m_nNextTxst += 1;	//	���̕���
							m_nCutTuto = 0;		//	�J�E���^�[�̏�����
							if (m_nNextTxst < 6)
							{// �����̏o�鉹
								pSound->PlaySound(CSound::SOUND_LABEL_SE_TEXTSE);
							}
							if (m_nNextTxst == 1)
							{//	�����~�߂�
								pSound->StopSound(CSound::SOUND_LABEL_BGM_STAGE3);
							}

						}
					}
				}
			}
			//	�`���[�g���A���̕��̒l�̐ݒ�
			nTutoNum = 43 + m_nNextTxst;
			if (m_nType == nTutoNum)
			{//	��ނ��ݒ肵���l�Ɠ����������ꍇ
				for (int nCount = 43; nCount < 50; nCount++)
				{//�`���[�g���A���̐�����
					if (m_nType == nCount)
					{//	�T�C�Y��ݒ肷��
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
			{//�`���[�g���A���̐�����
				if (nTutoNum != nCount &&m_nType == nCount)
				{//	���ݕ\������Ă���ȊO�̃`���[�g���A����UI�̃T�C�Y������������
					size.x = 0;
				}
			}
			if (m_nNextTxst > 6 && bPause == false)
			{//	�c�[�ƃ��A���̕����\�L���I�������
				CScene::SetStartUp(0);
			}
			else if (m_nNextTxst < 6)
			{//	�`���[�g���A�����͍X�V�~�߂�
				CScene::SetStartUp(CScene::PRIORITY_PAUSE);
			}
		}
		break;
	case CManager::MODE_OVER:	//	�Q�[���I�[�o�[
		if (m_nType == 42)
		{//	missionfild
			if (m_nCounterAnim <= 600)
			{//	600�t���[���ȉ��������ꍇ
				if (size.x <= 650)
				{//	�傫������
					size.x += 5.0f;
				}
			}
			else
			{//	600�t���[���ȏソ�����ꍇ
				m_nCounterAnim = 0;	//	����������
				size.x = 0.0f;
			}
			if ((m_nCounterAnim % 40) == 0)
			{//	60�b�œ_��
				m_bColChange = m_bColChange ? false : true;	//	�F�̕ύX
			}
			if (m_bColChange == false)
			{//	�F�̕ύX
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (m_bColChange == true)
			{//	�F�̕ύX
				col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
			}

		}
		if (m_nType == 5)
		{//	�v���X�G���^�[��������
			if (m_bPressButton == false)
			{//	�{�^���������Ă��Ȃ�
				if ((m_nCounterAnim % 60) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	�{�^����������
				if ((m_nCounterAnim % 6) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	�T�C�Y���Ȃ���
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	�T�C�Y�������̑�؂���C�߂�
				size.x = m_sizeOld.x;
			}
		}
		break;
	case CManager::MODE_CLEAR://�N���A	-------------------------------------------------------------------------------------------------------------------------------------
		if (m_nType == 5)
		{//	�v���X�G���^�[��������
			if (m_bPressButton == false)
			{//	�{�^���������Ă��Ȃ�
				if ((m_nCounterAnim % 60) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			else if (m_bPressButton == true)
			{//	�{�^����������
				if ((m_nCounterAnim % 6) == 0)
				{//	60�b�œ_��
					m_bFlash = m_bFlash ? false : true;

				}
			}
			if (m_bFlash == true)
			{//	�T�C�Y���Ȃ���
				size.x = 0;
			}
			else if (m_bFlash == false)
			{//	�T�C�Y�������̑�؂���C�߂�
				size.x = m_sizeOld.x;
			}
		}
		if (m_nType == 50)
		{//	missionfild
			if (m_nCounterAnim <= 600)
			{//	600�t���[���ȉ��������ꍇ
				if (size.x <= 650)
				{//	�傫������
					size.x += 5.0f;
				}
			}
			else
			{//	600�t���[���ȏソ�����ꍇ
				m_nCounterAnim = 0;	//	����������
				size.x = 0.0f;
			}
		}
		break;
	}

	CScene2D::Setpos(pos);				//	�ʒu�̐ݒ�
	CScene2D::Setsize(size);			//	�傫���̐ݒ�
	CScene2D::Setcol(col);				//	�F�̐ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();						// �`�揈��
}


