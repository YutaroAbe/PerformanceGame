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
#include "sideenemy.h"
#include "tbossenemy.h"
#include "effect.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define NCUT_ANIM_TIME (15)							//�J�E���g�A�j���[�V��������
#define NPAR_ANIM_TAIM (10)							//�A�j���[�V�����p�^�[��
#define POS_X (20)									//�|�W�V����_X
#define POS_Y (20)									//�|�W�V����_X
#define POLYGON_TEXTURENAMRE "data/TEXTURE/player000.png"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`���|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;   //���_�o�b�t�@�̃|�C���g
int g_nCounterAnim;									//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;									//�A�j���[�V�����p�^�[��No�A
Player g_Player;
float g_Spin;

//=============================================================================
//�����������v���C���[
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�e��_�ϐ�������
	g_nCounterAnim= 0;							    //	�J�E���^�[������������
	g_nPatternAnim = 0;							    //	�p�^�[������������
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�ʒu
	g_Player.nCounterState = 0;						//	��Ԃ̃J�E���^�[
	g_Player.nLife = 10;							//	����
	g_Player.bDisp = true;							//	���S���
	g_Player.state = PLAYERSTATE_NOMAL;

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
	g_Player.pos = D3DXVECTOR3(35, 365, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);			  //�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			  //����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);			  //�E��
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
	//�v���C���[�̉�ʂ̓����蔻��
	if (g_Player.pos.y <= 25)
	{//��ʏ�̓����蔻��̐ݒ�
		g_Player.move.y = 1;
	}
	if (g_Player.pos.y >= 695)
	{//��ʉ��̓����蔻��̐ݒ�
		g_Player.move.y = -1;
	}
	if (g_Player.pos.x <= 25)
	{//��ʉ��̓����蔻��̐ݒ�
		g_Player.move.x = 1;
	}
	if (g_Player.pos.x >= 1245)
	{//��ʉE�̓����蔻��̐ݒ�
		g_Player.move.x = -1;
	}

	if (g_Player.bDisp == true)
	{
		MODE pMode;
		pMode = GetMode();
		if (pMode == MODE_GAME)
		{
			SetEffect(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f), 13.0f, 10);
		}
	}
		//�v���C���[�̏�Ԃɂ��ݒ�
		switch (g_Player.state)
		{
		case PLAYERSTATE_NOMAL:
			break;

		case PLAYERSTATE_DAMAGE:

			g_Player.nCounterState--;	//�J�E���g�_�E��
			if (g_Player.nCounterState <= 0)
			{//	��ԃJ�E���^�[��0�ȉ��ɂȂ����ꍇ
				g_Player.state = PLAYERSTATE_NOMAL;			//	��Ԃ�ʏ���

				VERTEX_2D*pVtx;								//���_���̃|�C���^

				// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//	���_�o�b�t�@�A�����b�N����
				g_pVtxBuffPlayer->Unlock();
			}
			break;

		case PLAYERSTATE_DEATH:
			//	�J�E���g�_�E��
			g_Player.nCounterState--;
			if (g_Player.nCounterState <= 0)
			{//	��ԃJ�E���^�[��0�ȉ��ɂȂ����ꍇ
				SetGemeState(GAMESTATE_END);		//	���U���g��ʂɍs��
				g_Player.state = PLAYERSTATE_END;
			}
			break;
		case PLAYERSTATE_END:

			break;
		}
		//	�J�E���^�[���Z
		g_nCounterAnim++;

		if ((g_nCounterAnim %NCUT_ANIM_TIME) == 0)
		{
			g_nPatternAnim++;						//�p�^�[��No,�X�V
			g_nPatternAnim = (g_nPatternAnim) % NPAR_ANIM_TAIM;//�p�^�[�����������ɖ߂�
		}

		VERTEX_2D*pVtx;								//���_���̃|�C���^

		//�ړ��ݒ�=================================================================
		if (GetKeyboardPress(DIK_A) == true)
		{//�C�ӂ̃L�[(A�L�[)�������ꂽ���ǂ��� :���ړ�
			if (GetKeyboardPress(DIK_W) == true)
			{//����ړ�
				g_Player.move.x += sinf(-D3DX_PI * 0.75f) *1.05f;
				g_Player.move.y += cosf(-D3DX_PI * 0.75f) *1.05f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�����ړ�
				g_Player.move.x += sinf(-D3DX_PI * 0.25f) *1.05f;
				g_Player.move.y += cosf(-D3DX_PI * 0.25f) *1.05f;
			}
			else
			{//���ړ�
				g_Player.move.x += sinf(-D3DX_PI * 0.5f) *1.05f;
			}
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//�C�ӂ̃L�[(D�L�[)�������ꂽ���ǂ����@�F�E�ړ�

			if (GetKeyboardPress(DIK_W) == true)
			{//�E��ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.75f) *1.05f;
				g_Player.move.y += cosf(D3DX_PI * 0.75f) *1.05f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E���ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.25f) *1.05f;
				g_Player.move.y += cosf(D3DX_PI * 0.25f) *1.05f;
			}
			else
			{//�E�ړ�
				g_Player.move.x += sinf(D3DX_PI * 0.5f) *1.05f;
			}

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//�C�ӂ̃L�[(W�L�[)�������ꂽ���ǂ���
			g_Player.move.y -= 1.05f;						//�v���C���[�̈ʒu����Ɉړ�

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//	�C�ӂ̃L�[(S�L�[)�������ꂽ���ǂ���
			g_Player.move.y += 1.05f;					  //�v���C���[�̈ʒu�����Ɉړ�

			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}

		//�V�t�g+�ړ����x���ړ�����
		if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_D) == true)
		{//�E�x������

			if (GetKeyboardPress(DIK_W) == true)
			{//�E��ړ��x������
				g_Player.move.x -= sinf(D3DX_PI * 0.75f) *0.5f;
				g_Player.move.y -= cosf(D3DX_PI * 0.75f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E���ړ��x������
				g_Player.move.x -= sinf(D3DX_PI * 0.25f) *0.5f;
				g_Player.move.y -= cosf(D3DX_PI * 0.25f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//	�v���C���[�̈ʒu���Ɉړ�
				g_Player.move.x += 0.5f;
			}
			else
			{//	�v���C���[�̈ʒu����Ɉړ�
				g_Player.move.x -= 0.5f;
			}
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_A) == true)
		{//���x������

			if (GetKeyboardPress(DIK_W) == true)
			{//����ړ��x������
				g_Player.move.x -= sinf(-D3DX_PI * 0.75f) * 0.5f;
				g_Player.move.y -= cosf(-D3DX_PI * 0.75f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�����ړ��x������
				g_Player.move.x -= sinf(-D3DX_PI * 0.25f) *0.5f;
				g_Player.move.y -= cosf(-D3DX_PI * 0.25f) *0.5f;
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{
				g_Player.move.x -= 0.5f;					//�v���C���[�̈ʒu���Ɉړ�
			}
			else
			{
				g_Player.move.x += 0.5f;					//�v���C���[�̈ʒu���Ɉړ�
			}
			// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_W) == true)
		{//��ړ��x������
			g_Player.move.y += 0.5f;						//�v���C���[�̈ʒu����Ɉړ�

															// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true && GetKeyboardPress(DIK_S) == true)
		{//���ړ��x������
			g_Player.move.y -= 0.5f;						//�v���C���[�̈ʒu����Ɉړ�

															// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�o�b�t�@�A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;

		g_Player.move.x += (0.0f - g_Player.move.x)*0.075f;
		g_Player.move.y += (0.0f - g_Player.move.y)*0.075f;

		//	�e�̐ݒ�===================================================================
		if (g_Player.bDisp == true)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//�X�y�[�X�������ꍇ�̏���
				//(1)
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);			//	�e��
				SetBullet(g_Player.pos, D3DXVECTOR3(-8.0f, -0.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e��
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -2.0f, 0.0f), BULLETTYPE_PLAYER);			//	�e�E��
				SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 2.0f, 0.0f), BULLETTYPE_PLAYER);			//	�e�E��
			}

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//�X�y�[�X�������ꍇ�̏���
				if (g_Player.nLife <= 2)
				{
					//(1)
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e��
					SetBullet(g_Player.pos, D3DXVECTOR3(-8.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e�E
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -2.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e��
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 2.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e�E
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, -4.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e��
					SetBullet(g_Player.pos, D3DXVECTOR3(8.0f, 4.0f, 0.0f), BULLETTYPE_PLAYER);		//	�e�E
				}
			}
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//	�X�y�[�X�������ꍇ�̏���
				PlaySound(SOUND_LABEL_SE_GUN);
			}
		}
		//	���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y - POS_Y, 0.0f);	//	����
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y - POS_Y, 0.0f);	//	�E��
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - POS_X, g_Player.pos.y + POS_Y, 0.0f);	//	����
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + POS_X, g_Player.pos.y + POS_Y, 0.0f);	//	�E��

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
			g_Player.nLife = 10;					//�̗�
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

			SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

