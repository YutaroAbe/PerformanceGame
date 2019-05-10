//=============================================================================
//
// �eno���� [explosion.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "bullet.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION (128)					            //�����̍ő吔
#define POS_X         (25)								//�|�W�V����_X
#define POS_Y         (25)								//�|�W�V����_Y

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;      //�J���[
	int nCounterAnim;   //�A�j���[�V�����J�E���^�[
	int nPatternAnim;   //�A�j���[�V�����p�^�[��No
	bool bUse;          //�g�p���Ă��邩�ǂ���

}Explosion;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	    // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	    // ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];				    //�����̂̏��
#define EXPLOSION_TEXTURENAMRE "data/TEXTURE/explosion000.png"

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	int nCntExplosion;

	// �����̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col= D3DXCOLOR(255, 255, 255, 0);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURENAMRE, &g_pTextureExplosion);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�ݒ�
		//�|�W�V����
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y + POS_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y + POS_Y, 0.0f);
		//RHW
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);				//����
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);			//�E��
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);				//����
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);			//�E��

		pVtx += 4;	//���_�|�C���^��4�i�߂�
	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D*pVtx;//���_���̃|�C���^
	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)//�e���g�p����Ă��邩
			{
				g_aExplosion[nCntExplosion].nCounterAnim++;

				if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
				{
					//�p�^�[��No,�X�V
					g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;//�p�^�[�����������ɖ߂�

				//�e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.0f, 0.0f);				 //�E��
					pVtx[1].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 0.0f);       //�E��
					pVtx[2].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.0f, 1.0f);				 //�E��
					pVtx[3].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 1.0f);       //�E��

						if (g_aExplosion[nCntExplosion].nPatternAnim <= 0)
					{
						g_aExplosion[nCntExplosion].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}
				//���_���X�V
				pVtx += 4;
		}
		//���_�o�b�t�@�A�����b�N����
		g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//�e���g�p����Ă���
		{

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntExplosion,
				2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	VERTEX_2D*pVtx = NULL;								//���_���̃|�C���^


	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)	//�e���g�p����Ă��Ȃ�
		{
			g_aExplosion[nCntExplosion].pos = pos;
           //�J���[
			g_aExplosion[nCntExplosion].col = col;
			//�|�W�V����
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y - POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - POS_X, g_aExplosion[nCntExplosion].pos.y + POS_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + POS_X, g_aExplosion[nCntExplosion].pos.y + POS_Y, 0.0f);


			//�A�j���[�V����
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.0f, 0.0f);				 //�E��
			pVtx[1].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 0.0f);       //�E��
			pVtx[2].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8 + 0.0f), 1.0f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2(0.125f * (g_aExplosion[nCntExplosion].nPatternAnim % 8) + 0.125f, 1.0f);       //�E��


			g_aExplosion[nCntExplosion].bUse = true;//�e���g�p����Ă���
			break; //�g�p���Ă��Ȃ���Ԃɂ���

		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

