//=============================================================================
//
// �`���[�g���A������ [Tutorial.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "Tutorial.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Tutorial_TEXTURENAME1	"data/TEXTURE/TUTORIAL/Tutorial.png"	// �ǂݍ��ރe�N�X�`���̖��O�P
#define Tutorial_TEXTURENAME2	"data/TEXTURE/TUTORIAL/Tutorial.jpg"	// �ǂݍ��ރe�N�X�`���̖��O�Q
#define Tutorial_TEXTURENAME3	"data/TEXTURE/TUTORIAL/PressAnyBotton000.png"		// �ǂݍ��ރe�N�X�`���̖��O�R
#define Tutorial_LOGO_POS_X		(140.0f)							// ���S��X���W
#define Tutorial_LOGO_POS_Y		(35.0f)								// ���S��Y���W
#define Tutorial_LOGO_WIDTH		(280.0f)							// ���S�̕�
#define Tutorial_LOGO_HEIGHT	(70.0f)								// ���S�̍���
#define Tutorial_ENTER_POS_X	(SCREEN_WIDTH  - 180.0f)			// �G���^�[��X���W
#define Tutorial_ENTER_POS_Y	(SCREEN_HEIGHT - 70.0f)				// �G���^�[��Y���W
#define Tutorial_ENTER_WIDTH	(300.0f)							// �G���^�[�̕�
#define Tutorial_ENTER_HEIGHT	(90.0f)								// �G���^�[�̍���
#define Tutorial_FLASH_ENTER	(60)								// �G���^�[�̓_�ŊԊu

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	TutorialTEX_BG = 0,	// �w�i
	TutorialTEX_ENTER,	// �G���^�[
	TutorialTEX_MAX		// �e�N�X�`���̑���
} TutorialTEX;

typedef struct
{
	int nCntFps;		// �o�ߎ���
	bool bPush;			// �����ꂽ���ǂ���
} Tutorial;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureTutorial[TutorialTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
Tutorial g_Tutorial;
bool g_bDrawTutorial[TutorialTEX_MAX];	// �`�悷�邩�ǂ���

//=============================================================================
// �`���[�g���A������������
//=============================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �ݒ�̏�����
	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++)
	{
		g_bDrawTutorial[nCntTex] = true;
		if (nCntTex == TutorialTEX_ENTER)
		{// �G���^�[�̏ꍇ
			g_bDrawTutorial[nCntTex] = false;
		}
	}
	g_Tutorial.nCntFps = 0;
	g_Tutorial.bPush = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME1, &g_apTextureTutorial[TutorialTEX_BG]);
	D3DXCreateTextureFromFile(pDevice, Tutorial_TEXTURENAME3, &g_apTextureTutorial[TutorialTEX_ENTER]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TutorialTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTutorial
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		if (nCntTex == TutorialTEX_BG)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}

		else if (nCntTex == TutorialTEX_ENTER)
		{
			pVtx[0].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X - Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y - Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X + Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y - Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X - Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y + Tutorial_ENTER_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Tutorial_ENTER_POS_X + Tutorial_ENTER_WIDTH / 2, Tutorial_ENTER_POS_Y + Tutorial_ENTER_HEIGHT / 2, 0.0f);
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		if (nCntTex == TutorialTEX_ENTER)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();


}

//=============================================================================
// �`���[�g���A���I������
//=============================================================================
void UninitTutorial(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < TutorialTEX_MAX; nCntTex++)
	{
		if (g_apTextureTutorial[nCntTex] != NULL)
		{
			g_apTextureTutorial[nCntTex]->Release();
			g_apTextureTutorial[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}

//=============================================================================
// �`���[�g���A���X�V����
//=============================================================================
void UpdateTutorial(void)
{
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾


	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (pFade == FADE_NONE)
		{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
			PlaySound(SOUND_LABEL_SE000);
			g_Tutorial.bPush = true;
			SetFade(MODE_SELCT);
		}
	}


	g_Tutorial.nCntFps++;
	if (g_Tutorial.bPush == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (g_Tutorial.nCntFps % 2 == 0)
		{
			g_bDrawTutorial[TutorialTEX_ENTER] = g_bDrawTutorial[TutorialTEX_ENTER] ? false : true;
		}
	}
	else
	{// ����L�[(ENTER�L�[)��������Ă��Ȃ��ꍇ
		if (g_Tutorial.nCntFps % Tutorial_FLASH_ENTER == 0)
		{// �P�b�o�߂����ꍇ
			g_bDrawTutorial[TutorialTEX_ENTER] = g_bDrawTutorial[TutorialTEX_ENTER] ? false : true;
		}
	}
}

//=============================================================================
// �`���[�g���A���`�揈��
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_bDrawTutorial[nCntTex] == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorial[nCntTex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// �v���~�e�B�u�̎��
				, nCntTex * 4		// �J�n���钸�_�̃C���f�b�N�X
				, 2);				// �`�悷��v���~�e�B�u�̐�
		}
	}
}
