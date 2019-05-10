//=============================================================================
//
// �u���b�N�̏��� [Block.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "player.h"	
#include "input.h"
#include "sound.h"
#include "item.h"
#include "switch.h"
#include "fade.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define Block_TEXTURENAMRE0 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE1 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE2 "data/TEXTURE/block002.jpg"
#define Block_TEXTURENAMRE3 "data/TEXTURE/block003.jpg"
#define Block_TEXTURENAMRE4 "data/TEXTURE/block004.jpg"
#define Block_TEXTURENAMRE5 "data/TEXTURE/block001.jpg"
#define Block_TEXTURENAMRE6 "data/TEXTURE/beltkon000.png"
#define Block_TEXTURENAMRE7 "data/TEXTURE/bane000.png"
#define Block_TEXTURENAMRE8 "data/TEXTURE/kaidan000.png"
#define Block_TEXTURENAMRE9 "data/TEXTURE/Dokan001.png"
#define Block_TEXTURENAMRE10 "data/TEXTURE/kumo000.png"
#define Block_TEXTURENAMRE11 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE12 "data/TEXTURE/hatena000.png"
#define Block_TEXTURENAMRE13 "data/TEXTURE/bane001.png"
#define Block_TEXTURENAMRE14 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE15 "data/TEXTURE/.png"
#define Block_TEXTURENAMRE16 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE17 "data/TEXTURE/block000.jpg"
#define Block_TEXTURENAMRE18 "data/TEXTURE/tuto000.png"
#define Block_TEXTURENAMRE19 "data/TEXTURE/kanban000.png"
#define Block_TEXTURENAMRE20 "data/TEXTURE/kanban001.png"
#define Block_TEXTURENAMRE21 "data/TEXTURE/kanban002.png"
#define Block_TEXTURENAMRE22 "data/TEXTURE/kanban003.png"
#define Block_TEXTURENAMRE23 "data/TEXTURE/kanban004.png"
#define Block_TEXTURENAMRE24 "data/TEXTURE/hatena000.png"
#define Block_TEXTURENAMRE25 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE26 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE27 "data/TEXTURE/doa000.jpg"
#define Block_TEXTURENAMRE28 "data/TEXTURE/kanban005.png"
#define Block_TEXTURENAMRE29 "data/TEXTURE/kanban006.png"
#define Block_TEXTURENAMRE30 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE31 "data/TEXTURE/Dokan000.png"
#define Block_TEXTURENAMRE32 "data/TEXTURE/upblock000.png"
#define Block_TEXTURENAMRE33 "data/TEXTURE/aaa.png"
#define Block_TEXTURENAMRE34 "data/TEXTURE/111.png"
#define Block_TEXTURENAMRE35 "data/TEXTURE/upblock000.png"
#define	MAX_Block		(266)					// �u���b�N�̍ő吔
#define POS_X (150)								//�|�W�V����_X
#define POS_Y (25)								//�|�W�V����_Y
#define TEX_MAX (36)

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_Block];						//�u���b�N�̏��
bool g_BreakBlock;
bool g_Item =false;
bool g_blockSwitti;
//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nCounterrMove = 0;
		g_aBlock[nCntBlock].nType = 0;
		g_aBlock[nCntBlock].fWindth = 0;		//��
		g_aBlock[nCntBlock].fHeight = 0;		//����
		g_aBlock[nCntBlock].bUse = false;
	}
	g_blockSwitti = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE0, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE7, &g_pTextureBlock[7]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE8, &g_pTextureBlock[8]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE9, &g_pTextureBlock[9]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE10, &g_pTextureBlock[10]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE11, &g_pTextureBlock[11]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE12, &g_pTextureBlock[12]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE13, &g_pTextureBlock[13]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE14, &g_pTextureBlock[14]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE15, &g_pTextureBlock[15]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE16, &g_pTextureBlock[16]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE17, &g_pTextureBlock[17]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE18, &g_pTextureBlock[18]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE19, &g_pTextureBlock[19]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE20, &g_pTextureBlock[20]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE21, &g_pTextureBlock[21]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE22, &g_pTextureBlock[22]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE23, &g_pTextureBlock[23]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE24, &g_pTextureBlock[24]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE25, &g_pTextureBlock[25]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE26, &g_pTextureBlock[26]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE27, &g_pTextureBlock[27]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE28, &g_pTextureBlock[28]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE29, &g_pTextureBlock[29]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE30, &g_pTextureBlock[30]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE31, &g_pTextureBlock[31]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE32, &g_pTextureBlock[32]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE33, &g_pTextureBlock[33]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE34, &g_pTextureBlock[34]);
	D3DXCreateTextureFromFile(pDevice, Block_TEXTURENAMRE35, &g_pTextureBlock[35]);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Block,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);													//����
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);						//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);						//����
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//�E��
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
	g_pVtxBuffBlock->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlock[nCount] != NULL)
		{
			g_pTextureBlock[nCount]->Release();
			g_pTextureBlock[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=============================================================================
// �X�V���� 
//=============================================================================
void UpdateBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		g_aBlock[nCntBlock].posOld.x = g_aBlock[nCntBlock].pos.x;
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].pos.x == 0)
		{
			g_aBlock[nCntBlock].move.x = 0;
		}
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPlyer->pos.x >= 0)
			{//�v���C���[��0�ȏ�Ȃ�u���b�N���v���C���[�Ƃ͔��Ε����ɓ�����
				g_aBlock[nCntBlock].pos.x -= pPlyer->move.x;
				//	g_aBlock[nCntBlock].pos.x -= pPlyer->pos.x - pPlyer->posOld.x;

			}
			if (pPlyer->pos.y >= -0.1f)
			{
				g_aBlock[nCntBlock].pos.y -= pPlyer->move.y;
			}
			if (pPlyer->pos.y >= 0.1f)
			{
				g_aBlock[nCntBlock].pos.y += pPlyer->move.y;
			}

			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			g_aBlock[nCntBlock].nCounterrMove++;

			//�^�C�v3
			if (g_aBlock[nCntBlock].nCounterrMove % 60 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 3)
				{
					g_aBlock[nCntBlock].move.y *= 1.0f;
				}
			}
			if (g_aBlock[nCntBlock].nCounterrMove % 120 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 3)
				{
					g_aBlock[nCntBlock].move.y *= -1.0f;
				}
			}
			//�^�C�v15
			if (g_aBlock[nCntBlock].nCounterrMove % 60 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 15)
				{
					g_aBlock[nCntBlock].move.x *= 1.0f;
				}
			}
			if (g_aBlock[nCntBlock].nCounterrMove % 120 == 0)
			{
				if (g_aBlock[nCntBlock].nType == 15)
				{
					g_aBlock[nCntBlock].move.x *= -1.0f;
				}
			}
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//����
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//����
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//�E��
			
		}
		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);

		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)	//�u���b�N���g�p����Ă��Ȃ�
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWindth = fWindth;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].bUse = true;//�u���b�N���g�p����Ă���
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//����
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y - 0, 0.0f);//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 0, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//����
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);//�E��
			
			if (g_aBlock[nCntBlock].nType == 0)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//����
				pVtx[1].tex = D3DXVECTOR2(10.0f * 10/10, 0.0f);						//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f * 10 / 10);					//����
				pVtx[3].tex = D3DXVECTOR2(10.0f * 10 / 10, 5.0f * 10 / 10);			//�E��
			}
			if (g_aBlock[nCntBlock].nType == 16)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//����
				pVtx[1].tex = D3DXVECTOR2(1.0, 0.0f);								//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 5.0f * 10 / 10);					//����
				pVtx[3].tex = D3DXVECTOR2(1.0, 5.0f * 10 / 10);						//�E��
			}
			if (g_aBlock[nCntBlock].nType == 17)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);								//����
				pVtx[1].tex = D3DXVECTOR2(50.0f * 10 / 10, 0.0f);					//�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);								//����
				pVtx[3].tex = D3DXVECTOR2(50.0f * 10 / 10,1.0f);					//�E��
			}
			break;
		}
		pVtx += 4;			//�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
//�u���b�N�ƃv���C���[�Ƃ̔��菈��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 bool bLand = false;	//���n�������ǂ���
	 Enemy *pEnemy;
	 pEnemy = GetEnemy();

	 for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	 {
		 if (g_aBlock[nCntBlock].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aBlock[nCntBlock].pos.x  &&									//�v���C���[���E����߂荞��ł�Ƃ�
				 pPos->x - (*fWindth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&		//�v���C���[��������߂荞��ł�Ƃ�
				 pPos->y >= g_aBlock[nCntBlock].pos.y &&															//�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
				 pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)					//�v���C���[���������ɂ߂荞��ł�Ƃ�
			 {//YX���͈͓�
				 if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
				 {//�u���b�N�㔻��
					 bLand = true;
					 pPos->y = g_aBlock[nCntBlock].pos.y;		//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
					 if (pMove->y >= 20.0f)
					 {
						 HitPlayer(1);
					 }
					 pMove->y = 0.0f;
					 //�^�C�v2------------------------
					 if (g_aBlock[nCntBlock].nType == 2)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�u���b�N(�u���b�N������)
						 bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;														//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						 g_aBlock[nCntBlock].move.y = 0.8f;
					 }
					 //�^�C�v6------------------------
					 if (g_aBlock[nCntBlock].nType == 6)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�x���g�R���x�A
					  //bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;																						//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						 pMove->x = pMove->x + 1.0f;
					 }
					 //�^�C�v7------------------------
					 if (g_aBlock[nCntBlock].nType == 13)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�΂�
						 bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;																						//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						 pMove->y -= 20;				//�d��
						 g_aBlock[nCntBlock].nType = 7;
					 }
					 else if (g_aBlock[nCntBlock].nType == 7)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�΂�
						 PlaySound(SOUND_LABEL_SE_BANE);

						 g_aBlock[nCntBlock].nType = 13;
					 }

					 //�^�C�v3------------------------
					 if (g_aBlock[nCntBlock].nType == 3)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�u���b�N��(�������㉺)
						 bLand = true;

						 pPos->y = g_aBlock[nCntBlock].pos.y;														//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						 //pPos->y += g_aBlock[nCntBlock].move.y;
						 pPos->y += g_aBlock[nCntBlock].move.y;

					 }
					 //�^�C�v15------------------------
					 if (g_aBlock[nCntBlock].nType == 15)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�u���b�N��(������)
						 bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x;
						 pPos->x += g_aBlock[nCntBlock].move.x;
						 //pMove->x += g_aBlock[nCntBlock].move.x;
						 /*if (g_aBlock[nCntBlock].move.y >= 1.0f)
						 {
						 pPos->y -= g_aBlock[nCntBlock].move.y;
						 }
						 if (g_aBlock[nCntBlock].move.y <= -1.0f)
						 {
						 pPos->y += g_aBlock[nCntBlock].move.y;
						 }*/
					 }
					 //�^�C�v10------------------------
					 if (g_aBlock[nCntBlock].nType == 10)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�u���b�N��(�蓮�œ���)
					  //bLand = true;
						 pPos->y = g_aBlock[nCntBlock].pos.y;														//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
						 g_aBlock[nCntBlock].pos.x = pPos->x;
						 g_aBlock[nCntBlock].pos.x = 560;
					 }
					 //�^�C�v4-----------------------
					 if (g_aBlock[nCntBlock].nType == 4)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
					 {//�u���b�N��ɏ������false
						 bLand = true;
						 PlaySound(SOUND_LABEL_SE_BAKEHATU);
						 g_aBlock[nCntBlock].pos.y = 900;
					 }
					 //�^�C�v14-----------------------
					 if (g_aBlock[nCntBlock].nType == 14)
					 {

						 /*( g_aBlock[nCntBlock].nType = 14)=g_aBlock[nCntBlock].move.y = 1;
						 if (g_aBlock[nCntBlock].nType = 14 && g_aBlock[nCntBlock].posOld.y >= g_aBlock[nCntBlock].pos.y + 30)
						 {
							 g_aBlock[nCntBlock].move.y = -1;
						 }
						  pPos->y = g_aBlock[nCntBlock].pos.y;*/
					 }
				 }
				 else if (pPosOld->y - *fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&	//�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
					 pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)				//���݂̈ʒu���߂荞��ł�Ƃ�
				 {//�u���b�N������
					 //bLand = true;
					 pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;				//�v���C���[���u���b�N���S+�u���b�N�̍���+�v���C���[�̍����̈ʒu�ɏo��������
					 pMove->y = 0.0f;
					 //�^�C�v12------------------------
					 if (g_aBlock[nCntBlock].nType == 12)
					 {////?�u���b�N�R�C��
						 PlaySound(SOUND_LABEL_SE_HATENA);
						 bLand = true;
						 //�X�C�b�`
						 SetItem(0, D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWindth / 2), g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						 g_aBlock[nCntBlock].nType = 0;

					 }
					 //�^�C�v24------------------------
					 if (g_aBlock[nCntBlock].nType == 24)
					 {//?�u���b�N��
						 PlaySound(SOUND_LABEL_SE_HATENA);
						 SetItem(2, D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWindth / 2), g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						 g_aBlock[nCntBlock].nType = 0;

					 }
				 }
				 else if (pPosOld->x + *fWindth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&	//�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x - *fWindth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth)
				 {//�u���b�N�E����
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 pEnemy->move.x = 3.0f;
					 //�^�C�v5------------------------
					 if (g_aBlock[nCntBlock].nType == 5)
					 {//���E�Ɏ蓮�œ�����
						 g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x - 1.0f;
					 }
					 //�^�C�v11------------------------
					 if (g_aBlock[nCntBlock].nType == 11)
					 {//N�L�[�ŏ�ɏオ��
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;

						 }
						 else  if (GetKeyboardTrigger(DIK_N) == false)
						 {
							 g_aBlock[nCntBlock].pos.y += *fHeight;
						 }
					 }

				 }
				 else if (pPosOld->x - *fWindth <= g_aBlock[nCntBlock].pos.x &&									//�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x + *fWindth >= g_aBlock[nCntBlock].pos.x)
				 {//�u���b�N������
					 //bLand = true;
					 pPos->x = pPosOld->x;																		//�̂̈ʒu�ɏo��������
					 pMove->x = 0.0f;
					 pEnemy->move.x = -3.0f;
					 //�^�C�v5------------------------
					 if (g_aBlock[nCntBlock].nType == 5)
					 {//���E�Ɏ蓮�œ�����
						 g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x + 2.0f;
					 }
					 //�^�C�v8------------------------
					 if (g_aBlock[nCntBlock].nType == 8)															//�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 {//�u���b�N������ (�K�i)
						 //bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x;													//�̂̈ʒu�ɏo��������
						 pPos->y = g_aBlock[nCntBlock].pos.y;
						 pMove->x = 5.0f;

						 // g_aBlock[nCntBlock].move.y = 1.0f;
					 }
					 if (g_aBlock[nCntBlock].nType == 11)
					 {//N�L�[�ŏ�ɏオ��
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 25)
					 {//N�L�[�ŏ�ɏオ��
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 //�Z�b�g�G�l�~�[
							 SetEnemy(3, D3DXVECTOR3(1000, 300.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 50, 70, 7);
							 SetEnemy(2, D3DXVECTOR3(900, 300.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(2, D3DXVECTOR3(1150, 300.0f, 0), D3DXVECTOR3(0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(1, D3DXVECTOR3(1300, 300.0f, 0), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), 30, 60, 3);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 30)
					 {//N�L�[�ŏ�ɏオ��
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 //�Z�b�g�G�l�~�[
							 SetEnemy(3, D3DXVECTOR3(1000, 300.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 50, 70, 7);
							 SetEnemy(2, D3DXVECTOR3(900, 300.0f, 0), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(3, D3DXVECTOR3(1150, 300.0f, 0), D3DXVECTOR3(0.6f, 0.0f, 0.0f), 30, 60, 3);
							 SetEnemy(1, D3DXVECTOR3(4300, 500.0f, 0), D3DXVECTOR3(0.5f, 0.0f, 0.0f), 30, 60, 2);
							 SetEnemy(1, D3DXVECTOR3(4500, 500.0f, 0), D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30, 60, 2);
							 SetEnemy(1, D3DXVECTOR3(4800, 500.0f, 0), D3DXVECTOR3(0.8f, 0.0f, 0.0f), 30, 60, 2);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 32)
					 {//N�L�[�ŏ�ɏオ��
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 SetBlock(D3DXVECTOR3(1400, 355.0f, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40.0f, 50.0f, 33);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
					 //�^�C�v9------------------------
					 if (g_aBlock[nCntBlock].nType == 9)
					 {//�y�ǉ������
					  //bLand = true;
						 pPos->x = g_aBlock[nCntBlock].pos.x + *fWindth;																		//�̂̈ʒu�ɏo��������
						 pMove->x = 0.0f;
						 pMove->y = -30;
					 }
					 if (g_aBlock[nCntBlock].nType == 14)
					 {//�h�A
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //���[�h�ݒ�
								 SetFade(MODE_SELECT);

							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 26)
					 {//�h�A
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //���[�h�ݒ�
								 SetFade(MODE_GAME2);

							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 27)
					 {//�h�A
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 if (GetKeyboardTrigger(DIK_N) == true)
							 {
								 PlaySound(SOUND_LABEL_SE_DOA);
								 //���[�h�ݒ�
								 SetFade(MODE_GAME3);
							 }
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 33)
					 {
						 FADE pFade;
						 pFade = *GetFade();
						 if (pFade == FADE_NONE)
						 {
							 //���[�h�ݒ�
							 SetFade(MODE_CLIA);
						 }
					 }
					 if (g_aBlock[nCntBlock].nType == 35)
					 {//�h�A
						 if (GetKeyboardTrigger(DIK_N) == true)
						 {
							 PlaySound(SOUND_LABEL_SE_BLOCK000);
							 g_aBlock[nCntBlock].pos.y -= *fHeight;
						 }
					 }
				 }

			 }
		 }
	 }
	 return bLand;
}
//=============================================================================
//�u���b�N�ƃG�l�~�[�Ƃ̔��菈��
//=============================================================================
void CollisionBlockEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	for (int nCntBlock = 0; nCntBlock < MAX_Block; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aBlock[nCntBlock].pos.x  &&
				pPos->x - (*fWindth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&
				pPos->y >= g_aBlock[nCntBlock].pos.y &&
				pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
			{//YX���͈͓�
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//�u���b�N�㔻��
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;

				}
				else if (pPosOld->y - *fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - *fHeight <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//�u���b�N������
				 //bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;
					pMove->y = 0.0f;

				}
				else if (pPosOld->x + *fWindth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth &&
					pPos->x - *fWindth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWindth)
				{//�u���b�N�E����
				 //	bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
					if (pMove->x <= 0)
					{
						pMove->x = 1.0f;
					}
				}
				else if (pPosOld->x - *fWindth <= g_aBlock[nCntBlock].pos.x &&
					pPos->x + *fWindth >= g_aBlock[nCntBlock].pos.x)
				{//�u���b�N������
				 //bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
					if (pMove->x <= 0)
					{
						pMove->x -= 1.0f;
					}
				}
			}
		}
	}
}
			
//=============================================================================
// �G�̎擾
//=============================================================================
Block *Getblock(void)
{
	return &g_aBlock[0];
}