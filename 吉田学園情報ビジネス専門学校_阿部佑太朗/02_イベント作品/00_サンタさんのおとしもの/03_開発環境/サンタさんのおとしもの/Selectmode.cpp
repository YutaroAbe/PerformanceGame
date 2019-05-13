//=============================================================================
//
// �Z���N�g��ʏ��� [Selectmode.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "Selectmode.h"
#include "input.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE1 "data/TEXTURE/.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE2 "data/TEXTURE/sel0000.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE3 "data/TEXTURE/sel0001.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE4 "data/TEXTURE/sel0002.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE5 "data/TEXTURE/sel0003.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE6 "data/TEXTURE/KeyW.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE7 "data/TEXTURE/KeyS.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE8  "data/TEXTURE/Press000.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE9  "data/TEXTURE/1.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE10  "data/TEXTURE/2.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE11 "data/TEXTURE/3.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE12  "data/TEXTURE/4.png" //�ǂݍ��ރe�N�X�`��
#define SEL_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define SEL_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define MAX_SEL (12)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelectmode[MAX_SEL] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectmode = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Selectmode[MAX_SEL];
int g_aSelectMenu;
SELECTSTATE g_aSelstate;
int g_PressEnter;
int g_aPress;
int g_nCounterTitle;
//=============================================================================
//�����������|���S��
//=============================================================================
void InitSelectmode(void)
{
	//�I�������G�l�~�[
	InitEnemy();
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	g_nCounterTitle = 0;
	g_aSelectMenu = 0;
	g_aSelstate = SELECT_NOMAL;
	g_PressEnter = 0;
	g_aPress = 0;

	g_Selectmode[0] = D3DXVECTOR2(920, 130);//���C���Q�[��
	g_Selectmode[1] = D3DXVECTOR2(920, 290);
	g_Selectmode[2] = D3DXVECTOR2(920, 450);
	g_Selectmode[3] = D3DXVECTOR2(920, 610);//�I��
	g_Selectmode[4] = D3DXVECTOR2(500, 570);
	g_Selectmode[5] = D3DXVECTOR2(500, 650);
	g_Selectmode[6] = D3DXVECTOR2(0, 0);
	g_Selectmode[7] = D3DXVECTOR2(300,630);//�v���X�G���^�[

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE9, &g_pTextureSelectmode[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE10, &g_pTextureSelectmode[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE11, &g_pTextureSelectmode[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE12, &g_pTextureSelectmode[3]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTextureSelectmode[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTextureSelectmode[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE4, &g_pTextureSelectmode[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE5, &g_pTextureSelectmode[7]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE6, &g_pTextureSelectmode[8]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE7, &g_pTextureSelectmode[9]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE8, &g_pTextureSelectmode[10]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTextureSelectmode[11]);

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
	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);						 //�E��
		pVtx[1].pos = D3DXVECTOR3(SEL_WIDTH, 0, 0.0f);				 //�E��
		pVtx[2].pos = D3DXVECTOR3(0, SEL_HEIGHT, 0.0f);				 //����
		pVtx[3].pos = D3DXVECTOR3(SEL_WIDTH, SEL_HEIGHT, 0.0f);		 //����
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
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[16].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y - 70.0f, 0.0f);
		pVtx[17].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y - 70.0f, 0.0f);
		pVtx[18].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 270.0f, g_Selectmode[nCount].y + 70.0f, 0.0f);
		pVtx[19].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 270.0f, g_Selectmode[nCount].y + 70.0f, 0.0f);
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

	for (int nCount = 4; nCount < 6; nCount++)
	{
		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[32].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[33].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[34].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		pVtx[35].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		//RHW
		pVtx[32].rhw = 1.0f;
		pVtx[33].rhw = 1.0f;
		pVtx[34].rhw = 1.0f;
		pVtx[35].rhw = 1.0f;
		//�J���[
		pVtx[32].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[33].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[34].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[35].col = D3DCOLOR_RGBA(120, 120, 120, 120);

		//�e�N�X�`�����W
		pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//���_�ݒ�
	pVtx[40].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[41].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[42].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
	pVtx[43].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
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
	pVtx[40].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
	pVtx[41].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[42].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[43].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();
	SetEnemy(0, D3DXVECTOR3(1200, 430, 0.0f), D3DXVECTOR3(-2, 2, 0.0f), ENEMYSTATE_NOMAL);

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitSelectmode(void)
{
	//�I�������G�l�~�[
	UninitEnemy();
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
	//�X�V�����G�l�~�[
	UpdateEnemy();
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	g_PressEnter++;
	g_nCounterTitle++;
	FADE pFade;
	pFade = *GetFade();
	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_W) == true)
	{
		g_nCounterTitle = 0;
		PlaySound(SOUND_LABEL_SE_PAUSESELECT);
	}
	if (g_nCounterTitle >= 600)
	{//���u���Ă���^�C�g����ʂ�
		
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}
	if (g_PressEnter >= 60)
	{
		g_PressEnter = 0;
	}
		//�G���^�[�ŃZ���N�g��ʂ�
		if (pFade == FADE_NONE &&  GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[��������Z���N�g�G���h��
			g_aSelstate = SELECT_END;
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_aSelectMenu = (g_aSelectMenu + 1) % 4;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_aSelectMenu = (g_aSelectMenu + 3) % 4;
	}

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (pFade == FADE_NONE && GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[�ŃZ���N�g��ʂ�
			switch (g_aSelectMenu)
			{
			case  0://�`���[�g���A����
				SetFade(MODE_TUTO);
				break;
			case 1://�Q�[�����[�h��
					SetFade(MODE_GAME);
				break;
			case 2://�����L���O
				SetFade(MODE_RANK);
				break;
					
			case 3://�I��
				g_aSelstate = SELECT_QUIT;
				break;
			}
		/*	PlaySound(SOUND_LABEL_SE_DECIDE);*/
		}
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx += 4;	//���_�|�C���^��4�i�߂�
		//�J���[
		pVtx[12].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[13].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[14].col = D3DCOLOR_RGBA(90, 90, 90, 255);
		pVtx[15].col = D3DCOLOR_RGBA(90, 90, 90, 255);
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();


	switch (g_aSelstate)
	{
	case SELECT_NOMAL://�ʏ�
		
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		
			pVtx += 4 * (g_aSelectMenu + 1);
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

	if (GetKeyboardTrigger(DIK_W) == true)//----W�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[W
		pVtx[32].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[33].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[34].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[35].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_W) == false)//----W�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[32].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[33].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[34].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		pVtx[35].col = D3DCOLOR_RGBA(120, 120, 120, 255);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == true)//----W�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[W
		pVtx[36].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[37].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[38].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[39].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == false)//----W�{�^�������Ă��Ȃ��ꍇ
	{
		
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[36].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[37].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[38].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[39].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	Enemy *pEnemy;
	pEnemy = GetEnemy();

	if (pEnemy->pos.y >= 750)
	{//�G�l�~�[�̈ʒuY��750�ȏ�ɂȂ�����
		pEnemy->move.y = 0;
		//pEnemy->nType= 0;
		if (pEnemy->move.y == 0)
		{
			pEnemy->move.y = -2;
		}
	}
	if (pEnemy->pos.x >= 1280)
	{//�G�l�~�[�̈ʒuX��1280�ȏ�ɂȂ�����
		pEnemy->move.x = 0;
		//pEnemy->nType = 1;
		if (pEnemy->move.x == 0)
		{
			pEnemy->move.x = -2;
		}
	}
	if (pEnemy->pos.y <= 0)
	{// �G�l�~�[�̈ʒuY��0�ȉ��ɂȂ�����
		pEnemy->move.y = 0;
		//pEnemy->nType = 0;
		if (pEnemy->move.y == 0)
		{
			pEnemy->move.y = 2;
		}
	}
	if (pEnemy->pos.x <= 0)
	{//�G�l�~�[�̈ʒuX��0�ȉ��ɂȂ�����
		pEnemy->move.x = 0;
		//pEnemy->nType = 1;
		if (pEnemy->move.x == 0)
		{
			pEnemy->move.x = 2;
		}
	}
	if (pEnemy->move.x <= 0.1)
	{
		pEnemy->nType = 0;
	}
	else
	{
		pEnemy->nType = 1;
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
	switch (g_aSelectMenu)
	{
	case  0://�Q�[�����[�h��
			//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[0]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);
		break;
	case 1://�`���[�g���A����
		   //�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[1]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);
		break;
	case 2://�X�R�A��
		   //�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[2]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		break;
	case 3://�I��
		   //�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[3]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 3 * 4, 2);
		break;
	}
	for (int nCount = 4; nCount < 10; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_aSelstate)
	{
	case SELECT_NOMAL:
		if (g_PressEnter >= 30 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSelectmode[10]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 10 * 4, 2);
		}
		break;
	case SELECT_END:
		if (g_PressEnter % 6 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSelectmode[10]);
			//�|���S���`
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 10 * 4, 2);
		}
		break;
	}
	
	//�`�揈���G�l�~�[
	DrawEnemy();
}
//=============================================================================
//�Z���N�g�I��
//=============================================================================
SELECTSTATE GetSelstate(void)
{
	return g_aSelstate;
}
