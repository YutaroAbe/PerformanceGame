//=============================================================================
//
//	���U���g���� [result.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define RESULT_TEXTURENAMRE "data/TEXTURE/OVER001.png"			//	�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTURENAMRE1 "data/TEXTURE/OVER000.png"			//	�ǂݍ��ރe�N�X�`��
#define RESULT_TEXTURENAMRE2 "data/TEXTURE/title002.png"		//	�ǂݍ��ރe�N�X�`��
#define RESULT_POS_X  (0)�@�@�@									//	�w�i�̍���X���W
#define RESULT_POS_Y  (0)�@�@									//	�w�i�̍���Y���W
#define RESULT_WIDTH   (SCREEN_WIDTH)							//	�w�i�̕�
#define RESULT_HEIGHT   (SCREEN_HEIGHT)							//	�w�i�̍���
#define MAX_RESULT (3)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRESULT[MAX_RESULT] = {};			//	�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRESULT = NULL;				//	���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_posResult[2];
int g_aResult;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//	�f�o�C�X�ւ̃|�C���^
	//	�f�o�C�X�擾
	pDevice = GetDevice();
	g_aResult = 0;
	g_posResult[0] = D3DXVECTOR3(600, 250, 0.0f);
	g_posResult[1] = D3DXVECTOR3(1000, 600, 0.0f);

	//	�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE, &g_pTextureRESULT[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE1, &g_pTextureRESULT[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_TEXTURENAMRE2, &g_pTextureRESULT[2]);

	//	���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4* MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRESULT,
		NULL);

	VERTEX_2D*pVtx;									//	���_���̃|�C���^
	//	���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx,0);

	//	���_���W�ݒ�
	//	�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(RESULT_WIDTH, 0, 0.0f);				//�E��
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);	//	�E��
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);							//	����
	pVtx[3].pos = D3DXVECTOR3(0, RESULT_HEIGHT, 0.0f);				//	����
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
	pVtx[0].tex = D3DXVECTOR2(1.0f,0.0f);				//	�E��
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//	�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//	����
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//	����

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffRESULT->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	//�^�C�g��
	//�|�W�V����
	pVtx[4].pos = D3DXVECTOR3(g_posResult[0].x - 400, g_posResult[0].y - 100, 0.0f);		 //�E��
	pVtx[5].pos = D3DXVECTOR3(g_posResult[0].x + 400, g_posResult[0].y - 100, 0.0f);		 //�E��
	pVtx[6].pos = D3DXVECTOR3(g_posResult[0].x - 400, g_posResult[0].y + 100, 0.0f);		 //����
	pVtx[7].pos = D3DXVECTOR3(g_posResult[0].x + 400, g_posResult[0].y + 100, 0.0f);		 //����
																						 //RHW
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;
	//�J���[
	pVtx[4].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[5].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[6].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	pVtx[7].col = D3DCOLOR_RGBA(255, 0, 0, 0);
	//�e�N�X�`���ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffRESULT->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
	//�v���X�G���^�[
	//�|�W�V����
	pVtx[8].pos = D3DXVECTOR3(g_posResult[1].x - 100, g_posResult[1].y - 30, 0.0f);		 //�E��
	pVtx[9].pos = D3DXVECTOR3(g_posResult[1].x + 100, g_posResult[1].y - 30, 0.0f);	     //�E��
	pVtx[10].pos = D3DXVECTOR3(g_posResult[1].x - 100, g_posResult[1].y + 30, 0.0f);		 //����
	pVtx[11].pos = D3DXVECTOR3(g_posResult[1].x + 100, g_posResult[1].y + 30, 0.0f);		 //����
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
	g_pVtxBuffRESULT->Unlock();

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitRESULT(void)
{
	for (int nCount = 0; nCount < MAX_RESULT; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureRESULT[nCount] != NULL)
		{
			g_pTextureRESULT[nCount]->Release();
			g_pTextureRESULT[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRESULT != NULL)
	{
		g_pVtxBuffRESULT->Release();
		g_pVtxBuffRESULT = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdateRESULT(void)
{
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	FADE pFade;

	pFade = *GetFade();

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
		g_aResult++;
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = D3DCOLOR_RGBA(200- g_aResult, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(155 - g_aResult, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(55 - g_aResult, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0 - g_aResult, 255, 255, 255);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffRESULT->Unlock();
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		//�^�C�g���J���[
		pVtx[4].col = D3DCOLOR_RGBA(g_aResult + 250, g_aResult - 210, g_aResult - 0, 0);
		pVtx[5].col = D3DCOLOR_RGBA(g_aResult + 260, g_aResult - 220, g_aResult - 0, 0);
		pVtx[6].col = D3DCOLOR_RGBA(g_aResult + 270, g_aResult - 230, g_aResult - 0, 0);
		pVtx[7].col = D3DCOLOR_RGBA(g_aResult + 280, g_aResult - 240, g_aResult - 0, 0);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffRESULT->Unlock();
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[8].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[9].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[10].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		pVtx[11].col = D3DCOLOR_RGBA(g_aResult * 2, 0, 0, 0);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffRESULT->Unlock();
	}
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRESULT,0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < MAX_RESULT; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRESULT[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

