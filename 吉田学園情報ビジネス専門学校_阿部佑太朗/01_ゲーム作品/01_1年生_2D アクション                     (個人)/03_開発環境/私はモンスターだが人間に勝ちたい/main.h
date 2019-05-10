//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author : ABE YUUTAROU
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"								//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)			//ビルド時の警告対処用マクロ
#include "dinput.h"								//入力時に必要
#include "xaudio2.h"							//サウンド処理に必要

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")					//描画処理に必要
#pragma comment(lib,"d3dx9.lib")				//[d3d9]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")				//directtxコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")				//システム時刻取得に必要
#pragma comment(lib, "dinput8.lib")				//入力時に必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)					// ウインドウの幅
#define SCREEN_HEIGHT	(720)					// ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //頂点座標　｜　頂点カラー | テクスチャ座標

//*****************************************************************************
//構造体定義
//*****************************************************************************
typedef enum
{
	MODE_TITLE = 0,
	MODE_SELECT,
	MODE_ARASU,
	MODE_GAME,
	MODE_GAME2,
	MODE_GAME3,
	MODE_TUTO,
	MODE_RESULT,
	MODE_CLIA,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;							//頂点座標
	float rhw;									//1.0ｆで固定
	D3DCOLOR col;								//頂点カラー
	D3DXVECTOR2 tex;							//テクスチャ座標

}VERTEX_2D;
//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void SetMode(MODE mode);
MODE GetMode(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif