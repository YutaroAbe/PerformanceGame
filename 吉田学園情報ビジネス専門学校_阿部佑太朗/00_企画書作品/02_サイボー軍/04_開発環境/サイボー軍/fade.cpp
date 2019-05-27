//=============================================================================
//
//	フェイドの処理 [fade.cpp]
// Author : YUTARO ABE
//
//=============================================================================
#include  "input.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//
//
//
LPDIRECT3DTEXTURE9 CFade::m_Texture = NULL;
//==============================================================================
//	コンストラクタ
//==============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_Texture = NULL;
	m_modenext = CManager::MODE_TITLE;
	m_fade = FADE_NONE;
}

//==============================================================================
//	デストラクタ
//==============================================================================
CFade::~CFade()
{
}

//==============================================================================
//	初期化処理
//==============================================================================
void CFade::Init(CManager::MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// 値の初期化
	m_fade = FADE_IN;	//フェードの状態に
	m_modenext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒い画面(不透明)にしておく

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	//ポジション
	pVtx[0].pos = D3DXVECTOR3(BG_WIDTH, 0, 0.0f);		 //右上
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);//右下
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);				 //左上
	pVtx[3].pos = D3DXVECTOR3(0, BG_HEIGHT, 0.0f);		 //左下
	 //RHW
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);				//右上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);				//右下
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);				//左上
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);				//左下

	//頂点バッファアンロックする
	m_pVtxBuff->Unlock();


}

//==============================================================================
//	終了処理
//==============================================================================
void CFade::Uninit(void)
{
	// テクスチャの開放
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
//	更新処理
//==============================================================================
void CFade::Update(void)
{
	// 頂点バッファの情報を設定
	VERTEX_2D*pVtx;									//頂点情報のポインタ
	//頂点バッファをロックし、頂点データへのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)	//フェード状態
		{
			m_colorFade.a -= 1.0f / 60;	//画面を透明にしておく
			m_colorFade.a -= 1.0f / 60;	//画面を透明にしておく
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;		//何もしていない状態

			}
		}
		else if (m_fade == FADE_OUT)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_PRESS);
			m_colorFade.a += 1.0f / 60;
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;	//フェード状態に

				//モードの設定
				CManager::SetMode(m_modenext);
			}
		}
		//カラー
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		//頂点バッファアンロックする
		m_pVtxBuff->Unlock();
	}
}

//==============================================================================
//	描画処理
//==============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	pDevice = pRenderer->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modenext = modeNext;

	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒い画面(透明)にしておく
}
////==============================================================================
////	プレイヤーの生成処理
////==============================================================================
//CFade *CFade::Create(CManager::MODE modenext)
//{
//	CFade *pFade = NULL;
//	if (m_fade == FADE_NONE)
//	{
//		if (pFade == NULL)
//		{
//			pFade = new CFade;						//	メモリの確保
//			if (pFade != NULL)
//			{										//	メモリの確保出来たら
//				pFade->Init(modenext);						//	メモリの初期化処理
//				m_fade = FADE_OUT;
//			}
//			else
//			{
//			}
//		}
//	}
//	return pFade;
//}

//==============================================================================
//	テクスチャを読み込む
//==============================================================================
HRESULT CFade::Laod(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FADE_0, &m_Texture);

	return S_OK;
}

//==============================================================================
//	テクスチャの開放
//==============================================================================
void CFade::UnLoad(void)
{
	//	テクスチャの破棄
	if (m_Texture != NULL)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}