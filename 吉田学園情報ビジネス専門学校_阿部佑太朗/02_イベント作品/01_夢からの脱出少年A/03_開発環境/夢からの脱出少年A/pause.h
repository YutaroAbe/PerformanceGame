//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PAUSE_H_	//二重インクルード防止のマクロ定義
#define _PAUSE_H_

#include "main.h"

//=============================================================================
//								マクロ定義
//=============================================================================
#define PAUSE_TEXTURE_001 "data/TEXTURE/pause100.png"	  //背景に貼るテクスチャ
#define PAUSE_TEXTURE_002 "data/TEXTURE/Tutorial004.jpg"	  
#define PAUSE_TEXTURE_003 "data/TEXTURE/pause000.png"	  
#define PAUSE_TEXTURE_004 "data/TEXTURE/pause002.png"	

#define PAUSE_POS_X (330)					  //X座標		
#define PAUSE_POS_Y (100)					  //Y座標					
#define PAUSE_WIDTH (900)		
#define PAUSE_HEIGHT (480)

#define PAUSE_COL_A (0.3f)		//画面の色.a
//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
//void SerectReset(void);
//void DispReset(void);
#endif // !_PAUSE_H_

