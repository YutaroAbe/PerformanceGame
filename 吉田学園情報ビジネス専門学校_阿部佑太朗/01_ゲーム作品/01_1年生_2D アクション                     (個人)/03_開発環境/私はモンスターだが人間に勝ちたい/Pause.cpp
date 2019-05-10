//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "game2.h"
#include "game3.h"
#include "game.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/pause100.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE1 "data/TEXTURE/pause000.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE2 "data/TEXTURE/pause001.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE3 "data/TEXTURE/pause002.png" //�ǂݍ��ރe�N�X�`��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[4] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Pause[4];
int g_nSelectMenu;
D3DXCOLOR g_PColor;
MODE g_PMODE;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
													//�f�o�C�X�擾
	pDevice = GetDevice();

	g_PColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	g_PMODE = MODE_TITLE;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		g_Pause[0] = D3DXVECTOR2(630, 370);
		g_Pause[1] = D3DXVECTOR2(630, 270);
		g_Pause[2] = D3DXVECTOR2(630, 370);
		g_Pause[3] = D3DXVECTOR2(630, 470);
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTexturePause[0]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTexturePause[1]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTexturePause[2]);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTexturePause[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Pause[0].x - 150.0f, g_Pause[0].y - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Pause[0].x + 150.0f, g_Pause[0].y - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Pause[0].x - 150.0f, g_Pause[0].y + 150.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Pause[0].x + 150.0f, g_Pause[0].y + 150.0f, 0.0f);
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
														//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPause->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0 + 1; nCount < 4; nCount++)
	{
		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[4].pos = D3DXVECTOR3(g_Pause[nCount].x - 100.0f, g_Pause[nCount].y - 30.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Pause[nCount].x + 100.0f, g_Pause[nCount].y - 30.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Pause[nCount].x - 100.0f, g_Pause[nCount].y + 30.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Pause[nCount].x + 100.0f, g_Pause[nCount].y + 30.0f, 0.0f);
		//RHW
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;
		//�J���[
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		//�e�N�X�`�����W
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPause->Unlock();

	g_nSelectMenu = 0;

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitPause(void)
{
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount]->Release();
			g_pTexturePause[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdatePause(void)
{
	FADE pFade;
	pFade = *GetFade();

	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_nSelectMenu = (g_nSelectMenu + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_nSelectMenu = (g_nSelectMenu + 2) % 3;
	}
	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[�ŃZ���N�g��ʂ�
		 //�L�[�{�[�h�ݒ�
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);
				switch (g_nSelectMenu)
				{
				case  0:
					PaauseGame();
					PaauseGame2();
					break;
				case 1:
						//���[�h�ݒ�
						SetFade(MODE_GAME);

					break;
				case 2:
					//���[�h�ݒ�
					SetFade(MODE_SELECT);
					break;
				}
			}
		}
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;	//���_�|�C���^��4�i�߂�

	for (int nCount = 0 + 1; nCount < 4; nCount++)
	{
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

		pVtx += 4;	//���_�|�C���^��4�i�߂�

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPause->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * (g_nSelectMenu + 1);
	pVtx[0].col = g_PColor;
	pVtx[1].col = g_PColor;
	pVtx[2].col = g_PColor;
	pVtx[3].col = g_PColor;

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPause->Unlock();

}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
									//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
