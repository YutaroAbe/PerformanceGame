//=============================================================================
//
// UI処理 [ui.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene2d.h"	// シーン2D
#include "manager.h"	// マネージャー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UI_TEXMAX		(54)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPause;
class CBullet3D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CUI : public CScene2D
{// UI クラス
public:
	CUI();											// コンストラクタ
	~CUI();											// デストラクタ

	static HRESULT Load(CManager::MODE mode);		// ロード
	static void Unload(void);						// アンロード
													// 生成
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col ,D3DXVECTOR2 uv , int nType);
													// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR col, D3DXVECTOR2 uv, int nType);
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	static void CreateMode(CManager::MODE mode);
	static bool GetTutoEnd(void) { return m_bTutoEnd; }	//	チュートリアルの文字出しが終わった時
													//	セレクトモードの番号
	static int GetSelectNUM(void) { return m_nNumSelectMode; }
	static int GetNumTxst(void) { return m_nNextTxst; }	//
private:
	static LPDIRECT3DTEXTURE9	m_pTexture[UI_TEXMAX];		//  テクスチャ情報へのポインタ
	int m_nType;											//  種類
	int m_nCounterAnim;										//	アニメーション用カウンター
	int m_nPatternAnim;										//	アニメーションパターン
	D3DXVECTOR3 m_sizeOld;									//	初期の大きさの取得
	bool m_bFlash;											//	点滅
	static CManager::MODE m_mode;							//	ゲームのモード
	static int  	m_nNumSelectMode;						//	セレクト番号
	float			m_fFrameValue;							//	フレームの値
	bool			m_bPressButton;							//	ボタン押したかどうか
	static int		m_nNextTxst;							//	チュートリアルの表記設定
	int				m_nCutTuto;								//	チュートリアルのカウンター
	bool			m_bSize ;								//	大きさの変化
	int				m_nPlayerLife;							//	プレイヤーの体力
	int				m_nPlayerLifeOld ;						//	プレイヤーの体力の保存
	int				m_nPlayerLifeMax;						//	プレイヤーの体力の最大
	bool			m_nPlayerSquat;							//	プレイヤーがステルスしているかどうか
	bool			m_nPlayerDash;							//	プレイヤーがステルスしているかどうか
	D3DXVECTOR3		m_InitPos;								//	最初の位置
	static bool		m_bTutoEnd;								//	チュートリアルかどうか
	bool			m_bTutoOperation;						//	チュートリアルの操作説明描画するかしないか
	CBullet3D		*m_Bullet3D;							//	弾3D
	bool			m_bColChange;							//	色を変えるかどうか

	int				m_nStealthLifeMax;						//	プレイヤーのステルスの寿命最大
	int				m_nStealthLife;							//	プレイヤーのステルスの寿命最大
	int				m_nStealthCut;							//	プレイヤーのステルスのカウンター

	int				m_nDashLifeMax;							//	プレイヤーのダッシュの寿命最大
	int				m_nDashLife;							//	プレイヤーのダッシュの寿命最大
	int				m_nDashCut;								//	プレイヤーのダッシュのカウンター
protected:

};

#endif