//=============================================================================
//
// �e�̏��� [Door.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "door.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_DOOR		(10000)					// �e�̍ő吔
#define POS_X (55)								//�|�W�V����_X
#define POS_Y (65)								//�|�W�V����_Y2
#define Door__TEXTURENAMRE "data/TEXTURE/door.png"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	bool bUse;          //�g�p���Ă��邩�ǂ���
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No
	int nLife;			//����
	int nType;
}DOOR;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureDoor = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDoor = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
DOOR g_aDoor[MAX_DOOR];						//�e�̏��
int nState;
//=============================================================================
// ����������
//=============================================================================
void InitDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntDoor;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		g_aDoor[nCntDoor].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDoor[nCntDoor].bUse = false;
		g_aDoor[nCntDoor].nLife = 0;
		g_aDoor[nCntDoor].nCounterAnim = 0;
		g_aDoor[nCntDoor].nPatternAnim = 0;
		g_aDoor[nCntDoor].nType = 0;
	}
	nState = 0;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, Door__TEXTURENAMRE, &g_pTextureDoor);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DOOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDoor,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
													//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);//����
		pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);//�E��
		pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);//����
		pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);//�E��
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
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);			//�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffDoor->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitDoor(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureDoor != NULL)
	{
		g_pTextureDoor->Release();
		g_pTextureDoor = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDoor != NULL)
	{
		g_pVtxBuffDoor->Release();
		g_pVtxBuffDoor = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateDoor(void)
{
	VERTEX_2D*pVtx;//���_���̃|�C���^
				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//�e���g�p����Ă��邩
		{
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);



			Enemy *pEnemy;		//�G�l�~�[�|�C���^
			pEnemy = GetEnemy();
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{//�G�l�~�[
				if (pEnemy->bUse == true) //�G���g�p����Ă���
				{
					if (pEnemy->state == ENEMYSTATE_NOMAL)
					{
						//[�G�Ƃ̓����蔻��]
						if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType ==  0)
						{
							nState = 1;
							pEnemy->bUse = false;

						}
						else	if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType == 1)
						{
							nState = 2;
							pEnemy->bUse = false;

						}
						else	if (pEnemy->pos.x - 40 < g_aDoor[nCntDoor].pos.x && pEnemy->pos.x + 40 > g_aDoor[nCntDoor].pos.x  &&
							pEnemy->pos.y - 40 < g_aDoor[nCntDoor].pos.y && pEnemy->pos.y + 40 > g_aDoor[nCntDoor].pos.y && g_aDoor[nCntDoor].nType == 2)
						{
							nState = 3;
							pEnemy->bUse = false;

						}

					}
				}
			}

		}
		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffDoor->Unlock();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//�e���g�p����Ă��邩
		{
			switch (nState)
			{
			case 0:
				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);			//	����
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);			//	�E��
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);			//	����
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);			//	�E��
				g_aDoor[nCntDoor].nPatternAnim = 0;
				g_aDoor[nCntDoor].nCounterAnim = 0;
				break;
			case 1:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//�p�^�[��No,�X�V
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//�p�^�[�����������ɖ߂�

																							  //�e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //�E��
					pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
					pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //�E��
					pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;
			case 2:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//�p�^�[��No,�X�V
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//�p�^�[�����������ɖ߂�

																							  //�e�N�X�`�����W
					pVtx[4].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //�E��
					pVtx[5].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
					pVtx[6].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //�E��
					pVtx[7].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;

			case 3:
				g_aDoor[nCntDoor].nCounterAnim++;
				if ((g_aDoor[nCntDoor].nCounterAnim % 6) == 0)
				{
					//�p�^�[��No,�X�V
					g_aDoor[nCntDoor].nPatternAnim = (g_aDoor[nCntDoor].nPatternAnim + 1) % 4;//�p�^�[�����������ɖ߂�

																							  //�e�N�X�`�����W
					pVtx[8].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //�E��
					pVtx[9].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
					pVtx[10].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //�E��
					pVtx[11].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��

					if (g_aDoor[nCntDoor].nPatternAnim <= 0)
					{
						nState = 0;
						g_aDoor[nCntDoor].nPatternAnim = 4;

					}
				}
				break;
			}
		}

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffDoor->Unlock();

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawDoor(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntDoor;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffDoor, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureDoor);

	// �|���S���̕`��
	for (nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == true)//�e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0 + (4 * nCntDoor),2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetDoor(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;								//���_���̃|�C���^
												//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffDoor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDoor = 0; nCntDoor < MAX_DOOR; nCntDoor++)
	{
		if (g_aDoor[nCntDoor].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aDoor[nCntDoor].pos = pos;
			g_aDoor[nCntDoor].nCounterAnim = 0;
			g_aDoor[nCntDoor].nPatternAnim = 0;
			g_aDoor[nCntDoor].nType = nType;
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x - POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aDoor[nCntDoor].pos.x + POS_X, g_aDoor[nCntDoor].pos.y + POS_Y, 0.0f);
			//����

			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 0.0f);				 //�E��
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.0f, 1.0f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aDoor[nCntDoor].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��

			g_aDoor[nCntDoor].bUse = true;//�e���g�p����Ă���


			break;
		}
		pVtx += 4;			//�Y���̈ʒu�Ői�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffDoor->Unlock();
}
