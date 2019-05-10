//=============================================================================
//
// �t�����gBG���� [FrontBG.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "frontBG.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_FrontBG		(4)								// �G�̎��FrontBG
#define FrontBG_01 "data/TEXTURE/front000.png"
#define FrontBG_02 "data/TEXTURE/front001.png"
#define FrontBG_03 "data/TEXTURE/.png"
#define FrontBG_04 "data/TEXTURE/.png"
#define FrontBG_PMAX (15)											//�G�̑傫��
#define FrontBG_PMAY (35)											//�G�̑傫��
#define	MAX_FrontBG	(128)	// �G�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFrontBG[MAX_TYPE_FrontBG] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrontBG = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
FrontBG g_aFrontBG[MAX_FrontBG];										//�G�̏��

//=============================================================================
// ����������
//=============================================================================
void InitFrontBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFrontBG;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		g_aFrontBG[nCntFrontBG].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aFrontBG[nCntFrontBG].nType = 0;
		g_aFrontBG[nCntFrontBG].fHeight = 0;
		g_aFrontBG[nCntFrontBG].fWindth = 0;
		g_aFrontBG[nCntFrontBG].bUse = false;
		g_aFrontBG[nCntFrontBG].nCounterState = 0;
	}
	
	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, FrontBG_01, &g_apTextureFrontBG[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, FrontBG_02, &g_apTextureFrontBG[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, FrontBG_03, &g_apTextureFrontBG[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, FrontBG_04, &g_apTextureFrontBG[3]);
	
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FrontBG,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFrontBG,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		//�|�W�V����
		pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
		
		//RHW
		pVtx[nCntFrontBG * 4].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 1].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 2].rhw = 1.0f;
		pVtx[nCntFrontBG * 4 + 3].rhw = 1.0f;
		//�J���[
		pVtx[nCntFrontBG * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntFrontBG * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCntFrontBG * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[nCntFrontBG * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[nCntFrontBG * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[nCntFrontBG * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrontBG->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitFrontBG(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_FrontBG; nCntTex++)
	{
		if (g_apTextureFrontBG[nCntTex] != NULL)
		{
			g_apTextureFrontBG[nCntTex]->Release();
			g_apTextureFrontBG[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFrontBG != NULL)
	{
		g_pVtxBuffFrontBG->Release();
		g_pVtxBuffFrontBG = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFrontBG(void)
{
	VERTEX_2D*pVtx = NULL;	

	PLAYER *pPlyer;
	pPlyer = GetPlayer();
		
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
			g_aFrontBG[nCntFrontBG].pos.x -= pPlyer->move.x;
		
			if (g_aFrontBG[nCntFrontBG].bUse == true)//�G�l�~�[���g�p����Ă��邩 
			{//�|�W�V����
				pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
				pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);

			}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrontBG->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFrontBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFrontBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		if (g_aFrontBG[nCntFrontBG].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureFrontBG[g_aFrontBG[nCntFrontBG].nType]);
			//�|���S���̕`��
			if (g_aFrontBG[nCntFrontBG].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntFrontBG * 4,2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetFrontBG(int nType,D3DXVECTOR3 pos ,float fHeight, float fWindth)
{
	int nCntFrontBG;
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffFrontBG->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntFrontBG = 0; nCntFrontBG < MAX_FrontBG; nCntFrontBG++)
	{
		if (g_aFrontBG[nCntFrontBG].bUse == false)		//�G���g�p����Ă��Ȃ�
		{
			g_aFrontBG[nCntFrontBG].pos = pos;
			g_aFrontBG[nCntFrontBG].nType = nType;
			g_aFrontBG[nCntFrontBG].fHeight = fHeight;
			g_aFrontBG[nCntFrontBG].fWindth = fWindth;
			g_aFrontBG[nCntFrontBG].bUse = true;			//�G���g�p����Ă���

			//�|�W�V����
			pVtx[nCntFrontBG * 4].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 1].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y - g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 2].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x - g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);
			pVtx[nCntFrontBG * 4 + 3].pos = D3DXVECTOR3(g_aFrontBG[nCntFrontBG].pos.x + g_aFrontBG[nCntFrontBG].fWindth, g_aFrontBG[nCntFrontBG].pos.y + g_aFrontBG[nCntFrontBG].fHeight, 0.0f);

			break;
		}

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffFrontBG->Unlock();
}
//=============================================================================
// �G�̎擾
//=============================================================================
FrontBG *GetFrontBG(void)
{
	return &g_aFrontBG[0];
}