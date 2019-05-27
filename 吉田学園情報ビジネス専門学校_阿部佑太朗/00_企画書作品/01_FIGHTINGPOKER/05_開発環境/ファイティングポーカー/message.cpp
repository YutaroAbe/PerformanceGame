//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// ���b�Z�[�W���� [message.cpp]
// Author : �� �a��
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#include "message.h"
#include "main.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �}�N����`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESSAGE_MAX					(10)				// ���b�Z�[�W�̍ő吔
#define MESSAGE_WIDTH				(500)				// ��
#define MESSAGE_HEIGHT				(70)				// ����
#define MESSAGE_FRAME_WIDTH			(10)				// �g�̕�
#define MESSAGE_DEST_APPROX			(0.5f)				// �ړI�n�̋ߎ��l

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �\���̒�`
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // ��Ԃ̗񋓑�
	MESSAGE_STATE_NONE = 0,		// �ʏ���
	MESSAGE_STATE_SIZE_CHANGE,	// �T�C�Y�ύX���
	MESSAGE_STATE_WAIT,			// �ҋ@���
	MESSAGE_STATE_DELETE,		// �폜���
	MESSAGE_STATE_MAX,			// ����
}MESSAGE_STATE;

typedef struct
{
	char *pFilename;	// �t�@�C����
} MessageTexInfo;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fDestWidth;		// �ړI�̕�
	float fHeight;			// ����
	float fDestHeight;		// �ړI�̍���
	int nTexType;			// �e�N�X�`���̎��
	MESSAGE_STATE state;	// ���
	int nStateCounter;		// ��Ԃ̃J�E���^�[
	int nStateDestTime;		// �ړI�܂ł̎���
	bool bUse;				// �g�p���Ă��邩�ǂ���
}Message;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �v���g�^�C�v�錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice);
void UpdateVertexMessage(void);
void UpdateVertexMessage(int nCntMessage);

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// �O���[�o���ϐ��錾
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
LPDIRECT3DTEXTURE9		g_pTextureMessage[MESSAGE_TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMessage = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
Message					g_aMessage[MESSAGE_MAX];				// ���b�Z�[�W�̏��

// �ǂݍ��ރe�N�X�`�����̐ݒ�
MessageTexInfo g_apTextureMessageTInfo[MESSAGE_TEX_MAX] =
{

	{ "data//TEXTURE//MESSAGE//round1_000.png" },		// ROUND1
	{ "data//TEXTURE//MESSAGE//round2_000.png" },		// ROUND2
	{ "data//TEXTURE//MESSAGE//round3_000.png" },		// ROUND3
	{ "data//TEXTURE//MESSAGE//round4_000.png" },		// ROUND4
	{ "data//TEXTURE//MESSAGE//finalround.png" },		// FinalROUND
	{ "data//TEXTURE//MESSAGE//fight000.png" },			// �t�@�C�g
	{ "data//TEXTURE//MESSAGE//KO002.png" },			// KO
	{ "data//TEXTURE//MESSAGE//timeover000.png" },		// TIMEOVER
};

int g_nMessageCounter = 0;	// ���b�Z�[�W�\���^�C�~���O�̃J�E���^�[
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ����������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void InitMessage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		g_aMessage[nCntMessage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMessage[nCntMessage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aMessage[nCntMessage].fWidth = 0.0f;
		g_aMessage[nCntMessage].fDestWidth = 0.0f;
		g_aMessage[nCntMessage].fHeight = 0.0f;
		g_aMessage[nCntMessage].fDestHeight = 0.0f;
		g_aMessage[nCntMessage].state = MESSAGE_STATE_NONE;
		g_aMessage[nCntMessage].nStateCounter = 0;
		g_aMessage[nCntMessage].nStateDestTime = 0;
		g_aMessage[nCntMessage].bUse = false;
	}

	for (int nCntMessageTex = 0; nCntMessageTex < MESSAGE_TEX_MAX; nCntMessageTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			g_apTextureMessageTInfo[nCntMessageTex].pFilename,
			&g_pTextureMessage[nCntMessageTex]);
	}

	// ������
	g_nMessageCounter = 0;

	// ���_���̍쐬
	MakeVertexMessage(pDevice);

}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �I������
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UninitMessage(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < MESSAGE_TEX_MAX; nCntTex++)
	{
		if (g_pTextureMessage[nCntTex] != NULL)
		{
			g_pTextureMessage[nCntTex]->Release();
			g_pTextureMessage[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMessage != NULL)
	{
		g_pVtxBuffMessage->Release();
		g_pVtxBuffMessage = NULL;
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �X�V����
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateMessage()
{
	// ���E���h�����擾
	int nRound = GetRoundCounter();

	g_nMessageCounter++;

	if (g_nMessageCounter == MESSAGE_ROUND_FRAME)
	{// ���E���h����
		if (nRound == 1)
		{// 1���E���h��
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND1);
			SelectVolume(SOUND_LABEL_R1_SE, 0.8f);
		}
		else if (nRound == 2)
		{// 2���E���h��
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND2);
			SelectVolume(SOUND_LABEL_R2_SE, 0.8f);
		}
		else if (nRound == 3)
		{// 3���E���h��
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND3);
			SelectVolume(SOUND_LABEL_R3_SE, 0.8f);
		}
		else if (nRound == 4)
		{// 4���E���h��
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND4);
			SelectVolume(SOUND_LABEL_R4_SE, 0.8f);
		}
		else if (nRound == 5)
		{// �t�@�C�i�����E���h��
			SetMessage(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 400.0f, 300.0f, MESSAGE_TEX_ROUND5);
			SelectVolume(SOUND_LABEL_R5_SE, 0.8f);
		}
	}

	if (g_nMessageCounter == MESSAGE_FIGHT_FRAME)
	{// �t�@�C�g����
		SetMessage(D3DXVECTOR3(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f), 400.0f, 300.0f, MESSAGE_TEX_FIGHT);
		SelectVolume(SOUND_LABEL_FIGHT_SE, 0.8f);
	}


	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == true)
		{
			switch (g_aMessage[nCntMessage].state)
			{ // ��Ԃ̏���
			case MESSAGE_STATE_SIZE_CHANGE:
				g_aMessage[nCntMessage].nStateCounter++;

				// ���̑������s��
				g_aMessage[nCntMessage].fWidth += g_aMessage[nCntMessage].fDestWidth / (float)g_aMessage[nCntMessage].nStateDestTime;
				g_aMessage[nCntMessage].fHeight += g_aMessage[nCntMessage].fDestHeight / (float)g_aMessage[nCntMessage].nStateDestTime;

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // �w�肵�����ԂɂȂ����ꍇ
				  // �ړI�̒l����
					g_aMessage[nCntMessage].fWidth = g_aMessage[nCntMessage].fDestWidth;
					g_aMessage[nCntMessage].fHeight = g_aMessage[nCntMessage].fDestHeight;
					// ��Ԃ�ҋ@��Ԃɂ���
					g_aMessage[nCntMessage].state = MESSAGE_STATE_WAIT;
					// �ړI�̎��Ԃ�ݒ�
					g_aMessage[nCntMessage].nStateDestTime = MESSAGE_WAIT_FRAME;
					// �J�E���^�[�����Z�b�g
					g_aMessage[nCntMessage].nStateCounter = 0;
				}
				break;
			case MESSAGE_STATE_WAIT:
				g_aMessage[nCntMessage].nStateCounter++;

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // �w�肵�����ԂɂȂ����ꍇ
					// �ړI�̎��Ԃ�ݒ肷��
					g_aMessage[nCntMessage].nStateDestTime = 0;
					// ��Ԃ��폜��Ԃɂ���
					g_aMessage[nCntMessage].state = MESSAGE_STATE_DELETE;
					// �ړI�̎��Ԃ�ݒ�
					g_aMessage[nCntMessage].nStateDestTime = MESSAGE_DELETE_FRAME;
					// �J�E���^�[�����Z�b�g
					g_aMessage[nCntMessage].nStateCounter = 0;
				}
				break;
			case MESSAGE_STATE_DELETE:
				g_aMessage[nCntMessage].nStateCounter++;

				g_aMessage[nCntMessage].col.a -= float(1.0f / (float)g_aMessage[nCntMessage].nStateDestTime);

				if (g_aMessage[nCntMessage].nStateCounter == g_aMessage[nCntMessage].nStateDestTime)
				{ // �w�肵�����ԂɂȂ����ꍇ
					g_aMessage[nCntMessage].bUse = false;
				}
				break;
			}

			// ���_���̍X�V(��)
			UpdateVertexMessage(nCntMessage);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// �`�揈��
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void DrawMessage(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffMessage, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == true)	// ���b�Z�[�W���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMessage[g_aMessage[nCntMessage].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMessage * 4, 2);
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���b�Z�[�W�̐ݒ�
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void SetMessage(D3DXVECTOR3 pos, float fDestWidth, float fDestHeight, MESSAGE_TEX_TYPE texType)
{
	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++)
	{
		if (g_aMessage[nCntMessage].bUse == false)
		{ // ���b�Z�[�W���g�p����Ă��Ȃ��ꍇ
		  // ���_���̐ݒ�
			g_aMessage[nCntMessage].pos = pos;
			g_aMessage[nCntMessage].nTexType = texType;
			g_aMessage[nCntMessage].fWidth = 0.0f;
			g_aMessage[nCntMessage].fHeight = 0.0f;
			g_aMessage[nCntMessage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
			g_aMessage[nCntMessage].fDestWidth = fDestWidth;
			g_aMessage[nCntMessage].fDestHeight = fDestHeight;

			// ��Ԃ��폜��Ԃɂ���
			g_aMessage[nCntMessage].state = MESSAGE_STATE_SIZE_CHANGE;
			// �ړI�̎��Ԃ�ݒ�
			g_aMessage[nCntMessage].nStateDestTime = MESSAGE_APPEAR_FRAME;
			// �J�E���^�[�����Z�b�g
			g_aMessage[nCntMessage].nStateCounter = 0;

			// ���_���̍X�V(��)
			UpdateVertexMessage(nCntMessage);

			g_aMessage[nCntMessage].bUse = true;	// �g�p�����Ԃɂ���
			break;	// ����break�͂��Ȃ���
		}
	}
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍X�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexMessage(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMessage = 0; nCntMessage < MESSAGE_MAX; nCntMessage++, pVtx += 4)
	{

		// ���_���̐ݒ�
		pVtx[0].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[1].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[2].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[3].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = g_aMessage[nCntMessage].col;
		pVtx[1].col = g_aMessage[nCntMessage].col;
		pVtx[2].col = g_aMessage[nCntMessage].col;
		pVtx[3].col = g_aMessage[nCntMessage].col;
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMessage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̌ʍX�V
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void UpdateVertexMessage(int nCntMessage)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMessage->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����i�߂�
	pVtx += 4 * nCntMessage;

	pVtx[0].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, -g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(-g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = g_aMessage[nCntMessage].pos + D3DXVECTOR3(g_aMessage[nCntMessage].fWidth / 2.0f, g_aMessage[nCntMessage].fHeight / 2.0f, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].col = g_aMessage[nCntMessage].col;
	pVtx[1].col = g_aMessage[nCntMessage].col;
	pVtx[2].col = g_aMessage[nCntMessage].col;
	pVtx[3].col = g_aMessage[nCntMessage].col;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMessage->Unlock();
}

//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
// ���_���̍쐬
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
void MakeVertexMessage(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MESSAGE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMessage,
		NULL);

	// ���_���̍X�V
	UpdateVertexMessage();
}

