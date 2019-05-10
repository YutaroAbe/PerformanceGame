//=============================================================================
//
// �G�̏��� [sideenemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "sideenemy.h"
#include "explosion.h"
#include "bullet.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_SIDEENEMY		(4)								// �G�̎��
#define ENEMY_01 "data/TEXTURE/T0000.png"
#define ENEMY_02 "data/TEXTURE/T0001.png"
#define ENEMY_PMAX (30)											//�G�̑傫��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureSIDEEnemy[MAX_TYPE_SIDEENEMY] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSIDEEnemy = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
SideEnemy g_aSIDEEnemy[MAX_SIDEENEMY];										//�G�̏��

//=============================================================================
// ����������
//=============================================================================
void InitSideEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSIDEEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_SIDEENEMY; nCntEnemy++)
	{
		g_aSIDEEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aSIDEEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSIDEEnemy[nCntEnemy].nType = 0;
		g_aSIDEEnemy[nCntEnemy].bUse = false;
		//g_aSIDEEnemy[nCntEnemy].nLife = 1;
		g_aSIDEEnemy[nCntEnemy].nCounterState = 0;
		g_aSIDEEnemy[nCntEnemy].state = SIDEENEMYSTATE_NOMAL;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureSIDEEnemy[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureSIDEEnemy[1]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SIDEENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffSIDEEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntSIDEEnemy = 0; nCntSIDEEnemy < MAX_SIDEENEMY; nCntSIDEEnemy++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�E��
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�E��
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSIDEEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitSideEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_SIDEENEMY; nCntTex++)
	{
		if (g_apTextureSIDEEnemy[nCntTex] != NULL)
		{
			g_apTextureSIDEEnemy[nCntTex]->Release();
			g_apTextureSIDEEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSIDEEnemy != NULL)
	{
		g_pVtxBuffSIDEEnemy->Release();
		g_pVtxBuffSIDEEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSideEnemy(void)
{
	int nCntSideEnemy;

	for (nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++)
	{
		if (g_aSIDEEnemy[nCntSideEnemy].bUse == true)	//�G���g�p����Ă���
		{
			switch (g_aSIDEEnemy[nCntSideEnemy].state)
			{
			case SIDEENEMYSTATE_NOMAL:

				g_aSIDEEnemy[nCntSideEnemy].nCounterState--; //�J�E���g�_�E��

				if (g_aSIDEEnemy[nCntSideEnemy].bUse == true)
				{
					g_aSIDEEnemy[nCntSideEnemy].pos.x += g_aSIDEEnemy[nCntSideEnemy].move.x;
					g_aSIDEEnemy[nCntSideEnemy].pos.y += g_aSIDEEnemy[nCntSideEnemy].move.y;
					// ���_���̍쐬
					VERTEX_2D *pVtx;

					// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);
					//�|�W�V����
					pVtx[nCntSideEnemy * 4].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 1].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 2].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
					pVtx[nCntSideEnemy * 4 + 3].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
					// ���_�o�b�t�@���A�����b�N����
					g_pVtxBuffSIDEEnemy->Unlock();

					//g_aSIDEEnemy[nCntSideEnemy].pos.x + g_aSIDEEnemy[nCntSideEnemy].move.x;
					if (g_aSIDEEnemy[nCntSideEnemy].pos.x <= 0)
					{
						g_aSIDEEnemy[nCntSideEnemy].move.x = 1;
					}
					if (g_aSIDEEnemy[nCntSideEnemy].pos.x >= 1250)
					{
						g_aSIDEEnemy[nCntSideEnemy].move.x = -1;
					}


					if (rand() % 250 == 0)
					{//�U�����x
						SetBullet(g_aSIDEEnemy[nCntSideEnemy].pos, D3DXVECTOR3(0.0f, -4.0f, 0.0f), BULLTETYPE_ENEMY);		//�e��
					}
					break;
				}
			case SIDEENEMYSTATE_DAMAGE:

				g_aSIDEEnemy[nCntSideEnemy].nCounterState--; //�J�E���g�_�E��
				if (g_aSIDEEnemy[nCntSideEnemy].nCounterState <= 0)
				{
					g_aSIDEEnemy[nCntSideEnemy].state = SIDEENEMYSTATE_NOMAL;

					VERTEX_2D*pVtx;								//���_���̃|�C���^
					// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
					g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

					pVtx += (nCntSideEnemy * 4);//���_�|�C���^��4�i�߂�

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//���_�o�b�t�@�A�����b�N����
					g_pVtxBuffSIDEEnemy->Unlock();
				}
				break;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSideEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffSIDEEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_SIDEENEMY; nCntEnemy++)
	{
		if (g_aSIDEEnemy[nCntEnemy].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureSIDEEnemy[g_aSIDEEnemy[nCntEnemy].nType]);
			//�|���S���̕`��
			if (g_aSIDEEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					nCntEnemy * 4,
					2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetSideEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntSideEnemy;
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffSIDEEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntSideEnemy = 0; nCntSideEnemy < MAX_SIDEENEMY; nCntSideEnemy++)
	{
		if (g_aSIDEEnemy[nCntSideEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aSIDEEnemy[nCntSideEnemy].pos = pos;
			g_aSIDEEnemy[nCntSideEnemy].move = D3DXVECTOR3(-1, 0, 0);
			g_aSIDEEnemy[nCntSideEnemy].nType = nType;
			g_aSIDEEnemy[nCntSideEnemy].state = SIDEENEMYSTATE_NOMAL;
			g_aSIDEEnemy[nCntSideEnemy].nCounterState = 0;//�G�̃��C�t�ݒ�
			//g_aSIDEEnemy[nCntSideEnemy].nLife = 100;
			g_aSIDEEnemy[nCntSideEnemy].bUse = true;//�G���g�p����Ă���

			//�|�W�V����
			pVtx[nCntSideEnemy * 4].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 1].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 2].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x - ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);
			pVtx[nCntSideEnemy * 4 + 3].pos = D3DXVECTOR3(g_aSIDEEnemy[nCntSideEnemy].pos.x + ENEMY_PMAX, g_aSIDEEnemy[nCntSideEnemy].pos.y + ENEMY_PMAX, 0.0f);

			break;
		}
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffSIDEEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
SideEnemy *GetSideEnemy(void)
{
	return &g_aSIDEEnemy[0];
}
//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitSideEnemy(int nCntEnemy, int nDamage)
{
		g_aSIDEEnemy[nCntEnemy].nCounterState = 90;		//�_���[�W��Ԏ���
		g_aSIDEEnemy[nCntEnemy].bUse = false;

}
