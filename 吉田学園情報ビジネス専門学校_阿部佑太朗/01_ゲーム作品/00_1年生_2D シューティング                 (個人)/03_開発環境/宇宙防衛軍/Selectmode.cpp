//=============================================================================
//
// �Z���N�g��ʏ��� [Selectmode.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "Selectmode.h"
#include "fade.h"
#include "enemy.h"
#include "bg.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BG_TEXTURENAMRE "data/TEXTURE/.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE1 "data/TEXTURE/GameSel000.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE2 "data/TEXTURE/GameSel001.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE3 "data/TEXTURE/GameSel002.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE4 "data/TEXTURE/GameSel003.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE5 "data/TEXTURE/Key/KeyW.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE6 "data/TEXTURE/Key/KeyS.png" //�ǂݍ��ރe�N�X�`��
#define BG_TEXTURENAMRE7  "data/TEXTURE/title002.png" //�ǂݍ��ރe�N�X�`��
#define SEL_WIDTH   (SCREEN_WIDTH)//�w�i�̕�
#define SEL_HEIGHT   (SCREEN_HEIGHT)//�w�i�̍���
#define MAX_SEL (8)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSelectmode[MAX_SEL] = {};		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectmode = NULL;  //���_�o�b�t�@�̃|�C���g
D3DXVECTOR2 g_Selectmode[MAX_SEL];
int g_aSelectMenu;
int g_aPress;
int g_aCountSel;
SELECTSTATE g_aSelstate;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitSelectmode(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�����������o�b�N�O���E���h
	InitBG();

	g_aPress = 0;
	g_aSelstate = SELECT_NOMAL;
	g_aCountSel = 0;

	g_Selectmode[0] = D3DXVECTOR2(200, 200);//���C���Q�[��
	g_Selectmode[1] = D3DXVECTOR2(400, 550);
	g_Selectmode[2] = D3DXVECTOR2(700, 200);
	g_Selectmode[3] = D3DXVECTOR2(1000, 550);//�I��
	g_Selectmode[4] = D3DXVECTOR2(1000, 550);
	g_Selectmode[5] = D3DXVECTOR2(1100, 40);
	g_Selectmode[6] = D3DXVECTOR2(1100, 170);
	g_Selectmode[7] = D3DXVECTOR2(1100, 100);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE, &g_pTextureSelectmode[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE1, &g_pTextureSelectmode[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE2, &g_pTextureSelectmode[2]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE3, &g_pTextureSelectmode[3]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE4, &g_pTextureSelectmode[4]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE5, &g_pTextureSelectmode[5]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE6, &g_pTextureSelectmode[6]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURENAMRE7, &g_pTextureSelectmode[7]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4* MAX_SEL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectmode,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);		 //�E��
	pVtx[1].pos = D3DXVECTOR3(SEL_WIDTH, 0, 0.0f);//�E��
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

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[4].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 150.0f, g_Selectmode[nCount].y - 150.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 150.0f, g_Selectmode[nCount].y - 150.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 150.0f, g_Selectmode[nCount].y + 150.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 150.0f, g_Selectmode[nCount].y + 150.0f, 0.0f);
		//RHW
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;
		//�J���[
		pVtx[4].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[5].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[6].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[7].col = D3DCOLOR_RGBA(90, 90, 90, 90);

		//�e�N�X�`�����W
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 5; nCount < 7; nCount++)
	{
		//���_���W�ݒ�
		//���_�ݒ�
		pVtx[20].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[21].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y - 40.0f, 0.0f);
		pVtx[22].pos = D3DXVECTOR3(g_Selectmode[nCount].x - 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		pVtx[23].pos = D3DXVECTOR3(g_Selectmode[nCount].x + 40.0f, g_Selectmode[nCount].y + 40.0f, 0.0f);
		//RHW
		pVtx[20].rhw = 1.0f;
		pVtx[21].rhw = 1.0f;
		pVtx[22].rhw = 1.0f;
		pVtx[23].rhw = 1.0f;
		//�J���[
		pVtx[20].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[21].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[22].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[23].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
		pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
		pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�ݒ�
	//���_�ݒ�
	pVtx[28].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[29].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y - 30.0f, 0.0f);
	pVtx[30].pos = D3DXVECTOR3(g_Selectmode[7].x - 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
	pVtx[31].pos = D3DXVECTOR3(g_Selectmode[7].x + 100.0f, g_Selectmode[7].y + 30.0f, 0.0f);
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
	pVtx[28].tex = D3DXVECTOR2(0.0f, 0.0f);				//�E��
	pVtx[29].tex = D3DXVECTOR2(1.0f, 0.0f);				//�E��
	pVtx[30].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
	pVtx[31].tex = D3DXVECTOR2(1.0f, 1.0f);				//����
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();



	g_aSelectMenu = 0;

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitSelectmode(void)
{
	//�I�������o�b�N�O���E���h
	UninitBG();

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
	//�G���^�[�Ń��[�h�G���^�[�Ɉڍs
	FADE pFade;
	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[�ŃZ���N�g��ʂ�
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{//�G���^�[��������Z���N�g�G���h��
				PlaySound(SOUND_LABEL_SE_DECIDE);
				g_aSelstate = SELECT_END;
			}
		}
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//�X�V�����o�b�N�O���E���h
	UpdateBG();


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
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			switch (g_aSelectMenu)
			{
			case  0://�Q�[�����[�h��
				SetFade(MODE_GAME);
				break;
			case 1://�`���[�g���A����
				SetFade(MODE_TUTORIAL);
				break;
			case 2://�X�R�A��
				SetFade(MODE_RANKING);
				break;
			case 3://�I��
				g_aSelstate = SELECT_QUIT;
				break;
			}
		}
	}
	g_aCountSel++;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
	//�v���X�G���^�[�J���[
	pVtx[28].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[29].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[30].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	pVtx[31].col = D3DCOLOR_RGBA(g_aCountSel * 2, 0, 0, 0);
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		pVtx += 4;	//���_�|�C���^��4�i�߂�
					//�J���[
		pVtx[0].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[1].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[2].col = D3DCOLOR_RGBA(90, 90, 90, 90);
		pVtx[3].col = D3DCOLOR_RGBA(90, 90, 90, 90);
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSelectmode->Unlock();

	switch (g_aSelstate)
	{
	case SELECT_NOMAL://�ʏ�
		///�I���������[�h�̐F��߂�
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		if (GetKeyboardTrigger(DIK_RETURN) == false)
		{
			pVtx += 4 * (g_aSelectMenu + 1);
			//�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
		break;

	case SELECT_END://�I����_��
		g_aPress++;
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * (g_aSelectMenu + 1);
		pVtx[0].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[1].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[2].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);
		pVtx[3].col = D3DCOLOR_RGBA((g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5, (g_aPress * 250) * 5);

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
		break;
	}


	if (GetKeyboardTrigger(DIK_W) == true)//----W�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[W
		pVtx[20].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[21].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[22].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[23].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardPress(DIK_W) == false)//----W�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[20].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[21].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[22].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[23].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardTrigger(DIK_S) == true)//----W�{�^�������Ă�ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[W
		pVtx[24].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[25].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[26].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		pVtx[27].col = D3DCOLOR_RGBA(120 + 120, 120, 120, 120 + 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
	if (GetKeyboardPress(DIK_S) == false)//----W�{�^�������Ă��Ȃ��ꍇ
	{
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffSelectmode->Lock(0, 0, (void**)&pVtx, 0);
		//�J���[
		pVtx[24].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[25].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[26].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		pVtx[27].col = D3DCOLOR_RGBA(120, 120, 120, 120);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffSelectmode->Unlock();
	}
}
//=============================================================================
//�`�揈���|���S��
//=============================================================================
void DrawSelectmode(void)
{
	//�`�揈���o�b�N�O���E���h
	DrawBG();

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectmode, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_SEL; nCount++)
	{
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelectmode[nCount]);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//=============================================================================
//�Z���N�g�I��
//=============================================================================
SELECTSTATE GetSelstate(void)
{
	return g_aSelstate;
}
