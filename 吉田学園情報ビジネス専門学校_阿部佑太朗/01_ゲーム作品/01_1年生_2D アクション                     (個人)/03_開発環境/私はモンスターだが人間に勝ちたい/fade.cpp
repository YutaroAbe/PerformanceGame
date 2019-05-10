//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_TEXTURENAMRE1 "data/TEXTURE/fade000.png" //�ǂݍ��ރe�N�X�`��

#define BG_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define BG_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = FADE_IN;	//�t�F�[�h�̏�Ԃ�
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);	//�������(�s����)�ɂ��Ă���

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAMRE1, &g_pTextureFade);


	// ���_���̐ݒ�
	MakeVertexFade(pDevice);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);				 //����
	pVtx[3].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);		 //����
														 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;									//���_���̃|�C���^							
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)	//�t�F�[�h���
		{
			g_colorFade.r -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���
			g_colorFade.g -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���
			g_colorFade.b -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���
			g_colorFade.a -= 1.0f / 60;	//��ʂ𓧖��ɂ��Ă���

			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//�������Ă��Ȃ����
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.r += 1.0f / 60;
			g_colorFade.g += 1.0f / 60;
			g_colorFade.b += 1.0f / 60;
			g_colorFade.a += 1.0f / 60;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;	//�t�F�[�h��Ԃ�

				//���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}
		//�J���[
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//���_�o�b�t�@�A�����b�N����
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
	pDevice->SetTexture(0, g_pTextureFade);

	if (g_colorFade.a >= 0.25f)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�������(����)�ɂ��Ă���
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADE *GetFade(void)
{
	return &g_fade;
}