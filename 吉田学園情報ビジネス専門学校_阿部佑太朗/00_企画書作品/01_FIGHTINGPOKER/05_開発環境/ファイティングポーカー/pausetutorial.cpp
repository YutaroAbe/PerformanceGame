//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// �|�[�Y�`���[�g���A������ [pausetutorial.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "main.h"
#include "pausetutorial.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_PAUSETUTORIAL				(4)							// �|�[�Y�`���[�g���A���̍ő吔
#define MAX_PAUSETUTORIALPAGE			(3)							// �|�[�Y�`���[�g���A���̃X���C�h�̖���
#define PAUSETUTORIALPAGE_PATTERN_ANIM	float(1.0f / float(MAX_PAUSETUTORIALPAGE))	// �y�[�W�̉��Z��
#define PAUSETUTORIAL_DISP_NORMAL		(30)						// �ʏ펞�̓_�ł̊Ԋu
#define PAUSETUTORIAL_DISP_FAST			(2)							// ���莞�̓_�ł̊Ԋu
#define SLIDE_TIME					(20)							// �X�N���[���X�s�[�h

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{
	PAUSETUTORIAL_TEX_MAIN = 0,		// ���C���摜
	PAUSETUTORIAL_TEX_ARROWW_RIGHT,	// ���E
	PAUSETUTORIAL_TEX_ARROWW_LEFT,	// ���
	PAUSETUTORIAL_TEX_MAX,			// ����
}PauseTutorialTexName;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	PAUSETUTORIALTYPE type;	// ���
	D3DXCOLOR	col;		// �F
	int nTexType;			// �e�N�X�`���̎��
	float fWidth;			// ����
	float fHeight;			// �c��
	int nMoveCounter;		// �l�X�ȓ����̃J�E���^�[
	int nDispSpeed;			// �_�ł̃X�s�[�h
	bool bDisp;				// �\��
	bool bUse;				// �g�p���Ă��邩�ǂ���
}PauseTutorial;

typedef struct
{
	char *pFilename;	// �t�@�C����
} PauseTutorialTexInfo;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexPauseTutorial(LPDIRECT3DDEVICE9 pDevice);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ�
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9 g_pTexturePauseTutorial[PAUSETUTORIAL_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseTutorial = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
PauseTutorial g_aPauseTutorial[MAX_PAUSETUTORIAL];								// �|�[�Y�`���[�g���A���̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
PauseTutorialTexInfo g_apTexturePauseTutorialInfo[PAUSETUTORIAL_TEX_MAX] =
{
	{ "data//TEXTURE//pausetutorial.png" },		// ���C���摜
	{ "data//TEXTURE//arrowRight.png" },		// ���E
	{ "data//TEXTURE//arrowLeft.png" },			// ���
};

int g_nCntPagePause;			// ���݂̃y�[�W�����J�E���g
int g_nSlideFrameCntPause;		// �X���C�h���Ԃ̃J�E���^�[
bool g_bSlideUsePause;			// �X���C�h�����ǂ���
float g_fSlideTexAnimPause;		// �X���C�h�̃e�N�X�`���̌��݂̒l
float g_fSlideTexAnimAddPause;	// �X���C�h�̃e�N�X�`���̑����l
int g_nDispCounterPause;			// �_�ł̃J�E���^�[

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�`���[�g���A������������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitPauseTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �|�[�Y�`���[�g���A���̏��̏�����
	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		g_aPauseTutorial[nCntPauseTutorial].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPauseTutorial[nCntPauseTutorial].type = PAUSETUTORIALTYPE_MAIN;
		g_aPauseTutorial[nCntPauseTutorial].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPauseTutorial[nCntPauseTutorial].nTexType = PAUSETUTORIAL_TEX_MAIN;
		g_aPauseTutorial[nCntPauseTutorial].nDispSpeed = PAUSETUTORIAL_DISP_NORMAL;
		g_aPauseTutorial[nCntPauseTutorial].fWidth = 0;
		g_aPauseTutorial[nCntPauseTutorial].fHeight = 0;
		g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
		g_aPauseTutorial[nCntPauseTutorial].bUse = false;
	}

	g_nCntPagePause = 0;
	g_nSlideFrameCntPause = 0;
	g_bSlideUsePause = false;
	g_fSlideTexAnimPause = 0.0f;
	g_fSlideTexAnimAddPause = 0.0f;
	g_nDispCounterPause = 0;

	// �e�N�X�`���̓ǂݍ���
	for (int nCntPauseTutorialTex = 0; nCntPauseTutorialTex < PAUSETUTORIAL_TEX_MAX; nCntPauseTutorialTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTexturePauseTutorialInfo[nCntPauseTutorialTex].pFilename,
			&g_pTexturePauseTutorial[nCntPauseTutorialTex]);
	}

	// ���_���
	MakeVertexPauseTutorial(pDevice);

	SetPauseTutorial(D3DXVECTOR3(float(SCREEN_WIDTH / 2), float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_MAIN,(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	// ���
	SetPauseTutorial(D3DXVECTOR3(float(SCREEN_WIDTH - 40.0f), float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_ARROW_RIGHT, 70.0f, 200.0f);
	SetPauseTutorial(D3DXVECTOR3(40.0f, float(SCREEN_HEIGHT / 2), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), PAUSETUTORIALTYPE_ARROW_LEFT, 70.0f, 200.0f);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�`���[�g���A���I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitPauseTutorial(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < PAUSETUTORIAL_TEX_MAX; nCntTex++)
	{
		if (g_pTexturePauseTutorial[nCntTex] != NULL)
		{
			g_pTexturePauseTutorial[nCntTex]->Release();
			g_pTexturePauseTutorial[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseTutorial != NULL)
	{
		g_pVtxBuffPauseTutorial->Release();
		g_pVtxBuffPauseTutorial = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�`���[�g���A���X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdatePauseTutorial(void)
{
	FADE pFade;
	// �t�F�[�h���[�h�̎擾
	pFade = GetFade();
	g_nSlideFrameCntPause++;
	g_nDispCounterPause++;

	//if (g_bSlideUsePause == false)
	//{ // �X���C�h���Ŗ����ꍇ

	//	if ((GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_D) == true || GetGamePadTrigger(ELECOM_RB) == true
	//		|| GetGamePadPovPress(POV_RIGHT) == true || GetGamePadStickTrigger(STICK_RIGHT) == true) && g_nCntPagePause != MAX_PAUSETUTORIALPAGE-1)
	//	{ // �y�[�W���ő�l�łȂ��ꍇ
	//		// �y�[�W��i�߂�
	//		g_nCntPagePause++;
	//		g_bSlideUsePause = true;
	//		g_nSlideFrameCntPause = 0;
	//		g_fSlideTexAnimAddPause = float(PAUSETUTORIALPAGE_PATTERN_ANIM / SLIDE_TIME);

	//	}
	//	else if ((GetKeyboardTrigger(DIK_LEFT) == true || GetKeyboardTrigger(DIK_A) == true || GetGamePadTrigger(ELECOM_LB) == true
	//		|| GetGamePadPovPress(POV_LEFT) == true || GetGamePadStickTrigger(STICK_LEFT) == true) && g_nCntPagePause != 0)
	//	{ // �y�[�W���ŏ��l�łȂ��ꍇ
	//		// �y�[�W�߂�
	//		g_nCntPagePause--;
	//		g_bSlideUsePause = true;
	//		g_nSlideFrameCntPause = 0;
	//		g_fSlideTexAnimAddPause = float(-PAUSETUTORIALPAGE_PATTERN_ANIM / SLIDE_TIME);

	//	}

	//}

	// �X���C�h�̃e�N�X�`���̒l�ɑ����l�����Z
	g_fSlideTexAnimPause += g_fSlideTexAnimAddPause;

	if (g_nSlideFrameCntPause == SLIDE_TIME && g_bSlideUsePause == true)
	{ // �X���C�h���Ńt���[���J�E���^�[���K��l�ɒB�����ꍇ
		g_nSlideFrameCntPause = 0;
		g_bSlideUsePause = false;
		g_fSlideTexAnimAddPause = 0.0f;
		g_fSlideTexAnimPause = g_nCntPagePause * PAUSETUTORIALPAGE_PATTERN_ANIM;
	}

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == true)
		{
			if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_MAIN)
			{ // �X���C�h
				pVtx[0].tex = D3DXVECTOR2(g_fSlideTexAnimPause, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_fSlideTexAnimPause + PAUSETUTORIALPAGE_PATTERN_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_fSlideTexAnimPause, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_fSlideTexAnimPause + PAUSETUTORIALPAGE_PATTERN_ANIM, 1.0f);
			}
			else if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_ARROW_RIGHT)
			{ // �E���
				if (g_nCntPagePause != MAX_PAUSETUTORIALPAGE - 1 && g_bSlideUsePause == false)
				{
					if (g_nDispCounterPause % g_aPauseTutorial[nCntPauseTutorial].nDispSpeed == 0)
					{
						g_aPauseTutorial[nCntPauseTutorial].bDisp = g_aPauseTutorial[nCntPauseTutorial].bDisp ? false : true;
					}
				}
				else
				{
					g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
				}
			}
			else if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_ARROW_LEFT)
			{ // �����
				if (g_nCntPagePause != 0 && g_bSlideUsePause == false)
				{
					if (g_nDispCounterPause % g_aPauseTutorial[nCntPauseTutorial].nDispSpeed == 0)
					{
						g_aPauseTutorial[nCntPauseTutorial].bDisp = g_aPauseTutorial[nCntPauseTutorial].bDisp ? false : true;
					}
				}
				else
				{
					g_aPauseTutorial[nCntPauseTutorial].bDisp = false;
				}
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseTutorial->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �|�[�Y�`���[�g���A���`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawPauseTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == true)
		{ // �|�[�Y�`���[�g���A�����g�p����Ă���
			if (g_aPauseTutorial[nCntPauseTutorial].bDisp == true)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturePauseTutorial[g_aPauseTutorial[nCntPauseTutorial].nTexType]);

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseTutorial * 4, 2);
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// PauseTutorial�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetPauseTutorial(D3DXVECTOR3 pos, D3DXCOLOR col, PAUSETUTORIALTYPE type, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++,pVtx+=4)
	{
		if (g_aPauseTutorial[nCntPauseTutorial].bUse == false)
		{ // �^�C�g�����g�p����Ă��Ȃ��ꍇ
		  // ���_�ʒu�̐ݒ�
			g_aPauseTutorial[nCntPauseTutorial].pos = pos;
			g_aPauseTutorial[nCntPauseTutorial].fWidth = fWidth;
			g_aPauseTutorial[nCntPauseTutorial].fHeight = fHeight;
			// �F�̐ݒ�
			g_aPauseTutorial[nCntPauseTutorial].col = col;
			// �|�[�Y�`���[�g���A���̎�ނ̐ݒ�
			g_aPauseTutorial[nCntPauseTutorial].type = type;
			g_aPauseTutorial[nCntPauseTutorial].nTexType = type;

			 // ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x - g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y - g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x + g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y - g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x - g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y + g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPauseTutorial[nCntPauseTutorial].pos.x + g_aPauseTutorial[nCntPauseTutorial].fWidth / 2, g_aPauseTutorial[nCntPauseTutorial].pos.y + g_aPauseTutorial[nCntPauseTutorial].fHeight / 2, 0.0f);

			pVtx[0].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[1].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[2].col = g_aPauseTutorial[nCntPauseTutorial].col;
			pVtx[3].col = g_aPauseTutorial[nCntPauseTutorial].col;

			if (g_aPauseTutorial[nCntPauseTutorial].type == PAUSETUTORIALTYPE_MAIN)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(PAUSETUTORIALPAGE_PATTERN_ANIM, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(PAUSETUTORIALPAGE_PATTERN_ANIM, 1.0f);
			}

			g_aPauseTutorial[nCntPauseTutorial].bDisp = true;	// �\����Ԃɂ���
			g_aPauseTutorial[nCntPauseTutorial].bUse = true;	// �g�p�����Ԃɂ���
			break;	// ����break�͂��Ȃ���
		}
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPauseTutorial->Unlock();
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexPauseTutorial(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSETUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseTutorial,
		NULL);

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseTutorial = 0; nCntPauseTutorial < MAX_PAUSETUTORIAL; nCntPauseTutorial++, pVtx += 4)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseTutorial->Unlock();

}