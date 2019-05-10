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

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAMRE "data/TEXTURE/title.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTURENAMRE2 "data/TEXTURE/title000.png" //�ǂݍ��ރe�N�X�`��
#define TITLE_TEXTURENAMRE3 "data/TEXTURE/title002.png" //�ǂݍ��ރe�N�X�`��
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

	//�����l�ݒ�
	g_PosTitle = D3DXVECTOR3(1280 / 2, 290, 0.0f);     //�^�C�g��
	g_PosPressEnter = D3DXVECTOR3(600, 640, 0.0f);//�v���X�G���^�[
	g_aTPress = 0;
	g_aTitleCounter = 0;
	g_TState = TITLE_NOMAL;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE, &g_pTextureTITLE[0]);//�w�i
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE2, &g_pTextureTITLE[1]);//�v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURENAMRE3, &g_pTextureTITLE[2]);//�^�C�g��

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
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		             //�E��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);              //�E��
	pVtx[2].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);				 //����
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);		 //����
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
	pVtx[0].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y - 210, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y - 210, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_PosTitle.x - 400, g_PosTitle.y + 210, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_PosTitle.x + 400, g_PosTitle.y + 210, 0.0f);		 //����
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
	pVtx += 8;	//���_�|�C���^��4�i�߂�

				//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_PosPressEnter.x - 100, g_PosPressEnter.y - 30, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_PosPressEnter.x + 100, g_PosPressEnter.y - 30, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_PosPressEnter.x - 100, g_PosPressEnter.y + 30, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_PosPressEnter.x + 100, g_PosPressEnter.y + 30, 0.0f);		 //����
																							 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitTitle(void)
{
	//�e�N�X�`���̔j��[2]
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
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_TState = TITLE_END;
			//���[�h�ݒ�
			PlaySound(SOUND_LABEL_SE_DECIDE);
			SetFade(MODE_SELECTMODE);
		}
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTITLE->Unlock();

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

	for (int nCount = 0; nCount < MAX_TITLE_TEX - 1; nCount++)
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
		if (g_aTPress % 6 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTITLE[2]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}



}