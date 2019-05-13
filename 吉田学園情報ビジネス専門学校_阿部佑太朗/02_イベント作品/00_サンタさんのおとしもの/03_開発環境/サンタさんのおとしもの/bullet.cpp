//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author :���R���
//
//=============================================================================
#include "bullet.h"
//#include "explosion.h"
//#include "enemy.h"
#include "player.h"
//#include "effect.h"
#include "sound.h"
//#include "boss.h"
//#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET			(2048)								// �e�̍ő吔
#define POLYGON_X			(1200)								// �|���S����X���W
#define POLYGON_Y			(350)								// �|���S����Y���W
#define BULLET_TEXTURENAME	"data\\TEXTURE\\bullet000.png"		// �e�N�X�`����
#define BULLET_SIZE			(30)									// �e�̑傫��
#define BULLET_HIT			(25)								// �ʏ�̓G�̓����蔻��
#define BULLET_HIT_BOSS		(100)								// �{�X�̓����蔻��
#define PLAYER_HIT			(15)								// �v���C���[�̓����蔻��
#define MAX_TYPE_BULLET		(2)									// �ǂݍ��ރe�N�X�`���̐�
#define ITEM0_TEXTURE_NAME	"data\\TEXTURE\\present_boy.png"				// �ǂݍ��ރe�N�X�`����
#define ITEM1_TEXTURE_NAME	"data\\TEXTURE\\present_girl.png"			// �ǂݍ��ރe�N�X�`����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �e�̈ʒu
	D3DXVECTOR3 move;		// �e�̈ړ�
	D3DXCOLOR col;			// �e�̐F
	ITEMTYPE itemtype;		// �A�C�e���̎��
	float fBulletHeight;	// ����
	float fBulletWidth;		// ��
	int nLife;				// �e�̃��C�t
	bool bUse;
} Bullet;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBullet[MAX_TYPE_BULLET] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						// �g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �|���S�����W�̐ݒ�
	g_aBullet[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].itemtype = ITEMTYPE_COIN;
		g_aBullet[nCntBullet].fBulletHeight = BULLET_SIZE + 15.0f;
		g_aBullet[nCntBullet].fBulletWidth = BULLET_SIZE;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nLife = 200;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ITEM0_TEXTURE_NAME, &g_apTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM1_TEXTURE_NAME, &g_apTextureBullet[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,	// �m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet,
								NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_BULLET; nCntTex++)
	{
		if (g_apTextureBullet[nCntTex] != NULL)
		{
			g_apTextureBullet[nCntTex]->Release();
			g_apTextureBullet[nCntTex] = NULL;
		}
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
	int nCntBullet;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	// �e���g�p����Ă���
		{
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (4 * nCntBullet);	// �Y���̈ʒu�܂Ői�߂�

			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffBullet->Unlock();

			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;	// �g�p���Ă��Ȃ���Ԃɂ���
			}

			

			// ��莞�Ԍo��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				// �����̐ݒ�
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT && g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH && g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			// �G�t�F�N�g�̐ݒ�
			//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0, 1.0f, 1.0f, 0.5f), 15.0f, 10);
			
			
			Player *pPlayer;

			// �v���C���[�̎擾
			pPlayer = GetPlayer();

			if (pPlayer->bDis == true)
			{// �v���C���[���g�p����Ă���
					

				// ��莞�Ԍo��
				g_aBullet[nCntBullet].nLife--;
				if (g_aBullet[nCntBullet].nLife <= 0)
				{
					// �����̐ݒ�
					//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					g_aBullet[nCntBullet].bUse = false;
				}
			}
			// �G�t�F�N�g�̐ݒ�
			//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0, 0.0f, 0.0f, 0.5f), 15.0f, 10);
			
		}
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

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	// �e���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBullet[g_aBullet[nCntBullet].itemtype]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntBullet,
									2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, ITEMTYPE *itemtype)
{
	int nCntBullet;
	//float fDiffAngle;	// ����
	//float fDestAngle;	// �ړI�̊p�x
	//float fMoveAngle;	// ���݂̊p�x
	Player *pPlayer;

	// �v���C���[�̎擾
	pPlayer = GetPlayer();
	// �G�̎擾

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			
			g_aBullet[nCntBullet].pos = pos;

			VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBullet * 4);	// �Y���̈ʒu�܂Ői�߂�

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth, g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffBullet->Unlock();

			g_aBullet[nCntBullet].itemtype = *itemtype;   // �A�C�e���̎�ނ̃A�h���X������

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;	// �g�p���Ă�����
			g_aBullet[nCntBullet].nLife = 300;	// �g�p���Ă�����
			break;
		}
	}
}

//=============================================================================
// �e�̓����蔻��
//=============================================================================
bool CollisionBullet(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **itemtype)
{
	int nCntBullet;

	bool bBullet = false;

	// �v���C���[�̎擾
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// �v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (pPos->x + fWidth > g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth && pPos->y - fHeight < g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight
				&& pPos->x - fWidth < g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth && pPos->y > g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight)
			{
				//PlaySound(SOUND_LABEL_SE_COIN);
				//SetExplosion(g_aItem[nCntItem].pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				//AddScore(15000);				// �X�R�A���Z
				g_aBullet[nCntBullet].bUse = false;
				*itemtype = &g_aBullet[nCntBullet].itemtype;
				bBullet = true;
				//*nItem = &g_aItem[nCntItem].itemtype;   // �A�C�e���̎�ނ̃A�h���X������
			}
		}
		/*if (g_aItem[nCntItem].bUse == false)
		{
		nItem++;

		if (nItem == MAX_ITEM)
		{
		GAMESTATE GameState;
		GameState = GetGameState();

		if (GameState != GAMESTATE_CLEAR && GameState != GAMESTATE_FAILD)
		{
		SetGameState(GAMESTATE_CLEAR);
		*TimeStop = true;
		}
		}
		}*/
	}
	return bBullet;
}
//=============================================================================
// �e�̓����蔻��
//=============================================================================
bool CollisionBullet2(D3DXVECTOR3 *pPos, float fHeight, float fWidth ,int **nIdxBullet)
{
	int nCntBullet;

	bool bBullet = false;

	// �v���C���[�̎擾
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// �v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (pPos->x + fWidth > g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].fBulletWidth && pPos->y - fHeight < g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight
				&& pPos->x - fWidth < g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].fBulletWidth && pPos->y > g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].fBulletHeight)
			{
				//PlaySound(SOUND_LABEL_SE_COIN);
				//SetExplosion(g_aItem[nCntItem].pos, D3DXVECTOR3(0.0f, -3.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				//AddScore(15000);				// �X�R�A���Z
				g_aBullet[nCntBullet].bUse = false;
				*nIdxBullet = &nCntBullet;
				bBullet = true;
				//*nItem = &g_aItem[nCntItem].itemtype;   // �A�C�e���̎�ނ̃A�h���X������
			}
		}
		/*if (g_aItem[nCntItem].bUse == false)
		{
		nItem++;

		if (nItem == MAX_ITEM)
		{
		GAMESTATE GameState;
		GameState = GetGameState();

		if (GameState != GAMESTATE_CLEAR && GameState != GAMESTATE_FAILD)
		{
		SetGameState(GAMESTATE_CLEAR);
		*TimeStop = true;
		}
		}
		}*/
	}
	return bBullet;
}
//=============================================================================
// �e��������
//=============================================================================
void DeleteBullet(int nIdxBullet)
{
	g_aBullet[nIdxBullet].bUse = false;
}