//=============================================================================
//
// �X�g�[���[���� [Story.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "story.h"
#include "light.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STORY_TEXTURENAME1	"data/TEXTURE/STORY/box_horror_grbl.png"		// �ǂݍ��ރe�N�X�`���̖��O�P
#define STORY_TEXTURENAME2	"data/TEXTURE/STORY/KUROMEN.png"				// �ǂݍ��ރe�N�X�`���̖��O�P
//���b�Z�[�W�{�b�N�X
#define STORY_BOX_POS_X	(SCREEN_WIDTH/2)								// ���S��X���W_A
#define STORY_BOX_POS_Y	(SCREEN_HEIGHT/2 +250)							// ���S��Y���W_A
#define STORY_BOX_WIDTH	(900)											// ���S�̕�
#define STORY_BOX_HEIGHT (200)											// ���S�̍���
//��ʊJ�n�̍���
#define STORY_BLACK_POS_X	(SCREEN_WIDTH/2)							// ������X���W_A
#define STORY_BLACK_POS_Y	(SCREEN_HEIGHT/2)							// ������Y���W_A
#define STORY_BLACK_WIDTH	(SCREEN_WIDTH)								// �����̕�
#define STORY_BLACK_HEIGHT (SCREEN_HEIGHT)								// �����̍���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �e�N�X�`���̎��
	STORYTEX_BOX = 0,	// ���S
	STORYTEX_BLACK,		//�@��ʊJ�n�̍���
	STORYTEX_MAX		// �e�N�X�`���̑���
} STORYTEX;

typedef struct
{// �^�C�g���̏��
	D3DXVECTOR3 pos;	// �ʒu
	float fWidth;		// ��
	float fHeight;		// ����
	bool bFlash;		// �_�ł��邩�ǂ���
	bool bDraw;			// �`�悷�邩�ǂ���
} Story;

typedef enum
{// �e�N�X�`���̎��
	STORYTEX_BLACK_NOMAL = 0,	// �ʏ�
	STORYTEX_BLACK_DOWN,
	STORYTEX_BLACK_QUIT,		//�@�J���[�_�E��
	STORYTEX_BLACK_MAX				// �e�N�X�`���̑���
} BLACKTEX;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexStory(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureStory[STORYTEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffStory = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Story					g_aStory[STORYTEX_MAX];					// �^�C�g���̏��
STORYSTATE				g_aStoryState;							//�X�g�[���[��b���
BLACKTEX				g_nBlackstate;
int						 g_aStoryMene;;							//�X�g�[���[�̃��j���[
int						g_nCntFpsStory;							// �o�ߎ���
int						g_nCntLogoStopStory;					// �o�ߎ���
int						g_nBlackColDown;						// �����̃J���[�_�E��
int						g_aStoryCounterTXT;

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitStory(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̏�����
	for (int nCntTex = 0; nCntTex < STORYTEX_MAX; nCntTex++)
	{
		g_aStory[nCntTex].bFlash = false;
		switch (nCntTex)
		{
		case STORYTEX_BOX:			//���b�Z�[�W�{�b�N�X
			g_aStory[nCntTex].pos = D3DXVECTOR3(STORY_BOX_POS_X, STORY_BOX_POS_Y, 0.0f);
			g_aStory[nCntTex].fWidth = STORY_BOX_WIDTH;
			g_aStory[nCntTex].fHeight = STORY_BOX_HEIGHT;
			g_aStory[nCntTex].bDraw = true;
			break;
		case STORYTEX_BLACK:		//��ʊJ�n�̍���
			g_aStory[nCntTex].pos = D3DXVECTOR3(STORY_BLACK_POS_X, STORY_BLACK_POS_Y, 0.0f);
			g_aStory[nCntTex].fWidth = STORY_BLACK_WIDTH;
			g_aStory[nCntTex].fHeight = STORY_BLACK_HEIGHT;
			g_aStory[nCntTex].bDraw = true;
			break;
		}
	}
	//�ϐ��̏�����
	g_nCntFpsStory = 0;
	g_aStoryMene = 0;
	g_nCntLogoStopStory = 0;
	g_nBlackColDown = 0;
	g_nBlackstate = STORYTEX_BLACK_NOMAL;
	g_aStoryCounterTXT = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, STORY_TEXTURENAME1, &g_apTextureStory[STORYTEX_BOX]);
	D3DXCreateTextureFromFile(pDevice, STORY_TEXTURENAME2, &g_apTextureStory[STORYTEX_BLACK]);

	// ���_���̍쐬
	MakeVertexStory(pDevice);

	//���C�g�̏���������
	InitLight();
	//�J�����̏���������
	InitCamera();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitStory(void)
{
	//���C�g�̏I������
	UninitLight();
	// �J�����̏I������
	UninitCamera();

	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < STORYTEX_MAX; nCntTex++)
	{
		if (g_apTextureStory[nCntTex] != NULL)
		{
			g_apTextureStory[nCntTex]->Release();
			g_apTextureStory[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffStory != NULL)
	{
		g_pVtxBuffStory->Release();
		g_pVtxBuffStory = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateStory(void)
{
	VERTEX_2D *pVtx;
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾
	PLAYER *pPlayer = GetPlayer();

	g_aStoryCounterTXT = *GetStoryTXT();

	if (pFade == FADE_NONE)
	{
		switch (g_nBlackstate)
		{
		case STORYTEX_BLACK_NOMAL:
			if (pPlayer[0].bButton[BUTTON_ENTER] == true)
			{//�G���^�[�ŃZ���N�g��ʂ�
				g_nBlackstate = STORYTEX_BLACK_DOWN;
			}
			break;
		case STORYTEX_BLACK_DOWN:
			g_aStoryMene = 1;
			g_nBlackColDown++;
			if (g_nBlackColDown >= 200 )
			{
				g_aStoryCounterTXT = 200;
				g_nBlackColDown = 255;
				g_nBlackstate = STORYTEX_BLACK_QUIT;

			}
			break;
		case STORYTEX_BLACK_QUIT:
			//�L�[�{�[�h�ݒ�
			if ( pPlayer[0].bButton[BUTTON_ENTER] == true && g_aStoryCounterTXT >= 120)
			{//�G���^�[�ŃZ���N�g��ʂ�
					g_aStoryMene += 1;
					PlaySound(SOUND_LABEL_STORY_SE);

			}
			if (pPlayer[0].bButton[BUTTON_P] == true)
			{
				SetFade(MODE_SELCT, 0, 0.0f, 0);
			}

			switch (g_aStoryMene)
			{
			case  0:
				g_aStoryState = STORY_000;
				break;
			case 1:
				g_aStoryState = STORY_001;
				break;
			case 2:
				g_aStoryState = STORY_002;

				break;
			case 3:
				g_aStoryState = STORY_003;
				break;
			case 4:
				g_aStoryState = STORY_004;
				break;
			case 5:
				g_aStoryState = STORY_005;
				break;
			case 6:
				g_aStoryState = STORY_006;
				break;
			case 7:
				g_aStoryState = STORY_007;
				break;
			case 8:
				g_aStoryState = STORY_008;
				break;
			case 9:
				g_aStoryState = STORY_009;
				break;
			case 10:
				g_aStoryState = STORY_010;
				break;
			case 11:
				g_aStoryState = STORY_011;
				break;
			case 12:
				g_aStoryState = STORY_012;
				break;
			case 13:
				g_aStoryState = STORY_013;
				break;
			case 14:
				g_aStoryState = STORY_014;
				break;
			case 15:
				g_aStoryState = STORY_015;
				break;
			case 16:
				g_aStoryState = STORY_016;
				SetFade(MODE_SELCT, 0, 0.0f, 0);
				break;
			}
			break;
		}

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffStory->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_nBlackColDown);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_nBlackColDown);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_nBlackColDown);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - g_nBlackColDown);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStory->Unlock();
	}

	//���C�g�̍X�V����
	UpdateLight();
	//�J�����̍X�V����
	UpdateCamera();
}


//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawStory(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �J�����̐ݒ�
	SetCamera(0);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStory, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < STORYTEX_MAX; nCntTex++)
	{
		if (g_aStory[nCntTex].bDraw == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureStory[nCntTex]);

			// �|���S���̕`��// �v���~�e�B�u�̎��// �J�n���钸�_�̃C���f�b�N�X// �`�悷��v���~�e�B�u�̐�
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexStory(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * STORYTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffStory
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStory->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < STORYTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_aStory[nCntTex].fWidth / 2, -g_aStory[nCntTex].fHeight / 2, 0.0f) + g_aStory[nCntTex].pos;
		pVtx[1].pos = D3DXVECTOR3(g_aStory[nCntTex].fWidth / 2, -g_aStory[nCntTex].fHeight / 2, 0.0f) + g_aStory[nCntTex].pos;
		pVtx[2].pos = D3DXVECTOR3(-g_aStory[nCntTex].fWidth / 2, g_aStory[nCntTex].fHeight / 2, 0.0f) + g_aStory[nCntTex].pos;
		pVtx[3].pos = D3DXVECTOR3(g_aStory[nCntTex].fWidth / 2, g_aStory[nCntTex].fHeight / 2, 0.0f) + g_aStory[nCntTex].pos;

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
	g_pVtxBuffStory->Unlock();
}
//=============================================================================
//�Z���N�g�̏�ԏ��
//=============================================================================
STORYSTATE GetStstate(void)
{
	return g_aStoryState;
}
//=============================================================================
//�Z���N�g�̃��j���[���
//=============================================================================
int GetStoryMenu(void)
{
	return g_aStoryMene;
}