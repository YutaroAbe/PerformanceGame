//=============================================================================
//
// �G���h���[������ [EndRoll.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "endroll.h"
#include "input.h"
#include "fade.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENDROLL_TEXTURENAME_LOGO_1	"data/TEXTURE/ENDROLL/endroll000.png"			// ���Ċ��
#define ENDROLL_TEXTURENAME_LOGO_2	"data/TEXTURE/ENDROLL/endroll001.png"			// �v���O���}�[
#define ENDROLL_TEXTURENAME_LOGO_3	"data/TEXTURE/ENDROLL/endroll002.png"			// ���o
#define ENDROLL_TEXTURENAME_LOGO_4	"data/TEXTURE/ENDROLL/endroll003.png"			// �}�b�v
#define ENDROLL_TEXTURENAME_LOGO_5	"data/TEXTURE/ENDROLL/endroll004.png"			// ���f��
#define ENDROLL_TEXTURENAME_LOGO_6	"data/TEXTURE/ENDROLL/endroll005.png"			// �I�u�W�F�N�g
#define ENDROLL_TEXTURENAME_LOGO_7	"data/TEXTURE/ENDROLL/endroll006.png"			// ���[�V����
#define ENDROLL_TEXTURENAME_LOGO_8	"data/TEXTURE/ENDROLL/endroll007.png"			// �T�E���h
#define ENDROLL_TEXTURENAME_LOGO_9	"data/TEXTURE/ENDROLL/endroll008.png"			// �v���W�F�N�g���[�_�[
#define ENDROLL_TEXTURENAME_LOGO_10	"data/TEXTURE/ENDROLL/endroll009.png"			// ����

#define ENDROLL_TEXTURENAME_BG_1	"data/TEXTURE/ENDROLL/endrollbg000.png"			// �w�i[1]
#define ENDROLL_TEXTURENAME_BG_2	"data/TEXTURE/ENDROLL/endrollbg001.png"			// �w�i[2]
#define ENDROLL_TEXTURENAME_BG_3	"data/TEXTURE/ENDROLL/endrollbg000.png"			// �w�i[3]

// ���Ċ��-------------------------------------------------------------------------------1
#define ENDROLL_LOGO_POS_X_A	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_A
#define ENDROLL_LOGO_POS_Y_A	(SCREEN_HEIGHT +100)				// ���S��Y���W_A
#define ENDROLL_LOGO_WIDTH_A	(420)								// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_A	(200)								// ���S�̍���
//�v���O���}�[----------------------------------------------------------------------------2
#define ENDROLL_LOGO_POS_X_B	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_B
#define ENDROLL_LOGO_POS_Y_B	(SCREEN_HEIGHT + 600 )				// ���S��Y���W_B
#define ENDROLL_LOGO_WIDTH_B	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_B	(350/1.5f)							// ���S�̍���
//���o------------------------------------------------------------------------------------3
#define ENDROLL_LOGO_POS_X_C	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_C
#define ENDROLL_LOGO_POS_Y_C	(SCREEN_HEIGHT + 900 )				// ���S��Y���W_C
#define ENDROLL_LOGO_WIDTH_C	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_C	(300/1.5f)							// ���S�̍���
//�}�b�v---------------------------------------------------------------------------------4
#define ENDROLL_LOGO_POS_X_D	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_D
#define ENDROLL_LOGO_POS_Y_D	(SCREEN_HEIGHT + 1150 )				// ���S��Y���W_D
#define ENDROLL_LOGO_WIDTH_D	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_D	(200/1.5f)							// ���S�̍���
//���f��----------------------------------------------------------------------------------5
#define ENDROLL_LOGO_POS_X_E	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_E
#define ENDROLL_LOGO_POS_Y_E	(SCREEN_HEIGHT + 1400 )				// ���S��Y���W_E
#define ENDROLL_LOGO_WIDTH_E	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_E	(300/1.5f)							// ���S�̍���
//�I�u�W�F�N�g----------------------------------------------------------------------------6
#define ENDROLL_LOGO_POS_X_F	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_F
#define ENDROLL_LOGO_POS_Y_F	(SCREEN_HEIGHT + 1700 )				// ���S��Y���W_F
#define ENDROLL_LOGO_WIDTH_F	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_F	(300/1.5f)							// ���S�̍���
//���[�V����------------------------------------------------------------------------------7
#define ENDROLL_LOGO_POS_X_G	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_G
#define ENDROLL_LOGO_POS_Y_G	(SCREEN_HEIGHT + 2000 )				// ���S��Y���W_G
#define ENDROLL_LOGO_WIDTH_G	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_G	(300/1.5f)							// ���S�̍���
//�T�E���h--------------------------------------------------------------------------------8
#define ENDROLL_LOGO_POS_X_H	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_H
#define ENDROLL_LOGO_POS_Y_H	(SCREEN_HEIGHT + 2300 )				// ���S��Y���W_H
#define ENDROLL_LOGO_WIDTH_H	(400/1.4f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_H	(400/1.5f)							// ���S�̍���
//�v���W�F�N�g���[�_�[-------------------------------------------------------------------9
#define ENDROLL_LOGO_POS_X_I	((SCREEN_WIDTH/2) + 300)			// ���S��X���W_I
#define ENDROLL_LOGO_POS_Y_I	(SCREEN_HEIGHT + 2600 )				// ���S��Y���W_I
#define ENDROLL_LOGO_WIDTH_I	(400/1.2f)							// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_I	(200/1.5f)							// ���S�̍���
//����-----------------------------------------------------------------------------------10
#define ENDROLL_LOGO_POS_X_J	((SCREEN_WIDTH/2) )					// ���S��X���W_J
#define ENDROLL_LOGO_POS_Y_J	(SCREEN_HEIGHT + 2900 )				// ���S��Y���W_J
#define ENDROLL_LOGO_WIDTH_J	(500)								// ���S�̕�
#define ENDROLL_LOGO_HEIGHT_J	(200)								// ���S�̍���
//�w�i[1]-----------------------------------------------------------------------------------1
#define ENDROLL_BG_POS_X_A	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define ENDROLL_BG_POS_Y_A	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define ENDROLL_BG_WIDTH_A	(700)									// ���S�̕�
#define ENDROLL_BG_HEIGHT_A	(400)									// ���S�̍���
//�w�i[2]-----------------------------------------------------------------------------------2
#define ENDROLL_BG_POS_X_B	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define ENDROLL_BG_POS_Y_B	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define ENDROLL_BG_WIDTH_B	(700)									// ���S�̕�
#define ENDROLL_BG_HEIGHT_B	(400)									// ���S�̍���
//�w�i[3]-----------------------------------------------------------------------------------3
#define ENDROLL_BG_POS_X_C	((SCREEN_WIDTH/2/2)+50)					// ���S��X���W_J
#define ENDROLL_BG_POS_Y_C	((SCREEN_HEIGHT/2/2)+50 )				// ���S��Y���W_J
#define ENDROLL_BG_WIDTH_C	(700)									// ���S�̕�
#define ENDROLL_BG_HEIGHT_C	(400)									// ���S�̍���

//���S����
#define ENDROLL_MOVE_NOMAL	(2.0f)									// ���S�̓���
#define ENDROLL_MOVE_ACCELERATA	(5.0f)								// ���S�̉���

//BG�̐�
#define ENDROLL_BG_MAX (3)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��
	EndRollTEX_LOGO_A = 0,			// ���S[���Ċ��]
	EndRollTEX_LOGO_B,				// ���S[�v���O���}�[]
	EndRollTEX_LOGO_C,				// ���S[���o]
	EndRollTEX_LOGO_D,				// ���S[�}�b�v]
	EndRollTEX_LOGO_E,				// ���S[���f��]
	EndRollTEX_LOGO_F,				// ���S[�I�u�W�F�N�g]
	EndRollTEX_LOGO_G,				// ���S[���[�V����]
	EndRollTEX_LOGO_H,				// ���S[�T�E���h]
	EndRollTEX_LOGO_I,				// ���S[�v���W�F�N�g���[�_�[]
	EndRollTEX_LOGO_J,				// ���S[����]
	EndRollTEX_BG_A,				//�w�i[1]
	EndRollTEX_BG_B,				//�w�i[2]
	EndRollTEX_BG_C,				//�w�i[2]
	EndRollTEX_MAX					// �e�N�X�`���̑���
} ENDROLLTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;				// �ʒu
	float fWidth;					// ��
	float fHeight;					// ����
	bool bDraw;						// �`�悷�邩�ǂ���
} ENDROLL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEndRoll(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEndRoll[EndRollTEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffEndRoll = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
ENDROLL					g_aEndRoll[EndRollTEX_MAX];					// �^�C�g���̏��[���S]
int						g_nCntFpsEndRoll;							// �o�ߎ���
int						g_nLogoStopEndRoll;							// �o�ߎ���

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitEndRoll(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �������S��񏉊���
	for (int nCntTex = 0; nCntTex < EndRollTEX_MAX; nCntTex++)
	{
		switch (nCntTex)
		{
		case EndRollTEX_LOGO_A://���Ċ��
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_A, ENDROLL_LOGO_POS_Y_A, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_A;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_A;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_B://�v���O���}�[
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_B, ENDROLL_LOGO_POS_Y_B, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_B;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_B;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_C://���o
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_C, ENDROLL_LOGO_POS_Y_C, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_C;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_C;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_D://�}�b�v
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_D, ENDROLL_LOGO_POS_Y_D, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_D;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_D;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_E://���f��
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_E, ENDROLL_LOGO_POS_Y_E, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_E;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_E;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_F://�I�u�W�F�N�g
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_F, ENDROLL_LOGO_POS_Y_F, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_F;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_F;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_G://���[�V����
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_G, ENDROLL_LOGO_POS_Y_G, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_G;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_G;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_H://�T�E���h
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_H, ENDROLL_LOGO_POS_Y_H, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_H;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_H;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_I://�v���W�F�N�g���[�_�[]
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_I, ENDROLL_LOGO_POS_Y_I, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_I;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_I;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_LOGO_J://����
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_LOGO_POS_X_J, ENDROLL_LOGO_POS_Y_J, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_LOGO_WIDTH_J;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_LOGO_HEIGHT_J;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_BG_A:	//�w�i1
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_BG_POS_X_A, ENDROLL_BG_POS_Y_A, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_BG_WIDTH_A;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_BG_HEIGHT_A;
			g_aEndRoll[nCntTex].bDraw = true;
			break;
		case EndRollTEX_BG_B:	//�w�i2
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_BG_POS_X_B, ENDROLL_BG_POS_Y_B, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_BG_WIDTH_B;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_BG_HEIGHT_B;
			g_aEndRoll[nCntTex].bDraw = false;
			break;
		case EndRollTEX_BG_C:	//�w�i2
			g_aEndRoll[nCntTex].pos = D3DXVECTOR3(ENDROLL_BG_POS_X_B, ENDROLL_BG_POS_Y_B, 0.0f);
			g_aEndRoll[nCntTex].fWidth = ENDROLL_BG_WIDTH_B;
			g_aEndRoll[nCntTex].fHeight = ENDROLL_BG_HEIGHT_B;
			g_aEndRoll[nCntTex].bDraw = false;
			break;
		}
	}
	//�ϐ��̏�����
	g_nCntFpsEndRoll = 0;
	g_nLogoStopEndRoll = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_1, &g_apTextureEndRoll[EndRollTEX_LOGO_A]);//���Ċ��
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_2, &g_apTextureEndRoll[EndRollTEX_LOGO_B]);//�v���O���}�[
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_3, &g_apTextureEndRoll[EndRollTEX_LOGO_C]);//���o
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_4, &g_apTextureEndRoll[EndRollTEX_LOGO_D]);//�}�b�v
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_5, &g_apTextureEndRoll[EndRollTEX_LOGO_E]);//���f��
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_6, &g_apTextureEndRoll[EndRollTEX_LOGO_F]);//�I�u�W�F�N�g
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_7, &g_apTextureEndRoll[EndRollTEX_LOGO_G]);//���[�V����
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_8, &g_apTextureEndRoll[EndRollTEX_LOGO_H]);//�T�E���h
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_9, &g_apTextureEndRoll[EndRollTEX_LOGO_I]);//�v���W�F�N�g���[�_�[]
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_LOGO_10, &g_apTextureEndRoll[EndRollTEX_LOGO_J]);//����
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_BG_1, &g_apTextureEndRoll[EndRollTEX_BG_A]);		//�w�i[1]	
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_BG_2, &g_apTextureEndRoll[EndRollTEX_BG_B]);		//�w�i[2]	
	D3DXCreateTextureFromFile(pDevice, ENDROLL_TEXTURENAME_BG_3, &g_apTextureEndRoll[EndRollTEX_BG_C]);		//�w�i[3]	

	// ���_���̍쐬
	MakeVertexEndRoll(pDevice);
	// �J�����̏���������
	InitCamera();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitEndRoll(void)
{
	// �e��I�u�W�F�N�g�̏I������
	UninitCamera();

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < EndRollTEX_MAX; nCntTex++)
	{
		if (g_apTextureEndRoll[nCntTex] != NULL)
		{
			g_apTextureEndRoll[nCntTex]->Release();
			g_apTextureEndRoll[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEndRoll != NULL)
	{
		g_pVtxBuffEndRoll->Release();
		g_pVtxBuffEndRoll = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateEndRoll(void)
{
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEndRoll->Lock(0, 0, (void**)&pVtx, 0);

	if (pFade == FADE_NONE)
	{
		for (int nCntTex = 0; nCntTex < EndRollTEX_MAX - ENDROLL_BG_MAX; nCntTex++, pVtx += 4)
		{
			if (GetKeyboardPress(DIK_RETURN) == true)
			{//�G���^�[�ŉ���
				g_aEndRoll[nCntTex].pos.y -= ENDROLL_MOVE_ACCELERATA;
			}
			else
			{
				g_aEndRoll[nCntTex].pos.y -= ENDROLL_MOVE_NOMAL;
			}
			if (g_aEndRoll[nCntTex].pos.y <= -100)
			{	//Y-100�ŏ���
				g_aEndRoll[nCntTex].bDraw = false;
			}
			if (g_aEndRoll[EndRollTEX_LOGO_J].pos.y <= SCREEN_HEIGHT / 2)
			{//�Ō�̐���͐^�񒆂Ŏ~�߂�
				g_aEndRoll[EndRollTEX_LOGO_J].pos.y = SCREEN_HEIGHT / 2;
				g_nLogoStopEndRoll++;
				if (g_nLogoStopEndRoll >= 1200 && g_aEndRoll[EndRollTEX_LOGO_J].pos.y == SCREEN_HEIGHT / 2)
				{
					SetFade(MODE_TITLE);
				}
			}

			if (g_aEndRoll[EndRollTEX_LOGO_A].bDraw == false)		//��悪FALSE�ɂȂ�����
			{
				g_aEndRoll[EndRollTEX_BG_A].bDraw = false;			//�w�i[1]��FALSE�ɂ���
				if (g_aEndRoll[EndRollTEX_BG_A].bDraw == false)		//�w�i[1]��FALSE�ɂȂ�����
				{
					g_aEndRoll[EndRollTEX_BG_B].bDraw = true;		//�w�i[2]��TRUE�ɂ���
				}
			}
			if (g_aEndRoll[EndRollTEX_LOGO_C].bDraw == false)		//��悪FALSE�ɂȂ�����
			{
				g_aEndRoll[EndRollTEX_BG_B].bDraw = false;
				if (g_aEndRoll[EndRollTEX_BG_B].bDraw == false)
				{
					g_aEndRoll[EndRollTEX_BG_C].bDraw = true;
				}
			}
			if (g_aEndRoll[EndRollTEX_LOGO_H].bDraw == false)		//�T�E���h��FALSE�ɂȂ�����
			{
				g_aEndRoll[EndRollTEX_BG_C].bDraw = false;			//�w�i[3��FALSE]
			}
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEndRoll[nCntTex].fWidth / 2, -g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aEndRoll[nCntTex].fWidth / 2, -g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aEndRoll[nCntTex].fWidth / 2, g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aEndRoll[nCntTex].fWidth / 2, g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEndRoll->Unlock();
	}
}


//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawEndRoll(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �J�����̐ݒ�
	SetCamera();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEndRoll, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < EndRollTEX_MAX; nCntTex++)
	{
		if (g_aEndRoll[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEndRoll[nCntTex]);

			// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEndRoll(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * EndRollTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffEndRoll
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEndRoll->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < EndRollTEX_MAX ; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aEndRoll[nCntTex].fWidth / 2, -g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aEndRoll[nCntTex].fWidth / 2, -g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aEndRoll[nCntTex].fWidth / 2, g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aEndRoll[nCntTex].fWidth / 2, g_aEndRoll[nCntTex].fHeight / 2, 0.0f) + g_aEndRoll[nCntTex].pos;

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
	g_pVtxBuffEndRoll->Unlock();
}
