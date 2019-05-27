//=============================================================================
//
// UI [ui.cpp]
// Author : EbinaRiku
//
//=============================================================================
#include "rule.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_RULE		(RULE_MAX) // �ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRule[RULE_MAX] = {};	// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;	// ���_�o�b�t�@�̃|�C���^
RULE g_aRule[MAX_RULE];
int	g_PlessEnterCount;
float fColor;
//=============================================================================
// ����������
//=============================================================================
void InitRule(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++)
	{
		g_aRule[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRule[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRule[nCnt].fWidth = 0.0f;
		g_aRule[nCnt].fHeight = 0.0f;
		g_aRule[nCnt].type = RULE_FLOW;
		g_aRule[nCnt].bUse = false;
	}

	MakeVertexRule(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitRule(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < RULE_MAX; nCnt++)
	{
		if (g_pTextureRule[nCnt] != NULL)
		{
			g_pTextureRule[nCnt]->Release();
			g_pTextureRule[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateRule(void)
{
	VERTEX_2D  *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		switch (g_aRule[nCnt].type)
		{
		case RULE_PRESSBUTTON:
			//�I�����Ă���J���[�̒l�����炵�Ă���
			fColor -= 0.004f;

			if (fColor < 0.5f)
			{//�I�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
				fColor = 1.0f;
			}
			// �|���S���̐F
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, fColor);
			break;
		}

	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRule->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++)
	{
		if (g_aRule[nCnt].bUse == true)		//�g�p���Ă���Ȃ�`�悷��
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRule[g_aRule[nCnt].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//=============================================================================
// UI�ݒ�
//=============================================================================
void SetRule(D3DXVECTOR3 pos, float fWidth, float fHeight, RULETYPE type)
{
	VERTEX_2D  *pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		if (g_aRule[nCnt].bUse == false)
		{
			g_aRule[nCnt].pos = pos;			// �ʒu
			g_aRule[nCnt].fWidth = fWidth;	// ����
			g_aRule[nCnt].fHeight = fHeight;	// ��
			g_aRule[nCnt].type = type;		// ���

			pVtx[0].pos = D3DXVECTOR3(-g_aRule[nCnt].fWidth / 2, -(g_aRule[nCnt].fHeight / 2), 0.0f) + g_aRule[nCnt].pos;
			pVtx[1].pos = D3DXVECTOR3(g_aRule[nCnt].fWidth / 2, -(g_aRule[nCnt].fHeight / 2), 0.0f) + g_aRule[nCnt].pos;
			pVtx[2].pos = D3DXVECTOR3(-g_aRule[nCnt].fWidth / 2, g_aRule[nCnt].fHeight / 2, 0.0f) + g_aRule[nCnt].pos;
			pVtx[3].pos = D3DXVECTOR3(g_aRule[nCnt].fWidth / 2, g_aRule[nCnt].fHeight / 2, 0.0f) + g_aRule[nCnt].pos;
			g_aRule[nCnt].bUse = true;
			break;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRule->Unlock();
}
//=============================================================================
// ���_��񐶐�����
//=============================================================================
void MakeVertexRule(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RULE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK/Flow.png", &g_pTextureRule[RULE_FLOW]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\OperateKeyboard.png", &g_pTextureRule[RULE_KEYBORD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\OperateController.png", &g_pTextureRule[RULE_CONTROLLER]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\CardRole.png", &g_pTextureRule[RULE_ROLE]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/RULEBOOK\\Chara.png", &g_pTextureRule[RULE_CHARA]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/TITLE\\PressAnyBotton.png", &g_pTextureRule[RULE_PRESSBUTTON]);


	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RULE; nCnt++, pVtx += 4)
	{
		// �|���S���̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f) + g_aRule[nCnt].pos;
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// �|���S���̐F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRule->Unlock();
}
RULE *GetRule(void)
{
	return &g_aRule[0];
}
