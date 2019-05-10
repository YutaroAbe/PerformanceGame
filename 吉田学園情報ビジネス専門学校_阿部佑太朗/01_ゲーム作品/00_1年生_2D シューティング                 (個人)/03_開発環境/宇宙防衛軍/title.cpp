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
#include "bg.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAMRE "data/TEXTURE/title001.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTURENAMRE2 "data/TEXTURE/title002.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_POS_X  (0)�@�@�@//�w�i�̍���X���W
#define TITLE_POS_Y  (0)�@�@�@//�w�i�̍���Y���W
#define TITLE_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define TITLE_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTITLE[2] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_posTitle[2];
int g_title;
int g_title2;
TITLESTATE g_TitleMode;
//D3DXVECTOR3 g_moveTitle;

//=============================================================================
//�����������^�C�g��
//=============================================================================
void InitTITLE(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

	g_TitleMode = TITLE_NOMAL;
	g_title = 0;
	g_title2 = 120;
	g_posTitle[0] = D3DXVECTOR3(600, 250, 0.0f);
	g_posTitle[1] = D3DXVECTOR3(600, 600, 0.0f);

	//g_moveTitle = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE, &g_pTextureTITLE[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE2, &g_pTextureTITLE[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//�^�C�g��
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_posTitle[0].x - 400, g_posTitle[0].y - 100, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_posTitle[0].x + 400, g_posTitle[0].y - 100, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_posTitle[0].x - 400, g_posTitle[0].y + 100, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_posTitle[0].x + 400, g_posTitle[0].y + 100, 0.0f);		 //����
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	//�v���X�G���^�[
	//�|�W�V����
	pVtx[4].pos = D3DXVECTOR3(g_posTitle[1].x - 100, g_posTitle[1].y - 30, 0.0f);		 //�E��
	pVtx[5].pos = D3DXVECTOR3(g_posTitle[1].x + 100, g_posTitle[1].y - 30, 0.0f);	     //�E��
	pVtx[6].pos = D3DXVECTOR3(g_posTitle[1].x - 100, g_posTitle[1].y + 30, 0.0f);		 //����
	pVtx[7].pos = D3DXVECTOR3(g_posTitle[1].x + 100, g_posTitle[1].y + 30, 0.0f);		 //����
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
	g_pVtxBuffTITLE->Unlock();

	//�����������o�b�N�O���E���h
	InitBG();

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitTITLE(void)
{
	// �I�������o�b�N�O���E���h
	UninitBG();
	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���̔j��
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
void UpdateTITLE(void)
{
	
	//�G���^�[�Ń��[�h�G���^�[�Ɉڍs
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[�ŃZ���N�g��ʂ�
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_SELECTMODE);

		}
	}
	// �X�V�����o�b�N�O���E���h
	UpdateBG();	
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//�G���^�[�œ_�ōő�
		g_TitleMode = TITLE_END;
	}
	g_title++;
	g_title2++;
	VERTEX_2D*pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_TitleMode)
	{
	case TITLE_NOMAL:
		if (GetKeyboardTrigger(DIK_RETURN) == false)
		{
			//�^�C�g���J���[
			pVtx[0].col = D3DCOLOR_RGBA(g_title+0, g_title - 10, g_title - 50, 0);
			pVtx[1].col = D3DCOLOR_RGBA(g_title+0, g_title - 20, g_title - 60, 0);
			pVtx[2].col = D3DCOLOR_RGBA(g_title+0, g_title - 30, g_title - 70, 0);
			pVtx[3].col = D3DCOLOR_RGBA(g_title+0, g_title - 40, g_title - 80,0);
		}
		if (GetKeyboardTrigger(DIK_RETURN) == false)
		{
			//�v���X�G���^�[�J���[
			pVtx[4].col = D3DCOLOR_RGBA(g_title2 * 2, 0, 0, 0);
			pVtx[5].col = D3DCOLOR_RGBA(g_title2 * 2, 0, 0, 0);
			pVtx[6].col = D3DCOLOR_RGBA(g_title2 * 2, 0, 0, 0);
			pVtx[7].col = D3DCOLOR_RGBA(g_title2 * 2, 0, 0, 0);
		}
		break;
	case TITLE_END:
			//�^�C�g���J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		
			//�v���X�G���^�[�J���[
			pVtx[4].col = D3DCOLOR_RGBA((g_title2 * 250) * 5, 0, 0, 0);
			pVtx[5].col = D3DCOLOR_RGBA((g_title2 * 250) * 5, 0, 0, 0);
			pVtx[6].col = D3DCOLOR_RGBA((g_title2 * 250) * 5, 0, 0, 0);
			pVtx[7].col = D3DCOLOR_RGBA((g_title2 * 250) * 5, 0, 0, 0);
	
		break;
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

	
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawTITLE(void)
{
	//�`�揈���o�b�N�O���E���h
	DrawBG();
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE,0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);	
	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTITLE[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

