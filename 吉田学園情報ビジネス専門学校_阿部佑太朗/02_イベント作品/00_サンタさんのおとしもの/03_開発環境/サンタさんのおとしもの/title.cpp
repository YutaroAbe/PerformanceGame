//=============================================================================
//
// �^�C�g������ [title.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "enemy.h"
#include "bg2.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAMRE "data/TEXTURE/titlelogo.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTURENAMRE2 "data/TEXTURE/PRESSENTER.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTURENAMRE3 "data/TEXTURE/title001.png" //�ǂݍ��ރe�N�X�`��
#define MAX_TITLE_TEX (3)
#define BG_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define BG_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTITLE[MAX_TITLE_TEX] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_PosTitle;
D3DXVECTOR3 g_PosPressEnter;
D3DXVECTOR3 g_PosTitleEnemy;
int g_aTPress;												//�^�C�g���v���X�G���^�[
TITLESTATE g_TState;
int g_aTitleCounter;
//=============================================================================
//�����������^�C�g��
//=============================================================================
void InitTitle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;						
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//�����������w�i
	InitBG2();
	//�����������G�l�~�[
	InitEnemy();

	//�����l�ݒ�
	g_PosTitle = D3DXVECTOR3(1280 / 2, 250, 0.0f);      //�^�C�g��
	g_PosPressEnter = D3DXVECTOR3(600, 550, 0.0f);		//�v���X�G���^�[
	g_aTPress = 0;
	g_aTitleCounter = 0;
	g_TState = TITLE_NOMAL;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE3, &g_pTextureTITLE[0]);		//�w�i
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE, &g_pTextureTITLE[1]);		//�v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE2, &g_pTextureTITLE[2]);		//�^�C�g��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE, //���_�o�b�t�@�̃|�C���g
		NULL);	

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);						  //�E��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);                 //�E��
	pVtx[2].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);				  //����
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);		  //����
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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				 //�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y - 100, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y - 100, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y + 200, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y + 200, 0.0f);		 //����
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
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 8;	//���_�|�C���^��8�i�߂�
	
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_PosPressEnter.x - 200, g_PosPressEnter.y - 50, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_PosPressEnter.x + 200, g_PosPressEnter.y - 50, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_PosPressEnter.x - 200, g_PosPressEnter.y + 50, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_PosPressEnter.x + 200, g_PosPressEnter.y + 50, 0.0f);		 //����
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
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();


	SetEnemy(0, D3DXVECTOR3(1200, 430, 0.0f), D3DXVECTOR3(-2, 2, 0.0f), ENEMYSTATE_NOMAL);
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitTitle(void)
{
	//�I�������w�i
	UninitBG2();
	//�I�������G�l�~�[
	UninitEnemy();
	//�e�N�X�`���̔j��
	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{
		if (g_pTextureTITLE[nCount] != NULL)
		{
			g_pTextureTITLE[nCount]->Release();
			g_pTextureTITLE[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTITLE != NULL)
	{
		g_pVtxBuffTITLE->Release();
		g_pVtxBuffTITLE = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateTitle(void)
{
	g_aTPress++;
	g_aTitleCounter++;
	//�X�V�����w�i
	UpdateBG2();
	//�X�V�����G�l�~�[
	UpdateEnemy();

	if (g_aTPress >= 60)
	{
		g_aTPress = 0;
	}

	//�G���^�[�Ń��[�h�G���^�[�Ɉڍs
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardTrigger(DIK_RETURN) == true )
		{
			g_TState = TITLE_END;
			//���[�h�ݒ�			//PlaySound(SOUND_LABEL_SE_DECIDE);

			SetFade(MODE_SELECT);
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	//�J���[
	/*pVtx[0].col = D3DCOLOR_RGBA(g_aTitleCounter + 2, 55, g_aTitleCounter + (100), 120);
	pVtx[1].col = D3DCOLOR_RGBA(g_aTitleCounter + 2, 55, g_aTitleCounter + (100), 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);*/
	pVtx += 4;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(100 + (g_aTitleCounter + 10), 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(100 + (g_aTitleCounter + 10), 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 100 + (g_aTitleCounter + 10), 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 100 + (g_aTitleCounter + 10), 255);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

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
	//if (pEnemy->nType == 4)
	//{//�G�l�~�[�^�C�v��4�ɂȂ�����0��
	//	pEnemy->nType = 0;
	//}
	
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	

	for (int nCount = 0; nCount < MAX_TITLE_TEX-1 ; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTITLE[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_TState)
	{
	case TITLE_NOMAL:
			if (g_aTPress >= 30 == 0)
			{
				//�e�F�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureTITLE[2]);
				//�|���S���`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
			}
		break;
	case TITLE_END:
			if (g_aTPress %6 ==0)
			{
				//�e�F�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureTITLE[2]);
				//�|���S���`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
			}
		break;
	}
	//�`�揈���w�i
	DrawBG2();
	//�`�揈���G�l�~�[
	DrawEnemy();
}