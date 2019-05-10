//=============================================================================
//
// yajirusi���� [Yajirusi.cpp]
// Author :YUUTAROU ABE
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "Yajirusi.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "time.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_Yajirusi		(4)								// �G�̎��Yajirusi
#define Yajirusi_01 "data/TEXTURE/yaji000.png"
#define Yajirusi_02 "data/TEXTURE/yaji001.png"
#define Yajirusi_03 "data/TEXTURE/Yajirusi002.png"
#define Yajirusi_04 "data/TEXTURE/Yajirusi003.png"
#define Yajirusi_PMAX (15)											//�G�̑傫��
#define	MAX_Yajirusi	(128)	// �G�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureYajirusi[MAX_TYPE_Yajirusi] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffYajirusi = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Yajirusi g_aYajirusi[MAX_Yajirusi];										//�G�̏��
int g_YajiSe;
int g_YjirusiTime;

//=============================================================================
// ����������
//=============================================================================
void InitYajirusi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntYajirusi;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		g_aYajirusi[nCntYajirusi].pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aYajirusi[nCntYajirusi].nType = 0;
		g_aYajirusi[nCntYajirusi].fHeight = 0;
		g_aYajirusi[nCntYajirusi].fWindth = 0;
		g_aYajirusi[nCntYajirusi].bUse = false;
		g_aYajirusi[nCntYajirusi].nCounterAnim = 0;
		g_aYajirusi[nCntYajirusi].nPatternAnim = 0;
		g_aYajirusi[nCntYajirusi].nCounterState = 0;

		g_YajiSe = 0;
	}
	g_YjirusiTime = 0;
	
	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	// [1]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_01, &g_apTextureYajirusi[0]);
	// [2]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_02, &g_apTextureYajirusi[1]);
	// [3]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_03, &g_apTextureYajirusi[2]);
	// [4]
	D3DXCreateTextureFromFile(pDevice, Yajirusi_04, &g_apTextureYajirusi[3]);
	
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Yajirusi,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffYajirusi,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		//�|�W�V����
		pVtx[nCntYajirusi * 4].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
		pVtx[nCntYajirusi * 4 + 3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
		
		//RHW
		pVtx[nCntYajirusi * 4].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 1].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 2].rhw = 1.0f;
		pVtx[nCntYajirusi * 4 + 3].rhw = 1.0f;
		//�J���[
		pVtx[nCntYajirusi * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntYajirusi * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCntYajirusi * 4].tex = D3DXVECTOR2(0.0f, 0.0f);			//����
		pVtx[nCntYajirusi * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);			//�E��
		pVtx[nCntYajirusi * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);			//����
		pVtx[nCntYajirusi * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);			//�E��

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffYajirusi->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitYajirusi(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_Yajirusi; nCntTex++)
	{
		if (g_apTextureYajirusi[nCntTex] != NULL)
		{
			g_apTextureYajirusi[nCntTex]->Release();
			g_apTextureYajirusi[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffYajirusi != NULL)
	{
		g_pVtxBuffYajirusi->Release();
		g_pVtxBuffYajirusi = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateYajirusi(void)
{
	VERTEX_2D*pVtx = NULL;	

	PLAYER *pPlyer;
	pPlyer = GetPlayer();
		
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
			g_aYajirusi[nCntYajirusi].pos.x -= pPlyer->move.x;
		
		if (g_aYajirusi[nCntYajirusi].bUse == true)//�G�l�~�[���g�p����Ă��邩 
		{
			g_aYajirusi[nCntYajirusi].nCounterAnim++;
			if ((g_aYajirusi[nCntYajirusi].nCounterAnim % 15) == 0)
			{
				//�p�^�[��No,�X�V
				g_aYajirusi[nCntYajirusi].nPatternAnim = (g_aYajirusi[nCntYajirusi].nPatternAnim + 1) % 4;				//�p�^�[�����������ɖ߂� 
			}

			pVtx[0].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4), 0.0f);				 //�E��
			pVtx[1].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4) + 0.25f, 0.0f);       //�E��
			pVtx[2].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4), 1.0f);				 //�E��
			pVtx[3].tex = D3DXVECTOR2(0.25f * (g_aYajirusi[nCntYajirusi].nPatternAnim % 4) + 0.25f, 1.0f);       //�E��
		}
		pVtx += 4;
		
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffYajirusi->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawYajirusi(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffYajirusi, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		if (g_aYajirusi[nCntYajirusi].bUse == true) //�G���g�p����Ă��邩�ǂ���
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureYajirusi[g_aYajirusi[nCntYajirusi].nType]);
			//�|���S���̕`��
			if (g_aYajirusi[nCntYajirusi].bUse == true)//�G���g�p����Ă���
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntYajirusi * 4,2);
			}
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetYajirusi(int nType,D3DXVECTOR3 pos)
{
	int nCntYajirusi;
	VERTEX_2D*pVtx;									//���_���̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^
	g_pVtxBuffYajirusi->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntYajirusi = 0; nCntYajirusi < MAX_Yajirusi; nCntYajirusi++)
	{
		if (g_aYajirusi[nCntYajirusi].bUse == false)		//�G���g�p����Ă��Ȃ�
		{
			g_aYajirusi[nCntYajirusi].pos = pos;
			g_aYajirusi[nCntYajirusi].nType = nType;
			g_aYajirusi[nCntYajirusi].fHeight = 0;
			g_aYajirusi[nCntYajirusi].fWindth = 0;
			g_aYajirusi[nCntYajirusi].bUse = true;			//�G���g�p����Ă���
			g_aYajirusi[nCntYajirusi].nCounterAnim = 0;
			g_aYajirusi[nCntYajirusi].nPatternAnim = 0;

			//�|�W�V����
			pVtx[nCntYajirusi * 4].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 1].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y - Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 2].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x - Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			pVtx[nCntYajirusi * 4 + 3].pos = D3DXVECTOR3(g_aYajirusi[nCntYajirusi].pos.x + Yajirusi_PMAX, g_aYajirusi[nCntYajirusi].pos.y + Yajirusi_PMAX, 0.0f);
			break;
		}

	}
	//���_�o�b�t�@�A�����b�N����
	g_pVtxBuffYajirusi->Unlock();
}
//=============================================================================
// �G�̎擾
//=============================================================================
Yajirusi *GetYajirusi(void)
{
	return &g_aYajirusi[0];
}