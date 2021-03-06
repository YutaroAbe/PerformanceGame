//*****************************************************************************
//
//				ポーズ背景の処理[pausebg.h]
//				Auther : Shun Yokomichi
//
//*****************************************************************************
#ifndef _PAUSEBG_H_
#define _PAUSEBG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2d.h"		// シーン2D

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
//		マクロ定義
//*****************************************************************************

//*****************************************************************************
//		クラス定義(背景)
//*****************************************************************************
class CPauseBg : public CScene2D
{
public:
	CPauseBg();
	~CPauseBg();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//	静的メンバ関数
	static CPauseBg * Create();

private:
};

#endif
