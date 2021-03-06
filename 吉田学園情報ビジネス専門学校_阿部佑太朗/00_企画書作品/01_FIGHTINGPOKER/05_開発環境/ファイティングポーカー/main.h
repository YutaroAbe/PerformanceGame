//=============================================================================
//
// メイン処理 [main.h]
// Author : 舘田 翼
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"
#include "xaudio2.h"
//*****************************************************************************
// ライブラリファイル
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// ウインドウの幅
#define SCREEN_HEIGHT	(720)	// ウインドウの高さ

// 2D
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// 3D
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

 // 2Dポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

// 3Dポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
typedef enum
{
	MODE_TITLE = 0,
	MODE_SELECT,
	MODE_RULE,
	MODE_CREDIT,
	MODE_GAME,
	MODE_MAX
}MODE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
int GetNowRound(void);
#endif