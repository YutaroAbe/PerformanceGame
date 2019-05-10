//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author :　YUUTAROU ABE
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include"player.h"
#include "bullet.h"
#include "input.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数の定義
//=============================================================================
CScene *CScene::m_apScene[MAX_DROW][MAX_NUM] = {};			// ポリゴンの初期化
int CScene::m_nNumAll = 0;									// ポリゴン総数の初期化
bool CScene::m_bPasue = false;

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene::CScene()
{

}

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene::CScene(int nPriarity)
{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{//	ポリゴンの最大数分
			if (m_apScene[nPriarity][nCnt] == NULL)
			{//	何もなかったら
			 //	自分を返す
				m_apScene[nPriarity][nCnt] = this;			//　メモリを確保した分自分自身に代入する
				m_nID = nCnt;//　番号の代入指定
				m_nPriority = nPriarity;
				m_nNumAll++;								//　総数を加算
				m_object = OBJECT_NONE;
				break;
			}
		}
}

//=============================================================================
//デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//  オブジェクトの初期化処理
//=============================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}

//=============================================================================
//  オブジェクトの終了処理
//=============================================================================
void CScene::Uninit(void)
{
}

//=============================================================================
//  オブジェクトの更新処理
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
//  オブジェクトの描画処理
//=============================================================================
void CScene::Draw(void)
{
}

//=============================================================================
//	全ての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	m_bPasue = CGame::GetPause();

	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{//	ポリゴンの最大数分
			if (m_bPasue == false)
			{
				if (nCntPriority != 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	更新処理
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
			}
			else if (m_bPasue == true)
			{
				if (nCntPriority == 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	更新処理
						m_apScene[nCntPriority][nCnt]->Update();
					}
				}
			}
		}
	}
}

//=============================================================================
//	全ての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	m_bPasue = CGame::GetPause();

	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
		{
			if (m_bPasue == false)
			{
				if (nCntPriority != 7)
				{
					if (m_apScene[nCntPriority][nCnt] != NULL)
					{
						//	描画処理
						m_apScene[nCntPriority][nCnt]->Draw();
					}
				}
			}
			else if (m_bPasue == true)
			{
				if (m_apScene[nCntPriority][nCnt] != NULL)
				{
					//	更新処理
					m_apScene[nCntPriority][nCnt]->Draw();
				}
			}
		}
	}
}

//=============================================================================
//	全ての終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_DROW; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_NUM; nCnt++ )
		{
			//	シーンクラスの破棄
			if (m_apScene[nCntPriority][nCnt] != NULL)
			{
				// 終了処理
				m_apScene[nCntPriority][nCnt]->Uninit();
				//	メモリの開放
				delete m_apScene[nCntPriority][nCnt];
				//	NULLにする
				m_apScene[nCntPriority][nCnt] = NULL;
			}
		}
	}
}

//=============================================================================
//	オブシェクトの破棄
//=============================================================================
void CScene::Release(void)
{
	//	シーン2Dの破棄
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{//	指定した番号が空じゃなかったあら
		int nID;								//	保存よう変数
		int nPriority;
		nID = m_nID;							//	自分自身の番号の保存
		nPriority = m_nPriority;

		delete m_apScene[nPriority][nID];		//	指定した番号のメモリの開放//deleteをした瞬間m_nIDが不定になりNULLの代入でエラーがでる

		m_apScene[nPriority][nID] = NULL;		//	指定した番号を空にする

		m_nNumAll--;							//	指定した番号分の総数を減らす
	}
}

//=============================================================================
//	オブジェクトの種類設定
//=============================================================================
void CScene::SetObjType(OBJTYPE Objtype)
{
	m_object = Objtype;
}

//=============================================================================
//	オブジェクトの取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_object;
}

//=============================================================================
//	オブジェクトの取得
//=============================================================================
CScene * CScene::GetScene(int nPriarity, int nIndex)
{
	return m_apScene[nPriarity][nIndex];
}
//=============================================================================
//	オブジェクトの取得
//=============================================================================
int CScene::GetNumALL(void)
{
	return m_nNumAll;
}