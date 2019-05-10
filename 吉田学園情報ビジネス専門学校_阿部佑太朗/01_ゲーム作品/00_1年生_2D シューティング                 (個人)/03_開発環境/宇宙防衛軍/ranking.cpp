//=========================================================================================================================
//
// �����L���O���� [Ranking.cpp]
// Author :
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "ranking.h"//�X�R�A
#include "input.h"//�L�[�{�[�h
#include "fade.h"
#include "score.h"
#include "bg.h"
#include "sound.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_RANKING_NUMBER (8)
#define TEXTURE_RANKING "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;// ���_�o�b�t�@�ւ̃|�C���^
int g_aRanking = 0;//�����L���O
int g_aNumber[MAX_RANKING_NUMBER] = {0,0,0,0,0,0,0,0};

//=========================================================================================================================
// �X�R�A����������
//=========================================================================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//	�f�o�C�X�|�C���^
	int nCntRanking;							//	�X�R�A�J�E���g
	float nRankingPos;							//	�X�R�A�ʒu
	//	�����������o�b�N�O���E���h
	InitBG();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_RANKING,&g_pTextureRanking);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKING_NUMBER,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffRanking,
								NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffRanking->Lock(0,0,(void**)&pVtx,0);

	for (nCntRanking = 0, nRankingPos = 100; nCntRanking < MAX_RANKING_NUMBER; nCntRanking++, nRankingPos += 130)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(nRankingPos, 550.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(nRankingPos + 150.0f, 550.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(nRankingPos, 650.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(nRankingPos + 150.0f, 650.0f, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=========================================================================================================================
// �X�R�A�I������
//=========================================================================================================================
void UninitRanking(void)
{
	// �I�������o�b�N�O���E���h
	UninitBG();

	//�e�N�X�`���[�̔j��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//=========================================================================================================================
// �X�R�A�X�V����
//=========================================================================================================================
void UpdateRanking(void)
{
	// �X�V�����o�b�N�O���E���h
	UpdateBG();
	FADE pFade;

	pFade = *GetFade();

	if (pFade == FADE_NONE)
	{
		//�L�[�{�[�h�ݒ�
		if (GetKeyboardPress(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_SELECTMODE);
		}
	}
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffRanking->Lock(0,0,(void**)&pVtx,0);

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING_NUMBER; nCntRanking++)
	{//�X�R�A�J�E���g
		 //�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2((g_aNumber[nCntRanking] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((g_aNumber[nCntRanking]  * 0.1f ) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(((g_aNumber[nCntRanking] ) * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((g_aNumber[nCntRanking]) * 0.1f ) + 0.1f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}

		//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=========================================================================================================================
// �X�R�A�`�揈��
//=========================================================================================================================
void DrawRanking(void)
{
	//�`�揈���o�b�N�O���E���h
	DrawBG();
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	int nCntRanking;//�X�R�A�J�E���g

				  //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(0,g_pVtxBuffRanking,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�X�R�A�̕`��
	for (nCntRanking = 0; nCntRanking< MAX_RANKING_NUMBER; nCntRanking++)
	{//�X�R�A�J�E���g
	 //�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureRanking);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRanking * 4, 2);
	}
}
//=========================================================================================================================
//�Z�b�g�����L���O
//=========================================================================================================================
void SetRankScore(int nScore)
{
	if (nScore > g_aRanking)
	{
		g_aRanking = nScore;		//�n�C�X�R�A�X�V
	}
	g_aNumber[0] = g_aRanking / 100000000 / 10000000;
	g_aNumber[1] = g_aRanking % 10000000 / 1000000;
	g_aNumber[2] = g_aRanking % 1000000 / 100000;
	g_aNumber[3] = g_aRanking % 100000 / 10000;
	g_aNumber[4] = g_aRanking % 10000 / 1000;
	g_aNumber[5] = g_aRanking % 1000 / 100;
	g_aNumber[6] = g_aRanking % 100 / 10;
	g_aNumber[7] = g_aRanking % 10 / 1;
}
