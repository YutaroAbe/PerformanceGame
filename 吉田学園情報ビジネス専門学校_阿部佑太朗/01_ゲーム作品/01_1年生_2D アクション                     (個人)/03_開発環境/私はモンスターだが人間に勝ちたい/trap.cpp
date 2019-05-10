//=============================================================================
//
// �g���b�v�̏��� [Trap.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "trap.h"
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
#define Trap_TEXTURENAMRE0 "data/TEXTURE/trap000.png"
#define Trap_TEXTURENAMRE1 "data/TEXTURE/trap001.png"
#define Trap_TEXTURENAMRE2 "data/TEXTURE/trap002.png"
#define Trap_TEXTURENAMRE3 "data/TEXTURE/trap000.png"
#define Trap_TEXTURENAMRE4 "data/TEXTURE/trap003.png"

#define	MAX_Trap		(126)					// �u���b�N�̍ő吔
#define POS_X (150)								//�|�W�V����_X
#define POS_Y (25)								//�|�W�V����_Y
#define TEX_MAX (5)

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTrap[TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTrap = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
TRAP g_aTrap[MAX_Trap];						//�u���b�N�̏��
bool g_BreakTrap;
//bool g_Item = false;
bool g_TrapSwitti;
//=============================================================================
// ����������
//=============================================================================
void InitTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �u���b�N�̏��̏�����
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTrap[nCntTrap].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTrap[nCntTrap].nCounterrMove = 0;
		g_aTrap[nCntTrap].nType = 0;
		g_aTrap[nCntTrap].fWindth = 0;		//��
		g_aTrap[nCntTrap].fHeight = 0;		//����
		g_aTrap[nCntTrap].bUse = false;
	}
	g_TrapSwitti = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE0, &g_pTextureTrap[0]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE1, &g_pTextureTrap[1]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE2, &g_pTextureTrap[2]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE3, &g_pTextureTrap[3]);
	D3DXCreateTextureFromFile(pDevice, Trap_TEXTURENAMRE4, &g_pTextureTrap[4]);


	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Trap,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTrap,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);													//����
		pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);						//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);						//����
		pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//�E��
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
	g_pVtxBuffTrap->Unlock();

}
//=============================================================================
// �I������
//=============================================================================
void UninitTrap(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureTrap[nCount] != NULL)
		{
			g_pTextureTrap[nCount]->Release();
			g_pTextureTrap[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTrap != NULL)
	{
		g_pVtxBuffTrap->Release();
		g_pVtxBuffTrap = NULL;
	}
}
//=============================================================================
// �X�V���� 
//=============================================================================
void UpdateTrap(void)
{
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].posOld.x = g_aTrap[nCntTrap].pos.x;
	}
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		g_aTrap[nCntTrap].nCounterrMove++;
		if (g_aTrap[nCntTrap].pos.x == 0)
		{
			g_aTrap[nCntTrap].move.x = 0;
		}
		if (g_aTrap[nCntTrap].bUse == true)
		{
			g_aTrap[nCntTrap].pos.x += g_aTrap[nCntTrap].move.x;
			g_aTrap[nCntTrap].pos.y += g_aTrap[nCntTrap].move.y;
			if (pPlyer->pos.x >= 0)
			{//�v���C���[��0�ȏ�Ȃ�u���b�N���v���C���[�Ƃ͔��Ε����ɓ�����
				g_aTrap[nCntTrap].pos.x -= pPlyer->move.x;
				//	g_aTrap[nCntTrap].pos.x -= pPlyer->pos.x - pPlyer->posOld.x;

			}
			
			//�^�C�v3
			if (g_aTrap[nCntTrap].nCounterrMove % 60 == 0)
			{
				if (g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
				{
					g_aTrap[nCntTrap].move.y *= 1.0f;
				}
			}
			if (g_aTrap[nCntTrap].nCounterrMove % 120 == 0)
			{
				if (g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
				{
					g_aTrap[nCntTrap].move.y *= -1.0f;
				}
			}
			
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//����
			pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//����
			pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//�E��
			pVtx += 4;	//���_�|�C���^��4�i�߂�
		}
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTrap->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTrap, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTrap[g_aTrap[nCntTrap].nType]);
			// �|���S���̕`��
			if (g_aTrap[nCntTrap].bUse == true)//�u���b�N���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTrap, 2);
			}
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == false)	//�u���b�N���g�p����Ă��Ȃ�
		{
			g_aTrap[nCntTrap].pos = pos;
			g_aTrap[nCntTrap].move = move;
			g_aTrap[nCntTrap].fHeight = fHeight;
			g_aTrap[nCntTrap].fWindth = fWindth;
			g_aTrap[nCntTrap].nType = nType;
			g_aTrap[nCntTrap].bUse = true;		//�u���b�N���g�p����Ă���
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//����
			pVtx[1].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y - 0, 0.0f);//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x - 0, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//����
			pVtx[3].pos = D3DXVECTOR3(g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth, g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight, 0.0f);//�E��
			
			break;
		}
		pVtx += 4;								//�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTrap->Unlock();
}
//=============================================================================
//�u���b�N�ƃv���C���[�Ƃ̔��菈��
//=============================================================================
void CollisionTrap(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	 Enemy *pEnemy;
	 pEnemy = GetEnemy();

	 for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	 {
		 if (g_aTrap[nCntTrap].bUse == true)
		 {
			 if (pPos->x + (*fWindth / 2) >= g_aTrap[nCntTrap].pos.x  &&									//�v���C���[���E����߂荞��ł�Ƃ�
				 pPos->x - (*fWindth / 2) <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&		//�v���C���[��������߂荞��ł�Ƃ�
				 pPos->y >= g_aTrap[nCntTrap].pos.y &&															//�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
				 pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)					//�v���C���[���������ɂ߂荞��ł�Ƃ�
			 {//YX���͈͓�
				 if (pPosOld->y <= g_aTrap[nCntTrap].pos.y && pPos->y >= g_aTrap[nCntTrap].pos.y)			//�̂̈ʒu����ɋ��Č��݂̈ʒu���v���b�N�ɂ߂荞��ł�Ƃ�
				 {//�u���b�N�㔻��
					 pPos->y = g_aTrap[nCntTrap].pos.y;		//�v���C���[���u���b�N�̃|�W�V����Y�ɏo��������
					 pMove->y = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3 || g_aTrap[nCntTrap].nType == 4)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 1)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = -15.0f;
						 HitPlayer(1);
					 }
					
				 }
				 else if (pPosOld->y - *fHeight >= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight &&	//�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
					 pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)				//���݂̈ʒu���߂荞��ł�Ƃ�
				 {//�u���b�N������
					 //bLand = true;
					 pPos->y = g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight + *fHeight;				//�v���C���[���u���b�N���S+�u���b�N�̍���+�v���C���[�̍����̈ʒu�ɏo��������
					 pMove->y = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = 15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->y = 15.0f;
						 HitPlayer(1);
					 }
				 }
				 else if (pPosOld->x + *fWindth >= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&	//�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x - *fWindth <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth)
				 {//�u���b�N�E����
				 //	bLand = true;
					 pPos->x = pPosOld->x;
					 pMove->x = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = 15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = 15.0f;
						 pMove->y = -10.0f;
						 HitPlayer(1);
					 }
				 }
				 else if (pPosOld->x - *fWindth <= g_aTrap[nCntTrap].pos.x &&									//�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					 pPos->x + *fWindth >= g_aTrap[nCntTrap].pos.x)
				 {//�u���b�N������
					 //bLand = true;
					 pPos->x = pPosOld->x;																		//�̂̈ʒu�ɏo��������
					 pMove->x = 0.0f;
					 if (g_aTrap[nCntTrap].nType == 0 || g_aTrap[nCntTrap].nType == 3)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = -15.0f;
						 HitPlayer(1);
					 }
					 if (g_aTrap[nCntTrap].nType == 2)
					 {
						 PlaySound(SOUND_LABEL_SE_TRAP0);
						 pMove->x = -15.0f;
						 pMove->y = -10.0f;
						 HitPlayer(1);
					 }
				 }
				 
			 }
		 }
	 }
}
//=============================================================================
//�u���b�N�ƃG�l�~�[�Ƃ̔��菈��
//=============================================================================
void CollisionTrapEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{

	for (int nCntTrap = 0; nCntTrap < MAX_Trap; nCntTrap++)
	{
		if (g_aTrap[nCntTrap].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aTrap[nCntTrap].pos.x  &&
				pPos->x - (*fWindth / 2) <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&
				pPos->y >= g_aTrap[nCntTrap].pos.y &&
				pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)
			{//YX���͈͓�
				if (pPosOld->y <= g_aTrap[nCntTrap].pos.y && pPos->y >= g_aTrap[nCntTrap].pos.y)
				{//�u���b�N�㔻��
					pPos->y = g_aTrap[nCntTrap].pos.y;
					pMove->y = 0.0f;

				}
				else if (pPosOld->y - *fHeight >= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight &&
					pPos->y - *fHeight <= g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight)
				{//�u���b�N������
				 //bLand = true;
					pPos->y = g_aTrap[nCntTrap].pos.y + g_aTrap[nCntTrap].fHeight + *fHeight;
					pMove->y = 0.0f;

				}
				else if (pPosOld->x + *fWindth >= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth &&
					pPos->x - *fWindth <= g_aTrap[nCntTrap].pos.x + g_aTrap[nCntTrap].fWindth)
				{//�u���b�N�E����
				 //	bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
				}
				else if (pPosOld->x - *fWindth <= g_aTrap[nCntTrap].pos.x &&
					pPos->x + *fWindth >= g_aTrap[nCntTrap].pos.x)
				{//�u���b�N������
				 //bLand = true;
					pPos->x = pPosOld->x;
					pMove->x = 0;
				}
			}
		}
	}
}
			
//=============================================================================
// �G�̎擾
//=============================================================================
TRAP *GetTrap(void)
{
	return &g_aTrap[0];
}