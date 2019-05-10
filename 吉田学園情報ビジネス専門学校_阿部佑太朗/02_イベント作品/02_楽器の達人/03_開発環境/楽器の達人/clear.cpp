//=============================================================================
//
//	�N���A���� [clear.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "clear.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define CLEAR_TEXTURENAMRE "data/TEXTURE/clear000.png" //�ǂݍ��ރe�N�X�`��
#define CLEAR_TEXTURENAMRE1 "data/TEXTURE/CLEAR001.png" //�ǂݍ��ރe�N�X�`��
#define CLEAR_TEXTURENAMRE2 "data/TEXTURE/title002.png" //�ǂݍ��ރe�N�X�`��
#define CLEAR_POS_X  (0)�@�@�@//�w�i�̍���X���W
#define CLEAR_POS_Y  (0)�@�@�@//�w�i�̍���Y���W
#define CLEAR_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define CLEAR_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define MAX_CLEAR (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureCLEAR[MAX_CLEAR] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCLEAR = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_posClear[2];
int g_aClear;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitCLEAR(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	g_aClear = 0;
	g_posClear[0] = D3DXVECTOR3(600, 250, 0.0f);
	g_posClear[1] = D3DXVECTOR3(1000, 600, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CLEAR_TEXTURENAMRE,  &g_pTextureCLEAR[0]);
	D3DXCreateTextureFromFile(pDevice, CLEAR_TEXTURENAMRE1, &g_pTextureCLEAR[1]);
	D3DXCreateTextureFromFile(pDevice, CLEAR_TEXTURENAMRE2, &g_pTextureCLEAR[2]);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4* MAX_CLEAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCLEAR,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffCLEAR->Lock(0, 0, (void**)&pVtx,0);
	
	//���_���W�ݒ�
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(CLEAR_WIDTH, 0, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(CLEAR_WIDTH, CLEAR_HEIGHT, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);				 //����
	pVtx[3].pos = D3DXVECTOR3(0, CLEAR_HEIGHT, 0.0f);		 //����
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(1.0f,0.0f);				//�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffCLEAR->Unlock();
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffCLEAR->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//�^�C�g��
	//�|�W�V����
	pVtx[4].pos = D3DXVECTOR3(g_posClear[0].x - 400, g_posClear[0].y - 100, 0.0f);		 //�E��
	pVtx[5].pos = D3DXVECTOR3(g_posClear[0].x + 400, g_posClear[0].y - 100, 0.0f);		 //�E��
	pVtx[6].pos = D3DXVECTOR3(g_posClear[0].x - 400, g_posClear[0].y + 100, 0.0f);		 //����
	pVtx[7].pos = D3DXVECTOR3(g_posClear[0].x + 400, g_posClear[0].y + 100, 0.0f);		 //����
																						 //RHW
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//�J���[
	pVtx[4].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[5].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[6].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[7].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//�e�N�X�`���ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffCLEAR->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffCLEAR->Lock(0, 0, (void**)&pVtx, 0);
	//�v���X�G���^�[
	//�|�W�V����
	pVtx[8].pos = D3DXVECTOR3(g_posClear[1].x - 100, g_posClear[1].y - 30, 0.0f);		 //�E��
	pVtx[9].pos = D3DXVECTOR3(g_posClear[1].x + 100, g_posClear[1].y - 30, 0.0f);	     //�E��
	pVtx[10].pos = D3DXVECTOR3(g_posClear[1].x - 100, g_posClear[1].y + 30, 0.0f);		 //����
	pVtx[11].pos = D3DXVECTOR3(g_posClear[1].x + 100, g_posClear[1].y + 30, 0.0f);		 //����
																						 //RHW
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;
	//�J���[
	pVtx[8].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[9].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[10].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[11].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//�e�N�X�`���ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffCLEAR->Unlock();
	
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitCLEAR(void)
{
	for (int nCount = 0; nCount < MAX_CLEAR; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureCLEAR[nCount] != NULL)
		{
			g_pTextureCLEAR[nCount]->Release();
			g_pTextureCLEAR[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCLEAR != NULL)
	{
		g_pVtxBuffCLEAR->Release();
		g_pVtxBuffCLEAR = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateCLEAR(void)
{
	FADE pFade;

	pFade = *GetFade();
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	g_aClear++;

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_RANKING);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == false)
	{
		g_pVtxBuffCLEAR->Lock(0, 0, (void**)&pVtx, 0);
		//�^�C�g���J���[
		pVtx[4].col = D3DCOLOR_RGBA(g_aClear + 50, g_aClear - 10, g_aClear - 0, 0);
		pVtx[5].col = D3DCOLOR_RGBA(g_aClear + 60, g_aClear - 20, g_aClear - 0, 0);
		pVtx[6].col = D3DCOLOR_RGBA(g_aClear + 70, g_aClear - 30, g_aClear - 0, 0);
		pVtx[7].col = D3DCOLOR_RGBA(g_aClear + 80, g_aClear - 40, g_aClear - 0, 0);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffCLEAR->Unlock();
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffCLEAR->Lock(0, 0, (void**)&pVtx, 0);
			//�v���X�G���^�[�J���[
			pVtx[8].col = D3DCOLOR_RGBA(g_aClear * 2, 0, 0, 0);
			pVtx[9].col = D3DCOLOR_RGBA(g_aClear * 2, 0, 0, 0);
			pVtx[10].col = D3DCOLOR_RGBA(g_aClear * 2, 0, 0, 0);
			pVtx[11].col = D3DCOLOR_RGBA(g_aClear * 2, 0, 0, 0);
			//���_�o�b�t�@�A�����b�N����
			g_pVtxBuffCLEAR->Unlock();
	}
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawCLEAR(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCLEAR, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_CLEAR; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureCLEAR[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

