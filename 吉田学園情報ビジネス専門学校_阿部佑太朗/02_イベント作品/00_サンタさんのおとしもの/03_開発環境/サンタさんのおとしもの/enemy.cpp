//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "enemy.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)								// �G�̎��
#define ENEMY_01 "data/TEXTURE/Player.png"
#define ENEMY_02 "data/TEXTURE/Player0.png"
#define ENEMY_03 "data/TEXTURE/Player.png"
#define ENEMY_04 "data/TEXTURE/Player.png"
#define ENEMY_PMAX (50)											//�G�̑傫��

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

	//g_nCounterGAME++;

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].CountLife = 0;
	}
	g_nNumEnemy = 0;
	
	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ENEMY_01, &g_apTextureEnemy[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, ENEMY_02, &g_apTextureEnemy[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, ENEMY_03, &g_apTextureEnemy[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, ENEMY_04, &g_apTextureEnemy[3]);
	

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
		pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
		pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
		pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);
		pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);
		//RHW
		pVtx[nCntEnemy * 4].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 1].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 2].rhw = 1.0f;
		pVtx[nCntEnemy * 4 + 3].rhw = 1.0f;
		//�J���[
		pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCntEnemy * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

		//pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
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

	VERTEX_2D*pVtx = NULL;

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//VERTEX_2D*pVtx = NULL;//���_���̃|�C���^
		if (g_aEnemy[nCntEnemy].bUse == true)//�G�l�~�[���g�p����Ă��邩 
		{
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			g_aEnemy[nCntEnemy].nCounterAnim++;
			if ((g_aEnemy[nCntEnemy].nCounterAnim % 15) == 0)
			{
				//�p�^�[��No,�X�V
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;//�p�^�[�����������ɖ߂� 
			}

			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 2), 0.0f);					 //�E��
			pVtx[1].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 2) + 0.5f, 0.0f);       //�E��
			pVtx[2].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 2), 1.0f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2(0.5f * (g_aEnemy[nCntEnemy].nPatternAnim % 2) + 0.5f, 1.0f);       //�E��
			
		}
		pVtx += 4;
		
	}
	// ���_�o�b�t�@���A�����b�N����
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
	for(int nCntEnemy = 0; nCntEnemy < MAX_TYPE_ENEMY; nCntEnemy++)
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
void SetEnemy(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYSTATE state)
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
			g_aEnemy[nCntEnemy].state = state;
			g_aEnemy[nCntEnemy].nCounterState = 0;//�G�̃��C�t�ݒ�
			g_aEnemy[nCntEnemy].nLife = 3;
			g_aEnemy[nCntEnemy].bUse = true;//�G���g�p����Ă���
			g_aEnemy[nCntEnemy].nCounterAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			//�|�W�V����
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y - ENEMY_PMAX, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_PMAX, g_aEnemy[nCntEnemy].pos.y + ENEMY_PMAX, 0.0f);

			g_nNumEnemy++;
			break;
		}

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
		g_aEnemy[nCntEnemy].nCounterState = 90;		//�_���[�W��Ԏ���
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		
		
		g_nNumEnemy--;
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 10;		//�_���[�W��Ԏ���

		VERTEX_2D*pVtx;								//���_���̃|�C���^
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy *4);//���_�|�C���^��4�i�߂�
		
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffEnemy->Unlock();
		
	}
	//if (g_nNumEnemy <= 0)
	//{
	//	//SetTBossEnemy(D3DXVECTOR3(1.0f, 1.0f, 1.0f), 1);		//���{�X

	//}
	
	//
	//�U������ENMY���I�ɂȂ�
	//
	/*if ((g_aEnemy[nCntEnemy].nLife <= 0) || (g_aEnemy[nCntEnemy].nType = 0))
	{
		AddScore(g_aEnemy[nCntEnemy].nType + 1);
	}*/
}