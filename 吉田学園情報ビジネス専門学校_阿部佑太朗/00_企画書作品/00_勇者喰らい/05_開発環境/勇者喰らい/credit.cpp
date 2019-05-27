//=============================================================================
//
// �N���W�b�g���� [Credit.cpp]
// Author : 
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "credit.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Credit_TEXTURENAME1	"data/TEXTURE/CREDIT/credit.png"	// �ǂݍ��ރe�N�X�`���̖��O�P
#define Credit_TEXTURENAME2	"data/TEXTURE/CREDIT/credit.jpg"	// �ǂݍ��ރe�N�X�`���̖��O�Q
#define Credit_TEXTURENAME3	"data/TEXTURE/CREDIT/PressAnyBotton000.png"		// �ǂݍ��ރe�N�X�`���̖��O�R
#define Credit_LOGO_POS_X		(140.0f)							// ���S��X���W
#define Credit_LOGO_POS_Y		(35.0f)								// ���S��Y���W
#define Credit_LOGO_WIDTH		(280.0f)							// ���S�̕�
#define Credit_LOGO_HEIGHT	(70.0f)								// ���S�̍���
#define Credit_ENTER_POS_X	(SCREEN_WIDTH  - 180.0f)			// �G���^�[��X���W
#define Credit_ENTER_POS_Y	(SCREEN_HEIGHT - 70.0f)				// �G���^�[��Y���W
#define Credit_ENTER_WIDTH	(300.0f)							// �G���^�[�̕�
#define Credit_ENTER_HEIGHT	(90.0f)								// �G���^�[�̍���
#define Credit_FLASH_ENTER	(60)								// �G���^�[�̓_�ŊԊu

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	CreditTEX_BG = 0,	// �w�i
	CreditTEX_ENTER,	// �G���^�[
	CreditTEX_MAX		// �e�N�X�`���̑���
} CreditTEX;

typedef struct
{
	int nCntFps;		// �o�ߎ���
	bool bPush;			// �����ꂽ���ǂ���
} Credit;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureCredit[CreditTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCredit = NULL;
Credit g_Credit;
bool g_bDrawCredit[CreditTEX_MAX];	// �`�悷�邩�ǂ���

//=============================================================================
// �`���[�g���A������������
//=============================================================================
void InitCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �ݒ�̏�����
	for (int nCntTex = 0; nCntTex < CreditTEX_MAX; nCntTex++)
	{
		g_bDrawCredit[nCntTex] = true;
		if (nCntTex == CreditTEX_ENTER)
		{// �G���^�[�̏ꍇ
			g_bDrawCredit[nCntTex] = false;
		}
	}
	g_Credit.nCntFps = 0;
	g_Credit.bPush = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Credit_TEXTURENAME1, &g_apTextureCredit[CreditTEX_BG]);
	D3DXCreateTextureFromFile(pDevice, Credit_TEXTURENAME3, &g_apTextureCredit[CreditTEX_ENTER]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * CreditTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffCredit
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCredit->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < CreditTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		if (nCntTex == CreditTEX_BG)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		
		else if (nCntTex == CreditTEX_ENTER)
		{
			pVtx[0].pos = D3DXVECTOR3(Credit_ENTER_POS_X - Credit_ENTER_WIDTH / 2, Credit_ENTER_POS_Y - Credit_ENTER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Credit_ENTER_POS_X + Credit_ENTER_WIDTH / 2, Credit_ENTER_POS_Y - Credit_ENTER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Credit_ENTER_POS_X - Credit_ENTER_WIDTH / 2, Credit_ENTER_POS_Y + Credit_ENTER_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Credit_ENTER_POS_X + Credit_ENTER_WIDTH / 2, Credit_ENTER_POS_Y + Credit_ENTER_HEIGHT / 2, 0.0f);
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		if (nCntTex == CreditTEX_ENTER)
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
	g_pVtxBuffCredit->Unlock();

	
}

//=============================================================================
// �`���[�g���A���I������
//=============================================================================
void UninitCredit(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < CreditTEX_MAX; nCntTex++)
	{
		if (g_apTextureCredit[nCntTex] != NULL)
		{
			g_apTextureCredit[nCntTex]->Release();
			g_apTextureCredit[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCredit != NULL)
	{
		g_pVtxBuffCredit->Release();
		g_pVtxBuffCredit = NULL;
	}

}

//=============================================================================
// �`���[�g���A���X�V����
//=============================================================================
void UpdateCredit(void)
{
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾
	PLAYER *pPlayer = GetPlayer();


	if (GetKeyboardTrigger(DIK_RETURN) == true || pPlayer[0].bButton[BUTTON_ENTER] == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (pFade == FADE_NONE)
		{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
			PlaySound(SOUND_LABEL_ENTER);
			g_Credit.bPush = true;
			SetFade(MODE_SELCT,0,0.0,0);
		}
	}
	

	g_Credit.nCntFps++;
	if (g_Credit.bPush == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (g_Credit.nCntFps % 2 == 0)
		{
			g_bDrawCredit[CreditTEX_ENTER] = g_bDrawCredit[CreditTEX_ENTER] ? false : true;
		}
	}
	else
	{// ����L�[(ENTER�L�[)��������Ă��Ȃ��ꍇ
		if (g_Credit.nCntFps % Credit_FLASH_ENTER == 0)
		{// �P�b�o�߂����ꍇ
			g_bDrawCredit[CreditTEX_ENTER] = g_bDrawCredit[CreditTEX_ENTER] ? false : true;
		}
	}
}

//=============================================================================
// �`���[�g���A���`�揈��
//=============================================================================
void DrawCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCredit, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_bDrawCredit[nCntTex] == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureCredit[nCntTex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// �v���~�e�B�u�̎��
				, nCntTex * 4		// �J�n���钸�_�̃C���f�b�N�X
				, 2);				// �`�悷��v���~�e�B�u�̐�
		}
	}
}
