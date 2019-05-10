//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// カメラ処理 [camera.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MAX_CAMERA	(3)		// カメラの最大数

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// カメラの構造体
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posVDest;		// 目的の視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 posRDest;		// 目的の注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス（テレビのような物
	D3DXMATRIX mtxView;			// ビューマトリックス（カメラマンのような物
	D3DXVECTOR3 rot;			// 角度
	D3DXVECTOR3 rotDest;		// 目的の角度
	float fLength;				// 長さ
	float fHeight;				// 高さ
	D3DVIEWPORT9 viewport;		// ビューポート
}Camera;

typedef enum
{ // バトルモードのカメラの列挙体
	BATTLE_CAMERA_TYPE_MAIN = 0,	// メインカメラ
	BATTLE_CAMERA_TYPE_MAX,			// 総数
}BATTLE_CAMERA_TYPE;

typedef enum
{ // プレイヤーショウモードのカメラの列挙体
	PLAYERSHOW_CAMERA_TYPE_PLAYER01 = 0,	// 1Pビューポートカメラ
	PLAYERSHOW_CAMERA_TYPE_PLAYER02,		// 2Pビューポートカメラ
	PLAYERSHOW_CAMERA_TYPE_3DUI,			// 3DUIビューポートカメラ
	PLAYERSHOW_CAMERA_TYPE_MAX,		// 総数
}PLAYERSHOW_CAMERA_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdyCamera);
Camera *GetCamera(void);
#endif
