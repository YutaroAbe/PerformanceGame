//=============================================================================
//
// �X�R�A�\������ [getscore.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "getscore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME_GETSCORE  "data/TEXTURE/number.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORENUMBER       (4)                           // �X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGetScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGetScore = NULL;	   // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGetScore = NULL;	   // ���_�o�b�t�@�ւ̃|�C���^
int                     g_TextureGetScorePos;          // �e�N�X�`��X���W
GETSCORE                g_aGetScore[MAX_DRAW_SCORE];   // �X�R�A�\�����

//=============================================================================
// ����������
//=============================================================================
void InitGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntGetScore = 0; nCntGetScore < MAX_DRAW_SCORE; nCntGetScore++)
	{// �\���ł���X�R�A�̐������J��Ԃ�
		g_aGetScore[nCntGetScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // ���W��������
		g_aGetScore[nCntGetScore].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �ړ��ʂ�������
		g_aGetScore[nCntGetScore].fWidth = 0.0f;                          // ����������
		g_aGetScore[nCntGetScore].fHeight = 0.0f;                         // ������������
		g_aGetScore[nCntGetScore].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);   // �F��������
		g_aGetScore[nCntGetScore].bUse = false;                           // �g�p���Ă��Ȃ���Ԃɂ���
		g_aGetScore[nCntGetScore].GetScore = 0;                           // �\������X�R�A��������
		g_aGetScore[nCntGetScore].nCounterDraw = 0;                       // �\�����鎞�Ԃ�������
	}
												
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,   // �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME_GETSCORE,	         // �t�@�C���̖��O
		&g_pTextureGetScore);	         // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexGetScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGetScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureGetScore != NULL)
	{
		g_pTextureGetScore->Release();
		g_pTextureGetScore = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffGetScore != NULL)
	{
		g_pVtxBuffGetScore->Release();
		g_pVtxBuffGetScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGetScore(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// �\���ł���X�R�A�����J��Ԃ�
		if (g_aGetScore[nCntGetScore1].bUse == true)
		{// �g�p����Ă���
			float posS = 0.0f;
			g_aGetScore[nCntGetScore1].pos += g_aGetScore[nCntGetScore1].move;
			g_aGetScore[nCntGetScore1].nCounterDraw--;
			for (float nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// �\������X�R�A�̌��������J��Ԃ�
				float pow = powf(10.0f, nCntGetScore2);  // 10��n���p��
				int Score = (int)pow;                    // float�^��int�^�ɕϊ�
				g_TextureGetScorePos = g_aGetScore[nCntGetScore1].GetScore % (Score * 10) / Score;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 1.0f);

				pVtx += 4;
				posS -= 18.0f;
			}
			if (g_aGetScore[nCntGetScore1].nCounterDraw <= 0)
			{// �J�E���^�[��0�ɂȂ���
				g_aGetScore[nCntGetScore1].bUse = false;
			}
		}
		else
		{// �g�p���Ă��Ȃ�
			pVtx += 4 * MAX_SCORENUMBER;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGetScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGetScore);

	// �|���S���̕`��
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// �\���ł���X�R�A�����J��Ԃ�
		if (g_aGetScore[nCntGetScore1].bUse == true)
		{// �g�p����Ă���
			for (int nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// �\������X�R�A�̌��������J��Ԃ�
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					(nCntGetScore1 * 16) + (nCntGetScore2 * 4),
					2);
			}
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGetScore(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORENUMBER * MAX_DRAW_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGetScore,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;
	float posS = 0.0f;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// �\���ł���X�R�A�����J��Ԃ�
		for (int nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
		{// �\������X�R�A�̌��������J��Ԃ�
		 // ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

			// ���_�e�N�X�`��
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[
			pVtx[0].col = g_aGetScore[nCntGetScore1].col;
			pVtx[1].col = g_aGetScore[nCntGetScore1].col;
			pVtx[2].col = g_aGetScore[nCntGetScore1].col;
			pVtx[3].col = g_aGetScore[nCntGetScore1].col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
			posS -= 18.0f;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void SetScore(D3DXVECTOR3 pos, float width, float height,int score)
{
	float posS = 0.0f;
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGetScore1 = 0; nCntGetScore1 < MAX_DRAW_SCORE; nCntGetScore1++)
	{// �\���ł���X�R�A�̐������J��Ԃ�
		if (g_aGetScore[nCntGetScore1].bUse == false)
		{// �g�p����Ă��Ȃ�
			g_aGetScore[nCntGetScore1].pos = pos;
			g_aGetScore[nCntGetScore1].fWidth = width;
			g_aGetScore[nCntGetScore1].fHeight = height;
			g_aGetScore[nCntGetScore1].GetScore = score;
			g_aGetScore[nCntGetScore1].move.y = -2.0f;
			g_aGetScore[nCntGetScore1].nCounterDraw = 30;
			g_aGetScore[nCntGetScore1].bUse = true;
			for (float nCntGetScore2 = 0; nCntGetScore2 < MAX_SCORENUMBER; nCntGetScore2++)
			{// �\������X�R�A�̌��������J��Ԃ�
				float pow = powf(10.0f, nCntGetScore2);  // 10��n���p��
				int Score = (int)pow;                    // float�^��int�^�ɕϊ�
				g_TextureGetScorePos = g_aGetScore[nCntGetScore1].GetScore % (Score * 10) / Score;
			    // ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y - g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x - g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aGetScore[nCntGetScore1].pos.x + g_aGetScore[nCntGetScore1].fWidth + posS, g_aGetScore[nCntGetScore1].pos.y + g_aGetScore[nCntGetScore1].fHeight, g_aGetScore[nCntGetScore1].pos.z);

				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TextureGetScorePos), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TextureGetScorePos), 1.0f);

				pVtx += 4;
				posS -= 18.0f;
			}
			break;
		}
		pVtx += 4 * MAX_SCORENUMBER;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGetScore->Unlock();
}
//=============================================================================
// �X�R�A�\�����̎擾
//=============================================================================
GETSCORE *GetGetScore(void)
{
	return &g_aGetScore[0];
}