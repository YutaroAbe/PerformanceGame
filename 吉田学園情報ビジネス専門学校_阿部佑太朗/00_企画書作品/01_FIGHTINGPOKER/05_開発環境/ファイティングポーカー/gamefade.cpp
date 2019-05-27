//=============================================================================
//
// �Q�[���t�F�[�h���� [gamefade.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "gamefade.h"
#include "poker.h"
#include "cardModel.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_TEXTURENAME	"data//TEXTURE//fadeTitle.jpg"			//�ǂݍ��ޔw�i
#define NUM_FADE			(2)
#define FADE_POS_X			(0)								//�t�F�[�h�̍���X���W
#define FADE_POS_Y			(0)								//�t�F�[�h�̍���Y���W

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGameFade = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameFade = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
GAMEFADE				g_Gamefade;							// �t�F�[�h���
GAMEMODE				g_GameNext;						// ���̃��[�h
D3DXCOLOR				g_colorGameFade;				// �t�F�[�h�F
CARDSIDE				g_SideNext;						// 1P2P���
bool g_bChangeMode;
bool g_bChangeSide;
//=============================================================================
// ����������
//=============================================================================
void InitGameFade(GAMEMODE mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_Gamefade = GAMEFADE_IN;			//�t�F�[�h�C�����
	g_GameNext = mode;
	g_SideNext = CARD_SIDE_1P;
	g_bChangeMode = false;
	g_bChangeSide = false;
	g_colorGameFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FADE_TEXTURENAME, &g_pTextureGameFade);

	// ���_���̐ݒ�
	MakeVertexGameFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGameFade != NULL)
	{
		g_pTextureGameFade->Release();
		g_pTextureGameFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameFade != NULL)
	{
		g_pVtxBuffGameFade->Release();
		g_pVtxBuffGameFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameFade(void)
{
	VERTEX_2D *pVtx;

	if (g_Gamefade != GAMEFADE_NONE)
	{
		if (g_Gamefade == GAMEFADE_IN)			//�t�F�[�h�C����Ԃɂ���
		{
			g_colorGameFade.a -= 0.05f;			//��ʂ𓧖��ɂ��Ă���
			if (g_colorGameFade.a <= 0.0f)
			{
				g_colorGameFade.a -= 0.0f;
				g_Gamefade = GAMEFADE_NONE;
			}
		}
		else if (g_Gamefade == GAMEFADE_OUT)
		{
			g_colorGameFade.a += 0.07f;			//��ʂ�s�����ɂ��Ă���
			if (g_colorGameFade.a >= 1.0f)
			{
				g_colorGameFade.a += 1.0f;
				g_Gamefade = GAMEFADE_IN;
				//���[�h�̐ݒ�
				if (g_bChangeMode == true)
				{
					SetGameMode(g_GameNext);
					g_bChangeMode = false;
				}
				if (g_bChangeSide == true)
				{
					SetSide(g_SideNext);
					g_bChangeSide = false;
				}
			}
		}
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = g_colorGameFade;
		pVtx[1].col = g_colorGameFade;
		pVtx[2].col = g_colorGameFade;
		pVtx[3].col = g_colorGameFade;
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffGameFade->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawGameFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffGameFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_FADE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameFade,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�|���S���̐F
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameFade->Unlock();
}
//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetGameFade(GAMEMODE modeNext)
{
	g_Gamefade = GAMEFADE_OUT;					//�t�F�[�h�A�E�g��Ԃ�
	g_bChangeMode = true;
	g_GameNext = modeNext;
	g_colorGameFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}
//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetPokerFade(CARDSIDE sideNext)
{
	g_Gamefade = GAMEFADE_OUT;					//�t�F�[�h�A�E�g��Ԃ�
	g_bChangeSide = true;
	g_SideNext = sideNext;
	g_colorGameFade = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
}
//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
GAMEFADE GetGameFade(void)
{
	return g_Gamefade;
}
