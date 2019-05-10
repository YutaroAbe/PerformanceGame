//=============================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "item.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ITEM		(5)								// �G�̎��item
#define ITEM_01 "data/TEXTURE/coin000.png"
#define ITEM_02 "data/TEXTURE/HP101.png"
#define ITEM_03 "data/TEXTURE/HP101.png"
#define ITEM_04 "data/TEXTURE/item003.png"
#define ITEM_05 "data/TEXTURE/HP101.png"
#define ITEM_PMAX (25)											//�G�̑傫��
#define	MAX_ITEM	(50)	// �G�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Item g_aitem[MAX_ITEM];										//�G�̏��
int g_CoinSe;
int g_NamTime;

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntitem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//g_nCounterGAME++;

	// �G�̏��̏�����
	for(int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		g_aitem[nCntitem].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aitem[nCntitem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aitem[nCntitem].nType = 0;
		g_aitem[nCntitem].fHeight = 0;
		g_aitem[nCntitem].fWindth = 0;
		g_aitem[nCntitem].bUse = false;
		g_aitem[nCntitem].nCounterAnim = 0;
		g_aitem[nCntitem].nPatternAnim = 0;
		g_aitem[nCntitem].nCounterState = 0;
		g_aitem[nCntitem].nNumItem = 0;
		//g_aitem[nCntitem].CountLife = 0;

		g_CoinSe = 0;
	}
	g_NamTime = 0;

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, ITEM_01, &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_02, &g_apTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_03, &g_apTextureItem[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_04, &g_apTextureItem[3]);
	D3DXCreateTextureFromFile(pDevice, ITEM_05, &g_apTextureItem[4]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffItem,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		//�|�W�V����
		pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		/*pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - g_aitem[nCntitem].fAngle- g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, 0.0f);
		pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, g_aitem[nCntitem].pos.y + g_aitem[nCntitem].fAngle+ g_aitem[nCntitem].fLength, 0.0f);
*/
		//RHW
		pVtx[nCntitem * 4].rhw = 1.0f;
		pVtx[nCntitem * 4 + 1].rhw = 1.0f;
		pVtx[nCntitem * 4 + 2].rhw = 1.0f;
		pVtx[nCntitem * 4 + 3].rhw = 1.0f;
		//�J���[
		pVtx[nCntitem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntitem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCntitem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[nCntitem * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[nCntitem * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[nCntitem * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

		//pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{
		if (g_apTextureItem[nCntTex] != NULL)
		{
			g_apTextureItem[nCntTex]->Release();
			g_apTextureItem[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D*pVtx;

	PLAYER *pPlyer;
	pPlyer = GetPlayer();

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		g_aitem[nCntitem].pos.x -= pPlyer->move.x;

		if (g_aitem[nCntitem].bUse == true)//�G�l�~�[���g�p����Ă��邩
		{
			if (g_aitem[nCntitem].nType == 0)
			{
				g_aitem[nCntitem].nCounterAnim++;
				if ((g_aitem[nCntitem].nCounterAnim % 15) == 0)
				{
					//�p�^�[��No,�X�V
					g_aitem[nCntitem].nPatternAnim = (g_aitem[nCntitem].nPatternAnim + 1) % 4;				//�p�^�[�����������ɖ߂�
				}
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4), 0.0f);				 //�E��
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4), 1.0f);				 //�E��
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aitem[nCntitem].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��
			}

			pVtx[0].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		if (g_aitem[nCntitem].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureItem[g_aitem[nCntitem].nType]);
			//�|���S���̕`��
			if (g_aitem[nCntitem].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntitem * 4,2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetItem(int nType,D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	int nCntitem;
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++)
	{
		if (g_aitem[nCntitem].bUse == false)		//�G���g�p����Ă��Ȃ�
		{
			g_aitem[nCntitem].pos = pos;
			g_aitem[nCntitem].nType = nType;
			g_aitem[nCntitem].move = move;
			g_aitem[nCntitem].fHeight = 0;
			g_aitem[nCntitem].fWindth = 0;
			g_aitem[nCntitem].bUse = true;			//�G���g�p����Ă���
			g_aitem[nCntitem].nCounterAnim = 0;
			g_aitem[nCntitem].nPatternAnim = 0;

			//�|�W�V����
			pVtx[nCntitem * 4].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 1].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y - ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 2].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x - ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			pVtx[nCntitem * 4 + 3].pos = D3DXVECTOR3(g_aitem[nCntitem].pos.x + ITEM_PMAX, g_aitem[nCntitem].pos.y + ITEM_PMAX, 0.0f);
			break;
		}

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// �G�̎擾
//=============================================================================
Item *Getitem(void)
{
	return &g_aitem[0];
}
//=============================================================================
//�v���C���[�ƃA�C�e���̔��菈��
//=============================================================================
void CollisionItem(D3DXVECTOR3 *pPos, float *fWindth, float *fHeight)
{
	for (int nCntitem = 0; nCntitem < MAX_ITEM; nCntitem++, g_NamTime++)
	{
		if (g_aitem[nCntitem].bUse == true)
		{
			g_NamTime--;
			if (pPos->x - *fWindth <= g_aitem[nCntitem].pos.x &&
				pPos->x + *fWindth  >= g_aitem[nCntitem].pos.x &&
				pPos->y - *fHeight <= g_aitem[nCntitem].pos.y &&
				pPos->y  >= g_aitem[nCntitem].pos.y)
			{//�A�C�e���̔���

					g_aitem[nCntitem].bUse = false;					//�v���C���[���A�C�e���ɓ������������
					if (g_aitem[nCntitem].bUse == false)
					{
						if (g_aitem[nCntitem].nType == 0)
						{

							switch (rand() % 4)
							{											//���ʉ�
							case 0:
								PlaySound(SOUND_LABEL_SE_COIN000);
								break;
							case 1:
								PlaySound(SOUND_LABEL_SE_COIN001);
								break;
							case 2:
								PlaySound(SOUND_LABEL_SE_COIN002);
								break;
							case 3:
								PlaySound(SOUND_LABEL_SE_COIN003);
								break;
							}
							g_CoinSe += 1;
							if ((g_CoinSe >= 4))
							{
								g_CoinSe = 0;
							}
							//�R�C���̃|�C���g
							AddScore(100);								//�X�R�A���Z
						//	SetExplosion(g_aitem[nCntitem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);
							if (g_NamTime <= 0)
							{
								AddScore(10000);								//�X�R�A���Z
							}
						}

						if (g_aitem[nCntitem].nType == 4)
						{
							PLAYER *pPlyer;
							pPlyer = GetPlayer();
							if (pPlyer->nLife <= 9)
							{
								PlaySound(SOUND_LABEL_SE_KAIHUKU);
								pPlyer->nLife = 10;
							}
						}
						if (g_aitem[nCntitem].nType == 2)
						{
							PLAYER *pPlyer;
							pPlyer = GetPlayer();
							if (pPlyer->nLife <= 9)
							{
								PlaySound(SOUND_LABEL_SE_KAIHUKU);
								pPlyer->nLife += 1;
							}
						}
				}
			}
		}
	}
}