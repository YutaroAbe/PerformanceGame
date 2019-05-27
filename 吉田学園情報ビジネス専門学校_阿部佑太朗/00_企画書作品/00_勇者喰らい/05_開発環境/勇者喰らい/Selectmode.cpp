//=============================================================================
//
// �Z���N�g��ʏ��� [Selectmode.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "Selectmode.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "camera.h"
#include "goburin.h"
#include "light.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE1 "data/TEXTURE/SELECT/GAKUBUTI.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE2 "data/TEXTURE/SELECT/STORYMODE.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE3 "data/TEXTURE/SELECT/GAMEMODE.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE4 "data/TEXTURE/SELECT/SOUNDMODE.png"				 //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE5 "data/TEXTURE/SELECT/GAMEENDMODE.png"				 //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE6 "data/TEXTURE/SELECT/SELECTMODE.png"				//W
#define BG_TEXTURENAMRE7 "data/TEXTURE/SELECT/SELSOUSA.png"				//S
#define BG_TEXTURENAMRE8  "data/TEXTURE/SELECT/Press000.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE9  "data/TEXTURE/SELECT/KUROMEN.png"				//�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE13  "data/TEXTURE/SELECT/ooo.jpg"					//�ǂݍ��ރe�N�X�`��
#define SEL_WIDTH   (SCREEN_WIDTH)									//�w�i�̕�
#define SEL_HEIGHT   (SCREEN_HEIGHT)								//�w�i�̍���
#define MAX_SEL (13)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelectmode[MAX_SEL] = {};				//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectmode = NULL;				//���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Selectmode[MAX_SEL];
SELECTSTATE g_aSelstate;
int g_aSelectMenu;
int g_PressEnter;
int g_aPress;
int g_nCounterTitle;
int g_SELTITLE;
//=============================================================================
//�����������|���S��
//=============================================================================
void InitSelectmode(void)
{
	PLAYER *pPlayer = GetPlayer();
	pPlayer[0].state = JAYPAD_STATE_SELECT;
	int *pTime = GetTime();
	pTime[0] = 0;

	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	g_nCounterTitle = 0;
	g_aSelectMenu = 0;
	g_aSelstate = SELECT_NOMAL;
	g_PressEnter = 0;
	g_aPress = 0;

	g_Selectmode[0] = D3DXVECTOR2(290, 70);//���C���Q�[��
	g_Selectmode[1] = D3DXVECTOR2(290, 190);
	g_Selectmode[2] = D3DXVECTOR2(290, 310);
	g_Selectmode[3] = D3DXVECTOR2(290, 430);//�I��
	g_Selectmode[4] = D3DXVECTOR2(840, 125);//SELECTMODE
	g_Selectmode[5] = D3DXVECTOR2(870, 445);//�{�^���̂���
	g_Selectmode[6] = D3DXVECTOR2(300, 630);
	//g_Selectmode[7] = D3DXVECTOR2(0,0);	//�v���X�G���^�[

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE9, &g_pTextureSelectmode[0]);		//����������
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTextureSelectmode[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTextureSelectmode[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE4, &g_pTextureSelectmode[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE5, &g_pTextureSelectmode[7]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE6, &g_pTextureSelectmode[8]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE7, &g_pTextureSelectmode[9]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE8, &g_pTextureSelectmode[10]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTextureSelectmode[11]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE13, &g_pTextureSelectmode[12]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SEL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectmode,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);		 //�E��
		pVtx[1].pos = D3DXVECTOR3(900.0f, 500.0f, 0.0f);		 //�E��
		pVtx[2].pos = D3DXVECTOR3(200.0f, 700.0f, 0.0f);		 //����
		pVtx[3].pos = D3DXVECTOR3(900.0f, 700.0f, 0.0f);		 //����
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���_�ݒ�
		pVtx[16].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y - 20.0f, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y - 20.0f, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y + 20.0f, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y + 20.0f, 0.0f);
		//RHW
		pVtx[16].rhw = 1.0f;
		pVtx[17].rhw = 1.0f;
		pVtx[18].rhw = 1.0f;
		pVtx[19].rhw = 1.0f;

		//�J���[
		pVtx[16].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[17].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[18].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[19].col = D3DCOLOR_RGBA(90, 90, 90, 255);

		//�e�N�X�`�����W
		pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		//���_�ݒ�
		pVtx[32].pos = D3DXVECTOR3(g_Selectmode[4].x - 130.0f, g_Selectmode[4].y - 100.0f, 0.0f);
		pVtx[33].pos = D3DXVECTOR3(g_Selectmode[4].x + 400.0f, g_Selectmode[4].y - 100.0f, 0.0f);
		pVtx[34].pos = D3DXVECTOR3(g_Selectmode[4].x - 130.0f, g_Selectmode[4].y + 100.0f, 0.0f);
		pVtx[35].pos = D3DXVECTOR3(g_Selectmode[4].x + 400.0f, g_Selectmode[4].y + 100.0f, 0.0f);
		//RHW
		pVtx[32].rhw = 1.0f;
		pVtx[33].rhw = 1.0f;
		pVtx[34].rhw = 1.0f;
		pVtx[35].rhw = 1.0f;
		//�J���[
		pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;	//���_�|�C���^��4�i�߂�

		//���_�ݒ�
		pVtx[32].pos = D3DXVECTOR3(g_Selectmode[5].x - 130.0f, g_Selectmode[5].y - 21.0f, 0.0f);
		pVtx[33].pos = D3DXVECTOR3(g_Selectmode[5].x + 400.0f, g_Selectmode[5].y - 21.0f, 0.0f);
		pVtx[34].pos = D3DXVECTOR3(g_Selectmode[5].x - 130.0f, g_Selectmode[5].y + 21.0f, 0.0f);
		pVtx[35].pos = D3DXVECTOR3(g_Selectmode[5].x + 400.0f, g_Selectmode[5].y + 21.0f, 0.0f);
		//RHW
		pVtx[32].rhw = 1.0f;
		pVtx[33].rhw = 1.0f;
		pVtx[34].rhw = 1.0f;
		pVtx[35].rhw = 1.0f;
		//�J���[
		pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//���_�ݒ�
	pVtx[40].pos = D3DXVECTOR3(g_Selectmode[6].x - 100.0f, g_Selectmode[6].y - 30.0f, 0.0f);
	pVtx[41].pos = D3DXVECTOR3(g_Selectmode[6].x + 100.0f, g_Selectmode[6].y - 30.0f, 0.0f);
	pVtx[42].pos = D3DXVECTOR3(g_Selectmode[6].x - 100.0f, g_Selectmode[6].y + 30.0f, 0.0f);
	pVtx[43].pos = D3DXVECTOR3(g_Selectmode[6].x + 100.0f, g_Selectmode[6].y + 30.0f, 0.0f);
	//RHW
	pVtx[40].rhw = 1.0f;
	pVtx[41].rhw = 1.0f;
	pVtx[42].rhw = 1.0f;
	pVtx[43].rhw = 1.0f;
	//�J���[
	pVtx[40].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[41].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[42].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[43].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	//�e�N�X�`�����W
	pVtx[40].tex = D3DXVECTOR2(0.0f, 0.0f);					//�E��
	pVtx[41].tex = D3DXVECTOR2(1.0f, 0.0f);					//�E��
	pVtx[42].tex = D3DXVECTOR2(0.0f, 1.0f);					//����
	pVtx[43].tex = D3DXVECTOR2(1.0f, 1.0f);					//����
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	//���_�ݒ�
	pVtx[44].pos = D3DXVECTOR3(165.0f, 490.0f, 0.0f);		 //�E��
	pVtx[45].pos = D3DXVECTOR3(935.0f, 490.0f, 0.0f);		 //�E��
	pVtx[46].pos = D3DXVECTOR3(165.0f, 715.0f, 0.0f);		 //����
	pVtx[47].pos = D3DXVECTOR3(935.0f, 715.0f, 0.0f);		 //����
	//RHW
	pVtx[44].rhw = 1.0f;
	pVtx[45].rhw = 1.0f;
	pVtx[46].rhw = 1.0f;
	pVtx[47].rhw = 1.0f;

	//�J���[
	pVtx[44].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[45].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[46].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[47].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[44].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
	pVtx[45].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[46].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[47].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	//���_�ݒ�
	pVtx[48].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						 //�E��
	pVtx[49].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);				 //�E��
	pVtx[50].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);				 //����
	pVtx[51].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);		 //����

	//RHW
	pVtx[48].rhw = 1.0f;
	pVtx[49].rhw = 1.0f;
	pVtx[50].rhw = 1.0f;
	pVtx[51].rhw = 1.0f;

	//�J���[
	pVtx[48].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[49].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[50].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[51].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[48].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
	pVtx[49].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[50].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[51].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���C�g�̏���
	InitLight();
	//�J�����̏�����
	InitCamera();

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitSelectmode(void)
{
	UninitLight();
	// �J�����̏���������
	UninitCamera();
	for (int nCount = 0; nCount < MAX_SEL; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSelectmode[nCount] != NULL)
		{
			g_pTextureSelectmode[nCount]->Release();
			g_pTextureSelectmode[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelectmode != NULL)
	{
		g_pVtxBuffSelectmode->Release();
		g_pVtxBuffSelectmode = NULL;
	}

}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateSelectmode(void)
{
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	PLAYER *pPlayer = GetPlayer();
	int *pTime = GetTime();

	FADE pFade;
	pFade = *GetFade();

	g_SELTITLE++;
	g_PressEnter++;
	g_nCounterTitle++;


	if (g_SELTITLE >= 120)
	{
		g_SELTITLE = 0;
	}

	if (g_PressEnter >= 60)
	{//�v���X�G���^�[�_��
		g_PressEnter = 0;
	}

	//�G���^�[�ŃZ���N�g��ʂ�
	if (pFade == FADE_NONE && pPlayer[0].bButton[BUTTON_ENTER] == true)
	{//�G���^�[��������Z���N�g�G���h��
		g_aSelstate = SELECT_END;
		PlaySound(SOUND_LABEL_ENTER);
	}

	if ( pPlayer[0].bButton[BUTTON_S] == true)
	{
		PlaySound(SOUND_LABEL_SELECTMOVE);
		g_aSelectMenu = (g_aSelectMenu + 1) % 4;
		pTime[0] = 0;
	}
	if ( pPlayer[0].bButton[BUTTON_W] == true)
	{
		PlaySound(SOUND_LABEL_SELECTMOVE);
		g_aSelectMenu = (g_aSelectMenu + 3) % 4;

		pTime[0] = 0;
	}

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if ( pPlayer[0].bButton[BUTTON_ENTER] == true)
		{//�G���^�[�ŃZ���N�g��ʂ�
			switch (g_aSelectMenu)
			{
			case  0://���炷��
				SetFade(MODE_STORY, 0, 0.0f, 0);
					g_aSelstate = SELECT_STORY;
				break;
			case 1://�Q�[�����[�h��
				SetFade(MODE_START, 2, 0.0f, 0);
				g_aSelstate = SELECT_GAME;
				break;
			case 2://�N���W�b�g
				SetFade(MODE_CREDIT, 0, 0.0f, 0);
				break;
			case 3://�I��
				g_aSelstate = SELECT_QUIT;
				break;
			}
		}
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCount = 0; nCount < 4; nCount++)
		{
			//���_�ݒ�
			pVtx[16].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y - 50.0f, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y - 50.0f, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y + 50.0f, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y + 50.0f, 0.0f);

			//�J���[
			pVtx[16].col = D3DCOLOR_RGBA(90, 90, 90, 255);
			pVtx[17].col = D3DCOLOR_RGBA(90, 90, 90, 255);
			pVtx[18].col = D3DCOLOR_RGBA(90, 90, 90, 255);
			pVtx[19].col = D3DCOLOR_RGBA(90, 90, 90, 255);

			pVtx += 4;	//���_�|�C���^��4�i�߂�
		}
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();

	switch (g_aSelstate)
	{
	case SELECT_NOMAL://�ʏ�
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * (g_aSelectMenu + 1);

			//���_�ݒ�
			pVtx[12].pos = D3DXVECTOR3(g_Selectmode[g_aSelectMenu ].x - 270.0f, g_Selectmode[g_aSelectMenu ].y - 55.0f, 0.0f);
			pVtx[13].pos = D3DXVECTOR3(g_Selectmode[g_aSelectMenu ].x + 420.0f, g_Selectmode[g_aSelectMenu ].y - 55.0f, 0.0f);
			pVtx[14].pos = D3DXVECTOR3(g_Selectmode[g_aSelectMenu ].x - 270.0f, g_Selectmode[g_aSelectMenu ].y + 55.0f, 0.0f);
			pVtx[15].pos = D3DXVECTOR3(g_Selectmode[g_aSelectMenu ].x + 420.0f, g_Selectmode[g_aSelectMenu ].y + 55.0f, 0.0f);

			//�J���[
			pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[15].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�o�b�t�@�A�����b�N����d
		g_pVtxBuffSelectmode->Unlock();
		break;

	case SELECT_END://�I����_��
		g_aPress++;
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * (g_aSelectMenu + 1);
		pVtx[12].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[13].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[14].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[15].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
		break;
	}

	UpdateLight();
	UpdateCamera();


	pTime[0]++;

	if (pTime[0] == 900)
	{
		SetFade(MODE_TITLE, 0, 0.0f, 0);
	}

}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawSelectmode(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectmode, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�F�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSelectmode[12]);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * 12, 2);

	pDevice->SetTexture(0, g_pTextureSelectmode[0]);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);

	for (int nCount = 4; nCount < 9; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}

	//�z���u11�v
	pDevice->SetTexture(0, g_pTextureSelectmode[11]);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * 11, 2);


}
//=============================================================================
//�Z���N�g�I��
//=============================================================================
SELECTSTATE GetSelstate(void)
{
	return g_aSelstate;
}

//=============================================================================
//�Z���N�g�I��
//=============================================================================
int GetSelMenu(void)
{
	return g_aSelectMenu;
}

