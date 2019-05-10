//=========================================================================================================//
//
// [�e����]->�e�ړ����� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"				//�������ĂԂ���

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define BULLET_VERTEX_NUM			(4)					// ���_�̐�
#define BULLET_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define BULLET_MAX_Texture			(1)					//�摜�̎��
#define BULLET_TextureName		"data/TEXTURE/Digital000.png"
#define	MAX_BULLET					(256)				// �e�̍ő吔

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureDigital[BULLET_MAX_Texture] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDigital = NULL;	// ���_�o�b�t�@�ւ̃|�C���^		

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitDigital(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	DIGITAL *g_aDigital = GetDigital();

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//g_aBullet[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aBullet[nCntBullet].steep = 0.0f;
		//g_aBullet[nCntBullet].nType = 0;
		//g_aBullet[nCntBullet].nAtkType = 0;
		//g_aBullet[nCntBullet].nShot = 0;
		//g_aBullet[nCntBullet].nLengthX = 0;
		//g_aBullet[nCntBullet].nLengthY = 0;
		g_aDigital[nCntBullet].bUse = false;
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TextureName, &g_pTextureDigital[0]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * BULLET_VERTEX_NUM * MAX_BULLET,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffDigital,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDigital->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntBullet * 4].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 1].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 2].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 3].rhw = 1.0f;

		////�J���[�ݒ�
		pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = �����x
		pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�ݒ�
		pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffDigital->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitDigital(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < BULLET_MAX_Texture; nCntTexture++)
	{
		if (g_pTextureDigital[nCntTexture] != NULL)
		{
			g_pTextureDigital[nCntTexture]->Release();
			g_pTextureDigital[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffDigital != NULL)
	{
		g_pVtxBuffDigital->Release();
		g_pVtxBuffDigital = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateDigital(void)
{
	int nCntDigital;
	DIGITAL *g_aDigital = GetDigital();
	for (nCntDigital = 0; nCntDigital < MAX_BULLET; nCntDigital++)
	{
		if (g_aDigital[nCntDigital].bUse == true)
		{
			switch (g_aDigital[nCntDigital].state)
			{
			case DIGITALSTATE_NONE:
				g_aDigital[nCntDigital].col.a -= 0.0035f;
				if (g_aDigital[nCntDigital].col.a < 0.0f) { g_aDigital[nCntDigital].bUse = false; }
				break;
			case DIGITALSTATE_WAVE:
				if (g_aDigital[nCntDigital].nCntstate == 0)
				{//�W�����v+������
					g_aDigital[nCntDigital].col.a = 0.5f;
					g_aDigital[nCntDigital].move.y = -7.0f;
				}
				if(g_aDigital[nCntDigital].nCntstate <= 0)
				{//FADE+�d��
					if (g_aDigital[nCntDigital].col.a != 1.0f)
					{//��������
						g_aDigital[nCntDigital].col.a += 0.01f;
						if (g_aDigital[nCntDigital].col.a > 1.0f) { g_aDigital[nCntDigital].col.a = 1.0f; }
					}
					g_aDigital[nCntDigital].move.y += 0.35f;
					g_aDigital[nCntDigital].pos += g_aDigital[nCntDigital].move;
					if (g_aDigital[nCntDigital].pos.y > g_aDigital[nCntDigital].fHeight)
					{ 
						g_aDigital[nCntDigital].pos.y = g_aDigital[nCntDigital].fHeight;
						g_aDigital[nCntDigital].col.a -= 0.025f;
						if (g_aDigital[nCntDigital].col.a < 0.0f) { g_aDigital[nCntDigital].bUse = false; }
					}
				}
				g_aDigital[nCntDigital].nCntstate--;
				break;
			case DIGITALSTATE_WAVE0:
				if (g_aDigital[nCntDigital].nCntstate == 0)
				{//�W�����v+������
					g_aDigital[nCntDigital].col.a = 0.5f;
					g_aDigital[nCntDigital].move.y = -7.0f;
				}
				if (g_aDigital[nCntDigital].nCntstate <= 0)
				{//FADE+�d��
					if (g_aDigital[nCntDigital].col.a != 1.0f)
					{//��������
						g_aDigital[nCntDigital].col.a += 0.01f;
						if (g_aDigital[nCntDigital].col.a > 1.0f) { g_aDigital[nCntDigital].col.a = 1.0f; }
					}
					g_aDigital[nCntDigital].move.y += 0.35f;
					g_aDigital[nCntDigital].pos += g_aDigital[nCntDigital].move;
					if (g_aDigital[nCntDigital].pos.y > g_aDigital[nCntDigital].fHeight)
					{
						g_aDigital[nCntDigital].pos.y = g_aDigital[nCntDigital].fHeight;
						g_aDigital[nCntDigital].nCntstate = 60;
						//if (g_aDigital[nCntDigital].col.a < 0.0f) { g_aDigital[nCntDigital].bUse = false; }
					}
				}
				g_aDigital[nCntDigital].nCntstate--;
				break;
			case DIGITALSTATE_DAMAGE:
				if (g_aDigital[nCntDigital].nCntstate <= 0)
				{//�ړ�
					if (g_aDigital[nCntDigital].col.a != 1.0f)
					{//��������
						g_aDigital[nCntDigital].col.a += 0.06f;
						g_aDigital[nCntDigital].pos.y += 14.0f;
						g_aDigital[nCntDigital].pos.x += 20.0f;

						if (g_aDigital[nCntDigital].col.a > 1.0f)
						{ 
							g_aDigital[nCntDigital].col.a = 1.0f;
							g_aDigital[nCntDigital].nCntstate = 9999;
						}
					}
				}
				if(g_aDigital[nCntDigital].nCntstate != 9999){ g_aDigital[nCntDigital].nCntstate--; }
				else
				{//�~�܂�����
					g_aDigital[nCntDigital].col.a -= 0.01f;
					if (g_aDigital[nCntDigital].col.a < 0.7f)
					{ 
						g_aDigital[nCntDigital].pos.y += 2.8f;
						g_aDigital[nCntDigital].pos.x += 4.0f;
					}
					if (g_aDigital[nCntDigital].col.a < 0.0f) { g_aDigital[nCntDigital].bUse = false; }
				}
				break;
			case DIGITALSTATE_HEEL:
				if (g_aDigital[nCntDigital].nCntstate <= 0)
				{//�ړ�
					if (g_aDigital[nCntDigital].col.a != 1.0f)
					{//��������
						g_aDigital[nCntDigital].col.a += 0.06f;
						g_aDigital[nCntDigital].pos.y -= 14.0f;
						g_aDigital[nCntDigital].pos.x -= 20.0f;

						if (g_aDigital[nCntDigital].col.a > 1.0f)
						{
							g_aDigital[nCntDigital].col.a = 1.0f;
							g_aDigital[nCntDigital].nCntstate = 9999;
						}
					}
				}
				if (g_aDigital[nCntDigital].nCntstate != 9999) { g_aDigital[nCntDigital].nCntstate--; }
				else
				{//�~�܂�����
					g_aDigital[nCntDigital].col.a -= 0.01f;
					if (g_aDigital[nCntDigital].col.a < 0.7f)
					{
						g_aDigital[nCntDigital].pos.y -= 2.8f;
						g_aDigital[nCntDigital].pos.x -= 4.0f;
					}
					if (g_aDigital[nCntDigital].col.a < 0.0f) { g_aDigital[nCntDigital].bUse = false; }
				}
				break;
			}
		}
	}
}

//=========================================================================================================//
// * �e�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawDigital(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	DIGITAL *g_aDigital = GetDigital();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffDigital, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// �|���S���̕`��

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDigital->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aDigital[nCntBullet].bUse == true)
		{
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aDigital[nCntBullet].pos.x - g_aDigital[nCntBullet].nLengthX, g_aDigital[nCntBullet].pos.y - g_aDigital[nCntBullet].nLengthY, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aDigital[nCntBullet].pos.x + g_aDigital[nCntBullet].nLengthX, g_aDigital[nCntBullet].pos.y - g_aDigital[nCntBullet].nLengthY, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aDigital[nCntBullet].pos.x - g_aDigital[nCntBullet].nLengthX, g_aDigital[nCntBullet].pos.y + g_aDigital[nCntBullet].nLengthY, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aDigital[nCntBullet].pos.x + g_aDigital[nCntBullet].nLengthX, g_aDigital[nCntBullet].pos.y + g_aDigital[nCntBullet].nLengthY, 0.0f);

			pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aDigital[nCntBullet].nDigital % 5) * (1.0f / 5), (g_aDigital[nCntBullet].nDigital / 5) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aDigital[nCntBullet].nDigital % 5) * (1.0f / 5) + (1.0f / 5), (g_aDigital[nCntBullet].nDigital / 5) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aDigital[nCntBullet].nDigital % 5) * (1.0f / 5), (g_aDigital[nCntBullet].nDigital / 5) * (1.0f / 2) + (1.0f / 2));
			pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aDigital[nCntBullet].nDigital % 5) * (1.0f / 5) + (1.0f / 5), (g_aDigital[nCntBullet].nDigital / 5) * (1.0f / 2) + (1.0f / 2));

			//�J���[�ݒ�
			pVtx[nCntBullet * 4].col = g_aDigital[nCntBullet].col;	// A = �����x
			pVtx[nCntBullet * 4 + 1].col = g_aDigital[nCntBullet].col;
			pVtx[nCntBullet * 4 + 2].col = g_aDigital[nCntBullet].col;
			pVtx[nCntBullet * 4 + 3].col = g_aDigital[nCntBullet].col;

			pDevice->SetTexture(0, g_pTextureDigital[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, BULLET_PRIMITIVE_NUM);
		}
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffDigital->Unlock();
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetDigital(D3DXVECTOR3 pos, D3DXCOLOR col, DIGITALSTATE state, int nLengthX, int nLengthY, int nDigital)
{
	int nCntDigital;			//�e������́`
	int nCntBit = 0;
	int nCenter;
	int nCntCenter;
	int nPow;
	int nBit;
	DIGITAL *g_aDigital = GetDigital();

	for (nCntCenter = 0, nCenter = nDigital; nCenter > 0; nCenter /= 10, nCntCenter++) {}
	nPow = nCntCenter - 1;
	nBit = (int)pow(10.0f, nCntCenter - 1);
	if (nBit == 0) { nBit = 1; }
	do
	{//����|���S�����o��
		for (nCntDigital = 0; nCntDigital < MAX_BULLET; nCntDigital++)
		{//���
			if (g_aDigital[nCntDigital].bUse == false)
			{
				g_aDigital[nCntDigital].pos = D3DXVECTOR3(pos.x + (nLengthX * 2 * nCntBit) - (nLengthX * nCntCenter),pos.y, 0.0f );
				g_aDigital[nCntDigital].fHeight = pos.y;
				g_aDigital[nCntDigital].state = state;
				g_aDigital[nCntDigital].nCntstate = nCntBit * 5;
				g_aDigital[nCntDigital].move = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
				g_aDigital[nCntDigital].col = col;
				g_aDigital[nCntDigital].nDigital = nDigital / nBit % 10;
				g_aDigital[nCntDigital].nLengthX = nLengthX;
				g_aDigital[nCntDigital].nLengthY = nLengthY;
				g_aDigital[nCntDigital].bUse = true;
				nBit /= 10;
				nCntBit++;
				break;
			}
		}
	} while (nBit > 0);
}

//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void DigitalScroll(D3DXVECTOR3 move)
{
	int nCntBullet;
	DIGITAL *g_aBullet = GetDigital();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true && g_aBullet[nCntBullet].state == DIGITALSTATE_WAVE)
		{//�X�N���[��
			g_aBullet[nCntBullet].pos += move;
			g_aBullet[nCntBullet].fHeight += move.y;
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void BreakDigital(void)
{
	int nCntBullet;
	DIGITAL *g_aBullet = GetDigital();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//g_aBullet[nCntBullet].bUse = false;
	}
}

//=============================================================================
// �e�̎擾
//=============================================================================
DIGITAL *GetDigital(void)
{
	static DIGITAL digital[MAX_BULLET];//�e�̍ő吔

	return &digital[0];
}