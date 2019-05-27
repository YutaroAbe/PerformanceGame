//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "meshField.h"
#include "input.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FIELD_POKER_TEX			"data/TEXTURE/field_poker.jpg"	// �ǂݍ��ރe�N�X�`��
#define FIELD_RESULT_TEX		"data/TEXTURE/field_select.jpg"	// �ǂݍ��ރe�N�X�`��
#define FIELD_PLAYERSHOW_TEX	"data/TEXTURE/field_playershow.jpg"	// �ǂݍ��ރe�N�X�`��
#define FIELD_POS_X				(200.0f)						// �ʒu(X)
#define FIELD_POS_Y				(100.0f)						// �ʒu(Y)
#define FIELD_POS_Z				(200.0f)						// �ʒu(Z)
#define DIVISION_X				(1)								// ������
#define DIVISION_Z				(1)								// ������
#define MAX_FIELD				(FIELD_MAX)						// �ő吔
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureField[FIELD_MAX] = {};			// �e�N�X�`���̃|�C���^
FIELD g_aField[FIELD_MAX];									// �t�B�[���h�̍\����
//*****************************************************************************
// �t�B�[���h�̏��
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	float fWidth;			// ��
	float fDepth;			// ���s��
	int nDivision_X;		// X�̕�����
	int nDivision_Z;		// Z�̕�����
	FIELDTYPE type;
}FieldInfo;

//*****************************************************************************
// �t�B�[���h�̃Z�b�g
//*****************************************************************************
FieldInfo g_FieldInfo[] =
{// �ʒu�@�� �����@�� ���@�� �����@�� X�����@�� Z���� �� ���
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_POKER },
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_PLAYERSHOW },
	{ D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),SCREEN_WIDTH,SCREEN_HEIGHT,DIVISION_X,DIVISION_Z,FIELD_RESULT },
};
//=============================================================================
// ����������
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FIELD_POKER_TEX, &g_pTextureField[FIELD_POKER]);
	D3DXCreateTextureFromFile(pDevice, FIELD_PLAYERSHOW_TEX, &g_pTextureField[FIELD_PLAYERSHOW]);
	D3DXCreateTextureFromFile(pDevice, FIELD_RESULT_TEX, &g_pTextureField[FIELD_RESULT]);
	// �e�평����
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		g_aField[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCnt].fWidth = 0;
		g_aField[nCnt].fDepth = 0;
		g_aField[nCnt].nDivision_X = 0;
		g_aField[nCnt].nDivision_Z = 0;
		g_aField[nCnt].MaxIndex = 0;
		g_aField[nCnt].MaxVertex = 0;
		g_aField[nCnt].MaxPolygon = 0;
		g_aField[nCnt].bUse = false;
		g_aField[nCnt].type = FIELD_POKER;
	}
	for (int nCnt = 0; nCnt < sizeof g_FieldInfo / sizeof(FieldInfo); nCnt++)
	{
		g_aField[nCnt].pos = g_FieldInfo[nCnt].pos;
		g_aField[nCnt].rot = g_FieldInfo[nCnt].rot;
		g_aField[nCnt].fWidth = g_FieldInfo[nCnt].fWidth;
		g_aField[nCnt].fDepth = g_FieldInfo[nCnt].fDepth;
		g_aField[nCnt].nDivision_X = g_FieldInfo[nCnt].nDivision_X;
		g_aField[nCnt].nDivision_Z = g_FieldInfo[nCnt].nDivision_Z;
		g_aField[nCnt].MaxVertex = (g_aField[nCnt].nDivision_X + 1) * (g_aField[nCnt].nDivision_Z + 1);
		g_aField[nCnt].MaxIndex = (g_aField[nCnt].nDivision_X * g_aField[nCnt].nDivision_Z) * 2 + (g_aField[nCnt].nDivision_Z - 1) * 4 + 2;
		g_aField[nCnt].MaxPolygon = g_aField[nCnt].MaxIndex - 2;
		g_aField[nCnt].bUse = true;
		g_aField[nCnt].type = g_FieldInfo[nCnt].type;
	}
	MakeVertexField(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		if (g_pTextureField[nCnt] != NULL)
		{
			g_pTextureField[nCnt]->Release();
			g_pTextureField[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_FIELD; nCnt++)
	{
		// ���_�o�b�t�@�̊J��
		if (g_aField[nCnt].pVtxBuffField != NULL)
		{
			g_aField[nCnt].pVtxBuffField->Release();
			g_aField[nCnt].pVtxBuffField = NULL;
		}
		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_aField[nCnt].pIdxBuffField != NULL)
		{
			g_aField[nCnt].pIdxBuffField->Release();
			g_aField[nCnt].pIdxBuffField = NULL;
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	MODE mode = GetMode();
	GAMEMODE gamemode = GetGameMode();
	if (gamemode == GAMEMODE_POKER)
	{
		g_aField[0].bUse = true;
		g_aField[1].bUse = false;
		g_aField[2].bUse = false;
	}
	if (gamemode == GAMEMODE_PLAYERSHOW)
	{
		g_aField[0].bUse = false;
		g_aField[1].bUse = true;
		g_aField[2].bUse = false;
	}
	if (gamemode == GAMEMODE_RESULT)
	{
		g_aField[0].bUse = false;
		g_aField[1].bUse = false;
		g_aField[2].bUse = true;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aField[nCntField].mtxWorldField);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aField[nCntField].rot.y,						//Y,X,Z�̏���
			g_aField[nCntField].rot.x,
			g_aField[nCntField].rot.z);

		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorldField,
			&g_aField[nCntField].mtxWorldField,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			g_aField[nCntField].pos.x,
			g_aField[nCntField].pos.y,
			g_aField[nCntField].pos.z);

		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorldField,
			&g_aField[nCntField].mtxWorldField,
			&mtxTrans);


		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCntField].mtxWorldField);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_aField[nCntField].pVtxBuffField, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_aField[nCntField].pIdxBuffField);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		if (g_aField[nCntField].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureField[g_aField[nCntField].type]);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aField[nCntField].MaxIndex, 0, g_aField[nCntField].MaxPolygon);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_FIELD * g_aField[nCntField].MaxVertex,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_aField[nCntField].pVtxBuffField,
			NULL);

		// �C���f�b�N�X���̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_FIELD * g_aField[nCntField].MaxIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_aField[nCntField].pIdxBuffField,
			NULL);

		// ���_���ւ̃|�C���^�擾
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aField[nCntField].pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// �|���S���̍��W�ݒ�
		for (int nCntDepth = 0; nCntDepth < g_aField[nCntField].nDivision_Z + 1 ; nCntDepth++)
		{
			for (int nCntWidth = 0; nCntWidth < g_aField[nCntField].nDivision_X + 1 ; nCntWidth++)
			{
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].pos = D3DXVECTOR3(-g_aField[nCntField].fWidth + (g_aField[nCntField].fWidth * nCntWidth),
					0.0f,
					g_aField[nCntField].fDepth - (g_aField[nCntField].fDepth * nCntDepth));
				// �e�N�X�`���̍��W�ݒ�
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].tex = D3DXVECTOR2(1.0f * nCntWidth, 1.0f * nCntDepth);

				// �@���x�N�g���̐ݒ�
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// �|���S���̐F
				pVtx[nCntDepth * (g_aField[nCntField].nDivision_X + 1) + nCntWidth].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		// ���_�o�b�t�@���A�����b�N����
		g_aField[nCntField].pVtxBuffField->Unlock();

		// �C���f�b�N�X�ւ̃|�C���^�擾
		WORD *pIdx;

		// �C���f�b�N�X�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		g_aField[nCntField].pIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntZ = 0, nCntIdx = 0; nCntZ < g_aField[nCntField].nDivision_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= g_aField[nCntField].nDivision_X; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aField[nCntField].nDivision_X + 1) + nCntIdx;
				pIdx[1] = nCntIdx;

				pIdx += 2;
				if (nCntZ < g_aField[nCntField].nDivision_Z - 1 && nCntX == g_aField[nCntField].nDivision_X)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aField[nCntField].nDivision_X + 1) + nCntIdx + 1;

					pIdx += 2;
				}
			}
		}
		// �C���f�b�N�X�o�b�t�@���A�����b�N����
		g_aField[nCntField].pIdxBuffField->Unlock();
	}
}