//=========================================================================================================================
//
// �^�C���̏��� [time.cpp]
// Author :�@YUTARO�@ABE
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "time.h"//�^�C��
#include "input.h"//�L�[�{�[�h
#include "fade.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MAX_TIME_NUMBER (7)
#define TEXTURE_TIME "data/TEXTURE/number000.png"// �ǂݍ��ރe�N�X�`���t�@�C����

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;// ���_�o�b�t�@�ւ̃|�C���^
int g_nTime;// �X�R�A
D3DXVECTOR3 g_posTime;
//int g_nCounterTimeState;

//=========================================================================================================================
// �X�R�A����������
//=========================================================================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�|�C���^
	float nCntTime;//�X�R�A�J�E���g
	float nTimePos;//�X�R�A�ʒu

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nTime = 2000;

	//�ʒu
	g_posTime = D3DXVECTOR3(750, 70, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_TIME,
		&g_pTextureTime
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUMBER ,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffTime,
								NULL
								);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0, nTimePos = 1100; nCntTime < 2; nCntTime++, g_posTime.x -= 40)
	{
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - 20.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 20.0f, g_posTime.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - 20.0f, g_posTime.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 20.0f, g_posTime.y + 20.0f, 0.0f);
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
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0,0,(void**)&pVtx,0);

	for (nCntTime = 0, nTimePos = 1200; nCntTime < 4 ; nCntTime++, g_posTime.x -= 50)
	{
		//���_�ݒ�
		pVtx[8].pos = D3DXVECTOR3(g_posTime.x - 30.0f, g_posTime.y - 30.0f, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posTime.x + 30.0f, g_posTime.y - 30.0f, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posTime.x - 30.0f, g_posTime.y + 30.0f, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posTime.x + 30.0f, g_posTime.y + 30.0f, 0.0f);
		//1.0f�ŌŒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;
		//���_�J���[�ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
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
	if (g_nTime <= 0)
	{
		SetGemeState(GAMESTATE_END);

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
	int nCntTime;
	int nTexData;

	g_nTime -= nValue ;//�^�C������
	nTexData = g_nTime;//�^�C�����i�[

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTime->Lock(0,0,(void**)&pVtx,0);

		for (nCntTime = 0; nCntTime < MAX_TIME_NUMBER; nCntTime++)
		{//�X�R�A�J�E���g
		 //�e�N�X�`���ݒ�
			pVtx[nCntTime * 4].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 1].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 0.0f);
			pVtx[nCntTime * 4 + 2].tex = D3DXVECTOR2((nTexData % 10) * 0.1f, 1.0f);
			pVtx[nCntTime * 4 + 3].tex = D3DXVECTOR2((nTexData % 10) * 0.1f + 0.1f, 1.0f);
			nTexData /= 10;
		}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTime->Unlock();
}


