//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
//
// メッセージ処理 [message.h]
// Author : 圷 和也
//
//=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "main.h"
#include "player.h"

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// 構造体定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
typedef enum
{ // テクスチャの種類の列挙体
	MESSAGE_TEX_ROUND1 = 0,	// ROUND1
	MESSAGE_TEX_ROUND2,		// ROUND2
	MESSAGE_TEX_ROUND3,		// ROUND3
	MESSAGE_TEX_ROUND4,		// ROUND4
	MESSAGE_TEX_ROUND5,		// ROUND5
	MESSAGE_TEX_FIGHT,		// FIGHT
	MESSAGE_TEX_KO,			// KO
	MESSAGE_TEX_TIMEOVER,	// TIMEOVER
	MESSAGE_TEX_MAX,		// 総数
}MESSAGE_TEX_TYPE;

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// マクロ定義
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
#define MESSAGE_APPEAR_FRAME		(30)				// 出現フレーム数
#define MESSAGE_WAIT_FRAME			(30)				// 待機フレーム数
#define MESSAGE_DELETE_FRAME		(10)				// 削除フレーム数
#define MESSAGE_INFO_NUM			(2)					// インフォの数
#define MESSAGE_ROUND_FRAME			(10)				// ラウンド発生フレーム
#define MESSAGE_FIGHT_FRAME			(150)				// ファイト発生フレーム

//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
// プロトタイプ宣言
//*-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**
void InitMessage(void);
void UninitMessage(void);
void UpdateMessage(void);
void DrawMessage(void);
void SetMessage(D3DXVECTOR3 pos, float fDestWidth, float fDestHeight, MESSAGE_TEX_TYPE texType);

#endif
