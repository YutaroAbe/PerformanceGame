//=============================================================================
//
// DirectX���^���� [player.cpp]
// Author : ABE YUUTAROU
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "switch.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "enemy.h"
#include "tutorial.h"
#include "trap.h"
#include "explosion.h"
#include "game2.h"
//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define PLAYER_TEXTURENAMRE "data/TEXTURE/PPP.png" //�ǂݍ��ރe�N�X�`��
#define POS_X (25)								//�|�W�V����_X
#define POS_Y (50)								//�|�W�V����_Y

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //���_�o�b�t�@�̃|�C���g
D3DXVECTOR3 g_posPlayer;							//�|���S���̈ʒu
D3DXVECTOR3 g_movePlayer;							//�|���S���̈ړ���
PLAYER g_aPlayer;
int g_posCounter;

//=============================================================================
//�����������|���S��
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	g_posCounter = 0;
	g_aPlayer.nCounterAnim = 0;
	g_aPlayer.nPatternAnim = 0;
	g_aPlayer.nCounterState = 0;
	g_aPlayer.fHeight = POS_Y;
	g_aPlayer.fWindth = POS_X;
	g_aPlayer.state = PLAYERSTATE_NOMAL;
	g_aPlayer.nLife = 10;
	g_aPlayer.bDisp = true;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAMRE, &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx,0);

	//�|���S���ʒu�A�ړ�
	g_aPlayer.pos = D3DXVECTOR3(600, 600, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0, 0, 0.0f);

	//���_���W�ݒ�
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//����
	pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//�E��
	pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//����
	pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//�E��
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);			//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);			//����
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);			//�E��
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//�I�������X�V�����|���S��
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=============================================================================
//�X�V�����|���S��
//=============================================================================
void UpdatePlayer(void)
{
	if (g_aPlayer.bDisp == false)
	{
		g_aPlayer.move.x = 0;
		g_aPlayer.move.y = 0;
	}
	g_aPlayer.posOld = g_aPlayer.pos;		//�O��̈ʒu��ۑ�
	Block *g_aBlock;
	g_aBlock = Getblock();

	VERTEX_2D*pVtx;

	switch (g_aPlayer.state)
	{
	case PLAYERSTATE_NOMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		PlaySound(SOUND_LABEL_SE_ENEMY0);
		g_aPlayer.nCounterState--;	//�J�E���g�_�E��
		if (g_aPlayer.nCounterState <= 0)
		{
			g_aPlayer.state = PLAYERSTATE_NOMAL;

			VERTEX_2D*pVtx;								//���_���̃|�C���^

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		break;

	case PLAYERSTATE_DEATH:
		g_aPlayer.nCounterState--;	//�J�E���g�_�E��
		if (g_aPlayer.nCounterState <= 0)
		{
			SetGemeState(GAMESTATE_END);
			SetGemeState2(GAME2STATE_END);
			SetTutoState(TUTOSTATE_END);
			g_aPlayer.state = PLAYERSTATE_END;
		}
		return;
		break;

	case PLAYERSTATE_END:
		break;
	}

	if (g_aPlayer.bDisp == true)
	{
		if (g_aPlayer.pos.x = 600)
		{
			g_aPlayer.pos.x = 600;
		}
		if (g_aPlayer.pos.y <= 70)
		{
			HitPlayer(10);
		}
		if (g_aPlayer.pos.y >= 800)
		{
			HitPlayer(10);
		}
		//�C�ӂ̃L�[(A�L�[)�������ꂽ���ǂ��� :���ړ�
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_aPlayer.move.x += sinf(-D3DX_PI * 0.5) *2.25f;

		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//�C�ӂ̃L�[(D�L�[)�������ꂽ���ǂ����@�F�E�ړ�
			g_aPlayer.move.x += sinf(D3DX_PI * 0.5) *2.25f;
		}
		else
		{
			g_aPlayer.nPatternAnim = 0;
		}

		if (g_aPlayer.move.x <= -0.01f)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.DirectMove = 1;
			if (g_aPlayer.move.y <= -0.01f)
			{//�E�W�����v��
				g_aPlayer.DirectMove = 4;

			}
		}
		else if (g_aPlayer.move.x >= 0.01f)
		{
			g_aPlayer.nPatternAnim++;
			g_aPlayer.DirectMove = 0;
			if (g_aPlayer.move.y <= -0.01f)
			{//���W�����v��
				g_aPlayer.DirectMove = 3;
			}
		}
		switch (g_aPlayer.DirectMove)	//�v���C���[�e�N�X�`���؂�ւ�
		{
		case 0:			//�������ĕ����Ă���
			g_aPlayer.nCounterAnim++;
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			if ((g_aPlayer.nCounterAnim % 5) == 0)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.0f);					//����
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.0f);			//�E��
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.5f);					//����
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.5f);			//�E��
			}
			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
			break;
		case 1:			//�E�����ĕ����Ă���
			g_aPlayer.nCounterAnim++;
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			if ((g_aPlayer.nCounterAnim % 5) == 0)
			{
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 0.5f);					//����
				pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 0.5f);			//�E��
				pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4), 1.0f);					//����
				pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aPlayer.nPatternAnim % 4) + 0.25f, 1.0f);			//�E��
			}
			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
			break;
		case 3:			//����
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);			//����
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);			//�E��
			pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);			//����
			pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);			//�E��
			g_aPlayer.DirectMove = 0;
			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
			break;
		case 4:			//�E��
				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);			//����
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);			//�E��
			pVtx[2].tex = D3DXVECTOR2(0.25f, 1.0f);			//����
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);			//�E��
			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
			g_aPlayer.DirectMove = 1;
			break;
		}
		g_aPlayer.move.y += 0.75;				//�d��

		g_aPlayer.pos.x += g_aPlayer.move.x;	//���ړ�
		g_aPlayer.pos.y += g_aPlayer.move.y;	//����

		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x)*0.425f;
		//g_aPlayer.move.y += (0.0f - g_aPlayer.move.y)*0.625f;

		if (CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight) == true)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				g_aPlayer.move.y -= 15;			 //�W�����v��
			}
		}

		CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionItem(&g_aPlayer.pos, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionSwitch(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight);
		CollisionTrap(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move, &g_aPlayer.fWindth, &g_aPlayer.fHeight); //�u���b�N�Ƃ̔��菈��


		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//����
		pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//����
		pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//�E��
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}

}
//=============================================================================
//�`�揈���|���S��
//=============================================================================pp
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer,0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�F�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);
	if (g_aPlayer.bDisp == true)
	{
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=============================================================================
//�v���C���[�ݒ�
//=============================================================================
void SetPlayer(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPlayer.bDisp == false)				//�v���C���[���g�p����Ă��Ȃ�
	{
		g_aPlayer.pos = pos;					//�ʒu
		g_aPlayer.state = PLAYERSTATE_NOMAL;
		g_aPlayer.nType = nType;				//�^�C�v
		g_aPlayer.nCounterState = 0;			//�v���C���[�̃��C�t�ݒ�
		g_aPlayer.nLife = 10;					//�̗�
		g_aPlayer.bDisp = true;					//�v���C���[���g�p����Ă���

		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//����
		pVtx[1].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y - POS_Y, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aPlayer.pos.x - POS_X, g_aPlayer.pos.y + 0, 0.0f);//����
		pVtx[3].pos = D3DXVECTOR3(g_aPlayer.pos.x + POS_X, g_aPlayer.pos.y + 0, 0.0f);//�E��

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	//int nCount;
	g_aPlayer.nLife -= nDamage;

	if (g_aPlayer.nLife <= 0)
	{//�v���C���[�̗̑͂�0�ȉ��ɂȂ����Ƃ�
		SetExplosion(g_aPlayer.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		g_aPlayer.state = PLAYERSTATE_DEATH;
		g_aPlayer.nCounterState = 60;				//�_���[�W��Ԏ���
		g_aPlayer.bDisp = false;
	}
	else
	{
		g_aPlayer.state = PLAYERSTATE_DAMAGE;
		g_aPlayer.nCounterState = 15;				//�_���[�W��Ԏ���

		VERTEX_2D*pVtx;								//���_���̃|�C���^
		// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}
//=============================================================================
//
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_aPlayer;
}



