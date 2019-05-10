//=============================================================================
//
// �^�C�g������ [Arasuji.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "arasuji.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define Arasuji_TEXTURENAMRE "data/TEXTURE/Arasuji.png"				//	�ǂݍ��ރe�N�X�`��
#define Arasuji_TEXTURENAMRE2 "data/TEXTURE/Skip000.png"			//	�ǂݍ��ރe�N�X�`��
#define Arasuji_TEXTURENAMRE3 "data/TEXTURE/Arasuji000.png"			//	�ǂݍ��ރe�N�X�`��
#define MAX_Arasuji_TEX (3)
#define BG_WIDTH   (SCREEN_WIDTH)									//	�w�i�̕�
#define BG_HEIGHT   (SCREEN_HEIGHT)									//	�w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureArasuji[MAX_Arasuji_TEX] = {};			//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArasuji = NULL;					//���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_PosArasuji;
D3DXVECTOR3 g_ARAPressEnter;
int g_aAPress;														//�^�C�g���v���X�G���^�[
ARASUJISTATE g_TState;
D3DXVECTOR2 g_AS[2];
int g_aArasujiEND;
//=============================================================================
//�����������^�C�g��
//=============================================================================
void InitArasuji(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�����l�ݒ�
	g_PosArasuji = D3DXVECTOR3(600, 680, 0.0f);     //�^�C�g��
	g_ARAPressEnter = D3DXVECTOR3(1000, 690, 0.0f);//�v���X�G���^�[
	g_aAPress = 0;
	g_aArasujiEND = 0;
	g_AS[0] = D3DXVECTOR2(0.0f, 0.0f);
	g_AS[1] = D3DXVECTOR2(0.0f, 0.0f);
	g_TState = ARASUJI_NOMAL;
	//g_aArasujiEND = 0;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE3, &g_pTextureArasuji[0]);//�w�i
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE, &g_pTextureArasuji[1]);//�v���X�G���^�[
	D3DXCreateTextureFromFile(pDevice, Arasuji_TEXTURENAMRE2, &g_pTextureArasuji[2]);//�^�C�g��

																				 //���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Arasuji_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArasuji, //���_�o�b�t�@�̃|�C���g
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(0 + 100, 0+50, 0.0f);		             //�E��
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH - 100, 0 + 50, 0.0f);              //�E��
	pVtx[2].pos = D3DXVECTOR3(0 + 100, BG_HEIGHT - 100, 0.0f);				 //����
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH - 100, BG_HEIGHT - 100, 0.0f);		 //����
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

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				    //�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);				//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);				//����

														//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffArasuji->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_PosArasuji.x - 600, g_PosArasuji.y - 80, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_PosArasuji.x + 600, g_PosArasuji.y - 80, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_PosArasuji.x - 600, g_PosArasuji.y + 80, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_PosArasuji.x + 600, g_PosArasuji.y + 80, 0.0f);		 //
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
	g_pVtxBuffArasuji->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 8;	//���_�|�C���^��4�i�߂�

				//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_ARAPressEnter.x - 100, g_ARAPressEnter.y - 30, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(g_ARAPressEnter.x + 100, g_ARAPressEnter.y - 30, 0.0f);		 //�E��
	pVtx[2].pos = D3DXVECTOR3(g_ARAPressEnter.x - 100, g_ARAPressEnter.y + 30, 0.0f);		 //����
	pVtx[3].pos = D3DXVECTOR3(g_ARAPressEnter.x + 100, g_ARAPressEnter.y + 30, 0.0f);		 //����
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
	g_pVtxBuffArasuji->Unlock();
}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitArasuji(void)
{
	//�e�N�X�`���̔j��[2]
	for (int nCount = 0; nCount < MAX_Arasuji_TEX; nCount++)
	{

		if (g_pTextureArasuji[nCount] != NULL)
		{
			g_pTextureArasuji[nCount]->Release();
			g_pTextureArasuji[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffArasuji != NULL)
	{
		g_pVtxBuffArasuji->Release();
		g_pVtxBuffArasuji = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateArasuji(void)
{
	g_aAPress++;
	g_AS[0].y -= 0.0002f;
	g_AS[1].x += 0.003f;
	g_aArasujiEND++;
	FADE pFade;
	pFade = *GetFade();
	if (g_aArasujiEND >= 2100)
	{//���u���Ă���^�C�g����ʂ�

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_SELECT);
		}
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffArasuji->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - g_AS[0].y);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - g_AS[0].y);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f - g_AS[0].y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f - g_AS[0].y);
	pVtx += 4;
	pVtx[0].tex = D3DXVECTOR2(g_AS[1].x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_AS[1].x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_AS[1].x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_AS[1].x, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffArasuji->Unlock();
	if (g_aAPress >= 60)
	{
		g_aAPress = 0;
	}

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_TState = ARASUJI_END;
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_SELECT);
		}
	}

}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawArasuji(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffArasuji, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_Arasuji_TEX - 1; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureArasuji[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	switch (g_TState)
	{
	case ARASUJI_NOMAL:
		if (g_aAPress >= 30 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureArasuji[2]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	case ARASUJI_END:
		if (g_aAPress % 6 == 0)
		{
			//�e�F�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureArasuji[2]);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 2 * 4, 2);
		}
		break;
	}
}