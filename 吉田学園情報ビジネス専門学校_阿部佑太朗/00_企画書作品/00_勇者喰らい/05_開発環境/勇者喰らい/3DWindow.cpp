//=========================================================================================================//
//
// [�e����]->�e�ړ�:�������� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "input.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define EXPLOSION_VERTEX_NUM		(4)					// ���_�̐�
#define EXPLOSION_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define EXPLOSION_MAX_TEX			(5)
#define EXPLOSION_TextureName		"data/TEXTURE/GAGE000.jpg"
#define EXPLOSION_TextureName1		"data/TEXTURE/Lock_On001.png"
#define EXPLOSION_TextureName2		"data/TEXTURE/Lock_On100.png"
#define EXPLOSION_TextureName3		"data/TEXTURE/maxresdefault.jpg"
#define EXPLOSION_TextureName4		"data/TEXTURE/explosion.jpg"
#define	MAX_EXPLOSION				(1280)		// �e�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ʒu
	D3DXCOLOR col;	//�F
	WINDOWSTATE state;
	float		fCntState;
	int nType;			//�摜�̎w��
	int nView;
	float fLengthX;		//X�̒���
	float fLengthY;		//Y�̒���
	float fAngle;		//Z���̊p�x
	D3DXMATRIX mtxWorldBillBoord;	//���[���h�}�g���b�N�X
	bool bUse;

}ZWindow;

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9			g_pTextureZWindow[EXPLOSION_MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffZWindow = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
ZWindow						g_aZWindow[MAX_EXPLOSION];					//�ő��Animation��

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitZWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBullet;

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//g_aExplosion[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aExplosion[nCntBullet].col = { 1.0f, 1.0f, 1.0f, };
		//g_aExplosion[nCntBullet].nCntAnim = -1;
		//g_aExplosion[nCntBullet].nPtnAnim = -1;
		//g_aExplosion[nCntBullet].nType = 0;
		g_aZWindow[nCntBullet].bUse = false;
	}

	//TEXTURE�ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName, &g_pTextureZWindow[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName1, &g_pTextureZWindow[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName2, &g_pTextureZWindow[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName3, &g_pTextureZWindow[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName4, &g_pTextureZWindow[4]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * EXPLOSION_VERTEX_NUM * MAX_EXPLOSION,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffZWindow,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffZWindow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		pVtx[nCntBullet * 4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[nCntBullet * 4 + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[nCntBullet * 4 + 2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[nCntBullet * 4 + 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�e�N�X�`�����W�ݒ�
		pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffZWindow->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitZWindow(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	BreakZWindow();

	for (nCntTexture = 0; nCntTexture < EXPLOSION_MAX_TEX; nCntTexture++)
	{
		if (g_pTextureZWindow[nCntTexture] != NULL)
		{
			g_pTextureZWindow[nCntTexture]->Release();
			g_pTextureZWindow[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffZWindow != NULL)
	{
		g_pVtxBuffZWindow->Release();
		g_pVtxBuffZWindow = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateZWindow(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aZWindow[nCntBullet].bUse == true)
		{
			g_aZWindow[nCntBullet].pos += g_aZWindow[nCntBullet].move;

			switch (g_aZWindow[nCntBullet].state)
			{
			case WINDOWSTATE_Delete0:
				g_aZWindow[nCntBullet].bUse = false; break;

			case WINDOWSTATE_STAMINAGAGE:
			case WINDOWSTATE_MAXSTAMINAGAGE:
				if (g_aZWindow[nCntBullet].fCntState > 0.0f)
				{//�X�^�~�i�Q�[�W���g�p����Ă���Ȃ�
					if (g_aZWindow[nCntBullet].col.a == 1.0f) { g_aZWindow[nCntBullet].fCntState -= 1.0f; }
					else
					{
						g_aZWindow[nCntBullet].col.a += 0.08f;
						if (g_aZWindow[nCntBullet].col.a >= 1.0f) { g_aZWindow[nCntBullet].col.a = 1.0f; }
					}
				}
				else
				{//���񂾂������
					if (g_aZWindow[nCntBullet].col.a != 0.0f)
					{
						g_aZWindow[nCntBullet].col.a -= 0.08f;
						if (g_aZWindow[nCntBullet].col.a <= 0.0f) { g_aZWindow[nCntBullet].col.a = 0.0f; }
					}
				}
				break;

			case WINDOWSTATE_FADE_Z:
				g_aZWindow[nCntBullet].fLengthX *= 1.01f;
				g_aZWindow[nCntBullet].fLengthY *= 1.01f;
			case WINDOWSTATE_FADEOUT:
				if (g_aZWindow[nCntBullet].col.a != 0.0f)
				{
					g_aZWindow[nCntBullet].col.a -= g_aZWindow[nCntBullet].fCntState;
					if (g_aZWindow[nCntBullet].col.a <= 0.0f) { g_aZWindow[nCntBullet].bUse = false; }
				}
				break;
			}//swich
		}//bUse
	}//for
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawZWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//�v�Z�p�}�g���b�N�X
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^
	int nView = 0;

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffZWindow->Lock(0, 0, (void**)&pVtx, 0);
	//�|���S���̕`��
	for (int nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		if (g_aZWindow[nCntAnim].bUse == true)
		{
			if (nView != g_aZWindow[nCntAnim].nView)
			{
				switch (g_aZWindow[nCntAnim].nView)
				{
				case 0: //�ʏ�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					break;
				case 1:	//���Z����
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, 2);
					break;
				case 2:	//���Z����
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
					//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				}
				nView = g_aZWindow[nCntAnim].nView;
			}

			//Z�e�X�g�̊m�F
			if(g_aZWindow[nCntAnim].nType != 0){ pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); }
			if (g_aZWindow[nCntAnim].state >= WINDOWSTATE_STAMINAGAGE && g_aZWindow[nCntAnim].state <= WINDOWSTATE_AUTOLIFEGAGE)
			{
				pVtx[nCntAnim * 4].pos = D3DXVECTOR3(0.0f, g_aZWindow[nCntAnim].fLengthY * 1.0f, 0.0f);
				pVtx[nCntAnim * 4 + 1].pos = D3DXVECTOR3(g_aZWindow[nCntAnim].fLengthX * 1.0f, g_aZWindow[nCntAnim].fLengthY * 1.0f, 0.0f);
				pVtx[nCntAnim * 4 + 2].pos = D3DXVECTOR3(0.0f, -g_aZWindow[nCntAnim].fLengthY * 1.0f, 0.0f);
				pVtx[nCntAnim * 4 + 3].pos = D3DXVECTOR3(g_aZWindow[nCntAnim].fLengthX * 1.0f, -g_aZWindow[nCntAnim].fLengthY * 1.0f, 0.0f);

				pVtx[nCntAnim * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[nCntAnim * 4 + 1].tex = D3DXVECTOR2((g_aZWindow[nCntAnim].fLengthX / 100.0f) * 1.0f, 0.0f);
				pVtx[nCntAnim * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[nCntAnim * 4 + 3].tex = D3DXVECTOR2((g_aZWindow[nCntAnim].fLengthX / 100.0f) * 1.0f, 1.0f);
			}

				pVtx[nCntAnim * 4].col = g_aZWindow[nCntAnim].col;	// A = �����x
				pVtx[nCntAnim * 4 + 1].col = g_aZWindow[nCntAnim].col;
				pVtx[nCntAnim * 4 + 2].col = g_aZWindow[nCntAnim].col;
				pVtx[nCntAnim * 4 + 3].col = g_aZWindow[nCntAnim].col;

		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aZWindow[nCntAnim].mtxWorldBillBoord);

			//�r���{�[�h
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s���ݒ�
			g_aZWindow[nCntAnim].mtxWorldBillBoord._11 = mtxView._11;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._12 = mtxView._21;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._13 = mtxView._31;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._21 = mtxView._12;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._22 = mtxView._22;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._23 = mtxView._32;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._31 = mtxView._13;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._32 = mtxView._23;
			g_aZWindow[nCntAnim].mtxWorldBillBoord._33 = mtxView._33;

			////if (g_aZWindow[nCntAnim].nType == 3)
			//{// ��]�𔽉f
			//	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, g_aZWindow[nCntAnim].fAngle);
			//	D3DXMatrixMultiply(&g_aZWindow[nCntAnim].mtxWorldBillBoord, &g_aZWindow[nCntAnim].mtxWorldBillBoord, &mtxRot);
			//}

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aZWindow[nCntAnim].pos.x, g_aZWindow[nCntAnim].pos.y, g_aZWindow[nCntAnim].pos.z);

			D3DXMatrixMultiply(&g_aZWindow[nCntAnim].mtxWorldBillBoord, &g_aZWindow[nCntAnim].mtxWorldBillBoord, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aZWindow[nCntAnim].mtxWorldBillBoord);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffZWindow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureZWindow[g_aZWindow[nCntAnim].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntAnim * 4, 2);

			//Z�e�X�g��߂�
			if (g_aZWindow[nCntAnim].nType != 0) { pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE); }
		}
	}
	pDevice->SetTexture(0, NULL);

	//���_BUFFER���A�����b�N����
	g_pVtxBuffZWindow->Unlock();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
int SetZWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col , float nLengthX, float nLengthY, int nType, int nView, WINDOWSTATE state, float fCntState)
{
	int nCntBullet;
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffZWindow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aZWindow[nCntBullet].bUse == false)
		{
			g_aZWindow[nCntBullet].pos = pos;
			g_aZWindow[nCntBullet].move = move;
			g_aZWindow[nCntBullet].col = col;
			g_aZWindow[nCntBullet].fLengthX = nLengthX;
			g_aZWindow[nCntBullet].fLengthY = nLengthY;
			g_aZWindow[nCntBullet].nType = nType;
			g_aZWindow[nCntBullet].nView = nView;
			g_aZWindow[nCntBullet].state = state;
			g_aZWindow[nCntBullet].fCntState = fCntState;
			g_aZWindow[nCntBullet].fAngle = (rand() % 314) * 0.01f;
			g_aZWindow[nCntBullet].bUse = true;

			if (nType == 0)
			{
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0.0f, g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aZWindow[nCntBullet].fLengthX * 1.0f, g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0.0f, -g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aZWindow[nCntBullet].fLengthX * 1.0f, -g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
			}
			else
			{
				pVtx[nCntBullet * 4].pos = D3DXVECTOR3(-g_aZWindow[nCntBullet].fLengthX * 1.0f, g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aZWindow[nCntBullet].fLengthX * 1.0f, g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(-g_aZWindow[nCntBullet].fLengthX * 1.0f, -g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
				pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aZWindow[nCntBullet].fLengthX * 1.0f, -g_aZWindow[nCntBullet].fLengthY * 1.0f, 0.0f);
			}
			pVtx[nCntBullet * 4].col = col;	// A = �����x
			pVtx[nCntBullet * 4 + 1].col = col;
			pVtx[nCntBullet * 4 + 2].col = col;
			pVtx[nCntBullet * 4 + 3].col = col;

			//�e�N�X�`�����W�ݒ�
			pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffZWindow->Unlock();

	return nCntBullet;
}
//=========================================================================================================//
// * �SAnimation�j������
//=========================================================================================================//
void BreakZWindow(void)
{
	int nCntAnim;

	for (nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		g_aZWindow[nCntAnim].bUse = false;
	}
}
//=========================================================================================================//
// * �ԍ��ŃQ�[�W�̍X�V
//=========================================================================================================//
void ChangeZWindow(int nCount, float fMax, float fMin, D3DXVECTOR3 pos, bool bUse)
{
	float fPlus;

	if (g_aZWindow[nCount].bUse == true)
	{
		float fPercent;
		if (fMin < 0.0f) { fMin = 0.0f; }
		//�ő�l����%�����߂�
		fPercent = fMin / fMax;
		if (fPercent > 1.0f) { fPercent = 1.0f; }
		if (g_aZWindow[nCount].state == WINDOWSTATE_LIFEGAGE) 
		{ 
			if (g_aZWindow[nCount].fLengthX > 50.0f * fPercent){ g_aZWindow[nCount].fLengthX = 50.0f * fPercent; }
			else
			{
				fPlus = (50.0f * fPercent - g_aZWindow[nCount].fLengthX) * 0.03f;
				if (fPlus < 50.0f * 0.002f) { fPlus = 50.0f * 0.002f; }
				g_aZWindow[nCount].fLengthX += fPlus;
				if (g_aZWindow[nCount].fLengthX > 50.0f * fPercent) { g_aZWindow[nCount].fLengthX = 50.0f * fPercent; }
			}
		}
		else if (g_aZWindow[nCount].state == WINDOWSTATE_AUTOLIFEGAGE)
		{ 
			if (g_aZWindow[nCount].fLengthX > 50.0f * fPercent)
			{
				g_aZWindow[nCount].fLengthX -= 50.0f * 0.002f;
				g_aZWindow[nCount].col = D3DXCOLOR(0.76f, 0.1f, 0.0f, 1.0f);
				if (g_aZWindow[nCount].fLengthX < 50.0f * fPercent) { g_aZWindow[nCount].fLengthX = 50.0f * fPercent; }
			}
			else if (g_aZWindow[nCount].fLengthX < 50.0f * fPercent)
			{ 
				g_aZWindow[nCount].fLengthX = 50.0f * fPercent;
				g_aZWindow[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else{ g_aZWindow[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		}
		else if (g_aZWindow[nCount].state == WINDOWSTATE_STAMINAGAGE)
		{
			g_aZWindow[nCount].fLengthX = 50.0f * fPercent;
			if(fPercent != 1.0f){ g_aZWindow[nCount].fCntState = 30.0f; }
		}
		else if (g_aZWindow[nCount].state == WINDOWSTATE_MAXSTAMINAGAGE)
		{
			if (fPercent != 1.0f) { g_aZWindow[nCount].fCntState = 30.0f; }
		}
		g_aZWindow[nCount].pos = pos;
		g_aZWindow[nCount].bUse = bUse;
	}
}
