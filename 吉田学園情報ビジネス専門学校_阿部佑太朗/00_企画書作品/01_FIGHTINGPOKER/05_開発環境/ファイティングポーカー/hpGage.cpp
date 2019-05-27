//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// HP�Q�[�W���� [hpGage.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "hpGage.h"
#include "main.h"
#include "game.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define HPGAGE_MAX					(10)				// HP�Q�[�W�̍ő吔
#define HPGAGE_WIDTH				(500)				// ��
#define HPGAGE_HEIGHT				(70)				// ����
#define HPGAGE_FRAME_WIDTH			(10)				// �g�̕�
#define HPGAGE_DEST_APPROX			(0.5f)				// �ړI�n�̋ߎ��l
#define HPGAGE_ADD_FRAME			(10)				// HP�Q�[�W�̖ړI�̒l�܂łɂ�����t���[����
#define HPGAGE_ADD_FRAME_RED		(60)				// ��HP�Q�[�W�̖ړI�̒l�܂łɂ�����t���[����
#define HPGAGE_RED_ADD_START_FRAME	(90)				// ��HP�Q�[�W�̌����J�n�܂łɂ�����t���[����

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // �e�N�X�`���̎�ނ̗񋓑�
	HPGAGE_TEX_FRAME = 0,	// �t���[��
	HPGAGE_TEX_HPBLACK,		// HP��
	HPGAGE_TEX_HPRED,		// HP��
	HPGAGE_TEX_HP,			// HP
	HPGAGE_TEX_MAX,			// ����
}HPGAGE_TEX_NAME;

typedef enum
{ // ��Ԃ̗񋓑�
	HPGAGE_STATE_NONE = 0,	// �ʏ���
	HPGAGE_STATE_UP,		// �㏸���
	HPGAGE_STATE_DOWN,		// �������
	HPGAGE_STATE_MAX,		// ����
}HPGAGE_STATE;

typedef struct
{
	char *pFilename;	// �t�@�C����
} HpGageTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	float fInitWidth;		// ������
	float fDestWidth;		// �ړI�̕�
	float fAddWidth;		// ���̑����l
	float fFrameWidth;		// �g�̕�
	HPGAGE_TYPE type;		// ���
	int nTexType;			// �e�N�X�`���̎��
	HPGAGE_STATE state;		// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
}HpGage;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexHpGage(LPDIRECT3DDEVICE9 pDevice);
void UpdateVertexHpGage(void);
void UpdateVertexHpGage(int nCntHpGage);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ��錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTextureHpGage[HPGAGE_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHpGage = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
HpGage					g_aHpGage[HPGAGE_TYPE_MAX];				// HP�Q�[�W�̏��
int						g_aLife[MAX_PLAYER];					// ���C�t
int						g_aRedLifeGageCounter[MAX_PLAYER];		// �ԃ��C�t�̃J�E���^�[
// �ǂݍ��ރe�N�X�`�����̐ݒ�
HpGageTexInfo g_apTextureHpGageTInfo[HPGAGE_TEX_MAX] =
{
	{ "" },		// �t���[��
	{ "" },		// HP��
	{ "data//TEXTURE//Life_Red.jpg" },		// HP��
	{ "data//TEXTURE//Life_Normal.jpg" },	// HP
};


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitHpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		g_aHpGage[nCntHpGage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aHpGage[nCntHpGage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aHpGage[nCntHpGage].fWidth = 0.0f;
		g_aHpGage[nCntHpGage].fHeight = 0.0f;
		g_aHpGage[nCntHpGage].fInitWidth = 0.0f;
		g_aHpGage[nCntHpGage].fDestWidth = 0.0f;
		g_aHpGage[nCntHpGage].fFrameWidth = 0.0f;
		g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
		g_aHpGage[nCntHpGage].type = HPGAGE_TYPE_1P_FRAME;
		g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
		g_aHpGage[nCntHpGage].bUse = false;
	}

	for (int nCntHpGageTex = 0; nCntHpGageTex < HPGAGE_TEX_MAX; nCntHpGageTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureHpGageTInfo[nCntHpGageTex].pFilename,
			&g_pTextureHpGage[nCntHpGageTex]);
	}

	// ���_���̍쐬
	MakeVertexHpGage(pDevice);

	// HP���̏�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // �v���C���[�l������
		g_aLife[nCntPlayer] = PLAYER_LIFE;
	}
	
	SetHpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100.0f, HPGAGE_HEIGHT / 2.0f + 10.0f, 0.0f), PLAYER_CONTROL_1P);
	SetHpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, HPGAGE_HEIGHT / 2.0f + 10.0f, 0.0f), PLAYER_CONTROL_2P);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitHpGage(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < HPGAGE_TEX_MAX; nCntTex++)
	{
		if (g_pTextureHpGage[nCntTex] != NULL)
		{
			g_pTextureHpGage[nCntTex]->Release();
			g_pTextureHpGage[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHpGage != NULL)
	{
		g_pVtxBuffHpGage->Release();
		g_pVtxBuffHpGage = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateHpGage()
{
	// �ԃ��C�t�̃J�E���^�[����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // �v���C���[�l������
		g_aRedLifeGageCounter[nCntPlayer]--;
	}
	


	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)
		{
			// �ԃQ�[�W����
			if (g_aRedLifeGageCounter[PLAYER_CONTROL_1P] == 0 && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED)
			{ // 1P�p�̃J�E���^�[��0�ɂȂ�ԃQ�[�W�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[PLAYER_CONTROL_1P] / float(PLAYER_LIFE));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME_RED;

				// ��Ԃ̐ݒ�
				if (g_aHpGage[nCntHpGage].fDestWidth < g_aHpGage[nCntHpGage].fWidth)
				{ // ���̕��̕����傫���ꍇ
				  // ������Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_DOWN;
				}
				else
				{
					// �㏸��Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_UP;
				}
			}
			else if (g_aRedLifeGageCounter[PLAYER_CONTROL_2P] == 0 && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // 2P�p�̃J�E���^�[��0�ɂȂ�ԃQ�[�W�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[PLAYER_CONTROL_2P] / float(PLAYER_LIFE));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME_RED;

				// ��Ԃ̐ݒ�
				if (g_aHpGage[nCntHpGage].fDestWidth < g_aHpGage[nCntHpGage].fWidth)
				{ // ���̕��̕����傫���ꍇ
				  // ������Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_DOWN;
				}
				else
				{
					// �㏸��Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_UP;
				}
			}

			// ���̑������s��
			g_aHpGage[nCntHpGage].fWidth += g_aHpGage[nCntHpGage].fAddWidth;

			if (g_aHpGage[nCntHpGage].state == HPGAGE_STATE_DOWN)
			{ // �Q�[�W���������̏ꍇ
				if (g_aHpGage[nCntHpGage].fWidth < g_aHpGage[nCntHpGage].fDestWidth)
				{ // �ړI�̒l��菬�����Ȃ����ꍇ
					// �ړI�̒l����
					g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fDestWidth;
					// �����ʂ����Z�b�g
					g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
					// ��Ԃ�ʏ��Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
				}
			}
			else if (g_aHpGage[nCntHpGage].state == HPGAGE_STATE_UP)
			{ // �Q�[�W���㏸���̏ꍇ
				if (g_aHpGage[nCntHpGage].fWidth > g_aHpGage[nCntHpGage].fDestWidth)
				{ // �ړI�̒l���傫���Ȃ����ꍇ
				  // �ړI�̒l����
					g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fDestWidth;
					// �����ʂ����Z�b�g
					g_aHpGage[nCntHpGage].fAddWidth = 0.0f;
					// ��Ԃ�ʏ��Ԃɂ���
					g_aHpGage[nCntHpGage].state = HPGAGE_STATE_NONE;
				}
			}


			// ���_���̍X�V(��)
			UpdateVertexHpGage(nCntHpGage);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawHpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffHpGage, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HP�Q�[�W���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureHpGage[g_aHpGage[nCntHpGage].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHpGage * 4, 2);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HP�Q�[�W�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, HPGAGE_TYPE type)
{
	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == false)
		{ // HP�Q�[�W���g�p����Ă��Ȃ��ꍇ
		  // ���_���̐ݒ�
			g_aHpGage[nCntHpGage].pos = pos;
			g_aHpGage[nCntHpGage].rot = rot;
			g_aHpGage[nCntHpGage].fFrameWidth = HPGAGE_FRAME_WIDTH;
			g_aHpGage[nCntHpGage].type = type;

			if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
			{ // �t���[���̏ꍇ
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_FRAME;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPBLACK || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPBLACK)
			{ // HP���̏ꍇ
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HPBLACK;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // HP�Ԃ̏ꍇ
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HPRED;
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP)
			{ // HP�̏ꍇ
				g_aHpGage[nCntHpGage].nTexType = HPGAGE_TEX_HP;
			}


			if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPBLACK || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPBLACK)
			{ // HP���̏ꍇ�F�����ɐݒ肷��
				g_aHpGage[nCntHpGage].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED)
			{ // HP�Ԃ̏ꍇ�F��Ԃɐݒ肷��
				g_aHpGage[nCntHpGage].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			// ��ޕʒ��_�ʒu�ݒ�
			if(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
			{ // �t���[���̏ꍇ�t���[���̕���ݒ�
				g_aHpGage[nCntHpGage].fWidth = HPGAGE_WIDTH;
				g_aHpGage[nCntHpGage].fHeight = HPGAGE_HEIGHT;
			}
			else
			{ // �t���[���ȊO�̏ꍇ
				g_aHpGage[nCntHpGage].fWidth = HPGAGE_WIDTH - g_aHpGage[nCntHpGage].fFrameWidth * 2.0f;
				g_aHpGage[nCntHpGage].fHeight = HPGAGE_HEIGHT - g_aHpGage[nCntHpGage].fFrameWidth * 2.0f;
			}

			// ���������L�^
			g_aHpGage[nCntHpGage].fInitWidth = g_aHpGage[nCntHpGage].fWidth;

			// ���_���̍X�V(��)
			UpdateVertexHpGage(nCntHpGage);

			g_aHpGage[nCntHpGage].bUse = true;	// �g�p�����Ԃɂ���
			break;	// ����break�͂��Ȃ���
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HP�Q�[�W�̂܂Ƃߐݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpAsset(D3DXVECTOR3 pos, PLAYER_CONTROL playerID)
{
	D3DXVECTOR3 rot;
	if (playerID == PLAYER_CONTROL_1P)
	{ // 1P�p�̏ꍇ
		rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_FRAME);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HPBLACK);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HPRED);
		SetHpGage(pos, rot, HPGAGE_TYPE_1P_HP);
	}
	else if (playerID == PLAYER_CONTROL_2P)
	{ // 2P�p�̏ꍇ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_FRAME);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HPBLACK);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HPRED);
		SetHpGage(pos, rot, HPGAGE_TYPE_2P_HP);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HP�Q�[�W�̒l�ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGageLife(int nLife, PLAYER_CONTROL playerID)
{
	// life����
	g_aLife[playerID] = nLife;

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HP�Q�[�W���g�p����Ă���
		{
			if (playerID == PLAYER_CONTROL_1P && 
				(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HPRED))
			{ // 1P�p�̏ꍇ
			  // �l��ݒ�
				g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));
			}
			else if (playerID == PLAYER_CONTROL_2P &&
				(g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HPRED))
			{ // 2P�p�̏ꍇ
			  // �l��ݒ�
				g_aHpGage[nCntHpGage].fWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// HP�Q�[�W�̖ړI�̒l�ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetHpGageDestLife(int nLife, PLAYER_CONTROL playerID)
{
	HPGAGE_STATE state;

	// ��Ԃ̐ݒ�
	if (g_aLife[playerID] > nLife)
	{ // ����Life�̕����傫���ꍇ
		// ������Ԃɂ���
		state = HPGAGE_STATE_DOWN;
	}
	else
	{
		// �㏸��Ԃɂ���
		state = HPGAGE_STATE_UP;
	}

	// life����
	g_aLife[playerID] = nLife;

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++)
	{
		if (g_aHpGage[nCntHpGage].bUse == true)	// HP�Q�[�W���g�p����Ă���
		{
			if (playerID == PLAYER_CONTROL_1P && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_HP)
			{ // 1P�p�̏ꍇ
				// �ړI�̒l��ݒ�
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME;

				// ��Ԃ�ݒ肷��
				g_aHpGage[nCntHpGage].state = state;
			}
			else if (playerID == PLAYER_CONTROL_2P && g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_HP)
			{ // 2P�p�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aHpGage[nCntHpGage].fDestWidth = g_aHpGage[nCntHpGage].fInitWidth * (g_aLife[playerID] / float(PLAYER_LIFE));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aHpGage[nCntHpGage].fAddWidth = (g_aHpGage[nCntHpGage].fDestWidth - g_aHpGage[nCntHpGage].fWidth) / HPGAGE_ADD_FRAME;

				// ��Ԃ�ݒ肷��
				g_aHpGage[nCntHpGage].state = state;
			}
		}
	}

	// ��HP�Q�[�W�̌����J�n�܂łɂ�����t���[������ݒ�
	g_aRedLifeGageCounter[playerID] = HPGAGE_RED_ADD_START_FRAME;			
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍X�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexHpGage(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHpGage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHpGage = 0; nCntHpGage < HPGAGE_MAX; nCntHpGage++, pVtx += 4)
	{
		// ��ޕʒ��_�ʒu�ݒ�
		if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
		{ // �t���[���̏ꍇ�t���[���̕���ݒ�
			// ��]���
			float fAngleUp = atan2f((g_aHpGage[nCntHpGage].fWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			float fLength = sqrtf((g_aHpGage[nCntHpGage].fWidth) * (g_aHpGage[nCntHpGage].fWidth) + (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
			float fAngleDown = atan2f((g_aHpGage[nCntHpGage].fWidth), (g_aHpGage[nCntHpGage].fHeight / 2));

			// ���_���̐ݒ�
			pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), cosf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
			pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
			pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aHpGage[nCntHpGage].rot.y), cosf(0.0f + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
			pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
		}
		else
		{ // �t���[���ȊO�̏ꍇ
			// ��]���
			// ���_���[0]�̊p�x
			float fAngle0 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			// ���_���[2]�̊p�x
			float fAngle2 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
			// ���_���[0][2]�̋���
			float fLength02 = sqrtf((g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fFrameWidth)
				+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
			// ���_���[1]�̊p�x
			float fAngle1 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
			// ���_���[3]�̊p�x
			float fAngle3 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
			// ���_���[1][3]�̋���
			float fLength13 = sqrtf((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth)
				+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));

			// ���_���̐ݒ�
			pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
			pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
			pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
			pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
		}
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = g_aHpGage[nCntHpGage].col;
		pVtx[1].col = g_aHpGage[nCntHpGage].col;
		pVtx[2].col = g_aHpGage[nCntHpGage].col;
		pVtx[3].col = g_aHpGage[nCntHpGage].col;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̌ʍX�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexHpGage(int nCntHpGage)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHpGage->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����i�߂�
	pVtx += 4 * nCntHpGage;

	// ��ޕʒ��_�ʒu�ݒ�
	if (g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_1P_FRAME || g_aHpGage[nCntHpGage].type == HPGAGE_TYPE_2P_FRAME)
	{ // �t���[���̏ꍇ�t���[���̕���ݒ�
		// ��]���
		float fAngleUp = atan2f((g_aHpGage[nCntHpGage].fWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		float fLength = sqrtf((g_aHpGage[nCntHpGage].fWidth) * (g_aHpGage[nCntHpGage].fWidth) + (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
		float fAngleDown = atan2f((g_aHpGage[nCntHpGage].fWidth), (g_aHpGage[nCntHpGage].fHeight / 2));

		// ���_���̐ݒ�
		pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), cosf(D3DX_PI + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
		pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleUp + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
		pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aHpGage[nCntHpGage].rot.y), cosf(0.0f + g_aHpGage[nCntHpGage].rot.y), 0.0f) * (g_aHpGage[nCntHpGage].fHeight / 2);
		pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), cosf(fAngleDown + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength;
	}
	else
	{ // �t���[���ȊO�̏ꍇ
		// ��]���
		// ���_���[0]�̊p�x
		float fAngle0 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		// ���_���[2]�̊p�x
		float fAngle2 = atan2f((g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
		// ���_���[0][2]�̋���
		float fLength02 = sqrtf((g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fFrameWidth)
			+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));
		// ���_���[1]�̊p�x
		float fAngle1 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (-g_aHpGage[nCntHpGage].fHeight / 2));
		// ���_���[3]�̊p�x
		float fAngle3 = atan2f((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth), (g_aHpGage[nCntHpGage].fHeight / 2));
		// ���_���[1][3]�̋���
		float fLength13 = sqrtf((g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth) * (g_aHpGage[nCntHpGage].fWidth + g_aHpGage[nCntHpGage].fFrameWidth)
			+ (g_aHpGage[nCntHpGage].fHeight / 2) * (g_aHpGage[nCntHpGage].fHeight / 2));

		// ���_���̐ݒ�
		pVtx[0].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle0 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
		pVtx[1].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle1 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
		pVtx[2].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle2 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength02;
		pVtx[3].pos = g_aHpGage[nCntHpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), cosf(fAngle3 + g_aHpGage[nCntHpGage].rot.y), 0.0f) * fLength13;
	}
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_aHpGage[nCntHpGage].col;
	pVtx[1].col = g_aHpGage[nCntHpGage].col;
	pVtx[2].col = g_aHpGage[nCntHpGage].col;
	pVtx[3].col = g_aHpGage[nCntHpGage].col;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexHpGage(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPGAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHpGage,
		NULL);

	// ���_���̍X�V
	UpdateVertexHpGage();
}

