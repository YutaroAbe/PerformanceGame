//=============================================================================
//
// �N���W�b�g���� [credit.cpp]
// Author : ABE YUTARO
//
//=============================================================================
#include "credit.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "player.h"
#include "gamepad.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CREDIT_TEXTURENAME_LOGO_1	"data/TEXTURE/CREDIT/CREDIT000.png"			// ���Ċ��
#define CREDIT_TEXTURENAME_LOGO_2	"data/TEXTURE/CREDIT/CREDIT001.png"			// �v���O���}�[
#define CREDIT_TEXTURENAME_LOGO_3	"data/TEXTURE/CREDIT/CREDIT002.png"			// �v�����i
#define CREDIT_TEXTURENAME_LOGO_4	"data/TEXTURE/CREDIT/CREDIT003.png"			// UI�f�U�C��
#define CREDIT_TEXTURENAME_LOGO_5	"data/TEXTURE/CREDIT/CREDIT004.png"			// ���f��
#define CREDIT_TEXTURENAME_LOGO_6	"data/TEXTURE/CREDIT/CREDIT005.png"			// �I�u�W�F�N�g
#define CREDIT_TEXTURENAME_LOGO_7	"data/TEXTURE/CREDIT/CREDIT006.png"			// ���[�V����
#define CREDIT_TEXTURENAME_LOGO_8	"data/TEXTURE/CREDIT/CREDIT007.png"			// �T�E���h
#define CREDIT_TEXTURENAME_LOGO_9	"data/TEXTURE/CREDIT/CREDIT008.png"			// �v���W�F�N�g���[�_�[
#define CREDIT_TEXTURENAME_LOGO_10	"data/TEXTURE/CREDIT/CREDIT009.png"			// ����
#define CREDIT_TEXTURENAME_LOGO_11	"data/TEXTURE/CREDIT/CREDIT010.png"			//
#define CREDIT_TEXTURENAME_BG_1	"data/TEXTURE/CREDIT/CREDITbg002.png"			// �w�i[1]
#define CREDIT_TEXTURENAME_BG_2	"data/TEXTURE/CREDIT/CREDITbg001.png"			// �w�i[2]
#define CREDIT_TEXTURENAME_BG_3	"data/TEXTURE/CREDIT/CREDITbg000.png"			// �w�i[3]

// ���Ċ��-------------------------------------------------------------------------------1
#define CREDIT_LOGO_POS_X_A	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_A
#define CREDIT_LOGO_POS_Y_A	(SCREEN_HEIGHT +100)					// ���S��Y���W_A
#define CREDIT_LOGO_WIDTH_A	(420)									// ���S�̕�
#define CREDIT_LOGO_HEIGHT_A	(200)								// ���S�̍���
//�v���O���}�[----------------------------------------------------------------------------2
#define CREDIT_LOGO_POS_X_B	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_B
#define CREDIT_LOGO_POS_Y_B	(SCREEN_HEIGHT + 600 )					// ���S��Y���W_B
#define CREDIT_LOGO_WIDTH_B	(400/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_B	(450/1.5f)							// ���S�̍���
//�v�����i�[-------------------------------------------------------------------------------3
#define CREDIT_LOGO_POS_X_C	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_C
#define CREDIT_LOGO_POS_Y_C	(SCREEN_HEIGHT + 1100 )					// ���S��Y���W_C
#define CREDIT_LOGO_WIDTH_C	(380/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_C	(210/1.5f)							// ���S�̍���
//UI�f�U�C��-------------------------------------------------------------------------------4
#define CREDIT_LOGO_POS_X_D	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_D
#define CREDIT_LOGO_POS_Y_D	(SCREEN_HEIGHT + 1450 )					// ���S��Y���W_D
#define CREDIT_LOGO_WIDTH_D	(400/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_D	(330/1.5f)							// ���S�̍���
//���f��----------------------------------------------------------------------------------5
#define CREDIT_LOGO_POS_X_E	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_E
#define CREDIT_LOGO_POS_Y_E	(SCREEN_HEIGHT + 1800 )					// ���S��Y���W_E
#define CREDIT_LOGO_WIDTH_E	(400/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_E	(200/1.5f)							// ���S�̍���
//�I�u�W�F�N�g----------------------------------------------------------------------------6
#define CREDIT_LOGO_POS_X_F	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_F
#define CREDIT_LOGO_POS_Y_F	(SCREEN_HEIGHT + 2100 )					// ���S��Y���W_F
#define CREDIT_LOGO_WIDTH_F	(400/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_F	(300/1.5f)							// ���S�̍���
//���[�V����------------------------------------------------------------------------------7
#define CREDIT_LOGO_POS_X_G	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_G
#define CREDIT_LOGO_POS_Y_G	(SCREEN_HEIGHT + 2300 )					// ���S��Y���W_G
#define CREDIT_LOGO_WIDTH_G	(400/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_G	(200/1.5f)							// ���S�̍���
//�T�E���h--------------------------------------------------------------------------------8
#define CREDIT_LOGO_POS_X_H	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_H
#define CREDIT_LOGO_POS_Y_H	(SCREEN_HEIGHT + 2700 )					// ���S��Y���W_H
#define CREDIT_LOGO_WIDTH_H	(450/1.4f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_H	(600)								// ���S�̍���
//CV-----------------------------------------------------------------------------------10
#define CREDIT_LOGO_POS_X_K	((SCREEN_WIDTH/2)+300 )						// ���S��X���W_J
#define CREDIT_LOGO_POS_Y_K	(SCREEN_HEIGHT + 3400 )					// ���S��Y���W_J
#define CREDIT_LOGO_WIDTH_K	(400)									// ���S�̕�
#define CREDIT_LOGO_HEIGHT_K	(600)								// ���S�̍���
//�v���W�F�N�g���[�_�[-------------------------------------------------------------------9
#define CREDIT_LOGO_POS_X_I	((SCREEN_WIDTH/2) + 300)				// ���S��X���W_I
#define CREDIT_LOGO_POS_Y_I	(SCREEN_HEIGHT + 3950 )					// ���S��Y���W_I
#define CREDIT_LOGO_WIDTH_I	(400/1.2f)								// ���S�̕�
#define CREDIT_LOGO_HEIGHT_I	(220/1.5f)							// ���S�̍���
//����-----------------------------------------------------------------------------------10
#define CREDIT_LOGO_POS_X_J	((SCREEN_WIDTH/2) )						// ���S��X���W_J
#define CREDIT_LOGO_POS_Y_J	(SCREEN_HEIGHT + 4200 )					// ���S��Y���W_J
#define CREDIT_LOGO_WIDTH_J	(500)									// ���S�̕�
#define CREDIT_LOGO_HEIGHT_J	(200)								// ���S�̍���
//�w�i[1]-----------------------------------------------------------------------------------1
#define CREDIT_BG_POS_X_A	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define CREDIT_BG_POS_Y_A	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define CREDIT_BG_WIDTH_A	(700)									// ���S�̕�
#define CREDIT_BG_HEIGHT_A	(400)									// ���S�̍���
//�w�i[2]-----------------------------------------------------------------------------------2
#define CREDIT_BG_POS_X_B	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define CREDIT_BG_POS_Y_B	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define CREDIT_BG_WIDTH_B	(700)									// ���S�̕�
#define CREDIT_BG_HEIGHT_B	(400)									// ���S�̍���
//�w�i[3]-----------------------------------------------------------------------------------3
#define CREDIT_BG_POS_X_C	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define CREDIT_BG_POS_Y_C	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define CREDIT_BG_WIDTH_C	(700)									// ���S�̕�
#define CREDIT_BG_HEIGHT_C	(400)									// ���S�̍���
//���S����
#define CREDIT_MOVE_NOMAL	(2.0f)									// ���S�̓���
#define CREDIT_MOVE_ACCELERATA	(5.0f)								// ���S�̉���
//BG�̐�
#define CREDIT_BG_MAX (3)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��
	CREDITTEX_LOGO_A = 0,			// ���S[���Ċ��]
	CREDITTEX_LOGO_B,				// ���S[�v���O���}�[]
	CREDITTEX_LOGO_C,				// ���S[���o]
	CREDITTEX_LOGO_D,				// ���S[�}�b�v]
	CREDITTEX_LOGO_E,				// ���S[���f��]
	CREDITTEX_LOGO_F,				// ���S[�I�u�W�F�N�g]
	CREDITTEX_LOGO_G,				// ���S[���[�V����]
	CREDITTEX_LOGO_H,				// ���S[�T�E���h]
	CREDITTEX_LOGO_K,				// ���S[CV]
	CREDITTEX_LOGO_I,				// ���S[�v���W�F�N�g���[�_�[]
	CREDITTEX_LOGO_J,				// ���S[����]
	CREDITTEX_BG_A,					//�w�i[1]
	CREDITTEX_BG_B,					//�w�i[2]
	CREDITTEX_BG_C,					//�w�i[2]
	CREDITTEX_MAX					// �e�N�X�`���̑���
} CREDITTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;				// �ʒu
	float fWidth;					// ��
	float fHeight;					// ����
	bool bDraw;						// �`�悷�邩�ǂ���
} CREDIT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexCredit(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureCREDIT[CREDITTEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffCREDIT = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
CREDIT					g_aCredit[CREDITTEX_MAX];					// �^�C�g���̏��[���S]
int						g_nCntFpsCREDIT;							// �o�ߎ���
int						g_nLogoStopCREDIT;							// �o�ߎ���

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �������S��񏉊���
	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		switch (nCntTex)
		{
		case CREDITTEX_LOGO_A://���Ċ��
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_A, CREDIT_LOGO_POS_Y_A, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_A;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_A;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_B://�v���O���}�[
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_B, CREDIT_LOGO_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_C://���o
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_C, CREDIT_LOGO_POS_Y_C, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_C;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_C;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_D://�}�b�v
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_D, CREDIT_LOGO_POS_Y_D, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_D;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_D;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_E://���f��
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_E, CREDIT_LOGO_POS_Y_E, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_E;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_E;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_F://�I�u�W�F�N�g
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_F, CREDIT_LOGO_POS_Y_F, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_F;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_F;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_G://���[�V����
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_G, CREDIT_LOGO_POS_Y_G, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_G;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_G;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_H://�T�E���h
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_H, CREDIT_LOGO_POS_Y_H, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_H;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_H;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_K:	//	�w�i2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_K, CREDIT_LOGO_POS_Y_K, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_K;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_K;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_I://�v���W�F�N�g���[�_�[]
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_I, CREDIT_LOGO_POS_Y_I, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_I;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_I;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_LOGO_J://	����
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_LOGO_POS_X_J, CREDIT_LOGO_POS_Y_J, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_LOGO_WIDTH_J;
			g_aCredit[nCntTex].fHeight = CREDIT_LOGO_HEIGHT_J;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_BG_A:	//	�w�i1
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_A, CREDIT_BG_POS_Y_A, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_A;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_A;
			g_aCredit[nCntTex].bDraw = true;
			break;
		case CREDITTEX_BG_B:	//	�w�i2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_B, CREDIT_BG_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = false;
			break;
		case CREDITTEX_BG_C:	//	�w�i2
			g_aCredit[nCntTex].pos = D3DXVECTOR3(CREDIT_BG_POS_X_B, CREDIT_BG_POS_Y_B, 0.0f);
			g_aCredit[nCntTex].fWidth = CREDIT_BG_WIDTH_B;
			g_aCredit[nCntTex].fHeight = CREDIT_BG_HEIGHT_B;
			g_aCredit[nCntTex].bDraw = false;
			break;

		}
	}
	//�ϐ��̏�����
	g_nCntFpsCREDIT = 0;
	g_nLogoStopCREDIT = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_1, &g_apTextureCREDIT[CREDITTEX_LOGO_A]);//���Ċ��
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_2, &g_apTextureCREDIT[CREDITTEX_LOGO_B]);//�v���O���}�[
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_3, &g_apTextureCREDIT[CREDITTEX_LOGO_C]);//���o
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_4, &g_apTextureCREDIT[CREDITTEX_LOGO_D]);//�}�b�v
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_5, &g_apTextureCREDIT[CREDITTEX_LOGO_E]);//���f��
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_6, &g_apTextureCREDIT[CREDITTEX_LOGO_F]);//�I�u�W�F�N�g
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_7, &g_apTextureCREDIT[CREDITTEX_LOGO_G]);//���[�V����
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_8, &g_apTextureCREDIT[CREDITTEX_LOGO_H]);//�T�E���h
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_9, &g_apTextureCREDIT[CREDITTEX_LOGO_I]);//�v���W�F�N�g���[�_�[]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_10, &g_apTextureCREDIT[CREDITTEX_LOGO_J]);//����
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_LOGO_11, &g_apTextureCREDIT[CREDITTEX_LOGO_K]);//CV
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_1, &g_apTextureCREDIT[CREDITTEX_BG_A]);		//�w�i[1]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_2, &g_apTextureCREDIT[CREDITTEX_BG_B]);		//�w�i[2]
	D3DXCreateTextureFromFile(pDevice, CREDIT_TEXTURENAME_BG_3, &g_apTextureCREDIT[CREDITTEX_BG_C]);		//�w�i[3]

																											// ���_���̍쐬
	MakeVertexCredit(pDevice);
	// �J�����̏���������
	InitCamera();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitCredit(void)
{
	// �e��I�u�W�F�N�g�̏I������
	UninitCamera();

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		if (g_apTextureCREDIT[nCntTex] != NULL)
		{
			g_apTextureCREDIT[nCntTex]->Release();
			g_apTextureCREDIT[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCREDIT != NULL)
	{
		g_pVtxBuffCREDIT->Release();
		g_pVtxBuffCREDIT = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateCredit(void)
{
	FADE pFade = GetFade(); // �t�F�[�h�̎擾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCREDIT->Lock(0, 0, (void**)&pVtx, 0);

	if (pFade != FADE_OUT)
	{
		for (int nCntTex = 0; nCntTex < CREDITTEX_MAX - CREDIT_BG_MAX; nCntTex++, pVtx += 4)
		{
			if (GetKeyboardPress(DIK_RETURN) == true
				|| GetGamePadPress((int)PLAYER_CONTROL_1P, ELECOM_A) == true
				|| GetGamePadPovPress((int)PLAYER_CONTROL_1P, POV_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_1P, STICK_DOWN) == true
				|| GetGamePadPress((int)PLAYER_CONTROL_2P, ELECOM_A) == true
				|| GetGamePadPovPress((int)PLAYER_CONTROL_2P, POV_DOWN) == true
				|| GetGamePadStickPress((int)PLAYER_CONTROL_2P, STICK_DOWN) == true)

			{//�G���^�[�ŉ���
				g_aCredit[nCntTex].pos.y -= CREDIT_MOVE_ACCELERATA;
			}
			else
			{
				g_aCredit[nCntTex].pos.y -= CREDIT_MOVE_NOMAL;
			}
			if (g_aCredit[nCntTex].pos.y <= -400)
			{	//Y-100�ŏ���
				g_aCredit[nCntTex].bDraw = false;
			}
			if (g_aCredit[CREDITTEX_LOGO_J].pos.y <= SCREEN_HEIGHT / 2)
			{//�Ō�̐���͐^�񒆂Ŏ~�߂�
				g_aCredit[CREDITTEX_LOGO_J].pos.y = SCREEN_HEIGHT / 2;
				g_nLogoStopCREDIT++;
				if (g_nLogoStopCREDIT >= 1200 && g_aCredit[CREDITTEX_LOGO_J].pos.y == SCREEN_HEIGHT / 2)
				{
					SetFade(MODE_SELECT);
				}
			}

			if (g_aCredit[CREDITTEX_LOGO_A].bDraw == false)		//��悪FALSE�ɂȂ�����
			{
				g_aCredit[CREDITTEX_BG_A].bDraw = false;			//�w�i[1]��FALSE�ɂ���
				if (g_aCredit[CREDITTEX_BG_A].bDraw == false)		//�w�i[1]��FALSE�ɂȂ�����
				{
					g_aCredit[CREDITTEX_BG_B].bDraw = true;		//�w�i[2]��TRUE�ɂ���
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_C].bDraw == false)		//��悪FALSE�ɂȂ�����
			{
				g_aCredit[CREDITTEX_BG_B].bDraw = false;
				if (g_aCredit[CREDITTEX_BG_B].bDraw == false)
				{
					g_aCredit[CREDITTEX_BG_C].bDraw = true;
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_F].bDraw == false)		//�T�E���h��FALSE�ɂȂ�����
			{
				g_aCredit[CREDITTEX_BG_C].bDraw = false;			//�w�i[3��FALSE]
				if (g_aCredit[CREDITTEX_BG_C].bDraw == false)
				{
					g_aCredit[CREDITTEX_BG_C].bDraw = true;
				}
			}
			if (g_aCredit[CREDITTEX_LOGO_K].bDraw == false)		//�T�E���h��FALSE�ɂȂ�����
			{
				g_aCredit[CREDITTEX_BG_C].bDraw = false;
			}
			if (GetKeyboardPress(DIK_BACKSPACE) == true
				 || GetGamePadTrigger((int)PLAYER_CONTROL_1P, ELECOM_START) == true
				 || GetGamePadTrigger((int)PLAYER_CONTROL_2P, ELECOM_START) == true)
			{
				SetFade(MODE_SELECT);
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffCREDIT->Unlock();
	}
}


//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCREDIT, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++)
	{
		if (g_aCredit[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureCREDIT[nCntTex]);

			// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexCredit(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CREDITTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffCREDIT
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCREDIT->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < CREDITTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, -g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aCredit[nCntTex].fWidth / 2, g_aCredit[nCntTex].fHeight / 2, 0.0f) + g_aCredit[nCntTex].pos;

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
	g_pVtxBuffCREDIT->Unlock();
}
