//=============================================================================
//
// �J�������� [camera.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_POSV_X			(44.0f)		// �J�����̏������_[]
#define CAMERA_POSV_Y			(120.0f)	// �J�����̏������_[����]
#define CAMERA_POSV_Z			(-400.0f)	// �J�����̏������_[���s]

#define CAMERA_POSR_X			(44.0f)		// �J�����̏��������_[]
#define CAMERA_POSR_Y			(128.0f)	// �J�����̏��������_[����]
#define CAMERA_POSR_Z			(0.0f)		// �J�����̏��������_[���s]
#define CAMERA_m_rot_SPEED		(0.025f)	// �J�����̉�]���x
#define CAMERA_ZOOMIN_MAX		(50.0f)		// �J�����̍ő�g�勗��
#define CAMERA_ZOOMOUT_MAX		(500.0f)	// �J�����̍ő�k������

#define CAMERA_AXIS_MIN			(100.0f)		//	�X���̒l
#define CAMERA_SENSITEIVTY_X	(0.00004f)	//	�X���̒lX
#define CAMERA_SENSITEIVTY_Y	(0.00004f)	//	�X���̒lY

#define VIEW_Y_MIN				(-0.8f)					//	�J�����̊p�x�̍ŏ��l
#define VIEW_Y_MAX				(D3DX_PI * 0.05f)		//	�J�����̊p�x�̍ő�l

//*****************************************************************************
//	�ÓI�����o�ϐ��̏�����
//*****************************************************************************
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;
	m_fLength = 0;
	m_fCameraSpeed = 0.0f;
	m_fContCamSpeed = 0.0f;
	m_fCameraRotSpeed = 0.0f;
	m_CameraType = CAMERATYPE_NONE;
	for (int nCount = 0; nCount < 3; nCount++)
	{//�m�ە���
		m_nCameraMove[nCount] = 0;		//	�J���������Z����ϐ�
	}
	m_nGameCounter =0;					//	�Q�[���̃J�E���g
	m_bCameraMode = false;				//	�J�����̃��[�h�ؑ�

}
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT CCamera::Init(CAMERA_MODE CameraMode)
{
	m_CameraType = CameraMode;	//	�J�����̎�ނ̐ݒ�
	switch (m_CameraType)
	{
	case CAMERATYPE_NONE:
		break;
	case CAMERATYPE_TITLE:
		m_posR = D3DXVECTOR3(0.0f, 25, 315);
		m_posV = D3DXVECTOR3(0.0f, 70, -85);
		m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_rot = D3DXVECTOR3(0.0f, atan2f((m_posV.x - m_posR.x), (m_posV.z - m_posR.z)), 0.0f);
		m_rotDest = m_rot;
		m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));

		m_fContCamSpeed = 5.0f;				// �J�����̑�������̏����ݒ�
		m_fCameraSpeed = 5.0f;				// �J�����̑����̏����ݒ�
		m_fCameraRotSpeed = 0.025f;			// �J�����̉�]��������
		for (int nCount = 0; nCount < 3; nCount++)
		{//�m�ە���
			m_nCameraMove[nCount] = 0;					//	�J���������Z����ϐ�
		}
		m_nGameCounter = 0;					//	�Q�[���̃J�E���g
		break;
	case CAMERATYPE_GAME:
		CPlayer *pPlayer = CGame::GetPlayer();					//	�v���C���[�擾
		if (pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = pPlayer->Getpos();			//	���݂̈ʒu
			D3DXVECTOR3 PlayerPosOld = pPlayer->GetposOld();	//	�ߋ��̈ʒu
			D3DXVECTOR3 PlayerRot = pPlayer->Getrot();			//	�v���C���[�̌���
			m_posV = D3DXVECTOR3(PlayerPos.x , PlayerPos.y + CAMERA_POSV_Y, PlayerPos.z + CAMERA_POSV_Z);
			m_posR = D3DXVECTOR3(PlayerPos.x , PlayerPos.y + CAMERA_POSR_Y, PlayerPos.z + CAMERA_POSR_Z);
			m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_rot = D3DXVECTOR3(0.0f, atan2f((m_posV.x - m_posR.x), (m_posV.z - m_posR.z)), 0.0f);
			m_rotDest = m_rot;
			m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));

			m_fContCamSpeed = 5.0f;				// �J�����̑�������̏����ݒ�
			m_fCameraSpeed = 5.0f;				// �J�����̑����̏����ݒ�
			m_fCameraRotSpeed = 0.025f;			// �J�����̉�]��������
		}
		break;
	}
	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboad = CManager::GetInputKeyboard();

	switch (m_CameraType)
	{//	�J�����̎��
	case CAMERATYPE_NONE:
		break;
	case CAMERATYPE_TITLE:
		m_nGameCounter++;
		if (m_nGameCounter >= 200)
		{//	�Q�[���̃J�E���^�[��180�ȏ�
			m_nCameraMove[0]++;
			m_posR = D3DXVECTOR3(0.0f, 25.0f, 315.0f + (float)m_nCameraMove[0]);
			m_posV = D3DXVECTOR3(0.0f, 70.0f, -85.0f + (float)m_nCameraMove[0]);
		}
		if (m_nGameCounter >= 600)
		{
			m_nCameraMove[1]++;
			m_posR = D3DXVECTOR3(-219.3f + (float)m_nCameraMove[1], 25.0f, -128.0f + (float)m_nCameraMove[1]);
			m_posV = D3DXVECTOR3(-479.5f + (float)m_nCameraMove[1], 250.0f, -431.0f + (float)m_nCameraMove[1]);
		}
		if (m_nGameCounter >= 1000)
		{
			m_nCameraMove[2]++;
			m_posR = D3DXVECTOR3(219.3f - (float)m_nCameraMove[2], 25.0f, -128.0f + (float)m_nCameraMove[2]);
			m_posV = D3DXVECTOR3(479.5f - (float)m_nCameraMove[2], 250.0f, -431.0f + (float)m_nCameraMove[2]);
		}
		if (m_nGameCounter >= 1400)
		{
			m_nGameCounter = 0;
			m_nCameraMove[0]= 0;
			m_nCameraMove[1] = 0;
			m_nCameraMove[2] = 0;
			m_posR = D3DXVECTOR3(0.0f, 25, 315);
			m_posV = D3DXVECTOR3(0.0f, 70, -85);
		}

		if (pInputKeyboad->GetPress(DIK_NUMPAD8) == true)
		{// �J�����O���ړ�	[8]
			m_posV.x += sinf(m_rot.y - D3DX_PI) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD5) == true)
		{// �J��������ړ�	[5]
			m_posV.x += sinf(m_rot.y) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD4) == true)
		{// �J�������ړ�	[4]
			m_posV.x += sinf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD6) == true)
		{// �J�����E�ړ�	[6]
			m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD7) == true)
		{// �����_������	[7]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD9) == true)
		{// �����_�E����	[9]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD1) == true)
		{// ���_������	[1]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD3) == true)
		{// ���_�E����	[3]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADSLASH) == true)
		{// ���_�㏸	[/]
			m_posV.y += m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD0) == true)
		{// ���_���~	[0]
			m_posV.y -= m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADSTAR) == true)
		{// �����_�㏸	[*]
			m_posR.y += m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADPERIOD) == true)
		{// �����_���~	[.]
			m_posR.y -= m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADENTER) == true)
		{// �����ʒu�ɖ߂�
			m_posV.x = CAMERA_POSV_X;
			m_posV.y = CAMERA_POSV_Y;
			m_posV.z = CAMERA_POSV_Z;
			m_posR.x = CAMERA_POSR_X;
			m_posR.y = CAMERA_POSR_Y;
			m_posR.z = CAMERA_POSR_Z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADPLUS) == true)
		{//	�J�����̑����̐�����Z [2 +]
			m_fContCamSpeed += 1.0f;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADMINUS) == true)
		{//	�J�����̑����̐��䌸�Z [2 -]
			m_fContCamSpeed -= 1.0f;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADPLUS) == true)
		{//	�J�����̓����X�s�[�h�@[+]
			if (m_fContCamSpeed > m_fCameraSpeed)
			{//	�J�����̐���̐��l��菬���������ꍇ
				m_fCameraSpeed += 1.0f;
			}
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADMINUS) == true)
		{//	�J�����̓����X�s�[�h�@[-]
			if (m_fCameraSpeed > 0.0f)
			{//	�J�����̐���̐��l��菬���������ꍇ
				m_fCameraSpeed -= 1.0f;
			}
		}


		break;
	case CAMERATYPE_GAME:


		if (pInputKeyboad->GetPress(DIK_NUMPAD8) == true)
		{// �J�����O���ړ�	[8]
			m_posV.x += sinf(m_rot.y - D3DX_PI) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD5) == true)
		{// �J��������ړ�	[5]
			m_posV.x += sinf(m_rot.y) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD4) == true)
		{// �J�������ړ�	[4]
			m_posV.x += sinf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD6) == true)
		{// �J�����E�ړ�	[6]
			m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD7) == true)
		{// �����_������	[7]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD9) == true)
		{// �����_�E����	[9]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		//else if (pInputKeyboad->GetPress(DIK_NUMPAD1) == true)
		//{// ���_������	[1]
		//	m_rot.y += m_fCameraRotSpeed;
		//	if (m_rot.y > D3DX_PI)
		//	{
		//		m_rot.y -= D3DX_PI * 2.0f;
		//	}
		//	m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
		//	m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		//}
		//else if (pInputKeyboad->GetPress(DIK_NUMPAD3) == true)
		//{// ���_�E����	[3]
		//	m_rot.y -= m_fCameraRotSpeed;
		//	if (m_rot.y < -D3DX_PI)
		//	{
		//		m_rot.y += D3DX_PI * 2.0f;
		//	}

		//	m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
		//	m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		//}
		 if (pInputKeyboad->GetPress(DIK_NUMPADSLASH) == true)
		{// ���_�㏸	[/]
			m_posV.y += m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD0) == true)
		{// ���_���~	[0]
			m_posV.y -= m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADSTAR) == true)
		{// �����_�㏸	[*]
			m_posR.y += m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADPERIOD) == true)
		{// �����_���~	[.]
			m_posR.y -= m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADENTER) == true)
		{// �����ʒu�ɖ߂�
			m_posV.x = CAMERA_POSV_X;
			m_posV.y = CAMERA_POSV_Y;
			m_posV.z = CAMERA_POSV_Z;
			m_posR.x = CAMERA_POSR_X;
			m_posR.y = CAMERA_POSR_Y;
			m_posR.z = CAMERA_POSR_Z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADPLUS) == true)
		{//	�J�����̑����̐�����Z [2 +]
			m_fContCamSpeed += 1.0f;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADMINUS) == true)
		{//	�J�����̑����̐��䌸�Z [2 -]
			m_fContCamSpeed -= 1.0f;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADPLUS) == true)
		{//	�J�����̓����X�s�[�h�@[+]
			if (m_fContCamSpeed > m_fCameraSpeed)
			{//	�J�����̐���̐��l��菬���������ꍇ
				m_fCameraSpeed += 1.0f;
			}
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADMINUS) == true)
		{//	�J�����̓����X�s�[�h�@[-]
			if (m_fCameraSpeed > 0.0f)
			{//	�J�����̐���̐��l��菬���������ꍇ
				m_fCameraSpeed -= 1.0f;
			}
		}
		if (pInputKeyboad->GetPress(DIK_J) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_R_RIGHT, 0) == true)
		{// ���_������	[1]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}
		else if (pInputKeyboad->GetPress(DIK_H) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_R_LEFT, 0) == true)
		{// ���_�E����	[3]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}

		CPlayer *pPlayer = CGame::GetPlayer();					//	�v���C���[�擾
		if (pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = pPlayer->Getpos();			//	���݂̈ʒu
			D3DXVECTOR3 PlayerPosOld = pPlayer->GetposOld();	//	�ߋ��̈ʒu
			D3DXVECTOR3 PlayerRot = pPlayer->Getrot();			//	�v���C���[�̌���

			if (PlayerPosOld != PlayerPos)
			{
				//if (m_bCameraMode == false)
				{//	�J��������������
					//	�ړI�̒����_�����߂�
					m_posRDest = D3DXVECTOR3(PlayerPos.x + sinf(PlayerRot.y)*-25.0f, PlayerPos.y + 100, PlayerPos.z + cosf(PlayerRot.y)*-25.0f);
					//	�ړI�̎��_�����߂�
					m_posVDest = D3DXVECTOR3(PlayerPos.x + sinf(m_rot.y)*m_fLength, PlayerPos.y + 150.0f, PlayerPos.z + cosf(m_rot.y)*m_fLength);
				}
				//�@�����_�̍X�V ���݂̒����_�ƖړI�̒����_�̍��������Z����
				m_posR.x += (m_posRDest.x - m_posR.x) * 0.245f;
				m_posR.y += (m_posRDest.y - m_posR.y);
				m_posR.z += (m_posRDest.z - m_posR.z) * 0.245f;

				//	���_�̍X�V   ���݂̎��_�ƖړI�̎��_�̍��������Z����
				m_posV += (m_posVDest - m_posV)*0.3f;
			}
		}

		break;
	}


#ifdef _DEBUG
	CManager::m_CDebugProcRight->Print("\n�J�����̎��_  ( %.1f : %.1f  : %.1f)", m_posR.x, m_posR.y, m_posR.z);
	CManager::m_CDebugProcRight->Print("\n�J�����̒����_( %.1f : %.1f  : %.1f)", m_posV.x, m_posV.y, m_posV.z);
	CManager::m_CDebugProcRight->Print("\n�J�����̉�]( %.2f : %.2f  : %.2f)", m_rot.x, m_rot.y, m_rot.z);
	CManager::m_CDebugProcRight->Print("\n�J�����̑�������@(%.2f)", m_fContCamSpeed);
	CManager::m_CDebugProcRight->Print("\n�J�����̑���      (%.2f)", m_fCameraSpeed);
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_8 ] �O���ړ��@�@");
	CManager::m_CDebugProcRight->Print("\n[ N_5 ] ����ړ��@�@");
	CManager::m_CDebugProcRight->Print("\n[ N_4 ] ���ړ��@�@�@");
	CManager::m_CDebugProcRight->Print("\n[ N_6 ] �E�ړ��@�@�@");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_7 ] �����_������");
	CManager::m_CDebugProcRight->Print("\n[ N_9 ] �����_�E����");
	CManager::m_CDebugProcRight->Print("\n[ N_1 ] ���_������@");
	CManager::m_CDebugProcRight->Print("\n[ N_3 ] ���_�E����@");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_/ ] ���_�̏㏸  ");
	CManager::m_CDebugProcRight->Print("\n[ N_0 ] ���_�̉��~  ");
	CManager::m_CDebugProcRight->Print("\n[ N_* ] �����_�̏㏸");
	CManager::m_CDebugProcRight->Print("\n[ N_. ] �����_�̉��~");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_ENTER ] �����ʒu�ɖ߂�");
	CManager::m_CDebugProcRight->Print("\n[ N_+ ] �J�����̑������Z");
	CManager::m_CDebugProcRight->Print("\n[ N_- ] �J�����̑������Z");
	CManager::m_CDebugProcRight->Print("\n[ Pre N_2 & N_+ ] �J�����̑���������Z");
	CManager::m_CDebugProcRight->Print("\n[ Pre N_2 & N_- ] �J�����̑������䌸�Z");

#endif
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

														// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection
		, D3DXToRadian(45.0f)							// ��p
		, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT	// �䗦
		, 10.0f											// �`��͈�[��O]
		, 16000);										// �`��͈�[���s]

														// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView
		, &m_posV
		, &m_posR
		, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}
//=============================================================================
//	�J�����̉�]�̎擾
//=============================================================================
D3DXVECTOR3 CCamera::GetCameraRotate(void)
{
	return m_rot;
}

