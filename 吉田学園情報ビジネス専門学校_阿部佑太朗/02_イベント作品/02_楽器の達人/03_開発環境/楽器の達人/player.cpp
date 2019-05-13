//=============================================================================
//
// �v���C���[�̏��� [Player.cpp]
// Author : YUUTAROU ABE
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "bullet.h"
#include "fade.h"
#include "effect.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define NCUT_ANIM_TIME (15)							//�J�E���g�A�j���[�V��������
#define NPAR_ANIM_TAIM (10)							//�A�j���[�V�����p�^�[��
#define POS_X (40)									//�|�W�V����_X
#define POS_Y (70)									//�|�W�V����_X
#define POLYGON_TEXTURENAMRE "data/TEXTURE/player000.png"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //���_�o�b�t�@�̃|�C���g

Player g_Player;
float g_Spin;
int g_nPosState;
int g_nTexAnimState;
int nBulletType;
//=============================================================================
//�����������v���C���[
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();
	g_Player.nCounterAnim = 0;
	g_nTexAnimState = 0;
	g_Player.nPatternAnim = 0;
	//�e��_�ϐ�������
	g_Player.pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	//g_Player.bUse = true;
	g_Player.nCounterState = 0;
	g_Player.nLife = 10;
	g_Player.bDisp = true;
	g_Player.state = PLAYERSTATE_NOMAL;
	g_nPosState = 1;
	nBulletType = 0;

	//�e�N�X�`���ǂݍ��݉E
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAMRE, &g_pTexturePlayer);

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
	g_Player.pos = D3DXVECTOR3(200, 365, 0.0f);
	g_Player.move = D3DXVECTOR3(0,0,0.0f);

	//���_���W�ݒ�
	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//�E��
	//RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);			  //����
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);			  //�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);			  //����
	pVtx[3].tex = D3DXVECTOR2(0.125f, 0.5f);			  //�E��
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//�I�������X�V�����v���C���[
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
//�X�V�����v���C���[
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx = 0;								//���_���̃|�C���^

	if (GetKeyboardTrigger(DIK_W) == true)
	{//��ړ��x����

		g_nPosState -= 1;
	}
	else if (GetKeyboardTrigger(DIK_S) == true)
	{//���ړ��x������
		g_nPosState += 1;
	}
	switch (g_nPosState)
	{
	case 0:
		g_Player.pos.y = 260;
		break;
	case 1:
		g_Player.pos.y = 450;
		break;
	case 2:
		g_Player.pos.y = 640;
		break;
	}

	if (g_nPosState >= 2)
	{
		g_nPosState = 2;
	}
	else if (g_nPosState <= 0)
	{
		g_nPosState = 0;
	}


	if (GetKeyboardTrigger(DIK_I) == true)
	{//�X�y�[�X�������ꍇ�̏���

		g_nTexAnimState = 1;
	}
	else if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_nTexAnimState = 2;
	}
	else
	{
		nBulletType = 0;
	}
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	switch (g_nTexAnimState)
	{
	case 0:
		break;
	case 1:
		g_Player.nCounterAnim++;
		if ((g_Player.nCounterAnim % 2) == 0)
		{
			//�p�^�[��No,�X�V
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 6;//�p�^�[�����������ɖ߂�

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((1.0f/6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.0f);				 //�E��
			pVtx[1].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.0f);				 //�E��
			pVtx[2].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.5f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.5f);				//�E��
			if (g_Player.nPatternAnim <= 0)
			{
				g_nTexAnimState = 0;

			}
			else if (g_Player.nPatternAnim <= 3)
			{
				nBulletType = 1;
			}
		}
		break;
	case 2:
		g_Player.nCounterAnim++;
		if ((g_Player.nCounterAnim % 2) == 0)
		{
			//�p�^�[��No,�X�V
			g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 6;//�p�^�[�����������ɖ߂�

																	//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 0.5f);				 //�E��
			pVtx[1].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 0.5f);				 //�E��
			pVtx[2].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + 0.0f, 1.0f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2((1.0f / 6) * (g_Player.nPatternAnim % 6) + (1.0f / 6), 1.0f);				//�E��
			if (g_Player.nPatternAnim <= 0)
			{
				g_nTexAnimState = 0;

			}
			else if (g_Player.nPatternAnim <= 3)
			{
				nBulletType = 2;
			}
		}
		break;
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	switch (nBulletType)
	{
	case 0 :
		break;
	case 1:
		SetBullet(g_Player.pos + D3DXVECTOR3(30, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_000);			//�e��
		break;
	case 2:
		SetBullet(g_Player.pos + D3DXVECTOR3(30, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BULLETTYPE_001);			//�e��
		break;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�|�W�V����
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//�E��

	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}
//=============================================================================
//�`�揈���v���C���[
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�擾
		pDevice = GetDevice();
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
		//���_�t�H�[�}�b�g�ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		//�e�F�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);
		if (g_Player.bDisp == true)
		{
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}

}
//=============================================================================
// �v���C���[�̐ݒ�
//=============================================================================
void SetPlayer(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Player.bDisp == false)			//�v���C���[���g�p����Ă��Ȃ�
	{
		g_Player.pos = pos;					//�ʒu
		g_Player.state = PLAYERSTATE_NOMAL;
		g_Player.nType = nType;				//�^�C�v
		g_Player.nCounterState = 0;			//�v���C���[�̃��C�t�ݒ�
		g_Player.nLife = 10;				//�̗�
		g_Player.bDisp = true;				//�v���C���[���g�p����Ă���
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//����
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//�E��
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//����
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//�E��

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
	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//�v���C���[�̗̑͂�0�ȉ��ɂȂ����Ƃ�

			//SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_Player.state = PLAYERSTATE_DEATH;
			g_Player.nCounterState = 60;				//�_���[�W��Ԏ���
			g_Player.bDisp = false;
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 15;				//�_���[�W��Ԏ���

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
Player *GetPlayer(void)
{
	return &g_Player;
}

