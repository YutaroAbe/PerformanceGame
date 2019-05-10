//=========================================================================================================================
//
// �|�[�Y���[���̏��� [rulePause.cpp]
// Author :  �ړc ��
//
//=========================================================================================================================
#include "rulePause.h"	// �|�[�Y
#include "input.h"		// �L�[�{�[�h
#include "game.h"		// �|�[�Y
#include"main.h"        // ���C��
#include "rule.h"
#include "battle.h"
#include "sound.h"
#include "player.h"
#include "gamepad.h"
//******************************************************************************************************************************
// �\���̒�`
//******************************************************************************************************************************
typedef struct
{// ���
	D3DXVECTOR3 pos;			// ���S���W
	RULEPAUSETYPE nType;			// ���
	float fWidth;				// ��
	float fHeight;				// ����
} RulePauseInfo;

typedef struct
{// �e�N�X�`��
	char *pFileName;
}RulePauseTexture;
//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define RULEPAUSESELECT_MAX (6)
// �e�N�X�`���֘A=====================================================================================
#define MAX_TEXTURE					(RULEPAUSETYPE_MAX)					// �e�N�X�`���̍ő吔
// �Z�b�g���[���֘A======================================================================================
#define SETRULE_WIDTH			(SCREEN_WIDTH)					// �Z�b�g���[���̉���
#define SETRULE_HEIGHT			(SCREEN_HEIGHT)					// �Z�b�g���[���̏c��
#define SETRULE_POS_X			(SCREEN_WIDTH / 2)				// �Z�b�g���[����X���W
#define SETRULE_POS_Y			(SCREEN_HEIGHT / 2)				// �Z�b�g���[����Y���W
// �v���X�G���^�[
#define SETRULE_PRESS_WIDTH		(200.0f)						// �Z�b�g���[���@�v���X�G���^�[�̉���
#define SETRULE_PRESS_HEIGHT	(100.0f)						// �Z�b�g���[���@�v���X�G���^�[�̏c��
#define SETRULE_PRESS_POS_X		(1000.0f)						// �Z�b�g���[���@�v���X�G���^�[�̈ʒu
#define SETRULE_PRESS_POS_Y		(700.0f)						// �Z�b�g���[���@�v���X�G���^�[�̈ʒu
//���j���[�̃J���[========================================================================================
#define RULEPAUSE_NORMAL_COLOR			(1.0f)							// �ʏ�̎��̃J���[
#define RULEPAUSE_DEC_COLOR				(0.004f)						// �J���[�����炵�Ă����Ƃ��̒l
#define RULEPAUSE_CHANGE_COLOR			(0.5f)							// ���炵���J���[�����̒l�𒴂�����
//���j���[�̑傫���[========================================================================================
#define RULEMENU_WIDTH (400.0f)
#define RULEMENU_HEIGHT (100.0f)


//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureRulePause[RULEPAUSETYPE_MAX] = {};// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRulePause = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
RULEPAUSEMENU g_aRulePause[RULEPAUSETYPE_MAX];					// �|�X�̏��
int g_nPressCount;
int g_nSelect;
bool g_bMenu;
float g_SelectColor;										// �Z���N�g�J���[

RulePauseInfo g_aRulePauseInfo[] =
{	//�ʒu�@���@��ށ@���@�傫��
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),RULEPAUSETYPE_BG,SCREEN_WIDTH - 100,SCREEN_HEIGHT-100 },		// �w�i
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 110.0f, 0.0f),RULEPAUSETYPE_FLOW,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// �Q�[���̗���
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 210.0f, 0.0f),RULEPAUSETYPE_KEYBORD,RULEMENU_WIDTH,RULEMENU_HEIGHT },					// �L�[�{�[�h����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 310.0f, 0.0f), RULEPAUSETYPE_CONTROLLER,RULEMENU_WIDTH,RULEMENU_HEIGHT },				// �R���g���[���[����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 410.0f, 0.0f), RULEPAUSETYPE_ROLE,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// ���̐���
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 510.0f, 0.0f), RULEPAUSETYPE_CHARA,RULEMENU_WIDTH,RULEMENU_HEIGHT },					// �L����
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 610.0f, 0.0f), RULEPAUSETYPE_BACK,RULEMENU_WIDTH,RULEMENU_HEIGHT },						// �߂�
};

RulePauseTexture g_aRulebookTex[RULEPAUSETYPE_MAX] =
{
	{ "data/TEXTURE/RULEBOOK/Bgbook.png" },					// �ǂݍ��ރe�N�X�`��
	{ "data/TEXTURE/RULEBOOK/GameFlowContents.png" },		// �ǂݍ��ރe�N�X�`��1
	{ "data/TEXTURE/RULEBOOK/OperateContentsKEY.png" },		// �ǂݍ��ރe�N�X�`��2
	{ "data/TEXTURE/RULEBOOK/OperateContentsCON.png" },		// �ǂݍ��ރe�N�X�`��2
	{ "data/TEXTURE/RULEBOOK/CardRoleContents.png" },		// �ǂݍ��ރe�N�X�`��2
	{ "data/TEXTURE/RULEBOOK/CharacterRulesContents.png" },	// �ǂݍ��ރe�N�X�`��2
	{ "data/TEXTURE/RULEBOOK/Backselect.png" },				// �ǂݍ��ރe�N�X�`��2	�߂�
};
//=========================================================================================================================
// �|�[�Y����������
//=========================================================================================================================
void InitRulePause(void)
{
	g_nSelect = 0;
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���[���̏���������
	InitRule();

	// ���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	for (int nTex = 0; nTex < RULEPAUSETYPE_MAX; nTex++)
	{// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			g_aRulebookTex[nTex].pFileName,
			&g_apTextureRulePause[nTex]);
	}

	//���̏�����
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++)
	{
		g_aRulePause[nCntPause].SelectNum = 0;
		g_aRulePause[nCntPause].SelectColor = 1.0f;
		g_aRulePause[nCntPause].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRulePause[nCntPause].bMenu = false;
		g_aRulePause[nCntPause].bRule = false;
		g_nPressCount = 0;
	}


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRulePause,
		NULL
	);



	//���_�o�b�t�@�����b�N
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[1].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[2].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
		pVtx[3].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;

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
	g_pVtxBuffRulePause->Unlock();

	// ���̃Z�b�g
	for (int nCntPause = 0; nCntPause < sizeof g_aRulePauseInfo / sizeof(RulePauseInfo); nCntPause++)
	{
		SetRulePause(g_aRulePauseInfo[nCntPause].pos, g_aRulePauseInfo[nCntPause].nType, g_aRulePauseInfo[nCntPause].fWidth, g_aRulePauseInfo[nCntPause].fHeight);
	}
}

//=========================================================================================================================
// �|�[�Y�I������
//=========================================================================================================================
void UninitRulePause(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
	 //�e�N�X�`���[�̔j��
		if (g_apTextureRulePause[nCount] != NULL)
		{
			g_apTextureRulePause[nCount]->Release();
			g_apTextureRulePause[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRulePause != NULL)
	{
		g_pVtxBuffRulePause->Release();
		g_pVtxBuffRulePause = NULL;
	}
	// ���[���̏�����
	UninitRule();
}

//=========================================================================================================================
// �|�[�Y�X�V����
//=========================================================================================================================
void UpdateRulePause(void)
{
	// ���[���̍X�V����
	UpdateRule();

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	RULE *pRule;
	pRule = GetRule();


	// ���_�o�b�t�@�����b�N
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	if (g_bMenu == false)
	{
		if (GetKeyboardTrigger(DIK_W) == true
			|| GetGamePadPovTrigger((int)PLAYER_CONTROL_1P, POV_UP) == true
			|| GetGamePadStickTrigger((int)PLAYER_CONTROL_1P,STICK_UP) == true)
		{//���L�[�̏���������Ƃ�
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
			SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		 // ���_�J���[�ݒ�
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
		{//���L�[�̉����������Ƃ�
			PlaySound(SOUND_LABEL_SE_SELECTITEM_SE);
			SelectVolume(SOUND_LABEL_SE_SELECTITEM_SE, 0.5f);
		 // ���_�J���[�ݒ�
			pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			g_nSelect = (g_nSelect + 1) % RULEPAUSESELECT_MAX;
			g_SelectColor = RULEPAUSE_NORMAL_COLOR;
		}
		// �������̏���
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

		// �|�[�Y�J�E���^�[�̏�����
		if (GetKeyboardRelease(DIK_S) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_DOWN) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_DOWN) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_DOWN))
		{
			g_nPressCount = 0;
		}
		else if (GetKeyboardRelease(DIK_W) == true || GetGamePadPovRelease((int)PLAYER_CONTROL_1P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_1P, STICK_UP) || GetGamePadPovRelease((int)PLAYER_CONTROL_2P, POV_UP) == true || GetGamePadStickRelease((int)PLAYER_CONTROL_2P, STICK_UP))
		{
			g_nPressCount = 0;
		}
		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		g_SelectColor -= RULEPAUSE_DEC_COLOR;

		if (g_SelectColor < RULEPAUSE_CHANGE_COLOR)
		{//�I�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			g_SelectColor = RULEPAUSE_NORMAL_COLOR;
		}

		// ���_�J���[�ݒ�
		pVtx[g_nSelect * 4 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 1 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 2 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
		pVtx[g_nSelect * 4 + 3 + 4].col = D3DXCOLOR(g_SelectColor, g_SelectColor, g_SelectColor, 1.0f);
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_RETURN) == true
		|| GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A) == true)
	{
		g_bMenu = g_bMenu ? false : true;

		if (g_bMenu == true)
		{
			if (g_nSelect == RULE_FLOW)
			{// 1�Ԗڂ��I�΂ꂽ��
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_FLOW);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_KEYBORD)
			{// 2�Ԗڂ��I�΂ꂽ��
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_KEYBORD);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_CONTROLLER)
			{// 3�Ԗڂ��I�΂ꂽ��
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetRule(D3DXVECTOR3(SETRULE_POS_X, SETRULE_POS_Y, 0.0f), SETRULE_WIDTH, SETRULE_HEIGHT, RULE_CONTROLLER);
				SetRule(D3DXVECTOR3(SETRULE_PRESS_POS_X, SETRULE_PRESS_POS_Y, 0.0f), SETRULE_PRESS_WIDTH, SETRULE_PRESS_HEIGHT, RULE_PRESSBUTTON);
			}
			else if (g_nSelect == RULE_ROLE)
			{// 4�Ԗڂ��I�΂ꂽ��
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
			{// 4�Ԗڂ��I�΂ꂽ��
				PlaySound(SOUND_LABEL_SE_CANCEL);
				SetPauseState(true);		// �|�[�Y�g�p
				SetRulePauseState(false);	// ���[���|�[�Y�s�g�p
				g_bMenu = false;
				g_nSelect = 0;
			}
		}
		else
		{
			g_bMenu = false;
			for (int nCount = 0; nCount < RULE_MAX; nCount++)
			{// ���[����S�Ďg�p���Ă��Ȃ���Ԃɂ���
				pRule[nCount].bUse = false;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffRulePause->Unlock();
}

//=========================================================================================================================
// �|�[�Y�`�揈��
//=========================================================================================================================
void DrawRulePause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�|�C���^

	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++)
	{
		if (g_aRulePause[nCntPause].bUse == true)
		{
			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource
			(0, g_pVtxBuffRulePause, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureRulePause[g_aRulePause[nCntPause].nType]);

			//�|�[�Y�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
		}
	}

	// ���[���̕`�揈��
	DrawRule();
}
//==============================================================================================================================
// �|�[�Y�̐ݒ�
//==============================================================================================================================
void SetRulePause(D3DXVECTOR3 pos, int nType, float fWidth, float fHeight)
{
	VERTEX_2D*pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRulePause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPause = 0; nCntPause < RULEPAUSETYPE_MAX; nCntPause++, pVtx += 4)
	{
		if (g_aRulePause[nCntPause].bUse == false)
		{// �w�i���g�p����Ă��Ȃ�
			g_aRulePause[nCntPause].pos = pos;
			g_aRulePause[nCntPause].nType = nType;
			g_aRulePause[nCntPause].fWidth = fWidth;
			g_aRulePause[nCntPause].fHeight = fHeight;

			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[1].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), -(g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[2].pos = D3DXVECTOR3(-(g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;
			pVtx[3].pos = D3DXVECTOR3((g_aRulePause[nCntPause].fWidth / 2), (g_aRulePause[nCntPause].fHeight / 2), 0.0f) + g_aRulePause[nCntPause].pos;

			g_aRulePause[nCntPause].bUse = true;	// �g�p���Ă����Ԃɂ���
			break;
		}
	}
	g_pVtxBuffRulePause->Unlock();
}

//=========================================================================================================================
// �|�[�Y�`�揈��
//=========================================================================================================================
bool GetbMenu(void)
{
	return g_aRulePause[0].bRule;
}
