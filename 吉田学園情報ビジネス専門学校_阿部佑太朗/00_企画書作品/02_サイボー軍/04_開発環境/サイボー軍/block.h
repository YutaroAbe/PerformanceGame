//=============================================================================
//
// プロックの処理 [blook.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define TEXTURE_NAME_BLOCK_000 "data/TEXTURE/BLOCK/block000.png"
#define TEXTURE_NAME_BLOCK_001 "data/TEXTURE/BLOCK/block001.png"
#define TEXTURE_NAME_BLOCK_002 "data/TEXTURE/BLOCK/block002.png"
#define TEXTURE_NAME_BLOCK_003 "data/TEXTURE/BLOCK/block003.png"
#define TEXTURE_NAME_BLOCK_004 "data/TEXTURE/BLOCK/block004.png"
#define TEXTURE_NAME_BLOCK_005 "data/TEXTURE/BLOCK/block005.png"
#define TEXTURE_NAME_BLOCK_006 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_007 "data/TEXTURE/BLOCK/block007.png"
#define TEXTURE_NAME_BLOCK_008 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_009 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_010 "data/TEXTURE/BLOCK/.png"
#define TEXTURE_NAME_BLOCK_011 "data/TEXTURE/BLOCK/.png"
#define BLOCK_POLIGON_X (25)		//	ブロックの横の大きさ
#define BLOCK_POLIGON_Y (25)		//	ブロックの縦の大きさ
#define MAX_BLOCK (TYPE_MAX)		//	ブロックの数

//=============================================================================
//	ブロッククラス（シーンの派生クラス）
//=============================================================================
class CBlock : public CScene2D
{
public:
	typedef enum
	{//	ブロックの種類
		TYPE_NOMAL = 0,		//	通常
		TYPE_JUMP,			//	ジャンプ台
		TYPE_L_PLAYERMOVE,	//	ベルトコンベア[左]
		TYPE_R_PLAYERMOVE,	//	ベルトコンベア[右]
		TYPE_BREAKBLOCK,	//	壊れるブロック
		TYPE_FALL,			//	落ちるブロック
		TYPE_DAMAGE,		//	ダメージ受けるブロック
		TYPE_STAGE,			//	階段用ブロック
		TYPE_ITEMBLOCK,		//	アイテムが出るブロック
		TYPE_MAX			//	種類の最大
	}BLOCK_TYPE;

	CBlock();																												//	コンストラクタ
	~CBlock();																												//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos,  float fWindth, float fHeight,int nType,float fTexSplitX, float fTexSplitY);				//	ブロックの初期化処理
	void Uninit(void);																										//	ブロックの終了処理
	void Update(void);																										//	ブロックの更新処理
	void Draw(void);																										//	ブロックの描画処理
	static CBlock *Create(D3DXVECTOR3 pos,  float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY);	//	ブロックの生成
	static HRESULT Laod(void);																								//	ブロックのテクスチャを読み込む
	static void UnLoad(void);																								//	ブロックのテクスチャの開放
	static int GetNumBlock(void);																							//	ブロックの数の取得
	static int GetTypeBlock(void);
private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_BLOCK];																			//	ブロックの共通テクスチャのポインタ
	static int m_nType;																										//	ブロックの種類
	static int m_NumBlock;																									//	ブロックの数
protected:
	float m_fWindth;																										//	ブロックの幅
	float m_fHeight;																										//	ブロックの高さ
};

//=============================================================================
//	落ちるブロッククラス（ブロックの派生クラス）
//=============================================================================
class CBlockDrop : public CBlock
{
public:
	CBlockDrop();																											//	コンストラクタ
	~CBlockDrop();																											//	デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, float fWindth, float fHeight, int nType, float fTexSplitX, float fTexSplitY);				//	ブロックの初期化処理
	void Uninit(void);																										//	ブロックの終了処理
	void Update(void);																										//	ブロックの更新処理
	void Draw(void);																										//	ブロックの描画処理
private:

};
#endif
