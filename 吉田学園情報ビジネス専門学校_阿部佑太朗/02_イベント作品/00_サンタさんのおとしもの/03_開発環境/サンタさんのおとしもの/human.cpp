//=============================================================================
//
// ���ɂ���l�̏��� [human.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "human.h"
#include "demandpresent.h"
#include "score.h"
#include "bullet.h"
#include "sound.h"
#include "explosion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define HUMAN_TEXTURE_NAME0 "data/TEXTURE/boy.png"                    // �e�N�X�`���̃t�@�C����
#define HUMAN_TEXTURE_NAME1 "data/TEXTURE/girl.png"                   // �e�N�X�`���̃t�@�C����
#define ANIMATION_PATTERNX    ((1.0f / 5.0f) * (g_aHuman[nCntHuman].nPatternAnim % 4))// �e�N�X�`�����W(U)��؂�ւ���v�Z��
#define HUMAN_TEXTURE_PATTERN (4)                                           // �e�N�X�`���̃p�^�[����

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureHuman[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHuman = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Human                   g_aHuman[MAX_HUMAN];    // ���ɂ���l�̏��

//=============================================================================
// ����������
//=============================================================================
void InitHuman(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// �l�Ԃ̐������J��Ԃ�
		g_aHuman[nCntHuman].pos = D3DXVECTOR3(1400.0f, 400.0f, 0.0f);    // ���݂̈ʒu��������
		g_aHuman[nCntHuman].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �O��̈ʒu��������
		g_aHuman[nCntHuman].move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);      // �ړ��ʂ�������
		g_aHuman[nCntHuman].state = HUMANSTATE_NORMAL;                   // ��Ԃ͒ʏ�̏�Ԃ�
		g_aHuman[nCntHuman].fWidth = 20;                                 // ����������
		g_aHuman[nCntHuman].fHeight = 60;                                // ������������
		g_aHuman[nCntHuman].nPresentCounter = 0;                          // Present�J�E���^�[��������
		g_aHuman[nCntHuman].bUse = false;                                // �g�p���Ă��Ȃ���Ԃɂ���
		g_aHuman[nCntHuman].nNumtex = 0;                                 // �e�N�X�`���̔ԍ���������
	}

	// ���_�o�b�t�@�̍쐬
	MakeVertexHuman(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitHuman(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureHuman[nCntTex] != NULL)
		{
			g_pTextureHuman[nCntTex]->Release();
			g_pTextureHuman[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHuman != NULL)
	{
		g_pVtxBuffHuman->Release();
		g_pVtxBuffHuman = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateHuman(void)
{
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// �l�Ԃ̐������J��Ԃ�
		if (g_aHuman[nCntHuman].bUse == true)
		{// �g�p����Ă���
			g_aHuman[nCntHuman].posold = g_aHuman[nCntHuman].pos;  		// �O��̈ʒu�X�V

			if (g_aHuman[nCntHuman].state != HUMANSTATE_STOP)
			{// �~�܂��Ă����ԂłȂ�
			    // �ړ��ʍX�V
				g_aHuman[nCntHuman].pos += g_aHuman[nCntHuman].move;

				if (g_aHuman[nCntHuman].nCounterAnim % 7 == 0)
				{// �J�E���^�[��������x�i��
					g_aHuman[nCntHuman].nPatternAnim = (g_aHuman[nCntHuman].nPatternAnim + 1) % HUMAN_TEXTURE_PATTERN;   // �p�^�[��No. �X�V

					// �e�N�X�`�����W�̍X�V
					pVtx[0].tex.x = 0.0f + ANIMATION_PATTERNX;           
					pVtx[1].tex.x = (1.0f / 5.0f) + ANIMATION_PATTERNX;
					pVtx[2].tex.x = 0.0f + ANIMATION_PATTERNX;;
					pVtx[3].tex.x = (1.0f / 5.0f) + ANIMATION_PATTERNX;
				}
				g_aHuman[nCntHuman].nCounterAnim++;  // �J�E���^�[��i�߂�

				g_aHuman[nCntHuman].move.y += 1.0f;

				if (g_aHuman[nCntHuman].pos.y > SCREEN_HEIGHT)
				{
					g_aHuman[nCntHuman].pos.y = SCREEN_HEIGHT;
					g_aHuman[nCntHuman].move.y = 0.0f;
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_NORMAL)
			{// �ʏ�̏�Ԃ�������
				g_aHuman[nCntHuman].nPresentCounter--;
				if (g_aHuman[nCntHuman].nPresentCounter <= 0)
				{// �v���[���g�J�E���^�[��0�ɂȂ���
					g_aHuman[nCntHuman].nStopConter = 60;        // �X�g�b�v�J�E���^�[��ݒ�
					g_aHuman[nCntHuman].state = HUMANSTATE_STOP; // �~�܂��Ă����Ԃɐݒ�
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_STOP)
			{// �~�܂��Ă����Ԃ�������
				g_aHuman[nCntHuman].nStopConter--;   // �J�E���^�[�����炷
				if (g_aHuman[nCntHuman].nStopConter == 40)
				{// �J�E���^�[��������x������
					PlaySound(SOUND_LABEL_SE_WANT);
					SetDemandPresent(D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth + 10.0f, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight - 30.0f, 0.0f),nCntHuman,g_aHuman[nCntHuman].nNumtex);  // �~�����A�C�e����\��
				}
				if (g_aHuman[nCntHuman].nStopConter <= 0)
				{// �v���[���g�J�E���^�[��0�ɂȂ���
					g_aHuman[nCntHuman].state = HUMANSTATE_GIVEME_PRESENT; // �ʏ�̏�Ԃɐݒ�
				}
			}

			if (g_aHuman[nCntHuman].state == HUMANSTATE_GIVEME_PRESENT)
			{// �~�܂��Ă����Ԃ�������
				if (CollisionBullet(&g_aHuman[nCntHuman].pos, g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].fHeight, &g_aHuman[nCntHuman].itemtype) == true)
				{// �v���[���g�J�E���^�[��0�ɂȂ���

					if (g_aHuman[nCntHuman].nNumtex == *g_aHuman[nCntHuman].itemtype)
					{
						PlaySound(SOUND_LABEL_SE_HIT);
						g_aHuman[nCntHuman].state = HUMANSTATE_HAVEPRESENT; // �v���[���g�����������Ԃɐݒ�
						DeleteDemandPresent(nCntHuman);                     // �����o��������

						g_aHuman[nCntHuman].move.y -= 17.0f;

						// �X�R�A�̉��Z
						AddScore(5000, D3DXVECTOR3(g_aHuman[nCntHuman].pos.x, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight - 10.0f, 0.0f));
					}
				}
			}

			// ��ʒ[�ɍs���������
			if (g_aHuman[nCntHuman].move.x > 0 && g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth > SCREEN_WIDTH)
			{// �E�[�ɓ��B����
				g_aHuman[nCntHuman].bUse = false;
			}
			if (g_aHuman[nCntHuman].move.x < 0 && g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth < 0)
			{// ���[�ɓ��B����
				g_aHuman[nCntHuman].bUse = false;
			}

			//---------------------
			// ���_�o�b�t�@�̍X�V
			//---------------------

			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

			//// �e�N�X�`�����W
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;    // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawHuman(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffHuman, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// �l�Ԃ̐������J��Ԃ�
		if (g_aHuman[nCntHuman].bUse == true)
		{// �g�p����Ă���
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureHuman[g_aHuman[nCntHuman].nNumtex]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHuman * 4, 2);
		}
	}
}
//=============================================================================
// ���_�o�b�t�@�̍쐬
//=============================================================================
void MakeVertexHuman(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HUMAN_TEXTURE_NAME0,
		&g_pTextureHuman[0]);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HUMAN_TEXTURE_NAME1,
		&g_pTextureHuman[1]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HUMAN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHuman,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// �l�Ԃ̐������J��Ԃ�
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((1.0f / 5.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / 5.0f), 0.5f);

		pVtx += 4;     // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// �l�Ԃ̐ݒ�
//=============================================================================
void SetHuman(void)
{
	int randPos;       // �ʒu�����E�̂ǂ��炩�ɂ��邽�߂Ɏg�p
	float texV;        // �e�N�X�`����V���W
	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHuman->Lock(0, 0, (void**)&pVtx, 0);

	// �l�̐ݒ�
	for (int nCntHuman = 0; nCntHuman < MAX_HUMAN; nCntHuman++)
	{// �l�Ԃ̐������J��Ԃ�
		if (g_aHuman[nCntHuman].bUse == false)
		{// �g�p����Ă��Ȃ�
			randPos = rand() % 2;   // �o���ʒu���ǂ���ɂ��邩����
			if (randPos == 0)
			{// ��������o������Ȃ�
				g_aHuman[nCntHuman].pos = D3DXVECTOR3(-100.0f, SCREEN_HEIGHT, 0.0f);   // �ʒu��ݒ�
				g_aHuman[nCntHuman].move = D3DXVECTOR3(2.0f, 1.0f, 0.0f);              // �ړ��ʂ�ݒ�
				texV = 0.0f;
			}
			else if (randPos == 1)
			{// �E������o������Ȃ�
				g_aHuman[nCntHuman].pos = D3DXVECTOR3(SCREEN_WIDTH + 100, SCREEN_HEIGHT, 0.0f);   // �ʒu��ݒ�
				g_aHuman[nCntHuman].move = D3DXVECTOR3(-2.0f, 1.0f, 0.0f);                        // �ړ��ʂ�ݒ�
				texV = 0.5f;
			}
			g_aHuman[nCntHuman].nPresentCounter = rand() % 50 + 80;          // �v���[���g�J�E���^�[��ݒ�
			g_aHuman[nCntHuman].nNumtex = rand() % 2;                         // �e�N�X�`���ԍ���ݒ�
			g_aHuman[nCntHuman].state = HUMANSTATE_NORMAL;                    // �ʏ�̏�Ԃ�
			g_aHuman[nCntHuman].bUse = true;                                  // �g�p���Ă����Ԃɂ���

			//--------------------
			// ���_�o�b�t�@�̐ݒ�
			//--------------------

			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y - g_aHuman[nCntHuman].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x - g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aHuman[nCntHuman].pos.x + g_aHuman[nCntHuman].fWidth, g_aHuman[nCntHuman].pos.y, 0.0f);

			// �e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, texV);
			pVtx[1].tex = D3DXVECTOR2((1.0f / 5.0f), texV);
			pVtx[2].tex = D3DXVECTOR2(0.0f, texV + 0.5f);
			pVtx[3].tex = D3DXVECTOR2((1.0f / 5.0f), texV + 0.5f);

			break;
		}
		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHuman->Unlock();
}
//=============================================================================
// �l�Ԃ̎擾
//=============================================================================
Human *GetHuman(void)
{
	return &g_aHuman[0];
}