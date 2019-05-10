//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���R���
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURENAME	"data\\TEXTURE\\player000.png"		// �e�N�X�`����
#define POLYGON_X			(600)								// �|���S����X���W
#define POLYGON_Y			(200)								// �|���S����Y���W
#define PLAYER_WIDTH		(40)								// �v���C���[�̕�
#define PLAYER_HEIGHT		(40)								// �v���C���[�̍���
#define DAMAGE_TIME			(5)									// �_���[�W��Ԃ̎���
#define PLAYER_LIFE			(5)									// �v���C���[�̃��C�t
#define MAX_PARTTERN		(3)									// �p�^�[���̍ő�
#define POLYGON_COUNT		(8)									// �A�j���[�V�����Ɏg�����l
#define PLAYER_INERTIA		(1.0f)								// �A�j���[�V�����Ɏg�����l
#define UPDATE_ANIM_X		(((1.0f / 3.0f) * g_player.nPatternAnim))	// �ǂݍ��ރe�N�X�`���̃p�^�[��
#define UPDATE_ANIM_Y		((0.5f * g_player.nDirection))		// �ǂݍ��ރe�N�X�`���̃p�^�[��
#define PLAYER_MOVE			(1.0f)								// �v���C���[�̑��x


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;									// �A�j���[�V�����J�E���^�[
int g_nPartternAnim;								// �A�j���[�V�����p�^�[��No.
Player g_player;
ITEMKIND g_bulletkind;

//=============================================================================
// �v���C���[����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �v���C���[�̏��̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fPlayerHeight = 0.0f;
	g_player.fPlayerWidth = 0.0f;
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.nDirection = 1;
	g_player.nItem = NULL;
	g_player.kind = ITEMKIND_NONE;
	g_player.bDis = true;
	g_player.nCounterItem = 0;

	// �|���S�����W�̐ݒ�
	g_player.pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);

	g_nCounterAnim = 0;		// �J�E���^�[������������
	g_nPartternAnim = 0;	// �p�^�[��No.������������

	// �v���C���[�̍����ƕ���ݒ�
	g_player.fPlayerHeight = PLAYER_HEIGHT;	// ����
	g_player.fPlayerWidth = PLAYER_WIDTH;		// ��

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(POLYGON_X - g_player.fPlayerWidth, POLYGON_Y - g_player.fPlayerHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_X + g_player.fPlayerWidth, POLYGON_Y - g_player.fPlayerHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_X - g_player.fPlayerWidth, POLYGON_Y + g_player.fPlayerHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_X + g_player.fPlayerWidth, POLYGON_Y + g_player.fPlayerHeight, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f / 3.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 3.0f, 0.5f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �v���C���[�I������
//=============================================================================
void UninitPlayer(void)
{
	// �e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;
	g_nCounterAnim++;	// �J�E���^�[���Z
	D3DXVECTOR3 SetPos(0.0f, 0.0f, 0.0f);

	// �ړ�
	float fPlayerMove = PLAYER_MOVE;

	g_player.posOld = g_player.pos;

	// �u���b�N�̎擾
	Item *pItem;
	pItem = GetItem();
	
	if (g_player.bDis == true)
	{
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_A) == true)
		{// �������Ɉړ�
			g_player.move.x -= fPlayerMove;

			if (g_player.nDirection != 0)
			{
				g_player.nDirection = 0;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}

			SetEffect(D3DXVECTOR3(g_player.pos.x + 40.0f, g_player.pos.y + 20.0f, g_player.pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 10);
		}

		if (GetKeyboardPress(DIK_D) == true)
		{// �E�����Ɉړ�
			g_player.move.x += fPlayerMove;

			if (g_player.nDirection != 1)
			{
				g_player.nDirection = 1;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
			SetEffect(D3DXVECTOR3(g_player.pos.x - 40.0f, g_player.pos.y + 20.0f, g_player.pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 10);
		}

		if (g_player.move.x >= 0.25f || g_player.move.x <= -0.25f)
		{
			if ((g_player.nCounterAnim % POLYGON_COUNT) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % MAX_PARTTERN;	// �p�^�[��No.���X�V

																					// �e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + UPDATE_ANIM_X, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f) + UPDATE_ANIM_X, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[2].tex = D3DXVECTOR2(0.0f + UPDATE_ANIM_X, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f) + UPDATE_ANIM_X, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
			}
			g_player.nCounterAnim++;	// �J�E���^�[���Z
		}
		else if (g_player.move.x < 0.25f && g_player.move.x > -0.25)
		{
			if ((g_player.nCounterAnim % POLYGON_COUNT) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % MAX_PARTTERN;	// �p�^�[��No.���X�V

				// �e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3.0f), 0.0f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3.0f), 0.5f + UPDATE_ANIM_Y * (g_player.nDirection % 2));
			}
			g_player.nCounterAnim++;	// �J�E���^�[���Z
		}
		
		if (g_player.pos.x > SCREEN_WIDTH + g_player.fPlayerWidth)
		{// �@�̂���ʊO�ɏo����t��
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x < -g_player.fPlayerWidth)
		{// �@�̂���ʊO�ɏo����t��
			g_player.pos.x = SCREEN_WIDTH;
		}
		

		// �ʒu�X�V�i�ړ��j
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		g_player.move.x += (0.0f - g_player.move.x) * 0.15f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

		// ���_���W���X�V
		pVtx[0].pos.x = g_player.pos.x - g_player.fPlayerWidth;	// �����X���W��ݒ�
		pVtx[0].pos.y = g_player.pos.y - g_player.fPlayerHeight;	// �����Y���W��ݒ�
		pVtx[1].pos.x = g_player.pos.x + g_player.fPlayerWidth;	// �E���X���W��ݒ�
		pVtx[1].pos.y = g_player.pos.y - g_player.fPlayerHeight;	// �E���Y���W��ݒ�
		pVtx[2].pos.x = g_player.pos.x - g_player.fPlayerWidth;	// ������X���W��ݒ�
		pVtx[2].pos.y = g_player.pos.y + g_player.fPlayerHeight;	// ������Y���W��ݒ�
		pVtx[3].pos.x = g_player.pos.x + g_player.fPlayerWidth;	// �E����X���W��ݒ�
		pVtx[3].pos.y = g_player.pos.y + g_player.fPlayerHeight;	// �E����Y���W��ݒ�

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();
	}

	// �A�C�e���̓����蔻��
	if (g_player.nCounterItem == 0)
	{
		if (CollisionItem(&g_player.pos, g_player.fPlayerHeight, g_player.fPlayerWidth, &g_player.nItem) == true)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				if (g_player.nItem != NULL)
				{// �A�C�e���̎�ނ̃A�h���X����ł͂Ȃ�
					pItem += *g_player.nItem;  // �A�C�e���̎�ނ̕��|�C���^��i�߂�
				}
				SetExplosion(pItem->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
				pItem->bUse = false;      // �����Ȃ���Ԃɂ���
				g_player.nCounterItem++;
				PlaySound(SOUND_LABEL_SE_GET);
			}
		}
	}

	if (g_player.nCounterItem > 0)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, 7.0f, 0.0f), g_player.nItem);
			PlaySound(SOUND_LABEL_SE_FALL);
			g_player.nCounterItem = 0;
		}
	}
}

//=============================================================================
// �v���C���[�`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();			// �f�o�C�X���擾����

	if (g_player.bDis == true)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
ITEMKIND *GetItemKind(void)
{
	return &g_player.kind;
}