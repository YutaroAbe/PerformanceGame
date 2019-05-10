//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "enemy.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "block.h"
#include "trap.h"
#include "sound.h"
#include "fade.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(5)								// �G�̎��
#define ENEMY_01 "data/TEXTURE/.png"
#define ENEMY_02 "data/TEXTURE/enemy001.png"
#define ENEMY_03 "data/TEXTURE/enemy002.png"
#define ENEMY_04 "data/TEXTURE/enemy003.png"
#define ENEMY_05 "data/TEXTURE/enemy004.png"

#define ENEMY_PMAX (25)											//�G�̑傫��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].fHeight = 0;
		g_aEnemy[nCntEnemy].fWindth = 0;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterMove = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
	}
	g_nNumEnemy = 0;
	
	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_03, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_04, &g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_05, &g_apTextureEnemy[4]);
	

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
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

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	
	VERTEX_2D*pVtx;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�A�j���[�V����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G�l�~�[���g�p����Ă��邩 
		{
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;		//�O��̈ʒu��ۑ�
			g_aEnemy[nCntEnemy].pos.x -= pPlayer->move.x;
			g_aEnemy[nCntEnemy].nCounterAnim++;
			g_aEnemy[nCntEnemy].nCounterMove++;
			if (g_aEnemy[nCntEnemy].nType == 1)
			{//�i�C�g1
				if (g_aEnemy[nCntEnemy].nCounterMove % 60 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= -1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 2)
			{//�i�C�g2
				if (g_aEnemy[nCntEnemy].nCounterMove % 155 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 80 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -20.0f;
					g_aEnemy[nCntEnemy].move.x = -5.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 160 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= -1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 3)
			{//�i�C�g3
				if (g_aEnemy[nCntEnemy].nCounterMove % 190 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -5.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -5.0f;
					g_aEnemy[nCntEnemy].move.x = 6.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 90 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 150 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -15.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 4)
			{//�i�C�g3
				if (g_aEnemy[nCntEnemy].nCounterMove % 140 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -2.0f;
					g_aEnemy[nCntEnemy].move.x = -4.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 170 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -3.0f;
					g_aEnemy[nCntEnemy].move.x = 6.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 120 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].nCounterMove % 190 == 0)
				{
					g_aEnemy[nCntEnemy].move.y = -11.0f;
					g_aEnemy[nCntEnemy].move.x = -2.0f;
				}

				if (g_aEnemy[nCntEnemy].nCounterMove % 170 == 0)
				{
					g_aEnemy[nCntEnemy].move.x *= 1.0f;
				}
			}
			if ((g_aEnemy[nCntEnemy].nCounterAnim % 15) == 0)
			{
				//�p�^�[��No,�X�V
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;//�p�^�[�����������ɖ߂� 
			}

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.0f);					 //�E��
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //�E��

			if (g_aEnemy[nCntEnemy].move.x >= 0.5)
			{
					//�e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.0f);					 //�E��
					pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
					pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);				 //�E��
					pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //�E��
			}
			else if (g_aEnemy[nCntEnemy].move.x <= -0.5)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 0.5f);					 //�E��
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 0.5f);       //�E��
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4), 1.0f);				 //�E��
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aEnemy[nCntEnemy].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��
			}

		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
	
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		
		if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p����Ă���
		{
			g_aEnemy[nCntEnemy].move.y += 0.75;				//�d��
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				g_aEnemy[nCntEnemy].nCounterState--; //�J�E���g�_
				break;
			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEnemy].nCounterState--; //�J�E���g�_�E��

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);//���_�|�C���^��4�i�߂�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					// ���_�o�b�t�@���A�����b�N����
					g_pVtxBuffEnemy->Unlock();
					break;
				}
			}
		}
		
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//CollisionTrap(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].fWindth, &g_aEnemy[nCntEnemy].fHeight); //�u���b�N�Ƃ̔��菈��

		if (g_aEnemy[nCntEnemy].bUse == true)//�G�l�~�[���g�p����Ă��邩 
		{

			CollisionBlockEnemy(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, &g_aEnemy[nCntEnemy].fWindth, &g_aEnemy[nCntEnemy].fHeight);

			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//�|���S���̕`��
			if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEnemy * 4,2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWindth, float fHeight,int nLife )
{
	int nCntEnemy;
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = nLife;//�G�̃��C�t�ݒ�
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].fWindth = fWindth;
			g_aEnemy[nCntEnemy].bUse = true;//�G���g�p����Ă���
			g_aEnemy[nCntEnemy].nCounterAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth, g_aEnemy[nCntEnemy].pos.y + 0, 0.0f);
			
			break;
			g_nNumEnemy++;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//���C�t��0�ɂȂ����ꍇ
		if (g_aEnemy[nCntEnemy].nType == 1)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
		}
		if (g_aEnemy[nCntEnemy].nType == 2)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

		}
		if (g_aEnemy[nCntEnemy].nType == 3)
		{
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);

		}
		g_aEnemy[nCntEnemy].nCounterState = 90;		//�_���[�W��Ԏ���
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		if (g_aEnemy[nCntEnemy].nType == 1 || g_aEnemy[nCntEnemy].nType == 2 || g_aEnemy[nCntEnemy].nType == 4)
		{
			AddScore(100);
		}
		if (g_aEnemy[nCntEnemy].nType == 3)
		{
			AddScore(500);
		}
		g_nNumEnemy--;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 10;		//�_���[�W��Ԏ���

		VERTEX_2D*pVtx;								//���_���̃|�C���^
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);//���_�|�C���^��4�i�߂�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffEnemy->Unlock();
		
	}
}
//=============================================================================
//�v���C���[�ƃG�l�~�[�̔��菈��
//=============================================================================
void CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWindth, float *fHeight)
{
	for (int nCntEnemy = 0; nCntEnemy< MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (pPos->x + (*fWindth / 2) >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth &&									//�v���C���[���E����߂荞��ł�Ƃ�
				pPos->x - (*fWindth / 2) <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth &&		//�v���C���[��������߂荞��ł�Ƃ�
				pPos->y <= g_aEnemy[nCntEnemy].pos.y &&															//�v���C���[���ォ�牺�ɂ߂荞��ł�Ƃ�
				pPos->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)					//�v���C���[���������ɂ߂荞��ł�Ƃ�
			{//YX���͈͓�
				if (pPosOld->y - *fHeight <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight &&
					pPos->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)
				{//�G�㔻��	
					PlaySound(SOUND_LABEL_SE_ENEMY0);
					pPos->y = g_aEnemy[nCntEnemy].pos.y - (g_aEnemy[nCntEnemy].fHeight * 2);
					pMove->y = -8.0f;
					HitEnemy(nCntEnemy, 1);
				}
				else if (pPosOld->y - *fHeight >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight &&	//�v���C���[�̒��S�𓪂ɂ��Ă��̒��S�̐̂̈ʒu�͉��ɂ�����
					        pPos->y - *fHeight <= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight)				//���݂̈ʒu���߂荞��ł�Ƃ�
				{//	�G������
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					pPos->y = g_aEnemy[nCntEnemy].pos.y;
					HitPlayer(1);
				}
				else if (pPosOld->x + *fWindth >= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth &&	//�̂̈ʒu���u���b�N���E�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
						    pPos->x - *fWindth <= g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth)
				{//�u���b�N�E����
				 
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					HitPlayer(1);
					pPos->x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWindth;
					pMove->x = 20.0f;
					pMove->y = -10.0f;
					
				}
				else if (pPosOld->x - *fWindth <= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth&&									//�̂̈ʒu���u���b�N��荶�ɂ����Č��݂̈ʒu���߂荞��ł�ꍇ
					         pPos->x + *fWindth >= g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth)
				{//�u���b�N������
				 //bLand = true;
					PlaySound(SOUND_LABEL_SE_ENEMY1);
					HitPlayer(1);
					pPos->x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fWindth;
					pMove->x = -20.0f;
					pMove->y = - 10.0f;
				}
			}
		}
	}
}
