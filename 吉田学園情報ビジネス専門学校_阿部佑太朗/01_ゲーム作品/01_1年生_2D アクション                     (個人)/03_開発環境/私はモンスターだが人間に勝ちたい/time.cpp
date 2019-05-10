//=========================================================================================================================
//
// �^�C���̏��� [time.cpp]
// Author : 
//
//=========================================================================================================================
#include "time.h"//�^�C��
#include "input.h"//�L�[�{�[�h
#include "fade.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_TIME_NUMBER (3)
#define TEXTURE_TIME "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;// ���_�o�b�t�@�ւ̃|�C���^
int g_nTime;// �X�R�A
D3DXVECTOR3 g_posTime;
int nCounterTime;

//=========================================================================================================================
// �X�R�A����������
//=========================================================================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	float nCntTime;//�X�R�A�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nTime = 150 * 60;
	nCounterTime = 0;

	//�ʒu
	g_posTime = D3DXVECTOR3(630, 40, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_TIME,&g_pTextureTime);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUMBER ,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTime,
								NULL);	

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	 
	for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - 25.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 25.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - 25.0f, g_posTime.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 25.0f, g_posTime.y + 20.0f, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
		g_posTime.x += 50;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();

}

//=========================================================================================================================
// �X�R�A�I������
//=========================================================================================================================
void UninitTime(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=========================================================================================================================
// �X�R�A�X�V����
//=========================================================================================================================
void UpdateTime(void)
{
	nCounterTime++;
	if (nCounterTime % 60 == 0)
	{
		AddTime(1);
	}
	if (g_nTime <= 0)
	{
		g_nTime = 0;
	}
}

//=========================================================================================================================
// �X�R�A�`�揈��
//=========================================================================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	int nCntTime;//�X�R�A�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(0,g_pVtxBuffTime,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	//�X�R�A�̕`��
	for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
	{//�X�R�A�J�E���g
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//=========================================================================================================================
// �X�R�A�̉��Z
//=========================================================================================================================
void AddTime(int nValue )
{
	int nCntScore;
	int aNumber[MAX_TIME_NUMBER];

	g_nTime -= nValue;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	

	/*aNumber[0] = g_nTime / 100000000 / 10000000;
	aNumber[1] = g_nTime % 10000000 / 1000000;
	aNumber[2] = g_nTime % 1000000 / 100000;*/
	aNumber[0] = g_nTime / 60 % 1000/ 100;
	aNumber[1] = g_nTime / 60 % 100 / 10;
	aNumber[2] = g_nTime / 60 % 10 / 1;
	//aNumber[6] = g_nTime % 100 / 10;
	//aNumber[7] = g_nTime % 10 / 1;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntScore = 0; nCntScore < MAX_TIME_NUMBER; nCntScore++)
	{//�X�R�A�J�E���g
	 //�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();

	FADE pFade;
		pFade = *GetFade();
	if (g_nTime <= 0)
	{
		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RESULT);
		}
	}


}


