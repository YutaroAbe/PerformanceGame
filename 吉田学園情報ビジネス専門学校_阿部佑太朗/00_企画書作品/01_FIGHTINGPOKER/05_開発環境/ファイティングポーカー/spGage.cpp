//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// SP�Q�[�W���� [spGage.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "spGage.h"
#include "main.h"
#include "game.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define SPGAGE_MAX					(10)				// SP�Q�[�W�̍ő吔
#define SPGAGE_WIDTH				(500)				// ��
#define SPGAGE_HEIGHT				(70)				// ����
#define SPGAGE_FRAME_WIDTH			(10)				// �g�̕�
#define SPGAGE_DEST_APPROX			(0.5f)				// �ړI�n�̋ߎ��l
#define SPGAGE_ADD_FRAME			(10)				// SP�Q�[�W�̖ړI�̒l�܂łɂ�����t���[����
#define SPGAGE_ADD_FRAME_RED		(60)				// ��SP�Q�[�W�̖ړI�̒l�܂łɂ�����t���[����
#define SPGAGE_RED_ADD_START_FRAME	(90)				// ��SP�Q�[�W�̌����J�n�܂łɂ�����t���[����

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // �e�N�X�`���̎�ނ̗񋓑�
	SPGAGE_TEX_FRAME = 0,	// �t���[��
	SPGAGE_TEX_SPBLACK,		// SP��
	SPGAGE_TEX_SPRED,		// SP��
	SPGAGE_TEX_SP,			// SP
	SPGAGE_TEX_MAX,			// ����
}SPGAGE_TEX_NAME;

typedef enum
{ // ��Ԃ̗񋓑�
	SPGAGE_STATE_NONE = 0,	// �ʏ���
	SPGAGE_STATE_UP,		// �㏸���
	SPGAGE_STATE_DOWN,		// �������
	SPGAGE_STATE_MAX,		// ����
}SPGAGE_STATE;

typedef struct
{
	char *pFilename;	// �t�@�C����
} SpGageTexInfo;

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
	SPGAGE_TYPE type;		// ���
	int nTexType;			// �e�N�X�`���̎��
	SPGAGE_STATE state;		// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
}SpGage;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexSpGage(LPDIRECT3DDEVICE9 pDevice);
void UpdateVertexSpGage(void);
void UpdateVertexSpGage(int nCntSpGage);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ��錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTextureSpGage[SPGAGE_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSpGage = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
SpGage					g_aSpGage[SPGAGE_MAX];				// SP�Q�[�W�̏��
int						g_aSkillPoint[MAX_PLAYER];					// �|�C���g
int						g_aRedSkillPointGageCounter[MAX_PLAYER];		// �ԃ|�C���g�̃J�E���^�[
// �ǂݍ��ރe�N�X�`�����̐ݒ�
SpGageTexInfo g_apTextureSpGageTInfo[SPGAGE_TEX_MAX] =
{
	{ "" },		// �t���[��
	{ "" },		// SP��
	{ "data//TEXTURE//Life_Red.jpg" },		// SP��
	{ "data//TEXTURE//Skill_Normal.jpg" },	// SP
};


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitSpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		g_aSpGage[nCntSpGage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSpGage[nCntSpGage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSpGage[nCntSpGage].fWidth = 0.0f;
		g_aSpGage[nCntSpGage].fHeight = 0.0f;
		g_aSpGage[nCntSpGage].fInitWidth = 0.0f;
		g_aSpGage[nCntSpGage].fDestWidth = 0.0f;
		g_aSpGage[nCntSpGage].fFrameWidth = 0.0f;
		g_aSpGage[nCntSpGage].fAddWidth = 0.0f;
		g_aSpGage[nCntSpGage].type = SPGAGE_TYPE_1P_FRAME;
		g_aSpGage[nCntSpGage].state = SPGAGE_STATE_NONE;
		g_aSpGage[nCntSpGage].bUse = false;
	}

	for (int nCntSpGageTex = 0; nCntSpGageTex < SPGAGE_TEX_MAX; nCntSpGageTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureSpGageTInfo[nCntSpGageTex].pFilename,
			&g_pTextureSpGage[nCntSpGageTex]);
	}

	// ���_���̍쐬
	MakeVertexSpGage(pDevice);

	// SP���̏�����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // �v���C���[�l������
		g_aSkillPoint[nCntPlayer] = 0;
	}

	SetSpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100.0f, SCREEN_HEIGHT - SPGAGE_HEIGHT / 2.0f - 10.0f, 0.0f), PLAYER_CONTROL_1P);
	SetSpAsset(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT - SPGAGE_HEIGHT / 2.0f - 10.0f, 0.0f), PLAYER_CONTROL_2P);
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitSpGage(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < SPGAGE_TEX_MAX; nCntTex++)
	{
		if (g_pTextureSpGage[nCntTex] != NULL)
		{
			g_pTextureSpGage[nCntTex]->Release();
			g_pTextureSpGage[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSpGage != NULL)
	{
		g_pVtxBuffSpGage->Release();
		g_pVtxBuffSpGage = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateSpGage()
{
	// �ԃ|�C���g�̃J�E���^�[����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{ // �v���C���[�l������
		g_aRedSkillPointGageCounter[nCntPlayer]--;
	}

	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		if (g_aSpGage[nCntSpGage].bUse == true)
		{
			// �ԃQ�[�W����
			if (g_aRedSkillPointGageCounter[PLAYER_CONTROL_1P] == 0 && g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPRED)
			{ // 1P�p�̃J�E���^�[��0�ɂȂ�ԃQ�[�W�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aSpGage[nCntSpGage].fDestWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[PLAYER_CONTROL_1P] / float(PLAYER_MAX_SKILL_POINT));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aSpGage[nCntSpGage].fAddWidth = (g_aSpGage[nCntSpGage].fDestWidth - g_aSpGage[nCntSpGage].fWidth) / SPGAGE_ADD_FRAME_RED;

				// ��Ԃ̐ݒ�
				if (g_aSpGage[nCntSpGage].fDestWidth < g_aSpGage[nCntSpGage].fWidth)
				{ // ���̕��̕����傫���ꍇ
				  // ������Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_DOWN;
				}
				else
				{
					// �㏸��Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_UP;
				}
			}
			else if (g_aRedSkillPointGageCounter[PLAYER_CONTROL_2P] == 0 && g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPRED)
			{ // 2P�p�̃J�E���^�[��0�ɂȂ�ԃQ�[�W�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aSpGage[nCntSpGage].fDestWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[PLAYER_CONTROL_2P] / float(PLAYER_MAX_SKILL_POINT));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aSpGage[nCntSpGage].fAddWidth = (g_aSpGage[nCntSpGage].fDestWidth - g_aSpGage[nCntSpGage].fWidth) / SPGAGE_ADD_FRAME_RED;

				// ��Ԃ̐ݒ�
				if (g_aSpGage[nCntSpGage].fDestWidth < g_aSpGage[nCntSpGage].fWidth)
				{ // ���̕��̕����傫���ꍇ
				  // ������Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_DOWN;
				}
				else
				{
					// �㏸��Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_UP;
				}
			}

			// ���̑������s��
			g_aSpGage[nCntSpGage].fWidth += g_aSpGage[nCntSpGage].fAddWidth;

			if (g_aSpGage[nCntSpGage].state == SPGAGE_STATE_DOWN)
			{ // �Q�[�W���������̏ꍇ
				if (g_aSpGage[nCntSpGage].fWidth < g_aSpGage[nCntSpGage].fDestWidth)
				{ // �ړI�̒l��菬�����Ȃ����ꍇ
					// �ړI�̒l����
					g_aSpGage[nCntSpGage].fWidth = g_aSpGage[nCntSpGage].fDestWidth;
					// �����ʂ����Z�b�g
					g_aSpGage[nCntSpGage].fAddWidth = 0.0f;
					// ��Ԃ�ʏ��Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_NONE;
				}
			}
			else if (g_aSpGage[nCntSpGage].state == SPGAGE_STATE_UP)
			{ // �Q�[�W���㏸���̏ꍇ
				if (g_aSpGage[nCntSpGage].fWidth > g_aSpGage[nCntSpGage].fDestWidth)
				{ // �ړI�̒l���傫���Ȃ����ꍇ
				  // �ړI�̒l����
					g_aSpGage[nCntSpGage].fWidth = g_aSpGage[nCntSpGage].fDestWidth;
					// �����ʂ����Z�b�g
					g_aSpGage[nCntSpGage].fAddWidth = 0.0f;
					// ��Ԃ�ʏ��Ԃɂ���
					g_aSpGage[nCntSpGage].state = SPGAGE_STATE_NONE;
				}
			}

			// ���_���̍X�V(��)
			UpdateVertexSpGage(nCntSpGage);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawSpGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffSpGage, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		if (g_aSpGage[nCntSpGage].bUse == true)	// SP�Q�[�W���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSpGage[g_aSpGage[nCntSpGage].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSpGage * 4, 2);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// SP�Q�[�W�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetSpGage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SPGAGE_TYPE type)
{
	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		if (g_aSpGage[nCntSpGage].bUse == false)
		{ // SP�Q�[�W���g�p����Ă��Ȃ��ꍇ
			 // ���_���̐ݒ�
			g_aSpGage[nCntSpGage].pos = pos;
			g_aSpGage[nCntSpGage].rot = rot;
			g_aSpGage[nCntSpGage].fFrameWidth = SPGAGE_FRAME_WIDTH;
			g_aSpGage[nCntSpGage].type = type;

			if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_FRAME || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_FRAME)
			{ // �t���[���̏ꍇ
				g_aSpGage[nCntSpGage].nTexType = SPGAGE_TEX_FRAME;
			}
			else if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPBLACK || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPBLACK)
			{ // SP���̏ꍇ
				g_aSpGage[nCntSpGage].nTexType = SPGAGE_TEX_SPBLACK;
			}
			else if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPRED || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPRED)
			{ // SP�Ԃ̏ꍇ
				g_aSpGage[nCntSpGage].nTexType = SPGAGE_TEX_SPRED;
			}
			else if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SP || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SP)
			{ // SP�̏ꍇ
				g_aSpGage[nCntSpGage].nTexType = SPGAGE_TEX_SP;
			}


			if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPBLACK || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPBLACK)
			{ // SP���̏ꍇ�F�����ɐݒ肷��
				g_aSpGage[nCntSpGage].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPRED || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPRED)
			{ // SP�Ԃ̏ꍇ�F����ۂ�ɐݒ肷��
				g_aSpGage[nCntSpGage].col = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
			}

			// ��ޕʒ��_�ʒu�ݒ�
			if(g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_FRAME || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_FRAME)
			{ // �t���[���̏ꍇ�t���[���̕���ݒ�
				g_aSpGage[nCntSpGage].fWidth = SPGAGE_WIDTH;
				g_aSpGage[nCntSpGage].fHeight = SPGAGE_HEIGHT;
			}
			else
			{ // �t���[���ȊO�̏ꍇ
				g_aSpGage[nCntSpGage].fWidth = SPGAGE_WIDTH - g_aSpGage[nCntSpGage].fFrameWidth * 2.0f;
				g_aSpGage[nCntSpGage].fHeight = SPGAGE_HEIGHT - g_aSpGage[nCntSpGage].fFrameWidth * 2.0f;
			}

			// ���������L�^
			g_aSpGage[nCntSpGage].fInitWidth = g_aSpGage[nCntSpGage].fWidth;

			// ���_���̍X�V(��)
			UpdateVertexSpGage(nCntSpGage);

			g_aSpGage[nCntSpGage].bUse = true;	// �g�p�����Ԃɂ���
			break;	// ����break�͂��Ȃ���
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// SP�Q�[�W�̂܂Ƃߐݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetSpAsset(D3DXVECTOR3 pos, PLAYER_CONTROL playerID)
{
	D3DXVECTOR3 rot;
	if (playerID == PLAYER_CONTROL_1P)
	{ // 1P�p�̏ꍇ
		rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		SetSpGage(pos, rot, SPGAGE_TYPE_1P_FRAME);
		SetSpGage(pos, rot, SPGAGE_TYPE_1P_SPBLACK);
		SetSpGage(pos, rot, SPGAGE_TYPE_1P_SPRED);
		SetSpGage(pos, rot, SPGAGE_TYPE_1P_SP);
	}
	else if (playerID == PLAYER_CONTROL_2P)
	{ // 2P�p�̏ꍇ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetSpGage(pos, rot, SPGAGE_TYPE_2P_FRAME);
		SetSpGage(pos, rot, SPGAGE_TYPE_2P_SPBLACK);
		SetSpGage(pos, rot, SPGAGE_TYPE_2P_SPRED);
		SetSpGage(pos, rot, SPGAGE_TYPE_2P_SP);
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// SP�Q�[�W�̒l�ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetSpGageSkillPoint(int nSkillPoint, PLAYER_CONTROL playerID)
{
	// life����
	g_aSkillPoint[playerID] = nSkillPoint;

	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		if (g_aSpGage[nCntSpGage].bUse == true)	// SP�Q�[�W���g�p����Ă���
		{
			if (playerID == PLAYER_CONTROL_1P &&
				(g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SP || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SPRED))
			{ // 1P�p�̏ꍇ
			  // �l��ݒ�
				g_aSpGage[nCntSpGage].fWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[playerID] / float(PLAYER_MAX_SKILL_POINT));
			}
			else if (playerID == PLAYER_CONTROL_2P &&
				(g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SP || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SPRED))
			{ // 2P�p�̏ꍇ
			  // �l��ݒ�
				g_aSpGage[nCntSpGage].fWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[playerID] / float(PLAYER_MAX_SKILL_POINT));
			}
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// SP�Q�[�W�̖ړI�̒l�ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetSpGageDestSkillPoint(int nSkillPoint, PLAYER_CONTROL playerID)
{
	SPGAGE_STATE state;

	// ��Ԃ̐ݒ�
	if (g_aSkillPoint[playerID] > nSkillPoint)
	{ // ����SkillPoint�̕����傫���ꍇ
		// ������Ԃɂ���
		state = SPGAGE_STATE_DOWN;
	}
	else
	{
		// �㏸��Ԃɂ���
		state = SPGAGE_STATE_UP;
	}

	// life����
	g_aSkillPoint[playerID] = nSkillPoint;

	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++)
	{
		if (g_aSpGage[nCntSpGage].bUse == true)	// SP�Q�[�W���g�p����Ă���
		{
			if (playerID == PLAYER_CONTROL_1P && g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_SP)
			{ // 1P�p�̏ꍇ
				// �ړI�̒l��ݒ�
				g_aSpGage[nCntSpGage].fDestWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[playerID] / float(PLAYER_MAX_SKILL_POINT));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aSpGage[nCntSpGage].fAddWidth = (g_aSpGage[nCntSpGage].fDestWidth - g_aSpGage[nCntSpGage].fWidth) / SPGAGE_ADD_FRAME;

				// ��Ԃ�ݒ肷��
				g_aSpGage[nCntSpGage].state = state;
			}
			else if (playerID == PLAYER_CONTROL_2P && g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_SP)
			{ // 2P�p�̏ꍇ
			  // �ړI�̒l��ݒ�
				g_aSpGage[nCntSpGage].fDestWidth = g_aSpGage[nCntSpGage].fInitWidth * (g_aSkillPoint[playerID] / float(PLAYER_MAX_SKILL_POINT));

				// �ړI�̒l�܂ł�1�t���[��������̑����ʂ��Z�o
				g_aSpGage[nCntSpGage].fAddWidth = (g_aSpGage[nCntSpGage].fDestWidth - g_aSpGage[nCntSpGage].fWidth) / SPGAGE_ADD_FRAME;

				// ��Ԃ�ݒ肷��
				g_aSpGage[nCntSpGage].state = state;
			}
		}
	}

	// ��SP�Q�[�W�̌����J�n�܂łɂ�����t���[������ݒ�
	g_aRedSkillPointGageCounter[playerID] = SPGAGE_RED_ADD_START_FRAME;
}


//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍X�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexSpGage(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSpGage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSpGage = 0; nCntSpGage < SPGAGE_MAX; nCntSpGage++, pVtx += 4)
	{
		// ��ޕʒ��_�ʒu�ݒ�
		if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_FRAME || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_FRAME)
		{ // �t���[���̏ꍇ�t���[���̕���ݒ�
			// ��]���
			float fAngleUp = atan2f((g_aSpGage[nCntSpGage].fWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
			float fLength = sqrtf((g_aSpGage[nCntSpGage].fWidth) * (g_aSpGage[nCntSpGage].fWidth) + (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));
			float fAngleDown = atan2f((g_aSpGage[nCntSpGage].fWidth), (g_aSpGage[nCntSpGage].fHeight / 2));

			// ���_���̐ݒ�
			pVtx[0].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aSpGage[nCntSpGage].rot.y), cosf(D3DX_PI + g_aSpGage[nCntSpGage].rot.y), 0.0f) * (g_aSpGage[nCntSpGage].fHeight / 2);
			pVtx[1].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aSpGage[nCntSpGage].rot.y), cosf(fAngleUp + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength;
			pVtx[2].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aSpGage[nCntSpGage].rot.y), cosf(0.0f + g_aSpGage[nCntSpGage].rot.y), 0.0f) * (g_aSpGage[nCntSpGage].fHeight / 2);
			pVtx[3].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aSpGage[nCntSpGage].rot.y), cosf(fAngleDown + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength;
		}
		else
		{ // �t���[���ȊO�̏ꍇ
			// ��]���
			// ���_���[0]�̊p�x
			float fAngle0 = atan2f((g_aSpGage[nCntSpGage].fFrameWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
			// ���_���[2]�̊p�x
			float fAngle2 = atan2f((g_aSpGage[nCntSpGage].fFrameWidth), (g_aSpGage[nCntSpGage].fHeight / 2));
			// ���_���[0][2]�̋���
			float fLength02 = sqrtf((g_aSpGage[nCntSpGage].fFrameWidth) * (g_aSpGage[nCntSpGage].fFrameWidth)
				+ (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));
			// ���_���[1]�̊p�x
			float fAngle1 = atan2f((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
			// ���_���[3]�̊p�x
			float fAngle3 = atan2f((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth), (g_aSpGage[nCntSpGage].fHeight / 2));
			// ���_���[1][3]�̋���
			float fLength13 = sqrtf((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth) * (g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth)
				+ (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));

			// ���_���̐ݒ�
			pVtx[0].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle0 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength02;
			pVtx[1].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle1 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength13;
			pVtx[2].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle2 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength02;
			pVtx[3].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle3 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength13;
		}
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = g_aSpGage[nCntSpGage].col;
		pVtx[1].col = g_aSpGage[nCntSpGage].col;
		pVtx[2].col = g_aSpGage[nCntSpGage].col;
		pVtx[3].col = g_aSpGage[nCntSpGage].col;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̌ʍX�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexSpGage(int nCntSpGage)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSpGage->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����i�߂�
	pVtx += 4 * nCntSpGage;

	// ��ޕʒ��_�ʒu�ݒ�
	if (g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_1P_FRAME || g_aSpGage[nCntSpGage].type == SPGAGE_TYPE_2P_FRAME)
	{ // �t���[���̏ꍇ�t���[���̕���ݒ�
		// ��]���
		float fAngleUp = atan2f((g_aSpGage[nCntSpGage].fWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
		float fLength = sqrtf((g_aSpGage[nCntSpGage].fWidth) * (g_aSpGage[nCntSpGage].fWidth) + (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));
		float fAngleDown = atan2f((g_aSpGage[nCntSpGage].fWidth), (g_aSpGage[nCntSpGage].fHeight / 2));

		// ���_���̐ݒ�
		pVtx[0].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(D3DX_PI + g_aSpGage[nCntSpGage].rot.y), cosf(D3DX_PI + g_aSpGage[nCntSpGage].rot.y), 0.0f) * (g_aSpGage[nCntSpGage].fHeight / 2);
		pVtx[1].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngleUp + g_aSpGage[nCntSpGage].rot.y), cosf(fAngleUp + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength;
		pVtx[2].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(0.0f + g_aSpGage[nCntSpGage].rot.y), cosf(0.0f + g_aSpGage[nCntSpGage].rot.y), 0.0f) * (g_aSpGage[nCntSpGage].fHeight / 2);
		pVtx[3].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngleDown + g_aSpGage[nCntSpGage].rot.y), cosf(fAngleDown + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength;
	}
	else
	{ // �t���[���ȊO�̏ꍇ
		// ��]���
		// ���_���[0]�̊p�x
		float fAngle0 = atan2f((g_aSpGage[nCntSpGage].fFrameWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
		// ���_���[2]�̊p�x
		float fAngle2 = atan2f((g_aSpGage[nCntSpGage].fFrameWidth), (g_aSpGage[nCntSpGage].fHeight / 2));
		// ���_���[0][2]�̋���
		float fLength02 = sqrtf((g_aSpGage[nCntSpGage].fFrameWidth) * (g_aSpGage[nCntSpGage].fFrameWidth)
			+ (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));
		// ���_���[1]�̊p�x
		float fAngle1 = atan2f((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth), (-g_aSpGage[nCntSpGage].fHeight / 2));
		// ���_���[3]�̊p�x
		float fAngle3 = atan2f((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth), (g_aSpGage[nCntSpGage].fHeight / 2));
		// ���_���[1][3]�̋���
		float fLength13 = sqrtf((g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth) * (g_aSpGage[nCntSpGage].fWidth + g_aSpGage[nCntSpGage].fFrameWidth)
			+ (g_aSpGage[nCntSpGage].fHeight / 2) * (g_aSpGage[nCntSpGage].fHeight / 2));

		// ���_���̐ݒ�
		pVtx[0].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle0 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle0 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength02;
		pVtx[1].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle1 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle1 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength13;
		pVtx[2].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle2 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle2 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength02;
		pVtx[3].pos = g_aSpGage[nCntSpGage].pos + D3DXVECTOR3(sinf(fAngle3 + g_aSpGage[nCntSpGage].rot.y), cosf(fAngle3 + g_aSpGage[nCntSpGage].rot.y), 0.0f) * fLength13;
	}
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_aSpGage[nCntSpGage].col;
	pVtx[1].col = g_aSpGage[nCntSpGage].col;
	pVtx[2].col = g_aSpGage[nCntSpGage].col;
	pVtx[3].col = g_aSpGage[nCntSpGage].col;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSpGage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexSpGage(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SPGAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSpGage,
		NULL);

	// ���_���̍X�V
	UpdateVertexSpGage();
}

