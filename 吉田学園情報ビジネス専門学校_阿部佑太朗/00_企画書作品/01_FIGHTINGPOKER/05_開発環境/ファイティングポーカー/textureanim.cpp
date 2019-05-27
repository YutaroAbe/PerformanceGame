//=============================================================================
//
// �e�N�X�`���A�j���[�V�������� [textureanim.cpp]
// Author :  YUTARO ABE
//
//=============================================================================
#include "textureanim.h"
#include "camera.h"
#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXANIM_TEXTURENAME_000	"data/TEXTURE/explosion008.png"						// �ǂݍ��ރe�N�X�`���̖��O[	�O���r�e�B�o�C���h	]
#define TEXANIM_TEXTURENAME_001	"data/TEXTURE/explosion003.png"						// �ǂݍ��ރe�N�X�`���̖��O[	�n����	]
#define TEXANIM_TEXTURENAME_002	"data/TEXTURE/raizin000.png"						// �ǂݍ��ރe�N�X�`���̖��O[	���C�W��R	]
#define TEXANIM_TEXTURENAME_003	"data/TEXTURE/raizin001.png"						// �ǂݍ��ރe�N�X�`���̖��O[	���C�W��L	]
#define TEXANIM_TEXTURENAME_004	"data/TEXTURE/god000.png"							// �ǂݍ��ރe�N�X�`���̖��O[	�_�̂�������	]
#define TEXANIM_TEXTURENAME_005	"data/TEXTURE/dark000.png"							// �ǂݍ��ރe�N�X�`���̖��O[	�_�[�N�}�^�[	]

#define TEXANIM_TEXTYPE_MAX				(TEXANIM_MAX)								//	�e�N�X�`���̎��
#define TEXANIM_MAX								(100)								//	�ő吔


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTextureAnim(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTextureAnim[TEXANIM_TEXTYPE_MAX] = {};	// �@�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTextureAnim = NULL;						// �@���_�o�b�t�@�ւ̃|�C���^
Explosion g_aTextureAnim[TEXANIM_MAX];										// �@�e�N�X�`���A�j���[�V�����̏��
float g_fmoveX = 0.0f;														//	�O���r�e�B�o�C���h�̃|���S���h�炷�ϐ�
float g_fmoveY = 0.0f;														//	�O���r�e�B�o�C���h�̃|���S���h�炷�ϐ�

//=============================================================================
// ����������
//=============================================================================
void InitTextureAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_000, &g_pTextureTextureAnim[TEXANIM_GRAVITY]);	//	[�O���r�e�B�o�C���h]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_001, &g_pTextureTextureAnim[TEXANIM_FISSURES]);	//	[�n����]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_002, &g_pTextureTextureAnim[TEXANIM_RAIZIN_R]);	//	[���C�W��R]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_003, &g_pTextureTextureAnim[TEXANIM_RAIZIN_L]);	//	[���C�W��L]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_004, &g_pTextureTextureAnim[TEXANIM_GOD]);		//	[�_�̂�����]
	D3DXCreateTextureFromFile(pDevice, TEXANIM_TEXTURENAME_005, &g_pTextureTextureAnim[TEXANIM_DARK]);		//	[�_�[�N�}�^�[]
	// ���_���̍쐬
	MakeVertexTextureAnim(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTextureAnim(void)
{
	// �e�N�X�`���̊J��
	for(int nCntTextureAnim = 0; nCntTextureAnim <TEXANIM_TEXTYPE_MAX; nCntTextureAnim++)
	{
		if (g_pTextureTextureAnim[nCntTextureAnim] != NULL)
		{
			g_pTextureTextureAnim[nCntTextureAnim]->Release();
			g_pTextureTextureAnim[nCntTextureAnim] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTextureAnim != NULL)
	{
		g_pVtxBuffTextureAnim->Release();
		g_pVtxBuffTextureAnim = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTextureAnim(void)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == true)
		{// �e�N�X�`�����g�p����Ă���ꍇ
			g_aTextureAnim[nCntTextureAnim].nCounterAnim++;	// �J�E���^�[���Z
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GRAVITY)
			{//	[	�O���r�e�B�o�C���h	]
				g_aTextureAnim[nCntTextureAnim].nLife--;
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GRAVITY_CNT_FPS) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % GRAVITY_MAX_PATTERN; // �p�^�[��NO.�X�V

					// �e�N�X�`�����W�̍X�Vw
					pVtx[0].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);

					if (g_aTextureAnim[nCntTextureAnim].nLife <= g_aTextureAnim[nCntTextureAnim].nPatternAnim)
					{//	�|���S����ݒ肵�����Ԃɏ���
						g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
					g_fmoveY += GRAVITY_MOVE_X;
				}
				else if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GRAVITY_CNT_FPS) == GRAVITY_MAX_PATTERN)
				{
					g_fmoveY -= GRAVITY_MOVE_Y;
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_FISSURES)
			{//	[	�n����	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % FISSURES_CNT_FPS) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % FISSURES_MAX_PATTERN; // �p�^�[��NO.�X�V

					 // �e�N�X�`�����W�̍X�Vw
					pVtx[0].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// �p�^�[�����ŏ��ɖ߂����ꍇ
					 g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_R)
			{//	[	���C�W��R	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % RAIZIN_CNT_FPS_R) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1) % RAIZIN_MAX_PATTERN_R; // �p�^�[��NO.�X�V
					 // �e�N�X�`�����W�̍X�V
					pVtx[0].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// �p�^�[�����ŏ��ɖ߂����ꍇ
						g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_L)
			{//	[	���C�W��L	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % RAIZIN_CNT_FPS_L) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % RAIZIN_MAX_PATTERN_L; // �p�^�[��NO.�X�V
																																			  // �e�N�X�`�����W�̍X�V
					pVtx[0].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_L * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// �p�^�[�����ŏ��ɖ߂����ꍇ
						g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GOD	)
			{//	[	�_�̂�������	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % GOD_CNT_FPS) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % GOD_MAX_PATTERN; // �p�^�[��NO.�X�V
																																			 // �e�N�X�`�����W�̍X�V
					pVtx[0].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(GOD_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// �p�^�[�����ŏ��ɖ߂����ꍇ
						g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
				}
			}
			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_DARK)
			{//	[	�_�̂�������	]
				if ((g_aTextureAnim[nCntTextureAnim].nCounterAnim % DARK_CNT_FPS) == 0)
				{// ��莞�Ԍo�߂����ꍇ
					g_aTextureAnim[nCntTextureAnim].nPatternAnim = (g_aTextureAnim[nCntTextureAnim].nPatternAnim - 1) % DARK_MAX_PATTERN; // �p�^�[��NO.�X�V
																																		 // �e�N�X�`�����W�̍X�V
					pVtx[0].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 0.0f);
					pVtx[1].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 0.0f);
					pVtx[2].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim), 1.0f);
					pVtx[3].tex = D3DXVECTOR2(DARK_TEX_WIDTH * (g_aTextureAnim[nCntTextureAnim].nPatternAnim + 1), 1.0f);
					if (g_aTextureAnim[nCntTextureAnim].nPatternAnim == 0)
					{// �p�^�[�����ŏ��ɖ߂����ꍇ
						g_aTextureAnim[nCntTextureAnim].bUse = false; // �g�p����Ă��Ȃ���Ԃɂ���
					}
				}
			}

				// ���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, -g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X + g_fmoveX, -g_aTextureAnim[nCntTextureAnim].fRadius_Y + g_fmoveY, 0.0f);

		}
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTextureAnim->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTextureAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;		// �v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���C�e�B���O�̖�����
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);	// Z�e�X�g�̖�����

	// ���e�X�g�ɂ�铧���̈�̐؂蔲��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			// �A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// �A���t�@��l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		// ��r���@

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == true)
		{// �������g�p����Ă���ꍇ
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aTextureAnim[nCntTextureAnim].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �t�s���ݒ�
			g_aTextureAnim[nCntTextureAnim].mtxWorld._11 = mtxView._11;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._12 = mtxView._21;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._13 = mtxView._31;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._21 = mtxView._12;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._22 = mtxView._22;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._23 = mtxView._32;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._31 = mtxView._13;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._32 = mtxView._23;
			g_aTextureAnim[nCntTextureAnim].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aTextureAnim[nCntTextureAnim].pos.x, g_aTextureAnim[nCntTextureAnim].pos.y, g_aTextureAnim[nCntTextureAnim].pos.z);
			D3DXMatrixMultiply(&g_aTextureAnim[nCntTextureAnim].mtxWorld, &g_aTextureAnim[nCntTextureAnim].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aTextureAnim[nCntTextureAnim].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffTextureAnim, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTextureAnim[g_aTextureAnim[nCntTextureAnim].type]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTextureAnim, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	// �A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�e�B���O�̗L����
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTextureAnim(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * TEXANIM_MAX
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &g_pVtxBuffTextureAnim
		, NULL);

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
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
	g_pVtxBuffTextureAnim->Unlock();
	// ���̏�����
	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++)
	{
		g_aTextureAnim[nCntTextureAnim].type = TEXANIM_NONE;
		g_aTextureAnim[nCntTextureAnim].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTextureAnim[nCntTextureAnim].fRadius_X = 0.0f;
		g_aTextureAnim[nCntTextureAnim].fRadius_Y = 0.0f;
		g_aTextureAnim[nCntTextureAnim].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTextureAnim[nCntTextureAnim].nCounterAnim = 0;
		g_aTextureAnim[nCntTextureAnim].nPatternAnim = 0;
		g_aTextureAnim[nCntTextureAnim].bUse = false;
		g_aTextureAnim[nCntTextureAnim].nLife = 0;
		 g_fmoveX = 0.0f;
		 g_fmoveY = 0.0f;
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetTextureAnim(D3DXVECTOR3 pos, TEXANIMTYPA type)
{
	int nCount =0;
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTextureAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTextureAnim = 0; nCntTextureAnim < TEXANIM_MAX; nCntTextureAnim++, pVtx += 4)
	{
		if (g_aTextureAnim[nCntTextureAnim].bUse == false)
		{// �������g�p����Ă��Ȃ��ꍇ
			g_aTextureAnim[nCntTextureAnim].pos = pos;									//	�ʒu
			g_aTextureAnim[nCntTextureAnim].type = type;								//	���
			g_aTextureAnim[nCntTextureAnim].fRadius_X = 0;								//	���aX��
			g_aTextureAnim[nCntTextureAnim].fRadius_Y = 0;								//	���aY��
			g_aTextureAnim[nCntTextureAnim].nLife = 0;									//	����
			g_aTextureAnim[nCntTextureAnim].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	�F
			g_aTextureAnim[nCntTextureAnim].nCounterAnim = 0;							//	�A�j���[�V�����J�E���^�[
			g_aTextureAnim[nCntTextureAnim].nPatternAnim = 0;							//	�p�^�[���A�j���[�V����

			// ���_�J���[�̐ݒ�
			pVtx[0].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[1].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[2].col = g_aTextureAnim[nCntTextureAnim].col;
			pVtx[3].col = g_aTextureAnim[nCntTextureAnim].col;

			if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GRAVITY)
			{//	�O���r�e�B�o�C���h�̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_OU_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = GRAVITY_RADIUS_X;	//	���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = GRAVITY_RADIUS_Y;	//	���aY��
				g_aTextureAnim[nCntTextureAnim].nLife = GRAVITY_LIFE;			//	����
				g_aTextureAnim[nCntTextureAnim].col = GRAVITY_COLOR;			//	�F
				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(GRAVITY_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_FISSURES)
			{//	�n����̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_HEIMIN_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = FISSURES_RADIUS_X;	//�@���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = FISSURES_RADIUS_Y;	//	���aY��
				g_aTextureAnim[nCntTextureAnim].col = FISSURES_COLOR;			//	�F
				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(FISSURES_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_R)
			{//	���C�W��R�̐ݒ�
			 // ���_���W�̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_YUSHA_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = RAIZIN_RADIUS_X_R;	//�@���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = RAIZIN_RADIUS_Y_R;	//	���aY��
				g_aTextureAnim[nCntTextureAnim].col = RAIZIN_COLOR_R;				//	�F
				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(RAIZIN_TEX_WIDTH_R, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_RAIZIN_L)
			{//	���C�W��L�̐ݒ�
			 // ���_���W�̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_YUSHA_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;							//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = RAIZIN_RADIUS_X_L;		//�@���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = RAIZIN_RADIUS_Y_L;		//	���aY��
				g_aTextureAnim[nCntTextureAnim].col = RAIZIN_COLOR_L;				//	�F
																					// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.9f-(RAIZIN_TEX_WIDTH_L), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.9f - (RAIZIN_TEX_WIDTH_L), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_GOD)
			{//	���݂̂��������̐ݒ�
			 // ���_���W�̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_GOD_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = GOD_RADIUS_X;		//�@���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = GOD_RADIUS_Y;		//	���aY��
				g_aTextureAnim[nCntTextureAnim].col = GOD_COLOR;				//	�F
																				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(GOD_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(GOD_TEX_WIDTH, 1.0f);
			}
			else if (g_aTextureAnim[nCntTextureAnim].type == TEXANIM_DARK)
			{//���[���܂��̐ݒ�
			 // ���_���W�̐ݒ�
				PlaySound(SOUND_LABEL_SKILL_MAOU_SE);
				g_aTextureAnim[nCntTextureAnim].pos = pos;						//	�ʒu
				g_aTextureAnim[nCntTextureAnim].fRadius_X = DARK_RADIUS_X;		//�@���aX��
				g_aTextureAnim[nCntTextureAnim].fRadius_Y = DARK_RADIUS_Y;		//	���aY��
				g_aTextureAnim[nCntTextureAnim].col = DARK_COLOR;				//	�F
																				// �e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(DARK_TEX_WIDTH, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(DARK_TEX_WIDTH, 1.0f);
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X, g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X, g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aTextureAnim[nCntTextureAnim].fRadius_X, -g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTextureAnim[nCntTextureAnim].fRadius_X, -g_aTextureAnim[nCntTextureAnim].fRadius_Y, 0.0f);

			g_aTextureAnim[nCntTextureAnim].bUse = true;	// �g�p����Ă����Ԃɂ���
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTextureAnim->Unlock();
}
