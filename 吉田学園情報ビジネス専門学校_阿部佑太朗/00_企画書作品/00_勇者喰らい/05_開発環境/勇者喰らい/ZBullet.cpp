//=========================================================================================================//
//
// [�e����]->�e�ړ�:�������� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "camera.h"
#include "model.h"
#include "sound.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define	MAX_EXPLOSION				(64)		// �e�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ��l
	D3DXVECTOR3	blown;			//������ԋ���
	D3DXVECTOR3 rot;			//�p�x
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X
	MODEL_USE	use;			//���f���̔���p
	float		fRange;			//�U���͈�
	float		fAtkplus;		//�U���̔{�� ���ݎ��Ԍv�Z�����p
	float		fSlip;			//����{��
	float		fAttack;		//�U����
	float		fLife;			//�e��HP
	int			nInvincible;	//�q�b�g���̖��G�ɂȂ鎞��
	int			nCntAtk;		//�U�����萔
	int			nType;			//���ʎw��
	int			nAtkType;		//�U��Hit������
	int			nCntModel;		//�����̃��f��
	int			nCntStop;		//�~�܂��Ă��鎞��
	bool		bUse;
}Bullet;

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
Bullet	g_aBullet[MAX_EXPLOSION];					//�ő��Animation��

//=========================================================================================================//
// * �e	�X�V����
//=========================================================================================================//
void UpdateBullet(void)
{
	MODEL_INFO *pModel = GetModel_Info();
	D3DXMATRIX	mtxBullet;
	D3DXMATRIX	mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	int nCntBullet;


	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		if (g_aBullet[nCntBullet].bUse == true)
		{//�X�V�I

			if (g_aBullet[nCntBullet].nCntStop > 0) { g_aBullet[nCntBullet].nCntStop--; }
			else if (g_aBullet[nCntBullet].nCntStop == 0)
			{//�҂����ԏI��
				if (pModel[g_aBullet[nCntBullet].nCntModel].set.nNumMotion[1] < 12)
				{//��x�L�����Z�����ꂽ
					//g_aBullet[nCntBullet].bUse = false;
				}
				g_aBullet[nCntBullet].nCntStop = -1;
			}
			else
			{//�҂����Ԃ��Ȃ�
				g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

				//����
				//g_aBullet[nCntBullet].move.x *= g_aBullet[nCntBullet].fSlip;
				//g_aBullet[nCntBullet].move.z *= g_aBullet[nCntBullet].fSlip;

				//����
				UpdateEBullet(nCntBullet);

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&mtxBullet);

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBullet[nCntBullet].rot.y, g_aBullet[nCntBullet].rot.x, g_aBullet[nCntBullet].rot.z);
				D3DXMatrixMultiply(&mtxBullet, &mtxBullet, &mtxRot);

				// �ړ��𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
				D3DXMatrixMultiply(&mtxBullet, &mtxBullet, &mtxTrans);

				//�����蔻��
				Hitjudge(g_aBullet[nCntBullet].nCntModel
					, nCntBullet
					, g_aBullet[nCntBullet].nCntAtk
					, g_aBullet[nCntBullet].nInvincible
					, g_aBullet[nCntBullet].fRange
					, g_aBullet[nCntBullet].fAttack
					, g_aBullet[nCntBullet].fAtkplus
					, g_aBullet[nCntBullet].blown
					, mtxBullet, 1);

				//�����͌���
				g_aBullet[nCntBullet].fLife -= 1.0f;
				if (g_aBullet[nCntBullet].fLife < 0.0f) { g_aBullet[nCntBullet].bUse = false; }
			}
		}
	}
}

//=========================================================================================================//
// * �e	�펞�X�V����
//=========================================================================================================//
void UpdateEBullet(int nCntBullet)
{
	D3DXVECTOR3 pos = g_aBullet[nCntBullet].pos;
	float fRand[3];

	switch (g_aBullet[nCntBullet].nType)
	{//�펞�����������
	case 0:
		if (rand() % 4 == 0)
		{
		//SetAnimation(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), 200, 200, 5, 1, 5, 0, ANIMATION_NORMAL);
			SetZWindow(g_aBullet[nCntBullet].pos + D3DXVECTOR3((rand() % 100) * 0.5f, (rand() % 100) * 0.5f, (rand() % 100) * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50, 3, 1, WINDOWSTATE_FADEOUT, 0.05f);
		}
		break;
	case 1:

		break;
	case 2:

		break;
	case 40:	//���e�I
		if ((int)g_aBullet[nCntBullet].fLife % 10 == 1)
		{//�炵������Ƃ��邳��
			PlaySound(SOUND_LABEL_ATTACK402);
		}
		if ((int)g_aBullet[nCntBullet].fLife % 2 == 1)
		{//������񂶂�`
			fRand[0] = (rand() % 628) * 0.01f;
			fRand[1] = (rand() % 6000) * 0.1f + 150.0f;
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * fRand[1], 100.0f, cosf(fRand[0]) * fRand[1]), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 6, 6, 1, ANIMATION_NORMAL);
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * fRand[1], 100.0f, cosf(fRand[0]) * fRand[1]), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80, 8, 1, 1, 6, 1, ANIMATION_UP);
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * fRand[1], 60.0f, cosf(fRand[0]) * fRand[1]), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 6, 9, 10, ANIMATION_NORMAL);
			SetBullet(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * fRand[1], 60.0f, cosf(fRand[0]) * fRand[1]), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 12.5f, 30.0f), g_aBullet[nCntBullet].use, g_aBullet[nCntBullet].fAttack, 9.15f, 90.0f, 1.0f, 20, 3, 99999, 31, 31, -1, g_aBullet[nCntBullet].nCntModel);
		}
		break;
	case 42:	//����
		for (int nCount = 0; nCount < 12; nCount++)
		{//���˓I�Ȋ����ɔ��� 50 60 70 80 80 60 40 20
			fRand[0] = 20.0f;
			fRand[0] += nCount * 10.0f;
			if(nCount >= 12 / 2){ fRand[0] -= (nCount - (12 / 2 - 1)) * 10.0f; }
			
			if (rand() % 2 == 0)
			{
				SetAnimation(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), (int)fRand[0], (int)fRand[0], 8, 1, 2, 6, 1, ANIMATION_NORMAL);
			}
			pos += D3DXVECTOR3(sinf(g_aBullet[nCntBullet].rot.y) * -fRand[0] * 0.8f, 0.0f, cosf(g_aBullet[nCntBullet].rot.y) * -fRand[0] * 0.8f);
		}
		break;
	case 43:	//����
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf((rand() % 314) * 0.1f) * 20.0f, 50.0f, cosf((rand() % 314) * 0.1f) * 20.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 2, 10, 1, ANIMATION_NORMAL);
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf((rand() % 314) * 0.1f) * 20.0f, 80.0f, cosf((rand() % 314) * 0.1f) * 20.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 2, 10, 1, ANIMATION_NORMAL);
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf((rand() % 314) * 0.1f) * 20.0f, 110.0f, cosf((rand() % 314) * 0.1f) * 20.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 2, 10, 1, ANIMATION_NORMAL);
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf((rand() % 314) * 0.1f) * 20.0f, 140.0f, cosf((rand() % 314) * 0.1f) * 20.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 2, 10, 1, ANIMATION_NORMAL);
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf((rand() % 314) * 0.1f) * 20.0f, 170.0f, cosf((rand() % 314) * 0.1f) * 20.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 150, 8, 1, 2, 10, 1, ANIMATION_NORMAL);
		break;
	case 401://�������@�U��΂�
		SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(rand() % 1000 * 0.1f - 50.0f, 0.0f, rand() % 1000 * 0.1f - 50.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 8, 1, 4, 6, 1, ANIMATION_NORMAL);
		break;
	case 402://�n�ʂ����+��
		if ((int)g_aBullet[nCntBullet].fLife % 10 == 0)
		{
			PlaySound(SOUND_LABEL_ATTACK402);
			fRand[0] = (rand() % 314) * 0.01f;
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * 10.0f, 100.0f, cosf(fRand[0]) * 10.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 6, 6, 1, ANIMATION_NORMAL);
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * 10.0f, 100.0f, cosf(fRand[0]) * 10.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 80, 8, 1, 1, 6, 1, ANIMATION_UP);
			SetAnimation(g_aBullet[nCntBullet].pos + D3DXVECTOR3(sinf(fRand[0]) * 10.0f, 60.0f, cosf(fRand[0]) * 10.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 6, 9, 10, ANIMATION_NORMAL);
		}
		break;
	case 403://�d�̒e
		SetZWindow(g_aBullet[nCntBullet].pos + D3DXVECTOR3((rand() % 100) * 0.5f, (rand() % 100) * 0.5f, (rand() % 100) * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, WINDOWSTATE_FADEOUT, 0.05f);
		break;
	case 404://�d�̒e
		SetZWindow(g_aBullet[nCntBullet].pos + D3DXVECTOR3((rand() % 100) * 0.5f, (rand() % 100) * 0.5f, (rand() % 100) * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 3, 1, WINDOWSTATE_FADEOUT, 0.05f);
		break;
	case 405://�d�̒e
		SetZWindow(g_aBullet[nCntBullet].pos + D3DXVECTOR3((rand() % 100) * 0.5f, (rand() % 100) * 0.5f, (rand() % 100) * 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 3, 1, WINDOWSTATE_FADEOUT, 0.05f);
		break;

	case 500://�΂̒e
		SetAnimation(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), 80, 80, 8, 1, 3, 6, 1, ANIMATION_NORMAL);
		break;
	case 501://�΂̒e
		if (g_aBullet[nCntBullet].fLife == 2.0f)
		{
			SetBullet(pos, D3DXVECTOR3(sinf(g_aBullet[nCntBullet].rot.y), 0.0f, cosf(g_aBullet[nCntBullet].rot.y)) * -15.0f, D3DXVECTOR3(D3DX_PI * -0.5f, g_aBullet[nCntBullet].rot.y, 0.0f),
				D3DXVECTOR3(0.0f, 4.5f, 50.0f), g_aBullet[nCntBullet].use, g_aBullet[nCntBullet].fAttack, 1.85f, 70.0f, 1.0f, 120, 6, 99999, 42, 42, -1, g_aBullet[nCntBullet].nCntModel);
		}
		break;
	}
}
//=========================================================================================================//
// * �e	hit���X�V����
//=========================================================================================================//
void UpdateABullet(int nCntBullet, int nEnemy, float fAtk)
{
	MODEL_INFO *pModel = GetModel_Info();
	Camera *pCamera = GetCamera();

	switch (g_aBullet[nCntBullet].nAtkType)
	{//Hit�������������
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;

	case 41://���e�I
		SetZWindow(pModel[nEnemy].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		break;
	case 45://����
		pModel[nEnemy].data.nLifePoint = 1;
		break;

	case 400:
		SetAnimation(pModel[nEnemy].set.pos, D3DXCOLOR(0.5f, 1.0f, 1.0f, 0.5f), 550, 550, 5, 5, 2, 8, 2, ANIMATION_NORMAL);
		SetAnimation(pModel[nEnemy].set.pos, D3DXCOLOR(0.5f, 1.0f, 1.0f, 0.5f), 850, 850, 5, 5, 2, 8, 2, ANIMATION_NORMAL);
		break;
	case 401:
		SetZWindow(g_aBullet[nCntBullet].pos + D3DXVECTOR3(0.0f, 100.0f, 0.0f),D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 250, 4, 2, WINDOWSTATE_FADE_Z, 0.02f);
		break;
	case 402:
		SetAnimation(pModel[nEnemy].set.pos + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXCOLOR(0.5f, 1.0f, 1.0f, 0.5f), 350, 350, 5, 5, 2, 8, 2, ANIMATION_NORMAL);
		break;
	case 403://�d�̒e
		SetZWindow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		g_aBullet[nCntBullet].bUse = false;
		break;
	case 404://�d�̒e
		SetZWindow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120, 120, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		g_aBullet[nCntBullet].bUse = false;
		break;
	case 405://�d�̒e
		SetBullet(pModel[nEnemy].set.pos + D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, -50.0f, 30.0f), g_aBullet[nCntBullet].use, g_aBullet[nCntBullet].fAttack, 2.55f, 150.0f, 0.0f, 5, 4, 999999, 406, 406, 60, g_aBullet[nCntBullet].nCntModel);
		g_aBullet[nCntBullet].bUse = false;
		SetZWindow(pModel[nEnemy].set.pos + D3DXVECTOR3((rand() % 2000) * 0.1f - 100.0f, (rand() % 2000) * 0.1f - 100.0f, (rand() % 2000) * 0.1f - 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 250, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		break;

	case 406://�d�̒e
		PlaySound(SOUND_LABEL_Right);
		SetZWindow(pModel[g_aBullet[nCntBullet].nCntModel].set.pos + D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXVECTOR3(sinf(pCamera[0].rot.y), 0.0f, cosf(pCamera[0].rot.y)) * 3.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 300, 4, 2, WINDOWSTATE_FADE_Z, 0.02f);
		
		SetZWindow(pModel[nEnemy].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 250, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		SetZWindow(pModel[nEnemy].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 350, 350, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		SetZWindow(pModel[nEnemy].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 450, 450, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		SetZWindow(pModel[g_aBullet[nCntBullet].nCntModel].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 300, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		SetZWindow(pModel[g_aBullet[nCntBullet].nCntModel].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 400, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);
		SetZWindow(pModel[g_aBullet[nCntBullet].nCntModel].set.pos + D3DXVECTOR3((rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f, (rand() % 1000) * 0.1f - 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 500, 3, 2, WINDOWSTATE_FADEOUT, 0.05f);

		break;
	}
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 blown, MODEL_USE use, float fAttack, float fAtkplus, float fRange,
	float fSlip, float fLife, int nCntAtk, int nInvincible, int nType, int nAtkType, int nCntStop, int nCntModel)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].rot = rot;
			g_aBullet[nCntBullet].blown = blown;
			g_aBullet[nCntBullet].fAttack = fAttack;
			g_aBullet[nCntBullet].fAtkplus = fAtkplus;
			g_aBullet[nCntBullet].fRange = fRange;
			g_aBullet[nCntBullet].fSlip = fSlip;
			g_aBullet[nCntBullet].fLife = fLife;
			g_aBullet[nCntBullet].nCntAtk = nCntAtk;
			g_aBullet[nCntBullet].nInvincible = nInvincible;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].nAtkType = nAtkType;
			g_aBullet[nCntBullet].nCntStop = nCntStop;
			g_aBullet[nCntBullet].nCntModel = nCntModel;

			g_aBullet[nCntBullet].bUse = true;
			break;
		}
	}
}
//=========================================================================================================//
// * �SBullet�j������
//=========================================================================================================//
void BreakBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}
