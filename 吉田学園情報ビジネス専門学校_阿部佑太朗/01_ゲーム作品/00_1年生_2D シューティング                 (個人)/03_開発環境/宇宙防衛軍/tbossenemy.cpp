//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "tbossenemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "enemy.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_TBOSSENEMY		(4)								// �G�̎��
#define TBOSSENEMY_01 "data/TEXTURE/enemy002.png"
#define TBOSSENEMY_02 "data/TEXTURE/enemy004.png"
#define TBOSSENEMY_03 "data/TEXTURE/enemy002.png"
#define TBOSSENEMY_04 "data/TEXTURE/enemy003.png"


//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureTBossEnemy[MAX_TYPE_TBOSSENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTBossEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
TBossEnemy g_aTBossEnemy[MAX_TBOSSENEMY];										//�G�̏��
int g_nNumTBossEnemy;

//=============================================================================
// ����������
//=============================================================================
void InitTBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTBossEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		g_aTBossEnemy[nCntTBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aTBossEnemy[nCntTBossEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTBossEnemy[nCntTBossEnemy].nType = 0;
		g_aTBossEnemy[nCntTBossEnemy].bUse = false;
		g_aTBossEnemy[nCntTBossEnemy].nLife = 50;
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 0;
		g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;
		g_nNumTBossEnemy = 0;
		g_aTBossEnemy[nCntTBossEnemy].nCounterBullet = 0;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_01, &g_apTextureTBossEnemy[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_02, &g_apTextureTBossEnemy[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_03, &g_apTextureTBossEnemy[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, TBOSSENEMY_04, &g_apTextureTBossEnemy[3]);



	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TBOSSENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTBossEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//����
		pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//����
		pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//�E��
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);			//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);			//�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTBossEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTBossEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_TBOSSENEMY; nCntTex++)
	{
		if (g_apTextureTBossEnemy[nCntTex] != NULL)
		{
			g_apTextureTBossEnemy[nCntTex]->Release();
			g_apTextureTBossEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTBossEnemy != NULL)
	{
		g_pVtxBuffTBossEnemy->Release();
		g_pVtxBuffTBossEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTBossEnemy(void)
{

	int nCntTBossEnemy;


	for (nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		g_aTBossEnemy[nCntTBossEnemy].nCounterBullet++;
		Player*pPlayer;
		pPlayer = GetPlayer();
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //�G���g�p����Ă���
		{//�G�ɓ���������v���C���[���f�X���
			if (pPlayer->bDisp == true)
			{//
				if (pPlayer->pos.x - BOSSENEMY_SIZEMAX < g_aTBossEnemy[nCntTBossEnemy].pos.x && pPlayer->pos.x + BOSSENEMY_SIZEMAX > g_aTBossEnemy[nCntTBossEnemy].pos.x  &&
					pPlayer->pos.y - BOSSENEMY_SIZEMAX < g_aTBossEnemy[nCntTBossEnemy].pos.y && pPlayer->pos.y + BOSSENEMY_SIZEMAX > g_aTBossEnemy[nCntTBossEnemy].pos.y)
				{
					HitPlayer(pPlayer->nLife);

				}
			}
		}
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //�G���g�p����Ă���
		{
			if (rand() % 8 == 0)
			{//�U����
				float fBullet;

				fBullet = 0.05f * ((g_aTBossEnemy[nCntTBossEnemy].nCounterBullet) % 3600);

				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(fBullet)*10.0f, cosf(fBullet)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//�e
				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(3.14f - fBullet)*10.0f, cosf(3.14f - fBullet)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//�e

			}
			else if (rand() % 100 == 0)
			{

				float fDiffAngle;				//����
				float fDestAngle;				//�ړI�̊p�x
				float fMoveAngle;				//���݂̊p�x
				fDestAngle = D3DX_PI;
				fDestAngle = atan2f(pPlayer->pos.x - g_aTBossEnemy[nCntTBossEnemy].pos.x, pPlayer->pos.y - g_aTBossEnemy[nCntTBossEnemy].pos.y);
				fMoveAngle = (0.0f, 0.0f, 0.0f);

				fDiffAngle = fDestAngle - fMoveAngle;
				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				if (fDiffAngle < -D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				fMoveAngle += fDiffAngle * 0.1f;
				if (fMoveAngle > D3DX_PI)
				{
					fMoveAngle -= D3DX_PI * 2.0f;
				}
				if (fMoveAngle < -D3DX_PI)
				{
					fMoveAngle += D3DX_PI * 2.0f;
				}
				SetBullet(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXVECTOR3(sinf(fDiffAngle)*10.0f, cosf(fDiffAngle)*10.0f, 0.0f), BULLTETYPE_ENEMY);	//�e

			}
		}

		switch (g_aTBossEnemy[nCntTBossEnemy].state)
		{
		case TBOSSENEMYSTATE_NOMAL:
			//	�J�E���g�_�E��
			g_aTBossEnemy[nCntTBossEnemy].nCounterState--;
			if (g_aTBossEnemy[nCntTBossEnemy].bUse == true)
			{//	�G���g�p����Ă�����
				g_aTBossEnemy[nCntTBossEnemy].pos.x += g_aTBossEnemy[nCntTBossEnemy].move.x;
				g_aTBossEnemy[nCntTBossEnemy].pos.y += g_aTBossEnemy[nCntTBossEnemy].move.y;
				//	���_���̍쐬
				VERTEX_2D *pVtx;
				//	���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);
				//	�|�W�V����
				pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//����
				pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//�E��
				pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//����
				pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//�E��
				// ���_�o�b�t�@���A�����b�N����
				g_pVtxBuffTBossEnemy->Unlock();
				//	�ړ��̐ݒ�
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.x = 0;

					if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 1;

						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.y = 0;

							if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
							{
								g_aTBossEnemy[nCntTBossEnemy].move.x = -1;
							}
						}
					}
				}
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.x = 0;
					if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = -1;
						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.y = 0;
						}
						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.x = 1;
						}
					}

				}
				else
				{
					break;
				}

		case TBOSSENEMYSTATE_DAMAGE:
			g_aTBossEnemy[nCntTBossEnemy].pos.x += g_aTBossEnemy[nCntTBossEnemy].move.x;
			g_aTBossEnemy[nCntTBossEnemy].pos.y += g_aTBossEnemy[nCntTBossEnemy].move.y;

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

			//	�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//����
			pVtx[1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);	//�E��
			pVtx[2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//����
			pVtx[3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);	//�E��

			// ���_�o�b�t�@���A�����b�N����
			g_pVtxBuffTBossEnemy->Unlock();

			//�ړ��̐ݒ�o
			if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
			{
				g_aTBossEnemy[nCntTBossEnemy].move.x = 0;

				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 1100)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.y = 1;

					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 0;

						if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 600)
						{
							g_aTBossEnemy[nCntTBossEnemy].move.x = -1;
						}
					}
				}
			}
			if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
			{
				g_aTBossEnemy[nCntTBossEnemy].move.x = 0;
				if (g_aTBossEnemy[nCntTBossEnemy].pos.x == 950)
				{
					g_aTBossEnemy[nCntTBossEnemy].move.y = -1;
					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.y = 0;
					}
					if (g_aTBossEnemy[nCntTBossEnemy].pos.y == 200)
					{
						g_aTBossEnemy[nCntTBossEnemy].move.x = 1;
					}
				}

			}

			g_aTBossEnemy[nCntTBossEnemy].nCounterState--; //�J�E���g�_�E��
			if (g_aTBossEnemy[nCntTBossEnemy].nCounterState <= 0)
			{
				g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;

				VERTEX_2D*pVtx;								//���_���̃|�C���^
				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
				g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntTBossEnemy * 4);//���_�|�C���^��4�i�߂�

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���_�o�b�t�@�A�����b�N����
				g_pVtxBuffTBossEnemy->Unlock();

			}
			break;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffTBossEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureTBossEnemy[g_aTBossEnemy[nCntTBossEnemy].nType]);
			//�|���S���̕`��
			if (g_aTBossEnemy[nCntTBossEnemy].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntTBossEnemy * 4,
					2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetTBossEnemy(D3DXVECTOR3 pos,int nType)
{
	int nCntTBossEnemy;
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntTBossEnemy = 0; nCntTBossEnemy < MAX_TBOSSENEMY; nCntTBossEnemy++)
	{
		if (g_aTBossEnemy[nCntTBossEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aTBossEnemy[nCntTBossEnemy].pos = D3DXVECTOR3(1400, 300, 0.0f);
			g_aTBossEnemy[nCntTBossEnemy].move = D3DXVECTOR3(-1, 0, 0);
			//g_aTBossEnemy[nCntTBossEnemy].pos = pos;
			g_aTBossEnemy[nCntTBossEnemy].nType = nType;
			g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_NOMAL;
			g_aTBossEnemy[nCntTBossEnemy].nCounterState = 0;
			g_aTBossEnemy[nCntTBossEnemy].nLife = 50;//�G�̃��C�t�ݒ�
			g_aTBossEnemy[nCntTBossEnemy].bUse = true;//�G���g�p����Ă���

			//�|�W�V����
			pVtx[nCntTBossEnemy * 4].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y - BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x - BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);
			pVtx[nCntTBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aTBossEnemy[nCntTBossEnemy].pos.x + BOSSENEMY_SIZEMAX, g_aTBossEnemy[nCntTBossEnemy].pos.y + BOSSENEMY_SIZEMAX, 0.0f);

			g_nNumTBossEnemy++;
			break;
		}
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffTBossEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
TBossEnemy *GetTBossEnemy(void)
{
	return &g_aTBossEnemy[0];
}
//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitTBossEnemy(int nCntTBossEnemy, int nDamage)
{
	g_aTBossEnemy[nCntTBossEnemy].nLife -= nDamage;


	if (g_aTBossEnemy[nCntTBossEnemy].nLife <= 0)
	{//���C�t��0�ɂȂ����ꍇ
   		SetExplosion(g_aTBossEnemy[nCntTBossEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//SetGemeState(GAMESTATE_END);								//���U���g��ʂ�
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 90;			//�_���[�W��Ԏ���
		SetGemeState(GAMESTATE_CLEAR);								//���U���g��ʂ�
		g_aTBossEnemy[nCntTBossEnemy].bUse = false;
			AddScore(10000);

	}
	else
	{
		g_aTBossEnemy[nCntTBossEnemy].state = TBOSSENEMYSTATE_DAMAGE;
		g_aTBossEnemy[nCntTBossEnemy].nCounterState = 10;		//�_���[�W��Ԏ���

		VERTEX_2D*pVtx;								//���_���̃|�C���^
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffTBossEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[nCntTBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[nCntTBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffTBossEnemy->Unlock();
	}

	//�U������ENMY���I�ɂȂ�
	//
	/*if ((g_aEnemy[nCntEnemy].nLife <= 0) || (g_aEnemy[nCntEnemy].nType = 0))
	{
		AddScore(g_aEnemy[nCntEnemy].nType + 1);
	}*/
}
