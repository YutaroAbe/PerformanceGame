//=========================================================================================================//
//
// �w�i���� [bg.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "camera.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define MAX_FONT			(48)
#define MAX_FONT_TYPE		(8)
#define SETFONT_WIDE		(SCREEN_WIDTH * 0.35)
#define SETFONT_HEIGHT		(SCREEN_HEIGHT * 0.4)
#define Font_TextureName	"data/TEXTURE/50on.jpg"		//50���\

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9 g_pTextureFont = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFont = NULL;	//���_BUFFER�ւ̃|�C���^
LPD3DXFONT			g_pFont[MAX_FONT_TYPE] = {};			// �t�H���g�ւ̃|�C���^
Font				g_Font[MAX_FONT];
int					g_nSetFont = 0;
//=========================================================================================================//
// ����������
//=========================================================================================================//
void InitFont(void)
{
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		//g_Font[nCntFont].rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		g_Font[nCntFont].bUse = false;
		g_Font[nCntFont].bDisplay = false;
		g_Font[nCntFont].draw = WINDOW_DRAW_2;
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, Font_TextureName, &g_pTextureFont);	//�^�C�g��

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffFont,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);		//X,Y,0.0f
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// A = �����x
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//���_BUFFER���A�����b�N����
	g_pVtxBuffFont->Unlock();

	D3DXCreateFont(pDevice, 48, 18, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[0]);
	D3DXCreateFont(pDevice, 40, 12, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[1]);
	D3DXCreateFont(pDevice, 25, 9, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[2]);
	D3DXCreateFont(pDevice, 58, 22, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[3]);
	D3DXCreateFont(pDevice, 100, 34, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[4]);
	D3DXCreateFont(pDevice, 68, 32, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[5]);
	D3DXCreateFont(pDevice, 110, 44, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[6]);
	D3DXCreateFont(pDevice, 34, 11, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont[7]);
}
//=========================================================================================================//
// �I������
//=========================================================================================================//
void UninitFont(void)
{
	BreakFont();
	for (int nCntFont = 0; nCntFont < MAX_FONT_TYPE; nCntFont++)
	{
		if (g_pFont[nCntFont] != NULL)
		{// �f�o�b�O�\���p�t�H���g�̊J��
			g_pFont[nCntFont]->Release();
			g_pFont[nCntFont] = NULL;
		}
	}

	if (g_pTextureFont != NULL)
	{
		g_pTextureFont->Release();
		g_pTextureFont = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFont != NULL)
	{
		g_pVtxBuffFont->Release();
		g_pVtxBuffFont = NULL;
	}
}
//=========================================================================================================//
// �X�V����
//=========================================================================================================//
void UpdateFont(void)
{
	int nCntFont;
	Camera *pCamera = GetCamera();

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == true)
		{//�������\����ԂȂ�
			switch (g_Font[nCntFont].state)
			{
			case FONTSTATE_NONE:
				if (pCamera[0].state == CAMERA_STATE_MOVIE) { g_Font[nCntFont].bDisplay = false; }
				else { g_Font[nCntFont].bDisplay = true; }
				break;
			case FONTSTATE_DELETE:
				g_Font[nCntFont].rect.bottom -= 1;
				g_Font[nCntFont].rect.top -= 1;
				g_Font[nCntFont].col.a -= 0.01f;
				if (g_Font[nCntFont].col.a < 0.0f) { g_Font[nCntFont].bUse = false; }
				break;
			case FONTSTATE_FLASH:
				g_Font[nCntFont].nCntState++;
				if (g_Font[nCntFont].nCntState % 2 == 0) { g_Font[nCntFont].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);}
				else{ g_Font[nCntFont].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				break;
			case FONTSTATE_FLASH0:
				g_Font[nCntFont].nCntState++;
				if (g_Font[nCntFont].nCntState % 2 == 0) { g_Font[nCntFont].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f); }
				else { g_Font[nCntFont].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); }
				break;
			case FONTSTATE_FLOW:
				if (g_Font[nCntFont].nCntState == 0)
				{//������E�ɗ���Ȃ���\��
					g_Font[nCntFont].col.a += 0.05f;
					g_Font[nCntFont].rect.left += 20;
					g_Font[nCntFont].rect.right += 20;
					if (g_Font[nCntFont].col.a >= 1.0f)
					{
						g_Font[nCntFont].col.a = 1.0f;
						g_Font[nCntFont].nCntState = 1;
					}
				}
				else
				{//���Ԍo�߂�
					g_Font[nCntFont].nCntState++;
					if (g_Font[nCntFont].nCntState > 120)
					{//����Ɏ��Ԍo�߂�
						g_Font[nCntFont].col.a -= 0.029f;
						g_Font[nCntFont].rect.left += 8;
						g_Font[nCntFont].rect.right += 8;
						if (g_Font[nCntFont].col.a <= 0.0f)
						{//�E�ɗ���Ȃ��������
							g_Font[nCntFont].col.a = 0.0f;
							g_Font[nCntFont].bUse = false;
						}
					}
				}
			}
		}
	}
}

//=========================================================================================================//
// �`�揈��
//=========================================================================================================//
void DrawFont(WINDOW_DRAW draw)
{
	int nCntFont;
	D3DCOLOR col;
	RECT rect;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	char aStr[84];
	char aStr0[84];		//\n�m�F�p
	int nLength;
	
	if (g_nSetFont != 0 && draw == WINDOW_DRAW_1)
	{//50���\�\��
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
		//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, (g_nSetFont - 1.0f) * (1.0f / 3.0f));
		pVtx[1].tex = D3DXVECTOR2(1.0f, (g_nSetFont - 1.0f) * (1.0f / 3.0f));
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_nSetFont * (1.0f / 3.0f));
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_nSetFont * (1.0f / 3.0f));

		//���_BUFFER���A�����b�N����
		g_pVtxBuffFont->Unlock();

		LPDIRECT3DDEVICE9 pDevice;
		//�f�o�C�X���擾����
		pDevice = GetDevice();


		//���_BUFFER���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffFont, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

										//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFont);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == true && g_Font[nCntFont].bDisplay == true && g_Font[nCntFont].draw == draw)
		{// ��������� �\��
			strcpy(&aStr[0], &g_Font[nCntFont].aStr[0]);
			if (g_Font[nCntFont].nMaxFont > -1)
			{//�����������߂��Ă���
				nLength = (int)strlen(&aStr[0]);
				if (nLength > g_Font[nCntFont].nMaxFont)
				{//������̂ق�������
					strcpy(&aStr[g_Font[nCntFont].nMaxFont], "\0");
					g_Font[nCntFont].nCntTime--;
					if (g_Font[nCntFont].nCntTime == 0)
					{//�J�E���g���i��
						strcpy(&aStr0[0], &g_Font[nCntFont].aStr[0]);
						strcpy(&aStr0[g_Font[nCntFont].nMaxFont + 1], "\0");
						if(strcmp(&aStr0[g_Font[nCntFont].nMaxFont], "\n") == 0){ g_Font[nCntFont].nMaxFont++; }
						g_Font[nCntFont].nCntTime = SPEECH_FLOW;
						g_Font[nCntFont].nMaxFont += 2;
						if (nLength <= g_Font[nCntFont].nMaxFont){ g_Font[nCntFont].nMaxFont = -1; }
					}
				}
			}

			if (g_Font[nCntFont].bshadow == true)
			{
				col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				rect = g_Font[nCntFont].rect;
				rect.left += 2; rect.top += 2; rect.right += 2; rect.bottom += 2;
				g_pFont[g_Font[nCntFont].nType]->DrawText(NULL, &aStr[0], -1, &rect, g_Font[nCntFont].nFormat, col);
			}
			col = g_Font[nCntFont].col;
			g_pFont[g_Font[nCntFont].nType]->DrawText(NULL, &aStr[0], -1, &g_Font[nCntFont].rect, g_Font[nCntFont].nFormat, col);
		}
	}
	//DT_LEFT;
}
//=========================================================================================================//
// �����������  Set!!
//=========================================================================================================//
void SetFont(RECT rect, D3DXCOLOR col, char *aStr, int nNumber, int nType, int nFormat, int nMaxFont, bool bShadow, FONTSTATE state, WINDOW_DRAW draw)
{//�����Z�b�g
	g_Font[nNumber].bUse = true;
	g_Font[nNumber].bDisplay = true;
	g_Font[nNumber].draw = draw;
	g_Font[nNumber].state = state;
	g_Font[nNumber].nType = nType;
	g_Font[nNumber].nFormat = nFormat;
	g_Font[nNumber].nMaxFont = nMaxFont;
	g_Font[nNumber].nCntTime = 0;
	g_Font[nNumber].rect = rect;
	strcpy(&g_Font[nNumber].aStr[0], &aStr[0]);
	g_Font[nNumber].col = col;
	g_Font[nNumber].nCntState = 0;
	g_Font[nNumber].bshadow = bShadow;
}
//=========================================================================================================//
// �����������  Set!!
//=========================================================================================================//
void SetFontDamage(RECT rect, D3DCOLOR col, char *aStr, int nWide, int nHeight, FONTSTATE state)
{//�����Z�b�g
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == false)
		{
			g_Font[nCntFont].bUse = true;
			g_Font[nCntFont].bDisplay = true;
			g_Font[nCntFont].state = state;
			g_Font[nCntFont].rect = rect;
			strcpy(&g_Font[nCntFont].aStr[0], &aStr[0]);
			g_Font[nCntFont].col = col;
			g_Font[nCntFont].nCntState = 0;
			break;
		}
	}

}
//=========================================================================================================//
// �����������  Change!!
//=========================================================================================================//
void ChangeFont(bool bUse, char *aStr, int nNumber, int nStrType, int nMaxFont, int nCntTime, FONTSTATE state, D3DCOLOR col)
{//�Z�b�g���ꂽ���̂�ύX
	if (g_Font[nNumber].bUse == true)
	{
		g_Font[nNumber].bUse = bUse;
		if (bUse == true)
		{
			g_Font[nNumber].state = state;
			g_Font[nNumber].nMaxFont = nMaxFont;
			g_Font[nNumber].nCntTime = nCntTime;
			g_Font[nNumber].col = col;

			switch (nStrType)
			{
			case 0:
				if (aStr[0] != NULL) { strcpy(&g_Font[nNumber].aStr[0], &aStr[0]); }//NULL����Ȃ���΍X�V
				break;
			case 1:
				g_Font[nNumber].nMaxFont = (int)strlen(&g_Font[nNumber].aStr[0]);
				if (aStr[0] != NULL) { strcat(&g_Font[nNumber].aStr[0], &aStr[0]); }//NULL����Ȃ���΍X�V
				break;
			}
		}
	}
}
//=========================================================================================================//
// ������S�Ĕj��
//=========================================================================================================//
void BreakFont(void)
{//�Z�b�g���ꂽ���������ׂĔj��
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		g_Font[nCntFont].bUse = false;
	}

}
//=========================================================================================================//
// �Z�b�g����Ă���50���̎擾
//=========================================================================================================//
int *GetSetFont(void)
{
	return &g_nSetFont;
}
//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void FontScroll(D3DXVECTOR3 move)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_FONT; nCntItem++)
	{
		if (g_Font[nCntItem].bUse == true && g_Font[nCntItem].state == FONTSTATE_DELETE)
		{//�X�N���[��
			//g_Font[nCntItem].rect.top += (int)move.y;
			//g_Font[nCntItem].rect.bottom += (int)move.y;
			//g_Font[nCntItem].rect.left += (int)move.x;
			//g_Font[nCntItem].rect.right += (int)move.x;
		}
	}
}