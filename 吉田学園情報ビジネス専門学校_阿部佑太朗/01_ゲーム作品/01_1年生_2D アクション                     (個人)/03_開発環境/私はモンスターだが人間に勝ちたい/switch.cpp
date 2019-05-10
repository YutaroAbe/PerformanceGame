//=============================================================================
//
// �u���b�N�̏��� [Switch.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "switch.h"
#include "main.h"
#include "player.h"	
#include "input.h"
#include "sound.h"
#include "item.h"
#include "yajirusi.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Switch_TEXTURENAMRE0 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE1 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE2 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE3 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE4 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE5 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE6 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE7 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE8 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE9 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE10 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE11 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE12 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE13 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE14 "data/TEXTURE/Switti001.png"
#define Switch_TEXTURENAMRE15 "data/TEXTURE/Switti000.png"
#define Switch_TEXTURENAMRE16 "data/TEXTURE/Switti001.png"
#define	MAX_SWITCH		(126)					// �u���b�N�̍ő吔
#define POS_X (150)								//�|�W�V����_X
#define POS_Y (25)								//�|�W�V����_Y
#define TEX_MAX (17)

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSwitch[TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSwitch = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Switch g_aSwitch[MAX_SWITCH];						//�u���b�N�̏��
bool g_BreakSwitch;
bool g_SwitchSwitti;

//=============================================================================
// ����������
//=============================================================================
void InitSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		g_aSwitch[nCntSwitch].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCntSwitch].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCntSwitch].nType = 0;
		g_aSwitch[nCntSwitch].fWindth = 0;		//��
		g_aSwitch[nCntSwitch].fHeight = 0;		//����
		g_aSwitch[nCntSwitch].bUse = false;
	}
	g_SwitchSwitti = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE0, &g_pTextureSwitch[0]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE1, &g_pTextureSwitch[1]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE2, &g_pTextureSwitch[2]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE3, &g_pTextureSwitch[3]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE4, &g_pTextureSwitch[4]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE5, &g_pTextureSwitch[5]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE6, &g_pTextureSwitch[6]);//�g�p�ς�SWITCH
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE4, &g_pTextureSwitch[7]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE5, &g_pTextureSwitch[8]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE9, &g_pTextureSwitch[9]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE10, &g_pTextureSwitch[10]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE11, &g_pTextureSwitch[11]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE12, &g_pTextureSwitch[12]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE13, &g_pTextureSwitch[13]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE14, &g_pTextureSwitch[14]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE15, &g_pTextureSwitch[15]);
	D3DXCreateTextureFromFile(pDevice, Switch_TEXTURENAMRE16, &g_pTextureSwitch[16]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWITCH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSwitch,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);													//����
		pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);						//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);						//����
		pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//�E��
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSwitch->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitSwitch(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureSwitch[nCount] != NULL)
		{
			g_pTextureSwitch[nCount]->Release();
			g_pTextureSwitch[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSwitch != NULL)
	{
		g_pVtxBuffSwitch->Release();
		g_pVtxBuffSwitch = NULL;
	}
}
//=============================================================================
// �X�V���� 
//=============================================================================
void UpdateSwitch(void)
{
	PLAYER *pPlyer;
	pPlyer = GetPlayer();
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == true)	//�u���b�N���g�p�����ru
		{
			g_aSwitch[nCntSwitch].pos.x -= pPlyer->move.x;

			g_aSwitch[nCntSwitch].pos.x += g_aSwitch[nCntSwitch].move.x;
			g_aSwitch[nCntSwitch].pos.y += g_aSwitch[nCntSwitch].move.y;

			
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);													//����
			pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);						//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);						//����
			pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//�E��
			pVtx += 4;	//���_�|�C���^��4�i�߂�	
		}
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSwitch->Unlock();
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffSwitch, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSwitch[g_aSwitch[nCntSwitch].nType]);
			// �|���S���̕`��
			if (g_aSwitch[nCntSwitch].bUse == true)//�u���b�N���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntSwitch, 2);
			}
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetSwitch(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	{
		if (g_aSwitch[nCntSwitch].bUse == false)	//�u���b�N���g�p����Ă��Ȃ�
		{
			g_aSwitch[nCntSwitch].pos = pos;
			g_aSwitch[nCntSwitch].fHeight = fHeight;
			g_aSwitch[nCntSwitch].fWindth = fWindth;
			g_aSwitch[nCntSwitch].nType = nType;
			g_aSwitch[nCntSwitch].bUse = true;//�u���b�N���g�p����Ă���
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);//����
			pVtx[1].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y - 0, 0.0f);//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x - 0, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//����
			pVtx[3].pos = D3DXVECTOR3(g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth, g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight, 0.0f);//�E��
			
			break;
		}
		pVtx += 4;			//�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSwitch->Unlock();
}
//=============================================================================
//�u���b�N�ƃv���C���[�Ƃ̔��菈��
//=============================================================================
void CollisionSwitch(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 bool bLand = false;	//���n�������ǂ���
	 Item *pItem;
	 pItem = Getitem();

	 for (int nCntSwitch = 0; nCntSwitch < MAX_SWITCH; nCntSwitch++)
	 {
		 if (g_aSwitch[nCntSwitch].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aSwitch[nCntSwitch].pos.x  &&									//�v���C���[���E����߂荞��ł�Ƃ�
				 pPos->x - (*fWindth / 2) <= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth &&		//�v���C���[��������߂荞��ł�Ƃ�
				 pPos->y >= g_aSwitch[nCntSwitch].pos.y &&															//�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
				 pPos->y - *fHeight <= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight)					//�v���C���[���������ɂ߂荞��ł�Ƃ�
			 {//YX���͈͓�
				 if (pPosOld->y <= g_aSwitch[nCntSwitch].pos.y && pPos->y >= g_aSwitch[nCntSwitch].pos.y)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
				 {//�u���b�N�㔻��
					 bLand = true;
					 pPos->y = g_aSwitch[nCntSwitch].pos.y;														//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
					 pMove->y = 0.0f;
				 }
				 else if (pPosOld->y - *fHeight >= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight &&	//�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
					 pPos->y - *fHeight <= g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight)				//���݂̈ʒu���߂荞��ł�Ƃ�
				 {//�u���b�N������
					 //bLand = true;
					 pPos->y = g_aSwitch[nCntSwitch].pos.y + g_aSwitch[nCntSwitch].fHeight + *fHeight;				//�v���C���[���u���b�N���S+�u���b�N�̍���+�v���C���[�̍����̈ʒu�ɏo��������
					 pMove->y = 0.0f;
				 }
				 else if (pPosOld->x + *fWindth >= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth &&	//�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x - *fWindth <= g_aSwitch[nCntSwitch].pos.x + g_aSwitch[nCntSwitch].fWindth)
				 {//�u���b�N�E����
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 //�^�C�v14------------------------
					 if (g_aSwitch[nCntSwitch].nType == 0)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 1;
						 }

					 }
					 if (g_aSwitch[nCntSwitch].nType == 15)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 16;
						 }
					 }
				 }
				 else if (pPosOld->x - *fWindth <= g_aSwitch[nCntSwitch].pos.x &&									//�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x + *fWindth >= g_aSwitch[nCntSwitch].pos.x)
				 {//�u���b�N������
					 pPos->x = pPosOld->x;																		//�̂̈ʒu�ɏo��������
					 pMove->x = 0.0f;
					 if (g_aSwitch[nCntSwitch].nType == 2)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 3;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 4)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 5;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 7)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 8;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 9)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 10;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 11)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 12;
						 }
					 }
					 if (g_aSwitch[nCntSwitch].nType == 13)
					 {//�X�C�b�`OFF
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_SWITCH);
							 g_aSwitch[nCntSwitch].nType = 14;
						 }
					 }
					 
				 }
				 if (g_aSwitch[nCntSwitch].nType == 1)
				 {//�X�C�b�`ON
					 SetBlock(D3DXVECTOR3(1300, 580.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 70.0f, 5);
					
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 3)
				 {//�X�C�b�`ON
					 for (int nCut = 0; nCut < 8; nCut++)
					 {//�K�i
						 SetBlock(D3DXVECTOR3(900 + (nCut * 50.0f), 580 - (nCut * 20.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					// SetBlock(D3DXVECTOR3(1600.0f, 300.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 20.0f, 1);
					 //SWITCH
					// SetSwitch(D3DXVECTOR3(1670.0f, 260.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f, 4);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 5)
				 {//�X�C�b�`ON
					 for (int nCut = 0; nCut < 4; nCut++)
					 {//�K�i
						 SetBlock(D3DXVECTOR3(460.0f - (nCut * 50.0f), 325 - (nCut * 20.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 8)	//�`���[�g���A���ł��悤
				 {//�X�C�b�`ON
					 //�m�[�}���u���b�N
						 SetBlock(D3DXVECTOR3(800.0f, 585, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, 1);
						 //�͂Ă�
						// SetBlock(D3DXVECTOR3(850, 480, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 12);
						 ////��Ɏ������false
						// SetBlock(D3DXVECTOR3(900, 500, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 10.0f, 4);
						 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 10)	
				 {//�X�C�b�`ON
				  //�m�[�}���u���b�N
					 SetBlock(D3DXVECTOR3(800.0f, 350, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 20.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 12)	
				 {//�X�C�b�`ON
					 SetBlock(D3DXVECTOR3(700.0f, 220, 0), D3DXVECTOR3(0.0f, 0.8f, 0.0f), 100.0f, 20.0f, 3);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 14)
				 {//�X�C�b�`ON
					 SetYajirusi(1, D3DXVECTOR3(100, 150.0f, 0));
					 SetYajirusi(0, D3DXVECTOR3(-90, 150.0f, 0));
					 SetBlock(D3DXVECTOR3(-110, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 30.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 14)
				 {//�X�C�b�`ON
					 SetYajirusi(1, D3DXVECTOR3(100, 150.0f, 0));
					 SetYajirusi(0, D3DXVECTOR3(-90, 150.0f, 0));
					 SetBlock(D3DXVECTOR3(-110, 200, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 180.0f, 30.0f, 1);
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 if (g_aSwitch[nCntSwitch].nType == 16)
				 {//�X�C�b�`ON
					 for (int nCut = 0; nCut < 10; nCut++)
					 {//�K�i
						 SetBlock(D3DXVECTOR3(1500.0f + (nCut * 50.0f), 585 - (nCut * 30.0f), 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 20.0f, 8);
					 }
					 g_aSwitch[nCntSwitch].nType = 6;
				 }
				 
			 }
		 }
	 }
}
			
//=============================================================================
// �G�̎擾
//=============================================================================
Switch *GetSwitch(void)
{
	return &g_aSwitch[0];
}
