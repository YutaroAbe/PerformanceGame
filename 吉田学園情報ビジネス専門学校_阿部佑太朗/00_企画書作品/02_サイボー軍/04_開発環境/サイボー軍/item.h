//=============================================================================
//
// アイテムの処理 [item.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_ITEM_HP "data/TEXTURE/ITEM/HP000.png"
#define TEXTURE_NAME_ITEM_001 "data/TEXTURE/ITEM/001.jpg"
#define TEXTURE_NAME_ITEM_002 "data/TEXTURE/ITEM/002.png"
#define TEXTURE_NAME_ITEM_003 "data/TEXTURE/ITEM/003.png"
#define TEXTURE_NAME_ITEM_004 "data/TEXTURE/ITEM/004.png"
#define ITEM_POLIGON_X (25)
#define ITEM_POLIGON_Y (25)
#define MAX_TEX_ITEM (4)

//=============================================================================
//	プレイヤークラス（シーンの派生クラス）
//=============================================================================
class CItem : public CScene2D
{
public:
	CItem();																								//	コンストラクタ
	~CItem();																								//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos,int nType);																//	アイテムの初期化処理
	void Uninit(void);																						//	アイテムの終了処理
	void Update(void);																						//	アイテムの更新処理
	void Draw(void);																						//	アイテムの描画処理
	static CItem *Create(D3DXVECTOR3 pos, int nType);														//	アイテムの生成
	static HRESULT Laod(void);																				//	テクスチャを読み込む
	static void UnLoad(void);																				//	テクスチャの開放
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEX_ITEM];														//	共通テクスチャのポインタ
	int m_nType;																							//	種類
};
#endif
