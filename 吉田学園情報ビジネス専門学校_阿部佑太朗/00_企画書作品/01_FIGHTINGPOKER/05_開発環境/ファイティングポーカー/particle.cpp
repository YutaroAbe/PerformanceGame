//=============================================================================
//
// �p�[�e�B�N������ [PARTICLE.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_PARTICLE					(10000)									// �p�[�e�B�N���̍ő吔
#define	TEXTURE_PARTICLE_NAME_000 "data/TEXTURE/PARTICL/darkmatter.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PARTICLE_NAME_001	"data/TEXTURE/PARTICL/stone.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TEX						(PARTICLETYPE_MAX)

//	�_�[�N�}�^�[
#define DARK_COL_000			(D3DXCOLOR(0.6f, 0.0f, 0.0f, 0.8f))				//	[�@�_�[�N�}�^�[�@]�F1
#define DARK_COL_001			(D3DXCOLOR(0.6f, 0.8f, 0.0f, 0.5f))				//	[�@�_�[�N�}�^�[�@]�F2
#define DARK_COL_002			(D3DXCOLOR(0.6f, 1.0f, 1.0f, 0.3f))				//	[�@�_�[�N�}�^�[�@]�F3
#define DARK_NUM_TEX			(1)												//	[�@�_�[�N�}�^�[�@]�e�N�X�`���ԍ�
#define DARK_POLIGON_MAX		(50)											//	[�@�_�[�N�}�^�[�@]�|���S���̐�
#define DARK_LIFE				(60)											//	[�@�_�[�N�}�^�[�@]����
#define DARK_RDIUS				((rand() % 10 + 1) * 1.0f)						//	[�@�_�[�N�}�^�[�@]���a
#define DARK_MOVE_X				(sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1))
#define DARK_MOVE_Y				(cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1))

//	�����@
#define STONE_NUM_TEX			(2)												//	[�@���� ]�e�N�X�`���ԍ�
#define STONE_POLIGON_MAX		(50)											//	[�@���� ]�|���S���̐�
#define STONE_LIFE				((rand() % 50) + 1)								//	[�@���� ]����
#define STONE_RDIUS				((rand() % 6 + 1) * 1.0f)						//	[�@���� ]���a
#define STONE_NUM1_MOVE_X		(sinf((rand() % 314 / 2) / 100.0f) * ((rand() % 3) + 1))
#define STONE_NUM1_MOVE_Y		(cosf((rand() % 314 / 2) / 100.0f) * ((rand() % 3) + 1))
#define STONE_NUM2_MOVE_X		(sinf((rand() % -314 / 2) / -100.0f) * ((rand() % 3) + 1))
#define STONE_NUM2_MOVE_Y		(cosf((rand() % -314 / 2) / -100.0f) * ((rand() % 3) + 1))

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9				g_pTexturePARTICLE[MAX_TEX] = {};				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffPARTICLE = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
PARTICLE						g_aPARTICLE[MAX_PARTICLE];						// �p�[�e�B�N���̏��

//=============================================================================
// �p�[�e�B�N������������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PARTICLE_NAME_000, &g_pTexturePARTICLE[PARTICLETYPE_DARKMATTER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PARTICLE_NAME_001, &g_pTexturePARTICLE[PARTICLETYPE_STONE]);
	MakeVertexParticle(pDevice);
}

//=============================================================================
// �p�[�e�B�N���I������
//=============================================================================
void UninitParticle(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturePARTICLE[nCnt] != NULL)
		{
			g_pTexturePARTICLE[nCnt]->Release();
			g_pTexturePARTICLE[nCnt] = NULL;
		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPARTICLE != NULL)
	{
		g_pVtxBuffPARTICLE->Release();
		g_pVtxBuffPARTICLE = NULL;
	}
}

//=============================================================================
// �p�[�e�B�N���X�V����
//=============================================================================
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPARTICLE->Lock(0,0,(void**)&pVtx,0);

	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{// �p�[�e�B�N�����J�E���g
		if (g_aPARTICLE[nCntPARTICLE].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���ꍇ
			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
			{// �_�[�N�}�^�[�p�[�e�B�N���̏ꍇ
				g_aPARTICLE[nCntPARTICLE].pos += g_aPARTICLE[nCntPARTICLE].move;	// �ړ��l���
				g_aPARTICLE[nCntPARTICLE].nLife--;									// ��������
				// ���a����
				if (g_aPARTICLE[nCntPARTICLE].nLife > 0)
				{
					g_aPARTICLE[nCntPARTICLE].fRadius += 0.005f;
				}
				else
				{
					g_aPARTICLE[nCntPARTICLE].fRadius -= 0.5f;
				}

				if (g_aPARTICLE[nCntPARTICLE].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aPARTICLE[nCntPARTICLE].bUse = false;
				}
			}
			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_STONE)
			{// �΃p�[�e�B�N���̏ꍇ
				g_aPARTICLE[nCntPARTICLE].pos += g_aPARTICLE[nCntPARTICLE].move;	// �ړ��l���
				g_aPARTICLE[nCntPARTICLE].nLife--;									// ��������
																					// ���a����
				if (g_aPARTICLE[nCntPARTICLE].nLife > 0)
				{
					g_aPARTICLE[nCntPARTICLE].fRadius += 0.005f;
				}
				else
				{
					g_aPARTICLE[nCntPARTICLE].fRadius -= 0.5f;
				}

				if (g_aPARTICLE[nCntPARTICLE].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aPARTICLE[nCntPARTICLE].bUse = false;
				}
			}
		}
		// ���_�ݒ�
		pVtx[nCntPARTICLE * 4].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius,g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 1].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 2].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius, -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
		pVtx[nCntPARTICLE * 4 + 3].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius,  -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPARTICLE->Unlock();
}

//=============================================================================
// �p�[�e�B�N���`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//�v�Z�p�}�g���b�N�X
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aPARTICLE[nCntPARTICLE].mtxWorld);
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aPARTICLE[nCntPARTICLE].mtxWorld._11 = mtxView._11;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._12 = mtxView._21;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._13 = mtxView._31;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._21 = mtxView._12;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._22 = mtxView._22;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._23 = mtxView._32;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._31 = mtxView._13;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._32 = mtxView._23;
		g_aPARTICLE[nCntPARTICLE].mtxWorld._33 = mtxView._33;
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPARTICLE[nCntPARTICLE].rot.y, g_aPARTICLE[nCntPARTICLE].rot.x, g_aPARTICLE[nCntPARTICLE].rot.z);
		D3DXMatrixMultiply(&g_aPARTICLE[nCntPARTICLE].mtxWorld, &g_aPARTICLE[nCntPARTICLE].mtxWorld, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aPARTICLE[nCntPARTICLE].pos.x, g_aPARTICLE[nCntPARTICLE].pos.y, g_aPARTICLE[nCntPARTICLE].pos.z);
		D3DXMatrixMultiply(&g_aPARTICLE[nCntPARTICLE].mtxWorld, &g_aPARTICLE[nCntPARTICLE].mtxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aPARTICLE[nCntPARTICLE].mtxWorld);
		//�A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						//��l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//��r���@�i���傫���j�j
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);		//��r���@�i���傫���j�j
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPARTICLE, 0, sizeof(VERTEX_3D));
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aPARTICLE[nCntPARTICLE].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePARTICLE[g_aPARTICLE[nCntPARTICLE].nTypeTx]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPARTICLE * 4, 2);
		}
		//�A���t�@�l��߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
}

//=============================================================================
// 	�p�[�e�B�N���̐ݒ�
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, PARTICLETYPE Type)
{
	int nCount = 0;			// �p�[�e�B�N�����J�E���^
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPARTICLE->Lock(0,0,(void**)&pVtx,0);
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++, pVtx += 4)
	{// �p�[�e�B�N�����J�E���g
		if (g_aPARTICLE[nCntPARTICLE].bUse == false)
		{// �p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aPARTICLE[nCntPARTICLE].pos = pos;											// �ʒu
			g_aPARTICLE[nCntPARTICLE].Type = Type;											// ��ސݒ�
			g_aPARTICLE[nCntPARTICLE].bUse = true;											// �g�p���Ă�����

			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
			{//	[�_�[�N�}�^�[]
				g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);			// �J���[
				g_aPARTICLE[nCntPARTICLE].nTypeTx = DARK_NUM_TEX;							// ��ސݒ�
				g_aPARTICLE[nCntPARTICLE].nSetMax = DARK_POLIGON_MAX;						//�|���S���̐�
				g_aPARTICLE[nCntPARTICLE].nLife = DARK_LIFE;								// �����ݒ�
				// �ړ������_����
				g_aPARTICLE[nCntPARTICLE].move.x = DARK_MOVE_X;
				g_aPARTICLE[nCntPARTICLE].move.y = DARK_MOVE_Y;
				int nNumber = rand() % 3 + 1;
				if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_DARKMATTER)
				{
					if (nNumber == 1) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_000; }
					if (nNumber == 2) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_001; }
					if (nNumber == 3) { g_aPARTICLE[nCntPARTICLE].col = DARK_COL_002; }
				}
				g_aPARTICLE[nCntPARTICLE].fRadius = DARK_RDIUS;								// ���a�ݒ�
			}

			if (g_aPARTICLE[nCntPARTICLE].Type == PARTICLETYPE_STONE)
			{//	[��]
				g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);			// �J���[
				g_aPARTICLE[nCntPARTICLE].nTypeTx = STONE_NUM_TEX;							// ��ސݒ�
				g_aPARTICLE[nCntPARTICLE].nSetMax = STONE_POLIGON_MAX;
				g_aPARTICLE[nCntPARTICLE].nLife = (STONE_LIFE);								// �����ݒ�
				int nNumber = rand() % 2 + 1;
				// �ړ������_����
				if (nNumber == 1)
				{
					g_aPARTICLE[nCntPARTICLE].move.x = STONE_NUM1_MOVE_X;
					g_aPARTICLE[nCntPARTICLE].move.y = STONE_NUM1_MOVE_Y;
				}
				if (nNumber == 2)
				{
					g_aPARTICLE[nCntPARTICLE].move.x = STONE_NUM2_MOVE_X;
					g_aPARTICLE[nCntPARTICLE].move.y = STONE_NUM2_MOVE_Y;
				}

				g_aPARTICLE[nCntPARTICLE].fRadius = STONE_RDIUS;							// ���a�ݒ�
			}
			// ���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius,  -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, -g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPARTICLE[nCntPARTICLE].fRadius, g_aPARTICLE[nCntPARTICLE].fRadius, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[0].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[1].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[2].col = g_aPARTICLE[nCntPARTICLE].col;
			pVtx[3].col = g_aPARTICLE[nCntPARTICLE].col;
			nCount++;		// �����J�E���g
			if ( nCount == g_aPARTICLE[nCntPARTICLE].nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPARTICLE->Unlock();
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{// �p�[�e�B�N�����J�E���g
		g_aPARTICLE[nCntPARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�[�e�B�N�����S�l
		g_aPARTICLE[nCntPARTICLE].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�[�e�B�N�����S�l
		g_aPARTICLE[nCntPARTICLE].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�[�e�B�N���ړ��l
		g_aPARTICLE[nCntPARTICLE].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �p�[�e�B�N���F
		g_aPARTICLE[nCntPARTICLE].Type = PARTICLETYPE_NONE;						// �p�[�e�B�N����ސݒ�
		g_aPARTICLE[nCntPARTICLE].nTypeTx;										// �p�[�e�B�N���e�N�X�`����ސݒ�
		g_aPARTICLE[nCntPARTICLE].fRadius = 0.0f;								// �p�[�e�B�N�����a
		g_aPARTICLE[nCntPARTICLE].nLife = 0;									// �p�[�e�B�N������
		g_aPARTICLE[nCntPARTICLE].bUse = false;									// �p�[�e�B�N���g�p���Ă��Ȃ����
	}
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffPARTICLE, NULL);
	// ���_���̍쐬
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntPARTICLE = 0; nCntPARTICLE < MAX_PARTICLE; nCntPARTICLE++)
	{
	 // ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPARTICLE->Unlock();
}
