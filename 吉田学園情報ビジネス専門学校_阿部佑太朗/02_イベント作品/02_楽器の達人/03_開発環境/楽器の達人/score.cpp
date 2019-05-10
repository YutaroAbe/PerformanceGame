//=========================================================================================================================
//
// �X�R�A�̏��� [score.cpp]
// Author :�@YUTARO�@ABE
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "score.h"//�X�R�A
#include "input.h"//�L�[�{�[�h
#include "ranking.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_SCORE_NUMBER (8)
#define TEXTURE_SCORE "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SCORE1 "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SCORE2 "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;// ���_�o�b�t�@�ւ̃|�C���^
int g_nScore;// �X�R�A
D3DXVECTOR3 g_posScore;

//=========================================================================================================================
// �X�R�A����������
//=========================================================================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	float nCntScore;//�X�R�A�J�E���g
					//float nScorePos;//�X�R�A�ʒu

					//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 0;

	//�ʒu
	g_posScore = D3DXVECTOR3(880, 70, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(pDevice, TEXTURE_SCORE, &g_pTextureScore);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock
	(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y - 30, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y - 30, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x - 30, g_posScore.y + 30, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 30, g_posScore.y + 30, 0.0f);
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
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
		g_posScore.x += 50;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//=========================================================================================================================
// �X�R�A�I������
//=========================================================================================================================
void UninitScore(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
	SortRanking(g_nScore);
}

//=========================================================================================================================
// �X�R�A�X�V����
//=========================================================================================================================
void UpdateScore(void)
{
}

//=========================================================================================================================
// �X�R�A�`�揈��
//=========================================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	int nCntScore;//�X�R�A�J�E���g

				  //�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	//�X�R�A�̕`��
	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{//�X�R�A�J�E���g
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//=========================================================================================================================
// �X�R�A�̉��Z
//=========================================================================================================================
void AddScore(int nValue)
{

	int nCntScore;
	int aNumber[MAX_SCORE_NUMBER];

	g_nScore += nValue;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	aNumber[0] = g_nScore / 100000000 / 10000000;
	aNumber[1] = g_nScore % 10000000 / 1000000;
	aNumber[2] = g_nScore % 1000000 / 100000;
	aNumber[3] = g_nScore % 100000 / 10000;
	aNumber[4] = g_nScore % 10000 / 1000;
	aNumber[5] = g_nScore % 1000 / 100;
	aNumber[6] = g_nScore % 100 / 10;
	aNumber[7] = g_nScore % 10 / 1;


	for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
	{//�X�R�A�J�E���g
	 //�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
int GetScore(void)
{
	return g_nScore;
}
