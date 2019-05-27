////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �|�[�Y�̏��� [pause.cpp]
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
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{// ���
	D3DXVECTOR3 pos;			// ���S���W
	RULEBOOKTYPE nType;			// ���
	float fWidth;				// ��
	float fHeight;				// ����
} RulebookInfo;

typedef struct
{// �e�N�X�`��
	char *pFileName;
}RulebookTexture;

//******************************************************************************************************************************
// �}�N����`
//******************************************************************************************************************************
#define RULEBUUKSELECT_MAX	(6)
// �Z�b�g���[���֘A======================================================================================
#define SETRULE_WIDTH			(SCREEN_WIDTH)					// �Z�b�g���[���̉���
#define SETRULE_HEIGHT			(SCREEN_HEIGHT)					// �Z�b�g���[���̏c��
#define SETRULE_POS_X			(SCREEN_WIDTH / 2)				// �Z�b�g���[����X���W
#define SETRULE_POS_Y			(SCREEN_HEIGHT / 2)				// �Z�b�g���[����Y���W
// �v���X�G���^�[
#define SETRULE_PRESS_WIDTH		(300.0f)						// �Z�b�g���[���@�v���X�G���^�[�̉���
#define SETRULE_PRESS_HEIGHT	(100.0f)						// �Z�b�g���[���@�v���X�G���^�[�̏c��
#define SETRULE_PRESS_POS_X		(150.0f)						// �Z�b�g���[���@�v���X�G���^�[�̏c��
#define SETRULE_PRESS_POS_Y		(50.0f)						// �Z�b�g���[���@�v���X�G���^�[�̏c��

//���j���[�̃J���[========================================================================================
#define MENU_NORMAL_COLOR			(1.0f)							// �ʏ�̎��̃J���[
#define MENU_DEC_COLOR				(0.004f)						// �J���[�����炵�Ă����Ƃ��̒l
#define MENU_CHANGE_COLOR			(0.5f)							// ���炵���J���[�����̒l�𒴂�����
//���j���[�̑傫���[========================================================================================
#define RULEBOOK_WIDTH (400.0f)
#define RULEBOOK_HEIGHT (100.0f)

//******************************************************************************************************************************
// �O���[�o���ϐ�
//******************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureRulebook[PAUSETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRulebook = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
RULEBOOK g_aRulebook[PAUSETYPE_MAX];						// ���[���u�b�N�̃O���[�o���ϐ�
int g_nSelectBook;												// �Z���N�g�ԍ�
int g_nPressCounter;										// �Z���N�g�J�E���^
float g_SelectColorBook;										// �Z���N�g�J���[
bool g_bMenuBook;												// �g�p����Ă��邩�ǂ���

RulebookInfo g_aRulebookInfo[] =
{	//�ʒu�@���@��ށ@���@�傫��
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),BOOKTYPE_BG,SCREEN_WIDTH,SCREEN_HEIGHT },						// �w�i
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 100.0f, 0.0f),BOOKTYPE_FLOW,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },						// �Q�[���̗���
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 200.0f, 0.0f),BOOKTYPE_KEYBORD,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// �L�[�{�[�h����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 300.0f, 0.0f), BOOKTYPE_CONTROLLER,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },				// �R���g���[���[����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 400.0f, 0.0f), BOOKTYPE_ROLE,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// ���̐���
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, 500.0f, 0.0f), BOOKTYPE_CHARA,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// �L����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, 600.0f, 0.0f), BOOKTYPE_BACK,RULEBOOK_WIDTH,RULEBOOK_HEIGHT },					// �߂�
};
RulebookTexture g_aRulebookTex[PAUSETYPE_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },					// �ǂݍ��ރe�N�X�`��
	{ "data/TEXTURE/RULEBOOK/GameFlowContents.png" },		// �ǂݍ��ރe�N�X�`��1	�Q�[������
	{ "data/TEXTURE/RULEBOOK/OperateContentsKEY.png" },		// �ǂݍ��ރe�N�X�`��2	�L�[�{�[�h
	{ "data/TEXTURE/RULEBOOK/OperateContentsCON.png" },		// �ǂݍ��ރe�N�X�`��2	�R���g���[���[����
	{ "data/TEXTURE/RULEBOOK/CardRoleContents.png" },		// �ǂݍ��ރe�N�X�`��2	��
	{ "data/TEXTURE/RULEBOOK/CharacterRulesContents.png" },	// �ǂݍ��ރe�N�X�`��2	�L����
	{ "data/TEXTURE/RULEBOOK/Backselect.png" },				// �ǂݍ��ރe�N�X�`��2	�߂�
};

//==============================================================================================================================
// �����������i�|���S���j
//==============================================================================================================================
void InitRulebook(void)
{
	// ���[���̏���������
	InitRule();

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	for (int nTex = 0; nTex < PAUSETYPE_MAX; nTex++)
	{// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			g_aRulebookTex[nTex].pFileName,
			&g_apTextureRulebook[nTex]);
	}

	// �w�i�̏��̏�����
	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++)
	{
		g_aRulebook[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���W
		g_aRulebook[nCntPause].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_aRulebook[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �w�i�̈ړ���
		g_aRulebook[nCntPause].nType = 0;								// �^�C�v
		g_aRulebook[nCntPause].nCounterAnim = 0;						// �J�E���^�[
		g_aRulebook[nCntPause].nPatternAnim = 0;						// �p�^�[��No
		g_aRulebook[nCntPause].fWidth = 0;								// ��
		g_aRulebook[nCntPause].fHeight = 0;								// ����
		g_aRulebook[nCntPause].bUse = false;							// �g�p����Ă��邩�ǂ���
	}
	g_nSelectBook = 0;
	g_nPressCounter = 0;
	g_SelectColorBook = 1.0f;
	g_bMenuBook = false;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRulebook,
		NULL);

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[1].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[2].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
		pVtx[3].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// rhw�̐ݒ�
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].rhw = 1.0f;
		}

		if (nCntPause == 0)
		{
			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// ��ԏ�̐F�ȊO�͔����ɂ���
		 //���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRulebook->Unlock();

	// ���̃Z�b�g
	for (int nCntPause = 0; nCntPause < sizeof g_aRulebookInfo / sizeof(RulebookInfo); nCntPause++)
	{
		SetRulebook(g_aRulebookInfo[nCntPause].pos, g_aRulebookInfo[nCntPause].nType, g_aRulebookInfo[nCntPause].fWidth, g_aRulebookInfo[nCntPause].fHeight);
	}
}

//==============================================================================================================================
// �I�������i�|���S���j
//==============================================================================================================================
void UninitRulebook(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PAUSETYPE_MAX; nCntTex++)
	{
		if (g_apTextureRulebook[nCntTex] != NULL)
		{
			g_apTextureRulebook[nCntTex]->Release();
			g_apTextureRulebook[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffRulebook != NULL)
	{
		g_pVtxBuffRulebook->Release();
		g_pVtxBuffRulebook = NULL;
	}

	// ���[���̏�����
	UninitRule();
}

//==============================================================================================================================
// �X�V�����i�|���S���j
//==============================================================================================================================
void UpdateRulebook(void)
{
	VERTEX_2D*pVtx;

	FADE pFade = GetFade(); // �t�F�[�h�̎擾

							// ���[���̃|�C���^�̎擾
	RULE *pRule;
	pRule = GetRule();

	// ���[���̍X�V����
	UpdateRule();

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);

	if (g_bMenuBook == false)
	{
		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P, STICK_UP) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_2P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_2P, STICK_UP) == true)

		{//���L�[�̏���������Ƃ�
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		 // ���_�J���[�ݒ�
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

		{//���L�[�̉����������Ƃ�
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
		 // ���_�J���[�ݒ�
			pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			g_nSelectBook = (g_nSelectBook + 1) % RULEBUUKSELECT_MAX;
			g_SelectColorBook = MENU_NORMAL_COLOR;
		}
		// �������̏���
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

		// �|�[�Y�J�E���^�[�̏�����
		if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
		{
			g_nPressCounter = 0;
		}
		else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
		{
			g_nPressCounter = 0;
		}
		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		g_SelectColorBook -= MENU_DEC_COLOR;

		if (g_SelectColorBook < MENU_CHANGE_COLOR)
		{//�I�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			g_SelectColorBook = MENU_NORMAL_COLOR;
		}

		// ���_�J���[�ݒ�
		pVtx[g_nSelectBook * 4 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 1 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 2 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
		pVtx[g_nSelectBook * 4 + 3 + 4].col = D3DXCOLOR(g_SelectColorBook, g_SelectColorBook, g_SelectColorBook, 1.0f);
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{// �G���^�[���������Ƃ��� true false��؂�ւ���
		g_bMenuBook = g_bMenuBook ? false : true;

		if (g_bMenuBook == true)
		{
			PlaySound(SOUND_LABEL_SE_DECISION_SE);
			if (g_nSelectBook == RULE_FLOW)
			{// 1�Ԗڂ��I�΂ꂽ��	�Q�[���̗���
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_FLOW);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_KEYBORD)
			{// 2�Ԗڂ��I�΂ꂽ��	�L�[�{�[�h����
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_KEYBORD);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);

			}
			else if (g_nSelectBook == RULE_CONTROLLER)
			{// 3�Ԗڂ��I�΂ꂽ��	�R���g���[���[����
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CONTROLLER);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_ROLE)
			{// 4�Ԗڂ��I�΂ꂽ��	���̐���
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_ROLE);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == RULE_CHARA)
			{// 4�Ԗڂ��I�΂ꂽ��	�L��������
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CHARA);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelectBook == 5)
			{
				if (pFade != FADE_OUT)
				{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
					SetFade(MODE_SELECT);
				}
			}
		}
		else
		{//�g�p���Ă��Ȃ���Ԃɂ���
			g_bMenuBook = false;
			for (int nCount = 0; nCount < RULE_MAX; nCount++)
			{// ���[����S�Ďg�p���Ă��Ȃ���Ԃɂ���
				pRule[nCount].bUse = false;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRulebook->Unlock();
}
//==============================================================================================================================
// �`�揈���i�|���S���j
//==============================================================================================================================
void DrawRulebook(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
								// �f�o�C�X���擾����
	pDevice = GetDevice();

	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++)
	{
		if (g_aRulebook[nCntPause].bUse == true)
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffRulebook, 0, sizeof(VERTEX_2D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRulebook[g_aRulebook[nCntPause].nType]);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntPause * 4,
				2);
		}
	}
	// ���[���̕`�揈��
	DrawRule();
}
//==============================================================================================================================
// �|�[�Y�̐ݒ�
//==============================================================================================================================
void SetRulebook(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRulebook->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < PAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		if (g_aRulebook[nCntPause].bUse == false)
		{// �w�i���g�p����Ă��Ȃ�
			g_aRulebook[nCntPause].pos = pos;
			g_aRulebook[nCntPause].nType = nType;
			g_aRulebook[nCntPause].fWidth = fWidth;
			g_aRulebook[nCntPause].fHeight = fHeight;

			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[1].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), -(g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[2].pos = D3DXVECTOR3(-(g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;
			pVtx[3].pos = D3DXVECTOR3((g_aRulebook[nCntPause].fWidth / 2), (g_aRulebook[nCntPause].fHeight / 2), 0.0f) + g_aRulebook[nCntPause].pos;

			g_aRulebook[nCntPause].bUse = true;	// �g�p���Ă����Ԃɂ���
			break;
		}
	}
	g_pVtxBuffRulebook->Unlock();
}
