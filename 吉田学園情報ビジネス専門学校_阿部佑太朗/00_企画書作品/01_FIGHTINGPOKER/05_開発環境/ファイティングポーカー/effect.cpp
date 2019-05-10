//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author :  YUTARO ABE
//
//=============================================================================
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	EFFECT_TEX_NAME1	"data/TEXTURE/EFFECT/effect000.jpg"			// �ǂݍ��ރe�N�X�`�� �K�[�h
#define	EFFECT_TEX_NAME2	"data/TEXTURE/EFFECT/effect001.jpg"			// �ǂݍ��ރe�N�X�`�� �q�b�g��
#define	EFFECT_TEX_NAME3	"data/TEXTURE/EFFECT/effect001.jpg"			// �ǂݍ��ރe�N�X�`�� �q�b�g��
#define	EFFECT_TEX_NAME4	"data/TEXTURE/EFFECT/smoke001.jpg"			// �ǂݍ��ރe�N�X�`�� ��[�W�����v��]
#define	EFFECT_TEX_NAME5	"data/TEXTURE/EFFECT/smoke002.jpg"			// �ǂݍ��ރe�N�X�`�� ��[���n��]
#define	MAX_EFFECT			(4096)										// �G�t�F�N�g�̍ő吔
#define EFFECT_TRANS		(0.3f)										// �G�t�F�N�g�̕ω���
//	�K�[�h
#define GUARD_MOVE			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[�@�K�[�h�@]����
#define GUARD_COL			(D3DXCOLOR(0.2f, 0.7f, 0.7f, 1.0f))			//	[�@�K�[�h�@]�F
#define GUARD_RADIUS_X		(40)										//	[�@�K�[�h�@]���aX��
#define GUARD_RADIUS_Y		(60)										//	[�@�K�[�h�@]���aY��
#define GUARD_CLEAR			(1.0f / 60)									//	[�@�K�[�h�@]����
#define GUARD_LIFE			(60)										//	[�@�K�[�h�@]����
//	�q�b�g��
#define HIT_000_MOVE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[�@�q�b�g��@]����
#define HIT_000_COL			(D3DXCOLOR(0.7f, 0.3f, 0.0f, 1.0f))			//	[�@�q�b�g��@]�F
#define HIT_000_RADIUS_X	(80)										//	[�@�q�b�g��@]���aX��
#define HIT_000_RADIUS_Y	(80)										//	[�@�q�b�g��@]���aY��
#define HIT_000_CLEAR		( 1.0f / 60)								//	[�@�q�b�g��@]����
#define HIT_000_LIFE		(60)										//	[�@�q�b�g��@]����
//	�q�b�g��
#define HIT_001_MOVE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//	[�@�q�b�g���@]����
#define HIT_001_COL			(D3DXCOLOR(1.0f, 0.8f, 0.2f, 1.0f))			//	[�@�q�b�g���@]�F
#define HIT_001_RADIUS_X	(100)										//	[�@�q�b�g���@]���aX��
#define HIT_001_RADIUS_Y	(100)										//	[�@�q�b�g���@]���aY��
#define HIT_001_CLEAR		( 1.0f / 60)								//	[�@�q�b�g���@]����
#define HIT_001_LIFE		(60)										//	[�@�q�b�g���@]����
//	�X���[�N�W�����v��
#define SMOKE_000_MOVE		(D3DXVECTOR3(0.0f, -0.45f, 0.0f))			//	[�@�X���[�N�W�����v�� ]����
#define SMOKE_000_COL		(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f))			//	[�@�X���[�N�W�����v���@]�F
#define SMOKE_000_RADIUS_X	(60)										//	[�@�X���[�N�W�����v���@]���aX��
#define SMOKE_000_RADIUS_Y	(60)										//	[�@�X���[�N�W�����v���@]���aY��
#define SMOKE_000_CLEAR		( 1.0f / 60)								//	[�@�X���[�N�W�����v���@]����
#define SMOKE_000_LIFE		(60)										//	[�@�X���[�N�W�����v�� ]����
//	�X���[�N���n��
#define SMOKE_001_MOVE		(D3DXVECTOR3(0.0f, -0.45f, 0.0f))			//	[�@�X���[�N���n���@]����
#define SMOKE_001_COL		(D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.5f))			//	[�@�X���[�N���n���@]�F
#define SMOKE_001_RADIUS_X	(60)										//	[�@�X���[�N���n���@]���aX��
#define SMOKE_001_RADIUS_Y	(60)										//	[�@�X���[�N���n���@]���aY��
#define SMOKE_001_CLEAR		( 1.0f / 60)								//	[�@�X���[�N���n���@]����
#define SMOKE_001_LIFE		(60)										//	[�@�X���[�N���n���@]����



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEffect[EFFECTTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
EFFECT					g_aEffect[MAX_EFFECT];					// �G�t�F�N�g�̏��

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME1, &g_apTextureEffect[EFFECTTYPE_GUARD]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME2, &g_apTextureEffect[EFFECTTYPE_HIT_000]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME3, &g_apTextureEffect[EFFECTTYPE_HIT_001]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME4, &g_apTextureEffect[EFFECTTYPE_SMOKE_001]);
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX_NAME5, &g_apTextureEffect[EFFECTTYPE_SMOKE_002]);

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < EFFECTTYPE_MAX; nCntTex++)
	{
		if (g_apTextureEffect[nCntTex] != NULL)
		{
			g_apTextureEffect[nCntTex]->Release();
			g_apTextureEffect[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���ꍇ
			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			switch (g_aEffect[nCntEffect].size)
			{
			case EFFECTSIZE_NONE:
				break;
			case EFFECTSIZE_UP:
				g_aEffect[nCntEffect].fRadius_X += EFFECT_TRANS;	//	���a�̊g��X��
				g_aEffect[nCntEffect].fRadius_Y += EFFECT_TRANS;	//	���a�̊g��Y��
				break;
			case EFFECTSIZE_DOWN:
				g_aEffect[nCntEffect].fRadius_X -= EFFECT_TRANS;	//	���a�̏k��X��
				g_aEffect[nCntEffect].fRadius_Y -= EFFECT_TRANS;	//	���a�̏k��Y��
				break;
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);

			g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fClear;
			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0)
			{// ������0�ɂȂ����ꍇ
				g_aEffect[nCntEffect].bUse = false;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			// �v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���C�e�B���O�̖�����
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);	// Z�e�X�g�̖�����

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���ꍇ
		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �t�s���ݒ�
			g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect[g_aEffect[nCntEffect].type]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEffect, 2);
		}
	}
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O�̗L����
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffEffect
		, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

	// ���̏�����
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius_X = 0.0f;
		g_aEffect[nCntEffect].fRadius_Y = 0.0f;
		g_aEffect[nCntEffect].fClear = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
}


//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, EFFECTTYPE type)
{//�ʒu�E�����E�J���[�E���a(�傫��)�E�����E�g��/�k���E���
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ��ꍇ
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].type = type;
			if (type == EFFECTTYPE_GUARD)
			{//		�K�[�h [0]
				PlaySound(SOUND_LABEL_GUARD_000);
				g_aEffect[nCntEffect].move = GUARD_MOVE;
				g_aEffect[nCntEffect].col = GUARD_COL;
				g_aEffect[nCntEffect].fRadius_X = GUARD_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = GUARD_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = GUARD_CLEAR;
				g_aEffect[nCntEffect].nLife = GUARD_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_HIT_000)
			{//		�q�b�g	[��]
				PlaySound(SOUND_LABEL_HIT_000);
				g_aEffect[nCntEffect].move = HIT_000_MOVE;
				g_aEffect[nCntEffect].col = HIT_000_COL;
				g_aEffect[nCntEffect].fRadius_X = HIT_000_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = HIT_000_RADIUS_X;
				g_aEffect[nCntEffect].fClear = HIT_000_CLEAR;
				g_aEffect[nCntEffect].nLife = HIT_000_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_HIT_001)
			{//		 �q�b�g	[��]
				PlaySound(SOUND_LABEL_HIT_001);
				g_aEffect[nCntEffect].move = HIT_001_MOVE;
				g_aEffect[nCntEffect].col = HIT_001_COL;
				g_aEffect[nCntEffect].fRadius_X = HIT_001_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = HIT_001_RADIUS_X;
				g_aEffect[nCntEffect].fClear = HIT_001_CLEAR;
				g_aEffect[nCntEffect].nLife = HIT_001_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;
			}
			else	if (type == EFFECTTYPE_SMOKE_001)
			{//		��	[�W�����v]
				g_aEffect[nCntEffect].move = SMOKE_000_MOVE;
				g_aEffect[nCntEffect].col = SMOKE_000_COL;
				g_aEffect[nCntEffect].fRadius_X = SMOKE_000_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = SMOKE_000_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = SMOKE_000_CLEAR;
				g_aEffect[nCntEffect].nLife = SMOKE_000_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;

			}
			else	if (type == EFFECTTYPE_SMOKE_002)
			{//		 �� [���n]
				g_aEffect[nCntEffect].move = SMOKE_001_MOVE;
				g_aEffect[nCntEffect].col = SMOKE_001_COL;
				g_aEffect[nCntEffect].fRadius_X = SMOKE_001_RADIUS_X;
				g_aEffect[nCntEffect].fRadius_Y = SMOKE_001_RADIUS_Y;
				g_aEffect[nCntEffect].fClear = SMOKE_001_CLEAR;
				g_aEffect[nCntEffect].nLife = SMOKE_001_LIFE;
				g_aEffect[nCntEffect].size = EFFECTSIZE_UP;

			}
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius_X, -g_aEffect[nCntEffect].fRadius_Y, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].bUse = true;	// �g�p����Ă����Ԃɂ���
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}