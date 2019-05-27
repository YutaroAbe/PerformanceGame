//=============================================================================
//
// �|���S������ [Polygon.cpp]
// Author : ���{��
//
//=============================================================================
#include "game.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		MAX_SHADOW		(128)
#define		MAX_TEXSHADOW	(2)
#define		TEXTURE_EFFECT	""
#define		TEXTURE_EFFECT1	"data/TEXTURE/���̖��ݒ� 1 �̃R�s�[.jpg"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePolygon[MAX_TEXSHADOW] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;			//���_�o�b�t�@�ւ̃|�C���^
ZPolygon g_Polygon[MAX_SHADOW];

//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTexturePolygon[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT1, &g_pTexturePolygon[1]);

	// ���_���̍쐬
	MakeVertexPolygon(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	BreakPolygon(-1);

	for (int nCntTex = 0; nCntTex < MAX_TEXSHADOW; nCntTex++)
	{// �e�N�X�`���̊J��
		if (g_pTexturePolygon[nCntTex] != NULL)
		{
			g_pTexturePolygon[nCntTex]->Release();
			g_pTexturePolygon[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��;
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	//for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	//{//�S�e�����
	//	if (g_Polygon[nCntShadow].bUse == true)
	//	{
	//		CollisionObjectS(&g_Polygon[nCntShadow].pos);
	//	}
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	int nCntShadow;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// Z�e�X�g����
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, 2);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Polygon[nCntShadow].bUse == true)
		{
			//���_�J���[�̐ݒ�
			pVtx[nCntShadow * 4].col = g_Polygon[nCntShadow].col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[nCntShadow * 4 + 1].col = g_Polygon[nCntShadow].col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[nCntShadow * 4 + 2].col = g_Polygon[nCntShadow].col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[nCntShadow * 4 + 3].col = g_Polygon[nCntShadow].col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Polygon[nCntShadow].mtxWorldShadow);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Polygon[nCntShadow].rot.y, g_Polygon[nCntShadow].rot.x, g_Polygon[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Polygon[nCntShadow].mtxWorldShadow, &g_Polygon[nCntShadow].mtxWorldShadow, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Polygon[nCntShadow].pos.x, g_Polygon[nCntShadow].pos.y, g_Polygon[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Polygon[nCntShadow].mtxWorldShadow, &g_Polygon[nCntShadow].mtxWorldShadow, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Polygon[nCntShadow].mtxWorldShadow);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePolygon[g_Polygon[nCntShadow].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
	pDevice->SetTexture(0, NULL);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntShadow;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//�@���̐ݒ�
		pVtx[nCntShadow * 4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntShadow * 4 + 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[nCntShadow * 4].tex = D3DXVECTOR2(0.05f, 0.05f);
		pVtx[nCntShadow * 4 + 1].tex = D3DXVECTOR2(0.95f, 0.05f);
		pVtx[nCntShadow * 4 + 2].tex = D3DXVECTOR2(0.05f, 0.95f);
		pVtx[nCntShadow * 4 + 3].tex = D3DXVECTOR2(0.95f, 0.95f);

		//���_�J���[�̐ݒ�
		pVtx[nCntShadow * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
		pVtx[nCntShadow * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

																		   //g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
																		   //g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[nCntShadow].bUse = false;

	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
}
//=============================================================================
// �e�̍쐬
//=============================================================================
int SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nType)
{
	int nCntShadow;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Polygon[nCntShadow].bUse == false)
		{//�e�̏���ݒ肵�Ă��̔ԍ���Ԃ�

			g_Polygon[nCntShadow].bUse = true;
			g_Polygon[nCntShadow].nType = nType;
			g_Polygon[nCntShadow].col = col;

			g_Polygon[nCntShadow].pos = pos;
			g_Polygon[nCntShadow].rot = rot;
			g_Polygon[nCntShadow].fLengthX = fLengthX;
			g_Polygon[nCntShadow].fLengthZ = fLengthZ;

			pVtx[nCntShadow * 4].pos = D3DXVECTOR3(-g_Polygon[nCntShadow].fLengthX, 0.1f, g_Polygon[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 1].pos = D3DXVECTOR3(g_Polygon[nCntShadow].fLengthX, 0.1f, g_Polygon[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 2].pos = D3DXVECTOR3(-g_Polygon[nCntShadow].fLengthX, 0.1f, -g_Polygon[nCntShadow].fLengthZ);
			pVtx[nCntShadow * 4 + 3].pos = D3DXVECTOR3(g_Polygon[nCntShadow].fLengthX, 0.1f, -g_Polygon[nCntShadow].fLengthZ);
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPolygon->Unlock();
	return nCntShadow;
}
//=============================================================================
// �e�̔��f
//=============================================================================
void SettingPolygon(D3DXVECTOR3 pos)
{
	PLAYER *pPlayer = GetPlayer();

	//�ڕW�܂ł̋����v�Z
	D3DXVECTOR3 distance = pPlayer[0].target - pos;
	float		fDistance = powf(distance.x, 2) + powf(distance.z, 2);

	if (fDistance > 2000.0f * 2000.0f && pPlayer[0].bTarget == true)
	{//�ڕW��������
		g_Polygon[pPlayer[0].nCntTarget].col.a = 1.0f;
		g_Polygon[pPlayer[0].nCntTarget].rot.y = atan2f(distance.x, distance.z);
		g_Polygon[pPlayer[0].nCntTarget].pos = pos + D3DXVECTOR3(sinf(g_Polygon[pPlayer[0].nCntTarget].rot.y), 0.0f, cosf(g_Polygon[pPlayer[0].nCntTarget].rot.y)) * 1000.0f;
	}
	else if(pPlayer[0].bTarget == true)
	{//���񂾂������
		if (g_Polygon[pPlayer[0].nCntTarget].col.a != 0.0f)
		{
			g_Polygon[pPlayer[0].nCntTarget].col.a -= 0.05f;
		}
	}
	else { g_Polygon[pPlayer[0].nCntTarget].col.a = 0.0f; }
}
//=============================================================================
// �e�̍폜
//=============================================================================
void BreakPolygon(int nNumber)
{
	if (nNumber > -1) { g_Polygon[nNumber].bUse = false; }
	else if (nNumber == -1)
	{
		for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
		{
			g_Polygon[nCount].bUse = false;
		}
	}
	else
	{//�v���C���[�̂ݍ폜���Ȃ�
		PLAYER *pPlayer = GetPlayer();

		for (int nCount = 0; nCount < MAX_SHADOW; nCount++)
		{
			if (pPlayer[0].nCntTarget != nCount)
			{
				g_Polygon[nCount].bUse = false;
			}
		}
	}

}