//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : YUUTAROU ABE
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX_NUM (1000)
#define MAX_DROW (8)
//*****************************************************************************
//オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{//オブジェクトの種類
		OBJECT_NONE = 0,
		OBJECT_PLAYER,
		OBJECT_ENEMY,
		OBJECT_BULLET,
		OBJECT_BLOCK,
		OBJECT_ITEM,
		OBJECT_MAX
	}OBJTYPE;

	CScene(int nPriarity = 3);								//　　オーバーロードされたコンストラクタ
	CScene();												//	 コンストラクタ
	~CScene();												//	 デストラクタ
	virtual HRESULT Init(void) = 0;							//	 オブジェクトの初期化処理
	virtual void Uninit(void) = 0;							//	 オブジェクトの終了処理
	virtual void Update(void) = 0;							//	 オブジェクトの更新処理
	virtual void Draw(void) = 0;							//	 オブジェクトの描画処理
	static void UpdateAll(void);							//	 オブジェクトの全ての更新処理
	static void DrawAll(void);								//	 オブジェクトの全ての描画処理
	static void ReleaseAll(void);							//	 オブジェクトの全ての終了処理
	virtual void SetObjType(OBJTYPE Objtype);				//	 オブジェクトの種類設定
	OBJTYPE GetObjType(void);								//
	static CScene *GetScene(int nPriarity,int nIndex);					//
	void Release(void);
	static int GetNumALL(void);

protected:

private:
	//static CScene					*m_apScene[MAX_NUM];	//  静的メンバ関数 オブジェクトポインタ型のシーン
	static int m_nNumAll;									//  静的メンバ関数 オブジェクトの総数
	int m_nID;												//	自分自身の番号
	OBJTYPE m_object;										//	オブジェクトの種類
	static CScene *m_apScene[MAX_DROW][MAX_NUM];			//	優先順位用変数
	int m_nPriority;										//	優先順位の番号
	static bool m_bPasue;
};
#endif

