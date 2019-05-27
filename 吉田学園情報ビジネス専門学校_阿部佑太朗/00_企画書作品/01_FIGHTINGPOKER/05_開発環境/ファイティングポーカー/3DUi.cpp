
//=============================================================================
//
// 3DUI���� [3DUi.cpp]
// Author : Ebina Riku
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "camera.h"
#include "poker.h"
#include "3DUi.h"
#include "cardModel.h"
#include "fade.h"
#include "gamefade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOAD_CURSOR		"data/MODEL/cursor.x"	// �ǂݍ���X�t�@�C����
#define LOAD_KEY		"data/MODEL/key_0.25.x"	// �ǂݍ���X�t�@�C����
#define MAX_MODEL		(2)						// ���f���̍ő吔
#define LOCK_SPACE		(100.0f)				// ���̃X�y�[�X
#define CURSOR_SPACE	(85.0f)					// �J�[�\���̃X�y�[�X
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI_3D g_aUi[MAX_MODEL];			// ���f���̍\����(����)
P3DUI g_pUi[MAX_MODEL];			// ���f���̍\����(���)
//=============================================================================
// ����������
//=============================================================================
void Init3DUI(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���(�J�[�\��)
#if 1
	D3DXLoadMeshFromX(LOAD_CURSOR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pUi[0].pBuffMat,
		NULL,
		&g_pUi[0].nNumMat,
		&g_pUi[0].pMesh);
#endif
	// X�t�@�C���̓ǂݍ���(���}�[�N)
#if 1
	D3DXLoadMeshFromX(LOAD_KEY,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pUi[1].pBuffMat,
		NULL,
		&g_pUi[1].nNumMat,
		&g_pUi[1].pMesh);
#endif
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// �����ݒ�
		g_aUi[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}
//=============================================================================
// �I������
//=============================================================================
void Uninit3DUI(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pUi[nCnt].pTexture != NULL)
		{
			g_pUi[nCnt].pTexture->Release();
			g_pUi[nCnt].pTexture = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// ���b�V���̊J��
		if (g_pUi[nCnt].pMesh != NULL)
		{
			g_pUi[nCnt].pMesh->Release();
			g_pUi[nCnt].pMesh = NULL;
		}
		// �}�e���A���̊J��
		if (g_pUi[nCnt].pBuffMat != NULL)
		{
			g_pUi[nCnt].pBuffMat->Release();
			g_pUi[nCnt].pBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update3DUI(void)
{
	CARDSIDE side = GetPokerState();				// �|�[�J�[�̏�Ԏ擾
	D3DXVECTOR3 LockPos1P = GetLockPos1P(4);		// 1P���}�[�N
	D3DXVECTOR3 LockPos2P = GetLockPos2P(4);		// 2P���}�[�N
	D3DXVECTOR3 g_ButtonPos1P = GetLockPos1P(2);	// �����{�^��
	D3DXVECTOR3 g_ButtonPos2P = GetLockPos2P(2);	// �����{�^��
	bool bSetFinish = GetSet();						// �z�z���ꂽ��
	int nSelectCard = GetNum();						// ���Ԃ̃J�[�h��I��ł��邩

	GAMEFADE pGameFade;
	pGameFade = GetGameFade();
	if (bSetFinish == true)
	{
		if (side == CARD_SIDE_1P)
		{// 1P
			D3DXVECTOR3 CursorPos1P = GetCardPos1P(nSelectCard);
			g_aUi[0].pos.x = CursorPos1P.x;
			g_aUi[0].pos.z = CursorPos1P.z - CURSOR_SPACE;
			g_aUi[0].rot.y = 0.0f;
			g_aUi[1].pos.x = LockPos1P.x;
			g_aUi[1].pos.z = LockPos1P.z + LOCK_SPACE;
		}
		else if (side == CARD_SIDE_2P)
		{// 2P
			D3DXVECTOR3 CursorPos2P = GetCardPos2P(nSelectCard);
			g_aUi[0].pos.x = CursorPos2P.x;
			g_aUi[0].pos.z = CursorPos2P.z + CURSOR_SPACE;
			g_aUi[0].rot.y = D3DX_PI * 1.0f;
			g_aUi[1].pos.x = LockPos2P.x;
			g_aUi[1].pos.z = LockPos2P.z - LOCK_SPACE;
			g_aUi[1].rot.y = D3DX_PI * 1.0f;;
		}
		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			g_aUi[nCnt].bUse = true;
		}
	}
	if (pGameFade == GAMEFADE_OUT)
	{
		for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
		{
			g_aUi[nCnt].bUse = false;
		}
	}
	if (pGameFade == GAMEFADE_IN)
	{
		if (bSetFinish == true)
		{
			g_aUi[0].bUse = true;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void Draw3DUI(void)
{
	GAMEMODE GameMode = GetGameMode();
	CARDSIDE side = GetPokerState();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aUi[nCnt].bUse == true && GameMode == GAMEMODE_POKER)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aUi[nCnt].mtxWorldUI);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aUi[nCnt].rot.y,						// Y,X,Z�̏���
				g_aUi[nCnt].rot.x,
				g_aUi[nCnt].rot.z);

			D3DXMatrixMultiply(&g_aUi[nCnt].mtxWorldUI,
				&g_aUi[nCnt].mtxWorldUI,
				&mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_aUi[nCnt].pos.x,
				g_aUi[nCnt].pos.y,
				g_aUi[nCnt].pos.z);

			D3DXMatrixMultiply(&g_aUi[nCnt].mtxWorldUI,
				&g_aUi[nCnt].mtxWorldUI,
				&mtxTrans);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pUi[nCnt].pBuffMat->GetBufferPointer();

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aUi[nCnt].mtxWorldUI);

			for (int nCntMat = 0; nCntMat < (int)g_pUi[nCnt].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pUi[nCnt].pTexture);

				// ���f��(�p�[�c)�̕`��
				g_pUi[nCnt].pMesh->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
