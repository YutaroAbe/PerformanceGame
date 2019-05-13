//=============================================================================
//
// カメラ処理 [camera.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef enum
{// カメラの種類
	CAMERATYPE_MAIN = 0,	// メイン
	CAMERATYPE_EVENT,		// イベント用
	CAMERATYPE_MAX			// 種類の総数
} CAMERATYPE;

typedef struct
{
	D3DXVECTOR3	posV;			// 現在の視点
	D3DXVECTOR3	posR;			// 現在の注視点
	D3DXVECTOR3	posVDest;		// 目的の視点
	D3DXVECTOR3	posRDest;		// 目的の注視点
	D3DXVECTOR3	vecU;			// 上方向ベクトル
	D3DXMATRIX	mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX	mtxView;		// ビューマトリックス
	D3DXVECTOR3	rot;			// 現在の向き
	D3DXVECTOR3	rotDest;		// 目的の向き
	float		fLength;		// 注視点と視点の距離
	int			nCntStop;		// 停止時間
	bool		bOperation;		// 操作可能かどうか
	D3DVIEWPORT9 Viewport;		//ビューポート
} Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int IdxViewport);
Camera *GetCamera(void);

#endif
