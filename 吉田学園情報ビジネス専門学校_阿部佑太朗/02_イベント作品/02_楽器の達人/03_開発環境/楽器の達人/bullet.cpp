//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "bullet.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(10000)						// �e�̍ő吔
#define POS_X (40)								//�|�W�V����_X
#define POS_Y (30)								//�|�W�V����_Y2
#define BULLET__TEXTURENAMRE "data/TEXTURE/.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;   //�ړ���
	BULLETTYPE type;	//�e�̎��
	bool bUse;          //�g�p���Ă��邩�ǂ���
	int nLife;			//����
}Bullet;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nLife = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET__TEXTURENAMRE, &g_pTextureBullet);

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

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);//����
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);//����
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);//�E��
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
		{
			//�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
		{
			//�J���[
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		}

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

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
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_2D*pVtx;//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă��邩
		{
			//�e���ړ�������
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}

			//��莞�Ԍo��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//�e�̃��C�t�ݒ�
				g_aBullet[nCntBullet].bUse = false;
			}

			Enemy *pEnemy;		//�G�l�~�[�|�C���^
			pEnemy = GetEnemy();

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)	//�v���C���[�̒e
			{
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//�G�l�~�[

					if (pEnemy->bUse == true) //�G���g�p����Ă���
					{
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{
							//[�G�Ƃ̓����蔻��]
							if (pEnemy->pos.x - 40 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 0 )	//�v���C���[�̒e
								{
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
								}
							}
							if (pEnemy->pos.x - 40 * 3 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 * 3 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 2)	//�v���C���[�̒e
								{
									AddScore(100);
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
								}
							}
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001 )	//�v���C���[�̒e
			{
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//�G�l�~�[

					if (pEnemy->bUse == true) //�G���g�p����Ă���
					{
						if (pEnemy->state == ENEMYSTATE_NOMAL)
						{
							//[�G�Ƃ̓����蔻��]
							if (pEnemy->pos.x - 40 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40> g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 1 )
								{
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
								}

							}
							if (pEnemy->pos.x - 40 *3 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 40 * 3 > g_aBullet[nCntBullet].pos.x  &&
								pEnemy->pos.y - 40 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 40 > g_aBullet[nCntBullet].pos.y)
							{
								if (pEnemy->nType == 2)	//�v���C���[�̒e
								{
									AddScore(100);
									HitEnemy(nCntEnemy, 1);
									g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
								}
							}
						}
					}
				}
			}
		}
		pVtx += 4;
	}

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
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBullet) ,
				2);
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
			g_aBullet[nCntBullet].pos = pos;

			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POS_X, g_aBullet[nCntBullet].pos.y + POS_Y, 0.0f);
			//����
			g_aBullet[nCntBullet].nLife = 6;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;//�e���g�p����Ă���

			if (g_aBullet[nCntBullet].type == BULLETTYPE_000)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_001)
			{
				//�J���[
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 0);
			}

			break;
		}
		pVtx += 4;			//�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

