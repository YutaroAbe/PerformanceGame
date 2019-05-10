//=========================================================================================================//
//
// [�e����]->�e�ړ�:�������� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "camera.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define EXPLOSION_VERTEX_NUM		(4)					// ���_�̐�
#define EXPLOSION_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define EXPLOSION_MAX_TEX			(6)
#define EXPLOSION_TextureName		"data/TEXTURE/pipo-btleffect008.png"
#define EXPLOSION_TextureName1		"data/TEXTURE/bulleteffect000.png"
#define EXPLOSION_TextureName2		"data/TEXTURE/starburst_640x480.png"
#define EXPLOSION_TextureName3		"data/TEXTURE/EXP_GAGE.jpg"
#define EXPLOSION_TextureName4		"data/TEXTURE/frameeffects002m.png"
#define EXPLOSION_TextureName5		"data/TEXTURE/pipo-btleffect128.png"
#define	MAX_EXPLOSION				(80)		// �e�̍ő吔
#define HALFEXPLOSION				(30)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 Interval;	//�Ԋu
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	//�F
	EXPLOSIONSTATE state;
	int nLengthX;		//X�̒���
	int nLengthY;		//Y�̒���
	int nCntAnim;		//Animation�̃J�E���g
	int nPtnAnim;		//�w�肳�ꂽ���W�ŕ\��
	int nPtnHeight;		//�摜�̏c�̕�����
	int nPtnWide;		//�摜�̉��̕�����
	int nPtnSpeed;		//Animation���x
	int nType;			//�摜�̎w��
	float steep;		//�|���S���̊p�x
	ANIMATION anim;		//�A�j���[�V�����̎g����
	int	nView;			//�`����@
	bool bUse;
}Explosin;

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9			g_pTextureExplosion[EXPLOSION_MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffExplosion = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Explosin					g_aExplosion[MAX_EXPLOSION];					//�ő��Animation��

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//g_aExplosion[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aExplosion[nCntBullet].col = { 1.0f, 1.0f, 1.0f, };
		//g_aExplosion[nCntBullet].nCntAnim = -1;
		//g_aExplosion[nCntBullet].nPtnAnim = -1;
		//g_aExplosion[nCntBullet].nType = 0;
		g_aExplosion[nCntBullet].bUse = false;
	}

	//TEXTURE�ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName, &g_pTextureExplosion[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName1, &g_pTextureExplosion[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName2, &g_pTextureExplosion[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName3, &g_pTextureExplosion[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName4, &g_pTextureExplosion[4]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName5, &g_pTextureExplosion[5]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EXPLOSION_VERTEX_NUM * MAX_EXPLOSION,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
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
		//pVtx[nCntBullet * 4].col = D3DCOLOR_RGBA(0,0,0, 255);	// A = �����x
		//pVtx[nCntBullet * 4 + 1].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 2].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 3].col = D3DCOLOR_RGBA(0,0,0, 255);

		//�e�N�X�`�����W�ݒ�
		//pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitExplosion(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < EXPLOSION_MAX_TEX; nCntTexture++)
	{
		if (g_pTextureExplosion[nCntTexture] != NULL)
		{
			g_pTextureExplosion[nCntTexture]->Release();
			g_pTextureExplosion[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateExplosion(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		if (g_aExplosion[nCntBullet].bUse == true && g_aExplosion[nCntBullet].state != EXPLOSIONSTATE_LOAD)
		{//�e��O�ɔ�΂�
		 //MessageBox(0, "�{�������H", "�I��", MB_YESNO);
			if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_DELETE)
			{//�����Ă���
				g_aExplosion[nCntBullet].col.a -= 0.05f;
				if (g_aExplosion[nCntBullet].col.a <= 0.0f) { g_aExplosion[nCntBullet].bUse = false; }
			}
			if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_FADE)
			{//�o�Ă���
				if (g_aExplosion[nCntBullet].col.a < 1.0f) { g_aExplosion[nCntBullet].col.a += 0.01f; }
			}

			g_aExplosion[nCntBullet].nCntAnim++;

			if (g_aExplosion[nCntBullet].nCntAnim % g_aExplosion[nCntBullet].nPtnSpeed == 0)
			{
				g_aExplosion[nCntBullet].nPtnAnim++;
				if (g_aExplosion[nCntBullet].nPtnAnim >= g_aExplosion[nCntBullet].nPtnHeight * g_aExplosion[nCntBullet].nPtnWide && g_aExplosion[nCntBullet].anim != ANIMATION_LOOP)
				{//�S��1��\�������������
					g_aExplosion[nCntBullet].bUse = false;
				}
			}
		}
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawExplosion(void)
{
	Camera *pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	int nView = 0;
	float fPercent;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == true)
		{
			if (nView != g_aExplosion[nCntBullet].nView)
			{
				switch (g_aExplosion[nCntBullet].nView)
				{
				case 0: //�ʏ�
					// ���u�����f�B���O�����ɖ߂�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					break;
				case 1:	//���Z����
					// ���u�����f�B���O�����Z�����ɐݒ�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, 2);
					break;
				}
				nView = g_aExplosion[nCntBullet].nView;
			}

			if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_GAGE)
			{//�L�т镪 * (�ő咷�� / ����) 0.0���� +�{����
				if (pCamera[0].state == CAMERA_STATE_GAME)
				{
					g_aExplosion[nCntBullet].col.a = 1.0f;
					pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), g_aExplosion[nCntBullet].pos.y + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
					pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
					pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x, g_aExplosion[nCntBullet].pos.y, 0.0f);
					pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), 0.0f);

					fPercent = g_aExplosion[nCntBullet].nLengthY / 170.0f;
					if (fPercent > 1.0f) { fPercent = 1.0f; }
					fPercent -= 1.0f;
					pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) - ((1.0f / g_aExplosion[nCntBullet].nPtnHeight) * fPercent));
					pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) - ((1.0f / g_aExplosion[nCntBullet].nPtnHeight) * fPercent));
					pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
					pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
				}
				else { g_aExplosion[nCntBullet].col.a = 0.0f; }
			}
			else
			{
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);

				pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
				pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
				pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
				pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
			}
			//�J���[�ݒ�
			pVtx[nCntBullet * 4].col = g_aExplosion[nCntBullet].col;	// A = �����x
			pVtx[nCntBullet * 4 + 1].col = g_aExplosion[nCntBullet].col;
			pVtx[nCntBullet * 4 + 2].col = g_aExplosion[nCntBullet].col;
			pVtx[nCntBullet * 4 + 3].col = g_aExplosion[nCntBullet].col;

			// �e�N�X�`���̐ݒ� �|���S���̕`��
			pDevice->SetTexture(0, g_pTextureExplosion[g_aExplosion[nCntBullet].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, EXPLOSION_PRIMITIVE_NUM);
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffExplosion->Unlock();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
int SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col , int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, ANIMATION anim, EXPLOSIONSTATE state, float steep, int nView)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == false)
		{
			g_aExplosion[nCntBullet].steep = steep;
			g_aExplosion[nCntBullet].pos = pos;
			g_aExplosion[nCntBullet].Interval = Interval;
			g_aExplosion[nCntBullet].col = col;
			g_aExplosion[nCntBullet].state = state;
			g_aExplosion[nCntBullet].nCntAnim = -1;
			g_aExplosion[nCntBullet].nPtnAnim = -1;
			g_aExplosion[nCntBullet].nPtnHeight = nPtnHeight;
			g_aExplosion[nCntBullet].nPtnWide = nPtnWide;
			g_aExplosion[nCntBullet].nPtnSpeed = nPtnSpeed;
			g_aExplosion[nCntBullet].nLengthX = nLengthX;
			g_aExplosion[nCntBullet].nLengthY = nLengthY;
			g_aExplosion[nCntBullet].nType = nType;
			g_aExplosion[nCntBullet].anim = anim;
			g_aExplosion[nCntBullet].nView = nView;
			g_aExplosion[nCntBullet].bUse = true;
			break;
		}
	}
	return nCntBullet;
}
//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void ExplosionScroll(D3DXVECTOR3 move)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == true)
		{//�X�N���[��
			g_aExplosion[nCntBullet].pos += move;
		}
	}
}
//=========================================================================================================//
// * �SAnimation�j������
//=========================================================================================================//
void BreakExplosion(void)
{
	int nCntAnim;

	for (nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		g_aExplosion[nCntAnim].bUse = false;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void CheckEXP(float fEXP, float fMaxEXP, int nCntExplosion)
{
	float fPercent = fEXP / fMaxEXP;

	//�o���l�̃p�[�Z���e�[�W��100�����߂��Ă���Ζ߂�
	if (fPercent > 1.0) { fPercent = 1.0f; }
	g_aExplosion[nCntExplosion].nLengthY = (int)(170.0f * fPercent);
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void ChangeExplosion(int nCntExplosion, EXPLOSIONSTATE state)
{
	g_aExplosion[nCntExplosion].state = state;
}
