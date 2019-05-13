//=============================================================================
//
// �N���W�b�g���� [Clear.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "clear.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Clear_TEXTURENAME1	"data/TEXTURE/CLEAR/Clear.png"	// �ǂݍ��ރe�N�X�`���̖��O�P
#define Clear_TEXTURENAME2	"data/TEXTURE/CLEAR/Clear.jpg"	// �ǂݍ��ރe�N�X�`���̖��O�Q
#define Clear_TEXTURENAME3	"data/TEXTURE/CLEAR/PressAnyBotton000.png"		// �ǂݍ��ރe�N�X�`���̖��O�R
#define Clear_LOGO_POS_X		(140.0f)							// ���S��X���W
#define Clear_LOGO_POS_Y		(35.0f)								// ���S��Y���W
#define Clear_LOGO_WIDTH		(280.0f)							// ���S�̕�
#define Clear_LOGO_HEIGHT	(70.0f)								// ���S�̍���
#define Clear_ENTER_POS_X	(SCREEN_WIDTH /2)			// �G���^�[��X���W
#define Clear_ENTER_POS_Y	(SCREEN_HEIGHT /2 +230)				// �G���^�[��Y���W
#define Clear_ENTER_WIDTH	(300.0f)							// �G���^�[�̕�
#define Clear_ENTER_HEIGHT	(90.0f)								// �G���^�[�̍���
#define Clear_FLASH_ENTER	(60)								// �G���^�[�̓_�ŊԊu

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	ClearTEX_BG = 0,	// �w�i
	ClearTEX_ENTER,	// �G���^�[
	ClearTEX_MAX		// �e�N�X�`���̑���
} ClearTEX;

typedef struct
{
	int nCntFps;		// �o�ߎ���
	bool bPush;			// �����ꂽ���ǂ���
} Clear;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_apTextureClear[ClearTEX_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;
Clear g_Clear;
bool g_bDrawClear[ClearTEX_MAX];	// �`�悷�邩�ǂ���

//=============================================================================
// �N���A����������
//=============================================================================
void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// �ݒ�̏�����
	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++)
	{
		g_bDrawClear[nCntTex] = true;
		if (nCntTex == ClearTEX_ENTER)
		{// �G���^�[�̏ꍇ
			g_bDrawClear[nCntTex] = false;
		}
	}
	g_Clear.nCntFps = 0;
	g_Clear.bPush = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME1, &g_apTextureClear[ClearTEX_BG]);
	D3DXCreateTextureFromFile(pDevice, Clear_TEXTURENAME3, &g_apTextureClear[ClearTEX_ENTER]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ClearTEX_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_2D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffClear
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		if (nCntTex == ClearTEX_BG)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}

		else if (nCntTex == ClearTEX_ENTER)
		{
			pVtx[0].pos = D3DXVECTOR3(Clear_ENTER_POS_X - Clear_ENTER_WIDTH / 2-100, Clear_ENTER_POS_Y - Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(Clear_ENTER_POS_X + Clear_ENTER_WIDTH / 2 + 100, Clear_ENTER_POS_Y - Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(Clear_ENTER_POS_X - Clear_ENTER_WIDTH / 2 - 100, Clear_ENTER_POS_Y + Clear_ENTER_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(Clear_ENTER_POS_X + Clear_ENTER_WIDTH / 2 + 100, Clear_ENTER_POS_Y + Clear_ENTER_HEIGHT / 2, 0.0f);
		}

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		if (nCntTex == ClearTEX_ENTER)
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
	g_pVtxBuffClear->Unlock();


}

//=============================================================================
// �N���A�I������
//=============================================================================
void UninitClear(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < ClearTEX_MAX; nCntTex++)
	{
		if (g_apTextureClear[nCntTex] != NULL)
		{
			g_apTextureClear[nCntTex]->Release();
			g_apTextureClear[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}

}

//=============================================================================
// �N���A�X�V����
//=============================================================================
void UpdateClear(void)
{
	FADE pFade = *GetFade(); // �t�F�[�h�̎擾


	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(DIJS_BUTTON_1, 0) == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (pFade == FADE_NONE)
		{// �t�F�[�h���������Ă��Ȃ���Ԃ̏ꍇ
			PlaySound(SOUND_LABEL_SE000);
			g_Clear.bPush = true;
			SetFade(MODE_SELCT);
		}
	}


	g_Clear.nCntFps++;
	if (g_Clear.bPush == true)
	{// ����L�[(ENTER�L�[)�������ꂽ�ꍇ
		if (g_Clear.nCntFps % 2 == 0)
		{
			g_bDrawClear[ClearTEX_ENTER] = g_bDrawClear[ClearTEX_ENTER] ? false : true;
		}
	}
	else
	{// ����L�[(ENTER�L�[)��������Ă��Ȃ��ꍇ
		if (g_Clear.nCntFps % Clear_FLASH_ENTER == 0)
		{// �P�b�o�߂����ꍇ
			g_bDrawClear[ClearTEX_ENTER] = g_bDrawClear[ClearTEX_ENTER] ? false : true;
		}
	}
}

//=============================================================================
// �N���A�`�揈��
//=============================================================================
void DrawClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾����
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_bDrawClear[nCntTex] == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureClear[nCntTex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP	// �v���~�e�B�u�̎��
				, nCntTex * 4		// �J�n���钸�_�̃C���f�b�N�X
				, 2);				// �`�悷��v���~�e�B�u�̐�
		}
	}
}
