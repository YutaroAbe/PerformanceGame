//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "gameover.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "light.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_TEXTURENAME1	"data/TEXTURE/GAMEOVER/gameover_g.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME2	"data/TEXTURE/GAMEOVER/gameover_a.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME3	"data/TEXTURE/GAMEOVER/gameover_m.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME4	"data/TEXTURE/GAMEOVER/gameover_e.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME5	"data/TEXTURE/GAMEOVER/gameover_o.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME6	"data/TEXTURE/GAMEOVER/gameover_v.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME7	"data/TEXTURE/GAMEOVER/gameover_e.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME8	"data/TEXTURE/GAMEOVER/gameover_r.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define GAMEOVER_TEXTURENAME9	"data/TEXTURE/GAMEOVER/PressAnyBotton000.png"		// �ǂݍ��ރe�N�X�`���̖��O�Q

//G-----------------------------------------------------------------------------------
#define GAMEOVER_G_POS_X	(90)								// ���S��X���W
#define GAMEOVER_G_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_G_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_G_HEIGHT (160.0f)								// ���S�̍���
//A-----------------------------------------------------------------------------------
#define GAMEOVER_A_POS_X	(240)								// ���S��X���W
#define GAMEOVER_A_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_A_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_A_HEIGHT (160.0f)								// ���S�̍���
//M-----------------------------------------------------------------------------------
#define GAMEOVER_M_POS_X	(400)								// ���S��X���W
#define GAMEOVER_M_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_M_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_M_HEIGHT (160.0f)								// ���S�̍���
//E-----------------------------------------------------------------------------------
#define GAMEOVER_E_POS_X	(550)								// ���S��X���W
#define GAMEOVER_E_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_E_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_E_HEIGHT (160.0f)								// ���S�̍���
//O-----------------------------------------------------------------------------------
#define GAMEOVER_O_POS_X	(700)								// ���S��X���W
#define GAMEOVER_O_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_O_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_O_HEIGHT (160.0f)								// ���S�̍���
//V-----------------------------------------------------------------------------------
#define GAMEOVER_V_POS_X	(850)								// ���S��X���W
#define GAMEOVER_V_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_V_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_V_HEIGHT (160.0f)								// ���S�̍���
//E-----------------------------------------------------------------------------------
#define GAMEOVER_E2_POS_X	(1000)								// ���S��X���W
#define GAMEOVER_E2_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_E2_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_E2_HEIGHT (160.0f)								// ���S�̍���
//R-----------------------------------------------------------------------------------
#define GAMEOVER_R_POS_X	(1150)								// ���S��X���W
#define GAMEOVER_R_POS_Y	(310.0f)							// ���S��Y���W
#define GAMEOVER_R_WIDTH	(160.0f)							// ���S�̕�
#define GAMEOVER_R_HEIGHT (160.0f)								// ���S�̍���

//��������
#define GAMEOVER_LOGO_MOVE		(2.0f)							// ���S�̈ړ����x
#define GAMEOVER_LOGO_MOVE_MAX	(250.0f)						// ���S��Y���W�̌��E

#define GAMEOVER_MOVE_A	(0.8f)							// ���S��Y���W
#define GAMEOVER_MOVE_B	(0.5f)							// ���S��Y���W

#define GAMEOVER_ENTER_POS_X	(SCREEN_WIDTH / 2)				// �G���^�[��X���W
#define GAMEOVER_ENTER_POS_Y	(550.0f)						// �G���^�[��Y���W
#define GAMEOVER_ENTER_WIDTH	(400.0f)						// �G���^�[�̕�
#define GAMEOVER_ENTER_HEIGHT	(80.0f)							// �G���^�[�̍���
#define GAMEOVER_FLASH_ENTER	(60)							// �G���^�[�̓_�ŊԊu

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��
	GAMEOVETEX_LOGO_G = 0,	// G
	GAMEOVETEX_LOGO_A,		// A
	GAMEOVETEX_LOGO_M,		// M
	GAMEOVETEX_LOGO_E,		// E
	GAMEOVETEX_LOGO_O,		// O
	GAMEOVETEX_LOGO_V,		// V
	GAMEOVETEX_LOGO_E2,		// E
	GAMEOVETEX_LOGO_R,		// R
	GAMEOVETEX_ENTER,		// �G���^�[
	GAMEOVETEX_MAX			// �e�N�X�`���̑���
}GAMEOVERTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ʒu
	float fWidth;			// ��
	float fHeight;			// ����
	bool bFlash;			// �_�ł��邩�ǂ���
	bool bDraw;				// �`�悷�邩�ǂ���
} GameOver;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureGameOver[GAMEOVETEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffGameOver = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
GameOver				g_aGameOver[GAMEOVETEX_MAX];				// �^�C�g���̏��
int						g_nCntFpsGameOver;							// �o�ߎ���
int g_nCntFpsOver;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̏�����
	for (int nCntTex = 0; nCntTex < GAMEOVETEX_MAX; nCntTex++)
	{
		g_aGameOver[nCntTex].bFlash = false;
		switch (nCntTex)
		{
		case GAMEOVETEX_LOGO_G:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_G_POS_X, GAMEOVER_G_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f,- 0.3f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_G_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_G_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_A:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_A_POS_X, GAMEOVER_A_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_A_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_A_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_M:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_M_POS_X, GAMEOVER_M_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_M_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_M_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_E:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_E_POS_X, GAMEOVER_E_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_E_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_E_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_O:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_O_POS_X, GAMEOVER_O_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_O_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_O_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_V:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_V_POS_X, GAMEOVER_V_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_V_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_V_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_E2:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_E2_POS_X, GAMEOVER_E2_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_E2_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_E2_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_LOGO_R:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_R_POS_X, GAMEOVER_R_POS_Y, 0.0f);
			g_aGameOver[nCntTex].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_R_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_R_HEIGHT;
			g_aGameOver[nCntTex].bDraw = true;
			break;
		case GAMEOVETEX_ENTER:
			g_aGameOver[nCntTex].pos = D3DXVECTOR3(GAMEOVER_ENTER_POS_X, GAMEOVER_ENTER_POS_Y, 0.0f);
			g_aGameOver[nCntTex].fWidth = GAMEOVER_ENTER_WIDTH;
			g_aGameOver[nCntTex].fHeight = GAMEOVER_ENTER_HEIGHT;
			g_aGameOver[nCntTex].bDraw = false;
			break;
		}
	}
	g_nCntFpsGameOver = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME1, &g_apTextureGameOver[GAMEOVETEX_LOGO_G]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME2, &g_apTextureGameOver[GAMEOVETEX_LOGO_A]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME3, &g_apTextureGameOver[GAMEOVETEX_LOGO_M]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME4, &g_apTextureGameOver[GAMEOVETEX_LOGO_E]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME5, &g_apTextureGameOver[GAMEOVETEX_LOGO_O]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME6, &g_apTextureGameOver[GAMEOVETEX_LOGO_V]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME7, &g_apTextureGameOver[GAMEOVETEX_LOGO_E2]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME8, &g_apTextureGameOver[GAMEOVETEX_LOGO_R]);
	D3DXCreateTextureFromFile(pDevice, GAMEOVER_TEXTURENAME9, &g_apTextureGameOver[GAMEOVETEX_ENTER]);

	// ���_���̍쐬
	MakeVertexGameOver(pDevice);

	//���C�g�̏���
	InitLight();
	//�J�����̏�����
	InitCamera();

}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitGameOver(void)
{
	UninitLight();
	// �J�����̏���������
	UninitCamera();
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < GAMEOVETEX_MAX; nCntTex++)
	{
		if (g_apTextureGameOver[nCntTex] != NULL)
		{
			g_apTextureGameOver[nCntTex]->Release();
			g_apTextureGameOver[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameOver != NULL)
	{
		g_pVtxBuffGameOver->Release();
		g_pVtxBuffGameOver = NULL;
	}

}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateGameOver(void)
{
	VERTEX_2D *pVtx;
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾

	for (int nCntTex = 0; nCntTex < GAMEOVETEX_MAX; nCntTex++)
	{
		g_nCntFpsOver++;

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true)
		{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
			if (pFade == FADE_NONE)
			{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
				PlaySound(SOUND_LABEL_SE000);
				g_aGameOver[GAMEOVETEX_ENTER].bFlash = true;
				SetFade(MODE_SELCT);
			}
		}
			if (g_aGameOver[nCntTex].bFlash == true)
			{
				if (g_nCntFpsOver % 2 == 0)
				{// 2F�o�߂��Ƃ�
					g_aGameOver[nCntTex].bDraw = g_aGameOver[nCntTex].bDraw ? false : true;
				}
			}
			else
			{
				if (nCntTex == GAMEOVETEX_ENTER)
				{// �G���^�[�̏ꍇ
					if (g_nCntFpsOver % 120 == 0)
					{// ��莞�Ԍo�߂��Ƃ�
						g_aGameOver[nCntTex].bDraw = g_aGameOver[nCntTex].bDraw ? false : true;
					}
				}
			}


		//G-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_G].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_G].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_A].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_G].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_G].move.y += GAMEOVER_MOVE_B;
			}

		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_G].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_G].move.y = 0.0f;
		}

		//A-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_A].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_A].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_M].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_A].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_A].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_A].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_A].move.y = 0.0f;
		}

		//M-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_M].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_M].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_E].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_M].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_M].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_M].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_M].move.y = 0.0f;
		}

		//E-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_E].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_E].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_O].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_E].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_E].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_E].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_E].move.y = 0.0f;
		}

		//O-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_O].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_O].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_V].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_O].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_O].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_O].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_O].move.y = 0.0f;
		}

		//V-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_V].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_V].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_E2].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_V].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_V].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_V].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_V].move.y = 0.0f;
		}

		//E2-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_E2].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_E2].move.y = 0.0f;

			g_aGameOver[GAMEOVETEX_LOGO_R].move.y -= GAMEOVER_MOVE_A;

			if (g_aGameOver[GAMEOVETEX_LOGO_E2].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_E2].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_E2].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_E2].move.y = 0.0f;
		}
		//R-----------------------------------------------------------
		if (g_aGameOver[GAMEOVETEX_LOGO_R].pos.y <= 200)
		{
			g_aGameOver[GAMEOVETEX_LOGO_R].move.y = 0.0f;

			if (g_aGameOver[GAMEOVETEX_LOGO_R].move.y == 0.0f)
			{
				g_aGameOver[GAMEOVETEX_LOGO_R].move.y += GAMEOVER_MOVE_B;
			}
		}
		else if (g_aGameOver[GAMEOVETEX_LOGO_R].pos.y >= 320)
		{
			g_aGameOver[GAMEOVETEX_LOGO_R].move.y = 0.0f;
		}

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffGameOver->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_G].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_G].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_G].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_G].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_G].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_G].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_G].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_G].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_G].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_G].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_G].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_G].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_A].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_A].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_A].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_A].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_A].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_A].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_A].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_A].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_A].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_A].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_A].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_A].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_M].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_M].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_M].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_M].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_M].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_M].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_M].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_M].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_M].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_M].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_M].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_M].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_E].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_E].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_E].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_E].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_E].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_E].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_E].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_E].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_O].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_O].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_O].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_O].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_O].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_O].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_O].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_O].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_O].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_O].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_O].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_O].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_V].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_V].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_V].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_V].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_V].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_V].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_V].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_V].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_V].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_V].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_V].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_V].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_E2].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_E2].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E2].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_E2].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_E2].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E2].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_E2].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_E2].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E2].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_E2].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_E2].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_E2].pos;

		pVtx += 4;
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_R].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_R].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_R].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_R].fWidth / 2, -g_aGameOver[GAMEOVETEX_LOGO_R].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_R].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[GAMEOVETEX_LOGO_R].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_R].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_R].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[GAMEOVETEX_LOGO_R].fWidth / 2, g_aGameOver[GAMEOVETEX_LOGO_R].fHeight / 2, 0.0f) + g_aGameOver[GAMEOVETEX_LOGO_R].pos;


		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffGameOver->Unlock();

		g_aGameOver[GAMEOVETEX_LOGO_G].pos.y += g_aGameOver[GAMEOVETEX_LOGO_G].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_A].pos.y += g_aGameOver[GAMEOVETEX_LOGO_A].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_M].pos.y += g_aGameOver[GAMEOVETEX_LOGO_M].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_E].pos.y += g_aGameOver[GAMEOVETEX_LOGO_E].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_O].pos.y += g_aGameOver[GAMEOVETEX_LOGO_O].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_V].pos.y += g_aGameOver[GAMEOVETEX_LOGO_V].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_E2].pos.y += g_aGameOver[GAMEOVETEX_LOGO_E2].move.y;
		g_aGameOver[GAMEOVETEX_LOGO_R].pos.y += g_aGameOver[GAMEOVETEX_LOGO_R].move.y;
	}

	UpdateLight();
	UpdateCamera();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawGameOver(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGameOver, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < GAMEOVETEX_MAX; nCntTex++)
	{
		if (g_aGameOver[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureGameOver[nCntTex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// �v���~�e�B�u�̎��
				, nCntTex * 4		// �J�n���钸�_�̃C���f�b�N�X
				, 2);				// �`�悷��v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGameOver(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAMEOVETEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffGameOver
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGameOver->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < GAMEOVETEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aGameOver[nCntTex].fWidth / 2, -g_aGameOver[nCntTex].fHeight / 2, 0.0f) + g_aGameOver[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aGameOver[nCntTex].fWidth / 2, -g_aGameOver[nCntTex].fHeight / 2, 0.0f) + g_aGameOver[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aGameOver[nCntTex].fWidth / 2, g_aGameOver[nCntTex].fHeight / 2, 0.0f) + g_aGameOver[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aGameOver[nCntTex].fWidth / 2, g_aGameOver[nCntTex].fHeight / 2, 0.0f) + g_aGameOver[nCntTex].pos;

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
	g_pVtxBuffGameOver->Unlock();
}
