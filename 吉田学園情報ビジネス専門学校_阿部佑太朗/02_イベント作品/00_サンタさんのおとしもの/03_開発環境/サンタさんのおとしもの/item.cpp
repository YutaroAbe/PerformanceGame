//=============================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author :���R���
//
//=============================================================================
#include "item.h"
#include "game.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEM0_TEXTURE_NAME	"data\\TEXTURE\\present_boy.png"		// �ǂݍ��ރe�N�X�`����
#define ITEM1_TEXTURE_NAME	"data\\TEXTURE\\present_girl.png"  // �ǂݍ��ރe�N�X�`����
#define ITEM_SIZE_WIDTH		(35.0f)						    // �ǂݍ��ރe�N�X�`���̕��̑傫��
#define ITEM_SIZE_HEIGHT	(45.0f)							// �ǂݍ��ރe�N�X�`���̏c�̑傫��
#define ITEM_HIT			(8)								// �A�C�e���Ƃ̓����蔻��
#define ITEM_HIT1			(5)								// �A�C�e���Ƃ̓����蔻��
#define MAX_TYPE_ITEM		(2)								// �A�C�e���̎��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Item					g_aItem[MAX_ITEM];		// �g�p���Ă��邩�ǂ���
int g_nCntItemTimer;

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].itemtype = ITEMTYPE_COIN;
		g_aItem[nCntItem].fItemHeight = 0.0f;
		g_aItem[nCntItem].fItemWidth = 0.0f;
		g_aItem[nCntItem].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ITEM0_TEXTURE_NAME, &g_apTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM1_TEXTURE_NAME, &g_apTextureItem[1]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,												// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);

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
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
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
	int nCntItem;

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].nCounterAnim++;
			if (g_aItem[nCntItem].bUse == true)	// �A�C�e�����g�p����Ă���
			{
				// �e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			if (g_aItem[nCntItem].bUse == false)// �A�C�e�����g�p����Ă��Ȃ�
			{
				g_nCntItemTimer++;

				if (g_nCntItemTimer >= 80)
				{
					g_aItem[nCntItem].bUse = true;
					g_nCntItemTimer = 0;
				}
			}
		pVtx += 4;	// �Y���̈ʒu�܂Ői�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)	// �A�C�e�����g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].itemtype]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntItem,
				2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ菈��
//=============================================================================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE itemtype)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntItem * 4);	// �Y���̈ʒu�܂Ői�߂�

			g_aItem[nCntItem].itemtype = itemtype;

			switch (itemtype)
			{
			case ITEMTYPE_COIN:
				g_aItem[nCntItem].fItemHeight = ITEM_SIZE_HEIGHT;
				g_aItem[nCntItem].fItemWidth = ITEM_SIZE_WIDTH;
				break;

			case ITEMTYPE_MIKIYA:
				g_aItem[nCntItem].fItemHeight = ITEM_SIZE_HEIGHT;
				g_aItem[nCntItem].fItemWidth = ITEM_SIZE_WIDTH;
				break;
			}

			g_aItem[nCntItem].pos = pos;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fItemHeight, 0.0f);
			g_aItem[nCntItem].nPatternAnim = 0;

			// �e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�o�b�t�@���A�����b�N
			g_pVtxBuffItem->Unlock();

			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].bUse = true;	// �g�p���Ă�����
			break;
		}
	}
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// �A�C�e���̓����蔻��̏���
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, float fHeight, float fWidth, ITEMTYPE **nItem)
{
	int nCntItem;

	bool bItem = false;

	// �v���C���[�̎擾
	ITEMKIND *pItemKind;
	pItemKind = GetItemKind();

	// �v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPos->x + fWidth > g_aItem[nCntItem].pos.x - g_aItem[nCntItem].fItemWidth
				&& pPos->x - fWidth < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fItemWidth)
			{
				bItem = true;
				*nItem = &g_aItem[nCntItem].itemtype;   // �A�C�e���̎�ނ̃A�h���X������
			}
		}
	}
	return bItem;
}