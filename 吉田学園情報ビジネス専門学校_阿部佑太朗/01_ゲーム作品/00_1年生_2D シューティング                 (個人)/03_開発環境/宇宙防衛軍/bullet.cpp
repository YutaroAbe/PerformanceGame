//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================

//*****************************************************************************
//	�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bullet.h"		//	�e
#include "main.h"		//	���C��
#include "player.h"		//	�v���C���[
#include "input.h"		//	����
#include "explosion.h"	//	����
#include "enemy.h"		//	�G
#include "sideenemy.h"	//	�T�C�h���̓G
#include "tbossenemy.h"	//	�{�X
#include "effect.h"		//	�G�t�F�N�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(10000)								//	�e�̍ő吔
#define POS_X			(5)									//	�|�W�V����_X
#define POS_Y			(5)									//	�|�W�V����_Y2
#define BULLET_TEXTURENAMRE "data/TEXTURE/bullet000.png"	//	�e�N�X�`���̖��O

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//	�ʒu
	D3DXVECTOR3 move;   //	�ړ���
	BULLETTYPE type;	//	�e�̎��
	bool bUse;          //	�g�p���Ă��邩�ǂ���
	int nLife;			//	����

}Bullet;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//	�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//	���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//	�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	�e�̊m�ە���
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�ʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	����
		g_aBullet[nCntBullet].bUse = false;								//	�g�p���Ă��邩���Ȃ���
		g_aBullet[nCntBullet].nLife = 0;								//	����
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAMRE, &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	�e�̊m�ە���
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);	//	����
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);	//	�E��
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);	//	����
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);	//	�E��
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//	����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//	�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//	����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//	�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{//	�e�N�X�`�����g�p����Ă����ꍇ
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{//	���_�o�b�t�@���g�p����Ă����ꍇ
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;	//	���_���̃|�C���^

	//	���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//	�e�̊m�ە���
		if (g_aBullet[nCntBullet].bUse == true)
		{//	�e���g�p����Ă��邩
			//�e���ړ�������
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);

			//�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			if (g_aBullet[nCntBullet].pos.y <= 0|| g_aBullet[nCntBullet].pos.y >= 780 || g_aBullet[nCntBullet].pos.x <= 0 || g_aBullet[nCntBullet].pos.x >= 1280)
			{//	��ʊO�ɏo���ꍇ
				g_aBullet[nCntBullet].bUse = false;	//	�e������
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//	�v���C���[�̒e
				//	��莞�Ԍo��
				g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//	�e�̃��C�t�ݒ�
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
				if (g_aBullet[nCntBullet].nLife >= 0)
				{//	�G�t�F�N�g�̏���
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 10.0f, 10);
					g_aBullet[nCntBullet].bUse = true;
				}

				//	�G�|�C���^
				Enemy *pEnemy;
				pEnemy = GetEnemy();

				//	���{�X�G�l�~�[�|�C���^
				TBossEnemy *pTBossEnemy;
				pTBossEnemy = GetTBossEnemy();

				//	�T�C�h�G�l�~�[�|�C���^
				SideEnemy *pSideEnemy;
				pSideEnemy = GetSideEnemy();

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//	�G�̊m�ە���
					if (pEnemy->bUse == true)
					{//�G���g�p����Ă���
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{//	�G�̒ʏ���
							//[�G�Ƃ̓����蔻��]
							if (pEnemy->pos.x - ENEMY_SIZEMAX < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + ENEMY_SIZEMAX > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - ENEMY_SIZEMAX < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + ENEMY_SIZEMAX > g_aBullet[nCntBullet].pos.y)
							{
								HitEnemy(nCntEnemy, 1);
								g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
							}
						}
					}
				}
				for (int nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++, pTBossEnemy++)
				{//���{�X�G�l�~�[
					if (pTBossEnemy->bUse == true) //�G���g�p����Ă���
					{
						//[�G�Ƃ̓����蔻��]
						if (pTBossEnemy->pos.x - 50 - 50 < g_aBullet[nCntBullet].pos.x && pTBossEnemy->pos.x + 50 + 50 > g_aBullet[nCntBullet].pos.x  &&
							pTBossEnemy->pos.y - 50 - 50 < g_aBullet[nCntBullet].pos.y && pTBossEnemy->pos.y + 50 + 50 > g_aBullet[nCntBullet].pos.y)
						{
							HitTBossEnemy(nCntTBossEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
						}
					}
				}
				for (int nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++, pSideEnemy++)
				{//��C�G�l�~�[
					if (pSideEnemy->bUse == false) //�G���g�p����Ă���
					{
						//[�G�Ƃ̓����蔻��]
						if (pSideEnemy->pos.x - 15 - 15 < g_aBullet[nCntBullet].pos.x && pSideEnemy->pos.x + 15 + 15 > g_aBullet[nCntBullet].pos.x  &&
							pSideEnemy->pos.y - 15 - 15 < g_aBullet[nCntBullet].pos.y && pSideEnemy->pos.y + 15 + 15 > g_aBullet[nCntBullet].pos.y)
						{
							HitSideEnemy(nCntSideEnemy, 1);
						}
					}
				}
			}
			else  if (g_aBullet[nCntBullet].type == BULLTETYPE_ENEMY)	//�G�̒e
			{//�v���C���[

				if (g_aBullet[nCntBullet].nLife >= 0)
				{//�G�t�F�N�g�̏���
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 10.0f, 5);
					g_aBullet[nCntBullet].bUse = true;
				}
				Player*pPlayer;
				pPlayer = GetPlayer();
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				//�v���C���[
				pPlayer = GetPlayer();
				if (pPlayer->bDisp == true)
				{
					//[�v���C���[�Ƃ̓����蔻��]
					if (pPlayer->pos.x - 10 - 10 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 10 + 10 > g_aBullet[nCntBullet].pos.x  &&
						pPlayer->pos.y - 10 - 10 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 10 + 10 > g_aBullet[nCntBullet].pos.y)
					{//	�v���C���[�͈͓̔��ɓ������ꍇ
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}

		}
		pVtx += 4;		//	�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBullet->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntBullet ,2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aBullet[nCntBullet].pos = pos;		//	�ʒu
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			g_aBullet[nCntBullet].nLife = 35;		//	����
			g_aBullet[nCntBullet].move = move;		//	����
			g_aBullet[nCntBullet].type = type;		//	���
			g_aBullet[nCntBullet].bUse = true;		//	�e���g�p����Ă���
			break;
		}
		pVtx += 4;			//	�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

