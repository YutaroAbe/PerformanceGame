//=============================================================================
//
// �`���[�g���A������ [title.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "bg.h"
#include "tutorial.h"
#include "bullet.h"
#include"sound.h"
#include "effect.h"
#include "explosion.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TUTORIAL_TEXTURENAMRE "data/TEXTURE/Key/KeyW.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE1 "data/TEXTURE/Key/KeyA.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE2 "data/TEXTURE/Key/KeyS.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE3 "data/TEXTURE/Key/KeyD.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE4 "data/TEXTURE/Key/KeyP.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE5 "data/TEXTURE/Key/KeySPACE.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE6 "data/TEXTURE/Key/KeySHIFT.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE7 "data/TEXTURE/Key/Key001.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE8 "data/TEXTURE/Key/Key002.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE9 "data/TEXTURE/Key/Key003.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_TEXTURENAMRE10 "data/TEXTURE/title002.png" //�ǂݍ��ރe�N�X�`��
#define TUTORIAL_POS_X  (0)�@�@�@//�w�i�̍���X���W
#define TUTORIAL_POS_Y  (0)�@�@�@//�w�i�̍���Y���W
#define TUTORIAL_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define TUTORIAL_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define TUTORIAL_MAX (11)	//�e�N�X�`���̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTUTORIAL[TUTORIAL_MAX] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTORIAL = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_posTUTO[TUTORIAL_MAX];
D3DXCOLOR g_colTUTO[TUTORIAL_MAX];
int g_aCount2; //�J�E���g2
int g_aCount3; //�J�E���g3

//=============================================================================
//�����������|���S��
//=============================================================================
void InitTUTORIAL(void)
{
	//�����������o�b�N�O���E���h
	InitBG();
	//�����������o���b�g
	InitBullet();
	//�����������v���C���[
	InitPlayer();
	//�����������G�t�F�N�g
	InitEffect();
	//�����������G�N�X�v���[�W����
	InitExplosion();

	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE, &g_pTextureTUTORIAL[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE1, &g_pTextureTUTORIAL[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE2, &g_pTextureTUTORIAL[2]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE3, &g_pTextureTUTORIAL[3]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE4, &g_pTextureTUTORIAL[4]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE5, &g_pTextureTUTORIAL[5]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE6, &g_pTextureTUTORIAL[6]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE7, &g_pTextureTUTORIAL[7]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE8, &g_pTextureTUTORIAL[8]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE9, &g_pTextureTUTORIAL[9]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURENAMRE10, &g_pTextureTUTORIAL[10]);

	//�|�W�V����
	g_posTUTO[0] = D3DXVECTOR3(600, 40, 0);//W
	g_posTUTO[1] = D3DXVECTOR3(500, 100, 0);//A
	g_posTUTO[2] = D3DXVECTOR3(600, 100, 0);//S
	g_posTUTO[3] = D3DXVECTOR3(700, 100, 0);//D
	g_posTUTO[4] = D3DXVECTOR3(200, 100, 0);//P
	g_posTUTO[5] = D3DXVECTOR3(300, 100, 0);//�X�y�[�X
	g_posTUTO[6] = D3DXVECTOR3(400, 100, 0);//�V�t�g
	g_posTUTO[7] = D3DXVECTOR3(600, 600, 0);//
	g_posTUTO[8] = D3DXVECTOR3(300, 600, 0);//1
	g_posTUTO[9] = D3DXVECTOR3(700, 600, 0);//2
	g_posTUTO[10] = D3DXVECTOR3(1100, 100, 0);//�v���X�G���^�[

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* TUTORIAL_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTUTORIAL,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCount = 0; nCount < TUTORIAL_MAX - 1; nCount++)
	{
		//���_���W�ݒ�
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_posTUTO[nCount].x - 50, g_posTUTO[nCount].y - 30, 0.0f);		 //�E��
		pVtx[1].pos = D3DXVECTOR3(g_posTUTO[nCount].x + 50, g_posTUTO[nCount].y - 30, 0.0f);		 //�E��
		pVtx[2].pos = D3DXVECTOR3(g_posTUTO[nCount].x - 50, g_posTUTO[nCount].y + 30, 0.0f);		 //����
		pVtx[3].pos = D3DXVECTOR3(g_posTUTO[nCount].x + 50, g_posTUTO[nCount].y + 30, 0.0f);		 //����
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//�E��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);								//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);								//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);								//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//�|�W�V����
	pVtx[28].pos = D3DXVECTOR3(g_posTUTO[7].x - 800, g_posTUTO[7].y - 200, 0.0f);		 //�E��
	pVtx[29].pos = D3DXVECTOR3(g_posTUTO[7].x + 800, g_posTUTO[7].y - 200, 0.0f);		 //�E��
	pVtx[30].pos = D3DXVECTOR3(g_posTUTO[7].x - 800, g_posTUTO[7].y + 200, 0.0f);		 //����
	pVtx[31].pos = D3DXVECTOR3(g_posTUTO[7].x + 800, g_posTUTO[7].y + 200, 0.0f);		 //����
	 //RHW
	pVtx[28].rhw = 1.0f;
	pVtx[29].rhw = 1.0f;
	pVtx[30].rhw = 1.0f;
	pVtx[31].rhw = 1.0f;
	//�J���[
	pVtx[28].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[29].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[30].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[31].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);								//�E��
	pVtx[29].tex = D3DXVECTOR2(1.0f, 0.0f);								//�E��
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);								//����
	pVtx[31].tex = D3DXVECTOR2(1.0f, 1.0f);								//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//�|�W�V����
	pVtx[32].pos = D3DXVECTOR3(g_posTUTO[8].x - 200, g_posTUTO[8].y - 100, 0.0f);		 //�E��
	pVtx[33].pos = D3DXVECTOR3(g_posTUTO[8].x + 200, g_posTUTO[8].y - 100, 0.0f);		 //�E��
	pVtx[34].pos = D3DXVECTOR3(g_posTUTO[8].x - 200, g_posTUTO[8].y + 100, 0.0f);		 //����
	pVtx[35].pos = D3DXVECTOR3(g_posTUTO[8].x + 200, g_posTUTO[8].y + 100, 0.0f);		 //����
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
	pVtx[32].tex = D3DXVECTOR2(0.0f, 0.0f);								//�E��
	pVtx[33].tex = D3DXVECTOR2(1.0f, 0.0f);								//�E��
	pVtx[34].tex = D3DXVECTOR2(0.0f, 1.0f);								//����
	pVtx[35].tex = D3DXVECTOR2(1.0f, 1.0f);								//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//�|�W�V����
	pVtx[36].pos = D3DXVECTOR3(g_posTUTO[9].x - 200, g_posTUTO[9].y - 100, 0.0f);		 //�E��
	pVtx[37].pos = D3DXVECTOR3(g_posTUTO[9].x + 200, g_posTUTO[9].y - 100, 0.0f);		 //�E��
	pVtx[38].pos = D3DXVECTOR3(g_posTUTO[9].x - 200, g_posTUTO[9].y + 100, 0.0f);		 //����
	pVtx[39].pos = D3DXVECTOR3(g_posTUTO[9].x + 200, g_posTUTO[9].y + 100, 0.0f);		 //����
																						 //RHW
	pVtx[36].rhw = 1.0f;
	pVtx[37].rhw = 1.0f;
	pVtx[38].rhw = 1.0f;
	pVtx[39].rhw = 1.0f;
	//�J���[
	pVtx[36].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[37].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[38].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[39].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W
	pVtx[36].tex = D3DXVECTOR2(0.0f, 0.0f);								//�E��
	pVtx[37].tex = D3DXVECTOR2(1.0f, 0.0f);								//�E��
	pVtx[38].tex = D3DXVECTOR2(0.0f, 1.0f);								//����
	pVtx[39].tex = D3DXVECTOR2(1.0f, 1.0f);								//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//�|�W�V����
	pVtx[40].pos = D3DXVECTOR3(g_posTUTO[10].x - 100, g_posTUTO[10].y - 30, 0.0f);		 //�E��
	pVtx[41].pos = D3DXVECTOR3(g_posTUTO[10].x + 100, g_posTUTO[10].y - 30, 0.0f);		 //�E��
	pVtx[42].pos = D3DXVECTOR3(g_posTUTO[10].x - 100, g_posTUTO[10].y + 30, 0.0f);		 //����
	pVtx[43].pos = D3DXVECTOR3(g_posTUTO[10].x + 100, g_posTUTO[10].y + 30, 0.0f);		 //����
																						 //RHW
	pVtx[40].rhw = 1.0f;
	pVtx[41].rhw = 1.0f;
	pVtx[42].rhw = 1.0f;
	pVtx[43].rhw = 1.0f;
	//�J���[
	pVtx[40].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[41].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[42].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[43].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`�����W
	pVtx[40].tex = D3DXVECTOR2(0.0f, 0.0f);								//�E��
	pVtx[41].tex = D3DXVECTOR2(1.0f, 0.0f);								//�E��
	pVtx[42].tex = D3DXVECTOR2(0.0f, 1.0f);								//����
	pVtx[43].tex = D3DXVECTOR2(1.0f, 1.0f);								//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	g_aCount2 = 0;

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitTUTORIAL(void)
{
	// �I�������o�b�N�O���E���h
	UninitBG();
	//�I�������o���b�g
	UninitBullet();
	// �I�������v���C���[
	UninitPlayer();
	//�I�������G�t�F�N�g
	UninitEffect();
	// �I�������G�N�X�v���[�W����
	UninitExplosion();

	for (int nCount = 0; nCount < TUTORIAL_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTUTORIAL[nCount] != NULL)
		{
			g_pTextureTUTORIAL[nCount]->Release();
			g_pTextureTUTORIAL[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTUTORIAL != NULL)
	{
		g_pVtxBuffTUTORIAL->Release();
		g_pVtxBuffTUTORIAL = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateTUTORIAL(void)
{
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	// �X�V�����o�b�N�O���E���h
	UpdateBG();
	// �X�V�����o���b�g
	UpdateBullet();
	// �X�V�����v���C���[
	UpdatePlayer();
	//�X�V�����G�t�F�N�g
	UpdateEffect();
	// �X�V�����G�N�X�v���[�W����
	UpdateExplosion();
	FADE pFade;

	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_SELECTMODE);
		}
	}
	g_aCount2++;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
	//�v���X�G���^�[�J���[
	pVtx[40].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[41].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[42].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	pVtx[43].col = D3DCOLOR_RGBA(g_aCount2 * 2, 0, 0, 0);
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTUTORIAL->Unlock();

	//�{�^���_��----------------------------------------------------------------------------------
	//�L�[�{�[�hW
	if (GetKeyboardTrigger(DIK_W) == true)//----W�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[W
		pVtx[0].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[1].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[2].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[3].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_W) == false)//----W�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[1].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[2].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[3].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	//�L�[�{�[�hA
	if (GetKeyboardPress(DIK_A) == true)//----A�{�^���{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[A
		pVtx[4].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[5].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[6].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[7].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_A) == false)//----A�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[4].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[5].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[6].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[7].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	//�L�[�{�[�hS
	if (GetKeyboardPress(DIK_S) == true)//----S�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[S
		pVtx[8].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[9].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[10].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[11].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_S) == false)//----S�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[S
		pVtx[8].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[9].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[10].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[11].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_D) == true)//----D�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[D
		pVtx[12].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[13].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[14].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[15].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_D) == false)//----D�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[D
		pVtx[12].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[13].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[14].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[15].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_P) == true)//----P�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[16].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[17].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[18].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[19].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_P) == false)//----P�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[16].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[17].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[18].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[19].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_SPACE) == true)//----SPACE�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[20].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[21].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[22].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[23].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_SPACE) == false)//----SPACE�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[20].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[21].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[22].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[23].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_LSHIFT) == true)//----SHIFT�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[24].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[25].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[26].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		pVtx[27].col = D3DCOLOR_RGBA(120 + 120, 120 + 120, 120 + 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
	if (GetKeyboardPress(DIK_LSHIFT) == false)//----SHIFT�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTUTORIAL->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[24].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[25].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[26].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[27].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTUTORIAL->Unlock();
	}
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawTUTORIAL(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTUTORIAL, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
		for (int nCount = 0; nCount < TUTORIAL_MAX; nCount++)
		{  //�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTUTORIAL[nCount]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	//�`�揈���o�b�N�O���E���h
	DrawBG();
	//�`�揈���o���b�g
	DrawBullet();
	//�`�揈���v���C���[
	DrawPlayer();
	//�`�揈���G�t�F�N�g
	DrawEffect();
	// �`�揈���G�N�X�v���[�W����
	DrawExplosion();
}

