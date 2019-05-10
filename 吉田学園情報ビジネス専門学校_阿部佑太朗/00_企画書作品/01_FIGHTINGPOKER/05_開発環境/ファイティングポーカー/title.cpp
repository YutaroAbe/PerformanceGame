//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : ABE YUTARO
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "gamepad.h"
#include "player.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAME1	"data/TEXTURE/TITLE/TitleLogo000.png"				// �ǂݍ��ރe�N�X�`���̖��O�P
#define TITLE_TEXTURENAME2	"data/TEXTURE/TITLE/TitleLogo001.png"				// �ǂݍ��ރe�N�X�`���̖��O2
#define TITLE_TEXTURENAME3	"data/TEXTURE/TITLE/PressAnyBotton.png"				// �ǂݍ��ރe�N�X�`���̖��O�Q
#define TITLE_TEXTURENAME4	"data/TEXTURE/TITLE/lightning.png"					// �ǂݍ��ރe�N�X�`���̖��O�Q
#define TITLE_TEXTURENAME5	"data/TEXTURE/TITLE/KUROMEN.png"					// �ǂݍ��ރe�N�X�`���̖��O�Q
#define TITLE_TEXTURENAME6	"data/TEXTURE/TITLE/Trump.png"					    // �ǂݍ��ރe�N�X�`���̖��O�Q
#define TITLE_TEXTURENAME7	"data/TEXTURE/TITLE/sword.png"					    // �ǂݍ��ރe�N�X�`���̖��O�Q

//�^�C�g��BG---------------------------------------------------------------------------
#define TITLE_BG_POS_X_A	(SCREEN_WIDTH/2)				// ���S��X���W_A
#define TITLE_BG_POS_Y_A	(SCREEN_HEIGHT/2)				// ���S��Y���W_A
#define TITLE_BG_WIDTH_A	(SCREEN_WIDTH)					// ���S�̕�
#define TITLE_BG_HEIGHT_A	(SCREEN_HEIGHT)					// ���S�̍���
//�\�[�h------------------------------------------------------------------------------
#define TITLE_SWORD_POS_X	(400.0f)						// ���S��X���W_A
#define TITLE_SWORD_POS_Y	(250.0f)						// ���S��Y���W_A
#define TITLE_SWORD_WIDTH	(400.0f)						// ���S�̕�
#define TITLE_SWORDG_HEIGHT	(250.0f)						// ���S�̍���
//�t�@�C�e�B���O-----------------------------------------------------------------------
#define TITLE_LOGO_POS_X_A	(-200)							// ���S��X���W_A
#define TITLE_LOGO_POS_Y_A	(450.0f)						// ���S��Y���W_A
#define TITLE_LOGO_MOVE_MAX_A_X	(350.0f)					// ���S��x���W�̌��E
#define TITLE_LOGO_MOVE_MAX_A_Y	(280.0f)					// ���S��Y���W�̌��E
#define TITLE_LOGO_WIDTH_A	(750.0f)						// ���S�̕�
#define TITLE_LOGO_HEIGHT_A	(400.0f)						// ���S�̍���
//�|�[�J�[-----------------------------------------------------------------------------
#define TITLE_LOGO_POS_X_B	(1480)							// ���S��X���W_B
#define TITLE_LOGO_POS_Y_B	(350.0f)						// ���S��Y���W_B
#define TITLE_LOGO_MOVE_MAX_B_X	(890.0f)					// ���S��x���W�̌��E
#define TITLE_LOGO_MOVE_MAX_B_Y	(380.0f)					// ���S��Y���W�̌��E
#define TITLE_LOGO_WIDTH_B	(600.0f)						// ���S�̕�
#define TITLE_LOGO_HEIGHT_B	(400.0f)						// ���S�̍���
//�E�ҋ�炢����-----------------------------------------------------------------------
#define TITLE_LOGO_MOVE_X		(4.0f)						// ���S�̈ړ����x
#define TITLE_LOGO_MOVE_Y		(5.0f)						// ���S�̈ړ����x
//PressAnyBotton-----------------------------------------------------------------------
#define TITLE_ENTER_POS_X	(SCREEN_WIDTH / 2)				// �G���^�[��X���W
#define TITLE_ENTER_POS_Y	(600.0f)						// �G���^�[��Y���W
#define TITLE_ENTER_WIDTH	(400.0f)						// �G���^�[�̕�
#define TITLE_ENTER_HEIGHT	(120.0f)							// �G���^�[�̍���
#define TITLE_FLASH_ENTER	(60)							// �G���^�[�̓_�ŊԊu
//��-----------------------------------------------------------------------------------
#define TITLE_CLAW_MARK_POS_X	(SCREEN_WIDTH / 2)			// �܍���X���W
#define TITLE_CLAW_MARK_POS_Y	(350.0f)					// �܍���Y���W
#define TITLE_CLAW_MARK_WIDTH	(400.0f)					// �܍��̕�
#define TITLE_CLAW_MARK_HEIGHT	(300.0f)					// �܍��̍���
//�g�����v-----------------------------------------------------------------------------
#define TITLE_TRUNP_POS_X	(1150)					// �g�����v��X���W
#define TITLE_TRUNP_POS_Y	(380.0f)				// �g�����v��Y���W
#define TITLE_TRUNP_WIDTH	(200.0f)					// �g�����v�̕�
#define TITLE_TRUNP_HEIGHT	(200.0f)					// �g�����v�̍���
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��

	TITLETEX_BG_A = 0,			// ���S
	TITLETEX_SWORD,
	TITLETEX_LOGO_A,			// ���S
	TITLETEX_LOGO_B,			// ���S
	TITLETEX_ENTER,				// �G���^�[
	TITLETEX_CLAW_MARK,			//�@�܍�
	TITLETEX_TRUNP,				//�@�g�����v
	TITLETEX_MAX				// �e�N�X�`���̑���
} TITLETEX;

typedef enum
{// �e�N�X�`���̎��
	TITLETEX_ENTERCOL_000 = 0,	// ���S
	TITLETEX_ENTERCOL_001,		// ���S
	TITLETEX_ENTER_MAX			// �e�N�X�`���̑���
} TITLEENTERTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;			// �ʒu
	float fWidth;				// ��
	float fHeight;				// ����
	bool bFlash;				// �_�ł��邩�ǂ���
	bool bDraw;					// �`�悷�邩�ǂ���
} Title;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureTitle[TITLETEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTitle = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Title					g_aTitle[TITLETEX_MAX];					// �^�C�g���̏��
TITLEENTERTEX			g_aTitleEntreCol;						//�@�G���^�[�̃J���[�ύX
int						g_nCntFpsTitle;							// �o�ߎ���
int						g_nCntLogoStopTitle;					// �o�ߎ���
int						g_nPlaySpecialVoice = 0;
bool					g_bPlaySpecialVoice;
//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTitle(void)
{
	g_nPlaySpecialVoice = 0;
	g_bPlaySpecialVoice = false;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̏�����
	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		g_aTitle[nCntTex].bFlash = false;
		switch (nCntTex)
		{
		case TITLETEX_BG_A://BG
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_BG_POS_X_A, TITLE_BG_POS_Y_A, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_BG_WIDTH_A;
			g_aTitle[nCntTex].fHeight = TITLE_BG_HEIGHT_A;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_SWORD://�\�[�h
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_SWORD_POS_X, TITLE_SWORD_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_SWORD_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_SWORDG_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_LOGO_A://�E��
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_LOGO_POS_X_A, TITLE_LOGO_POS_Y_A, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_LOGO_WIDTH_A;
			g_aTitle[nCntTex].fHeight = TITLE_LOGO_HEIGHT_A;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_LOGO_B://��炢
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_LOGO_POS_X_B, TITLE_LOGO_POS_Y_B, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_LOGO_WIDTH_B;
			g_aTitle[nCntTex].fHeight = TITLE_LOGO_HEIGHT_B;
			g_aTitle[nCntTex].bDraw = true;
			break;
		case TITLETEX_ENTER://PressAnyBoyyon
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_ENTER_POS_X, TITLE_ENTER_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_ENTER_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_ENTER_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_CLAW_MARK://�܍�
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_CLAW_MARK_POS_X, TITLE_CLAW_MARK_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_CLAW_MARK_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_CLAW_MARK_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		case TITLETEX_TRUNP://�g�����v
			g_aTitle[nCntTex].pos = D3DXVECTOR3(TITLE_TRUNP_POS_X, TITLE_TRUNP_POS_Y, 0.0f);
			g_aTitle[nCntTex].fWidth = TITLE_TRUNP_WIDTH;
			g_aTitle[nCntTex].fHeight = TITLE_TRUNP_HEIGHT;
			g_aTitle[nCntTex].bDraw = false;
			break;
		}
	}
	//�ϐ��̏�����
	g_nCntFpsTitle = 0;
	g_nCntLogoStopTitle = 0;
	g_aTitleEntreCol = TITLETEX_ENTERCOL_000;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME1, &g_apTextureTitle[TITLETEX_LOGO_A]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME2, &g_apTextureTitle[TITLETEX_LOGO_B]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME3, &g_apTextureTitle[TITLETEX_ENTER]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME4, &g_apTextureTitle[TITLETEX_CLAW_MARK]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME5, &g_apTextureTitle[TITLETEX_BG_A]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME6, &g_apTextureTitle[TITLETEX_TRUNP]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAME7, &g_apTextureTitle[TITLETEX_SWORD]);

	// ���_���̍쐬
	MakeVertexTitle(pDevice);
	// �J�����̏���������
	InitCamera();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	// �e��I�u�W�F�N�g�̏I������
	UninitCamera();

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		if (g_apTextureTitle[nCntTex] != NULL)
		{
			g_apTextureTitle[nCntTex]->Release();
			g_apTextureTitle[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	// �X�y�V�����{�C�X�Đ�
#if 1
	if (g_bPlaySpecialVoice == false)
	{
		if (GetKeyboardTrigger(DIK_BACKSPACE) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START))
		{
			g_bPlaySpecialVoice = true;
			g_nPlaySpecialVoice = 60;
		}
	}
	if (g_bPlaySpecialVoice == true)
	{
 		g_nPlaySpecialVoice--;
		if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_BACK) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_BACK))
		{
			if (g_nPlaySpecialVoice >= 0)
			{
				PlaySound(SOUND_LABEL_SE_SPECIAL);
				g_bPlaySpecialVoice = false;
				g_nPlaySpecialVoice = 0;
			}
		}
	}
#endif
	VERTEX_2D *pVtx;
	FADE pFade = GetFade(); // �t�F�[�h�̎擾
	int nPressChange = 0;		//	PRESS�@A�@�Ɓ@PRESS�@ENTER�@�̓���ւ�

	if (g_aTitle[TITLETEX_LOGO_A].pos.x == TITLE_LOGO_MOVE_MAX_A_X  && g_aTitle[TITLETEX_LOGO_A].pos.y == TITLE_LOGO_MOVE_MAX_A_Y
		|| g_aTitle[TITLETEX_LOGO_B].pos.x == TITLE_LOGO_MOVE_MAX_B_X  && g_aTitle[TITLETEX_LOGO_B].pos.y == TITLE_LOGO_MOVE_MAX_B_Y)
	{// ���S����߂��ʒu�ɂ���ꍇ
		g_nCntFpsTitle++;

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_A))
		{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
			if (pFade != FADE_OUT)
			{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
				g_aTitle[TITLETEX_ENTER].bFlash = true;
				PlaySound(SOUND_LABEL_SE_DECISION_SE);
				SetFade(MODE_SELECT);
			}

		}

		for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
		{
			if (g_aTitle[nCntTex].bFlash == true)
			{

				if (g_nCntFpsTitle % 2 == 0)
				{// 2F�o�߂��Ƃ�
					g_aTitle[nCntTex].bDraw = g_aTitle[nCntTex].bDraw ? false : true;
				}
			}
			else
			{
				if (nCntTex == TITLETEX_ENTER)
				{// �G���^�[�̏ꍇ
					if (g_nCntFpsTitle % TITLE_FLASH_ENTER == 0)
					{// ��莞�Ԍo�߂��Ƃ�
						g_aTitle[nCntTex].bDraw = g_aTitle[nCntTex].bDraw ? false : true;
					}
				}
			}
		}
	}
	else
	{// ���S����߂��ʒu�ɂȂ��ꍇ
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_A) == true)
		{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
			g_aTitle[TITLETEX_LOGO_A].pos.x = TITLE_LOGO_MOVE_MAX_A_X;			// �E�҂�POSX�F400
			g_aTitle[TITLETEX_LOGO_A].pos.y = TITLE_LOGO_MOVE_MAX_A_Y;			// �E�҂�POSY�F220

			g_aTitle[TITLETEX_LOGO_B].pos.x = TITLE_LOGO_MOVE_MAX_B_X;			// ��炢��POSX:890
			g_aTitle[TITLETEX_LOGO_B].pos.y = TITLE_LOGO_MOVE_MAX_B_Y;			// ��炢��POSY:380

			g_aTitle[TITLETEX_ENTER].bDraw = true;								// PressAnyBotton���g�p������Ԃɂ���
			g_aTitle[TITLETEX_TRUNP].bDraw = true;								//
			g_aTitle[TITLETEX_SWORD].bDraw = true;								//
																				//g_aTitle[TITLETEX_CLAW_MARK].bDraw = true;							//�܂��g�p������Ԃɂ���
			g_aTitleEntreCol = TITLETEX_ENTERCOL_001;							//�܍����Â�����
		}

		if (g_aTitle[TITLETEX_LOGO_A].pos.x > TITLE_LOGO_MOVE_MAX_A_X && g_aTitle[TITLETEX_LOGO_B].pos.x < TITLE_LOGO_MOVE_MAX_B_X)
		{// ���S����߂��ʒu�𒴂����ꍇ�i�E��X��450�ȏ�ɂȂ�����:��炢840�ȉ��ɂȂ�����j

			g_nCntLogoStopTitle++;

			g_aTitle[TITLETEX_LOGO_A].pos.x = TITLE_LOGO_MOVE_MAX_A_X;		//X���W���ʒu��
			g_aTitle[TITLETEX_LOGO_B].pos.x = TITLE_LOGO_MOVE_MAX_B_X;		//X���W���ʒu��
			if (g_nCntLogoStopTitle > 5)
			{//5F�𒴂�����
			 //g_aTitle[TITLETEX_CLAW_MARK].bDraw = true;					//�܍����g�p����
			}
			if (g_nCntLogoStopTitle > 13)
			{//13F�𒴂�����
				g_aTitle[TITLETEX_ENTER].bDraw = true;						//PressAnyBotton���g�p������Ԃɂ���

				g_aTitle[TITLETEX_LOGO_A].pos.y = TITLE_LOGO_MOVE_MAX_A_Y;	//Y���W���ʒu��
				g_aTitle[TITLETEX_LOGO_B].pos.y = TITLE_LOGO_MOVE_MAX_B_Y;	//Y���W���ʒu��
				g_aTitleEntreCol = TITLETEX_ENTERCOL_001;
				g_aTitle[TITLETEX_TRUNP].bDraw = true;
				g_aTitle[TITLETEX_SWORD].bDraw = true;
			}

		}
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 8;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_A].fWidth / 2, -g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_A].fWidth / 2, -g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_A].fWidth / 2, g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_A].fWidth / 2, g_aTitle[TITLETEX_LOGO_A].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_A].pos;
		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_B].fWidth / 2, -g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_B].fWidth / 2, -g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[TITLETEX_LOGO_B].fWidth / 2, g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[TITLETEX_LOGO_B].fWidth / 2, g_aTitle[TITLETEX_LOGO_B].fHeight / 2, 0.0f) + g_aTitle[TITLETEX_LOGO_B].pos;

		switch (g_aTitleEntreCol)
		{
		case TITLETEX_ENTERCOL_000:
			g_aTitle[TITLETEX_LOGO_A].pos.x += TITLE_LOGO_MOVE_X;				//A��MOVE��
			g_aTitle[TITLETEX_LOGO_B].pos.x -= TITLE_LOGO_MOVE_X;				//B��MOVE��
																				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 8;
			// ���_�J���[�̐ݒ�
			pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();
			break;
		case TITLETEX_ENTERCOL_001:

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 8;
			// ���_�J���[�̐ݒ�
			pVtx[12].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[13].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[14].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);
			pVtx[15].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f);

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTitle->Unlock();
			break;
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTitle->Unlock();
	}
}


//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++)
	{
		if (g_aTitle[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTitle[nCntTex]);

			// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTitle
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < TITLETEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aTitle[nCntTex].fWidth / 2, -g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTex].fWidth / 2, -g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aTitle[nCntTex].fWidth / 2, g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTex].fWidth / 2, g_aTitle[nCntTex].fHeight / 2, 0.0f) + g_aTitle[nCntTex].pos;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
