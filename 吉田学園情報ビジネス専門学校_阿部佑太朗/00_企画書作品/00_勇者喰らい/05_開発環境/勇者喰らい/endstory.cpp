//=============================================================================
//
// �^�C�g������ [ENDSTORY.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "endstory.h"
#include "light.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENDSTORY_TEXTURENAME1	"data/TEXTURE/STORY/box_horror_grbl.png"			// �ǂݍ��ރe�N�X�`���̖��O�P
#define ENDSTORY_TEXTURENAME2	"data/TEXTURE/STORY/KUROMEN.png"					// �ǂݍ��ރe�N�X�`���̖��O�P
//���b�Z�[�W�{�b�N�X
#define ENDSTORY_BOX_POS_X	(SCREEN_WIDTH/2)								// ���S��X���W_A
#define ENDSTORY_BOX_POS_Y	(SCREEN_HEIGHT/2 +250)							// ���S��Y���W_A
#define ENDSTORY_BOX_WIDTH	(900)											// ���S�̕�
#define ENDSTORY_BOX_HEIGHT (200)											// ���S�̍���
//��ʊJ�n�̍���
#define ENDSTORY_BLACK_POS_X	(SCREEN_WIDTH/2)							//	������X���W_A
#define ENDSTORY_BLACK_POS_Y	(SCREEN_HEIGHT/2)							//�@������Y���W_A
#define ENDSTORY_BLACK_WIDTH	(SCREEN_WIDTH)								// �����̕�
#define ENDSTORY_BLACK_HEIGHT (SCREEN_HEIGHT)								// �����̍���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��
	ENDSTORYTEX_BOX = 0,	// ���S
	ENDSTORYTEX_BLACK,		//�@��ʊJ�n�̍���
	ENDSTORYTEX_MAX		// �e�N�X�`���̑���
} ENDSTORYTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;	// �ʒu
	float fWidth;		// ��
	float fHeight;		// ����
	bool bFlash;		// �_�ł��邩�ǂ���
	bool bDraw;			// �`�悷�邩�ǂ���
} ENDSTORY;

typedef enum
{// �e�N�X�`���̎��
	ENDSTORYTEX_BLACK_NOMAL = 0,	// �ʏ�
	ENDSTORYTEX_BLACK_DOWN,
	ENDSTORYTEX_BLACK_QUIT,		//�@�J���[�_�E��
	ENDSTORYTEX_BLACK_MAX				// �e�N�X�`���̑���
} BLACKTEX;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEndStory(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureENDSTORY[ENDSTORYTEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffENDSTORY = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
ENDSTORY				g_aENDSTORY[ENDSTORYTEX_MAX];					// �^�C�g���̏��
ENDSTORYSTATE			g_aENDSTORYState;							//�X�g�[���[��b���
BLACKTEX				g_eBlackstate;
int						 g_aENDSTORYMene;;							//�X�g�[���[�̃��j���[
int						g_nCntFpsENDSTORY;							// �o�ߎ���
int						g_nCntLogoStopENDSTORY;					// �o�ߎ���
int						g_eBlackColDown;						// �����̃J���[�_�E��
int						g_aENDStoryCounterTXT;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitEndStory(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̏�����
	for (int nCntTex = 0; nCntTex < ENDSTORYTEX_MAX; nCntTex++)
	{
		g_aENDSTORY[nCntTex].bFlash = false;
		switch (nCntTex)
		{
		case ENDSTORYTEX_BOX:			//���b�Z�[�W�{�b�N�X
			g_aENDSTORY[nCntTex].pos = D3DXVECTOR3(ENDSTORY_BOX_POS_X, ENDSTORY_BOX_POS_Y, 0.0f);
			g_aENDSTORY[nCntTex].fWidth = ENDSTORY_BOX_WIDTH;
			g_aENDSTORY[nCntTex].fHeight = ENDSTORY_BOX_HEIGHT;
			g_aENDSTORY[nCntTex].bDraw = true;
			break;
		case ENDSTORYTEX_BLACK:		//��ʊJ�n�̍���
			g_aENDSTORY[nCntTex].pos = D3DXVECTOR3(ENDSTORY_BLACK_POS_X, ENDSTORY_BLACK_POS_Y, 0.0f);
			g_aENDSTORY[nCntTex].fWidth = ENDSTORY_BLACK_WIDTH;
			g_aENDSTORY[nCntTex].fHeight = ENDSTORY_BLACK_HEIGHT;
			g_aENDSTORY[nCntTex].bDraw = true;
			break;
		}
	}
	//�ϐ��̏�����
	g_nCntFpsENDSTORY = 0;
	g_aENDSTORYMene = 0;
	g_nCntLogoStopENDSTORY = 0;
	g_eBlackColDown = 0;
	g_eBlackstate = ENDSTORYTEX_BLACK_NOMAL;
	g_aENDStoryCounterTXT = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENDSTORY_TEXTURENAME1, &g_apTextureENDSTORY[ENDSTORYTEX_BOX]);
	D3DXCreateTextureFromFile(pDevice, ENDSTORY_TEXTURENAME2, &g_apTextureENDSTORY[ENDSTORYTEX_BLACK]);

	// ���_���̍쐬
	MakeVertexEndStory(pDevice);

	//���C�g�̏���������
	InitLight();
	//�J�����̏���������
	InitCamera();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitEndStory(void)
{
	//���C�g�̏I������
	UninitLight();
	// �J�����̏I������
	UninitCamera();

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < ENDSTORYTEX_MAX; nCntTex++)
	{
		if (g_apTextureENDSTORY[nCntTex] != NULL)
		{
			g_apTextureENDSTORY[nCntTex]->Release();
			g_apTextureENDSTORY[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffENDSTORY != NULL)
	{
		g_pVtxBuffENDSTORY->Release();
		g_pVtxBuffENDSTORY = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateEndStory(void)
{
	VERTEX_2D *pVtx;
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾
	PLAYER *pPlayer = GetPlayer();

	g_aENDStoryCounterTXT = *GetENDStoryTXT();

	if (pFade == FADE_NONE)
	{

		switch (g_eBlackstate)
		{
		case ENDSTORYTEX_BLACK_NOMAL:
			if (pPlayer[0].bButton[BUTTON_ENTER] == true)
			{//�G���^�[�ŃZ���N�g��ʂ�
				g_eBlackstate = ENDSTORYTEX_BLACK_DOWN;
			}
			break;
		case ENDSTORYTEX_BLACK_DOWN:
			g_aENDSTORYMene = 1;
			g_eBlackColDown++;
			if (g_eBlackColDown >= 220)
			{
				g_aENDStoryCounterTXT = 200;
				g_eBlackColDown = 255;
				g_eBlackstate = ENDSTORYTEX_BLACK_QUIT;

			}
			break;
		case ENDSTORYTEX_BLACK_QUIT:
			//�L�[�{�[�h�ݒ�
			if (pPlayer[0].bButton[BUTTON_ENTER] == true && g_aENDStoryCounterTXT >120)
			{//�G���^�[�ŃZ���N�g��ʂ�
				g_aENDSTORYMene += 1;
				PlaySound(SOUND_LABEL_STORY_SE);
			}
			switch (g_aENDSTORYMene)
			{
			case  0:
				g_aENDSTORYState = ENDSTORY_000;
				break;
			case 1:
				g_aENDSTORYState = ENDSTORY_001;
				break;
			case 2:
				g_aENDSTORYState = ENDSTORY_002;
				break;
			case 3:
				g_aENDSTORYState = ENDSTORY_003;
				break;
			case 4:
				g_aENDSTORYState = ENDSTORY_004;
				break;
			case 5:
				g_aENDSTORYState = ENDSTORY_005;
				break;
			case 6:
				g_aENDSTORYState = ENDSTORY_006;
				break;
			case 7:
				g_aENDSTORYState = ENDSTORY_007;
				break;
			case 8:
				g_aENDSTORYState = ENDSTORY_008;
				break;
			case 9:
				g_aENDSTORYState = ENDSTORY_009;
				break;
			case 10:
				g_aENDSTORYState = ENDSTORY_010;
				break;
			case 11:
				g_aENDSTORYState = ENDSTORY_011;
				break;
			case 12:
				g_aENDSTORYState = ENDSTORY_012;
				break;
			case 13:
				g_aENDSTORYState = ENDSTORY_013;
				break;
			case 14:
				SetFade(MODE_ENDROLL, 0, 0.0f, 0);
				g_aENDSTORYState = ENDSTORY_014;
				break;
			}


			break;
		}

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffENDSTORY->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_eBlackColDown);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_eBlackColDown);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_eBlackColDown);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_eBlackColDown);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffENDSTORY->Unlock();
	}

	//���C�g�̍X�V����
	UpdateLight();
	//�J�����̍X�V����
	UpdateCamera();
}


//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawEndStory(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �J�����̐ݒ�
	SetCamera(0);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffENDSTORY, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < ENDSTORYTEX_MAX; nCntTex++)
	{
		if (g_aENDSTORY[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureENDSTORY[nCntTex]);

			// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEndStory(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ENDSTORYTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffENDSTORY
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffENDSTORY->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < ENDSTORYTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aENDSTORY[nCntTex].fWidth / 2, -g_aENDSTORY[nCntTex].fHeight / 2, 0.0f) + g_aENDSTORY[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aENDSTORY[nCntTex].fWidth / 2, -g_aENDSTORY[nCntTex].fHeight / 2, 0.0f) + g_aENDSTORY[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aENDSTORY[nCntTex].fWidth / 2, g_aENDSTORY[nCntTex].fHeight / 2, 0.0f) + g_aENDSTORY[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aENDSTORY[nCntTex].fWidth / 2, g_aENDSTORY[nCntTex].fHeight / 2, 0.0f) + g_aENDSTORY[nCntTex].pos;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffENDSTORY->Unlock();
}
//=============================================================================
//�Z���N�g�̏�ԏ��
//=============================================================================
ENDSTORYSTATE GetEndStstate(void)
{
	return g_aENDSTORYState;
}
//=============================================================================
//�Z���N�g�̃��j���[���
//=============================================================================
int GetEndStoryMenu(void)
{
	return g_aENDSTORYMene;
}