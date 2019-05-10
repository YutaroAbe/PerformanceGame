//=============================================================================
//
// カメラ処理 [camera.cpp]
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
// マクロ定義
//*****************************************************************************
#define CAMERA_POSV_X			(44.0f)		// カメラの初期視点[]
#define CAMERA_POSV_Y			(120.0f)	// カメラの初期視点[高さ]
#define CAMERA_POSV_Z			(-400.0f)	// カメラの初期視点[奥行]

#define CAMERA_POSR_X			(44.0f)		// カメラの初期注視点[]
#define CAMERA_POSR_Y			(128.0f)	// カメラの初期注視点[高さ]
#define CAMERA_POSR_Z			(0.0f)		// カメラの初期注視点[奥行]
#define CAMERA_m_rot_SPEED		(0.025f)	// カメラの回転速度
#define CAMERA_ZOOMIN_MAX		(50.0f)		// カメラの最大拡大距離
#define CAMERA_ZOOMOUT_MAX		(500.0f)	// カメラの最大縮小距離

#define CAMERA_AXIS_MIN			(100.0f)		//	傾きの値
#define CAMERA_SENSITEIVTY_X	(0.00004f)	//	傾きの値X
#define CAMERA_SENSITEIVTY_Y	(0.00004f)	//	傾きの値Y

#define VIEW_Y_MIN				(-0.8f)					//	カメラの角度の最小値
#define VIEW_Y_MAX				(D3DX_PI * 0.05f)		//	カメラの角度の最大値

//*****************************************************************************
//	静的メンバ変数の初期化
//*****************************************************************************
D3DXVECTOR3 CCamera::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
//	コンストラクタ
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
	{//確保分回す
		m_nCameraMove[nCount] = 0;		//	カメラを加算する変数
	}
	m_nGameCounter =0;					//	ゲームのカウント
	m_bCameraMode = false;				//	カメラのモード切替

}
//=============================================================================
//	コンストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// カメラの初期化処理
//=============================================================================
HRESULT CCamera::Init(CAMERA_MODE CameraMode)
{
	m_CameraType = CameraMode;	//	カメラの種類の設定
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

		m_fContCamSpeed = 5.0f;				// カメラの速さ上限の初期設定
		m_fCameraSpeed = 5.0f;				// カメラの速さの初期設定
		m_fCameraRotSpeed = 0.025f;			// カメラの回転動く速さ
		for (int nCount = 0; nCount < 3; nCount++)
		{//確保分回す
			m_nCameraMove[nCount] = 0;					//	カメラを加算する変数
		}
		m_nGameCounter = 0;					//	ゲームのカウント
		break;
	case CAMERATYPE_GAME:
		CPlayer *pPlayer = CGame::GetPlayer();					//	プレイヤー取得
		if (pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = pPlayer->Getpos();			//	現在の位置
			D3DXVECTOR3 PlayerPosOld = pPlayer->GetposOld();	//	過去の位置
			D3DXVECTOR3 PlayerRot = pPlayer->Getrot();			//	プレイヤーの向き
			m_posV = D3DXVECTOR3(PlayerPos.x , PlayerPos.y + CAMERA_POSV_Y, PlayerPos.z + CAMERA_POSV_Z);
			m_posR = D3DXVECTOR3(PlayerPos.x , PlayerPos.y + CAMERA_POSR_Y, PlayerPos.z + CAMERA_POSR_Z);
			m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			m_rot = D3DXVECTOR3(0.0f, atan2f((m_posV.x - m_posR.x), (m_posV.z - m_posR.z)), 0.0f);
			m_rotDest = m_rot;
			m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));

			m_fContCamSpeed = 5.0f;				// カメラの速さ上限の初期設定
			m_fCameraSpeed = 5.0f;				// カメラの速さの初期設定
			m_fCameraRotSpeed = 0.025f;			// カメラの回転動く速さ
		}
		break;
	}
	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboad = CManager::GetInputKeyboard();

	switch (m_CameraType)
	{//	カメラの種類
	case CAMERATYPE_NONE:
		break;
	case CAMERATYPE_TITLE:
		m_nGameCounter++;
		if (m_nGameCounter >= 200)
		{//	ゲームのカウンターが180以上
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
		{// カメラ前方移動	[8]
			m_posV.x += sinf(m_rot.y - D3DX_PI) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD5) == true)
		{// カメラ後方移動	[5]
			m_posV.x += sinf(m_rot.y) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD4) == true)
		{// カメラ左移動	[4]
			m_posV.x += sinf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD6) == true)
		{// カメラ右移動	[6]
			m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD7) == true)
		{// 注視点左旋回	[7]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD9) == true)
		{// 注視点右旋回	[9]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD1) == true)
		{// 視点左旋回	[1]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD3) == true)
		{// 視点右旋回	[3]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADSLASH) == true)
		{// 視点上昇	[/]
			m_posV.y += m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD0) == true)
		{// 視点下降	[0]
			m_posV.y -= m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADSTAR) == true)
		{// 注視点上昇	[*]
			m_posR.y += m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADPERIOD) == true)
		{// 注視点下降	[.]
			m_posR.y -= m_fCameraSpeed;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPADENTER) == true)
		{// 初期位置に戻す
			m_posV.x = CAMERA_POSV_X;
			m_posV.y = CAMERA_POSV_Y;
			m_posV.z = CAMERA_POSV_Z;
			m_posR.x = CAMERA_POSR_X;
			m_posR.y = CAMERA_POSR_Y;
			m_posR.z = CAMERA_POSR_Z;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADPLUS) == true)
		{//	カメラの速さの制御加算 [2 +]
			m_fContCamSpeed += 1.0f;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADMINUS) == true)
		{//	カメラの速さの制御減算 [2 -]
			m_fContCamSpeed -= 1.0f;
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADPLUS) == true)
		{//	カメラの動くスピード　[+]
			if (m_fContCamSpeed > m_fCameraSpeed)
			{//	カメラの制御の数値より小さかった場合
				m_fCameraSpeed += 1.0f;
			}
		}
		else if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADMINUS) == true)
		{//	カメラの動くスピード　[-]
			if (m_fCameraSpeed > 0.0f)
			{//	カメラの制御の数値より小さかった場合
				m_fCameraSpeed -= 1.0f;
			}
		}


		break;
	case CAMERATYPE_GAME:


		if (pInputKeyboad->GetPress(DIK_NUMPAD8) == true)
		{// カメラ前方移動	[8]
			m_posV.x += sinf(m_rot.y - D3DX_PI) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD5) == true)
		{// カメラ後方移動	[5]
			m_posV.x += sinf(m_rot.y) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD4) == true)
		{// カメラ左移動	[4]
			m_posV.x += sinf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - (-D3DX_PI * 0.5f)) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD6) == true)
		{// カメラ右移動	[6]
			m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;
			m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * m_fCameraSpeed;

			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD7) == true)
		{// 注視点左旋回	[7]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD9) == true)
		{// 注視点右旋回	[9]
			m_rot.y += m_fCameraRotSpeed;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			m_posR.x = sinf(m_rot.y - D3DX_PI) * m_fLength + m_posV.x;
			m_posR.z = cosf(m_rot.y - D3DX_PI) * m_fLength + m_posV.z;
		}
		//else if (pInputKeyboad->GetPress(DIK_NUMPAD1) == true)
		//{// 視点左旋回	[1]
		//	m_rot.y += m_fCameraRotSpeed;
		//	if (m_rot.y > D3DX_PI)
		//	{
		//		m_rot.y -= D3DX_PI * 2.0f;
		//	}
		//	m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
		//	m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		//}
		//else if (pInputKeyboad->GetPress(DIK_NUMPAD3) == true)
		//{// 視点右旋回	[3]
		//	m_rot.y -= m_fCameraRotSpeed;
		//	if (m_rot.y < -D3DX_PI)
		//	{
		//		m_rot.y += D3DX_PI * 2.0f;
		//	}

		//	m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
		//	m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		//}
		 if (pInputKeyboad->GetPress(DIK_NUMPADSLASH) == true)
		{// 視点上昇	[/]
			m_posV.y += m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD0) == true)
		{// 視点下降	[0]
			m_posV.y -= m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADSTAR) == true)
		{// 注視点上昇	[*]
			m_posR.y += m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADPERIOD) == true)
		{// 注視点下降	[.]
			m_posR.y -= m_fCameraSpeed;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPADENTER) == true)
		{// 初期位置に戻す
			m_posV.x = CAMERA_POSV_X;
			m_posV.y = CAMERA_POSV_Y;
			m_posV.z = CAMERA_POSV_Z;
			m_posR.x = CAMERA_POSR_X;
			m_posR.y = CAMERA_POSR_Y;
			m_posR.z = CAMERA_POSR_Z;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADPLUS) == true)
		{//	カメラの速さの制御加算 [2 +]
			m_fContCamSpeed += 1.0f;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) == true && pInputKeyboad->GetTrigger(DIK_NUMPADMINUS) == true)
		{//	カメラの速さの制御減算 [2 -]
			m_fContCamSpeed -= 1.0f;
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADPLUS) == true)
		{//	カメラの動くスピード　[+]
			if (m_fContCamSpeed > m_fCameraSpeed)
			{//	カメラの制御の数値より小さかった場合
				m_fCameraSpeed += 1.0f;
			}
		}
		 if (pInputKeyboad->GetPress(DIK_NUMPAD2) != true && pInputKeyboad->GetPress(DIK_NUMPADMINUS) == true)
		{//	カメラの動くスピード　[-]
			if (m_fCameraSpeed > 0.0f)
			{//	カメラの制御の数値より小さかった場合
				m_fCameraSpeed -= 1.0f;
			}
		}
		if (pInputKeyboad->GetPress(DIK_J) == true ||
			CManager::GetInputXPad()->GetPress(CInputXPad::XPADOTHER_STICK_R_RIGHT, 0) == true)
		{// 視点左旋回	[1]
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
		{// 視点右旋回	[3]
			m_rot.y -= m_fCameraRotSpeed;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			m_posV.x = sinf(m_rot.y) * m_fLength + m_posR.x;
			m_posV.z = cosf(m_rot.y) * m_fLength + m_posR.z;
		}

		CPlayer *pPlayer = CGame::GetPlayer();					//	プレイヤー取得
		if (pPlayer != NULL)
		{
			D3DXVECTOR3 PlayerPos = pPlayer->Getpos();			//	現在の位置
			D3DXVECTOR3 PlayerPosOld = pPlayer->GetposOld();	//	過去の位置
			D3DXVECTOR3 PlayerRot = pPlayer->Getrot();			//	プレイヤーの向き

			if (PlayerPosOld != PlayerPos)
			{
				//if (m_bCameraMode == false)
				{//	カメラを遠くする
					//	目的の注視点を求める
					m_posRDest = D3DXVECTOR3(PlayerPos.x + sinf(PlayerRot.y)*-25.0f, PlayerPos.y + 100, PlayerPos.z + cosf(PlayerRot.y)*-25.0f);
					//	目的の視点を求める
					m_posVDest = D3DXVECTOR3(PlayerPos.x + sinf(m_rot.y)*m_fLength, PlayerPos.y + 150.0f, PlayerPos.z + cosf(m_rot.y)*m_fLength);
				}
				//　注視点の更新 現在の注視点と目的の注視点の差分を加算する
				m_posR.x += (m_posRDest.x - m_posR.x) * 0.245f;
				m_posR.y += (m_posRDest.y - m_posR.y);
				m_posR.z += (m_posRDest.z - m_posR.z) * 0.245f;

				//	視点の更新   現在の視点と目的の視点の差分を加算する
				m_posV += (m_posVDest - m_posV)*0.3f;
			}
		}

		break;
	}


#ifdef _DEBUG
	CManager::m_CDebugProcRight->Print("\nカメラの視点  ( %.1f : %.1f  : %.1f)", m_posR.x, m_posR.y, m_posR.z);
	CManager::m_CDebugProcRight->Print("\nカメラの注視点( %.1f : %.1f  : %.1f)", m_posV.x, m_posV.y, m_posV.z);
	CManager::m_CDebugProcRight->Print("\nカメラの回転( %.2f : %.2f  : %.2f)", m_rot.x, m_rot.y, m_rot.z);
	CManager::m_CDebugProcRight->Print("\nカメラの速さ上限　(%.2f)", m_fContCamSpeed);
	CManager::m_CDebugProcRight->Print("\nカメラの速さ      (%.2f)", m_fCameraSpeed);
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_8 ] 前方移動　　");
	CManager::m_CDebugProcRight->Print("\n[ N_5 ] 後方移動　　");
	CManager::m_CDebugProcRight->Print("\n[ N_4 ] 左移動　　　");
	CManager::m_CDebugProcRight->Print("\n[ N_6 ] 右移動　　　");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_7 ] 注視点左旋回");
	CManager::m_CDebugProcRight->Print("\n[ N_9 ] 注視点右旋回");
	CManager::m_CDebugProcRight->Print("\n[ N_1 ] 視点左旋回　");
	CManager::m_CDebugProcRight->Print("\n[ N_3 ] 視点右旋回　");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_/ ] 視点の上昇  ");
	CManager::m_CDebugProcRight->Print("\n[ N_0 ] 視点の下降  ");
	CManager::m_CDebugProcRight->Print("\n[ N_* ] 注視点の上昇");
	CManager::m_CDebugProcRight->Print("\n[ N_. ] 注視点の下降");
	CManager::m_CDebugProcRight->Print("\n");
	CManager::m_CDebugProcRight->Print("\n[ N_ENTER ] 初期位置に戻す");
	CManager::m_CDebugProcRight->Print("\n[ N_+ ] カメラの速さ加算");
	CManager::m_CDebugProcRight->Print("\n[ N_- ] カメラの速さ減算");
	CManager::m_CDebugProcRight->Print("\n[ Pre N_2 & N_+ ] カメラの速さ制御加算");
	CManager::m_CDebugProcRight->Print("\n[ Pre N_2 & N_- ] カメラの速さ制御減算");

#endif
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// デバイスの取得

														// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection
		, D3DXToRadian(45.0f)							// 画角
		, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT	// 比率
		, 10.0f											// 描画範囲[手前]
		, 16000);										// 描画範囲[奥行]

														// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView
		, &m_posV
		, &m_posR
		, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}
//=============================================================================
//	カメラの回転の取得
//=============================================================================
D3DXVECTOR3 CCamera::GetCameraRotate(void)
{
	return m_rot;
}

