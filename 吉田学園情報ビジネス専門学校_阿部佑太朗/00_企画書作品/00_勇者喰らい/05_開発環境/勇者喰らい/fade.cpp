//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "main.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FADE_TEX		(3)
#define Fade_TextureName	"data/TEXTURE/�`���[�g���A��001.jpg"				//FADE��TEXTURE��
#define Fade_TextureName1	"data/TEXTURE/�`���[�g���A��002.jpg"				//FADE��TEXTURE��
#define Fade_TextureName2	"data/TEXTURE/�`���[�g���A��003.jpg"				//FADE��TEXTURE��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade[MAX_FADE_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F
int						g_nTypeFade;			//�X�V���e
int						g_nTex;			//�摜

//=============================================================================
// ����������
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fade = FADE_IN;	//�����^�������
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR{ 0.0f,0.0f,0.0f,1.0f };
	g_nTypeFade = 0;
	g_nTex = 0;

	D3DXCreateTextureFromFile(pDevice, Fade_TextureName, &g_pTextureFade[0]);	//�`���[�g���A���쐬��
	D3DXCreateTextureFromFile(pDevice, Fade_TextureName1, &g_pTextureFade[1]);	//�`���[�g���A���L�[�{�[�h�퓬��
	D3DXCreateTextureFromFile(pDevice, Fade_TextureName2, &g_pTextureFade[2]);	//�`���[�g���A���W���C�p�b�h�퓬��

	// �l�̏�����
	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//X,Y,0.0f
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�ݒ�
	pVtx[0].col = g_colorFade;	// A = �����x
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_BUFFER���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	for (int nCount = 0; nCount < MAX_FADE_TEX; nCount++)
	{
		if (g_pTextureFade[nCount] != NULL)
		{
			g_pTextureFade[nCount]->Release();
			g_pTextureFade[nCount] = NULL;
		}
	}
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	PLAYER *pPlayer = GetPlayer();

	if (g_fade != FADE_NONE)
	{//�t�F�[�h���
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
		//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		if (g_fade == FADE_IN)
		{//���邭�ȁ`��
			g_colorFade.a -= 0.03f;
			if (g_colorFade.a <= 0.0f)
			{//���S�ɓ����ɂȂ�����
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if(g_fade == FADE_OUT)
		{//�Â��ȁ`��
			g_colorFade.a += 0.03f;
			if (g_colorFade.a >= 1.0f)
			{//���S�ɕs�����ɂȂ�����
				g_colorFade.a = 1.0f;
				SetMode(g_modeNext, g_nTypeFade);

				if (g_nTypeFade == 0 || g_nTypeFade == 1)
				{//���̂܂ܐ���
					g_fade = FADE_IN;
				}
				else
				{
					g_fade = FADE_ENTER;
					LoadBreakWindow();
					SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.95f, 0.0f), D3DXCOLOR{ 1.0f,0.99f,0.04f, 1.0f }, 150, 30, 0, 0, WINDOWSTATE_FLASH, WINDOWUSE_LOAD);
				}
			}
		}
		else if (g_fade == FADE_ENTER && pPlayer[0].bButton[BUTTON_ENTER] == true)
		{
			g_fade = FADE_IN;
			LoadBreakWindow();
		}
		//�J���[�ݒ�
		pVtx[0].col = g_colorFade;	// A = �����x
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//���_BUFFER���A�����b�N����
		g_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade[g_nTex]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_�o�b�t�@�̏���ݒ�

}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFade(MODE modeNext, int nTypeFade, float fCola, int nTex)
{
	if (g_fade == FADE_NONE)
	{
		g_nTex = nTex;
		g_nTypeFade = nTypeFade;
		g_fade = FADE_OUT;		//�Â��ȁ`��
		//�؂�ւ��̗\��
		if (nTypeFade == 1)
		{
			MODE *pmode = GetMode();
			g_modeNext = pmode[0];
		}
		else{ g_modeNext = modeNext; }
		if (nTypeFade == 0 || nTypeFade == 1) { g_colorFade = D3DXCOLOR{ 0.0f,0.0f,0.0f,0.0f }; }
		else
		{
		g_colorFade = D3DXCOLOR{ 1.0f,1.0f,1.0f,0.0f };
		SetFadeWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.95f, 0.0f), D3DXCOLOR{ 0.0f,0.0f,0.0f, 0.0f }, 150, 30, 1, 0, WINDOWSTATE_FADEIN, WINDOWUSE_LOAD);
		}
	}
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADE *GetFade(void)
{
	return &g_fade;
}

